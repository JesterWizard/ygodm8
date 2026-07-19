#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_18: map 0 state 18 */

EVENT_SCRIPT_REPLACEMENT(0x08E34A54, map_00_state_18_08E34A54, 0x08E34A60, EVENT_NOP)
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
  MOVE_OBJECT(SPRITE_ISHIZU, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(SPRITE_YUGI, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(SPRITE_JOEY, DIRECTION_UP, 0, 0)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "But we cannot worry about that now. Time is of the",
      "essence.",
      "The second Millennium Item must be found...",
      "So that we can restore the Egyptian God Cards.",
      "That is the only way we can defeat Sol Chevalsky...",
      "And imprison Reshef the Dark Being again.",
      "{PLAYER}, please find the next Millennium Item."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A60, map_00_state_18_08E34A60, 0x08E34A78, 0x08E34A6C)
  TALK(PORTRAIT_NONE, "{CARD_1}Yes\nNo{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A78, map_00_state_18_08E34A78, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_HAPPY, PORTRAIT_POSITION_AUTO,
      "Thank you.",
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
  TEXT(
      "Go to Domino Pier.",
      "The Millennium Item should be aboard the cruise ship."
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_UNLOCKED_DOMINO_PIER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A6C, map_00_state_18_08E34A6C, 0x08E34A60, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "{PLAYER}, I have no one to turn to but to you.",
      "I know I am asking for the impossible, but I beg for",
      "your help."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
