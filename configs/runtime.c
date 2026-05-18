#include "runtime.h"

const RuntimeConfig gRuntimeConfig __attribute__((section(".runtime_config"))) = {
    .restore_life_points_after_duel = TRUE,
    .cap_life_points_after_duel = FALSE,
    .max_duelist_level_at_start = TRUE,
    .max_deck_capacity_at_start = TRUE,
    .max_deck_cards = 40,
    .max_money_at_start = FALSE,
    .disable_ban_list = TRUE,
    .skip_opening_sequence = TRUE,
    .turn_off_visual_scanner = TRUE,
    .disable_element_system = FALSE,
    .duel_fields_start_on_arena = TRUE,
    .dynamic_card_shop_and_trunk_sorting = FALSE, // Needs more work
    .faster_walking_speed = 2,
    .start_with_three_copies_of_every_card = TRUE,
    .randomize_card_costs_at_start = TRUE,
    .enable_custom_cards_past_800 = FALSE,
    .enable_custom_decks = TRUE,
    .allow_ante_with_one_copy_of_card = TRUE,
    .allow_sell_one_copy_of_card = TRUE,
    .add_all_cards_in_deck_to_trunk = TRUE,
    .repeatable_opponent_capacity_reward = 10,
    .story_opponent_capacity_reward = 30,
    .alternate_win_reward_multiplier = 3,
    .instant_win_with_l_button = TRUE,
    .card_in_hand = SHIELD_AND_SWORD
};
