#include "event_macros.h"
#include "overworld.h"

/* map_42_state_04: map 42 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08ED9E54, map_42_state_04_08ED9E54, 0x08ED9DC4, 0x08F04040)
  PLAY_MUSIC(403)
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(32)
  MOVE_OBJECT(2, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT("I didn't realize until now\nthat you've gotten really\n\nstrong, {PLAYER}.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
