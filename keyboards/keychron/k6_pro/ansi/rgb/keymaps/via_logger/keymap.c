/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#include "via.h"
#include "mousekey.h"

#include "key_logger.h"

static bool is_keyboard_locked = false;
static bool is_win_locked = false;

// 定义自定义键值
enum custom_keycodes {
    KEY_LOG_DUMP = NEW_SAFE_RANGE, // 从安全范围开始定义
    KEY_LOCK_KB,
    KEY_LOCK_WIN,
    KEY_MS_SPD,
};

// clang-format off
enum layers{
  MAC_BASE,
  WIN_BASE,
  MAC_FN1,
  WIN_FN1,
  FN2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC_BASE] = LAYOUT_ansi_68(
     KC_ESC,      KC_1,       KC_2,       KC_3,        KC_4,          KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC, RGB_TOG,
     KC_TAB,      KC_Q,       KC_W,       KC_E,        KC_R,          KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS, KC_DEL,
     KC_LCTL,     KC_A,       KC_S,       KC_D,        KC_F,          KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,      KC_ENT,        KC_PGUP,
     KC_LSFT,     KC_Z,       KC_X,       KC_C,        KC_V,          KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,          KC_UP,      KC_PGDN,
     MO(MAC_FN1), KC_LOPTN,   KC_LCMMD,                                         KC_SPC,                       MO(FN2),  KC_RALT,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[WIN_BASE] = LAYOUT_ansi_68(
     KC_ESC,      KC_1,       KC_2,       KC_3,        KC_4,          KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC, RGB_TOG,
     KC_TAB,      KC_Q,       KC_W,       KC_E,        KC_R,          KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS, KC_DEL,
     KC_LCTL,     KC_A,       KC_S,       KC_D,        KC_F,          KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,  KC_PGUP,
     KC_LSFT,     KC_Z,       KC_X,       KC_C,        KC_V,          KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,             KC_UP,  KC_PGDN,
     MO(WIN_FN1), KC_LALT,    KC_LGUI,                                        KC_SPC,                         MO(FN2),  KC_RALT,  KC_RCTL,  KC_LEFT,  KC_DOWN, KC_RGHT),

// left Fn
[MAC_FN1] = LAYOUT_ansi_68(
     KC_GRV,      KC_BRID,    KC_BRIU,    KC_MCTL,     KC_LPAD,       RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,  RGB_TOG,
     KC_TRNS,     BT_HST1,    BT_HST2,    BT_HST3,     KC_TRNS,       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     RGB_TOG,     RGB_MOD,    RGB_VAI,    RGB_HUI,     RGB_SAI,       RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
     KC_TRNS,     RGB_RMOD,   RGB_VAD,    RGB_HUD,     RGB_SAD,       RGB_SPD,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,     KC_TRNS,    KC_TRNS,                                KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

// left Fn
[WIN_FN1] = LAYOUT_ansi_68(
     KC_GRV,      KC_F1,      KC_F2,      KC_F3,       KC_F4,         KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_DEL,  KEY_LOCK_KB,
     KC_TRNS,     KC_TRNS,    KC_MS_UP,   KEY_MS_SPD,     KC_CAPS,       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_INS,   KC_TRNS,  KC_PSCR,  KC_BRIU,  KC_BRID, KC_TRNS, KEY_LOG_DUMP,
     KC_LNG1,     KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_WH_DOWN, KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_HOME,  KC_END,      KC_TRNS,          QK_BOOTLOADER,
     KC_LNG2,     KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2,  KC_MS_WH_UP,   BAT_LVL,  KC_TRNS,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,  KC_HOME,              RGB_VAI, KC_END,
     KC_TRNS,     KC_TRNS,    KEY_LOCK_WIN,                           KC_TRNS,                                KEY_LOCK_KB,KC_TRNS,KC_APP,  RGB_MOD,    RGB_VAD, RGB_RMOD),

// Right Fn
[FN2] = LAYOUT_ansi_68(
     S(KC_GRV),   BT_HST1,    BT_HST2,    BT_HST3,     BAT_LVL,       KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,  KEY_LOCK_KB,
     KC_TRNS,     KC_GRV,     KC_MS_UP,   KEY_MS_SPD,  KC_CAPS,       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_INS,   KC_TRNS,  KC_PSCR,  KC_BRIU,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_LNG1,     KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_WH_DOWN, KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_HOME,  KC_END,         KC_TRNS,      KC_TRNS,
     KC_LNG2,     KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2,  KC_MS_WH_UP,   BAT_LVL,  KC_TRNS,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,  KC_HOME,            KC_TRNS,  KC_TRNS,
     KEY_LOCK_KB, KC_TRNS,    KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),
};

// 1. 初始化
void keyboard_post_init_user(void) {
    logger_init();
}

// 2. 记录按键
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (is_keyboard_locked) {
        if (keycode == KEY_LOCK_KB) {
            if (record->event.pressed) {
                is_keyboard_locked = false;
            }
            return false;
        }

        switch (keycode) {
            case MO(MAC_FN1):
            case MO(WIN_FN1):
            case MO(FN2):
                return true;
        }
        if (record->event.pressed) {
            return false;
        }
    }

    if (is_win_locked && (keycode == KC_LWIN || keycode == KC_RWIN)) {
        return false; // 拦截Win键
    }

    if (record->event.pressed) {
        switch (keycode) {
            case KEY_LOCK_KB: {
                is_keyboard_locked = true;
                return false;
            }
            case KEY_LOCK_WIN: {
                is_win_locked = !is_win_locked;
                return false;
            }
            case KEY_MS_SPD: {
                static uint8_t speed_stage = 0;
                speed_stage = (speed_stage + 1) % 3;

                if (speed_stage == 0) mk_max_speed = 16;     // 慢 (默认)
                else if (speed_stage == 1) mk_max_speed = 8; // 中 (2K屏)
                else mk_max_speed = 4;                       // 快 (4K屏)
                uprintf("Mouse Key Speed set to %u\n", mk_max_speed);
                return false;
            }
            case KEY_LOG_DUMP: {
                // logger_dump_all(); // 导出数据
                logger_dump_sorted(); // 导出排序后的数据
                return false;
            }
            default: {
                log_key_press(keycode);
                return true;
            }
        }
    }
    return true;
}
// 3. 定时任务
void housekeeping_task_user(void) {
    logger_task();
}
// 4. 休眠保存
void suspend_power_down_user(void) {
    logger_save_now();
}
