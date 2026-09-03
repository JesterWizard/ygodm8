#include "global.h"

#define NUM_CUSTOM_NAME_SORT_CARDS 207

static const u8 sAmazonChainMasterSortName[] APPEND_RODATA = "Amazoness Chain Master";
static const u8 sAmazonFighterSortName[] APPEND_RODATA = "Amazoness Fighter";
static const u8 sAmazonSwordWomanSortName[] APPEND_RODATA = "Amazoness Sword Woman";
static const u8 sBlueEyesShiningDragonSortName[] APPEND_RODATA = "Blue-Eyes Shining Dragon";
static const u8 sBlueEyesChaosMaxDragonSortName[] APPEND_RODATA = "Blue-Eyes Chaos Max Dragon";
static const u8 sKaibamanSortName[] APPEND_RODATA = "Kaibaman";
static const u8 sUltimateOfferingSortName[] APPEND_RODATA = "Ultimate Offering";
static const u8 sWaveMotionCannonSortName[] APPEND_RODATA = "Wave Motion Cannon";
static const u8 sSoulExchangeSortName[] APPEND_RODATA = "Soul Exchange";
static const u8 sMysticalSpaceTyphoonSortName[] APPEND_RODATA = "Mystical Space Typhoon";
static const u8 sRareMetalDragonSortName[] APPEND_RODATA = "Rare Metal Dragon";
static const u8 sMaskOfRestrictSortName[] APPEND_RODATA = "Mask of Restrict";
static const u8 sBlueEyesAlternativeWhiteDragonSortName[] APPEND_RODATA = "Blue-Eyes Alternative White Dragon";
static const u8 sSealOfOrichalcosSortName[] APPEND_RODATA = "Seal of Orichalcos";
static const u8 sSkillDrainSortName[] APPEND_RODATA = "Skill Drain";
static const u8 sMagicCylinderSortName[] APPEND_RODATA = "Magic Cylinder";
static const u8 sDelinquentDuoSortName[] APPEND_RODATA = "Delinquent Duo";
static const u8 sYataGarasuSortName[] APPEND_RODATA = "Yata-Garasu";
static const u8 sUpstartGoblinSortName[] APPEND_RODATA = "Upstart Goblin";
static const u8 sCallOfTheHauntedSortName[] APPEND_RODATA = "Call of the Haunted";
static const u8 sSwiftGaiaTheFierceKnightSortName[] APPEND_RODATA = "Swift Gaia The Fierce Knight";
static const u8 sLimiterRemovalSortName[] APPEND_RODATA = "Limiter Removal";
static const u8 sRecklessGreedSortName[] APPEND_RODATA = "Reckless Greed";
static const u8 sCardDestructionSortName[] APPEND_RODATA = "Card Destruction";
static const u8 sGracefulCharitySortName[] APPEND_RODATA = "Graceful Charity";
static const u8 sImperialOrderSortName[] APPEND_RODATA = "Imperial Order";
static const u8 sRoyalDecreeSortName[] APPEND_RODATA = "Royal Decree";
static const u8 sDoubleCostonSortName[] APPEND_RODATA = "Double Coston";
static const u8 sFinalCountdownSortName[] APPEND_RODATA = "Final Countdown";
static const u8 sBookOfMoonSortName[] APPEND_RODATA = "Book of Moon";
static const u8 sAmazonessTigerSortName[] APPEND_RODATA = "Amazoness Tiger";
static const u8 sConfiscationSortName[] APPEND_RODATA = "Confiscation";
static const u8 sZaborgTheThunderMonarchSortName[] APPEND_RODATA = "Zaborg the Thunder Monarch";
static const u8 sPolymerizationSortName[] APPEND_RODATA = "Polymerization";
static const u8 sCyberDragonSortName[] APPEND_RODATA = "Cyber Dragon";
static const u8 sCyberTwinDragonSortName[] APPEND_RODATA = "Cyber Twin Dragon";
static const u8 sCyberEndDragonSortName[] APPEND_RODATA = "Cyber End Dragon";
static const u8 sCaiusTheShadowMonarchSortName[] APPEND_RODATA = "Caius the Shadow Monarch";
static const u8 sMobiusTheFrostMonarchSortName[] APPEND_RODATA = "Mobius the Frost Monarch";
static const u8 sProtoCyberDragonSortName[] APPEND_RODATA = "Proto-Cyber Dragon";
static const u8 sAmazonessArcherSortName[] APPEND_RODATA = "Amazoness Archer";
static const u8 sElementalHeroWildheartSortName[] APPEND_RODATA = "Elemental HERO Wildheart";
static const u8 sTheSanctuaryInTheSkySortName[] APPEND_RODATA = "The Sanctuary in the Sky";
static const u8 sMirrorForceSortName[] APPEND_RODATA = "Mirror Force";
static const u8 sBlueEyesChaosDragonSortName[] APPEND_RODATA = "Blue-Eyes Chaos Dragon";
static const u8 sDeFusionSortName[] APPEND_RODATA = "De-Fusion";
static const u8 sALegendaryOceanSortName[] APPEND_RODATA = "A Legendary Ocean";
static const u8 sDarkMagicianOfChaosSortName[] APPEND_RODATA = "Dark Magician of Chaos";
static const u8 sElementalHeroPhoenixEnforcerSortName[] APPEND_RODATA = "Elemental HERO Phoenix Enforcer";
static const u8 sElementalHeroFlameWingmanSortName[] APPEND_RODATA = "Elemental HERO Flame Wingman";
static const u8 sElementalHeroShiningFlareWingmanSortName[] APPEND_RODATA = "Elemental HERO Shining Flare Wingman";
static const u8 sMiracleFusionSortName[] APPEND_RODATA = "Miracle Fusion";
static const u8 sChaosEmperorDragonEnvoyOfTheEndSortName[] APPEND_RODATA = "Chaos Emperor Dragon - Envoy of the End";
static const u8 sBlackLusterSoldierEnvoyOfTheBeginningSortName[] APPEND_RODATA = "Black Luster Soldier - Envoy of the Beginning";
static const u8 sElementalHeroNeosSortName[] APPEND_RODATA = "Elemental HERO Neos";
static const u8 sFusionRecoverySortName[] APPEND_RODATA = "Fusion Recovery";
static const u8 sSkyscraperSortName[] APPEND_RODATA = "Skyscraper";
static const u8 sHHeatedHeartSortName[] APPEND_RODATA = "H - Heated Heart";
static const u8 sEEmergencyCallSortName[] APPEND_RODATA = "E - Emergency Call";
static const u8 sElementalHeroIceEdgeSortName[] APPEND_RODATA = "Elemental HERO Ice Edge";
static const u8 sElementalHeroBlazemanSortName[] APPEND_RODATA = "Elemental HERO Blazeman";
static const u8 sElementalHeroStratosSortName[] APPEND_RODATA = "Elemental HERO Stratos";
static const u8 sChimeratechOverdragonSortName[] APPEND_RODATA = "Chimeratech Overdragon";
static const u8 sCyberneticFusionSupportSortName[] APPEND_RODATA = "Cybernetic Fusion Support";
static const u8 sOverloadFusionSortName[] APPEND_RODATA = "Overload Fusion";
static const u8 sPowerBondSortName[] APPEND_RODATA = "Power Bond";
static const u8 sDivineSanctuarySortName[] APPEND_RODATA = "Divine Sanctuary";
static const u8 sYubelSortName[] APPEND_RODATA = "Yubel";
static const u8 sYubelTerrorIncarnateSortName[] APPEND_RODATA = "Yubel - Terror Incarnate";
static const u8 sYubelTheUltimateNightmareSortName[] APPEND_RODATA = "Yubel - The Ultimate Nightmare";
static const u8 sTradeInSortName[] APPEND_RODATA = "Trade-In";
static const u8 sCyberBarrierDragonSortName[] APPEND_RODATA = "Cyber Barrier Dragon";
static const u8 sCyberLaserDragonSortName[] APPEND_RODATA = "Cyber Laser Dragon";
static const u8 sDestinyHeroBladeMasterSortName[] APPEND_RODATA = "Destiny HERO - Blade Master";
static const u8 sDestinyHeroCaptainTenaciousSortName[] APPEND_RODATA = "Destiny HERO - Captain Tenacious";
static const u8 sDestinyHeroCelestialSortName[] APPEND_RODATA = "Destiny HERO - Celestial";
static const u8 sDestinyHeroDangerousSortName[] APPEND_RODATA = "Destiny HERO - Dangerous";
static const u8 sDestinyHeroDasherSortName[] APPEND_RODATA = "Destiny HERO - Dasher";
static const u8 sDoomVirusDragonSortName[] APPEND_RODATA = "Doom Virus Dragon";
static const u8 sInstantFusionSortName[] APPEND_RODATA = "Instant Fusion";
static const u8 sJudgmentDragonSortName[] APPEND_RODATA = "Judgment Dragon";
static const u8 sManjuOfTheTenThousandHandsSortName[] APPEND_RODATA = "Manju of the Ten Thousand Hands";
static const u8 sMarshmallonSortName[] APPEND_RODATA = "Marshmallon";
static const u8 sNecrovalleySortName[] APPEND_RODATA = "Necrovalley";
static const u8 sNibiruThePrimalBeingSortName[] APPEND_RODATA = "Nibiru, the Primal Being";
static const u8 sPhotonGeneratorUnitSortName[] APPEND_RODATA = "Photon Generator Unit";
static const u8 sReaperScytheDreadscytheSortName[] APPEND_RODATA = "Reaper Scythe - Dreadscythe";
static const u8 sRedEyesBlackDragonSwordSortName[] APPEND_RODATA = "Red-Eyes Black Dragon Sword";
static const u8 sRedGadgetSortName[] APPEND_RODATA = "Red Gadget";
static const u8 sRocketHermosCannonSortName[] APPEND_RODATA = "Rocket Hermos Cannon";
static const u8 sScapegoatSortName[] APPEND_RODATA = "Scapegoat";
static const u8 sSolemnJudgmentSortName[] APPEND_RODATA = "Solemn Judgment";
static const u8 sSuperPolymerizationSortName[] APPEND_RODATA = "Super Polymerization";
static const u8 sVisionHeroAdorationSortName[] APPEND_RODATA = "Vision HERO Adoration";
static const u8 sVisionHeroFarisSortName[] APPEND_RODATA = "Vision HERO Faris";
static const u8 sVisionHeroGravitoSortName[] APPEND_RODATA = "Vision HERO Gravito";
static const u8 sVisionHeroIncreaseSortName[] APPEND_RODATA = "Vision HERO Increase";
static const u8 sAromaBlendSortName[] APPEND_RODATA = "Aroma Blend";
static const u8 sAromaGardenSortName[] APPEND_RODATA = "Aroma Garden";
static const u8 sAromaGardeningSortName[] APPEND_RODATA = "Aroma Gardening";
static const u8 sAromaJarSortName[] APPEND_RODATA = "Aroma Jar";
static const u8 sBlueEyesJetDragonSortName[] APPEND_RODATA = "Blue-Eyes Jet Dragon";
static const u8 sBlueEyesSolidDragonSortName[] APPEND_RODATA = "Blue-Eyes Solid Dragon";
static const u8 sBrionacDragonOfTheIceBarrierSortName[] APPEND_RODATA = "Brionac, Dragon of the Ice Barrier";
static const u8 sCyberSlashHarpieLadySortName[] APPEND_RODATA = "Cyber Slash Harpie Lady";
static const u8 sDarkMagicAttackSortName[] APPEND_RODATA = "Dark Magic Attack";
static const u8 sDarkMagicInheritanceSortName[] APPEND_RODATA = "Dark Magic Inheritance";
static const u8 sDarkMagicVeilSortName[] APPEND_RODATA = "Dark Magic Veil";
static const u8 sDarkMagicalCircleSortName[] APPEND_RODATA = "Dark Magical Circle";
static const u8 sDarkMagicianOfDestructionSortName[] APPEND_RODATA = "Dark Magician of Destruction";
static const u8 sDeepEyesWhiteDragonSortName[] APPEND_RODATA = "Deep-Eyes White Dragon";
static const u8 sDragonSpiritOfWhiteSortName[] APPEND_RODATA = "Dragon Spirit of White";
static const u8 sElShaddollConstructSortName[] APPEND_RODATA = "El Shaddoll Construct";
static const u8 sElShaddollWindaSortName[] APPEND_RODATA = "El Shaddoll Winda";
static const u8 sEternalSoulSortName[] APPEND_RODATA = "Eternal Soul";
static const u8 sEvilHeroAdustedGoldSortName[] APPEND_RODATA = "Evil HERO Adusted Gold";
static const u8 sEvilHeroDarkGaiaSortName[] APPEND_RODATA = "Evil HERO Dark Gaia";
static const u8 sEvilHeroDarkestKnightSortName[] APPEND_RODATA = "Evil HERO Darkest Knight";
static const u8 sEvilHeroDeadEndPrisonSortName[] APPEND_RODATA = "Evil HERO Dead-End Prison";
static const u8 sEvilHeroInfernalGainerSortName[] APPEND_RODATA = "Evil HERO Infernal Gainer";
static const u8 sGoyoGuardianSortName[] APPEND_RODATA = "Goyo Guardian";
static const u8 sHarpieChannelerSortName[] APPEND_RODATA = "Harpie Channeler";
static const u8 sHarpieConductorSortName[] APPEND_RODATA = "Harpie Conductor";
static const u8 sHarpieDancerSortName[] APPEND_RODATA = "Harpie Dancer";
static const u8 sHarpieHarpistSortName[] APPEND_RODATA = "Harpie Harpist";
static const u8 sHarpieLadyEleganceSortName[] APPEND_RODATA = "Harpie Lady Elegance";
static const u8 sHarpieOracleSortName[] APPEND_RODATA = "Harpie Oracle";
static const u8 sHarpiePerfumerSortName[] APPEND_RODATA = "Harpie Perfumer";
static const u8 sHarpieQueenSortName[] APPEND_RODATA = "Harpie Queen";
static const u8 sHarpiesFeatherRestSortName[] APPEND_RODATA = "Harpie's Feather Rest";
static const u8 sHarpiesFeatherStormSortName[] APPEND_RODATA = "Harpie's Feather Storm";
static const u8 sHarpiesHuntingGroundSortName[] APPEND_RODATA = "Harpies' Hunting Ground";
static const u8 sHarpiesPetPhantasmalDragonSortName[] APPEND_RODATA = "Harpie's Pet Phantasmal Dragon";
static const u8 sJunkWarriorSortName[] APPEND_RODATA = "Junk Warrior";
static const u8 sMagicianOfDarkIllusionSortName[] APPEND_RODATA = "Magician of Dark Illusion";
static const u8 sMagiciansRodSortName[] APPEND_RODATA = "Magician's Rod";
static const u8 sMagiciansSoulsSortName[] APPEND_RODATA = "Magicians' Souls";
static const u8 sMasterOfChaosSortName[] APPEND_RODATA = "Master of Chaos";
static const u8 sRedDragonArchfiendSortName[] APPEND_RODATA = "Red Dragon Archfiend";
static const u8 sReptilianneGardnaSortName[] APPEND_RODATA = "Reptilianne Gardna";
static const u8 sReptilianneGorgonSortName[] APPEND_RODATA = "Reptilianne Gorgon";
static const u8 sReptilianneHydraSortName[] APPEND_RODATA = "Reptilianne Hydra";
static const u8 sReturnOfTheDragonLordsSortName[] APPEND_RODATA = "Return of the Dragon Lords";
static const u8 sSecretsOfDarkMagicSortName[] APPEND_RODATA = "Secrets of Dark Magic";
static const u8 sShaddollBeastSortName[] APPEND_RODATA = "Shaddoll Beast";
static const u8 sShaddollDragonSortName[] APPEND_RODATA = "Shaddoll Dragon";
static const u8 sShaddollFusionSortName[] APPEND_RODATA = "Shaddoll Fusion";
static const u8 sShaddollHedgehogSortName[] APPEND_RODATA = "Shaddoll Hedgehog";
static const u8 sShaddollSquamataSortName[] APPEND_RODATA = "Shaddoll Squamata";
static const u8 sSilversCrySortName[] APPEND_RODATA = "Silver's Cry";
static const u8 sSoulServantSortName[] APPEND_RODATA = "Soul Servant";
static const u8 sStardustDragonSortName[] APPEND_RODATA = "Stardust Dragon";
static const u8 sTheMelodyOfAwakeningDragonSortName[] APPEND_RODATA = "The Melody of Awakening Dragon";
static const u8 sTheWhiteStoneOfAncientsSortName[] APPEND_RODATA = "The White Stone of Ancients";
static const u8 sTheWhiteStoneOfLegendSortName[] APPEND_RODATA = "The White Stone of Legend";
static const u8 sVenomBoaSortName[] APPEND_RODATA = "Venom Boa";
static const u8 sVenomBurnSortName[] APPEND_RODATA = "Venom Burn";
static const u8 sArcanaForce0TheFoolSortName[] APPEND_RODATA = "Arcana Force 0 - The Fool";
static const u8 sArcanaForceExTheDarkRulerSortName[] APPEND_RODATA = "Arcana Force EX - The Dark Ruler";
static const u8 sArcanaForceITheMagicianSortName[] APPEND_RODATA = "Arcana Force I - The Magician";
static const u8 sGladiatorBeastAlexanderSortName[] APPEND_RODATA = "Gladiator Beast Alexander";
static const u8 sGladiatorBeastAttorixSortName[] APPEND_RODATA = "Gladiator Beast Attorix";
static const u8 sGladiatorBeastAugustusSortName[] APPEND_RODATA = "Gladiator Beast Augustus";
static const u8 sGladiatorBeastBattleHalberdSortName[] APPEND_RODATA = "Gladiator Beast's Battle Halberd";
static const u8 sGladiatorBeastBestiariSortName[] APPEND_RODATA = "Gladiator Beast Bestiari";
static const u8 sGladiatorBeastClaudiusSortName[] APPEND_RODATA = "Gladiator Beast Claudius";
static const u8 sLightswornAegisSortName[] APPEND_RODATA = "Lightsworn Aegis";
static const u8 sLightswornBarrierSortName[] APPEND_RODATA = "Lightsworn Barrier";
static const u8 sLightswornDragonlingSortName[] APPEND_RODATA = "Lightsworn Dragonling";
static const u8 sLightswornJudgementSortName[] APPEND_RODATA = "Lightsworn Judgment";
static const u8 sLightswornSabreSortName[] APPEND_RODATA = "Lightsworn Sabre";
static const u8 sLightswornSanctuarySortName[] APPEND_RODATA = "Lightsworn Sanctuary";
static const u8 sNeoSpacianAirHummingbirdSortName[] APPEND_RODATA = "Neo-Spacian Air Hummingbird";
static const u8 sNeoSpacianAquaDolphinSortName[] APPEND_RODATA = "Neo-Spacian Aqua Dolphin";
static const u8 sNeoSpacianFlareScarabSortName[] APPEND_RODATA = "Neo-Spacian Flare Scarab";
static const u8 sNeoSpacianGlowMossSortName[] APPEND_RODATA = "Neo-Spacian Glow Moss";
static const u8 sAncientGearSortName[] APPEND_RODATA = "Ancient Gear";
static const u8 sAncientGearAdvanceSortName[] APPEND_RODATA = "Ancient Gear Advance";
static const u8 sAncientGearBeastSortName[] APPEND_RODATA = "Ancient Gear Beast";
static const u8 sAncientGearCannonSortName[] APPEND_RODATA = "Ancient Gear Cannon";
static const u8 sAncientGearCastleSortName[] APPEND_RODATA = "Ancient Gear Castle";
static const u8 sCyberDragonInfinitySortName[] APPEND_RODATA = "Cyber Dragon Infinity";
static const u8 sEvolzarDolkkaSortName[] APPEND_RODATA = "Evolzar Dolkka";
static const u8 sHonestSortName[] APPEND_RODATA = "Honest";
static const u8 sJunkSynchronSortName[] APPEND_RODATA = "Junk Synchron";
static const u8 sAmazonessAugustaSortName[] APPEND_RODATA = "Amazoness Augusta";
static const u8 sAmazonessEmpressSortName[] APPEND_RODATA = "Amazoness Empress";
static const u8 sAmazonessPrincessSortName[] APPEND_RODATA = "Amazoness Princess";
static const u8 sAmazonessQueenSortName[] APPEND_RODATA = "Amazoness Queen";
static const u8 sAmazonessCallSortName[] APPEND_RODATA = "Amazoness Call";
static const u8 sAmazonessOnslaughtSortName[] APPEND_RODATA = "Amazoness Onslaught";
static const u8 sAmazonessVillageSortName[] APPEND_RODATA = "Amazoness Village";
static const u8 sAshBlossomAndJoyousSpringSortName[] APPEND_RODATA = "Ash Blossom & Joyous Spring";
static const u8 sForbiddenChaliceSortName[] APPEND_RODATA = "Forbidden Chalice";
static const u8 sForbiddenLanceSortName[] APPEND_RODATA = "Forbidden Lance";
static const u8 sGravekeepersChiefSortName[] APPEND_RODATA = "Gravekeeper's Chief";
static const u8 sGravekeepersCommandantSortName[] APPEND_RODATA = "Gravekeeper's Commandant";
static const u8 sGravekeepersHeadmanSortName[] APPEND_RODATA = "Gravekeeper's Headman";
static const u8 sGravekeepersOracleSortName[] APPEND_RODATA = "Gravekeeper's Oracle";
static const u8 sGravekeepersRecruiterSortName[] APPEND_RODATA = "Gravekeeper's Recruiter";
static const u8 sGravekeepersSpiritualistSortName[] APPEND_RODATA = "Gravekeeper's Spiritualist";
static const u8 sGravekeepersTrapSortName[] APPEND_RODATA = "Gravekeeper's Trap";
static const u8 sImperialTombsOfNecrovalleySortName[] APPEND_RODATA = "Imperial Tombs of Necrovalley";
static const u8 sInfiniteImpermanenceSortName[] APPEND_RODATA = "Infinite Impermanence";
static const u8 sHiddenTemplesOfNecrovalleySortName[] APPEND_RODATA = "Hidden Temples of Necrovalley";
static const u8 sLightningStormSortName[] APPEND_RODATA = "Lightning Storm";
static const u8 sPotOfAvariceSortName[] APPEND_RODATA = "Pot of Avarice";
static const u8 sNumber39UtopiaSortName[] APPEND_RODATA = "Number 39: Utopia";
static const u8 sMaxxCSortName[] APPEND_RODATA = "Maxx C";
static const u8 sToadallyAwesomeSortName[] APPEND_RODATA = "Toadally Awesome";

