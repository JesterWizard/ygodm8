#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_10_state_02: map 10 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E63254, map_10_state_02_08E63254, 0x08E63260, 0x08E6326C)
  LOAD_SPRITE(1, SPRITE_LOST_DUELIST)
  CHECK_FLAG(EVENT_FLAG_SCARED_LOST_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E63260, map_10_state_02_08E63260, EVENT_NOP, EVENT_NOP)
  TEXT("S-sorry! I have no more rare cards to give you!")
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_1)
  TEXT(
      "Huh? You're not the Neo Ghouls?",
      "Don't scare me like that!",
      "Those thugs shook me down and took my rare cards...",
      "I'm so angry..."
  )
  SET_FLAG(EVENT_FLAG_SCARED_LOST_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6326C, map_10_state_02_08E6326C, EVENT_NOP, EVENT_NOP)
  TEXT(
      "I'm going to practice until the Neo Ghouls can't beat",
      "me!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
