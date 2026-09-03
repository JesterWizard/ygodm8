# Custom Card Keep List (trimmed)

Curated subset of the **1,290-card custom trunk** (IDs 801+) to focus development and trunk visibility. Everything else stays in the manifest for now but is **out of scope** until effects are finished or the card is promoted.

---

## Summary

| Metric | Count |
|--------|------:|
| Custom trunk total | 1290 |
| **Keep** | 207 |
| Excluded (unwired) | 51 |
| Deferred, not on keep list | 81 |

Machine-readable list: [`tools/custom_card_keep_list.json`](../tools/custom_card_keep_list.json)

---

## Policy

1. **Keep** — dedicated effect file (or shared hook) with playable logic; iconic or actively maintained.
2. **Exclude** — 51 effect cards with **no wiring** (TCG text only). Listed in `exclude_consts` in the JSON.
3. **Cut for now** — full archetype bloat (e.g. all 31 Morphtronic), most Extra-Deck stand-ins, and deferred chain/Xyz debt unless iconic.
4. **Archetype cap** — 3–6 cards per engine (Gladiator Beast, Lightsworn, D-Hero, etc.); Harpie/Blue-Eyes/DM get larger packages because they are recent polish targets.

---

## Excluded — unwired (do not promote)

These have effect text in-game but **no effect logic**. Safe to hide from trunk/shop until implemented.

- `DRAIN_TIME` — Drain Time
- `EGYPTIAN_GOD_SLIME` — Egyptian God Slime
- `ELEMENTAL_HERO_MUDBALLMAN` — Elemental HERO Mudballman
- `ELEMENTAL_HERO_NEOS_KLUGER` — Elemental HERO Neos Kluger
- `EMERGENCY_PROVISIONS` — Emergency Provisions
- `EXODIUS_THE_ULTIMATE_FORBIDDEN_LORD` — Exodius the Ultimate Forbidden Lord
- `FATAL_ABACUS` — Fatal Abacus
- `FELGRAND_DRAGON` — Felgrand Dragon
- `FIELDS_SANCTUARY` — Fields Sanctuary
- `FIRES_OF_DOOMSDAY` — Fires of Doomsday
- `FORCED_REQUISITION` — Forced Requisition
- `JOWGEN_THE_SPIRITUALIST` — Jowgen the Spiritualist
- `KA_2_DES_SCISSORS` — KA-2 Des Scissors
- `KING_DRAGUN` — King Dragun
- `KING_OF_THE_SWAMP` — King of the Swamp
- `KING_TIGER_WANGHU` — King Tiger Wanghu
- `KURAZ_THE_LIGHT_MONARCH` — Kuraz the Light Monarch
- `KURIBANDIT` — Kuribandit
- `LAST_TURN` — Last Turn
- `LEGENDARY_FLAME_LORD` — Legendary Flame Lord
- `LEGEND_OF_HEART` — Legend of Heart
- `MAGICIANS_VALKYRIA` — Magician's Valkyria
- `PALADIN_OF_WHITE_DRAGON` — Paladin Of White Dragon
- `RED_EYES_DARKNESS_METAL_DRAGON` — Red-Eyes Darkness Metal Dragon
- `RED_EYES_DARK_DRAGOON` — Red-Eyes Dark Dragoon
- `RED_EYES_TRANSMIGRATION` — Red-Eyes Transmigration
- `RELAY_SOUL` — Relay Soul
- `REVERSE_OF_REVERSE` — Reverse of Reverse
- `ROPE_OF_LIFE` — Rope of Life
- `SPELL_ABSORPTION` — Spell Absorption
- `SPHINX_TELEIA` — Sphinx Teleia
- `STATUE_OF_THE_WICKED` — Statue of the Wicked
- `STAUNCH_DEFENDER` — Staunch Defender
- `STRAY_LAMBS` — Stray Lambs
- `STRONGHOLD_THE_MOVING_FORTRESS` — Stronghold the Moving Fortress
- `ST_JOAN` — St Joan
- `SUMMONER_MONK` — Summoner Monk
- `SUMMONER_OF_ILLUSIONS` — Summoner of Illusions
- `TERRAFORMING` — Terraforming
- `VISION_HERO_MINIMUM_RAY` — Vision HERO Minimum Ray
- `VISION_HERO_MULTIPLY_GUY` — Vision HERO Multiply Guy
- `VISION_HERO_POISONER` — Vision HERO Poisoner
- `VISION_HERO_TRINITY` — Vision HERO Trinity
- `VISION_HERO_VYON` — Vision HERO Vyon
- `VISION_HERO_WITCH_RAIDER` — Vision HERO Witch Raider
- `VISION_RELEASE` — Vision Release
- `WATAPON` — Watapon
- `WHITE_DRAGON_RITUAL` — White Dragon Ritual
- `WILD_NATURES_RELEASE` — Wild Nature's Release
- `WOUGHTWEILER` — Wroughtweiler
- `YELLOW_GADGET` — Yellow Gadget

