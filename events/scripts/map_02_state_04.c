#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_02_state_04: map 2 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08E47944, map_02_state_04_08E47944, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_BLUE_JACKET)
  LOAD_SPRITE(2, SPRITE_LINT)
  LOAD_SPRITE(3, SPRITE_MAI)
  TEXT
  (
      "The Neo Ghouls weren't that\n"
      "scary, were they?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47950, map_02_state_04_08E47950, 0x08E4795C, 0x08E47974)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_BLUE_JACKET2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4795C, map_02_state_04_08E4795C, 0x08E47968, 0x08F0404C)
  TEXT
  (
      "You're challenging me to a\n"
      "duel?\n\n"
      "Okay, sure.\n"
      "I'll take you on.\n\n"
  )
  DUEL(DUELIST_ID_087)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47968, map_02_state_04_08E47968, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT
  (
      "Uh... I guess I'm just not\n"
      "concentrating today.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_BLUE_JACKET2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47974, map_02_state_04_08E47974, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I'm not feeling good today.\n"
      "No thanks.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47980, map_02_state_04_08E47980, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Zompire is the awesomest!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4798C, map_02_state_04_08E4798C, 0x08E47998, 0x08E479B0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_LINT2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47998, map_02_state_04_08E47998, 0x08E479A4, 0x08F0404C)
  TEXT
  (
      "A real hero doesn't run from\n"
      "a fight.\n\n"
      "That's why I'm going to stay\n"
      "and duel because that's\n\n"
      "what Zompire would do!\n\n"
  )
  DUEL(DUELIST_ID_088)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E479A4, map_02_state_04_08E479A4, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT
  (
      "I guess I'll never be a true\n"
      "hero...\n\n"
      "No! I have to push those\n"
      "negative thoughts out of my\n\n"
      "head!\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_LINT2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E479B0, map_02_state_04_08E479B0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Only hard work will turn me\n"
      "from a zero into a hero.\n\n"
      "That's why I have to keep\n"
      "trying.\n\n"
      "Please duel with me again in\n"
      "the future.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E479BC, map_02_state_04_08E479BC, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "The Town of Domino is now\n"
      "safe.\n\n"
      "But you still have something\n"
      "to do, don't you?\n\n"
      "I'm going back to the cruise\n"
      "ship.\n\n"
      "Don't give up, {PLAYER}!\n\n"
  )
  WALK_OBJECT_Y(3, 39)
  WALK_OBJECT_X(3, 0)
  SET_OBJECT_POSITION(3, 128, 96, 0)
  SET_FLAG(EVENT_FLAG_MAI_LEFT_CLOCK_TOWER_SQUARE)
  SET_MAP_MUSIC(4)
  FALLTHROUGH()
END_EVENT_SCRIPT()
