#pragma once
#include "quantum.h"

#include "key_logger_shared.h"

// 初始化 Logger
void logger_init(void);
// 记录按键
void log_key_press(uint16_t keycode);
// 定时任务 (检查是否需要自动保存)
void logger_task(void);
// 强制保存 (用于休眠前)
void logger_save_now(void);
// 打印所有统计数据到控制台
void logger_dump_all(void);
// VIA 协议处理函数
void logger_via_handler(uint8_t *data, uint8_t length);
