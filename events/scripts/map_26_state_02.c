#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_26_state_02: map 26 state 2 */

LOAD_SPRITE(1, SPRITE_MAI)
LOAD_SPRITE(2, SPRITE_TRISTAN)
LOAD_SPRITE(3, SPRITE_DUKE)
PLAY_MUSIC(MUSIC_DOMINO_PIER)
WALK_OBJECT_Y(2, 70)
WALK_OBJECT_Y(2, 40)
WALK_OBJECT_Y(3, 40)
WALK_OBJECT_Y(3, 70)
PORTRAIT(PORTRAIT_MAI, EXPRESSION_MAI_ANGRY, PORTRAIT_LEFT)
TEXT
(
    "C'mon, boys! Work harder,\n"
    "you two!\n\n"
    "At this rate, you'll never\n"
    "become real duelists.\n\n"
    "It'll take you a hundred\n"
    "years to reach my skill\n\n"
    "level!\n\n"
)
PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_TRISTAN_TEETH_GRITTED, PORTRAIT_LEFT)
TEXT
(
    "Wh-why are we working for\n"
    "Mai?\n\n"
)
PORTRAIT(PORTRAIT_DUKE, EXPRESSION_DUKE_TEETH_GRITTED, PORTRAIT_LEFT)
TEXT
(
    "What'd we do to deserve\n"
    "this?\n\n"
)
PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
PLAY_MUSIC(MUSIC_271)
REACTION(REACTION_EXCLAMATION_MARK, OBJECT_1)
PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "Oh, hi Joey!\n\n"
    "Do you want me to train you\n"
    "too?\n\n"
)
PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_TEETH_GRITTED, PORTRAIT_LEFT)
TEXT
(
    "Why would I need training?\n\n"
)
PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "Ahahaha, I'm only joking.\n\n"
    "Minion One and Minion Two,\n"
    "stop slacking off!\n\n"
)
PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_TRISTAN_TEETH_GRITTED, PORTRAIT_LEFT)
TEXT
(
    "M-Minion One?\n\n"
)
PORTRAIT(PORTRAIT_DUKE, EXPRESSION_DUKE_TEETH_GRITTED, PORTRAIT_LEFT)
TEXT
(
    "Two?!\n\n"
)
PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "This sucks...\n\n"
)
PORTRAIT(PORTRAIT_MAI, EXPRESSION_MAI_SWEATDROP, PORTRAIT_LEFT)
TEXT
(
    "Wipe those frowns off your\n"
    "faces.\n\n"
    "If you really want to\n"
    "improve your dueling\n\n"
    "skills, you should hit the\n"
    "road on a training quest.\n\n"
)
PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "A training quest?\n\n"
)
PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_TRISTAN_HAPPY, PORTRAIT_LEFT)
TEXT
(
    "I'm going! I am soooo going!\n\n"
    "Anything beats getting\n"
    "worked like a mule.\n\n"
    "I would rather be anywhere\n"
    "else but here!\n\n"
    "Duke, let's go!\n\n"
)
WALK_OBJECT_Y(2, 70)
WALK_OBJECT_X(2, 52)
WALK_OBJECT_Y(2, 96)
PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "S-sure. Wait for me,\n"
    "Tristan.\n\n"
)
WALK_OBJECT_X(3, 60)
WALK_OBJECT_Y(3, 96)
PORTRAIT(PORTRAIT_MAI, EXPRESSION_MAI_SWEATDROP, PORTRAIT_LEFT)
TEXT
(
    "Those two... I was only\n"
    "kidding. I mean, what's a\n\n"
    "training quest anyway?\n\n"
    "Sigh... Now that my minions\n"
    "are gone, I have to do my\n\n"
    "own work.\n\n"
)
SET_FLAG(EVENT_FLAG_SAW_TRISTAN_AND_DUKE_LEAVING_ON_A_TRAINING_QUEST)

EVENT_SCRIPT_REPLACEMENT(0x08EA3B84, map_26_state_02_08EA3B84, 0x08F04040, 0x08F04040)
PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Tristan and Duke left on a\n"
      "training quest.\n\n"
      "But what are they training\n"
      "for?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
