#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_04_state_04: map 4 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08E4D174, map_04_state_04_08E4D174, 0x08E4D180, 0x08E4D18C)
  LOAD_SPRITE(1, SPRITE_DUELIST_HATER)
  LOAD_SPRITE(2, SPRITE_TOURIST)
  LOAD_SPRITE(3, SPRITE_BONZ)
  TEXT
  (
      "Do all duelists want rare\n"
      "cards?\n\n"
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D180, map_04_state_04_08E4D180, 0x08F04040, 0x08F04040)
  TEXT
  (
      "The Neo Ghouls were also\n"
      "collecting rare cards.\n\n"
      "But stealing them by\n"
      "force... That's plain\n\n"
      "wrong.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D18C, map_04_state_04_08E4D18C, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Yeah, that's why those Neo\n"
      "Ghouls had their priorities\n\n"
      "mixed up.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D198, map_04_state_04_08E4D198, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Oh, no. I'm not a duelist.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D1A4, map_04_state_04_08E4D1A4, 0x08F04040, 0x08F04040)
  TEXT
  (
      "You're... Not with the Neo\n"
      "Ghouls. Whew.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D1B0, map_04_state_04_08E4D1B0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "No, I've had enough duels to\n"
      "last me a lifetime.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D1BC, map_04_state_04_08E4D1BC, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "It's a little too bright out\n"
    "here.\n\n"
    "I'll make my way back to the\n"
    "graveyard. Home sweet home.\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(3, 0)
  SET_OBJECT_POSITION(3, 128, 96, 0)
  SET_FLAG(EVENT_FLAG_BONZ_LEFT_CLOCK_TOWER_SQUARE)
  SET_MAP_MUSIC(4)
  FALLTHROUGH()
END_EVENT_SCRIPT()
