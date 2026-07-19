#ifndef EVENT_MACROS_H
#define EVENT_MACROS_H

/* These files are parsed by tools/vanilla_events.py, not compiled directly.
 * TEXT("page", "page", ...) — each string is one textbox page (auto-wrapped).
 * TALK(portrait[, expression[, position]], "page", ...) — defaults NEUTRAL + LEFT.
 */

#define EVENT_SCRIPT_REPLACEMENT(vanilla_addr, name, on_false, on_true)
#define EVENT_SCRIPT(name, on_false, on_true)
#define END_EVENT_SCRIPT()

/* Dead branch target (vanilla nop script). Prefer this over raw 0x08F04040. */
#define EVENT_NOP 0x08F04040

#define RAW(...)
#define DIALOGUE(...)
#define LANGUAGE_TEXT(language, text)
#define END_LANGUAGE_TEXT()
#define TEXT(...)
#define TEXT_FRAGMENT(text)
#define PLAYER_NAME()
#define NEWLINE()
#define PAGE_BREAK()
/* CHOICE/ELSE/END_CHOICE: sequential scene sugar (compiler expands to Script nodes).
 * Bare CHOICE() with no ELSE remains the legacy {CARD_2} control opcode. */
#define CHOICE()
#define ELSE()
#define END_CHOICE()
#define PORTRAIT(portrait_id, expression, position)
#define TALK(...)
#define HIDE_PORTRAIT()
#define SET_FLAG(flag)
#define CHECK_FLAG(flag)
#define CLEAR_FLAG(flag)
#define RESTORE_LIFE_POINTS()
#define DUEL(opponent)
#define PLAY_MUSIC(music)
#define SET_MAP_MUSIC(music)
#define STOP_MUSIC(speed)
#define FADE_MUSIC(speed)
#define START_MENU()
#define SAVE()
#define MOVE_OBJECT(object_id, direction, distance, wander) // object_id: slot id or SPRITE_* after LOAD_SPRITE
#define STOP_FOOTSTEPS()
#define SET_OBJECT_POSITION(object_id, x, y, frame, direction) // object_id: slot id or SPRITE_*
#define SHOW_OBJECT(object_id, x, y, frame, mode, unused) // object_id: slot id or SPRITE_*
#define WALK_OBJECT_X(object_id, target) // object_id: slot id or SPRITE_*
#define WALK_OBJECT_Y(object_id, target) // object_id: slot id or SPRITE_*
#define SLIDE_OBJECT(object_id, direction, distance) // object_id: slot id or SPRITE_*
#define OBJECT_EFFECT(object_mask, mode) // object_mask: OBJECT_N, SPRITE_*, or combined with |
#define SPECIAL(command)
#define CUTSCENE(cutscene_id)
#define DELAY(frames)
#define ADD_CARD(card)
#define REMOVE_CARD(card)
#define CONDITION_CHECK(condition)
#define FADE_SCREEN(speed)
#define SWAP_OBJECT_SPRITE(object_id, sprite_id)
#define LOAD_SPRITE(object_id, sprite_id) SWAP_OBJECT_SPRITE(object_id, sprite_id)
#define WARP(location, state, entrance, unused)
#define REACTION(reaction, object_mask) // object_mask: OBJECT_N, SPRITE_*, or combined with |
#define COMMAND_7C_ARG(command, argument)
#define FALLTHROUGH()
#define END()

#define SCREEN_SHAKE(speed) COMMAND_7C_ARG(7, speed)
#define SHOW_OVERWORLD_GRAPHIC(graphic_id) COMMAND_7C_ARG(8, graphic_id)
#define DISPLAY_CG(cg_id, fade_speed) RAW(0x7C, '9', cg_id, fade_speed)
#define HIDE_CG(fade_speed) RAW(0x7C, 'A', fade_speed)

/* Status tracker: Puzzle=0 Ring=1 Key=2 Scale=3 Rod=4 Eye=5 Necklace=6 */
#define MILLENNIUM_ITEM_PUZZLE   0
#define MILLENNIUM_ITEM_RING     1
#define MILLENNIUM_ITEM_KEY      2
#define MILLENNIUM_ITEM_SCALE    3
#define MILLENNIUM_ITEM_ROD      4
#define MILLENNIUM_ITEM_EYE      5
#define MILLENNIUM_ITEM_NECKLACE 6
#define SET_MILLENNIUM_ITEM(id) RAW(0x7C, 'B', (id), 1)
#define CLEAR_MILLENNIUM_ITEM(id) RAW(0x7C, 'B', (id), 0)

#endif
