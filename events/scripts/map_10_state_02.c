#include "event_macros.h"
#include "overworld.h"

/* map_10_state_02: map 10 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E63254, map_10_state_02_08E63254, 0x08E63260, 0x08E6326C)
  LOAD_SPRITE(1, SPRITE_LOST_DUELIST)
  CHECK_FLAG(EVENT_FLAG_SCARED_LOST_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E63260, map_10_state_02_08E63260, 0x08F04040, 0x08F04040)
  TEXT("S-sorry! I have no more rare\ncards to give you!\n\n")
  PLAY_MUSIC(272)
  REACTION(REACTION_ELLIPSIS, 2)
  TEXT("Huh? You're not the Neo\nGhouls?\n\nDon't scare me like that!\n\nThose thugs shook me down\nand took my rare cards...\n\nI'm so angry...\n\n")
  SET_FLAG(EVENT_FLAG_SCARED_LOST_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6326C, map_10_state_02_08E6326C, 0x08F04040, 0x08F04040)
  TEXT("I'm going to practice until\nthe Neo Ghouls can't beat\n\nme!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
