#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_40_state_01: map 40 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08ED55F0, map_40_state_01_08ED55F0, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  PLAY_MUSIC(MUSIC_252)
  DELAY(8)
  WALK_OBJECT_X(1, 56)
  DELAY(8)
  WALK_OBJECT_X(0, 76)
  WALK_OBJECT_X(13, 86)
  WALK_OBJECT_X(14, 86)
  DELAY(16)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "So... This is Pegasus's island.",
      "Seto Kaiba has probably already gone ahead."
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  HIDE_PORTRAIT()
  DELAY(48)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I do not know what Pegasus is planning.",
      "But we cannot ignore Reshef the Dark Being.",
      "Harsh battles await.",
      "But don't succumb in the face of adversity."
  )
  SET_FLAG(EVENT_FLAG_ENTERED_PEGASUS_ISLAND)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED5608, map_40_state_01_08ED5608, 0x08F04244, EVENT_NOP)
  SET_FLAG(EVENT_FLAG_LEAVING_THE_CABLE_CAR_LEADS_TO_THE_TOP_OF_PEGASUS_ISLAND)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED55FC, map_40_state_01_08ED55FC, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "The Duelist Kingdom Tournament was once held",
      "here.",
      "However, the island has been transformed since then.",
      "There must be many duelists under Reshef's control.",
      "They're ready to ambush us.",
      "Be careful as you make your way to Pegasus's castle."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
