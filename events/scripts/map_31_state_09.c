#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_31_state_09: map 31 state 9 */

EVENT_SCRIPT_REPLACEMENT(0x08EB43A8, map_31_state_09_08EB43A8, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_PARADOX)
  PLAY_MUSIC(MUSIC_410)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(8)
  PLAY_MUSIC(MUSIC_280)
  SHOW_OBJECT(1, 72, 44, 0, 1, 0)
  DELAY(64)
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I am Paradox.",
      "I am the sage of all duelists.",
      "I have heard many things about you."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_1)
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_1)
  DELAY(16)
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "However, there's something different about you.",
      "You're not who I expected..."
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_14, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO,
      "Enough with the weird introductions!",
      "Let's cut to the chase. Where's Pegasus?"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(13, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, OBJECT_0 | OBJECT_13)
  DELAY(16)
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Why do you want to know?")
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "We have to stop the Dark Being at all costs!")
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Reshef the Dark Being...",
      "If the three Egyptian God Cards regained their",
      "power...",
      "It may be possible to thwart Reshef's grand design..."
  )
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Yeah, so tell us where he's at...")
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Patience, young one. Patience.",
      "{PLAYER}, The Winged Dragon of Ra that you hold..."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0)
  DELAY(16)
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "That card will not help you at Pegasus's castle.",
      "The Winged Dragon of Ra has not yet awoken."
  )
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "That's right!",
      "It's in Sphere Mode, right?"
  )
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You must restore Ra's power.",
      "There must be someone who knows how to wake it..."
  )
  HIDE_PORTRAIT()
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_TALKED_TO_PARADOX_ABOUT_RA)
  FALLTHROUGH()
END_EVENT_SCRIPT()
