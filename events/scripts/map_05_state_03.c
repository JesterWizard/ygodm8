#include "event_macros.h"
#include "overworld.h"

/* map_05_state_03: map 5 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E50F8C, map_05_state_03_08E50F8C, 0x08E50F98, 0x08E50FA4)
  LOAD_SPRITE(1, SPRITE_STRINGER)
  LOAD_SPRITE(2, SPRITE_RED_MOHAWK)
  LOAD_SPRITE(3, SPRITE_MAKO)
  TEXT("I'm the greatest! I sent the\nNeo Ghouls running!\n\nWitnesses may say that the\nfunky fisherman guy scared\n\nthem off, but that's not\ntrue! He came later.\n\nAll he did was watch, that's\nall. I'm not lying!\n\nI'll show you the secret\ntechniques I used to beat\n\nthe Neo Ghouls.\n\nIt'll cost you a rare card,\nthough.\n\n{CARD_1}Yes\nNo{CARD_2}\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50F98, map_05_state_03_08E50F98, 0x08F04040, 0x08F04040)
  TEXT("Thank you kindly!\n\nGo and duel other duelists\nas much as possible.\n\nThat will make you better,\nguaranteed.\n\n")
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, 1)
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TEXT("Heheh! I scored a rare card!\n\nI have a knack for business!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FA4, map_05_state_03_08E50FA4, 0x08F04040, 0x08F04040)
  TEXT("Tightwad...\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FB0, map_05_state_03_08E50FB0, 0x08F04040, 0x08F04040)
  TEXT("There sure are some really\ngood duelists out there.\n\nOne duelist crushed the Neo\nGhouls in a sec.\n\nHe knows what he's doing\nwith his Sea Deck.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FBC, map_05_state_03_08E50FBC, 0x08E50FE0, 0x08E50FC8)
  CHECK_FLAG(EVENT_FLAG_SEARCHING_FOR_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FE0, map_05_state_03_08E50FE0, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Gahaha! I've hauled in a\nschool of Neo Ghouls!\n\nLeave the dueling to me!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FC8, map_05_state_03_08E50FC8, 0x08E50FD4, 0x08E50FE0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FD4, map_05_state_03_08E50FD4, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("You want to know about the\nNeo Ghouls hiding out in\n\nthe Town of Domino?\n\nLook, I'm a fisherman.\n\nI'm not a detective.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FEC, map_05_state_03_08E50FEC, 0x08E50FF8, 0x08F0404C)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Excellent! I was getting\nbored of the Neo Ghouls!\n\nPrepare to be swamped!\n\n")
  DUEL(62)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FF8, map_05_state_03_08E50FF8, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_DOMINO_CITY_LIBERATED)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("You are a worthy adversary!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
