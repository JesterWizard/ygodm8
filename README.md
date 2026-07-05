# ygodm8

`ygodm8` is a GBA decompilation-style codebase that builds with the legacy `agbcc` toolchain.

It is intended for inspecting, modifying, and rebuilding the game from a C and assembly decompiled source. That makes it useful for reverse engineering, bug fixes, feature work, and ROM hacking.

## Setup

See [SETUP.md](SETUP.md) for toolchain requirements, platform setup (Linux, WSL, or Windows via devkitPro), building, testing, and troubleshooting.

## Custom features

This build extends vanilla Yu-Gi-Oh! Forbidden Memories with manifest-driven content, LynJump hooks, and runtime toggles in `configs/runtime.c`. Most features can be turned on or off at compile time.

### Cards and effects

- **Custom cards** — New cards past ID 800 via `tools/card_data_manifest.json`, with 512×512 art pipeline, auto mini-art, and expanded save/trunk memory ([adding-custom-cards.md](documentation/adding-custom-cards.md), [custom-card-memory.md](documentation/custom-card-memory.md)).
- **280+ card effect hooks** — Spell, trap, activated, permanent, battle, turn, and passive effects for existing cards (`src_custom/card_effect_tally.md`).
- **Custom field spells** — New terrain graphics and field-spell behavior ([custom-field-spells.md](documentation/custom-field-spells.md)).
- **Card descriptions** — Generated description text for custom cards ([card-descriptions.md](documentation/card-descriptions.md)).
- **Activated effect text** — Improved in-duel effect messaging ([activated-effect-text.md](documentation/activated-effect-text.md)).
- **Big card art palette extension** — Up to 112 colors on the card detail view (experimental; off by default) ([big-card-art-palette-extension.md](documentation/big-card-art-palette-extension.md)).
- **Duel helpers API** — Reusable draw, destroy, LP change, summon, and stat-overlay helpers for effect authors (`include/duel_helpers.h`).

### Duel gameplay

- **Expanded graveyard** — 40-card graveyard stacks with in-duel B-menu viewer ([expanded-graveyard.md](documentation/expanded-graveyard.md)).
- **Duel board life points** — Player and opponent LP counters on the field ([duel-board-life-points.md](documentation/duel-board-life-points.md)).
- **Turn counter on board** — Yellow turn count between the LP displays.
- **Duel retry after defeat** — Immediate restart prompt after losing ([duel-retry-after-defeat.md](documentation/duel-retry-after-defeat.md)).
- **Surrender in B menu** — Fourth B-menu option to forfeit ([duel-b-menu-surrender.md](documentation/duel-b-menu-surrender.md)).
- **Opponent hand field scroll** — Scroll past the opponent back row to peek at their hand.
- **Low-LP BGM tempo** — Speed up duel music when LP drops below a threshold ([duel-low-lp-bgm-tempo.md](documentation/duel-low-lp-bgm-tempo.md)).
- **Duel shop card drops** — Post-win popup listing cards added to the shop ([duel-shop-card-drops.md](documentation/duel-shop-card-drops.md)).
- **Smarter AI** — Vary among top-rated AI lines instead of one fixed play ([smarter-ai.md](documentation/smarter-ai.md)).
- **Fast AI** — Cap speculative sim work per decision to keep turns responsive.
- **AI both sides** — Fully automated duels from the debug menu ([ai-both-sides-duel-mode.md](documentation/ai-both-sides-duel-mode.md)).
- **Timed duels** — Puzzle layouts with EWRAM completion tracking ([timed-duels.md](documentation/timed-duels.md)).
- **Ban list disabled** — Freedoms for testing and custom rulesets.
- **Configurable duel start field** — Force a terrain or use each duelist’s default.
- **Element system toggle** — Optional disable of the vanilla element wheel.

### Progression and economy

