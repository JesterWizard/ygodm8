#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_08: map 0 state 8 */


END()
EVENT_SCRIPT_REPLACEMENT(0x08E34BF8, map_00_state_08_08E34BF8, 0x08E34C10, 0x08E34C1C)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  LOAD_SPRITE(2, SPRITE_LUCKY)
  CHECK_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_ROD_TO_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C10, map_00_state_08_08E34C10, 0x08F04040, 0x08F04040)
  WALK_OBJECT_Y(0, 32)
  WALK_OBJECT_X(0, 48)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  WALK_OBJECT_Y(13, 42)
  WALK_OBJECT_X(13, 54)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  WALK_OBJECT_Y(14, 42)
  WALK_OBJECT_X(14, 42)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I see you have obtained the\n"
    "Millennium Rod.\n\n"
    "Only two Millennium Items\n"
    "remain...\n\n"
)
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_1 | OBJECT_13 | OBJECT_14)
  PLAY_MUSIC(MUSIC_264)
  SCREEN_SHAKE(8)
  DELAY(8)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Reshef the Dark Being's\n"
    "power grows catastrophic!\n\n"
    "Time is running out!\n\n"
    "Please search for the next\n"
    "Millennium Item.\n\n"
    "The next Millennium Item\n"
    "is."
)
  DELAY(43)
  TEXT
  (
      "."
  )
  DELAY(43)
  TEXT
  (
      "."
  )
  DELAY(43)
  TEXT
  (
      "\n\n"
      "In the Galapagos Islands.\n"
      "Please hurry.\n\n"
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_ROD_TO_ISHIZU)
  SET_FLAG(EVENT_FLAG_UNLOCKED_GALAPAGOS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C1C, map_00_state_08_08E34C1C, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "The Dark Being was\n"
    "resurrected by Sol\n\n"
    "Chevalsky...\n\n"
    "I'm sorry, I meant Pegasus.\n\n"
    "To imprison Reshef, we need\n"
    "one more Egyptian God Card.\n\n"
    "We need the power of The\n"
    "Winged Dragon of Ra.\n\n"
    "We must resurrect the card\n"
    "from stone.\n\n"
    "Please find the Millennium\n"
    "Item to restore it.\n\n"
    "The sixth Millennium Item is\n"
    "in the Galapagos Islands.\n\n"
    "Please, you must hurry.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C04, map_00_state_08_08E34C04, 0x08E34C10, 0x08E34C28)
  CHECK_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_ROD_TO_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C28, map_00_state_08_08E34C28, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Please. Hurry to the\n"
    "Galapagos Islands.\n\n"
    "Reshef the Dark Being will\n"
    "soon engulf the world in\n\n"
    "shadows.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
