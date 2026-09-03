#include "global.h"

static const unsigned char sSenjuOfTheThousandHandsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/senju_of_the_thousand_hands.huff");
static const unsigned short sSenjuOfTheThousandHandsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/senju_of_the_thousand_hands.gbapal");
static const unsigned char sSenjuOfTheThousandHandsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/senju_of_the_thousand_hands.lz");

static const unsigned char sBlackPendantBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/black_pendant.huff");
static const unsigned short sBlackPendantBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/black_pendant.gbapal");
static const unsigned char sBlackPendantMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/black_pendant.lz");

static const unsigned char sTheBistroButcherBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_bistro_butcher.huff");
static const unsigned short sTheBistroButcherBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_bistro_butcher.gbapal");
static const unsigned char sTheBistroButcherMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_bistro_butcher.lz");

static const unsigned char sBlueEyesShiningDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_shining_dragon.huff");
static const unsigned short sBlueEyesShiningDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_shining_dragon.gbapal");
static const unsigned char sBlueEyesShiningDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_shining_dragon.lz");

static const unsigned char sBlueEyesChaosMaxDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_chaos_max_dragon.huff");
static const unsigned short sBlueEyesChaosMaxDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_chaos_max_dragon.gbapal");
static const unsigned char sBlueEyesChaosMaxDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_chaos_max_dragon.lz");

static const unsigned char sKaibamanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/kaibaman.huff");
static const unsigned short sKaibamanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/kaibaman.gbapal");
static const unsigned char sKaibamanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/kaibaman.lz");

static const unsigned char sUltimateOfferingBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ultimate_offering.huff");
static const unsigned short sUltimateOfferingBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ultimate_offering.gbapal");
static const unsigned char sUltimateOfferingMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ultimate_offering.lz");

static const unsigned char sWaveMotionCannonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/wave_motion_cannon.huff");
static const unsigned short sWaveMotionCannonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/wave_motion_cannon.gbapal");
static const unsigned char sWaveMotionCannonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/wave_motion_cannon.lz");

static const unsigned char sSoulExchangeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/soul_exchange.huff");
static const unsigned short sSoulExchangeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/soul_exchange.gbapal");
static const unsigned char sSoulExchangeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/soul_exchange.lz");

static const unsigned char sMysticalSpaceTyphoonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mystical_space_typhoon.huff");
static const unsigned short sMysticalSpaceTyphoonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mystical_space_typhoon.gbapal");
static const unsigned char sMysticalSpaceTyphoonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mystical_space_typhoon.lz");

static const unsigned char sRareMetalDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/rare_metal_dragon.huff");
static const unsigned short sRareMetalDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/rare_metal_dragon.gbapal");
static const unsigned char sRareMetalDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/rare_metal_dragon.lz");

static const unsigned char sMaskOfRestrictBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mask_of_restrict.huff");
static const unsigned short sMaskOfRestrictBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mask_of_restrict.gbapal");
static const unsigned char sMaskOfRestrictMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mask_of_restrict.lz");

static const unsigned char sBlueEyesAlternativeWhiteDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_alternative_white_dragon.huff");
static const unsigned short sBlueEyesAlternativeWhiteDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_alternative_white_dragon.gbapal");
static const unsigned char sBlueEyesAlternativeWhiteDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_alternative_white_dragon.lz");

static const unsigned char sSealOfOrichalcosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/seal_of_orichalcos.huff");
static const unsigned short sSealOfOrichalcosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/seal_of_orichalcos.gbapal");
static const unsigned char sSealOfOrichalcosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/seal_of_orichalcos.lz");

static const unsigned char sSkillDrainBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/skill_drain.huff");
static const unsigned short sSkillDrainBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/skill_drain.gbapal");
static const unsigned char sSkillDrainMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/skill_drain.lz");

static const unsigned char sMagicCylinderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magic_cylinder.huff");
static const unsigned short sMagicCylinderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magic_cylinder.gbapal");
static const unsigned char sMagicCylinderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magic_cylinder.lz");

static const unsigned char sDelinquentDuoBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/delinquent_duo.huff");
static const unsigned short sDelinquentDuoBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/delinquent_duo.gbapal");
static const unsigned char sDelinquentDuoMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/delinquent_duo.lz");

static const unsigned char sYataGarasuBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/yata_garasu.huff");
static const unsigned short sYataGarasuBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/yata_garasu.gbapal");
static const unsigned char sYataGarasuMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/yata_garasu.lz");

static const unsigned char sUpstartGoblinBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/upstart_goblin.huff");
static const unsigned short sUpstartGoblinBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/upstart_goblin.gbapal");
static const unsigned char sUpstartGoblinMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/upstart_goblin.lz");

static const unsigned char sCallOfTheHauntedBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/call_of_the_haunted.huff");
static const unsigned short sCallOfTheHauntedBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/call_of_the_haunted.gbapal");
static const unsigned char sCallOfTheHauntedMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/call_of_the_haunted.lz");

static const unsigned char sSwiftGaiaTheFierceKnightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/swift_gaia_the_fierce_knight.huff");
static const unsigned short sSwiftGaiaTheFierceKnightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/swift_gaia_the_fierce_knight.gbapal");
static const unsigned char sSwiftGaiaTheFierceKnightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/swift_gaia_the_fierce_knight.lz");

static const unsigned char sLimiterRemovalBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/limiter_removal.huff");
static const unsigned short sLimiterRemovalBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/limiter_removal.gbapal");
static const unsigned char sLimiterRemovalMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/limiter_removal.lz");

static const unsigned char sRecklessGreedBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reckless_greed.huff");
static const unsigned short sRecklessGreedBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reckless_greed.gbapal");
static const unsigned char sRecklessGreedMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reckless_greed.lz");

static const unsigned char sCardDestructionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/card_destruction.huff");
static const unsigned short sCardDestructionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/card_destruction.gbapal");
static const unsigned char sCardDestructionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/card_destruction.lz");

static const unsigned char sGracefulCharityBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/graceful_charity.huff");
static const unsigned short sGracefulCharityBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/graceful_charity.gbapal");
static const unsigned char sGracefulCharityMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/graceful_charity.lz");

static const unsigned char sImperialOrderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/imperial_order.huff");
static const unsigned short sImperialOrderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/imperial_order.gbapal");
static const unsigned char sImperialOrderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/imperial_order.lz");

static const unsigned char sRoyalDecreeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/royal_decree.huff");
static const unsigned short sRoyalDecreeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/royal_decree.gbapal");
static const unsigned char sRoyalDecreeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/royal_decree.lz");

static const unsigned char sDoubleCostonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/double_coston.huff");
static const unsigned short sDoubleCostonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/double_coston.gbapal");
static const unsigned char sDoubleCostonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/double_coston.lz");

static const unsigned char sFinalCountdownBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/final_countdown.huff");
static const unsigned short sFinalCountdownBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/final_countdown.gbapal");
static const unsigned char sFinalCountdownMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/final_countdown.lz");

static const unsigned char sBookOfMoonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/book_of_moon.huff");
static const unsigned short sBookOfMoonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/book_of_moon.gbapal");
static const unsigned char sBookOfMoonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/book_of_moon.lz");

static const unsigned char sAmazonessTigerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/amazoness_tiger.huff");
static const unsigned short sAmazonessTigerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/amazoness_tiger.gbapal");
static const unsigned char sAmazonessTigerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/amazoness_tiger.lz");

static const unsigned char sConfiscationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/confiscation.huff");
static const unsigned short sConfiscationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/confiscation.gbapal");
static const unsigned char sConfiscationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/confiscation.lz");

static const unsigned char sZaborgTheThunderMonarchBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/zaborg_the_thunder_monarch.huff");
static const unsigned short sZaborgTheThunderMonarchBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/zaborg_the_thunder_monarch.gbapal");
static const unsigned char sZaborgTheThunderMonarchMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/zaborg_the_thunder_monarch.lz");

static const unsigned char sPolymerizationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/polymerization.huff");
static const unsigned short sPolymerizationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/polymerization.gbapal");
static const unsigned char sPolymerizationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/polymerization.lz");

static const unsigned char sCyberDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cyber_dragon.huff");
static const unsigned short sCyberDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cyber_dragon.gbapal");
static const unsigned char sCyberDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cyber_dragon.lz");

static const unsigned char sCyberTwinDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cyber_twin_dragon.huff");
static const unsigned short sCyberTwinDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cyber_twin_dragon.gbapal");
static const unsigned char sCyberTwinDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cyber_twin_dragon.lz");

static const unsigned char sCyberEndDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cyber_end_dragon.huff");
static const unsigned short sCyberEndDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cyber_end_dragon.gbapal");
static const unsigned char sCyberEndDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cyber_end_dragon.lz");

static const unsigned char sCaiusTheShadowMonarchBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/caius_the_shadow_monarch.huff");
static const unsigned short sCaiusTheShadowMonarchBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/caius_the_shadow_monarch.gbapal");
static const unsigned char sCaiusTheShadowMonarchMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/caius_the_shadow_monarch.lz");

static const unsigned char sMobiusTheFrostMonarchBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mobius_the_frost_monarch.huff");
static const unsigned short sMobiusTheFrostMonarchBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mobius_the_frost_monarch.gbapal");
static const unsigned char sMobiusTheFrostMonarchMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mobius_the_frost_monarch.lz");

static const unsigned char sProtoCyberDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/proto_cyber_dragon.huff");
static const unsigned short sProtoCyberDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/proto_cyber_dragon.gbapal");
static const unsigned char sProtoCyberDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/proto_cyber_dragon.lz");

static const unsigned char sAmazonessArcherBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/amazoness_archer.huff");
static const unsigned short sAmazonessArcherBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/amazoness_archer.gbapal");
static const unsigned char sAmazonessArcherMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/amazoness_archer.lz");

static const unsigned char sElementalHeroWildheartBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_wildheart.huff");
static const unsigned short sElementalHeroWildheartBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_wildheart.gbapal");
static const unsigned char sElementalHeroWildheartMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_wildheart.lz");

static const unsigned char sTheSanctuaryInTheSkyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_sanctuary_in_the_sky.huff");
static const unsigned short sTheSanctuaryInTheSkyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_sanctuary_in_the_sky.gbapal");
static const unsigned char sTheSanctuaryInTheSkyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_sanctuary_in_the_sky.lz");

static const unsigned char sMirrorForceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mirror_force.huff");
static const unsigned short sMirrorForceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mirror_force.gbapal");
static const unsigned char sMirrorForceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mirror_force.lz");

static const unsigned char sBlueEyesChaosDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_chaos_dragon.huff");
static const unsigned short sBlueEyesChaosDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_chaos_dragon.gbapal");
static const unsigned char sBlueEyesChaosDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_chaos_dragon.lz");

static const unsigned char sDeFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/de_fusion.huff");
static const unsigned short sDeFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/de_fusion.gbapal");
static const unsigned char sDeFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/de_fusion.lz");

static const unsigned char sALegendaryOceanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/a_legendary_ocean.huff");
static const unsigned short sALegendaryOceanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/a_legendary_ocean.gbapal");
static const unsigned char sALegendaryOceanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/a_legendary_ocean.lz");

static const unsigned char sDarkMagicianOfChaosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_magician_of_chaos.huff");
static const unsigned short sDarkMagicianOfChaosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_magician_of_chaos.gbapal");
static const unsigned char sDarkMagicianOfChaosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_magician_of_chaos.lz");

static const unsigned char sElementalHeroPhoenixEnforcerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_phoenix_enforcer.huff");
static const unsigned short sElementalHeroPhoenixEnforcerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_phoenix_enforcer.gbapal");
static const unsigned char sElementalHeroPhoenixEnforcerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_phoenix_enforcer.lz");

static const unsigned char sElementalHeroFlameWingmanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_flame_wingman.huff");
static const unsigned short sElementalHeroFlameWingmanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_flame_wingman.gbapal");
static const unsigned char sElementalHeroFlameWingmanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_flame_wingman.lz");

static const unsigned char sElementalHeroShiningFlareWingmanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_shining_flare_wingman.huff");
static const unsigned short sElementalHeroShiningFlareWingmanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_shining_flare_wingman.gbapal");
static const unsigned char sElementalHeroShiningFlareWingmanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_shining_flare_wingman.lz");

