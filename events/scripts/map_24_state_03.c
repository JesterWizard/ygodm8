#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_24_state_03: map 24 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E981D4, map_24_state_03_08E981D4, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_TAKESHI)
  LOAD_SPRITE(2, SPRITE_ETSUKO)
  LOAD_SPRITE(3, SPRITE_NEO_GHOUL)
  LOAD_SPRITE(4, SPRITE_VIDEO_CARD)
  PLAY_MUSIC(MUSIC_NEO_GHOULS)
  DELAY(16)
  TEXT(
      "I'm sorry, I'm sorry.",
      "Here are my rare cards."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_285)
  SHOW_OBJECT(4, 44, 36, 0, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_3)
  DELAY(16)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Humph, these cards are garbage.")
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_285)
  SHOW_OBJECT(4, 44, 96, 0, 0, 0)
  DELAY(8)
  TEXT("Oh... Uh, then how about this one?")
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_285)
  SHOW_OBJECT(4, 44, 36, 0, 0, 0)
  DELAY(48)
  PLAY_MUSIC(MUSIC_285)
  SHOW_OBJECT(4, 44, 96, 0, 0, 0)
  DELAY(8)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "That better be all of them.")
  TALK(PORTRAIT_NONE, "That's all I have, I swear.")
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(32)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  TEXT("Takeshi... Are you, like, sure about this?")
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TEXT("Y-yeah, I'm positive.")
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "What? You have a problem?")
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TEXT("No no no no no no no no no. I don't want any trouble.")
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Humph, you spineless worm. You're not even worth",
      "dueling."
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
  TEXT(
      "Pah! Who's spineless!",
      "He's the one who has to hang out with a bunch of",
      "cheaters to win!",
      "Are they really, you know, like, cheaters?"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TEXT(
      "Wasn't it obvious?",
      "I would do anything to protect you from those",
      "guys.",
      "Takeshi... You protected me?"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  TEXT("Well, of course.")
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_273)
  REACTION(REACTION_LOVE_HEART, OBJECT_2)
  DELAY(16)
  TEXT("Like, thank you.")
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
  TEXT("shi...")
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

EVENT_SCRIPT_REPLACEMENT(0x08E981EC, map_24_state_03_08E981EC, EVENT_NOP, EVENT_NOP)
  TEXT(
      "N-no, I don't have any more rare cards.",
      "...Wait, you're not the Neo Ghouls.",
      "Don't scare me like that!"
  )
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  SET_FLAG(EVENT_FLAG_SCARED_TAKESHI)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E981F8, map_24_state_03_08E981F8, EVENT_NOP, EVENT_NOP)
  TEXT("Don't talk to me, kid..")
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98204, map_24_state_03_08E98204, EVENT_NOP, EVENT_NOP)
  TEXT(
      "How am I supposed to duel when they took my cards?",
      "Duh!"
  )
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98210, map_24_state_03_08E98210, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Like, what's your problem!",
      "Why can't you be, like, brave, like my man Takeshi?"
  )
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
