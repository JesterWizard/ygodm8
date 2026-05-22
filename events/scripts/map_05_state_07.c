#include "event_macros.h"
#include "overworld.h"

/* map_05_state_07: map 5 state 7 */

EVENT_SCRIPT_REPLACEMENT(0x08E51094, map_05_state_07_08E51094, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_STRINGER)
  LOAD_SPRITE(2, SPRITE_RED_MOHAWK)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("I can't believe Tristan made\nus go all the way around\n\nthe world just because his\nstomach was growlin'!\n\n")
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("It wasn't Tristan's fault.\nIt was just a\n\nmisunderstanding.\n\nAnyway, we have more\nimportant things to do.\n\n")
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Oh yeah! Maybe Ishizu has\ngood news.\n\nShe may have found a way to\nrestore the Egyptian God\n\nCards.\n\n")
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Yes, I hope so.\n\n{PLAYER}, Joey, let's meet\nup with Ishizu.\n\n")
  SET_FLAG(EVENT_FLAG_JOEY_COMPLAINED_ABOUT_TRISTAN)
  FALLTHROUGH()
END_EVENT_SCRIPT()
