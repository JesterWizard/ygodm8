#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_22_state_01: map 22 state 1 */


END()
EVENT_SCRIPT_REPLACEMENT(0x08E8CAB0, map_22_state_01_08E8CAB0, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_DAMIEN_DRACO)
  LOAD_SPRITE(2, SPRITE_TAKESHI)
  TEXT(
      "Here sleeps the power of ancient pharaohs.",
      "I know that ancient power will make me stronger!",
      "I will become a guardian of darkness...",
      "As long as the pharaohs give me power!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CABC, map_22_state_01_08E8CABC, 0x08E8CAC8, 0x08E8CAE0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_DAMIEN_DRACO2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CAC8, map_22_state_01_08E8CAC8, 0x08E8CAD4, 0x08F0404C)
  TEXT(
      "I'm most worthy of being a guardian of darkness.",
      "As such, this place is the most suitable location for",
      "my abilities!",
      "There is no way I can lose!"
  )
  DUEL(DUELIST_ID_030)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CAD4, map_22_state_01_08E8CAD4, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_230)
  TEXT("I lost? B-but how?")
  SET_FLAG(EVENT_FLAG_DEFEATED_DAMIEN_DRACO2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CAE0, map_22_state_01_08E8CAE0, EVENT_NOP, EVENT_NOP)
  TEXT("Wh-where can I win?")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CAEC, map_22_state_01_08E8CAEC, 0x08E8CAF8, 0x08E8CB04)
  CHECK_FLAG(EVENT_FLAG_TAKESHI_MOVED_OUT_OF_THE_WAY)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CAF8, map_22_state_01_08E8CAF8, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Did a dark, big guy come this way?",
      "Well, yes..."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_LEFT, 16, 0)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TEXT("He ran down the stairs here.")
  SET_FLAG(EVENT_FLAG_TAKESHI_MOVED_OUT_OF_THE_WAY)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CB04, map_22_state_01_08E8CB04, EVENT_NOP, EVENT_NOP)
  TEXT("The big man took off down the stairs here.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CB10, map_22_state_01_08E8CB10, EVENT_NOP, EVENT_NOP)
  TEXT("No, I don't duel. You should find someone else.")
  FALLTHROUGH()
END_EVENT_SCRIPT()
