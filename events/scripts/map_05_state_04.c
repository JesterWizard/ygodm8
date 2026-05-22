#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_05_state_04: map 5 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08E51004, map_05_state_04_08E51004, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_STRINGER)
  LOAD_SPRITE(2, SPRITE_RED_MOHAWK)
  LOAD_SPRITE(3, SPRITE_MAKO)
  TEXT
  (
      "Let's see... Who might have\n"
      "rare cards...\n\n"
      "Who looks weak enough for me\n"
      "to beat...\n\n"
      "There have to be suckers\n"
      "around somewhere.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E51010, map_05_state_04_08E51010, 0x08E5101C, 0x08E51034)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_STRINGER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5101C, map_05_state_04_08E5101C, 0x08E51028, 0x08F0404C)
  TEXT
  (
      "If you lose, it's going to\n"
      "cost you a rare card.\n\n"
      "Those are my rules, and if\n"
      "you don't like it, tough!\n\n"
  )
  DUEL(90)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E51028, map_05_state_04_08E51028, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT
  (
      "You're not supposed to be\n"
      "strong!\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_STRINGER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E51034, map_05_state_04_08E51034, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Forget it. I'm not dueling\n"
      "you again.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E51040, map_05_state_04_08E51040, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I'll never forget Mako\n"
      "Tsunami.\n\n"
      "He's one of the duelists who\n"
      "saved the Town of Domino.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5104C, map_05_state_04_08E5104C, 0x08E51058, 0x08E51070)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_RED_MOHAWK2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E51058, map_05_state_04_08E51058, 0x08E51064, 0x08F0404C)
  TEXT
  (
      "Yes! I accept your\n"
      "challenge!\n\n"
  )
  DUEL(91)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E51064, map_05_state_04_08E51064, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT
  (
      "I'm not as good as Mako\n"
      "Tsunami yet.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_RED_MOHAWK2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E51070, map_05_state_04_08E51070, 0x08F04040, 0x08F04040)
  TEXT
  (
      "If you pick on me, you're no\n"
      "different than the Neo\n\n"
      "Ghouls.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5107C, map_05_state_04_08E5107C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Sigh... I miss the sea! I'm\n"
      "going back home among the\n\n"
      "waves!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(3, 61)
  WALK_OBJECT_Y(3, 0)
  SET_OBJECT_POSITION(3, 128, 96, 0)
  SET_FLAG(EVENT_FLAG_MAKO_LEFT_CLOCK_TOWER_SQUARE)
  SET_MAP_MUSIC(4)
  FALLTHROUGH()
END_EVENT_SCRIPT()