static const unsigned char sMiracleFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/miracle_fusion.huff");
static const unsigned short sMiracleFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/miracle_fusion.gbapal");
static const unsigned char sMiracleFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/miracle_fusion.lz");

static const unsigned char sChaosEmperorDragonEnvoyOfTheEndBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chaos_emperor_dragon_envoy_of_the_end.huff");
static const unsigned short sChaosEmperorDragonEnvoyOfTheEndBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chaos_emperor_dragon_envoy_of_the_end.gbapal");
static const unsigned char sChaosEmperorDragonEnvoyOfTheEndMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chaos_emperor_dragon_envoy_of_the_end.lz");

static const unsigned char sBlackLusterSoldierEnvoyOfTheBeginningBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/black_luster_soldier_envoy_of_the_beginning.huff");
static const unsigned short sBlackLusterSoldierEnvoyOfTheBeginningBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/black_luster_soldier_envoy_of_the_beginning.gbapal");
static const unsigned char sBlackLusterSoldierEnvoyOfTheBeginningMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/black_luster_soldier_envoy_of_the_beginning.lz");

static const unsigned char sElementalHeroNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_neos.huff");
static const unsigned short sElementalHeroNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_neos.gbapal");
static const unsigned char sElementalHeroNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_neos.lz");

static const unsigned char sFusionRecoveryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/fusion_recovery.huff");
static const unsigned short sFusionRecoveryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/fusion_recovery.gbapal");
static const unsigned char sFusionRecoveryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/fusion_recovery.lz");

static const unsigned char sSkyscraperBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/skyscraper.huff");
static const unsigned short sSkyscraperBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/skyscraper.gbapal");
static const unsigned char sSkyscraperMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/skyscraper.lz");

static const unsigned char sHHeatedHeartBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/h_heated_heart.huff");
static const unsigned short sHHeatedHeartBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/h_heated_heart.gbapal");
static const unsigned char sHHeatedHeartMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/h_heated_heart.lz");

static const unsigned char sEEmergencyCallBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/e_emergency_call.huff");
static const unsigned short sEEmergencyCallBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/e_emergency_call.gbapal");
static const unsigned char sEEmergencyCallMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/e_emergency_call.lz");

static const unsigned char sElementalHeroIceEdgeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_ice_edge.huff");
static const unsigned short sElementalHeroIceEdgeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_ice_edge.gbapal");
static const unsigned char sElementalHeroIceEdgeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_ice_edge.lz");

static const unsigned char sElementalHeroBlazemanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_blazeman.huff");
static const unsigned short sElementalHeroBlazemanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_blazeman.gbapal");
static const unsigned char sElementalHeroBlazemanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_blazeman.lz");

static const unsigned char sElementalHeroStratosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_stratos.huff");
static const unsigned short sElementalHeroStratosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_stratos.gbapal");
static const unsigned char sElementalHeroStratosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_stratos.lz");

static const unsigned char sChimeratechOverdragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chimeratech_overdragon.huff");
static const unsigned short sChimeratechOverdragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chimeratech_overdragon.gbapal");
static const unsigned char sChimeratechOverdragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chimeratech_overdragon.lz");

static const unsigned char sCyberneticFusionSupportBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cybernetic_fusion_support.huff");
static const unsigned short sCyberneticFusionSupportBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cybernetic_fusion_support.gbapal");
static const unsigned char sCyberneticFusionSupportMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cybernetic_fusion_support.lz");

static const unsigned char sOverloadFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/overload_fusion.huff");
static const unsigned short sOverloadFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/overload_fusion.gbapal");
static const unsigned char sOverloadFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/overload_fusion.lz");

static const unsigned char sPowerBondBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/power_bond.huff");
static const unsigned short sPowerBondBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/power_bond.gbapal");
static const unsigned char sPowerBondMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/power_bond.lz");

static const unsigned char sDivineSanctuaryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/divine_sanctuary.huff");
static const unsigned short sDivineSanctuaryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/divine_sanctuary.gbapal");
static const unsigned char sDivineSanctuaryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/divine_sanctuary.lz");

static const unsigned char sYubelBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/yubel.huff");
static const unsigned short sYubelBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/yubel.gbapal");
static const unsigned char sYubelMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/yubel.lz");

static const unsigned char sYubelTerrorIncarnateBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/yubel_terror_incarnate.huff");
static const unsigned short sYubelTerrorIncarnateBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/yubel_terror_incarnate.gbapal");
static const unsigned char sYubelTerrorIncarnateMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/yubel_terror_incarnate.lz");

static const unsigned char sYubelTheUltimateNightmareBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/yubel_the_ultimate_nightmare.huff");
static const unsigned short sYubelTheUltimateNightmareBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/yubel_the_ultimate_nightmare.gbapal");
static const unsigned char sYubelTheUltimateNightmareMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/yubel_the_ultimate_nightmare.lz");

static const unsigned char sTradeInBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/trade_in.huff");
static const unsigned short sTradeInBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/trade_in.gbapal");
static const unsigned char sTradeInMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/trade_in.lz");

static const unsigned char sCyberBarrierDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cyber_barrier_dragon.huff");
static const unsigned short sCyberBarrierDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cyber_barrier_dragon.gbapal");
static const unsigned char sCyberBarrierDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cyber_barrier_dragon.lz");

static const unsigned char sCyberLaserDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cyber_laser_dragon.huff");
static const unsigned short sCyberLaserDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cyber_laser_dragon.gbapal");
static const unsigned char sCyberLaserDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cyber_laser_dragon.lz");

static const unsigned char sDestinyHeroBladeMasterBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_blade_master.huff");
static const unsigned short sDestinyHeroBladeMasterBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_blade_master.gbapal");
static const unsigned char sDestinyHeroBladeMasterMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_blade_master.lz");

static const unsigned char sDestinyHeroCaptainTenaciousBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_captain_tenacious.huff");
static const unsigned short sDestinyHeroCaptainTenaciousBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_captain_tenacious.gbapal");
static const unsigned char sDestinyHeroCaptainTenaciousMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_captain_tenacious.lz");

static const unsigned char sDestinyHeroCelestialBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_celestial.huff");
static const unsigned short sDestinyHeroCelestialBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_celestial.gbapal");
static const unsigned char sDestinyHeroCelestialMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_celestial.lz");

static const unsigned char sDestinyHeroDangerousBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dangerous.huff");
static const unsigned short sDestinyHeroDangerousBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dangerous.gbapal");
static const unsigned char sDestinyHeroDangerousMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dangerous.lz");

static const unsigned char sDestinyHeroDasherBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dasher.huff");
static const unsigned short sDestinyHeroDasherBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dasher.gbapal");
static const unsigned char sDestinyHeroDasherMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dasher.lz");

static const unsigned char sDoomVirusDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/doom_virus_dragon.huff");
static const unsigned short sDoomVirusDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/doom_virus_dragon.gbapal");
static const unsigned char sDoomVirusDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/doom_virus_dragon.lz");

static const unsigned char sInstantFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/instant_fusion.huff");
static const unsigned short sInstantFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/instant_fusion.gbapal");
static const unsigned char sInstantFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/instant_fusion.lz");

static const unsigned char sJudgmentDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/judgment_dragon.huff");
static const unsigned short sJudgmentDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/judgment_dragon.gbapal");
static const unsigned char sJudgmentDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/judgment_dragon.lz");

static const unsigned char sManjuOfTheTenThousandHandsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/manju_of_the_ten_thousand_hands.huff");
static const unsigned short sManjuOfTheTenThousandHandsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/manju_of_the_ten_thousand_hands.gbapal");
static const unsigned char sManjuOfTheTenThousandHandsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/manju_of_the_ten_thousand_hands.lz");

static const unsigned char sMarshmallonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/marshmallon.huff");
static const unsigned short sMarshmallonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/marshmallon.gbapal");
static const unsigned char sMarshmallonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/marshmallon.lz");

static const unsigned char sNecrovalleyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/necrovalley.huff");
static const unsigned short sNecrovalleyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/necrovalley.gbapal");
static const unsigned char sNecrovalleyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/necrovalley.lz");

static const unsigned char sNibiruThePrimalBeingBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/nibiru_the_primal_being.huff");
static const unsigned short sNibiruThePrimalBeingBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/nibiru_the_primal_being.gbapal");
static const unsigned char sNibiruThePrimalBeingMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/nibiru_the_primal_being.lz");

static const unsigned char sPhotonGeneratorUnitBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/photon_generator_unit.huff");
static const unsigned short sPhotonGeneratorUnitBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/photon_generator_unit.gbapal");
static const unsigned char sPhotonGeneratorUnitMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/photon_generator_unit.lz");

static const unsigned char sReaperScytheDreadscytheBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reaper_scythe_dreadscythe.huff");
static const unsigned short sReaperScytheDreadscytheBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reaper_scythe_dreadscythe.gbapal");
static const unsigned char sReaperScytheDreadscytheMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reaper_scythe_dreadscythe.lz");

static const unsigned char sRedEyesBlackDragonSwordBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/red_eyes_black_dragon_sword.huff");
static const unsigned short sRedEyesBlackDragonSwordBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/red_eyes_black_dragon_sword.gbapal");
static const unsigned char sRedEyesBlackDragonSwordMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/red_eyes_black_dragon_sword.lz");

static const unsigned char sRedGadgetBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/red_gadget.huff");
static const unsigned short sRedGadgetBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/red_gadget.gbapal");
static const unsigned char sRedGadgetMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/red_gadget.lz");

static const unsigned char sRocketHermosCannonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/rocket_hermos_cannon.huff");
static const unsigned short sRocketHermosCannonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/rocket_hermos_cannon.gbapal");
static const unsigned char sRocketHermosCannonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/rocket_hermos_cannon.lz");

static const unsigned char sScapegoatBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/scapegoat.huff");
static const unsigned short sScapegoatBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/scapegoat.gbapal");
static const unsigned char sScapegoatMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/scapegoat.lz");

static const unsigned char sSolemnJudgmentBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/solemn_judgment.huff");
static const unsigned short sSolemnJudgmentBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/solemn_judgment.gbapal");
static const unsigned char sSolemnJudgmentMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/solemn_judgment.lz");

static const unsigned char sSuperPolymerizationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/super_polymerization.huff");
static const unsigned short sSuperPolymerizationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/super_polymerization.gbapal");
static const unsigned char sSuperPolymerizationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/super_polymerization.lz");

static const unsigned char sVisionHeroAdorationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vision_hero_adoration.huff");
static const unsigned short sVisionHeroAdorationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vision_hero_adoration.gbapal");
static const unsigned char sVisionHeroAdorationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vision_hero_adoration.lz");

static const unsigned char sVisionHeroFarisBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vision_hero_faris.huff");
static const unsigned short sVisionHeroFarisBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vision_hero_faris.gbapal");
static const unsigned char sVisionHeroFarisMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vision_hero_faris.lz");

static const unsigned char sVisionHeroGravitoBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vision_hero_gravito.huff");
static const unsigned short sVisionHeroGravitoBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vision_hero_gravito.gbapal");
static const unsigned char sVisionHeroGravitoMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vision_hero_gravito.lz");

static const unsigned char sVisionHeroIncreaseBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vision_hero_increase.huff");
static const unsigned short sVisionHeroIncreaseBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vision_hero_increase.gbapal");
static const unsigned char sVisionHeroIncreaseMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vision_hero_increase.lz");

static const unsigned char sAromaBlendBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aroma_blend.huff");
static const unsigned short sAromaBlendBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aroma_blend.gbapal");
static const unsigned char sAromaBlendMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aroma_blend.lz");

static const unsigned char sAromaGardenBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aroma_garden.huff");
static const unsigned short sAromaGardenBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aroma_garden.gbapal");
static const unsigned char sAromaGardenMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aroma_garden.lz");

static const unsigned char sAromaGardeningBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aroma_gardening.huff");
static const unsigned short sAromaGardeningBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aroma_gardening.gbapal");
static const unsigned char sAromaGardeningMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aroma_gardening.lz");

static const unsigned char sAromaJarBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aroma_jar.huff");
static const unsigned short sAromaJarBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aroma_jar.gbapal");
static const unsigned char sAromaJarMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aroma_jar.lz");

