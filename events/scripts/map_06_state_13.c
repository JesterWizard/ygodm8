#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_06_state_13: map 6 state 13 */

EVENT_SCRIPT_REPLACEMENT(0x08E5CD08, map_06_state_13_08E5CD08, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_TRISTAN)
  LOAD_SPRITE(2, SPRITE_DUKE)
  LOAD_SPRITE(3, SPRITE_SERENITY)
  LOAD_SPRITE(4, SPRITE_LUCKY)
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You did it, {PLAYER}.\n\n"
      "You got rid of the Neo\n"
      "Ghouls... Awesome!\n\n"
      "But... Your battle isn't\n"
      "over yet, is it?\n\n"
      "{PLAYER}, I know you can\n"
      "win!\n\n"
      "Don't worry about the Town\n"
      "of Domino. We'll take care\n\n"
      "of it.\n\n"
      "Go on ahead and duel like a\n"
      "champion!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CD14, map_06_state_13_08E5CD14, 0x08E5CD20, 0x08F0404C)
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Sure! If you think you can\n"
      "learn something from me,\n\n"
      "I'll duel you!\n\n"
  )
  DUEL(92)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CD20, map_06_state_13_08E5CD20, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_GAME_SHOP)
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I hope that was good\n"
      "practice.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CD2C, map_06_state_13_08E5CD2C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "We'll look after things\n"
      "while you're gone,\n\n"
      "{PLAYER}.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CD38, map_06_state_13_08E5CD38, 0x08E5CD44, 0x08F0404C)
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "No problem! I'll duel if you\n"
      "want me to.\n\n"
  )
  DUEL(93)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CD44, map_06_state_13_08E5CD44, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_GAME_SHOP)
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I guess I'm too weak to duel\n"
      "you, {PLAYER}.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CD50, map_06_state_13_08E5CD50, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}, good luck.\n\n"
      "I hope Joey doesn't get in\n"
      "the way...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CD5C, map_06_state_13_08E5CD5C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I wouldn't be much of a\n"
      "challenge, {PLAYER}.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
