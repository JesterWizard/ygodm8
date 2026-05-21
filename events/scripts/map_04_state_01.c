#include "event_macros.h"
#include "overworld.h"

/* map_04_state_01: map 4 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E4D03C, map_04_state_01_08E4D03C, 0x08F04040, 0x08F04040)
  TEXT("You say you're a true\nduelist, but you're just an\n\namateur that likes playing\ngames.\n\nYou're all talk!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D048, map_04_state_01_08E4D048, 0x08F04040, 0x08F04040)
  TEXT("No way, I don't duel.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D054, map_04_state_01_08E4D054, 0x08F04040, 0x08F04040)
  TEXT("You're a duelist, aren't\nyou?\n\nI can tell from your Duel\nDisk.\n\nBoy, there sure are a lot of\nduelists in the Town of\n\nDomino.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D060, map_04_state_01_08E4D060, 0x08E4D06C, 0x08E4D084)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_TOURIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D06C, map_04_state_01_08E4D06C, 0x08E4D078, 0x08F0404C)
  TEXT("A street duel in the city\nwhere the Duel Disk was\n\ninvented...\n\nThis is exactly the duel\nI've been waiting for!\n\nLet's duel!\n\n")
  DUEL(7)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D078, map_04_state_01_08E4D078, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(4)
  TEXT("Are all the duelists in the\nTown of Domino this strong?\n\nI'm way out of my league.\n\n")
  SET_FLAG(EVENT_FLAG_DEFEATED_TOURIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D084, map_04_state_01_08E4D084, 0x08F04040, 0x08F04040)
  TEXT("Nah, I know now that you're\nan expert..\n\nWhy don't you look for other\nduelists?\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
