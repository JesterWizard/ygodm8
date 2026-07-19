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
  TEXT(
      "You step into my territory and have the gall to",
      "challenge me?",
      "We'll duel for a rare card!"
  )
  DUEL(DUELIST_ID_011)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64310, map_11_state_01_08E64310, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_BACK_ALLEY)
  TEXT(
      "Dagnabbit! You tricked me!",
      "I'm only here because I heard that all the tough",
      "duelists were somewhere else.",
      "You're supposed to be on the Duel Express, not dueling",
      "me!"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_AMBUSHER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6431C, map_11_state_01_08E6431C, EVENT_NOP, EVENT_NOP)
  TEXT("Where's a wimpy duelist when you need one...")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E642F8, map_11_state_01_08E642F8, 0x08E64304, 0x08E64328)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_AMBUSHER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64328, map_11_state_01_08E64328, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Go away already!",
      "You're scaring all the weak duelists away!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
