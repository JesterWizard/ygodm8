#include "global.h"

#define NUM_CUSTOM_NAME_SORT_CARDS 326

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

static const u16 sCustomCardsByName[NUM_CUSTOM_NAME_SORT_CARDS] APPEND_RODATA = {
  0x040B, // A Legendary Ocean
  0x03A0, // Absorbing Kid from the Sky
  0x0381, // Airknight Parshath
  0x03F0, // Amazoness Archer
  0x03C0, // Amazoness Tiger
  0x0382, // Amphibious Bugroth MK-3
  0x033E, // Ancient Rules
  0x0457, // Angel's Tear
  0x0453, // Archlord Kristya
  0x03A1, // Arsenal Bug
  0x0455, // Athena
  0x0409, // Autonomous Action Unit
  0x03A3, // Battle Footballer
  0x03AC, // Berserk Gorilla
  0x03E8, // Big Bang Shot
  0x041C, // Black Luster Soldier - Envoy of the Beginning
  0x0383, // Black Tyranno
  0x03C1, // Blast Held by a Tribute
  0x0385, // Blasting The Ruins
  0x0354, // Block Attack
  0x0403, // Blowback Dragon
  0x033D, // Blue-Eyes Alternative White Dragon
  0x0402, // Blue-Eyes Chaos Dragon
  0x0329, // Blue-Eyes Chaos Max Dragon
  0x0324, // Blue-Eyes Shining Dragon
  0x0405, // Book of Life
  0x03AE, // Book of Moon
  0x0406, // Book of Taiyou
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
  0x0404, // Chaos Command Magician
  0x041B, // Chaos Emperor Dragon - Envoy of the End
  0x03AD, // Chaos Greed
  0x043E, // Chimeratech Overdragon
  0x0387, // Coffin Seller
  0x03C3, // Confiscation
  0x032D, // Copycat
  0x033C, // Cost Down
  0x0459, // Court of Justice
  0x03D1, // Creature Swap
  0x0348, // Cure Mermaid
  0x0386, // Curse Of Darkness
  0x0465, // Cyber Barrier Dragon
  0x03EA, // Cyber Dragon
  0x03EC, // Cyber End Dragon
  0x0466, // Cyber Laser Dragon
  0x03EB, // Cyber Twin Dragon
  0x043F, // Cybernetic Fusion Support
  0x03C2, // D.D. Warrior
  0x03A4, // Dancing Fairy
  0x038A, // Dark Driceratops
  0x03DE, // Dark Dust Spirit
  0x0346, // Dark Magic Curtain
  0x040C, // Dark Magician of Chaos
  0x0389, // Dark Room Of Nightmare
  0x03C7, // Dark Snake Syndrome
  0x03B0, // Darklord Marie
  0x0407, // De-Fusion
  0x0322, // Deck Destruction Virus
  0x040D, // Dedication through Light and Darkness
  0x0355, // Delinquent Duo
  0x03C5, // Des Kangaroo
  0x0349, // Des Koala
  0x03CA, // Dice Jar
  0x0408, // Diffusion Wave-Motion
  0x0458, // Divine Sanctuary
  0x039C, // Double Coston
  0x0338, // Double Summon
  0x0356, // Draining Shield
  0x03C6, // Drillago
  0x03A6, // Drop Off
  0x03E4, // Dust Tornado
  0x0434, // E - Emergency Call
  0x0368, // Ebon Magician Curran
  0x03E5, // Ectoplasmer
  0x0427, // Elemental HERO Absolute Zero
  0x03F1, // Elemental HERO Avian
  0x03F6, // Elemental HERO Bladedge
  0x043C, // Elemental HERO Blazeman
  0x03F4, // Elemental HERO Bubbleman
  0x03F2, // Elemental HERO Burstinatrix
  0x043A, // Elemental HERO Captain Gold
  0x03F7, // Elemental HERO Clayman
  0x0438, // Elemental HERO Core
  0x0417, // Elemental HERO Electrum
  0x042C, // Elemental HERO Escuridao
  0x0411, // Elemental HERO Flame Wingman
  0x042A, // Elemental HERO Flash
  0x042B, // Elemental HERO Gaia
  0x0423, // Elemental HERO Great Tornado
  0x0420, // Elemental HERO Heat
  0x043B, // Elemental HERO Ice Edge
  0x042E, // Elemental HERO Inferno
  0x0425, // Elemental HERO Knospe
  0x0421, // Elemental HERO Lady Heat
  0x0416, // Elemental HERO Mariner
  0x03F8, // Elemental HERO Mudballman
  0x042F, // Elemental HERO Necroid Shaman
  0x0418, // Elemental HERO Necroshade
  0x041D, // Elemental HERO Neos
  0x0422, // Elemental HERO Neos Alius
  0x041F, // Elemental HERO Ocean
  0x040F, // Elemental HERO Phoenix Enforcer
  0x0430, // Elemental HERO Plasma Vice
  0x0426, // Elemental HERO Poison Rose
  0x040A, // Elemental HERO Rampart Blaster
  0x0412, // Elemental HERO Shining Flare Wingman
  0x0410, // Elemental HERO Shining Phoenix Enforcer
  0x03F3, // Elemental HERO Sparkman
  0x040E, // Elemental HERO Steam Healer
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
  0x032C, // Exchange
  0x033B, // Fairy Box
  0x0341, // Familiar Knight
  0x03B1, // Fenrir
  0x039F, // Final Countdown
  0x03D6, // Fire Princess
  0x0431, // Fusion Recovery
  0x0442, // Fusion Sage
  0x0437, // Future Fusion
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
  0x0433, // H - Heated Heart
  0x03F9, // Harpie Lady 1
  0x03FA, // Harpie Lady 2
  0x03FB, // Harpie Lady 3
  0x0401, // Harpie's Pet Baby Dragon
  0x0352, // Hayabusa Knight
  0x045A, // Hecatrice
  0x03A9, // Hyper Hammerhead
  0x0396, // Imperial Order
  0x03D7, // Invader of the Throne
  0x0452, // Iofiel
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
  0x0400, // Level Limit - Area A
  0x03BE, // Level Limit Area B
  0x03E6, // Levia Dragon Daedalus
  0x037B, // Limiter Removal
  0x034F, // Luster Dragon
  0x0443, // Lyrilusc - Independent Nightingale
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
  0x044D, // Mighty Angel Virch
  0x0419, // Miracle Fusion
  0x03FF, // Mirror Force
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
  0x0436, // O - Oversoul
  0x0339, // Obnoxious Celtic Guardian
  0x034E, // Ojama Trio
  0x0440, // Overload Fusion
  0x0325, // Paladin Of White Dragon
  0x037A, // Peten The Dark Clown
  0x0365, // Piranha Army
  0x03E9, // Polymerization
  0x03CE, // Possessed Dark Soul
  0x0441, // Power Bond
  0x039D, // Precious Cards From Beyond
  0x045B, // Premature Burial
  0x03EF, // Proto-Cyber Dragon
  0x0334, // Pyramid of Light
  0x0435, // R - Righteous Justice
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
  0x0451, // Seraphim Blaster
  0x03BC, // Servant of Catabolism
  0x03B7, // Seven Tools of the Bandit
  0x0450, // Shatiel
  0x0328, // Shield And Sword
  0x034A, // Skill Drain
  0x0370, // Skull Invitation
  0x0432, // Skyscraper
  0x035A, // Solar Flare Dragon
  0x0391, // Solar Ray
  0x0392, // Solemn Wishes
  0x0321, // Sorcerer of Dark Magic
  0x0335, // Soul Exchange
  0x0390, // Soul Taker
  0x0343, // Spear Dragon
  0x032B, // Spell Canceller
  0x03FC, // Spell Economics
  0x03D9, // Spirit Caller
  0x03A5, // Spirit of the Breeze
  0x03D3, // Spirit of the Pot of Greed
  0x03B4, // Spirit Reaper
  0x03BF, // Spirit Ryu
  0x0333, // St Joan
  0x0393, // Stealth Bird
  0x036E, // Swift Gaia The Fierce Knight
  0x0374, // Terrorking Salmon
  0x0454, // Tethys, Goddess of Light
  0x0384, // The Agent Of Creation - Venus
  0x041A, // The Agent of Force - Mars
  0x0446, // The Big Saturn
  0x044A, // The Blazing Mars
  0x036D, // The Dark Door
  0x0449, // The Despair Uranus
  0x03D8, // The Flute of Summoning Dragon
  0x0373, // The Forceful Sentry
  0x0448, // The Grand Jupiter
  0x03FE, // The Sanctuary in the Sky
  0x0445, // The Splendid Venus
  0x044B, // The Suppression Pluto
  0x044C, // The Supremacy Sun
  0x03D0, // The Thing in the Crater
  0x045F, // The Tricky
  0x0447, // The Tripper Mercury
  0x0444, // The Tyrant Neptune
  0x03FD, // The Unstoppable Exodia Incarnate
  0x0462, // The Wicked Avatar
  0x0460, // The Wicked Dreadroot
  0x0461, // The Wicked Eraser
  0x03E7, // Theban Nightmare
  0x036C, // Thousand Energy
  0x038F, // Thousand Knives
  0x03B5, // Thunder Crash
  0x036B, // Time Seal
  0x044E, // Tiny Angel
  0x0358, // Toll
  0x03B6, // Torpedo Fish
  0x0464, // Trade-In
  0x038D, // Triangle Power
  0x0463, // Tribute Doll
  0x038E, // Twin Swords of Flashing Light - Tryce
  0x039E, // Tyrant Dragon
  0x0330, // Ultimate Offering
  0x0331, // United We Stand
  0x035C, // Upstart Goblin
  0x0456, // Valhalla, Hall of the Fallen
  0x0372, // Vampire Baby
  0x03DA, // Vengeful Bog Spirit
  0x03DB, // Wall of Revealing Light
  0x036A, // Warrior of Zera
  0x0332, // Wave Motion Cannon
  0x0369, // Weather Report
  0x0367, // White Magician Pikeru
  0x03DC, // World Suppression
  0x035B, // Yata-Garasu
  0x045C, // Yubel
  0x045D, // Yubel - Terror Incarnate
  0x045E, // Yubel - The Ultimate Nightmare
  0x03D4, // Zaborg the Thunder Monarch
  0x044F, // Zeriel
};

