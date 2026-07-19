#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_12_state_11: map 12 state 11 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F168, map_12_state_11_08E6F168, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_ROLAND)
  LOAD_SPRITE(2, SPRITE_MOKUBA)
  LOAD_SPRITE(3, SPRITE_BIG_FIVE)
  LOAD_SPRITE(4, SPRITE_BIG_FIVE)
  LOAD_SPRITE(5, SPRITE_BIG_FIVE)
  LOAD_SPRITE(6, SPRITE_BIG_FIVE)
  LOAD_SPRITE(7, SPRITE_BIG_FIVE)
  PLAY_MUSIC(MUSIC_KAIBACORP)
  TEXT(
      "M-master Mokuba...",
      "Please, please give us one more chance."
  )
  TALK(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_ANGRY, PORTRAIT_POSITION_AUTO, "After all the horrible things you've done to us?")
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I know we were wrong. But...",
      "Times are tough. No one has any money!",
      "We want to work, but no one's hiring.",
      "Please, we're begging you to rehire us."
  )
  TALK(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Well... I guess I have something for you...")
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "R-really?",
      "Oh, thank you!"
  )
  TALK(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "All right. Quick, get changed.")
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_3 | OBJECT_4 | OBJECT_5 | OBJECT_6 | OBJECT_7)
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Where's Serenity?")
  FADE_SCREEN(4)
  WARP(LOCATION_KAIBA_LAND, 1, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
