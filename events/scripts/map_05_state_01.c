#include "event_macros.h"
#include "overworld.h"

/* map_05_state_01: map 5 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E50EA8, map_05_state_01_08E50EA8, 0x08F04040, 0x08F04040)
  TEXT("I won't be riding the Duel\nExpress...\n\nBut that doesn't mean my\nduelist level is low!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EB4, map_05_state_01_08E50EB4, 0x08E50EC0, 0x08E50ED8)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_STRINGER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EC0, map_05_state_01_08E50EC0, 0x08E50ECC, 0x08F0404C)
  TEXT("I still have my pride as a\nduelist.\n\nI don't feel like dueling,\nbut I'll still take you on\n\nfair and square.\n\n")
  DUEL(8)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50ECC, map_05_state_01_08E50ECC, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(4)
  TEXT("Instead of fair and square,\nmaybe we should've played\n\nby my rules.\n\n")
  SET_FLAG(EVENT_FLAG_DEFEATED_STRINGER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50ED8, map_05_state_01_08E50ED8, 0x08F04040, 0x08F04040)
  TEXT("Let me tell this to you\nstraight. I'm not one of\n\nthose gracious losers. I\nhate losing!\n\nIt's no fun to lose to a\ntough duelist.\n\nSo you can forget about\ndueling me ever again.\n\nHumph!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EE4, map_05_state_01_08E50EE4, 0x08F04040, 0x08F04040)
  TEXT("Did you hear about the Duel\nExpress?\n\nAny duelist can get on\nboard.\n\nMaybe I should go, too.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EF0, map_05_state_01_08E50EF0, 0x08E50EFC, 0x08E50F14)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_RED_MOHAWK)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EFC, map_05_state_01_08E50EFC, 0x08E50F08, 0x08F0404C)
  TEXT("Sure thing!\n\nA duel's a duel, no matter\nwhere it's played!\n\n")
  DUEL(9)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50F08, map_05_state_01_08E50F08, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(4)
  TEXT("Tsk... Lost that one.\n\n")
  SET_FLAG(EVENT_FLAG_DEFEATED_RED_MOHAWK)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50F14, map_05_state_01_08E50F14, 0x08F04040, 0x08F04040)
  TEXT("Huh? You again? Are you\npicking on me, you bully!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
