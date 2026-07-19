#include "global.h"

#define NUM_CUSTOM_NAME_SORT_CARDS 1193

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
static const u8 sElementalHeroMudballmanSortName[] APPEND_RODATA = "Elemental HERO Mudballman";
static const u8 sHarpieLady1SortName[] APPEND_RODATA = "Harpie Lady 1";
static const u8 sHarpieLady2SortName[] APPEND_RODATA = "Harpie Lady 2";
static const u8 sHarpieLady3SortName[] APPEND_RODATA = "Harpie Lady 3";
static const u8 sSpellEconomicsSortName[] APPEND_RODATA = "Spell Economics";
static const u8 sTheUnstoppableExodiaIncarnateSortName[] APPEND_RODATA = "The Unstoppable Exodia Incarnate";
static const u8 sTheSanctuaryInTheSkySortName[] APPEND_RODATA = "The Sanctuary in the Sky";
static const u8 sMirrorForceSortName[] APPEND_RODATA = "Mirror Force";
static const u8 sLevelLimitAreaASortName[] APPEND_RODATA = "Level Limit - Area A";
static const u8 sHarpiesPetBabyDragonSortName[] APPEND_RODATA = "Harpie's Pet Baby Dragon";
static const u8 sBlueEyesChaosDragonSortName[] APPEND_RODATA = "Blue-Eyes Chaos Dragon";
static const u8 sBlowbackDragonSortName[] APPEND_RODATA = "Blowback Dragon";
static const u8 sChaosCommandMagicianSortName[] APPEND_RODATA = "Chaos Command Magician";
static const u8 sBookOfLifeSortName[] APPEND_RODATA = "Book of Life";
static const u8 sBookOfTaiyouSortName[] APPEND_RODATA = "Book of Taiyou";
static const u8 sDeFusionSortName[] APPEND_RODATA = "De-Fusion";
static const u8 sDiffusionWaveMotionSortName[] APPEND_RODATA = "Diffusion Wave-Motion";
static const u8 sAutonomousActionUnitSortName[] APPEND_RODATA = "Autonomous Action Unit";
static const u8 sElementalHeroRampartBlasterSortName[] APPEND_RODATA = "Elemental HERO Rampart Blaster";
static const u8 sALegendaryOceanSortName[] APPEND_RODATA = "A Legendary Ocean";
static const u8 sDarkMagicianOfChaosSortName[] APPEND_RODATA = "Dark Magician of Chaos";
static const u8 sDedicationThroughLightAndDarknessSortName[] APPEND_RODATA = "Dedication through Light and Darkness";
static const u8 sElementalHeroSteamHealerSortName[] APPEND_RODATA = "Elemental HERO Steam Healer";
static const u8 sElementalHeroPhoenixEnforcerSortName[] APPEND_RODATA = "Elemental HERO Phoenix Enforcer";
static const u8 sElementalHeroShiningPhoenixEnforcerSortName[] APPEND_RODATA = "Elemental HERO Shining Phoenix Enforcer";
static const u8 sElementalHeroFlameWingmanSortName[] APPEND_RODATA = "Elemental HERO Flame Wingman";
static const u8 sElementalHeroShiningFlareWingmanSortName[] APPEND_RODATA = "Elemental HERO Shining Flare Wingman";
static const u8 sElementalHeroTempestSortName[] APPEND_RODATA = "Elemental HERO Tempest";
static const u8 sElementalHeroWildedgeSortName[] APPEND_RODATA = "Elemental HERO Wildedge";
static const u8 sElementalHeroThunderGiantSortName[] APPEND_RODATA = "Elemental HERO Thunder Giant";
static const u8 sElementalHeroMarinerSortName[] APPEND_RODATA = "Elemental HERO Mariner";
static const u8 sElementalHeroElectrumSortName[] APPEND_RODATA = "Elemental HERO Electrum";
static const u8 sElementalHeroNecroshadeSortName[] APPEND_RODATA = "Elemental HERO Necroshade";
static const u8 sMiracleFusionSortName[] APPEND_RODATA = "Miracle Fusion";
static const u8 sTheAgentOfForceMarsSortName[] APPEND_RODATA = "The Agent of Force - Mars";
static const u8 sChaosEmperorDragonEnvoyOfTheEndSortName[] APPEND_RODATA = "Chaos Emperor Dragon - Envoy of the End";
static const u8 sBlackLusterSoldierEnvoyOfTheBeginningSortName[] APPEND_RODATA = "Black Luster Soldier - Envoy of the Beginning";
static const u8 sElementalHeroNeosSortName[] APPEND_RODATA = "Elemental HERO Neos";
static const u8 sElementalHeroWoodsmanSortName[] APPEND_RODATA = "Elemental HERO Woodsman";
static const u8 sElementalHeroOceanSortName[] APPEND_RODATA = "Elemental HERO Ocean";
static const u8 sElementalHeroHeatSortName[] APPEND_RODATA = "Elemental HERO Heat";
static const u8 sElementalHeroLadyHeatSortName[] APPEND_RODATA = "Elemental HERO Lady Heat";
static const u8 sElementalHeroNeosAliusSortName[] APPEND_RODATA = "Elemental HERO Neos Alius";
static const u8 sElementalHeroGreatTornadoSortName[] APPEND_RODATA = "Elemental HERO Great Tornado";
static const u8 sElementalHeroTerraFirmaSortName[] APPEND_RODATA = "Elemental HERO Terra Firma";
static const u8 sElementalHeroKnospeSortName[] APPEND_RODATA = "Elemental HERO Knospe";
static const u8 sElementalHeroPoisonRoseSortName[] APPEND_RODATA = "Elemental HERO Poison Rose";
static const u8 sElementalHeroAbsoluteZeroSortName[] APPEND_RODATA = "Elemental HERO Absolute Zero";
static const u8 sElementalHeroWildWingmanSortName[] APPEND_RODATA = "Elemental HERO Wild Wingman";
static const u8 sElementalHeroVolticSortName[] APPEND_RODATA = "Elemental HERO Voltic";
static const u8 sElementalHeroFlashSortName[] APPEND_RODATA = "Elemental HERO Flash";
static const u8 sElementalHeroGaiaSortName[] APPEND_RODATA = "Elemental HERO Gaia";
static const u8 sElementalHeroEscuridaoSortName[] APPEND_RODATA = "Elemental HERO Escuridao";
static const u8 sElementalHeroTheShiningSortName[] APPEND_RODATA = "Elemental HERO The Shining";
static const u8 sElementalHeroInfernoSortName[] APPEND_RODATA = "Elemental HERO Inferno";
static const u8 sElementalHeroNecroidShamanSortName[] APPEND_RODATA = "Elemental HERO Necroid Shaman";
static const u8 sElementalHeroPlasmaViceSortName[] APPEND_RODATA = "Elemental HERO Plasma Vice";
static const u8 sFusionRecoverySortName[] APPEND_RODATA = "Fusion Recovery";
static const u8 sSkyscraperSortName[] APPEND_RODATA = "Skyscraper";
static const u8 sHHeatedHeartSortName[] APPEND_RODATA = "H - Heated Heart";
static const u8 sEEmergencyCallSortName[] APPEND_RODATA = "E - Emergency Call";
static const u8 sRRighteousJusticeSortName[] APPEND_RODATA = "R - Righteous Justice";
static const u8 sOOversoulSortName[] APPEND_RODATA = "O - Oversoul";
static const u8 sFutureFusionSortName[] APPEND_RODATA = "Future Fusion";
static const u8 sElementalHeroCoreSortName[] APPEND_RODATA = "Elemental HERO Core";
static const u8 sElementalHeroSunriseSortName[] APPEND_RODATA = "Elemental HERO Sunrise";
static const u8 sElementalHeroCaptainGoldSortName[] APPEND_RODATA = "Elemental HERO Captain Gold";
static const u8 sElementalHeroIceEdgeSortName[] APPEND_RODATA = "Elemental HERO Ice Edge";
static const u8 sElementalHeroBlazemanSortName[] APPEND_RODATA = "Elemental HERO Blazeman";
static const u8 sElementalHeroStratosSortName[] APPEND_RODATA = "Elemental HERO Stratos";
static const u8 sChimeratechOverdragonSortName[] APPEND_RODATA = "Chimeratech Overdragon";
static const u8 sCyberneticFusionSupportSortName[] APPEND_RODATA = "Cybernetic Fusion Support";
static const u8 sOverloadFusionSortName[] APPEND_RODATA = "Overload Fusion";
static const u8 sPowerBondSortName[] APPEND_RODATA = "Power Bond";
static const u8 sFusionSageSortName[] APPEND_RODATA = "Fusion Sage";
static const u8 sLyriluscIndependentNightingaleSortName[] APPEND_RODATA = "Lyrilusc - Independent Nightingale";
static const u8 sTheTyrantNeptuneSortName[] APPEND_RODATA = "The Tyrant Neptune";
static const u8 sTheSplendidVenusSortName[] APPEND_RODATA = "The Splendid Venus";
static const u8 sTheBigSaturnSortName[] APPEND_RODATA = "The Big Saturn";
static const u8 sTheTripperMercurySortName[] APPEND_RODATA = "The Tripper Mercury";
static const u8 sTheGrandJupiterSortName[] APPEND_RODATA = "The Grand Jupiter";
static const u8 sTheDespairUranusSortName[] APPEND_RODATA = "The Despair Uranus";
static const u8 sTheBlazingMarsSortName[] APPEND_RODATA = "The Blazing Mars";
static const u8 sTheSuppressionPlutoSortName[] APPEND_RODATA = "The Suppression Pluto";
static const u8 sTheSupremacySunSortName[] APPEND_RODATA = "The Supremacy Sun";
static const u8 sMightyAngelVirchSortName[] APPEND_RODATA = "Mighty Angel Virch";
static const u8 sTinyAngelSortName[] APPEND_RODATA = "Tiny Angel";
static const u8 sZerielSortName[] APPEND_RODATA = "Zeriel";
static const u8 sShatielSortName[] APPEND_RODATA = "Shatiel";
static const u8 sSeraphimBlasterSortName[] APPEND_RODATA = "Seraphim Blaster";
static const u8 sIofielSortName[] APPEND_RODATA = "Iofiel";
static const u8 sArchlordKristyaSortName[] APPEND_RODATA = "Archlord Kristya";
static const u8 sTethysGoddessOfLightSortName[] APPEND_RODATA = "Tethys, Goddess of Light";
static const u8 sAthenaSortName[] APPEND_RODATA = "Athena";
static const u8 sValhallaHallOfTheFallenSortName[] APPEND_RODATA = "Valhalla, Hall of the Fallen";
static const u8 sAngelsTearSortName[] APPEND_RODATA = "Angel's Tear";
static const u8 sDivineSanctuarySortName[] APPEND_RODATA = "Divine Sanctuary";
static const u8 sCourtOfJusticeSortName[] APPEND_RODATA = "Court of Justice";
static const u8 sHecatriceSortName[] APPEND_RODATA = "Hecatrice";
static const u8 sPrematureBurialSortName[] APPEND_RODATA = "Premature Burial";
static const u8 sYubelSortName[] APPEND_RODATA = "Yubel";
static const u8 sYubelTerrorIncarnateSortName[] APPEND_RODATA = "Yubel - Terror Incarnate";
static const u8 sYubelTheUltimateNightmareSortName[] APPEND_RODATA = "Yubel - The Ultimate Nightmare";
static const u8 sTheTrickySortName[] APPEND_RODATA = "The Tricky";
static const u8 sTheWickedDreadrootSortName[] APPEND_RODATA = "The Wicked Dreadroot";
static const u8 sTheWickedEraserSortName[] APPEND_RODATA = "The Wicked Eraser";
static const u8 sTheWickedAvatarSortName[] APPEND_RODATA = "The Wicked Avatar";
static const u8 sTributeDollSortName[] APPEND_RODATA = "Tribute Doll";
static const u8 sTradeInSortName[] APPEND_RODATA = "Trade-In";
static const u8 sCyberBarrierDragonSortName[] APPEND_RODATA = "Cyber Barrier Dragon";
static const u8 sCyberLaserDragonSortName[] APPEND_RODATA = "Cyber Laser Dragon";
static const u8 sDarkEndDragonSortName[] APPEND_RODATA = "Dark End Dragon";
static const u8 sLightEndDragonSortName[] APPEND_RODATA = "Light End Dragon";
static const u8 sDarkArmedDragonSortName[] APPEND_RODATA = "Dark Armed Dragon";
static const u8 sAHeroEmergesSortName[] APPEND_RODATA = "A Hero Emerges";
static const u8 sAHeroLivesSortName[] APPEND_RODATA = "A Hero Lives";
static const u8 sAWingbeatOfGiantDragonSortName[] APPEND_RODATA = "A Wingbeat of Giant Dragon";
static const u8 sAllureOfDarknessSortName[] APPEND_RODATA = "Allure of Darkness";
static const u8 sAmuletDragonSortName[] APPEND_RODATA = "Amulet Dragon";
static const u8 sAndroSphinxSortName[] APPEND_RODATA = "Andro Sphinx";
static const u8 sAntiSpellFragranceSortName[] APPEND_RODATA = "Anti-Spell Fragrance";
static const u8 sAppropriateSortName[] APPEND_RODATA = "Appropriate";
static const u8 sApprenticeIllusionMagicianSortName[] APPEND_RODATA = "Apprentice Illusion Magician";
static const u8 sApparationSortName[] APPEND_RODATA = "Apparition";
static const u8 sAttackGuidanceArmorSortName[] APPEND_RODATA = "Attack Guidance Armor";
static const u8 sAttackReflectorUnitSortName[] APPEND_RODATA = "Attack Reflector Unit";
static const u8 sBackupSquadSortName[] APPEND_RODATA = "Backup Squad";
static const u8 sArmageddonKnightSortName[] APPEND_RODATA = "Armageddon Knight";
static const u8 sArmedDragonLv3SortName[] APPEND_RODATA = "Armed Dragon LV3";
static const u8 sArmedDragonLv5SortName[] APPEND_RODATA = "Armed Dragon LV5";
static const u8 sArmedDragonLv7SortName[] APPEND_RODATA = "Armed Dragon LV7";
static const u8 sArmedDragonLv10SortName[] APPEND_RODATA = "Armed Dragon LV10";
static const u8 sAttackAndReceiveSortName[] APPEND_RODATA = "Attack and Receive";
static const u8 sBackfireSortName[] APPEND_RODATA = "Backfire";
static const u8 sHamonLordOfStrikingThunderSortName[] APPEND_RODATA = "Hamon, Lord of Striking Thunder";
static const u8 sUriaLordOfSearingFlamesSortName[] APPEND_RODATA = "Uria, Lord of Searing Flames";
static const u8 sRavielLordOfPhantasmsSortName[] APPEND_RODATA = "Raviel, Lord of Phantasms";
static const u8 sBerserkerSoulSortName[] APPEND_RODATA = "Berserker Soul";
static const u8 sBirdfaceSortName[] APPEND_RODATA = "Birdface";
static const u8 sBlueEyesAlternativeUltimateDragonSortName[] APPEND_RODATA = "Blue-Eyes Alternative Ultimate Dragon";
static const u8 sBreakTheDestinySortName[] APPEND_RODATA = "Break the Destiny";
static const u8 sBubbleBlasterSortName[] APPEND_RODATA = "Bubble Blaster";
static const u8 sBurdenOfTheMightySortName[] APPEND_RODATA = "Burden of the Mighty";
static const u8 sCallOfTheMummySortName[] APPEND_RODATA = "Call of the Mummy";
static const u8 sCannonballSpearShellfishSortName[] APPEND_RODATA = "Cannonball Spear Shellfish";
static const u8 sCelestialSwordEatosSortName[] APPEND_RODATA = "Celestial Sword - Eatos";
static const u8 sChaosFormSortName[] APPEND_RODATA = "Chaos Form";
static const u8 sChickenGameSortName[] APPEND_RODATA = "Chicken Game";
static const u8 sChimeratechFortressDragonSortName[] APPEND_RODATA = "Chimeratech Fortress Dragon";
static const u8 sChimeratechMegafleetDragonSortName[] APPEND_RODATA = "Chimeratech Megafleet Dragon";
static const u8 sChimeratechRampageDragonSortName[] APPEND_RODATA = "Chimeratech Rampage Dragon";
static const u8 sClockTowerPrisonSortName[] APPEND_RODATA = "Clock Tower Prison";
static const u8 sColdWaveSortName[] APPEND_RODATA = "Cold Wave";
static const u8 sContinuousDestructionPunchSortName[] APPEND_RODATA = "Continuous Destruction Punch";
static const u8 sCyberEltaninSortName[] APPEND_RODATA = "Cyber Eltanin";
static const u8 sCyberKirinSortName[] APPEND_RODATA = "Cyber Kirin";
static const u8 sCyberPhoenixSortName[] APPEND_RODATA = "Cyber Phoenix";
static const u8 sCyberValleySortName[] APPEND_RODATA = "Cyber Valley";
static const u8 sCyberneticZoneSortName[] APPEND_RODATA = "Cybernetic Zone";
static const u8 sDTacticsSortName[] APPEND_RODATA = "D - Tactics";
static const u8 sDTimeSortName[] APPEND_RODATA = "D - Time";
static const u8 sDamagePolarizerSortName[] APPEND_RODATA = "Damage Polarizer";
static const u8 sDBurstSortName[] APPEND_RODATA = "D - Burst";
static const u8 sDForceSortName[] APPEND_RODATA = "D - Force";
static const u8 sDarkBladeTheDragonKnightSortName[] APPEND_RODATA = "Dark Blade the Dragon Knight";
static const u8 sDarkGrepherSortName[] APPEND_RODATA = "Dark Grepher";
static const u8 sDarkMagicianGirlTheDragonKnightSortName[] APPEND_RODATA = "Dark Magician Girl the Dragon Knight";
static const u8 sDarklordNurseReficuleSortName[] APPEND_RODATA = "Darklord Nurse Reficule";
static const u8 sDarknessNeosphereSortName[] APPEND_RODATA = "Darkness Neosphere";
static const u8 sDarkCityAtMidnightSortName[] APPEND_RODATA = "Dark City at Midnight";
static const u8 sDarkMagicianTheDragonKnightSortName[] APPEND_RODATA = "Dark Magician the Dragon Knight";
static const u8 sDecoyDragonSortName[] APPEND_RODATA = "Decoy Dragon";
static const u8 sDesCounterblowSortName[] APPEND_RODATA = "Des Counterblow";
static const u8 sDespairFromTheDarkSortName[] APPEND_RODATA = "Despair from the Dark";
static const u8 sDestinyDrawSortName[] APPEND_RODATA = "Destiny Draw";
static const u8 sDestinyEndDragoonSortName[] APPEND_RODATA = "Destiny End Dragoon";
static const u8 sDestinyHeroBladeMasterSortName[] APPEND_RODATA = "Destiny HERO - Blade Master";
static const u8 sDestinyHeroCaptainTenaciousSortName[] APPEND_RODATA = "Destiny HERO - Captain Tenacious";
static const u8 sDestinyHeroCelestialSortName[] APPEND_RODATA = "Destiny HERO - Celestial";
static const u8 sDestinyHeroDangerousSortName[] APPEND_RODATA = "Destiny HERO - Dangerous";
static const u8 sDestinyHeroDarkAngelSortName[] APPEND_RODATA = "Destiny HERO - Dark Angel";
static const u8 sDestinyHeroDasherSortName[] APPEND_RODATA = "Destiny HERO - Dasher";
static const u8 sDestinyHeroDeciderSortName[] APPEND_RODATA = "Destiny HERO - Decider";
static const u8 sDestinyHeroDefenderSortName[] APPEND_RODATA = "Destiny HERO - Defender";
static const u8 sDestinyHeroDenierSortName[] APPEND_RODATA = "Destiny HERO - Denier";
static const u8 sDestinyHeroDestroyerPhoenixEnforcerSortName[] APPEND_RODATA = "Destiny HERO - Destroyer Phoenix Enforcer";
static const u8 sDestinyHeroDiamondDudeSortName[] APPEND_RODATA = "Destiny HERO - Diamond Dude";
static const u8 sDestinyHeroDiskCommanderSortName[] APPEND_RODATA = "Destiny HERO - Disk Commander";
static const u8 sDestinyHeroDogmaSortName[] APPEND_RODATA = "Destiny HERO - Dogma";
static const u8 sDestinyHeroDominanceSortName[] APPEND_RODATA = "Destiny HERO - Dominance";
static const u8 sDestinyHeroDoomLordSortName[] APPEND_RODATA = "Destiny HERO - Doom Lord";
static const u8 sDestinyHeroDoubleDudeSortName[] APPEND_RODATA = "Destiny HERO - Double Dude";
static const u8 sDestinyHeroDrawhandSortName[] APPEND_RODATA = "Destiny HERO - Drawhand";
static const u8 sDestinyHeroDreadServantSortName[] APPEND_RODATA = "Destiny HERO - Dread Servant";
static const u8 sDestinyHeroDreadmasterSortName[] APPEND_RODATA = "Destiny HERO - Dreadmaster";
static const u8 sDestinyHeroDoomOverlordSortName[] APPEND_RODATA = "Destiny HERO - Doom Overlord";
static const u8 sDestinyHeroDreadnoughtMasterSortName[] APPEND_RODATA = "Destiny HERO - Dreadnought Master";
static const u8 sDestinyHeroDreadnoughtServantSortName[] APPEND_RODATA = "Destiny HERO - Dreadnought Servant";
static const u8 sDestinyHeroDreamerSortName[] APPEND_RODATA = "Destiny HERO - Dreamer";
static const u8 sDestinyHeroDrilldarkSortName[] APPEND_RODATA = "Destiny HERO - Drilldark";
static const u8 sDestinyHeroDunkerSortName[] APPEND_RODATA = "Destiny HERO - Dunker";
static const u8 sDestinyHeroDynatagSortName[] APPEND_RODATA = "Destiny HERO - Dynatag";
static const u8 sDestinyHeroDystopiaSortName[] APPEND_RODATA = "Destiny HERO - Dystopia";
static const u8 sDestinyHeroFearMongerSortName[] APPEND_RODATA = "Destiny HERO - Fear Monger";
static const u8 sDestinyHeroMaliciousSortName[] APPEND_RODATA = "Destiny HERO - Malicious";
static const u8 sDestinyHeroPlasmaSortName[] APPEND_RODATA = "Destiny HERO - Plasma";
static const u8 sDifferentDimensionCapsuleSortName[] APPEND_RODATA = "Different Dimension Capsule";
static const u8 sDestinyHeroDusktopiaSortName[] APPEND_RODATA = "Destiny HERO - Dusktopia";
static const u8 sDimensionFusionSortName[] APPEND_RODATA = "Dimension Fusion";
static const u8 sDivineSerpentGehSortName[] APPEND_RODATA = "Divine Serpent Geh";
static const u8 sDonZaloogSortName[] APPEND_RODATA = "Don Zaloog";
static const u8 sDoubleSpellSortName[] APPEND_RODATA = "Double Spell";
static const u8 sDragonSRageSortName[] APPEND_RODATA = "Dragon's Rage";
static const u8 sDestinyHeroDestroyDogmaSortName[] APPEND_RODATA = "Destiny HERO - Destro-Dogma";
static const u8 sDoctorDSortName[] APPEND_RODATA = "Doctor D";
static const u8 sDoomVirusDragonSortName[] APPEND_RODATA = "Doom Virus Dragon";
static const u8 sDoppelgangerSortName[] APPEND_RODATA = "Doppelganger";
static const u8 sEgyptianGodSlimeSortName[] APPEND_RODATA = "Egyptian God Slime";
static const u8 sElementalHeroNeosKlugerSortName[] APPEND_RODATA = "Elemental HERO Neos Kluger";
static const u8 sEmergencyProvisionsSortName[] APPEND_RODATA = "Emergency Provisions";
static const u8 sExodiusTheUltimateForbiddenLordSortName[] APPEND_RODATA = "Exodius the Ultimate Forbidden Lord";
static const u8 sFatalAbacusSortName[] APPEND_RODATA = "Fatal Abacus";
static const u8 sFelgrandDragonSortName[] APPEND_RODATA = "Felgrand Dragon";
static const u8 sFiresOfDoomsdaySortName[] APPEND_RODATA = "Fires of Doomsday";
static const u8 sForcedRequisitionSortName[] APPEND_RODATA = "Forced Requisition";
static const u8 sDrainTimeSortName[] APPEND_RODATA = "Drain Time";
static const u8 sFieldsSanctuarySortName[] APPEND_RODATA = "Fields Sanctuary";
static const u8 sFusionDestinySortName[] APPEND_RODATA = "Fusion Destiny";
static const u8 sFusionGateSortName[] APPEND_RODATA = "Fusion Gate";
static const u8 sGateGuardiansCombinedSortName[] APPEND_RODATA = "Gate Guardians Combined";
static const u8 sGiftCardSortName[] APPEND_RODATA = "Gift Card";
static const u8 sGoddessBowSortName[] APPEND_RODATA = "Goddess Bow";
static const u8 sGorzTheEmissaryOfDarknessSortName[] APPEND_RODATA = "Gorz the Emissary of Darkness";
static const u8 sGranmargTheRockMonarchSortName[] APPEND_RODATA = "Granmarg the Rock Monarch";
static const u8 sGreenGadgetSortName[] APPEND_RODATA = "Green Gadget";
static const u8 sGroundCollapseSortName[] APPEND_RODATA = "Ground Collapse";
static const u8 sGuardianDreadscytheSortName[] APPEND_RODATA = "Guardian Dreadscythe";
static const u8 sHarpieLadyPhoenixFormationSortName[] APPEND_RODATA = "Harpie Lady Phoenix Formation";
static const u8 sHeroFlashSortName[] APPEND_RODATA = "Hero Flash!!";
static const u8 sInsectImitationSortName[] APPEND_RODATA = "Insect Imitation";
static const u8 sInstantFusionSortName[] APPEND_RODATA = "Instant Fusion";
static const u8 sGuardianEatosSortName[] APPEND_RODATA = "Guardian Eatos";
static const u8 sHeraldOfCreationSortName[] APPEND_RODATA = "Herald of Creation";
static const u8 sHolactieTheCreatorOfLightSortName[] APPEND_RODATA = "Holactie the Creator of Light";
static const u8 sHorusTheBlackFlameDragonLv8SortName[] APPEND_RODATA = "Horus the Black Flame Dragon LV8";
static const u8 sHorusTheBlackFlameDragonLv4SortName[] APPEND_RODATA = "Horus the Black Flame Dragon LV4";
static const u8 sHorusTheBlackFlameDragonLv6SortName[] APPEND_RODATA = "Horus the Black Flame Dragon LV6";
static const u8 sJowgenTheSpiritualistSortName[] APPEND_RODATA = "Jowgen the Spiritualist";
static const u8 sJudgmentDragonSortName[] APPEND_RODATA = "Judgment Dragon";
static const u8 sKingDragunSortName[] APPEND_RODATA = "King Dragun";
static const u8 sKingOfTheSwampSortName[] APPEND_RODATA = "King of the Swamp";
static const u8 sKurazTheLightMonarchSortName[] APPEND_RODATA = "Kuraz the Light Monarch";
static const u8 sKuribanditSortName[] APPEND_RODATA = "Kuribandit";
static const u8 sLastTurnSortName[] APPEND_RODATA = "Last Turn";
static const u8 sLegendOfHeartSortName[] APPEND_RODATA = "Legend of Heart";
static const u8 sLegendaryFlameLordSortName[] APPEND_RODATA = "Legendary Flame Lord";
static const u8 sKingTigerWanghuSortName[] APPEND_RODATA = "King Tiger Wanghu";
static const u8 sLegendaryKnightCritiasSortName[] APPEND_RODATA = "Legendary Knight Critias";
static const u8 sLegendaryKnightHermosSortName[] APPEND_RODATA = "Legendary Knight Hermos";
static const u8 sLegendaryKnightTimaeusSortName[] APPEND_RODATA = "Legendary Knight Timaeus";
static const u8 sLekungaSortName[] APPEND_RODATA = "Lekunga";
static const u8 sLightAndDarknessDragonSortName[] APPEND_RODATA = "Light and Darkness Dragon";
static const u8 sLordOfTheRedSortName[] APPEND_RODATA = "Lord of the Red";
static const u8 sMaAtSortName[] APPEND_RODATA = "Ma'at";
static const u8 sMagicalDimensionSortName[] APPEND_RODATA = "Magical Dimension";
static const u8 sMagicalHatsSortName[] APPEND_RODATA = "Magical Hats";
static const u8 sMagicalPlantMandragolaSortName[] APPEND_RODATA = "Magical Plant Mandragola";
static const u8 sMagicalScientistSortName[] APPEND_RODATA = "Magical Scientist";
static const u8 sMagicalStoneExcavationSortName[] APPEND_RODATA = "Magical Stone Excavation";
static const u8 sMajesticMechGoryuSortName[] APPEND_RODATA = "Majestic Mech - Goryu";
static const u8 sManjuOfTheTenThousandHandsSortName[] APPEND_RODATA = "Manju of the Ten Thousand Hands";
static const u8 sMarshmallonSortName[] APPEND_RODATA = "Marshmallon";
static const u8 sMaskOfDispelSortName[] APPEND_RODATA = "Mask of Dispel";
static const u8 sMasterPeaceTheTrueDracoslayingKingSortName[] APPEND_RODATA = "Master Peace, the True Dracoslaying King";
static const u8 sMaskOfTheAccursedSortName[] APPEND_RODATA = "Mask of the Accursed";
static const u8 sMausoleumOfTheEmperorSortName[] APPEND_RODATA = "Mausoleum of the Emperor";
static const u8 sMazeraDevilleSortName[] APPEND_RODATA = "Mazera DeVille";
static const u8 sMetamorphosisSortName[] APPEND_RODATA = "Metamorphosis";
static const u8 sMeteorainSortName[] APPEND_RODATA = "Meteorain";
static const u8 sMirageOfNightmareSortName[] APPEND_RODATA = "Mirage of Nightmare";
static const u8 sMirrorForceDragonSortName[] APPEND_RODATA = "Mirror Force Dragon";
static const u8 sMoltenZombieSortName[] APPEND_RODATA = "Molten Zombie";
static const u8 sMonsterGateSortName[] APPEND_RODATA = "Monster Gate";
static const u8 sMonsterRecoverySortName[] APPEND_RODATA = "Monster Recovery";
static const u8 sMoraleBoostSortName[] APPEND_RODATA = "Morale Boost";
static const u8 sMucusYolkSortName[] APPEND_RODATA = "Mucus Yolk";
static const u8 sMystikWokSortName[] APPEND_RODATA = "Mystik Wok";
static const u8 sNecrovalleySortName[] APPEND_RODATA = "Necrovalley";
static const u8 sNeedleWallSortName[] APPEND_RODATA = "Needle Wall";
static const u8 sNeoBlueEyesUltimateDragonSortName[] APPEND_RODATA = "Neo Blue-Eyes Ultimate Dragon";
static const u8 sNeosWisemanSortName[] APPEND_RODATA = "Neos Wiseman";
static const u8 sNibiruThePrimalBeingSortName[] APPEND_RODATA = "Nibiru, the Primal Being";
static const u8 sNuminousHealerSortName[] APPEND_RODATA = "Numinous Healer";
static const u8 sOjamaKingSortName[] APPEND_RODATA = "Ojama King";
static const u8 sOrichalcosShunorosSortName[] APPEND_RODATA = "Orichalcos Shunoros";
static const u8 sOverDestinySortName[] APPEND_RODATA = "Over Destiny";
static const u8 sPainfulChoiceSortName[] APPEND_RODATA = "Painful Choice";
static const u8 sPandemoniumSortName[] APPEND_RODATA = "Pandemonium";
static const u8 sParallelWorldFusionSortName[] APPEND_RODATA = "Parallel World Fusion";
static const u8 sPhotonGeneratorUnitSortName[] APPEND_RODATA = "Photon Generator Unit";
static const u8 sPoisonOfTheOldManSortName[] APPEND_RODATA = "Poison of the Old Man";
static const u8 sProtectorOfTheSanctuarySortName[] APPEND_RODATA = "Protector of the Sanctuary";
static const u8 sQuintetMagicianSortName[] APPEND_RODATA = "Quintet Magician";
static const u8 sRaigekiBreakSortName[] APPEND_RODATA = "Raigeki Break";
static const u8 sProphecySortName[] APPEND_RODATA = "Prophecy";
static const u8 sReaperScytheDreadscytheSortName[] APPEND_RODATA = "Reaper Scythe - Dreadscythe";
static const u8 sRedEyesBlackDragonSwordSortName[] APPEND_RODATA = "Red-Eyes Black Dragon Sword";
static const u8 sRedEyesDarkDragoonSortName[] APPEND_RODATA = "Red-Eyes Dark Dragoon";
static const u8 sRedEyesDarknessMetalDragonSortName[] APPEND_RODATA = "Red-Eyes Darkness Metal Dragon";
static const u8 sRedEyesTransmigrationSortName[] APPEND_RODATA = "Red-Eyes Transmigration";
static const u8 sRedGadgetSortName[] APPEND_RODATA = "Red Gadget";
static const u8 sRelaySoulSortName[] APPEND_RODATA = "Relay Soul";
static const u8 sReverseOfReverseSortName[] APPEND_RODATA = "Reverse of Reverse";
static const u8 sRocketHermosCannonSortName[] APPEND_RODATA = "Rocket Hermos Cannon";
static const u8 sRopeOfLifeSortName[] APPEND_RODATA = "Rope of Life";
static const u8 sRoyalMagicalLibrarySortName[] APPEND_RODATA = "Royal Magical Library";
static const u8 sScapegoatSortName[] APPEND_RODATA = "Scapegoat";
static const u8 sSecondCoinTossSortName[] APPEND_RODATA = "Second Coin Toss";
static const u8 sSecretVillageOfTheSpellcastersSortName[] APPEND_RODATA = "Secret Village of the Spellcasters";
static const u8 sShareThePainSortName[] APPEND_RODATA = "Share the Pain";
static const u8 sSixthSenseSortName[] APPEND_RODATA = "Sixth Sense";
static const u8 sSkilledDarkMagicianSortName[] APPEND_RODATA = "Skilled Dark Magician";
static const u8 sSkilledWhiteMagicianSortName[] APPEND_RODATA = "Skilled White Magician";
static const u8 sSolemnJudgmentSortName[] APPEND_RODATA = "Solemn Judgment";
static const u8 sSparkBlasterSortName[] APPEND_RODATA = "Spark Blaster";
static const u8 sSkyscraper2HeroCitySortName[] APPEND_RODATA = "Skyscraper 2 - Hero City";
static const u8 sSpellAbsorptionSortName[] APPEND_RODATA = "Spell Absorption";
static const u8 sSphinxTeleiaSortName[] APPEND_RODATA = "Sphinx Teleia";
static const u8 sStatueOfTheWickedSortName[] APPEND_RODATA = "Statue of the Wicked";
static const u8 sStaunchDefenderSortName[] APPEND_RODATA = "Staunch Defender";
static const u8 sStrayLambsSortName[] APPEND_RODATA = "Stray Lambs";
static const u8 sStrongholdTheMovingFortressSortName[] APPEND_RODATA = "Stronghold the Moving Fortress";
static const u8 sSummonerMonkSortName[] APPEND_RODATA = "Summoner Monk";
static const u8 sSummonerOfIllusionsSortName[] APPEND_RODATA = "Summoner of Illusions";
static const u8 sSuperPolymerizationSortName[] APPEND_RODATA = "Super Polymerization";
static const u8 sTerraformingSortName[] APPEND_RODATA = "Terraforming";
static const u8 sTheAForcesSortName[] APPEND_RODATA = "The A. Forces";
static const u8 sTheAgentOfJudgmentSaturnSortName[] APPEND_RODATA = "The Agent of Judgment - Saturn";
static const u8 sTheAgentOfWisdomMercurySortName[] APPEND_RODATA = "The Agent of Wisdom - Mercury";
static const u8 sTheClawOfHermosSortName[] APPEND_RODATA = "The Claw of Hermos";
static const u8 sTheCreatorSortName[] APPEND_RODATA = "The Creator";
static const u8 sTheCreatorIncarnateSortName[] APPEND_RODATA = "The Creator Incarnate";
static const u8 sTheEyeOfTimaeusSortName[] APPEND_RODATA = "The Eye of Timaeus";
static const u8 sTheFangOfCritiasSortName[] APPEND_RODATA = "The Fang of Critias";
static const u8 sTheLawOfTheNormalSortName[] APPEND_RODATA = "The Law of the Normal";
static const u8 sTheLegendaryExodiaIncarnateSortName[] APPEND_RODATA = "The Legendary Exodia Incarnate";
static const u8 sTheShallowGraveSortName[] APPEND_RODATA = "The Shallow Grave";
static const u8 sTheinenTheGreatSphinxSortName[] APPEND_RODATA = "Theinen the Great Sphinx";
static const u8 sThestalosTheFirestormMonarchSortName[] APPEND_RODATA = "Thestalos the Firestorm Monarch";
static const u8 sThunderDragonColossusSortName[] APPEND_RODATA = "Thunder Dragon Colossus";
static const u8 sThunderDragonTitanSortName[] APPEND_RODATA = "Thunder Dragon Titan";
static const u8 sTimaeusTheKnightOfDestinySortName[] APPEND_RODATA = "Timaeus the Knight of Destiny";
static const u8 sTimeMagicHammerSortName[] APPEND_RODATA = "Time Magic Hammer";
static const u8 sTornadoWallSortName[] APPEND_RODATA = "Tornado Wall";
static const u8 sToonWorldSortName[] APPEND_RODATA = "Toon World";
static const u8 sTornadoBirdSortName[] APPEND_RODATA = "Tornado Bird";
static const u8 sTrapDustshootSortName[] APPEND_RODATA = "Trap Dustshoot";
static const u8 sTyrantBurstDragonSortName[] APPEND_RODATA = "Tyrant Burst Dragon";
static const u8 sTyrantWingSortName[] APPEND_RODATA = "Tyrant Wing";
static const u8 sUltimateConductorTyrannoSortName[] APPEND_RODATA = "Ultimate Conductor Tyranno";
static const u8 sUltimateObedientFiendSortName[] APPEND_RODATA = "Ultimate Obedient Fiend";
static const u8 sVisionFusionSortName[] APPEND_RODATA = "Vision Fusion";
static const u8 sVisionHeroAdorationSortName[] APPEND_RODATA = "Vision HERO Adoration";
static const u8 sVisionHeroFarisSortName[] APPEND_RODATA = "Vision HERO Faris";
static const u8 sVisionHeroGravitoSortName[] APPEND_RODATA = "Vision HERO Gravito";
static const u8 sVisionHeroIncreaseSortName[] APPEND_RODATA = "Vision HERO Increase";
static const u8 sVisionHeroMinimumRaySortName[] APPEND_RODATA = "Vision HERO Minimum Ray";
static const u8 sVisionHeroMultiplyGuySortName[] APPEND_RODATA = "Vision HERO Multiply Guy";
static const u8 sVisionHeroPoisonerSortName[] APPEND_RODATA = "Vision HERO Poisoner";
static const u8 sVisionHeroTrinitySortName[] APPEND_RODATA = "Vision HERO Trinity";
static const u8 sVisionHeroVyonSortName[] APPEND_RODATA = "Vision HERO Vyon";
static const u8 sVisionReleaseSortName[] APPEND_RODATA = "Vision Release";
static const u8 sWataponSortName[] APPEND_RODATA = "Watapon";
static const u8 sWhiteDragonRitualSortName[] APPEND_RODATA = "White Dragon Ritual";
static const u8 sWildNaturesReleaseSortName[] APPEND_RODATA = "Wild Nature's Release";
static const u8 sWoughtweilerSortName[] APPEND_RODATA = "Wroughtweiler";
static const u8 sYellowGadgetSortName[] APPEND_RODATA = "Yellow Gadget";
static const u8 sVisionHeroWitchRaiderSortName[] APPEND_RODATA = "Vision HERO Witch Raider";
static const u8 sAlluringMirrorSplitSortName[] APPEND_RODATA = "Alluring Mirror Split";
static const u8 sAmbushFangsSortName[] APPEND_RODATA = "Ambush Fangs";
static const u8 sArcaniteMagicianSortName[] APPEND_RODATA = "Arcanite Magician";
static const u8 sArmoryArmSortName[] APPEND_RODATA = "Armory Arm";
static const u8 sAromaBlendSortName[] APPEND_RODATA = "Aroma Blend";
static const u8 sAromaGardenSortName[] APPEND_RODATA = "Aroma Garden";
static const u8 sAromaGardeningSortName[] APPEND_RODATA = "Aroma Gardening";
static const u8 sAromaJarSortName[] APPEND_RODATA = "Aroma Jar";
static const u8 sAromageBergamotSortName[] APPEND_RODATA = "Aromage Bergamot";
static const u8 sAromageCanangaSortName[] APPEND_RODATA = "Aromage Cananga";
static const u8 sAromageJasmineSortName[] APPEND_RODATA = "Aromage Jasmine";
static const u8 sAromageLaurelSortName[] APPEND_RODATA = "Aromage Laurel";
static const u8 sAromageMarjoramSortName[] APPEND_RODATA = "Aromage Marjoram";
static const u8 sAromageRosemarySortName[] APPEND_RODATA = "Aromage Rosemary";
static const u8 sAromalilithMagnoliaSortName[] APPEND_RODATA = "Aromalilith Magnolia";
static const u8 sAromalilithRosalinaSortName[] APPEND_RODATA = "Aromalilith Rosalina";
static const u8 sAromalilithRosemarySortName[] APPEND_RODATA = "Aromalilith Rosemary";
static const u8 sAromaseraphyJasmineSortName[] APPEND_RODATA = "Aromaseraphy Jasmine";
static const u8 sAromaseraphyRosemarySortName[] APPEND_RODATA = "Aromaseraphy Rosemary";
static const u8 sAromaseraphySweetMarjoramSortName[] APPEND_RODATA = "Aromaseraphy Sweet Marjoram";
static const u8 sAttackPheromonesSortName[] APPEND_RODATA = "Attack Pheromones";
static const u8 sAzureEyesSilverDragonSortName[] APPEND_RODATA = "Azure-Eyes Silver Dragon";
static const u8 sBlackRoseDragonSortName[] APPEND_RODATA = "Black Rose Dragon";
static const u8 sBlessedWindsSortName[] APPEND_RODATA = "Blessed Winds";
static const u8 sBlueEyesJetDragonSortName[] APPEND_RODATA = "Blue-Eyes Jet Dragon";
static const u8 sBlueEyesSolidDragonSortName[] APPEND_RODATA = "Blue-Eyes Solid Dragon";
static const u8 sBlueEyesTyrantDragonSortName[] APPEND_RODATA = "Blue-Eyes Tyrant Dragon";
static const u8 sBlueEyesUltimateSpiritDragonSortName[] APPEND_RODATA = "Blue-Eyes Ultimate Spirit Dragon";
static const u8 sBondBetweenTeacherAndStudentSortName[] APPEND_RODATA = "Bond Between Teacher and Student";
static const u8 sBlueEyesSpiritDragonSortName[] APPEND_RODATA = "Blue-Eyes Spirit Dragon";
static const u8 sBrionacDragonOfTheIceBarrierSortName[] APPEND_RODATA = "Brionac, Dragon of the Ice Barrier";
static const u8 sChainMaterialSortName[] APPEND_RODATA = "Chain Material";
static const u8 sColossalFighterSortName[] APPEND_RODATA = "Colossal Fighter";
static const u8 sCupOfAceSortName[] APPEND_RODATA = "Cup of Ace";
static const u8 sCyberSlashHarpieLadySortName[] APPEND_RODATA = "Cyber Slash Harpie Lady";
static const u8 sDamageReptileSortName[] APPEND_RODATA = "Damage = Reptile";
static const u8 sDarkBurningAttackSortName[] APPEND_RODATA = "Dark Burning Attack";
static const u8 sDarkBurningMagicSortName[] APPEND_RODATA = "Dark Burning Magic";
static const u8 sDarkCallingSortName[] APPEND_RODATA = "Dark Calling";
static const u8 sDarkContactSortName[] APPEND_RODATA = "Dark Contact";
static const u8 sDarkFusionSortName[] APPEND_RODATA = "Dark Fusion";
static const u8 sDarkMagicAttackSortName[] APPEND_RODATA = "Dark Magic Attack";
static const u8 sDarkMagicInheritanceSortName[] APPEND_RODATA = "Dark Magic Inheritance";
static const u8 sDarkMagicVeilSortName[] APPEND_RODATA = "Dark Magic Veil";
static const u8 sDarkMagicalCircleSortName[] APPEND_RODATA = "Dark Magical Circle";
static const u8 sDarkMagicianGirlTheMagicianSApprenticeSortName[] APPEND_RODATA = "Dark Magician Girl the Magician's Apprentice";
static const u8 sDarkMagicianOfDestructionSortName[] APPEND_RODATA = "Dark Magician of Destruction";
static const u8 sDarkMagicianTheMagicianOfBlackMagicSortName[] APPEND_RODATA = "Dark Magician the Magician of Black Magic";
static const u8 sDarkRenewalSortName[] APPEND_RODATA = "Dark Renewal";
static const u8 sDarkStrikeFighterSortName[] APPEND_RODATA = "Dark Strike Fighter";
static const u8 sDarkSupremacySortName[] APPEND_RODATA = "Dark Supremacy";
static const u8 sDestinedRivalsSortName[] APPEND_RODATA = "Destined Rivals";
static const u8 sDriedWindsSortName[] APPEND_RODATA = "Dried Winds";
static const u8 sDragonRavineSortName[] APPEND_RODATA = "Dragon Ravine";
static const u8 sDragonShrineSortName[] APPEND_RODATA = "Dragon Shrine";
static const u8 sDeepEyesWhiteDragonSortName[] APPEND_RODATA = "Deep-Eyes White Dragon";
static const u8 sDragonMasterMagiaSortName[] APPEND_RODATA = "Dragon Master Magia";
static const u8 sDragonSpiritOfWhiteSortName[] APPEND_RODATA = "Dragon Spirit of White";
static const u8 sEbonIllusionMagicianSortName[] APPEND_RODATA = "Ebon Illusion Magician";
static const u8 sElShaddollAnoyatyllisSortName[] APPEND_RODATA = "El Shaddoll Anoyatyllis";
static const u8 sElShaddollApkalloneSortName[] APPEND_RODATA = "El Shaddoll Apkallone";
static const u8 sElShaddollConstructSortName[] APPEND_RODATA = "El Shaddoll Construct";
static const u8 sElShaddollFusionSortName[] APPEND_RODATA = "El Shaddoll Fusion";
static const u8 sElShaddollGrystaSortName[] APPEND_RODATA = "El Shaddoll Grysta";
static const u8 sElShaddollMeshahrailSortName[] APPEND_RODATA = "El Shaddoll Meshahrail";
static const u8 sElShaddollShekhinagaSortName[] APPEND_RODATA = "El Shaddoll Shekhinaga";
static const u8 sElShaddollWendigoSortName[] APPEND_RODATA = "El Shaddoll Wendigo";
static const u8 sElShaddollWindaSortName[] APPEND_RODATA = "El Shaddoll Winda";
static const u8 sEternalSoulSortName[] APPEND_RODATA = "Eternal Soul";
static const u8 sEvilAssaultSortName[] APPEND_RODATA = "Evil Assault";
static const u8 sEvilDragonAnantaSortName[] APPEND_RODATA = "Evil Dragon Ananta";
static const u8 sEvilHeroAdustedGoldSortName[] APPEND_RODATA = "Evil HERO Adusted Gold";
static const u8 sEvilHeroDarkGaiaSortName[] APPEND_RODATA = "Evil HERO Dark Gaia";
static const u8 sEvilHeroDarkestKnightSortName[] APPEND_RODATA = "Evil HERO Darkest Knight";
static const u8 sEvilHeroDeadEndPrisonSortName[] APPEND_RODATA = "Evil HERO Dead-End Prison";
static const u8 sEvilHeroInfernalGainerSortName[] APPEND_RODATA = "Evil HERO Infernal Gainer";
static const u8 sEvilHeroInfernalProdigySortName[] APPEND_RODATA = "Evil HERO Infernal Prodigy";
static const u8 sEvilHeroInfernalRiderSortName[] APPEND_RODATA = "Evil HERO Infernal Rider";
static const u8 sEvilHeroInfernalSniperSortName[] APPEND_RODATA = "Evil HERO Infernal Sniper";
static const u8 sEvilHeroInfernoWingSortName[] APPEND_RODATA = "Evil HERO Inferno Wing";
static const u8 sEvilHeroInfernoWingBackfireSortName[] APPEND_RODATA = "Evil HERO Inferno Wing - Backfire";
static const u8 sEvilHeroLightningGolemSortName[] APPEND_RODATA = "Evil HERO Lightning Golem";
static const u8 sEvilHeroMaliciousBaneSortName[] APPEND_RODATA = "Evil HERO Malicious Bane";
static const u8 sEvilHeroMaliciousEdgeSortName[] APPEND_RODATA = "Evil HERO Malicious Edge";
static const u8 sEvilHeroMaliciousFiendSortName[] APPEND_RODATA = "Evil HERO Malicious Fiend";
static const u8 sEvilHeroNeosLordSortName[] APPEND_RODATA = "Evil HERO Neos Lord";
static const u8 sEvilHeroSinisterNecromSortName[] APPEND_RODATA = "Evil HERO Sinister Necrom";
static const u8 sEvilHeroToxicBubbleSortName[] APPEND_RODATA = "Evil HERO Toxic Bubble";
static const u8 sEvilHeroViciousClawsSortName[] APPEND_RODATA = "Evil HERO Vicious Claws";
static const u8 sEvilHeroWildCycloneSortName[] APPEND_RODATA = "Evil HERO Wild Cyclone";
static const u8 sEvilMindSortName[] APPEND_RODATA = "Evil Mind";
static const u8 sFusionDeploymentSortName[] APPEND_RODATA = "Fusion Deployment";
static const u8 sGandoraGTheDragonOfDestructionSortName[] APPEND_RODATA = "Gandora-G the Dragon of Destruction";
static const u8 sGandoraXTheDragonOfDemolitionSortName[] APPEND_RODATA = "Gandora-X the Dragon of Demolition";
static const u8 sGoyoGuardianSortName[] APPEND_RODATA = "Goyo Guardian";
static const u8 sGrinderGolemSortName[] APPEND_RODATA = "Grinder Golem";
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
static const u8 sHelshaddollHollowSortName[] APPEND_RODATA = "Helshaddoll Hollow";
static const u8 sHeraldOfPerfectionSortName[] APPEND_RODATA = "Herald of Perfection";
static const u8 sHeraldOfUltimatenessSortName[] APPEND_RODATA = "Herald of Ultimateness";
static const u8 sHeroKidSortName[] APPEND_RODATA = "Hero Kid";
static const u8 sHumidWindsSortName[] APPEND_RODATA = "Humid Winds";
static const u8 sHystericPartySortName[] APPEND_RODATA = "Hysteric Party";
static const u8 sHystericSignSortName[] APPEND_RODATA = "Hysteric Sign";
static const u8 sIllusionMagicSortName[] APPEND_RODATA = "Illusion Magic";
static const u8 sIllusionOfChaosSortName[] APPEND_RODATA = "Illusion of Chaos";
static const u8 sIpiriaSortName[] APPEND_RODATA = "Ipiria";
static const u8 sJunkWarriorSortName[] APPEND_RODATA = "Junk Warrior";
static const u8 sKeeperOfDragonMagicSortName[] APPEND_RODATA = "Keeper of Dragon Magic";
static const u8 sLegendaryMajuGarzettSortName[] APPEND_RODATA = "Legendary Maju Garzett";
static const u8 sLevShaddollFusionSortName[] APPEND_RODATA = "Lev Shaddoll Fusion";
static const u8 sLightSerpentSortName[] APPEND_RODATA = "Lightserpent";
static const u8 sLightningWarriorSortName[] APPEND_RODATA = "Lightning Warrior";
static const u8 sLonefireBlossomSortName[] APPEND_RODATA = "Lonefire Blossom";
static const u8 sMagicianNavigationSortName[] APPEND_RODATA = "Magician Navigation";
static const u8 sMagicianOfDarkIllusionSortName[] APPEND_RODATA = "Magician of Dark Illusion";
static const u8 sMagiciansCombinationSortName[] APPEND_RODATA = "Magicians' Combination";
static const u8 sMagiciansRobeSortName[] APPEND_RODATA = "Magician's Robe";
static const u8 sMagiciansRodSortName[] APPEND_RODATA = "Magician's Rod";
static const u8 sMagiciansSoulsSortName[] APPEND_RODATA = "Magicians' Souls";
static const u8 sMasterOfChaosSortName[] APPEND_RODATA = "Master of Chaos";
static const u8 sMetaverseSortName[] APPEND_RODATA = "Metaverse";
static const u8 sMillenniumEyesRestrictSortName[] APPEND_RODATA = "Millennium-Eyes Restrict";
static const u8 sMoltingEscapeSortName[] APPEND_RODATA = "Molting Escape";
static const u8 sMysticMineSortName[] APPEND_RODATA = "Mystic Mine";
static const u8 sNaelshaddollArielSortName[] APPEND_RODATA = "Naelshaddoll Ariel";
static const u8 sNehshaddollGeniusSortName[] APPEND_RODATA = "Nehshaddoll Genius";
static const u8 sNepheShaddollFusionSortName[] APPEND_RODATA = "Nephe Shaddoll Fusion";
static const u8 sNeutronBlastSortName[] APPEND_RODATA = "Neutron Blast";
static const u8 sOfferingToTheSnakeDeitySortName[] APPEND_RODATA = "Offering to the Snake Deity";
static const u8 sOshaleonSortName[] APPEND_RODATA = "Oshaleon";
static const u8 sPowerToolDragonSortName[] APPEND_RODATA = "Power Tool Dragon";
static const u8 sPredaplantVerteAnacondaSortName[] APPEND_RODATA = "Predaplant Verte Anaconda";
static const u8 sQadshaddollKeiosSortName[] APPEND_RODATA = "Qadshaddoll Keios";
static const u8 sRedDragonArchfiendSortName[] APPEND_RODATA = "Red Dragon Archfiend";
static const u8 sRedRebootSortName[] APPEND_RODATA = "Red Reboot";
static const u8 sReeshaddollWendiSortName[] APPEND_RODATA = "Reeshaddoll Wendi";
static const u8 sReeshaddollWendikuruhuSortName[] APPEND_RODATA = "Reeshaddoll Wendikurhu";
static const u8 sReptilanneRageSortName[] APPEND_RODATA = "Reptilianne Rage";
static const u8 sReptilianneEchidnaSortName[] APPEND_RODATA = "Reptilianne Echidna";
static const u8 sReptilianneGardnaSortName[] APPEND_RODATA = "Reptilianne Gardna";
static const u8 sReptilianneGorgonSortName[] APPEND_RODATA = "Reptilianne Gorgon";
static const u8 sReptilianneHydraSortName[] APPEND_RODATA = "Reptilianne Hydra";
static const u8 sReptilianneLamiaSortName[] APPEND_RODATA = "Reptilianne Lamia";
static const u8 sReptilianneMedusaSortName[] APPEND_RODATA = "Reptilianne Medusa";
static const u8 sReptilianneNagaSortName[] APPEND_RODATA = "Reptilianne Naga";
static const u8 sReptiliannePoisonSortName[] APPEND_RODATA = "Reptilianne Poison";
static const u8 sReptilianneScyllaSortName[] APPEND_RODATA = "Reptilianne Scylla";
static const u8 sReptilianneServantSortName[] APPEND_RODATA = "Reptilianne Servant";
static const u8 sReptilianneSpawnSortName[] APPEND_RODATA = "Reptilianne Spawn";
static const u8 sReptilianneVaskiiSortName[] APPEND_RODATA = "Reptilianne Vaskii";
static const u8 sReptilianneViperSortName[] APPEND_RODATA = "Reptilianne Viper";
static const u8 sReturnOfTheDragonLordsSortName[] APPEND_RODATA = "Return of the Dragon Lords";
static const u8 sRiseOfTheSnakeDeitySortName[] APPEND_RODATA = "Rise of the Snake Deity";
static const u8 sSecretsOfDarkMagicSortName[] APPEND_RODATA = "Secrets of Dark Magic";
static const u8 sSerpentSuppressionSortName[] APPEND_RODATA = "Serpent Suppression";
static const u8 sShaddollBeastSortName[] APPEND_RODATA = "Shaddoll Beast";
static const u8 sShaddollCoreSortName[] APPEND_RODATA = "Shaddoll Core";
static const u8 sShaddollDragonSortName[] APPEND_RODATA = "Shaddoll Dragon";
static const u8 sShaddollFalcoSortName[] APPEND_RODATA = "Shaddoll Falco";
static const u8 sShaddollFusionSortName[] APPEND_RODATA = "Shaddoll Fusion";
static const u8 sShaddollHedgehogSortName[] APPEND_RODATA = "Shaddoll Hedgehog";
static const u8 sShaddollHoundSortName[] APPEND_RODATA = "Shaddoll Hound";
static const u8 sShaddollSchismSortName[] APPEND_RODATA = "Shaddoll Schism";
static const u8 sShaddollSquamataSortName[] APPEND_RODATA = "Shaddoll Squamata";
static const u8 sSilversCrySortName[] APPEND_RODATA = "Silver's Cry";
static const u8 sSnakeDeitysCommandSortName[] APPEND_RODATA = "Snake Deity's Command";
static const u8 sSnakeRainSortName[] APPEND_RODATA = "Snake Rain";
static const u8 sSnakeWhistleSortName[] APPEND_RODATA = "Snake Whistle";
static const u8 sSoulServantSortName[] APPEND_RODATA = "Soul Servant";
static const u8 sStardustDragonSortName[] APPEND_RODATA = "Stardust Dragon";
static const u8 sSupremeKingsCastleSortName[] APPEND_RODATA = "Supreme King's Castle";
static const u8 sThatGrassLooksGreenerSortName[] APPEND_RODATA = "That Grass Looks Greener";
static const u8 sTheDarkMagiciansSortName[] APPEND_RODATA = "The Dark Magicians";
static const u8 sTheGazeOfTimaeusSortName[] APPEND_RODATA = "The Gaze of Timaeus";
static const u8 sTheMelodyOfAwakeningDragonSortName[] APPEND_RODATA = "The Melody of Awakening Dragon";
static const u8 sTheWhiteStoneOfAncientsSortName[] APPEND_RODATA = "The White Stone of Ancients";
static const u8 sTheWhiteStoneOfLegendSortName[] APPEND_RODATA = "The White Stone of Legend";
static const u8 sTimeaeusTheUnitedMagicalDragonSortName[] APPEND_RODATA = "Timaeus the United Magical Dragon";
static const u8 sTimeausTheUnitedDragonSortName[] APPEND_RODATA = "Timaeus the United Dragon";
static const u8 sTohushaddollGrystaSortName[] APPEND_RODATA = "Tohushaddoll Grysta";
static const u8 sTrapTrickSortName[] APPEND_RODATA = "Trap Trick";
static const u8 sTriangleEcstasySparkSortName[] APPEND_RODATA = "Triangle Ecstasy Spark";
static const u8 sUltraPolymerizationSortName[] APPEND_RODATA = "Ultra Polymerization";
static const u8 sVennominagaTheDeityOfPoisonousSnakesSortName[] APPEND_RODATA = "Vennominaga the Deity of Poisonous Snakes";
static const u8 sVennominonTheKingOfPoisonousSnakesSortName[] APPEND_RODATA = "Vennominon the King of Poisonous Snakes";
static const u8 sVenomBoaSortName[] APPEND_RODATA = "Venom Boa";
static const u8 sVenomBurnSortName[] APPEND_RODATA = "Venom Burn";
static const u8 sVenomCobraSortName[] APPEND_RODATA = "Venom Cobra";
static const u8 sVenomSerpentSortName[] APPEND_RODATA = "Venom Serpent";
static const u8 sVenomShotSortName[] APPEND_RODATA = "Venom Shot";
static const u8 sVenomSnakeSortName[] APPEND_RODATA = "Venom Snake";
static const u8 sVenomSwampSortName[] APPEND_RODATA = "Venom Swamp";
static const u8 sVipersRebirthSortName[] APPEND_RODATA = "Viper's Rebirth";
static const u8 sYamorimoriSortName[] APPEND_RODATA = "Yamorimori";
static const u8 sYowieSortName[] APPEND_RODATA = "Yowie";
static const u8 sAceOfSwordSortName[] APPEND_RODATA = "Ace of Sword";
static const u8 sAceOfWandSortName[] APPEND_RODATA = "Ace of Wand";
static const u8 sArcanaCallSortName[] APPEND_RODATA = "Arcana Call";
static const u8 sArcanaForce0TheFoolSortName[] APPEND_RODATA = "Arcana Force 0 - The Fool";
static const u8 sArcanaForceExTheDarkRulerSortName[] APPEND_RODATA = "Arcana Force EX - The Dark Ruler";
static const u8 sArcanaForceExTheLightRulerSortName[] APPEND_RODATA = "Arcana Force EX - The Light Ruler";
static const u8 sArcanaForceITheMagicianSortName[] APPEND_RODATA = "Arcana Force I - The Magician";
static const u8 sArcanaForceIiiTheEmpressSortName[] APPEND_RODATA = "Arcana Force III - The Empress";
static const u8 sArcanaForceIvTheEmperorSortName[] APPEND_RODATA = "Arcana Force IV - The Emperor";
static const u8 sArcanaForceTheChaosRulerSortName[] APPEND_RODATA = "Arcana Force EX - The Chaos Ruler";
static const u8 sArcanaForceVTheHierophantSortName[] APPEND_RODATA = "Arcana Force V - The Hierophant";
static const u8 sArcanaForceViTheLoversSortName[] APPEND_RODATA = "Arcana Force VI - The Lovers";
static const u8 sArcanaForceViiTheChariotSortName[] APPEND_RODATA = "Arcana Force VII - The Chariot";
static const u8 sArcanaForceViiiTheStrengthSortName[] APPEND_RODATA = "Arcana Force VIII - The Strength";
static const u8 sArcanaForceXiiTheHangmanSortName[] APPEND_RODATA = "Arcana Force XII - The Hangman";
static const u8 sArcanaForceXivTemperanceSortName[] APPEND_RODATA = "Arcana Force XIV - Temperance";
static const u8 sArcanaForceXixTheSunSortName[] APPEND_RODATA = "Arcana Force XIX - The Sun";
static const u8 sArcanaForceXvTheFiendSortName[] APPEND_RODATA = "Arcana Force XV - The Fiend";
static const u8 sArcanaForceXviiiTheMoonSortName[] APPEND_RODATA = "Arcana Force XVIII - The Moon";
static const u8 sArcanaForceXxiTheWorldSortName[] APPEND_RODATA = "Arcana Force XXI - The World";
static const u8 sArcanaReadingSortName[] APPEND_RODATA = "Arcana Reading";
static const u8 sArcanaSpreadSortName[] APPEND_RODATA = "Arcana Spread";
static const u8 sArmedNeosSortName[] APPEND_RODATA = "Armed Neos";
static const u8 sAurkusLightswornDruidSortName[] APPEND_RODATA = "Aurkus, Lightsworn Druid";
static const u8 sCelestiaLightswornAngelSortName[] APPEND_RODATA = "Celestia, Lightsworn Angel";
static const u8 sChargeOfTheLightBrigadeSortName[] APPEND_RODATA = "Charge of the Light Brigade";
static const u8 sChrysalisChickySortName[] APPEND_RODATA = "Chrysalis Chicky";
static const u8 sChrysalisDolphinSortName[] APPEND_RODATA = "Chrysalis Dolphin";
static const u8 sChrysalisMoleSortName[] APPEND_RODATA = "Chrysalis Mole";
static const u8 sChrysalisPantailSortName[] APPEND_RODATA = "Chrysalis Pantail";
static const u8 sChrysalisPinnySortName[] APPEND_RODATA = "Chrysalis Pinny";
static const u8 sCocoonPartySortName[] APPEND_RODATA = "Cocoon Party";
static const u8 sCocoonRebirthSortName[] APPEND_RODATA = "Cocoon Rebirth";
static const u8 sColosseumCageOfTheGladiatorBeastsSortName[] APPEND_RODATA = "Colosseum - Cage of the Gladiator Beasts";
static const u8 sContactSortName[] APPEND_RODATA = "Contact";
static const u8 sContactGateSortName[] APPEND_RODATA = "Contact Gate";
static const u8 sConvertContactSortName[] APPEND_RODATA = "Convert Contact";
static const u8 sCrossKeeperSortName[] APPEND_RODATA = "Cross Keeper";
static const u8 sCuriousTheLightswornDominionSortName[] APPEND_RODATA = "Curious, the Lightsworn Dominion";
static const u8 sEhrenLightswornMonkSortName[] APPEND_RODATA = "Ehren, Lightsworn Monk";
static const u8 sElementalHeroAirNeosSortName[] APPEND_RODATA = "Elemental HERO Air Neos";
static const u8 sElementalHeroAquaNeosSortName[] APPEND_RODATA = "Elemental HERO Aqua Neos";
static const u8 sElementalHeroBraveNeosSortName[] APPEND_RODATA = "Elemental HERO Brave Neos";
static const u8 sElementalHeroChaosNeosSortName[] APPEND_RODATA = "Elemental HERO Chaos Neos";
static const u8 sElementalHeroCosmoNeosSortName[] APPEND_RODATA = "Elemental HERO Cosmo Neos";
static const u8 sElementalHeroDarkNeosSortName[] APPEND_RODATA = "Elemental HERO Dark Neos";
static const u8 sElementalHeroFlareNeosSortName[] APPEND_RODATA = "Elemental HERO Flare Neos";
static const u8 sElementalHeroGlowNeosSortName[] APPEND_RODATA = "Elemental HERO Glow Neos";
static const u8 sElementalHeroGrandNeosSortName[] APPEND_RODATA = "Elemental HERO Grand Neos";
static const u8 sElementalHeroMagmaNeosSortName[] APPEND_RODATA = "Elemental HERO Magma Neos";
static const u8 sElementalHeroMarineNeosSortName[] APPEND_RODATA = "Elemental HERO Marine Neos";
static const u8 sElementalHeroNebulaNeosSortName[] APPEND_RODATA = "Elemental HERO Nebula Neos";
static const u8 sElementalHeroShiningNeosWingmanSortName[] APPEND_RODATA = "Elemental HERO Shining Neos Wingman";
static const u8 sElementalHeroSpiritOfNeosSortName[] APPEND_RODATA = "Elemental HERO Spirit of Neos";
static const u8 sElementalHeroStormNeosSortName[] APPEND_RODATA = "Elemental HERO Storm Neos";
static const u8 sEnEngageNeoSpaceSortName[] APPEND_RODATA = "EN - Engage Neo Space";
static const u8 sEnShuffleSortName[] APPEND_RODATA = "EN Shuffle";
static const u8 sEnWaveSortName[] APPEND_RODATA = "EN Wave";
static const u8 sEnlightenmentDragonSortName[] APPEND_RODATA = "Enlightenment Dragon";
static const u8 sFavouriteContactSortName[] APPEND_RODATA = "Favorite Contact";
static const u8 sFelisLightswornArcherSortName[] APPEND_RODATA = "Felis, Lightsworn Archer";
static const u8 sFlavianColosseumOfTheGladiatorBeastsSortName[] APPEND_RODATA = "Flavian - Colosseum of the Gladiator Beasts";
static const u8 sGaronithLightswornDragonSortName[] APPEND_RODATA = "Gragonith, Lightsworn Dragon";
static const u8 sGarothLightswornWarriorSortName[] APPEND_RODATA = "Garoth, Lightsworn Warrior";
static const u8 sGenerationNextSortName[] APPEND_RODATA = "Generation Next";
static const u8 sGladiatorBeastAlexanderSortName[] APPEND_RODATA = "Gladiator Beast Alexander";
static const u8 sGladiatorBeastAndabataSortName[] APPEND_RODATA = "Gladiator Beast Andabata";
static const u8 sGladiatorBeastAndalSortName[] APPEND_RODATA = "Gladiator Beast Andal";
static const u8 sGladiatorBeastAttorixSortName[] APPEND_RODATA = "Gladiator Beast Attorix";
static const u8 sGladiatorBeastAugustusSortName[] APPEND_RODATA = "Gladiator Beast Augustus";
static const u8 sGladiatorBeastBattleHalberdSortName[] APPEND_RODATA = "Gladiator Beast's Battle Halberd";
static const u8 sGladiatorBeastBestiariSortName[] APPEND_RODATA = "Gladiator Beast Bestiari";
static const u8 sGladiatorBeastClaudiusSortName[] APPEND_RODATA = "Gladiator Beast Claudius";
static const u8 sGladiatorBeastDareiosSortName[] APPEND_RODATA = "Gladiator Beast Dareios";
static const u8 sGladiatorBeastDariusSortName[] APPEND_RODATA = "Gladiator Beast Darius";
static const u8 sGladiatorBeastDimacariSortName[] APPEND_RODATA = "Gladiator Beast Dimacari";
static const u8 sGladiatorBeastDomitianusSortName[] APPEND_RODATA = "Gladiator Beast Domitianus";
static const u8 sGladiatorBeastDragasesSortName[] APPEND_RODATA = "Gladiator Beast Dragases";
static const u8 sGladiatorBeastEquesteSortName[] APPEND_RODATA = "Gladiator Beast Equeste";
static const u8 sGladiatorBeastEssedariiSortName[] APPEND_RODATA = "Gladiator Beast Essedarii";
static const u8 sGladiatorBeastGaiodiazSortName[] APPEND_RODATA = "Gladiator Beast Gaiodiaz";
static const u8 sGladiatorBeastGistelSortName[] APPEND_RODATA = "Gladiator Beast Gistel";
static const u8 sGladiatorBeastGyzarusSortName[] APPEND_RODATA = "Gladiator Beast Gyzarus";
static const u8 sGladiatorBeastHeraklinosSortName[] APPEND_RODATA = "Gladiator Beast Heraklinos";
static const u8 sGladiatorBeastHoplomusSortName[] APPEND_RODATA = "Gladiator Beast Hoplomus";
static const u8 sGladiatorBeastLanistaSortName[] APPEND_RODATA = "Gladiator Beast Lanista";
static const u8 sGladiatorBeastLaquariSortName[] APPEND_RODATA = "Gladiator Beast Laquari";
static const u8 sGladiatorBeastMurmilloSortName[] APPEND_RODATA = "Gladiator Beast Murmillo";
static const u8 sGladiatorBeastNerokiusSortName[] APPEND_RODATA = "Gladiator Beast Nerokius";
static const u8 sGladiatorBeastNoxiousSortName[] APPEND_RODATA = "Gladiator Beast Noxious";
static const u8 sGladiatorBeastOctaviusSortName[] APPEND_RODATA = "Gladiator Beast Octavius";
static const u8 sGladiatorBeastRetiariSortName[] APPEND_RODATA = "Gladiator Beast Retiari";
static const u8 sGladiatorBeastSagittariiSortName[] APPEND_RODATA = "Gladiator Beast Sagittarii";
static const u8 sGladiatorBeastSamniteSortName[] APPEND_RODATA = "Gladiator Beast Samnite";
static const u8 sGladiatorBeastSecutorSortName[] APPEND_RODATA = "Gladiator Beast Secutor";
static const u8 sGladiatorBeastSpartacusSortName[] APPEND_RODATA = "Gladiator Beast Spartacus";
static const u8 sGladiatorBeastTamerEditorSortName[] APPEND_RODATA = "Gladiator Beast Tamer Editor";
static const u8 sGladiatorBeastToraxSortName[] APPEND_RODATA = "Gladiator Beast Torax";
static const u8 sGladiatorBeastTygeriusSortName[] APPEND_RODATA = "Gladiator Beast Tygerius";
static const u8 sGladiatorBeastVespasiusSortName[] APPEND_RODATA = "Gladiator Beast Vespasius";
static const u8 sGladiatorBeastWarChariotSortName[] APPEND_RODATA = "Gladiator Beast War Chariot";
static const u8 sGladiatorBeastsBattleArchfiendShieldSortName[] APPEND_RODATA = "Gladiator Beast's Battle Archfiend Shield";
static const u8 sGladiatorBeastsBattleGladiusSortName[] APPEND_RODATA = "Gladiator Beast's Battle Gladius";
static const u8 sGladiatorBeastsBattleManicaSortName[] APPEND_RODATA = "Gladiator Beast's Battle Manica";
static const u8 sGladiatorBeastsMedusaShieldSortName[] APPEND_RODATA = "Gladiator Beast's Medusa Shield";
static const u8 sGladiatorBeastsValorSortName[] APPEND_RODATA = "Gladiator Beast's Valor";
static const u8 sGladiatorNaumachiaSortName[] APPEND_RODATA = "Gladiator Naumachia";
static const u8 sGloriousIllusionSortName[] APPEND_RODATA = "Glorious Illusion";
static const u8 sInstantContactSortName[] APPEND_RODATA = "Instant Contact";
static const u8 sInstantNeoSpaceSortName[] APPEND_RODATA = "Instant Neo Space";
static const u8 sJainLightswornPaladinSortName[] APPEND_RODATA = "Jain, Lightsworn Paladin";
static const u8 sJainTwilightswornGeneralSortName[] APPEND_RODATA = "Jain, Twilightsworn General";
static const u8 sJenisLightswornMenderSortName[] APPEND_RODATA = "Jenis, Lightsworn Mender";
static const u8 sJudgmentTheDragonOfHeavenSortName[] APPEND_RODATA = "Judgment, the Dragon of Heaven";
static const u8 sKnightOfPentaclesSortName[] APPEND_RODATA = "Knight of Pentacles";
static const u8 sLightBarrierSortName[] APPEND_RODATA = "Light Barrier";
static const u8 sLightForceSortName[] APPEND_RODATA = "Light Force";
static const u8 sLightOfDestructionSortName[] APPEND_RODATA = "Light of Destruction";
static const u8 sLightSpiralSortName[] APPEND_RODATA = "Light Spiral";
static const u8 sLightswornAegisSortName[] APPEND_RODATA = "Lightsworn Aegis";
static const u8 sLightswornBarrierSortName[] APPEND_RODATA = "Lightsworn Barrier";
static const u8 sLightswornDragonlingSortName[] APPEND_RODATA = "Lightsworn Dragonling";
static const u8 sLightswornJudgementSortName[] APPEND_RODATA = "Lightsworn Judgment";
static const u8 sLightswornSabreSortName[] APPEND_RODATA = "Lightsworn Sabre";
static const u8 sLightswornSanctuarySortName[] APPEND_RODATA = "Lightsworn Sanctuary";
static const u8 sLuminaLightswornSummonerSortName[] APPEND_RODATA = "Lumina, Lightsworn Summoner";
static const u8 sLuminaTwilightswornShamanSortName[] APPEND_RODATA = "Lumina, Twilightsworn Shaman";
static const u8 sLylaLightswornSorceressSortName[] APPEND_RODATA = "Lyla, Lightsworn Sorceress";
static const u8 sLylaTwilightswornEnchantressSortName[] APPEND_RODATA = "Lyla, Twilightsworn Enchantress";
static const u8 sMarchOfTheDarkBrigadeSortName[] APPEND_RODATA = "March of the Dark Brigade";
static const u8 sMichaelTheArchLightswornSortName[] APPEND_RODATA = "Michael, the Arch-Lightsworn";
static const u8 sMinervaLightswornMaidenSortName[] APPEND_RODATA = "Minerva, Lightsworn Maiden";
static const u8 sMinervaTheAthenianLightswornSortName[] APPEND_RODATA = "Minerva, the Athenian Lightsworn";
static const u8 sMinervaTheExhaltedLightswornSortName[] APPEND_RODATA = "Minerva, the Exalted Lightsworn";
static const u8 sMiracleContactSortName[] APPEND_RODATA = "Miracle Contact";
static const u8 sMoonTokenSortName[] APPEND_RODATA = "Moon Token";
static const u8 sNeoSpaceSortName[] APPEND_RODATA = "Neo Space";
static const u8 sNeoSpaceConnectorSortName[] APPEND_RODATA = "Neo Space Connector";
static const u8 sNeoSpacianAirHummingbirdSortName[] APPEND_RODATA = "Neo-Spacian Air Hummingbird";
static const u8 sNeoSpacianAquaDolphinSortName[] APPEND_RODATA = "Neo-Spacian Aqua Dolphin";
static const u8 sNeoSpacianDarkPantherSortName[] APPEND_RODATA = "Neo-Spacian Dark Panther";
static const u8 sNeoSpacianFlareScarabSortName[] APPEND_RODATA = "Neo-Spacian Flare Scarab";
static const u8 sNeoSpacianGlowMossSortName[] APPEND_RODATA = "Neo-Spacian Glow Moss";
static const u8 sNeoSpacianGrandMoleSortName[] APPEND_RODATA = "Neo-Spacian Grand Mole";
static const u8 sNeoSpacianMarineDolphinSortName[] APPEND_RODATA = "Neo-Spacian Marine Dolphin";
static const u8 sNeoSpacianTwinkleMossSortName[] APPEND_RODATA = "Neo-Spacian Twinkle Moss";
static const u8 sNexSortName[] APPEND_RODATA = "NEX";
static const u8 sNextSortName[] APPEND_RODATA = "NEXT";
static const u8 sPentacleOfAceSortName[] APPEND_RODATA = "Pentacle of Ace";
static const u8 sPunishmentDragonSortName[] APPEND_RODATA = "Punishment Dragon";
static const u8 sRaidenHandOfTheLightswornSortName[] APPEND_RODATA = "Raiden, Hand of the Lightsworn";
static const u8 sRealmOfLightSortName[] APPEND_RODATA = "Realm of Light";
static const u8 sRescueCatSortName[] APPEND_RODATA = "Rescue Cat";
static const u8 sRescueRabbitSortName[] APPEND_RODATA = "Rescue Rabbit";
static const u8 sReversalOfFateSortName[] APPEND_RODATA = "Reversal of Fate";
static const u8 sRinyanLightswornRogueSortName[] APPEND_RODATA = "Rinyan, Lightsworn Rogue";
static const u8 sRykoLightswornHunterSortName[] APPEND_RODATA = "Ryko, Lightsworn Hunter";
static const u8 sRykoTwilightswornFighterSortName[] APPEND_RODATA = "Ryko, Twilightsworn Fighter";
static const u8 sShireLightswornSpiritSortName[] APPEND_RODATA = "Shire, Lightsworn Spirit";
static const u8 sSolarRechargeSortName[] APPEND_RODATA = "Solar Recharge";
static const u8 sSuitOfSwordXSortName[] APPEND_RODATA = "Suit of Sword X";
static const u8 sTestBearSortName[] APPEND_RODATA = "Test Bear";
static const u8 sTestPantherSortName[] APPEND_RODATA = "Test Panther";
static const u8 sTestTigerSortName[] APPEND_RODATA = "Test Tiger";
static const u8 sThumbsDownSortName[] APPEND_RODATA = "Thumbs Down";
static const u8 sTourOfDoomSortName[] APPEND_RODATA = "Tour of Doom";
static const u8 sTrojanGladiatorBeastSortName[] APPEND_RODATA = "Trojan Gladiator Beast";
static const u8 sTwilightClothSortName[] APPEND_RODATA = "Twilight Cloth";
static const u8 sTwilightEraserSortName[] APPEND_RODATA = "Twilight Eraser";
static const u8 sTwlightTwinDragonsSortName[] APPEND_RODATA = "Twilight Twin Dragons";
static const u8 sVanquishingLightSortName[] APPEND_RODATA = "Vanquishing Light";
static const u8 sWeissLightswornArchfiendSortName[] APPEND_RODATA = "Weiss, Lightsworn Archfiend";
static const u8 sWulfLightswornBeastSortName[] APPEND_RODATA = "Wulf, Lightsworn Beast";
static const u8 sAllOutAttacksSortName[] APPEND_RODATA = "All-Out Attacks";
static const u8 sAncientFairyDragonSortName[] APPEND_RODATA = "Ancient Fairy Dragon";
static const u8 sAncientGearSortName[] APPEND_RODATA = "Ancient Gear";
static const u8 sAncientGearAdvanceSortName[] APPEND_RODATA = "Ancient Gear Advance";
static const u8 sAncientGearBeastSortName[] APPEND_RODATA = "Ancient Gear Beast";
static const u8 sAncientGearCannonSortName[] APPEND_RODATA = "Ancient Gear Cannon";
static const u8 sAncientGearCastleSortName[] APPEND_RODATA = "Ancient Gear Castle";
static const u8 sAncientGearCommanderSortName[] APPEND_RODATA = "Ancient Gear Commander";
static const u8 sAncientGearDarkGolemSortName[] APPEND_RODATA = "Ancient Gear Dark Golem";
static const u8 sAncientGearDragonSortName[] APPEND_RODATA = "Ancient Gear Dragon";
static const u8 sAncientGearDrillSortName[] APPEND_RODATA = "Ancient Gear Drill";
static const u8 sAncientGearDuelSortName[] APPEND_RODATA = "Ancient Gear Duel";
static const u8 sAncientGearEngineerSortName[] APPEND_RODATA = "Ancient Gear Engineer";
static const u8 sAncientGearExplosiveSortName[] APPEND_RODATA = "Ancient Gear Explosive";
static const u8 sAncientGearFactorySortName[] APPEND_RODATA = "Ancient Gear Factory";
static const u8 sAncientGearFistSortName[] APPEND_RODATA = "Ancient Gear Fist";
static const u8 sAncientGearFrameSortName[] APPEND_RODATA = "Ancient Gear Frame";
static const u8 sAncientGearFusionSortName[] APPEND_RODATA = "Ancient Gear Fusion";
static const u8 sAncientGearGadjiltronChimeraSortName[] APPEND_RODATA = "Ancient Gear Gadjiltron Chimera";
static const u8 sAncientGearGadjiltronDragonSortName[] APPEND_RODATA = "Ancient Gear Gadjiltron Dragon";
static const u8 sAncientGearGolemSortName[] APPEND_RODATA = "Ancient Gear Golem";
static const u8 sAncientGearGolemUltimatePoundSortName[] APPEND_RODATA = "Ancient Gear Golem - Ultimate Pound";
static const u8 sAncientGearKnightSortName[] APPEND_RODATA = "Ancient Gear Knight";
static const u8 sAncientGearMegatonGolemSortName[] APPEND_RODATA = "Ancient Gear Megaton Golem";
static const u8 sAncientGearSoldierSortName[] APPEND_RODATA = "Ancient Gear Soldier";
static const u8 sAncientGearStatueSortName[] APPEND_RODATA = "Ancient Gear Statue";
static const u8 sAncientGearTankSortName[] APPEND_RODATA = "Ancient Gear Tank";
static const u8 sAncientGearTankerSortName[] APPEND_RODATA = "Ancient Gear Tanker";
static const u8 sAncientGearWorkshopSortName[] APPEND_RODATA = "Ancient Gear Workshop";
static const u8 sAncientLeafSortName[] APPEND_RODATA = "Ancient Leaf";
static const u8 sAncientSacredWyvernSortName[] APPEND_RODATA = "Ancient Sacred Wyvern";
static const u8 sArcanaKnightJokerSortName[] APPEND_RODATA = "Arcana Knight Joker";
static const u8 sArcaneBarrierSortName[] APPEND_RODATA = "Arcane Barrier";
static const u8 sArmityleTheChaosPhantasmSortName[] APPEND_RODATA = "Armityle the Chaos Phantasm";
static const u8 sBabycerasaurusSortName[] APPEND_RODATA = "Babycerasaurus";
static const u8 sBarrierStatueOfTheStormwindsSortName[] APPEND_RODATA = "Barrier Statue of the Stormwinds";
static const u8 sBattleManiaSortName[] APPEND_RODATA = "Battle Mania";
static const u8 sBigEvolutionPillSortName[] APPEND_RODATA = "Big Evolution Pill";
static const u8 sBlackWingedDragonSortName[] APPEND_RODATA = "Black-Winged Dragon";
static const u8 sBeastMachineKingBarbarosUrSortName[] APPEND_RODATA = "Beast Machine King Barbaros Ür";
static const u8 sChainStrikeSortName[] APPEND_RODATA = "Chain Strike";
static const u8 sChainSummoningSortName[] APPEND_RODATA = "Chain Summoning";
static const u8 sChaosAncientGearGiantSortName[] APPEND_RODATA = "Chaos Ancient Gear Giant";
static const u8 sCoralDragonSortName[] APPEND_RODATA = "Coral Dragon";
static const u8 sCrimsonBladerSortName[] APPEND_RODATA = "Crimson Blader";
static const u8 sCrimsonDragonSortName[] APPEND_RODATA = "Crimson Dragon";
static const u8 sCrossDimensonalDuelSortName[] APPEND_RODATA = "Cross-Dimensional Duel";
static const u8 sCyberDragonInfinitySortName[] APPEND_RODATA = "Cyber Dragon Infinity";
static const u8 sCyberSlashHarpyLadySortName[] APPEND_RODATA = "Cyber Slash Harpie Lady";
static const u8 sDarkHorusSortName[] APPEND_RODATA = "Dark Horus";
static const u8 sDarkMagicianGirlTheMagiciansApprenticeSortName[] APPEND_RODATA = "Dark Magician Girl the Magician's Apprentice";
static const u8 sDarkblazeDragonSortName[] APPEND_RODATA = "Darkblaze Dragon";
static const u8 sBootUpSoldierDreadDynamoSortName[] APPEND_RODATA = "Boot-Up Soldier - Dread Dynamo";
static const u8 sCastelTheSkyBlasterMusketeerSortName[] APPEND_RODATA = "Castel, the Skyblaster Musketeer";
static const u8 sDamageEqualsReptileSortName[] APPEND_RODATA = "Damage = Reptile";
static const u8 sDarkMagicianCircleSortName[] APPEND_RODATA = "Dark Magical Circle";
static const u8 sDarkMagicianTheMagicianOfBlackChaosSortName[] APPEND_RODATA = "Dark Magician the Magician of Black Magic";
static const u8 sDeSynchroSortName[] APPEND_RODATA = "De-Synchro";
static const u8 sDemiseKingOfArmageddonSortName[] APPEND_RODATA = "Demise, King of Armageddon";
static const u8 sDoubleToolCAndDSortName[] APPEND_RODATA = "Double Tool C&D";
static const u8 sEndOfTheWorldSortName[] APPEND_RODATA = "End of the World";
static const u8 sEvolzarDolkkaSortName[] APPEND_RODATA = "Evolzar Dolkka";
static const u8 sExchangeOfTheSpiritSortName[] APPEND_RODATA = "Exchange of the Spirit";
static const u8 sFactoryOfOneHundredMachinesSortName[] APPEND_RODATA = "Factory of 100 Machines";
static const u8 sFieldBarrierSortName[] APPEND_RODATA = "Field Barrier";
static const u8 sFlameRulerSortName[] APPEND_RODATA = "Flame Ruler";
static const u8 sFormulaSynchronSortName[] APPEND_RODATA = "Formula Synchron";
static const u8 sFossilExcavationSortName[] APPEND_RODATA = "Fossil Excavation";
static const u8 sGadgetBoxSortName[] APPEND_RODATA = "Gadget Box";
static const u8 sGandoraXTheDragonOfDestructionSortName[] APPEND_RODATA = "Gandora-X the Dragon of Demolition";
static const u8 sGeartownSortName[] APPEND_RODATA = "Geartown";
static const u8 sGladiatorProvingGroundSortName[] APPEND_RODATA = "Gladiator Proving Ground";
static const u8 sGrandConvergenceSortName[] APPEND_RODATA = "Grand Convergence";
static const u8 sGreatPoseidonBeetleSortName[] APPEND_RODATA = "Great Poseidon Beetle";
static const u8 sGreenBaboonDefenderOfTheForestSortName[] APPEND_RODATA = "Green Baboon, Defender of the Forest";
static const u8 sGungnirDragonOfTheIceBarrierSortName[] APPEND_RODATA = "Gungnir, Dragon of the Ice Barrier";
static const u8 sHeraldOfTheArcLightSortName[] APPEND_RODATA = "Herald of the Arc Light";
static const u8 sHeraldOfUlimatenessSortName[] APPEND_RODATA = "Herald of Ultimateness";
static const u8 sHonestSortName[] APPEND_RODATA = "Honest";
static const u8 sDragonsMirrorSortName[] APPEND_RODATA = "Dragon's Mirror";
static const u8 sHuntingInstinctSortName[] APPEND_RODATA = "Hunting Instinct";
static const u8 sIcarusAttackSortName[] APPEND_RODATA = "Icarus Attack";
static const u8 sJunkSynchronSortName[] APPEND_RODATA = "Junk Synchron";
static const u8 sLevelTuningSortName[] APPEND_RODATA = "Level Tuning";
static const u8 sLeviairTheSeaDragonSortName[] APPEND_RODATA = "Leviair the Sea Dragon";
static const u8 sLifeStreamDragonSortName[] APPEND_RODATA = "Life Stream Dragon";
static const u8 sMacroCosmosSortName[] APPEND_RODATA = "Macro Cosmos";
static const u8 sMagicalArmShieldSortName[] APPEND_RODATA = "Magical Arm Shield";
static const u8 sMagicalMarionetteSortName[] APPEND_RODATA = "Magical Marionette";
static const u8 sMagiciansCircleSortName[] APPEND_RODATA = "Magician's Circle";
static const u8 sMagnaDragoSortName[] APPEND_RODATA = "Magna Drago";
static const u8 sMirageDragonSortName[] APPEND_RODATA = "Mirage Dragon";
static const u8 sMontageDragonSortName[] APPEND_RODATA = "Montage Dragon";
static const u8 sMorphtronicAcceleratorSortName[] APPEND_RODATA = "Morphtronic Accelerator";
static const u8 sMorphtronicBindSortName[] APPEND_RODATA = "Morphtronic Bind";
static const u8 sMorphtronicBoardenSortName[] APPEND_RODATA = "Morphtronic Boarden";
static const u8 sMorphtronicBoomboxenSortName[] APPEND_RODATA = "Morphtronic Boomboxen";
static const u8 sMorphtronicCameranSortName[] APPEND_RODATA = "Morphtronic Cameran";
static const u8 sMorphtronicCelfonSortName[] APPEND_RODATA = "Morphtronic Celfon";
static const u8 sMorphtronicClockenSortName[] APPEND_RODATA = "Morphtronic Clocken";
static const u8 sMorphtronicConverterSortName[] APPEND_RODATA = "Morphtronic Converter";
static const u8 sMorphtronicCordSortName[] APPEND_RODATA = "Morphtronic Cord";
static const u8 sMorphtronicDatatronSortName[] APPEND_RODATA = "Morphtronic Datatron";
static const u8 sMorphtronicEarfonSortName[] APPEND_RODATA = "Morphtronic Earfon";
static const u8 sMorphtronicEngineSortName[] APPEND_RODATA = "Morphtronic Engine";
static const u8 sMorphtronicForcefieldSortName[] APPEND_RODATA = "Morphtronic Forcefield";
static const u8 sMorphtronicImpactReturnSortName[] APPEND_RODATA = "Morphtronic Impact Return";
static const u8 sMorphtronicLantronSortName[] APPEND_RODATA = "Morphtronic Lantron";
static const u8 sMorphtronicMagnenSortName[] APPEND_RODATA = "Morphtronic Magnen";
static const u8 sMorphtronicMagnenBarSortName[] APPEND_RODATA = "Morphtronic Magnen Bar";
static const u8 sMorphtronicMapSortName[] APPEND_RODATA = "Morphtronic Map";
static const u8 sMorphtronicMonitronSortName[] APPEND_RODATA = "Morphtronic Monitron";
static const u8 sMorphtronicRadionSortName[] APPEND_RODATA = "Morphtronic Radion";
static const u8 sMorphtronicRemotenSortName[] APPEND_RODATA = "Morphtronic Remoten";
static const u8 sMorphtronicRepairUnitSortName[] APPEND_RODATA = "Morphtronic Repair Unit";
static const u8 sMorphtronicRustyEngineSortName[] APPEND_RODATA = "Morphtronic Rusty Engine";
static const u8 sMorphtronicScannenSortName[] APPEND_RODATA = "Morphtronic Scannen";
static const u8 sMorphtronicScopenSortName[] APPEND_RODATA = "Morphtronic Scopen";
static const u8 sMorphtronicSlingenSortName[] APPEND_RODATA = "Morphtronic Slingen";
static const u8 sMorphtronicMixupSortName[] APPEND_RODATA = "Morphtronic Mix-up";
static const u8 sMorphtronicSmartfonSortName[] APPEND_RODATA = "Morphtronic Smartfon";
static const u8 sMorphtronicStaplenSortName[] APPEND_RODATA = "Morphtronic Staplen";
static const u8 sMorphtronicTelefonSortName[] APPEND_RODATA = "Morphtronic Telefon";
static const u8 sMorphtronicVacuumenSortName[] APPEND_RODATA = "Morphtronic Vacuumen";
static const u8 sMorphtronicVideonSortName[] APPEND_RODATA = "Morphtronic Videon";
static const u8 sNaturiaBeastSortName[] APPEND_RODATA = "Naturia Beast";
static const u8 sNitroWarriorSortName[] APPEND_RODATA = "Nitro Warrior";
static const u8 sPowerFilterSortName[] APPEND_RODATA = "Power Filter";
static const u8 sPowerToolBraverDragonSortName[] APPEND_RODATA = "Power Tool Braver Dragon";
static const u8 sPseudoSpaceSortName[] APPEND_RODATA = "Pseudo Space";
static const u8 sRainbowDarkDragonSortName[] APPEND_RODATA = "Rainbow Dark Dragon";
static const u8 sRoadSynchronSortName[] APPEND_RODATA = "Road Synchron";
static const u8 sRoadWarriorSortName[] APPEND_RODATA = "Road Warrior";
static const u8 sScrapIronScarecrowSortName[] APPEND_RODATA = "Scrap-Iron Scarecrow";
static const u8 sSilentMagicianLv4SortName[] APPEND_RODATA = "Silent Magician LV4";
static const u8 sSilentMagicianLv8SortName[] APPEND_RODATA = "Silent Magician LV8";
static const u8 sSimorghBirdOfAncestrySortName[] APPEND_RODATA = "Simorgh, Bird of Ancestry";
static const u8 sSpellChronicleSortName[] APPEND_RODATA = "Spell Chronicle";
static const u8 sSpellGearSortName[] APPEND_RODATA = "Spell Gear";
static const u8 sOverflowingTreasureSortName[] APPEND_RODATA = "Overflowing Treasure";
static const u8 sSpellStrikerSortName[] APPEND_RODATA = "Spell Striker";
static const u8 sTGHyperLibrarianSortName[] APPEND_RODATA = "T.G. Hyper Librarian";
static const u8 sTatsunokoSortName[] APPEND_RODATA = "Tatsunoko";
static const u8 sTimeThiefRedoerSortName[] APPEND_RODATA = "Time Thief Redoer";
static const u8 sTrishulaDragonOfTheIceBarrierSortName[] APPEND_RODATA = "Trishula, Dragon of the Ice Barrier";
static const u8 sTuningwareSortName[] APPEND_RODATA = "Tuningware";
static const u8 sTurboBoosterSortName[] APPEND_RODATA = "Turbo Booster";
static const u8 sTurboCannonSortName[] APPEND_RODATA = "Turbo Cannon";
static const u8 sTurboRocketSortName[] APPEND_RODATA = "Turbo Rocket";
static const u8 sTurboSynchronSortName[] APPEND_RODATA = "Turbo Synchron";
static const u8 sTyrannoInfinitySortName[] APPEND_RODATA = "Tyranno Infinity";
static const u8 sUltimateAncientGearGolemSortName[] APPEND_RODATA = "Ultimate Ancient Gear Golem";
static const u8 sUltimateTyrannoSortName[] APPEND_RODATA = "Ultimate Tyranno";
static const u8 sUnstableEvolutionSortName[] APPEND_RODATA = "Unstable Evolution";
static const u8 sUrgentTuningSortName[] APPEND_RODATA = "Urgent Tuning";
static const u8 sWarriorOfAtlantisSortName[] APPEND_RODATA = "Warrior of Atlantis";
static const u8 sWaterhazardSortName[] APPEND_RODATA = "Water Hazard";
static const u8 sWeaponChangeSortName[] APPEND_RODATA = "Weapon Change";
static const u8 sWetlandsSortName[] APPEND_RODATA = "Wetlands";
static const u8 sXSaberAirbellumSortName[] APPEND_RODATA = "X-Saber Airbellum";
static const u8 sACatOfIllOmenSortName[] APPEND_RODATA = "A Cat of Ill Omen";
static const u8 sAmazonessAugustaSortName[] APPEND_RODATA = "Amazoness Augusta";
static const u8 sAmazonessBabyTigerSortName[] APPEND_RODATA = "Amazoness Baby Tiger";
static const u8 sAmazonessEmpressSortName[] APPEND_RODATA = "Amazoness Empress";
static const u8 sAmazonessPetLigerSortName[] APPEND_RODATA = "Amazoness Pet Liger";
static const u8 sAmazonessPetLigerKingSortName[] APPEND_RODATA = "Amazoness Pet Liger King";
static const u8 sAmazonessPrincessSortName[] APPEND_RODATA = "Amazoness Princess";
static const u8 sAmazonessQueenSortName[] APPEND_RODATA = "Amazoness Queen";
static const u8 sAmazonessSageSortName[] APPEND_RODATA = "Amazoness Sage";
static const u8 sAmazonessScoutsSortName[] APPEND_RODATA = "Amazoness Scouts";
static const u8 sAlectorSovereignOfBirdsSortName[] APPEND_RODATA = "Alector, Sovereign of Birds";
static const u8 sAmazonessCallSortName[] APPEND_RODATA = "Amazoness Call";
static const u8 sAmazonessFightingSpiritSortName[] APPEND_RODATA = "Amazoness Fighting Spirit";
static const u8 sAmazonessHeirloomSortName[] APPEND_RODATA = "Amazoness Heirloom";
static const u8 sAmazonessSecretArtsSortName[] APPEND_RODATA = "Amazoness Secret Arts";
static const u8 sAegisOfTheOceanDragonLordSortName[] APPEND_RODATA = "Aegis of the Ocean Dragon Lord";
static const u8 sAmazonessHallSortName[] APPEND_RODATA = "Amazoness Hall";
static const u8 sAmazonessHotSpringSortName[] APPEND_RODATA = "Amazoness Hot Spring";
static const u8 sAmazonessOnslaughtSortName[] APPEND_RODATA = "Amazoness Onslaught";
static const u8 sAmazonessShamanismSortName[] APPEND_RODATA = "Amazoness Shamanism";
static const u8 sAmazonessSpellcasterSortName[] APPEND_RODATA = "Amazoness Spellcaster";
static const u8 sAmazonessVillageSortName[] APPEND_RODATA = "Amazoness Village";
static const u8 sAnteSortName[] APPEND_RODATA = "Ante";
static const u8 sAquaJetSortName[] APPEND_RODATA = "Aqua Jet";
static const u8 sAmazonessWillpowerSortName[] APPEND_RODATA = "Amazoness Willpower";
static const u8 sAmazonessSpiritualistSortName[] APPEND_RODATA = "Amazoness Spiritualist";
static const u8 sAmazonessSpySortName[] APPEND_RODATA = "Amazoness Spy";
static const u8 sAmazonessTraineeSortName[] APPEND_RODATA = "Amazoness Trainee";
static const u8 sAmazonessWarChiefSortName[] APPEND_RODATA = "Amazoness War Chief";
static const u8 sAnOwlOfLuckSortName[] APPEND_RODATA = "An Owl of Luck";
static const u8 sAtlanteanAttackSquadSortName[] APPEND_RODATA = "Atlantean Attack Squad";
static const u8 sAtlanteanDragoonsSortName[] APPEND_RODATA = "Atlantean Dragoons";
static const u8 sAtlanteanHeavyInfantrySortName[] APPEND_RODATA = "Atlantean Heavy Infantry";
static const u8 sAtlanteanMarksmanSortName[] APPEND_RODATA = "Atlantean Marksman";
static const u8 sBeastKingBarbarosSortName[] APPEND_RODATA = "Beast King Barbaros";
static const u8 sCelestialKnightlordParshathSortName[] APPEND_RODATA = "Celestial Knightlord Parshath";
static const u8 sChainsawInsectSortName[] APPEND_RODATA = "Chainsaw Insect";
static const u8 sCharmOfShabtiSortName[] APPEND_RODATA = "Charm of Shabti";
static const u8 sBazooTheSoulEaterSortName[] APPEND_RODATA = "Bazoo the Soul-Eater";
static const u8 sAshBlossomAndJoyousSpringSortName[] APPEND_RODATA = "Ash Blossom & Joyous Spring";
static const u8 sDoubleCycloneSortName[] APPEND_RODATA = "Double Cyclone";
static const u8 sForbiddenChaliceSortName[] APPEND_RODATA = "Forbidden Chalice";
static const u8 sForbiddenDressSortName[] APPEND_RODATA = "Forbidden Dress";
static const u8 sForbiddenLanceSortName[] APPEND_RODATA = "Forbidden Lance";
static const u8 sDramaticRescueSortName[] APPEND_RODATA = "Dramatic Rescue";
static const u8 sForgottenTempleOfTheDeepSortName[] APPEND_RODATA = "Forgotten Temple of the Deep";
static const u8 sClearViceDragonSortName[] APPEND_RODATA = "Clear Vice Dragon";
static const u8 sCyberneticMagicianSortName[] APPEND_RODATA = "Cybernetic Magician";
static const u8 sDarklordDesireSortName[] APPEND_RODATA = "Darklord Desire";
static const u8 sDeepSeaDivaSortName[] APPEND_RODATA = "Deep Sea Diva";
static const u8 sDivinerOfTheHeraldSortName[] APPEND_RODATA = "Diviner of the Herald";
static const u8 sElderEntityNordenSortName[] APPEND_RODATA = "Elder Entity Norden";
static const u8 sEnragedBattleOxSortName[] APPEND_RODATA = "Enraged Battle Ox";
static const u8 sFogKingSortName[] APPEND_RODATA = "Fog King";
static const u8 sGagagigoTheRisenSortName[] APPEND_RODATA = "Gagagigo the Risen";
static const u8 sGoldenHomunculusSortName[] APPEND_RODATA = "Golden Homunculus";
static const u8 sFusilierDragonTheDualModeBeastSortName[] APPEND_RODATA = "Fusilier Dragon, the Dual-Mode Beast";
static const u8 sGamecialTheSeaTurtleKaijuSortName[] APPEND_RODATA = "Gameciel, the Sea Turtle Kaiju";
static const u8 sGravekeepersAmbusherSortName[] APPEND_RODATA = "Gravekeeper's Ambusher";
static const u8 sGravekeepersCannonholderSortName[] APPEND_RODATA = "Gravekeeper's Cannonholder";

