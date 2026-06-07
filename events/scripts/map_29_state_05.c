#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_29_state_05: map 29 state 5 */

LOAD_SPRITE(1, SPRITE_BONZ)
LOAD_SPRITE(2, SPRITE_NEO_GHOUL)
PLAY_MUSIC(MUSIC_NEO_GHOULS)
TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "You're defying Master\n"
    "Keith's orders?\n\n"
    "After he was willing to let\n"
    "you join him, just like old\n\n"
    "times!\n\n"
)
TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "He never treated me with\n"
    "respect!\n\n"
    "I don't trust him!\n\n"
)
TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "You fool! Pledge your\n"
    "allegiance to Bandit Keith!\n\n"
    "If you do, he's willing to\n"
    "let you use all the rare\n\n"
    "cards you want.\n\n"
)
TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "I'm not afraid of him\n"
    "anymore!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_X(0, 56)
WALK_OBJECT_X(13, 46)
WALK_OBJECT_X(14, 46)
DELAY(16)
MOVE_OBJECT(SPRITE_NEO_GHOUL, DIRECTION_LEFT, 0, 0)
DELAY(8)
PLAY_MUSIC(MUSIC_271)
REACTION(REACTION_EXCLAMATION_MARK, SPRITE_NEO_GHOUL)
DELAY(8)
TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "Tsk, the cavalry arrives!\n\n"
    "I'll take care of them\n"
    "first!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_X(SPRITE_NEO_GHOUL, 66)
DELAY(16)
DUEL(DUELIST_NEO_GHOUL_065)
PLAY_MUSIC(MUSIC_241)
TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "Grah! You'll regret this!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_Y(SPRITE_NEO_GHOUL, 57)
WALK_OBJECT_X(SPRITE_NEO_GHOUL, 248)
WALK_OBJECT_Y(SPRITE_BONZ, 54)
MOVE_OBJECT(SPRITE_BONZ, DIRECTION_LEFT, 8, 0)
DELAY(16)
TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "Th-thanks for saving me!\n\n"
    "Honestly, I was a little\n"
    "scared.\n\n"
    "But you guys... Why are you\n"
    "here?\n\n"
)
PLAY_MUSIC(MUSIC_332)
FADE_SCREEN(4)
PLAY_MUSIC(SOUND_NONE)
PLAY_MUSIC(MUSIC_702)
TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "I didn't know that was going\n"
    "on in town!\n\n"
    "The Neo Ghouls don't scare\n"
    "me anymore.\n\n"
    "I'm a much better duelist!\n"
    "I'll help you, too.\n\n"
    "I'll go to the Town of\n"
    "Domino! The Neo Ghouls\n\n"
    "don't stand a ghost of a\n"
    "chance!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_Y(SPRITE_BONZ, 51)
WALK_OBJECT_X(SPRITE_BONZ, 248)
DELAY(16)
SET_FLAG(EVENT_FLAG_DEFEATED_BONZ_GHOUL)
CONDITION_CHECK(0)
MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Let's go find another ally!\n\n"
)
HIDE_PORTRAIT()
FADE_MUSIC(2)
DELAY(32)

EVENT_SCRIPT_REPLACEMENT(0x08EAC900, map_29_state_05_08EAC900, 0x08F04040, 0x08F04040)
MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Okay! Let's also get back to\n"
    "the Town of Domino!\n\n"
)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_FOUND_ALL_ALLIES)
  FALLTHROUGH()
END_EVENT_SCRIPT()
