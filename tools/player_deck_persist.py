#!/usr/bin/env python3
"""Host-testable layout for extra player deck flash persistence (mirrors player_decks.c)."""

from __future__ import annotations

import struct
from typing import Sequence

PLAYER_DECK_SAVE_MAGIC = 0xD5
PLAYER_DECK_CARD_COUNT = 40
PLAYER_DECK_CARD_BYTES = 0x50
CARD_NONE = 0x0000


class PlayerDeckPersistError(Exception):
    pass


def is_complete_deck(cards: Sequence[int], num_total_cards: int) -> bool:
    if len(cards) != PLAYER_DECK_CARD_COUNT:
        return False
    for card_id in cards:
        if card_id == CARD_NONE or card_id >= num_total_cards:
            return False
    return True


def serialize_flash_record(
    deck2: Sequence[int],
    deck3: Sequence[int],
    active_deck_index: int,
    magic: int = PLAYER_DECK_SAVE_MAGIC,
) -> bytes:
    if len(deck2) != PLAYER_DECK_CARD_COUNT or len(deck3) != PLAYER_DECK_CARD_COUNT:
        raise PlayerDeckPersistError("deck arrays must contain 40 card ids")
    if not 0 <= magic <= 0xFF:
        raise PlayerDeckPersistError("magic must be a single byte")
    if not 0 <= active_deck_index <= 0xFF:
        raise PlayerDeckPersistError("active_deck_index must be a single byte")
    parts = [struct.pack("<B", magic)]
    parts.append(struct.pack(f"<{PLAYER_DECK_CARD_COUNT}H", *deck2))
    parts.append(struct.pack(f"<{PLAYER_DECK_CARD_COUNT}H", *deck3))
    parts.append(struct.pack("<B", active_deck_index))
    return b"".join(parts)


def deserialize_flash_record(data: bytes) -> tuple[list[int], list[int], int, int]:
    expected = 1 + PLAYER_DECK_CARD_BYTES + PLAYER_DECK_CARD_BYTES + 1
    if len(data) != expected:
        raise PlayerDeckPersistError(f"expected {expected} bytes, got {len(data)}")
    magic = data[0]
    offset = 1
    deck2 = list(struct.unpack_from(f"<{PLAYER_DECK_CARD_COUNT}H", data, offset))
    offset += PLAYER_DECK_CARD_BYTES
    deck3 = list(struct.unpack_from(f"<{PLAYER_DECK_CARD_COUNT}H", data, offset))
    offset += PLAYER_DECK_CARD_BYTES
    (active_deck_index,) = struct.unpack_from("<B", data, offset)
    return deck2, deck3, active_deck_index, magic


def magic_is_valid(magic: int) -> bool:
    return magic == PLAYER_DECK_SAVE_MAGIC