static const unsigned char sBlueEyesJetDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_jet_dragon.huff");
static const unsigned short sBlueEyesJetDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_jet_dragon.gbapal");
static const unsigned char sBlueEyesJetDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_jet_dragon.lz");

static const unsigned char sBlueEyesSolidDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_solid_dragon.huff");
static const unsigned short sBlueEyesSolidDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_solid_dragon.gbapal");
static const unsigned char sBlueEyesSolidDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_solid_dragon.lz");

static const unsigned char sBrionacDragonOfTheIceBarrierBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/brionac_dragon_of_the_ice_barrier.huff");
static const unsigned short sBrionacDragonOfTheIceBarrierBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/brionac_dragon_of_the_ice_barrier.gbapal");
static const unsigned char sBrionacDragonOfTheIceBarrierMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/brionac_dragon_of_the_ice_barrier.lz");

static const unsigned char sCyberSlashHarpieLadyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cyber_slash_harpie_lady.huff");
static const unsigned short sCyberSlashHarpieLadyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cyber_slash_harpie_lady.gbapal");
static const unsigned char sCyberSlashHarpieLadyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cyber_slash_harpie_lady.lz");

static const unsigned char sDarkMagicAttackBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_magic_attack.huff");
static const unsigned short sDarkMagicAttackBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_magic_attack.gbapal");
static const unsigned char sDarkMagicAttackMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_magic_attack.lz");

static const unsigned char sDarkMagicInheritanceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_magic_inheritance.huff");
static const unsigned short sDarkMagicInheritanceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_magic_inheritance.gbapal");
static const unsigned char sDarkMagicInheritanceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_magic_inheritance.lz");

static const unsigned char sDarkMagicVeilBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_magic_veil.huff");
static const unsigned short sDarkMagicVeilBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_magic_veil.gbapal");
static const unsigned char sDarkMagicVeilMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_magic_veil.lz");

static const unsigned char sDarkMagicalCircleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_magical_circle.huff");
static const unsigned short sDarkMagicalCircleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_magical_circle.gbapal");
static const unsigned char sDarkMagicalCircleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_magical_circle.lz");

static const unsigned char sDarkMagicianOfDestructionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_magician_of_destruction.huff");
static const unsigned short sDarkMagicianOfDestructionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_magician_of_destruction.gbapal");
static const unsigned char sDarkMagicianOfDestructionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_magician_of_destruction.lz");

static const unsigned char sDeepEyesWhiteDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/deep_eyes_white_dragon.huff");
static const unsigned short sDeepEyesWhiteDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/deep_eyes_white_dragon.gbapal");
static const unsigned char sDeepEyesWhiteDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/deep_eyes_white_dragon.lz");

static const unsigned char sDragonSpiritOfWhiteBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dragon_spirit_of_white.huff");
static const unsigned short sDragonSpiritOfWhiteBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dragon_spirit_of_white.gbapal");
static const unsigned char sDragonSpiritOfWhiteMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dragon_spirit_of_white.lz");

static const unsigned char sElShaddollConstructBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/el_shaddoll_construct.huff");
static const unsigned short sElShaddollConstructBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/el_shaddoll_construct.gbapal");
static const unsigned char sElShaddollConstructMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/el_shaddoll_construct.lz");

static const unsigned char sElShaddollWindaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/el_shaddoll_winda.huff");
static const unsigned short sElShaddollWindaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/el_shaddoll_winda.gbapal");
static const unsigned char sElShaddollWindaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/el_shaddoll_winda.lz");

static const unsigned char sEternalSoulBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/eternal_soul.huff");
static const unsigned short sEternalSoulBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/eternal_soul.gbapal");
static const unsigned char sEternalSoulMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/eternal_soul.lz");

static const unsigned char sEvilHeroAdustedGoldBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_adusted_gold.huff");
static const unsigned short sEvilHeroAdustedGoldBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_adusted_gold.gbapal");
static const unsigned char sEvilHeroAdustedGoldMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_adusted_gold.lz");

static const unsigned char sEvilHeroDarkGaiaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_dark_gaia.huff");
static const unsigned short sEvilHeroDarkGaiaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_dark_gaia.gbapal");
static const unsigned char sEvilHeroDarkGaiaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_dark_gaia.lz");

static const unsigned char sEvilHeroDarkestKnightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_darkest_knight.huff");
static const unsigned short sEvilHeroDarkestKnightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_darkest_knight.gbapal");
static const unsigned char sEvilHeroDarkestKnightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_darkest_knight.lz");

static const unsigned char sEvilHeroDeadEndPrisonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_dead_end_prison.huff");
static const unsigned short sEvilHeroDeadEndPrisonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_dead_end_prison.gbapal");
static const unsigned char sEvilHeroDeadEndPrisonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_dead_end_prison.lz");

static const unsigned char sEvilHeroInfernalGainerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_infernal_gainer.huff");
static const unsigned short sEvilHeroInfernalGainerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_infernal_gainer.gbapal");
static const unsigned char sEvilHeroInfernalGainerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_infernal_gainer.lz");

static const unsigned char sGoyoGuardianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/goyo_guardian.huff");
static const unsigned short sGoyoGuardianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/goyo_guardian.gbapal");
static const unsigned char sGoyoGuardianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/goyo_guardian.lz");

static const unsigned char sHarpieChannelerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpie_channeler.huff");
static const unsigned short sHarpieChannelerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpie_channeler.gbapal");
static const unsigned char sHarpieChannelerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpie_channeler.lz");

static const unsigned char sHarpieConductorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpie_conductor.huff");
static const unsigned short sHarpieConductorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpie_conductor.gbapal");
static const unsigned char sHarpieConductorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpie_conductor.lz");

static const unsigned char sHarpieDancerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpie_dancer.huff");
static const unsigned short sHarpieDancerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpie_dancer.gbapal");
static const unsigned char sHarpieDancerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpie_dancer.lz");

static const unsigned char sHarpieHarpistBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpie_harpist.huff");
static const unsigned short sHarpieHarpistBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpie_harpist.gbapal");
static const unsigned char sHarpieHarpistMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpie_harpist.lz");

static const unsigned char sHarpieLadyEleganceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpie_lady_elegance.huff");
static const unsigned short sHarpieLadyEleganceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpie_lady_elegance.gbapal");
static const unsigned char sHarpieLadyEleganceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpie_lady_elegance.lz");

static const unsigned char sHarpieOracleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpie_oracle.huff");
static const unsigned short sHarpieOracleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpie_oracle.gbapal");
static const unsigned char sHarpieOracleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpie_oracle.lz");

static const unsigned char sHarpiePerfumerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpie_perfumer.huff");
static const unsigned short sHarpiePerfumerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpie_perfumer.gbapal");
static const unsigned char sHarpiePerfumerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpie_perfumer.lz");

static const unsigned char sHarpieQueenBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpie_queen.huff");
static const unsigned short sHarpieQueenBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpie_queen.gbapal");
static const unsigned char sHarpieQueenMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpie_queen.lz");

static const unsigned char sHarpiesFeatherRestBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpies_feather_rest.huff");
static const unsigned short sHarpiesFeatherRestBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpies_feather_rest.gbapal");
static const unsigned char sHarpiesFeatherRestMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpies_feather_rest.lz");

static const unsigned char sHarpiesFeatherStormBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpies_feather_storm.huff");
static const unsigned short sHarpiesFeatherStormBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpies_feather_storm.gbapal");
static const unsigned char sHarpiesFeatherStormMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpies_feather_storm.lz");

static const unsigned char sHarpiesHuntingGroundBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpies_hunting_ground.huff");
static const unsigned short sHarpiesHuntingGroundBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpies_hunting_ground.gbapal");
static const unsigned char sHarpiesHuntingGroundMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpies_hunting_ground.lz");

static const unsigned char sHarpiesPetPhantasmalDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpies_pet_phantasmal_dragon.huff");
static const unsigned short sHarpiesPetPhantasmalDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpies_pet_phantasmal_dragon.gbapal");
static const unsigned char sHarpiesPetPhantasmalDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpies_pet_phantasmal_dragon.lz");

static const unsigned char sJunkWarriorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/junk_warrior.huff");
static const unsigned short sJunkWarriorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/junk_warrior.gbapal");
static const unsigned char sJunkWarriorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/junk_warrior.lz");

static const unsigned char sMagicianOfDarkIllusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magician_of_dark_illusion.huff");
static const unsigned short sMagicianOfDarkIllusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magician_of_dark_illusion.gbapal");
static const unsigned char sMagicianOfDarkIllusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magician_of_dark_illusion.lz");

static const unsigned char sMagiciansRodBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magicians_rod.huff");
static const unsigned short sMagiciansRodBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magicians_rod.gbapal");
static const unsigned char sMagiciansRodMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magicians_rod.lz");

static const unsigned char sMagiciansSoulsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magicians_souls.huff");
static const unsigned short sMagiciansSoulsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magicians_souls.gbapal");
static const unsigned char sMagiciansSoulsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magicians_souls.lz");

static const unsigned char sMasterOfChaosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/master_of_chaos.huff");
static const unsigned short sMasterOfChaosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/master_of_chaos.gbapal");
static const unsigned char sMasterOfChaosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/master_of_chaos.lz");

static const unsigned char sRedDragonArchfiendBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/red_dragon_archfiend.huff");
static const unsigned short sRedDragonArchfiendBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/red_dragon_archfiend.gbapal");
static const unsigned char sRedDragonArchfiendMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/red_dragon_archfiend.lz");

static const unsigned char sReptilianneGardnaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_gardna.huff");
static const unsigned short sReptilianneGardnaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_gardna.gbapal");
static const unsigned char sReptilianneGardnaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_gardna.lz");

static const unsigned char sReptilianneGorgonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_gorgon.huff");
static const unsigned short sReptilianneGorgonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_gorgon.gbapal");
static const unsigned char sReptilianneGorgonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_gorgon.lz");

static const unsigned char sReptilianneHydraBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_hydra.huff");
static const unsigned short sReptilianneHydraBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_hydra.gbapal");
static const unsigned char sReptilianneHydraMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_hydra.lz");

static const unsigned char sReturnOfTheDragonLordsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/return_of_the_dragon_lords.huff");
static const unsigned short sReturnOfTheDragonLordsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/return_of_the_dragon_lords.gbapal");
static const unsigned char sReturnOfTheDragonLordsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/return_of_the_dragon_lords.lz");

static const unsigned char sSecretsOfDarkMagicBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/secrets_of_dark_magic.huff");
static const unsigned short sSecretsOfDarkMagicBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/secrets_of_dark_magic.gbapal");
static const unsigned char sSecretsOfDarkMagicMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/secrets_of_dark_magic.lz");

static const unsigned char sShaddollBeastBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shaddoll_beast.huff");
static const unsigned short sShaddollBeastBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shaddoll_beast.gbapal");
static const unsigned char sShaddollBeastMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shaddoll_beast.lz");

static const unsigned char sShaddollDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shaddoll_dragon.huff");
static const unsigned short sShaddollDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shaddoll_dragon.gbapal");
static const unsigned char sShaddollDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shaddoll_dragon.lz");

static const unsigned char sShaddollFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shaddoll_fusion.huff");
static const unsigned short sShaddollFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shaddoll_fusion.gbapal");
static const unsigned char sShaddollFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shaddoll_fusion.lz");

static const unsigned char sShaddollHedgehogBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shaddoll_hedgehog.huff");
static const unsigned short sShaddollHedgehogBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shaddoll_hedgehog.gbapal");
static const unsigned char sShaddollHedgehogMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shaddoll_hedgehog.lz");

static const unsigned char sShaddollSquamataBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shaddoll_squamata.huff");
static const unsigned short sShaddollSquamataBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shaddoll_squamata.gbapal");
static const unsigned char sShaddollSquamataMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shaddoll_squamata.lz");

static const unsigned char sSilversCryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/silvers_cry.huff");
static const unsigned short sSilversCryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/silvers_cry.gbapal");
static const unsigned char sSilversCryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/silvers_cry.lz");

static const unsigned char sSoulServantBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/soul_servant.huff");
static const unsigned short sSoulServantBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/soul_servant.gbapal");
static const unsigned char sSoulServantMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/soul_servant.lz");

static const unsigned char sStardustDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/stardust_dragon.huff");
static const unsigned short sStardustDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/stardust_dragon.gbapal");
static const unsigned char sStardustDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/stardust_dragon.lz");

static const unsigned char sTheMelodyOfAwakeningDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_melody_of_awakening_dragon.huff");
static const unsigned short sTheMelodyOfAwakeningDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_melody_of_awakening_dragon.gbapal");
static const unsigned char sTheMelodyOfAwakeningDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_melody_of_awakening_dragon.lz");

static const unsigned char sTheWhiteStoneOfAncientsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_white_stone_of_ancients.huff");
static const unsigned short sTheWhiteStoneOfAncientsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_white_stone_of_ancients.gbapal");
static const unsigned char sTheWhiteStoneOfAncientsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_white_stone_of_ancients.lz");

static const unsigned char sTheWhiteStoneOfLegendBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_white_stone_of_legend.huff");
static const unsigned short sTheWhiteStoneOfLegendBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_white_stone_of_legend.gbapal");
static const unsigned char sTheWhiteStoneOfLegendMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_white_stone_of_legend.lz");

static const unsigned char sVenomBoaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/venom_boa.huff");
static const unsigned short sVenomBoaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/venom_boa.gbapal");
static const unsigned char sVenomBoaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/venom_boa.lz");

static const unsigned char sVenomBurnBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/venom_burn.huff");
static const unsigned short sVenomBurnBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/venom_burn.gbapal");
static const unsigned char sVenomBurnMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/venom_burn.lz");

static const unsigned char sArcanaForce0TheFoolBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_0_the_fool.huff");
static const unsigned short sArcanaForce0TheFoolBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_0_the_fool.gbapal");
static const unsigned char sArcanaForce0TheFoolMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_0_the_fool.lz");

static const unsigned char sArcanaForceExTheDarkRulerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_ex_the_dark_ruler.huff");
static const unsigned short sArcanaForceExTheDarkRulerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_ex_the_dark_ruler.gbapal");
static const unsigned char sArcanaForceExTheDarkRulerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_ex_the_dark_ruler.lz");

static const unsigned char sArcanaForceITheMagicianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_i_the_magician.huff");
static const unsigned short sArcanaForceITheMagicianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_i_the_magician.gbapal");
static const unsigned char sArcanaForceITheMagicianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_i_the_magician.lz");

static const unsigned char sGladiatorBeastAlexanderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_alexander.huff");
static const unsigned short sGladiatorBeastAlexanderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_alexander.gbapal");
static const unsigned char sGladiatorBeastAlexanderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_alexander.lz");

static const unsigned char sGladiatorBeastAttorixBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_attorix.huff");
static const unsigned short sGladiatorBeastAttorixBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_attorix.gbapal");
static const unsigned char sGladiatorBeastAttorixMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_attorix.lz");

static const unsigned char sGladiatorBeastAugustusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_augustus.huff");
static const unsigned short sGladiatorBeastAugustusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_augustus.gbapal");
static const unsigned char sGladiatorBeastAugustusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_augustus.lz");

static const unsigned char sGladiatorBeastBattleHalberdBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_battle_halberd.huff");
static const unsigned short sGladiatorBeastBattleHalberdBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_battle_halberd.gbapal");
static const unsigned char sGladiatorBeastBattleHalberdMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_battle_halberd.lz");

static const unsigned char sGladiatorBeastBestiariBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_bestiari.huff");
static const unsigned short sGladiatorBeastBestiariBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_bestiari.gbapal");
static const unsigned char sGladiatorBeastBestiariMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_bestiari.lz");

static const unsigned char sGladiatorBeastClaudiusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_claudius.huff");
static const unsigned short sGladiatorBeastClaudiusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_claudius.gbapal");
static const unsigned char sGladiatorBeastClaudiusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_claudius.lz");

static const unsigned char sLightswornAegisBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lightsworn_aegis.huff");
static const unsigned short sLightswornAegisBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lightsworn_aegis.gbapal");
static const unsigned char sLightswornAegisMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lightsworn_aegis.lz");

static const unsigned char sLightswornBarrierBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lightsworn_barrier.huff");
static const unsigned short sLightswornBarrierBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lightsworn_barrier.gbapal");
static const unsigned char sLightswornBarrierMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lightsworn_barrier.lz");

static const unsigned char sLightswornDragonlingBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lightsworn_dragonling.huff");
static const unsigned short sLightswornDragonlingBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lightsworn_dragonling.gbapal");
static const unsigned char sLightswornDragonlingMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lightsworn_dragonling.lz");

static const unsigned char sLightswornJudgementBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lightsworn_judgement.huff");
static const unsigned short sLightswornJudgementBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lightsworn_judgement.gbapal");
static const unsigned char sLightswornJudgementMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lightsworn_judgement.lz");

static const unsigned char sLightswornSabreBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lightsworn_sabre.huff");
static const unsigned short sLightswornSabreBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lightsworn_sabre.gbapal");
static const unsigned char sLightswornSabreMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lightsworn_sabre.lz");

static const unsigned char sLightswornSanctuaryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lightsworn_sanctuary.huff");
static const unsigned short sLightswornSanctuaryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lightsworn_sanctuary.gbapal");
static const unsigned char sLightswornSanctuaryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lightsworn_sanctuary.lz");

static const unsigned char sNeoSpacianAirHummingbirdBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_spacian_air_hummingbird.huff");
static const unsigned short sNeoSpacianAirHummingbirdBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_spacian_air_hummingbird.gbapal");
static const unsigned char sNeoSpacianAirHummingbirdMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_spacian_air_hummingbird.lz");

static const unsigned char sNeoSpacianAquaDolphinBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_spacian_aqua_dolphin.huff");
static const unsigned short sNeoSpacianAquaDolphinBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_spacian_aqua_dolphin.gbapal");
static const unsigned char sNeoSpacianAquaDolphinMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_spacian_aqua_dolphin.lz");

static const unsigned char sNeoSpacianFlareScarabBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_spacian_flare_scarab.huff");
static const unsigned short sNeoSpacianFlareScarabBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_spacian_flare_scarab.gbapal");
static const unsigned char sNeoSpacianFlareScarabMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_spacian_flare_scarab.lz");

static const unsigned char sNeoSpacianGlowMossBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_spacian_glow_moss.huff");
static const unsigned short sNeoSpacianGlowMossBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_spacian_glow_moss.gbapal");
static const unsigned char sNeoSpacianGlowMossMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_spacian_glow_moss.lz");

static const unsigned char sAncientGearBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear.huff");
static const unsigned short sAncientGearBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear.gbapal");
static const unsigned char sAncientGearMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear.lz");

static const unsigned char sAncientGearAdvanceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_advance.huff");
static const unsigned short sAncientGearAdvanceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_advance.gbapal");
static const unsigned char sAncientGearAdvanceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_advance.lz");

static const unsigned char sAncientGearBeastBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_beast.huff");
static const unsigned short sAncientGearBeastBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_beast.gbapal");
static const unsigned char sAncientGearBeastMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_beast.lz");

static const unsigned char sAncientGearCannonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_cannon.huff");
static const unsigned short sAncientGearCannonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_cannon.gbapal");
static const unsigned char sAncientGearCannonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_cannon.lz");

static const unsigned char sAncientGearCastleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_castle.huff");
static const unsigned short sAncientGearCastleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_castle.gbapal");
static const unsigned char sAncientGearCastleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_castle.lz");

static const unsigned char sCyberDragonInfinityBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cyber_dragon_infinity.huff");
static const unsigned short sCyberDragonInfinityBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cyber_dragon_infinity.gbapal");
static const unsigned char sCyberDragonInfinityMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cyber_dragon_infinity.lz");

static const unsigned char sEvolzarDolkkaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evolzar_dolkka.huff");
static const unsigned short sEvolzarDolkkaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evolzar_dolkka.gbapal");
static const unsigned char sEvolzarDolkkaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evolzar_dolkka.lz");

static const unsigned char sHonestBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/honest.huff");
static const unsigned short sHonestBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/honest.gbapal");
static const unsigned char sHonestMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/honest.lz");

static const unsigned char sJunkSynchronBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/junk_synchron.huff");
static const unsigned short sJunkSynchronBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/junk_synchron.gbapal");
static const unsigned char sJunkSynchronMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/junk_synchron.lz");

static const unsigned char sAmazonessAugustaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/amazoness_augusta.huff");
static const unsigned short sAmazonessAugustaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/amazoness_augusta.gbapal");
static const unsigned char sAmazonessAugustaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/amazoness_augusta.lz");

static const unsigned char sAmazonessEmpressBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/amazoness_empress.huff");
static const unsigned short sAmazonessEmpressBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/amazoness_empress.gbapal");
static const unsigned char sAmazonessEmpressMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/amazoness_empress.lz");

static const unsigned char sAmazonessPrincessBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/amazoness_princess.huff");
static const unsigned short sAmazonessPrincessBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/amazoness_princess.gbapal");
static const unsigned char sAmazonessPrincessMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/amazoness_princess.lz");

static const unsigned char sAmazonessQueenBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/amazoness_queen.huff");
static const unsigned short sAmazonessQueenBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/amazoness_queen.gbapal");
static const unsigned char sAmazonessQueenMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/amazoness_queen.lz");

static const unsigned char sAmazonessCallBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/amazoness_call.huff");
static const unsigned short sAmazonessCallBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/amazoness_call.gbapal");
static const unsigned char sAmazonessCallMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/amazoness_call.lz");

static const unsigned char sAmazonessOnslaughtBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/amazoness_onslaught.huff");
static const unsigned short sAmazonessOnslaughtBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/amazoness_onslaught.gbapal");
static const unsigned char sAmazonessOnslaughtMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/amazoness_onslaught.lz");

static const unsigned char sAmazonessVillageBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/amazoness_village.huff");
static const unsigned short sAmazonessVillageBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/amazoness_village.gbapal");
static const unsigned char sAmazonessVillageMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/amazoness_village.lz");

static const unsigned char sAshBlossomAndJoyousSpringBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ash_blossom_and_joyous_spring.huff");
static const unsigned short sAshBlossomAndJoyousSpringBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ash_blossom_and_joyous_spring.gbapal");
static const unsigned char sAshBlossomAndJoyousSpringMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ash_blossom_and_joyous_spring.lz");

static const unsigned char sForbiddenChaliceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/forbidden_chalice.huff");
static const unsigned short sForbiddenChaliceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/forbidden_chalice.gbapal");
static const unsigned char sForbiddenChaliceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/forbidden_chalice.lz");

static const unsigned char sForbiddenLanceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/forbidden_lance.huff");
static const unsigned short sForbiddenLanceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/forbidden_lance.gbapal");
static const unsigned char sForbiddenLanceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/forbidden_lance.lz");

static const unsigned char sGravekeepersChiefBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gravekeepers_chief.huff");
static const unsigned short sGravekeepersChiefBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gravekeepers_chief.gbapal");
static const unsigned char sGravekeepersChiefMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gravekeepers_chief.lz");

static const unsigned char sGravekeepersCommandantBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gravekeepers_commandant.huff");
static const unsigned short sGravekeepersCommandantBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gravekeepers_commandant.gbapal");
static const unsigned char sGravekeepersCommandantMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gravekeepers_commandant.lz");

static const unsigned char sGravekeepersHeadmanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gravekeepers_headman.huff");
static const unsigned short sGravekeepersHeadmanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gravekeepers_headman.gbapal");
static const unsigned char sGravekeepersHeadmanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gravekeepers_headman.lz");

static const unsigned char sGravekeepersOracleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gravekeepers_oracle.huff");
static const unsigned short sGravekeepersOracleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gravekeepers_oracle.gbapal");
static const unsigned char sGravekeepersOracleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gravekeepers_oracle.lz");

static const unsigned char sGravekeepersRecruiterBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gravekeepers_recruiter.huff");
static const unsigned short sGravekeepersRecruiterBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gravekeepers_recruiter.gbapal");
static const unsigned char sGravekeepersRecruiterMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gravekeepers_recruiter.lz");

static const unsigned char sGravekeepersSpiritualistBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gravekeepers_spiritualist.huff");
static const unsigned short sGravekeepersSpiritualistBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gravekeepers_spiritualist.gbapal");
static const unsigned char sGravekeepersSpiritualistMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gravekeepers_spiritualist.lz");

