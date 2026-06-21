# Duelling (GBA ROM hack)

Yu-Gi-Oh! GBA ROM hack: cards, effects, and duel mechanics for the Game Boy Advance game engine.

## Language

**Graveyard**:
A per-player stack of cards that have been sent from the field, hand, or deck. Up to 40 cards deep, stored in an expanded EWRAM array with a LIFO ordering. The legacy `u16` field in `DuelistBattleState` remains synced to the top of the stack for vanilla code compatibility.

**Graveyard viewer**:
A scrollable trunk-style list opened from the duel field by moving the cursor to a player's GY icon and pressing A. Shows the full 40-card stack for that player.

**Combined graveyard selector**:
A trunk-style picker that shows both players' graveyards together (player's cards in blue, opponent's in red). Used by effects like Monster Reborn that can revive from either GY. Per-player selectors (for Premature Burial, Call of the Haunted) show only that player's own stack.
