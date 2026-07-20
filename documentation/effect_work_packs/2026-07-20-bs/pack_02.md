# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ARCANA_FORCE_III_THE_EMPRESS (permanent)
- file: `src_custom/permanent_effects/arcana_force_iii_the_empress.c`
- clone: `src_custom/permanent_effects/arcana_force_vii_the_chariot.c` (ARCANA_FORCE_VII_THE_CHARIOT)
- text: Coin: draw on your or opp Normal Summon. When this card is Summoned, toss a coin: Heads: Each time your opponent Normal Summons or Sets a monster, you can Special Summon 1 Arcana Force monster from your hand. Tails: Each time your opponent Normal Summons or Sets a monster, send 1 card from your hand to the Graveyard.

## DESTINY_HERO_DREAD_SERVANT (permanent)
- file: `src_custom/permanent_effects/destiny_hero_dread_servant.c`
- clone: `src_custom/permanent_effects/elemental_hero_sunrise.c` (ELEMENTAL_HERO_SUNRISE)
- text: If this card is Normal Summoned: Place 1 Clock Counter on each Clock Tower Prison. When this card is destroyed by batt If this card is Normal Summoned: Place 1 Clock Counter on each Clock Tower Prison. When this card is destroyed by battle and sent to the GY: You can target 1 Spell/Trap you control; destroy that target.

## LEGENDARY_MAJU_GARZETT (permanent)
- file: `src_custom/permanent_effects/legendary_maju_garzett.c`
- clone: `src_custom/permanent_effects/elemental_hero_shining_flare_wingman.c` (ELEMENTAL_HERO_SHINING_FLARE_WINGMAN)
- text: SS by Tributing all; ATK = their original ATK. Piercing. Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by Tributing all monsters you control. This card's ATK becomes the combined original ATK of the Tributed monsters. If this card attacks a Defense Position monster, inflict piercing battle damage.

## ELEMENTAL_HERO_FLARE_NEOS (permanent)
- file: `src_custom/permanent_effects/elemental_hero_flare_neos.c`
- clone: `src_custom/permanent_effects/elemental_hero_sunrise.c` (ELEMENTAL_HERO_SUNRISE)
- text: +400 ATK per S/T; return at End. Elemental HERO Neos + Neo-Spacian Flare Scarab Must first be Special Summoned (from your Extra Deck) by shuffling the above cards you control into the Deck. (You do not use Polymerization.) This card gains 400 ATK for each Spell/Trap Card on the field. During the End Phase: Shuffle this card into the Extra Deck.
