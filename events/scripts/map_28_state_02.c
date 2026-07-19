#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_28_state_02: map 28 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08EA69A4, map_28_state_02_08EA69A4, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_OLD_MAN)
  LOAD_SPRITE(2, SPRITE_OLD_WOMAN)
  TEXT(
      "I heard there's a good fortuneteller around these",
      "parts.",
      "Where might he be?"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA69B0, map_28_state_02_08EA69B0, EVENT_NOP, EVENT_NOP)
  TEXT(
      "I'm on a date with my man.",
      "My heart is pounding like a jackhammer!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
