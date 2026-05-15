#include "runtime.h"

const RuntimeConfig gRuntimeConfig __attribute__((section(".runtime_config"))) = {
    .restore_life_points_after_duel = TRUE,
    .cap_life_points_after_duel = FALSE,
    .max_duelist_level_at_start = TRUE,
    .max_deck_capacity_at_start = TRUE,
    .max_money_at_start = FALSE,
    .disable_ban_list = TRUE,
    .skip_opening_sequence = TRUE,
    .turn_off_visual_scanner = TRUE,
    .disable_element_system = FALSE,
    .dynamic_card_shop_and_trunk_sorting = FALSE, // Needs more work
    .start_with_three_copies_of_every_card = FALSE,
    .allow_ante_with_one_copy_of_card = TRUE,
    .allow_sell_one_copy_of_card = TRUE,
    .repeatable_opponent_capacity_reward = 10,
    .story_opponent_capacity_reward = 30,
    .alternate_win_reward_multiplier = 3,
};
