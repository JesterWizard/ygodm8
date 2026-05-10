#include "gba/types.h"
#include "gba/defines.h"

typedef struct {
    u8 restore_life_points_after_duel;
    u8 max_duelist_level_at_start;
    u8 max_deck_capacity_at_start;
    u8 max_money_at_start;
    u8 disable_ban_list;
    u8 skip_opening_sequence;
    u8 turn_off_visual_scanner;
    u8 dynamic_card_shop_and_trunk_sorting;
    u8 start_with_three_copies_of_every_card;
    u8 repeatable_opponent_capacity_reward;
    u8 story_opponent_capacity_reward;
} RuntimeConfig;

/*
 * Build-time PC port settings.
 * Toggle these before building to change default runtime behavior.
 */

extern const RuntimeConfig gRuntimeConfig;


#define _maybe_unused __attribute__((unused))

#define LYN_REPLACE_CHECK(name) \
    extern __typeof__(name) name; \
    static const void *const _maybe_unused lyn_exists_check_##name = &name

#define APPEND_TEXT __attribute__((section(".append_text")))
#define APPEND_RODATA __attribute__((section(".append_rodata")))
#define APPEND_ASSET __attribute__((section(".append_assets")))
#define APPEND_DATA __attribute__((section(".append_data")))

typedef struct {
    u16 atk;
    u16 def;
    u32 cost;
    u8 attribute;
    u8 level;
    u8 type;
    u8 color;
    u8 monsterEffect;
    u8 spellEffect;
    u8 trapEffect;
} CardData;

extern const CardData gCardData_NEW[NUM_CARDS];
