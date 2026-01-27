#pragma once
// #pragma message("Applying custom mousekey configuration for VIA Logger keymap")

// 1. 默认模式：纯色常亮
#undef RGB_MATRIX_DEFAULT_MODE
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
// 2. 默认颜色：白色
// Hue (色相): 0 (白色不看色相)
// Sat (饱和度): 0 (0 就是纯白/无色，255 是最艳)
#undef RGB_MATRIX_DEFAULT_HUE
#define RGB_MATRIX_DEFAULT_HUE 0
#undef RGB_MATRIX_DEFAULT_SAT
#define RGB_MATRIX_DEFAULT_SAT 0
// 3. 默认亮度：50%
// 范围 0-255，50% 约为 128
#undef RGB_MATRIX_DEFAULT_VAL
#define RGB_MATRIX_DEFAULT_VAL 128
// 4. 默认速度 (保持中等即可)
#undef RGB_MATRIX_DEFAULT_SPD
#define RGB_MATRIX_DEFAULT_SPD 128

// --- 鼠标键手感调优 (4K/2.5K 优化版) ---

// 1. 极速响应
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0        // 按下即动，无延迟
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 16    // 16ms ≈ 60fps 刷新率，保证高分屏下的丝滑感

// 2. 速度设置 (核心调整)
// 默认是 7，对于 4K 屏来说太慢了。
// 建议设置为 14-16。这样在最高速时，每帧移动 16 像素，一秒移动约 1000 像素。
// 划过 4K 屏幕宽度 (3840) 大约需要 3-4 秒，这是一个比较舒适的节奏。
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 16

// 3. 加速曲线 (核心调整)
// 默认是 60。因为我们提高了最大速度，如果加速太快，稍微一按光标就飞了，没法精准点击。
// 建议稍微延长加速时间到 100-120 (约 1.5 - 2 秒达到极速)。
// 这样您短按时依然是慢速，适合点按钮；长按时才会飙车。
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 100

// 4. 滚轮设置 (4K 屏网页通常很长，建议加快)
// |Define                      |Default|Description                                              |
// |----------------------------|-------|---------------------------------------------------------|
// |`MOUSEKEY_DELAY`            |10     |Delay between pressing a movement key and cursor movement|
// |`MOUSEKEY_INTERVAL`         |20     |Time between cursor movements in milliseconds            |
// |`MOUSEKEY_MOVE_DELTA`       |8      |Step size                                                |
// |`MOUSEKEY_MAX_SPEED`        |10     |Maximum cursor speed at which acceleration stops         |
// |`MOUSEKEY_TIME_TO_MAX`      |30     |Time until maximum cursor speed is reached               |
// |`MOUSEKEY_WHEEL_DELAY`      |10     |Delay between pressing a wheel key and wheel movement    |
// |`MOUSEKEY_WHEEL_INTERVAL`   |80     |Time between wheel movements                             |
// |`MOUSEKEY_WHEEL_MAX_SPEED`  |8      |Maximum number of scroll steps per scroll action         |
// |`MOUSEKEY_WHEEL_TIME_TO_MAX`|40     |Time until maximum scroll speed is reached               |
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 10
#undef MOUSEKEY_WHEEL_INTERVAL
#define MOUSEKEY_WHEEL_INTERVAL 80
#undef MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 8 // 默认是 8，稍微加一点
#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40


// 判定阈值 (默认 200ms)
// 意思是：按住按键超过 200ms，就被认为是“按住”；否则认为是“点击”。
// 如果您打字很快，觉得按住 Fn 键反应太慢，可以减小到 175 或 150。
#undef TAPPING_TERM
#define TAPPING_TERM 150

// 激进保持 (Permissive Hold)
// 如果您开启了这个，当您按下 "Mod-Tap键" + "其他键" 时，
// 即使您按住的时间没到 200ms，QMK 也会立刻判定为“按住”。
// 推荐开启：这能显著减少快速打字时的误触（比如想按 Ctrl+C，结果打出了 c）。
#undef PERMISSIVE_HOLD
#define PERMISSIVE_HOLD

// 去抖动时间 (ms)
// 默认通常是 5ms。
// 如果您的轴体状态很好（不是那种用了几年的老轴），可以尝试改到 3ms 甚至 1ms。
// 效果：按键响应会变快几毫秒，玩游戏更跟手。
// 风险：如果改太小 (0或1)，可能会出现“按一下出两个字”的双击问题。
#undef DEBOUNCE
#define DEBOUNCE 5  // 保守建议 5，激进建议 3

// 组合键判定窗口 (ms)
// 默认 50ms。意思是您必须在 50ms 内同时按下两个键。
// 如果您经常按不出组合键，可以把这个值改大一点 (例如 60 或 80)。
#undef COMBO_TERM
#define COMBO_TERM 50

#define COMBO_ONLY_FROM_LAYER 0


// Hardware specific
#undef USB_POLLING_INTERVAL_MS
#define USB_POLLING_INTERVAL_MS 1

#undef DEBOUNCE

#undef MATRIX_IO_DELAY
#define MATRIX_IO_DELAY 5
