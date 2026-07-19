#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_11_state_02: map 11 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E64334, map_11_state_02_08E64334, 0x08E64340, 0x08E6434C)
  LOAD_SPRITE(1, SPRITE_AMBUSHER)
  CHECK_FLAG(EVENT_FLAG_SCARED_AMBUSHER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64340, map_11_state_02_08E64340, EVENT_NOP, EVENT_NOP)
  TEXT("N-no! I swear, I wasn't hiding from you!")
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_1)
  TEXT(
      "Oh... You're not with the Neo Ghouls.",
      "Don't scare me like that, okay?"
  )
  SET_FLAG(EVENT_FLAG_SCARED_AMBUSHER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6434C, map_11_state_02_08E6434C, EVENT_NOP, EVENT_NOP)
  TEXT("I'm not giving up my rare cards to anyone.")
  FALLTHROUGH()
END_EVENT_SCRIPT()
