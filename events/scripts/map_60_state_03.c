#include "event_macros.h"
#include "overworld.h"

/* map_60_state_03: map 60 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08F03AD4, map_60_state_03_08F03AD4, 0x08F04040, 0x08F04040)
  COMMAND_7C_ARG(2, 4)
  FADE_SCREEN(4)
  CLEAR_FLAG(226)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A68, map_60_state_03_08F03A68, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("The Winged Dragon of Ra has\nbeen fully awakened.\n\n{PLAYER}!\n\nImprison Reshef with the\npower of Ra!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A74, map_60_state_03_08F03A74, 0x08F03A80, 0x08F0404C)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("You wish to test Ra's full\npower on me?\n\nFine. I accept.\n\nI will not hold anything\nback!\n\n")
  DUEL(158)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A80, map_60_state_03_08F03A80, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(27)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("...You are a true duelist.\n\nYou can fully control The\nWinged Dragon of Ra.\n\nI did not realize how\npowerful you have become\n\nuntil now.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03AB0, map_60_state_03_08F03AB0, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Reshef toys with the spirits\nof duelists...\n\nIt dominates through\ndeception and terror.\n\nBut before the Phoenix Mode,\nit will cower.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03ABC, map_60_state_03_08F03ABC, 0x08F03AC8, 0x08F0404C)
  PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("{PLAYER}, you have obtained\nthe power of the Egyptian\n\nGod Phoenix.\n\nI have little idea how I\nwill fare against you.\n\nBut I accept your challenge.\nIt's time to duel!\n\n")
  DUEL(157)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03AC8, map_60_state_03_08F03AC8, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(27)
  PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Ah, yes. You have mastered\nthe Phoenix Mode.\n\nI am no match for your\nbrilliance.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
