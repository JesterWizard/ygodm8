#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_31_state_06: map 31 state 6 */

LOAD_SPRITE(1, SPRITE_PARADOX)
PLAY_MUSIC(MUSIC_410)
DELAY(16)
PLAY_MUSIC(MUSIC_280)
SHOW_OBJECT(SPRITE_PARADOX, 72, 44, 0, 1, 0)
DELAY(64)
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "The Winged Dragon of Ra has\n"
    "awakened, I see.\n\n"
)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "We did exactly what you\n"
    "said, pops.\n\n"
    "Now come on, where's Pegasus\n"
    "hiding?\n\n"
)
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Be patient.\n\n"
    "I've been living in the\n"
    "mountains for generations,\n\n"
    "and I've become bored.\n\n"
    "I feel like playing a game.\n\n"
    "It's very simple.\n\n"
    "You have to first catch me,\n"
    "then duel me.\n\n"
    "If you win, I will tell you\n"
    "whatever you wish.\n\n"
    "But I won't be\n"
    "caught so easily.\n\n"
    "Fwohoho.\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_X(SPRITE_PARADOX, 128)
HIDE_PORTRAIT()
FADE_MUSIC(2)
DELAY(32)
PLAY_MUSIC(MUSIC_242)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "What's up with dat guy...\n\n"
)
TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Who knows...\n\n"
    "Let's go catch him!\n\n"
)
SET_FLAG(EVENT_FLAG_SAW_PARADOX_FLEE)

EVENT_SCRIPT_REPLACEMENT(0x08EB43B4, map_31_state_06_08EB43B4, 0x08F04040, 0x08F04040)
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "You must restore Ra's power.\n\n"
    "There must be someone who\n"
    "knows how to wake it...\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