static const unsigned char sGravekeepersTrapBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gravekeepers_trap.huff");
static const unsigned short sGravekeepersTrapBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gravekeepers_trap.gbapal");
static const unsigned char sGravekeepersTrapMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gravekeepers_trap.lz");

static const unsigned char sImperialTombsOfNecrovalleyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/imperial_tombs_of_necrovalley.huff");
static const unsigned short sImperialTombsOfNecrovalleyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/imperial_tombs_of_necrovalley.gbapal");
static const unsigned char sImperialTombsOfNecrovalleyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/imperial_tombs_of_necrovalley.lz");

static const unsigned char sInfiniteImpermanenceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/infinite_impermanence.huff");
static const unsigned short sInfiniteImpermanenceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/infinite_impermanence.gbapal");
static const unsigned char sInfiniteImpermanenceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/infinite_impermanence.lz");

static const unsigned char sHiddenTemplesOfNecrovalleyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/hidden_temples_of_necrovalley.huff");
static const unsigned short sHiddenTemplesOfNecrovalleyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/hidden_temples_of_necrovalley.gbapal");
static const unsigned char sHiddenTemplesOfNecrovalleyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/hidden_temples_of_necrovalley.lz");

static const unsigned char sLightningStormBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lightning_storm.huff");
static const unsigned short sLightningStormBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lightning_storm.gbapal");
static const unsigned char sLightningStormMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lightning_storm.lz");

static const unsigned char sPotOfAvariceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/pot_of_avarice.huff");
static const unsigned short sPotOfAvariceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/pot_of_avarice.gbapal");
static const unsigned char sPotOfAvariceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/pot_of_avarice.lz");

static const unsigned char sNumber39UtopiaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/number_39_utopia.huff");
static const unsigned short sNumber39UtopiaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/number_39_utopia.gbapal");
static const unsigned char sNumber39UtopiaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/number_39_utopia.lz");

static const unsigned char sMaxxCBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/maxx_c.huff");
static const unsigned short sMaxxCBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/maxx_c.gbapal");
static const unsigned char sMaxxCMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/maxx_c.lz");

static const unsigned char sToadallyAwesomeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/toadally_awesome.huff");
static const unsigned short sToadallyAwesomeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/toadally_awesome.gbapal");
static const unsigned char sToadallyAwesomeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/toadally_awesome.lz");

const unsigned char *gCardArts_Hook[] APPEND_RODATA = {
  [0x00AE] = sSenjuOfTheThousandHandsBigArt,
  [0x0137] = sBlackPendantBigArt,
  [0x020B] = sTheBistroButcherBigArt,
  [0x0321] = sBlueEyesShiningDragonBigArt,
  [0x0322] = sBlueEyesChaosMaxDragonBigArt,
  [0x0323] = sKaibamanBigArt,
  [0x0324] = sUltimateOfferingBigArt,
  [0x0325] = sWaveMotionCannonBigArt,
  [0x0326] = sSoulExchangeBigArt,
  [0x0327] = sMysticalSpaceTyphoonBigArt,
  [0x0328] = sRareMetalDragonBigArt,
  [0x0329] = sMaskOfRestrictBigArt,
  [0x032A] = sBlueEyesAlternativeWhiteDragonBigArt,
  [0x032B] = sSealOfOrichalcosBigArt,
  [0x032C] = sSkillDrainBigArt,
  [0x032D] = sMagicCylinderBigArt,
  [0x032E] = sDelinquentDuoBigArt,
  [0x032F] = sYataGarasuBigArt,
  [0x0330] = sUpstartGoblinBigArt,
  [0x0331] = sCallOfTheHauntedBigArt,
  [0x0332] = sSwiftGaiaTheFierceKnightBigArt,
  [0x0333] = sLimiterRemovalBigArt,
  [0x0334] = sRecklessGreedBigArt,
  [0x0335] = sCardDestructionBigArt,
  [0x0336] = sGracefulCharityBigArt,
  [0x0337] = sImperialOrderBigArt,
  [0x0338] = sRoyalDecreeBigArt,
  [0x0339] = sDoubleCostonBigArt,
  [0x033A] = sFinalCountdownBigArt,
  [0x033B] = sBookOfMoonBigArt,
  [0x033C] = sAmazonessTigerBigArt,
  [0x033D] = sConfiscationBigArt,
  [0x033E] = sZaborgTheThunderMonarchBigArt,
  [0x033F] = sPolymerizationBigArt,
  [0x0340] = sCyberDragonBigArt,
  [0x0341] = sCyberTwinDragonBigArt,
  [0x0342] = sCyberEndDragonBigArt,
  [0x0343] = sCaiusTheShadowMonarchBigArt,
  [0x0344] = sMobiusTheFrostMonarchBigArt,
  [0x0345] = sProtoCyberDragonBigArt,
  [0x0346] = sAmazonessArcherBigArt,
  [0x0347] = sElementalHeroWildheartBigArt,
  [0x0348] = sTheSanctuaryInTheSkyBigArt,
  [0x0349] = sMirrorForceBigArt,
  [0x034A] = sBlueEyesChaosDragonBigArt,
  [0x034B] = sDeFusionBigArt,
  [0x034C] = sALegendaryOceanBigArt,
  [0x034D] = sDarkMagicianOfChaosBigArt,
  [0x034E] = sElementalHeroPhoenixEnforcerBigArt,
  [0x034F] = sElementalHeroFlameWingmanBigArt,
  [0x0350] = sElementalHeroShiningFlareWingmanBigArt,
  [0x0351] = sMiracleFusionBigArt,
  [0x0352] = sChaosEmperorDragonEnvoyOfTheEndBigArt,
  [0x0353] = sBlackLusterSoldierEnvoyOfTheBeginningBigArt,
  [0x0354] = sElementalHeroNeosBigArt,
  [0x0355] = sFusionRecoveryBigArt,
  [0x0356] = sSkyscraperBigArt,
  [0x0357] = sHHeatedHeartBigArt,
  [0x0358] = sEEmergencyCallBigArt,
  [0x0359] = sElementalHeroIceEdgeBigArt,
  [0x035A] = sElementalHeroBlazemanBigArt,
  [0x035B] = sElementalHeroStratosBigArt,
  [0x035C] = sChimeratechOverdragonBigArt,
  [0x035D] = sCyberneticFusionSupportBigArt,
  [0x035E] = sOverloadFusionBigArt,
  [0x035F] = sPowerBondBigArt,
  [0x0360] = sDivineSanctuaryBigArt,
  [0x0361] = sYubelBigArt,
  [0x0362] = sYubelTerrorIncarnateBigArt,
  [0x0363] = sYubelTheUltimateNightmareBigArt,
  [0x0364] = sTradeInBigArt,
  [0x0365] = sCyberBarrierDragonBigArt,
  [0x0366] = sCyberLaserDragonBigArt,
  [0x0367] = sDestinyHeroBladeMasterBigArt,
  [0x0368] = sDestinyHeroCaptainTenaciousBigArt,
  [0x0369] = sDestinyHeroCelestialBigArt,
  [0x036A] = sDestinyHeroDangerousBigArt,
  [0x036B] = sDestinyHeroDasherBigArt,
  [0x036C] = sDoomVirusDragonBigArt,
  [0x036D] = sInstantFusionBigArt,
  [0x036E] = sJudgmentDragonBigArt,
  [0x036F] = sManjuOfTheTenThousandHandsBigArt,
  [0x0370] = sMarshmallonBigArt,
  [0x0371] = sNecrovalleyBigArt,
  [0x0372] = sNibiruThePrimalBeingBigArt,
  [0x0373] = sPhotonGeneratorUnitBigArt,
  [0x0374] = sReaperScytheDreadscytheBigArt,
  [0x0375] = sRedEyesBlackDragonSwordBigArt,
  [0x0376] = sRedGadgetBigArt,
  [0x0377] = sRocketHermosCannonBigArt,
  [0x0378] = sScapegoatBigArt,
  [0x0379] = sSolemnJudgmentBigArt,
  [0x037A] = sSuperPolymerizationBigArt,
  [0x037B] = sVisionHeroAdorationBigArt,
  [0x037C] = sVisionHeroFarisBigArt,
  [0x037D] = sVisionHeroGravitoBigArt,
  [0x037E] = sVisionHeroIncreaseBigArt,
  [0x037F] = sAromaBlendBigArt,
  [0x0380] = sAromaGardenBigArt,
  [0x0381] = sAromaGardeningBigArt,
  [0x0382] = sAromaJarBigArt,
  [0x0383] = sBlueEyesJetDragonBigArt,
  [0x0384] = sBlueEyesSolidDragonBigArt,
  [0x0385] = sBrionacDragonOfTheIceBarrierBigArt,
  [0x0386] = sCyberSlashHarpieLadyBigArt,
  [0x0387] = sDarkMagicAttackBigArt,
  [0x0388] = sDarkMagicInheritanceBigArt,
  [0x0389] = sDarkMagicVeilBigArt,
  [0x038A] = sDarkMagicalCircleBigArt,
  [0x038B] = sDarkMagicianOfDestructionBigArt,
  [0x038C] = sDeepEyesWhiteDragonBigArt,
  [0x038D] = sDragonSpiritOfWhiteBigArt,
  [0x038E] = sElShaddollConstructBigArt,
  [0x038F] = sElShaddollWindaBigArt,
  [0x0390] = sEternalSoulBigArt,
  [0x0391] = sEvilHeroAdustedGoldBigArt,
  [0x0392] = sEvilHeroDarkGaiaBigArt,
  [0x0393] = sEvilHeroDarkestKnightBigArt,
  [0x0394] = sEvilHeroDeadEndPrisonBigArt,
  [0x0395] = sEvilHeroInfernalGainerBigArt,
  [0x0396] = sGoyoGuardianBigArt,
  [0x0397] = sHarpieChannelerBigArt,
  [0x0398] = sHarpieConductorBigArt,
  [0x0399] = sHarpieDancerBigArt,
  [0x039A] = sHarpieHarpistBigArt,
  [0x039B] = sHarpieLadyEleganceBigArt,
  [0x039C] = sHarpieOracleBigArt,
  [0x039D] = sHarpiePerfumerBigArt,
  [0x039E] = sHarpieQueenBigArt,
  [0x039F] = sHarpiesFeatherRestBigArt,
  [0x03A0] = sHarpiesFeatherStormBigArt,
  [0x03A1] = sHarpiesHuntingGroundBigArt,
  [0x03A2] = sHarpiesPetPhantasmalDragonBigArt,
  [0x03A3] = sJunkWarriorBigArt,
  [0x03A4] = sMagicianOfDarkIllusionBigArt,
  [0x03A5] = sMagiciansRodBigArt,
  [0x03A6] = sMagiciansSoulsBigArt,
  [0x03A7] = sMasterOfChaosBigArt,
  [0x03A8] = sRedDragonArchfiendBigArt,
  [0x03A9] = sReptilianneGardnaBigArt,
  [0x03AA] = sReptilianneGorgonBigArt,
  [0x03AB] = sReptilianneHydraBigArt,
  [0x03AC] = sReturnOfTheDragonLordsBigArt,
  [0x03AD] = sSecretsOfDarkMagicBigArt,
  [0x03AE] = sShaddollBeastBigArt,
  [0x03AF] = sShaddollDragonBigArt,
  [0x03B0] = sShaddollFusionBigArt,
  [0x03B1] = sShaddollHedgehogBigArt,
  [0x03B2] = sShaddollSquamataBigArt,
  [0x03B3] = sSilversCryBigArt,
  [0x03B4] = sSoulServantBigArt,
  [0x03B5] = sStardustDragonBigArt,
  [0x03B6] = sTheMelodyOfAwakeningDragonBigArt,
  [0x03B7] = sTheWhiteStoneOfAncientsBigArt,
  [0x03B8] = sTheWhiteStoneOfLegendBigArt,
  [0x03B9] = sVenomBoaBigArt,
  [0x03BA] = sVenomBurnBigArt,
  [0x03BB] = sArcanaForce0TheFoolBigArt,
  [0x03BC] = sArcanaForceExTheDarkRulerBigArt,
  [0x03BD] = sArcanaForceITheMagicianBigArt,
  [0x03BE] = sGladiatorBeastAlexanderBigArt,
  [0x03BF] = sGladiatorBeastAttorixBigArt,
  [0x03C0] = sGladiatorBeastAugustusBigArt,
  [0x03C1] = sGladiatorBeastBattleHalberdBigArt,
  [0x03C2] = sGladiatorBeastBestiariBigArt,
  [0x03C3] = sGladiatorBeastClaudiusBigArt,
  [0x03C4] = sLightswornAegisBigArt,
  [0x03C5] = sLightswornBarrierBigArt,
  [0x03C6] = sLightswornDragonlingBigArt,
  [0x03C7] = sLightswornJudgementBigArt,
  [0x03C8] = sLightswornSabreBigArt,
  [0x03C9] = sLightswornSanctuaryBigArt,
  [0x03CA] = sNeoSpacianAirHummingbirdBigArt,
  [0x03CB] = sNeoSpacianAquaDolphinBigArt,
  [0x03CC] = sNeoSpacianFlareScarabBigArt,
  [0x03CD] = sNeoSpacianGlowMossBigArt,
  [0x03CE] = sAncientGearBigArt,
  [0x03CF] = sAncientGearAdvanceBigArt,
  [0x03D0] = sAncientGearBeastBigArt,
  [0x03D1] = sAncientGearCannonBigArt,
  [0x03D2] = sAncientGearCastleBigArt,
  [0x03D3] = sCyberDragonInfinityBigArt,
  [0x03D4] = sEvolzarDolkkaBigArt,
  [0x03D5] = sHonestBigArt,
  [0x03D6] = sJunkSynchronBigArt,
  [0x03D7] = sAmazonessAugustaBigArt,
  [0x03D8] = sAmazonessEmpressBigArt,
  [0x03D9] = sAmazonessPrincessBigArt,
  [0x03DA] = sAmazonessQueenBigArt,
  [0x03DB] = sAmazonessCallBigArt,
  [0x03DC] = sAmazonessOnslaughtBigArt,
  [0x03DD] = sAmazonessVillageBigArt,
  [0x03DE] = sAshBlossomAndJoyousSpringBigArt,
  [0x03DF] = sForbiddenChaliceBigArt,
  [0x03E0] = sForbiddenLanceBigArt,
  [0x03E1] = sGravekeepersChiefBigArt,
  [0x03E2] = sGravekeepersCommandantBigArt,
  [0x03E3] = sGravekeepersHeadmanBigArt,
  [0x03E4] = sGravekeepersOracleBigArt,
  [0x03E5] = sGravekeepersRecruiterBigArt,
  [0x03E6] = sGravekeepersSpiritualistBigArt,
  [0x03E7] = sGravekeepersTrapBigArt,
  [0x03E8] = sImperialTombsOfNecrovalleyBigArt,
  [0x03E9] = sInfiniteImpermanenceBigArt,
  [0x03EA] = sHiddenTemplesOfNecrovalleyBigArt,
  [0x03EB] = sLightningStormBigArt,
  [0x03EC] = sPotOfAvariceBigArt,
  [0x03ED] = sNumber39UtopiaBigArt,
  [0x03EE] = sMaxxCBigArt,
  [0x03EF] = sToadallyAwesomeBigArt,
};

