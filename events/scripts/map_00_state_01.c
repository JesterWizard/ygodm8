#include "event_macros.h"
#include "overworld.h"

/* map_00_state_01: map 0 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E349DC, map_00_state_01_08E349DC, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("The Egyptian God Cards are\nrequired to seal away the\n\nDark Being.\n\nFirst, the Egyptian God\nCards must be restored from\n\ntheir stone prisons.\n\nIn order to do so, we need\nthe Millennium Items and\n\ntheir mystical energies.\n\nThe first Millennium Item is\nat the Egypt Exhibition.\n\nYou can reach the Exhibition\nfrom the railway station.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E349E8, map_00_state_01_08E349E8, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Please. Hurry to the Egypt\nExhibition.\n\nReshef the Dark Being will\nsoon engulf the world in\n\ndarkness.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
