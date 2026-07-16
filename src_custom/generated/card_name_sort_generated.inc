#include "global.h"

#define NUM_CUSTOM_NAME_SORT_CARDS 771

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

static const u16 sCustomCardsByName[NUM_CUSTOM_NAME_SORT_CARDS] APPEND_RODATA = {
  0x046A, // A Hero Emerges
  0x046B, // A Hero Lives
  0x040B, // A Legendary Ocean
  0x046C, // A Wingbeat of Giant Dragon
  0x03A0, // Absorbing Kid from the Sky
  0x0381, // Airknight Parshath
  0x046D, // Allure of Darkness
  0x0572, // Alluring Mirror Split
  0x03F0, // Amazoness Archer
  0x03C0, // Amazoness Tiger
  0x0573, // Ambush Fangs
  0x0382, // Amphibious Bugroth MK-3
  0x046E, // Amulet Dragon
  0x033E, // Ancient Rules
  0x046F, // Andro Sphinx
  0x0457, // Angel's Tear
  0x0470, // Anti-Spell Fragrance
  0x0473, // Apparition
  0x0472, // Apprentice Illusion Magician
  0x0471, // Appropriate
  0x0574, // Arcanite Magician
  0x0453, // Archlord Kristya
  0x0477, // Armageddon Knight
  0x047B, // Armed Dragon LV10
  0x0478, // Armed Dragon LV3
  0x0479, // Armed Dragon LV5
  0x047A, // Armed Dragon LV7
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
  0x0455, // Athena
  0x047C, // Attack and Receive
  0x0474, // Attack Guidance Armor
  0x0586, // Attack Pheromones
  0x0475, // Attack Reflector Unit
  0x0409, // Autonomous Action Unit
  0x0587, // Azure-Eyes Silver Dragon
  0x047D, // Backfire
  0x0476, // Backup Squad
  0x03A3, // Battle Footballer
  0x03AC, // Berserk Gorilla
  0x0481, // Berserker Soul
  0x03E8, // Big Bang Shot
  0x0482, // Birdface
  0x041C, // Black Luster Soldier - Envoy of the Beginning
  0x0588, // Black Rose Dragon
  0x0383, // Black Tyranno
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
  0x0347, // Cat's Ear Tribe
  0x0489, // Celestial Sword - Eatos
  0x032A, // Chain Energy
  0x0591, // Chain Material
  0x0404, // Chaos Command Magician
  0x041B, // Chaos Emperor Dragon - Envoy of the End
  0x048A, // Chaos Form
  0x03AD, // Chaos Greed
  0x048B, // Chicken Game
  0x048C, // Chimeratech Fortress Dragon
  0x048D, // Chimeratech Megafleet Dragon
  0x043E, // Chimeratech Overdragon
  0x048E, // Chimeratech Rampage Dragon
  0x048F, // Clock Tower Prison
  0x0387, // Coffin Seller
  0x0490, // Cold Wave
  0x0592, // Colossal Fighter
  0x03C3, // Confiscation
  0x0491, // Continuous Destruction Punch
  0x032D, // Copycat
  0x033C, // Cost Down
  0x0459, // Court of Justice
  0x03D1, // Creature Swap
  0x0593, // Cup of Ace
  0x0348, // Cure Mermaid
  0x0386, // Curse Of Darkness
  0x0465, // Cyber Barrier Dragon
  0x03EA, // Cyber Dragon
  0x0492, // Cyber Eltanin
  0x03EC, // Cyber End Dragon
  0x0493, // Cyber Kirin
  0x0466, // Cyber Laser Dragon
  0x0494, // Cyber Phoenix
  0x0594, // Cyber Slash Harpie Lady
  0x03EB, // Cyber Twin Dragon
  0x0495, // Cyber Valley
  0x043F, // Cybernetic Fusion Support
  0x0496, // Cybernetic Zone
  0x049A, // D - Burst
  0x049B, // D - Force
  0x0497, // D - Tactics
  0x0498, // D - Time
  0x03C2, // D.D. Warrior
  0x0595, // Damage = Reptile
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
  0x059B, // Dark Magic Attack
  0x0346, // Dark Magic Curtain
  0x059C, // Dark Magic Inheritance
  0x059D, // Dark Magic Veil
  0x059E, // Dark Magical Circle
  0x049E, // Dark Magician Girl the Dragon Knight
  0x059F, // Dark Magician Girl the Magician's Apprentice
  0x040C, // Dark Magician of Chaos
  0x05A0, // Dark Magician of Destruction
  0x04A2, // Dark Magician the Dragon Knight
  0x05A1, // Dark Magician the Magician of Black Magic
  0x05A2, // Dark Renewal
  0x0389, // Dark Room Of Nightmare
  0x03C7, // Dark Snake Syndrome
  0x05A3, // Dark Strike Fighter
  0x05A4, // Dark Supremacy
  0x03B0, // Darklord Marie
  0x049F, // Darklord Nurse Reficule
  0x04A0, // Darkness Neosphere
  0x0407, // De-Fusion
  0x0322, // Deck Destruction Virus
  0x04A3, // Decoy Dragon
  0x040D, // Dedication through Light and Darkness
  0x05A9, // Deep-Eyes White Dragon
  0x0355, // Delinquent Duo
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
  0x04CE, // Doctor D
  0x04CA, // Don Zaloog
  0x04CF, // Doom Virus Dragon
  0x04D0, // Doppelganger
  0x039C, // Double Coston
  0x04CB, // Double Spell
  0x0338, // Double Summon
  0x05AA, // Dragon Master Magia
  0x05A7, // Dragon Ravine
  0x05A8, // Dragon Shrine
  0x05AB, // Dragon Spirit of White
  0x04CC, // Dragon's Rage
  0x04D9, // Drain Time
  0x0356, // Draining Shield
  0x05A6, // Dried Winds
  0x03C6, // Drillago
  0x03A6, // Drop Off
  0x03E4, // Dust Tornado
  0x0434, // E - Emergency Call
  0x05AC, // Ebon Illusion Magician
  0x0368, // Ebon Magician Curran
  0x03E5, // Ectoplasmer
  0x04D1, // Egyptian God Slime
  0x05AD, // El Shaddoll Anoyatyllis
  0x05AE, // El Shaddoll Apkallone
  0x05AF, // El Shaddoll Construct
  0x05B0, // El Shaddoll Fusion
  0x05B1, // El Shaddoll Grysta
  0x05B2, // El Shaddoll Meshahrail
  0x05B3, // El Shaddoll Shekhinaga
  0x05B4, // El Shaddoll Wendigo
  0x05B5, // El Shaddoll Winda
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
  0x04D2, // Elemental HERO Neos Kluger
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
  0x04D3, // Emergency Provisions
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
  0x032C, // Exchange
  0x04D4, // Exodius the Ultimate Forbidden Lord
  0x033B, // Fairy Box
  0x0341, // Familiar Knight
  0x04D5, // Fatal Abacus
  0x04D6, // Felgrand Dragon
  0x03B1, // Fenrir
  0x04DA, // Fields Sanctuary
  0x039F, // Final Countdown
  0x03D6, // Fire Princess
  0x04D7, // Fires of Doomsday
  0x04D8, // Forced Requisition
  0x05CD, // Fusion Deployment
  0x04DB, // Fusion Destiny
  0x04DC, // Fusion Gate
  0x0431, // Fusion Recovery
  0x0442, // Fusion Sage
  0x0437, // Future Fusion
  0x05CE, // Gandora-G the Dragon of Destruction
  0x05CF, // Gandora-X the Dragon of Demolition
  0x04DD, // Gate Guardians Combined
  0x03DF, // Ghost Knight of Jackal
  0x04DE, // Gift Card
  0x037F, // Gift Of The Mystical Elf
  0x037D, // Gilasaurus
  0x03A7, // Goblin King
  0x0351, // Goblin Thief
  0x04DF, // Goddess Bow
  0x04E0, // Gorz the Emissary of Darkness
  0x05D0, // Goyo Guardian
  0x038B, // Graceful Charity
  0x03AB, // Graceful Dice
  0x03A8, // Granadora
  0x04E1, // Granmarg the Rock Monarch
  0x03C9, // Gravekeeper's Servant
  0x037E, // Gravity Bind
  0x038C, // Great Maju Garzett
  0x04E2, // Green Gadget
  0x0397, // Gren Maju Da Eiza
  0x05D1, // Grinder Golem
  0x04E3, // Ground Collapse
  0x0379, // Guardian Angel Joan
  0x04E4, // Guardian Dreadscythe
  0x04E9, // Guardian Eatos
  0x034B, // Guardian Treasure
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
  0x05E0, // Herald of Ultimateness
  0x04E6, // Hero Flash!!
  0x05E1, // Hero Kid
  0x04EB, // Holactie the Creator of Light
  0x04ED, // Horus the Black Flame Dragon LV4
  0x04EE, // Horus the Black Flame Dragon LV6
  0x04EC, // Horus the Black Flame Dragon LV8
  0x05E2, // Humid Winds
  0x03A9, // Hyper Hammerhead
  0x05E3, // Hysteric Party
  0x05E4, // Hysteric Sign
  0x05E5, // Illusion Magic
  0x05E6, // Illusion of Chaos
  0x0396, // Imperial Order
  0x04E7, // Insect Imitation
  0x04E8, // Instant Fusion
  0x03D7, // Invader of the Throne
  0x0452, // Iofiel
  0x05E7, // Ipiria
  0x034C, // Jar of Greed
  0x03C8, // Jar Robber
  0x04EF, // Jowgen the Spiritualist
  0x03CC, // Jowls of Dark Demise
  0x04F0, // Judgment Dragon
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
  0x03E6, // Levia Dragon Daedalus
  0x04FD, // Light and Darkness Dragon
  0x0468, // Light End Dragon
  0x05ED, // Lightning Warrior
  0x05EC, // Lightserpent
  0x037B, // Limiter Removal
  0x05EE, // Lonefire Blossom
  0x04FE, // Lord of the Red
  0x034F, // Luster Dragon
  0x0443, // Lyrilusc - Independent Nightingale
  0x04FF, // Ma'at
  0x034D, // Mad Sword Beast
  0x032E, // Mage Power
  0x0353, // Magic Cylinder
  0x033F, // Magic Jammer
  0x0500, // Magical Dimension
  0x0501, // Magical Hats
  0x03B2, // Magical Merchant
  0x0502, // Magical Plant Mandragola
  0x0503, // Magical Scientist
  0x0504, // Magical Stone Excavation
  0x05EF, // Magician Navigation
  0x05F0, // Magician of Dark Illusion
  0x05F2, // Magician's Robe
  0x05F3, // Magician's Rod
  0x0323, // Magician's Valkyria
  0x05F1, // Magicians' Combination
  0x05F4, // Magicians' Souls
  0x0505, // Majestic Mech - Goryu
  0x03E3, // Maju Garzett
  0x03BD, // Man-Thro-Thro
  0x0506, // Manju of the Ten Thousand Hands
  0x035F, // Marauding Captain
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
  0x044D, // Mighty Angel Virch
  0x05F7, // Millennium-Eyes Restrict
  0x0419, // Miracle Fusion
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
  0x0514, // Morale Boost
  0x0515, // Mucus Yolk
  0x05F9, // Mystic Mine
  0x0350, // Mystical Shine Ball
  0x0336, // Mystical Space Typhoon
  0x0516, // Mystik Wok
  0x05FA, // Naelshaddoll Ariel
  0x0517, // Necrovalley
  0x0394, // Needle Burrower
  0x0518, // Needle Wall
  0x035D, // Negate Attack
  0x039A, // Negative Energy
  0x05FB, // Nehshaddoll Genius
  0x0519, // Neo Blue-Eyes Ultimate Dragon
  0x051A, // Neos Wiseman
  0x05FC, // Nephe Shaddoll Fusion
  0x05FD, // Neutron Blast
  0x051B, // Nibiru, the Primal Being
  0x0371, // Nightmare Horse
  0x03E1, // Nightmare Wheel
  0x051C, // Numinous Healer
  0x0436, // O - Oversoul
  0x0339, // Obnoxious Celtic Guardian
  0x05FE, // Offering to the Snake Deity
  0x051D, // Ojama King
  0x034E, // Ojama Trio
  0x051E, // Orichalcos Shunoros
  0x05FF, // Oshaleon
  0x051F, // Over Destiny
  0x0440, // Overload Fusion
  0x0520, // Painful Choice
  0x0325, // Paladin Of White Dragon
  0x0521, // Pandemonium
  0x0522, // Parallel World Fusion
  0x037A, // Peten The Dark Clown
  0x0523, // Photon Generator Unit
  0x0365, // Piranha Army
  0x0524, // Poison of the Old Man
  0x03E9, // Polymerization
  0x03CE, // Possessed Dark Soul
  0x0441, // Power Bond
  0x0600, // Power Tool Dragon
  0x039D, // Precious Cards From Beyond
  0x0601, // Predaplant Verte Anaconda
  0x045B, // Premature Burial
  0x0528, // Prophecy
  0x0525, // Protector of the Sanctuary
  0x03EF, // Proto-Cyber Dragon
  0x0334, // Pyramid of Light
  0x0602, // Qadshaddoll Keios
  0x0526, // Quintet Magician
  0x0435, // R - Righteous Justice
  0x0527, // Raigeki Break
  0x0359, // Rain of Mercy
  0x0337, // Rare Metal Dragon
  0x03B3, // Raregold Armor
  0x0480, // Raviel, Lord of Phantasms
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
  0x0615, // Return of the Dragon Lords
  0x0530, // Reverse of Reverse
  0x03B9, // Ring of Destruction
  0x0342, // Riryoku
  0x0616, // Rise of the Snake Deity
  0x03B8, // Rivalry of Warlords
  0x0361, // Robbin' Goblin
  0x0362, // Robbin' Zombie
  0x0531, // Rocket Hermos Cannon
  0x0532, // Rope of Life
  0x0398, // Royal Decree
  0x03CF, // Royal Knight
  0x0533, // Royal Magical Library
  0x03DD, // Ryu-Kishin Clown
  0x0344, // Sage's Stone
  0x0375, // Sasuke Samurai
  0x03BA, // Sasuke Samurai #2
  0x03BB, // Sasuke Samurai #3
  0x0534, // Scapegoat
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
  0x0622, // Silver's Cry
  0x0538, // Sixth Sense
  0x034A, // Skill Drain
  0x0539, // Skilled Dark Magician
  0x053A, // Skilled White Magician
  0x0370, // Skull Invitation
  0x0432, // Skyscraper
  0x053D, // Skyscraper 2 - Hero City
  0x0623, // Snake Deity's Command
  0x035A, // Solar Flare Dragon
  0x0391, // Solar Ray
  0x053B, // Solemn Judgment
  0x0392, // Solemn Wishes
  0x0321, // Sorcerer of Dark Magic
  0x0335, // Soul Exchange
  0x0390, // Soul Taker
  0x053C, // Spark Blaster
  0x0343, // Spear Dragon
  0x053E, // Spell Absorption
  0x032B, // Spell Canceller
  0x03FC, // Spell Economics
  0x053F, // Sphinx Teleia
  0x03D9, // Spirit Caller
  0x03A5, // Spirit of the Breeze
  0x03D3, // Spirit of the Pot of Greed
  0x03B4, // Spirit Reaper
  0x03BF, // Spirit Ryu
  0x0333, // St Joan
  0x0540, // Statue of the Wicked
  0x0541, // Staunch Defender
  0x0393, // Stealth Bird
  0x0542, // Stray Lambs
  0x0543, // Stronghold the Moving Fortress
  0x0544, // Summoner Monk
  0x0545, // Summoner of Illusions
  0x0546, // Super Polymerization
  0x036E, // Swift Gaia The Fierce Knight
  0x0547, // Terraforming
  0x0374, // Terrorking Salmon
  0x0454, // Tethys, Goddess of Light
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
  0x0449, // The Despair Uranus
  0x054E, // The Eye of Timaeus
  0x054F, // The Fang of Critias
  0x03D8, // The Flute of Summoning Dragon
  0x0373, // The Forceful Sentry
  0x0448, // The Grand Jupiter
  0x0550, // The Law of the Normal
  0x0551, // The Legendary Exodia Incarnate
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
  0x0462, // The Wicked Avatar
  0x0460, // The Wicked Dreadroot
  0x0461, // The Wicked Eraser
  0x03E7, // Theban Nightmare
  0x0553, // Theinen the Great Sphinx
  0x0554, // Thestalos the Firestorm Monarch
  0x036C, // Thousand Energy
  0x038F, // Thousand Knives
  0x03B5, // Thunder Crash
  0x0555, // Thunder Dragon Colossus
  0x0556, // Thunder Dragon Titan
  0x0557, // Timaeus the Knight of Destiny
  0x0558, // Time Magic Hammer
  0x036B, // Time Seal
  0x044E, // Tiny Angel
  0x0358, // Toll
  0x055A, // Toon World
  0x055B, // Tornado Bird
  0x0559, // Tornado Wall
  0x03B6, // Torpedo Fish
  0x0464, // Trade-In
  0x055C, // Trap Dustshoot
  0x038D, // Triangle Power
  0x0463, // Tribute Doll
  0x038E, // Twin Swords of Flashing Light - Tryce
  0x055D, // Tyrant Burst Dragon
  0x039E, // Tyrant Dragon
  0x055E, // Tyrant Wing
  0x055F, // Ultimate Conductor Tyranno
  0x0560, // Ultimate Obedient Fiend
  0x0330, // Ultimate Offering
  0x0331, // United We Stand
  0x035C, // Upstart Goblin
  0x047F, // Uria, Lord of Searing Flames
  0x0456, // Valhalla, Hall of the Fallen
  0x0372, // Vampire Baby
  0x03DA, // Vengeful Bog Spirit
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
  0x036A, // Warrior of Zera
  0x056C, // Watapon
  0x0332, // Wave Motion Cannon
  0x0369, // Weather Report
  0x056D, // White Dragon Ritual
  0x0367, // White Magician Pikeru
  0x056E, // Wild Nature's Release
  0x03DC, // World Suppression
  0x056F, // Wroughtweiler
  0x035B, // Yata-Garasu
  0x0570, // Yellow Gadget
  0x045C, // Yubel
  0x045D, // Yubel - Terror Incarnate
  0x045E, // Yubel - The Ultimate Nightmare
  0x03D4, // Zaborg the Thunder Monarch
  0x044F, // Zeriel
};