---

## Keep list by package

### Amazoness (9)

- `AMAZONESS_TIGER` — Amazoness Tiger
- `AMAZONESS_ARCHER` — Amazoness Archer
- `AMAZONESS_AUGUSTA` — Amazoness Augusta
- `AMAZONESS_EMPRESS` — Amazoness Empress
- `AMAZONESS_PRINCESS` — Amazoness Princess
- `AMAZONESS_QUEEN` — Amazoness Queen
- `AMAZONESS_CALL` — Amazoness Call
- `AMAZONESS_ONSLAUGHT` — Amazoness Onslaught
- `AMAZONESS_VILLAGE` — Amazoness Village

### Ancient Gear (5)

- `ANCIENT_GEAR` — Ancient Gear
- `ANCIENT_GEAR_ADVANCE` — Ancient Gear Advance
- `ANCIENT_GEAR_BEAST` — Ancient Gear Beast
- `ANCIENT_GEAR_CANNON` — Ancient Gear Cannon
- `ANCIENT_GEAR_CASTLE` — Ancient Gear Castle

### Arcana Force (3)

- `ARCANA_FORCE_0_THE_FOOL` — Arcana Force 0 - The Fool
- `ARCANA_FORCE_EX_THE_DARK_RULER` — Arcana Force EX - The Dark Ruler
- `ARCANA_FORCE_I_THE_MAGICIAN` — Arcana Force I - The Magician

### Aroma (4)

- `AROMA_BLEND` — Aroma Blend
- `AROMA_GARDEN` — Aroma Garden
- `AROMA_GARDENING` — Aroma Gardening
- `AROMA_JAR` — Aroma Jar

### Blue-Eyes (11)

- `BLUE_EYES_SHINING_DRAGON` — Blue-Eyes Shining Dragon
- `BLUE_EYES_CHAOS_DRAGON` — Blue-Eyes Chaos Dragon
- `BLUE_EYES_JET_DRAGON` — Blue-Eyes Jet Dragon
- `BLUE_EYES_SOLID_DRAGON` — Blue-Eyes Solid Dragon
- `DEEP_EYES_WHITE_DRAGON` — Deep-Eyes White Dragon
- `DRAGON_SPIRIT_OF_WHITE` — Dragon Spirit of White
- `RETURN_OF_THE_DRAGON_LORDS` — Return of the Dragon Lords
- `SILVERS_CRY` — Silver's Cry
- `THE_MELODY_OF_AWAKENING_DRAGON` — The Melody of Awakening Dragon
- `THE_WHITE_STONE_OF_ANCIENTS` — The White Stone of Ancients
- `THE_WHITE_STONE_OF_LEGEND` — The White Stone of Legend

### Cyber (9)

- `CYBER_DRAGON` — Cyber Dragon
- `PROTO_CYBER_DRAGON` — Proto-Cyber Dragon
- `CHIMERATECH_OVERDRAGON` — Chimeratech Overdragon
- `CYBERNETIC_FUSION_SUPPORT` — Cybernetic Fusion Support
- `OVERLOAD_FUSION` — Overload Fusion
- `CYBER_BARRIER_DRAGON` — Cyber Barrier Dragon
- `CYBER_LASER_DRAGON` — Cyber Laser Dragon
- `PHOTON_GENERATOR_UNIT` — Photon Generator Unit
- `CYBER_DRAGON_INFINITY` — Cyber Dragon Infinity

### Dark Magician (12)

- `DARK_MAGIC_ATTACK` — Dark Magic Attack
- `DARK_MAGIC_INHERITANCE` — Dark Magic Inheritance
- `DARK_MAGIC_VEIL` — Dark Magic Veil
- `DARK_MAGICAL_CIRCLE` — Dark Magical Circle
- `DARK_MAGICIAN_OF_DESTRUCTION` — Dark Magician of Destruction
- `ETERNAL_SOUL` — Eternal Soul
- `MAGICIAN_OF_DARK_ILLUSION` — Magician of Dark Illusion
- `MAGICIANS_ROD` — Magician's Rod
- `MAGICIANS_SOULS` — Magicians' Souls
- `MASTER_OF_CHAOS` — Master of Chaos
- `SECRETS_OF_DARK_MAGIC` — Secrets of Dark Magic
- `SOUL_SERVANT` — Soul Servant

