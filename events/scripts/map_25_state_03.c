#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_25_state_03: map 25 state 3
 * Dealer A/R share one script address — challenge Yes/No only. */

EVENT_SCRIPT_REPLACEMENT(0x08E99600, map_25_state_03_08E99600, map_25_state_03_dealer_play, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_SHIP_DEALER)
  LOAD_SPRITE(2, SPRITE_CASINO_PLAYER)
  TEXT(
      "I don't duel, but I deal. Care for Blackjack?",
      "{CARD_1}Yes\nNo{CARD_2}"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

/* Patron A: offer rules. Yes → on_false (rules); No → on_true (nop). */
EVENT_SCRIPT_REPLACEMENT(0x08E9960C, map_25_state_03_08E9960C, map_25_state_03_patron_rules, EVENT_NOP)
  TEXT(
      "I like to play Concentration.",
      "Want me to explain the rules?",
      "{CARD_1}Yes\nNo{CARD_2}"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

/* Patron R: not a duelist — challenge to Concentration. Yes → play. */
EVENT_SCRIPT_REPLACEMENT(0x08E99618, map_25_state_03_08E99618, map_25_state_03_patron_play, EVENT_NOP)
  TEXT(
      "I'm not a duelist...",
      "But I can challenge you to a game of Concentration!",
      "{CARD_1}Yes\nNo{CARD_2}"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT(map_25_state_03_dealer_play, EVENT_NOP, EVENT_NOP)
  SPECIAL(36)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT(map_25_state_03_patron_rules, EVENT_NOP, EVENT_NOP)
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

EVENT_SCRIPT(map_25_state_03_patron_play, EVENT_NOP, EVENT_NOP)
  SPECIAL(37)
  FALLTHROUGH()
END_EVENT_SCRIPT()
