#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_28_state_03: map 28 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08EA69BC, map_28_state_03_08EA69BC, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_BONZ)
  LOAD_SPRITE(2, SPRITE_OLD_MAN)
  LOAD_SPRITE(3, SPRITE_OLD_WOMAN)
  PLAY_MUSIC(MUSIC_ITALY)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_2, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  TEXT
  (
      "I want the fortuneteller to\n"
      "tell me if me and my\n\n"
      "snookums are made for each\n"
      "other!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_3, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  TEXT
  (
      "I'll get him to look into my\n"
      "past life.\n\n"
  )
  TEXT
  (
      "Isn't it exciting,\n"
      "sugarmuffin?\n\n"
  )
  TEXT
  (
      "It certainly is, kissylips!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 104)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_2 | OBJECT_3)
  DELAY(8)
  MOVE_OBJECT(3, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_1)
  DELAY(16)
  TEXT
  (
      "L-look... There he is...\n\n"
      "I... I know.\n\n"
      "Okay! Let's have him tell\n"
      "our fortunes!\n\n"
      "Urgh!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(3, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  TEXT
  (
      "Wh-what's the matter,\n"
      "lovebucket?\n\n"
      "My back... Ow, ow, ow...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 56)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Are you okay?\n\n"
      "The elderly should take it\n"
      "easy.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_2 | OBJECT_3)
  DELAY(8)
  TEXT
  (
      "I had him do a reading about\n"
      "my health...\n\n"
      "Oh... What a waste...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_1)
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Speaking of who... What\n"
      "happened to him?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 16, 0)
  DELAY(8)
  WALK_OBJECT_Y(3, 54)
  MOVE_OBJECT(3, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  TEXT
  (
      "Wh-where are you going?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "To see my friend.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 0)
  SHOW_OBJECT(1, 128, 96, 0, 0, 0)
  COMMAND_7C_ARG(2, 16)
  FADE_SCREEN(16)
  WARP(31, 8, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
