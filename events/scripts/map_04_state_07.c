#include "event_macros.h"
#include "overworld.h"

/* map_04_state_07: map 4 state 7 */

EVENT_SCRIPT_REPLACEMENT(0x08E4D1D4, map_04_state_07_08E4D1D4, 0x08F04040, 0x08F04040)
  DELAY(16)
  WALK_OBJECT_X(1, 96)
  DELAY(32)
  MOVE_OBJECT(1, 2, 0, 0)
  DELAY(16)
  MOVE_OBJECT(1, 0, 0, 0)
  DELAY(16)
  MOVE_OBJECT(1, 3, 0, 0)
  DELAY(16)
  MOVE_OBJECT(1, 1, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT("I'm sure they're supposed to\nbe around here somewhere.\n\nHuh? They're not here yet?\n\n")
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(2, 24)
  PORTRAIT(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT("My cosmic powers tell me\nthis is the place.\n\nI hope they come back\nsafely.\n\n")
  COMMAND_7C_ARG(2, 8)
  FADE_SCREEN(8)
  WARP(1, 7, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
