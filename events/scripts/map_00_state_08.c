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

EVENT_SCRIPT_REPLACEMENT(0x08E34C10, map_00_state_08_08E34C10, EVENT_NOP, EVENT_NOP)
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
      "I see you have obtained the Millennium Rod.",
      "Only two Millennium Items remain..."
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_1 | OBJECT_13 | OBJECT_14)
  PLAY_MUSIC(MUSIC_264)
  SCREEN_SHAKE(8)
  DELAY(8)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Reshef the Dark Being's power grows catastrophic!",
      "Time is running out!",
      "Please search for the next Millennium Item.",
      "The next Millennium Item is."
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
  TEXT("In the Galapagos Islands. Please hurry.")
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_ROD_TO_ISHIZU)
  SET_FLAG(EVENT_FLAG_UNLOCKED_GALAPAGOS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C1C, map_00_state_08_08E34C1C, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "The Dark Being was resurrected by Sol",
      "Chevalsky...",
      "I'm sorry, I meant Pegasus.",
      "To imprison Reshef, we need one more Egyptian God Card.",
      "We need the power of The Winged Dragon of Ra.",
      "We must resurrect the card from stone.",
      "Please find the Millennium Item to restore it.",
      "The sixth Millennium Item is in the Galapagos Islands.",
      "Please, you must hurry."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C04, map_00_state_08_08E34C04, 0x08E34C10, 0x08E34C28)
  CHECK_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_ROD_TO_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C28, map_00_state_08_08E34C28, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Please. Hurry to the Galapagos Islands.",
      "Reshef the Dark Being will soon engulf the world in",
      "shadows."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
