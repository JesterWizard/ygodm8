#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_50_state_01: map 50 state 1 */

LOAD_SPRITE(1, SPRITE_PARADOX)
PLAY_MUSIC(MUSIC_410)
DELAY(16)
WALK_OBJECT_Y(0, 72)
DELAY(4)
PLAY_MUSIC(MUSIC_271)
REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
DELAY(8)
PLAY_MUSIC(MUSIC_280)
SHOW_OBJECT(SPRITE_PARADOX, 60, 52, 0, 1, 0)
DELAY(64)
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Excellent. You've done well\n"
    "to get this far.\n\n"
    "However, in order to\n"
    "proceed, you must conquer\n\n"
    "this labyrinth.\n\n"
    "It is full of paths that\n"
    "neither begin nor end.\n\n"
    "You need a light to navigate\n"
    "its neverending\n\n"
    "passageways.\n\n"
    "But it is no ordinary light\n"
    "that you need.\n\n"
    "You must have the light of\n"
    "the spirits.\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
PLAY_MUSIC(MUSIC_272)
REACTION(REACTION_ELLIPSIS, OBJECT_0)
DELAY(16)
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Yes... You must light your\n"
    "way with spirit cards.\n\n"
    "The cards that embody the\n"
    "spirits of your fellow\n\n"
    "duelists.\n\n"
    "Hold them aloft at forks in\n"
    "the road and let them light\n\n"
    "your way.\n\n"
    "However, you must never ask\n"
    "for spirit cards.\n\n"
    "You must obtain them fairly.\n\n"
    "You must win them in duels.\n"
    "There is no other way.\n\n"
)
SET_FLAG(EVENT_FLAG_PARADOX_SAID_TO_GET_SPIRIT_CARDS)

EVENT_SCRIPT_REPLACEMENT(0x08EE04C4, map_50_state_01_08EE04C4, 0x08EE050C, 0x08EE04D0)
CHECK_FLAG(EVENT_FLAG_DEFEATED_BONZ3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE050C, map_50_state_01_08EE050C, 0x08F04040, 0x08F04040)
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Go seek out your dueling\n"
    "compatriots, and obtain a\n\n"
    "spirit card from each of\n"
    "them.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE04D0, map_50_state_01_08EE04D0, 0x08EE050C, 0x08EE04DC)
CHECK_FLAG(EVENT_FLAG_DEFEATED_REX3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE04DC, map_50_state_01_08EE04DC, 0x08EE050C, 0x08EE04E8)
CHECK_FLAG(EVENT_FLAG_DEFEATED_WEEVIL3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE04E8, map_50_state_01_08EE04E8, 0x08EE050C, 0x08EE04F4)
CHECK_FLAG(EVENT_FLAG_DEFEATED_MAKO3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE04F4, map_50_state_01_08EE04F4, 0x08EE050C, 0x08EE0500)
CHECK_FLAG(EVENT_FLAG_DEFEATED_ESPA_ROBA2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE0500, map_50_state_01_08EE0500, 0x08EE050C, 0x08EE0518)
CHECK_FLAG(EVENT_FLAG_DEFEATED_MAI3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE0518, map_50_state_01_08EE0518, 0x08F04040, 0x08F04040)
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "You have gathered the\n"
    "required spirit cards.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE0524, map_50_state_01_08EE0524, 0x08F04040, 0x08F04040)
TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Duelists do not communicate\n"
    "with words.\n\n"
    "Duels unite your spirits.\n\n"
    "With your hearts as one,\n"
    "your wishes will come true.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
