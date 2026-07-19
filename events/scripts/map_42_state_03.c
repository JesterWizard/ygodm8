#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_42_state_03: map 42 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08ED9E48, map_42_state_03_08ED9E48, 0x08ED9DC4, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_PANIK)
  LOAD_SPRITE(2, SPRITE_JOEY)
  LOAD_SPRITE(3, SPRITE_MIMIC_OF_DOOM)
  PLAY_MUSIC(MUSIC_403)
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  DELAY(32)
  MOVE_OBJECT(2, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_JOEY,
      "I didn't realize until now that you've gotten really",
      "strong, {PLAYER}."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
