#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_05_state_03: map 5 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E50F8C, map_05_state_03_08E50F8C, 0x08E50F98, 0x08E50FA4)
  LOAD_SPRITE(1, SPRITE_STRINGER)
  LOAD_SPRITE(2, SPRITE_RED_MOHAWK)
  LOAD_SPRITE(3, SPRITE_MAKO)
  TEXT
  (
      "I'm the greatest! I sent the\n"
      "Neo Ghouls running!\n\n"
      "Witnesses may say that the\n"
      "funky fisherman guy scared\n\n"
      "them off, but that's not\n"
      "true! He came later.\n\n"
      "All he did was watch, that's\n"
      "all. I'm not lying!\n\n"
      "I'll show you the secret\n"
      "techniques I used to beat\n\n"
      "the Neo Ghouls.\n\n"
      "It'll cost you a rare card,\n"
      "though.\n\n"
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50F98, map_05_state_03_08E50F98, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Thank you kindly!\n\n"
      "Go and duel other duelists\n"
      "as much as possible.\n\n"
      "That will make you better,\n"
      "guaranteed.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, OBJECT_0)
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TEXT
  (
      "Heheh! I scored a rare card!\n\n"
      "I have a knack for business!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FA4, map_05_state_03_08E50FA4, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Tightwad...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FB0, map_05_state_03_08E50FB0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "There sure are some really\n"
      "good duelists out there.\n\n"
      "One duelist crushed the Neo\n"
      "Ghouls in a sec.\n\n"
      "He knows what he's doing\n"
      "with his Sea Deck.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FBC, map_05_state_03_08E50FBC, 0x08E50FE0, 0x08E50FC8)
  CHECK_FLAG(EVENT_FLAG_SEARCHING_FOR_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FE0, map_05_state_03_08E50FE0, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Gahaha! I've hauled in a\n"
      "school of Neo Ghouls!\n\n"
      "Leave the dueling to me!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FC8, map_05_state_03_08E50FC8, 0x08E50FD4, 0x08E50FE0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FD4, map_05_state_03_08E50FD4, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You want to know about the\n"
      "Neo Ghouls hiding out in\n\n"
      "the Town of Domino?\n\n"
      "Look, I'm a fisherman.\n\n"
      "I'm not a detective.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FEC, map_05_state_03_08E50FEC, 0x08E50FF8, 0x08F0404C)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Excellent! I was getting\n"
      "bored of the Neo Ghouls!\n\n"
      "Prepare to be swamped!\n\n"
  )
  DUEL(DUELIST_MAKO_062)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FF8, map_05_state_03_08E50FF8, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_DOMINO_CITY_LIBERATED)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You are a worthy adversary!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