static const u16 sCustomCardsByName[NUM_CUSTOM_NAME_SORT_CARDS] APPEND_RODATA = {
  0x034C, // A Legendary Ocean
  0x0346, // Amazoness Archer
  0x03D7, // Amazoness Augusta
  0x03DB, // Amazoness Call
  0x03D8, // Amazoness Empress
  0x03DC, // Amazoness Onslaught
  0x03D9, // Amazoness Princess
  0x03DA, // Amazoness Queen
  0x033C, // Amazoness Tiger
  0x03DD, // Amazoness Village
  0x03CE, // Ancient Gear
  0x03CF, // Ancient Gear Advance
  0x03D0, // Ancient Gear Beast
  0x03D1, // Ancient Gear Cannon
  0x03D2, // Ancient Gear Castle
  0x03BB, // Arcana Force 0 - The Fool
  0x03BC, // Arcana Force EX - The Dark Ruler
  0x03BD, // Arcana Force I - The Magician
  0x037F, // Aroma Blend
  0x0380, // Aroma Garden
  0x0381, // Aroma Gardening
  0x0382, // Aroma Jar
  0x03DE, // Ash Blossom & Joyous Spring
  0x0353, // Black Luster Soldier - Envoy of the Beginning
  0x032A, // Blue-Eyes Alternative White Dragon
  0x034A, // Blue-Eyes Chaos Dragon
  0x0322, // Blue-Eyes Chaos Max Dragon
  0x0383, // Blue-Eyes Jet Dragon
  0x0321, // Blue-Eyes Shining Dragon
  0x0384, // Blue-Eyes Solid Dragon
  0x033B, // Book of Moon
  0x0385, // Brionac, Dragon of the Ice Barrier
  0x0343, // Caius the Shadow Monarch
  0x0331, // Call of the Haunted
  0x0335, // Card Destruction
  0x0352, // Chaos Emperor Dragon - Envoy of the End
  0x035C, // Chimeratech Overdragon
  0x033D, // Confiscation
  0x0365, // Cyber Barrier Dragon
  0x0340, // Cyber Dragon
  0x03D3, // Cyber Dragon Infinity
  0x0342, // Cyber End Dragon
  0x0366, // Cyber Laser Dragon
  0x0386, // Cyber Slash Harpie Lady
  0x0341, // Cyber Twin Dragon
  0x035D, // Cybernetic Fusion Support
  0x0387, // Dark Magic Attack
  0x0388, // Dark Magic Inheritance
  0x0389, // Dark Magic Veil
  0x038A, // Dark Magical Circle
  0x034D, // Dark Magician of Chaos
  0x038B, // Dark Magician of Destruction
  0x034B, // De-Fusion
  0x038C, // Deep-Eyes White Dragon
  0x032E, // Delinquent Duo
  0x0367, // Destiny HERO - Blade Master
  0x0368, // Destiny HERO - Captain Tenacious
  0x0369, // Destiny HERO - Celestial
  0x036A, // Destiny HERO - Dangerous
  0x036B, // Destiny HERO - Dasher
  0x0360, // Divine Sanctuary
  0x036C, // Doom Virus Dragon
  0x0339, // Double Coston
  0x038D, // Dragon Spirit of White
  0x0358, // E - Emergency Call
  0x038E, // El Shaddoll Construct
  0x038F, // El Shaddoll Winda
  0x035A, // Elemental HERO Blazeman
  0x034F, // Elemental HERO Flame Wingman
  0x0359, // Elemental HERO Ice Edge
  0x0354, // Elemental HERO Neos
  0x034E, // Elemental HERO Phoenix Enforcer
  0x0350, // Elemental HERO Shining Flare Wingman
  0x035B, // Elemental HERO Stratos
  0x0347, // Elemental HERO Wildheart
  0x0390, // Eternal Soul
  0x0391, // Evil HERO Adusted Gold
  0x0392, // Evil HERO Dark Gaia
  0x0393, // Evil HERO Darkest Knight
  0x0394, // Evil HERO Dead-End Prison
  0x0395, // Evil HERO Infernal Gainer
  0x03D4, // Evolzar Dolkka
  0x033A, // Final Countdown
  0x03DF, // Forbidden Chalice
  0x03E0, // Forbidden Lance
  0x0355, // Fusion Recovery
  0x03BE, // Gladiator Beast Alexander
  0x03BF, // Gladiator Beast Attorix
  0x03C0, // Gladiator Beast Augustus
  0x03C2, // Gladiator Beast Bestiari
  0x03C3, // Gladiator Beast Claudius
  0x03C1, // Gladiator Beast's Battle Halberd
  0x0396, // Goyo Guardian
  0x0336, // Graceful Charity
  0x03E1, // Gravekeeper's Chief
  0x03E2, // Gravekeeper's Commandant
  0x03E3, // Gravekeeper's Headman
  0x03E4, // Gravekeeper's Oracle
  0x03E5, // Gravekeeper's Recruiter
  0x03E6, // Gravekeeper's Spiritualist
  0x03E7, // Gravekeeper's Trap
  0x0357, // H - Heated Heart
  0x0397, // Harpie Channeler
  0x0398, // Harpie Conductor
  0x0399, // Harpie Dancer
  0x039A, // Harpie Harpist
  0x039B, // Harpie Lady Elegance
  0x039C, // Harpie Oracle
  0x039D, // Harpie Perfumer
  0x039E, // Harpie Queen
  0x039F, // Harpie's Feather Rest
  0x03A0, // Harpie's Feather Storm
  0x03A2, // Harpie's Pet Phantasmal Dragon
  0x03A1, // Harpies' Hunting Ground
  0x03EA, // Hidden Temples of Necrovalley
  0x03D5, // Honest
  0x0337, // Imperial Order
  0x03E8, // Imperial Tombs of Necrovalley
  0x03E9, // Infinite Impermanence
  0x036D, // Instant Fusion
  0x036E, // Judgment Dragon
  0x03D6, // Junk Synchron
  0x03A3, // Junk Warrior
  0x0323, // Kaibaman
  0x03EB, // Lightning Storm
  0x03C4, // Lightsworn Aegis
  0x03C5, // Lightsworn Barrier
  0x03C6, // Lightsworn Dragonling
  0x03C7, // Lightsworn Judgment
  0x03C8, // Lightsworn Sabre
  0x03C9, // Lightsworn Sanctuary
  0x0333, // Limiter Removal
  0x032D, // Magic Cylinder
  0x03A4, // Magician of Dark Illusion
  0x03A5, // Magician's Rod
  0x03A6, // Magicians' Souls
  0x036F, // Manju of the Ten Thousand Hands
  0x0370, // Marshmallon
  0x0329, // Mask of Restrict
  0x03A7, // Master of Chaos
  0x03EE, // Maxx C
  0x0351, // Miracle Fusion
  0x0349, // Mirror Force
  0x0344, // Mobius the Frost Monarch
  0x0327, // Mystical Space Typhoon
  0x0371, // Necrovalley
  0x03CA, // Neo-Spacian Air Hummingbird
  0x03CB, // Neo-Spacian Aqua Dolphin
  0x03CC, // Neo-Spacian Flare Scarab
  0x03CD, // Neo-Spacian Glow Moss
  0x0372, // Nibiru, the Primal Being
  0x03ED, // Number 39: Utopia
  0x035E, // Overload Fusion
  0x0373, // Photon Generator Unit
  0x033F, // Polymerization
  0x03EC, // Pot of Avarice
  0x035F, // Power Bond
  0x0345, // Proto-Cyber Dragon
  0x0328, // Rare Metal Dragon
  0x0374, // Reaper Scythe - Dreadscythe
  0x0334, // Reckless Greed
  0x03A8, // Red Dragon Archfiend
  0x0376, // Red Gadget
  0x0375, // Red-Eyes Black Dragon Sword
  0x03A9, // Reptilianne Gardna
  0x03AA, // Reptilianne Gorgon
  0x03AB, // Reptilianne Hydra
  0x03AC, // Return of the Dragon Lords
  0x0377, // Rocket Hermos Cannon
  0x0338, // Royal Decree
  0x0378, // Scapegoat
  0x032B, // Seal of Orichalcos
  0x03AD, // Secrets of Dark Magic
  0x03AE, // Shaddoll Beast
  0x03AF, // Shaddoll Dragon
  0x03B0, // Shaddoll Fusion
  0x03B1, // Shaddoll Hedgehog
  0x03B2, // Shaddoll Squamata
  0x03B3, // Silver's Cry
  0x032C, // Skill Drain
  0x0356, // Skyscraper
  0x0379, // Solemn Judgment
  0x0326, // Soul Exchange
  0x03B4, // Soul Servant
  0x03B5, // Stardust Dragon
  0x037A, // Super Polymerization
  0x0332, // Swift Gaia The Fierce Knight
  0x03B6, // The Melody of Awakening Dragon
  0x0348, // The Sanctuary in the Sky
  0x03B7, // The White Stone of Ancients
  0x03B8, // The White Stone of Legend
  0x03EF, // Toadally Awesome
  0x0364, // Trade-In
  0x0324, // Ultimate Offering
  0x0330, // Upstart Goblin
  0x03B9, // Venom Boa
  0x03BA, // Venom Burn
  0x037B, // Vision HERO Adoration
  0x037C, // Vision HERO Faris
  0x037D, // Vision HERO Gravito
  0x037E, // Vision HERO Increase
  0x0325, // Wave Motion Cannon
  0x032F, // Yata-Garasu
  0x0361, // Yubel
  0x0362, // Yubel - Terror Incarnate
  0x0363, // Yubel - The Ultimate Nightmare
  0x033E, // Zaborg the Thunder Monarch
};

