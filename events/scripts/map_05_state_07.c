#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_05_state_07: map 5 state 7 */

EVENT_SCRIPT_REPLACEMENT(0x08E51094, map_05_state_07_08E51094, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_STRINGER)
  LOAD_SPRITE(2, SPRITE_RED_MOHAWK)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I can't believe Tristan made us go all the way around",
      "the world just because his stomach was growlin'!"
  )
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "It wasn't Tristan's fault. It was just a",
      "misunderstanding.",
      "Anyway, we have more important things to do."
  )
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Oh yeah! Maybe Ishizu has good news.",
      "She may have found a way to restore the Egyptian God",
      "Cards."
  )
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Yes, I hope so.",
      "{PLAYER}, Joey, let's meet up with Ishizu."
  )
  SET_FLAG(EVENT_FLAG_JOEY_COMPLAINED_ABOUT_TRISTAN)
  FALLTHROUGH()
END_EVENT_SCRIPT()
