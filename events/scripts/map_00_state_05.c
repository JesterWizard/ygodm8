#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_05: map 0 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E34B14, map_00_state_05_08E34B14, 0x08E34B2C, 0x08E34B38)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  CHECK_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_RING_TO_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B2C, map_00_state_05_08E34B2C, 0x08F04040, 0x08F04040)
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
  COMMAND_7C_ARG(2, 2)
  DELAY(32)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Bandit Keith is also\n"
      "searching for the\n\n"
      "Millennium Items...\n\n"
      "I am afraid that he\n"
      "complicates matters\n\n"
      "greatly.\n\n"
      "Our need for urgency has\n"
      "increased.\n\n"
      "Reshef the Dark Being is\n"
      "insidious.\n\n"
      "He exploits the weaknesses\n"
      "in the souls of duelists.\n\n"
      "I hope that Bandit Keith\n"
      "does not succumb to his\n\n"
      "power...\n\n"
      "Fortunately, Bandit Keith\n"
      "did not find the Millennium\n\n"
      "Ring.\n\n"
      "That is a ray of hope among\n"
      "all this darkness.\n\n"
      "Four Millennium Items\n"
      "remain...\n\n"
      "And the next one is in."
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
      "\n"
      "China. At the Great Wall.\n\n"
      "The Dark Being's power is\n"
      "intensifying with every\n\n"
      "passing moment.\n\n"
      "Please find the next\n"
      "Millennium Item quickly.\n\n"
  )
  HIDE_PORTRAIT()
  COMMAND_7C_ARG(2, 2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_RING_TO_ISHIZU)
  SET_FLAG(EVENT_FLAG_UNLOCKED_CHINA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B38, map_00_state_05_08E34B38, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Sol Chevalsky resurrected\n"
      "the Dark Being...\n\n"
      "We need the Egyptian God\n"
      "Cards to stop it.\n\n"
      "We must restore the Egyptian\n"
      "God Cards from stone.\n\n"
      "But in order to do so, we\n"
      "require the Millennium\n\n"
      "Items.\n\n"
      "The fourth item is at the\n"
      "Great Wall of China.\n\n"
      "Please recover it as soon as\n"
      "you can.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B20, map_00_state_05_08E34B20, 0x08E34B2C, 0x08E34B44)
  CHECK_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_RING_TO_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B44, map_00_state_05_08E34B44, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Please. Hurry to the Great\n"
      "Wall of China.\n\n"
      "Reshef the Dark Being will\n"
      "soon engulf the world.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
