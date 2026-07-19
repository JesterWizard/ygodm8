#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_11_state_03: map 11 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E64358, map_11_state_03_08E64358, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_AMBUSHER)
  TEXT("I managed to hide my rare cards from the Neo Ghouls.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64364, map_11_state_03_08E64364, 0x08E64370, 0x08E64388)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_AMBUSHER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64370, map_11_state_03_08E64370, 0x08E6437C, 0x08F0404C)
  TEXT(
      "Do you know how hard it was to protect my rare cards?!",
      "I won't let you have one so easily!"
  )
  DUEL(DUELIST_ID_095)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6437C, map_11_state_03_08E6437C, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_BACK_ALLEY)
  TEXT("Tsk... After all I did to save that rare card...")
  SET_FLAG(EVENT_FLAG_DEFEATED_AMBUSHER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64388, map_11_state_03_08E64388, EVENT_NOP, EVENT_NOP)
  TEXT("I don't want to lose any more rare cards to you.")
  FALLTHROUGH()
END_EVENT_SCRIPT()
