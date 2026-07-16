#include "global.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_menu.h"
#include "debug_menu_internal.h"

/* ------------------------------------------------------------------ */
/*  Config entry table                                                 */
/* ------------------------------------------------------------------ */
/* ponytail: only toggleable (TRUE/FALSE) u8 fields are listed.      */
/* Numeric/enum u8 and u16 fields are excluded.                       */

/* Custom offsetof for GCC -- compile-time, never dereferences at runtime. */
#ifndef offsetof
#define offsetof(type, member) ((u32)(u32)&((type*)0)->member)
#endif

/* Embedded char array avoids dangling .rodata pointer references that
 * the linker discards when APPEND_RODATA is used. */
#define CONF(_name, _field) \
    { _name, offsetof(RuntimeConfig, _field) }

static const struct {
    char label[12];
    u16 offset;
} sRuntimeConfigEntries[] APPEND_RODATA = {
    CONF("Restore LP",   restore_life_points_after_duel),
    CONF("Cap LP",       cap_life_points_after_duel),
    CONF("Preserve LP",  preserve_life_points_above_8000_after_duel),
    CONF("Return Home",  return_home_after_defeat),
    CONF("Offer Retry",  offer_duel_retry_after_defeat),
    CONF("Max Level",    max_duelist_level_at_start),
    CONF("Max Deck Cap", max_deck_capacity_at_start),
    CONF("Max Money",    max_money_at_start),
    CONF("No Ban List",  disable_ban_list),
    CONF("Skip Start",   skip_opening_sequence),
    CONF("Cust Opening", enable_custom_opening_screens),
    CONF("Cust Title",   enable_custom_title_screen),
    CONF("No Scanner",   turn_off_visual_scanner),
    CONF("No Element",   disable_element_system),
    CONF("Dyna Sort",    dynamic_card_shop_and_trunk_sorting),
    CONF("Hide Unowned", hide_unowned_trunk_cards),
    CONF("Dyna Costs",   dynamic_card_shop_costs),
    CONF("Start 1x",     start_shop_with_one_copy_of_every_card),
    CONF("Start 3x",     start_with_three_copies_of_every_card),
    CONF("Rand Costs",   randomize_card_costs_at_start),
    CONF("Custom 800+",  enable_custom_cards_past_800),
    CONF("Cust Decks",   enable_custom_decks),
    CONF("Multi Decks",  enable_multiple_decks),
    CONF("Cust Events",  enable_custom_events),
    CONF("Ante 1 Copy",  allow_ante_with_one_copy_of_card),
    CONF("Sell 1 Copy",  allow_sell_one_copy_of_card),
    CONF("Deck>Trunk",   add_all_cards_in_deck_to_trunk),
    CONF("Disc Lv Cost", discount_shop_costs_by_duelist_level),
    CONF("Instant Win",  instant_win_with_start_button),
    CONF("Surrender",    enable_surrender_in_duel_b_menu),
    CONF("Expand GY",    expand_graveyard),
    CONF("RFP Zone",     enable_removed_from_play_zone),
    CONF("Thought Bb",   enable_world_map_thought_bubbles),
    CONF("Debug Menu",   enable_debug_menu),
    CONF("Ante Viewer",  enable_ante_card_viewer),
    CONF("Deck Viewer",  enable_duelist_deck_viewer),
    CONF("Pwd Feedbk",   enable_password_terminal_feedback),
    CONF("Shiny Zone",   enable_shiny_zones),
    CONF("Big Art Ext",  enable_big_card_art_palette_extension),
    CONF("Show Coord",   show_player_screen_pixel_coords),
    CONF("Show LP",      show_duel_life_points_on_board),
    CONF("Show Turn",    show_duel_turn_counter_on_board),
    CONF("Show Drops",   show_duel_shop_card_drops),
    CONF("Scroll Hand",  enable_opponent_hand_field_scroll),
    CONF("Summon Anim",  enable_summon_animations),
    CONF("Cursor>Hand",  move_cursor_to_hand_on_draw),
    CONF("Smart AI",     enable_smarter_ai),
    CONF("Fast AI",      fast_ai),
    CONF("No Tribute",   ignore_tribute_requirements),
    CONF("Repeat Duel",  enable_repeatable_duel_icon),
    CONF("Skip Duel",    skip_to_duel),
    CONF("Title Video",  enable_title_screen_video),
    CONF("Small Desc",   use_small_card_description_font),
    CONF("Mill Track",   enable_millennium_item_tracker),
};

