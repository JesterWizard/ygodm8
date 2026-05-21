#include "event_macros.h"
#include "overworld.h"

/* map_12_state_08: map 12 state 8 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F180, map_12_state_08_08E6F180, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_SEEKER)
  PLAY_MUSIC(407)
  PORTRAIT(PORTRAIT_SEEKER, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT("Kukuku... Fresh new prey to\nhunt...\n\n")
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 96)
  WALK_OBJECT_Y(1, 68)
  WALK_OBJECT_X(1, 128)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT("There he is! It's him,\n{PLAYER}!\n\n")
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT("He must be one of da\nremaining Neo Ghouls.\n\nHe's who Espa Roba was\ntalking about.\n\nI can't believe we couldn't\nfind him 'til now!\n\n")
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT("Let's go!\n\n")
  FADE_SCREEN(8)
  WARP(57, 2, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
