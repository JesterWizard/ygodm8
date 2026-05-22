#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_35_state_06: map 35 state 6 */

EVENT_SCRIPT_REPLACEMENT(0x08EC63E0, map_35_state_06_08EC63E0, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_GIRL_ARCHEOLOGIST)
  LOAD_SPRITE(2, SPRITE_THOUGHTFUL_ARCHEOLOGIST)
  TEXT("Fossils are the remains of\nprehistoric life forms.\n\nOver millions of years, they\nwere preserved in stone.\n\nYou can think of this area\nas a primordial graveyard.\n\nYoug might call digging up\nfossils graverobbing...\n\nBut this is for research.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC63EC, map_35_state_06_08EC63EC, 0x08F04040, 0x08F04040)
  TEXT("Remnants of living creatures\npreserved in stone...\n\nThat makes fossils sound\ncreppy, eh?\n\nCome to think of it, I've\nbeen having these eerie\n\nfeelings lately.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