### Destiny Hero (5)

- `DESTINY_HERO_BLADE_MASTER` — Destiny HERO - Blade Master
- `DESTINY_HERO_CAPTAIN_TENACIOUS` — Destiny HERO - Captain Tenacious
- `DESTINY_HERO_CELESTIAL` — Destiny HERO - Celestial
- `DESTINY_HERO_DANGEROUS` — Destiny HERO - Dangerous
- `DESTINY_HERO_DASHER` — Destiny HERO - Dasher

### Elemental HERO (11)

- `ELEMENTAL_HERO_FLAME_WINGMAN` — Elemental HERO Flame Wingman
- `ELEMENTAL_HERO_SHINING_FLARE_WINGMAN` — Elemental HERO Shining Flare Wingman
- `MIRACLE_FUSION` — Miracle Fusion
- `ELEMENTAL_HERO_NEOS` — Elemental HERO Neos
- `FUSION_RECOVERY` — Fusion Recovery
- `SKYSCRAPER` — Skyscraper
- `H_HEATED_HEART` — H - Heated Heart
- `E_EMERGENCY_CALL` — E - Emergency Call
- `ELEMENTAL_HERO_ICE_EDGE` — Elemental HERO Ice Edge
- `ELEMENTAL_HERO_BLAZEMAN` — Elemental HERO Blazeman
- `ELEMENTAL_HERO_STRATOS` — Elemental HERO Stratos

### Evil Hero (5)

- `EVIL_HERO_ADUSTED_GOLD` — Evil HERO Adusted Gold
- `EVIL_HERO_DARK_GAIA` — Evil HERO Dark Gaia
- `EVIL_HERO_DARKEST_KNIGHT` — Evil HERO Darkest Knight
- `EVIL_HERO_DEAD_END_PRISON` — Evil HERO Dead-End Prison
- `EVIL_HERO_INFERNAL_GAINER` — Evil HERO Infernal Gainer

### Extra stand-ins (5)

- `INSTANT_FUSION` — Instant Fusion
- `EVOLZAR_DOLKKA` — Evolzar Dolkka
- `HONEST` — Honest
- `NUMBER_39_UTOPIA` — Number 39: Utopia
- `TOADALLY_AWESOME` — Toadally Awesome

### Field / meta (5)

- `SEAL_OF_ORICHALCOS` — Seal of Orichalcos
- `THE_SANCTUARY_IN_THE_SKY` — The Sanctuary in the Sky
- `A_LEGENDARY_OCEAN` — A Legendary Ocean
- `DIVINE_SANCTUARY` — Divine Sanctuary
- `NECROVALLEY` — Necrovalley

### Gladiator Beast (6)

- `GLADIATOR_BEAST_ALEXANDER` — Gladiator Beast Alexander
- `GLADIATOR_BEAST_ATTORIX` — Gladiator Beast Attorix
- `GLADIATOR_BEAST_AUGUSTUS` — Gladiator Beast Augustus
- `GLADIATOR_BEAST_BATTLE_HALBERD` — Gladiator Beast's Battle Halberd
- `GLADIATOR_BEAST_BESTIARI` — Gladiator Beast Bestiari
- `GLADIATOR_BEAST_CLAUDIUS` — Gladiator Beast Claudius

### Gravekeepers (9)

- `GRAVEKEEPERS_CHIEF` — Gravekeeper's Chief
- `GRAVEKEEPERS_COMMANDANT` — Gravekeeper's Commandant
- `GRAVEKEEPERS_HEADMAN` — Gravekeeper's Headman
- `GRAVEKEEPERS_ORACLE` — Gravekeeper's Oracle
- `GRAVEKEEPERS_RECRUITER` — Gravekeeper's Recruiter
- `GRAVEKEEPERS_SPIRITUALIST` — Gravekeeper's Spiritualist
- `GRAVEKEEPERS_TRAP` — Gravekeeper's Trap
- `IMPERIAL_TOMBS_OF_NECROVALLEY` — Imperial Tombs of Necrovalley
- `HIDDEN_TEMPLES_OF_NECROVALLEY` — Hidden Temples of Necrovalley

### Harpie (13)

