#include "event_macros.h"
#include "overworld.h"

/* map_14_state_05: map 14 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E7748C, map_14_state_05_08E7748C, 0x08F04040, 0x08F04040)
  TEXT("Those Neo Ghoul weirdoes\nare finally gone.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E77498, map_14_state_05_08E77498, 0x08F04040, 0x08F04040)
  TEXT("Sorry, I don't have time for\nfun and games.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E774BC, map_14_state_05_08E774BC, 0x08F04040, 0x08F04040)
  TEXT("The Neo Ghouls at the\nturnstiles may have left...\n\nBut unfortunately, there are\nstill more on the train.\n\nIf you board the train,\nplease be careful.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
