#pragma GCC push_options
#pragma GCC optimize ("O3")

#include "quantum.h"
#include "k6_pro.h"

#include "key_defs.h"
#include "combo.h"

const uint16_t PROGMEM combo_rfn_h[]    = {KC_RFN, KC_H, COMBO_END};
const uint16_t PROGMEM combo_rfn_j[]    = {KC_RFN, KC_J, COMBO_END};
const uint16_t PROGMEM combo_rfn_k[]    = {KC_RFN, KC_K, COMBO_END};
const uint16_t PROGMEM combo_rfn_l[]    = {KC_RFN, KC_L, COMBO_END};
const uint16_t PROGMEM combo_rfn_scln[] = {KC_RFN, KC_SCLN, COMBO_END};
const uint16_t PROGMEM combo_rfn_quot[] = {KC_RFN, KC_QUOT, COMBO_END};

const uint16_t PROGMEM combo_space_h[]    = {KC_SPACE, KC_H, COMBO_END};
const uint16_t PROGMEM combo_space_j[]    = {KC_SPACE, KC_J, COMBO_END};
const uint16_t PROGMEM combo_space_k[]    = {KC_SPACE, KC_K, COMBO_END};
const uint16_t PROGMEM combo_space_l[]    = {KC_SPACE, KC_L, COMBO_END};
const uint16_t PROGMEM combo_space_scln[] = {KC_SPACE, KC_SCLN, COMBO_END};
const uint16_t PROGMEM combo_space_quot[] = {KC_SPACE, KC_QUOT, COMBO_END};

combo_t key_combos[] = {
    // [CMB_RFN_H_LEFT]    = COMBO(combo_rfn_h,    KC_LEFT),
    // [CMB_RFN_J_DOWN]    = COMBO(combo_rfn_j,    KC_DOWN),
    // [CMB_RFN_K_UP]      = COMBO(combo_rfn_k,    KC_UP),
    // [CMB_RFN_L_RGHT]    = COMBO(combo_rfn_l,    KC_RGHT),
    [CMB_RFN_SCLN_HOME] = COMBO(combo_rfn_scln, KC_HOME),
    [CMB_RFN_QUOT_END]  = COMBO(combo_rfn_quot, KC_END),

    // [CMB_SPACE_H_LEFT]    = COMBO(combo_space_h,    KC_LEFT),
    // [CMB_SPACE_J_DOWN]    = COMBO(combo_space_j,    KC_DOWN),
    // [CMB_SPACE_K_UP]      = COMBO(combo_space_k,    KC_UP),
    // [CMB_SPACE_L_RGHT]    = COMBO(combo_space_l,    KC_RGHT),
    // [CMB_SPACE_SCLN_HOME] = COMBO(combo_space_scln, KC_HOME),
    // [CMB_SPACE_QUOT_END]  = COMBO(combo_space_quot, KC_END),
};
uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(key_combos[0]);

// 当 Combo 触发按下时：强制开启 FN2 层
// void process_combo_event(uint16_t combo_index, bool pressed) {
//     // 只有在按下瞬间处理
//     if (pressed) {
//         switch(combo_index) {
//             // 把你所有涉及 RFn 的 Combo 都列在这里
//             case CMB_RFN_H_LEFT:
//             case CMB_RFN_J_DOWN:
//             case CMB_RFN_K_UP:
//             case CMB_RFN_L_RGHT:
//             case CMB_RFN_SCLN_HOME:
//             case CMB_RFN_QUOT_END:
//                 layer_on(FN2); // 手动开启层
//                 break;
//         }
//     }
// }

// 当 Combo 的按键被释放时：强制关闭 FN2 层
// bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
//     if (keycode == KEY_FN_CUSTOM) {
//         layer_off(FN2);
//     }
//     return false;
// }
