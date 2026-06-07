#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_12_state_14: map 12 state 14 */

LOAD_SPRITE(1, SPRITE_ROLAND)
PLAY_MUSIC(MUSIC_KAIBACORP)
DELAY(32)
MOVE_OBJECT(SPRITE_ROLAND, DIRECTION_LEFT, 8, 0)
DELAY(16)
TALK(PORTRAIT_ROLAND, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Master Mokuba... Master\n"
    "Seto...\n\n"
)
HIDE_PORTRAIT()
DELAY(32)
TALK(PORTRAIT_ROLAND, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "There's no point standing\n"
    "around.\n\n"
    "There must be something that\n"
    "I can do...\n\n"
    "I know!\n\n"
)
WALK_OBJECT_X(SPRITE_ROLAND, 104)
WALK_OBJECT_Y(SPRITE_ROLAND, 40)
WALK_OBJECT_X(SPRITE_ROLAND, 128)
FADE_SCREEN(8)
WARP(LOCATION_KAIBA_LAND, 3, 0, 0)
