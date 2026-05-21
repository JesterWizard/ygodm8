#include "event_macros.h"
#include "overworld.h"

/* map_12_state_05: map 12 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F00C, map_12_state_05_08E6F00C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "Tristan and Duke are\ntraining inside.\n\n")
  LANGUAGE_TEXT(1, "Tristan et Duke\ns'entra\xeenent \xe0 l'int\xe9rieur.\n\n")
  LANGUAGE_TEXT(2, "Tristan und Duke trainieren\ndrinnen.\n\n")
  LANGUAGE_TEXT(3, "Tristan e Duke si stanno\nallenando dentro.\n\n")
  LANGUAGE_TEXT(4, "Tristan y Duke se\nentrenan dentro.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
