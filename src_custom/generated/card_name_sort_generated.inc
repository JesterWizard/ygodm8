#include "global.h"

#define NUM_CUSTOM_NAME_SORT_CARDS 215

static const u8 sAmazonChainMasterSortName[] APPEND_RODATA = "Amazoness Chain Master";
static const u8 sAmazonFighterSortName[] APPEND_RODATA = "Amazoness Fighter";
static const u8 sAmazonSwordWomanSortName[] APPEND_RODATA = "Amazoness Sword Woman";
static const u8 sSorcererOfDarkMagicSortName[] APPEND_RODATA = "Sorcerer of Dark Magic";
static const u8 sDeckDestructionVirusSortName[] APPEND_RODATA = "Deck Destruction Virus";
static const u8 sMagiciansValkyriaSortName[] APPEND_RODATA = "Magician's Valkyria";
static const u8 sBlueEyesShiningDragonSortName[] APPEND_RODATA = "Blue-Eyes Shining Dragon";
static const u8 sPaladinOfWhiteDragonSortName[] APPEND_RODATA = "Paladin Of White Dragon";
static const u8 sCardOfDemiseSortName[] APPEND_RODATA = "Card Of Demise";
static const u8 sCardOfSanctitySortName[] APPEND_RODATA = "Card Of Sanctity";
static const u8 sShieldAndSwordSortName[] APPEND_RODATA = "Shield And Sword";
static const u8 sBlueEyesChaosMaxDragonSortName[] APPEND_RODATA = "Blue-Eyes Chaos Max Dragon";
static const u8 sChainEnergySortName[] APPEND_RODATA = "Chain Energy";
static const u8 sSpellCancellerSortName[] APPEND_RODATA = "Spell Canceller";
static const u8 sExchangeSortName[] APPEND_RODATA = "Exchange";
static const u8 sCopycatSortName[] APPEND_RODATA = "Copycat";
static const u8 sMagePowerSortName[] APPEND_RODATA = "Mage Power";
static const u8 sKaibamanSortName[] APPEND_RODATA = "Kaibaman";
static const u8 sUltimateOfferingSortName[] APPEND_RODATA = "Ultimate Offering";
static const u8 sUnitedWeStandSortName[] APPEND_RODATA = "United We Stand";
static const u8 sWaveMotionCannonSortName[] APPEND_RODATA = "Wave Motion Cannon";
static const u8 sStJoanSortName[] APPEND_RODATA = "St Joan";
static const u8 sPyramidOfLightSortName[] APPEND_RODATA = "Pyramid of Light";
static const u8 sSoulExchangeSortName[] APPEND_RODATA = "Soul Exchange";
static const u8 sMysticalSpaceTyphoonSortName[] APPEND_RODATA = "Mystical Space Typhoon";
static const u8 sRareMetalDragonSortName[] APPEND_RODATA = "Rare Metal Dragon";
static const u8 sDoubleSummonSortName[] APPEND_RODATA = "Double Summon";
static const u8 sObnoxiousCelticGuardianSortName[] APPEND_RODATA = "Obnoxious Celtic Guardian";
static const u8 sMaskOfRestrictSortName[] APPEND_RODATA = "Mask of Restrict";
static const u8 sFairyBoxSortName[] APPEND_RODATA = "Fairy Box";
static const u8 sCostDownSortName[] APPEND_RODATA = "Cost Down";
static const u8 sBlueEyesAlternativeWhiteDragonSortName[] APPEND_RODATA = "Blue-Eyes Alternative White Dragon";
static const u8 sAncientRulesSortName[] APPEND_RODATA = "Ancient Rules";
static const u8 sMagicJammerSortName[] APPEND_RODATA = "Magic Jammer";
static const u8 sSealOfOrichalcosSortName[] APPEND_RODATA = "Seal of Orichalcos";
static const u8 sFamiliarKnightSortName[] APPEND_RODATA = "Familiar Knight";
static const u8 sRiryokuSortName[] APPEND_RODATA = "Riryoku";
static const u8 sSpearDragonSortName[] APPEND_RODATA = "Spear Dragon";
static const u8 sSagesStoneSortName[] APPEND_RODATA = "Sage's Stone";
static const u8 sBowganianSortName[] APPEND_RODATA = "Bowganian";
static const u8 sDarkMagicCurtainSortName[] APPEND_RODATA = "Dark Magic Curtain";
static const u8 sCatsEarTribeSortName[] APPEND_RODATA = "Cat's Ear Tribe";
static const u8 sCureMermaidSortName[] APPEND_RODATA = "Cure Mermaid";
static const u8 sDesKoalaSortName[] APPEND_RODATA = "Des Koala";
static const u8 sSkillDrainSortName[] APPEND_RODATA = "Skill Drain";
static const u8 sGuardianTreasureSortName[] APPEND_RODATA = "Guardian Treasure";
static const u8 sJarOfGreedSortName[] APPEND_RODATA = "Jar of Greed";
static const u8 sMadSwordBeastSortName[] APPEND_RODATA = "Mad Sword Beast";
static const u8 sOjamaTrioSortName[] APPEND_RODATA = "Ojama Trio";
static const u8 sLusterDragonSortName[] APPEND_RODATA = "Luster Dragon";
static const u8 sMysticalShineBallSortName[] APPEND_RODATA = "Mystical Shine Ball";
static const u8 sGoblinThiefSortName[] APPEND_RODATA = "Goblin Thief";
static const u8 sHayabusaKnightSortName[] APPEND_RODATA = "Hayabusa Knight";
static const u8 sMagicCylinderSortName[] APPEND_RODATA = "Magic Cylinder";
static const u8 sBlockAttackSortName[] APPEND_RODATA = "Block Attack";
static const u8 sDelinquentDuoSortName[] APPEND_RODATA = "Delinquent Duo";
static const u8 sDrainingShieldSortName[] APPEND_RODATA = "Draining Shield";
static const u8 sMeteorOfDestructionSortName[] APPEND_RODATA = "Meteor of Destruction";
static const u8 sTollSortName[] APPEND_RODATA = "Toll";
static const u8 sRainOfMercySortName[] APPEND_RODATA = "Rain of Mercy";
static const u8 sSolarFlareDragonSortName[] APPEND_RODATA = "Solar Flare Dragon";
static const u8 sYataGarasuSortName[] APPEND_RODATA = "Yata-Garasu";
static const u8 sUpstartGoblinSortName[] APPEND_RODATA = "Upstart Goblin";
static const u8 sNegateAttackSortName[] APPEND_RODATA = "Negate Attack";
static const u8 sReloadSortName[] APPEND_RODATA = "Reload";
static const u8 sMaraudingCaptainSortName[] APPEND_RODATA = "Marauding Captain";
static const u8 sSecretBarrelSortName[] APPEND_RODATA = "Secret Barrel";
static const u8 sRobbinGoblinSortName[] APPEND_RODATA = "Robbin' Goblin";
static const u8 sRobbinZombieSortName[] APPEND_RODATA = "Robbin' Zombie";
static const u8 sCallOfTheHauntedSortName[] APPEND_RODATA = "Call of the Haunted";
static const u8 sKaiserGliderSortName[] APPEND_RODATA = "Kaiser Glider";
static const u8 sPiranhaArmySortName[] APPEND_RODATA = "Piranha Army";
static const u8 sMoisterCreatureSortName[] APPEND_RODATA = "Moister Creature";
static const u8 sWhiteMagicianPikeruSortName[] APPEND_RODATA = "White Magician Pikeru";
static const u8 sEbonMagicianCurranSortName[] APPEND_RODATA = "Ebon Magician Curran";
static const u8 sWeatherReportSortName[] APPEND_RODATA = "Weather Report";
static const u8 sWarriorOfZeraSortName[] APPEND_RODATA = "Warrior of Zera";
static const u8 sTimeSealSortName[] APPEND_RODATA = "Time Seal";
static const u8 sThousandEnergySortName[] APPEND_RODATA = "Thousand Energy";
static const u8 sTheDarkDoorSortName[] APPEND_RODATA = "The Dark Door";
static const u8 sSwiftGaiaTheFierceKnightSortName[] APPEND_RODATA = "Swift Gaia The Fierce Knight";
static const u8 sSelfDestructButtonSortName[] APPEND_RODATA = "Self-Destruct Button";
static const u8 sSkullInvitationSortName[] APPEND_RODATA = "Skull Invitation";
static const u8 sNightmareHorseSortName[] APPEND_RODATA = "Nightmare Horse";
static const u8 sVampireBabySortName[] APPEND_RODATA = "Vampire Baby";
static const u8 sTheForcefulSentrySortName[] APPEND_RODATA = "The Forceful Sentry";
static const u8 sTerrorkingSalmonSortName[] APPEND_RODATA = "Terrorking Salmon";
static const u8 sSasukeSamuraiSortName[] APPEND_RODATA = "Sasuke Samurai";
static const u8 sMaryokutaiSortName[] APPEND_RODATA = "Maryokutai";
static const u8 sMermaidKnightSortName[] APPEND_RODATA = "Mermaid Knight";
static const u8 sMefistTheInfernalGeneralSortName[] APPEND_RODATA = "Mefist The Infernal General";
static const u8 sGuardianAngelJoanSortName[] APPEND_RODATA = "Guardian Angel Joan";
static const u8 sPetenTheDarkClownSortName[] APPEND_RODATA = "Peten The Dark Clown";
static const u8 sLimiterRemovalSortName[] APPEND_RODATA = "Limiter Removal";
static const u8 sJustDesertsSortName[] APPEND_RODATA = "Just Deserts";
static const u8 sGilasaurusSortName[] APPEND_RODATA = "Gilasaurus";
static const u8 sGravityBindSortName[] APPEND_RODATA = "Gravity Bind";
static const u8 sGiftOfTheMysticalElfSortName[] APPEND_RODATA = "Gift Of The Mystical Elf";
static const u8 sRecklessGreedSortName[] APPEND_RODATA = "Reckless Greed";
static const u8 sAirknightParshathSortName[] APPEND_RODATA = "Airknight Parshath";
static const u8 sAmphibiousBugrothMk3SortName[] APPEND_RODATA = "Amphibious Bugroth MK-3";
static const u8 sBlackTyrannoSortName[] APPEND_RODATA = "Black Tyranno";
static const u8 sTheAgentOfCreationVenusSortName[] APPEND_RODATA = "The Agent Of Creation - Venus";
static const u8 sBlastingTheRuinsSortName[] APPEND_RODATA = "Blasting The Ruins";
static const u8 sCurseOfDarknessSortName[] APPEND_RODATA = "Curse Of Darkness";
static const u8 sCoffinSellerSortName[] APPEND_RODATA = "Coffin Seller";
static const u8 sCardDestructionSortName[] APPEND_RODATA = "Card Destruction";
static const u8 sDarkRoomOfNightmareSortName[] APPEND_RODATA = "Dark Room Of Nightmare";
static const u8 sDarkDriceratopsSortName[] APPEND_RODATA = "Dark Driceratops";
static const u8 sGracefulCharitySortName[] APPEND_RODATA = "Graceful Charity";
static const u8 sGreatMajuGarzettSortName[] APPEND_RODATA = "Great Maju Garzett";
static const u8 sTrianglePowerSortName[] APPEND_RODATA = "Triangle Power";
static const u8 sTwinSwordsOfFlashingLightTryceSortName[] APPEND_RODATA = "Twin Swords of Flashing Light - Tryce";
static const u8 sThousandKnivesSortName[] APPEND_RODATA = "Thousand Knives";
static const u8 sSoulTakerSortName[] APPEND_RODATA = "Soul Taker";
static const u8 sSolarRaySortName[] APPEND_RODATA = "Solar Ray";
static const u8 sSolemnWishesSortName[] APPEND_RODATA = "Solemn Wishes";
static const u8 sStealthBirdSortName[] APPEND_RODATA = "Stealth Bird";
static const u8 sNeedleBurrowerSortName[] APPEND_RODATA = "Needle Burrower";
static const u8 sKa2DesScissorsSortName[] APPEND_RODATA = "KA-2 Des Scissors";
static const u8 sImperialOrderSortName[] APPEND_RODATA = "Imperial Order";
static const u8 sGrenMajuDaEizaSortName[] APPEND_RODATA = "Gren Maju Da Eiza";
static const u8 sRoyalDecreeSortName[] APPEND_RODATA = "Royal Decree";
static const u8 sReaperOnTheNightmareSortName[] APPEND_RODATA = "Reaper on the Nightmare";
static const u8 sNegativeEnergySortName[] APPEND_RODATA = "Negative Energy";
static const u8 sMatazaTheZapperSortName[] APPEND_RODATA = "Mataza the Zapper";
static const u8 sDoubleCostonSortName[] APPEND_RODATA = "Double Coston";
static const u8 sPreciousCardsFromBeyondSortName[] APPEND_RODATA = "Precious Cards From Beyond";
static const u8 sTyrantDragonSortName[] APPEND_RODATA = "Tyrant Dragon";
static const u8 sFinalCountdownSortName[] APPEND_RODATA = "Final Countdown";
static const u8 sAbsorbingKidFromTheSkySortName[] APPEND_RODATA = "Absorbing Kid from the Sky";
static const u8 sArsenalBugSortName[] APPEND_RODATA = "Arsenal Bug";
static const u8 sBurningLandSortName[] APPEND_RODATA = "Burning Land";
static const u8 sBattleFootballerSortName[] APPEND_RODATA = "Battle Footballer";
static const u8 sDancingFairySortName[] APPEND_RODATA = "Dancing Fairy";
static const u8 sSpiritOfTheBreezeSortName[] APPEND_RODATA = "Spirit of the Breeze";
static const u8 sDropOffSortName[] APPEND_RODATA = "Drop Off";
static const u8 sGoblinKingSortName[] APPEND_RODATA = "Goblin King";
static const u8 sGranadoraSortName[] APPEND_RODATA = "Granadora";
static const u8 sHyperHammerheadSortName[] APPEND_RODATA = "Hyper Hammerhead";
static const u8 sGyakuGirePandaSortName[] APPEND_RODATA = "Gyaku-Gire Panda";
static const u8 sGracefulDiceSortName[] APPEND_RODATA = "Graceful Dice";
static const u8 sBerserkGorillaSortName[] APPEND_RODATA = "Berserk Gorilla";
static const u8 sChaosGreedSortName[] APPEND_RODATA = "Chaos Greed";
static const u8 sBookOfMoonSortName[] APPEND_RODATA = "Book of Moon";
static const u8 sBurningAlgaeSortName[] APPEND_RODATA = "Burning Algae";
static const u8 sDarklordMarieSortName[] APPEND_RODATA = "Darklord Marie";
static const u8 sFenrirSortName[] APPEND_RODATA = "Fenrir";
static const u8 sMagicalMerchantSortName[] APPEND_RODATA = "Magical Merchant";
static const u8 sRaregoldArmorSortName[] APPEND_RODATA = "Raregold Armor";
static const u8 sSpiritReaperSortName[] APPEND_RODATA = "Spirit Reaper";
static const u8 sThunderCrashSortName[] APPEND_RODATA = "Thunder Crash";
static const u8 sTorpedoFishSortName[] APPEND_RODATA = "Torpedo Fish";
static const u8 sSevenToolsOfTheBanditSortName[] APPEND_RODATA = "Seven Tools of the Bandit";
static const u8 sRivalryOfWarlordsSortName[] APPEND_RODATA = "Rivalry of Warlords";
static const u8 sRingOfDestructionSortName[] APPEND_RODATA = "Ring of Destruction";
static const u8 sSasukeSamurai2SortName[] APPEND_RODATA = "Sasuke Samurai #2";
static const u8 sSasukeSamurai3SortName[] APPEND_RODATA = "Sasuke Samurai #3";
static const u8 sServantOfCatabolismSortName[] APPEND_RODATA = "Servant of Catabolism";
static const u8 sManThroTroSortName[] APPEND_RODATA = "Man-Thro-Thro";
static const u8 sLevelLimitAreaBSortName[] APPEND_RODATA = "Level Limit Area B";
static const u8 sSpiritRyuSortName[] APPEND_RODATA = "Spirit Ryu";
static const u8 sAmazonessTigerSortName[] APPEND_RODATA = "Amazoness Tiger";
static const u8 sBlastHeldByATributeSortName[] APPEND_RODATA = "Blast Held by a Tribute";
static const u8 sDDWarriorSortName[] APPEND_RODATA = "D.D. Warrior";
static const u8 sConfiscationSortName[] APPEND_RODATA = "Confiscation";
static const u8 sBreakerTheMagicalWarriorSortName[] APPEND_RODATA = "Breaker the Magical Warrior";
static const u8 sDesKangarooSortName[] APPEND_RODATA = "Des Kangaroo";
static const u8 sDrillagoSortName[] APPEND_RODATA = "Drillago";
static const u8 sDarkSnakeSyndromeSortName[] APPEND_RODATA = "Dark Snake Syndrome";
static const u8 sJarRobberSortName[] APPEND_RODATA = "Jar Robber";
static const u8 sGravekeepersServantSortName[] APPEND_RODATA = "Gravekeeper's Servant";
static const u8 sDiceJarSortName[] APPEND_RODATA = "Dice Jar";
static const u8 sKnightsTitleSortName[] APPEND_RODATA = "Knight's Title";
static const u8 sJowlsOfDarkDemiseSortName[] APPEND_RODATA = "Jowls of Dark Demise";
static const u8 sKishidoSpiritSortName[] APPEND_RODATA = "Kishido Spirit";
static const u8 sPossessedDarkSoulSortName[] APPEND_RODATA = "Possessed Dark Soul";
static const u8 sRoyalKnightSortName[] APPEND_RODATA = "Royal Knight";
static const u8 sTheThingInTheCraterSortName[] APPEND_RODATA = "The Thing in the Crater";
static const u8 sCreatureSwapSortName[] APPEND_RODATA = "Creature Swap";
static const u8 sLesserFiendSortName[] APPEND_RODATA = "Lesser Fiend";
static const u8 sSpiritOfThePotOfGreedSortName[] APPEND_RODATA = "Spirit of the Pot of Greed";
static const u8 sZaborgTheThunderMonarchSortName[] APPEND_RODATA = "Zaborg the Thunder Monarch";
static const u8 sBottomlessShiftingSandSortName[] APPEND_RODATA = "Bottomless Shifting Sand";
static const u8 sFirePrincessSortName[] APPEND_RODATA = "Fire Princess";
static const u8 sInvaderOfTheThroneSortName[] APPEND_RODATA = "Invader of the Throne";
static const u8 sTheFluteOfSummoningDragonSortName[] APPEND_RODATA = "The Flute of Summoning Dragon";
static const u8 sSpiritCallerSortName[] APPEND_RODATA = "Spirit Caller";
static const u8 sVengefulBogSpiritSortName[] APPEND_RODATA = "Vengeful Bog Spirit";
static const u8 sWallOfRevealingLightSortName[] APPEND_RODATA = "Wall of Revealing Light";
static const u8 sWorldSuppressionSortName[] APPEND_RODATA = "World Suppression";
static const u8 sRyuKishinClownSortName[] APPEND_RODATA = "Ryu-Kishin Clown";
static const u8 sDarkDustSpiritSortName[] APPEND_RODATA = "Dark Dust Spirit";
static const u8 sGhostKnightOfJackalSortName[] APPEND_RODATA = "Ghost Knight of Jackal";
static const u8 sKaiserColosseumSortName[] APPEND_RODATA = "Kaiser Colosseum";
static const u8 sNightmareWheelSortName[] APPEND_RODATA = "Nightmare Wheel";
static const u8 sMirrorWallSortName[] APPEND_RODATA = "Mirror Wall";
static const u8 sMajuGarzettSortName[] APPEND_RODATA = "Maju Garzett";
static const u8 sDustTornadoSortName[] APPEND_RODATA = "Dust Tornado";
static const u8 sEctoplasmerSortName[] APPEND_RODATA = "Ectoplasmer";
static const u8 sLeviaDragonDaedalusSortName[] APPEND_RODATA = "Levia Dragon Daedalus";
static const u8 sThebanNightmareSortName[] APPEND_RODATA = "Theban Nightmare";
static const u8 sBigBangShotSortName[] APPEND_RODATA = "Big Bang Shot";
static const u8 sPolymerizationSortName[] APPEND_RODATA = "Polymerization";
static const u8 sCyberDragonSortName[] APPEND_RODATA = "Cyber Dragon";
static const u8 sCyberTwinDragonSortName[] APPEND_RODATA = "Cyber Twin Dragon";
static const u8 sCyberEndDragonSortName[] APPEND_RODATA = "Cyber End Dragon";
static const u8 sCaiusTheShadowMonarchSortName[] APPEND_RODATA = "Caius the Shadow Monarch";
static const u8 sMobiusTheFrostMonarchSortName[] APPEND_RODATA = "Mobius the Frost Monarch";
static const u8 sProtoCyberDragonSortName[] APPEND_RODATA = "Proto-Cyber Dragon";
static const u8 sAmazonessArcherSortName[] APPEND_RODATA = "Amazoness Archer";
static const u8 sElementalHeroAvianSortName[] APPEND_RODATA = "Elemental HERO Avian";
static const u8 sElementalHeroBurstinatrixSortName[] APPEND_RODATA = "Elemental HERO Burstinatrix";
static const u8 sElementalHeroSparkmanSortName[] APPEND_RODATA = "Elemental HERO Sparkman";
static const u8 sElementalHeroBubblemanSortName[] APPEND_RODATA = "Elemental HERO Bubbleman";
static const u8 sElementalHeroWildheartSortName[] APPEND_RODATA = "Elemental HERO Wildheart";
static const u8 sElementalHeroBladedgeSortName[] APPEND_RODATA = "Elemental HERO Bladedge";
static const u8 sElementalHeroClaymanSortName[] APPEND_RODATA = "Elemental HERO Clayman";

