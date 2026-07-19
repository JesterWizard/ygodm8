#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_20_state_05: map 20 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E84FC0, map_20_state_05_08E84FC0, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_KAIBA_COSPLAYER)
  TEXT(
      "Heart of the cards, guide me!",
      "...No matter how hard I try, I can't draw the card I",
      "want...",
      "Huh? You want to know what I'm doing?",
      "I'm practicing so I can draw cards exactly when I need",
      "them."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84FCC, map_20_state_05_08E84FCC, 0x08E84FD8, 0x08E84FF0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_KAIBA_COSPLAYER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84FD8, map_20_state_05_08E84FD8, 0x08E84FE4, 0x08F0404C)
  TEXT(
      "I'll show you how good I am at drawing the right cards",
      "at the right time!"
  )
  DUEL(DUELIST_ID_096)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84FE4, map_20_state_05_08E84FE4, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_231)
  TEXT("I couldn't draw the cards I needed...")
  SET_FLAG(EVENT_FLAG_DEFEATED_KAIBA_COSPLAYER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84FF0, map_20_state_05_08E84FF0, EVENT_NOP, EVENT_NOP)
  TEXT("When I get better at drawing the cards I need, okay?")
  FALLTHROUGH()
END_EVENT_SCRIPT()
