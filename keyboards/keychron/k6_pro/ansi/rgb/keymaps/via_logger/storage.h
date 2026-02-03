#pragma once

#include "quantum.h"
#include "eeprom.h"

#include <assert.h>

#include "key_logger.h"

#define STORAGE_MAGIC   0x0514
#define STORAGE_VERSION 0x0001

#define STORAGE_ADDR_BASE 1400

// --- 数据结构 ---
// 总大小 = 2(magic) + 2(version) + 484(counts) = 488 字节
// 1536 + 488 = 2024 < 2048 (安全)
typedef struct {
    uint16_t magic;                   // 2 Bytes
    uint16_t version;                 // 2 bytes
    uint16_t writes;                  // 2 Bytes 继续写入次数
    uint32_t counts[MAX_LOG_KEY + 1]; // 484 Bytes
} logger_store_t;

#pragma pack(push, 1)
typedef struct Storage {
    uint16_t magic;                   // 2 Bytes
    uint16_t version;                 // 2 bytes
    logger_store_t logger_data;
    bool is_swap_ralt_rfn;
} storage_t;
#pragma pack(pop)
static_assert(
    STORAGE_ADDR_BASE + sizeof(storage_t) <= 2048,
    "Storage exceeds EEPROM size");

extern storage_t storage;

void save_storage(void);

void load_storage(void);