static const u16 sCustomCardsByName[NUM_CUSTOM_NAME_SORT_CARDS] APPEND_RODATA = {
  0x03A0, // Absorbing Kid from the Sky
  0x0381, // Airknight Parshath
  0x03F0, // Amazoness Archer
  0x03C0, // Amazoness Tiger
  0x0382, // Amphibious Bugroth MK-3
  0x033E, // Ancient Rules
  0x03A1, // Arsenal Bug
  0x03A3, // Battle Footballer
  0x03AC, // Berserk Gorilla
  0x03E8, // Big Bang Shot
  0x0383, // Black Tyranno
  0x03C1, // Blast Held by a Tribute
  0x0385, // Blasting The Ruins
  0x0354, // Block Attack
  0x033D, // Blue-Eyes Alternative White Dragon
  0x0329, // Blue-Eyes Chaos Max Dragon
  0x0324, // Blue-Eyes Shining Dragon
  0x03AE, // Book of Moon
  0x03D5, // Bottomless Shifting Sand
  0x0345, // Bowganian
  0x03C4, // Breaker the Magical Warrior
  0x03AF, // Burning Algae
  0x03A2, // Burning Land
  0x03ED, // Caius the Shadow Monarch
  0x0363, // Call of the Haunted
  0x0388, // Card Destruction
  0x0326, // Card Of Demise
  0x0327, // Card Of Sanctity
  0x0347, // Cat's Ear Tribe
  0x032A, // Chain Energy
  0x03AD, // Chaos Greed
  0x0387, // Coffin Seller
  0x03C3, // Confiscation
  0x032D, // Copycat
  0x033C, // Cost Down
  0x03D1, // Creature Swap
  0x0348, // Cure Mermaid
  0x0386, // Curse Of Darkness
  0x03EA, // Cyber Dragon
  0x03EC, // Cyber End Dragon
  0x03EB, // Cyber Twin Dragon
  0x03C2, // D.D. Warrior
  0x03A4, // Dancing Fairy
  0x038A, // Dark Driceratops
  0x03DE, // Dark Dust Spirit
  0x0346, // Dark Magic Curtain
  0x0389, // Dark Room Of Nightmare
  0x03C7, // Dark Snake Syndrome
  0x03B0, // Darklord Marie
  0x0322, // Deck Destruction Virus
  0x0355, // Delinquent Duo
  0x03C5, // Des Kangaroo
  0x0349, // Des Koala
  0x03CA, // Dice Jar
  0x039C, // Double Coston
  0x0338, // Double Summon
  0x0356, // Draining Shield
  0x03C6, // Drillago
  0x03A6, // Drop Off
  0x03E4, // Dust Tornado
  0x0368, // Ebon Magician Curran
  0x03E5, // Ectoplasmer
  0x03F1, // Elemental HERO Avian
  0x03F6, // Elemental HERO Bladedge
  0x03F4, // Elemental HERO Bubbleman
  0x03F2, // Elemental HERO Burstinatrix
  0x03F7, // Elemental HERO Clayman
  0x03F3, // Elemental HERO Sparkman
  0x03F5, // Elemental HERO Wildheart
  0x032C, // Exchange
  0x033B, // Fairy Box
  0x0341, // Familiar Knight
  0x03B1, // Fenrir
  0x039F, // Final Countdown
  0x03D6, // Fire Princess
  0x03DF, // Ghost Knight of Jackal
  0x037F, // Gift Of The Mystical Elf
  0x037D, // Gilasaurus
  0x03A7, // Goblin King
  0x0351, // Goblin Thief
  0x038B, // Graceful Charity
  0x03AB, // Graceful Dice
  0x03A8, // Granadora
  0x03C9, // Gravekeeper's Servant
  0x037E, // Gravity Bind
  0x038C, // Great Maju Garzett
  0x0397, // Gren Maju Da Eiza
  0x0379, // Guardian Angel Joan
  0x034B, // Guardian Treasure
  0x03AA, // Gyaku-Gire Panda
  0x0352, // Hayabusa Knight
  0x03A9, // Hyper Hammerhead
  0x0396, // Imperial Order
  0x03D7, // Invader of the Throne
  0x034C, // Jar of Greed
  0x03C8, // Jar Robber
  0x03CC, // Jowls of Dark Demise
  0x037C, // Just Deserts
  0x0395, // KA-2 Des Scissors
  0x032F, // Kaibaman
  0x03E0, // Kaiser Colosseum
  0x0364, // Kaiser Glider
  0x03CD, // Kishido Spirit
  0x03CB, // Knight's Title
  0x03D2, // Lesser Fiend
  0x03BE, // Level Limit Area B
  0x03E6, // Levia Dragon Daedalus
  0x037B, // Limiter Removal
  0x034F, // Luster Dragon
  0x034D, // Mad Sword Beast
  0x032E, // Mage Power
  0x0353, // Magic Cylinder
  0x033F, // Magic Jammer
  0x03B2, // Magical Merchant
  0x0323, // Magician's Valkyria
  0x03E3, // Maju Garzett
  0x03BD, // Man-Thro-Thro
  0x035F, // Marauding Captain
  0x0376, // Maryokutai
  0x033A, // Mask of Restrict
  0x039B, // Mataza the Zapper
  0x0378, // Mefist The Infernal General
  0x0377, // Mermaid Knight
  0x0357, // Meteor of Destruction
  0x03E2, // Mirror Wall
  0x03EE, // Mobius the Frost Monarch
  0x0366, // Moister Creature
  0x0350, // Mystical Shine Ball
  0x0336, // Mystical Space Typhoon
  0x0394, // Needle Burrower
  0x035D, // Negate Attack
  0x039A, // Negative Energy
  0x0371, // Nightmare Horse
  0x03E1, // Nightmare Wheel
  0x0339, // Obnoxious Celtic Guardian
  0x034E, // Ojama Trio
  0x0325, // Paladin Of White Dragon
  0x037A, // Peten The Dark Clown
  0x0365, // Piranha Army
  0x03E9, // Polymerization
  0x03CE, // Possessed Dark Soul
  0x039D, // Precious Cards From Beyond
  0x03EF, // Proto-Cyber Dragon
  0x0334, // Pyramid of Light
  0x0359, // Rain of Mercy
  0x0337, // Rare Metal Dragon
  0x03B3, // Raregold Armor
  0x0399, // Reaper on the Nightmare
  0x0380, // Reckless Greed
  0x035E, // Reload
  0x03B9, // Ring of Destruction
  0x0342, // Riryoku
  0x03B8, // Rivalry of Warlords
  0x0361, // Robbin' Goblin
  0x0362, // Robbin' Zombie
  0x0398, // Royal Decree
  0x03CF, // Royal Knight
  0x03DD, // Ryu-Kishin Clown
  0x0344, // Sage's Stone
  0x0375, // Sasuke Samurai
  0x03BA, // Sasuke Samurai #2
  0x03BB, // Sasuke Samurai #3
  0x0340, // Seal of Orichalcos
  0x0360, // Secret Barrel
  0x036F, // Self-Destruct Button
  0x03BC, // Servant of Catabolism
  0x03B7, // Seven Tools of the Bandit
  0x0328, // Shield And Sword
  0x034A, // Skill Drain
  0x0370, // Skull Invitation
  0x035A, // Solar Flare Dragon
  0x0391, // Solar Ray
  0x0392, // Solemn Wishes
  0x0321, // Sorcerer of Dark Magic
  0x0335, // Soul Exchange
  0x0390, // Soul Taker
  0x0343, // Spear Dragon
  0x032B, // Spell Canceller
  0x03D9, // Spirit Caller
  0x03A5, // Spirit of the Breeze
  0x03D3, // Spirit of the Pot of Greed
  0x03B4, // Spirit Reaper
  0x03BF, // Spirit Ryu
  0x0333, // St Joan
  0x0393, // Stealth Bird
  0x036E, // Swift Gaia The Fierce Knight
  0x0374, // Terrorking Salmon
  0x0384, // The Agent Of Creation - Venus
  0x036D, // The Dark Door
  0x03D8, // The Flute of Summoning Dragon
  0x0373, // The Forceful Sentry
  0x03D0, // The Thing in the Crater
  0x03E7, // Theban Nightmare
  0x036C, // Thousand Energy
  0x038F, // Thousand Knives
  0x03B5, // Thunder Crash
  0x036B, // Time Seal
  0x0358, // Toll
  0x03B6, // Torpedo Fish
  0x038D, // Triangle Power
  0x038E, // Twin Swords of Flashing Light - Tryce
  0x039E, // Tyrant Dragon
  0x0330, // Ultimate Offering
  0x0331, // United We Stand
  0x035C, // Upstart Goblin
  0x0372, // Vampire Baby
  0x03DA, // Vengeful Bog Spirit
  0x03DB, // Wall of Revealing Light
  0x036A, // Warrior of Zera
  0x0332, // Wave Motion Cannon
  0x0369, // Weather Report
  0x0367, // White Magician Pikeru
  0x03DC, // World Suppression
  0x035B, // Yata-Garasu
  0x03D4, // Zaborg the Thunder Monarch
};

