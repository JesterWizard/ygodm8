#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_12_state_14: map 12 state 14 */

LOAD_SPRITE(1, SPRITE_ROLAND)
PLAY_MUSIC(MUSIC_KAIBACORP)
DELAY(32)
MOVE_OBJECT(1, DIRECTION_LEFT, 8, 0)
DELAY(16)
PORTRAIT(PORTRAIT_ROLAND, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "Master Mokuba... Master\n"
    "Seto...\n\n"
)
HIDE_PORTRAIT()
DELAY(32)
PORTRAIT(PORTRAIT_ROLAND, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "There's no point standing\n"
    "around.\n\n"
    "There must be something that\n"
    "I can do...\n\n"
    "I know!\n\n"
)
WALK_OBJECT_X(1, 104)
WALK_OBJECT_Y(1, 40)
WALK_OBJECT_X(1, 128)
FADE_SCREEN(8)
WARP(LOCATION_KAIBA_LAND, 3, 0, 0)
