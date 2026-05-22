#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_26_state_09: map 26 state 9 */

EVENT_SCRIPT_REPLACEMENT(0x08EA3D88, map_26_state_09_08EA3D88, 0x08EA3D94, 0x08EA3DA0)
  LOAD_SPRITE(1, SPRITE_MAI)
  LOAD_SPRITE(2, SPRITE_RICH_HUSBAND)
  LOAD_SPRITE(3, SPRITE_RICHE_WIFE)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MAI3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D94, map_26_state_09_08EA3D94, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}... You came here\n"
      "for a reason, didn't you?\n\n"
      "Whatever it is, I'm here to\n"
      "help.\n\n"
      "Challenge me whenever you\n"
      "feel ready.\n\n"
      "As duelists, we understand\n"
      "each other the best when we\n\n"
      "duel.\n\n"
      "It sounds weird, but it's\n"
      "true.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DA0, map_26_state_09_08EA3DA0, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "The people in the Town of\n"
      "Domino are happy now that\n\n"
      "the Neo Ghouls are gone.\n\n"
      "But don't you sense\n"
      "something strange?\n\n"
      "I don't know what it is, but\n"
      "it doesn't feel good.\n\n"
      "It feels like the last turn\n"
      "of a duel that I'm about to\n\n"
      "lose.\n\n"
      "It's just awful!\n\n"
      "{PLAYER}, this enemy that\n"
      "you're facing...\n\n"
      "Who is it?\n\n"
      "Who can create so much\n"
      "tension in the air?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DAC, map_26_state_09_08EA3DAC, 0x08EA3DB8, 0x08EA3DD0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MAI3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DB8, map_26_state_09_08EA3DB8, 0x08EA3DC4, 0x08F0404C)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Duelists get to know each\n"
      "other through dueling.\n\n"
      "Once duelists battle, a bond\n"
      "develops that didn't exist\n\n"
      "before.\n\n"
      "{PLAYER}, I accept your\n"
      "duel!\n\n"
  )
  DUEL(97)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DC4, map_26_state_09_08EA3DC4, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}...\n\n"
      "I can tell you're planning\n"
      "to face something huge and\n\n"
      "terrible...\n\n"
      "But you'll be fine.\n\n"
      "There's a bond between us!\n\n"
      "Even when we're far apart,\n"
      "our hearts beat as one.\n\n"
      "This is Harpie Lady. It\n"
      "represents my spirit as a\n\n"
      "duelist.\n\n"
      "I'm not required to give it\n"
      "to you, but I want you to\n\n"
      "have it.\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Received Harpie Lady."
  )
  PLAY_MUSIC(MUSIC_701)
  DELAY(240)
  DELAY(80)
  PLAY_MUSIC(MUSIC_DOMINO_PIER)
  PAGE_BREAK()
  ADD_CARD(62)
  SET_FLAG(EVENT_FLAG_DEFEATED_MAI3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DD0, map_26_state_09_08EA3DD0, 0x08EA3DDC, 0x08F0404C)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}, I don't know what\n"
      "you're facing.\n\n"
      "But I know it won't be easy.\n\n"
      "Remember that every duelist\n"
      "has unlimited potential.\n\n"
      "If you think it'll help,\n"
      "I'll duel you anytime!\n\n"
  )
  DUEL(147)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DDC, map_26_state_09_08EA3DDC, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_DOMINO_PIER)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Did this duel help you?\n\n"
      "Don't lose, {PLAYER}!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
