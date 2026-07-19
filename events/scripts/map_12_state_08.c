#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_12_state_08: map 12 state 8 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F180, map_12_state_08_08E6F180, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_SEEKER)
  PLAY_MUSIC(MUSIC_407)
  TALK(PORTRAIT_SEEKER, "Kukuku... Fresh new prey to hunt...")
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 96)
  WALK_OBJECT_Y(1, 68)
  WALK_OBJECT_X(1, 128)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "There he is! It's him, {PLAYER}!")
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "He must be one of da remaining Neo Ghouls.",
      "He's who Espa Roba was talking about.",
      "I can't believe we couldn't find him 'til now!"
  )
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "Let's go!")
  FADE_SCREEN(8)
  WARP(LOCATION_KAIBA_LAND, 2, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