const unsigned short *gCardArtPalettes_Hook[] APPEND_RODATA = {
  [0x00AE] = sSenjuOfTheThousandHandsBigPalette,
  [0x0137] = sBlackPendantBigPalette,
  [0x020B] = sTheBistroButcherBigPalette,
  [0x0321] = sBlueEyesShiningDragonBigPalette,
  [0x0322] = sBlueEyesChaosMaxDragonBigPalette,
  [0x0323] = sKaibamanBigPalette,
  [0x0324] = sUltimateOfferingBigPalette,
  [0x0325] = sWaveMotionCannonBigPalette,
  [0x0326] = sSoulExchangeBigPalette,
  [0x0327] = sMysticalSpaceTyphoonBigPalette,
  [0x0328] = sRareMetalDragonBigPalette,
  [0x0329] = sMaskOfRestrictBigPalette,
  [0x032A] = sBlueEyesAlternativeWhiteDragonBigPalette,
  [0x032B] = sSealOfOrichalcosBigPalette,
  [0x032C] = sSkillDrainBigPalette,
  [0x032D] = sMagicCylinderBigPalette,
  [0x032E] = sDelinquentDuoBigPalette,
  [0x032F] = sYataGarasuBigPalette,
  [0x0330] = sUpstartGoblinBigPalette,
  [0x0331] = sCallOfTheHauntedBigPalette,
  [0x0332] = sSwiftGaiaTheFierceKnightBigPalette,
  [0x0333] = sLimiterRemovalBigPalette,
  [0x0334] = sRecklessGreedBigPalette,
  [0x0335] = sCardDestructionBigPalette,
  [0x0336] = sGracefulCharityBigPalette,
  [0x0337] = sImperialOrderBigPalette,
  [0x0338] = sRoyalDecreeBigPalette,
  [0x0339] = sDoubleCostonBigPalette,
  [0x033A] = sFinalCountdownBigPalette,
  [0x033B] = sBookOfMoonBigPalette,
  [0x033C] = sAmazonessTigerBigPalette,
  [0x033D] = sConfiscationBigPalette,
  [0x033E] = sZaborgTheThunderMonarchBigPalette,
  [0x033F] = sPolymerizationBigPalette,
  [0x0340] = sCyberDragonBigPalette,
  [0x0341] = sCyberTwinDragonBigPalette,
  [0x0342] = sCyberEndDragonBigPalette,
  [0x0343] = sCaiusTheShadowMonarchBigPalette,
  [0x0344] = sMobiusTheFrostMonarchBigPalette,
  [0x0345] = sProtoCyberDragonBigPalette,
  [0x0346] = sAmazonessArcherBigPalette,
  [0x0347] = sElementalHeroWildheartBigPalette,
  [0x0348] = sTheSanctuaryInTheSkyBigPalette,
  [0x0349] = sMirrorForceBigPalette,
  [0x034A] = sBlueEyesChaosDragonBigPalette,
  [0x034B] = sDeFusionBigPalette,
  [0x034C] = sALegendaryOceanBigPalette,
  [0x034D] = sDarkMagicianOfChaosBigPalette,
  [0x034E] = sElementalHeroPhoenixEnforcerBigPalette,
  [0x034F] = sElementalHeroFlameWingmanBigPalette,
  [0x0350] = sElementalHeroShiningFlareWingmanBigPalette,
  [0x0351] = sMiracleFusionBigPalette,
  [0x0352] = sChaosEmperorDragonEnvoyOfTheEndBigPalette,
  [0x0353] = sBlackLusterSoldierEnvoyOfTheBeginningBigPalette,
  [0x0354] = sElementalHeroNeosBigPalette,
  [0x0355] = sFusionRecoveryBigPalette,
  [0x0356] = sSkyscraperBigPalette,
  [0x0357] = sHHeatedHeartBigPalette,
  [0x0358] = sEEmergencyCallBigPalette,
  [0x0359] = sElementalHeroIceEdgeBigPalette,
  [0x035A] = sElementalHeroBlazemanBigPalette,
  [0x035B] = sElementalHeroStratosBigPalette,
  [0x035C] = sChimeratechOverdragonBigPalette,
  [0x035D] = sCyberneticFusionSupportBigPalette,
  [0x035E] = sOverloadFusionBigPalette,
  [0x035F] = sPowerBondBigPalette,
  [0x0360] = sDivineSanctuaryBigPalette,
  [0x0361] = sYubelBigPalette,
  [0x0362] = sYubelTerrorIncarnateBigPalette,
  [0x0363] = sYubelTheUltimateNightmareBigPalette,
  [0x0364] = sTradeInBigPalette,
  [0x0365] = sCyberBarrierDragonBigPalette,
  [0x0366] = sCyberLaserDragonBigPalette,
  [0x0367] = sDestinyHeroBladeMasterBigPalette,
  [0x0368] = sDestinyHeroCaptainTenaciousBigPalette,
  [0x0369] = sDestinyHeroCelestialBigPalette,
  [0x036A] = sDestinyHeroDangerousBigPalette,
  [0x036B] = sDestinyHeroDasherBigPalette,
  [0x036C] = sDoomVirusDragonBigPalette,
  [0x036D] = sInstantFusionBigPalette,
  [0x036E] = sJudgmentDragonBigPalette,
  [0x036F] = sManjuOfTheTenThousandHandsBigPalette,
  [0x0370] = sMarshmallonBigPalette,
  [0x0371] = sNecrovalleyBigPalette,
  [0x0372] = sNibiruThePrimalBeingBigPalette,
  [0x0373] = sPhotonGeneratorUnitBigPalette,
  [0x0374] = sReaperScytheDreadscytheBigPalette,
  [0x0375] = sRedEyesBlackDragonSwordBigPalette,
  [0x0376] = sRedGadgetBigPalette,
  [0x0377] = sRocketHermosCannonBigPalette,
  [0x0378] = sScapegoatBigPalette,
  [0x0379] = sSolemnJudgmentBigPalette,
  [0x037A] = sSuperPolymerizationBigPalette,
  [0x037B] = sVisionHeroAdorationBigPalette,
  [0x037C] = sVisionHeroFarisBigPalette,
  [0x037D] = sVisionHeroGravitoBigPalette,
  [0x037E] = sVisionHeroIncreaseBigPalette,
  [0x037F] = sAromaBlendBigPalette,
  [0x0380] = sAromaGardenBigPalette,
  [0x0381] = sAromaGardeningBigPalette,
  [0x0382] = sAromaJarBigPalette,
  [0x0383] = sBlueEyesJetDragonBigPalette,
  [0x0384] = sBlueEyesSolidDragonBigPalette,
  [0x0385] = sBrionacDragonOfTheIceBarrierBigPalette,
  [0x0386] = sCyberSlashHarpieLadyBigPalette,
  [0x0387] = sDarkMagicAttackBigPalette,
  [0x0388] = sDarkMagicInheritanceBigPalette,
  [0x0389] = sDarkMagicVeilBigPalette,
  [0x038A] = sDarkMagicalCircleBigPalette,
  [0x038B] = sDarkMagicianOfDestructionBigPalette,
  [0x038C] = sDeepEyesWhiteDragonBigPalette,
  [0x038D] = sDragonSpiritOfWhiteBigPalette,
  [0x038E] = sElShaddollConstructBigPalette,
  [0x038F] = sElShaddollWindaBigPalette,
  [0x0390] = sEternalSoulBigPalette,
  [0x0391] = sEvilHeroAdustedGoldBigPalette,
  [0x0392] = sEvilHeroDarkGaiaBigPalette,
  [0x0393] = sEvilHeroDarkestKnightBigPalette,
  [0x0394] = sEvilHeroDeadEndPrisonBigPalette,
  [0x0395] = sEvilHeroInfernalGainerBigPalette,
  [0x0396] = sGoyoGuardianBigPalette,
  [0x0397] = sHarpieChannelerBigPalette,
  [0x0398] = sHarpieConductorBigPalette,
  [0x0399] = sHarpieDancerBigPalette,
  [0x039A] = sHarpieHarpistBigPalette,
  [0x039B] = sHarpieLadyEleganceBigPalette,
  [0x039C] = sHarpieOracleBigPalette,
  [0x039D] = sHarpiePerfumerBigPalette,
  [0x039E] = sHarpieQueenBigPalette,
  [0x039F] = sHarpiesFeatherRestBigPalette,
  [0x03A0] = sHarpiesFeatherStormBigPalette,
  [0x03A1] = sHarpiesHuntingGroundBigPalette,
  [0x03A2] = sHarpiesPetPhantasmalDragonBigPalette,
  [0x03A3] = sJunkWarriorBigPalette,
  [0x03A4] = sMagicianOfDarkIllusionBigPalette,
  [0x03A5] = sMagiciansRodBigPalette,
  [0x03A6] = sMagiciansSoulsBigPalette,
  [0x03A7] = sMasterOfChaosBigPalette,
  [0x03A8] = sRedDragonArchfiendBigPalette,
  [0x03A9] = sReptilianneGardnaBigPalette,
  [0x03AA] = sReptilianneGorgonBigPalette,
  [0x03AB] = sReptilianneHydraBigPalette,
  [0x03AC] = sReturnOfTheDragonLordsBigPalette,
  [0x03AD] = sSecretsOfDarkMagicBigPalette,
  [0x03AE] = sShaddollBeastBigPalette,
  [0x03AF] = sShaddollDragonBigPalette,
  [0x03B0] = sShaddollFusionBigPalette,
  [0x03B1] = sShaddollHedgehogBigPalette,
  [0x03B2] = sShaddollSquamataBigPalette,
  [0x03B3] = sSilversCryBigPalette,
  [0x03B4] = sSoulServantBigPalette,
  [0x03B5] = sStardustDragonBigPalette,
  [0x03B6] = sTheMelodyOfAwakeningDragonBigPalette,
  [0x03B7] = sTheWhiteStoneOfAncientsBigPalette,
  [0x03B8] = sTheWhiteStoneOfLegendBigPalette,
  [0x03B9] = sVenomBoaBigPalette,
  [0x03BA] = sVenomBurnBigPalette,
  [0x03BB] = sArcanaForce0TheFoolBigPalette,
  [0x03BC] = sArcanaForceExTheDarkRulerBigPalette,
  [0x03BD] = sArcanaForceITheMagicianBigPalette,
  [0x03BE] = sGladiatorBeastAlexanderBigPalette,
  [0x03BF] = sGladiatorBeastAttorixBigPalette,
  [0x03C0] = sGladiatorBeastAugustusBigPalette,
  [0x03C1] = sGladiatorBeastBattleHalberdBigPalette,
  [0x03C2] = sGladiatorBeastBestiariBigPalette,
  [0x03C3] = sGladiatorBeastClaudiusBigPalette,
  [0x03C4] = sLightswornAegisBigPalette,
  [0x03C5] = sLightswornBarrierBigPalette,
  [0x03C6] = sLightswornDragonlingBigPalette,
  [0x03C7] = sLightswornJudgementBigPalette,
  [0x03C8] = sLightswornSabreBigPalette,
  [0x03C9] = sLightswornSanctuaryBigPalette,
  [0x03CA] = sNeoSpacianAirHummingbirdBigPalette,
  [0x03CB] = sNeoSpacianAquaDolphinBigPalette,
  [0x03CC] = sNeoSpacianFlareScarabBigPalette,
  [0x03CD] = sNeoSpacianGlowMossBigPalette,
  [0x03CE] = sAncientGearBigPalette,
  [0x03CF] = sAncientGearAdvanceBigPalette,
  [0x03D0] = sAncientGearBeastBigPalette,
  [0x03D1] = sAncientGearCannonBigPalette,
  [0x03D2] = sAncientGearCastleBigPalette,
  [0x03D3] = sCyberDragonInfinityBigPalette,
  [0x03D4] = sEvolzarDolkkaBigPalette,
  [0x03D5] = sHonestBigPalette,
  [0x03D6] = sJunkSynchronBigPalette,
  [0x03D7] = sAmazonessAugustaBigPalette,
  [0x03D8] = sAmazonessEmpressBigPalette,
  [0x03D9] = sAmazonessPrincessBigPalette,
  [0x03DA] = sAmazonessQueenBigPalette,
  [0x03DB] = sAmazonessCallBigPalette,
  [0x03DC] = sAmazonessOnslaughtBigPalette,
  [0x03DD] = sAmazonessVillageBigPalette,
  [0x03DE] = sAshBlossomAndJoyousSpringBigPalette,
  [0x03DF] = sForbiddenChaliceBigPalette,
  [0x03E0] = sForbiddenLanceBigPalette,
  [0x03E1] = sGravekeepersChiefBigPalette,
  [0x03E2] = sGravekeepersCommandantBigPalette,
  [0x03E3] = sGravekeepersHeadmanBigPalette,
  [0x03E4] = sGravekeepersOracleBigPalette,
  [0x03E5] = sGravekeepersRecruiterBigPalette,
  [0x03E6] = sGravekeepersSpiritualistBigPalette,
  [0x03E7] = sGravekeepersTrapBigPalette,
  [0x03E8] = sImperialTombsOfNecrovalleyBigPalette,
  [0x03E9] = sInfiniteImpermanenceBigPalette,
  [0x03EA] = sHiddenTemplesOfNecrovalleyBigPalette,
  [0x03EB] = sLightningStormBigPalette,
  [0x03EC] = sPotOfAvariceBigPalette,
  [0x03ED] = sNumber39UtopiaBigPalette,
  [0x03EE] = sMaxxCBigPalette,
  [0x03EF] = sToadallyAwesomeBigPalette,
};

