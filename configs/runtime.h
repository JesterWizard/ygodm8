#include "gba/types.h"
#include "gba/defines.h"

typedef struct {
    bool8 restore_life_points_after_duel;
    bool8 max_duelist_level_at_start;
    bool8 max_deck_capacity_at_start;
    bool8 max_money_at_start;
    bool8 skip_opening_sequence;
} RuntimeConfig;

/*
 * Build-time PC port settings.
 * Toggle these before building to change default runtime behavior.
 */

extern const RuntimeConfig gRuntimeConfig;


#define _maybe_unused __attribute__((unused))

#define LYN_REPLACE_CHECK(name) \
    extern void name(void); \
    static const void *const _maybe_unused lyn_exists_check_##name = &name

#define APPEND_TEXT __attribute__((section(".append_text")))
#define APPEND_RODATA __attribute__((section(".append_rodata")))
#define APPEND_ASSET __attribute__((section(".append_assets")))
#define APPEND_DATA __attribute__((section(".append_data")))
