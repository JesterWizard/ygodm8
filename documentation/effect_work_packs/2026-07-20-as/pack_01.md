# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ELEMENTAL_HERO_AQUA_NEOS (activated)
- file: `src_custom/activated_effects/elemental_hero_aqua_neos.c`
- clone: `src_custom/activated_effects/elemental_hero_necroid_shaman.c` (ELEMENTAL_HERO_NECROID_SHAMAN)
- text: Discard; destroy random hand card. Elemental HERO Neos + Neo-Spacian Aqua Dolphin Must first be Special Summoned (from your Extra Deck) by shuffling the above cards you control into the Deck. (You do not use Polymerization.) Once per turn: You can discard 1 card; destroy 1 random card in your opponent's hand. During the End Phase: Shuffle this card into the Extra Deck.

## DESTINY_HERO_CAPTAIN_TENACIOUS (activated)
- file: `src_custom/activated_effects/destiny_hero_captain_tenacious.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: Once per turn, during your Standby Phase: You can target 1 Destiny HERO monster in your Graveyard that was destroyed by  Once per turn, during your Standby Phase: You can target 1 Destiny HERO monster in your Graveyard that was destroyed by battle since your last Standby Phase, if you controlled this face-up card when the target was destroyed; Special Summon that target.

## LYLA_LIGHTSWORN_SORCERESS (activated)
- file: `src_custom/activated_effects/lyla_lightsworn_sorceress.c`
- clone: `src_custom/activated_effects/lyla_twilightsworn_enchantress.c` (LYLA_TWILIGHTSWORN_ENCHANTRESS)
- text: Destroy S/T via Defense; mill 3. You can target 1 Spell/Trap your opponent controls; this card's battle position cannot be changed until the end of your next turn, also change this card you control from face-up Attack Position to face-up Defense Position, and if you do, destroy that target. Once per turn, during your End Phase: Send the top 3 cards of your Deck to the GY.

## ATLANTEAN_DRAGOONS (activated)
- file: `src_custom/activated_effects/atlantean_dragoons.c`
- clone: `src_custom/activated_effects/amazoness_trainee.c` (AMAZONESS_TRAINEE)
- text: All Level 3 or lower Sea Serpent-Type monsters you control can attack your opponent directly. When this card is sent to  All Level 3 or lower Sea Serpent-Type monsters you control can attack your opponent directly. When this card is sent to the Graveyard to activate a WATER monster's effect: Add 1 Sea Serpent-Type monster from your Deck to your hand, except Atlantean Dragoons.
