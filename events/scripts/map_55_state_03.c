#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_55_state_03: map 55 state 3 */

LOAD_SPRITE(1, SPRITE_PEGASUS)
LOAD_SPRITE(2, SPRITE_CHEVALIER)
LOAD_SPRITE(3, SPRITE_CHEVALIER)
LOAD_SPRITE(4, SPRITE_CHEVALIER)
LOAD_SPRITE(5, SPRITE_CHEVALIER)
PORTRAIT(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
TEXT
(
    "Fufufu... You've finally\n"
    "arrived.\n\n"
    "Duelists of pure hearts and\n"
    "spirits, I was hoping you\n\n"
    "would come.\n\n"
    "Why? Because your defeats\n"
    "will make the best\n\n"
    "offerings for the reborn\n"
    "Reshef!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
DELAY(16)
PORTRAIT(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
TEXT
(
    "Now! Go, my disciples!\n\n"
    "Go forth and defeat them!\n\n"
)
HIDE_PORTRAIT()
DELAY(8)
PLAY_MUSIC(MUSIC_260)
OBJECT_EFFECT(OBJECT_2, OBJECT_EFFECT_JUMPING)
PORTRAIT(PORTRAIT_CHEVALIER, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
TEXT
(
    "Gawry nida!\n\n"
)
HIDE_PORTRAIT()
DELAY(8)
PLAY_MUSIC(MUSIC_260)
OBJECT_EFFECT(OBJECT_3, OBJECT_EFFECT_JUMPING)
PORTRAIT(PORTRAIT_CHEVALIER, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "Gawry nida!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_Y(5, 96)
WALK_OBJECT_Y(4, 96)
WALK_OBJECT_Y(3, 96)
WALK_OBJECT_Y(2, 96)
PORTRAIT(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
TEXT
(
    "Reshef the Dark Being\n"
    "created my disciples.\n\n"
    "These duelists have neither\n"
    "emotion nor mercy.\n\n"
    "Crush them, my minions!\n\n"
)
PORTRAIT(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_SOL_CHEVALSKY_HAPPY, PORTRAIT_POSITION_AUTO)
TEXT
(
    "Ahahahahaha!\n\n"
)
FADE_SCREEN(8)
WARP(LOCATION_PEGASUS_ISLAND_DUNGEON_ENTRANCE, 3, 4, 0)
