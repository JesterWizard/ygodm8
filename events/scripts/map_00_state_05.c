#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_05: map 0 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E34B14, map_00_state_05_08E34B14, 0x08E34B2C, 0x08E34B38)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  CHECK_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_RING_TO_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B2C, map_00_state_05_08E34B2C, EVENT_NOP, EVENT_NOP)
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
      "Bandit Keith is also searching for the",
      "Millennium Items...",
      "I am afraid that he complicates matters",
      "greatly.",
      "Our need for urgency has increased.",
      "Reshef the Dark Being is insidious.",
      "He exploits the weaknesses in the souls of duelists.",
      "I hope that Bandit Keith does not succumb to his",
      "power...",
      "Fortunately, Bandit Keith did not find the Millennium",
      "Ring.",
      "That is a ray of hope among all this darkness.",
      "Four Millennium Items remain...",
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
  TEXT(
      "China. At the Great Wall.",
      "The Dark Being's power is intensifying with every",
      "passing moment.",
      "Please find the next Millennium Item quickly."
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_RING_TO_ISHIZU)
  SET_FLAG(EVENT_FLAG_UNLOCKED_CHINA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B38, map_00_state_05_08E34B38, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Sol Chevalsky resurrected the Dark Being...",
      "We need the Egyptian God Cards to stop it.",
      "We must restore the Egyptian God Cards from stone.",
      "But in order to do so, we require the Millennium",
      "Items.",
      "The fourth item is at the Great Wall of China.",
      "Please recover it as soon as you can."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B20, map_00_state_05_08E34B20, 0x08E34B2C, 0x08E34B44)
  CHECK_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_RING_TO_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B44, map_00_state_05_08E34B44, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Please. Hurry to the Great Wall of China.",
      "Reshef the Dark Being will soon engulf the world."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
