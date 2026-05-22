#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_18: map 0 state 18 */

EVENT_SCRIPT_REPLACEMENT(0x08E34A54, map_00_state_18_08E34A54, 0x08E34A60, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  LOAD_SPRITE(2, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(3, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(4, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(5, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(6, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(7, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(8, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(9, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(10, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(11, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(12, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(13, SPRITE_YUGI)
  LOAD_SPRITE(14, SPRITE_JOEY)
  DELAY(32)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "But we cannot worry about\n"
      "that now. Time is of the\n\n"
      "essence.\n\n"
      "The second Millennium Item\n"
      "must be found...\n\n"
      "So that we can restore the\n"
      "Egyptian God Cards.\n\n"
      "That is the only way we can\n"
      "defeat Sol Chevalsky...\n\n"
      "And imprison Reshef the Dark\n"
      "Being again.\n\n"
      "{PLAYER}, please find the\n"
      "next Millennium Item.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A60, map_00_state_18_08E34A60, 0x08E34A78, 0x08E34A6C)
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A78, map_00_state_18_08E34A78, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_HAPPY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Thank you.\n\n"
      "The next Millennium Item."
  )
  DELAY(43)
  TEXT
  (
      "."
  )
  DELAY(43)
  TEXT
  (
      "."
  )
  DELAY(43)
  TEXT
  (
      "\n"
      "Go to Domino Pier.\n\n"
      "The Millennium Item should\n"
      "be aboard the cruise ship.\n\n"
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_UNLOCKED_DOMINO_PIER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A6C, map_00_state_18_08E34A6C, 0x08E34A60, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}, I have no one to\n"
      "turn to but to you.\n\n"
      "I know I am asking for the\n"
      "impossible, but I beg for\n\n"
      "your help.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