#undef CONF

#define TOTAL_ENTRIES ((u16)ARRAY_COUNT(sRuntimeConfigEntries))

/* ------------------------------------------------------------------ */
/*  Draw — uses standard DebugMenuCopyLine (16-char rows).           */
/* ------------------------------------------------------------------ */

void DebugMenuDrawRuntimeConfig(u8 scrollTop, u8 cursor) {
    u8 row;

    (void)cursor;

    for (row = 0; row < DEBUG_ROWS; row++) {
        u8 index = scrollTop + row;
        u8 buf[DEBUG_CHARS + 1];
        u8 i, t;
        u8 value;

        if (index >= TOTAL_ENTRIES) {
            DebugMenuCopyLine(row, gDebugMenuBlankLine);
            continue;
        }

        value = *(u8 *)((u8 *)&gRuntimeConfig + sRuntimeConfigEntries[index].offset);

        /* label (up to 12 chars) padded to 12 + space + ON/OFF = 16 */
        t = 0;
        for (i = 0; i < 12; i++)
            buf[i] = sRuntimeConfigEntries[index].label[t] ? sRuntimeConfigEntries[index].label[t++] : ' ';

        buf[12] = ' ';
        if (value) {
            buf[13] = 'O';
            buf[14] = 'N';
            buf[15] = ' ';
        } else {
            buf[13] = 'O';
            buf[14] = 'F';
            buf[15] = 'F';
        }
        buf[DEBUG_CHARS] = '\0';

        DebugMenuCopyLine(row, buf);
    }
}

/* ------------------------------------------------------------------ */
/*  Viewer loop                                                       */
/* ------------------------------------------------------------------ */

void DebugRuntimeConfigViewer(void) {
    u8 cursor = 0, scrollTop = 0;

    DebugMenuRedraw(0, 0, DEBUG_VIEW_RUNTIME_CONFIG);
    DebugMenuWaitVBlank();

    while (1) {
        u16 buttons = DebugMenuButtons();

        if (buttons & B_BUTTON)
            break;

        if (buttons & DPAD_UP && cursor != 0) {
            PlayMusic(SFX_MOVE_CURSOR);
            if (--cursor < scrollTop)
                scrollTop = cursor;
            DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_RUNTIME_CONFIG);
        }

        if (buttons & DPAD_DOWN && cursor < TOTAL_ENTRIES - 1) {
            PlayMusic(SFX_MOVE_CURSOR);
            if (++cursor >= scrollTop + DEBUG_ROWS)
                scrollTop = cursor - (DEBUG_ROWS - 1);
            DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_RUNTIME_CONFIG);
        }

        if (buttons & A_BUTTON) {
            u8 *field;

            PlayMusic(SFX_SELECT);
            field = (u8 *)&gRuntimeConfig + sRuntimeConfigEntries[cursor].offset;
            *field = *field ? FALSE : TRUE;
            DebugMenuRedraw(scrollTop, cursor, DEBUG_VIEW_RUNTIME_CONFIG);
            DebugMenuWaitRelease(A_BUTTON);
        }

        DebugMenuUpdateCursor(cursor - scrollTop);
        LoadOam();
        DebugMenuWaitVBlank();
    }

    DebugMenuWaitRelease(B_BUTTON);
    DebugMenuVBlankNoWin();
    DebugMenuRedraw(0, 0, DEBUG_VIEW_ROOT);
    DebugMenuVBlankNoWin();
    DebugMenuWaitVBlank();
}
