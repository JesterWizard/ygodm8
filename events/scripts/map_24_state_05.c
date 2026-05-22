#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_24_state_05: map 24 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E9821C, map_24_state_05_08E9821C, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_TAKESHI)
  LOAD_SPRITE(2, SPRITE_ETSUKO)
  TEXT
  (
      "It's so awesome that the Neo\n"
      "Ghouls are gone.\n\n"
  )
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98228, map_24_state_05_08E98228, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Get lost! Stop making fun of\n"
      "me!\n\n"
      "How am I supposed to duel\n"
      "without any cards?\n\n"
      "The Neo Ghouls stole every\n"
      "one of my cards!\n\n"
  )
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98234, map_24_state_05_08E98234, 0x08F04040, 0x08F04040)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  TEXT
  (
      "Takeshi, like, I don't care\n"
      "if you can't duel. I love\n\n"
      "you!\n\n"
  )
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98240, map_24_state_05_08E98240, 0x08F04040, 0x08F04040)
  TEXT
  (
      "What are you, like some kind\n"
      "of dueling fanatic?\n\n"
      "You're, like, totally\n"
      "bugging me! Go away.\n\n"
  )
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
