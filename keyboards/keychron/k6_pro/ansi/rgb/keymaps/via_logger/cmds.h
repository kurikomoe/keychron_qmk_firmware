#pragma once
#include "quantum.h"

static inline void send_sysrq_cmd(uint8_t key) {
    register_code(KC_LALT);
    register_code(KC_PSCR);
    tap_code(key);
    unregister_code(KC_PSCR);
    unregister_code(KC_LALT);
}

// ============ exports ==========
static inline void cmd_test(void) {
    SEND_STRING("Hello From QMKuriko!");
}

static inline void safe_linux_reboot(void) {
    // R: unRaw (把键盘控制权从 X Server 抢回)
    send_sysrq_cmd(KC_R);
    wait_ms(50);
    // E: tErminate (给所有进程发送 SIGTERM，让它们有机会保存数据)
    send_sysrq_cmd(KC_E);
    wait_ms(1000); // 等待 1秒，给程序关闭的时间
    // I: kIll (给剩下的进程发送 SIGKILL，强制关闭)
    send_sysrq_cmd(KC_I);
    wait_ms(100);
    // S: Sync (非常重要！把缓存中的数据写入硬盘)
    send_sysrq_cmd(KC_S);
    wait_ms(2000); // 等待 2秒，确保数据写完
    // U: Unmount (以只读模式重新挂载文件系统)
    send_sysrq_cmd(KC_U);
    wait_ms(1000); // 等待 1秒
    // B: reBoot (重启)
    send_sysrq_cmd(KC_B);
}
