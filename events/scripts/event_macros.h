#ifndef EVENT_MACROS_H
#define EVENT_MACROS_H

/* These files are parsed by tools/vanilla_events.py, not compiled directly.
 * TEXT/DIALOGUE/LANGUAGE_TEXT accept normal Python string literals, including
 * triple-quoted multiline strings for easier authoring.
 */

#define EVENT_SCRIPT_REPLACEMENT(vanilla_addr, name, on_false, on_true)
#define EVENT_SCRIPT(name, on_false, on_true)
#define END_EVENT_SCRIPT()

#define RAW(...)
#define DIALOGUE(text)
#define LANGUAGE_TEXT(language, text)
#define END_LANGUAGE_TEXT()
#define TEXT(text) LANGUAGE_TEXT(LANGUAGE_ENGLISH, text) END_LANGUAGE_TEXT()
#define TEXT_FRAGMENT(text)
#define PLAYER_NAME()
#define NEWLINE()
#define PAGE_BREAK()
#define CHOICE()
#define PORTRAIT(portrait_id, expression, position)
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

#endif
