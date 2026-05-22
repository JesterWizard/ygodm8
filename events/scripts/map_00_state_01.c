#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_01: map 0 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E349DC, map_00_state_01_08E349DC, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "The Egyptian God Cards are\n"
      "required to seal away the\n\n"
      "Dark Being.\n\n"
      "First, the Egyptian God\n"
      "Cards must be restored from\n\n"
      "their stone prisons.\n\n"
      "In order to do so, we need\n"
      "the Millennium Items and\n\n"
      "their mystical energies.\n\n"
      "The first Millennium Item is\n"
      "at the Egypt Exhibition.\n\n"
      "You can reach the Exhibition\n"
      "from the railway station.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E349E8, map_00_state_01_08E349E8, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Please. Hurry to the Egypt\n"
      "Exhibition.\n\n"
      "Reshef the Dark Being will\n"
      "soon engulf the world in\n\n"
      "darkness.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
