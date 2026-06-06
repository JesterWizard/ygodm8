#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_40_state_01: map 40 state 1 */

LOAD_SPRITE(1, SPRITE_ISHIZU)
PLAY_MUSIC(MUSIC_252)
DELAY(8)
WALK_OBJECT_X(1, 56)
DELAY(8)
WALK_OBJECT_X(0, 76)
WALK_OBJECT_X(13, 86)
WALK_OBJECT_X(14, 86)
DELAY(16)
PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
TEXT
(
    "So... This is Pegasus's\n"
    "island.\n\n"
    "Seto Kaiba has probably\n"
    "already gone ahead.\n\n"
)
PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
HIDE_PORTRAIT()
DELAY(48)
MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
DELAY(16)
PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
TEXT
(
    "I do not know what Pegasus\n"
    "is planning.\n\n"
    "But we cannot ignore Reshef\n"
    "the Dark Being.\n\n"
    "Harsh battles await.\n\n"
    "But don't succumb in the\n"
    "face of adversity.\n\n"
)
SET_FLAG(EVENT_FLAG_ENTERED_PEGASUS_ISLAND)

EVENT_SCRIPT_REPLACEMENT(0x08ED5608, map_40_state_01_08ED5608, 0x08F04244, 0x08F04040)
SET_FLAG(EVENT_FLAG_LEAVING_THE_CABLE_CAR_LEADS_TO_THE_TOP_OF_PEGASUS_ISLAND)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED55FC, map_40_state_01_08ED55FC, 0x08F04040, 0x08F04040)
PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "The Duelist Kingdom\n"
      "Tournament was once held\n\n"
      "here.\n\n"
      "However, the island has been\n"
      "transformed since then.\n\n"
      "There must be many duelists\n"
      "under Reshef's control.\n\n"
      "They're ready to ambush us.\n\n"
      "Be careful as you make your\n"
      "way to Pegasus's castle.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