const u8 gCardArtUsesExtendedPalette_Hook[] APPEND_RODATA = {
  [0x00AE] = 0,
  [0x0137] = 0,
  [0x020B] = 0,
  [0x0321] = 0,
  [0x0322] = 0,
  [0x0323] = 0,
  [0x0324] = 0,
  [0x0325] = 0,
  [0x0326] = 0,
  [0x0327] = 0,
  [0x0328] = 0,
  [0x0329] = 0,
  [0x032A] = 0,
  [0x032B] = 0,
  [0x032C] = 0,
  [0x032D] = 0,
  [0x032E] = 0,
  [0x032F] = 0,
  [0x0330] = 0,
  [0x0331] = 0,
  [0x0332] = 0,
  [0x0333] = 0,
  [0x0334] = 0,
  [0x0335] = 0,
  [0x0336] = 0,
  [0x0337] = 0,
  [0x0338] = 0,
  [0x0339] = 0,
  [0x033A] = 0,
  [0x033B] = 0,
  [0x033C] = 0,
  [0x033D] = 0,
  [0x033E] = 0,
  [0x033F] = 0,
  [0x0340] = 0,
  [0x0341] = 0,
  [0x0342] = 0,
  [0x0343] = 0,
  [0x0344] = 0,
  [0x0345] = 0,
  [0x0346] = 0,
  [0x0347] = 0,
  [0x0348] = 0,
  [0x0349] = 0,
  [0x034A] = 0,
  [0x034B] = 0,
  [0x034C] = 0,
  [0x034D] = 0,
  [0x034E] = 0,
  [0x034F] = 0,
  [0x0350] = 0,
  [0x0351] = 0,
  [0x0352] = 0,
  [0x0353] = 0,
  [0x0354] = 0,
  [0x0355] = 0,
  [0x0356] = 0,
  [0x0357] = 0,
  [0x0358] = 0,
  [0x0359] = 0,
  [0x035A] = 0,
  [0x035B] = 0,
  [0x035C] = 0,
  [0x035D] = 0,
  [0x035E] = 0,
  [0x035F] = 0,
  [0x0360] = 0,
  [0x0361] = 0,
  [0x0362] = 0,
  [0x0363] = 0,
  [0x0364] = 0,
  [0x0365] = 0,
  [0x0366] = 0,
  [0x0367] = 0,
  [0x0368] = 0,
  [0x0369] = 0,
  [0x036A] = 0,
  [0x036B] = 0,
  [0x036C] = 0,
  [0x036D] = 0,
  [0x036E] = 0,
  [0x036F] = 0,
  [0x0370] = 0,
  [0x0371] = 0,
  [0x0372] = 0,
  [0x0373] = 0,
  [0x0374] = 0,
  [0x0375] = 0,
  [0x0376] = 0,
  [0x0377] = 0,
  [0x0378] = 0,
  [0x0379] = 0,
  [0x037A] = 0,
  [0x037B] = 0,
  [0x037C] = 0,
  [0x037D] = 0,
  [0x037E] = 0,
  [0x037F] = 0,
  [0x0380] = 0,
  [0x0381] = 0,
  [0x0382] = 0,
  [0x0383] = 0,
  [0x0384] = 0,
  [0x0385] = 0,
  [0x0386] = 0,
  [0x0387] = 0,
  [0x0388] = 0,
  [0x0389] = 0,
  [0x038A] = 0,
  [0x038B] = 0,
  [0x038C] = 0,
  [0x038D] = 0,
  [0x038E] = 0,
  [0x038F] = 0,
  [0x0390] = 0,
  [0x0391] = 0,
  [0x0392] = 0,
  [0x0393] = 0,
  [0x0394] = 0,
  [0x0395] = 0,
  [0x0396] = 0,
  [0x0397] = 0,
  [0x0398] = 0,
  [0x0399] = 0,
  [0x039A] = 0,
  [0x039B] = 0,
  [0x039C] = 0,
  [0x039D] = 0,
  [0x039E] = 0,
  [0x039F] = 0,
  [0x03A0] = 0,
  [0x03A1] = 0,
  [0x03A2] = 0,
  [0x03A3] = 0,
  [0x03A4] = 0,
  [0x03A5] = 0,
  [0x03A6] = 0,
  [0x03A7] = 0,
  [0x03A8] = 0,
  [0x03A9] = 0,
  [0x03AA] = 0,
  [0x03AB] = 0,
  [0x03AC] = 0,
  [0x03AD] = 0,
  [0x03AE] = 0,
  [0x03AF] = 0,
  [0x03B0] = 0,
  [0x03B1] = 0,
  [0x03B2] = 0,
  [0x03B3] = 0,
  [0x03B4] = 0,
  [0x03B5] = 0,
  [0x03B6] = 0,
  [0x03B7] = 0,
  [0x03B8] = 0,
  [0x03B9] = 0,
  [0x03BA] = 0,
  [0x03BB] = 0,
  [0x03BC] = 0,
  [0x03BD] = 0,
  [0x03BE] = 0,
  [0x03BF] = 0,
  [0x03C0] = 0,
  [0x03C1] = 0,
  [0x03C2] = 0,
  [0x03C3] = 0,
  [0x03C4] = 0,
  [0x03C5] = 0,
  [0x03C6] = 0,
  [0x03C7] = 0,
  [0x03C8] = 0,
  [0x03C9] = 0,
  [0x03CA] = 0,
  [0x03CB] = 0,
  [0x03CC] = 0,
  [0x03CD] = 0,
  [0x03CE] = 0,
  [0x03CF] = 0,
  [0x03D0] = 0,
  [0x03D1] = 0,
  [0x03D2] = 0,
  [0x03D3] = 0,
  [0x03D4] = 0,
  [0x03D5] = 0,
  [0x03D6] = 0,
  [0x03D7] = 0,
  [0x03D8] = 0,
  [0x03D9] = 0,
  [0x03DA] = 0,
  [0x03DB] = 0,
  [0x03DC] = 0,
  [0x03DD] = 0,
  [0x03DE] = 0,
  [0x03DF] = 0,
  [0x03E0] = 0,
  [0x03E1] = 0,
  [0x03E2] = 0,
  [0x03E3] = 0,
  [0x03E4] = 0,
  [0x03E5] = 0,
  [0x03E6] = 0,
  [0x03E7] = 0,
  [0x03E8] = 0,
  [0x03E9] = 0,
  [0x03EA] = 0,
  [0x03EB] = 0,
  [0x03EC] = 0,
  [0x03ED] = 0,
  [0x03EE] = 0,
  [0x03EF] = 0,
};

