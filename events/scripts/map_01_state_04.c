#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_01_state_04: map 1 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08E427CC, map_01_state_04_08E427CC, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_RED_HAT)
  LOAD_SPRITE(2, SPRITE_STYLISH_HAIR)
  LOAD_SPRITE(3, SPRITE_WEEVIL)
  TEXT
  (
      "You know that duelist with\n"
      "the weird laugh?\n\n"
      "He chased away the Neo\n"
      "Ghouls!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E427D8, map_01_state_04_08E427D8, 0x08F04040, 0x08F04040)
  TEXT
  (
      "That weird little kid with\n"
      "glasses saved us.\n\n"
      "But he's kind of arrogant\n"
      "and annoying, isn't he?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E427E4, map_01_state_04_08E427E4, 0x08E42808, 0x08E427F0)
  CHECK_FLAG(EVENT_FLAG_SEARCHING_FOR_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42808, map_01_state_04_08E42808, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_WEEVIL_HAPPY, PORTRAIT_POSITION_AUTO,
    "Hyohyohyohyo!\n\n"
    "How could anyone lose to the\n"
    "Neo Ghouls?\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E427F0, map_01_state_04_08E427F0, 0x08E427FC, 0x08E42808)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E427FC, map_01_state_04_08E427FC, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_WEEVIL_HAPPY, PORTRAIT_POSITION_AUTO,
    "You want to know where the\n"
    "Neo Ghouls are hiding the\n\n"
    "Town of Domino?\n\n"
    "What makes you think I would\n"
    "know, you foolish flea!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42814, map_01_state_04_08E42814, 0x08E42820, 0x08F0404C)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_WEEVIL_HAPPY, PORTRAIT_POSITION_AUTO,
    "Hyohyohyo! You're wasting my\n"
    "time, you gruesome grub!\n\n"
    "You can't beat me in a duel!\n\n"
)
  DUEL(DUELIST_WEEVIL_056)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42820, map_01_state_04_08E42820, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_DOMINO_CITY_LIBERATED)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Gyooeeeeeh!\n\n"
    "Just buzz off!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
