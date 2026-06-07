#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_60_state_03: map 60 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08F03AD4, map_60_state_03_08F03AD4, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_MARIK)
  LOAD_SPRITE(2, SPRITE_ODION)
  FADE_MUSIC(4)
  FADE_SCREEN(4)
  CLEAR_FLAG(226)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A68, map_60_state_03_08F03A68, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "The Winged Dragon of Ra has\n"
    "been fully awakened.\n\n"
    "{PLAYER}!\n\n"
    "Imprison Reshef with the\n"
    "power of Ra!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A74, map_60_state_03_08F03A74, 0x08F03A80, 0x08F0404C)
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "You wish to test Ra's full\n"
    "power on me?\n\n"
    "Fine. I accept.\n\n"
    "I will not hold anything\n"
    "back!\n\n"
)
  DUEL(DUELIST_MARIK_158)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A80, map_60_state_03_08F03A80, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_MARIK_ISHTAR)
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "...You are a true duelist.\n\n"
    "You can fully control The\n"
    "Winged Dragon of Ra.\n\n"
    "I did not realize how\n"
    "powerful you have become\n\n"
    "until now.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03AB0, map_60_state_03_08F03AB0, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Reshef toys with the spirits\n"
    "of duelists...\n\n"
    "It dominates through\n"
    "deception and terror.\n\n"
    "But before the Phoenix Mode,\n"
    "it will cower.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03ABC, map_60_state_03_08F03ABC, 0x08F03AC8, 0x08F0404C)
  TALK(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "{PLAYER}, you have obtained\n"
    "the power of the Egyptian\n\n"
    "God Phoenix.\n\n"
    "I have little idea how I\n"
    "will fare against you.\n\n"
    "But I accept your challenge.\n"
    "It's time to duel!\n\n"
)
  DUEL(DUELIST_ODION_157)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03AC8, map_60_state_03_08F03AC8, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_MARIK_ISHTAR)
  TALK(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Ah, yes. You have mastered\n"
    "the Phoenix Mode.\n\n"
    "I am no match for your\n"
    "brilliance.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
