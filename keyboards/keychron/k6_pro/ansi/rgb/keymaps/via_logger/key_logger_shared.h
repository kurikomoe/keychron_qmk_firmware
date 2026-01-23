#pragma once

// 监控范围：0 - 120 (覆盖所有标准键位)
// 占用空间：121 * 4 = 484 Bytes
#define MAX_LOG_KEY 120

// VIA 协议常量
#define LOGGER_MAGIC 0x2233  // 2bytes
#define VERSION 1            // 2bytes

#define VIA_ID_CUSTOM_GET_VALUE 0x08
#define VIA_LOGGER_CHANNEL_ID   0x55
