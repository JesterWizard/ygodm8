#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_36_state_03: map 36 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08EC9CB4, map_36_state_03_08EC9CB4, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_REX)
  LOAD_SPRITE(2, SPRITE_SERIOUS_ARCHEOLOGIST)
  LOAD_SPRITE(3, SPRITE_CHIEF_ARCHEOLOGIST)
  LOAD_SPRITE(4, SPRITE_FRIVOULOUS_ARCHEOLOGIST)
  LOAD_SPRITE(5, SPRITE_GIRL_ARCHEOLOGIST)
  LOAD_SPRITE(6, SPRITE_THOUGHTFUL_ARCHEOLOGIST)
  PLAY_MUSIC(MUSIC_382)
  DELAY(8)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_2, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  TEXT
  (
      "Whoa, this is a huge\n"
      "discovery, eh.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_3, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  TEXT
  (
      "Yeah, I agree with you\n"
      "there.\n\n"
  )
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "It is awesome.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_4, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  TEXT
  (
      "M-maybe we're the first in\n"
      "the world to find this?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_1 | OBJECT_2 | OBJECT_3 | OBJECT_4 | OBJECT_5 | OBJECT_6)
  DELAY(8)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TEXT
  (
      "That's a distinct\n"
      "possibility, eh.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
  DELAY(6)
  MOVE_OBJECT(4, DIRECTION_UP, 0, 0)
  DELAY(6)
  MOVE_OBJECT(4, DIRECTION_LEFT, 0, 0)
  DELAY(6)
  MOVE_OBJECT(4, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TEXT
  (
      "This is going to make us\n"
      "famous!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_1)
  DELAY(16)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You guys took prehistoric\n"
      "pride in your work...\n\n"
      "That's why you found the\n"
      "fossil in such an enormous\n\n"
      "mountain.\n\n"
      "If I think of my deck as a\n"
      "mountain, I wonder if I can\n\n"
      "find my fossil...\n\n"
      "Can I draw the card I need?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(5, DIRECTION_LEFT, 0, 0)
  DELAY(32)
  WALK_OBJECT_Y(5, 54)
  WALK_OBJECT_X(5, 65)
  DELAY(16)
  TEXT
  (
      "You're overthinking it.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(8)
  TEXT
  (
      "We're among friends.\n\n"
      "We made our discovery\n"
      "because we helped each\n\n"
      "other.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  WALK_OBJECT_Y(6, 62)
  WALK_OBJECT_X(6, 56)
  MOVE_OBJECT(6, DIRECTION_UP, 0, 0)
  DELAY(16)
  TEXT
  (
      "He's right. No one can do\n"
      "this alone.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Friends...\n\n"
      "Yeah, maybe that's what life\n"
      "is all about.\n\n"
      "Thanks!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 0)
  SHOW_OBJECT(1, 128, 96, 0, 0, 0)
  FADE_MUSIC(16)
  FADE_SCREEN(16)
  WARP(LOCATION_GALAPAGOS_BEACH, 6, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
