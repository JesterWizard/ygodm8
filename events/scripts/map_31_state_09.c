#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_31_state_09: map 31 state 9 */

EVENT_SCRIPT_REPLACEMENT(0x08EB43A8, map_31_state_09_08EB43A8, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_PARADOX)
  PLAY_MUSIC(MUSIC_410)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(8)
  PLAY_MUSIC(MUSIC_280)
  SHOW_OBJECT(1, 72, 44, 0, 1, 0)
  DELAY(64)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I am Paradox.\n\n"
      "I am the sage of all\n"
      "duelists.\n\n"
      "I have heard many things\n"
      "about you.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_1)
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_1)
  DELAY(16)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "However, there's something\n"
      "different about you.\n\n"
      "You're not who I\n"
      "expected...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_14, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Enough with the weird\n"
      "introductions!\n\n"
      "Let's cut to the chase.\n"
      "Where's Pegasus?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(13, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, OBJECT_0 | OBJECT_13)
  DELAY(16)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Why do you want to know?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "We have to stop the Dark\n"
      "Being at all costs!\n\n"
  )
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Reshef the Dark Being...\n\n"
      "If the three Egyptian God\n"
      "Cards regained their\n\n"
      "power...\n\n"
      "It may be possible to thwart\n"
      "Reshef's grand design...\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Yeah, so tell us where he's\n"
      "at...\n\n"
  )
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Patience, young one.\n"
      "Patience.\n\n"
      "{PLAYER}, The Winged Dragon\n"
      "of Ra that you hold...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0)
  DELAY(16)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "That card will not help you\n"
      "at Pegasus's castle.\n\n"
      "The Winged Dragon of Ra has\n"
      "not yet awoken.\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "That's right!\n\n"
      "It's in Sphere Mode, right?\n\n"
  )
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You must restore Ra's power.\n\n"
      "There must be someone who\n"
      "knows how to wake it...\n\n"
  )
  HIDE_PORTRAIT()
  HIDE_PORTRAIT()
  COMMAND_7C_ARG(2, 2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_TALKED_TO_PARADOX_ABOUT_RA)
  FALLTHROUGH()
END_EVENT_SCRIPT()
