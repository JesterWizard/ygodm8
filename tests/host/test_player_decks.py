#!/usr/bin/env python3

import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from player_deck_persist import (  # noqa: E402
    CARD_NONE,
    PLAYER_DECK_CARD_COUNT,
    deck_has_any_valid_card,
    sanitize_deck_cards,
    simulate_save_slot_read,
    switch_active_deck,
)

NUM_TOTAL_CARDS = 0x0341


def make_deck(first_card: int, count: int = PLAYER_DECK_CARD_COUNT) -> list[int]:
    deck = [CARD_NONE] * PLAYER_DECK_CARD_COUNT
    for i in range(min(count, PLAYER_DECK_CARD_COUNT)):
        deck[i] = first_card + i
    return deck


class PlayerDeckSwitchTests(unittest.TestCase):
    def test_switch_deck1_to_deck2_and_back_preserves_deck1(self):
        deck1 = make_deck(0x0100, 40)
        deck2 = make_deck(0x0200, 24)
        deck3 = [CARD_NONE] * PLAYER_DECK_CARD_COUNT

        menu, b1, b2, b3, active = switch_active_deck(
            deck1, deck1, deck2, deck3, 1, 2, NUM_TOTAL_CARDS
        )
        self.assertEqual(active, 2)
        self.assertEqual(b1, deck1)
        self.assertEqual(menu, deck2[:40])

        menu, b1, b2, b3, active = switch_active_deck(
            menu, b1, b2, b3, active, 1, NUM_TOTAL_CARDS
        )
        self.assertEqual(active, 1)
        self.assertEqual(b1, deck1)
        self.assertEqual(menu, deck1)
        self.assertEqual(b2, deck2)

    def test_round_trip_all_three_decks(self):
        deck1 = make_deck(0x0100, 40)
        deck2 = make_deck(0x0200, 10)
        deck3 = make_deck(0x0300, 15)

        menu, b1, b2, b3, active = deck1[:], deck1[:], deck2[:], deck3[:], 1

        for target in (2, 3, 1, 3, 2, 1):
            expected_backing = {1: deck1, 2: deck2, 3: deck3}[target]
            menu, b1, b2, b3, active = switch_active_deck(
                menu, b1, b2, b3, active, target, NUM_TOTAL_CARDS
            )
            self.assertEqual(active, target)
            self.assertEqual(menu, expected_backing)

        self.assertEqual(b1, deck1)
        self.assertEqual(b2, deck2)
        self.assertEqual(b3, deck3)

    def test_switching_to_same_deck_does_not_reload(self):
        deck1 = make_deck(0x0100, 40)
        deck2 = [CARD_NONE] * PLAYER_DECK_CARD_COUNT
        deck3 = [CARD_NONE] * PLAYER_DECK_CARD_COUNT
        edited = make_deck(0x0150, 40)

        menu, b1, b2, b3, active = switch_active_deck(
            edited, deck1, deck2, deck3, 1, 1, NUM_TOTAL_CARDS
        )

        self.assertEqual(menu, edited)
        self.assertEqual(b1, deck1)

    def test_save_slot_read_reloads_active_backing(self):
        deck1 = make_deck(0x0100, 40)
        deck2 = make_deck(0x0200, 24)
        deck3 = [CARD_NONE] * PLAYER_DECK_CARD_COUNT

        menu, b1, b2, b3, active = simulate_save_slot_read(
            deck1, deck2, deck3, 2, NUM_TOTAL_CARDS
        )

        self.assertEqual(active, 1)
        self.assertEqual(b1, deck1)
        self.assertEqual(menu, deck1)

    def test_sanitize_deck_cards_clears_invalid_ids(self):
        deck = [CARD_NONE] * PLAYER_DECK_CARD_COUNT
        deck[0] = 1
        deck[1] = NUM_TOTAL_CARDS
        deck[2] = NUM_TOTAL_CARDS + 10

        sanitized = sanitize_deck_cards(deck, NUM_TOTAL_CARDS)

        self.assertEqual(sanitized[0], 1)
        self.assertEqual(sanitized[1], CARD_NONE)
        self.assertEqual(sanitized[2], CARD_NONE)

    def test_deck_has_any_valid_card(self):
        self.assertTrue(deck_has_any_valid_card(make_deck(1, 1), NUM_TOTAL_CARDS))
        self.assertFalse(deck_has_any_valid_card([CARD_NONE] * 40, NUM_TOTAL_CARDS))


if __name__ == "__main__":
    unittest.main()
