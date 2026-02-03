#pragma GCC push_options
#pragma GCC optimize ("O3")
#include <string.h> // for memset

#include "quantum.h"
#include "via.h"

#include "storage.h"

#include "key_logger.h"
#include "key_logger_shared.h"

// EEPROM 偏移量：设为 1536 (1.5KB)
// 空间计算：1536 (Start) + 488 (Size) = 2024 < 2048 (Limit) -> 安全
#define EEPROM_LOGGER_OFFSET 1536

// 策略参数
// 自动保存间隔
// 检查频率：每 1 分钟检查一次 (读取 RAM，不耗寿命)
#define CHECK_INTERVAL 60000
// 高水位线：积压超过 5000 次 -> 强制保存
#define THRESHOLD_HIGH 5000
// 低水位线：积压超过 100 次 -> 准备闲时保存
#define THRESHOLD_LOW 100
// 闲时判定：5 分钟无操作
#define IDLE_TIMEOUT 300000




// RAM 缓冲区
#define log_store (storage.logger_data)

static bool is_dirty = false;
static uint32_t unsaved_count = 0;
static uint32_t last_check_time = 0;
static uint32_t last_keypress_time = 0;

// --- 实现 ---
void logger_init(void) {
    // 2. 检查魔数和版本号
    if (log_store.magic != LOGGER_MAGIC || log_store.version != VERSION) {
        uprintf("Logger: First run or version mismatch, initializing EEPROM...\n");
        log_store.magic = LOGGER_MAGIC;
        log_store.version = VERSION;
        log_store.writes = 0;
        memset(log_store.counts, 0, sizeof(log_store.counts));
        // 立即写入初始化状态
        save_storage();
    } else {
        uprintf("Logger: Loaded from EEPROM.\n");
    }

    // 初始化时间戳，防止刚开机就触发闲时保存
    last_check_time = last_keypress_time = timer_read32();
}

// 记录按键函数
void log_key_press(uint16_t keycode) {
    if (keycode <= MAX_LOG_KEY) {
        log_store.counts[keycode]++;
        unsaved_count++;

        last_keypress_time = timer_read32();
        is_dirty = true;
    }
}

// logger_save_now 函数
void logger_save_now(void) {
    if (is_dirty) {
        uprintf("Logger: Saving %lu keys to EEPROM.\n", unsaved_count);
        log_store.writes++;
        save_storage();
        is_dirty = false;
        unsaved_count = 0;
    }
}

// 任务循环
void logger_task(void) {
    // 每 1 分钟醒来检查一次
    if (timer_elapsed32(last_check_time) > CHECK_INTERVAL) {
        last_check_time = timer_read32();

        // 场景 A: 疯狂打字模式 (高水位)
        if (unsaved_count >= THRESHOLD_HIGH) {
            logger_save_now();
            return;
        }

        // 场景 B: 休息摸鱼模式 (智能闲时保存)
        if (unsaved_count >= THRESHOLD_LOW &&
            timer_elapsed32(last_keypress_time) > IDLE_TIMEOUT) {
            logger_save_now();
            return;
        }
    }
}

void logger_dump_all(void) {
    uprintf("\n--- KEY LOGGER REPORT ---\n");
    uprintf("Magic: 0x%x, Ver: %u, Writes: %u\n",
        log_store.magic, log_store.version, log_store.writes);
    uint32_t total_keys = 0;
    for (int i = 0; i <= MAX_LOG_KEY; i++) {
        if (log_store.counts[i] > 0) {
            print_key_name(i);
            uprintf(", %lu\n", log_store.counts[i]);
            total_keys += log_store.counts[i];
        }
    }
    uprintf("Total Key Presses Logged: %lu\n", total_keys);
    uprintf("--- END REPORT ---\n");
}

typedef struct {
    uint8_t keycode;
    uint32_t count;
} key_sort_entry_t;

int compare_entries(const void *a, const void *b) {
    key_sort_entry_t *entry_a = (key_sort_entry_t *)a;
    key_sort_entry_t *entry_b = (key_sort_entry_t *)b;

    if (entry_a->count < entry_b->count) return -1;
    if (entry_a->count > entry_b->count) return 1;
    return 0;
}

void logger_dump_sorted(void) {
    static key_sort_entry_t entries[MAX_LOG_KEY + 1];
    int valid_count = 0;
    uint32_t total_keys = 0;
    for (int i = 0; i <= MAX_LOG_KEY; i++) {
        if (log_store.counts[i] > 0) {
            entries[valid_count].keycode = i;
            entries[valid_count].count = log_store.counts[i];
            total_keys += log_store.counts[i];
            valid_count++;
        }
    }
    qsort(entries, valid_count, sizeof(key_sort_entry_t), compare_entries);
    uprintf("\n--- KEY LOGGER REPORT (SORTED ASC) ---\n");
    uprintf("Magic: 0x%x, Ver: %u, Writes: %u\n",
        log_store.magic, log_store.version, log_store.writes);
    uprintf("Key, Count\n");
    for (int i = 0; i < valid_count; i++) {
        print_key_name(entries[i].keycode);
        uprintf(", %lu\n", entries[i].count);
    }

    uprintf("Total: %lu\n", total_keys);
    uprintf("--- END REPORT ---\n");
}

// 内部处理逻辑
void logger_via_handler(uint8_t *data, uint8_t length) {
    uint8_t key_idx = data[2];

    if (key_idx <= MAX_LOG_KEY) {
        uint32_t count = log_store.counts[key_idx];
        data[2] = (count >> 24) & 0xFF;
        data[3] = (count >> 16) & 0xFF;
        data[4] = (count >> 8) & 0xFF;
        data[5] = (count >> 0) & 0xFF;
    } else {
        data[2] = 0xFF; data[3] = 0xFF; data[4] = 0xFF; data[5] = 0xFF;
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *channel_id = &(data[1]);

    // 指令 ID 必须是 0x08，且频道 ID 必须是 0x55
    if (*command_id == VIA_ID_CUSTOM_GET_VALUE
        && *channel_id == VIA_LOGGER_CHANNEL_ID)
    {
        logger_via_handler(data, length);
        return;
    }

    *command_id = id_unhandled;
}
