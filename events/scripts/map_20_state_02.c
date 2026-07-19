#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_20_state_02: map 20 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E84F48, map_20_state_02_08E84F48, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_KAIBA_COSPLAYER)
  TEXT(
      "Grovel before me like the dog that you are!",
      "I'm trying to imitate Kaiba. Pretty good, right?",
      "Huh? He doesn't sound like that? A-are you sure?"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F54, map_20_state_02_08E84F54, 0x08E84F60, 0x08E84F78)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_KAIBA_COSPLAYER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F60, map_20_state_02_08E84F60, 0x08E84F6C, 0x08F0404C)
  TEXT(
      "The road to victory lies in combat!",
      "With this duel, I will finish you!"
  )
  DUEL(DUELIST_ID_029)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F6C, map_20_state_02_08E84F6C, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_231)
  TEXT(
      "Hahaha! Acting tough didn't do a thing for my",
      "strategies!"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_KAIBA_COSPLAYER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F78, map_20_state_02_08E84F78, EVENT_NOP, EVENT_NOP)
  TEXT(
      "No, it's okay.",
      "I now know that I can't win just by pretending to be",
      "Kaiba."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
