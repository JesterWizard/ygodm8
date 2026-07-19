#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_35_state_06: map 35 state 6 */

EVENT_SCRIPT_REPLACEMENT(0x08EC63E0, map_35_state_06_08EC63E0, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_GIRL_ARCHEOLOGIST)
  LOAD_SPRITE(2, SPRITE_THOUGHTFUL_ARCHEOLOGIST)
  TEXT(
      "Fossils are the remains of prehistoric life forms.",
      "Over millions of years, they were preserved in stone.",
      "You can think of this area as a primordial graveyard.",
      "Youg might call digging up fossils graverobbing...",
      "But this is for research."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC63EC, map_35_state_06_08EC63EC, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Remnants of living creatures preserved in stone...",
      "That makes fossils sound creppy, eh?",
      "Come to think of it, I've been having these eerie",
      "feelings lately."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
