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
    u8 cards[NUM_CARDS];
} CardU8Table;

typedef struct {
    u16 cards[NUM_CARDS];
} CardU16Table;

typedef struct {
    u32 cards[NUM_CARDS];
} CardU32Table;

extern const CardU16Table gCardAtks_NEW;
extern const CardU8Table gCardAttributes_NEW;
extern const CardU8Table gCardColors_NEW;
extern const CardU32Table gCardCosts_NEW;
extern const CardU16Table gCardDefs_NEW;
extern const CardU8Table gCardLevels_NEW;
extern const CardU8Table gCardMagicEffect_NEW;
extern const CardU8Table gCardMonsterEffects_NEW;
extern const CardU8Table gCardTrapEffect_NEW;
extern const CardU8Table gCardTypes_NEW;
