#include "storage.h"
#include "key_logger.h"


storage_t storage;

void save_storage(void) {
    eeprom_write_block(
        &storage,
        (void*)STORAGE_ADDR_BASE,
        sizeof(storage_t)
    );
}

void load_storage(void) {
    eeprom_read_block(
        &storage,
        (void*)STORAGE_ADDR_BASE,
        sizeof(storage_t)
    );
    if (storage.magic != STORAGE_MAGIC) {
        // 未初始化，设置默认值
        storage.magic = STORAGE_MAGIC;
        storage.version = STORAGE_VERSION;
        storage.is_swap_ralt_rfn = false;
        memset(&storage.logger_data, 0, sizeof(logger_store_t));
        save_storage();
    }
}
