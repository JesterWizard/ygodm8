#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_06_state_10: map 6 state 10 */

LOAD_SPRITE(1, SPRITE_LUCKY)
LOAD_SPRITE(2, SPRITE_DUKE)
LOAD_SPRITE(3, SPRITE_SERENITY)
LOAD_SPRITE(4, SPRITE_YUGI_UNUSED)
LOAD_SPRITE(5, SPRITE_YUGI_UNUSED)
LOAD_SPRITE(6, SPRITE_YUGI_UNUSED)
LOAD_SPRITE(7, SPRITE_YUGI_UNUSED)
LOAD_SPRITE(8, SPRITE_YUGI_UNUSED)
LOAD_SPRITE(9, SPRITE_YUGI_UNUSED)
LOAD_SPRITE(10, SPRITE_YUGI_UNUSED)
LOAD_SPRITE(11, SPRITE_YUGI_UNUSED)
LOAD_SPRITE(12, SPRITE_YUGI_UNUSED)
LOAD_SPRITE(13, SPRITE_YUGI)
LOAD_SPRITE(14, SPRITE_JOEY)
TALK(PORTRAIT_DUKE, EXPRESSION_DUKE_TEETH_GRITTED, PORTRAIT_POSITION_AUTO,
    "...And that's what happened.\n\n"
)
PLAY_MUSIC(MUSIC_272)
REACTION(REACTION_ELLIPSIS, OBJECT_0 | SPRITE_YUGI | SPRITE_JOEY)
TALK(PORTRAIT_SERENITY, EXPRESSION_SERENITY_SAD, PORTRAIT_POSITION_AUTO,
    "Big brother... I saw this\n"
    "look on Tristan's face...\n\n"
    "It was as if he was saying\n"
    "that he didn't want anyone\n\n"
    "to follow him.\n\n"
    "I wonder if he's going to be\n"
    "okay...\n\n"
)
TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO,
    "Don't worry about a thing,\n"
    "Serenity.\n\n"
    "Tristan's our friend.\n"
    "There's no way we'll\n\n"
    "abandon him!\n\n"
    "We'll look for him, but I\n"
    "want you to stay here,\n\n"
    "Serenity. Just in case he\n"
    "comes back.\n\n"
)
SET_FLAG(EVENT_FLAG_SEARCHING_FOR_ROBOT_TRISTAN)

EVENT_SCRIPT_REPLACEMENT(0x08E5CD98, map_06_state_10_08E5CD98, 0x08F04040, 0x08F04040)
TALK(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I bet Tristan ran off on\n"
    "purpose!\n\n"
    "That's the only way Serenity\n"
    "would pay attention to him\n\n"
    "instead of me!\n\n"
    "...N-no, he wouldn't do\n"
    "that. He's not that type of\n\n"
    "guy.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CD8C, map_06_state_10_08E5CD8C, 0x08F04040, 0x08F04040)
TALK(PORTRAIT_SERENITY, EXPRESSION_SERENITY_SAD, PORTRAIT_POSITION_AUTO,
    "Where could Tristan have\n"
    "gone?\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
