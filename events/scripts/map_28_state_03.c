#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_28_state_03: map 28 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08EA69BC, map_28_state_03_08EA69BC, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_BONZ)
  LOAD_SPRITE(2, SPRITE_OLD_MAN)
  LOAD_SPRITE(3, SPRITE_OLD_WOMAN)
  PLAY_MUSIC(MUSIC_ITALY)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_2, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  TEXT(
      "I want the fortuneteller to tell me if me and my",
      "snookums are made for each other!"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_3, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  TEXT("I'll get him to look into my past life.")
  TEXT("Isn't it exciting, sugarmuffin?")
  TEXT("It certainly is, kissylips!")
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
  TEXT(
      "L-look... There he is...",
      "I... I know.",
      "Okay! Let's have him tell our fortunes!",
      "Urgh!"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(3, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  TEXT(
      "Wh-what's the matter, lovebucket?",
      "My back... Ow, ow, ow..."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 56)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "Are you okay?",
      "The elderly should take it easy."
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_2 | OBJECT_3)
  DELAY(8)
  TEXT(
      "I had him do a reading about my health...",
      "Oh... What a waste..."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_1)
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "Speaking of who... What happened to him?")
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 16, 0)
  DELAY(8)
  WALK_OBJECT_Y(3, 54)
  MOVE_OBJECT(3, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  TEXT("Wh-where are you going?")
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "To see my friend.")
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 0)
  SHOW_OBJECT(1, 128, 96, 0, 0, 0)
  FADE_MUSIC(16)
  FADE_SCREEN(16)
  WARP(LOCATION_CHINA_GREAT_WALL_ENTRANCE, 8, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
