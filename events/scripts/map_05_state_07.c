#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_05_state_07: map 5 state 7 */

EVENT_SCRIPT_REPLACEMENT(0x08E51094, map_05_state_07_08E51094, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_STRINGER)
  LOAD_SPRITE(2, SPRITE_RED_MOHAWK)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I can't believe Tristan made\n"
      "us go all the way around\n\n"
      "the world just because his\n"
      "stomach was growlin'!\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "It wasn't Tristan's fault.\n"
      "It was just a\n\n"
      "misunderstanding.\n\n"
      "Anyway, we have more\n"
      "important things to do.\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Oh yeah! Maybe Ishizu has\n"
      "good news.\n\n"
      "She may have found a way to\n"
      "restore the Egyptian God\n\n"
      "Cards.\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Yes, I hope so.\n\n"
      "{PLAYER}, Joey, let's meet\n"
      "up with Ishizu.\n\n"
  )
  SET_FLAG(EVENT_FLAG_JOEY_COMPLAINED_ABOUT_TRISTAN)
  FALLTHROUGH()
END_EVENT_SCRIPT()
