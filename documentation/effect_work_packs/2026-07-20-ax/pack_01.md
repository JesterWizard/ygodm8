# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## LIGHTSWORN_DRAGONLING (activated)
- file: `src_custom/activated_effects/lightsworn_dragonling.c`
- clone: `src_custom/activated_effects/chimeratech_megafleet_dragon.c` (CHIMERATECH_MEGAFLEET_DRAGON)
- text: Hand SS; mill LS; search JD Dragon. If you have a Lightsworn monster in your GY: You can Special Summon this card from your hand. If this card is Special Summoned: You can send 1 Lightsworn card from your Deck to the GY, except Lightsworn Dragonling. If this card is sent to the GY: You can add 1 Dragon monster with 3000 ATK/2600 DEF from your Deck to your hand. You can only use each effect of Lightsworn Dragonling once per turn.

## GLADIATOR_BEAST_HERAKLINOS (activated)
- file: `src_custom/activated_effects/gladiator_beast_heraklinos.c`
- clone: `src_custom/activated_effects/gladiator_beast_bestiari.c` (GLADIATOR_BEAST_BESTIARI)
- text: Negate S/T; tag out after battle. Gladiator Beast Laquari + 2 Gladiator Beast monsters Must first be Special Summoned (from your Extra Deck) by shuffling the above cards you control into the Deck. (You do not use Polymerization.) During either player's turn, when a Spell/Trap Card is activated: You can discard 1 card; negate the activation and destroy it. This card must be face-up on the field to activate and to resolve this effect.

## ATLANTEAN_MARKSMAN (activated)
- file: `src_custom/activated_effects/atlantean_marksman.c`
- clone: `src_custom/activated_effects/chimeratech_megafleet_dragon.c` (CHIMERATECH_MEGAFLEET_DRAGON)
- text: When this card inflicts battle damage to your opponent: You can Special Summon 1 Level 4 or lower "Atlantean" Sea Serpen When this card inflicts battle damage to your opponent: You can Special Summon 1 Level 4 or lower Atlantean Sea Serpent-Type monster from your Deck, except Atlantean Marksman. When this card is sent to the Graveyard to activate a WATER monster's effect: Target 1 Set card your opponent controls; destroy that target.

## HORUS_THE_BLACK_FLAME_DRAGON_LV8 (activated)
- file: `src_custom/activated_effects/horus_the_black_flame_dragon_lv8.c`
- clone: `src_custom/activated_effects/elemental_hero_necroid_shaman.c` (ELEMENTAL_HERO_NECROID_SHAMAN)
- text: Cannot be Normal Summoned/Set. Must be Special Summoned by Horus the Black Flame Dragon LV6, and cannot be  Cannot be Normal Summoned/Set. Must be Special Summoned by Horus the Black Flame Dragon LV6, and cannot be Special Summoned by other ways. During either player's turn, when a Spell Card is activated: You can negate the activation, and if you do, destroy it. You must control this face-up card to activate and to resolve this effect.
