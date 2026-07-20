# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GLADIATOR_BEAST_LANISTA (activated)
- file: `src_custom/activated_effects/gladiator_beast_lanista.c`
- clone: `src_custom/activated_effects/chimeratech_megafleet_dragon.c` (CHIMERATECH_MEGAFLEET_DRAGON)
- text: Copy banished GB name; tag out. When this card is Special Summoned by the effect of a Gladiator Beast monster: Target 1 Gladiator Beast monster in your Graveyard; banish that target, and this card's name becomes the target's name until the End Phase. At the end of the Battle Phase, if this card attacked or was attacked: You can shuffle it into the Deck; Special Summon 1 Gladiator Beast monster from your Deck, except Gladiator Beast Lanista.

## HONEST (activated)
- file: `src_custom/activated_effects/honest.c`
- clone: `src_custom/activated_effects/elemental_hero_neos_alius.c` (ELEMENTAL_HERO_NEOS_ALIUS)
- text: During your Main Phase: You can return this face-up card from the field to the hand. During the Damage Step, when a LIGH During your Main Phase: You can return this face-up card from the field to the hand. During the Damage Step, when a LIGHT monster you control battles (Quick Effect): You can send this card from your hand to the GY; that monster gains ATK equal to the ATK of the opponent's monster it is battling, until the end of this turn.

## ARCANA_KNIGHT_JOKER (activated)
- file: `src_custom/activated_effects/arcana_knight_joker.c`
- clone: `src_custom/activated_effects/atlantean_attack_squad.c` (ATLANTEAN_ATTACK_SQUAD)
- text: Queen's Knight + Jack's Knight + King's Knight
A Fusion Summon of this card can only be done with the above mater Queen's Knight + Jack's Knight + King's Knight A Fusion Summon of this card can only be done with the above materials. Once per turn, when a Spell/Trap Card, or monster effect, is activated that targets this face-up card on the field (Quick Effect): You can discard the same type of card (Monster, Spell, or Trap); negate the effect.

## ARCANA_FORCE_XV_THE_FIEND (activated)
- file: `src_custom/activated_effects/arcana_force_xv_the_fiend.c`
- clone: `src_custom/activated_effects/shaddoll_hound.c` (SHADDOLL_HOUND)
- text: Discard: search Light Barrier. Coin wipe. You can discard this card; add 1 Light Barrier from your Deck or GY to your hand. If this card is Summoned: Toss a coin and this card gains the appropriate effect. Heads: When an attack is declared involving this card: You can target 1 monster on the field; destroy it, and if you do, inflict 500 damage to its controller. Tails: If an attack is declared involving this card: Destroy all monsters on the field.
