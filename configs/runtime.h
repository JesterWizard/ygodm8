#ifndef GUARD_RUNTIME_CONFIG_H
#define GUARD_RUNTIME_CONFIG_H

#include "gba/types.h"
#include "gba/defines.h"
#include "constants/card_ids.h"

typedef struct {
    u8 restore_life_points_after_duel;
    u8 cap_life_points_after_duel;
    u8 preserve_life_points_above_8000_after_duel; // Keep duel LP above 8000 when saving.
    u8 return_home_after_defeat; // Return home after losing regular overworld duels.
    u8 max_duelist_level_at_start;
    u8 max_deck_capacity_at_start;
    u8 max_deck_cards;
    u8 max_money_at_start;
    u8 disable_ban_list;
    u8 skip_opening_sequence;
    u8 turn_off_visual_scanner;
    u8 disable_element_system;
    u8 duel_fields_start_on_arena; // Force duel starts onto the arena field.
    u8 dynamic_card_shop_and_trunk_sorting;
    u8 dynamic_card_shop_costs; // Use card cost * 40 for shop pricing.
    u8 faster_walking_speed;
    u8 start_shop_with_one_copy_of_every_card;
    u8 start_with_three_copies_of_every_card;
    u8 randomize_card_costs_at_start;
    u8 enable_custom_cards_past_800;
    u8 enable_custom_decks;
    u8 allow_ante_with_one_copy_of_card;
    u8 allow_sell_one_copy_of_card;
    u8 add_all_cards_in_deck_to_trunk;
    u8 repeatable_opponent_capacity_reward;
    u8 story_opponent_capacity_reward;
    u8 alternate_win_reward_multiplier;
    u8 discount_shop_costs_by_duelist_level; // 5% off buy price per 100 duelist levels.
    u8 instant_win_with_l_button; // L in duel -> immediate player win.
    u8 enable_world_map_thought_bubbles; // L on world map toggles thought bubble sprite.
    u8 enable_password_terminal_feedback; // Show password result popup and charge only on valid passwords.
    u16 card_in_hand;
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
    u8 password[8];
    const u8 *description;
} CardData;

extern const CardData gCardData_NEW[];

#endif