static const u16 sCustomCardNameSortOrder[NUM_CUSTOM_NAME_SORT_CARDS] APPEND_RODATA = {
  1, // Absorbing Kid from the Sky
  2, // Airknight Parshath
  3, // Amazoness Archer
  4, // Amazoness Tiger
  5, // Amphibious Bugroth MK-3
  6, // Ancient Rules
  7, // Arsenal Bug
  8, // Battle Footballer
  9, // Berserk Gorilla
  10, // Big Bang Shot
  11, // Black Tyranno
  12, // Blast Held by a Tribute
  13, // Blasting The Ruins
  14, // Block Attack
  15, // Blue-Eyes Alternative White Dragon
  16, // Blue-Eyes Chaos Max Dragon
  17, // Blue-Eyes Shining Dragon
  18, // Book of Moon
  19, // Bottomless Shifting Sand
  20, // Bowganian
  21, // Breaker the Magical Warrior
  22, // Burning Algae
  23, // Burning Land
  24, // Caius the Shadow Monarch
  25, // Call of the Haunted
  26, // Card Destruction
  27, // Card Of Demise
  28, // Card Of Sanctity
  29, // Cat's Ear Tribe
  30, // Chain Energy
  31, // Chaos Greed
  32, // Coffin Seller
  33, // Confiscation
  34, // Copycat
  35, // Cost Down
  36, // Creature Swap
  37, // Cure Mermaid
  38, // Curse Of Darkness
  39, // Cyber Dragon
  40, // Cyber End Dragon
  41, // Cyber Twin Dragon
  42, // D.D. Warrior
  43, // Dancing Fairy
  44, // Dark Driceratops
  45, // Dark Dust Spirit
  46, // Dark Magic Curtain
  47, // Dark Room Of Nightmare
  48, // Dark Snake Syndrome
  49, // Darklord Marie
  50, // Deck Destruction Virus
  51, // Delinquent Duo
  52, // Des Kangaroo
  53, // Des Koala
  54, // Dice Jar
  55, // Double Coston
  56, // Double Summon
  57, // Draining Shield
  58, // Drillago
  59, // Drop Off
  60, // Dust Tornado
  61, // Ebon Magician Curran
  62, // Ectoplasmer
  63, // Elemental HERO Avian
  64, // Elemental HERO Bladedge
  65, // Elemental HERO Bubbleman
  66, // Elemental HERO Burstinatrix
  67, // Elemental HERO Clayman
  68, // Elemental HERO Sparkman
  69, // Elemental HERO Wildheart
  70, // Exchange
  71, // Fairy Box
  72, // Familiar Knight
  73, // Fenrir
  74, // Final Countdown
  75, // Fire Princess
  76, // Ghost Knight of Jackal
  77, // Gift Of The Mystical Elf
  78, // Gilasaurus
  79, // Goblin King
  80, // Goblin Thief
  81, // Graceful Charity
  82, // Graceful Dice
  83, // Granadora
  84, // Gravekeeper's Servant
  85, // Gravity Bind
  86, // Great Maju Garzett
  87, // Gren Maju Da Eiza
  88, // Guardian Angel Joan
  89, // Guardian Treasure
  90, // Gyaku-Gire Panda
  91, // Hayabusa Knight
  92, // Hyper Hammerhead
  93, // Imperial Order
  94, // Invader of the Throne
  95, // Jar of Greed
  96, // Jar Robber
  97, // Jowls of Dark Demise
  98, // Just Deserts
  99, // KA-2 Des Scissors
  100, // Kaibaman
  101, // Kaiser Colosseum
  102, // Kaiser Glider
  103, // Kishido Spirit
  104, // Knight's Title
  105, // Lesser Fiend
  106, // Level Limit Area B
  107, // Levia Dragon Daedalus
  108, // Limiter Removal
  109, // Luster Dragon
  110, // Mad Sword Beast
  111, // Mage Power
  112, // Magic Cylinder
  113, // Magic Jammer
  114, // Magical Merchant
  115, // Magician's Valkyria
  116, // Maju Garzett
  117, // Man-Thro-Thro
  118, // Marauding Captain
  119, // Maryokutai
  120, // Mask of Restrict
  121, // Mataza the Zapper
  122, // Mefist The Infernal General
  123, // Mermaid Knight
  124, // Meteor of Destruction
  125, // Mirror Wall
  126, // Mobius the Frost Monarch
  127, // Moister Creature
  128, // Mystical Shine Ball
  129, // Mystical Space Typhoon
  130, // Needle Burrower
  131, // Negate Attack
  132, // Negative Energy
  133, // Nightmare Horse
  134, // Nightmare Wheel
  135, // Obnoxious Celtic Guardian
  136, // Ojama Trio
  137, // Paladin Of White Dragon
  138, // Peten The Dark Clown
  139, // Piranha Army
  140, // Polymerization
  141, // Possessed Dark Soul
  142, // Precious Cards From Beyond
  143, // Proto-Cyber Dragon
  144, // Pyramid of Light
  145, // Rain of Mercy
  146, // Rare Metal Dragon
  147, // Raregold Armor
  148, // Reaper on the Nightmare
  149, // Reckless Greed
  150, // Reload
  151, // Ring of Destruction
  152, // Riryoku
  153, // Rivalry of Warlords
  154, // Robbin' Goblin
  155, // Robbin' Zombie
  156, // Royal Decree
  157, // Royal Knight
  158, // Ryu-Kishin Clown
  159, // Sage's Stone
  160, // Sasuke Samurai
  161, // Sasuke Samurai #2
  162, // Sasuke Samurai #3
  163, // Seal of Orichalcos
  164, // Secret Barrel
  165, // Self-Destruct Button
  166, // Servant of Catabolism
  167, // Seven Tools of the Bandit
  168, // Shield And Sword
  169, // Skill Drain
  170, // Skull Invitation
  171, // Solar Flare Dragon
  172, // Solar Ray
  173, // Solemn Wishes
  174, // Sorcerer of Dark Magic
  175, // Soul Exchange
  176, // Soul Taker
  177, // Spear Dragon
  178, // Spell Canceller
  179, // Spirit Caller
  180, // Spirit of the Breeze
  181, // Spirit of the Pot of Greed
  182, // Spirit Reaper
  183, // Spirit Ryu
  184, // St Joan
  185, // Stealth Bird
  186, // Swift Gaia The Fierce Knight
  187, // Terrorking Salmon
  188, // The Agent Of Creation - Venus
  189, // The Dark Door
  190, // The Flute of Summoning Dragon
  191, // The Forceful Sentry
  192, // The Thing in the Crater
  193, // Theban Nightmare
  194, // Thousand Energy
  195, // Thousand Knives
  196, // Thunder Crash
  197, // Time Seal
  198, // Toll
  199, // Torpedo Fish
  200, // Triangle Power
  201, // Twin Swords of Flashing Light - Tryce
  202, // Tyrant Dragon
  203, // Ultimate Offering
  204, // United We Stand
  205, // Upstart Goblin
  206, // Vampire Baby
  207, // Vengeful Bog Spirit
  208, // Wall of Revealing Light
  209, // Warrior of Zera
  210, // Wave Motion Cannon
  211, // Weather Report
  212, // White Magician Pikeru
  213, // World Suppression
  214, // Yata-Garasu
  215, // Zaborg the Thunder Monarch
};

