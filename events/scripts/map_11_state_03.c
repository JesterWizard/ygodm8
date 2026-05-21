#include "event_macros.h"
#include "overworld.h"

/* map_11_state_03: map 11 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E64358, map_11_state_03_08E64358, 0x08F04040, 0x08F04040)
  TEXT("I managed to hide my rare\ncards from the Neo Ghouls.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64364, map_11_state_03_08E64364, 0x08E64370, 0x08E64388)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_AMBUSHER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64370, map_11_state_03_08E64370, 0x08E6437C, 0x08F0404C)
  TEXT("Do you know how hard it was\nto protect my rare cards?!\n\nI won't let you have one so\neasily!\n\n")
  DUEL(95)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6437C, map_11_state_03_08E6437C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(7)
  TEXT("Tsk... After all I did to\nsave that rare card...\n\n")
  SET_FLAG(EVENT_FLAG_DEFEATED_AMBUSHER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64388, map_11_state_03_08E64388, 0x08F04040, 0x08F04040)
  TEXT("I don't want to lose any\nmore rare cards to you.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
