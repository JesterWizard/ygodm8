#include "event_macros.h"
#include "overworld.h"

/* map_02_state_03: map 2 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E478E4, map_02_state_03_08E478E4, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "Those Neo Ghouls!\n\nThey'd better watch out or\nI'll pummel them next time!\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E478F0, map_02_state_03_08E478F0, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "Zompire is the most\nawesomest ever! He's my\n\nhero!\n\nOne day, I'm going to be\nstrong, just like Zompire.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E478FC, map_02_state_03_08E478FC, 0x08E47920, 0x08E47908)
  CHECK_FLAG(EVENT_FLAG_SEARCHING_FOR_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47920, map_02_state_03_08E47920, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "Leave it to me!\n\nThe Neo Ghouls are no match\nfor me!\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47908, map_02_state_03_08E47908, 0x08E47914, 0x08E47920)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47914, map_02_state_03_08E47914, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "There are Neo Ghouls still\nhiding in the Town of\n\nDomino?\n\nThat may explain some\nthings. There's something\n\nmysterious going on at\nKaibaCorp.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4792C, map_02_state_03_08E4792C, 0x08E47938, 0x08F0404C)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "You want to duel me for\npractice before facing the\n\nNeo Ghouls?\n\nI hope I don't beat you so\nhard that you don't feel\n\nlike dueling ever again.\n\n")
  END_LANGUAGE_TEXT()
  DUEL(58)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47938, map_02_state_03_08E47938, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(9)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "Good! Now show those same\ntechniques against the Neo\n\nGhouls.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
