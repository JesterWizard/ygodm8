# Custom Content Index

This repository keeps custom work outside the vanilla source tree. These are completely seperate from the vanilla decomp and can be disabled easily.

## Custom Folders

| Path | What it contains |
| --- | --- |
| `src_custom/` | Main custom code, generated includes, and custom assets. |
| `src_custom/assets/` | Custom card art and thought bubble assets. |
| `src_custom/custom_decks/` | Custom deck definitions and helpers. |
| `src_custom/generated/` | Generated data and lookup files used by the build. |
| `src_custom/permanent_effects/` | Custom permanent effect hooks. |
| `src_custom/spell_effects/` | Custom spell effect hooks. |
| `events/` | Custom event scripts and event documentation. |
| `documentation/` | Project-specific design and implementation notes. |
| `plans/` | Planning notes and pipeline writeups. |

## Notable Root Files

| Path | What it contains |
| --- | --- |
| `README.md` | Project overview and build instructions. |
| `CUSTOM_CONTENT.md` | This index of custom folders and files. |

## Notes

- `src_custom/` is the main place to look for project-specific additions.
- Generated files live in `src_custom/generated/` and should usually be edited through the scripts or sources that produce them.