static const u16 sCustomCardNameSortOrder[NUM_CUSTOM_NAME_SORT_CARDS] APPEND_RODATA = {
  1, // A Hero Emerges
  2, // A Hero Lives
  3, // A Legendary Ocean
  4, // A Wingbeat of Giant Dragon
  5, // Absorbing Kid from the Sky
  6, // Airknight Parshath
  7, // Allure of Darkness
  8, // Alluring Mirror Split
  9, // Amazoness Archer
  10, // Amazoness Tiger
  11, // Ambush Fangs
  12, // Amphibious Bugroth MK-3
  13, // Amulet Dragon
  14, // Ancient Rules
  15, // Andro Sphinx
  16, // Angel's Tear
  17, // Anti-Spell Fragrance
  18, // Apparition
  19, // Apprentice Illusion Magician
  20, // Appropriate
  21, // Arcanite Magician
  22, // Archlord Kristya
  23, // Armageddon Knight
  24, // Armed Dragon LV10
  25, // Armed Dragon LV3
  26, // Armed Dragon LV5
  27, // Armed Dragon LV7
  28, // Armory Arm
  29, // Aroma Blend
  30, // Aroma Garden
  31, // Aroma Gardening
  32, // Aroma Jar
  33, // Aromage Bergamot
  34, // Aromage Cananga
  35, // Aromage Jasmine
  36, // Aromage Laurel
  37, // Aromage Marjoram
  38, // Aromage Rosemary
  39, // Aromalilith Magnolia
  40, // Aromalilith Rosalina
  41, // Aromalilith Rosemary
  42, // Aromaseraphy Jasmine
  43, // Aromaseraphy Rosemary
  44, // Aromaseraphy Sweet Marjoram
  45, // Arsenal Bug
  46, // Athena
  47, // Attack and Receive
  48, // Attack Guidance Armor
  49, // Attack Pheromones
  50, // Attack Reflector Unit
  51, // Autonomous Action Unit
  52, // Azure-Eyes Silver Dragon
  53, // Backfire
  54, // Backup Squad
  55, // Battle Footballer
  56, // Berserk Gorilla
  57, // Berserker Soul
  58, // Big Bang Shot
  59, // Birdface
  60, // Black Luster Soldier - Envoy of the Beginning
  61, // Black Rose Dragon
  62, // Black Tyranno
  63, // Blast Held by a Tribute
  64, // Blasting The Ruins
  65, // Blessed Winds
  66, // Block Attack
  67, // Blowback Dragon
  68, // Blue-Eyes Alternative Ultimate Dragon
  69, // Blue-Eyes Alternative White Dragon
  70, // Blue-Eyes Chaos Dragon
  71, // Blue-Eyes Chaos Max Dragon
  72, // Blue-Eyes Jet Dragon
  73, // Blue-Eyes Shining Dragon
  74, // Blue-Eyes Solid Dragon
  75, // Blue-Eyes Spirit Dragon
  76, // Blue-Eyes Tyrant Dragon
  77, // Blue-Eyes Ultimate Spirit Dragon
  78, // Bond Between Teacher and Student
  79, // Book of Life
  80, // Book of Moon
  81, // Book of Taiyou
  82, // Bottomless Shifting Sand
  83, // Bowganian
  84, // Break the Destiny
  85, // Breaker the Magical Warrior
  86, // Brionac, Dragon of the Ice Barrier
  87, // Bubble Blaster
  88, // Burden of the Mighty
  89, // Burning Algae
  90, // Burning Land
  91, // Caius the Shadow Monarch
  92, // Call of the Haunted
  93, // Call of the Mummy
  94, // Cannonball Spear Shellfish
  95, // Card Destruction
  96, // Card Of Demise
  97, // Card Of Sanctity
  98, // Cat's Ear Tribe
  99, // Celestial Sword - Eatos
  100, // Chain Energy
  101, // Chain Material
  102, // Chaos Command Magician
  103, // Chaos Emperor Dragon - Envoy of the End
  104, // Chaos Form
  105, // Chaos Greed
  106, // Chicken Game
  107, // Chimeratech Fortress Dragon
  108, // Chimeratech Megafleet Dragon
  109, // Chimeratech Overdragon
  110, // Chimeratech Rampage Dragon
  111, // Clock Tower Prison
  112, // Coffin Seller
  113, // Cold Wave
  114, // Colossal Fighter
  115, // Confiscation
  116, // Continuous Destruction Punch
  117, // Copycat
  118, // Cost Down
  119, // Court of Justice
  120, // Creature Swap
  121, // Cup of Ace
  122, // Cure Mermaid
  123, // Curse Of Darkness
  124, // Cyber Barrier Dragon
  125, // Cyber Dragon
  126, // Cyber Eltanin
  127, // Cyber End Dragon
  128, // Cyber Kirin
  129, // Cyber Laser Dragon
  130, // Cyber Phoenix
  131, // Cyber Slash Harpie Lady
  132, // Cyber Twin Dragon
  133, // Cyber Valley
  134, // Cybernetic Fusion Support
  135, // Cybernetic Zone
  136, // D - Burst
  137, // D - Force
  138, // D - Tactics
  139, // D - Time
  140, // D.D. Warrior
  141, // Damage = Reptile
  142, // Damage Polarizer
  143, // Dancing Fairy
  144, // Dark Armed Dragon
  145, // Dark Blade the Dragon Knight
  146, // Dark Burning Attack
  147, // Dark Burning Magic
  148, // Dark Calling
  149, // Dark City at Midnight
  150, // Dark Contact
  151, // Dark Driceratops
  152, // Dark Dust Spirit
  153, // Dark End Dragon
  154, // Dark Fusion
  155, // Dark Grepher
  156, // Dark Magic Attack
  157, // Dark Magic Curtain
  158, // Dark Magic Inheritance
  159, // Dark Magic Veil
  160, // Dark Magical Circle
  161, // Dark Magician Girl the Dragon Knight
  162, // Dark Magician Girl the Magician's Apprentice
  163, // Dark Magician of Chaos
  164, // Dark Magician of Destruction
  165, // Dark Magician the Dragon Knight
  166, // Dark Magician the Magician of Black Magic
  167, // Dark Renewal
  168, // Dark Room Of Nightmare
  169, // Dark Snake Syndrome
  170, // Dark Strike Fighter
  171, // Dark Supremacy
  172, // Darklord Marie
  173, // Darklord Nurse Reficule
  174, // Darkness Neosphere
  175, // De-Fusion
  176, // Deck Destruction Virus
  177, // Decoy Dragon
  178, // Dedication through Light and Darkness
  179, // Deep-Eyes White Dragon
  180, // Delinquent Duo
  181, // Des Counterblow
  182, // Des Kangaroo
  183, // Des Koala
  184, // Despair from the Dark
  185, // Destined Rivals
  186, // Destiny Draw
  187, // Destiny End Dragoon
  188, // Destiny HERO - Blade Master
  189, // Destiny HERO - Captain Tenacious
  190, // Destiny HERO - Celestial
  191, // Destiny HERO - Dangerous
  192, // Destiny HERO - Dark Angel
  193, // Destiny HERO - Dasher
  194, // Destiny HERO - Decider
  195, // Destiny HERO - Defender
  196, // Destiny HERO - Denier
  197, // Destiny HERO - Destro-Dogma
  198, // Destiny HERO - Destroyer Phoenix Enforcer
  199, // Destiny HERO - Diamond Dude
  200, // Destiny HERO - Disk Commander
  201, // Destiny HERO - Dogma
  202, // Destiny HERO - Dominance
  203, // Destiny HERO - Doom Lord
  204, // Destiny HERO - Doom Overlord
  205, // Destiny HERO - Double Dude
  206, // Destiny HERO - Drawhand
  207, // Destiny HERO - Dread Servant
  208, // Destiny HERO - Dreadmaster
  209, // Destiny HERO - Dreadnought Master
  210, // Destiny HERO - Dreadnought Servant
  211, // Destiny HERO - Dreamer
  212, // Destiny HERO - Drilldark
  213, // Destiny HERO - Dunker
  214, // Destiny HERO - Dusktopia
  215, // Destiny HERO - Dynatag
  216, // Destiny HERO - Dystopia
  217, // Destiny HERO - Fear Monger
  218, // Destiny HERO - Malicious
  219, // Destiny HERO - Plasma
  220, // Dice Jar
  221, // Different Dimension Capsule
  222, // Diffusion Wave-Motion
  223, // Dimension Fusion
  224, // Divine Sanctuary
  225, // Divine Serpent Geh
  226, // Doctor D
  227, // Don Zaloog
  228, // Doom Virus Dragon
  229, // Doppelganger
  230, // Double Coston
  231, // Double Spell
  232, // Double Summon
  233, // Dragon Master Magia
  234, // Dragon Ravine
  235, // Dragon Shrine
  236, // Dragon Spirit of White
  237, // Dragon's Rage
  238, // Drain Time
  239, // Draining Shield
  240, // Dried Winds
  241, // Drillago
  242, // Drop Off
  243, // Dust Tornado
  244, // E - Emergency Call
  245, // Ebon Illusion Magician
  246, // Ebon Magician Curran
  247, // Ectoplasmer
  248, // Egyptian God Slime
  249, // El Shaddoll Anoyatyllis
  250, // El Shaddoll Apkallone
  251, // El Shaddoll Construct
  252, // El Shaddoll Fusion
  253, // El Shaddoll Grysta
  254, // El Shaddoll Meshahrail
  255, // El Shaddoll Shekhinaga
  256, // El Shaddoll Wendigo
  257, // El Shaddoll Winda
  258, // Elemental HERO Absolute Zero
  259, // Elemental HERO Avian
  260, // Elemental HERO Bladedge
  261, // Elemental HERO Blazeman
  262, // Elemental HERO Bubbleman
  263, // Elemental HERO Burstinatrix
  264, // Elemental HERO Captain Gold
  265, // Elemental HERO Clayman
  266, // Elemental HERO Core
  267, // Elemental HERO Electrum
  268, // Elemental HERO Escuridao
  269, // Elemental HERO Flame Wingman
  270, // Elemental HERO Flash
  271, // Elemental HERO Gaia
  272, // Elemental HERO Great Tornado
  273, // Elemental HERO Heat
  274, // Elemental HERO Ice Edge
  275, // Elemental HERO Inferno
  276, // Elemental HERO Knospe
  277, // Elemental HERO Lady Heat
  278, // Elemental HERO Mariner
  279, // Elemental HERO Mudballman
  280, // Elemental HERO Necroid Shaman
  281, // Elemental HERO Necroshade
  282, // Elemental HERO Neos
  283, // Elemental HERO Neos Alius
  284, // Elemental HERO Neos Kluger
  285, // Elemental HERO Ocean
  286, // Elemental HERO Phoenix Enforcer
  287, // Elemental HERO Plasma Vice
  288, // Elemental HERO Poison Rose
  289, // Elemental HERO Rampart Blaster
  290, // Elemental HERO Shining Flare Wingman
  291, // Elemental HERO Shining Phoenix Enforcer
  292, // Elemental HERO Sparkman
  293, // Elemental HERO Steam Healer
  294, // Elemental HERO Stratos
  295, // Elemental HERO Sunrise
  296, // Elemental HERO Tempest
  297, // Elemental HERO Terra Firma
  298, // Elemental HERO The Shining
  299, // Elemental HERO Thunder Giant
  300, // Elemental HERO Voltic
  301, // Elemental HERO Wild Wingman
  302, // Elemental HERO Wildedge
  303, // Elemental HERO Wildheart
  304, // Elemental HERO Woodsman
  305, // Emergency Provisions
  306, // Eternal Soul
  307, // Evil Assault
  308, // Evil Dragon Ananta
  309, // Evil HERO Adusted Gold
  310, // Evil HERO Dark Gaia
  311, // Evil HERO Darkest Knight
  312, // Evil HERO Dead-End Prison
  313, // Evil HERO Infernal Gainer
  314, // Evil HERO Infernal Prodigy
  315, // Evil HERO Infernal Rider
  316, // Evil HERO Infernal Sniper
  317, // Evil HERO Inferno Wing
  318, // Evil HERO Inferno Wing - Backfire
  319, // Evil HERO Lightning Golem
  320, // Evil HERO Malicious Bane
  321, // Evil HERO Malicious Edge
  322, // Evil HERO Malicious Fiend
  323, // Evil HERO Neos Lord
  324, // Evil HERO Sinister Necrom
  325, // Evil HERO Toxic Bubble
  326, // Evil HERO Vicious Claws
  327, // Evil HERO Wild Cyclone
  328, // Evil Mind
  329, // Exchange
  330, // Exodius the Ultimate Forbidden Lord
  331, // Fairy Box
  332, // Familiar Knight
  333, // Fatal Abacus
  334, // Felgrand Dragon
  335, // Fenrir
  336, // Fields Sanctuary
  337, // Final Countdown
  338, // Fire Princess
  339, // Fires of Doomsday
  340, // Forced Requisition
  341, // Fusion Deployment
  342, // Fusion Destiny
  343, // Fusion Gate
  344, // Fusion Recovery
  345, // Fusion Sage
  346, // Future Fusion
  347, // Gandora-G the Dragon of Destruction
  348, // Gandora-X the Dragon of Demolition
  349, // Gate Guardians Combined
  350, // Ghost Knight of Jackal
  351, // Gift Card
  352, // Gift Of The Mystical Elf
  353, // Gilasaurus
  354, // Goblin King
  355, // Goblin Thief
  356, // Goddess Bow
  357, // Gorz the Emissary of Darkness
  358, // Goyo Guardian
  359, // Graceful Charity
  360, // Graceful Dice
  361, // Granadora
  362, // Granmarg the Rock Monarch
  363, // Gravekeeper's Servant
  364, // Gravity Bind
  365, // Great Maju Garzett
  366, // Green Gadget
  367, // Gren Maju Da Eiza
  368, // Grinder Golem
  369, // Ground Collapse
  370, // Guardian Angel Joan
  371, // Guardian Dreadscythe
  372, // Guardian Eatos
  373, // Guardian Treasure
  374, // Gyaku-Gire Panda
  375, // H - Heated Heart
  376, // Hamon, Lord of Striking Thunder
  377, // Harpie Channeler
  378, // Harpie Conductor
  379, // Harpie Dancer
  380, // Harpie Harpist
  381, // Harpie Lady 1
  382, // Harpie Lady 2
  383, // Harpie Lady 3
  384, // Harpie Lady Elegance
  385, // Harpie Lady Phoenix Formation
  386, // Harpie Oracle
  387, // Harpie Perfumer
  388, // Harpie Queen
  389, // Harpie's Feather Rest
  390, // Harpie's Feather Storm
  391, // Harpie's Pet Baby Dragon
  392, // Harpie's Pet Phantasmal Dragon
  393, // Harpies' Hunting Ground
  394, // Hayabusa Knight
  395, // Hecatrice
  396, // Helshaddoll Hollow
  397, // Herald of Creation
  398, // Herald of Perfection
  399, // Herald of Ultimateness
  400, // Hero Flash!!
  401, // Hero Kid
  402, // Holactie the Creator of Light
  403, // Horus the Black Flame Dragon LV4
  404, // Horus the Black Flame Dragon LV6
  405, // Horus the Black Flame Dragon LV8
  406, // Humid Winds
  407, // Hyper Hammerhead
  408, // Hysteric Party
  409, // Hysteric Sign
  410, // Illusion Magic
  411, // Illusion of Chaos
  412, // Imperial Order
  413, // Insect Imitation
  414, // Instant Fusion
  415, // Invader of the Throne
  416, // Iofiel
  417, // Ipiria
  418, // Jar of Greed
  419, // Jar Robber
  420, // Jowgen the Spiritualist
  421, // Jowls of Dark Demise
  422, // Judgment Dragon
  423, // Junk Warrior
  424, // Just Deserts
  425, // KA-2 Des Scissors
  426, // Kaibaman
  427, // Kaiser Colosseum
  428, // Kaiser Glider
  429, // Keeper of Dragon Magic
  430, // King Dragun
  431, // King of the Swamp
  432, // King Tiger Wanghu
  433, // Kishido Spirit
  434, // Knight's Title
  435, // Kuraz the Light Monarch
  436, // Kuribandit
  437, // Last Turn
  438, // Legend of Heart
  439, // Legendary Flame Lord
  440, // Legendary Knight Critias
  441, // Legendary Knight Hermos
  442, // Legendary Knight Timaeus
  443, // Legendary Maju Garzett
  444, // Lekunga
  445, // Lesser Fiend
  446, // Lev Shaddoll Fusion
  447, // Level Limit - Area A
  448, // Level Limit Area B
  449, // Levia Dragon Daedalus
  450, // Light and Darkness Dragon
  451, // Light End Dragon
  452, // Lightning Warrior
  453, // Lightserpent
  454, // Limiter Removal
  455, // Lonefire Blossom
  456, // Lord of the Red
  457, // Luster Dragon
  458, // Lyrilusc - Independent Nightingale
  459, // Ma'at
  460, // Mad Sword Beast
  461, // Mage Power
  462, // Magic Cylinder
  463, // Magic Jammer
  464, // Magical Dimension
  465, // Magical Hats
  466, // Magical Merchant
  467, // Magical Plant Mandragola
  468, // Magical Scientist
  469, // Magical Stone Excavation
  470, // Magician Navigation
  471, // Magician of Dark Illusion
  472, // Magician's Robe
  473, // Magician's Rod
  474, // Magician's Valkyria
  475, // Magicians' Combination
  476, // Magicians' Souls
  477, // Majestic Mech - Goryu
  478, // Maju Garzett
  479, // Man-Thro-Thro
  480, // Manju of the Ten Thousand Hands
  481, // Marauding Captain
  482, // Marshmallon
  483, // Maryokutai
  484, // Mask of Dispel
  485, // Mask of Restrict
  486, // Mask of the Accursed
  487, // Master of Chaos
  488, // Master Peace, the True Dracoslaying King
  489, // Mataza the Zapper
  490, // Mausoleum of the Emperor
  491, // Mazera DeVille
  492, // Mefist The Infernal General
  493, // Mermaid Knight
  494, // Metamorphosis
  495, // Metaverse
  496, // Meteor of Destruction
  497, // Meteorain
  498, // Mighty Angel Virch
  499, // Millennium-Eyes Restrict
  500, // Miracle Fusion
  501, // Mirage of Nightmare
  502, // Mirror Force
  503, // Mirror Force Dragon
  504, // Mirror Wall
  505, // Mobius the Frost Monarch
  506, // Moister Creature
  507, // Molten Zombie
  508, // Molting Escape
  509, // Monster Gate
  510, // Monster Recovery
  511, // Morale Boost
  512, // Mucus Yolk
  513, // Mystic Mine
  514, // Mystical Shine Ball
  515, // Mystical Space Typhoon
  516, // Mystik Wok
  517, // Naelshaddoll Ariel
  518, // Necrovalley
  519, // Needle Burrower
  520, // Needle Wall
  521, // Negate Attack
  522, // Negative Energy
  523, // Nehshaddoll Genius
  524, // Neo Blue-Eyes Ultimate Dragon
  525, // Neos Wiseman
  526, // Nephe Shaddoll Fusion
  527, // Neutron Blast
  528, // Nibiru, the Primal Being
  529, // Nightmare Horse
  530, // Nightmare Wheel
  531, // Numinous Healer
  532, // O - Oversoul
  533, // Obnoxious Celtic Guardian
  534, // Offering to the Snake Deity
  535, // Ojama King
  536, // Ojama Trio
  537, // Orichalcos Shunoros
  538, // Oshaleon
  539, // Over Destiny
  540, // Overload Fusion
  541, // Painful Choice
  542, // Paladin Of White Dragon
  543, // Pandemonium
  544, // Parallel World Fusion
  545, // Peten The Dark Clown
  546, // Photon Generator Unit
  547, // Piranha Army
  548, // Poison of the Old Man
  549, // Polymerization
  550, // Possessed Dark Soul
  551, // Power Bond
  552, // Power Tool Dragon
  553, // Precious Cards From Beyond
  554, // Predaplant Verte Anaconda
  555, // Premature Burial
  556, // Prophecy
  557, // Protector of the Sanctuary
  558, // Proto-Cyber Dragon
  559, // Pyramid of Light
  560, // Qadshaddoll Keios
  561, // Quintet Magician
  562, // R - Righteous Justice
  563, // Raigeki Break
  564, // Rain of Mercy
  565, // Rare Metal Dragon
  566, // Raregold Armor
  567, // Raviel, Lord of Phantasms
  568, // Reaper on the Nightmare
  569, // Reaper Scythe - Dreadscythe
  570, // Reckless Greed
  571, // Red Dragon Archfiend
  572, // Red Gadget
  573, // Red Reboot
  574, // Red-Eyes Black Dragon Sword
  575, // Red-Eyes Dark Dragoon
  576, // Red-Eyes Darkness Metal Dragon
  577, // Red-Eyes Transmigration
  578, // Reeshaddoll Wendi
  579, // Reeshaddoll Wendikurhu
  580, // Relay Soul
  581, // Reload
  582, // Reptilianne Echidna
  583, // Reptilianne Gardna
  584, // Reptilianne Gorgon
  585, // Reptilianne Hydra
  586, // Reptilianne Lamia
  587, // Reptilianne Medusa
  588, // Reptilianne Naga
  589, // Reptilianne Poison
  590, // Reptilianne Rage
  591, // Reptilianne Scylla
  592, // Reptilianne Servant
  593, // Reptilianne Spawn
  594, // Reptilianne Vaskii
  595, // Reptilianne Viper
  596, // Return of the Dragon Lords
  597, // Reverse of Reverse
  598, // Ring of Destruction
  599, // Riryoku
  600, // Rise of the Snake Deity
  601, // Rivalry of Warlords
  602, // Robbin' Goblin
  603, // Robbin' Zombie
  604, // Rocket Hermos Cannon
  605, // Rope of Life
  606, // Royal Decree
  607, // Royal Knight
  608, // Royal Magical Library
  609, // Ryu-Kishin Clown
  610, // Sage's Stone
  611, // Sasuke Samurai
  612, // Sasuke Samurai #2
  613, // Sasuke Samurai #3
  614, // Scapegoat
  615, // Seal of Orichalcos
  616, // Second Coin Toss
  617, // Secret Barrel
  618, // Secret Village of the Spellcasters
  619, // Secrets of Dark Magic
  620, // Self-Destruct Button
  621, // Seraphim Blaster
  622, // Serpent Suppression
  623, // Servant of Catabolism
  624, // Seven Tools of the Bandit
  625, // Shaddoll Beast
  626, // Shaddoll Core
  627, // Shaddoll Dragon
  628, // Shaddoll Falco
  629, // Shaddoll Fusion
  630, // Shaddoll Hedgehog
  631, // Shaddoll Hound
  632, // Shaddoll Schism
  633, // Shaddoll Squamata
  634, // Share the Pain
  635, // Shatiel
  636, // Shield And Sword
  637, // Silver's Cry
  638, // Sixth Sense
  639, // Skill Drain
  640, // Skilled Dark Magician
  641, // Skilled White Magician
  642, // Skull Invitation
  643, // Skyscraper
  644, // Skyscraper 2 - Hero City
  645, // Snake Deity's Command
  646, // Solar Flare Dragon
  647, // Solar Ray
  648, // Solemn Judgment
  649, // Solemn Wishes
  650, // Sorcerer of Dark Magic
  651, // Soul Exchange
  652, // Soul Taker
  653, // Spark Blaster
  654, // Spear Dragon
  655, // Spell Absorption
  656, // Spell Canceller
  657, // Spell Economics
  658, // Sphinx Teleia
  659, // Spirit Caller
  660, // Spirit of the Breeze
  661, // Spirit of the Pot of Greed
  662, // Spirit Reaper
  663, // Spirit Ryu
  664, // St Joan
  665, // Statue of the Wicked
  666, // Staunch Defender
  667, // Stealth Bird
  668, // Stray Lambs
  669, // Stronghold the Moving Fortress
  670, // Summoner Monk
  671, // Summoner of Illusions
  672, // Super Polymerization
  673, // Swift Gaia The Fierce Knight
  674, // Terraforming
  675, // Terrorking Salmon
  676, // Tethys, Goddess of Light
  677, // The A. Forces
  678, // The Agent Of Creation - Venus
  679, // The Agent of Force - Mars
  680, // The Agent of Judgment - Saturn
  681, // The Agent of Wisdom - Mercury
  682, // The Big Saturn
  683, // The Blazing Mars
  684, // The Claw of Hermos
  685, // The Creator
  686, // The Creator Incarnate
  687, // The Dark Door
  688, // The Despair Uranus
  689, // The Eye of Timaeus
  690, // The Fang of Critias
  691, // The Flute of Summoning Dragon
  692, // The Forceful Sentry
  693, // The Grand Jupiter
  694, // The Law of the Normal
  695, // The Legendary Exodia Incarnate
  696, // The Sanctuary in the Sky
  697, // The Shallow Grave
  698, // The Splendid Venus
  699, // The Suppression Pluto
  700, // The Supremacy Sun
  701, // The Thing in the Crater
  702, // The Tricky
  703, // The Tripper Mercury
  704, // The Tyrant Neptune
  705, // The Unstoppable Exodia Incarnate
  706, // The Wicked Avatar
  707, // The Wicked Dreadroot
  708, // The Wicked Eraser
  709, // Theban Nightmare
  710, // Theinen the Great Sphinx
  711, // Thestalos the Firestorm Monarch
  712, // Thousand Energy
  713, // Thousand Knives
  714, // Thunder Crash
  715, // Thunder Dragon Colossus
  716, // Thunder Dragon Titan
  717, // Timaeus the Knight of Destiny
  718, // Time Magic Hammer
  719, // Time Seal
  720, // Tiny Angel
  721, // Toll
  722, // Toon World
  723, // Tornado Bird
  724, // Tornado Wall
  725, // Torpedo Fish
  726, // Trade-In
  727, // Trap Dustshoot
  728, // Triangle Power
  729, // Tribute Doll
  730, // Twin Swords of Flashing Light - Tryce
  731, // Tyrant Burst Dragon
  732, // Tyrant Dragon
  733, // Tyrant Wing
  734, // Ultimate Conductor Tyranno
  735, // Ultimate Obedient Fiend
  736, // Ultimate Offering
  737, // United We Stand
  738, // Upstart Goblin
  739, // Uria, Lord of Searing Flames
  740, // Valhalla, Hall of the Fallen
  741, // Vampire Baby
  742, // Vengeful Bog Spirit
  743, // Vision Fusion
  744, // Vision HERO Adoration
  745, // Vision HERO Faris
  746, // Vision HERO Gravito
  747, // Vision HERO Increase
  748, // Vision HERO Minimum Ray
  749, // Vision HERO Multiply Guy
  750, // Vision HERO Poisoner
  751, // Vision HERO Trinity
  752, // Vision HERO Vyon
  753, // Vision HERO Witch Raider
  754, // Vision Release
  755, // Wall of Revealing Light
  756, // Warrior of Zera
  757, // Watapon
  758, // Wave Motion Cannon
  759, // Weather Report
  760, // White Dragon Ritual
  761, // White Magician Pikeru
  762, // Wild Nature's Release
  763, // World Suppression
  764, // Wroughtweiler
  765, // Yata-Garasu
  766, // Yellow Gadget
  767, // Yubel
  768, // Yubel - Terror Incarnate
  769, // Yubel - The Ultimate Nightmare
  770, // Zaborg the Thunder Monarch
  771, // Zeriel
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

  return gCardNames[cardId];
}

static u16 GetCustomCardNameSortOrder(u16 cardId) {
  u16 i;

  for (i = 0; i < NUM_CUSTOM_NAME_SORT_CARDS; i++)
    if (sCustomCardsByName[i] == cardId)
      return sCustomCardNameSortOrder[i];

  return 0;
}
