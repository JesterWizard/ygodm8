#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_04_state_07: map 4 state 7 */

LOAD_SPRITE(1, SPRITE_REX)
LOAD_SPRITE(2, SPRITE_BONZ)
DELAY(16)
WALK_OBJECT_X(SPRITE_REX, 96)
DELAY(32)
MOVE_OBJECT(SPRITE_REX, DIRECTION_UP, 0, 0)
DELAY(16)
MOVE_OBJECT(SPRITE_REX, DIRECTION_DOWN, 0, 0)
DELAY(16)
MOVE_OBJECT(SPRITE_REX, DIRECTION_RIGHT, 0, 0)
DELAY(16)
MOVE_OBJECT(SPRITE_REX, DIRECTION_LEFT, 0, 0)
DELAY(16)
TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "I'm sure they're supposed to\n"
    "be around here somewhere.\n\n"
    "Huh? They're not here yet?\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_X(SPRITE_BONZ, 24)
TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "My cosmic powers tell me\n"
    "this is the place.\n\n"
    "I hope they come back\n"
    "safely.\n\n"
)
FADE_MUSIC(8)
FADE_SCREEN(8)
WARP(LOCATION_CLOCK_TOWER_SQUARE_NORTH, 7, 0, 0)
