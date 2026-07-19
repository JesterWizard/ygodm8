#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_24_state_05: map 24 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E9821C, map_24_state_05_08E9821C, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_TAKESHI)
  LOAD_SPRITE(2, SPRITE_ETSUKO)
  TEXT("It's so awesome that the Neo Ghouls are gone.")
  MOVE_OBJECT(SPRITE_TAKESHI, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98228, map_24_state_05_08E98228, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Get lost! Stop making fun of me!",
      "How am I supposed to duel without any cards?",
      "The Neo Ghouls stole every one of my cards!"
  )
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98234, map_24_state_05_08E98234, EVENT_NOP, EVENT_NOP)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  TEXT(
      "Takeshi, like, I don't care if you can't duel. I love",
      "you!"
  )
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98240, map_24_state_05_08E98240, EVENT_NOP, EVENT_NOP)
  TEXT(
      "What are you, like some kind of dueling fanatic?",
      "You're, like, totally bugging me! Go away."
  )
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
