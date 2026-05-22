#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_37_state_03: map 37 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08ECD8A4, map_37_state_03_08ECD8A4, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_MAKO)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "There's a cartload of\n"
      "monkeys around..\n\n"
      "They're in the rainforest.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD8B0, map_37_state_03_08ECD8B0, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "These days, monkeys are so\n"
      "smart that they can duel.\n\n"
      "If you have time to burn, go\n"
      "into the rainforest.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
