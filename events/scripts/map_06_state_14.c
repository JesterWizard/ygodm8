#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_06_state_14: map 6 state 14 */

LOAD_SPRITE(1, SPRITE_TRISTAN)
LOAD_SPRITE(2, SPRITE_DUKE)
LOAD_SPRITE(3, SPRITE_SERENITY)
LOAD_SPRITE(4, SPRITE_LUCKY)
LOAD_SPRITE(5, SPRITE_TEA)
LOAD_SPRITE(6, SPRITE_GRANDPA_MUTO)
PLAY_MUSIC(MUSIC_ENDING_THEME)
DELAY(32)
SHOW_OBJECT(SPRITE_TEA, 75, 39, 0, 0, 0)
DELAY(16)
WALK_OBJECT_Y(SPRITE_TEA, 48)
WALK_OBJECT_X(SPRITE_TEA, 64)
TALK(PORTRAIT_TEA, EXPRESSION_TEA_SAD, PORTRAIT_RIGHT,
    "I can't stand waiting\n"
    "anymore!\n\n"
    "I'm going to find and help\n"
    "Yugi, Joey, and {PLAYER}!\n\n"
)
TALK(PORTRAIT_TRISTAN, EXPRESSION_TRISTAN_ANGRY, PORTRAIT_RIGHT,
    "And just how are you going\n"
    "to help them?\n\n"
)
TALK(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "Tristan's right, Tea.\n\n"
)
TALK(PORTRAIT_SERENITY, EXPRESSION_SERENITY_SAD, PORTRAIT_RIGHT,
    "Tea... Please, you have to\n"
    "believe in my brother...\n\n"
    "And have faith in them.\n\n"
)
TALK(PORTRAIT_TEA, EXPRESSION_TEA_SAD, PORTRAIT_RIGHT,
    "I believe... I believe in\n"
    "them, but...\n\n"
    "I can't stand waiting\n"
    "around.\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
SHOW_OBJECT(SPRITE_GRANDPA_MUTO, 75, 39, 0, 0, 0)
DELAY(16)
WALK_OBJECT_Y(SPRITE_GRANDPA_MUTO, 48)
MOVE_OBJECT(SPRITE_GRANDPA_MUTO, DIRECTION_LEFT, 0, 0)
DELAY(16)
MOVE_OBJECT(SPRITE_TEA, DIRECTION_RIGHT, 0, 0)
DELAY(16)
TALK(PORTRAIT_SOLOMON, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Tea... They'll be fine.\n\n"
    "Can't you tell? Can't you\n"
    "feel it?\n\n"
)
PLAY_MUSIC(MUSIC_270)
REACTION(REACTION_QUESTION_MARK, SPRITE_TEA)
FADE_SCREEN(8)
WARP(LOCATION_CLOCK_TOWER_SQUARE_SOUTH, 6, 0, 0)
