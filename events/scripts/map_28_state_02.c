#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_28_state_02: map 28 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08EA69A4, map_28_state_02_08EA69A4, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_OLD_MAN)
  LOAD_SPRITE(2, SPRITE_OLD_WOMAN)
  TEXT
  (
      "I heard there's a good\n"
      "fortuneteller around these\n\n"
      "parts.\n\n"
      "Where might he be?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA69B0, map_28_state_02_08EA69B0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I'm on a date with my man.\n\n"
      "My heart is pounding like a\n"
      "jackhammer!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