static const u16 sCustomCardNameSortOrder[NUM_CUSTOM_NAME_SORT_CARDS] APPEND_RODATA = {
  1, // A Legendary Ocean
  2, // Amazoness Archer
  3, // Amazoness Augusta
  4, // Amazoness Call
  5, // Amazoness Empress
  6, // Amazoness Onslaught
  7, // Amazoness Princess
  8, // Amazoness Queen
  9, // Amazoness Tiger
  10, // Amazoness Village
  11, // Ancient Gear
  12, // Ancient Gear Advance
  13, // Ancient Gear Beast
  14, // Ancient Gear Cannon
  15, // Ancient Gear Castle
  16, // Arcana Force 0 - The Fool
  17, // Arcana Force EX - The Dark Ruler
  18, // Arcana Force I - The Magician
  19, // Aroma Blend
  20, // Aroma Garden
  21, // Aroma Gardening
  22, // Aroma Jar
  23, // Ash Blossom & Joyous Spring
  24, // Black Luster Soldier - Envoy of the Beginning
  25, // Blue-Eyes Alternative White Dragon
  26, // Blue-Eyes Chaos Dragon
  27, // Blue-Eyes Chaos Max Dragon
  28, // Blue-Eyes Jet Dragon
  29, // Blue-Eyes Shining Dragon
  30, // Blue-Eyes Solid Dragon
  31, // Book of Moon
  32, // Brionac, Dragon of the Ice Barrier
  33, // Caius the Shadow Monarch
  34, // Call of the Haunted
  35, // Card Destruction
  36, // Chaos Emperor Dragon - Envoy of the End
  37, // Chimeratech Overdragon
  38, // Confiscation
  39, // Cyber Barrier Dragon
  40, // Cyber Dragon
  41, // Cyber Dragon Infinity
  42, // Cyber End Dragon
  43, // Cyber Laser Dragon
  44, // Cyber Slash Harpie Lady
  45, // Cyber Twin Dragon
  46, // Cybernetic Fusion Support
  47, // Dark Magic Attack
  48, // Dark Magic Inheritance
  49, // Dark Magic Veil
  50, // Dark Magical Circle
  51, // Dark Magician of Chaos
  52, // Dark Magician of Destruction
  53, // De-Fusion
  54, // Deep-Eyes White Dragon
  55, // Delinquent Duo
  56, // Destiny HERO - Blade Master
  57, // Destiny HERO - Captain Tenacious
  58, // Destiny HERO - Celestial
  59, // Destiny HERO - Dangerous
  60, // Destiny HERO - Dasher
  61, // Divine Sanctuary
  62, // Doom Virus Dragon
  63, // Double Coston
  64, // Dragon Spirit of White
  65, // E - Emergency Call
  66, // El Shaddoll Construct
  67, // El Shaddoll Winda
  68, // Elemental HERO Blazeman
  69, // Elemental HERO Flame Wingman
  70, // Elemental HERO Ice Edge
  71, // Elemental HERO Neos
  72, // Elemental HERO Phoenix Enforcer
  73, // Elemental HERO Shining Flare Wingman
  74, // Elemental HERO Stratos
  75, // Elemental HERO Wildheart
  76, // Eternal Soul
  77, // Evil HERO Adusted Gold
  78, // Evil HERO Dark Gaia
  79, // Evil HERO Darkest Knight
  80, // Evil HERO Dead-End Prison
  81, // Evil HERO Infernal Gainer
  82, // Evolzar Dolkka
  83, // Final Countdown
  84, // Forbidden Chalice
  85, // Forbidden Lance
  86, // Fusion Recovery
  87, // Gladiator Beast Alexander
  88, // Gladiator Beast Attorix
  89, // Gladiator Beast Augustus
  90, // Gladiator Beast Bestiari
  91, // Gladiator Beast Claudius
  92, // Gladiator Beast's Battle Halberd
  93, // Goyo Guardian
  94, // Graceful Charity
  95, // Gravekeeper's Chief
  96, // Gravekeeper's Commandant
  97, // Gravekeeper's Headman
  98, // Gravekeeper's Oracle
  99, // Gravekeeper's Recruiter
  100, // Gravekeeper's Spiritualist
  101, // Gravekeeper's Trap
  102, // H - Heated Heart
  103, // Harpie Channeler
  104, // Harpie Conductor
  105, // Harpie Dancer
  106, // Harpie Harpist
  107, // Harpie Lady Elegance
  108, // Harpie Oracle
  109, // Harpie Perfumer
  110, // Harpie Queen
  111, // Harpie's Feather Rest
  112, // Harpie's Feather Storm
  113, // Harpie's Pet Phantasmal Dragon
  114, // Harpies' Hunting Ground
  115, // Hidden Temples of Necrovalley
  116, // Honest
  117, // Imperial Order
  118, // Imperial Tombs of Necrovalley
  119, // Infinite Impermanence
  120, // Instant Fusion
  121, // Judgment Dragon
  122, // Junk Synchron
  123, // Junk Warrior
  124, // Kaibaman
  125, // Lightning Storm
  126, // Lightsworn Aegis
  127, // Lightsworn Barrier
  128, // Lightsworn Dragonling
  129, // Lightsworn Judgment
  130, // Lightsworn Sabre
  131, // Lightsworn Sanctuary
  132, // Limiter Removal
  133, // Magic Cylinder
  134, // Magician of Dark Illusion
  135, // Magician's Rod
  136, // Magicians' Souls
  137, // Manju of the Ten Thousand Hands
  138, // Marshmallon
  139, // Mask of Restrict
  140, // Master of Chaos
  141, // Maxx C
  142, // Miracle Fusion
  143, // Mirror Force
  144, // Mobius the Frost Monarch
  145, // Mystical Space Typhoon
  146, // Necrovalley
  147, // Neo-Spacian Air Hummingbird
  148, // Neo-Spacian Aqua Dolphin
  149, // Neo-Spacian Flare Scarab
  150, // Neo-Spacian Glow Moss
  151, // Nibiru, the Primal Being
  152, // Number 39: Utopia
  153, // Overload Fusion
  154, // Photon Generator Unit
  155, // Polymerization
  156, // Pot of Avarice
  157, // Power Bond
  158, // Proto-Cyber Dragon
  159, // Rare Metal Dragon
  160, // Reaper Scythe - Dreadscythe
  161, // Reckless Greed
  162, // Red Dragon Archfiend
  163, // Red Gadget
  164, // Red-Eyes Black Dragon Sword
  165, // Reptilianne Gardna
  166, // Reptilianne Gorgon
  167, // Reptilianne Hydra
  168, // Return of the Dragon Lords
  169, // Rocket Hermos Cannon
  170, // Royal Decree
  171, // Scapegoat
  172, // Seal of Orichalcos
  173, // Secrets of Dark Magic
  174, // Shaddoll Beast
  175, // Shaddoll Dragon
  176, // Shaddoll Fusion
  177, // Shaddoll Hedgehog
  178, // Shaddoll Squamata
  179, // Silver's Cry
  180, // Skill Drain
  181, // Skyscraper
  182, // Solemn Judgment
  183, // Soul Exchange
  184, // Soul Servant
  185, // Stardust Dragon
  186, // Super Polymerization
  187, // Swift Gaia The Fierce Knight
  188, // The Melody of Awakening Dragon
  189, // The Sanctuary in the Sky
  190, // The White Stone of Ancients
  191, // The White Stone of Legend
  192, // Toadally Awesome
  193, // Trade-In
  194, // Ultimate Offering
  195, // Upstart Goblin
  196, // Venom Boa
  197, // Venom Burn
  198, // Vision HERO Adoration
  199, // Vision HERO Faris
  200, // Vision HERO Gravito
  201, // Vision HERO Increase
  202, // Wave Motion Cannon
  203, // Yata-Garasu
  204, // Yubel
  205, // Yubel - Terror Incarnate
  206, // Yubel - The Ultimate Nightmare
  207, // Zaborg the Thunder Monarch
};

