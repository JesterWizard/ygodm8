#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_12_state_08: map 12 state 8 */

LOAD_SPRITE(1, SPRITE_SEEKER)
PLAY_MUSIC(MUSIC_407)
TALK(PORTRAIT_SEEKER, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Kukuku... Fresh new prey to\n"
    "hunt...\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_X(SPRITE_SEEKER, 96)
WALK_OBJECT_Y(SPRITE_SEEKER, 68)
WALK_OBJECT_X(SPRITE_SEEKER, 128)
TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "There he is! It's him,\n"
    "{PLAYER}!\n\n"
)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "He must be one of da\n"
    "remaining Neo Ghouls.\n\n"
    "He's who Espa Roba was\n"
    "talking about.\n\n"
    "I can't believe we couldn't\n"
    "find him 'til now!\n\n"
)
TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "Let's go!\n\n"
)
FADE_SCREEN(8)
WARP(LOCATION_KAIBA_LAND, 2, 0, 0)
