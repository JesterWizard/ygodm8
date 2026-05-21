#include "event_macros.h"
#include "overworld.h"

/* map_17_state_03: map 17 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E7F148, map_17_state_03_08E7F148, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_NON_DUELIST_PASSENGER)
  TEXT("I should've taken first\nclass...\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7F154, map_17_state_03_08E7F154, 0x08F04040, 0x08F04040)
  TEXT("This is the train's deck!\n\nDon't confuse it with a duel\ndeck!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
