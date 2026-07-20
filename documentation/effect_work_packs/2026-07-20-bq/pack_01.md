# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## AURKUS_LIGHTSWORN_DRUID (permanent)
- file: `src_custom/permanent_effects/aurkus_lightsworn_druid.c`
- clone: `src_custom/permanent_effects/reptilianne_viper.c` (REPTILIANNE_VIPER)
- text: Protect Lightsworn; mill 2 at End. Neither player can target Lightsworn monsters (anywhere) with card effects. During each of your End Phases: Send the top 2 cards of your Deck to the Graveyard.

## GLADIATOR_BEAST_ESSEDARII (permanent)
- file: `src_custom/permanent_effects/gladiator_beast_essedarii.c`
- clone: `src_custom/permanent_effects/fenrir.c` (FENRIR)
- text: Contact Fusion; tag after battle. 2 Gladiator Beast monsters Must first be Special Summoned (from your Extra Deck) by shuffling the above cards you control into the Deck. (You do not use Polymerization.)

## JENIS_LIGHTSWORN_MENDER (permanent)
- file: `src_custom/permanent_effects/jenis_lightsworn_mender.c`
- clone: `src_custom/permanent_effects/reptilianne_viper.c` (REPTILIANNE_VIPER)
- text: Heal per miller; mill 2 at End. During the End Phase, if a card(s) was sent from your Deck to the Graveyard by the effect of a Lightsworn card this turn: Inflict 500 damage to your opponent, and if you do, gain 500 LP.

## EVIL_HERO_MALICIOUS_EDGE (permanent)
- file: `src_custom/permanent_effects/evil_hero_malicious_edge.c`
- clone: `src_custom/permanent_effects/elemental_hero_knospe.c` (ELEMENTAL_HERO_KNOSPE)
- text: 1 Tribute if opp has a monster. Piercing battle damage. If your opponent controls a monster, you can Tribute Summon this card face-up with 1 Tribute. If this card attacks a Defense Position monster, inflict piercing battle damage.
