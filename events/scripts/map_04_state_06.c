#include "event_macros.h"
#include "overworld.h"

/* map_04_state_06: map 4 state 6 */

EVENT_SCRIPT_REPLACEMENT(0x08E4D1C8, map_04_state_06_08E4D1C8, 0x08F04040, 0x08F04040)
  DELAY(16)
  PLAY_MUSIC(293)
  OBJECT_EFFECT(2, 1)
  TEXT("Let's duel!\n\n")
  PLAY_MUSIC(293)
  OBJECT_EFFECT(4, 1)
  TEXT("Okay.\n\n")
  FADE_SCREEN(8)
  WARP(5, 6, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
