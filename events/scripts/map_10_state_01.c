#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_10_state_01: map 10 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E63218, map_10_state_01_08E63218, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_LOST_DUELIST)
  TEXT
  (
      "I want to get on the Duel\n"
      "Express...\n\n"
      "But I'm lost. I can't find\n"
      "Domino Station.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E63224, map_10_state_01_08E63224, 0x08E63230, 0x08E63248)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_LOST_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E63230, map_10_state_01_08E63230, 0x08E6323C, 0x08F0404C)
  TEXT
  (
      "I'll duel with the deck I\n"
      "made exclusively for the\n\n"
      "Duel Express tournament.\n\n"
  )
  DUEL(DUELIST_ID_010)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6323C, map_10_state_01_08E6323C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_BACK_ALLEY)
  TEXT
  (
      "Maybe it's a good think I'm\n"
      "not on the Duel Express...\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_LOST_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E63248, map_10_state_01_08E63248, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Let me think about how to\n"
      "reconstruct my deck first.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
