#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_25_state_01: Domino Pier casino left room */

EVENT_SCRIPT_REPLACEMENT(0x08E99588, map_25_state_01_08E99588, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_SHIP_DEALER)
  LOAD_SPRITE(2, SPRITE_CASINO_PLAYER)
  TEXT
  (
      "Care for a hand of\n"
      "Blackjack?\n\n"
      "Monster levels are your\n"
      "ranks. Elevens are Aces.\n\n"
  )
  SPECIAL(36)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E99594, map_25_state_01_08E99594, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Hit or stand. I stand on\n"
      "all seventeens.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

/* Patron A: offer rules. Yes → on_false (rules); No → on_true (nop). */
EVENT_SCRIPT_REPLACEMENT(0x08E995A0, map_25_state_01_08E995A0, map_25_state_01_patron_rules, 0x08F04040)
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
EVENT_SCRIPT_REPLACEMENT(0x08E995AC, map_25_state_01_08E995AC, map_25_state_01_patron_play, 0x08F04040)
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

EVENT_SCRIPT(map_25_state_01_patron_rules, 0x08F04040, 0x08F04040)
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

EVENT_SCRIPT(map_25_state_01_patron_play, 0x08F04040, 0x08F04040)
  SPECIAL(37)
  FALLTHROUGH()
END_EVENT_SCRIPT()
