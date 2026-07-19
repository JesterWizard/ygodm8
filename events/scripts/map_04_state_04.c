#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_04_state_04: map 4 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08E4D174, map_04_state_04_08E4D174, 0x08E4D180, 0x08E4D18C)
  LOAD_SPRITE(1, SPRITE_DUELIST_HATER)
  LOAD_SPRITE(2, SPRITE_TOURIST)
  LOAD_SPRITE(3, SPRITE_BONZ)
  TEXT(
      "Do all duelists want rare cards?",
      "{CARD_1}Yes\nNo{CARD_2}"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D180, map_04_state_04_08E4D180, EVENT_NOP, EVENT_NOP)
  TEXT(
      "The Neo Ghouls were also collecting rare cards.",
      "But stealing them by force... That's plain",
      "wrong."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D18C, map_04_state_04_08E4D18C, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Yeah, that's why those Neo Ghouls had their priorities",
      "mixed up."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D198, map_04_state_04_08E4D198, EVENT_NOP, EVENT_NOP)
  TEXT("Oh, no. I'm not a duelist.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D1A4, map_04_state_04_08E4D1A4, EVENT_NOP, EVENT_NOP)
  TEXT("You're... Not with the Neo Ghouls. Whew.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D1B0, map_04_state_04_08E4D1B0, EVENT_NOP, EVENT_NOP)
  TEXT("No, I've had enough duels to last me a lifetime.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D1BC, map_04_state_04_08E4D1BC, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "It's a little too bright out here.",
      "I'll make my way back to the graveyard. Home sweet home."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(3, 0)
  SET_OBJECT_POSITION(3, 128, 96, 0)
  SET_FLAG(EVENT_FLAG_BONZ_LEFT_CLOCK_TOWER_SQUARE)
  SET_MAP_MUSIC(4)
  FALLTHROUGH()
END_EVENT_SCRIPT()