static const u16 sCustomCardsByName[NUM_CUSTOM_NAME_SORT_CARDS] APPEND_RODATA = {
  0x078E, // A Cat of Ill Omen
  0x046A, // A Hero Emerges
  0x046B, // A Hero Lives
  0x040B, // A Legendary Ocean
  0x046C, // A Wingbeat of Giant Dragon
  0x03A0, // Absorbing Kid from the Sky
  0x0641, // Ace of Sword
  0x0642, // Ace of Wand
  0x079D, // Aegis of the Ocean Dragon Lord
  0x0381, // Airknight Parshath
  0x0798, // Alector, Sovereign of Birds
  0x06EE, // All-Out Attacks
  0x046D, // Allure of Darkness
  0x0572, // Alluring Mirror Split
  0x03F0, // Amazoness Archer
  0x078F, // Amazoness Augusta
  0x0790, // Amazoness Baby Tiger
  0x0799, // Amazoness Call
  0x0791, // Amazoness Empress
  0x079A, // Amazoness Fighting Spirit
  0x079E, // Amazoness Hall
  0x079B, // Amazoness Heirloom
  0x079F, // Amazoness Hot Spring
  0x07A0, // Amazoness Onslaught
  0x0792, // Amazoness Pet Liger
  0x0793, // Amazoness Pet Liger King
  0x0794, // Amazoness Princess
  0x0795, // Amazoness Queen
  0x0796, // Amazoness Sage
  0x0797, // Amazoness Scouts
  0x079C, // Amazoness Secret Arts
  0x07A1, // Amazoness Shamanism
  0x07A2, // Amazoness Spellcaster
  0x07A7, // Amazoness Spiritualist
  0x07A8, // Amazoness Spy
  0x03C0, // Amazoness Tiger
  0x07A9, // Amazoness Trainee
  0x07A3, // Amazoness Village
  0x07AA, // Amazoness War Chief
  0x07A6, // Amazoness Willpower
  0x0573, // Ambush Fangs
  0x0382, // Amphibious Bugroth MK-3
  0x046E, // Amulet Dragon
  0x07AB, // An Owl of Luck
  0x06EF, // Ancient Fairy Dragon
  0x06F0, // Ancient Gear
  0x06F1, // Ancient Gear Advance
  0x06F2, // Ancient Gear Beast
  0x06F3, // Ancient Gear Cannon
  0x06F4, // Ancient Gear Castle
  0x06F5, // Ancient Gear Commander
  0x06F6, // Ancient Gear Dark Golem
  0x06F7, // Ancient Gear Dragon
  0x06F8, // Ancient Gear Drill
  0x06F9, // Ancient Gear Duel
  0x06FA, // Ancient Gear Engineer
  0x06FB, // Ancient Gear Explosive
  0x06FC, // Ancient Gear Factory
  0x06FD, // Ancient Gear Fist
  0x06FE, // Ancient Gear Frame
  0x06FF, // Ancient Gear Fusion
  0x0700, // Ancient Gear Gadjiltron Chimera
  0x0701, // Ancient Gear Gadjiltron Dragon
  0x0702, // Ancient Gear Golem
  0x0703, // Ancient Gear Golem - Ultimate Pound
  0x0704, // Ancient Gear Knight
  0x0705, // Ancient Gear Megaton Golem
  0x0706, // Ancient Gear Soldier
  0x0707, // Ancient Gear Statue
  0x0708, // Ancient Gear Tank
  0x0709, // Ancient Gear Tanker
  0x070A, // Ancient Gear Workshop
  0x070B, // Ancient Leaf
  0x033E, // Ancient Rules
  0x070C, // Ancient Sacred Wyvern
  0x046F, // Andro Sphinx
  0x0457, // Angel's Tear
  0x07A4, // Ante
  0x0470, // Anti-Spell Fragrance
  0x0473, // Apparition
  0x0472, // Apprentice Illusion Magician
  0x0471, // Appropriate
  0x07A5, // Aqua Jet
  0x0643, // Arcana Call
  0x0644, // Arcana Force 0 - The Fool
  0x064A, // Arcana Force EX - The Chaos Ruler
  0x0645, // Arcana Force EX - The Dark Ruler
  0x0646, // Arcana Force EX - The Light Ruler
  0x0647, // Arcana Force I - The Magician
  0x0648, // Arcana Force III - The Empress
  0x0649, // Arcana Force IV - The Emperor
  0x064B, // Arcana Force V - The Hierophant
  0x064C, // Arcana Force VI - The Lovers
  0x064D, // Arcana Force VII - The Chariot
  0x064E, // Arcana Force VIII - The Strength
  0x064F, // Arcana Force XII - The Hangman
  0x0650, // Arcana Force XIV - Temperance
  0x0651, // Arcana Force XIX - The Sun
  0x0652, // Arcana Force XV - The Fiend
  0x0653, // Arcana Force XVIII - The Moon
  0x0654, // Arcana Force XXI - The World
  0x070D, // Arcana Knight Joker
  0x0655, // Arcana Reading
  0x0656, // Arcana Spread
  0x070E, // Arcane Barrier
  0x0574, // Arcanite Magician
  0x0453, // Archlord Kristya
  0x0477, // Armageddon Knight
  0x047B, // Armed Dragon LV10
  0x0478, // Armed Dragon LV3
  0x0479, // Armed Dragon LV5
  0x047A, // Armed Dragon LV7
  0x0657, // Armed Neos
  0x070F, // Armityle the Chaos Phantasm
  0x0575, // Armory Arm
  0x0576, // Aroma Blend
  0x0577, // Aroma Garden
  0x0578, // Aroma Gardening
  0x0579, // Aroma Jar
  0x057A, // Aromage Bergamot
  0x057B, // Aromage Cananga
  0x057C, // Aromage Jasmine
  0x057D, // Aromage Laurel
  0x057E, // Aromage Marjoram
  0x057F, // Aromage Rosemary
  0x0580, // Aromalilith Magnolia
  0x0581, // Aromalilith Rosalina
  0x0582, // Aromalilith Rosemary
  0x0583, // Aromaseraphy Jasmine
  0x0584, // Aromaseraphy Rosemary
  0x0585, // Aromaseraphy Sweet Marjoram
  0x03A1, // Arsenal Bug
  0x07B5, // Ash Blossom & Joyous Spring
  0x0455, // Athena
  0x07AC, // Atlantean Attack Squad
  0x07AD, // Atlantean Dragoons
  0x07AE, // Atlantean Heavy Infantry
  0x07AF, // Atlantean Marksman
  0x047C, // Attack and Receive
  0x0474, // Attack Guidance Armor
  0x0586, // Attack Pheromones
  0x0475, // Attack Reflector Unit
  0x0658, // Aurkus, Lightsworn Druid
  0x0409, // Autonomous Action Unit
  0x0587, // Azure-Eyes Silver Dragon
  0x0710, // Babycerasaurus
  0x047D, // Backfire
  0x0476, // Backup Squad
  0x0711, // Barrier Statue of the Stormwinds
  0x03A3, // Battle Footballer
  0x0712, // Battle Mania
  0x07B4, // Bazoo the Soul-Eater
  0x07B0, // Beast King Barbaros
  0x0715, // Beast Machine King Barbaros Ür
  0x03AC, // Berserk Gorilla
  0x0481, // Berserker Soul
  0x03E8, // Big Bang Shot
  0x0713, // Big Evolution Pill
  0x0482, // Birdface
  0x041C, // Black Luster Soldier - Envoy of the Beginning
  0x0588, // Black Rose Dragon
  0x0383, // Black Tyranno
  0x0714, // Black-Winged Dragon
  0x03C1, // Blast Held by a Tribute
  0x0385, // Blasting The Ruins
  0x0589, // Blessed Winds
  0x0354, // Block Attack
  0x0403, // Blowback Dragon
  0x0483, // Blue-Eyes Alternative Ultimate Dragon
  0x033D, // Blue-Eyes Alternative White Dragon
  0x0402, // Blue-Eyes Chaos Dragon
  0x0329, // Blue-Eyes Chaos Max Dragon
  0x058A, // Blue-Eyes Jet Dragon
  0x0324, // Blue-Eyes Shining Dragon
  0x058B, // Blue-Eyes Solid Dragon
  0x058F, // Blue-Eyes Spirit Dragon
  0x058C, // Blue-Eyes Tyrant Dragon
  0x058D, // Blue-Eyes Ultimate Spirit Dragon
  0x058E, // Bond Between Teacher and Student
  0x0405, // Book of Life
  0x03AE, // Book of Moon
  0x0406, // Book of Taiyou
  0x0722, // Boot-Up Soldier - Dread Dynamo
  0x03D5, // Bottomless Shifting Sand
  0x0345, // Bowganian
  0x0484, // Break the Destiny
  0x03C4, // Breaker the Magical Warrior
  0x0590, // Brionac, Dragon of the Ice Barrier
  0x0485, // Bubble Blaster
  0x0486, // Burden of the Mighty
  0x03AF, // Burning Algae
  0x03A2, // Burning Land
  0x03ED, // Caius the Shadow Monarch
  0x0363, // Call of the Haunted
  0x0487, // Call of the Mummy
  0x0488, // Cannonball Spear Shellfish
  0x0388, // Card Destruction
  0x0326, // Card Of Demise
  0x0327, // Card Of Sanctity
  0x0723, // Castel, the Skyblaster Musketeer
  0x0347, // Cat's Ear Tribe
  0x0659, // Celestia, Lightsworn Angel
  0x07B1, // Celestial Knightlord Parshath
  0x0489, // Celestial Sword - Eatos
  0x032A, // Chain Energy
  0x0591, // Chain Material
  0x0716, // Chain Strike
  0x0717, // Chain Summoning
  0x07B2, // Chainsaw Insect
  0x0718, // Chaos Ancient Gear Giant
  0x0404, // Chaos Command Magician
  0x041B, // Chaos Emperor Dragon - Envoy of the End
  0x048A, // Chaos Form
  0x03AD, // Chaos Greed
  0x065A, // Charge of the Light Brigade
  0x07B3, // Charm of Shabti
  0x048B, // Chicken Game
  0x048C, // Chimeratech Fortress Dragon
  0x048D, // Chimeratech Megafleet Dragon
  0x043E, // Chimeratech Overdragon
  0x048E, // Chimeratech Rampage Dragon
  0x065B, // Chrysalis Chicky
  0x065C, // Chrysalis Dolphin
  0x065D, // Chrysalis Mole
  0x065E, // Chrysalis Pantail
  0x065F, // Chrysalis Pinny
  0x07BC, // Clear Vice Dragon
  0x048F, // Clock Tower Prison
  0x0660, // Cocoon Party
  0x0661, // Cocoon Rebirth
  0x0387, // Coffin Seller
  0x0490, // Cold Wave
  0x0592, // Colossal Fighter
  0x0662, // Colosseum - Cage of the Gladiator Beasts
  0x03C3, // Confiscation
  0x0663, // Contact
  0x0664, // Contact Gate
  0x0491, // Continuous Destruction Punch
  0x0665, // Convert Contact
  0x032D, // Copycat
  0x0719, // Coral Dragon
  0x033C, // Cost Down
  0x0459, // Court of Justice
  0x03D1, // Creature Swap
  0x071A, // Crimson Blader
  0x071B, // Crimson Dragon
  0x0666, // Cross Keeper
  0x071C, // Cross-Dimensional Duel
  0x0593, // Cup of Ace
  0x0348, // Cure Mermaid
  0x0667, // Curious, the Lightsworn Dominion
  0x0386, // Curse Of Darkness
  0x0465, // Cyber Barrier Dragon
  0x03EA, // Cyber Dragon
  0x071D, // Cyber Dragon Infinity
  0x0492, // Cyber Eltanin
  0x03EC, // Cyber End Dragon
  0x0493, // Cyber Kirin
  0x0466, // Cyber Laser Dragon
  0x0494, // Cyber Phoenix
  0x0594, // Cyber Slash Harpie Lady
  0x071E, // Cyber Slash Harpie Lady
  0x03EB, // Cyber Twin Dragon
  0x0495, // Cyber Valley
  0x043F, // Cybernetic Fusion Support
  0x07BD, // Cybernetic Magician
  0x0496, // Cybernetic Zone
  0x049A, // D - Burst
  0x049B, // D - Force
  0x0497, // D - Tactics
  0x0498, // D - Time
  0x03C2, // D.D. Warrior
  0x0595, // Damage = Reptile
  0x0724, // Damage = Reptile
  0x0499, // Damage Polarizer
  0x03A4, // Dancing Fairy
  0x0469, // Dark Armed Dragon
  0x049C, // Dark Blade the Dragon Knight
  0x0596, // Dark Burning Attack
  0x0597, // Dark Burning Magic
  0x0598, // Dark Calling
  0x04A1, // Dark City at Midnight
  0x0599, // Dark Contact
  0x038A, // Dark Driceratops
  0x03DE, // Dark Dust Spirit
  0x0467, // Dark End Dragon
  0x059A, // Dark Fusion
  0x049D, // Dark Grepher
  0x071F, // Dark Horus
  0x059B, // Dark Magic Attack
  0x0346, // Dark Magic Curtain
  0x059C, // Dark Magic Inheritance
  0x059D, // Dark Magic Veil
  0x059E, // Dark Magical Circle
  0x0725, // Dark Magical Circle
  0x049E, // Dark Magician Girl the Dragon Knight
  0x059F, // Dark Magician Girl the Magician's Apprentice
  0x0720, // Dark Magician Girl the Magician's Apprentice
  0x040C, // Dark Magician of Chaos
  0x05A0, // Dark Magician of Destruction
  0x04A2, // Dark Magician the Dragon Knight
  0x05A1, // Dark Magician the Magician of Black Magic
  0x0726, // Dark Magician the Magician of Black Magic
  0x05A2, // Dark Renewal
  0x0389, // Dark Room Of Nightmare
  0x03C7, // Dark Snake Syndrome
  0x05A3, // Dark Strike Fighter
  0x05A4, // Dark Supremacy
  0x0721, // Darkblaze Dragon
  0x07BE, // Darklord Desire
  0x03B0, // Darklord Marie
  0x049F, // Darklord Nurse Reficule
  0x04A0, // Darkness Neosphere
  0x0407, // De-Fusion
  0x0727, // De-Synchro
  0x0322, // Deck Destruction Virus
  0x04A3, // Decoy Dragon
  0x040D, // Dedication through Light and Darkness
  0x07BF, // Deep Sea Diva
  0x05A9, // Deep-Eyes White Dragon
  0x0355, // Delinquent Duo
  0x0728, // Demise, King of Armageddon
  0x04A4, // Des Counterblow
  0x03C5, // Des Kangaroo
  0x0349, // Des Koala
  0x04A5, // Despair from the Dark
  0x05A5, // Destined Rivals
  0x04A6, // Destiny Draw
  0x04A7, // Destiny End Dragoon
  0x04A8, // Destiny HERO - Blade Master
  0x04A9, // Destiny HERO - Captain Tenacious
  0x04AA, // Destiny HERO - Celestial
  0x04AB, // Destiny HERO - Dangerous
  0x04AC, // Destiny HERO - Dark Angel
  0x04AD, // Destiny HERO - Dasher
  0x04AE, // Destiny HERO - Decider
  0x04AF, // Destiny HERO - Defender
  0x04B0, // Destiny HERO - Denier
  0x04CD, // Destiny HERO - Destro-Dogma
  0x04B1, // Destiny HERO - Destroyer Phoenix Enforcer
  0x04B2, // Destiny HERO - Diamond Dude
  0x04B3, // Destiny HERO - Disk Commander
  0x04B4, // Destiny HERO - Dogma
  0x04B5, // Destiny HERO - Dominance
  0x04B6, // Destiny HERO - Doom Lord
  0x04BB, // Destiny HERO - Doom Overlord
  0x04B7, // Destiny HERO - Double Dude
  0x04B8, // Destiny HERO - Drawhand
  0x04B9, // Destiny HERO - Dread Servant
  0x04BA, // Destiny HERO - Dreadmaster
  0x04BC, // Destiny HERO - Dreadnought Master
  0x04BD, // Destiny HERO - Dreadnought Servant
  0x04BE, // Destiny HERO - Dreamer
  0x04BF, // Destiny HERO - Drilldark
  0x04C0, // Destiny HERO - Dunker
  0x04C7, // Destiny HERO - Dusktopia
  0x04C1, // Destiny HERO - Dynatag
  0x04C2, // Destiny HERO - Dystopia
  0x04C3, // Destiny HERO - Fear Monger
  0x04C4, // Destiny HERO - Malicious
  0x04C5, // Destiny HERO - Plasma
  0x03CA, // Dice Jar
  0x04C6, // Different Dimension Capsule
  0x0408, // Diffusion Wave-Motion
  0x04C8, // Dimension Fusion
  0x0458, // Divine Sanctuary
  0x04C9, // Divine Serpent Geh
  0x07C0, // Diviner of the Herald
  0x04CE, // Doctor D
  0x04CA, // Don Zaloog
  0x04CF, // Doom Virus Dragon
  0x04D0, // Doppelganger
  0x039C, // Double Coston
  0x07B6, // Double Cyclone
  0x04CB, // Double Spell
  0x0338, // Double Summon
  0x0729, // Double Tool C&D
  0x05AA, // Dragon Master Magia
  0x05A7, // Dragon Ravine
  0x05A8, // Dragon Shrine
  0x05AB, // Dragon Spirit of White
  0x073D, // Dragon's Mirror
  0x04CC, // Dragon's Rage
  0x04D9, // Drain Time
  0x0356, // Draining Shield
  0x07BA, // Dramatic Rescue
  0x05A6, // Dried Winds
  0x03C6, // Drillago
  0x03A6, // Drop Off
  0x03E4, // Dust Tornado
  0x0434, // E - Emergency Call
  0x05AC, // Ebon Illusion Magician
  0x0368, // Ebon Magician Curran
  0x03E5, // Ectoplasmer
  0x04D1, // Egyptian God Slime
  0x0668, // Ehren, Lightsworn Monk
  0x05AD, // El Shaddoll Anoyatyllis
  0x05AE, // El Shaddoll Apkallone
  0x05AF, // El Shaddoll Construct
  0x05B0, // El Shaddoll Fusion
  0x05B1, // El Shaddoll Grysta
  0x05B2, // El Shaddoll Meshahrail
  0x05B3, // El Shaddoll Shekhinaga
  0x05B4, // El Shaddoll Wendigo
  0x05B5, // El Shaddoll Winda
  0x07C1, // Elder Entity Norden
  0x0427, // Elemental HERO Absolute Zero
  0x0669, // Elemental HERO Air Neos
  0x066A, // Elemental HERO Aqua Neos
  0x03F1, // Elemental HERO Avian
  0x03F6, // Elemental HERO Bladedge
  0x043C, // Elemental HERO Blazeman
  0x066B, // Elemental HERO Brave Neos
  0x03F4, // Elemental HERO Bubbleman
  0x03F2, // Elemental HERO Burstinatrix
  0x043A, // Elemental HERO Captain Gold
  0x066C, // Elemental HERO Chaos Neos
  0x03F7, // Elemental HERO Clayman
  0x0438, // Elemental HERO Core
  0x066D, // Elemental HERO Cosmo Neos
  0x066E, // Elemental HERO Dark Neos
  0x0417, // Elemental HERO Electrum
  0x042C, // Elemental HERO Escuridao
  0x0411, // Elemental HERO Flame Wingman
  0x066F, // Elemental HERO Flare Neos
  0x042A, // Elemental HERO Flash
  0x042B, // Elemental HERO Gaia
  0x0670, // Elemental HERO Glow Neos
  0x0671, // Elemental HERO Grand Neos
  0x0423, // Elemental HERO Great Tornado
  0x0420, // Elemental HERO Heat
  0x043B, // Elemental HERO Ice Edge
  0x042E, // Elemental HERO Inferno
  0x0425, // Elemental HERO Knospe
  0x0421, // Elemental HERO Lady Heat
  0x0672, // Elemental HERO Magma Neos
  0x0673, // Elemental HERO Marine Neos
  0x0416, // Elemental HERO Mariner
  0x03F8, // Elemental HERO Mudballman
  0x0674, // Elemental HERO Nebula Neos
  0x042F, // Elemental HERO Necroid Shaman
  0x0418, // Elemental HERO Necroshade
  0x041D, // Elemental HERO Neos
  0x0422, // Elemental HERO Neos Alius
  0x04D2, // Elemental HERO Neos Kluger
  0x041F, // Elemental HERO Ocean
  0x040F, // Elemental HERO Phoenix Enforcer
  0x0430, // Elemental HERO Plasma Vice
  0x0426, // Elemental HERO Poison Rose
  0x040A, // Elemental HERO Rampart Blaster
  0x0412, // Elemental HERO Shining Flare Wingman
  0x0675, // Elemental HERO Shining Neos Wingman
  0x0410, // Elemental HERO Shining Phoenix Enforcer
  0x03F3, // Elemental HERO Sparkman
  0x0676, // Elemental HERO Spirit of Neos
  0x040E, // Elemental HERO Steam Healer
  0x0677, // Elemental HERO Storm Neos
  0x043D, // Elemental HERO Stratos
  0x0439, // Elemental HERO Sunrise
  0x0413, // Elemental HERO Tempest
  0x0424, // Elemental HERO Terra Firma
  0x042D, // Elemental HERO The Shining
  0x0415, // Elemental HERO Thunder Giant
  0x0429, // Elemental HERO Voltic
  0x0428, // Elemental HERO Wild Wingman
  0x0414, // Elemental HERO Wildedge
  0x03F5, // Elemental HERO Wildheart
  0x041E, // Elemental HERO Woodsman
  0x04D3, // Emergency Provisions
  0x0678, // EN - Engage Neo Space
  0x0679, // EN Shuffle
  0x067A, // EN Wave
  0x072A, // End of the World
  0x067B, // Enlightenment Dragon
  0x07C2, // Enraged Battle Ox
  0x05B6, // Eternal Soul
  0x05B7, // Evil Assault
  0x05B8, // Evil Dragon Ananta
  0x05B9, // Evil HERO Adusted Gold
  0x05BA, // Evil HERO Dark Gaia
  0x05BB, // Evil HERO Darkest Knight
  0x05BC, // Evil HERO Dead-End Prison
  0x05BD, // Evil HERO Infernal Gainer
  0x05BE, // Evil HERO Infernal Prodigy
  0x05BF, // Evil HERO Infernal Rider
  0x05C0, // Evil HERO Infernal Sniper
  0x05C1, // Evil HERO Inferno Wing
  0x05C2, // Evil HERO Inferno Wing - Backfire
  0x05C3, // Evil HERO Lightning Golem
  0x05C4, // Evil HERO Malicious Bane
  0x05C5, // Evil HERO Malicious Edge
  0x05C6, // Evil HERO Malicious Fiend
  0x05C7, // Evil HERO Neos Lord
  0x05C8, // Evil HERO Sinister Necrom
  0x05C9, // Evil HERO Toxic Bubble
  0x05CA, // Evil HERO Vicious Claws
  0x05CB, // Evil HERO Wild Cyclone
  0x05CC, // Evil Mind
  0x072B, // Evolzar Dolkka
  0x032C, // Exchange
  0x072C, // Exchange of the Spirit
  0x04D4, // Exodius the Ultimate Forbidden Lord
  0x072D, // Factory of 100 Machines
  0x033B, // Fairy Box
  0x0341, // Familiar Knight
  0x04D5, // Fatal Abacus
  0x067C, // Favorite Contact
  0x04D6, // Felgrand Dragon
  0x067D, // Felis, Lightsworn Archer
  0x03B1, // Fenrir
  0x072E, // Field Barrier
  0x04DA, // Fields Sanctuary
  0x039F, // Final Countdown
  0x03D6, // Fire Princess
  0x04D7, // Fires of Doomsday
  0x072F, // Flame Ruler
  0x067E, // Flavian - Colosseum of the Gladiator Beasts
  0x07C3, // Fog King
  0x07B7, // Forbidden Chalice
  0x07B8, // Forbidden Dress
  0x07B9, // Forbidden Lance
  0x04D8, // Forced Requisition
  0x07BB, // Forgotten Temple of the Deep
  0x0730, // Formula Synchron
  0x0731, // Fossil Excavation
  0x07C6, // Fusilier Dragon, the Dual-Mode Beast
  0x05CD, // Fusion Deployment
  0x04DB, // Fusion Destiny
  0x04DC, // Fusion Gate
  0x0431, // Fusion Recovery
  0x0442, // Fusion Sage
  0x0437, // Future Fusion
  0x0732, // Gadget Box
  0x07C4, // Gagagigo the Risen
  0x07C7, // Gameciel, the Sea Turtle Kaiju
  0x05CE, // Gandora-G the Dragon of Destruction
  0x05CF, // Gandora-X the Dragon of Demolition
  0x0733, // Gandora-X the Dragon of Demolition
  0x0680, // Garoth, Lightsworn Warrior
  0x04DD, // Gate Guardians Combined
  0x0734, // Geartown
  0x0681, // Generation Next
  0x03DF, // Ghost Knight of Jackal
  0x04DE, // Gift Card
  0x037F, // Gift Of The Mystical Elf
  0x037D, // Gilasaurus
  0x0682, // Gladiator Beast Alexander
  0x0683, // Gladiator Beast Andabata
  0x0684, // Gladiator Beast Andal
  0x0685, // Gladiator Beast Attorix
  0x0686, // Gladiator Beast Augustus
  0x0688, // Gladiator Beast Bestiari
  0x0689, // Gladiator Beast Claudius
  0x068A, // Gladiator Beast Dareios
  0x068B, // Gladiator Beast Darius
  0x068C, // Gladiator Beast Dimacari
  0x068D, // Gladiator Beast Domitianus
  0x068E, // Gladiator Beast Dragases
  0x068F, // Gladiator Beast Equeste
  0x0690, // Gladiator Beast Essedarii
  0x0691, // Gladiator Beast Gaiodiaz
  0x0692, // Gladiator Beast Gistel
  0x0693, // Gladiator Beast Gyzarus
  0x0694, // Gladiator Beast Heraklinos
  0x0695, // Gladiator Beast Hoplomus
  0x0696, // Gladiator Beast Lanista
  0x0697, // Gladiator Beast Laquari
  0x0698, // Gladiator Beast Murmillo
  0x0699, // Gladiator Beast Nerokius
  0x069A, // Gladiator Beast Noxious
  0x069B, // Gladiator Beast Octavius
  0x069C, // Gladiator Beast Retiari
  0x069D, // Gladiator Beast Sagittarii
  0x069E, // Gladiator Beast Samnite
  0x069F, // Gladiator Beast Secutor
  0x06A0, // Gladiator Beast Spartacus
  0x06A1, // Gladiator Beast Tamer Editor
  0x06A2, // Gladiator Beast Torax
  0x06A3, // Gladiator Beast Tygerius
  0x06A4, // Gladiator Beast Vespasius
  0x06A5, // Gladiator Beast War Chariot
  0x06A6, // Gladiator Beast's Battle Archfiend Shield
  0x06A7, // Gladiator Beast's Battle Gladius
  0x0687, // Gladiator Beast's Battle Halberd
  0x06A8, // Gladiator Beast's Battle Manica
  0x06A9, // Gladiator Beast's Medusa Shield
  0x06AA, // Gladiator Beast's Valor
  0x06AB, // Gladiator Naumachia
  0x0735, // Gladiator Proving Ground
  0x06AC, // Glorious Illusion
  0x03A7, // Goblin King
  0x0351, // Goblin Thief
  0x04DF, // Goddess Bow
  0x07C5, // Golden Homunculus
  0x04E0, // Gorz the Emissary of Darkness
  0x05D0, // Goyo Guardian
  0x038B, // Graceful Charity
  0x03AB, // Graceful Dice
  0x067F, // Gragonith, Lightsworn Dragon
  0x03A8, // Granadora
  0x0736, // Grand Convergence
  0x04E1, // Granmarg the Rock Monarch
  0x07C8, // Gravekeeper's Ambusher
  0x07C9, // Gravekeeper's Cannonholder
  0x03C9, // Gravekeeper's Servant
  0x037E, // Gravity Bind
  0x038C, // Great Maju Garzett
  0x0737, // Great Poseidon Beetle
  0x0738, // Green Baboon, Defender of the Forest
  0x04E2, // Green Gadget
  0x0397, // Gren Maju Da Eiza
  0x05D1, // Grinder Golem
  0x04E3, // Ground Collapse
  0x0379, // Guardian Angel Joan
  0x04E4, // Guardian Dreadscythe
  0x04E9, // Guardian Eatos
  0x034B, // Guardian Treasure
  0x0739, // Gungnir, Dragon of the Ice Barrier
  0x03AA, // Gyaku-Gire Panda
  0x0433, // H - Heated Heart
  0x047E, // Hamon, Lord of Striking Thunder
  0x05D2, // Harpie Channeler
  0x05D3, // Harpie Conductor
  0x05D4, // Harpie Dancer
  0x05D5, // Harpie Harpist
  0x03F9, // Harpie Lady 1
  0x03FA, // Harpie Lady 2
  0x03FB, // Harpie Lady 3
  0x05D6, // Harpie Lady Elegance
  0x04E5, // Harpie Lady Phoenix Formation
  0x05D7, // Harpie Oracle
  0x05D8, // Harpie Perfumer
  0x05D9, // Harpie Queen
  0x05DA, // Harpie's Feather Rest
  0x05DB, // Harpie's Feather Storm
  0x0401, // Harpie's Pet Baby Dragon
  0x05DD, // Harpie's Pet Phantasmal Dragon
  0x05DC, // Harpies' Hunting Ground
  0x0352, // Hayabusa Knight
  0x045A, // Hecatrice
  0x05DE, // Helshaddoll Hollow
  0x04EA, // Herald of Creation
  0x05DF, // Herald of Perfection
  0x073A, // Herald of the Arc Light
  0x05E0, // Herald of Ultimateness
  0x073B, // Herald of Ultimateness
  0x04E6, // Hero Flash!!
  0x05E1, // Hero Kid
  0x04EB, // Holactie the Creator of Light
  0x073C, // Honest
  0x04ED, // Horus the Black Flame Dragon LV4
  0x04EE, // Horus the Black Flame Dragon LV6
  0x04EC, // Horus the Black Flame Dragon LV8
  0x05E2, // Humid Winds
  0x073E, // Hunting Instinct
  0x03A9, // Hyper Hammerhead
  0x05E3, // Hysteric Party
  0x05E4, // Hysteric Sign
  0x073F, // Icarus Attack
  0x05E5, // Illusion Magic
  0x05E6, // Illusion of Chaos
  0x0396, // Imperial Order
  0x04E7, // Insect Imitation
  0x06AD, // Instant Contact
  0x04E8, // Instant Fusion
  0x06AE, // Instant Neo Space
  0x03D7, // Invader of the Throne
  0x0452, // Iofiel
  0x05E7, // Ipiria
  0x06AF, // Jain, Lightsworn Paladin
  0x06B0, // Jain, Twilightsworn General
  0x034C, // Jar of Greed
  0x03C8, // Jar Robber
  0x06B1, // Jenis, Lightsworn Mender
  0x04EF, // Jowgen the Spiritualist
  0x03CC, // Jowls of Dark Demise
  0x04F0, // Judgment Dragon
  0x06B2, // Judgment, the Dragon of Heaven
  0x0740, // Junk Synchron
  0x05E8, // Junk Warrior
  0x037C, // Just Deserts
  0x0395, // KA-2 Des Scissors
  0x032F, // Kaibaman
  0x03E0, // Kaiser Colosseum
  0x0364, // Kaiser Glider
  0x05E9, // Keeper of Dragon Magic
  0x04F1, // King Dragun
  0x04F2, // King of the Swamp
  0x04F8, // King Tiger Wanghu
  0x03CD, // Kishido Spirit
  0x06B3, // Knight of Pentacles
  0x03CB, // Knight's Title
  0x04F3, // Kuraz the Light Monarch
  0x04F4, // Kuribandit
  0x04F5, // Last Turn
  0x04F6, // Legend of Heart
  0x04F7, // Legendary Flame Lord
  0x04F9, // Legendary Knight Critias
  0x04FA, // Legendary Knight Hermos
  0x04FB, // Legendary Knight Timaeus
  0x05EA, // Legendary Maju Garzett
  0x04FC, // Lekunga
  0x03D2, // Lesser Fiend
  0x05EB, // Lev Shaddoll Fusion
  0x0400, // Level Limit - Area A
  0x03BE, // Level Limit Area B
  0x0741, // Level Tuning
  0x03E6, // Levia Dragon Daedalus
  0x0742, // Leviair the Sea Dragon
  0x0743, // Life Stream Dragon
  0x04FD, // Light and Darkness Dragon
  0x06B4, // Light Barrier
  0x0468, // Light End Dragon
  0x06B5, // Light Force
  0x06B6, // Light of Destruction
  0x06B7, // Light Spiral
  0x05ED, // Lightning Warrior
  0x05EC, // Lightserpent
  0x06B8, // Lightsworn Aegis
  0x06B9, // Lightsworn Barrier
  0x06BA, // Lightsworn Dragonling
  0x06BB, // Lightsworn Judgment
  0x06BC, // Lightsworn Sabre
  0x06BD, // Lightsworn Sanctuary
  0x037B, // Limiter Removal
  0x05EE, // Lonefire Blossom
  0x04FE, // Lord of the Red
  0x06BE, // Lumina, Lightsworn Summoner
  0x06BF, // Lumina, Twilightsworn Shaman
  0x034F, // Luster Dragon
  0x06C0, // Lyla, Lightsworn Sorceress
  0x06C1, // Lyla, Twilightsworn Enchantress
  0x0443, // Lyrilusc - Independent Nightingale
  0x04FF, // Ma'at
  0x0744, // Macro Cosmos
  0x034D, // Mad Sword Beast
  0x032E, // Mage Power
  0x0353, // Magic Cylinder
  0x033F, // Magic Jammer
  0x0745, // Magical Arm Shield
  0x0500, // Magical Dimension
  0x0501, // Magical Hats
  0x0746, // Magical Marionette
  0x03B2, // Magical Merchant
  0x0502, // Magical Plant Mandragola
  0x0503, // Magical Scientist
  0x0504, // Magical Stone Excavation
  0x05EF, // Magician Navigation
  0x05F0, // Magician of Dark Illusion
  0x0747, // Magician's Circle
  0x05F2, // Magician's Robe
  0x05F3, // Magician's Rod
  0x0323, // Magician's Valkyria
  0x05F1, // Magicians' Combination
  0x05F4, // Magicians' Souls
  0x0748, // Magna Drago
  0x0505, // Majestic Mech - Goryu
  0x03E3, // Maju Garzett
  0x03BD, // Man-Thro-Thro
  0x0506, // Manju of the Ten Thousand Hands
  0x035F, // Marauding Captain
  0x06C2, // March of the Dark Brigade
  0x0507, // Marshmallon
  0x0376, // Maryokutai
  0x0508, // Mask of Dispel
  0x033A, // Mask of Restrict
  0x050A, // Mask of the Accursed
  0x05F5, // Master of Chaos
  0x0509, // Master Peace, the True Dracoslaying King
  0x039B, // Mataza the Zapper
  0x050B, // Mausoleum of the Emperor
  0x050C, // Mazera DeVille
  0x0378, // Mefist The Infernal General
  0x0377, // Mermaid Knight
  0x050D, // Metamorphosis
  0x05F6, // Metaverse
  0x0357, // Meteor of Destruction
  0x050E, // Meteorain
  0x06C3, // Michael, the Arch-Lightsworn
  0x044D, // Mighty Angel Virch
  0x05F7, // Millennium-Eyes Restrict
  0x06C4, // Minerva, Lightsworn Maiden
  0x06C5, // Minerva, the Athenian Lightsworn
  0x06C6, // Minerva, the Exalted Lightsworn
  0x06C7, // Miracle Contact
  0x0419, // Miracle Fusion
  0x0749, // Mirage Dragon
  0x050F, // Mirage of Nightmare
  0x03FF, // Mirror Force
  0x0510, // Mirror Force Dragon
  0x03E2, // Mirror Wall
  0x03EE, // Mobius the Frost Monarch
  0x0366, // Moister Creature
  0x0511, // Molten Zombie
  0x05F8, // Molting Escape
  0x0512, // Monster Gate
  0x0513, // Monster Recovery
  0x074A, // Montage Dragon
  0x06C8, // Moon Token
  0x0514, // Morale Boost
  0x074B, // Morphtronic Accelerator
  0x074C, // Morphtronic Bind
  0x074D, // Morphtronic Boarden
  0x074E, // Morphtronic Boomboxen
  0x074F, // Morphtronic Cameran
  0x0750, // Morphtronic Celfon
  0x0751, // Morphtronic Clocken
  0x0752, // Morphtronic Converter
  0x0753, // Morphtronic Cord
  0x0754, // Morphtronic Datatron
  0x0755, // Morphtronic Earfon
  0x0756, // Morphtronic Engine
  0x0757, // Morphtronic Forcefield
  0x0758, // Morphtronic Impact Return
  0x0759, // Morphtronic Lantron
  0x075A, // Morphtronic Magnen
  0x075B, // Morphtronic Magnen Bar
  0x075C, // Morphtronic Map
  0x0765, // Morphtronic Mix-up
  0x075D, // Morphtronic Monitron
  0x075E, // Morphtronic Radion
  0x075F, // Morphtronic Remoten
  0x0760, // Morphtronic Repair Unit
  0x0761, // Morphtronic Rusty Engine
  0x0762, // Morphtronic Scannen
  0x0763, // Morphtronic Scopen
  0x0764, // Morphtronic Slingen
  0x0766, // Morphtronic Smartfon
  0x0767, // Morphtronic Staplen
  0x0768, // Morphtronic Telefon
  0x0769, // Morphtronic Vacuumen
  0x076A, // Morphtronic Videon
  0x0515, // Mucus Yolk
  0x05F9, // Mystic Mine
  0x0350, // Mystical Shine Ball
  0x0336, // Mystical Space Typhoon
  0x0516, // Mystik Wok
  0x05FA, // Naelshaddoll Ariel
  0x076B, // Naturia Beast
  0x0517, // Necrovalley
  0x0394, // Needle Burrower
  0x0518, // Needle Wall
  0x035D, // Negate Attack
  0x039A, // Negative Energy
  0x05FB, // Nehshaddoll Genius
  0x0519, // Neo Blue-Eyes Ultimate Dragon
  0x06C9, // Neo Space
  0x06CA, // Neo Space Connector
  0x06CB, // Neo-Spacian Air Hummingbird
  0x06CC, // Neo-Spacian Aqua Dolphin
  0x06CD, // Neo-Spacian Dark Panther
  0x06CE, // Neo-Spacian Flare Scarab
  0x06CF, // Neo-Spacian Glow Moss
  0x06D0, // Neo-Spacian Grand Mole
  0x06D1, // Neo-Spacian Marine Dolphin
  0x06D2, // Neo-Spacian Twinkle Moss
  0x051A, // Neos Wiseman
  0x05FC, // Nephe Shaddoll Fusion
  0x05FD, // Neutron Blast
  0x06D3, // NEX
  0x06D4, // NEXT
  0x051B, // Nibiru, the Primal Being
  0x0371, // Nightmare Horse
  0x03E1, // Nightmare Wheel
  0x076C, // Nitro Warrior
  0x051C, // Numinous Healer
  0x0436, // O - Oversoul
  0x0339, // Obnoxious Celtic Guardian
  0x05FE, // Offering to the Snake Deity
  0x051D, // Ojama King
  0x034E, // Ojama Trio
  0x051E, // Orichalcos Shunoros
  0x05FF, // Oshaleon
  0x051F, // Over Destiny
  0x0779, // Overflowing Treasure
  0x0440, // Overload Fusion
  0x0520, // Painful Choice
  0x0325, // Paladin Of White Dragon
  0x0521, // Pandemonium
  0x0522, // Parallel World Fusion
  0x06D5, // Pentacle of Ace
  0x037A, // Peten The Dark Clown
  0x0523, // Photon Generator Unit
  0x0365, // Piranha Army
  0x0524, // Poison of the Old Man
  0x03E9, // Polymerization
  0x03CE, // Possessed Dark Soul
  0x0441, // Power Bond
  0x076D, // Power Filter
  0x076E, // Power Tool Braver Dragon
  0x0600, // Power Tool Dragon
  0x039D, // Precious Cards From Beyond
  0x0601, // Predaplant Verte Anaconda
  0x045B, // Premature Burial
  0x0528, // Prophecy
  0x0525, // Protector of the Sanctuary
  0x03EF, // Proto-Cyber Dragon
  0x076F, // Pseudo Space
  0x06D6, // Punishment Dragon
  0x0334, // Pyramid of Light
  0x0602, // Qadshaddoll Keios
  0x0526, // Quintet Magician
  0x0435, // R - Righteous Justice
  0x06D7, // Raiden, Hand of the Lightsworn
  0x0527, // Raigeki Break
  0x0359, // Rain of Mercy
  0x0770, // Rainbow Dark Dragon
  0x0337, // Rare Metal Dragon
  0x03B3, // Raregold Armor
  0x0480, // Raviel, Lord of Phantasms
  0x06D8, // Realm of Light
  0x0399, // Reaper on the Nightmare
  0x0529, // Reaper Scythe - Dreadscythe
  0x0380, // Reckless Greed
  0x0603, // Red Dragon Archfiend
  0x052E, // Red Gadget
  0x0604, // Red Reboot
  0x052A, // Red-Eyes Black Dragon Sword
  0x052B, // Red-Eyes Dark Dragoon
  0x052C, // Red-Eyes Darkness Metal Dragon
  0x052D, // Red-Eyes Transmigration
  0x0605, // Reeshaddoll Wendi
  0x0606, // Reeshaddoll Wendikurhu
  0x052F, // Relay Soul
  0x035E, // Reload
  0x0608, // Reptilianne Echidna
  0x0609, // Reptilianne Gardna
  0x060A, // Reptilianne Gorgon
  0x060B, // Reptilianne Hydra
  0x060C, // Reptilianne Lamia
  0x060D, // Reptilianne Medusa
  0x060E, // Reptilianne Naga
  0x060F, // Reptilianne Poison
  0x0607, // Reptilianne Rage
  0x0610, // Reptilianne Scylla
  0x0611, // Reptilianne Servant
  0x0612, // Reptilianne Spawn
  0x0613, // Reptilianne Vaskii
  0x0614, // Reptilianne Viper
  0x06D9, // Rescue Cat
  0x06DA, // Rescue Rabbit
  0x0615, // Return of the Dragon Lords
  0x06DB, // Reversal of Fate
  0x0530, // Reverse of Reverse
  0x03B9, // Ring of Destruction
  0x06DC, // Rinyan, Lightsworn Rogue
  0x0342, // Riryoku
  0x0616, // Rise of the Snake Deity
  0x03B8, // Rivalry of Warlords
  0x0771, // Road Synchron
  0x0772, // Road Warrior
  0x0361, // Robbin' Goblin
  0x0362, // Robbin' Zombie
  0x0531, // Rocket Hermos Cannon
  0x0532, // Rope of Life
  0x0398, // Royal Decree
  0x03CF, // Royal Knight
  0x0533, // Royal Magical Library
  0x06DD, // Ryko, Lightsworn Hunter
  0x06DE, // Ryko, Twilightsworn Fighter
  0x03DD, // Ryu-Kishin Clown
  0x0344, // Sage's Stone
  0x0375, // Sasuke Samurai
  0x03BA, // Sasuke Samurai #2
  0x03BB, // Sasuke Samurai #3
  0x0534, // Scapegoat
  0x0773, // Scrap-Iron Scarecrow
  0x0340, // Seal of Orichalcos
  0x0535, // Second Coin Toss
  0x0360, // Secret Barrel
  0x0536, // Secret Village of the Spellcasters
  0x0617, // Secrets of Dark Magic
  0x036F, // Self-Destruct Button
  0x0451, // Seraphim Blaster
  0x0618, // Serpent Suppression
  0x03BC, // Servant of Catabolism
  0x03B7, // Seven Tools of the Bandit
  0x0619, // Shaddoll Beast
  0x061A, // Shaddoll Core
  0x061B, // Shaddoll Dragon
  0x061C, // Shaddoll Falco
  0x061D, // Shaddoll Fusion
  0x061E, // Shaddoll Hedgehog
  0x061F, // Shaddoll Hound
  0x0620, // Shaddoll Schism
  0x0621, // Shaddoll Squamata
  0x0537, // Share the Pain
  0x0450, // Shatiel
  0x0328, // Shield And Sword
  0x06DF, // Shire, Lightsworn Spirit
  0x0774, // Silent Magician LV4
  0x0775, // Silent Magician LV8
  0x0622, // Silver's Cry
  0x0776, // Simorgh, Bird of Ancestry
  0x0538, // Sixth Sense
  0x034A, // Skill Drain
  0x0539, // Skilled Dark Magician
  0x053A, // Skilled White Magician
  0x0370, // Skull Invitation
  0x0432, // Skyscraper
  0x053D, // Skyscraper 2 - Hero City
  0x0623, // Snake Deity's Command
  0x0624, // Snake Rain
  0x0625, // Snake Whistle
  0x035A, // Solar Flare Dragon
  0x0391, // Solar Ray
  0x06E0, // Solar Recharge
  0x053B, // Solemn Judgment
  0x0392, // Solemn Wishes
  0x0321, // Sorcerer of Dark Magic
  0x0335, // Soul Exchange
  0x0626, // Soul Servant
  0x0390, // Soul Taker
  0x053C, // Spark Blaster
  0x0343, // Spear Dragon
  0x053E, // Spell Absorption
  0x032B, // Spell Canceller
  0x0777, // Spell Chronicle
  0x03FC, // Spell Economics
  0x0778, // Spell Gear
  0x077A, // Spell Striker
  0x053F, // Sphinx Teleia
  0x03D9, // Spirit Caller
  0x03A5, // Spirit of the Breeze
  0x03D3, // Spirit of the Pot of Greed
  0x03B4, // Spirit Reaper
  0x03BF, // Spirit Ryu
  0x0333, // St Joan
  0x0627, // Stardust Dragon
  0x0540, // Statue of the Wicked
  0x0541, // Staunch Defender
  0x0393, // Stealth Bird
  0x0542, // Stray Lambs
  0x0543, // Stronghold the Moving Fortress
  0x06E1, // Suit of Sword X
  0x0544, // Summoner Monk
  0x0545, // Summoner of Illusions
  0x0546, // Super Polymerization
  0x0628, // Supreme King's Castle
  0x036E, // Swift Gaia The Fierce Knight
  0x077B, // T.G. Hyper Librarian
  0x077C, // Tatsunoko
  0x0547, // Terraforming
  0x0374, // Terrorking Salmon
  0x06E2, // Test Bear
  0x06E3, // Test Panther
  0x06E4, // Test Tiger
  0x0454, // Tethys, Goddess of Light
  0x0629, // That Grass Looks Greener
  0x0548, // The A. Forces
  0x0384, // The Agent Of Creation - Venus
  0x041A, // The Agent of Force - Mars
  0x0549, // The Agent of Judgment - Saturn
  0x054A, // The Agent of Wisdom - Mercury
  0x0446, // The Big Saturn
  0x044A, // The Blazing Mars
  0x054B, // The Claw of Hermos
  0x054C, // The Creator
  0x054D, // The Creator Incarnate
  0x036D, // The Dark Door
  0x062A, // The Dark Magicians
  0x0449, // The Despair Uranus
  0x054E, // The Eye of Timaeus
  0x054F, // The Fang of Critias
  0x03D8, // The Flute of Summoning Dragon
  0x0373, // The Forceful Sentry
  0x062B, // The Gaze of Timaeus
  0x0448, // The Grand Jupiter
  0x0550, // The Law of the Normal
  0x0551, // The Legendary Exodia Incarnate
  0x062C, // The Melody of Awakening Dragon
  0x03FE, // The Sanctuary in the Sky
  0x0552, // The Shallow Grave
  0x0445, // The Splendid Venus
  0x044B, // The Suppression Pluto
  0x044C, // The Supremacy Sun
  0x03D0, // The Thing in the Crater
  0x045F, // The Tricky
  0x0447, // The Tripper Mercury
  0x0444, // The Tyrant Neptune
  0x03FD, // The Unstoppable Exodia Incarnate
  0x062D, // The White Stone of Ancients
  0x062E, // The White Stone of Legend
  0x0462, // The Wicked Avatar
  0x0460, // The Wicked Dreadroot
  0x0461, // The Wicked Eraser
  0x03E7, // Theban Nightmare
  0x0553, // Theinen the Great Sphinx
  0x0554, // Thestalos the Firestorm Monarch
  0x036C, // Thousand Energy
  0x038F, // Thousand Knives
  0x06E5, // Thumbs Down
  0x03B5, // Thunder Crash
  0x0555, // Thunder Dragon Colossus
  0x0556, // Thunder Dragon Titan
  0x0557, // Timaeus the Knight of Destiny
  0x0630, // Timaeus the United Dragon
  0x062F, // Timaeus the United Magical Dragon
  0x0558, // Time Magic Hammer
  0x036B, // Time Seal
  0x077D, // Time Thief Redoer
  0x044E, // Tiny Angel
  0x0631, // Tohushaddoll Grysta
  0x0358, // Toll
  0x055A, // Toon World
  0x055B, // Tornado Bird
  0x0559, // Tornado Wall
  0x03B6, // Torpedo Fish
  0x06E6, // Tour of Doom
  0x0464, // Trade-In
  0x055C, // Trap Dustshoot
  0x0632, // Trap Trick
  0x0633, // Triangle Ecstasy Spark
  0x038D, // Triangle Power
  0x0463, // Tribute Doll
  0x077E, // Trishula, Dragon of the Ice Barrier
  0x06E7, // Trojan Gladiator Beast
  0x077F, // Tuningware
  0x0780, // Turbo Booster
  0x0781, // Turbo Cannon
  0x0782, // Turbo Rocket
  0x0783, // Turbo Synchron
  0x06E8, // Twilight Cloth
  0x06E9, // Twilight Eraser
  0x06EA, // Twilight Twin Dragons
  0x038E, // Twin Swords of Flashing Light - Tryce
  0x0784, // Tyranno Infinity
  0x055D, // Tyrant Burst Dragon
  0x039E, // Tyrant Dragon
  0x055E, // Tyrant Wing
  0x0785, // Ultimate Ancient Gear Golem
  0x055F, // Ultimate Conductor Tyranno
  0x0560, // Ultimate Obedient Fiend
  0x0330, // Ultimate Offering
  0x0786, // Ultimate Tyranno
  0x0634, // Ultra Polymerization
  0x0331, // United We Stand
  0x0787, // Unstable Evolution
  0x035C, // Upstart Goblin
  0x0788, // Urgent Tuning
  0x047F, // Uria, Lord of Searing Flames
  0x0456, // Valhalla, Hall of the Fallen
  0x0372, // Vampire Baby
  0x06EB, // Vanquishing Light
  0x03DA, // Vengeful Bog Spirit
  0x0635, // Vennominaga the Deity of Poisonous Snakes
  0x0636, // Vennominon the King of Poisonous Snakes
  0x0637, // Venom Boa
  0x0638, // Venom Burn
  0x0639, // Venom Cobra
  0x063A, // Venom Serpent
  0x063B, // Venom Shot
  0x063C, // Venom Snake
  0x063D, // Venom Swamp
  0x063E, // Viper's Rebirth
  0x0561, // Vision Fusion
  0x0562, // Vision HERO Adoration
  0x0563, // Vision HERO Faris
  0x0564, // Vision HERO Gravito
  0x0565, // Vision HERO Increase
  0x0566, // Vision HERO Minimum Ray
  0x0567, // Vision HERO Multiply Guy
  0x0568, // Vision HERO Poisoner
  0x0569, // Vision HERO Trinity
  0x056A, // Vision HERO Vyon
  0x0571, // Vision HERO Witch Raider
  0x056B, // Vision Release
  0x03DB, // Wall of Revealing Light
  0x0789, // Warrior of Atlantis
  0x036A, // Warrior of Zera
  0x056C, // Watapon
  0x078A, // Water Hazard
  0x0332, // Wave Motion Cannon
  0x078B, // Weapon Change
  0x0369, // Weather Report
  0x06EC, // Weiss, Lightsworn Archfiend
  0x078C, // Wetlands
  0x056D, // White Dragon Ritual
  0x0367, // White Magician Pikeru
  0x056E, // Wild Nature's Release
  0x03DC, // World Suppression
  0x056F, // Wroughtweiler
  0x06ED, // Wulf, Lightsworn Beast
  0x078D, // X-Saber Airbellum
  0x063F, // Yamorimori
  0x035B, // Yata-Garasu
  0x0570, // Yellow Gadget
  0x0640, // Yowie
  0x045C, // Yubel
  0x045D, // Yubel - Terror Incarnate
  0x045E, // Yubel - The Ultimate Nightmare
  0x03D4, // Zaborg the Thunder Monarch
  0x044F, // Zeriel
};

