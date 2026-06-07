#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_31_state_03: map 31 state 3 */

LOAD_SPRITE(1, SPRITE_PARA)
LOAD_SPRITE(2, SPRITE_DOX_FLIPPING)
LOAD_SPRITE(3, SPRITE_YUGI)
LOAD_SPRITE(4, SPRITE_JOEY)
LOAD_SPRITE(5, SPRITE_SETO)
LOAD_SPRITE(6, SPRITE_MOKUBA)
SET_FLAG(EVENT_FLAG_JOEY_FOUND_PARA_AND_DOX_SUSPICIOUS)
WALK_OBJECT_X(14, 104)
MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
DELAY(16)
TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP, PORTRAIT_LEFT,
    "There's somethin' fishy\n"
    "about those guys. Really\n\n"
    "fishy.\n\n"
    "{PLAYER}, you think so too,\n"
    "right?\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
DELAY(16)
PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Let's check 'em out again.\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)

EVENT_SCRIPT_REPLACEMENT(0x08EB42C4, map_31_state_03_08EB42C4, 0x08F04040, 0x08F04040)
TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP, PORTRAIT_LEFT,
    "I'm tellin' ya, there's\n"
    "somethin' weird about those\n\n"
    "guys!\n\n"
    "Every bone in my body tells\n"
    "me dat, and my instinct is\n\n"
    "never wrong!\n\n"
    "Let's check 'em out again.\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
