#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_20_state_05: map 20 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E84FC0, map_20_state_05_08E84FC0, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_KAIBA_COSPLAYER)
  TEXT
  (
      "Heart of the cards, guide\n"
      "me!\n\n"
      "...No matter how hard I try,\n"
      "I can't draw the card I\n\n"
      "want...\n\n"
      "Huh? You want to know what\n"
      "I'm doing?\n\n"
      "I'm practicing so I can draw\n"
      "cards exactly when I need\n\n"
      "them.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84FCC, map_20_state_05_08E84FCC, 0x08E84FD8, 0x08E84FF0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_KAIBA_COSPLAYER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84FD8, map_20_state_05_08E84FD8, 0x08E84FE4, 0x08F0404C)
  TEXT
  (
      "I'll show you how good I am\n"
      "at drawing the right cards\n\n"
      "at the right time!\n\n"
  )
  DUEL(96)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84FE4, map_20_state_05_08E84FE4, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_231)
  TEXT
  (
      "I couldn't draw the cards I\n"
      "needed...\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_KAIBA_COSPLAYER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84FF0, map_20_state_05_08E84FF0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "When I get better at drawing\n"
      "the cards I need, okay?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
