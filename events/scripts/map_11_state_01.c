#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_11_state_01: map 11 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E642EC, map_11_state_01_08E642EC, 0x08E64304, 0x08E6431C)
  LOAD_SPRITE(1, SPRITE_AMBUSHER)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_AMBUSHER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64304, map_11_state_01_08E64304, 0x08E64310, 0x08F0404C)
  TEXT
  (
      "You step into my territory\n"
      "and have the gall to\n\n"
      "challenge me?\n\n"
      "We'll duel for a rare card!\n\n"
  )
  DUEL(11)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64310, map_11_state_01_08E64310, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_BACK_ALLEY)
  TEXT
  (
      "Dagnabbit! You tricked me!\n\n"
      "I'm only here because I\n"
      "heard that all the tough\n\n"
      "duelists were somewhere\n"
      "else.\n\n"
      "You're supposed to be on the\n"
      "Duel Express, not dueling\n\n"
      "me!\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_AMBUSHER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6431C, map_11_state_01_08E6431C, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Where's a wimpy duelist when\n"
      "you need one...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E642F8, map_11_state_01_08E642F8, 0x08E64304, 0x08E64328)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_AMBUSHER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64328, map_11_state_01_08E64328, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Go away already!\n\n"
      "You're scaring all the weak\n"
      "duelists away!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
