#include "event_macros.h"
#include "overworld.h"

/* map_05_state_06: map 5 state 6 */

EVENT_SCRIPT_REPLACEMENT(0x08E51088, map_05_state_06_08E51088, 0x08F04040, 0x08F04040)
  DELAY(16)
  PLAY_MUSIC(293)
  OBJECT_EFFECT(2, 1)
  LANGUAGE_TEXT(0, "Oh no! I lost again.\n\n")
  END_LANGUAGE_TEXT()
  PLAY_MUSIC(293)
  OBJECT_EFFECT(4, 1)
  LANGUAGE_TEXT(0, "Hahah, I did it! Try harder\nnext time!\n\n")
  END_LANGUAGE_TEXT()
  PLAY_MUSIC(293)
  OBJECT_EFFECT(2, 1)
  LANGUAGE_TEXT(0, "Yeah, I'm not going to lose\nagain!\n\n")
  END_LANGUAGE_TEXT()
  FADE_SCREEN(8)
  WARP(6, 15, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
