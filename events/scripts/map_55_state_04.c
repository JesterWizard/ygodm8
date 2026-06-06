#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_55_state_04: map 55 state 4 */

LOAD_SPRITE(1, SPRITE_PEGASUS)
PORTRAIT(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
TEXT
(
    "The path you are on is\n"
    "neverending!\n\n"
    "I have taken the miserable\n"
    "spirits of the duelists you\n\n"
    "defeated...\n\n"
    "And crystallized them into\n"
    "these dark duelists!\n\n"
    "They are invincible! Enjoy!\n\n"
)
PORTRAIT(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_SOL_CHEVALSKY_HAPPY, PORTRAIT_POSITION_AUTO)
TEXT
(
    "Ahahahahaha!\n\n"
)
SET_FLAG(EVENT_FLAG_ENTERED_PEGASUS_CASTLE)
FADE_SCREEN(8)
WARP(LOCATION_PEGASUS_CASTLE_HALLWAY, 1, 2, 0)
