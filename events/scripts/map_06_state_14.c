#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_06_state_14: map 6 state 14 */

EVENT_SCRIPT_REPLACEMENT(0x08E5CDE0, map_06_state_14_08E5CDE0, 0x08F04040, 0x08F04040)
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
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SAD, PORTRAIT_RIGHT)
  TEXT
  (
      "I can't stand waiting\n"
      "anymore!\n\n"
      "I'm going to find and help\n"
      "Yugi, Joey, and {PLAYER}!\n\n"
  )
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_TRISTAN_ANGRY, PORTRAIT_RIGHT)
  TEXT
  (
      "And just how are you going\n"
      "to help them?\n\n"
  )
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Tristan's right, Tea.\n\n"
  )
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_SERENITY_SAD, PORTRAIT_RIGHT)
  TEXT
  (
      "Tea... Please, you have to\n"
      "believe in my brother...\n\n"
      "And have faith in them.\n\n"
  )
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SAD, PORTRAIT_RIGHT)
  TEXT
  (
      "I believe... I believe in\n"
      "them, but...\n\n"
      "I can't stand waiting\n"
      "around.\n\n"
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
  PORTRAIT(PORTRAIT_SOLOMON, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Tea... They'll be fine.\n\n"
      "Can't you tell? Can't you\n"
      "feel it?\n\n"
  )
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_5)
  FADE_SCREEN(8)
  WARP(LOCATION_CLOCK_TOWER_SQUARE_SOUTH, 6, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
