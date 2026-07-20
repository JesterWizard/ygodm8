# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## HARPIES_FEATHER_STORM (trap)
- file: `src_custom/trap_effects/harpies_feather_storm.c`
- clone: `src_custom/trap_effects/lightsworn_judgement.c` (LIGHTSWORN_JUDGEMENT)
- text: Negate opp monster effects. Hand-activatable. GY: search Duster. If you control a WIND Winged Beast monster: Until the end of this turn, negate any monster effects your opponent activates. If you control a Harpie monster, you can activate this card from your hand. If this card in its owner's Spell & Trap Zone is destroyed by an opponent's card effect: You can add 1 Harpie's Feather Duster from your Deck or GY to your hand.

## SHADDOLL_SCHISM (trap)
- file: `src_custom/trap_effects/shaddoll_schism.c`
- clone: `src_custom/trap_effects/light_spiral.c` (LIGHT_SPIRAL)
- text: Fusion Summon banishing mats; then send 1 opp monster to GY. During the Main Phase, you can: Fusion Summon 1 Shaddoll Fusion Monster from your Extra Deck, by banishing Fusion Materials listed on it from your field or GY, but it cannot attack directly. Then, you can send to the GY 1 monster your opponent controls with the same Attribute as that Fusion Summoned monster. You can only use this effect of Shaddoll Schism once per turn.

## SHADDOLL_CORE (trap)
- file: `src_custom/trap_effects/shaddoll_core.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: SS as monster. If Tributed: add 1 Shaddoll from GY to hand. Special Summon this card as an Effect Monster (Spellcaster/DARK/Level 9/ATK 1450/DEF 1950). (This card is also still a Trap.) If Summoned this way, you can substitute this monster for 1 Fusion Material that lists an Attribute, on a Shaddoll Fusion Monster Card. If this card is sent to the GY by a card effect: You can target 1 Shaddoll Spell/Trap in your GY, except Shaddoll Core; add it to your hand.

## DARK_SUPREMACY (trap)
- file: `src_custom/trap_effects/dark_supremacy.c`
- clone: `src_custom/trap_effects/light_of_destruction.c` (LIGHT_OF_DESTRUCTION)
- text: Negate opp face-up cards up to Dark Fusion count in GY. GY: shuffle up to 5 HERO. Target face-up cards your opponent controls, up to the number of Dark Fusion and Spells that mention it in your GY; negate their effects until the end of this turn. If this card is in your GY, except the turn it was sent there: You can banish it, then target up to 5 HERO monsters in your GY and/or banishment; shuffle them into the Deck. You can only use each effect of Dark Supremacy once per turn.
