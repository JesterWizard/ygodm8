#include "event_macros.h"
#include "overworld.h"

/* map_20_state_02: map 20 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E84F48, map_20_state_02_08E84F48, 0x08F04040, 0x08F04040)
  TEXT("Grovel before me like the\ndog that you are!\n\nI'm trying to imitate Kaiba.\nPretty good, right?\n\nHuh? He doesn't sound like\nthat? A-are you sure?\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F54, map_20_state_02_08E84F54, 0x08E84F60, 0x08E84F78)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_KAIBA_COSPLAYER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F60, map_20_state_02_08E84F60, 0x08E84F6C, 0x08F0404C)
  TEXT("The road to victory lies in\ncombat!\n\nWith this duel, I will\nfinish you!\n\n")
  DUEL(29)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F6C, map_20_state_02_08E84F6C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(231)
  TEXT("Hahaha! Acting tough didn't\ndo a thing for my\n\nstrategies!\n\n")
  SET_FLAG(EVENT_FLAG_DEFEATED_KAIBA_COSPLAYER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F78, map_20_state_02_08E84F78, 0x08F04040, 0x08F04040)
  TEXT("No, it's okay.\n\nI now know that I can't win\njust by pretending to be\n\nKaiba.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
