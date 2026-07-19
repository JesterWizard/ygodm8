#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_06_state_14: map 6 state 14 */

EVENT_SCRIPT_REPLACEMENT(0x08E5CDE0, map_06_state_14_08E5CDE0, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_TRISTAN)
  LOAD_SPRITE(2, SPRITE_DUKE)
  LOAD_SPRITE(3, SPRITE_SERENITY)
  LOAD_SPRITE(4, SPRITE_LUCKY)
  LOAD_SPRITE(5, SPRITE_TEA)
  LOAD_SPRITE(6, SPRITE_GRANDPA_MUTO)
  PLAY_MUSIC(MUSIC_ENDING_THEME)
  DELAY(32)
  SHOW_OBJECT(5, 75, 39, 0, 0, 0)
  DELAY(16)
  WALK_OBJECT_Y(5, 48)
  WALK_OBJECT_X(5, 64)
  TALK(PORTRAIT_TEA, EXPRESSION_TEA_SAD, PORTRAIT_RIGHT,
      "I can't stand waiting anymore!",
      "I'm going to find and help Yugi, Joey, and {PLAYER}!"
  )
  TALK(PORTRAIT_TRISTAN, EXPRESSION_TRISTAN_ANGRY, PORTRAIT_RIGHT, "And just how are you going to help them?")
  TALK(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "Tristan's right, Tea.")
  TALK(PORTRAIT_SERENITY, EXPRESSION_SERENITY_SAD, PORTRAIT_RIGHT,
      "Tea... Please, you have to believe in my brother...",
      "And have faith in them."
  )
  TALK(PORTRAIT_TEA, EXPRESSION_TEA_SAD, PORTRAIT_RIGHT,
      "I believe... I believe in them, but...",
      "I can't stand waiting around."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  SHOW_OBJECT(6, 75, 39, 0, 0, 0)
  DELAY(16)
  WALK_OBJECT_Y(6, 48)
  MOVE_OBJECT(6, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  MOVE_OBJECT(5, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_SOLOMON,
      "Tea... They'll be fine.",
      "Can't you tell? Can't you feel it?"
  )
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_5)
  FADE_SCREEN(8)
  WARP(LOCATION_CLOCK_TOWER_SQUARE_SOUTH, 6, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
