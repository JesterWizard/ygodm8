#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_25_state_02: map 25 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E995B8, map_25_state_02_08E995B8, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_SHIP_DEALER)
  LOAD_SPRITE(2, SPRITE_CASINO_PLAYER)
  TEXT
  (
      "Blackjack keeps me calm.\n"
      "Want to play?\n\n"
  )
  SPECIAL(36)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E995C4, map_25_state_02_08E995C4, 0x08F04040, 0x08F04040)
  TEXT
  (
      "No, no, please! I am not a\n"
      "duelist!\n\n"
      "There are duelists on the\n"
      "next floor!\n\n"
      "...Oh? You're not the Neo\n"
      "Ghouls?\n\n"
  )
  SET_FLAG(EVENT_FLAG_SCARED_SHIP_DEALER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E995D0, map_25_state_02_08E995D0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "If only I were a duelist...\n\n"
      "Those Neo Ghouls wouldn't\n"
      "stand a chance!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E995DC, map_25_state_02_08E995DC, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Elevens count as Aces.\n"
      "Don't bust.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

/* Patron A: offer rules. Yes → on_false (rules); No → on_true (nop). */
EVENT_SCRIPT_REPLACEMENT(0x08E995E8, map_25_state_02_08E995E8, map_25_state_02_patron_rules, 0x08F04040)
  TEXT
  (
      "I like to play\n"
      "Concentration.\n\n"
      "Want me to explain the\n"
      "rules?\n\n"
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

/* Patron R: not a duelist — challenge to Concentration. Yes → play. */
EVENT_SCRIPT_REPLACEMENT(0x08E995F4, map_25_state_02_08E995F4, map_25_state_02_patron_play, 0x08F04040)
  TEXT
  (
      "I'm not a duelist...\n\n"
      "But I can challenge you to\n"
      "a game of Concentration!\n\n"
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT(map_25_state_02_patron_rules, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Twenty cards lay face down\n"
      "on a board.\n\n"
      "Each turn, the current\n"
      "player flips two cards.\n\n"
      "If they match, those cards\n"
      "are removed and you score.\n\n"
      "We alternate turns, trying\n"
      "to match cards for points.\n\n"
      "Whoever gets the most\n"
      "points wins the game.\n\n"
      "You can bet Domino money\n"
      "or ante a card from trunk.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT(map_25_state_02_patron_play, 0x08F04040, 0x08F04040)
  SPECIAL(37)
  FALLTHROUGH()
END_EVENT_SCRIPT()
