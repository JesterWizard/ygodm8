#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_10_state_01: map 10 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E63218, map_10_state_01_08E63218, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_LOST_DUELIST)
  TEXT(
      "I want to get on the Duel Express...",
      "But I'm lost. I can't find Domino Station."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E63224, map_10_state_01_08E63224, 0x08E63230, 0x08E63248)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_LOST_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E63230, map_10_state_01_08E63230, 0x08E6323C, 0x08F0404C)
  TEXT(
      "I'll duel with the deck I made exclusively for the",
      "Duel Express tournament."
  )
  DUEL(DUELIST_ID_010)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6323C, map_10_state_01_08E6323C, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_BACK_ALLEY)
  TEXT("Maybe it's a good think I'm not on the Duel Express...")
  SET_FLAG(EVENT_FLAG_DEFEATED_LOST_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E63248, map_10_state_01_08E63248, EVENT_NOP, EVENT_NOP)
  TEXT("Let me think about how to reconstruct my deck first.")
  FALLTHROUGH()
END_EVENT_SCRIPT()
