# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Traps: only edit listed trap .c. Do not leave TODO bodies. One make at the end of the whole batch.

## ACE_OF_WAND (trap)
- file: `src_custom/trap_effects/ace_of_wand.c`
- clone: `src_custom/trap_effects/gift_of_the_mystical_elf.c` (GIFT_OF_THE_MYSTICAL_ELF)
- text: Coin: heal or burn destroyed ATK. When a monster is destroyed by a card effect: toss a coin. Heads: its controller gains LP equal to total ATK. Tails: they take that much damage.

## LIGHT_SPIRAL (trap)
- file: `src_custom/trap_effects/light_spiral.c`
- clone: `src_custom/trap_effects/coffin_seller.c` (COFFIN_SELLER)
- text: Lightsworn mill: banish opp top. Each time a card(s) is sent from your Deck to the Graveyard by the effect of a Lightsworn monster, remove from play the top card of your opponent's Deck.

## SNAKE_WHISTLE (trap)
- file: `src_custom/trap_effects/snake_whistle.c`
- clone: `src_custom/trap_effects/embodiment_of_apophis.c` (EMBODIMENT_OF_APOPHIS)
- text: If Reptile destroyed: SS Lv4- Reptile from Deck. Activate only when a Reptile-Type monster you control is destroyed. Special Summon 1 Level 4 or lower Reptile-Type monster from your Deck.

## SERPENT_SUPPRESSION (trap)
- file: `src_custom/trap_effects/serpent_suppression.c`
- clone: `src_custom/trap_effects/level_limit_area_a.c` (LEVEL_LIMIT_AREA_A)
- text: Opp Attack Position 0 ATK monsters cannot be destroyed by battle. Face-up Attack Position monsters with 0 ATK your opponent controls cannot be destroyed by battle with Reptilianne monsters.