static u8 *GetSortCardName(u16 cardId) {
  if (cardId == 0x021B)
    return (u8 *)sAmazonChainMasterSortName;
  if (cardId == 0x0276)
    return (u8 *)sAmazonFighterSortName;
  if (cardId == 0x0279)
    return (u8 *)sAmazonSwordWomanSortName;
  if (cardId == 0x0321)
    return (u8 *)sSorcererOfDarkMagicSortName;
  if (cardId == 0x0322)
    return (u8 *)sDeckDestructionVirusSortName;
  if (cardId == 0x0323)
    return (u8 *)sMagiciansValkyriaSortName;
  if (cardId == 0x0324)
    return (u8 *)sBlueEyesShiningDragonSortName;
  if (cardId == 0x0325)
    return (u8 *)sPaladinOfWhiteDragonSortName;
  if (cardId == 0x0326)
    return (u8 *)sCardOfDemiseSortName;
  if (cardId == 0x0327)
    return (u8 *)sCardOfSanctitySortName;
  if (cardId == 0x0328)
    return (u8 *)sShieldAndSwordSortName;
  if (cardId == 0x0329)
    return (u8 *)sBlueEyesChaosMaxDragonSortName;
  if (cardId == 0x032A)
    return (u8 *)sChainEnergySortName;
  if (cardId == 0x032B)
    return (u8 *)sSpellCancellerSortName;
  if (cardId == 0x032C)
    return (u8 *)sExchangeSortName;
  if (cardId == 0x032D)
    return (u8 *)sCopycatSortName;
  if (cardId == 0x032E)
    return (u8 *)sMagePowerSortName;
  if (cardId == 0x032F)
    return (u8 *)sKaibamanSortName;
  if (cardId == 0x0330)
    return (u8 *)sUltimateOfferingSortName;
  if (cardId == 0x0331)
    return (u8 *)sUnitedWeStandSortName;
  if (cardId == 0x0332)
    return (u8 *)sWaveMotionCannonSortName;
  if (cardId == 0x0333)
    return (u8 *)sStJoanSortName;
  if (cardId == 0x0334)
    return (u8 *)sPyramidOfLightSortName;
  if (cardId == 0x0335)
    return (u8 *)sSoulExchangeSortName;
  if (cardId == 0x0336)
    return (u8 *)sMysticalSpaceTyphoonSortName;
  if (cardId == 0x0337)
    return (u8 *)sRareMetalDragonSortName;
  if (cardId == 0x0338)
    return (u8 *)sDoubleSummonSortName;
  if (cardId == 0x0339)
    return (u8 *)sObnoxiousCelticGuardianSortName;
  if (cardId == 0x033A)
    return (u8 *)sMaskOfRestrictSortName;
  if (cardId == 0x033B)
    return (u8 *)sFairyBoxSortName;
  if (cardId == 0x033C)
    return (u8 *)sCostDownSortName;
  if (cardId == 0x033D)
    return (u8 *)sBlueEyesAlternativeWhiteDragonSortName;
  if (cardId == 0x033E)
    return (u8 *)sAncientRulesSortName;
  if (cardId == 0x033F)
    return (u8 *)sMagicJammerSortName;
  if (cardId == 0x0340)
    return (u8 *)sSealOfOrichalcosSortName;
  if (cardId == 0x0341)
    return (u8 *)sFamiliarKnightSortName;
  if (cardId == 0x0342)
    return (u8 *)sRiryokuSortName;
  if (cardId == 0x0343)
    return (u8 *)sSpearDragonSortName;
  if (cardId == 0x0344)
    return (u8 *)sSagesStoneSortName;
  if (cardId == 0x0345)
    return (u8 *)sBowganianSortName;
  if (cardId == 0x0346)
    return (u8 *)sDarkMagicCurtainSortName;
  if (cardId == 0x0347)
    return (u8 *)sCatsEarTribeSortName;
  if (cardId == 0x0348)
    return (u8 *)sCureMermaidSortName;
  if (cardId == 0x0349)
    return (u8 *)sDesKoalaSortName;
  if (cardId == 0x034A)
    return (u8 *)sSkillDrainSortName;
  if (cardId == 0x034B)
    return (u8 *)sGuardianTreasureSortName;
  if (cardId == 0x034C)
    return (u8 *)sJarOfGreedSortName;
  if (cardId == 0x034D)
    return (u8 *)sMadSwordBeastSortName;
  if (cardId == 0x034E)
    return (u8 *)sOjamaTrioSortName;
  if (cardId == 0x034F)
    return (u8 *)sLusterDragonSortName;
  if (cardId == 0x0350)
    return (u8 *)sMysticalShineBallSortName;
  if (cardId == 0x0351)
    return (u8 *)sGoblinThiefSortName;
  if (cardId == 0x0352)
    return (u8 *)sHayabusaKnightSortName;
  if (cardId == 0x0353)
    return (u8 *)sMagicCylinderSortName;
  if (cardId == 0x0354)
    return (u8 *)sBlockAttackSortName;
  if (cardId == 0x0355)
    return (u8 *)sDelinquentDuoSortName;
  if (cardId == 0x0356)
    return (u8 *)sDrainingShieldSortName;
  if (cardId == 0x0357)
    return (u8 *)sMeteorOfDestructionSortName;
  if (cardId == 0x0358)
    return (u8 *)sTollSortName;
  if (cardId == 0x0359)
    return (u8 *)sRainOfMercySortName;
  if (cardId == 0x035A)
    return (u8 *)sSolarFlareDragonSortName;
  if (cardId == 0x035B)
    return (u8 *)sYataGarasuSortName;
  if (cardId == 0x035C)
    return (u8 *)sUpstartGoblinSortName;
  if (cardId == 0x035D)
    return (u8 *)sNegateAttackSortName;
  if (cardId == 0x035E)
    return (u8 *)sReloadSortName;
  if (cardId == 0x035F)
    return (u8 *)sMaraudingCaptainSortName;
  if (cardId == 0x0360)
    return (u8 *)sSecretBarrelSortName;
  if (cardId == 0x0361)
    return (u8 *)sRobbinGoblinSortName;
  if (cardId == 0x0362)
    return (u8 *)sRobbinZombieSortName;
  if (cardId == 0x0363)
    return (u8 *)sCallOfTheHauntedSortName;
  if (cardId == 0x0364)
    return (u8 *)sKaiserGliderSortName;
  if (cardId == 0x0365)
    return (u8 *)sPiranhaArmySortName;
  if (cardId == 0x0366)
    return (u8 *)sMoisterCreatureSortName;
  if (cardId == 0x0367)
    return (u8 *)sWhiteMagicianPikeruSortName;
  if (cardId == 0x0368)
    return (u8 *)sEbonMagicianCurranSortName;
  if (cardId == 0x0369)
    return (u8 *)sWeatherReportSortName;
  if (cardId == 0x036A)
    return (u8 *)sWarriorOfZeraSortName;
  if (cardId == 0x036B)
    return (u8 *)sTimeSealSortName;
  if (cardId == 0x036C)
    return (u8 *)sThousandEnergySortName;
  if (cardId == 0x036D)
    return (u8 *)sTheDarkDoorSortName;
  if (cardId == 0x036E)
    return (u8 *)sSwiftGaiaTheFierceKnightSortName;
  if (cardId == 0x036F)
    return (u8 *)sSelfDestructButtonSortName;
  if (cardId == 0x0370)
    return (u8 *)sSkullInvitationSortName;
  if (cardId == 0x0371)
    return (u8 *)sNightmareHorseSortName;
  if (cardId == 0x0372)
    return (u8 *)sVampireBabySortName;
  if (cardId == 0x0373)
    return (u8 *)sTheForcefulSentrySortName;
  if (cardId == 0x0374)
    return (u8 *)sTerrorkingSalmonSortName;
  if (cardId == 0x0375)
    return (u8 *)sSasukeSamuraiSortName;
  if (cardId == 0x0376)
    return (u8 *)sMaryokutaiSortName;
  if (cardId == 0x0377)
    return (u8 *)sMermaidKnightSortName;
  if (cardId == 0x0378)
    return (u8 *)sMefistTheInfernalGeneralSortName;
  if (cardId == 0x0379)
    return (u8 *)sGuardianAngelJoanSortName;
  if (cardId == 0x037A)
    return (u8 *)sPetenTheDarkClownSortName;
  if (cardId == 0x037B)
    return (u8 *)sLimiterRemovalSortName;
  if (cardId == 0x037C)
    return (u8 *)sJustDesertsSortName;
  if (cardId == 0x037D)
    return (u8 *)sGilasaurusSortName;
  if (cardId == 0x037E)
    return (u8 *)sGravityBindSortName;
  if (cardId == 0x037F)
    return (u8 *)sGiftOfTheMysticalElfSortName;
  if (cardId == 0x0380)
    return (u8 *)sRecklessGreedSortName;
  if (cardId == 0x0381)
    return (u8 *)sAirknightParshathSortName;
  if (cardId == 0x0382)
    return (u8 *)sAmphibiousBugrothMk3SortName;
  if (cardId == 0x0383)
    return (u8 *)sBlackTyrannoSortName;
  if (cardId == 0x0384)
    return (u8 *)sTheAgentOfCreationVenusSortName;
  if (cardId == 0x0385)
    return (u8 *)sBlastingTheRuinsSortName;
  if (cardId == 0x0386)
    return (u8 *)sCurseOfDarknessSortName;
  if (cardId == 0x0387)
    return (u8 *)sCoffinSellerSortName;
  if (cardId == 0x0388)
    return (u8 *)sCardDestructionSortName;
  if (cardId == 0x0389)
    return (u8 *)sDarkRoomOfNightmareSortName;
  if (cardId == 0x038A)
    return (u8 *)sDarkDriceratopsSortName;
  if (cardId == 0x038B)
    return (u8 *)sGracefulCharitySortName;
  if (cardId == 0x038C)
    return (u8 *)sGreatMajuGarzettSortName;
  if (cardId == 0x038D)
    return (u8 *)sTrianglePowerSortName;
  if (cardId == 0x038E)
    return (u8 *)sTwinSwordsOfFlashingLightTryceSortName;
  if (cardId == 0x038F)
    return (u8 *)sThousandKnivesSortName;
  if (cardId == 0x0390)
    return (u8 *)sSoulTakerSortName;
  if (cardId == 0x0391)
    return (u8 *)sSolarRaySortName;
  if (cardId == 0x0392)
    return (u8 *)sSolemnWishesSortName;
  if (cardId == 0x0393)
    return (u8 *)sStealthBirdSortName;
  if (cardId == 0x0394)
    return (u8 *)sNeedleBurrowerSortName;
  if (cardId == 0x0395)
    return (u8 *)sKa2DesScissorsSortName;
  if (cardId == 0x0396)
    return (u8 *)sImperialOrderSortName;
  if (cardId == 0x0397)
    return (u8 *)sGrenMajuDaEizaSortName;
  if (cardId == 0x0398)
    return (u8 *)sRoyalDecreeSortName;
  if (cardId == 0x0399)
    return (u8 *)sReaperOnTheNightmareSortName;
  if (cardId == 0x039A)
    return (u8 *)sNegativeEnergySortName;
  if (cardId == 0x039B)
    return (u8 *)sMatazaTheZapperSortName;
  if (cardId == 0x039C)
    return (u8 *)sDoubleCostonSortName;
  if (cardId == 0x039D)
    return (u8 *)sPreciousCardsFromBeyondSortName;
  if (cardId == 0x039E)
    return (u8 *)sTyrantDragonSortName;
  if (cardId == 0x039F)
    return (u8 *)sFinalCountdownSortName;
  if (cardId == 0x03A0)
    return (u8 *)sAbsorbingKidFromTheSkySortName;
  if (cardId == 0x03A1)
    return (u8 *)sArsenalBugSortName;
  if (cardId == 0x03A2)
    return (u8 *)sBurningLandSortName;
  if (cardId == 0x03A3)
    return (u8 *)sBattleFootballerSortName;
  if (cardId == 0x03A4)
    return (u8 *)sDancingFairySortName;
  if (cardId == 0x03A5)
    return (u8 *)sSpiritOfTheBreezeSortName;
  if (cardId == 0x03A6)
    return (u8 *)sDropOffSortName;
  if (cardId == 0x03A7)
    return (u8 *)sGoblinKingSortName;
  if (cardId == 0x03A8)
    return (u8 *)sGranadoraSortName;
  if (cardId == 0x03A9)
    return (u8 *)sHyperHammerheadSortName;
  if (cardId == 0x03AA)
    return (u8 *)sGyakuGirePandaSortName;
  if (cardId == 0x03AB)
    return (u8 *)sGracefulDiceSortName;
  if (cardId == 0x03AC)
    return (u8 *)sBerserkGorillaSortName;
  if (cardId == 0x03AD)
    return (u8 *)sChaosGreedSortName;
  if (cardId == 0x03AE)
    return (u8 *)sBookOfMoonSortName;
  if (cardId == 0x03AF)
    return (u8 *)sBurningAlgaeSortName;
  if (cardId == 0x03B0)
    return (u8 *)sDarklordMarieSortName;
  if (cardId == 0x03B1)
    return (u8 *)sFenrirSortName;
  if (cardId == 0x03B2)
    return (u8 *)sMagicalMerchantSortName;
  if (cardId == 0x03B3)
    return (u8 *)sRaregoldArmorSortName;
  if (cardId == 0x03B4)
    return (u8 *)sSpiritReaperSortName;
  if (cardId == 0x03B5)
    return (u8 *)sThunderCrashSortName;
  if (cardId == 0x03B6)
    return (u8 *)sTorpedoFishSortName;
  if (cardId == 0x03B7)
    return (u8 *)sSevenToolsOfTheBanditSortName;
  if (cardId == 0x03B8)
    return (u8 *)sRivalryOfWarlordsSortName;
  if (cardId == 0x03B9)
    return (u8 *)sRingOfDestructionSortName;
  if (cardId == 0x03BA)
    return (u8 *)sSasukeSamurai2SortName;
  if (cardId == 0x03BB)
    return (u8 *)sSasukeSamurai3SortName;
  if (cardId == 0x03BC)
    return (u8 *)sServantOfCatabolismSortName;
  if (cardId == 0x03BD)
    return (u8 *)sManThroTroSortName;
  if (cardId == 0x03BE)
    return (u8 *)sLevelLimitAreaBSortName;
  if (cardId == 0x03BF)
    return (u8 *)sSpiritRyuSortName;
  if (cardId == 0x03C0)
    return (u8 *)sAmazonessTigerSortName;
  if (cardId == 0x03C1)
    return (u8 *)sBlastHeldByATributeSortName;
  if (cardId == 0x03C2)
    return (u8 *)sDDWarriorSortName;
  if (cardId == 0x03C3)
    return (u8 *)sConfiscationSortName;
  if (cardId == 0x03C4)
    return (u8 *)sBreakerTheMagicalWarriorSortName;
  if (cardId == 0x03C5)
    return (u8 *)sDesKangarooSortName;
  if (cardId == 0x03C6)
    return (u8 *)sDrillagoSortName;
  if (cardId == 0x03C7)
    return (u8 *)sDarkSnakeSyndromeSortName;
  if (cardId == 0x03C8)
    return (u8 *)sJarRobberSortName;
  if (cardId == 0x03C9)
    return (u8 *)sGravekeepersServantSortName;
  if (cardId == 0x03CA)
    return (u8 *)sDiceJarSortName;
  if (cardId == 0x03CB)
    return (u8 *)sKnightsTitleSortName;
  if (cardId == 0x03CC)
    return (u8 *)sJowlsOfDarkDemiseSortName;
  if (cardId == 0x03CD)
    return (u8 *)sKishidoSpiritSortName;
  if (cardId == 0x03CE)
    return (u8 *)sPossessedDarkSoulSortName;
  if (cardId == 0x03CF)
    return (u8 *)sRoyalKnightSortName;
  if (cardId == 0x03D0)
    return (u8 *)sTheThingInTheCraterSortName;
  if (cardId == 0x03D1)
    return (u8 *)sCreatureSwapSortName;
  if (cardId == 0x03D2)
    return (u8 *)sLesserFiendSortName;
  if (cardId == 0x03D3)
    return (u8 *)sSpiritOfThePotOfGreedSortName;
  if (cardId == 0x03D4)
    return (u8 *)sZaborgTheThunderMonarchSortName;
  if (cardId == 0x03D5)
    return (u8 *)sBottomlessShiftingSandSortName;
  if (cardId == 0x03D6)
    return (u8 *)sFirePrincessSortName;
  if (cardId == 0x03D7)
    return (u8 *)sInvaderOfTheThroneSortName;
  if (cardId == 0x03D8)
    return (u8 *)sTheFluteOfSummoningDragonSortName;
  if (cardId == 0x03D9)
    return (u8 *)sSpiritCallerSortName;
  if (cardId == 0x03DA)
    return (u8 *)sVengefulBogSpiritSortName;
  if (cardId == 0x03DB)
    return (u8 *)sWallOfRevealingLightSortName;
  if (cardId == 0x03DC)
    return (u8 *)sWorldSuppressionSortName;
  if (cardId == 0x03DD)
    return (u8 *)sRyuKishinClownSortName;
  if (cardId == 0x03DE)
    return (u8 *)sDarkDustSpiritSortName;
  if (cardId == 0x03DF)
    return (u8 *)sGhostKnightOfJackalSortName;
  if (cardId == 0x03E0)
    return (u8 *)sKaiserColosseumSortName;
  if (cardId == 0x03E1)
    return (u8 *)sNightmareWheelSortName;
  if (cardId == 0x03E2)
    return (u8 *)sMirrorWallSortName;
  if (cardId == 0x03E3)
    return (u8 *)sMajuGarzettSortName;
  if (cardId == 0x03E4)
    return (u8 *)sDustTornadoSortName;
  if (cardId == 0x03E5)
    return (u8 *)sEctoplasmerSortName;
  if (cardId == 0x03E6)
    return (u8 *)sLeviaDragonDaedalusSortName;
  if (cardId == 0x03E7)
    return (u8 *)sThebanNightmareSortName;
  if (cardId == 0x03E8)
    return (u8 *)sBigBangShotSortName;
  if (cardId == 0x03E9)
    return (u8 *)sPolymerizationSortName;
  if (cardId == 0x03EA)
    return (u8 *)sCyberDragonSortName;
  if (cardId == 0x03EB)
    return (u8 *)sCyberTwinDragonSortName;
  if (cardId == 0x03EC)
    return (u8 *)sCyberEndDragonSortName;
  if (cardId == 0x03ED)
    return (u8 *)sCaiusTheShadowMonarchSortName;
  if (cardId == 0x03EE)
    return (u8 *)sMobiusTheFrostMonarchSortName;
  if (cardId == 0x03EF)
    return (u8 *)sProtoCyberDragonSortName;
  if (cardId == 0x03F0)
    return (u8 *)sAmazonessArcherSortName;
  if (cardId == 0x03F1)
    return (u8 *)sElementalHeroAvianSortName;
  if (cardId == 0x03F2)
    return (u8 *)sElementalHeroBurstinatrixSortName;
  if (cardId == 0x03F3)
    return (u8 *)sElementalHeroSparkmanSortName;
  if (cardId == 0x03F4)
    return (u8 *)sElementalHeroBubblemanSortName;
  if (cardId == 0x03F5)
    return (u8 *)sElementalHeroWildheartSortName;
  if (cardId == 0x03F6)
    return (u8 *)sElementalHeroBladedgeSortName;
  if (cardId == 0x03F7)
    return (u8 *)sElementalHeroClaymanSortName;

  return gCardNames[cardId];
}

static u16 GetCustomCardNameSortOrder(u16 cardId) {
  u16 i;

  for (i = 0; i < NUM_CUSTOM_NAME_SORT_CARDS; i++)
    if (sCustomCardsByName[i] == cardId)
      return sCustomCardNameSortOrder[i];

  return 0;
}
