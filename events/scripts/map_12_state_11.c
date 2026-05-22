#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_12_state_11: map 12 state 11 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F168, map_12_state_11_08E6F168, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_ROLAND)
  LOAD_SPRITE(2, SPRITE_MOKUBA)
  LOAD_SPRITE(3, SPRITE_BIG_FIVE)
  LOAD_SPRITE(4, SPRITE_BIG_FIVE)
  LOAD_SPRITE(5, SPRITE_BIG_FIVE)
  LOAD_SPRITE(6, SPRITE_BIG_FIVE)
  LOAD_SPRITE(7, SPRITE_BIG_FIVE)
  PLAY_MUSIC(MUSIC_KAIBACORP)
  TEXT
  (
      "M-master Mokuba...\n\n"
      "Please, please give us one\n"
      "more chance.\n\n"
  )
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_ANGRY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "After all the horrible\n"
      "things you've done to us?\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I know we were wrong. But...\n\n"
      "Times are tough. No one has\n"
      "any money!\n\n"
      "We want to work, but no\n"
      "one's hiring.\n\n"
      "Please, we're begging you to\n"
      "rehire us.\n\n"
  )
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Well... I guess I have\n"
      "something for you...\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "R-really?\n\n"
      "Oh, thank you!\n\n"
  )
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "All right. Quick, get\n"
      "changed.\n\n"
  )
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_3 | OBJECT_4 | OBJECT_5 | OBJECT_6 | OBJECT_7)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Where's Serenity?\n\n"
  )
  FADE_SCREEN(4)
  WARP(57, 1, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
