#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_01: map 0 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E349DC, map_00_state_01_08E349DC, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "The Egyptian God Cards are required to seal away the",
      "Dark Being.",
      "First, the Egyptian God Cards must be restored from",
      "their stone prisons.",
      "In order to do so, we need the Millennium Items and",
      "their mystical energies.",
      "The first Millennium Item is at the Egypt Exhibition.",
      "You can reach the Exhibition from the railway station."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E349E8, map_00_state_01_08E349E8, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Please. Hurry to the Egypt Exhibition.",
      "Reshef the Dark Being will soon engulf the world in",
      "darkness."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