- `CYBER_SLASH_HARPIE_LADY` — Cyber Slash Harpie Lady
- `HARPIE_CHANNELER` — Harpie Channeler
- `HARPIE_CONDUCTOR` — Harpie Conductor
- `HARPIE_DANCER` — Harpie Dancer
- `HARPIE_HARPIST` — Harpie Harpist
- `HARPIE_LADY_ELEGANCE` — Harpie Lady Elegance
- `HARPIE_ORACLE` — Harpie Oracle
- `HARPIE_PERFUMER` — Harpie Perfumer
- `HARPIE_QUEEN` — Harpie Queen
- `HARPIES_FEATHER_REST` — Harpie's Feather Rest
- `HARPIES_FEATHER_STORM` — Harpie's Feather Storm
- `HARPIES_HUNTING_GROUND` — Harpies' Hunting Ground
- `HARPIES_PET_PHANTASMAL_DRAGON` — Harpie's Pet Phantasmal Dragon

### Lightsworn (6)

- `LIGHTSWORN_AEGIS` — Lightsworn Aegis
- `LIGHTSWORN_BARRIER` — Lightsworn Barrier
- `LIGHTSWORN_DRAGONLING` — Lightsworn Dragonling
- `LIGHTSWORN_JUDGEMENT` — Lightsworn Judgment
- `LIGHTSWORN_SABRE` — Lightsworn Sabre
- `LIGHTSWORN_SANCTUARY` — Lightsworn Sanctuary

### Neo Spacian (4)

- `NEO_SPACIAN_AIR_HUMMINGBIRD` — Neo-Spacian Air Hummingbird
- `NEO_SPACIAN_AQUA_DOLPHIN` — Neo-Spacian Aqua Dolphin
- `NEO_SPACIAN_FLARE_SCARAB` — Neo-Spacian Flare Scarab
- `NEO_SPACIAN_GLOW_MOSS` — Neo-Spacian Glow Moss

### Reptilianne (3)

- `REPTILIANNE_GARDNA` — Reptilianne Gardna
- `REPTILIANNE_GORGON` — Reptilianne Gorgon
- `REPTILIANNE_HYDRA` — Reptilianne Hydra

### Shaddoll (7)

- `EL_SHADDOLL_CONSTRUCT` — El Shaddoll Construct
- `EL_SHADDOLL_WINDA` — El Shaddoll Winda
- `SHADDOLL_BEAST` — Shaddoll Beast
- `SHADDOLL_DRAGON` — Shaddoll Dragon
- `SHADDOLL_FUSION` — Shaddoll Fusion
- `SHADDOLL_HEDGEHOG` — Shaddoll Hedgehog
- `SHADDOLL_SQUAMATA` — Shaddoll Squamata

### Shared-hook cards (12)

- `RARE_METAL_DRAGON` — Rare Metal Dragon
- `SWIFT_GAIA_THE_FIERCE_KNIGHT` — Swift Gaia The Fierce Knight
- `DOUBLE_COSTON` — Double Coston
- `ELEMENTAL_HERO_WILDHEART` — Elemental HERO Wildheart
- `ELEMENTAL_HERO_PHOENIX_ENFORCER` — Elemental HERO Phoenix Enforcer
- `DOOM_VIRUS_DRAGON` — Doom Virus Dragon
- `JUDGMENT_DRAGON` — Judgment Dragon
- `REAPER_SCYTHE_DREADSCYTHE` — Reaper Scythe - Dreadscythe
- `RED_EYES_BLACK_DRAGON_SWORD` — Red-Eyes Black Dragon Sword
- `RED_GADGET` — Red Gadget
- `ROCKET_HERMOS_CANNON` — Rocket Hermos Cannon
- `SUPER_POLYMERIZATION` — Super Polymerization

### Synchro stand-ins (6)

- `BRIONAC_DRAGON_OF_THE_ICE_BARRIER` — Brionac, Dragon of the Ice Barrier
- `GOYO_GUARDIAN` — Goyo Guardian
- `JUNK_WARRIOR` — Junk Warrior
- `RED_DRAGON_ARCHFIEND` — Red Dragon Archfiend
- `STARDUST_DRAGON` — Stardust Dragon
- `JUNK_SYNCHRON` — Junk Synchron

### Universal staples (48)

