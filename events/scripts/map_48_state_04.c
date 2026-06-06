#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_48_state_04: map 48 state 4 */

LOAD_SPRITE(1, SPRITE_YUGI)
LOAD_SPRITE(2, SPRITE_PARA_FLIPPING)
LOAD_SPRITE(3, SPRITE_DOX_FLIPPING)
PLAY_MUSIC(MUSIC_DUNGEON)
PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
TEXT
(
    "I also have to get the\n"
    "spirit of the Puzzle back.\n\n"
    "That's why I have to keep up\n"
    "with your skills, {PLAYER}.\n\n"
)
