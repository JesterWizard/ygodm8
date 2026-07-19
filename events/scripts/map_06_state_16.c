#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_06_state_16: map 6 state 16 */

EVENT_SCRIPT_REPLACEMENT(0x08E5CDF8, map_06_state_16_08E5CDF8, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_TRISTAN)
  LOAD_SPRITE(2, SPRITE_DUKE)
  LOAD_SPRITE(3, SPRITE_LUCKY)
  TALK(PORTRAIT_TRISTAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Have fun with Serenity.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CE04, map_06_state_16_08E5CE04, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Huh? Aren't you supposed to be with Serenity?",
      "You have to catch the Kaibaman show."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
