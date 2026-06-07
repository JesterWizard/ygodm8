#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_06_state_09: map 6 state 9 */

EVENT_SCRIPT_REPLACEMENT(0x08E5CD74, map_06_state_09_08E5CD74, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_LUCKY)
  LOAD_SPRITE(2, SPRITE_DUKE)
  LOAD_SPRITE(3, SPRITE_SERENITY)
  LOAD_SPRITE(4, SPRITE_MONKEY_ROBOT)
  PLAY_MUSIC(MUSIC_MONKEY_ROBOTS)
  DELAY(64)
  SET_OBJECT_POSITION(4, 74, 40, 0)
  DELAY(48)
  WALK_OBJECT_Y(4, 48)
  DELAY(16)
  PLAY_MUSIC(MUSIC_324)
  PORTRAIT(PORTRAIT_ROBOT_MOkNEY, 2, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Ukkiii!\n\n"
  )
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_SERENITY_SURPRISED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Oh! This monkey...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(4, 52)
  DELAY(16)
  PLAY_MUSIC(MUSIC_327)
  PORTRAIT(PORTRAIT_ROBOT_MOkNEY, 0, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Uki, uki. uki.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_273)
  REACTION(REACTION_LOVE_HEART, OBJECT_4)
  WALK_OBJECT_X(1, 96)
  DELAY(16)
  PLAY_MUSIC(MUSIC_203)
  TEXT
  (
      "Arf arf arf!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
  WALK_OBJECT_X(1, 76)
  DELAY(16)
  WALK_OBJECT_X(4, 68)
  DELAY(16)
  PLAY_MUSIC(MUSIC_203)
  TEXT
  (
      "Arf.\n\n"
  )
  PLAY_MUSIC(MUSIC_323)
  PORTRAIT(PORTRAIT_ROBOT_MOkNEY, 0, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Uki!\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  PLAY_MUSIC(MUSIC_203)
  TEXT
  (
      "Arf arf!\n\n"
  )
  PLAY_MUSIC(MUSIC_326)
  PORTRAIT(PORTRAIT_ROBOT_MOkNEY, 0, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Uki uki.\n\n"
  )
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I read that monkeys and dogs\n"
      "don't get along...\n\n"
      "But this monkey and Lucky\n"
      "seem like best friends.\n\n"
  )
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "It can't be... This monkey\n"
      "robot...\n\n"
      "Could it be Tristan?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_3)
  DELAY(8)
  MOVE_OBJECT(3, DIRECTION_UP, 0, 0)
  DELAY(8)
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_SERENITY_SURPRISED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Really?!\n\n"
      "Tristan turned into a robot?\n\n"
  )
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Lucky is Tristan's dog, and\n"
      "it's getting along great\n\n"
      "with this robot.\n\n"
      "That's all the proof I need.\n\n"
  )
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I... I guess so.\n\n"
  )
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "And...\n\n"
  )
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "And?\n\n"
  )
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "This may be another\n"
      "repercussion due to\n\n"
      "Reshef's resurrection.\n\n"
  )
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_SERENITY_SURPRISED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "H-how...\n\n"
  )
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Who other reason can you\n"
      "think of?\n\n"
      "I mean, if this was the\n"
      "virtual world, I wouldn't\n\n"
      "be surprised if Tristan\n"
      "turned into a monkey.\n\n"
      "But a guy can't turn into a\n"
      "robot in real life.\n\n"
  )
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I... I guess so.\n\n"
  )
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_DUKE_TEETH_GRITTED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "But if this is true...\n"
      "Tristan might never regain\n\n"
      "his human form...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_4)
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_325)
  PORTRAIT(PORTRAIT_ROBOT_MOkNEY, 5, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Ukiiiiiiii!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(3, DIRECTION_RIGHT, 0, 0)
  DELAY(8)
  WALK_OBJECT_X(4, 144)
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_SERENITY_SURPRISED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Tristan!\n\n"
  )
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Tristan!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(64)
  FADE_SCREEN(4)
  CLEAR_FLAG(243)
  WARP(LOCATION_CARD_SHOP_OUTSIDE, 10, 4, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
