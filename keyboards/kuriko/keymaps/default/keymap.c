/* Copyright 2021 @ Keychron (Modified for Kuriko DZ60) */

#include QMK_KEYBOARD_H

// 确保包含您的 logger 头文件
// #include "key_logger.h"

// 声明外部变量
extern uint8_t mk_max_speed;

static bool is_keyboard_locked = false;
static bool is_win_locked = false;

// 自定义键码
enum custom_keycodes {
    KEY_LOG_DUMP = SAFE_RANGE,
    KEY_LOCK_KB,
    KEY_LOCK_WIN,
    KEY_MS_SPD,
};

// 层级定义
enum layers {
    _WIN_BASE, // Layer 0
    _WIN_FN1,  // Layer 1
    _FN2       // Layer 2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Layer 0: Windows Base
     * LFn (MO 1) -> 左下角 LCtrl 位置
     * RFn (MO 2) -> 空格右侧 RAlt 位置
     */
    [_WIN_BASE] = LAYOUT(
        KC_ESC,       KC_1,         KC_2,    KC_3,       KC_4,          KC_5,    KC_6,    KC_7,    KC_8,     KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,       KC_Q,         KC_W,    KC_E,       KC_R,          KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS,      KC_A,         KC_S,    KC_D,       KC_F,          KC_G,    KC_H,    KC_J,    KC_K,     KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,      KC_Z,         KC_X,    KC_C,       KC_V,          KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_DEL,
        MO(_WIN_FN1), KC_LALT,      KC_LGUI,                            KC_SPC,                    MO(_FN2), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Layer 1: Win Fn
     * 对应您的 [WIN_FN1]
     * 注意：Delete 键放在了右上角 (原 K6 灯光键位置调整)
     */
    [_WIN_FN1] = LAYOUT(
        KC_GRV,       KC_F1,        KC_F2,   KC_F3,      KC_F4,         KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KEY_LOCK_KB,
        KC_TRNS,      KC_TRNS,      MS_UP,   KEY_MS_SPD, KC_CAPS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,   KC_TRNS, KC_PSCR, KC_BRIU, KC_BRID, KEY_LOG_DUMP,
        KC_TRNS,      MS_LEFT,      MS_DOWN, MS_RGHT,   MS_WHLD,       KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,    KC_RGHT, KC_HOME, KC_END,           KC_TRNS,
        KC_TRNS,      MS_BTN1,      MS_BTN3, MS_BTN2,    MS_WHLU,       KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLD,  KC_VOLU, KC_TRNS, KC_HOME, MS_UP,   KC_END,
        KC_TRNS,      KC_TRNS,      KEY_LOCK_WIN,                       KC_TRNS,                              KEY_LOCK_KB, KC_APP,  MS_LEFT, MS_DOWN, MS_RGHT
    ),

    /* Layer 2: Functional Layer
     * 严格对应您的 [FN2]
     * 1-4 被设为 KC_NO (抛弃 BT/BAT)
     * Caps/LShift 被设为 KC_NO (抛弃 LNG1/2)
     * LCtrl 位置 -> KEY_LOCK_KB
     * Backspace 位置 -> KEY_LOCK_KB (对应 K6 右上角)
     * 增加了 QK_BOOT 在回车键，防止无法刷机
     */
    [_FN2] = LAYOUT(
        S(KC_GRV),   S(KC_F1),     S(KC_F2), S(KC_F3),   S(KC_F4),    S(KC_F5), S(KC_F6),  S(KC_F7), S(KC_F8),  S(KC_F9),  S(KC_F10), S(KC_F11), S(KC_F12),  KEY_LOCK_KB,
        KC_TRNS,     KC_GRV,       MS_UP,    KEY_MS_SPD, KC_CAPS,     KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,
        KC_LNG1,     MS_LEFT,      MS_DOWN,  MS_RGHT,    MS_WHLD,     KC_TRNS,  KC_LEFT,   KC_DOWN,  KC_UP,     KC_RGHT,   KC_HOME,   KC_END,                QK_BOOT,
        KC_LNG2,     MS_BTN1,      MS_BTN3,  MS_BTN2,    MS_WHLU,      KC_NO,    KC_TRNS,   KC_MUTE,  KC_VOLD,   KC_VOLU,   KC_TRNS,   KC_HOME,   KC_TRNS,    KC_END,
        KEY_LOCK_KB, KC_TRNS,      KC_TRNS,                        KC_TRNS,                                     KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS
    )
};

// --- 核心逻辑 ---

void keyboard_post_init_user(void) {
    // logger_init();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // 1. 键盘锁定逻辑 (优先级最高)
    if (is_keyboard_locked) {
        // 唯一能解锁的键
        if (keycode == KEY_LOCK_KB) {
            if (record->event.pressed) {
                is_keyboard_locked = false;
            }
            return false;
        }
        // 允许层级切换，否则锁在层内出不去
        switch (keycode) {
            case MO(_WIN_FN1):
            case MO(_FN2):
                return true;
        }
        // 拦截其他所有按键
        if (record->event.pressed) {
            return false;
        }
    }

    // 2. Win键锁定
    if (is_win_locked && (keycode == KC_LWIN || keycode == KC_RWIN)) {
        return false;
    }

    if (record->event.pressed) {
        switch (keycode) {
            case KEY_LOCK_KB:
                is_keyboard_locked = true;
                return false;

            case KEY_LOCK_WIN:
                is_win_locked = !is_win_locked;
                return false;

            case KEY_MS_SPD: {
                static uint8_t speed_stage = 0;
                speed_stage = (speed_stage + 1) % 3;
                if (speed_stage == 0) mk_max_speed = 16;      // 慢
                else if (speed_stage == 1) mk_max_speed = 32; // 中
                else mk_max_speed = 64;                       // 快
                return false;
            }

            // case KEY_LOG_DUMP:
            //     logger_dump_sorted();
            //     return false;

            default:
                // log_key_press(keycode);
                return true;
        }
    }
    return true;
}

// void housekeeping_task_user(void) {
//     logger_task();
// }

// void suspend_power_down_user(void) {
//     logger_save_now();
// }
