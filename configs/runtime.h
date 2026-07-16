#ifndef GUARD_RUNTIME_CONFIG_H
#define GUARD_RUNTIME_CONFIG_H

#include "gba/types.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef struct {
    u8 restore_life_points_after_duel;
    u8 cap_life_points_after_duel;
    u8 preserve_life_points_above_8000_after_duel; // Keep duel LP above 8000 when saving.
    u16 set_life_points_after_duel; // Overworld LP on new game and after duels; 0 keeps vanilla behavior.
    u8 return_home_after_defeat; // Return home after losing regular overworld duels.
    u8 offer_duel_retry_after_defeat; // Prompt to restart the duel immediately after losing.
    u8 max_duelist_level_at_start;
    u8 max_deck_capacity_at_start;
    u8 max_deck_cards;
    u8 max_money_at_start;
    u8 disable_ban_list;
    u8 skip_opening_sequence;
    u8 enable_custom_opening_screens; // Replace boot copyright splashes with custom PNGs.
    u8 enable_custom_title_screen; // Replace title screen background art with custom PNG.
    u8 turn_off_visual_scanner;
    u8 disable_element_system;
    u8 duel_start_field; // FIELD_* from constants/duel_fields.h; NUM_FIELDS uses each duelist's field.
    u8 field_stat_change_percent; // ATK/DEF boost or penalty from terrain; 30 = vanilla +/-30%.
    u8 dynamic_card_shop_and_trunk_sorting;
    u8 hide_unowned_trunk_cards; // Trunk list only shows cards you own at least one copy of.
    u8 dynamic_card_shop_costs; // Use card cost * 40 for shop pricing.
    u8 faster_walking_speed;
    u8 start_shop_with_one_copy_of_every_card;
    u8 start_with_three_copies_of_every_card;
    u8 randomize_card_costs_at_start;
    u8 enable_custom_cards_past_800;
    u8 enable_custom_decks;
    u8 enable_multiple_decks;
    u8 enable_custom_events; // Use custom event script replacements instead of vanilla overworld scripts.
    u8 allow_ante_with_one_copy_of_card;
    u8 allow_sell_one_copy_of_card;
    u8 add_all_cards_in_deck_to_trunk;
    u8 repeatable_opponent_capacity_reward;
    u8 story_opponent_capacity_reward;
    u8 alternate_win_reward_multiplier;
    u8 discount_shop_costs_by_duelist_level; // 5% off buy price per 100 duelist levels.
    u8 instant_win_with_start_button; // START in duel -> immediate player win.
    u8 enable_surrender_in_duel_b_menu; // B menu 4th option -> forfeit the duel.
    u8 expand_graveyard; // Store each player's graveyard as a 40-card stack and enable in-duel viewing.
    u8 enable_removed_from_play_zone; // Track banished cards; L/R in duel opens each duelist's list.
    u8 enable_world_map_thought_bubbles; // L on world map toggles thought bubble sprite.
    u8 enable_debug_menu; // R alone on field overworld opens debug menu.
    u8 enable_ante_card_viewer; // SELECT facing a duelist opens their ante reward card list.
    u8 enable_duelist_deck_viewer; // START facing a duelist opens a read-only deck list viewer.
    u8 enable_password_terminal_feedback; // Show password result popup and charge only on valid passwords.
    u8 enable_shiny_zones; // Interactable overworld card pickups from the shiny-zone manifest.
    u8 enable_big_card_art_palette_extension; // Card detail view: extend big art palettes to 7 BG banks (112 colors).
    u8 enable_new_card_colors; // Synchro/XYZ/Pendulum/Link card color palettes via src_custom hooks.
    u8 show_player_screen_pixel_coords; // Show player screen pixel X/Y on overworld BG0.
    u8 show_duel_life_points_on_board; // Show player/opponent LP on the duel field (left/right).
    u8 show_duel_turn_counter_on_board; // Show duel turn count between the board LP counters (yellow).
    u16 increase_bgm_tempo_when_lp_at_or_below; // Duel BGM tempo boost when player LP is at/below this; 0 disables.
    u16 increase_bgm_tempo_speed_percent; // Boosted duel BGM tempo as percent of normal; 100 = unchanged, 150 = 1.5x.
    u8 show_duel_shop_card_drops; // After duel win, show cards added to the shop this win.
    u8 enable_opponent_hand_field_scroll; // Scroll up past opponent backrow to view opponent hand on the field.
    u8 enable_summon_animations; // Show pop-up full-art BG0 animations on summon for registered boss monsters.
    u8 move_cursor_to_hand_on_draw; // After the draw phase, snap the player cursor to their hand.
    u8 enable_smarter_ai; // Vary among top-rated AI lines instead of one fixed optimal play.
    u8 fast_ai; // Cap AI sim work per decision (~60 frames); skips heavy permanent sim.
    u8 ignore_tribute_requirements; // When TRUE, all tribute summon requirements are waived.
    u16 card_in_hand_1;
    u16 card_in_hand_2;
    u16 card_in_hand_3;
    u16 card_in_hand_4;
    u16 card_in_hand_5;
    u16 opponent_deck_card_id; // When not CARD_NONE, every opponent deck is 40 copies of this card.
    u16 player_deck_card_id; // When not CARD_NONE, player deck is 40 copies of this card; card_in_hand_* still override opening hand.
    u8 skip_to_duel; // Skip intro screens, title screen, and overworld — go straight to a duel.
    u8 skip_to_duel_opponent_id; // Opponent index to duel when skip_to_duel is TRUE.
    u8 enable_title_screen_video; // Play intro video on title screen after 5 seconds of idle time.
    u8 enable_repeatable_duel_icon; // Show duel icon above duelable overworld NPCs.
    u8 enable_card_detail_navigation; // DPAD LEFT/RIGHT in card detail view switches between deck/trunk cards.
    u8 enable_manifest_map_overrides; // Override map graphics via custom_map_manifest.json redirects.
    u8 enable_extra_deck; // Extra deck system: store/remove fusion monsters from a 15-card extra deck per player deck.
    u8 use_small_card_description_font; // Card detail: 8x8 font (10 rows) instead of 8x16 (5 rows).
    u8 enable_millennium_item_tracker; // Status menu: show the seven-item progress row.
} RuntimeConfig;

/*
 * Build-time PC port settings (ROM const copy).
 * Toggle these before building to change default runtime behavior.
 */

extern const RuntimeConfig gRuntimeConfigRom;

/* EWRAM mirror — initialised from gRuntimeConfigRom at boot.
 * The debug menu Runtime Config submenu toggles these at runtime.
 * All consumers transparently read the EWRAM copy via the #define below. */
extern RuntimeConfig gRuntimeConfigEwram;
#define gRuntimeConfig gRuntimeConfigEwram


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
