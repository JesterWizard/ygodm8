#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_02_state_04: map 2 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08E47944, map_02_state_04_08E47944, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_BLUE_JACKET)
  LOAD_SPRITE(2, SPRITE_LINT)
  LOAD_SPRITE(3, SPRITE_MAI)
  TEXT("The Neo Ghouls weren't that scary, were they?")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47950, map_02_state_04_08E47950, 0x08E4795C, 0x08E47974)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_BLUE_JACKET2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4795C, map_02_state_04_08E4795C, 0x08E47968, 0x08F0404C)
  TEXT(
      "You're challenging me to a duel?",
      "Okay, sure. I'll take you on."
  )
  DUEL(DUELIST_ID_087)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47968, map_02_state_04_08E47968, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT("Uh... I guess I'm just not concentrating today.")
  SET_FLAG(EVENT_FLAG_DEFEATED_BLUE_JACKET2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47974, map_02_state_04_08E47974, EVENT_NOP, EVENT_NOP)
  TEXT("I'm not feeling good today. No thanks.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47980, map_02_state_04_08E47980, EVENT_NOP, EVENT_NOP)
  TEXT("Zompire is the awesomest!")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4798C, map_02_state_04_08E4798C, 0x08E47998, 0x08E479B0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_LINT2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47998, map_02_state_04_08E47998, 0x08E479A4, 0x08F0404C)
  TEXT(
      "A real hero doesn't run from a fight.",
      "That's why I'm going to stay and duel because that's",
      "what Zompire would do!"
  )
  DUEL(DUELIST_ID_088)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E479A4, map_02_state_04_08E479A4, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT(
      "I guess I'll never be a true hero...",
      "No! I have to push those negative thoughts out of my",
      "head!"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_LINT2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E479B0, map_02_state_04_08E479B0, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Only hard work will turn me from a zero into a hero.",
      "That's why I have to keep trying.",
      "Please duel with me again in the future."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E479BC, map_02_state_04_08E479BC, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "The Town of Domino is now safe.",
      "But you still have something to do, don't you?",
      "I'm going back to the cruise ship.",
      "Don't give up, {PLAYER}!"
  )
  WALK_OBJECT_Y(3, 39)
  WALK_OBJECT_X(3, 0)
  SET_OBJECT_POSITION(3, 128, 96, 0)
  SET_FLAG(EVENT_FLAG_MAI_LEFT_CLOCK_TOWER_SQUARE)
  SET_MAP_MUSIC(4)
  FALLTHROUGH()
END_EVENT_SCRIPT()
