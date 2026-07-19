#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_07: map 0 state 7 */


END()
EVENT_SCRIPT_REPLACEMENT(0x08E34BBC, map_00_state_07_08E34BBC, 0x08E34BD4, 0x08E34BE0)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_ISHIZU_AFTER_WATCHING_THE_KAIBAMAN_SHOW)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34BD4, map_00_state_07_08E34BD4, EVENT_NOP, EVENT_NOP)
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
      "It is always important to relax and take a step away",
      "from your main mission.",
      "For the road of destiny is not a straight path.",
      "There are many side roads and streets that you can",
      "wander along.",
      "The more roads you take, the more you will see of the",
      "world, and the more you will learn.",
      "However, Reshef is gaining power far faster than",
      "expected.",
      "We must return to the main path. Hurry and resurrect",
      "the Egyptian God Cards.",
      "The last Egyptian God Card remaining is The Winged",
      "Dragon of Ra.",
      "In order to restore the final Egyptian God Card",
      "from stone...",
      "Please hurry and obtain the next Millennium Item.",
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
  TEXT(
      "In a place where prehistoric life forms are preserved in",
      "rock...",
      "A fossil excavation site in Canada."
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_TALKED_TO_ISHIZU_AFTER_WATCHING_THE_KAIBAMAN_SHOW)
  SET_FLAG(EVENT_FLAG_UNLOCKED_CANADA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34BE0, map_00_state_07_08E34BE0, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "The Dark Being was resurrected by Sol",
      "Chevalsky...",
      "No, not Sol Chevalsky, but Pegasus.",
      "To imprison Reshef, we need one more Egyptian God Card.",
      "We need the power of The Winged Dragon of Ra.",
      "We must resurrect the card from stone.",
      "Please find the Millennium Items to restore it.",
      "The fifth Millennium Item is in Canada among fossils.",
      "You will find it at a fossil excavation site."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34BC8, map_00_state_07_08E34BC8, 0x08E34BD4, 0x08E34BEC)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_ISHIZU_AFTER_WATCHING_THE_KAIBAMAN_SHOW)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34BEC, map_00_state_07_08E34BEC, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Please. Hurry to the fossil excavation site.",
      "Reshef the Dark Being will soon engulf the world."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
