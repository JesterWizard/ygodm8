#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_35_state_06: map 35 state 6 */

EVENT_SCRIPT_REPLACEMENT(0x08EC63E0, map_35_state_06_08EC63E0, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_GIRL_ARCHEOLOGIST)
  LOAD_SPRITE(2, SPRITE_THOUGHTFUL_ARCHEOLOGIST)
  TEXT
  (
      "Fossils are the remains of\n"
      "prehistoric life forms.\n\n"
      "Over millions of years, they\n"
      "were preserved in stone.\n\n"
      "You can think of this area\n"
      "as a primordial graveyard.\n\n"
      "Youg might call digging up\n"
      "fossils graverobbing...\n\n"
      "But this is for research.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC63EC, map_35_state_06_08EC63EC, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Remnants of living creatures\n"
      "preserved in stone...\n\n"
      "That makes fossils sound\n"
      "creppy, eh?\n\n"
      "Come to think of it, I've\n"
      "been having these eerie\n\n"
      "feelings lately.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
