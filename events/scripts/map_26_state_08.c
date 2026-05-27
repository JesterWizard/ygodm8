#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_26_state_08: map 26 state 8 */

EVENT_SCRIPT_REPLACEMENT(0x08EA3DE8, map_26_state_08_08EA3DE8, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_RICH_HUSBAND)
  LOAD_SPRITE(2, SPRITE_RICHE_WIFE)
  TEXT
  (
      "Roulette, poker, slot\n"
      "machines...\n\n"
      "There are many kinds of\n"
      "games I enjoy.\n\n"
      "But the best of all is Duel\n"
      "Monsters.\n\n"
      "The game has become the love\n"
      "of my life!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DF4, map_26_state_08_08EA3DF4, 0x08EA3E00, 0x08EA3E18)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_RICH_HUSBAND)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E00, map_26_state_08_08EA3E00, 0x08EA3E0C, 0x08F0404C)
  TEXT
  (
      "Okay!\n\n"
      "Don't expect any mercy,\n"
      "laddie!\n\n"
  )
  DUEL(DUELIST_ID_098)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E0C, map_26_state_08_08EA3E0C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_DOMINO_PIER)
  TEXT
  (
      "Oh no!\n\n"
      "I was beaten by a mere\n"
      "child!\n\n"
      "But unpredictability is one\n"
      "of the reasons this game is\n\n"
      "so fun!\n\n"
      "I also like fixing my deck\n"
      "after a loss.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_RICH_HUSBAND)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E18, map_26_state_08_08EA3E18, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Sorry, laddie! You'll have\n"
      "to wait.\n\n"
      "I'm making adjustments to my\n"
      "deck.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E24, map_26_state_08_08EA3E24, 0x08F04040, 0x08F04040)
  TEXT
  (
      "My husband is engrossed in\n"
      "dueling.\n\n"
      "It's funny, he wasn't\n"
      "interested at all before.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E30, map_26_state_08_08EA3E30, 0x08EA3E3C, 0x08EA3E54)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_RICH_WIFE2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E3C, map_26_state_08_08EA3E3C, 0x08EA3E48, 0x08F0404C)
  TEXT
  (
      "Why certainly.\n\n"
  )
  DUEL(DUELIST_ID_099)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E48, map_26_state_08_08EA3E48, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_DOMINO_PIER)
  TEXT
  (
      "I must construct my deck\n"
      "wisely.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_RICH_WIFE2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E54, map_26_state_08_08EA3E54, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Another time, dear.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
