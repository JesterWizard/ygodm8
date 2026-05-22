#include "event_macros.h"
#include "overworld.h"

/* map_11_state_02: map 11 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E64334, map_11_state_02_08E64334, 0x08E64340, 0x08E6434C)
  LOAD_SPRITE(1, SPRITE_AMBUSHER)
  CHECK_FLAG(EVENT_FLAG_SCARED_AMBUSHER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64340, map_11_state_02_08E64340, 0x08F04040, 0x08F04040)
  TEXT("N-no! I swear, I wasn't\nhiding from you!\n\n")
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, 2)
  TEXT("Oh... You're not with the\nNeo Ghouls.\n\nDon't scare me like that,\nokay?\n\n")
  SET_FLAG(EVENT_FLAG_SCARED_AMBUSHER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6434C, map_11_state_02_08E6434C, 0x08F04040, 0x08F04040)
  TEXT("I'm not giving up my rare\ncards to anyone.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
