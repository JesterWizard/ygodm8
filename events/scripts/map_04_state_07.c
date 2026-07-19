#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_04_state_07: map 4 state 7 */

EVENT_SCRIPT_REPLACEMENT(0x08E4D1D4, map_04_state_07_08E4D1D4, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_REX)
  LOAD_SPRITE(2, SPRITE_BONZ)
  DELAY(16)
  WALK_OBJECT_X(1, 96)
  DELAY(32)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_REX,
      "I'm sure they're supposed to be around here somewhere.",
      "Huh? They're not here yet?"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(2, 24)
  TALK(PORTRAIT_BONZ,
      "My cosmic powers tell me this is the place.",
      "I hope they come back safely."
  )
  FADE_MUSIC(8)
  FADE_SCREEN(8)
  WARP(LOCATION_CLOCK_TOWER_SQUARE_NORTH, 7, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
