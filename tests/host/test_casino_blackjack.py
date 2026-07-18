"""Soft-total / Ace rules for Domino boat Blackjack."""

import unittest


def blackjack_hand_total(levels):
    total = 0
    aces = 0
    for lv in levels:
        if lv == 11:
            aces += 1
            total += 11
        elif 1 <= lv <= 10:
            total += lv
    while total > 21 and aces > 0:
        total -= 10
        aces -= 1
    return total


class TestCasinoBlackjack(unittest.TestCase):
    def test_ace_soft_then_hard(self):
        self.assertEqual(blackjack_hand_total([11, 9]), 20)
        self.assertEqual(blackjack_hand_total([11, 11]), 12)
        self.assertEqual(blackjack_hand_total([11, 11, 11]), 13)
        self.assertEqual(blackjack_hand_total([11, 6, 5]), 12)
        self.assertEqual(blackjack_hand_total([10, 11]), 21)
        self.assertEqual(blackjack_hand_total([10, 7, 5]), 22)

    def test_no_aces(self):
        self.assertEqual(blackjack_hand_total([5, 6, 7]), 18)
        self.assertEqual(blackjack_hand_total([10, 10]), 20)


if __name__ == "__main__":
    unittest.main()