static u8 *GetSortCardName(u16 cardId) {
  if (cardId == 0x021B)
    return (u8 *)sAmazonChainMasterSortName;
  if (cardId == 0x0276)
    return (u8 *)sAmazonFighterSortName;
  if (cardId == 0x0279)
    return (u8 *)sAmazonSwordWomanSortName;
  if (cardId == 0x0321)
    return (u8 *)sBlueEyesShiningDragonSortName;
  if (cardId == 0x0322)
    return (u8 *)sBlueEyesChaosMaxDragonSortName;
  if (cardId == 0x0323)
    return (u8 *)sKaibamanSortName;
  if (cardId == 0x0324)
    return (u8 *)sUltimateOfferingSortName;
  if (cardId == 0x0325)
    return (u8 *)sWaveMotionCannonSortName;
  if (cardId == 0x0326)
    return (u8 *)sSoulExchangeSortName;
  if (cardId == 0x0327)
    return (u8 *)sMysticalSpaceTyphoonSortName;
  if (cardId == 0x0328)
    return (u8 *)sRareMetalDragonSortName;
  if (cardId == 0x0329)
    return (u8 *)sMaskOfRestrictSortName;
  if (cardId == 0x032A)
    return (u8 *)sBlueEyesAlternativeWhiteDragonSortName;
  if (cardId == 0x032B)
    return (u8 *)sSealOfOrichalcosSortName;
  if (cardId == 0x032C)
    return (u8 *)sSkillDrainSortName;
  if (cardId == 0x032D)
    return (u8 *)sMagicCylinderSortName;
  if (cardId == 0x032E)
    return (u8 *)sDelinquentDuoSortName;
  if (cardId == 0x032F)
    return (u8 *)sYataGarasuSortName;
  if (cardId == 0x0330)
    return (u8 *)sUpstartGoblinSortName;
  if (cardId == 0x0331)
    return (u8 *)sCallOfTheHauntedSortName;
  if (cardId == 0x0332)
    return (u8 *)sSwiftGaiaTheFierceKnightSortName;
  if (cardId == 0x0333)
    return (u8 *)sLimiterRemovalSortName;
  if (cardId == 0x0334)
    return (u8 *)sRecklessGreedSortName;
  if (cardId == 0x0335)
    return (u8 *)sCardDestructionSortName;
  if (cardId == 0x0336)
    return (u8 *)sGracefulCharitySortName;
  if (cardId == 0x0337)
    return (u8 *)sImperialOrderSortName;
  if (cardId == 0x0338)
    return (u8 *)sRoyalDecreeSortName;
  if (cardId == 0x0339)
    return (u8 *)sDoubleCostonSortName;
  if (cardId == 0x033A)
    return (u8 *)sFinalCountdownSortName;
  if (cardId == 0x033B)
    return (u8 *)sBookOfMoonSortName;
  if (cardId == 0x033C)
    return (u8 *)sAmazonessTigerSortName;
  if (cardId == 0x033D)
    return (u8 *)sConfiscationSortName;
  if (cardId == 0x033E)
    return (u8 *)sZaborgTheThunderMonarchSortName;
  if (cardId == 0x033F)
    return (u8 *)sPolymerizationSortName;
  if (cardId == 0x0340)
    return (u8 *)sCyberDragonSortName;
  if (cardId == 0x0341)
    return (u8 *)sCyberTwinDragonSortName;
  if (cardId == 0x0342)
    return (u8 *)sCyberEndDragonSortName;
  if (cardId == 0x0343)
    return (u8 *)sCaiusTheShadowMonarchSortName;
  if (cardId == 0x0344)
    return (u8 *)sMobiusTheFrostMonarchSortName;
  if (cardId == 0x0345)
    return (u8 *)sProtoCyberDragonSortName;
  if (cardId == 0x0346)
    return (u8 *)sAmazonessArcherSortName;
  if (cardId == 0x0347)
    return (u8 *)sElementalHeroWildheartSortName;
  if (cardId == 0x0348)
    return (u8 *)sTheSanctuaryInTheSkySortName;
  if (cardId == 0x0349)
    return (u8 *)sMirrorForceSortName;
  if (cardId == 0x034A)
    return (u8 *)sBlueEyesChaosDragonSortName;
  if (cardId == 0x034B)
    return (u8 *)sDeFusionSortName;
  if (cardId == 0x034C)
    return (u8 *)sALegendaryOceanSortName;
  if (cardId == 0x034D)
    return (u8 *)sDarkMagicianOfChaosSortName;
  if (cardId == 0x034E)
    return (u8 *)sElementalHeroPhoenixEnforcerSortName;
  if (cardId == 0x034F)
    return (u8 *)sElementalHeroFlameWingmanSortName;
  if (cardId == 0x0350)
    return (u8 *)sElementalHeroShiningFlareWingmanSortName;
  if (cardId == 0x0351)
    return (u8 *)sMiracleFusionSortName;
  if (cardId == 0x0352)
    return (u8 *)sChaosEmperorDragonEnvoyOfTheEndSortName;
  if (cardId == 0x0353)
    return (u8 *)sBlackLusterSoldierEnvoyOfTheBeginningSortName;
  if (cardId == 0x0354)
    return (u8 *)sElementalHeroNeosSortName;
  if (cardId == 0x0355)
    return (u8 *)sFusionRecoverySortName;
  if (cardId == 0x0356)
    return (u8 *)sSkyscraperSortName;
  if (cardId == 0x0357)
    return (u8 *)sHHeatedHeartSortName;
  if (cardId == 0x0358)
    return (u8 *)sEEmergencyCallSortName;
  if (cardId == 0x0359)
    return (u8 *)sElementalHeroIceEdgeSortName;
  if (cardId == 0x035A)
    return (u8 *)sElementalHeroBlazemanSortName;
  if (cardId == 0x035B)
    return (u8 *)sElementalHeroStratosSortName;
  if (cardId == 0x035C)
    return (u8 *)sChimeratechOverdragonSortName;
  if (cardId == 0x035D)
    return (u8 *)sCyberneticFusionSupportSortName;
  if (cardId == 0x035E)
    return (u8 *)sOverloadFusionSortName;
  if (cardId == 0x035F)
    return (u8 *)sPowerBondSortName;
  if (cardId == 0x0360)
    return (u8 *)sDivineSanctuarySortName;
  if (cardId == 0x0361)
    return (u8 *)sYubelSortName;
  if (cardId == 0x0362)
    return (u8 *)sYubelTerrorIncarnateSortName;
  if (cardId == 0x0363)
    return (u8 *)sYubelTheUltimateNightmareSortName;
  if (cardId == 0x0364)
    return (u8 *)sTradeInSortName;
  if (cardId == 0x0365)
    return (u8 *)sCyberBarrierDragonSortName;
  if (cardId == 0x0366)
    return (u8 *)sCyberLaserDragonSortName;
  if (cardId == 0x0367)
    return (u8 *)sDestinyHeroBladeMasterSortName;
  if (cardId == 0x0368)
    return (u8 *)sDestinyHeroCaptainTenaciousSortName;
  if (cardId == 0x0369)
    return (u8 *)sDestinyHeroCelestialSortName;
  if (cardId == 0x036A)
    return (u8 *)sDestinyHeroDangerousSortName;
  if (cardId == 0x036B)
    return (u8 *)sDestinyHeroDasherSortName;
  if (cardId == 0x036C)
    return (u8 *)sDoomVirusDragonSortName;
  if (cardId == 0x036D)
    return (u8 *)sInstantFusionSortName;
  if (cardId == 0x036E)
    return (u8 *)sJudgmentDragonSortName;
  if (cardId == 0x036F)
    return (u8 *)sManjuOfTheTenThousandHandsSortName;
  if (cardId == 0x0370)
    return (u8 *)sMarshmallonSortName;
  if (cardId == 0x0371)
    return (u8 *)sNecrovalleySortName;
  if (cardId == 0x0372)
    return (u8 *)sNibiruThePrimalBeingSortName;
  if (cardId == 0x0373)
    return (u8 *)sPhotonGeneratorUnitSortName;
  if (cardId == 0x0374)
    return (u8 *)sReaperScytheDreadscytheSortName;
  if (cardId == 0x0375)
    return (u8 *)sRedEyesBlackDragonSwordSortName;
  if (cardId == 0x0376)
    return (u8 *)sRedGadgetSortName;
  if (cardId == 0x0377)
    return (u8 *)sRocketHermosCannonSortName;
  if (cardId == 0x0378)
    return (u8 *)sScapegoatSortName;
  if (cardId == 0x0379)
    return (u8 *)sSolemnJudgmentSortName;
  if (cardId == 0x037A)
    return (u8 *)sSuperPolymerizationSortName;
  if (cardId == 0x037B)
    return (u8 *)sVisionHeroAdorationSortName;
  if (cardId == 0x037C)
    return (u8 *)sVisionHeroFarisSortName;
  if (cardId == 0x037D)
    return (u8 *)sVisionHeroGravitoSortName;
  if (cardId == 0x037E)
    return (u8 *)sVisionHeroIncreaseSortName;
  if (cardId == 0x037F)
    return (u8 *)sAromaBlendSortName;
  if (cardId == 0x0380)
    return (u8 *)sAromaGardenSortName;
  if (cardId == 0x0381)
    return (u8 *)sAromaGardeningSortName;
  if (cardId == 0x0382)
    return (u8 *)sAromaJarSortName;
  if (cardId == 0x0383)
    return (u8 *)sBlueEyesJetDragonSortName;
  if (cardId == 0x0384)
    return (u8 *)sBlueEyesSolidDragonSortName;
  if (cardId == 0x0385)
    return (u8 *)sBrionacDragonOfTheIceBarrierSortName;
  if (cardId == 0x0386)
    return (u8 *)sCyberSlashHarpieLadySortName;
  if (cardId == 0x0387)
    return (u8 *)sDarkMagicAttackSortName;
  if (cardId == 0x0388)
    return (u8 *)sDarkMagicInheritanceSortName;
  if (cardId == 0x0389)
    return (u8 *)sDarkMagicVeilSortName;
  if (cardId == 0x038A)
    return (u8 *)sDarkMagicalCircleSortName;
  if (cardId == 0x038B)
    return (u8 *)sDarkMagicianOfDestructionSortName;
  if (cardId == 0x038C)
    return (u8 *)sDeepEyesWhiteDragonSortName;
  if (cardId == 0x038D)
    return (u8 *)sDragonSpiritOfWhiteSortName;
  if (cardId == 0x038E)
    return (u8 *)sElShaddollConstructSortName;
  if (cardId == 0x038F)
    return (u8 *)sElShaddollWindaSortName;
  if (cardId == 0x0390)
    return (u8 *)sEternalSoulSortName;
  if (cardId == 0x0391)
    return (u8 *)sEvilHeroAdustedGoldSortName;
  if (cardId == 0x0392)
    return (u8 *)sEvilHeroDarkGaiaSortName;
  if (cardId == 0x0393)
    return (u8 *)sEvilHeroDarkestKnightSortName;
  if (cardId == 0x0394)
    return (u8 *)sEvilHeroDeadEndPrisonSortName;
  if (cardId == 0x0395)
    return (u8 *)sEvilHeroInfernalGainerSortName;
  if (cardId == 0x0396)
    return (u8 *)sGoyoGuardianSortName;
  if (cardId == 0x0397)
    return (u8 *)sHarpieChannelerSortName;
  if (cardId == 0x0398)
    return (u8 *)sHarpieConductorSortName;
  if (cardId == 0x0399)
    return (u8 *)sHarpieDancerSortName;
  if (cardId == 0x039A)
    return (u8 *)sHarpieHarpistSortName;
  if (cardId == 0x039B)
    return (u8 *)sHarpieLadyEleganceSortName;
  if (cardId == 0x039C)
    return (u8 *)sHarpieOracleSortName;
  if (cardId == 0x039D)
    return (u8 *)sHarpiePerfumerSortName;
  if (cardId == 0x039E)
    return (u8 *)sHarpieQueenSortName;
  if (cardId == 0x039F)
    return (u8 *)sHarpiesFeatherRestSortName;
  if (cardId == 0x03A0)
    return (u8 *)sHarpiesFeatherStormSortName;
  if (cardId == 0x03A1)
    return (u8 *)sHarpiesHuntingGroundSortName;
  if (cardId == 0x03A2)
    return (u8 *)sHarpiesPetPhantasmalDragonSortName;
  if (cardId == 0x03A3)
    return (u8 *)sJunkWarriorSortName;
  if (cardId == 0x03A4)
    return (u8 *)sMagicianOfDarkIllusionSortName;
  if (cardId == 0x03A5)
    return (u8 *)sMagiciansRodSortName;
  if (cardId == 0x03A6)
    return (u8 *)sMagiciansSoulsSortName;
  if (cardId == 0x03A7)
    return (u8 *)sMasterOfChaosSortName;
  if (cardId == 0x03A8)
    return (u8 *)sRedDragonArchfiendSortName;
  if (cardId == 0x03A9)
    return (u8 *)sReptilianneGardnaSortName;
  if (cardId == 0x03AA)
    return (u8 *)sReptilianneGorgonSortName;
  if (cardId == 0x03AB)
    return (u8 *)sReptilianneHydraSortName;
  if (cardId == 0x03AC)
    return (u8 *)sReturnOfTheDragonLordsSortName;
  if (cardId == 0x03AD)
    return (u8 *)sSecretsOfDarkMagicSortName;
  if (cardId == 0x03AE)
    return (u8 *)sShaddollBeastSortName;
  if (cardId == 0x03AF)
    return (u8 *)sShaddollDragonSortName;
  if (cardId == 0x03B0)
    return (u8 *)sShaddollFusionSortName;
  if (cardId == 0x03B1)
    return (u8 *)sShaddollHedgehogSortName;
  if (cardId == 0x03B2)
    return (u8 *)sShaddollSquamataSortName;
  if (cardId == 0x03B3)
    return (u8 *)sSilversCrySortName;
  if (cardId == 0x03B4)
    return (u8 *)sSoulServantSortName;
  if (cardId == 0x03B5)
    return (u8 *)sStardustDragonSortName;
  if (cardId == 0x03B6)
    return (u8 *)sTheMelodyOfAwakeningDragonSortName;
  if (cardId == 0x03B7)
    return (u8 *)sTheWhiteStoneOfAncientsSortName;
  if (cardId == 0x03B8)
    return (u8 *)sTheWhiteStoneOfLegendSortName;
  if (cardId == 0x03B9)
    return (u8 *)sVenomBoaSortName;
  if (cardId == 0x03BA)
    return (u8 *)sVenomBurnSortName;
  if (cardId == 0x03BB)
    return (u8 *)sArcanaForce0TheFoolSortName;
  if (cardId == 0x03BC)
    return (u8 *)sArcanaForceExTheDarkRulerSortName;
  if (cardId == 0x03BD)
    return (u8 *)sArcanaForceITheMagicianSortName;
  if (cardId == 0x03BE)
    return (u8 *)sGladiatorBeastAlexanderSortName;
  if (cardId == 0x03BF)
    return (u8 *)sGladiatorBeastAttorixSortName;
  if (cardId == 0x03C0)
    return (u8 *)sGladiatorBeastAugustusSortName;
  if (cardId == 0x03C1)
    return (u8 *)sGladiatorBeastBattleHalberdSortName;
  if (cardId == 0x03C2)
    return (u8 *)sGladiatorBeastBestiariSortName;
  if (cardId == 0x03C3)
    return (u8 *)sGladiatorBeastClaudiusSortName;
  if (cardId == 0x03C4)
    return (u8 *)sLightswornAegisSortName;
  if (cardId == 0x03C5)
    return (u8 *)sLightswornBarrierSortName;
  if (cardId == 0x03C6)
    return (u8 *)sLightswornDragonlingSortName;
  if (cardId == 0x03C7)
    return (u8 *)sLightswornJudgementSortName;
  if (cardId == 0x03C8)
    return (u8 *)sLightswornSabreSortName;
  if (cardId == 0x03C9)
    return (u8 *)sLightswornSanctuarySortName;
  if (cardId == 0x03CA)
    return (u8 *)sNeoSpacianAirHummingbirdSortName;
  if (cardId == 0x03CB)
    return (u8 *)sNeoSpacianAquaDolphinSortName;
  if (cardId == 0x03CC)
    return (u8 *)sNeoSpacianFlareScarabSortName;
  if (cardId == 0x03CD)
    return (u8 *)sNeoSpacianGlowMossSortName;
  if (cardId == 0x03CE)
    return (u8 *)sAncientGearSortName;
  if (cardId == 0x03CF)
    return (u8 *)sAncientGearAdvanceSortName;
  if (cardId == 0x03D0)
    return (u8 *)sAncientGearBeastSortName;
  if (cardId == 0x03D1)
    return (u8 *)sAncientGearCannonSortName;
  if (cardId == 0x03D2)
    return (u8 *)sAncientGearCastleSortName;
  if (cardId == 0x03D3)
    return (u8 *)sCyberDragonInfinitySortName;
  if (cardId == 0x03D4)
    return (u8 *)sEvolzarDolkkaSortName;
  if (cardId == 0x03D5)
    return (u8 *)sHonestSortName;
  if (cardId == 0x03D6)
    return (u8 *)sJunkSynchronSortName;
  if (cardId == 0x03D7)
    return (u8 *)sAmazonessAugustaSortName;
  if (cardId == 0x03D8)
    return (u8 *)sAmazonessEmpressSortName;
  if (cardId == 0x03D9)
    return (u8 *)sAmazonessPrincessSortName;
  if (cardId == 0x03DA)
    return (u8 *)sAmazonessQueenSortName;
  if (cardId == 0x03DB)
    return (u8 *)sAmazonessCallSortName;
  if (cardId == 0x03DC)
    return (u8 *)sAmazonessOnslaughtSortName;
  if (cardId == 0x03DD)
    return (u8 *)sAmazonessVillageSortName;
  if (cardId == 0x03DE)
    return (u8 *)sAshBlossomAndJoyousSpringSortName;
  if (cardId == 0x03DF)
    return (u8 *)sForbiddenChaliceSortName;
  if (cardId == 0x03E0)
    return (u8 *)sForbiddenLanceSortName;
  if (cardId == 0x03E1)
    return (u8 *)sGravekeepersChiefSortName;
  if (cardId == 0x03E2)
    return (u8 *)sGravekeepersCommandantSortName;
  if (cardId == 0x03E3)
    return (u8 *)sGravekeepersHeadmanSortName;
  if (cardId == 0x03E4)
    return (u8 *)sGravekeepersOracleSortName;
  if (cardId == 0x03E5)
    return (u8 *)sGravekeepersRecruiterSortName;
  if (cardId == 0x03E6)
    return (u8 *)sGravekeepersSpiritualistSortName;
  if (cardId == 0x03E7)
    return (u8 *)sGravekeepersTrapSortName;
  if (cardId == 0x03E8)
    return (u8 *)sImperialTombsOfNecrovalleySortName;
  if (cardId == 0x03E9)
    return (u8 *)sInfiniteImpermanenceSortName;
  if (cardId == 0x03EA)
    return (u8 *)sHiddenTemplesOfNecrovalleySortName;
  if (cardId == 0x03EB)
    return (u8 *)sLightningStormSortName;
  if (cardId == 0x03EC)
    return (u8 *)sPotOfAvariceSortName;
  if (cardId == 0x03ED)
    return (u8 *)sNumber39UtopiaSortName;
  if (cardId == 0x03EE)
    return (u8 *)sMaxxCSortName;
  if (cardId == 0x03EF)
    return (u8 *)sToadallyAwesomeSortName;

  return gCardNames[cardId];
}

static u16 GetCustomCardNameSortOrder(u16 cardId) {
  u16 i;

  for (i = 0; i < NUM_CUSTOM_NAME_SORT_CARDS; i++)
    if (sCustomCardsByName[i] == cardId)
      return sCustomCardNameSortOrder[i];

  return 0;
}