const unsigned char *gMiniCardArts_Hook[] APPEND_RODATA = {
  [0x00AE] = sSenjuOfTheThousandHandsMiniArt,
  [0x0137] = sBlackPendantMiniArt,
  [0x020B] = sTheBistroButcherMiniArt,
  [0x0321] = sBlueEyesShiningDragonMiniArt,
  [0x0322] = sBlueEyesChaosMaxDragonMiniArt,
  [0x0323] = sKaibamanMiniArt,
  [0x0324] = sUltimateOfferingMiniArt,
  [0x0325] = sWaveMotionCannonMiniArt,
  [0x0326] = sSoulExchangeMiniArt,
  [0x0327] = sMysticalSpaceTyphoonMiniArt,
  [0x0328] = sRareMetalDragonMiniArt,
  [0x0329] = sMaskOfRestrictMiniArt,
  [0x032A] = sBlueEyesAlternativeWhiteDragonMiniArt,
  [0x032B] = sSealOfOrichalcosMiniArt,
  [0x032C] = sSkillDrainMiniArt,
  [0x032D] = sMagicCylinderMiniArt,
  [0x032E] = sDelinquentDuoMiniArt,
  [0x032F] = sYataGarasuMiniArt,
  [0x0330] = sUpstartGoblinMiniArt,
  [0x0331] = sCallOfTheHauntedMiniArt,
  [0x0332] = sSwiftGaiaTheFierceKnightMiniArt,
  [0x0333] = sLimiterRemovalMiniArt,
  [0x0334] = sRecklessGreedMiniArt,
  [0x0335] = sCardDestructionMiniArt,
  [0x0336] = sGracefulCharityMiniArt,
  [0x0337] = sImperialOrderMiniArt,
  [0x0338] = sRoyalDecreeMiniArt,
  [0x0339] = sDoubleCostonMiniArt,
  [0x033A] = sFinalCountdownMiniArt,
  [0x033B] = sBookOfMoonMiniArt,
  [0x033C] = sAmazonessTigerMiniArt,
  [0x033D] = sConfiscationMiniArt,
  [0x033E] = sZaborgTheThunderMonarchMiniArt,
  [0x033F] = sPolymerizationMiniArt,
  [0x0340] = sCyberDragonMiniArt,
  [0x0341] = sCyberTwinDragonMiniArt,
  [0x0342] = sCyberEndDragonMiniArt,
  [0x0343] = sCaiusTheShadowMonarchMiniArt,
  [0x0344] = sMobiusTheFrostMonarchMiniArt,
  [0x0345] = sProtoCyberDragonMiniArt,
  [0x0346] = sAmazonessArcherMiniArt,
  [0x0347] = sElementalHeroWildheartMiniArt,
  [0x0348] = sTheSanctuaryInTheSkyMiniArt,
  [0x0349] = sMirrorForceMiniArt,
  [0x034A] = sBlueEyesChaosDragonMiniArt,
  [0x034B] = sDeFusionMiniArt,
  [0x034C] = sALegendaryOceanMiniArt,
  [0x034D] = sDarkMagicianOfChaosMiniArt,
  [0x034E] = sElementalHeroPhoenixEnforcerMiniArt,
  [0x034F] = sElementalHeroFlameWingmanMiniArt,
  [0x0350] = sElementalHeroShiningFlareWingmanMiniArt,
  [0x0351] = sMiracleFusionMiniArt,
  [0x0352] = sChaosEmperorDragonEnvoyOfTheEndMiniArt,
  [0x0353] = sBlackLusterSoldierEnvoyOfTheBeginningMiniArt,
  [0x0354] = sElementalHeroNeosMiniArt,
  [0x0355] = sFusionRecoveryMiniArt,
  [0x0356] = sSkyscraperMiniArt,
  [0x0357] = sHHeatedHeartMiniArt,
  [0x0358] = sEEmergencyCallMiniArt,
  [0x0359] = sElementalHeroIceEdgeMiniArt,
  [0x035A] = sElementalHeroBlazemanMiniArt,
  [0x035B] = sElementalHeroStratosMiniArt,
  [0x035C] = sChimeratechOverdragonMiniArt,
  [0x035D] = sCyberneticFusionSupportMiniArt,
  [0x035E] = sOverloadFusionMiniArt,
  [0x035F] = sPowerBondMiniArt,
  [0x0360] = sDivineSanctuaryMiniArt,
  [0x0361] = sYubelMiniArt,
  [0x0362] = sYubelTerrorIncarnateMiniArt,
  [0x0363] = sYubelTheUltimateNightmareMiniArt,
  [0x0364] = sTradeInMiniArt,
  [0x0365] = sCyberBarrierDragonMiniArt,
  [0x0366] = sCyberLaserDragonMiniArt,
  [0x0367] = sDestinyHeroBladeMasterMiniArt,
  [0x0368] = sDestinyHeroCaptainTenaciousMiniArt,
  [0x0369] = sDestinyHeroCelestialMiniArt,
  [0x036A] = sDestinyHeroDangerousMiniArt,
  [0x036B] = sDestinyHeroDasherMiniArt,
  [0x036C] = sDoomVirusDragonMiniArt,
  [0x036D] = sInstantFusionMiniArt,
  [0x036E] = sJudgmentDragonMiniArt,
  [0x036F] = sManjuOfTheTenThousandHandsMiniArt,
  [0x0370] = sMarshmallonMiniArt,
  [0x0371] = sNecrovalleyMiniArt,
  [0x0372] = sNibiruThePrimalBeingMiniArt,
  [0x0373] = sPhotonGeneratorUnitMiniArt,
  [0x0374] = sReaperScytheDreadscytheMiniArt,
  [0x0375] = sRedEyesBlackDragonSwordMiniArt,
  [0x0376] = sRedGadgetMiniArt,
  [0x0377] = sRocketHermosCannonMiniArt,
  [0x0378] = sScapegoatMiniArt,
  [0x0379] = sSolemnJudgmentMiniArt,
  [0x037A] = sSuperPolymerizationMiniArt,
  [0x037B] = sVisionHeroAdorationMiniArt,
  [0x037C] = sVisionHeroFarisMiniArt,
  [0x037D] = sVisionHeroGravitoMiniArt,
  [0x037E] = sVisionHeroIncreaseMiniArt,
  [0x037F] = sAromaBlendMiniArt,
  [0x0380] = sAromaGardenMiniArt,
  [0x0381] = sAromaGardeningMiniArt,
  [0x0382] = sAromaJarMiniArt,
  [0x0383] = sBlueEyesJetDragonMiniArt,
  [0x0384] = sBlueEyesSolidDragonMiniArt,
  [0x0385] = sBrionacDragonOfTheIceBarrierMiniArt,
  [0x0386] = sCyberSlashHarpieLadyMiniArt,
  [0x0387] = sDarkMagicAttackMiniArt,
  [0x0388] = sDarkMagicInheritanceMiniArt,
  [0x0389] = sDarkMagicVeilMiniArt,
  [0x038A] = sDarkMagicalCircleMiniArt,
  [0x038B] = sDarkMagicianOfDestructionMiniArt,
  [0x038C] = sDeepEyesWhiteDragonMiniArt,
  [0x038D] = sDragonSpiritOfWhiteMiniArt,
  [0x038E] = sElShaddollConstructMiniArt,
  [0x038F] = sElShaddollWindaMiniArt,
  [0x0390] = sEternalSoulMiniArt,
  [0x0391] = sEvilHeroAdustedGoldMiniArt,
  [0x0392] = sEvilHeroDarkGaiaMiniArt,
  [0x0393] = sEvilHeroDarkestKnightMiniArt,
  [0x0394] = sEvilHeroDeadEndPrisonMiniArt,
  [0x0395] = sEvilHeroInfernalGainerMiniArt,
  [0x0396] = sGoyoGuardianMiniArt,
  [0x0397] = sHarpieChannelerMiniArt,
  [0x0398] = sHarpieConductorMiniArt,
  [0x0399] = sHarpieDancerMiniArt,
  [0x039A] = sHarpieHarpistMiniArt,
  [0x039B] = sHarpieLadyEleganceMiniArt,
  [0x039C] = sHarpieOracleMiniArt,
  [0x039D] = sHarpiePerfumerMiniArt,
  [0x039E] = sHarpieQueenMiniArt,
  [0x039F] = sHarpiesFeatherRestMiniArt,
  [0x03A0] = sHarpiesFeatherStormMiniArt,
  [0x03A1] = sHarpiesHuntingGroundMiniArt,
  [0x03A2] = sHarpiesPetPhantasmalDragonMiniArt,
  [0x03A3] = sJunkWarriorMiniArt,
  [0x03A4] = sMagicianOfDarkIllusionMiniArt,
  [0x03A5] = sMagiciansRodMiniArt,
  [0x03A6] = sMagiciansSoulsMiniArt,
  [0x03A7] = sMasterOfChaosMiniArt,
  [0x03A8] = sRedDragonArchfiendMiniArt,
  [0x03A9] = sReptilianneGardnaMiniArt,
  [0x03AA] = sReptilianneGorgonMiniArt,
  [0x03AB] = sReptilianneHydraMiniArt,
  [0x03AC] = sReturnOfTheDragonLordsMiniArt,
  [0x03AD] = sSecretsOfDarkMagicMiniArt,
  [0x03AE] = sShaddollBeastMiniArt,
  [0x03AF] = sShaddollDragonMiniArt,
  [0x03B0] = sShaddollFusionMiniArt,
  [0x03B1] = sShaddollHedgehogMiniArt,
  [0x03B2] = sShaddollSquamataMiniArt,
  [0x03B3] = sSilversCryMiniArt,
  [0x03B4] = sSoulServantMiniArt,
  [0x03B5] = sStardustDragonMiniArt,
  [0x03B6] = sTheMelodyOfAwakeningDragonMiniArt,
  [0x03B7] = sTheWhiteStoneOfAncientsMiniArt,
  [0x03B8] = sTheWhiteStoneOfLegendMiniArt,
  [0x03B9] = sVenomBoaMiniArt,
  [0x03BA] = sVenomBurnMiniArt,
  [0x03BB] = sArcanaForce0TheFoolMiniArt,
  [0x03BC] = sArcanaForceExTheDarkRulerMiniArt,
  [0x03BD] = sArcanaForceITheMagicianMiniArt,
  [0x03BE] = sGladiatorBeastAlexanderMiniArt,
  [0x03BF] = sGladiatorBeastAttorixMiniArt,
  [0x03C0] = sGladiatorBeastAugustusMiniArt,
  [0x03C1] = sGladiatorBeastBattleHalberdMiniArt,
  [0x03C2] = sGladiatorBeastBestiariMiniArt,
  [0x03C3] = sGladiatorBeastClaudiusMiniArt,
  [0x03C4] = sLightswornAegisMiniArt,
  [0x03C5] = sLightswornBarrierMiniArt,
  [0x03C6] = sLightswornDragonlingMiniArt,
  [0x03C7] = sLightswornJudgementMiniArt,
  [0x03C8] = sLightswornSabreMiniArt,
  [0x03C9] = sLightswornSanctuaryMiniArt,
  [0x03CA] = sNeoSpacianAirHummingbirdMiniArt,
  [0x03CB] = sNeoSpacianAquaDolphinMiniArt,
  [0x03CC] = sNeoSpacianFlareScarabMiniArt,
  [0x03CD] = sNeoSpacianGlowMossMiniArt,
  [0x03CE] = sAncientGearMiniArt,
  [0x03CF] = sAncientGearAdvanceMiniArt,
  [0x03D0] = sAncientGearBeastMiniArt,
  [0x03D1] = sAncientGearCannonMiniArt,
  [0x03D2] = sAncientGearCastleMiniArt,
  [0x03D3] = sCyberDragonInfinityMiniArt,
  [0x03D4] = sEvolzarDolkkaMiniArt,
  [0x03D5] = sHonestMiniArt,
  [0x03D6] = sJunkSynchronMiniArt,
  [0x03D7] = sAmazonessAugustaMiniArt,
  [0x03D8] = sAmazonessEmpressMiniArt,
  [0x03D9] = sAmazonessPrincessMiniArt,
  [0x03DA] = sAmazonessQueenMiniArt,
  [0x03DB] = sAmazonessCallMiniArt,
  [0x03DC] = sAmazonessOnslaughtMiniArt,
  [0x03DD] = sAmazonessVillageMiniArt,
  [0x03DE] = sAshBlossomAndJoyousSpringMiniArt,
  [0x03DF] = sForbiddenChaliceMiniArt,
  [0x03E0] = sForbiddenLanceMiniArt,
  [0x03E1] = sGravekeepersChiefMiniArt,
  [0x03E2] = sGravekeepersCommandantMiniArt,
  [0x03E3] = sGravekeepersHeadmanMiniArt,
  [0x03E4] = sGravekeepersOracleMiniArt,
  [0x03E5] = sGravekeepersRecruiterMiniArt,
  [0x03E6] = sGravekeepersSpiritualistMiniArt,
  [0x03E7] = sGravekeepersTrapMiniArt,
  [0x03E8] = sImperialTombsOfNecrovalleyMiniArt,
  [0x03E9] = sInfiniteImpermanenceMiniArt,
  [0x03EA] = sHiddenTemplesOfNecrovalleyMiniArt,
  [0x03EB] = sLightningStormMiniArt,
  [0x03EC] = sPotOfAvariceMiniArt,
  [0x03ED] = sNumber39UtopiaMiniArt,
  [0x03EE] = sMaxxCMiniArt,
  [0x03EF] = sToadallyAwesomeMiniArt,
};
