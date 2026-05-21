#include "event_macros.h"
#include "overworld.h"

/* map_02_state_04: map 2 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08E47944, map_02_state_04_08E47944, 0x08F04040, 0x08F04040)
  TEXT("The Neo Ghouls weren't that\nscary, were they?\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47950, map_02_state_04_08E47950, 0x08E4795C, 0x08E47974)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_BLUE_JACKET2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4795C, map_02_state_04_08E4795C, 0x08E47968, 0x08F0404C)
  TEXT("You're challenging me to a\nduel?\n\nOkay, sure.\nI'll take you on.\n\n")
  DUEL(87)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47968, map_02_state_04_08E47968, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(4)
  TEXT("Uh... I guess I'm just not\nconcentrating today.\n\n")
  SET_FLAG(EVENT_FLAG_DEFEATED_BLUE_JACKET2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47974, map_02_state_04_08E47974, 0x08F04040, 0x08F04040)
  TEXT("I'm not feeling good today.\nNo thanks.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47980, map_02_state_04_08E47980, 0x08F04040, 0x08F04040)
  TEXT("Zompire is the awesomest!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4798C, map_02_state_04_08E4798C, 0x08E47998, 0x08E479B0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_LINT2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47998, map_02_state_04_08E47998, 0x08E479A4, 0x08F0404C)
  TEXT("A real hero doesn't run from\na fight.\n\nThat's why I'm going to stay\nand duel because that's\n\nwhat Zompire would do!\n\n")
  DUEL(88)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E479A4, map_02_state_04_08E479A4, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(4)
  TEXT("I guess I'll never be a true\nhero...\n\nNo! I have to push those\nnegative thoughts out of my\n\nhead!\n\n")
  SET_FLAG(EVENT_FLAG_DEFEATED_LINT2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E479B0, map_02_state_04_08E479B0, 0x08F04040, 0x08F04040)
  TEXT("Only hard work will turn me\nfrom a zero into a hero.\n\nThat's why I have to keep\ntrying.\n\nPlease duel with me again in\nthe future.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E479BC, map_02_state_04_08E479BC, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("The Town of Domino is now\nsafe.\n\nBut you still have something\nto do, don't you?\n\nI'm going back to the cruise\nship.\n\nDon't give up, {PLAYER}!\n\n")
  WALK_OBJECT_Y(3, 39)
  WALK_OBJECT_X(3, 0)
  SET_OBJECT_POSITION(3, 128, 96, 0)
  SET_FLAG(EVENT_FLAG_MAI_LEFT_CLOCK_TOWER_SQUARE)
  SET_MAP_MUSIC(4)
  FALLTHROUGH()
END_EVENT_SCRIPT()
