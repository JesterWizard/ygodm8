#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_37_state_03: map 37 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08ECD8A4, map_37_state_03_08ECD8A4, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_MAKO)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "There's a cartload of monkeys around..",
      "They're in the rainforest."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD8B0, map_37_state_03_08ECD8B0, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "These days, monkeys are so smart that they can duel.",
      "If you have time to burn, go into the rainforest."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
