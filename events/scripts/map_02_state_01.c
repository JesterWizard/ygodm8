#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_02_state_01: map 2 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E477DC, map_02_state_01_08E477DC, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_BLUE_JACKET)
  LOAD_SPRITE(2, SPRITE_LINT)
  TEXT
  (
      "Street duels are the hippest\n"
      "thing right now.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E477E8, map_02_state_01_08E477E8, 0x08E477F4, 0x08E4780C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_BLUE_JACKET)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E477F4, map_02_state_01_08E477F4, 0x08E47800, 0x08F0404C)
  TEXT
  (
      "You wanna get with the times\n"
      "and have a street battle?\n\n"
      "You're on!\n\n"
  )
  DUEL(DUELIST_ID_003)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47800, map_02_state_01_08E47800, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT
  (
      "Yeah, you gotta admit,\n"
      "street duels are pretty\n\n"
      "fly.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_BLUE_JACKET)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4780C, map_02_state_01_08E4780C, 0x08F04040, 0x08F04040)
  TEXT
  (
      "No, I've had enough for\n"
      "today.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47818, map_02_state_01_08E47818, 0x08F04040, 0x08F04040)
  TEXT
  (
      "KaibaCorp chartered an\n"
      "entire express train.\n\n"
      "For a duel tournament called\n"
      "Duel Express.\n\n"
      "It's amazing what rich\n"
      "people can do!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47824, map_02_state_01_08E47824, 0x08E47830, 0x08E47848)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_LINT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47830, map_02_state_01_08E47830, 0x08E4783C, 0x08F0404C)
  TEXT
  (
      "Even I'm willing to take on\n"
      "a duel!\n\n"
  )
  DUEL(DUELIST_ID_004)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4783C, map_02_state_01_08E4783C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT
  (
      "Well, that was fun.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_LINT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47848, map_02_state_01_08E47848, 0x08F04040, 0x08F04040)
  TEXT
  (
      "We should play again some\n"
      "other time.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
