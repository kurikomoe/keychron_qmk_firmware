# VIA_ENABLE = yes
OPT_DEFS += -DDYNAMIC_KEYMAP_LAYER_COUNT=5

DEBOUNCE_TYPE = asym_eager_defer_pk

# LEADER_ENABLE = no
COMBO_ENABLE = yes
LTO_ENABLE = yes

SRC += key_logger.c \
	   key_logger_shared.c
