#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_25_state_01: Domino Pier casino left room */

/* Dealer A: offer rules. Yes → on_false (rules); No → on_true (nop). */
EVENT_SCRIPT_REPLACEMENT(0x08E99588, map_25_state_01_08E99588, map_25_state_01_dealer_rules, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_SHIP_DEALER)
  LOAD_SPRITE(2, SPRITE_CASINO_PLAYER)
  TEXT(
      "I like dealing Blackjack.",
      "Want me to explain the rules?",
      "{CARD_1}Yes\nNo{CARD_2}"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

/* Dealer R: challenge. Yes → play. */
EVENT_SCRIPT_REPLACEMENT(0x08E99594, map_25_state_01_08E99594, map_25_state_01_dealer_play, EVENT_NOP)
  TEXT(
      "Care for a hand of Blackjack?",
      "{CARD_1}Yes\nNo{CARD_2}"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

/* Patron A: offer rules. Yes → on_false (rules); No → on_true (nop). */
EVENT_SCRIPT_REPLACEMENT(0x08E995A0, map_25_state_01_08E995A0, map_25_state_01_patron_rules, EVENT_NOP)
  TEXT(
      "I like to play Concentration.",
      "Want me to explain the rules?",
      "{CARD_1}Yes\nNo{CARD_2}"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

/* Patron R: not a duelist — challenge to Concentration. Yes → play. */
EVENT_SCRIPT_REPLACEMENT(0x08E995AC, map_25_state_01_08E995AC, map_25_state_01_patron_play, EVENT_NOP)
  TEXT(
      "I'm not a duelist...",
      "But I can challenge you to a game of Concentration!",
      "{CARD_1}Yes\nNo{CARD_2}"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT(map_25_state_01_dealer_rules, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Monster levels are your card ranks.",
      "Elevens count as Aces.",
      "Get close to twenty-one without going over.",
      "Hit to take another card. Stand to hold your total.",
      "I stand on all seventeens. Bust, and you lose.",
      "Bet Domino money or ante a card from your trunk."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT(map_25_state_01_dealer_play, EVENT_NOP, EVENT_NOP)
  SPECIAL(36)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT(map_25_state_01_patron_rules, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Twenty cards lay face down on a board.",
      "Each turn, the current player flips two cards.",
      "If they match, those cards are removed and you score.",
      "We alternate turns, trying to match cards for points.",
      "Whoever gets the most points wins the game.",
      "You can bet Domino money or ante a card from trunk."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT(map_25_state_01_patron_play, EVENT_NOP, EVENT_NOP)
  SPECIAL(37)
  FALLTHROUGH()
END_EVENT_SCRIPT()
