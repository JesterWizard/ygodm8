#include "event_macros.h"
#include "overworld.h"

/* map_12_state_08: map 12 state 8 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F180, map_12_state_08_08E6F180, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(407)
  PORTRAIT(PORTRAIT_SEEKER, EXPRESSION_NEUTRAL, 0)
  LANGUAGE_TEXT(0, "Kukuku... Fresh new prey to\nhunt...\n\n")
  END_LANGUAGE_TEXT()
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 96)
  WALK_OBJECT_Y(1, 68)
  WALK_OBJECT_X(1, 128)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, 1)
  LANGUAGE_TEXT(0, "There he is! It's him,\n{PLAYER}!\n\n")
  END_LANGUAGE_TEXT()
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, 1)
  LANGUAGE_TEXT(0, "He must be one of da\nremaining Neo Ghouls.\n\nHe's who Espa Roba was\ntalking about.\n\nI can't believe we couldn't\nfind him 'til now!\n\n")
  END_LANGUAGE_TEXT()
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, 1)
  LANGUAGE_TEXT(0, "Let's go!\n\n")
  END_LANGUAGE_TEXT()
  FADE_SCREEN(8)
  WARP(57, 2, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
