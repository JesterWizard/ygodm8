# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## CHAIN_STRIKE (spell)
- file: `src_custom/spell_effects/chain_strike.c`
- clone: `src_custom/spell_effects/chain_energy.c` (CHAIN_ENERGY)
- optional template: `--fill burn CHAIN_STRIKE`
- text: Activate only as Chain Link 2 or higher; inflict 400 damage to your opponent times the Chain Link number of this card. Y Activate only as Chain Link 2 or higher; inflict 400 damage to your opponent times the Chain Link number of this card. You cannot activate this card if multiple cards/effects with the same name are in that Chain.

## POT_OF_EXTRAVAGANCE (spell)
- file: `src_custom/spell_effects/pot_of_extravagance.c`
- clone: `src_custom/spell_effects/backup_squad.c` (BACKUP_SQUAD)
- optional template: `--fill draw_n POT_OF_EXTRAVAGANCE`
- text: At the start of your Main Phase 1: Banish 3 or 6 random face-down cards from your Extra Deck, face-down; draw 1 card for At the start of your Main Phase 1: Banish 3 or 6 random face-down cards from your Extra Deck, face-down; draw 1 card for every 3 cards banished. For the rest of this turn after this card resolves, you cannot draw any cards by card effects.

## LEV_SHADDOLL_FUSION (spell)
- file: `src_custom/spell_effects/lev_shaddoll_fusion.c`
- clone: `src_custom/spell_effects/tribute_doll.c` (TRIBUTE_DOLL)
- optional template: `--fill tribute_summon LEV_SHADDOLL_FUSION`
- text: Send Fusion from Extra. Tribute Fusion; SS Shaddoll Fusion ATK 0. OPT. When this card is activated: Send 1 Fusion Monster from your Extra Deck to the GY. You can Tribute 1 Fusion Monster; Special Summon 1 Shaddoll Fusion Monster with a different Attribute from your Extra Deck (this is treated as a Fusion Summon), but change its ATK to 0. You can only use each effect of Lev Shaddoll Fusion once per turn, also you cannot Special Summon from the Extra Deck the turn you activate either of this card'

## PENTACLE_OF_ACE (spell)
- file: `src_custom/spell_effects/pentacle_of_ace.c`
- text: Coin: draw+heal you or opp. Toss a coin. Heads: draw 1 and gain 500 LP. Tails: opponent draws 1 and gains 500 LP.
