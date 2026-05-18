# Custom Deck Modules

Each custom character gets its own module in this folder.

## Layout

- `custom_decks.c`
  - Shared registry, lookup, pending duel state, and text/script builders.
- `tea.c`
  - Tea-specific deck data and card-shop entry data.
- `tea.h`
  - Tea module exports.
- `character_template.c`
  - Copy this file when adding a new character.

## Add A Character

1. Copy `character_template.c` to `<name>.c`.
2. Replace the placeholder deck, portrait, sprite, location, and dialogue.
3. Add a matching `<name>.h` only if the module needs to export helpers.
4. Register the new module in `custom_decks.c`.

## Rules

- Keep character-specific data inside the character module.
- Keep shared lookup and duel plumbing in `custom_decks.c`.
- Keep human-edited dialogue as string literals, not byte lists.
