# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GLADIATOR_BEAST_MURMILLO (activated)
- file: `src_custom/activated_effects/gladiator_beast_murmillo.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: Destroy monster; tag out after. When this card is Special Summoned by the effect of a Gladiator Beast monster: Target 1 face-up monster; destroy that target. At the end of the Battle Phase, if this card attacked or was attacked: You can shuffle it into the Deck; Special Summon 1 Gladiator Beast monster from your Deck, except Gladiator Beast Murmillo.

## SKILLED_WHITE_MAGICIAN (activated)
- file: `src_custom/activated_effects/skilled_white_magician.c`
- clone: `src_custom/activated_effects/chimeratech_fortress_dragon.c` (CHIMERATECH_FORTRESS_DRAGON)
- text: Each time a Spell Card is activated, place 1 Spell Counter on this card when that Spell Card resolves (max. 3). You can  Each time a Spell Card is activated, place 1 Spell Counter on this card when that Spell Card resolves (max. 3). You can Tribute this card with 3 Spell Counters on it; Special Summon 1 Buster Blader from your hand, Deck, or Graveyard.

## BEAST_MACHINE_KING_BARBAROS_UR (activated)
- file: `src_custom/activated_effects/beast_machine_king_barbaros_ur.c`
- clone: `src_custom/activated_effects/crimson_blader.c` (CRIMSON_BLADER)
- text: You can Special Summon this card (from your hand) by banishing 1 Machine-Type monster and 1 Beast-Warrior-Type monster f You can Special Summon this card (from your hand) by banishing 1 Machine-Type monster and 1 Beast-Warrior-Type monster from your hand, field, and/or Graveyard. If this card attacks or is attacked, your opponent takes no battle damage.

## EVIL_HERO_ADUSTED_GOLD (activated)
- file: `src_custom/activated_effects/evil_hero_adusted_gold.c`
- clone: `src_custom/activated_effects/evil_hero_lightning_golem.c` (EVIL_HERO_LIGHTNING_GOLEM)
- text: Discard: search Dark Fusion or related. Can't attack without a Fusion. You can discard this card; add 1 Dark Fusion, or 1 card that specifically lists Dark Fusion in its text, from your Deck to your hand, except Evil HERO Adusted Gold. You can only use this effect of Evil HERO Adusted Gold once per turn. Cannot attack unless you control a Fusion Monster.
