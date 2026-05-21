#include "event_macros.h"
#include "overworld.h"

/* map_06_state_16: map 6 state 16 */

EVENT_SCRIPT_REPLACEMENT(0x08E5CDF8, map_06_state_16_08E5CDF8, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "Have fun with Serenity.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CE04, map_06_state_16_08E5CE04, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "Huh? Aren't you supposed to\nbe with Serenity?\n\nYou have to catch the\nKaibaman show.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
