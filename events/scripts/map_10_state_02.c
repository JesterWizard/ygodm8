#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_10_state_02: map 10 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E63254, map_10_state_02_08E63254, 0x08E63260, 0x08E6326C)
  LOAD_SPRITE(1, SPRITE_LOST_DUELIST)
  CHECK_FLAG(EVENT_FLAG_SCARED_LOST_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E63260, map_10_state_02_08E63260, 0x08F04040, 0x08F04040)
  TEXT
  (
      "S-sorry! I have no more rare\n"
      "cards to give you!\n\n"
  )
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_1)
  TEXT
  (
      "Huh? You're not the Neo\n"
      "Ghouls?\n\n"
      "Don't scare me like that!\n\n"
      "Those thugs shook me down\n"
      "and took my rare cards...\n\n"
      "I'm so angry...\n\n"
  )
  SET_FLAG(EVENT_FLAG_SCARED_LOST_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6326C, map_10_state_02_08E6326C, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I'm going to practice until\n"
      "the Neo Ghouls can't beat\n\n"
      "me!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
