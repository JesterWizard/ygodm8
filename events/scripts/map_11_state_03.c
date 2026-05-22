#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_11_state_03: map 11 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E64358, map_11_state_03_08E64358, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_AMBUSHER)
  TEXT
  (
      "I managed to hide my rare\n"
      "cards from the Neo Ghouls.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64364, map_11_state_03_08E64364, 0x08E64370, 0x08E64388)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_AMBUSHER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64370, map_11_state_03_08E64370, 0x08E6437C, 0x08F0404C)
  TEXT
  (
      "Do you know how hard it was\n"
      "to protect my rare cards?!\n\n"
      "I won't let you have one so\n"
      "easily!\n\n"
  )
  DUEL(95)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6437C, map_11_state_03_08E6437C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_BACK_ALLEY)
  TEXT
  (
      "Tsk... After all I did to\n"
      "save that rare card...\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_AMBUSHER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64388, map_11_state_03_08E64388, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I don't want to lose any\n"
      "more rare cards to you.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
