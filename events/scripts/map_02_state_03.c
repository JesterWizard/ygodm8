#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_02_state_03: map 2 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E478E4, map_02_state_03_08E478E4, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_BLUE_JACKET)
  LOAD_SPRITE(2, SPRITE_LINT)
  LOAD_SPRITE(3, SPRITE_MAI)
  TEXT
  (
      "Those Neo Ghouls!\n\n"
      "They'd better watch out or\n"
      "I'll pummel them next time!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E478F0, map_02_state_03_08E478F0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Zompire is the most\n"
      "awesomest ever! He's my\n\n"
      "hero!\n\n"
      "One day, I'm going to be\n"
      "strong, just like Zompire.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E478FC, map_02_state_03_08E478FC, 0x08E47920, 0x08E47908)
  CHECK_FLAG(EVENT_FLAG_SEARCHING_FOR_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47920, map_02_state_03_08E47920, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Leave it to me!\n\n"
      "The Neo Ghouls are no match\n"
      "for me!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47908, map_02_state_03_08E47908, 0x08E47914, 0x08E47920)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47914, map_02_state_03_08E47914, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "There are Neo Ghouls still\n"
      "hiding in the Town of\n\n"
      "Domino?\n\n"
      "That may explain some\n"
      "things. There's something\n\n"
      "mysterious going on at\n"
      "KaibaCorp.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4792C, map_02_state_03_08E4792C, 0x08E47938, 0x08F0404C)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You want to duel me for\n"
      "practice before facing the\n\n"
      "Neo Ghouls?\n\n"
      "I hope I don't beat you so\n"
      "hard that you don't feel\n\n"
      "like dueling ever again.\n\n"
  )
  DUEL(DUELIST_MAI_058)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47938, map_02_state_03_08E47938, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_DOMINO_CITY_LIBERATED)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Good! Now show those same\n"
      "techniques against the Neo\n\n"
      "Ghouls.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
