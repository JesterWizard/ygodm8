#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_02_state_03: map 2 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E478E4, map_02_state_03_08E478E4, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_BLUE_JACKET)
  LOAD_SPRITE(2, SPRITE_LINT)
  LOAD_SPRITE(3, SPRITE_MAI)
  TEXT(
      "Those Neo Ghouls!",
      "They'd better watch out or I'll pummel them next time!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E478F0, map_02_state_03_08E478F0, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Zompire is the most awesomest ever! He's my",
      "hero!",
      "One day, I'm going to be strong, just like Zompire."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E478FC, map_02_state_03_08E478FC, 0x08E47920, 0x08E47908)
  CHECK_FLAG(EVENT_FLAG_SEARCHING_FOR_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47920, map_02_state_03_08E47920, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Leave it to me!",
      "The Neo Ghouls are no match for me!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47908, map_02_state_03_08E47908, 0x08E47914, 0x08E47920)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47914, map_02_state_03_08E47914, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "There are Neo Ghouls still hiding in the Town of",
      "Domino?",
      "That may explain some things. There's something",
      "mysterious going on at KaibaCorp."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4792C, map_02_state_03_08E4792C, 0x08E47938, 0x08F0404C)
  TALK(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You want to duel me for practice before facing the",
      "Neo Ghouls?",
      "I hope I don't beat you so hard that you don't feel",
      "like dueling ever again."
  )
  DUEL(DUELIST_MAI_058)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47938, map_02_state_03_08E47938, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_DOMINO_CITY_LIBERATED)
  TALK(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Good! Now show those same techniques against the Neo",
      "Ghouls."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
