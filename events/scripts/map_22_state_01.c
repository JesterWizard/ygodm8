#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_22_state_01: map 22 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E8CAB0, map_22_state_01_08E8CAB0, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_DAMIEN_DRACO)
  LOAD_SPRITE(2, SPRITE_TAKESHI)
  TEXT
  (
      "Here sleeps the power of\n"
      "ancient pharaohs.\n\n"
      "I know that ancient power\n"
      "will make me stronger!\n\n"
      "I will become a guardian of\n"
      "darkness...\n\n"
      "As long as the pharaohs give\n"
      "me power!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CABC, map_22_state_01_08E8CABC, 0x08E8CAC8, 0x08E8CAE0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_DAMIEN_DRACO2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CAC8, map_22_state_01_08E8CAC8, 0x08E8CAD4, 0x08F0404C)
  TEXT
  (
      "I'm most worthy of being a\n"
      "guardian of darkness.\n\n"
      "As such, this place is the\n"
      "most suitable location for\n\n"
      "my abilities!\n\n"
      "There is no way I can lose!\n\n"
  )
  DUEL(DUELIST_ID_030)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CAD4, map_22_state_01_08E8CAD4, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_230)
  TEXT
  (
      "I lost? B-but how?\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_DAMIEN_DRACO2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CAE0, map_22_state_01_08E8CAE0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Wh-where can I win?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CAEC, map_22_state_01_08E8CAEC, 0x08E8CAF8, 0x08E8CB04)
  CHECK_FLAG(EVENT_FLAG_TAKESHI_MOVED_OUT_OF_THE_WAY)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CAF8, map_22_state_01_08E8CAF8, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Did a dark, big guy come\n"
      "this way?\n\n"
      "Well, yes...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_LEFT, 16, 0)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TEXT
  (
      "He ran down the stairs here.\n\n"
  )
  SET_FLAG(EVENT_FLAG_TAKESHI_MOVED_OUT_OF_THE_WAY)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CB04, map_22_state_01_08E8CB04, 0x08F04040, 0x08F04040)
  TEXT
  (
      "The big man took off down\n"
      "the stairs here.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CB10, map_22_state_01_08E8CB10, 0x08F04040, 0x08F04040)
  TEXT
  (
      "No, I don't duel. You should\n"
      "find someone else.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
