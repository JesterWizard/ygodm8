#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_24_state_03: map 24 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E981D4, map_24_state_03_08E981D4, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_TAKESHI)
  LOAD_SPRITE(2, SPRITE_ETSUKO)
  LOAD_SPRITE(3, SPRITE_NEO_GHOUL)
  LOAD_SPRITE(4, SPRITE_VIDEO_CARD)
  PLAY_MUSIC(MUSIC_NEO_GHOULS)
  DELAY(16)
  TEXT
  (
      "I'm sorry, I'm sorry.\n\n"
      "Here are my rare cards.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_285)
  SHOW_OBJECT(4, 44, 36, 0, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_3)
  DELAY(16)
  PORTRAIT(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Humph, these cards are\n"
      "garbage.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_285)
  SHOW_OBJECT(4, 44, 96, 0, 0, 0)
  DELAY(8)
  TEXT
  (
      "Oh... Uh, then how about\n"
      "this one?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_285)
  SHOW_OBJECT(4, 44, 36, 0, 0, 0)
  DELAY(48)
  PLAY_MUSIC(MUSIC_285)
  SHOW_OBJECT(4, 44, 96, 0, 0, 0)
  DELAY(8)
  PORTRAIT(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "That better be all of them.\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "That's all I have, I swear.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(32)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  TEXT
  (
      "Takeshi... Are you, like,\n"
      "sure about this?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TEXT
  (
      "Y-yeah, I'm positive.\n\n"
  )
  PORTRAIT(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "What? You have a problem?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TEXT
  (
      "No no no no no no no no no.\n"
      "I don't want any trouble.\n\n"
  )
  PORTRAIT(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Humph, you spineless worm.\n"
      "You're not even worth\n\n"
      "dueling.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(3, 14)
  WALK_OBJECT_Y(3, 42)
  WALK_OBJECT_X(3, 0)
  SHOW_OBJECT(3, 128, 96, 0, 0, 0)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  TEXT
  (
      "Pah! Who's spineless!\n\n"
      "He's the one who has to hang\n"
      "out with a bunch of\n\n"
      "cheaters to win!\n\n"
      "Are they really, you know,\n"
      "like, cheaters?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TEXT
  (
      "Wasn't it obvious?\n\n"
      "I would do anything to\n"
      "protect you from those\n\n"
      "guys.\n\n"
      "Takeshi... You protected me?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  TEXT
  (
      "Well, of course.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_273)
  REACTION(REACTION_LOVE_HEART, OBJECT_2)
  DELAY(16)
  TEXT
  (
      "Like, thank you.\n"
  )
  DELAY(32)
  TEXT
  (
      "Ta"
  )
  DELAY(32)
  TEXT
  (
      "ke"
  )
  DELAY(32)
  TEXT
  (
      "shi...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  DELAY(8)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  SET_FLAG(EVENT_FLAG_SAW_TAKESHI_GIVE_HIS_CARDS_TO_A_GHOUL)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E981E0, map_24_state_03_08E981E0, 0x08E981EC, 0x08E981F8)
  CHECK_FLAG(EVENT_FLAG_SCARED_TAKESHI)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E981EC, map_24_state_03_08E981EC, 0x08F04040, 0x08F04040)
  TEXT
  (
      "N-no, I don't have any more\n"
      "rare cards.\n\n"
      "...Wait, you're not the Neo\n"
      "Ghouls.\n\n"
      "Don't scare me like that!\n\n"
  )
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  SET_FLAG(EVENT_FLAG_SCARED_TAKESHI)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E981F8, map_24_state_03_08E981F8, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Don't talk to me, kid..\n\n"
  )
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98204, map_24_state_03_08E98204, 0x08F04040, 0x08F04040)
  TEXT
  (
      "How am I supposed to duel\n"
      "when they took my cards?\n\n"
      "Duh!\n\n"
  )
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98210, map_24_state_03_08E98210, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Like, what's your problem!\n\n"
      "Why can't you be, like,\n"
      "brave, like my man Takeshi?\n\n"
  )
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
