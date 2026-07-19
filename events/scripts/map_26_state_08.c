#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_26_state_08: map 26 state 8 */

EVENT_SCRIPT_REPLACEMENT(0x08EA3DE8, map_26_state_08_08EA3DE8, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_RICH_HUSBAND)
  LOAD_SPRITE(2, SPRITE_RICHE_WIFE)
  TEXT(
      "Roulette, poker, slot machines...",
      "There are many kinds of games I enjoy.",
      "But the best of all is Duel Monsters.",
      "The game has become the love of my life!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DF4, map_26_state_08_08EA3DF4, 0x08EA3E00, 0x08EA3E18)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_RICH_HUSBAND)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E00, map_26_state_08_08EA3E00, 0x08EA3E0C, 0x08F0404C)
  TEXT(
      "Okay!",
      "Don't expect any mercy, laddie!"
  )
  DUEL(DUELIST_ID_098)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E0C, map_26_state_08_08EA3E0C, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_DOMINO_PIER)
  TEXT(
      "Oh no!",
      "I was beaten by a mere child!",
      "But unpredictability is one of the reasons this game is",
      "so fun!",
      "I also like fixing my deck after a loss."
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_RICH_HUSBAND)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E18, map_26_state_08_08EA3E18, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Sorry, laddie! You'll have to wait.",
      "I'm making adjustments to my deck."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E24, map_26_state_08_08EA3E24, EVENT_NOP, EVENT_NOP)
  TEXT(
      "My husband is engrossed in dueling.",
      "It's funny, he wasn't interested at all before."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E30, map_26_state_08_08EA3E30, 0x08EA3E3C, 0x08EA3E54)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_RICH_WIFE2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E3C, map_26_state_08_08EA3E3C, 0x08EA3E48, 0x08F0404C)
  TEXT("Why certainly.")
  DUEL(DUELIST_ID_099)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E48, map_26_state_08_08EA3E48, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_DOMINO_PIER)
  TEXT("I must construct my deck wisely.")
  SET_FLAG(EVENT_FLAG_DEFEATED_RICH_WIFE2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E54, map_26_state_08_08EA3E54, EVENT_NOP, EVENT_NOP)
  TEXT("Another time, dear.")
  FALLTHROUGH()
END_EVENT_SCRIPT()
