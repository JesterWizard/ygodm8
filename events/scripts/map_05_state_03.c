#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_05_state_03: map 5 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E50F8C, map_05_state_03_08E50F8C, 0x08E50F98, 0x08E50FA4)
  LOAD_SPRITE(1, SPRITE_STRINGER)
  LOAD_SPRITE(2, SPRITE_RED_MOHAWK)
  LOAD_SPRITE(3, SPRITE_MAKO)
  TEXT(
      "I'm the greatest! I sent the Neo Ghouls running!",
      "Witnesses may say that the funky fisherman guy scared",
      "them off, but that's not true! He came later.",
      "All he did was watch, that's all. I'm not lying!",
      "I'll show you the secret techniques I used to beat",
      "the Neo Ghouls.",
      "It'll cost you a rare card, though.",
      "{CARD_1}Yes\nNo{CARD_2}"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50F98, map_05_state_03_08E50F98, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Thank you kindly!",
      "Go and duel other duelists as much as possible.",
      "That will make you better, guaranteed."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, OBJECT_0)
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TEXT(
      "Heheh! I scored a rare card!",
      "I have a knack for business!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FA4, map_05_state_03_08E50FA4, EVENT_NOP, EVENT_NOP)
  TEXT("Tightwad...")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FB0, map_05_state_03_08E50FB0, EVENT_NOP, EVENT_NOP)
  TEXT(
      "There sure are some really good duelists out there.",
      "One duelist crushed the Neo Ghouls in a sec.",
      "He knows what he's doing with his Sea Deck."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FBC, map_05_state_03_08E50FBC, 0x08E50FE0, 0x08E50FC8)
  CHECK_FLAG(EVENT_FLAG_SEARCHING_FOR_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FE0, map_05_state_03_08E50FE0, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Gahaha! I've hauled in a school of Neo Ghouls!",
      "Leave the dueling to me!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FC8, map_05_state_03_08E50FC8, 0x08E50FD4, 0x08E50FE0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FD4, map_05_state_03_08E50FD4, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You want to know about the Neo Ghouls hiding out in",
      "the Town of Domino?",
      "Look, I'm a fisherman.",
      "I'm not a detective."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FEC, map_05_state_03_08E50FEC, 0x08E50FF8, 0x08F0404C)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Excellent! I was getting bored of the Neo Ghouls!",
      "Prepare to be swamped!"
  )
  DUEL(DUELIST_MAKO_062)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50FF8, map_05_state_03_08E50FF8, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_DOMINO_CITY_LIBERATED)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "You are a worthy adversary!")
  FALLTHROUGH()
END_EVENT_SCRIPT()
