#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_06_state_16: map 6 state 16 */

EVENT_SCRIPT_REPLACEMENT(0x08E5CDF8, map_06_state_16_08E5CDF8, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_TRISTAN)
  LOAD_SPRITE(2, SPRITE_DUKE)
  LOAD_SPRITE(3, SPRITE_LUCKY)
  TALK(PORTRAIT_TRISTAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Have fun with Serenity.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CE04, map_06_state_16_08E5CE04, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Huh? Aren't you supposed to\n"
    "be with Serenity?\n\n"
    "You have to catch the\n"
    "Kaibaman show.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
