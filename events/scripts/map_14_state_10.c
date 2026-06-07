#include "event_macros.h"
#include "event_object_slots.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_14_state_10: map 14 state 10 */

EVENT_SCRIPT_REPLACEMENT(0x08E775C4, map_14_state_10_08E775C4, 0x08E775D0, 0x08E775DC)
  LOAD_SPRITE(1, SPRITE_YUGI)
  LOAD_SPRITE(2, SPRITE_JOEY)
  LOAD_SPRITE(3, SPRITE_DOMINO_STATION_GUARD)
  LOAD_SPRITE(4, SPRITE_DOMINO_STATION_GUARD)
  LOAD_SPRITE(5, SPRITE_DOMINO_STATION_GUARD)
  LOAD_SPRITE(6, SPRITE_FENG_LONG)
  LOAD_SPRITE(7, SPRITE_NIBBLES)
  PLAY_MUSIC(MUSIC_230)
  HIDE_PORTRAIT()
  DELAY(64)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Gotta hand it to you, Yugi.\n"
      "That duel lasted barely a\n\n"
      "second!\n\n"
      "On the other hand...\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP, PORTRAIT_RIGHT)
  TEXT
  (
      "{PLAYER}, you had me\n"
      "worried!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, OBJECT_0)
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I... I couldn't afford to\n"
      "waste any time.\n\n"
      "I have to find the spirit\n"
      "right away!\n\n"
      "But {PLAYER}'s duel was\n"
      "pretty impressive.\n\n"
      "Let's keep this up, guys!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(64)
  FADE_MUSIC(4)
  FADE_SCREEN(4)
  CLEAR_FLAG(243)
  CHECK_FLAG(EVENT_FLAG_CHOSE_TO_FIGHT_DOX2)
  FALLTHROUGH()
END_EVENT_SCRIPT()
