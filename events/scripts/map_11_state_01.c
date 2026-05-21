#include "event_macros.h"
#include "overworld.h"

/* map_11_state_01: map 11 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E642EC, map_11_state_01_08E642EC, 0x08E64304, 0x08E6431C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_AMBUSHER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64304, map_11_state_01_08E64304, 0x08E64310, 0x08F0404C)
  TEXT("You step into my territory\nand have the gall to\n\nchallenge me?\n\nWe'll duel for a rare card!\n\n")
  DUEL(11)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64310, map_11_state_01_08E64310, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(7)
  TEXT("Dagnabbit! You tricked me!\n\nI'm only here because I\nheard that all the tough\n\nduelists were somewhere\nelse.\n\nYou're supposed to be on the\nDuel Express, not dueling\n\nme!\n\n")
  SET_FLAG(EVENT_FLAG_DEFEATED_AMBUSHER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6431C, map_11_state_01_08E6431C, 0x08F04040, 0x08F04040)
  TEXT("Where's a wimpy duelist when\nyou need one...\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E642F8, map_11_state_01_08E642F8, 0x08E64304, 0x08E64328)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_AMBUSHER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64328, map_11_state_01_08E64328, 0x08F04040, 0x08F04040)
  TEXT("Go away already!\n\nYou're scaring all the weak\nduelists away!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
