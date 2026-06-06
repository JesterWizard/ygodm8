#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_05_state_06: map 5 state 6 */

LOAD_SPRITE(1, SPRITE_KID_1)
LOAD_SPRITE(2, SPRITE_KID_2)
DELAY(16)
PLAY_MUSIC(MUSIC_293)
OBJECT_EFFECT(OBJECT_1, OBJECT_EFFECT_JUMPING)
TEXT
(
    "Oh no! I lost again.\n\n"
)
PLAY_MUSIC(MUSIC_293)
OBJECT_EFFECT(OBJECT_2, OBJECT_EFFECT_JUMPING)
TEXT
(
    "Hahah, I did it! Try harder\n"
    "next time!\n\n"
)
PLAY_MUSIC(MUSIC_293)
OBJECT_EFFECT(OBJECT_1, OBJECT_EFFECT_JUMPING)
TEXT
(
    "Yeah, I'm not going to lose\n"
    "again!\n\n"
)
FADE_SCREEN(8)
WARP(LOCATION_CARD_SHOP_OUTSIDE, 15, 0, 0)
