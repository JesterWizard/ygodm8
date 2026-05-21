#include "event_macros.h"
#include "overworld.h"

/* map_37_state_03: map 37 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08ECD8A4, map_37_state_03_08ECD8A4, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "There's a cartload of\nmonkeys around..\n\nThey're in the rainforest.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD8B0, map_37_state_03_08ECD8B0, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "These days, monkeys are so\nsmart that they can duel.\n\nIf you have time to burn, go\ninto the rainforest.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
