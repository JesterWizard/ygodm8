# Custom Content Index

This repository keeps custom work outside the vanilla source tree. These are completely seperate from the vanilla decomp and can be disabled easily.

## Custom Folders

| Path | What it contains |
| --- | --- |
| `src_custom/` | Main custom code, generated includes, and custom assets. |
| `src_custom/assets/` | Custom card art and thought bubble assets. |
| `src_custom/assets/portraits/` | Custom dialogue portrait PNGs and generated portrait data. |
| `src_custom/custom_decks/` | Custom deck definitions and helpers. |
| `src_custom/generated/` | Generated data and lookup files used by the build. |
| `src_custom/permanent_effects/` | Custom permanent effect hooks. |
| `src_custom/spell_effects/` | Custom spell effect hooks. |
| `events/` | Custom event scripts and event documentation. |
| `documentation/` | Project-specific design and implementation notes. |
| `tests/` | Host unit tests, golden generator output, and fixtures (`make test` / `make test-host`). |
| `plans/` | Planning notes and pipeline writeups. |

## Notable Root Files

| Path | What it contains |
| --- | --- |
| `README.md` | Project overview and build instructions. |
| `ARCHITECTURE.md` | Repo goals, folder map, where to look, core systems. |
| `SESSION_LOG.md` | Recent work history for contributors and agents. |
| `CUSTOM_CONTENT.md` | This index of custom folders and files. |
| `documentation/custom-portraits.md` | How to add custom dialogue portraits and use them in event scripts. |
| `documentation/adding-custom-cards.md` | How to add custom cards, including 80×80 big card art from source PNGs. |
| `documentation/duel-board-life-points.md` | Runtime toggle to show player and opponent LP on the duel field. |
| `documentation/duel-retry-after-defeat.md` | Runtime toggle to offer an immediate duel restart after losing. |
| `documentation/ante-card-viewer.md` | Overworld **SELECT** UI to preview a duelist’s normal and low ante card pools. |
| `documentation/expanded-graveyard.md` | 40-card graveyard stacks, B-menu viewer, EWRAM layout, and AI sim save/restore. |
| `documentation/debug-menu.md` | Developer debug menu (music, portrait, sprite viewers) on overworld **B**. |
| `documentation/tdd-framework.md` | Test-driven development harness: host tests, goldens, `make test`, and manual ROM smoke checks. |

## Notes

- `src_custom/` is the main place to look for project-specific additions.
- Generated files live in `src_custom/generated/` and should usually be edited through the scripts or sources that produce them.
