#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_20_state_02: map 20 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E84F48, map_20_state_02_08E84F48, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_KAIBA_COSPLAYER)
  TEXT
  (
      "Grovel before me like the\n"
      "dog that you are!\n\n"
      "I'm trying to imitate Kaiba.\n"
      "Pretty good, right?\n\n"
      "Huh? He doesn't sound like\n"
      "that? A-are you sure?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F54, map_20_state_02_08E84F54, 0x08E84F60, 0x08E84F78)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_KAIBA_COSPLAYER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F60, map_20_state_02_08E84F60, 0x08E84F6C, 0x08F0404C)
  TEXT
  (
      "The road to victory lies in\n"
      "combat!\n\n"
      "With this duel, I will\n"
      "finish you!\n\n"
  )
  DUEL(DUELIST_ID_029)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F6C, map_20_state_02_08E84F6C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_231)
  TEXT
  (
      "Hahaha! Acting tough didn't\n"
      "do a thing for my\n\n"
      "strategies!\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_KAIBA_COSPLAYER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F78, map_20_state_02_08E84F78, 0x08F04040, 0x08F04040)
  TEXT
  (
      "No, it's okay.\n\n"
      "I now know that I can't win\n"
      "just by pretending to be\n\n"
      "Kaiba.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