- **Multiple player decks** — Switch between saved deck loadouts ([multiple-decks.md](documentation/multiple-decks.md)).
- **Custom deck definitions** — Author decks under `src_custom/custom_decks/`.
- **Deck capacity rewards** — Configurable trunk-size rewards for story and repeat wins.
- **Alternate win reward multiplier** — Boost non-story duel payouts.
- **Duelist level shop discounts** — Buy-price reduction scaled by duelist level ([duelist-level-shop-discounts.md](documentation/duelist-level-shop-discounts.md)).
- **Dynamic card shop costs** — Shop prices from card cost × 40.
- **Dynamic trunk and shop sorting** — Manifest-driven sort order.
- **Hide unowned trunk cards** — Optional trunk list that only shows owned cards.
- **Ante and sell with one copy** — Loosen vanilla copy restrictions for QoL.
- **Add deck cards to trunk** — Deck builder cards sync into the trunk.
- **Persistent card cost randomizer** — Seeded shop price shuffle at new game ([card-cost-randomizer.md](documentation/card-cost-randomizer.md)).
- **Start with full trunk** — Optional new-game grants (one or three copies of every card).
- **Duelist reward manifest** — Data-driven normal and low ante drop tables ([duelist-reward-manifest.md](documentation/duelist-reward-manifest.md)).
- **Password terminal feedback** — Result popups and pay-only-on-success for card passwords ([password-terminal-feedback.md](documentation/password-terminal-feedback.md)).

### Overworld and UI

- **Custom opening screens** — Replace boot copyright splashes ([opening-screens.md](documentation/opening-screens.md)).
- **Custom title screen** — Replace title background art ([title-screen.md](documentation/title-screen.md)).
- **Title screen intro video** — Optional idle-triggered FMV on the title screen ([intro-videos.md](documentation/intro-videos.md)).
- **Skip opening sequence** — Jump straight to gameplay for faster iteration.
- **Custom dialogue portraits** — PNG portraits wired into event scripts ([custom-portraits.md](documentation/custom-portraits.md)).
- **Thought bubbles** — Event-flag-driven overworld bubble art ([thought-bubbles.md](documentation/thought-bubbles.md)).
- **Shiny zones** — Interactable overworld card pickups from a manifest ([shiny-zones.md](documentation/shiny-zones.md)).
- **Custom event scripts** — Overworld script replacements under `events/`.
- **Event CG framework** — Full-screen event illustrations ([event-cg.md](documentation/event-cg.md)).
- **Status menu layout** — Custom millennium-item icons and label/value layout ([status-menu-layout.md](documentation/status-menu-layout.md)).
- **Faster walking speed** — Configurable overworld move rate.
- **Ante card viewer** — **SELECT** facing a duelist to preview their ante pools ([ante-card-viewer.md](documentation/ante-card-viewer.md)).
- **Duelist deck viewer** — **START** facing a duelist for a read-only deck list ([duelist-deck-viewer.md](documentation/duelist-deck-viewer.md)).

### Audio and visuals

- **Custom background music** — DPCM music manifest and in-ROM track slots ([custom-music.md](documentation/custom-music.md)).
- **Custom duelist voices** — Per-duelist voice clip overrides ([custom-voices.md](documentation/custom-voices.md)).
- **m4a HQ mixer** — Higher-quality music playback path ([m4a-hq-mixer.md](documentation/m4a-hq-mixer.md)).

### Developer tools

- **Debug menu** — Overworld **R** sidebar with music, portrait, sprite, reaction, voice, graphic, match-setter, map teleport, scene, ruleset, and deck-preset tools ([debug-menu.md](documentation/debug-menu.md)).
- **Save anywhere** — House save prompt from any overworld tile via the debug menu ([save-anywhere.md](documentation/save-anywhere.md)).
- **Reaction viewer** — Preview overworld reaction animations ([reaction-viewer.md](documentation/reaction-viewer.md)).
- **Runtime test hand and skip-to-duel** — Opening hand, mono-deck, and direct-to-duel shortcuts in `configs/runtime.c`.
- **Test-driven development harness** — Host unit tests, golden output, and ROM validators (`make test`, `make test-host`) ([tdd-framework.md](documentation/tdd-framework.md)).

### Infrastructure

- **LynJump replacements** — Patch vanilla functions post-link without editing `src/` ([lynjump-replacements.md](documentation/lynjump-replacements.md)).
- **RAM map allocation** — Documented IWRAM/EWRAM/Flash layout for custom globals and save growth ([ram-map.md](documentation/ram-map.md)).
- **Toggle custom layers** — `CUSTOM_CODE=0`, `CUSTOM_EVENTS=0`, and `CUSTOM_CARD_MANIFEST=0` Makefile switches for vanilla comparisons.

See [CUSTOM_CONTENT.md](CUSTOM_CONTENT.md) for the custom folder index and [ARCHITECTURE.md](ARCHITECTURE.md) for how the pieces fit together.
