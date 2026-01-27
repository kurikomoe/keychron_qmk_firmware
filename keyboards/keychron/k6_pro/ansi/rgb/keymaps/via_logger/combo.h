#pragma once

#include "quantum.h"
#include "process_combo.h"

#include "key_defs.h"

// Combo 的枚举 ID
enum combos {
    CMB_RFN_H_LEFT,
    CMB_RFN_J_DOWN,
    CMB_RFN_K_UP,
    CMB_RFN_L_RGHT,
    CMB_RFN_SCLN_HOME,
    CMB_RFN_QUOT_END,

    CMB_SPACE_H_LEFT,
    CMB_SPACE_J_DOWN,
    CMB_SPACE_K_UP,
    CMB_SPACE_L_RGHT,
    CMB_SPACE_SCLN_HOME,
    CMB_SPACE_QUOT_END
};

// 定义参与 Combo 的按键组合
// 注意：这里必须填你在 BASE 层上实际看到的按键 Keycode
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

// 注册 Combo 对应的输出结果
combo_t key_combos[] = {
    [CMB_RFN_H_LEFT]    = COMBO(combo_rfn_h,    KC_LEFT),
    [CMB_RFN_J_DOWN]    = COMBO(combo_rfn_j,    KC_DOWN),
    [CMB_RFN_K_UP]      = COMBO(combo_rfn_k,    KC_UP),
    [CMB_RFN_L_RGHT]    = COMBO(combo_rfn_l,    KC_RGHT),
    [CMB_RFN_SCLN_HOME] = COMBO(combo_rfn_scln, KC_HOME),
    [CMB_RFN_QUOT_END]  = COMBO(combo_rfn_quot, KC_END),

    [CMB_SPACE_H_LEFT]    = COMBO(combo_space_h,    KC_LEFT),
    [CMB_SPACE_J_DOWN]    = COMBO(combo_space_j,    KC_DOWN),
    [CMB_SPACE_K_UP]      = COMBO(combo_space_k,    KC_UP),
    [CMB_SPACE_L_RGHT]    = COMBO(combo_space_l,    KC_RGHT),
    [CMB_SPACE_SCLN_HOME] = COMBO(combo_space_scln, KC_HOME),
    [CMB_SPACE_QUOT_END]  = COMBO(combo_space_quot, KC_END),
};
uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(key_combos[0]);
