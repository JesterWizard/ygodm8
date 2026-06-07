#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_07: map 0 state 7 */

EVENT_SCRIPT_REPLACEMENT(0x08E34BBC, map_00_state_07_08E34BBC, 0x08E34BD4, 0x08E34BE0)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_ISHIZU_AFTER_WATCHING_THE_KAIBAMAN_SHOW)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34BD4, map_00_state_07_08E34BD4, 0x08F04040, 0x08F04040)
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
    "It is always important to\n"
    "relax and take a step away\n\n"
    "from your main mission.\n\n"
    "For the road of destiny is\n"
    "not a straight path.\n\n"
    "There are many side roads\n"
    "and streets that you can\n\n"
    "wander along.\n\n"
    "The more roads you take, the\n"
    "more you will see of the\n\n"
    "world, and the more you will\n"
    "learn.\n\n"
    "However, Reshef is gaining\n"
    "power far faster than\n\n"
    "expected.\n\n"
    "We must return to the main\n"
    "path. Hurry and resurrect\n\n"
    "the Egyptian God Cards.\n\n"
    "The last Egyptian God Card\n"
    "remaining is The Winged\n\n"
    "Dragon of Ra.\n\n"
    "In order to restore the\n"
    "final Egyptian God Card\n\n"
    "from stone...\n\n"
    "Please hurry and obtain the\n"
    "next Millennium Item.\n\n"
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
      "In a place where prehistoric\n"
      "life forms are preserved in\n\n"
      "rock...\n\n"
      "A fossil excavation site in\n"
      "Canada.\n\n"
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_TALKED_TO_ISHIZU_AFTER_WATCHING_THE_KAIBAMAN_SHOW)
  SET_FLAG(EVENT_FLAG_UNLOCKED_CANADA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34BE0, map_00_state_07_08E34BE0, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "The Dark Being was\n"
    "resurrected by Sol\n\n"
    "Chevalsky...\n\n"
    "No, not Sol Chevalsky, but\n"
    "Pegasus.\n\n"
    "To imprison Reshef, we need\n"
    "one more Egyptian God Card.\n\n"
    "We need the power of The\n"
    "Winged Dragon of Ra.\n\n"
    "We must resurrect the card\n"
    "from stone.\n\n"
    "Please find the Millennium\n"
    "Items to restore it.\n\n"
    "The fifth Millennium Item is\n"
    "in Canada among fossils.\n\n"
    "You will find it at a fossil\n"
    "excavation site.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34BC8, map_00_state_07_08E34BC8, 0x08E34BD4, 0x08E34BEC)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_ISHIZU_AFTER_WATCHING_THE_KAIBAMAN_SHOW)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34BEC, map_00_state_07_08E34BEC, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Please. Hurry to the fossil\n"
    "excavation site.\n\n"
    "Reshef the Dark Being will\n"
    "soon engulf the world.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