static const u16 sCustomCardNameSortOrder[NUM_CUSTOM_NAME_SORT_CARDS] APPEND_RODATA = {
  1, // A Cat of Ill Omen
  2, // A Hero Emerges
  3, // A Hero Lives
  4, // A Legendary Ocean
  5, // A Wingbeat of Giant Dragon
  6, // Absorbing Kid from the Sky
  7, // Ace of Sword
  8, // Ace of Wand
  9, // Aegis of the Ocean Dragon Lord
  10, // Airknight Parshath
  11, // Alector, Sovereign of Birds
  12, // All-Out Attacks
  13, // Allure of Darkness
  14, // Alluring Mirror Split
  15, // Amazoness Archer
  16, // Amazoness Augusta
  17, // Amazoness Baby Tiger
  18, // Amazoness Call
  19, // Amazoness Empress
  20, // Amazoness Fighting Spirit
  21, // Amazoness Hall
  22, // Amazoness Heirloom
  23, // Amazoness Hot Spring
  24, // Amazoness Onslaught
  25, // Amazoness Pet Liger
  26, // Amazoness Pet Liger King
  27, // Amazoness Princess
  28, // Amazoness Queen
  29, // Amazoness Sage
  30, // Amazoness Scouts
  31, // Amazoness Secret Arts
  32, // Amazoness Shamanism
  33, // Amazoness Spellcaster
  34, // Amazoness Spiritualist
  35, // Amazoness Spy
  36, // Amazoness Tiger
  37, // Amazoness Trainee
  38, // Amazoness Village
  39, // Amazoness War Chief
  40, // Amazoness Willpower
  41, // Ambush Fangs
  42, // Amphibious Bugroth MK-3
  43, // Amulet Dragon
  44, // An Owl of Luck
  45, // Ancient Fairy Dragon
  46, // Ancient Gear
  47, // Ancient Gear Advance
  48, // Ancient Gear Beast
  49, // Ancient Gear Cannon
  50, // Ancient Gear Castle
  51, // Ancient Gear Commander
  52, // Ancient Gear Dark Golem
  53, // Ancient Gear Dragon
  54, // Ancient Gear Drill
  55, // Ancient Gear Duel
  56, // Ancient Gear Engineer
  57, // Ancient Gear Explosive
  58, // Ancient Gear Factory
  59, // Ancient Gear Fist
  60, // Ancient Gear Frame
  61, // Ancient Gear Fusion
  62, // Ancient Gear Gadjiltron Chimera
  63, // Ancient Gear Gadjiltron Dragon
  64, // Ancient Gear Golem
  65, // Ancient Gear Golem - Ultimate Pound
  66, // Ancient Gear Knight
  67, // Ancient Gear Megaton Golem
  68, // Ancient Gear Soldier
  69, // Ancient Gear Statue
  70, // Ancient Gear Tank
  71, // Ancient Gear Tanker
  72, // Ancient Gear Workshop
  73, // Ancient Leaf
  74, // Ancient Rules
  75, // Ancient Sacred Wyvern
  76, // Andro Sphinx
  77, // Angel's Tear
  78, // Ante
  79, // Anti-Spell Fragrance
  80, // Apparition
  81, // Apprentice Illusion Magician
  82, // Appropriate
  83, // Aqua Jet
  84, // Arcana Call
  85, // Arcana Force 0 - The Fool
  86, // Arcana Force EX - The Chaos Ruler
  87, // Arcana Force EX - The Dark Ruler
  88, // Arcana Force EX - The Light Ruler
  89, // Arcana Force I - The Magician
  90, // Arcana Force III - The Empress
  91, // Arcana Force IV - The Emperor
  92, // Arcana Force V - The Hierophant
  93, // Arcana Force VI - The Lovers
  94, // Arcana Force VII - The Chariot
  95, // Arcana Force VIII - The Strength
  96, // Arcana Force XII - The Hangman
  97, // Arcana Force XIV - Temperance
  98, // Arcana Force XIX - The Sun
  99, // Arcana Force XV - The Fiend
  100, // Arcana Force XVIII - The Moon
  101, // Arcana Force XXI - The World
  102, // Arcana Knight Joker
  103, // Arcana Reading
  104, // Arcana Spread
  105, // Arcane Barrier
  106, // Arcanite Magician
  107, // Archlord Kristya
  108, // Armageddon Knight
  109, // Armed Dragon LV10
  110, // Armed Dragon LV3
  111, // Armed Dragon LV5
  112, // Armed Dragon LV7
  113, // Armed Neos
  114, // Armityle the Chaos Phantasm
  115, // Armory Arm
  116, // Aroma Blend
  117, // Aroma Garden
  118, // Aroma Gardening
  119, // Aroma Jar
  120, // Aromage Bergamot
  121, // Aromage Cananga
  122, // Aromage Jasmine
  123, // Aromage Laurel
  124, // Aromage Marjoram
  125, // Aromage Rosemary
  126, // Aromalilith Magnolia
  127, // Aromalilith Rosalina
  128, // Aromalilith Rosemary
  129, // Aromaseraphy Jasmine
  130, // Aromaseraphy Rosemary
  131, // Aromaseraphy Sweet Marjoram
  132, // Arsenal Bug
  133, // Ash Blossom & Joyous Spring
  134, // Athena
  135, // Atlantean Attack Squad
  136, // Atlantean Dragoons
  137, // Atlantean Heavy Infantry
  138, // Atlantean Marksman
  139, // Attack and Receive
  140, // Attack Guidance Armor
  141, // Attack Pheromones
  142, // Attack Reflector Unit
  143, // Aurkus, Lightsworn Druid
  144, // Autonomous Action Unit
  145, // Azure-Eyes Silver Dragon
  146, // Babycerasaurus
  147, // Backfire
  148, // Backup Squad
  149, // Barrier Statue of the Stormwinds
  150, // Battle Footballer
  151, // Battle Mania
  152, // Bazoo the Soul-Eater
  153, // Beast King Barbaros
  154, // Beast Machine King Barbaros Ür
  155, // Berserk Gorilla
  156, // Berserker Soul
  157, // Big Bang Shot
  158, // Big Evolution Pill
  159, // Birdface
  160, // Black Luster Soldier - Envoy of the Beginning
  161, // Black Rose Dragon
  162, // Black Tyranno
  163, // Black-Winged Dragon
  164, // Blast Held by a Tribute
  165, // Blasting The Ruins
  166, // Blessed Winds
  167, // Block Attack
  168, // Blowback Dragon
  169, // Blue-Eyes Alternative Ultimate Dragon
  170, // Blue-Eyes Alternative White Dragon
  171, // Blue-Eyes Chaos Dragon
  172, // Blue-Eyes Chaos Max Dragon
  173, // Blue-Eyes Jet Dragon
  174, // Blue-Eyes Shining Dragon
  175, // Blue-Eyes Solid Dragon
  176, // Blue-Eyes Spirit Dragon
  177, // Blue-Eyes Tyrant Dragon
  178, // Blue-Eyes Ultimate Spirit Dragon
  179, // Bond Between Teacher and Student
  180, // Book of Life
  181, // Book of Moon
  182, // Book of Taiyou
  183, // Boot-Up Soldier - Dread Dynamo
  184, // Bottomless Shifting Sand
  185, // Bowganian
  186, // Break the Destiny
  187, // Breaker the Magical Warrior
  188, // Brionac, Dragon of the Ice Barrier
  189, // Bubble Blaster
  190, // Burden of the Mighty
  191, // Burning Algae
  192, // Burning Land
  193, // Caius the Shadow Monarch
  194, // Call of the Haunted
  195, // Call of the Mummy
  196, // Cannonball Spear Shellfish
  197, // Card Destruction
  198, // Card Of Demise
  199, // Card Of Sanctity
  200, // Castel, the Skyblaster Musketeer
  201, // Cat's Ear Tribe
  202, // Celestia, Lightsworn Angel
  203, // Celestial Knightlord Parshath
  204, // Celestial Sword - Eatos
  205, // Chain Energy
  206, // Chain Material
  207, // Chain Strike
  208, // Chain Summoning
  209, // Chainsaw Insect
  210, // Chaos Ancient Gear Giant
  211, // Chaos Command Magician
  212, // Chaos Emperor Dragon - Envoy of the End
  213, // Chaos Form
  214, // Chaos Greed
  215, // Charge of the Light Brigade
  216, // Charm of Shabti
  217, // Chicken Game
  218, // Chimeratech Fortress Dragon
  219, // Chimeratech Megafleet Dragon
  220, // Chimeratech Overdragon
  221, // Chimeratech Rampage Dragon
  222, // Chrysalis Chicky
  223, // Chrysalis Dolphin
  224, // Chrysalis Mole
  225, // Chrysalis Pantail
  226, // Chrysalis Pinny
  227, // Clear Vice Dragon
  228, // Clock Tower Prison
  229, // Cocoon Party
  230, // Cocoon Rebirth
  231, // Coffin Seller
  232, // Cold Wave
  233, // Colossal Fighter
  234, // Colosseum - Cage of the Gladiator Beasts
  235, // Confiscation
  236, // Contact
  237, // Contact Gate
  238, // Continuous Destruction Punch
  239, // Convert Contact
  240, // Copycat
  241, // Coral Dragon
  242, // Cost Down
  243, // Court of Justice
  244, // Creature Swap
  245, // Crimson Blader
  246, // Crimson Dragon
  247, // Cross Keeper
  248, // Cross-Dimensional Duel
  249, // Cup of Ace
  250, // Cure Mermaid
  251, // Curious, the Lightsworn Dominion
  252, // Curse Of Darkness
  253, // Cyber Barrier Dragon
  254, // Cyber Dragon
  255, // Cyber Dragon Infinity
  256, // Cyber Eltanin
  257, // Cyber End Dragon
  258, // Cyber Kirin
  259, // Cyber Laser Dragon
  260, // Cyber Phoenix
  261, // Cyber Slash Harpie Lady
  262, // Cyber Slash Harpie Lady
  263, // Cyber Twin Dragon
  264, // Cyber Valley
  265, // Cybernetic Fusion Support
  266, // Cybernetic Magician
  267, // Cybernetic Zone
  268, // D - Burst
  269, // D - Force
  270, // D - Tactics
  271, // D - Time
  272, // D.D. Warrior
  273, // Damage = Reptile
  274, // Damage = Reptile
  275, // Damage Polarizer
  276, // Dancing Fairy
  277, // Dark Armed Dragon
  278, // Dark Blade the Dragon Knight
  279, // Dark Burning Attack
  280, // Dark Burning Magic
  281, // Dark Calling
  282, // Dark City at Midnight
  283, // Dark Contact
  284, // Dark Driceratops
  285, // Dark Dust Spirit
  286, // Dark End Dragon
  287, // Dark Fusion
  288, // Dark Grepher
  289, // Dark Horus
  290, // Dark Magic Attack
  291, // Dark Magic Curtain
  292, // Dark Magic Inheritance
  293, // Dark Magic Veil
  294, // Dark Magical Circle
  295, // Dark Magical Circle
  296, // Dark Magician Girl the Dragon Knight
  297, // Dark Magician Girl the Magician's Apprentice
  298, // Dark Magician Girl the Magician's Apprentice
  299, // Dark Magician of Chaos
  300, // Dark Magician of Destruction
  301, // Dark Magician the Dragon Knight
  302, // Dark Magician the Magician of Black Magic
  303, // Dark Magician the Magician of Black Magic
  304, // Dark Renewal
  305, // Dark Room Of Nightmare
  306, // Dark Snake Syndrome
  307, // Dark Strike Fighter
  308, // Dark Supremacy
  309, // Darkblaze Dragon
  310, // Darklord Desire
  311, // Darklord Marie
  312, // Darklord Nurse Reficule
  313, // Darkness Neosphere
  314, // De-Fusion
  315, // De-Synchro
  316, // Deck Destruction Virus
  317, // Decoy Dragon
  318, // Dedication through Light and Darkness
  319, // Deep Sea Diva
  320, // Deep-Eyes White Dragon
  321, // Delinquent Duo
  322, // Demise, King of Armageddon
  323, // Des Counterblow
  324, // Des Kangaroo
  325, // Des Koala
  326, // Despair from the Dark
  327, // Destined Rivals
  328, // Destiny Draw
  329, // Destiny End Dragoon
  330, // Destiny HERO - Blade Master
  331, // Destiny HERO - Captain Tenacious
  332, // Destiny HERO - Celestial
  333, // Destiny HERO - Dangerous
  334, // Destiny HERO - Dark Angel
  335, // Destiny HERO - Dasher
  336, // Destiny HERO - Decider
  337, // Destiny HERO - Defender
  338, // Destiny HERO - Denier
  339, // Destiny HERO - Destro-Dogma
  340, // Destiny HERO - Destroyer Phoenix Enforcer
  341, // Destiny HERO - Diamond Dude
  342, // Destiny HERO - Disk Commander
  343, // Destiny HERO - Dogma
  344, // Destiny HERO - Dominance
  345, // Destiny HERO - Doom Lord
  346, // Destiny HERO - Doom Overlord
  347, // Destiny HERO - Double Dude
  348, // Destiny HERO - Drawhand
  349, // Destiny HERO - Dread Servant
  350, // Destiny HERO - Dreadmaster
  351, // Destiny HERO - Dreadnought Master
  352, // Destiny HERO - Dreadnought Servant
  353, // Destiny HERO - Dreamer
  354, // Destiny HERO - Drilldark
  355, // Destiny HERO - Dunker
  356, // Destiny HERO - Dusktopia
  357, // Destiny HERO - Dynatag
  358, // Destiny HERO - Dystopia
  359, // Destiny HERO - Fear Monger
  360, // Destiny HERO - Malicious
  361, // Destiny HERO - Plasma
  362, // Dice Jar
  363, // Different Dimension Capsule
  364, // Diffusion Wave-Motion
  365, // Dimension Fusion
  366, // Divine Sanctuary
  367, // Divine Serpent Geh
  368, // Diviner of the Herald
  369, // Doctor D
  370, // Don Zaloog
  371, // Doom Virus Dragon
  372, // Doppelganger
  373, // Double Coston
  374, // Double Cyclone
  375, // Double Spell
  376, // Double Summon
  377, // Double Tool C&D
  378, // Dragon Master Magia
  379, // Dragon Ravine
  380, // Dragon Shrine
  381, // Dragon Spirit of White
  382, // Dragon's Mirror
  383, // Dragon's Rage
  384, // Drain Time
  385, // Draining Shield
  386, // Dramatic Rescue
  387, // Dried Winds
  388, // Drillago
  389, // Drop Off
  390, // Dust Tornado
  391, // E - Emergency Call
  392, // Ebon Illusion Magician
  393, // Ebon Magician Curran
  394, // Ectoplasmer
  395, // Egyptian God Slime
  396, // Ehren, Lightsworn Monk
  397, // El Shaddoll Anoyatyllis
  398, // El Shaddoll Apkallone
  399, // El Shaddoll Construct
  400, // El Shaddoll Fusion
  401, // El Shaddoll Grysta
  402, // El Shaddoll Meshahrail
  403, // El Shaddoll Shekhinaga
  404, // El Shaddoll Wendigo
  405, // El Shaddoll Winda
  406, // Elder Entity Norden
  407, // Elemental HERO Absolute Zero
  408, // Elemental HERO Air Neos
  409, // Elemental HERO Aqua Neos
  410, // Elemental HERO Avian
  411, // Elemental HERO Bladedge
  412, // Elemental HERO Blazeman
  413, // Elemental HERO Brave Neos
  414, // Elemental HERO Bubbleman
  415, // Elemental HERO Burstinatrix
  416, // Elemental HERO Captain Gold
  417, // Elemental HERO Chaos Neos
  418, // Elemental HERO Clayman
  419, // Elemental HERO Core
  420, // Elemental HERO Cosmo Neos
  421, // Elemental HERO Dark Neos
  422, // Elemental HERO Electrum
  423, // Elemental HERO Escuridao
  424, // Elemental HERO Flame Wingman
  425, // Elemental HERO Flare Neos
  426, // Elemental HERO Flash
  427, // Elemental HERO Gaia
  428, // Elemental HERO Glow Neos
  429, // Elemental HERO Grand Neos
  430, // Elemental HERO Great Tornado
  431, // Elemental HERO Heat
  432, // Elemental HERO Ice Edge
  433, // Elemental HERO Inferno
  434, // Elemental HERO Knospe
  435, // Elemental HERO Lady Heat
  436, // Elemental HERO Magma Neos
  437, // Elemental HERO Marine Neos
  438, // Elemental HERO Mariner
  439, // Elemental HERO Mudballman
  440, // Elemental HERO Nebula Neos
  441, // Elemental HERO Necroid Shaman
  442, // Elemental HERO Necroshade
  443, // Elemental HERO Neos
  444, // Elemental HERO Neos Alius
  445, // Elemental HERO Neos Kluger
  446, // Elemental HERO Ocean
  447, // Elemental HERO Phoenix Enforcer
  448, // Elemental HERO Plasma Vice
  449, // Elemental HERO Poison Rose
  450, // Elemental HERO Rampart Blaster
  451, // Elemental HERO Shining Flare Wingman
  452, // Elemental HERO Shining Neos Wingman
  453, // Elemental HERO Shining Phoenix Enforcer
  454, // Elemental HERO Sparkman
  455, // Elemental HERO Spirit of Neos
  456, // Elemental HERO Steam Healer
  457, // Elemental HERO Storm Neos
  458, // Elemental HERO Stratos
  459, // Elemental HERO Sunrise
  460, // Elemental HERO Tempest
  461, // Elemental HERO Terra Firma
  462, // Elemental HERO The Shining
  463, // Elemental HERO Thunder Giant
  464, // Elemental HERO Voltic
  465, // Elemental HERO Wild Wingman
  466, // Elemental HERO Wildedge
  467, // Elemental HERO Wildheart
  468, // Elemental HERO Woodsman
  469, // Emergency Provisions
  470, // EN - Engage Neo Space
  471, // EN Shuffle
  472, // EN Wave
  473, // End of the World
  474, // Enlightenment Dragon
  475, // Enraged Battle Ox
  476, // Eternal Soul
  477, // Evil Assault
  478, // Evil Dragon Ananta
  479, // Evil HERO Adusted Gold
  480, // Evil HERO Dark Gaia
  481, // Evil HERO Darkest Knight
  482, // Evil HERO Dead-End Prison
  483, // Evil HERO Infernal Gainer
  484, // Evil HERO Infernal Prodigy
  485, // Evil HERO Infernal Rider
  486, // Evil HERO Infernal Sniper
  487, // Evil HERO Inferno Wing
  488, // Evil HERO Inferno Wing - Backfire
  489, // Evil HERO Lightning Golem
  490, // Evil HERO Malicious Bane
  491, // Evil HERO Malicious Edge
  492, // Evil HERO Malicious Fiend
  493, // Evil HERO Neos Lord
  494, // Evil HERO Sinister Necrom
  495, // Evil HERO Toxic Bubble
  496, // Evil HERO Vicious Claws
  497, // Evil HERO Wild Cyclone
  498, // Evil Mind
  499, // Evolzar Dolkka
  500, // Exchange
  501, // Exchange of the Spirit
  502, // Exodius the Ultimate Forbidden Lord
  503, // Factory of 100 Machines
  504, // Fairy Box
  505, // Familiar Knight
  506, // Fatal Abacus
  507, // Favorite Contact
  508, // Felgrand Dragon
  509, // Felis, Lightsworn Archer
  510, // Fenrir
  511, // Field Barrier
  512, // Fields Sanctuary
  513, // Final Countdown
  514, // Fire Princess
  515, // Fires of Doomsday
  516, // Flame Ruler
  517, // Flavian - Colosseum of the Gladiator Beasts
  518, // Fog King
  519, // Forbidden Chalice
  520, // Forbidden Dress
  521, // Forbidden Lance
  522, // Forced Requisition
  523, // Forgotten Temple of the Deep
  524, // Formula Synchron
  525, // Fossil Excavation
  526, // Fusilier Dragon, the Dual-Mode Beast
  527, // Fusion Deployment
  528, // Fusion Destiny
  529, // Fusion Gate
  530, // Fusion Recovery
  531, // Fusion Sage
  532, // Future Fusion
  533, // Gadget Box
  534, // Gagagigo the Risen
  535, // Gameciel, the Sea Turtle Kaiju
  536, // Gandora-G the Dragon of Destruction
  537, // Gandora-X the Dragon of Demolition
  538, // Gandora-X the Dragon of Demolition
  539, // Garoth, Lightsworn Warrior
  540, // Gate Guardians Combined
  541, // Geartown
  542, // Generation Next
  543, // Ghost Knight of Jackal
  544, // Gift Card
  545, // Gift Of The Mystical Elf
  546, // Gilasaurus
  547, // Gladiator Beast Alexander
  548, // Gladiator Beast Andabata
  549, // Gladiator Beast Andal
  550, // Gladiator Beast Attorix
  551, // Gladiator Beast Augustus
  552, // Gladiator Beast Bestiari
  553, // Gladiator Beast Claudius
  554, // Gladiator Beast Dareios
  555, // Gladiator Beast Darius
  556, // Gladiator Beast Dimacari
  557, // Gladiator Beast Domitianus
  558, // Gladiator Beast Dragases
  559, // Gladiator Beast Equeste
  560, // Gladiator Beast Essedarii
  561, // Gladiator Beast Gaiodiaz
  562, // Gladiator Beast Gistel
  563, // Gladiator Beast Gyzarus
  564, // Gladiator Beast Heraklinos
  565, // Gladiator Beast Hoplomus
  566, // Gladiator Beast Lanista
  567, // Gladiator Beast Laquari
  568, // Gladiator Beast Murmillo
  569, // Gladiator Beast Nerokius
  570, // Gladiator Beast Noxious
  571, // Gladiator Beast Octavius
  572, // Gladiator Beast Retiari
  573, // Gladiator Beast Sagittarii
  574, // Gladiator Beast Samnite
  575, // Gladiator Beast Secutor
  576, // Gladiator Beast Spartacus
  577, // Gladiator Beast Tamer Editor
  578, // Gladiator Beast Torax
  579, // Gladiator Beast Tygerius
  580, // Gladiator Beast Vespasius
  581, // Gladiator Beast War Chariot
  582, // Gladiator Beast's Battle Archfiend Shield
  583, // Gladiator Beast's Battle Gladius
  584, // Gladiator Beast's Battle Halberd
  585, // Gladiator Beast's Battle Manica
  586, // Gladiator Beast's Medusa Shield
  587, // Gladiator Beast's Valor
  588, // Gladiator Naumachia
  589, // Gladiator Proving Ground
  590, // Glorious Illusion
  591, // Goblin King
  592, // Goblin Thief
  593, // Goddess Bow
  594, // Golden Homunculus
  595, // Gorz the Emissary of Darkness
  596, // Goyo Guardian
  597, // Graceful Charity
  598, // Graceful Dice
  599, // Gragonith, Lightsworn Dragon
  600, // Granadora
  601, // Grand Convergence
  602, // Granmarg the Rock Monarch
  603, // Gravekeeper's Ambusher
  604, // Gravekeeper's Cannonholder
  605, // Gravekeeper's Servant
  606, // Gravity Bind
  607, // Great Maju Garzett
  608, // Great Poseidon Beetle
  609, // Green Baboon, Defender of the Forest
  610, // Green Gadget
  611, // Gren Maju Da Eiza
  612, // Grinder Golem
  613, // Ground Collapse
  614, // Guardian Angel Joan
  615, // Guardian Dreadscythe
  616, // Guardian Eatos
  617, // Guardian Treasure
  618, // Gungnir, Dragon of the Ice Barrier
  619, // Gyaku-Gire Panda
  620, // H - Heated Heart
  621, // Hamon, Lord of Striking Thunder
  622, // Harpie Channeler
  623, // Harpie Conductor
  624, // Harpie Dancer
  625, // Harpie Harpist
  626, // Harpie Lady 1
  627, // Harpie Lady 2
  628, // Harpie Lady 3
  629, // Harpie Lady Elegance
  630, // Harpie Lady Phoenix Formation
  631, // Harpie Oracle
  632, // Harpie Perfumer
  633, // Harpie Queen
  634, // Harpie's Feather Rest
  635, // Harpie's Feather Storm
  636, // Harpie's Pet Baby Dragon
  637, // Harpie's Pet Phantasmal Dragon
  638, // Harpies' Hunting Ground
  639, // Hayabusa Knight
  640, // Hecatrice
  641, // Helshaddoll Hollow
  642, // Herald of Creation
  643, // Herald of Perfection
  644, // Herald of the Arc Light
  645, // Herald of Ultimateness
  646, // Herald of Ultimateness
  647, // Hero Flash!!
  648, // Hero Kid
  649, // Holactie the Creator of Light
  650, // Honest
  651, // Horus the Black Flame Dragon LV4
  652, // Horus the Black Flame Dragon LV6
  653, // Horus the Black Flame Dragon LV8
  654, // Humid Winds
  655, // Hunting Instinct
  656, // Hyper Hammerhead
  657, // Hysteric Party
  658, // Hysteric Sign
  659, // Icarus Attack
  660, // Illusion Magic
  661, // Illusion of Chaos
  662, // Imperial Order
  663, // Insect Imitation
  664, // Instant Contact
  665, // Instant Fusion
  666, // Instant Neo Space
  667, // Invader of the Throne
  668, // Iofiel
  669, // Ipiria
  670, // Jain, Lightsworn Paladin
  671, // Jain, Twilightsworn General
  672, // Jar of Greed
  673, // Jar Robber
  674, // Jenis, Lightsworn Mender
  675, // Jowgen the Spiritualist
  676, // Jowls of Dark Demise
  677, // Judgment Dragon
  678, // Judgment, the Dragon of Heaven
  679, // Junk Synchron
  680, // Junk Warrior
  681, // Just Deserts
  682, // KA-2 Des Scissors
  683, // Kaibaman
  684, // Kaiser Colosseum
  685, // Kaiser Glider
  686, // Keeper of Dragon Magic
  687, // King Dragun
  688, // King of the Swamp
  689, // King Tiger Wanghu
  690, // Kishido Spirit
  691, // Knight of Pentacles
  692, // Knight's Title
  693, // Kuraz the Light Monarch
  694, // Kuribandit
  695, // Last Turn
  696, // Legend of Heart
  697, // Legendary Flame Lord
  698, // Legendary Knight Critias
  699, // Legendary Knight Hermos
  700, // Legendary Knight Timaeus
  701, // Legendary Maju Garzett
  702, // Lekunga
  703, // Lesser Fiend
  704, // Lev Shaddoll Fusion
  705, // Level Limit - Area A
  706, // Level Limit Area B
  707, // Level Tuning
  708, // Levia Dragon Daedalus
  709, // Leviair the Sea Dragon
  710, // Life Stream Dragon
  711, // Light and Darkness Dragon
  712, // Light Barrier
  713, // Light End Dragon
  714, // Light Force
  715, // Light of Destruction
  716, // Light Spiral
  717, // Lightning Warrior
  718, // Lightserpent
  719, // Lightsworn Aegis
  720, // Lightsworn Barrier
  721, // Lightsworn Dragonling
  722, // Lightsworn Judgment
  723, // Lightsworn Sabre
  724, // Lightsworn Sanctuary
  725, // Limiter Removal
  726, // Lonefire Blossom
  727, // Lord of the Red
  728, // Lumina, Lightsworn Summoner
  729, // Lumina, Twilightsworn Shaman
  730, // Luster Dragon
  731, // Lyla, Lightsworn Sorceress
  732, // Lyla, Twilightsworn Enchantress
  733, // Lyrilusc - Independent Nightingale
  734, // Ma'at
  735, // Macro Cosmos
  736, // Mad Sword Beast
  737, // Mage Power
  738, // Magic Cylinder
  739, // Magic Jammer
  740, // Magical Arm Shield
  741, // Magical Dimension
  742, // Magical Hats
  743, // Magical Marionette
  744, // Magical Merchant
  745, // Magical Plant Mandragola
  746, // Magical Scientist
  747, // Magical Stone Excavation
  748, // Magician Navigation
  749, // Magician of Dark Illusion
  750, // Magician's Circle
  751, // Magician's Robe
  752, // Magician's Rod
  753, // Magician's Valkyria
  754, // Magicians' Combination
  755, // Magicians' Souls
  756, // Magna Drago
  757, // Majestic Mech - Goryu
  758, // Maju Garzett
  759, // Man-Thro-Thro
  760, // Manju of the Ten Thousand Hands
  761, // Marauding Captain
  762, // March of the Dark Brigade
  763, // Marshmallon
  764, // Maryokutai
  765, // Mask of Dispel
  766, // Mask of Restrict
  767, // Mask of the Accursed
  768, // Master of Chaos
  769, // Master Peace, the True Dracoslaying King
  770, // Mataza the Zapper
  771, // Mausoleum of the Emperor
  772, // Mazera DeVille
  773, // Mefist The Infernal General
  774, // Mermaid Knight
  775, // Metamorphosis
  776, // Metaverse
  777, // Meteor of Destruction
  778, // Meteorain
  779, // Michael, the Arch-Lightsworn
  780, // Mighty Angel Virch
  781, // Millennium-Eyes Restrict
  782, // Minerva, Lightsworn Maiden
  783, // Minerva, the Athenian Lightsworn
  784, // Minerva, the Exalted Lightsworn
  785, // Miracle Contact
  786, // Miracle Fusion
  787, // Mirage Dragon
  788, // Mirage of Nightmare
  789, // Mirror Force
  790, // Mirror Force Dragon
  791, // Mirror Wall
  792, // Mobius the Frost Monarch
  793, // Moister Creature
  794, // Molten Zombie
  795, // Molting Escape
  796, // Monster Gate
  797, // Monster Recovery
  798, // Montage Dragon
  799, // Moon Token
  800, // Morale Boost
  801, // Morphtronic Accelerator
  802, // Morphtronic Bind
  803, // Morphtronic Boarden
  804, // Morphtronic Boomboxen
  805, // Morphtronic Cameran
  806, // Morphtronic Celfon
  807, // Morphtronic Clocken
  808, // Morphtronic Converter
  809, // Morphtronic Cord
  810, // Morphtronic Datatron
  811, // Morphtronic Earfon
  812, // Morphtronic Engine
  813, // Morphtronic Forcefield
  814, // Morphtronic Impact Return
  815, // Morphtronic Lantron
  816, // Morphtronic Magnen
  817, // Morphtronic Magnen Bar
  818, // Morphtronic Map
  819, // Morphtronic Mix-up
  820, // Morphtronic Monitron
  821, // Morphtronic Radion
  822, // Morphtronic Remoten
  823, // Morphtronic Repair Unit
  824, // Morphtronic Rusty Engine
  825, // Morphtronic Scannen
  826, // Morphtronic Scopen
  827, // Morphtronic Slingen
  828, // Morphtronic Smartfon
  829, // Morphtronic Staplen
  830, // Morphtronic Telefon
  831, // Morphtronic Vacuumen
  832, // Morphtronic Videon
  833, // Mucus Yolk
  834, // Mystic Mine
  835, // Mystical Shine Ball
  836, // Mystical Space Typhoon
  837, // Mystik Wok
  838, // Naelshaddoll Ariel
  839, // Naturia Beast
  840, // Necrovalley
  841, // Needle Burrower
  842, // Needle Wall
  843, // Negate Attack
  844, // Negative Energy
  845, // Nehshaddoll Genius
  846, // Neo Blue-Eyes Ultimate Dragon
  847, // Neo Space
  848, // Neo Space Connector
  849, // Neo-Spacian Air Hummingbird
  850, // Neo-Spacian Aqua Dolphin
  851, // Neo-Spacian Dark Panther
  852, // Neo-Spacian Flare Scarab
  853, // Neo-Spacian Glow Moss
  854, // Neo-Spacian Grand Mole
  855, // Neo-Spacian Marine Dolphin
  856, // Neo-Spacian Twinkle Moss
  857, // Neos Wiseman
  858, // Nephe Shaddoll Fusion
  859, // Neutron Blast
  860, // NEX
  861, // NEXT
  862, // Nibiru, the Primal Being
  863, // Nightmare Horse
  864, // Nightmare Wheel
  865, // Nitro Warrior
  866, // Numinous Healer
  867, // O - Oversoul
  868, // Obnoxious Celtic Guardian
  869, // Offering to the Snake Deity
  870, // Ojama King
  871, // Ojama Trio
  872, // Orichalcos Shunoros
  873, // Oshaleon
  874, // Over Destiny
  875, // Overflowing Treasure
  876, // Overload Fusion
  877, // Painful Choice
  878, // Paladin Of White Dragon
  879, // Pandemonium
  880, // Parallel World Fusion
  881, // Pentacle of Ace
  882, // Peten The Dark Clown
  883, // Photon Generator Unit
  884, // Piranha Army
  885, // Poison of the Old Man
  886, // Polymerization
  887, // Possessed Dark Soul
  888, // Power Bond
  889, // Power Filter
  890, // Power Tool Braver Dragon
  891, // Power Tool Dragon
  892, // Precious Cards From Beyond
  893, // Predaplant Verte Anaconda
  894, // Premature Burial
  895, // Prophecy
  896, // Protector of the Sanctuary
  897, // Proto-Cyber Dragon
  898, // Pseudo Space
  899, // Punishment Dragon
  900, // Pyramid of Light
  901, // Qadshaddoll Keios
  902, // Quintet Magician
  903, // R - Righteous Justice
  904, // Raiden, Hand of the Lightsworn
  905, // Raigeki Break
  906, // Rain of Mercy
  907, // Rainbow Dark Dragon
  908, // Rare Metal Dragon
  909, // Raregold Armor
  910, // Raviel, Lord of Phantasms
  911, // Realm of Light
  912, // Reaper on the Nightmare
  913, // Reaper Scythe - Dreadscythe
  914, // Reckless Greed
  915, // Red Dragon Archfiend
  916, // Red Gadget
  917, // Red Reboot
  918, // Red-Eyes Black Dragon Sword
  919, // Red-Eyes Dark Dragoon
  920, // Red-Eyes Darkness Metal Dragon
  921, // Red-Eyes Transmigration
  922, // Reeshaddoll Wendi
  923, // Reeshaddoll Wendikurhu
  924, // Relay Soul
  925, // Reload
  926, // Reptilianne Echidna
  927, // Reptilianne Gardna
  928, // Reptilianne Gorgon
  929, // Reptilianne Hydra
  930, // Reptilianne Lamia
  931, // Reptilianne Medusa
  932, // Reptilianne Naga
  933, // Reptilianne Poison
  934, // Reptilianne Rage
  935, // Reptilianne Scylla
  936, // Reptilianne Servant
  937, // Reptilianne Spawn
  938, // Reptilianne Vaskii
  939, // Reptilianne Viper
  940, // Rescue Cat
  941, // Rescue Rabbit
  942, // Return of the Dragon Lords
  943, // Reversal of Fate
  944, // Reverse of Reverse
  945, // Ring of Destruction
  946, // Rinyan, Lightsworn Rogue
  947, // Riryoku
  948, // Rise of the Snake Deity
  949, // Rivalry of Warlords
  950, // Road Synchron
  951, // Road Warrior
  952, // Robbin' Goblin
  953, // Robbin' Zombie
  954, // Rocket Hermos Cannon
  955, // Rope of Life
  956, // Royal Decree
  957, // Royal Knight
  958, // Royal Magical Library
  959, // Ryko, Lightsworn Hunter
  960, // Ryko, Twilightsworn Fighter
  961, // Ryu-Kishin Clown
  962, // Sage's Stone
  963, // Sasuke Samurai
  964, // Sasuke Samurai #2
  965, // Sasuke Samurai #3
  966, // Scapegoat
  967, // Scrap-Iron Scarecrow
  968, // Seal of Orichalcos
  969, // Second Coin Toss
  970, // Secret Barrel
  971, // Secret Village of the Spellcasters
  972, // Secrets of Dark Magic
  973, // Self-Destruct Button
  974, // Seraphim Blaster
  975, // Serpent Suppression
  976, // Servant of Catabolism
  977, // Seven Tools of the Bandit
  978, // Shaddoll Beast
  979, // Shaddoll Core
  980, // Shaddoll Dragon
  981, // Shaddoll Falco
  982, // Shaddoll Fusion
  983, // Shaddoll Hedgehog
  984, // Shaddoll Hound
  985, // Shaddoll Schism
  986, // Shaddoll Squamata
  987, // Share the Pain
  988, // Shatiel
  989, // Shield And Sword
  990, // Shire, Lightsworn Spirit
  991, // Silent Magician LV4
  992, // Silent Magician LV8
  993, // Silver's Cry
  994, // Simorgh, Bird of Ancestry
  995, // Sixth Sense
  996, // Skill Drain
  997, // Skilled Dark Magician
  998, // Skilled White Magician
  999, // Skull Invitation
  1000, // Skyscraper
  1001, // Skyscraper 2 - Hero City
  1002, // Snake Deity's Command
  1003, // Snake Rain
  1004, // Snake Whistle
  1005, // Solar Flare Dragon
  1006, // Solar Ray
  1007, // Solar Recharge
  1008, // Solemn Judgment
  1009, // Solemn Wishes
  1010, // Sorcerer of Dark Magic
  1011, // Soul Exchange
  1012, // Soul Servant
  1013, // Soul Taker
  1014, // Spark Blaster
  1015, // Spear Dragon
  1016, // Spell Absorption
  1017, // Spell Canceller
  1018, // Spell Chronicle
  1019, // Spell Economics
  1020, // Spell Gear
  1021, // Spell Striker
  1022, // Sphinx Teleia
  1023, // Spirit Caller
  1024, // Spirit of the Breeze
  1025, // Spirit of the Pot of Greed
  1026, // Spirit Reaper
  1027, // Spirit Ryu
  1028, // St Joan
  1029, // Stardust Dragon
  1030, // Statue of the Wicked
  1031, // Staunch Defender
  1032, // Stealth Bird
  1033, // Stray Lambs
  1034, // Stronghold the Moving Fortress
  1035, // Suit of Sword X
  1036, // Summoner Monk
  1037, // Summoner of Illusions
  1038, // Super Polymerization
  1039, // Supreme King's Castle
  1040, // Swift Gaia The Fierce Knight
  1041, // T.G. Hyper Librarian
  1042, // Tatsunoko
  1043, // Terraforming
  1044, // Terrorking Salmon
  1045, // Test Bear
  1046, // Test Panther
  1047, // Test Tiger
  1048, // Tethys, Goddess of Light
  1049, // That Grass Looks Greener
  1050, // The A. Forces
  1051, // The Agent Of Creation - Venus
  1052, // The Agent of Force - Mars
  1053, // The Agent of Judgment - Saturn
  1054, // The Agent of Wisdom - Mercury
  1055, // The Big Saturn
  1056, // The Blazing Mars
  1057, // The Claw of Hermos
  1058, // The Creator
  1059, // The Creator Incarnate
  1060, // The Dark Door
  1061, // The Dark Magicians
  1062, // The Despair Uranus
  1063, // The Eye of Timaeus
  1064, // The Fang of Critias
  1065, // The Flute of Summoning Dragon
  1066, // The Forceful Sentry
  1067, // The Gaze of Timaeus
  1068, // The Grand Jupiter
  1069, // The Law of the Normal
  1070, // The Legendary Exodia Incarnate
  1071, // The Melody of Awakening Dragon
  1072, // The Sanctuary in the Sky
  1073, // The Shallow Grave
  1074, // The Splendid Venus
  1075, // The Suppression Pluto
  1076, // The Supremacy Sun
  1077, // The Thing in the Crater
  1078, // The Tricky
  1079, // The Tripper Mercury
  1080, // The Tyrant Neptune
  1081, // The Unstoppable Exodia Incarnate
  1082, // The White Stone of Ancients
  1083, // The White Stone of Legend
  1084, // The Wicked Avatar
  1085, // The Wicked Dreadroot
  1086, // The Wicked Eraser
  1087, // Theban Nightmare
  1088, // Theinen the Great Sphinx
  1089, // Thestalos the Firestorm Monarch
  1090, // Thousand Energy
  1091, // Thousand Knives
  1092, // Thumbs Down
  1093, // Thunder Crash
  1094, // Thunder Dragon Colossus
  1095, // Thunder Dragon Titan
  1096, // Timaeus the Knight of Destiny
  1097, // Timaeus the United Dragon
  1098, // Timaeus the United Magical Dragon
  1099, // Time Magic Hammer
  1100, // Time Seal
  1101, // Time Thief Redoer
  1102, // Tiny Angel
  1103, // Tohushaddoll Grysta
  1104, // Toll
  1105, // Toon World
  1106, // Tornado Bird
  1107, // Tornado Wall
  1108, // Torpedo Fish
  1109, // Tour of Doom
  1110, // Trade-In
  1111, // Trap Dustshoot
  1112, // Trap Trick
  1113, // Triangle Ecstasy Spark
  1114, // Triangle Power
  1115, // Tribute Doll
  1116, // Trishula, Dragon of the Ice Barrier
  1117, // Trojan Gladiator Beast
  1118, // Tuningware
  1119, // Turbo Booster
  1120, // Turbo Cannon
  1121, // Turbo Rocket
  1122, // Turbo Synchron
  1123, // Twilight Cloth
  1124, // Twilight Eraser
  1125, // Twilight Twin Dragons
  1126, // Twin Swords of Flashing Light - Tryce
  1127, // Tyranno Infinity
  1128, // Tyrant Burst Dragon
  1129, // Tyrant Dragon
  1130, // Tyrant Wing
  1131, // Ultimate Ancient Gear Golem
  1132, // Ultimate Conductor Tyranno
  1133, // Ultimate Obedient Fiend
  1134, // Ultimate Offering
  1135, // Ultimate Tyranno
  1136, // Ultra Polymerization
  1137, // United We Stand
  1138, // Unstable Evolution
  1139, // Upstart Goblin
  1140, // Urgent Tuning
  1141, // Uria, Lord of Searing Flames
  1142, // Valhalla, Hall of the Fallen
  1143, // Vampire Baby
  1144, // Vanquishing Light
  1145, // Vengeful Bog Spirit
  1146, // Vennominaga the Deity of Poisonous Snakes
  1147, // Vennominon the King of Poisonous Snakes
  1148, // Venom Boa
  1149, // Venom Burn
  1150, // Venom Cobra
  1151, // Venom Serpent
  1152, // Venom Shot
  1153, // Venom Snake
  1154, // Venom Swamp
  1155, // Viper's Rebirth
  1156, // Vision Fusion
  1157, // Vision HERO Adoration
  1158, // Vision HERO Faris
  1159, // Vision HERO Gravito
  1160, // Vision HERO Increase
  1161, // Vision HERO Minimum Ray
  1162, // Vision HERO Multiply Guy
  1163, // Vision HERO Poisoner
  1164, // Vision HERO Trinity
  1165, // Vision HERO Vyon
  1166, // Vision HERO Witch Raider
  1167, // Vision Release
  1168, // Wall of Revealing Light
  1169, // Warrior of Atlantis
  1170, // Warrior of Zera
  1171, // Watapon
  1172, // Water Hazard
  1173, // Wave Motion Cannon
  1174, // Weapon Change
  1175, // Weather Report
  1176, // Weiss, Lightsworn Archfiend
  1177, // Wetlands
  1178, // White Dragon Ritual
  1179, // White Magician Pikeru
  1180, // Wild Nature's Release
  1181, // World Suppression
  1182, // Wroughtweiler
  1183, // Wulf, Lightsworn Beast
  1184, // X-Saber Airbellum
  1185, // Yamorimori
  1186, // Yata-Garasu
  1187, // Yellow Gadget
  1188, // Yowie
  1189, // Yubel
  1190, // Yubel - Terror Incarnate
  1191, // Yubel - The Ultimate Nightmare
  1192, // Zaborg the Thunder Monarch
  1193, // Zeriel
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
  if (cardId == 0x03F8)
    return (u8 *)sElementalHeroMudballmanSortName;
  if (cardId == 0x03F9)
    return (u8 *)sHarpieLady1SortName;
  if (cardId == 0x03FA)
    return (u8 *)sHarpieLady2SortName;
  if (cardId == 0x03FB)
    return (u8 *)sHarpieLady3SortName;
  if (cardId == 0x03FC)
    return (u8 *)sSpellEconomicsSortName;
  if (cardId == 0x03FD)
    return (u8 *)sTheUnstoppableExodiaIncarnateSortName;
  if (cardId == 0x03FE)
    return (u8 *)sTheSanctuaryInTheSkySortName;
  if (cardId == 0x03FF)
    return (u8 *)sMirrorForceSortName;
  if (cardId == 0x0400)
    return (u8 *)sLevelLimitAreaASortName;
  if (cardId == 0x0401)
    return (u8 *)sHarpiesPetBabyDragonSortName;
  if (cardId == 0x0402)
    return (u8 *)sBlueEyesChaosDragonSortName;
  if (cardId == 0x0403)
    return (u8 *)sBlowbackDragonSortName;
  if (cardId == 0x0404)
    return (u8 *)sChaosCommandMagicianSortName;
  if (cardId == 0x0405)
    return (u8 *)sBookOfLifeSortName;
  if (cardId == 0x0406)
    return (u8 *)sBookOfTaiyouSortName;
  if (cardId == 0x0407)
    return (u8 *)sDeFusionSortName;
  if (cardId == 0x0408)
    return (u8 *)sDiffusionWaveMotionSortName;
  if (cardId == 0x0409)
    return (u8 *)sAutonomousActionUnitSortName;
  if (cardId == 0x040A)
    return (u8 *)sElementalHeroRampartBlasterSortName;
  if (cardId == 0x040B)
    return (u8 *)sALegendaryOceanSortName;
  if (cardId == 0x040C)
    return (u8 *)sDarkMagicianOfChaosSortName;
  if (cardId == 0x040D)
    return (u8 *)sDedicationThroughLightAndDarknessSortName;
  if (cardId == 0x040E)
    return (u8 *)sElementalHeroSteamHealerSortName;
  if (cardId == 0x040F)
    return (u8 *)sElementalHeroPhoenixEnforcerSortName;
  if (cardId == 0x0410)
    return (u8 *)sElementalHeroShiningPhoenixEnforcerSortName;
  if (cardId == 0x0411)
    return (u8 *)sElementalHeroFlameWingmanSortName;
  if (cardId == 0x0412)
    return (u8 *)sElementalHeroShiningFlareWingmanSortName;
  if (cardId == 0x0413)
    return (u8 *)sElementalHeroTempestSortName;
  if (cardId == 0x0414)
    return (u8 *)sElementalHeroWildedgeSortName;
  if (cardId == 0x0415)
    return (u8 *)sElementalHeroThunderGiantSortName;
  if (cardId == 0x0416)
    return (u8 *)sElementalHeroMarinerSortName;
  if (cardId == 0x0417)
    return (u8 *)sElementalHeroElectrumSortName;
  if (cardId == 0x0418)
    return (u8 *)sElementalHeroNecroshadeSortName;
  if (cardId == 0x0419)
    return (u8 *)sMiracleFusionSortName;
  if (cardId == 0x041A)
    return (u8 *)sTheAgentOfForceMarsSortName;
  if (cardId == 0x041B)
    return (u8 *)sChaosEmperorDragonEnvoyOfTheEndSortName;
  if (cardId == 0x041C)
    return (u8 *)sBlackLusterSoldierEnvoyOfTheBeginningSortName;
  if (cardId == 0x041D)
    return (u8 *)sElementalHeroNeosSortName;
  if (cardId == 0x041E)
    return (u8 *)sElementalHeroWoodsmanSortName;
  if (cardId == 0x041F)
    return (u8 *)sElementalHeroOceanSortName;
  if (cardId == 0x0420)
    return (u8 *)sElementalHeroHeatSortName;
  if (cardId == 0x0421)
    return (u8 *)sElementalHeroLadyHeatSortName;
  if (cardId == 0x0422)
    return (u8 *)sElementalHeroNeosAliusSortName;
  if (cardId == 0x0423)
    return (u8 *)sElementalHeroGreatTornadoSortName;
  if (cardId == 0x0424)
    return (u8 *)sElementalHeroTerraFirmaSortName;
  if (cardId == 0x0425)
    return (u8 *)sElementalHeroKnospeSortName;
  if (cardId == 0x0426)
    return (u8 *)sElementalHeroPoisonRoseSortName;
  if (cardId == 0x0427)
    return (u8 *)sElementalHeroAbsoluteZeroSortName;
  if (cardId == 0x0428)
    return (u8 *)sElementalHeroWildWingmanSortName;
  if (cardId == 0x0429)
    return (u8 *)sElementalHeroVolticSortName;
  if (cardId == 0x042A)
    return (u8 *)sElementalHeroFlashSortName;
  if (cardId == 0x042B)
    return (u8 *)sElementalHeroGaiaSortName;
  if (cardId == 0x042C)
    return (u8 *)sElementalHeroEscuridaoSortName;
  if (cardId == 0x042D)
    return (u8 *)sElementalHeroTheShiningSortName;
  if (cardId == 0x042E)
    return (u8 *)sElementalHeroInfernoSortName;
  if (cardId == 0x042F)
    return (u8 *)sElementalHeroNecroidShamanSortName;
  if (cardId == 0x0430)
    return (u8 *)sElementalHeroPlasmaViceSortName;
  if (cardId == 0x0431)
    return (u8 *)sFusionRecoverySortName;
  if (cardId == 0x0432)
    return (u8 *)sSkyscraperSortName;
  if (cardId == 0x0433)
    return (u8 *)sHHeatedHeartSortName;
  if (cardId == 0x0434)
    return (u8 *)sEEmergencyCallSortName;
  if (cardId == 0x0435)
    return (u8 *)sRRighteousJusticeSortName;
  if (cardId == 0x0436)
    return (u8 *)sOOversoulSortName;
  if (cardId == 0x0437)
    return (u8 *)sFutureFusionSortName;
  if (cardId == 0x0438)
    return (u8 *)sElementalHeroCoreSortName;
  if (cardId == 0x0439)
    return (u8 *)sElementalHeroSunriseSortName;
  if (cardId == 0x043A)
    return (u8 *)sElementalHeroCaptainGoldSortName;
  if (cardId == 0x043B)
    return (u8 *)sElementalHeroIceEdgeSortName;
  if (cardId == 0x043C)
    return (u8 *)sElementalHeroBlazemanSortName;
  if (cardId == 0x043D)
    return (u8 *)sElementalHeroStratosSortName;
  if (cardId == 0x043E)
    return (u8 *)sChimeratechOverdragonSortName;
  if (cardId == 0x043F)
    return (u8 *)sCyberneticFusionSupportSortName;
  if (cardId == 0x0440)
    return (u8 *)sOverloadFusionSortName;
  if (cardId == 0x0441)
    return (u8 *)sPowerBondSortName;
  if (cardId == 0x0442)
    return (u8 *)sFusionSageSortName;
  if (cardId == 0x0443)
    return (u8 *)sLyriluscIndependentNightingaleSortName;
  if (cardId == 0x0444)
    return (u8 *)sTheTyrantNeptuneSortName;
  if (cardId == 0x0445)
    return (u8 *)sTheSplendidVenusSortName;
  if (cardId == 0x0446)
    return (u8 *)sTheBigSaturnSortName;
  if (cardId == 0x0447)
    return (u8 *)sTheTripperMercurySortName;
  if (cardId == 0x0448)
    return (u8 *)sTheGrandJupiterSortName;
  if (cardId == 0x0449)
    return (u8 *)sTheDespairUranusSortName;
  if (cardId == 0x044A)
    return (u8 *)sTheBlazingMarsSortName;
  if (cardId == 0x044B)
    return (u8 *)sTheSuppressionPlutoSortName;
  if (cardId == 0x044C)
    return (u8 *)sTheSupremacySunSortName;
  if (cardId == 0x044D)
    return (u8 *)sMightyAngelVirchSortName;
  if (cardId == 0x044E)
    return (u8 *)sTinyAngelSortName;
  if (cardId == 0x044F)
    return (u8 *)sZerielSortName;
  if (cardId == 0x0450)
    return (u8 *)sShatielSortName;
  if (cardId == 0x0451)
    return (u8 *)sSeraphimBlasterSortName;
  if (cardId == 0x0452)
    return (u8 *)sIofielSortName;
  if (cardId == 0x0453)
    return (u8 *)sArchlordKristyaSortName;
  if (cardId == 0x0454)
    return (u8 *)sTethysGoddessOfLightSortName;
  if (cardId == 0x0455)
    return (u8 *)sAthenaSortName;
  if (cardId == 0x0456)
    return (u8 *)sValhallaHallOfTheFallenSortName;
  if (cardId == 0x0457)
    return (u8 *)sAngelsTearSortName;
  if (cardId == 0x0458)
    return (u8 *)sDivineSanctuarySortName;
  if (cardId == 0x0459)
    return (u8 *)sCourtOfJusticeSortName;
  if (cardId == 0x045A)
    return (u8 *)sHecatriceSortName;
  if (cardId == 0x045B)
    return (u8 *)sPrematureBurialSortName;
  if (cardId == 0x045C)
    return (u8 *)sYubelSortName;
  if (cardId == 0x045D)
    return (u8 *)sYubelTerrorIncarnateSortName;
  if (cardId == 0x045E)
    return (u8 *)sYubelTheUltimateNightmareSortName;
  if (cardId == 0x045F)
    return (u8 *)sTheTrickySortName;
  if (cardId == 0x0460)
    return (u8 *)sTheWickedDreadrootSortName;
  if (cardId == 0x0461)
    return (u8 *)sTheWickedEraserSortName;
  if (cardId == 0x0462)
    return (u8 *)sTheWickedAvatarSortName;
  if (cardId == 0x0463)
    return (u8 *)sTributeDollSortName;
  if (cardId == 0x0464)
    return (u8 *)sTradeInSortName;
  if (cardId == 0x0465)
    return (u8 *)sCyberBarrierDragonSortName;
  if (cardId == 0x0466)
    return (u8 *)sCyberLaserDragonSortName;
  if (cardId == 0x0467)
    return (u8 *)sDarkEndDragonSortName;
  if (cardId == 0x0468)
    return (u8 *)sLightEndDragonSortName;
  if (cardId == 0x0469)
    return (u8 *)sDarkArmedDragonSortName;
  if (cardId == 0x046A)
    return (u8 *)sAHeroEmergesSortName;
  if (cardId == 0x046B)
    return (u8 *)sAHeroLivesSortName;
  if (cardId == 0x046C)
    return (u8 *)sAWingbeatOfGiantDragonSortName;
  if (cardId == 0x046D)
    return (u8 *)sAllureOfDarknessSortName;
  if (cardId == 0x046E)
    return (u8 *)sAmuletDragonSortName;
  if (cardId == 0x046F)
    return (u8 *)sAndroSphinxSortName;
  if (cardId == 0x0470)
    return (u8 *)sAntiSpellFragranceSortName;
  if (cardId == 0x0471)
    return (u8 *)sAppropriateSortName;
  if (cardId == 0x0472)
    return (u8 *)sApprenticeIllusionMagicianSortName;
  if (cardId == 0x0473)
    return (u8 *)sApparationSortName;
  if (cardId == 0x0474)
    return (u8 *)sAttackGuidanceArmorSortName;
  if (cardId == 0x0475)
    return (u8 *)sAttackReflectorUnitSortName;
  if (cardId == 0x0476)
    return (u8 *)sBackupSquadSortName;
  if (cardId == 0x0477)
    return (u8 *)sArmageddonKnightSortName;
  if (cardId == 0x0478)
    return (u8 *)sArmedDragonLv3SortName;
  if (cardId == 0x0479)
    return (u8 *)sArmedDragonLv5SortName;
  if (cardId == 0x047A)
    return (u8 *)sArmedDragonLv7SortName;
  if (cardId == 0x047B)
    return (u8 *)sArmedDragonLv10SortName;
  if (cardId == 0x047C)
    return (u8 *)sAttackAndReceiveSortName;
  if (cardId == 0x047D)
    return (u8 *)sBackfireSortName;
  if (cardId == 0x047E)
    return (u8 *)sHamonLordOfStrikingThunderSortName;
  if (cardId == 0x047F)
    return (u8 *)sUriaLordOfSearingFlamesSortName;
  if (cardId == 0x0480)
    return (u8 *)sRavielLordOfPhantasmsSortName;
  if (cardId == 0x0481)
    return (u8 *)sBerserkerSoulSortName;
  if (cardId == 0x0482)
    return (u8 *)sBirdfaceSortName;
  if (cardId == 0x0483)
    return (u8 *)sBlueEyesAlternativeUltimateDragonSortName;
  if (cardId == 0x0484)
    return (u8 *)sBreakTheDestinySortName;
  if (cardId == 0x0485)
    return (u8 *)sBubbleBlasterSortName;
  if (cardId == 0x0486)
    return (u8 *)sBurdenOfTheMightySortName;
  if (cardId == 0x0487)
    return (u8 *)sCallOfTheMummySortName;
  if (cardId == 0x0488)
    return (u8 *)sCannonballSpearShellfishSortName;
  if (cardId == 0x0489)
    return (u8 *)sCelestialSwordEatosSortName;
  if (cardId == 0x048A)
    return (u8 *)sChaosFormSortName;
  if (cardId == 0x048B)
    return (u8 *)sChickenGameSortName;
  if (cardId == 0x048C)
    return (u8 *)sChimeratechFortressDragonSortName;
  if (cardId == 0x048D)
    return (u8 *)sChimeratechMegafleetDragonSortName;
  if (cardId == 0x048E)
    return (u8 *)sChimeratechRampageDragonSortName;
  if (cardId == 0x048F)
    return (u8 *)sClockTowerPrisonSortName;
  if (cardId == 0x0490)
    return (u8 *)sColdWaveSortName;
  if (cardId == 0x0491)
    return (u8 *)sContinuousDestructionPunchSortName;
  if (cardId == 0x0492)
    return (u8 *)sCyberEltaninSortName;
  if (cardId == 0x0493)
    return (u8 *)sCyberKirinSortName;
  if (cardId == 0x0494)
    return (u8 *)sCyberPhoenixSortName;
  if (cardId == 0x0495)
    return (u8 *)sCyberValleySortName;
  if (cardId == 0x0496)
    return (u8 *)sCyberneticZoneSortName;
  if (cardId == 0x0497)
    return (u8 *)sDTacticsSortName;
  if (cardId == 0x0498)
    return (u8 *)sDTimeSortName;
  if (cardId == 0x0499)
    return (u8 *)sDamagePolarizerSortName;
  if (cardId == 0x049A)
    return (u8 *)sDBurstSortName;
  if (cardId == 0x049B)
    return (u8 *)sDForceSortName;
  if (cardId == 0x049C)
    return (u8 *)sDarkBladeTheDragonKnightSortName;
  if (cardId == 0x049D)
    return (u8 *)sDarkGrepherSortName;
  if (cardId == 0x049E)
    return (u8 *)sDarkMagicianGirlTheDragonKnightSortName;
  if (cardId == 0x049F)
    return (u8 *)sDarklordNurseReficuleSortName;
  if (cardId == 0x04A0)
    return (u8 *)sDarknessNeosphereSortName;
  if (cardId == 0x04A1)
    return (u8 *)sDarkCityAtMidnightSortName;
  if (cardId == 0x04A2)
    return (u8 *)sDarkMagicianTheDragonKnightSortName;
  if (cardId == 0x04A3)
    return (u8 *)sDecoyDragonSortName;
  if (cardId == 0x04A4)
    return (u8 *)sDesCounterblowSortName;
  if (cardId == 0x04A5)
    return (u8 *)sDespairFromTheDarkSortName;
  if (cardId == 0x04A6)
    return (u8 *)sDestinyDrawSortName;
  if (cardId == 0x04A7)
    return (u8 *)sDestinyEndDragoonSortName;
  if (cardId == 0x04A8)
    return (u8 *)sDestinyHeroBladeMasterSortName;
  if (cardId == 0x04A9)
    return (u8 *)sDestinyHeroCaptainTenaciousSortName;
  if (cardId == 0x04AA)
    return (u8 *)sDestinyHeroCelestialSortName;
  if (cardId == 0x04AB)
    return (u8 *)sDestinyHeroDangerousSortName;
  if (cardId == 0x04AC)
    return (u8 *)sDestinyHeroDarkAngelSortName;
  if (cardId == 0x04AD)
    return (u8 *)sDestinyHeroDasherSortName;
  if (cardId == 0x04AE)
    return (u8 *)sDestinyHeroDeciderSortName;
  if (cardId == 0x04AF)
    return (u8 *)sDestinyHeroDefenderSortName;
  if (cardId == 0x04B0)
    return (u8 *)sDestinyHeroDenierSortName;
  if (cardId == 0x04B1)
    return (u8 *)sDestinyHeroDestroyerPhoenixEnforcerSortName;
  if (cardId == 0x04B2)
    return (u8 *)sDestinyHeroDiamondDudeSortName;
  if (cardId == 0x04B3)
    return (u8 *)sDestinyHeroDiskCommanderSortName;
  if (cardId == 0x04B4)
    return (u8 *)sDestinyHeroDogmaSortName;
  if (cardId == 0x04B5)
    return (u8 *)sDestinyHeroDominanceSortName;
  if (cardId == 0x04B6)
    return (u8 *)sDestinyHeroDoomLordSortName;
  if (cardId == 0x04B7)
    return (u8 *)sDestinyHeroDoubleDudeSortName;
  if (cardId == 0x04B8)
    return (u8 *)sDestinyHeroDrawhandSortName;
  if (cardId == 0x04B9)
    return (u8 *)sDestinyHeroDreadServantSortName;
  if (cardId == 0x04BA)
    return (u8 *)sDestinyHeroDreadmasterSortName;
  if (cardId == 0x04BB)
    return (u8 *)sDestinyHeroDoomOverlordSortName;
  if (cardId == 0x04BC)
    return (u8 *)sDestinyHeroDreadnoughtMasterSortName;
  if (cardId == 0x04BD)
    return (u8 *)sDestinyHeroDreadnoughtServantSortName;
  if (cardId == 0x04BE)
    return (u8 *)sDestinyHeroDreamerSortName;
  if (cardId == 0x04BF)
    return (u8 *)sDestinyHeroDrilldarkSortName;
  if (cardId == 0x04C0)
    return (u8 *)sDestinyHeroDunkerSortName;
  if (cardId == 0x04C1)
    return (u8 *)sDestinyHeroDynatagSortName;
  if (cardId == 0x04C2)
    return (u8 *)sDestinyHeroDystopiaSortName;
  if (cardId == 0x04C3)
    return (u8 *)sDestinyHeroFearMongerSortName;
  if (cardId == 0x04C4)
    return (u8 *)sDestinyHeroMaliciousSortName;
  if (cardId == 0x04C5)
    return (u8 *)sDestinyHeroPlasmaSortName;
  if (cardId == 0x04C6)
    return (u8 *)sDifferentDimensionCapsuleSortName;
  if (cardId == 0x04C7)
    return (u8 *)sDestinyHeroDusktopiaSortName;
  if (cardId == 0x04C8)
    return (u8 *)sDimensionFusionSortName;
  if (cardId == 0x04C9)
    return (u8 *)sDivineSerpentGehSortName;
  if (cardId == 0x04CA)
    return (u8 *)sDonZaloogSortName;
  if (cardId == 0x04CB)
    return (u8 *)sDoubleSpellSortName;
  if (cardId == 0x04CC)
    return (u8 *)sDragonSRageSortName;
  if (cardId == 0x04CD)
    return (u8 *)sDestinyHeroDestroyDogmaSortName;
  if (cardId == 0x04CE)
    return (u8 *)sDoctorDSortName;
  if (cardId == 0x04CF)
    return (u8 *)sDoomVirusDragonSortName;
  if (cardId == 0x04D0)
    return (u8 *)sDoppelgangerSortName;
  if (cardId == 0x04D1)
    return (u8 *)sEgyptianGodSlimeSortName;
  if (cardId == 0x04D2)
    return (u8 *)sElementalHeroNeosKlugerSortName;
  if (cardId == 0x04D3)
    return (u8 *)sEmergencyProvisionsSortName;
  if (cardId == 0x04D4)
    return (u8 *)sExodiusTheUltimateForbiddenLordSortName;
  if (cardId == 0x04D5)
    return (u8 *)sFatalAbacusSortName;
  if (cardId == 0x04D6)
    return (u8 *)sFelgrandDragonSortName;
  if (cardId == 0x04D7)
    return (u8 *)sFiresOfDoomsdaySortName;
  if (cardId == 0x04D8)
    return (u8 *)sForcedRequisitionSortName;
  if (cardId == 0x04D9)
    return (u8 *)sDrainTimeSortName;
  if (cardId == 0x04DA)
    return (u8 *)sFieldsSanctuarySortName;
  if (cardId == 0x04DB)
    return (u8 *)sFusionDestinySortName;
  if (cardId == 0x04DC)
    return (u8 *)sFusionGateSortName;
  if (cardId == 0x04DD)
    return (u8 *)sGateGuardiansCombinedSortName;
  if (cardId == 0x04DE)
    return (u8 *)sGiftCardSortName;
  if (cardId == 0x04DF)
    return (u8 *)sGoddessBowSortName;
  if (cardId == 0x04E0)
    return (u8 *)sGorzTheEmissaryOfDarknessSortName;
  if (cardId == 0x04E1)
    return (u8 *)sGranmargTheRockMonarchSortName;
  if (cardId == 0x04E2)
    return (u8 *)sGreenGadgetSortName;
  if (cardId == 0x04E3)
    return (u8 *)sGroundCollapseSortName;
  if (cardId == 0x04E4)
    return (u8 *)sGuardianDreadscytheSortName;
  if (cardId == 0x04E5)
    return (u8 *)sHarpieLadyPhoenixFormationSortName;
  if (cardId == 0x04E6)
    return (u8 *)sHeroFlashSortName;
  if (cardId == 0x04E7)
    return (u8 *)sInsectImitationSortName;
  if (cardId == 0x04E8)
    return (u8 *)sInstantFusionSortName;
  if (cardId == 0x04E9)
    return (u8 *)sGuardianEatosSortName;
  if (cardId == 0x04EA)
    return (u8 *)sHeraldOfCreationSortName;
  if (cardId == 0x04EB)
    return (u8 *)sHolactieTheCreatorOfLightSortName;
  if (cardId == 0x04EC)
    return (u8 *)sHorusTheBlackFlameDragonLv8SortName;
  if (cardId == 0x04ED)
    return (u8 *)sHorusTheBlackFlameDragonLv4SortName;
  if (cardId == 0x04EE)
    return (u8 *)sHorusTheBlackFlameDragonLv6SortName;
  if (cardId == 0x04EF)
    return (u8 *)sJowgenTheSpiritualistSortName;
  if (cardId == 0x04F0)
    return (u8 *)sJudgmentDragonSortName;
  if (cardId == 0x04F1)
    return (u8 *)sKingDragunSortName;
  if (cardId == 0x04F2)
    return (u8 *)sKingOfTheSwampSortName;
  if (cardId == 0x04F3)
    return (u8 *)sKurazTheLightMonarchSortName;
  if (cardId == 0x04F4)
    return (u8 *)sKuribanditSortName;
  if (cardId == 0x04F5)
    return (u8 *)sLastTurnSortName;
  if (cardId == 0x04F6)
    return (u8 *)sLegendOfHeartSortName;
  if (cardId == 0x04F7)
    return (u8 *)sLegendaryFlameLordSortName;
  if (cardId == 0x04F8)
    return (u8 *)sKingTigerWanghuSortName;
  if (cardId == 0x04F9)
    return (u8 *)sLegendaryKnightCritiasSortName;
  if (cardId == 0x04FA)
    return (u8 *)sLegendaryKnightHermosSortName;
  if (cardId == 0x04FB)
    return (u8 *)sLegendaryKnightTimaeusSortName;
  if (cardId == 0x04FC)
    return (u8 *)sLekungaSortName;
  if (cardId == 0x04FD)
    return (u8 *)sLightAndDarknessDragonSortName;
  if (cardId == 0x04FE)
    return (u8 *)sLordOfTheRedSortName;
  if (cardId == 0x04FF)
    return (u8 *)sMaAtSortName;
  if (cardId == 0x0500)
    return (u8 *)sMagicalDimensionSortName;
  if (cardId == 0x0501)
    return (u8 *)sMagicalHatsSortName;
  if (cardId == 0x0502)
    return (u8 *)sMagicalPlantMandragolaSortName;
  if (cardId == 0x0503)
    return (u8 *)sMagicalScientistSortName;
  if (cardId == 0x0504)
    return (u8 *)sMagicalStoneExcavationSortName;
  if (cardId == 0x0505)
    return (u8 *)sMajesticMechGoryuSortName;
  if (cardId == 0x0506)
    return (u8 *)sManjuOfTheTenThousandHandsSortName;
  if (cardId == 0x0507)
    return (u8 *)sMarshmallonSortName;
  if (cardId == 0x0508)
    return (u8 *)sMaskOfDispelSortName;
  if (cardId == 0x0509)
    return (u8 *)sMasterPeaceTheTrueDracoslayingKingSortName;
  if (cardId == 0x050A)
    return (u8 *)sMaskOfTheAccursedSortName;
  if (cardId == 0x050B)
    return (u8 *)sMausoleumOfTheEmperorSortName;
  if (cardId == 0x050C)
    return (u8 *)sMazeraDevilleSortName;
  if (cardId == 0x050D)
    return (u8 *)sMetamorphosisSortName;
  if (cardId == 0x050E)
    return (u8 *)sMeteorainSortName;
  if (cardId == 0x050F)
    return (u8 *)sMirageOfNightmareSortName;
  if (cardId == 0x0510)
    return (u8 *)sMirrorForceDragonSortName;
  if (cardId == 0x0511)
    return (u8 *)sMoltenZombieSortName;
  if (cardId == 0x0512)
    return (u8 *)sMonsterGateSortName;
  if (cardId == 0x0513)
    return (u8 *)sMonsterRecoverySortName;
  if (cardId == 0x0514)
    return (u8 *)sMoraleBoostSortName;
  if (cardId == 0x0515)
    return (u8 *)sMucusYolkSortName;
  if (cardId == 0x0516)
    return (u8 *)sMystikWokSortName;
  if (cardId == 0x0517)
    return (u8 *)sNecrovalleySortName;
  if (cardId == 0x0518)
    return (u8 *)sNeedleWallSortName;
  if (cardId == 0x0519)
    return (u8 *)sNeoBlueEyesUltimateDragonSortName;
  if (cardId == 0x051A)
    return (u8 *)sNeosWisemanSortName;
  if (cardId == 0x051B)
    return (u8 *)sNibiruThePrimalBeingSortName;
  if (cardId == 0x051C)
    return (u8 *)sNuminousHealerSortName;
  if (cardId == 0x051D)
    return (u8 *)sOjamaKingSortName;
  if (cardId == 0x051E)
    return (u8 *)sOrichalcosShunorosSortName;
  if (cardId == 0x051F)
    return (u8 *)sOverDestinySortName;
  if (cardId == 0x0520)
    return (u8 *)sPainfulChoiceSortName;
  if (cardId == 0x0521)
    return (u8 *)sPandemoniumSortName;
  if (cardId == 0x0522)
    return (u8 *)sParallelWorldFusionSortName;
  if (cardId == 0x0523)
    return (u8 *)sPhotonGeneratorUnitSortName;
  if (cardId == 0x0524)
    return (u8 *)sPoisonOfTheOldManSortName;
  if (cardId == 0x0525)
    return (u8 *)sProtectorOfTheSanctuarySortName;
  if (cardId == 0x0526)
    return (u8 *)sQuintetMagicianSortName;
  if (cardId == 0x0527)
    return (u8 *)sRaigekiBreakSortName;
  if (cardId == 0x0528)
    return (u8 *)sProphecySortName;
  if (cardId == 0x0529)
    return (u8 *)sReaperScytheDreadscytheSortName;
  if (cardId == 0x052A)
    return (u8 *)sRedEyesBlackDragonSwordSortName;
  if (cardId == 0x052B)
    return (u8 *)sRedEyesDarkDragoonSortName;
  if (cardId == 0x052C)
    return (u8 *)sRedEyesDarknessMetalDragonSortName;
  if (cardId == 0x052D)
    return (u8 *)sRedEyesTransmigrationSortName;
  if (cardId == 0x052E)
    return (u8 *)sRedGadgetSortName;
  if (cardId == 0x052F)
    return (u8 *)sRelaySoulSortName;
  if (cardId == 0x0530)
    return (u8 *)sReverseOfReverseSortName;
  if (cardId == 0x0531)
    return (u8 *)sRocketHermosCannonSortName;
  if (cardId == 0x0532)
    return (u8 *)sRopeOfLifeSortName;
  if (cardId == 0x0533)
    return (u8 *)sRoyalMagicalLibrarySortName;
  if (cardId == 0x0534)
    return (u8 *)sScapegoatSortName;
  if (cardId == 0x0535)
    return (u8 *)sSecondCoinTossSortName;
  if (cardId == 0x0536)
    return (u8 *)sSecretVillageOfTheSpellcastersSortName;
  if (cardId == 0x0537)
    return (u8 *)sShareThePainSortName;
  if (cardId == 0x0538)
    return (u8 *)sSixthSenseSortName;
  if (cardId == 0x0539)
    return (u8 *)sSkilledDarkMagicianSortName;
  if (cardId == 0x053A)
    return (u8 *)sSkilledWhiteMagicianSortName;
  if (cardId == 0x053B)
    return (u8 *)sSolemnJudgmentSortName;
  if (cardId == 0x053C)
    return (u8 *)sSparkBlasterSortName;
  if (cardId == 0x053D)
    return (u8 *)sSkyscraper2HeroCitySortName;
  if (cardId == 0x053E)
    return (u8 *)sSpellAbsorptionSortName;
  if (cardId == 0x053F)
    return (u8 *)sSphinxTeleiaSortName;
  if (cardId == 0x0540)
    return (u8 *)sStatueOfTheWickedSortName;
  if (cardId == 0x0541)
    return (u8 *)sStaunchDefenderSortName;
  if (cardId == 0x0542)
    return (u8 *)sStrayLambsSortName;
  if (cardId == 0x0543)
    return (u8 *)sStrongholdTheMovingFortressSortName;
  if (cardId == 0x0544)
    return (u8 *)sSummonerMonkSortName;
  if (cardId == 0x0545)
    return (u8 *)sSummonerOfIllusionsSortName;
  if (cardId == 0x0546)
    return (u8 *)sSuperPolymerizationSortName;
  if (cardId == 0x0547)
    return (u8 *)sTerraformingSortName;
  if (cardId == 0x0548)
    return (u8 *)sTheAForcesSortName;
  if (cardId == 0x0549)
    return (u8 *)sTheAgentOfJudgmentSaturnSortName;
  if (cardId == 0x054A)
    return (u8 *)sTheAgentOfWisdomMercurySortName;
  if (cardId == 0x054B)
    return (u8 *)sTheClawOfHermosSortName;
  if (cardId == 0x054C)
    return (u8 *)sTheCreatorSortName;
  if (cardId == 0x054D)
    return (u8 *)sTheCreatorIncarnateSortName;
  if (cardId == 0x054E)
    return (u8 *)sTheEyeOfTimaeusSortName;
  if (cardId == 0x054F)
    return (u8 *)sTheFangOfCritiasSortName;
  if (cardId == 0x0550)
    return (u8 *)sTheLawOfTheNormalSortName;
  if (cardId == 0x0551)
    return (u8 *)sTheLegendaryExodiaIncarnateSortName;
  if (cardId == 0x0552)
    return (u8 *)sTheShallowGraveSortName;
  if (cardId == 0x0553)
    return (u8 *)sTheinenTheGreatSphinxSortName;
  if (cardId == 0x0554)
    return (u8 *)sThestalosTheFirestormMonarchSortName;
  if (cardId == 0x0555)
    return (u8 *)sThunderDragonColossusSortName;
  if (cardId == 0x0556)
    return (u8 *)sThunderDragonTitanSortName;
  if (cardId == 0x0557)
    return (u8 *)sTimaeusTheKnightOfDestinySortName;
  if (cardId == 0x0558)
    return (u8 *)sTimeMagicHammerSortName;
  if (cardId == 0x0559)
    return (u8 *)sTornadoWallSortName;
  if (cardId == 0x055A)
    return (u8 *)sToonWorldSortName;
  if (cardId == 0x055B)
    return (u8 *)sTornadoBirdSortName;
  if (cardId == 0x055C)
    return (u8 *)sTrapDustshootSortName;
  if (cardId == 0x055D)
    return (u8 *)sTyrantBurstDragonSortName;
  if (cardId == 0x055E)
    return (u8 *)sTyrantWingSortName;
  if (cardId == 0x055F)
    return (u8 *)sUltimateConductorTyrannoSortName;
  if (cardId == 0x0560)
    return (u8 *)sUltimateObedientFiendSortName;
  if (cardId == 0x0561)
    return (u8 *)sVisionFusionSortName;
  if (cardId == 0x0562)
    return (u8 *)sVisionHeroAdorationSortName;
  if (cardId == 0x0563)
    return (u8 *)sVisionHeroFarisSortName;
  if (cardId == 0x0564)
    return (u8 *)sVisionHeroGravitoSortName;
  if (cardId == 0x0565)
    return (u8 *)sVisionHeroIncreaseSortName;
  if (cardId == 0x0566)
    return (u8 *)sVisionHeroMinimumRaySortName;
  if (cardId == 0x0567)
    return (u8 *)sVisionHeroMultiplyGuySortName;
  if (cardId == 0x0568)
    return (u8 *)sVisionHeroPoisonerSortName;
  if (cardId == 0x0569)
    return (u8 *)sVisionHeroTrinitySortName;
  if (cardId == 0x056A)
    return (u8 *)sVisionHeroVyonSortName;
  if (cardId == 0x056B)
    return (u8 *)sVisionReleaseSortName;
  if (cardId == 0x056C)
    return (u8 *)sWataponSortName;
  if (cardId == 0x056D)
    return (u8 *)sWhiteDragonRitualSortName;
  if (cardId == 0x056E)
    return (u8 *)sWildNaturesReleaseSortName;
  if (cardId == 0x056F)
    return (u8 *)sWoughtweilerSortName;
  if (cardId == 0x0570)
    return (u8 *)sYellowGadgetSortName;
  if (cardId == 0x0571)
    return (u8 *)sVisionHeroWitchRaiderSortName;
  if (cardId == 0x0572)
    return (u8 *)sAlluringMirrorSplitSortName;
  if (cardId == 0x0573)
    return (u8 *)sAmbushFangsSortName;
  if (cardId == 0x0574)
    return (u8 *)sArcaniteMagicianSortName;
  if (cardId == 0x0575)
    return (u8 *)sArmoryArmSortName;
  if (cardId == 0x0576)
    return (u8 *)sAromaBlendSortName;
  if (cardId == 0x0577)
    return (u8 *)sAromaGardenSortName;
  if (cardId == 0x0578)
    return (u8 *)sAromaGardeningSortName;
  if (cardId == 0x0579)
    return (u8 *)sAromaJarSortName;
  if (cardId == 0x057A)
    return (u8 *)sAromageBergamotSortName;
  if (cardId == 0x057B)
    return (u8 *)sAromageCanangaSortName;
  if (cardId == 0x057C)
    return (u8 *)sAromageJasmineSortName;
  if (cardId == 0x057D)
    return (u8 *)sAromageLaurelSortName;
  if (cardId == 0x057E)
    return (u8 *)sAromageMarjoramSortName;
  if (cardId == 0x057F)
    return (u8 *)sAromageRosemarySortName;
  if (cardId == 0x0580)
    return (u8 *)sAromalilithMagnoliaSortName;
  if (cardId == 0x0581)
    return (u8 *)sAromalilithRosalinaSortName;
  if (cardId == 0x0582)
    return (u8 *)sAromalilithRosemarySortName;
  if (cardId == 0x0583)
    return (u8 *)sAromaseraphyJasmineSortName;
  if (cardId == 0x0584)
    return (u8 *)sAromaseraphyRosemarySortName;
  if (cardId == 0x0585)
    return (u8 *)sAromaseraphySweetMarjoramSortName;
  if (cardId == 0x0586)
    return (u8 *)sAttackPheromonesSortName;
  if (cardId == 0x0587)
    return (u8 *)sAzureEyesSilverDragonSortName;
  if (cardId == 0x0588)
    return (u8 *)sBlackRoseDragonSortName;
  if (cardId == 0x0589)
    return (u8 *)sBlessedWindsSortName;
  if (cardId == 0x058A)
    return (u8 *)sBlueEyesJetDragonSortName;
  if (cardId == 0x058B)
    return (u8 *)sBlueEyesSolidDragonSortName;
  if (cardId == 0x058C)
    return (u8 *)sBlueEyesTyrantDragonSortName;
  if (cardId == 0x058D)
    return (u8 *)sBlueEyesUltimateSpiritDragonSortName;
  if (cardId == 0x058E)
    return (u8 *)sBondBetweenTeacherAndStudentSortName;
  if (cardId == 0x058F)
    return (u8 *)sBlueEyesSpiritDragonSortName;
  if (cardId == 0x0590)
    return (u8 *)sBrionacDragonOfTheIceBarrierSortName;
  if (cardId == 0x0591)
    return (u8 *)sChainMaterialSortName;
  if (cardId == 0x0592)
    return (u8 *)sColossalFighterSortName;
  if (cardId == 0x0593)
    return (u8 *)sCupOfAceSortName;
  if (cardId == 0x0594)
    return (u8 *)sCyberSlashHarpieLadySortName;
  if (cardId == 0x0595)
    return (u8 *)sDamageReptileSortName;
  if (cardId == 0x0596)
    return (u8 *)sDarkBurningAttackSortName;
  if (cardId == 0x0597)
    return (u8 *)sDarkBurningMagicSortName;
  if (cardId == 0x0598)
    return (u8 *)sDarkCallingSortName;
  if (cardId == 0x0599)
    return (u8 *)sDarkContactSortName;
  if (cardId == 0x059A)
    return (u8 *)sDarkFusionSortName;
  if (cardId == 0x059B)
    return (u8 *)sDarkMagicAttackSortName;
  if (cardId == 0x059C)
    return (u8 *)sDarkMagicInheritanceSortName;
  if (cardId == 0x059D)
    return (u8 *)sDarkMagicVeilSortName;
  if (cardId == 0x059E)
    return (u8 *)sDarkMagicalCircleSortName;
  if (cardId == 0x059F)
    return (u8 *)sDarkMagicianGirlTheMagicianSApprenticeSortName;
  if (cardId == 0x05A0)
    return (u8 *)sDarkMagicianOfDestructionSortName;
  if (cardId == 0x05A1)
    return (u8 *)sDarkMagicianTheMagicianOfBlackMagicSortName;
  if (cardId == 0x05A2)
    return (u8 *)sDarkRenewalSortName;
  if (cardId == 0x05A3)
    return (u8 *)sDarkStrikeFighterSortName;
  if (cardId == 0x05A4)
    return (u8 *)sDarkSupremacySortName;
  if (cardId == 0x05A5)
    return (u8 *)sDestinedRivalsSortName;
  if (cardId == 0x05A6)
    return (u8 *)sDriedWindsSortName;
  if (cardId == 0x05A7)
    return (u8 *)sDragonRavineSortName;
  if (cardId == 0x05A8)
    return (u8 *)sDragonShrineSortName;
  if (cardId == 0x05A9)
    return (u8 *)sDeepEyesWhiteDragonSortName;
  if (cardId == 0x05AA)
    return (u8 *)sDragonMasterMagiaSortName;
  if (cardId == 0x05AB)
    return (u8 *)sDragonSpiritOfWhiteSortName;
  if (cardId == 0x05AC)
    return (u8 *)sEbonIllusionMagicianSortName;
  if (cardId == 0x05AD)
    return (u8 *)sElShaddollAnoyatyllisSortName;
  if (cardId == 0x05AE)
    return (u8 *)sElShaddollApkalloneSortName;
  if (cardId == 0x05AF)
    return (u8 *)sElShaddollConstructSortName;
  if (cardId == 0x05B0)
    return (u8 *)sElShaddollFusionSortName;
  if (cardId == 0x05B1)
    return (u8 *)sElShaddollGrystaSortName;
  if (cardId == 0x05B2)
    return (u8 *)sElShaddollMeshahrailSortName;
  if (cardId == 0x05B3)
    return (u8 *)sElShaddollShekhinagaSortName;
  if (cardId == 0x05B4)
    return (u8 *)sElShaddollWendigoSortName;
  if (cardId == 0x05B5)
    return (u8 *)sElShaddollWindaSortName;
  if (cardId == 0x05B6)
    return (u8 *)sEternalSoulSortName;
  if (cardId == 0x05B7)
    return (u8 *)sEvilAssaultSortName;
  if (cardId == 0x05B8)
    return (u8 *)sEvilDragonAnantaSortName;
  if (cardId == 0x05B9)
    return (u8 *)sEvilHeroAdustedGoldSortName;
  if (cardId == 0x05BA)
    return (u8 *)sEvilHeroDarkGaiaSortName;
  if (cardId == 0x05BB)
    return (u8 *)sEvilHeroDarkestKnightSortName;
  if (cardId == 0x05BC)
    return (u8 *)sEvilHeroDeadEndPrisonSortName;
  if (cardId == 0x05BD)
    return (u8 *)sEvilHeroInfernalGainerSortName;
  if (cardId == 0x05BE)
    return (u8 *)sEvilHeroInfernalProdigySortName;
  if (cardId == 0x05BF)
    return (u8 *)sEvilHeroInfernalRiderSortName;
  if (cardId == 0x05C0)
    return (u8 *)sEvilHeroInfernalSniperSortName;
  if (cardId == 0x05C1)
    return (u8 *)sEvilHeroInfernoWingSortName;
  if (cardId == 0x05C2)
    return (u8 *)sEvilHeroInfernoWingBackfireSortName;
  if (cardId == 0x05C3)
    return (u8 *)sEvilHeroLightningGolemSortName;
  if (cardId == 0x05C4)
    return (u8 *)sEvilHeroMaliciousBaneSortName;
  if (cardId == 0x05C5)
    return (u8 *)sEvilHeroMaliciousEdgeSortName;
  if (cardId == 0x05C6)
    return (u8 *)sEvilHeroMaliciousFiendSortName;
  if (cardId == 0x05C7)
    return (u8 *)sEvilHeroNeosLordSortName;
  if (cardId == 0x05C8)
    return (u8 *)sEvilHeroSinisterNecromSortName;
  if (cardId == 0x05C9)
    return (u8 *)sEvilHeroToxicBubbleSortName;
  if (cardId == 0x05CA)
    return (u8 *)sEvilHeroViciousClawsSortName;
  if (cardId == 0x05CB)
    return (u8 *)sEvilHeroWildCycloneSortName;
  if (cardId == 0x05CC)
    return (u8 *)sEvilMindSortName;
  if (cardId == 0x05CD)
    return (u8 *)sFusionDeploymentSortName;
  if (cardId == 0x05CE)
    return (u8 *)sGandoraGTheDragonOfDestructionSortName;
  if (cardId == 0x05CF)
    return (u8 *)sGandoraXTheDragonOfDemolitionSortName;
  if (cardId == 0x05D0)
    return (u8 *)sGoyoGuardianSortName;
  if (cardId == 0x05D1)
    return (u8 *)sGrinderGolemSortName;
  if (cardId == 0x05D2)
    return (u8 *)sHarpieChannelerSortName;
  if (cardId == 0x05D3)
    return (u8 *)sHarpieConductorSortName;
  if (cardId == 0x05D4)
    return (u8 *)sHarpieDancerSortName;
  if (cardId == 0x05D5)
    return (u8 *)sHarpieHarpistSortName;
  if (cardId == 0x05D6)
    return (u8 *)sHarpieLadyEleganceSortName;
  if (cardId == 0x05D7)
    return (u8 *)sHarpieOracleSortName;
  if (cardId == 0x05D8)
    return (u8 *)sHarpiePerfumerSortName;
  if (cardId == 0x05D9)
    return (u8 *)sHarpieQueenSortName;
  if (cardId == 0x05DA)
    return (u8 *)sHarpiesFeatherRestSortName;
  if (cardId == 0x05DB)
    return (u8 *)sHarpiesFeatherStormSortName;
  if (cardId == 0x05DC)
    return (u8 *)sHarpiesHuntingGroundSortName;
  if (cardId == 0x05DD)
    return (u8 *)sHarpiesPetPhantasmalDragonSortName;
  if (cardId == 0x05DE)
    return (u8 *)sHelshaddollHollowSortName;
  if (cardId == 0x05DF)
    return (u8 *)sHeraldOfPerfectionSortName;
  if (cardId == 0x05E0)
    return (u8 *)sHeraldOfUltimatenessSortName;
  if (cardId == 0x05E1)
    return (u8 *)sHeroKidSortName;
  if (cardId == 0x05E2)
    return (u8 *)sHumidWindsSortName;
  if (cardId == 0x05E3)
    return (u8 *)sHystericPartySortName;
  if (cardId == 0x05E4)
    return (u8 *)sHystericSignSortName;
  if (cardId == 0x05E5)
    return (u8 *)sIllusionMagicSortName;
  if (cardId == 0x05E6)
    return (u8 *)sIllusionOfChaosSortName;
  if (cardId == 0x05E7)
    return (u8 *)sIpiriaSortName;
  if (cardId == 0x05E8)
    return (u8 *)sJunkWarriorSortName;
  if (cardId == 0x05E9)
    return (u8 *)sKeeperOfDragonMagicSortName;
  if (cardId == 0x05EA)
    return (u8 *)sLegendaryMajuGarzettSortName;
  if (cardId == 0x05EB)
    return (u8 *)sLevShaddollFusionSortName;
  if (cardId == 0x05EC)
    return (u8 *)sLightSerpentSortName;
  if (cardId == 0x05ED)
    return (u8 *)sLightningWarriorSortName;
  if (cardId == 0x05EE)
    return (u8 *)sLonefireBlossomSortName;
  if (cardId == 0x05EF)
    return (u8 *)sMagicianNavigationSortName;
  if (cardId == 0x05F0)
    return (u8 *)sMagicianOfDarkIllusionSortName;
  if (cardId == 0x05F1)
    return (u8 *)sMagiciansCombinationSortName;
  if (cardId == 0x05F2)
    return (u8 *)sMagiciansRobeSortName;
  if (cardId == 0x05F3)
    return (u8 *)sMagiciansRodSortName;
  if (cardId == 0x05F4)
    return (u8 *)sMagiciansSoulsSortName;
  if (cardId == 0x05F5)
    return (u8 *)sMasterOfChaosSortName;
  if (cardId == 0x05F6)
    return (u8 *)sMetaverseSortName;
  if (cardId == 0x05F7)
    return (u8 *)sMillenniumEyesRestrictSortName;
  if (cardId == 0x05F8)
    return (u8 *)sMoltingEscapeSortName;
  if (cardId == 0x05F9)
    return (u8 *)sMysticMineSortName;
  if (cardId == 0x05FA)
    return (u8 *)sNaelshaddollArielSortName;
  if (cardId == 0x05FB)
    return (u8 *)sNehshaddollGeniusSortName;
  if (cardId == 0x05FC)
    return (u8 *)sNepheShaddollFusionSortName;
  if (cardId == 0x05FD)
    return (u8 *)sNeutronBlastSortName;
  if (cardId == 0x05FE)
    return (u8 *)sOfferingToTheSnakeDeitySortName;
  if (cardId == 0x05FF)
    return (u8 *)sOshaleonSortName;
  if (cardId == 0x0600)
    return (u8 *)sPowerToolDragonSortName;
  if (cardId == 0x0601)
    return (u8 *)sPredaplantVerteAnacondaSortName;
  if (cardId == 0x0602)
    return (u8 *)sQadshaddollKeiosSortName;
  if (cardId == 0x0603)
    return (u8 *)sRedDragonArchfiendSortName;
  if (cardId == 0x0604)
    return (u8 *)sRedRebootSortName;
  if (cardId == 0x0605)
    return (u8 *)sReeshaddollWendiSortName;
  if (cardId == 0x0606)
    return (u8 *)sReeshaddollWendikuruhuSortName;
  if (cardId == 0x0607)
    return (u8 *)sReptilanneRageSortName;
  if (cardId == 0x0608)
    return (u8 *)sReptilianneEchidnaSortName;
  if (cardId == 0x0609)
    return (u8 *)sReptilianneGardnaSortName;
  if (cardId == 0x060A)
    return (u8 *)sReptilianneGorgonSortName;
  if (cardId == 0x060B)
    return (u8 *)sReptilianneHydraSortName;
  if (cardId == 0x060C)
    return (u8 *)sReptilianneLamiaSortName;
  if (cardId == 0x060D)
    return (u8 *)sReptilianneMedusaSortName;
  if (cardId == 0x060E)
    return (u8 *)sReptilianneNagaSortName;
  if (cardId == 0x060F)
    return (u8 *)sReptiliannePoisonSortName;
  if (cardId == 0x0610)
    return (u8 *)sReptilianneScyllaSortName;
  if (cardId == 0x0611)
    return (u8 *)sReptilianneServantSortName;
  if (cardId == 0x0612)
    return (u8 *)sReptilianneSpawnSortName;
  if (cardId == 0x0613)
    return (u8 *)sReptilianneVaskiiSortName;
  if (cardId == 0x0614)
    return (u8 *)sReptilianneViperSortName;
  if (cardId == 0x0615)
    return (u8 *)sReturnOfTheDragonLordsSortName;
  if (cardId == 0x0616)
    return (u8 *)sRiseOfTheSnakeDeitySortName;
  if (cardId == 0x0617)
    return (u8 *)sSecretsOfDarkMagicSortName;
  if (cardId == 0x0618)
    return (u8 *)sSerpentSuppressionSortName;
  if (cardId == 0x0619)
    return (u8 *)sShaddollBeastSortName;
  if (cardId == 0x061A)
    return (u8 *)sShaddollCoreSortName;
  if (cardId == 0x061B)
    return (u8 *)sShaddollDragonSortName;
  if (cardId == 0x061C)
    return (u8 *)sShaddollFalcoSortName;
  if (cardId == 0x061D)
    return (u8 *)sShaddollFusionSortName;
  if (cardId == 0x061E)
    return (u8 *)sShaddollHedgehogSortName;
  if (cardId == 0x061F)
    return (u8 *)sShaddollHoundSortName;
  if (cardId == 0x0620)
    return (u8 *)sShaddollSchismSortName;
  if (cardId == 0x0621)
    return (u8 *)sShaddollSquamataSortName;
  if (cardId == 0x0622)
    return (u8 *)sSilversCrySortName;
  if (cardId == 0x0623)
    return (u8 *)sSnakeDeitysCommandSortName;
  if (cardId == 0x0624)
    return (u8 *)sSnakeRainSortName;
  if (cardId == 0x0625)
    return (u8 *)sSnakeWhistleSortName;
  if (cardId == 0x0626)
    return (u8 *)sSoulServantSortName;
  if (cardId == 0x0627)
    return (u8 *)sStardustDragonSortName;
  if (cardId == 0x0628)
    return (u8 *)sSupremeKingsCastleSortName;
  if (cardId == 0x0629)
    return (u8 *)sThatGrassLooksGreenerSortName;
  if (cardId == 0x062A)
    return (u8 *)sTheDarkMagiciansSortName;
  if (cardId == 0x062B)
    return (u8 *)sTheGazeOfTimaeusSortName;
  if (cardId == 0x062C)
    return (u8 *)sTheMelodyOfAwakeningDragonSortName;
  if (cardId == 0x062D)
    return (u8 *)sTheWhiteStoneOfAncientsSortName;
  if (cardId == 0x062E)
    return (u8 *)sTheWhiteStoneOfLegendSortName;
  if (cardId == 0x062F)
    return (u8 *)sTimeaeusTheUnitedMagicalDragonSortName;
  if (cardId == 0x0630)
    return (u8 *)sTimeausTheUnitedDragonSortName;
  if (cardId == 0x0631)
    return (u8 *)sTohushaddollGrystaSortName;
  if (cardId == 0x0632)
    return (u8 *)sTrapTrickSortName;
  if (cardId == 0x0633)
    return (u8 *)sTriangleEcstasySparkSortName;
  if (cardId == 0x0634)
    return (u8 *)sUltraPolymerizationSortName;
  if (cardId == 0x0635)
    return (u8 *)sVennominagaTheDeityOfPoisonousSnakesSortName;
  if (cardId == 0x0636)
    return (u8 *)sVennominonTheKingOfPoisonousSnakesSortName;
  if (cardId == 0x0637)
    return (u8 *)sVenomBoaSortName;
  if (cardId == 0x0638)
    return (u8 *)sVenomBurnSortName;
  if (cardId == 0x0639)
    return (u8 *)sVenomCobraSortName;
  if (cardId == 0x063A)
    return (u8 *)sVenomSerpentSortName;
  if (cardId == 0x063B)
    return (u8 *)sVenomShotSortName;
  if (cardId == 0x063C)
    return (u8 *)sVenomSnakeSortName;
  if (cardId == 0x063D)
    return (u8 *)sVenomSwampSortName;
  if (cardId == 0x063E)
    return (u8 *)sVipersRebirthSortName;
  if (cardId == 0x063F)
    return (u8 *)sYamorimoriSortName;
  if (cardId == 0x0640)
    return (u8 *)sYowieSortName;
  if (cardId == 0x0641)
    return (u8 *)sAceOfSwordSortName;
  if (cardId == 0x0642)
    return (u8 *)sAceOfWandSortName;
  if (cardId == 0x0643)
    return (u8 *)sArcanaCallSortName;
  if (cardId == 0x0644)
    return (u8 *)sArcanaForce0TheFoolSortName;
  if (cardId == 0x0645)
    return (u8 *)sArcanaForceExTheDarkRulerSortName;
  if (cardId == 0x0646)
    return (u8 *)sArcanaForceExTheLightRulerSortName;
  if (cardId == 0x0647)
    return (u8 *)sArcanaForceITheMagicianSortName;
  if (cardId == 0x0648)
    return (u8 *)sArcanaForceIiiTheEmpressSortName;
  if (cardId == 0x0649)
    return (u8 *)sArcanaForceIvTheEmperorSortName;
  if (cardId == 0x064A)
    return (u8 *)sArcanaForceTheChaosRulerSortName;
  if (cardId == 0x064B)
    return (u8 *)sArcanaForceVTheHierophantSortName;
  if (cardId == 0x064C)
    return (u8 *)sArcanaForceViTheLoversSortName;
  if (cardId == 0x064D)
    return (u8 *)sArcanaForceViiTheChariotSortName;
  if (cardId == 0x064E)
    return (u8 *)sArcanaForceViiiTheStrengthSortName;
  if (cardId == 0x064F)
    return (u8 *)sArcanaForceXiiTheHangmanSortName;
  if (cardId == 0x0650)
    return (u8 *)sArcanaForceXivTemperanceSortName;
  if (cardId == 0x0651)
    return (u8 *)sArcanaForceXixTheSunSortName;
  if (cardId == 0x0652)
    return (u8 *)sArcanaForceXvTheFiendSortName;
  if (cardId == 0x0653)
    return (u8 *)sArcanaForceXviiiTheMoonSortName;
  if (cardId == 0x0654)
    return (u8 *)sArcanaForceXxiTheWorldSortName;
  if (cardId == 0x0655)
    return (u8 *)sArcanaReadingSortName;
  if (cardId == 0x0656)
    return (u8 *)sArcanaSpreadSortName;
  if (cardId == 0x0657)
    return (u8 *)sArmedNeosSortName;
  if (cardId == 0x0658)
    return (u8 *)sAurkusLightswornDruidSortName;
  if (cardId == 0x0659)
    return (u8 *)sCelestiaLightswornAngelSortName;
  if (cardId == 0x065A)
    return (u8 *)sChargeOfTheLightBrigadeSortName;
  if (cardId == 0x065B)
    return (u8 *)sChrysalisChickySortName;
  if (cardId == 0x065C)
    return (u8 *)sChrysalisDolphinSortName;
  if (cardId == 0x065D)
    return (u8 *)sChrysalisMoleSortName;
  if (cardId == 0x065E)
    return (u8 *)sChrysalisPantailSortName;
  if (cardId == 0x065F)
    return (u8 *)sChrysalisPinnySortName;
  if (cardId == 0x0660)
    return (u8 *)sCocoonPartySortName;
  if (cardId == 0x0661)
    return (u8 *)sCocoonRebirthSortName;
  if (cardId == 0x0662)
    return (u8 *)sColosseumCageOfTheGladiatorBeastsSortName;
  if (cardId == 0x0663)
    return (u8 *)sContactSortName;
  if (cardId == 0x0664)
    return (u8 *)sContactGateSortName;
  if (cardId == 0x0665)
    return (u8 *)sConvertContactSortName;
  if (cardId == 0x0666)
    return (u8 *)sCrossKeeperSortName;
  if (cardId == 0x0667)
    return (u8 *)sCuriousTheLightswornDominionSortName;
  if (cardId == 0x0668)
    return (u8 *)sEhrenLightswornMonkSortName;
  if (cardId == 0x0669)
    return (u8 *)sElementalHeroAirNeosSortName;
  if (cardId == 0x066A)
    return (u8 *)sElementalHeroAquaNeosSortName;
  if (cardId == 0x066B)
    return (u8 *)sElementalHeroBraveNeosSortName;
  if (cardId == 0x066C)
    return (u8 *)sElementalHeroChaosNeosSortName;
  if (cardId == 0x066D)
    return (u8 *)sElementalHeroCosmoNeosSortName;
  if (cardId == 0x066E)
    return (u8 *)sElementalHeroDarkNeosSortName;
  if (cardId == 0x066F)
    return (u8 *)sElementalHeroFlareNeosSortName;
  if (cardId == 0x0670)
    return (u8 *)sElementalHeroGlowNeosSortName;
  if (cardId == 0x0671)
    return (u8 *)sElementalHeroGrandNeosSortName;
  if (cardId == 0x0672)
    return (u8 *)sElementalHeroMagmaNeosSortName;
  if (cardId == 0x0673)
    return (u8 *)sElementalHeroMarineNeosSortName;
  if (cardId == 0x0674)
    return (u8 *)sElementalHeroNebulaNeosSortName;
  if (cardId == 0x0675)
    return (u8 *)sElementalHeroShiningNeosWingmanSortName;
  if (cardId == 0x0676)
    return (u8 *)sElementalHeroSpiritOfNeosSortName;
  if (cardId == 0x0677)
    return (u8 *)sElementalHeroStormNeosSortName;
  if (cardId == 0x0678)
    return (u8 *)sEnEngageNeoSpaceSortName;
  if (cardId == 0x0679)
    return (u8 *)sEnShuffleSortName;
  if (cardId == 0x067A)
    return (u8 *)sEnWaveSortName;
  if (cardId == 0x067B)
    return (u8 *)sEnlightenmentDragonSortName;
  if (cardId == 0x067C)
    return (u8 *)sFavouriteContactSortName;
  if (cardId == 0x067D)
    return (u8 *)sFelisLightswornArcherSortName;
  if (cardId == 0x067E)
    return (u8 *)sFlavianColosseumOfTheGladiatorBeastsSortName;
  if (cardId == 0x067F)
    return (u8 *)sGaronithLightswornDragonSortName;
  if (cardId == 0x0680)
    return (u8 *)sGarothLightswornWarriorSortName;
  if (cardId == 0x0681)
    return (u8 *)sGenerationNextSortName;
  if (cardId == 0x0682)
    return (u8 *)sGladiatorBeastAlexanderSortName;
  if (cardId == 0x0683)
    return (u8 *)sGladiatorBeastAndabataSortName;
  if (cardId == 0x0684)
    return (u8 *)sGladiatorBeastAndalSortName;
  if (cardId == 0x0685)
    return (u8 *)sGladiatorBeastAttorixSortName;
  if (cardId == 0x0686)
    return (u8 *)sGladiatorBeastAugustusSortName;
  if (cardId == 0x0687)
    return (u8 *)sGladiatorBeastBattleHalberdSortName;
  if (cardId == 0x0688)
    return (u8 *)sGladiatorBeastBestiariSortName;
  if (cardId == 0x0689)
    return (u8 *)sGladiatorBeastClaudiusSortName;
  if (cardId == 0x068A)
    return (u8 *)sGladiatorBeastDareiosSortName;
  if (cardId == 0x068B)
    return (u8 *)sGladiatorBeastDariusSortName;
  if (cardId == 0x068C)
    return (u8 *)sGladiatorBeastDimacariSortName;
  if (cardId == 0x068D)
    return (u8 *)sGladiatorBeastDomitianusSortName;
  if (cardId == 0x068E)
    return (u8 *)sGladiatorBeastDragasesSortName;
  if (cardId == 0x068F)
    return (u8 *)sGladiatorBeastEquesteSortName;
  if (cardId == 0x0690)
    return (u8 *)sGladiatorBeastEssedariiSortName;
  if (cardId == 0x0691)
    return (u8 *)sGladiatorBeastGaiodiazSortName;
  if (cardId == 0x0692)
    return (u8 *)sGladiatorBeastGistelSortName;
  if (cardId == 0x0693)
    return (u8 *)sGladiatorBeastGyzarusSortName;
  if (cardId == 0x0694)
    return (u8 *)sGladiatorBeastHeraklinosSortName;
  if (cardId == 0x0695)
    return (u8 *)sGladiatorBeastHoplomusSortName;
  if (cardId == 0x0696)
    return (u8 *)sGladiatorBeastLanistaSortName;
  if (cardId == 0x0697)
    return (u8 *)sGladiatorBeastLaquariSortName;
  if (cardId == 0x0698)
    return (u8 *)sGladiatorBeastMurmilloSortName;
  if (cardId == 0x0699)
    return (u8 *)sGladiatorBeastNerokiusSortName;
  if (cardId == 0x069A)
    return (u8 *)sGladiatorBeastNoxiousSortName;
  if (cardId == 0x069B)
    return (u8 *)sGladiatorBeastOctaviusSortName;
  if (cardId == 0x069C)
    return (u8 *)sGladiatorBeastRetiariSortName;
  if (cardId == 0x069D)
    return (u8 *)sGladiatorBeastSagittariiSortName;
  if (cardId == 0x069E)
    return (u8 *)sGladiatorBeastSamniteSortName;
  if (cardId == 0x069F)
    return (u8 *)sGladiatorBeastSecutorSortName;
  if (cardId == 0x06A0)
    return (u8 *)sGladiatorBeastSpartacusSortName;
  if (cardId == 0x06A1)
    return (u8 *)sGladiatorBeastTamerEditorSortName;
  if (cardId == 0x06A2)
    return (u8 *)sGladiatorBeastToraxSortName;
  if (cardId == 0x06A3)
    return (u8 *)sGladiatorBeastTygeriusSortName;
  if (cardId == 0x06A4)
    return (u8 *)sGladiatorBeastVespasiusSortName;
  if (cardId == 0x06A5)
    return (u8 *)sGladiatorBeastWarChariotSortName;
  if (cardId == 0x06A6)
    return (u8 *)sGladiatorBeastsBattleArchfiendShieldSortName;
  if (cardId == 0x06A7)
    return (u8 *)sGladiatorBeastsBattleGladiusSortName;
  if (cardId == 0x06A8)
    return (u8 *)sGladiatorBeastsBattleManicaSortName;
  if (cardId == 0x06A9)
    return (u8 *)sGladiatorBeastsMedusaShieldSortName;
  if (cardId == 0x06AA)
    return (u8 *)sGladiatorBeastsValorSortName;
  if (cardId == 0x06AB)
    return (u8 *)sGladiatorNaumachiaSortName;
  if (cardId == 0x06AC)
    return (u8 *)sGloriousIllusionSortName;
  if (cardId == 0x06AD)
    return (u8 *)sInstantContactSortName;
  if (cardId == 0x06AE)
    return (u8 *)sInstantNeoSpaceSortName;
  if (cardId == 0x06AF)
    return (u8 *)sJainLightswornPaladinSortName;
  if (cardId == 0x06B0)
    return (u8 *)sJainTwilightswornGeneralSortName;
  if (cardId == 0x06B1)
    return (u8 *)sJenisLightswornMenderSortName;
  if (cardId == 0x06B2)
    return (u8 *)sJudgmentTheDragonOfHeavenSortName;
  if (cardId == 0x06B3)
    return (u8 *)sKnightOfPentaclesSortName;
  if (cardId == 0x06B4)
    return (u8 *)sLightBarrierSortName;
  if (cardId == 0x06B5)
    return (u8 *)sLightForceSortName;
  if (cardId == 0x06B6)
    return (u8 *)sLightOfDestructionSortName;
  if (cardId == 0x06B7)
    return (u8 *)sLightSpiralSortName;
  if (cardId == 0x06B8)
    return (u8 *)sLightswornAegisSortName;
  if (cardId == 0x06B9)
    return (u8 *)sLightswornBarrierSortName;
  if (cardId == 0x06BA)
    return (u8 *)sLightswornDragonlingSortName;
  if (cardId == 0x06BB)
    return (u8 *)sLightswornJudgementSortName;
  if (cardId == 0x06BC)
    return (u8 *)sLightswornSabreSortName;
  if (cardId == 0x06BD)
    return (u8 *)sLightswornSanctuarySortName;
  if (cardId == 0x06BE)
    return (u8 *)sLuminaLightswornSummonerSortName;
  if (cardId == 0x06BF)
    return (u8 *)sLuminaTwilightswornShamanSortName;
  if (cardId == 0x06C0)
    return (u8 *)sLylaLightswornSorceressSortName;
  if (cardId == 0x06C1)
    return (u8 *)sLylaTwilightswornEnchantressSortName;
  if (cardId == 0x06C2)
    return (u8 *)sMarchOfTheDarkBrigadeSortName;
  if (cardId == 0x06C3)
    return (u8 *)sMichaelTheArchLightswornSortName;
  if (cardId == 0x06C4)
    return (u8 *)sMinervaLightswornMaidenSortName;
  if (cardId == 0x06C5)
    return (u8 *)sMinervaTheAthenianLightswornSortName;
  if (cardId == 0x06C6)
    return (u8 *)sMinervaTheExhaltedLightswornSortName;
  if (cardId == 0x06C7)
    return (u8 *)sMiracleContactSortName;
  if (cardId == 0x06C8)
    return (u8 *)sMoonTokenSortName;
  if (cardId == 0x06C9)
    return (u8 *)sNeoSpaceSortName;
  if (cardId == 0x06CA)
    return (u8 *)sNeoSpaceConnectorSortName;
  if (cardId == 0x06CB)
    return (u8 *)sNeoSpacianAirHummingbirdSortName;
  if (cardId == 0x06CC)
    return (u8 *)sNeoSpacianAquaDolphinSortName;
  if (cardId == 0x06CD)
    return (u8 *)sNeoSpacianDarkPantherSortName;
  if (cardId == 0x06CE)
    return (u8 *)sNeoSpacianFlareScarabSortName;
  if (cardId == 0x06CF)
    return (u8 *)sNeoSpacianGlowMossSortName;
  if (cardId == 0x06D0)
    return (u8 *)sNeoSpacianGrandMoleSortName;
  if (cardId == 0x06D1)
    return (u8 *)sNeoSpacianMarineDolphinSortName;
  if (cardId == 0x06D2)
    return (u8 *)sNeoSpacianTwinkleMossSortName;
  if (cardId == 0x06D3)
    return (u8 *)sNexSortName;
  if (cardId == 0x06D4)
    return (u8 *)sNextSortName;
  if (cardId == 0x06D5)
    return (u8 *)sPentacleOfAceSortName;
  if (cardId == 0x06D6)
    return (u8 *)sPunishmentDragonSortName;
  if (cardId == 0x06D7)
    return (u8 *)sRaidenHandOfTheLightswornSortName;
  if (cardId == 0x06D8)
    return (u8 *)sRealmOfLightSortName;
  if (cardId == 0x06D9)
    return (u8 *)sRescueCatSortName;
  if (cardId == 0x06DA)
    return (u8 *)sRescueRabbitSortName;
  if (cardId == 0x06DB)
    return (u8 *)sReversalOfFateSortName;
  if (cardId == 0x06DC)
    return (u8 *)sRinyanLightswornRogueSortName;
  if (cardId == 0x06DD)
    return (u8 *)sRykoLightswornHunterSortName;
  if (cardId == 0x06DE)
    return (u8 *)sRykoTwilightswornFighterSortName;
  if (cardId == 0x06DF)
    return (u8 *)sShireLightswornSpiritSortName;
  if (cardId == 0x06E0)
    return (u8 *)sSolarRechargeSortName;
  if (cardId == 0x06E1)
    return (u8 *)sSuitOfSwordXSortName;
  if (cardId == 0x06E2)
    return (u8 *)sTestBearSortName;
  if (cardId == 0x06E3)
    return (u8 *)sTestPantherSortName;
  if (cardId == 0x06E4)
    return (u8 *)sTestTigerSortName;
  if (cardId == 0x06E5)
    return (u8 *)sThumbsDownSortName;
  if (cardId == 0x06E6)
    return (u8 *)sTourOfDoomSortName;
  if (cardId == 0x06E7)
    return (u8 *)sTrojanGladiatorBeastSortName;
  if (cardId == 0x06E8)
    return (u8 *)sTwilightClothSortName;
  if (cardId == 0x06E9)
    return (u8 *)sTwilightEraserSortName;
  if (cardId == 0x06EA)
    return (u8 *)sTwlightTwinDragonsSortName;
  if (cardId == 0x06EB)
    return (u8 *)sVanquishingLightSortName;
  if (cardId == 0x06EC)
    return (u8 *)sWeissLightswornArchfiendSortName;
  if (cardId == 0x06ED)
    return (u8 *)sWulfLightswornBeastSortName;
  if (cardId == 0x06EE)
    return (u8 *)sAllOutAttacksSortName;
  if (cardId == 0x06EF)
    return (u8 *)sAncientFairyDragonSortName;
  if (cardId == 0x06F0)
    return (u8 *)sAncientGearSortName;
  if (cardId == 0x06F1)
    return (u8 *)sAncientGearAdvanceSortName;
  if (cardId == 0x06F2)
    return (u8 *)sAncientGearBeastSortName;
  if (cardId == 0x06F3)
    return (u8 *)sAncientGearCannonSortName;
  if (cardId == 0x06F4)
    return (u8 *)sAncientGearCastleSortName;
  if (cardId == 0x06F5)
    return (u8 *)sAncientGearCommanderSortName;
  if (cardId == 0x06F6)
    return (u8 *)sAncientGearDarkGolemSortName;
  if (cardId == 0x06F7)
    return (u8 *)sAncientGearDragonSortName;
  if (cardId == 0x06F8)
    return (u8 *)sAncientGearDrillSortName;
  if (cardId == 0x06F9)
    return (u8 *)sAncientGearDuelSortName;
  if (cardId == 0x06FA)
    return (u8 *)sAncientGearEngineerSortName;
  if (cardId == 0x06FB)
    return (u8 *)sAncientGearExplosiveSortName;
  if (cardId == 0x06FC)
    return (u8 *)sAncientGearFactorySortName;
  if (cardId == 0x06FD)
    return (u8 *)sAncientGearFistSortName;
  if (cardId == 0x06FE)
    return (u8 *)sAncientGearFrameSortName;
  if (cardId == 0x06FF)
    return (u8 *)sAncientGearFusionSortName;
  if (cardId == 0x0700)
    return (u8 *)sAncientGearGadjiltronChimeraSortName;
  if (cardId == 0x0701)
    return (u8 *)sAncientGearGadjiltronDragonSortName;
  if (cardId == 0x0702)
    return (u8 *)sAncientGearGolemSortName;
  if (cardId == 0x0703)
    return (u8 *)sAncientGearGolemUltimatePoundSortName;
  if (cardId == 0x0704)
    return (u8 *)sAncientGearKnightSortName;
  if (cardId == 0x0705)
    return (u8 *)sAncientGearMegatonGolemSortName;
  if (cardId == 0x0706)
    return (u8 *)sAncientGearSoldierSortName;
  if (cardId == 0x0707)
    return (u8 *)sAncientGearStatueSortName;
  if (cardId == 0x0708)
    return (u8 *)sAncientGearTankSortName;
  if (cardId == 0x0709)
    return (u8 *)sAncientGearTankerSortName;
  if (cardId == 0x070A)
    return (u8 *)sAncientGearWorkshopSortName;
  if (cardId == 0x070B)
    return (u8 *)sAncientLeafSortName;
  if (cardId == 0x070C)
    return (u8 *)sAncientSacredWyvernSortName;
  if (cardId == 0x070D)
    return (u8 *)sArcanaKnightJokerSortName;
  if (cardId == 0x070E)
    return (u8 *)sArcaneBarrierSortName;
  if (cardId == 0x070F)
    return (u8 *)sArmityleTheChaosPhantasmSortName;
  if (cardId == 0x0710)
    return (u8 *)sBabycerasaurusSortName;
  if (cardId == 0x0711)
    return (u8 *)sBarrierStatueOfTheStormwindsSortName;
  if (cardId == 0x0712)
    return (u8 *)sBattleManiaSortName;
  if (cardId == 0x0713)
    return (u8 *)sBigEvolutionPillSortName;
  if (cardId == 0x0714)
    return (u8 *)sBlackWingedDragonSortName;
  if (cardId == 0x0715)
    return (u8 *)sBeastMachineKingBarbarosUrSortName;
  if (cardId == 0x0716)
    return (u8 *)sChainStrikeSortName;
  if (cardId == 0x0717)
    return (u8 *)sChainSummoningSortName;
  if (cardId == 0x0718)
    return (u8 *)sChaosAncientGearGiantSortName;
  if (cardId == 0x0719)
    return (u8 *)sCoralDragonSortName;
  if (cardId == 0x071A)
    return (u8 *)sCrimsonBladerSortName;
  if (cardId == 0x071B)
    return (u8 *)sCrimsonDragonSortName;
  if (cardId == 0x071C)
    return (u8 *)sCrossDimensonalDuelSortName;
  if (cardId == 0x071D)
    return (u8 *)sCyberDragonInfinitySortName;
  if (cardId == 0x071E)
    return (u8 *)sCyberSlashHarpyLadySortName;
  if (cardId == 0x071F)
    return (u8 *)sDarkHorusSortName;
  if (cardId == 0x0720)
    return (u8 *)sDarkMagicianGirlTheMagiciansApprenticeSortName;
  if (cardId == 0x0721)
    return (u8 *)sDarkblazeDragonSortName;
  if (cardId == 0x0722)
    return (u8 *)sBootUpSoldierDreadDynamoSortName;
  if (cardId == 0x0723)
    return (u8 *)sCastelTheSkyBlasterMusketeerSortName;
  if (cardId == 0x0724)
    return (u8 *)sDamageEqualsReptileSortName;
  if (cardId == 0x0725)
    return (u8 *)sDarkMagicianCircleSortName;
  if (cardId == 0x0726)
    return (u8 *)sDarkMagicianTheMagicianOfBlackChaosSortName;
  if (cardId == 0x0727)
    return (u8 *)sDeSynchroSortName;
  if (cardId == 0x0728)
    return (u8 *)sDemiseKingOfArmageddonSortName;
  if (cardId == 0x0729)
    return (u8 *)sDoubleToolCAndDSortName;
  if (cardId == 0x072A)
    return (u8 *)sEndOfTheWorldSortName;
  if (cardId == 0x072B)
    return (u8 *)sEvolzarDolkkaSortName;
  if (cardId == 0x072C)
    return (u8 *)sExchangeOfTheSpiritSortName;
  if (cardId == 0x072D)
    return (u8 *)sFactoryOfOneHundredMachinesSortName;
  if (cardId == 0x072E)
    return (u8 *)sFieldBarrierSortName;
  if (cardId == 0x072F)
    return (u8 *)sFlameRulerSortName;
  if (cardId == 0x0730)
    return (u8 *)sFormulaSynchronSortName;
  if (cardId == 0x0731)
    return (u8 *)sFossilExcavationSortName;
  if (cardId == 0x0732)
    return (u8 *)sGadgetBoxSortName;
  if (cardId == 0x0733)
    return (u8 *)sGandoraXTheDragonOfDestructionSortName;
  if (cardId == 0x0734)
    return (u8 *)sGeartownSortName;
  if (cardId == 0x0735)
    return (u8 *)sGladiatorProvingGroundSortName;
  if (cardId == 0x0736)
    return (u8 *)sGrandConvergenceSortName;
  if (cardId == 0x0737)
    return (u8 *)sGreatPoseidonBeetleSortName;
  if (cardId == 0x0738)
    return (u8 *)sGreenBaboonDefenderOfTheForestSortName;
  if (cardId == 0x0739)
    return (u8 *)sGungnirDragonOfTheIceBarrierSortName;
  if (cardId == 0x073A)
    return (u8 *)sHeraldOfTheArcLightSortName;
  if (cardId == 0x073B)
    return (u8 *)sHeraldOfUlimatenessSortName;
  if (cardId == 0x073C)
    return (u8 *)sHonestSortName;
  if (cardId == 0x073D)
    return (u8 *)sDragonsMirrorSortName;
  if (cardId == 0x073E)
    return (u8 *)sHuntingInstinctSortName;
  if (cardId == 0x073F)
    return (u8 *)sIcarusAttackSortName;
  if (cardId == 0x0740)
    return (u8 *)sJunkSynchronSortName;
  if (cardId == 0x0741)
    return (u8 *)sLevelTuningSortName;
  if (cardId == 0x0742)
    return (u8 *)sLeviairTheSeaDragonSortName;
  if (cardId == 0x0743)
    return (u8 *)sLifeStreamDragonSortName;
  if (cardId == 0x0744)
    return (u8 *)sMacroCosmosSortName;
  if (cardId == 0x0745)
    return (u8 *)sMagicalArmShieldSortName;
  if (cardId == 0x0746)
    return (u8 *)sMagicalMarionetteSortName;
  if (cardId == 0x0747)
    return (u8 *)sMagiciansCircleSortName;
  if (cardId == 0x0748)
    return (u8 *)sMagnaDragoSortName;
  if (cardId == 0x0749)
    return (u8 *)sMirageDragonSortName;
  if (cardId == 0x074A)
    return (u8 *)sMontageDragonSortName;
  if (cardId == 0x074B)
    return (u8 *)sMorphtronicAcceleratorSortName;
  if (cardId == 0x074C)
    return (u8 *)sMorphtronicBindSortName;
  if (cardId == 0x074D)
    return (u8 *)sMorphtronicBoardenSortName;
  if (cardId == 0x074E)
    return (u8 *)sMorphtronicBoomboxenSortName;
  if (cardId == 0x074F)
    return (u8 *)sMorphtronicCameranSortName;
  if (cardId == 0x0750)
    return (u8 *)sMorphtronicCelfonSortName;
  if (cardId == 0x0751)
    return (u8 *)sMorphtronicClockenSortName;
  if (cardId == 0x0752)
    return (u8 *)sMorphtronicConverterSortName;
  if (cardId == 0x0753)
    return (u8 *)sMorphtronicCordSortName;
  if (cardId == 0x0754)
    return (u8 *)sMorphtronicDatatronSortName;
  if (cardId == 0x0755)
    return (u8 *)sMorphtronicEarfonSortName;
  if (cardId == 0x0756)
    return (u8 *)sMorphtronicEngineSortName;
  if (cardId == 0x0757)
    return (u8 *)sMorphtronicForcefieldSortName;
  if (cardId == 0x0758)
    return (u8 *)sMorphtronicImpactReturnSortName;
  if (cardId == 0x0759)
    return (u8 *)sMorphtronicLantronSortName;
  if (cardId == 0x075A)
    return (u8 *)sMorphtronicMagnenSortName;
  if (cardId == 0x075B)
    return (u8 *)sMorphtronicMagnenBarSortName;
  if (cardId == 0x075C)
    return (u8 *)sMorphtronicMapSortName;
  if (cardId == 0x075D)
    return (u8 *)sMorphtronicMonitronSortName;
  if (cardId == 0x075E)
    return (u8 *)sMorphtronicRadionSortName;
  if (cardId == 0x075F)
    return (u8 *)sMorphtronicRemotenSortName;
  if (cardId == 0x0760)
    return (u8 *)sMorphtronicRepairUnitSortName;
  if (cardId == 0x0761)
    return (u8 *)sMorphtronicRustyEngineSortName;
  if (cardId == 0x0762)
    return (u8 *)sMorphtronicScannenSortName;
  if (cardId == 0x0763)
    return (u8 *)sMorphtronicScopenSortName;
  if (cardId == 0x0764)
    return (u8 *)sMorphtronicSlingenSortName;
  if (cardId == 0x0765)
    return (u8 *)sMorphtronicMixupSortName;
  if (cardId == 0x0766)
    return (u8 *)sMorphtronicSmartfonSortName;
  if (cardId == 0x0767)
    return (u8 *)sMorphtronicStaplenSortName;
  if (cardId == 0x0768)
    return (u8 *)sMorphtronicTelefonSortName;
  if (cardId == 0x0769)
    return (u8 *)sMorphtronicVacuumenSortName;
  if (cardId == 0x076A)
    return (u8 *)sMorphtronicVideonSortName;
  if (cardId == 0x076B)
    return (u8 *)sNaturiaBeastSortName;
  if (cardId == 0x076C)
    return (u8 *)sNitroWarriorSortName;
  if (cardId == 0x076D)
    return (u8 *)sPowerFilterSortName;
  if (cardId == 0x076E)
    return (u8 *)sPowerToolBraverDragonSortName;
  if (cardId == 0x076F)
    return (u8 *)sPseudoSpaceSortName;
  if (cardId == 0x0770)
    return (u8 *)sRainbowDarkDragonSortName;
  if (cardId == 0x0771)
    return (u8 *)sRoadSynchronSortName;
  if (cardId == 0x0772)
    return (u8 *)sRoadWarriorSortName;
  if (cardId == 0x0773)
    return (u8 *)sScrapIronScarecrowSortName;
  if (cardId == 0x0774)
    return (u8 *)sSilentMagicianLv4SortName;
  if (cardId == 0x0775)
    return (u8 *)sSilentMagicianLv8SortName;
  if (cardId == 0x0776)
    return (u8 *)sSimorghBirdOfAncestrySortName;
  if (cardId == 0x0777)
    return (u8 *)sSpellChronicleSortName;
  if (cardId == 0x0778)
    return (u8 *)sSpellGearSortName;
  if (cardId == 0x0779)
    return (u8 *)sOverflowingTreasureSortName;
  if (cardId == 0x077A)
    return (u8 *)sSpellStrikerSortName;
  if (cardId == 0x077B)
    return (u8 *)sTGHyperLibrarianSortName;
  if (cardId == 0x077C)
    return (u8 *)sTatsunokoSortName;
  if (cardId == 0x077D)
    return (u8 *)sTimeThiefRedoerSortName;
  if (cardId == 0x077E)
    return (u8 *)sTrishulaDragonOfTheIceBarrierSortName;
  if (cardId == 0x077F)
    return (u8 *)sTuningwareSortName;
  if (cardId == 0x0780)
    return (u8 *)sTurboBoosterSortName;
  if (cardId == 0x0781)
    return (u8 *)sTurboCannonSortName;
  if (cardId == 0x0782)
    return (u8 *)sTurboRocketSortName;
  if (cardId == 0x0783)
    return (u8 *)sTurboSynchronSortName;
  if (cardId == 0x0784)
    return (u8 *)sTyrannoInfinitySortName;
  if (cardId == 0x0785)
    return (u8 *)sUltimateAncientGearGolemSortName;
  if (cardId == 0x0786)
    return (u8 *)sUltimateTyrannoSortName;
  if (cardId == 0x0787)
    return (u8 *)sUnstableEvolutionSortName;
  if (cardId == 0x0788)
    return (u8 *)sUrgentTuningSortName;
  if (cardId == 0x0789)
    return (u8 *)sWarriorOfAtlantisSortName;
  if (cardId == 0x078A)
    return (u8 *)sWaterhazardSortName;
  if (cardId == 0x078B)
    return (u8 *)sWeaponChangeSortName;
  if (cardId == 0x078C)
    return (u8 *)sWetlandsSortName;
  if (cardId == 0x078D)
    return (u8 *)sXSaberAirbellumSortName;
  if (cardId == 0x078E)
    return (u8 *)sACatOfIllOmenSortName;
  if (cardId == 0x078F)
    return (u8 *)sAmazonessAugustaSortName;
  if (cardId == 0x0790)
    return (u8 *)sAmazonessBabyTigerSortName;
  if (cardId == 0x0791)
    return (u8 *)sAmazonessEmpressSortName;
  if (cardId == 0x0792)
    return (u8 *)sAmazonessPetLigerSortName;
  if (cardId == 0x0793)
    return (u8 *)sAmazonessPetLigerKingSortName;
  if (cardId == 0x0794)
    return (u8 *)sAmazonessPrincessSortName;
  if (cardId == 0x0795)
    return (u8 *)sAmazonessQueenSortName;
  if (cardId == 0x0796)
    return (u8 *)sAmazonessSageSortName;
  if (cardId == 0x0797)
    return (u8 *)sAmazonessScoutsSortName;
  if (cardId == 0x0798)
    return (u8 *)sAlectorSovereignOfBirdsSortName;
  if (cardId == 0x0799)
    return (u8 *)sAmazonessCallSortName;
  if (cardId == 0x079A)
    return (u8 *)sAmazonessFightingSpiritSortName;
  if (cardId == 0x079B)
    return (u8 *)sAmazonessHeirloomSortName;
  if (cardId == 0x079C)
    return (u8 *)sAmazonessSecretArtsSortName;
  if (cardId == 0x079D)
    return (u8 *)sAegisOfTheOceanDragonLordSortName;
  if (cardId == 0x079E)
    return (u8 *)sAmazonessHallSortName;
  if (cardId == 0x079F)
    return (u8 *)sAmazonessHotSpringSortName;
  if (cardId == 0x07A0)
    return (u8 *)sAmazonessOnslaughtSortName;
  if (cardId == 0x07A1)
    return (u8 *)sAmazonessShamanismSortName;
  if (cardId == 0x07A2)
    return (u8 *)sAmazonessSpellcasterSortName;
  if (cardId == 0x07A3)
    return (u8 *)sAmazonessVillageSortName;
  if (cardId == 0x07A4)
    return (u8 *)sAnteSortName;
  if (cardId == 0x07A5)
    return (u8 *)sAquaJetSortName;
  if (cardId == 0x07A6)
    return (u8 *)sAmazonessWillpowerSortName;
  if (cardId == 0x07A7)
    return (u8 *)sAmazonessSpiritualistSortName;
  if (cardId == 0x07A8)
    return (u8 *)sAmazonessSpySortName;
  if (cardId == 0x07A9)
    return (u8 *)sAmazonessTraineeSortName;
  if (cardId == 0x07AA)
    return (u8 *)sAmazonessWarChiefSortName;
  if (cardId == 0x07AB)
    return (u8 *)sAnOwlOfLuckSortName;
  if (cardId == 0x07AC)
    return (u8 *)sAtlanteanAttackSquadSortName;
  if (cardId == 0x07AD)
    return (u8 *)sAtlanteanDragoonsSortName;
  if (cardId == 0x07AE)
    return (u8 *)sAtlanteanHeavyInfantrySortName;
  if (cardId == 0x07AF)
    return (u8 *)sAtlanteanMarksmanSortName;
  if (cardId == 0x07B0)
    return (u8 *)sBeastKingBarbarosSortName;
  if (cardId == 0x07B1)
    return (u8 *)sCelestialKnightlordParshathSortName;
  if (cardId == 0x07B2)
    return (u8 *)sChainsawInsectSortName;
  if (cardId == 0x07B3)
    return (u8 *)sCharmOfShabtiSortName;
  if (cardId == 0x07B4)
    return (u8 *)sBazooTheSoulEaterSortName;
  if (cardId == 0x07B5)
    return (u8 *)sAshBlossomAndJoyousSpringSortName;
  if (cardId == 0x07B6)
    return (u8 *)sDoubleCycloneSortName;
  if (cardId == 0x07B7)
    return (u8 *)sForbiddenChaliceSortName;
  if (cardId == 0x07B8)
    return (u8 *)sForbiddenDressSortName;
  if (cardId == 0x07B9)
    return (u8 *)sForbiddenLanceSortName;
  if (cardId == 0x07BA)
    return (u8 *)sDramaticRescueSortName;
  if (cardId == 0x07BB)
    return (u8 *)sForgottenTempleOfTheDeepSortName;
  if (cardId == 0x07BC)
    return (u8 *)sClearViceDragonSortName;
  if (cardId == 0x07BD)
    return (u8 *)sCyberneticMagicianSortName;
  if (cardId == 0x07BE)
    return (u8 *)sDarklordDesireSortName;
  if (cardId == 0x07BF)
    return (u8 *)sDeepSeaDivaSortName;
  if (cardId == 0x07C0)
    return (u8 *)sDivinerOfTheHeraldSortName;
  if (cardId == 0x07C1)
    return (u8 *)sElderEntityNordenSortName;
  if (cardId == 0x07C2)
    return (u8 *)sEnragedBattleOxSortName;
  if (cardId == 0x07C3)
    return (u8 *)sFogKingSortName;
  if (cardId == 0x07C4)
    return (u8 *)sGagagigoTheRisenSortName;
  if (cardId == 0x07C5)
    return (u8 *)sGoldenHomunculusSortName;
  if (cardId == 0x07C6)
    return (u8 *)sFusilierDragonTheDualModeBeastSortName;
  if (cardId == 0x07C7)
    return (u8 *)sGamecialTheSeaTurtleKaijuSortName;
  if (cardId == 0x07C8)
    return (u8 *)sGravekeepersAmbusherSortName;
  if (cardId == 0x07C9)
    return (u8 *)sGravekeepersCannonholderSortName;

  return gCardNames[cardId];
}

static u16 GetCustomCardNameSortOrder(u16 cardId) {
  u16 i;

  for (i = 0; i < NUM_CUSTOM_NAME_SORT_CARDS; i++)
    if (sCustomCardsByName[i] == cardId)
      return sCustomCardNameSortOrder[i];

  return 0;
}
