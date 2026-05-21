#include "event_macros.h"
#include "overworld.h"

/* map_15_state_04: map 15 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08E7A5F0, map_15_state_04_08E7A5F0, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "The Neo Ghouls robbed me of\nall my rare cards.\n\nI can't duel anymore.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5FC, map_15_state_04_08E7A5FC, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "The next stop is the Egypt\nExhibition...\n\nBut the Neo Ghouls have\ntaken over the train.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A608, map_15_state_04_08E7A608, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "Please don't joke at a time\nlike this.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
