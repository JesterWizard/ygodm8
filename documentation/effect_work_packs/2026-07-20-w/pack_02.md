# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## DAMAGE_REPTILE (trap)
- file: `src_custom/trap_effects/damage_reptile.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: OPT when battle dmg with Reptile: SS Reptile from Deck with ATK <= damage. Once per turn, when you take Battle Damage from a battle involving a Reptile-Type monster, you can Special Summon 1 Reptile-Type monster from your Deck with ATK less than or equal to the Battle Damage you took.

## SCRAP_IRON_SCARECROW (trap)
- file: `src_custom/trap_effects/scrap_iron_scarecrow.c`
- clone: `src_custom/trap_effects/coffin_seller.c` (COFFIN_SELLER)
- text: When an opponent's monster declares an attack: Target the attacking monster; negate the attack, also, after that, Set th When an opponent's monster declares an attack: Target the attacking monster; negate the attack, also, after that, Set this card face-down instead of sending it to the GY.

## MORPHTRONIC_FORCEFIELD (trap)
- file: `src_custom/trap_effects/morphtronic_forcefield.c`
- clone: `src_custom/trap_effects/morphtronic_bind.c` (MORPHTRONIC_BIND)
- text: Negate the activation of a Spell or Trap Card that would destroy a face-up Morphtronic monster you control and destroy Negate the activation of a Spell or Trap Card that would destroy a face-up Morphtronic monster you control and destroy it. Add 1 Morphtronic card from your Deck to your hand.

## QUEENS_PAWN (trap)
- file: `src_custom/trap_effects/queens_pawn.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: Activate only when an Amazoness monster you control destroys an opponent's monster by battle and sends it to the Grave Activate only when an Amazoness monster you control destroys an opponent's monster by battle and sends it to the Graveyard. Special Summon 1 Level 4 or lower Amazoness monster from your Deck.
