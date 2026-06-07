#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_31_state_09: map 31 state 9 */

LOAD_SPRITE(1, SPRITE_PARADOX)
PLAY_MUSIC(MUSIC_410)
DELAY(8)
PLAY_MUSIC(MUSIC_271)
REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_13 | OBJECT_14)
DELAY(8)
PLAY_MUSIC(MUSIC_280)
SHOW_OBJECT(SPRITE_PARADOX, 72, 44, 0, 1, 0)
DELAY(64)
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I am Paradox.\n\n"
    "I am the sage of all\n"
    "duelists.\n\n"
    "I have heard many things\n"
    "about you.\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
PLAY_MUSIC(MUSIC_271)
REACTION(REACTION_EXCLAMATION_MARK, SPRITE_PARADOX)
DELAY(16)
PLAY_MUSIC(MUSIC_272)
REACTION(REACTION_ELLIPSIS, SPRITE_PARADOX)
DELAY(16)
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
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
TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO,
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
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Why do you want to know?\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
DELAY(16)
TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "We have to stop the Dark\n"
    "Being at all costs!\n\n"
)
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Reshef the Dark Being...\n\n"
    "If the three Egyptian God\n"
    "Cards regained their\n\n"
    "power...\n\n"
    "It may be possible to thwart\n"
    "Reshef's grand design...\n\n"
)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Yeah, so tell us where he's\n"
    "at...\n\n"
)
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
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
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "That card will not help you\n"
    "at Pegasus's castle.\n\n"
    "The Winged Dragon of Ra has\n"
    "not yet awoken.\n\n"
)
TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "That's right!\n\n"
    "It's in Sphere Mode, right?\n\n"
)
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "You must restore Ra's power.\n\n"
    "There must be someone who\n"
    "knows how to wake it...\n\n"
)
HIDE_PORTRAIT()
HIDE_PORTRAIT()
FADE_MUSIC(2)
DELAY(32)
SET_FLAG(EVENT_FLAG_TALKED_TO_PARADOX_ABOUT_RA)