static const u16 sCustomCardNameSortOrder[NUM_CUSTOM_NAME_SORT_CARDS] APPEND_RODATA = {
  1, // A Legendary Ocean
  2, // Absorbing Kid from the Sky
  3, // Airknight Parshath
  4, // Amazoness Archer
  5, // Amazoness Tiger
  6, // Amphibious Bugroth MK-3
  7, // Ancient Rules
  8, // Angel's Tear
  9, // Archlord Kristya
  10, // Arsenal Bug
  11, // Athena
  12, // Autonomous Action Unit
  13, // Battle Footballer
  14, // Berserk Gorilla
  15, // Big Bang Shot
  16, // Black Luster Soldier - Envoy of the Beginning
  17, // Black Tyranno
  18, // Blast Held by a Tribute
  19, // Blasting The Ruins
  20, // Block Attack
  21, // Blowback Dragon
  22, // Blue-Eyes Alternative White Dragon
  23, // Blue-Eyes Chaos Dragon
  24, // Blue-Eyes Chaos Max Dragon
  25, // Blue-Eyes Shining Dragon
  26, // Book of Life
  27, // Book of Moon
  28, // Book of Taiyou
  29, // Bottomless Shifting Sand
  30, // Bowganian
  31, // Breaker the Magical Warrior
  32, // Burning Algae
  33, // Burning Land
  34, // Caius the Shadow Monarch
  35, // Call of the Haunted
  36, // Card Destruction
  37, // Card Of Demise
  38, // Card Of Sanctity
  39, // Cat's Ear Tribe
  40, // Chain Energy
  41, // Chaos Command Magician
  42, // Chaos Emperor Dragon - Envoy of the End
  43, // Chaos Greed
  44, // Chimeratech Overdragon
  45, // Coffin Seller
  46, // Confiscation
  47, // Copycat
  48, // Cost Down
  49, // Court of Justice
  50, // Creature Swap
  51, // Cure Mermaid
  52, // Curse Of Darkness
  53, // Cyber Barrier Dragon
  54, // Cyber Dragon
  55, // Cyber End Dragon
  56, // Cyber Laser Dragon
  57, // Cyber Twin Dragon
  58, // Cybernetic Fusion Support
  59, // D.D. Warrior
  60, // Dancing Fairy
  61, // Dark Driceratops
  62, // Dark Dust Spirit
  63, // Dark Magic Curtain
  64, // Dark Magician of Chaos
  65, // Dark Room Of Nightmare
  66, // Dark Snake Syndrome
  67, // Darklord Marie
  68, // De-Fusion
  69, // Deck Destruction Virus
  70, // Dedication through Light and Darkness
  71, // Delinquent Duo
  72, // Des Kangaroo
  73, // Des Koala
  74, // Dice Jar
  75, // Diffusion Wave-Motion
  76, // Divine Sanctuary
  77, // Double Coston
  78, // Double Summon
  79, // Draining Shield
  80, // Drillago
  81, // Drop Off
  82, // Dust Tornado
  83, // E - Emergency Call
  84, // Ebon Magician Curran
  85, // Ectoplasmer
  86, // Elemental HERO Absolute Zero
  87, // Elemental HERO Avian
  88, // Elemental HERO Bladedge
  89, // Elemental HERO Blazeman
  90, // Elemental HERO Bubbleman
  91, // Elemental HERO Burstinatrix
  92, // Elemental HERO Captain Gold
  93, // Elemental HERO Clayman
  94, // Elemental HERO Core
  95, // Elemental HERO Electrum
  96, // Elemental HERO Escuridao
  97, // Elemental HERO Flame Wingman
  98, // Elemental HERO Flash
  99, // Elemental HERO Gaia
  100, // Elemental HERO Great Tornado
  101, // Elemental HERO Heat
  102, // Elemental HERO Ice Edge
  103, // Elemental HERO Inferno
  104, // Elemental HERO Knospe
  105, // Elemental HERO Lady Heat
  106, // Elemental HERO Mariner
  107, // Elemental HERO Mudballman
  108, // Elemental HERO Necroid Shaman
  109, // Elemental HERO Necroshade
  110, // Elemental HERO Neos
  111, // Elemental HERO Neos Alius
  112, // Elemental HERO Ocean
  113, // Elemental HERO Phoenix Enforcer
  114, // Elemental HERO Plasma Vice
  115, // Elemental HERO Poison Rose
  116, // Elemental HERO Rampart Blaster
  117, // Elemental HERO Shining Flare Wingman
  118, // Elemental HERO Shining Phoenix Enforcer
  119, // Elemental HERO Sparkman
  120, // Elemental HERO Steam Healer
  121, // Elemental HERO Stratos
  122, // Elemental HERO Sunrise
  123, // Elemental HERO Tempest
  124, // Elemental HERO Terra Firma
  125, // Elemental HERO The Shining
  126, // Elemental HERO Thunder Giant
  127, // Elemental HERO Voltic
  128, // Elemental HERO Wild Wingman
  129, // Elemental HERO Wildedge
  130, // Elemental HERO Wildheart
  131, // Elemental HERO Woodsman
  132, // Exchange
  133, // Fairy Box
  134, // Familiar Knight
  135, // Fenrir
  136, // Final Countdown
  137, // Fire Princess
  138, // Fusion Recovery
  139, // Fusion Sage
  140, // Future Fusion
  141, // Ghost Knight of Jackal
  142, // Gift Of The Mystical Elf
  143, // Gilasaurus
  144, // Goblin King
  145, // Goblin Thief
  146, // Graceful Charity
  147, // Graceful Dice
  148, // Granadora
  149, // Gravekeeper's Servant
  150, // Gravity Bind
  151, // Great Maju Garzett
  152, // Gren Maju Da Eiza
  153, // Guardian Angel Joan
  154, // Guardian Treasure
  155, // Gyaku-Gire Panda
  156, // H - Heated Heart
  157, // Harpie Lady 1
  158, // Harpie Lady 2
  159, // Harpie Lady 3
  160, // Harpie's Pet Baby Dragon
  161, // Hayabusa Knight
  162, // Hecatrice
  163, // Hyper Hammerhead
  164, // Imperial Order
  165, // Invader of the Throne
  166, // Iofiel
  167, // Jar of Greed
  168, // Jar Robber
  169, // Jowls of Dark Demise
  170, // Just Deserts
  171, // KA-2 Des Scissors
  172, // Kaibaman
  173, // Kaiser Colosseum
  174, // Kaiser Glider
  175, // Kishido Spirit
  176, // Knight's Title
  177, // Lesser Fiend
  178, // Level Limit - Area A
  179, // Level Limit Area B
  180, // Levia Dragon Daedalus
  181, // Limiter Removal
  182, // Luster Dragon
  183, // Lyrilusc - Independent Nightingale
  184, // Mad Sword Beast
  185, // Mage Power
  186, // Magic Cylinder
  187, // Magic Jammer
  188, // Magical Merchant
  189, // Magician's Valkyria
  190, // Maju Garzett
  191, // Man-Thro-Thro
  192, // Marauding Captain
  193, // Maryokutai
  194, // Mask of Restrict
  195, // Mataza the Zapper
  196, // Mefist The Infernal General
  197, // Mermaid Knight
  198, // Meteor of Destruction
  199, // Mighty Angel Virch
  200, // Miracle Fusion
  201, // Mirror Force
  202, // Mirror Wall
  203, // Mobius the Frost Monarch
  204, // Moister Creature
  205, // Mystical Shine Ball
  206, // Mystical Space Typhoon
  207, // Needle Burrower
  208, // Negate Attack
  209, // Negative Energy
  210, // Nightmare Horse
  211, // Nightmare Wheel
  212, // O - Oversoul
  213, // Obnoxious Celtic Guardian
  214, // Ojama Trio
  215, // Overload Fusion
  216, // Paladin Of White Dragon
  217, // Peten The Dark Clown
  218, // Piranha Army
  219, // Polymerization
  220, // Possessed Dark Soul
  221, // Power Bond
  222, // Precious Cards From Beyond
  223, // Premature Burial
  224, // Proto-Cyber Dragon
  225, // Pyramid of Light
  226, // R - Righteous Justice
  227, // Rain of Mercy
  228, // Rare Metal Dragon
  229, // Raregold Armor
  230, // Reaper on the Nightmare
  231, // Reckless Greed
  232, // Reload
  233, // Ring of Destruction
  234, // Riryoku
  235, // Rivalry of Warlords
  236, // Robbin' Goblin
  237, // Robbin' Zombie
  238, // Royal Decree
  239, // Royal Knight
  240, // Ryu-Kishin Clown
  241, // Sage's Stone
  242, // Sasuke Samurai
  243, // Sasuke Samurai #2
  244, // Sasuke Samurai #3
  245, // Seal of Orichalcos
  246, // Secret Barrel
  247, // Self-Destruct Button
  248, // Seraphim Blaster
  249, // Servant of Catabolism
  250, // Seven Tools of the Bandit
  251, // Shatiel
  252, // Shield And Sword
  253, // Skill Drain
  254, // Skull Invitation
  255, // Skyscraper
  256, // Solar Flare Dragon
  257, // Solar Ray
  258, // Solemn Wishes
  259, // Sorcerer of Dark Magic
  260, // Soul Exchange
  261, // Soul Taker
  262, // Spear Dragon
  263, // Spell Canceller
  264, // Spell Economics
  265, // Spirit Caller
  266, // Spirit of the Breeze
  267, // Spirit of the Pot of Greed
  268, // Spirit Reaper
  269, // Spirit Ryu
  270, // St Joan
  271, // Stealth Bird
  272, // Swift Gaia The Fierce Knight
  273, // Terrorking Salmon
  274, // Tethys, Goddess of Light
  275, // The Agent Of Creation - Venus
  276, // The Agent of Force - Mars
  277, // The Big Saturn
  278, // The Blazing Mars
  279, // The Dark Door
  280, // The Despair Uranus
  281, // The Flute of Summoning Dragon
  282, // The Forceful Sentry
  283, // The Grand Jupiter
  284, // The Sanctuary in the Sky
  285, // The Splendid Venus
  286, // The Suppression Pluto
  287, // The Supremacy Sun
  288, // The Thing in the Crater
  289, // The Tricky
  290, // The Tripper Mercury
  291, // The Tyrant Neptune
  292, // The Unstoppable Exodia Incarnate
  293, // The Wicked Avatar
  294, // The Wicked Dreadroot
  295, // The Wicked Eraser
  296, // Theban Nightmare
  297, // Thousand Energy
  298, // Thousand Knives
  299, // Thunder Crash
  300, // Time Seal
  301, // Tiny Angel
  302, // Toll
  303, // Torpedo Fish
  304, // Trade-In
  305, // Triangle Power
  306, // Tribute Doll
  307, // Twin Swords of Flashing Light - Tryce
  308, // Tyrant Dragon
  309, // Ultimate Offering
  310, // United We Stand
  311, // Upstart Goblin
  312, // Valhalla, Hall of the Fallen
  313, // Vampire Baby
  314, // Vengeful Bog Spirit
  315, // Wall of Revealing Light
  316, // Warrior of Zera
  317, // Wave Motion Cannon
  318, // Weather Report
  319, // White Magician Pikeru
  320, // World Suppression
  321, // Yata-Garasu
  322, // Yubel
  323, // Yubel - Terror Incarnate
  324, // Yubel - The Ultimate Nightmare
  325, // Zaborg the Thunder Monarch
  326, // Zeriel
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

  return gCardNames[cardId];
}

static u16 GetCustomCardNameSortOrder(u16 cardId) {
  u16 i;

  for (i = 0; i < NUM_CUSTOM_NAME_SORT_CARDS; i++)
    if (sCustomCardsByName[i] == cardId)
      return sCustomCardNameSortOrder[i];

  return 0;
}
