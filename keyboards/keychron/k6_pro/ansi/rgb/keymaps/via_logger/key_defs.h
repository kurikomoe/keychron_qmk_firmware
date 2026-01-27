#pragma once

// 定义自定义键值
enum custom_keycodes {
    KEY_LOG_DUMP = NEW_SAFE_RANGE, // 从安全范围开始定义
    KEY_LOCK_KB,
    KEY_LOCK_WIN,
    KEY_MS_SPD,
    KEY_FN_CUSTOM,
};

// clang-format off
enum layers{
  MAC_BASE,
  WIN_BASE,
  MAC_FN1,
  WIN_FN1,
  FN2
};

#define KC_RFN KEY_FN_CUSTOM
