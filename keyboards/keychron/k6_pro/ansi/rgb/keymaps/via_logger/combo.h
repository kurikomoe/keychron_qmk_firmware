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
extern const uint16_t PROGMEM combo_rfn_h[];
extern const uint16_t PROGMEM combo_rfn_j[];
extern const uint16_t PROGMEM combo_rfn_k[];
extern const uint16_t PROGMEM combo_rfn_l[];
extern const uint16_t PROGMEM combo_rfn_scln[];
extern const uint16_t PROGMEM combo_rfn_quot[];

extern const uint16_t PROGMEM combo_space_h[];
extern const uint16_t PROGMEM combo_space_j[];
extern const uint16_t PROGMEM combo_space_k[];
extern const uint16_t PROGMEM combo_space_l[];
extern const uint16_t PROGMEM combo_space_scln[];
extern const uint16_t PROGMEM combo_space_quot[];

// 注册 Combo 对应的输出结果
extern combo_t key_combos[];
extern uint16_t COMBO_LEN;
