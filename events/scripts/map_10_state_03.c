#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_10_state_03: map 10 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E63278, map_10_state_03_08E63278, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_LOST_DUELIST)
  TEXT
  (
      "The Neo Ghouls are gone,\n"
      "but...\n\n"
      "Something doesn't feel\n"
      "right.\n\n"
      "I hope nothing terrible\n"
      "happens.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E63284, map_10_state_03_08E63284, 0x08E63290, 0x08E632A8)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_LOST_DUELIST2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E63290, map_10_state_03_08E63290, 0x08E6329C, 0x08F0404C)
  TEXT
  (
      "I'll show you that I've\n"
      "improved.\n\n"
  )
  DUEL(94)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6329C, map_10_state_03_08E6329C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_BACK_ALLEY)
  TEXT
  (
      "Shucks. I guess I'm not good\n"
      "enough yet.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_LOST_DUELIST2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E632A8, map_10_state_03_08E632A8, 0x08F04040, 0x08F04040)
  TEXT
  (
      "After I make my deck\n"
      "stronger, okay?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