- `BLUE_EYES_CHAOS_MAX_DRAGON` — Blue-Eyes Chaos Max Dragon
- `KAIBAMAN` — Kaibaman
- `ULTIMATE_OFFERING` — Ultimate Offering
- `WAVE_MOTION_CANNON` — Wave Motion Cannon
- `SOUL_EXCHANGE` — Soul Exchange
- `MYSTICAL_SPACE_TYPHOON` — Mystical Space Typhoon
- `MASK_OF_RESTRICT` — Mask of Restrict
- `BLUE_EYES_ALTERNATIVE_WHITE_DRAGON` — Blue-Eyes Alternative White Dragon
- `SKILL_DRAIN` — Skill Drain
- `MAGIC_CYLINDER` — Magic Cylinder
- `DELINQUENT_DUO` — Delinquent Duo
- `YATA_GARASU` — Yata-Garasu
- `UPSTART_GOBLIN` — Upstart Goblin
- `CALL_OF_THE_HAUNTED` — Call of the Haunted
- `LIMITER_REMOVAL` — Limiter Removal
- `RECKLESS_GREED` — Reckless Greed
- `CARD_DESTRUCTION` — Card Destruction
- `GRACEFUL_CHARITY` — Graceful Charity
- `IMPERIAL_ORDER` — Imperial Order
- `ROYAL_DECREE` — Royal Decree
- `FINAL_COUNTDOWN` — Final Countdown
- `BOOK_OF_MOON` — Book of Moon
- `CONFISCATION` — Confiscation
- `ZABORG_THE_THUNDER_MONARCH` — Zaborg the Thunder Monarch
- `POLYMERIZATION` — Polymerization
- `CYBER_TWIN_DRAGON` — Cyber Twin Dragon
- `CYBER_END_DRAGON` — Cyber End Dragon
- `CAIUS_THE_SHADOW_MONARCH` — Caius the Shadow Monarch
- `MOBIUS_THE_FROST_MONARCH` — Mobius the Frost Monarch
- `MIRROR_FORCE` — Mirror Force
- `DE_FUSION` — De-Fusion
- `DARK_MAGICIAN_OF_CHAOS` — Dark Magician of Chaos
- `CHAOS_EMPEROR_DRAGON_ENVOY_OF_THE_END` — Chaos Emperor Dragon - Envoy of the End
- `BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING` — Black Luster Soldier - Envoy of the Beginning
- `POWER_BOND` — Power Bond
- `TRADE_IN` — Trade-In
- `MANJU_OF_THE_TEN_THOUSAND_HANDS` — Manju of the Ten Thousand Hands
- `MARSHMALLON` — Marshmallon
- `NIBIRU_THE_PRIMAL_BEING` — Nibiru, the Primal Being
- `SCAPEGOAT` — Scapegoat
- `SOLEMN_JUDGMENT` — Solemn Judgment
- `ASH_BLOSSOM_AND_JOYOUS_SPRING` — Ash Blossom & Joyous Spring
- `FORBIDDEN_CHALICE` — Forbidden Chalice
- `FORBIDDEN_LANCE` — Forbidden Lance
- `INFINITE_IMPERMANENCE` — Infinite Impermanence
- `LIGHTNING_STORM` — Lightning Storm
- `POT_OF_AVARICE` — Pot of Avarice
- `MAXX_C` — Maxx C

### Venom (2)

- `VENOM_BOA` — Venom Boa
- `VENOM_BURN` — Venom Burn

### Vision Hero (4)

- `VISION_HERO_ADORATION` — Vision HERO Adoration
- `VISION_HERO_FARIS` — Vision HERO Faris
- `VISION_HERO_GRAVITO` — Vision HERO Gravito
- `VISION_HERO_INCREASE` — Vision HERO Increase

### Yubel (3)

- `YUBEL` — Yubel
- `YUBEL_TERROR_INCARNATE` — Yubel - Terror Incarnate
- `YUBEL_THE_ULTIMATE_NIGHTMARE` — Yubel - The Ultimate Nightmare

---

## Using this list

Build-time only (default **on**):

```bash
make                          # CUSTOM_CARD_KEEP_LIST=1 — 207 custom cards, NUM_TOTAL_CARDS ≈ 0x3F0 (1008)
make CUSTOM_CARD_KEEP_LIST=0  # full 1,287-custom manifest (~2088 cards)
```

- `CUSTOM_CARD_KEEP_LIST` / `YGO_CUSTOM_CARD_KEEP_LIST` — `tools/add_card_art.py` filters `tools/card_data_manifest.json` to vanilla + `keep_consts` before generating `card_ids.h`, trunk, shop tables, and card data.
- `tools/custom_card_keep_list.json` — source of truth (`keep_consts`).
- Removed custom cards get stub IDs in `include/constants/custom_card_removed_stubs.h` so shared effect hooks still compile; they are not in trunk/shop ROM tables.

## Open / next

- [x] Build-time manifest trim: IDs top out ~1000 with keep list on (`NUM_TOTAL_CARDS` 0x3F0).
- [ ] Wire the 51 excluded cards or remove from manifest.
- [ ] Revisit deferred stand-ins after chain / Extra Deck engine milestones.
