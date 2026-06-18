#include "global.h"

static const unsigned char sGiantRatBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/giant_rat.huff");
static const unsigned short sGiantRatBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/giant_rat.gbapal");
static const unsigned char sGiantRatMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/giant_rat.lz");

static const unsigned char sSenjuOfTheThousandHandsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/senju_of_the_thousand_hands.huff");
static const unsigned short sSenjuOfTheThousandHandsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/senju_of_the_thousand_hands.gbapal");
static const unsigned char sSenjuOfTheThousandHandsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/senju_of_the_thousand_hands.lz");

static const unsigned char sBlackPendantBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/black_pendant.huff");
static const unsigned short sBlackPendantBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/black_pendant.gbapal");
static const unsigned char sBlackPendantMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/black_pendant.lz");

static const unsigned char sSorcererOfDarkMagicBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/sorcerer_of_dark_magic.huff");
static const unsigned short sSorcererOfDarkMagicBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/sorcerer_of_dark_magic.gbapal");
static const unsigned char sSorcererOfDarkMagicMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/sorcerer_of_dark_magic.lz");

static const unsigned char sDeckDestructionVirusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/deck_destruction_virus.huff");
static const unsigned short sDeckDestructionVirusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/deck_destruction_virus.gbapal");
static const unsigned char sDeckDestructionVirusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/deck_destruction_virus.lz");

static const unsigned char sMagiciansValkyriaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magicians_valkyria.huff");
static const unsigned short sMagiciansValkyriaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magicians_valkyria.gbapal");
static const unsigned char sMagiciansValkyriaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magicians_valkyria.lz");

static const unsigned char sBlueEyesShiningDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_shining_dragon.huff");
static const unsigned short sBlueEyesShiningDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_shining_dragon.gbapal");
static const unsigned char sBlueEyesShiningDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_shining_dragon.lz");

static const unsigned char sPaladinOfWhiteDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/paladin_of_white_dragon.huff");
static const unsigned short sPaladinOfWhiteDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/paladin_of_white_dragon.gbapal");
static const unsigned char sPaladinOfWhiteDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/paladin_of_white_dragon.lz");

static const unsigned char sCardOfDemiseBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/card_of_demise.huff");
static const unsigned short sCardOfDemiseBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/card_of_demise.gbapal");
static const unsigned char sCardOfDemiseMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/card_of_demise.lz");

static const unsigned char sCardOfSanctityBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/card_of_sanctity.huff");
static const unsigned short sCardOfSanctityBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/card_of_sanctity.gbapal");
static const unsigned char sCardOfSanctityMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/card_of_sanctity.lz");

static const unsigned char sShieldAndSwordBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shield_and_sword.huff");
static const unsigned short sShieldAndSwordBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shield_and_sword.gbapal");
static const unsigned char sShieldAndSwordMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shield_and_sword.lz");

static const unsigned char sBlueEyesChaosMaxDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_chaos_max_dragon.huff");
static const unsigned short sBlueEyesChaosMaxDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_chaos_max_dragon.gbapal");
static const unsigned char sBlueEyesChaosMaxDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_chaos_max_dragon.lz");

static const unsigned char sChainEnergyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chain_energy.huff");
static const unsigned short sChainEnergyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chain_energy.gbapal");
static const unsigned char sChainEnergyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chain_energy.lz");

static const unsigned char sSpellCancellerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/spell_canceller.huff");
static const unsigned short sSpellCancellerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/spell_canceller.gbapal");
static const unsigned char sSpellCancellerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/spell_canceller.lz");

static const unsigned char sExchangeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/exchange.huff");
static const unsigned short sExchangeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/exchange.gbapal");
static const unsigned char sExchangeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/exchange.lz");

static const unsigned char sCopycatBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/copycat.huff");
static const unsigned short sCopycatBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/copycat.gbapal");
static const unsigned char sCopycatMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/copycat.lz");

static const unsigned char sMagePowerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mage_power.huff");
static const unsigned short sMagePowerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mage_power.gbapal");
static const unsigned char sMagePowerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mage_power.lz");

static const unsigned char sKaibamanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/kaibaman.huff");
static const unsigned short sKaibamanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/kaibaman.gbapal");
static const unsigned char sKaibamanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/kaibaman.lz");

static const unsigned char sUltimateOfferingBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ultimate_offering.huff");
static const unsigned short sUltimateOfferingBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ultimate_offering.gbapal");
static const unsigned char sUltimateOfferingMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ultimate_offering.lz");

static const unsigned char sUnitedWeStandBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/united_we_stand.huff");
static const unsigned short sUnitedWeStandBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/united_we_stand.gbapal");
static const unsigned char sUnitedWeStandMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/united_we_stand.lz");

static const unsigned char sWaveMotionCannonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/wave_motion_cannon.huff");
static const unsigned short sWaveMotionCannonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/wave_motion_cannon.gbapal");
static const unsigned char sWaveMotionCannonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/wave_motion_cannon.lz");

static const unsigned char sStJoanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/st_joan.huff");
static const unsigned short sStJoanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/st_joan.gbapal");
static const unsigned char sStJoanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/st_joan.lz");

static const unsigned char sPyramidOfLightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/pyramid_of_light.huff");
static const unsigned short sPyramidOfLightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/pyramid_of_light.gbapal");
static const unsigned char sPyramidOfLightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/pyramid_of_light.lz");

static const unsigned char sSoulExchangeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/soul_exchange.huff");
static const unsigned short sSoulExchangeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/soul_exchange.gbapal");
static const unsigned char sSoulExchangeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/soul_exchange.lz");

static const unsigned char sMysticalSpaceTyphoonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mystical_space_typhoon.huff");
static const unsigned short sMysticalSpaceTyphoonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mystical_space_typhoon.gbapal");
static const unsigned char sMysticalSpaceTyphoonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mystical_space_typhoon.lz");

static const unsigned char sRareMetalDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/rare_metal_dragon.huff");
static const unsigned short sRareMetalDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/rare_metal_dragon.gbapal");
static const unsigned char sRareMetalDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/rare_metal_dragon.lz");

static const unsigned char sDoubleSummonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/double_summon.huff");
static const unsigned short sDoubleSummonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/double_summon.gbapal");
static const unsigned char sDoubleSummonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/double_summon.lz");

static const unsigned char sObnoxiousCelticGuardianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/obnoxious_celtic_guardian.huff");
static const unsigned short sObnoxiousCelticGuardianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/obnoxious_celtic_guardian.gbapal");
static const unsigned char sObnoxiousCelticGuardianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/obnoxious_celtic_guardian.lz");

static const unsigned char sMaskOfRestrictBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mask_of_restrict.huff");
static const unsigned short sMaskOfRestrictBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mask_of_restrict.gbapal");
static const unsigned char sMaskOfRestrictMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mask_of_restrict.lz");

static const unsigned char sFairyBoxBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/fairy_box.huff");
static const unsigned short sFairyBoxBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/fairy_box.gbapal");
static const unsigned char sFairyBoxMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/fairy_box.lz");

static const unsigned char sCostDownBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cost_down.huff");
static const unsigned short sCostDownBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cost_down.gbapal");
static const unsigned char sCostDownMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cost_down.lz");

static const unsigned char sBlueEyesAlternativeWhiteDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_alternative_white_dragon.huff");
static const unsigned short sBlueEyesAlternativeWhiteDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_alternative_white_dragon.gbapal");
static const unsigned char sBlueEyesAlternativeWhiteDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_alternative_white_dragon.lz");

static const unsigned char sAncientRulesBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_rules.huff");
static const unsigned short sAncientRulesBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_rules.gbapal");
static const unsigned char sAncientRulesMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_rules.lz");

static const unsigned char sMagicJammerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magic_jammer.huff");
static const unsigned short sMagicJammerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magic_jammer.gbapal");
static const unsigned char sMagicJammerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magic_jammer.lz");

static const unsigned char sSealOfOrichalcosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/seal_of_orichalcos.huff");
static const unsigned short sSealOfOrichalcosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/seal_of_orichalcos.gbapal");
static const unsigned char sSealOfOrichalcosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/seal_of_orichalcos.lz");

static const unsigned char sFamiliarKnightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/familiar_knight.huff");
static const unsigned short sFamiliarKnightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/familiar_knight.gbapal");
static const unsigned char sFamiliarKnightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/familiar_knight.lz");

static const unsigned char sRiryokuBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/riryoku.huff");
static const unsigned short sRiryokuBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/riryoku.gbapal");
static const unsigned char sRiryokuMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/riryoku.lz");

static const unsigned char sSpearDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/spear_dragon.huff");
static const unsigned short sSpearDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/spear_dragon.gbapal");
static const unsigned char sSpearDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/spear_dragon.lz");

static const unsigned char sSagesStoneBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/sages_stone.huff");
static const unsigned short sSagesStoneBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/sages_stone.gbapal");
static const unsigned char sSagesStoneMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/sages_stone.lz");

static const unsigned char sBowganianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/bowganian.huff");
static const unsigned short sBowganianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/bowganian.gbapal");
static const unsigned char sBowganianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/bowganian.lz");

static const unsigned char sDarkMagicCurtainBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_magic_curtain.huff");
static const unsigned short sDarkMagicCurtainBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_magic_curtain.gbapal");
static const unsigned char sDarkMagicCurtainMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_magic_curtain.lz");

static const unsigned char sCatsEarTribeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cats_ear_tribe.huff");
static const unsigned short sCatsEarTribeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cats_ear_tribe.gbapal");
static const unsigned char sCatsEarTribeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cats_ear_tribe.lz");

static const unsigned char sCureMermaidBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cure_mermaid.huff");
static const unsigned short sCureMermaidBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cure_mermaid.gbapal");
static const unsigned char sCureMermaidMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cure_mermaid.lz");

static const unsigned char sDesKoalaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/des_koala.huff");
static const unsigned short sDesKoalaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/des_koala.gbapal");
static const unsigned char sDesKoalaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/des_koala.lz");

static const unsigned char sSkillDrainBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/skill_drain.huff");
static const unsigned short sSkillDrainBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/skill_drain.gbapal");
static const unsigned char sSkillDrainMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/skill_drain.lz");

static const unsigned char sGuardianTreasureBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/guardian_treasure.huff");
static const unsigned short sGuardianTreasureBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/guardian_treasure.gbapal");
static const unsigned char sGuardianTreasureMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/guardian_treasure.lz");

static const unsigned char sJarOfGreedBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/jar_of_greed.huff");
static const unsigned short sJarOfGreedBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/jar_of_greed.gbapal");
static const unsigned char sJarOfGreedMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/jar_of_greed.lz");

static const unsigned char sMadSwordBeastBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mad_sword_beast.huff");
static const unsigned short sMadSwordBeastBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mad_sword_beast.gbapal");
static const unsigned char sMadSwordBeastMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mad_sword_beast.lz");

static const unsigned char sOjamaTrioBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ojama_trio.huff");
static const unsigned short sOjamaTrioBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ojama_trio.gbapal");
static const unsigned char sOjamaTrioMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ojama_trio.lz");

static const unsigned char sLusterDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/luster_dragon.huff");
static const unsigned short sLusterDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/luster_dragon.gbapal");
static const unsigned char sLusterDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/luster_dragon.lz");

static const unsigned char sMysticalShineBallBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mystical_shine_ball.huff");
static const unsigned short sMysticalShineBallBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mystical_shine_ball.gbapal");
static const unsigned char sMysticalShineBallMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mystical_shine_ball.lz");

static const unsigned char sGoblinThiefBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/goblin_thief.huff");
static const unsigned short sGoblinThiefBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/goblin_thief.gbapal");
static const unsigned char sGoblinThiefMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/goblin_thief.lz");

static const unsigned char sHayabusaKnightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/hayabusa_knight.huff");
static const unsigned short sHayabusaKnightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/hayabusa_knight.gbapal");
static const unsigned char sHayabusaKnightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/hayabusa_knight.lz");

static const unsigned char sMagicCylinderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magic_cylinder.huff");
static const unsigned short sMagicCylinderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magic_cylinder.gbapal");
static const unsigned char sMagicCylinderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magic_cylinder.lz");

static const unsigned char sBlockAttackBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/block_attack.huff");
static const unsigned short sBlockAttackBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/block_attack.gbapal");
static const unsigned char sBlockAttackMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/block_attack.lz");

static const unsigned char sDelinquentDuoBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/delinquent_duo.huff");
static const unsigned short sDelinquentDuoBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/delinquent_duo.gbapal");
static const unsigned char sDelinquentDuoMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/delinquent_duo.lz");

static const unsigned char sDrainingShieldBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/draining_shield.huff");
static const unsigned short sDrainingShieldBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/draining_shield.gbapal");
static const unsigned char sDrainingShieldMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/draining_shield.lz");

static const unsigned char sMeteorOfDestructionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/meteor_of_destruction.huff");
static const unsigned short sMeteorOfDestructionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/meteor_of_destruction.gbapal");
static const unsigned char sMeteorOfDestructionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/meteor_of_destruction.lz");

static const unsigned char sTollBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/toll.huff");
static const unsigned short sTollBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/toll.gbapal");
static const unsigned char sTollMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/toll.lz");

static const unsigned char sRainOfMercyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/rain_of_mercy.huff");
static const unsigned short sRainOfMercyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/rain_of_mercy.gbapal");
static const unsigned char sRainOfMercyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/rain_of_mercy.lz");

static const unsigned char sSolarFlareDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/solar_flare_dragon.huff");
static const unsigned short sSolarFlareDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/solar_flare_dragon.gbapal");
static const unsigned char sSolarFlareDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/solar_flare_dragon.lz");

static const unsigned char sYataGarasuBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/yata_garasu.huff");
static const unsigned short sYataGarasuBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/yata_garasu.gbapal");
static const unsigned char sYataGarasuMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/yata_garasu.lz");

static const unsigned char sUpstartGoblinBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/upstart_goblin.huff");
static const unsigned short sUpstartGoblinBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/upstart_goblin.gbapal");
static const unsigned char sUpstartGoblinMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/upstart_goblin.lz");

static const unsigned char sNegateAttackBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/negate_attack.huff");
static const unsigned short sNegateAttackBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/negate_attack.gbapal");
static const unsigned char sNegateAttackMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/negate_attack.lz");

static const unsigned char sReloadBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reload.huff");
static const unsigned short sReloadBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reload.gbapal");
static const unsigned char sReloadMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reload.lz");

static const unsigned char sMaraudingCaptainBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/marauding_captain.huff");
static const unsigned short sMaraudingCaptainBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/marauding_captain.gbapal");
static const unsigned char sMaraudingCaptainMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/marauding_captain.lz");

static const unsigned char sSecretBarrelBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/secret_barrel.huff");
static const unsigned short sSecretBarrelBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/secret_barrel.gbapal");
static const unsigned char sSecretBarrelMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/secret_barrel.lz");

static const unsigned char sRobbinGoblinBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/robbin_goblin.huff");
static const unsigned short sRobbinGoblinBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/robbin_goblin.gbapal");
static const unsigned char sRobbinGoblinMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/robbin_goblin.lz");

static const unsigned char sRobbinZombieBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/robbin_zombie.huff");
static const unsigned short sRobbinZombieBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/robbin_zombie.gbapal");
static const unsigned char sRobbinZombieMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/robbin_zombie.lz");

static const unsigned char sCallOfTheHauntedBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/call_of_the_haunted.huff");
static const unsigned short sCallOfTheHauntedBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/call_of_the_haunted.gbapal");
static const unsigned char sCallOfTheHauntedMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/call_of_the_haunted.lz");

static const unsigned char sKaiserGliderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/kaiser_glider.huff");
static const unsigned short sKaiserGliderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/kaiser_glider.gbapal");
static const unsigned char sKaiserGliderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/kaiser_glider.lz");

static const unsigned char sPiranhaArmyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/piranha_army.huff");
static const unsigned short sPiranhaArmyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/piranha_army.gbapal");
static const unsigned char sPiranhaArmyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/piranha_army.lz");

static const unsigned char sMoisterCreatureBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/moister_creature.huff");
static const unsigned short sMoisterCreatureBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/moister_creature.gbapal");
static const unsigned char sMoisterCreatureMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/moister_creature.lz");

static const unsigned char sWhiteMagicianPikeruBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/white_magician_pikeru.huff");
static const unsigned short sWhiteMagicianPikeruBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/white_magician_pikeru.gbapal");
static const unsigned char sWhiteMagicianPikeruMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/white_magician_pikeru.lz");

static const unsigned char sEbonMagicianCurranBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ebon_magician_curran.huff");
static const unsigned short sEbonMagicianCurranBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ebon_magician_curran.gbapal");
static const unsigned char sEbonMagicianCurranMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ebon_magician_curran.lz");

static const unsigned char sWeatherReportBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/weather_report.huff");
static const unsigned short sWeatherReportBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/weather_report.gbapal");
static const unsigned char sWeatherReportMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/weather_report.lz");

static const unsigned char sWarriorOfZeraBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/warrior_of_zera.huff");
static const unsigned short sWarriorOfZeraBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/warrior_of_zera.gbapal");
static const unsigned char sWarriorOfZeraMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/warrior_of_zera.lz");

static const unsigned char sTimeSealBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/time_seal.huff");
static const unsigned short sTimeSealBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/time_seal.gbapal");
static const unsigned char sTimeSealMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/time_seal.lz");

static const unsigned char sThousandEnergyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/thousand_energy.huff");
static const unsigned short sThousandEnergyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/thousand_energy.gbapal");
static const unsigned char sThousandEnergyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/thousand_energy.lz");

static const unsigned char sTheDarkDoorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_dark_door.huff");
static const unsigned short sTheDarkDoorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_dark_door.gbapal");
static const unsigned char sTheDarkDoorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_dark_door.lz");

static const unsigned char sSwiftGaiaTheFierceKnightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/swift_gaia_the_fierce_knight.huff");
static const unsigned short sSwiftGaiaTheFierceKnightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/swift_gaia_the_fierce_knight.gbapal");
static const unsigned char sSwiftGaiaTheFierceKnightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/swift_gaia_the_fierce_knight.lz");

static const unsigned char sSelfDestructButtonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/self_destruct_button.huff");
static const unsigned short sSelfDestructButtonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/self_destruct_button.gbapal");
static const unsigned char sSelfDestructButtonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/self_destruct_button.lz");

static const unsigned char sSkullInvitationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/skull_invitation.huff");
static const unsigned short sSkullInvitationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/skull_invitation.gbapal");
static const unsigned char sSkullInvitationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/skull_invitation.lz");

static const unsigned char sNightmareHorseBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/nightmare_horse.huff");
static const unsigned short sNightmareHorseBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/nightmare_horse.gbapal");
static const unsigned char sNightmareHorseMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/nightmare_horse.lz");

static const unsigned char sVampireBabyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vampire_baby.huff");
static const unsigned short sVampireBabyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vampire_baby.gbapal");
static const unsigned char sVampireBabyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vampire_baby.lz");

static const unsigned char sTheForcefulSentryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_forceful_sentry.huff");
static const unsigned short sTheForcefulSentryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_forceful_sentry.gbapal");
static const unsigned char sTheForcefulSentryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_forceful_sentry.lz");

static const unsigned char sTerrorkingSalmonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/terrorking_salmon.huff");
static const unsigned short sTerrorkingSalmonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/terrorking_salmon.gbapal");
static const unsigned char sTerrorkingSalmonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/terrorking_salmon.lz");

static const unsigned char sSasukeSamuraiBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/sasuke_samurai.huff");
static const unsigned short sSasukeSamuraiBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/sasuke_samurai.gbapal");
static const unsigned char sSasukeSamuraiMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/sasuke_samurai.lz");

static const unsigned char sMaryokutaiBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/maryokutai.huff");
static const unsigned short sMaryokutaiBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/maryokutai.gbapal");
static const unsigned char sMaryokutaiMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/maryokutai.lz");

static const unsigned char sMermaidKnightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mermaid_knight.huff");
static const unsigned short sMermaidKnightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mermaid_knight.gbapal");
static const unsigned char sMermaidKnightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mermaid_knight.lz");

static const unsigned char sMefistTheInfernalGeneralBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mefist_the_infernal_general.huff");
static const unsigned short sMefistTheInfernalGeneralBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mefist_the_infernal_general.gbapal");
static const unsigned char sMefistTheInfernalGeneralMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mefist_the_infernal_general.lz");

static const unsigned char sGuardianAngelJoanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/guardian_angel_joan.huff");
static const unsigned short sGuardianAngelJoanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/guardian_angel_joan.gbapal");
static const unsigned char sGuardianAngelJoanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/guardian_angel_joan.lz");

static const unsigned char sPetenTheDarkClownBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/peten_the_dark_clown.huff");
static const unsigned short sPetenTheDarkClownBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/peten_the_dark_clown.gbapal");
static const unsigned char sPetenTheDarkClownMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/peten_the_dark_clown.lz");

static const unsigned char sLimiterRemovalBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/limiter_removal.huff");
static const unsigned short sLimiterRemovalBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/limiter_removal.gbapal");
static const unsigned char sLimiterRemovalMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/limiter_removal.lz");

static const unsigned char sJustDesertsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/just_deserts.huff");
static const unsigned short sJustDesertsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/just_deserts.gbapal");
static const unsigned char sJustDesertsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/just_deserts.lz");

static const unsigned char sGilasaurusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gilasaurus.huff");
static const unsigned short sGilasaurusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gilasaurus.gbapal");
static const unsigned char sGilasaurusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gilasaurus.lz");

static const unsigned char sGravityBindBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gravity_bind.huff");
static const unsigned short sGravityBindBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gravity_bind.gbapal");
static const unsigned char sGravityBindMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gravity_bind.lz");

static const unsigned char sGiftOfTheMysticalElfBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gift_of_the_mystical_elf.huff");
static const unsigned short sGiftOfTheMysticalElfBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gift_of_the_mystical_elf.gbapal");
static const unsigned char sGiftOfTheMysticalElfMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gift_of_the_mystical_elf.lz");

static const unsigned char sRecklessGreedBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reckless_greed.huff");
static const unsigned short sRecklessGreedBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reckless_greed.gbapal");
static const unsigned char sRecklessGreedMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reckless_greed.lz");

static const unsigned char sAirknightParshathBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/airknight_parshath.huff");
static const unsigned short sAirknightParshathBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/airknight_parshath.gbapal");
static const unsigned char sAirknightParshathMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/airknight_parshath.lz");

static const unsigned char sAmphibiousBugrothMk3BigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/amphibious_bugroth_mk_3.huff");
static const unsigned short sAmphibiousBugrothMk3BigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/amphibious_bugroth_mk_3.gbapal");
static const unsigned char sAmphibiousBugrothMk3MiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/amphibious_bugroth_mk_3.lz");

static const unsigned char sBlackTyrannoBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/black_tyranno.huff");
static const unsigned short sBlackTyrannoBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/black_tyranno.gbapal");
static const unsigned char sBlackTyrannoMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/black_tyranno.lz");

static const unsigned char sTheAgentOfCreationVenusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_agent_of_creation_venus.huff");
static const unsigned short sTheAgentOfCreationVenusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_agent_of_creation_venus.gbapal");
static const unsigned char sTheAgentOfCreationVenusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_agent_of_creation_venus.lz");

static const unsigned char sBlastingTheRuinsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blasting_the_ruins.huff");
static const unsigned short sBlastingTheRuinsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blasting_the_ruins.gbapal");
static const unsigned char sBlastingTheRuinsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blasting_the_ruins.lz");

static const unsigned char sCurseOfDarknessBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/curse_of_darkness.huff");
static const unsigned short sCurseOfDarknessBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/curse_of_darkness.gbapal");
static const unsigned char sCurseOfDarknessMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/curse_of_darkness.lz");

static const unsigned char sCoffinSellerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/coffin_seller.huff");
static const unsigned short sCoffinSellerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/coffin_seller.gbapal");
static const unsigned char sCoffinSellerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/coffin_seller.lz");

static const unsigned char sCardDestructionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/card_destruction.huff");
static const unsigned short sCardDestructionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/card_destruction.gbapal");
static const unsigned char sCardDestructionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/card_destruction.lz");

static const unsigned char sDarkRoomOfNightmareBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_room_of_nightmare.huff");
static const unsigned short sDarkRoomOfNightmareBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_room_of_nightmare.gbapal");
static const unsigned char sDarkRoomOfNightmareMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_room_of_nightmare.lz");

static const unsigned char sDarkDriceratopsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_driceratops.huff");
static const unsigned short sDarkDriceratopsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_driceratops.gbapal");
static const unsigned char sDarkDriceratopsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_driceratops.lz");

static const unsigned char sGracefulCharityBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/graceful_charity.huff");
static const unsigned short sGracefulCharityBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/graceful_charity.gbapal");
static const unsigned char sGracefulCharityMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/graceful_charity.lz");

static const unsigned char sGreatMajuGarzettBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/great_maju_garzett.huff");
static const unsigned short sGreatMajuGarzettBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/great_maju_garzett.gbapal");
static const unsigned char sGreatMajuGarzettMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/great_maju_garzett.lz");

static const unsigned char sTrianglePowerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/triangle_power.huff");
static const unsigned short sTrianglePowerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/triangle_power.gbapal");
static const unsigned char sTrianglePowerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/triangle_power.lz");

static const unsigned char sTwinSwordsOfFlashingLightTryceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/twin_swords_of_flashing_light_tryce.huff");
static const unsigned short sTwinSwordsOfFlashingLightTryceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/twin_swords_of_flashing_light_tryce.gbapal");
static const unsigned char sTwinSwordsOfFlashingLightTryceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/twin_swords_of_flashing_light_tryce.lz");

static const unsigned char sThousandKnivesBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/thousand_knives.huff");
static const unsigned short sThousandKnivesBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/thousand_knives.gbapal");
static const unsigned char sThousandKnivesMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/thousand_knives.lz");

static const unsigned char sSoulTakerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/soul_taker.huff");
static const unsigned short sSoulTakerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/soul_taker.gbapal");
static const unsigned char sSoulTakerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/soul_taker.lz");

static const unsigned char sSolarRayBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/solar_ray.huff");
static const unsigned short sSolarRayBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/solar_ray.gbapal");
static const unsigned char sSolarRayMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/solar_ray.lz");

static const unsigned char sSolemnWishesBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/solemn_wishes.huff");
static const unsigned short sSolemnWishesBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/solemn_wishes.gbapal");
static const unsigned char sSolemnWishesMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/solemn_wishes.lz");

static const unsigned char sStealthBirdBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/stealth_bird.huff");
static const unsigned short sStealthBirdBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/stealth_bird.gbapal");
static const unsigned char sStealthBirdMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/stealth_bird.lz");

static const unsigned char sNeedleBurrowerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/needle_burrower.huff");
static const unsigned short sNeedleBurrowerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/needle_burrower.gbapal");
static const unsigned char sNeedleBurrowerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/needle_burrower.lz");

static const unsigned char sDesScissorsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/des_scissors.huff");
static const unsigned short sDesScissorsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/des_scissors.gbapal");
static const unsigned char sDesScissorsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/des_scissors.lz");

static const unsigned char sImperialOrderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/imperial_order.huff");
static const unsigned short sImperialOrderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/imperial_order.gbapal");
static const unsigned char sImperialOrderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/imperial_order.lz");

static const unsigned char sGrenMajuDaEizaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gren_maju_da_eiza.huff");
static const unsigned short sGrenMajuDaEizaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gren_maju_da_eiza.gbapal");
static const unsigned char sGrenMajuDaEizaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gren_maju_da_eiza.lz");

static const unsigned char sRoyalDecreeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/royal_decree.huff");
static const unsigned short sRoyalDecreeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/royal_decree.gbapal");
static const unsigned char sRoyalDecreeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/royal_decree.lz");

static const unsigned char sReaperOnTheNightmareBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reaper_on_the_nightmare.huff");
static const unsigned short sReaperOnTheNightmareBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reaper_on_the_nightmare.gbapal");
static const unsigned char sReaperOnTheNightmareMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reaper_on_the_nightmare.lz");

static const unsigned char sNegativeEnergyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/negative_energy.huff");
static const unsigned short sNegativeEnergyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/negative_energy.gbapal");
static const unsigned char sNegativeEnergyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/negative_energy.lz");

static const unsigned char sMatazaTheZapperBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mataza_the_zapper.huff");
static const unsigned short sMatazaTheZapperBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mataza_the_zapper.gbapal");
static const unsigned char sMatazaTheZapperMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mataza_the_zapper.lz");

static const unsigned char sDoubleCostonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/double_coston.huff");
static const unsigned short sDoubleCostonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/double_coston.gbapal");
static const unsigned char sDoubleCostonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/double_coston.lz");

static const unsigned char sPreciousCardsFromBeyondBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/precious_cards_from_beyond.huff");
static const unsigned short sPreciousCardsFromBeyondBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/precious_cards_from_beyond.gbapal");
static const unsigned char sPreciousCardsFromBeyondMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/precious_cards_from_beyond.lz");

static const unsigned char sTyrantDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/tyrant_dragon.huff");
static const unsigned short sTyrantDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/tyrant_dragon.gbapal");
static const unsigned char sTyrantDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/tyrant_dragon.lz");

static const unsigned char sFinalCountdownBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/final_countdown.huff");
static const unsigned short sFinalCountdownBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/final_countdown.gbapal");
static const unsigned char sFinalCountdownMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/final_countdown.lz");

static const unsigned char sAbsorbingKidFromTheSkyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/absorbing_kid_from_the_sky.huff");
static const unsigned short sAbsorbingKidFromTheSkyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/absorbing_kid_from_the_sky.gbapal");
static const unsigned char sAbsorbingKidFromTheSkyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/absorbing_kid_from_the_sky.lz");

static const unsigned char sArsenalBugBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arsenal_bug.huff");
static const unsigned short sArsenalBugBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arsenal_bug.gbapal");
static const unsigned char sArsenalBugMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arsenal_bug.lz");

static const unsigned char sBurningLandBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/burning_land.huff");
static const unsigned short sBurningLandBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/burning_land.gbapal");
static const unsigned char sBurningLandMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/burning_land.lz");

static const unsigned char sBattleFootballerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/battle_footballer.huff");
static const unsigned short sBattleFootballerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/battle_footballer.gbapal");
static const unsigned char sBattleFootballerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/battle_footballer.lz");

static const unsigned char sDancingFairyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dancing_fairy.huff");
static const unsigned short sDancingFairyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dancing_fairy.gbapal");
static const unsigned char sDancingFairyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dancing_fairy.lz");

static const unsigned char sSpiritOfTheBreezeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/spirit_of_the_breeze.huff");
static const unsigned short sSpiritOfTheBreezeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/spirit_of_the_breeze.gbapal");
static const unsigned char sSpiritOfTheBreezeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/spirit_of_the_breeze.lz");

static const unsigned char sDropOffBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/drop_off.huff");
static const unsigned short sDropOffBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/drop_off.gbapal");
static const unsigned char sDropOffMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/drop_off.lz");

static const unsigned char sGoblinKingBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/goblin_king.huff");
static const unsigned short sGoblinKingBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/goblin_king.gbapal");
static const unsigned char sGoblinKingMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/goblin_king.lz");

static const unsigned char sGranadoraBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/granadora.huff");
static const unsigned short sGranadoraBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/granadora.gbapal");
static const unsigned char sGranadoraMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/granadora.lz");

static const unsigned char sHyperHammerheadBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/hyper_hammerhead.huff");
static const unsigned short sHyperHammerheadBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/hyper_hammerhead.gbapal");
static const unsigned char sHyperHammerheadMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/hyper_hammerhead.lz");

static const unsigned char sGyakuGirePandaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gyaku_gire_panda.huff");
static const unsigned short sGyakuGirePandaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gyaku_gire_panda.gbapal");
static const unsigned char sGyakuGirePandaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gyaku_gire_panda.lz");

static const unsigned char sGracefulDiceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/graceful_dice.huff");
static const unsigned short sGracefulDiceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/graceful_dice.gbapal");
static const unsigned char sGracefulDiceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/graceful_dice.lz");

static const unsigned char sBerserkGorillaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/berserk_gorilla.huff");
static const unsigned short sBerserkGorillaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/berserk_gorilla.gbapal");
static const unsigned char sBerserkGorillaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/berserk_gorilla.lz");

static const unsigned char sChaosGreedBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chaos_greed.huff");
static const unsigned short sChaosGreedBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chaos_greed.gbapal");
static const unsigned char sChaosGreedMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chaos_greed.lz");

static const unsigned char sBookOfMoonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/book_of_moon.huff");
static const unsigned short sBookOfMoonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/book_of_moon.gbapal");
static const unsigned char sBookOfMoonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/book_of_moon.lz");

static const unsigned char sBurningAlgaeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/burning_algae.huff");
static const unsigned short sBurningAlgaeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/burning_algae.gbapal");
static const unsigned char sBurningAlgaeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/burning_algae.lz");

static const unsigned char sDarklordMarieBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/darklord_marie.huff");
static const unsigned short sDarklordMarieBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/darklord_marie.gbapal");
static const unsigned char sDarklordMarieMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/darklord_marie.lz");

static const unsigned char sFenrirBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/fenrir.huff");
static const unsigned short sFenrirBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/fenrir.gbapal");
static const unsigned char sFenrirMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/fenrir.lz");

static const unsigned char sMagicalMerchantBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magical_merchant.huff");
static const unsigned short sMagicalMerchantBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magical_merchant.gbapal");
static const unsigned char sMagicalMerchantMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magical_merchant.lz");

static const unsigned char sRaregoldArmorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/raregold_armor.huff");
static const unsigned short sRaregoldArmorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/raregold_armor.gbapal");
static const unsigned char sRaregoldArmorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/raregold_armor.lz");

static const unsigned char sSpiritReaperBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/spirit_reaper.huff");
static const unsigned short sSpiritReaperBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/spirit_reaper.gbapal");
static const unsigned char sSpiritReaperMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/spirit_reaper.lz");

static const unsigned char sThunderCrashBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/thunder_crash.huff");
static const unsigned short sThunderCrashBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/thunder_crash.gbapal");
static const unsigned char sThunderCrashMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/thunder_crash.lz");

static const unsigned char sTorpedoFishBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/torpedo_fish.huff");
static const unsigned short sTorpedoFishBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/torpedo_fish.gbapal");
static const unsigned char sTorpedoFishMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/torpedo_fish.lz");

static const unsigned char sSevenToolsOfTheBanditBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/seven_tools_of_the_bandit.huff");
static const unsigned short sSevenToolsOfTheBanditBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/seven_tools_of_the_bandit.gbapal");
static const unsigned char sSevenToolsOfTheBanditMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/seven_tools_of_the_bandit.lz");

static const unsigned char sRivalryOfWarlordsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/rivalry_of_warlords.huff");
static const unsigned short sRivalryOfWarlordsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/rivalry_of_warlords.gbapal");
static const unsigned char sRivalryOfWarlordsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/rivalry_of_warlords.lz");

static const unsigned char sRingOfDestructionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ring_of_destruction.huff");
static const unsigned short sRingOfDestructionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ring_of_destruction.gbapal");
static const unsigned char sRingOfDestructionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ring_of_destruction.lz");

static const unsigned char sSasukeSamurai2BigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/sasuke_samurai_2.huff");
static const unsigned short sSasukeSamurai2BigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/sasuke_samurai_2.gbapal");
static const unsigned char sSasukeSamurai2MiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/sasuke_samurai_2.lz");

static const unsigned char sSasukeSamurai3BigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/sasuke_samurai_3.huff");
static const unsigned short sSasukeSamurai3BigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/sasuke_samurai_3.gbapal");
static const unsigned char sSasukeSamurai3MiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/sasuke_samurai_3.lz");

const unsigned char *gCardArts_Hook[] APPEND_RODATA = {
  [0x00AD] = sGiantRatBigArt,
  [0x00AE] = sSenjuOfTheThousandHandsBigArt,
  [0x0137] = sBlackPendantBigArt,
  [0x0321] = sSorcererOfDarkMagicBigArt,
  [0x0322] = sDeckDestructionVirusBigArt,
  [0x0323] = sMagiciansValkyriaBigArt,
  [0x0324] = sBlueEyesShiningDragonBigArt,
  [0x0325] = sPaladinOfWhiteDragonBigArt,
  [0x0326] = sCardOfDemiseBigArt,
  [0x0327] = sCardOfSanctityBigArt,
  [0x0328] = sShieldAndSwordBigArt,
  [0x0329] = sBlueEyesChaosMaxDragonBigArt,
  [0x032A] = sChainEnergyBigArt,
  [0x032B] = sSpellCancellerBigArt,
  [0x032C] = sExchangeBigArt,
  [0x032D] = sCopycatBigArt,
  [0x032E] = sMagePowerBigArt,
  [0x032F] = sKaibamanBigArt,
  [0x0330] = sUltimateOfferingBigArt,
  [0x0331] = sUnitedWeStandBigArt,
  [0x0332] = sWaveMotionCannonBigArt,
  [0x0333] = sStJoanBigArt,
  [0x0334] = sPyramidOfLightBigArt,
  [0x0335] = sSoulExchangeBigArt,
  [0x0336] = sMysticalSpaceTyphoonBigArt,
  [0x0337] = sRareMetalDragonBigArt,
  [0x0338] = sDoubleSummonBigArt,
  [0x0339] = sObnoxiousCelticGuardianBigArt,
  [0x033A] = sMaskOfRestrictBigArt,
  [0x033B] = sFairyBoxBigArt,
  [0x033C] = sCostDownBigArt,
  [0x033D] = sBlueEyesAlternativeWhiteDragonBigArt,
  [0x033E] = sAncientRulesBigArt,
  [0x033F] = sMagicJammerBigArt,
  [0x0340] = sSealOfOrichalcosBigArt,
  [0x0341] = sFamiliarKnightBigArt,
  [0x0342] = sRiryokuBigArt,
  [0x0343] = sSpearDragonBigArt,
  [0x0344] = sSagesStoneBigArt,
  [0x0345] = sBowganianBigArt,
  [0x0346] = sDarkMagicCurtainBigArt,
  [0x0347] = sCatsEarTribeBigArt,
  [0x0348] = sCureMermaidBigArt,
  [0x0349] = sDesKoalaBigArt,
  [0x034A] = sSkillDrainBigArt,
  [0x034B] = sGuardianTreasureBigArt,
  [0x034C] = sJarOfGreedBigArt,
  [0x034D] = sMadSwordBeastBigArt,
  [0x034E] = sOjamaTrioBigArt,
  [0x034F] = sLusterDragonBigArt,
  [0x0350] = sMysticalShineBallBigArt,
  [0x0351] = sGoblinThiefBigArt,
  [0x0352] = sHayabusaKnightBigArt,
  [0x0353] = sMagicCylinderBigArt,
  [0x0354] = sBlockAttackBigArt,
  [0x0355] = sDelinquentDuoBigArt,
  [0x0356] = sDrainingShieldBigArt,
  [0x0357] = sMeteorOfDestructionBigArt,
  [0x0358] = sTollBigArt,
  [0x0359] = sRainOfMercyBigArt,
  [0x035A] = sSolarFlareDragonBigArt,
  [0x035B] = sYataGarasuBigArt,
  [0x035C] = sUpstartGoblinBigArt,
  [0x035D] = sNegateAttackBigArt,
  [0x035E] = sReloadBigArt,
  [0x035F] = sMaraudingCaptainBigArt,
  [0x0360] = sSecretBarrelBigArt,
  [0x0361] = sRobbinGoblinBigArt,
  [0x0362] = sRobbinZombieBigArt,
  [0x0363] = sCallOfTheHauntedBigArt,
  [0x0364] = sKaiserGliderBigArt,
  [0x0365] = sPiranhaArmyBigArt,
  [0x0366] = sMoisterCreatureBigArt,
  [0x0367] = sWhiteMagicianPikeruBigArt,
  [0x0368] = sEbonMagicianCurranBigArt,
  [0x0369] = sWeatherReportBigArt,
  [0x036A] = sWarriorOfZeraBigArt,
  [0x036B] = sTimeSealBigArt,
  [0x036C] = sThousandEnergyBigArt,
  [0x036D] = sTheDarkDoorBigArt,
  [0x036E] = sSwiftGaiaTheFierceKnightBigArt,
  [0x036F] = sSelfDestructButtonBigArt,
  [0x0370] = sSkullInvitationBigArt,
  [0x0371] = sNightmareHorseBigArt,
  [0x0372] = sVampireBabyBigArt,
  [0x0373] = sTheForcefulSentryBigArt,
  [0x0374] = sTerrorkingSalmonBigArt,
  [0x0375] = sSasukeSamuraiBigArt,
  [0x0376] = sMaryokutaiBigArt,
  [0x0377] = sMermaidKnightBigArt,
  [0x0378] = sMefistTheInfernalGeneralBigArt,
  [0x0379] = sGuardianAngelJoanBigArt,
  [0x037A] = sPetenTheDarkClownBigArt,
  [0x037B] = sLimiterRemovalBigArt,
  [0x037C] = sJustDesertsBigArt,
  [0x037D] = sGilasaurusBigArt,
  [0x037E] = sGravityBindBigArt,
  [0x037F] = sGiftOfTheMysticalElfBigArt,
  [0x0380] = sRecklessGreedBigArt,
  [0x0381] = sAirknightParshathBigArt,
  [0x0382] = sAmphibiousBugrothMk3BigArt,
  [0x0383] = sBlackTyrannoBigArt,
  [0x0384] = sTheAgentOfCreationVenusBigArt,
  [0x0385] = sBlastingTheRuinsBigArt,
  [0x0386] = sCurseOfDarknessBigArt,
  [0x0387] = sCoffinSellerBigArt,
  [0x0388] = sCardDestructionBigArt,
  [0x0389] = sDarkRoomOfNightmareBigArt,
  [0x038A] = sDarkDriceratopsBigArt,
  [0x038B] = sGracefulCharityBigArt,
  [0x038C] = sGreatMajuGarzettBigArt,
  [0x038D] = sTrianglePowerBigArt,
  [0x038E] = sTwinSwordsOfFlashingLightTryceBigArt,
  [0x038F] = sThousandKnivesBigArt,
  [0x0390] = sSoulTakerBigArt,
  [0x0391] = sSolarRayBigArt,
  [0x0392] = sSolemnWishesBigArt,
  [0x0393] = sStealthBirdBigArt,
  [0x0394] = sNeedleBurrowerBigArt,
  [0x0395] = sDesScissorsBigArt,
  [0x0396] = sImperialOrderBigArt,
  [0x0397] = sGrenMajuDaEizaBigArt,
  [0x0398] = sRoyalDecreeBigArt,
  [0x0399] = sReaperOnTheNightmareBigArt,
  [0x039A] = sNegativeEnergyBigArt,
  [0x039B] = sMatazaTheZapperBigArt,
  [0x039C] = sDoubleCostonBigArt,
  [0x039D] = sPreciousCardsFromBeyondBigArt,
  [0x039E] = sTyrantDragonBigArt,
  [0x039F] = sFinalCountdownBigArt,
  [0x03A0] = sAbsorbingKidFromTheSkyBigArt,
  [0x03A1] = sArsenalBugBigArt,
  [0x03A2] = sBurningLandBigArt,
  [0x03A3] = sBattleFootballerBigArt,
  [0x03A4] = sDancingFairyBigArt,
  [0x03A5] = sSpiritOfTheBreezeBigArt,
  [0x03A6] = sDropOffBigArt,
  [0x03A7] = sGoblinKingBigArt,
  [0x03A8] = sGranadoraBigArt,
  [0x03A9] = sHyperHammerheadBigArt,
  [0x03AA] = sGyakuGirePandaBigArt,
  [0x03AB] = sGracefulDiceBigArt,
  [0x03AC] = sBerserkGorillaBigArt,
  [0x03AD] = sChaosGreedBigArt,
  [0x03AE] = sBookOfMoonBigArt,
  [0x03AF] = sBurningAlgaeBigArt,
  [0x03B0] = sDarklordMarieBigArt,
  [0x03B1] = sFenrirBigArt,
  [0x03B2] = sMagicalMerchantBigArt,
  [0x03B3] = sRaregoldArmorBigArt,
  [0x03B4] = sSpiritReaperBigArt,
  [0x03B5] = sThunderCrashBigArt,
  [0x03B6] = sTorpedoFishBigArt,
  [0x03B7] = sSevenToolsOfTheBanditBigArt,
  [0x03B8] = sRivalryOfWarlordsBigArt,
  [0x03B9] = sRingOfDestructionBigArt,
  [0x03BA] = sSasukeSamurai2BigArt,
  [0x03BB] = sSasukeSamurai3BigArt,
};

const unsigned short *gCardArtPalettes_Hook[] APPEND_RODATA = {
  [0x00AD] = sGiantRatBigPalette,
  [0x00AE] = sSenjuOfTheThousandHandsBigPalette,
  [0x0137] = sBlackPendantBigPalette,
  [0x0321] = sSorcererOfDarkMagicBigPalette,
  [0x0322] = sDeckDestructionVirusBigPalette,
  [0x0323] = sMagiciansValkyriaBigPalette,
  [0x0324] = sBlueEyesShiningDragonBigPalette,
  [0x0325] = sPaladinOfWhiteDragonBigPalette,
  [0x0326] = sCardOfDemiseBigPalette,
  [0x0327] = sCardOfSanctityBigPalette,
  [0x0328] = sShieldAndSwordBigPalette,
  [0x0329] = sBlueEyesChaosMaxDragonBigPalette,
  [0x032A] = sChainEnergyBigPalette,
  [0x032B] = sSpellCancellerBigPalette,
  [0x032C] = sExchangeBigPalette,
  [0x032D] = sCopycatBigPalette,
  [0x032E] = sMagePowerBigPalette,
  [0x032F] = sKaibamanBigPalette,
  [0x0330] = sUltimateOfferingBigPalette,
  [0x0331] = sUnitedWeStandBigPalette,
  [0x0332] = sWaveMotionCannonBigPalette,
  [0x0333] = sStJoanBigPalette,
  [0x0334] = sPyramidOfLightBigPalette,
  [0x0335] = sSoulExchangeBigPalette,
  [0x0336] = sMysticalSpaceTyphoonBigPalette,
  [0x0337] = sRareMetalDragonBigPalette,
  [0x0338] = sDoubleSummonBigPalette,
  [0x0339] = sObnoxiousCelticGuardianBigPalette,
  [0x033A] = sMaskOfRestrictBigPalette,
  [0x033B] = sFairyBoxBigPalette,
  [0x033C] = sCostDownBigPalette,
  [0x033D] = sBlueEyesAlternativeWhiteDragonBigPalette,
  [0x033E] = sAncientRulesBigPalette,
  [0x033F] = sMagicJammerBigPalette,
  [0x0340] = sSealOfOrichalcosBigPalette,
  [0x0341] = sFamiliarKnightBigPalette,
  [0x0342] = sRiryokuBigPalette,
  [0x0343] = sSpearDragonBigPalette,
  [0x0344] = sSagesStoneBigPalette,
  [0x0345] = sBowganianBigPalette,
  [0x0346] = sDarkMagicCurtainBigPalette,
  [0x0347] = sCatsEarTribeBigPalette,
  [0x0348] = sCureMermaidBigPalette,
  [0x0349] = sDesKoalaBigPalette,
  [0x034A] = sSkillDrainBigPalette,
  [0x034B] = sGuardianTreasureBigPalette,
  [0x034C] = sJarOfGreedBigPalette,
  [0x034D] = sMadSwordBeastBigPalette,
  [0x034E] = sOjamaTrioBigPalette,
  [0x034F] = sLusterDragonBigPalette,
  [0x0350] = sMysticalShineBallBigPalette,
  [0x0351] = sGoblinThiefBigPalette,
  [0x0352] = sHayabusaKnightBigPalette,
  [0x0353] = sMagicCylinderBigPalette,
  [0x0354] = sBlockAttackBigPalette,
  [0x0355] = sDelinquentDuoBigPalette,
  [0x0356] = sDrainingShieldBigPalette,
  [0x0357] = sMeteorOfDestructionBigPalette,
  [0x0358] = sTollBigPalette,
  [0x0359] = sRainOfMercyBigPalette,
  [0x035A] = sSolarFlareDragonBigPalette,
  [0x035B] = sYataGarasuBigPalette,
  [0x035C] = sUpstartGoblinBigPalette,
  [0x035D] = sNegateAttackBigPalette,
  [0x035E] = sReloadBigPalette,
  [0x035F] = sMaraudingCaptainBigPalette,
  [0x0360] = sSecretBarrelBigPalette,
  [0x0361] = sRobbinGoblinBigPalette,
  [0x0362] = sRobbinZombieBigPalette,
  [0x0363] = sCallOfTheHauntedBigPalette,
  [0x0364] = sKaiserGliderBigPalette,
  [0x0365] = sPiranhaArmyBigPalette,
  [0x0366] = sMoisterCreatureBigPalette,
  [0x0367] = sWhiteMagicianPikeruBigPalette,
  [0x0368] = sEbonMagicianCurranBigPalette,
  [0x0369] = sWeatherReportBigPalette,
  [0x036A] = sWarriorOfZeraBigPalette,
  [0x036B] = sTimeSealBigPalette,
  [0x036C] = sThousandEnergyBigPalette,
  [0x036D] = sTheDarkDoorBigPalette,
  [0x036E] = sSwiftGaiaTheFierceKnightBigPalette,
  [0x036F] = sSelfDestructButtonBigPalette,
  [0x0370] = sSkullInvitationBigPalette,
  [0x0371] = sNightmareHorseBigPalette,
  [0x0372] = sVampireBabyBigPalette,
  [0x0373] = sTheForcefulSentryBigPalette,
  [0x0374] = sTerrorkingSalmonBigPalette,
  [0x0375] = sSasukeSamuraiBigPalette,
  [0x0376] = sMaryokutaiBigPalette,
  [0x0377] = sMermaidKnightBigPalette,
  [0x0378] = sMefistTheInfernalGeneralBigPalette,
  [0x0379] = sGuardianAngelJoanBigPalette,
  [0x037A] = sPetenTheDarkClownBigPalette,
  [0x037B] = sLimiterRemovalBigPalette,
  [0x037C] = sJustDesertsBigPalette,
  [0x037D] = sGilasaurusBigPalette,
  [0x037E] = sGravityBindBigPalette,
  [0x037F] = sGiftOfTheMysticalElfBigPalette,
  [0x0380] = sRecklessGreedBigPalette,
  [0x0381] = sAirknightParshathBigPalette,
  [0x0382] = sAmphibiousBugrothMk3BigPalette,
  [0x0383] = sBlackTyrannoBigPalette,
  [0x0384] = sTheAgentOfCreationVenusBigPalette,
  [0x0385] = sBlastingTheRuinsBigPalette,
  [0x0386] = sCurseOfDarknessBigPalette,
  [0x0387] = sCoffinSellerBigPalette,
  [0x0388] = sCardDestructionBigPalette,
  [0x0389] = sDarkRoomOfNightmareBigPalette,
  [0x038A] = sDarkDriceratopsBigPalette,
  [0x038B] = sGracefulCharityBigPalette,
  [0x038C] = sGreatMajuGarzettBigPalette,
  [0x038D] = sTrianglePowerBigPalette,
  [0x038E] = sTwinSwordsOfFlashingLightTryceBigPalette,
  [0x038F] = sThousandKnivesBigPalette,
  [0x0390] = sSoulTakerBigPalette,
  [0x0391] = sSolarRayBigPalette,
  [0x0392] = sSolemnWishesBigPalette,
  [0x0393] = sStealthBirdBigPalette,
  [0x0394] = sNeedleBurrowerBigPalette,
  [0x0395] = sDesScissorsBigPalette,
  [0x0396] = sImperialOrderBigPalette,
  [0x0397] = sGrenMajuDaEizaBigPalette,
  [0x0398] = sRoyalDecreeBigPalette,
  [0x0399] = sReaperOnTheNightmareBigPalette,
  [0x039A] = sNegativeEnergyBigPalette,
  [0x039B] = sMatazaTheZapperBigPalette,
  [0x039C] = sDoubleCostonBigPalette,
  [0x039D] = sPreciousCardsFromBeyondBigPalette,
  [0x039E] = sTyrantDragonBigPalette,
  [0x039F] = sFinalCountdownBigPalette,
  [0x03A0] = sAbsorbingKidFromTheSkyBigPalette,
  [0x03A1] = sArsenalBugBigPalette,
  [0x03A2] = sBurningLandBigPalette,
  [0x03A3] = sBattleFootballerBigPalette,
  [0x03A4] = sDancingFairyBigPalette,
  [0x03A5] = sSpiritOfTheBreezeBigPalette,
  [0x03A6] = sDropOffBigPalette,
  [0x03A7] = sGoblinKingBigPalette,
  [0x03A8] = sGranadoraBigPalette,
  [0x03A9] = sHyperHammerheadBigPalette,
  [0x03AA] = sGyakuGirePandaBigPalette,
  [0x03AB] = sGracefulDiceBigPalette,
  [0x03AC] = sBerserkGorillaBigPalette,
  [0x03AD] = sChaosGreedBigPalette,
  [0x03AE] = sBookOfMoonBigPalette,
  [0x03AF] = sBurningAlgaeBigPalette,
  [0x03B0] = sDarklordMarieBigPalette,
  [0x03B1] = sFenrirBigPalette,
  [0x03B2] = sMagicalMerchantBigPalette,
  [0x03B3] = sRaregoldArmorBigPalette,
  [0x03B4] = sSpiritReaperBigPalette,
  [0x03B5] = sThunderCrashBigPalette,
  [0x03B6] = sTorpedoFishBigPalette,
  [0x03B7] = sSevenToolsOfTheBanditBigPalette,
  [0x03B8] = sRivalryOfWarlordsBigPalette,
  [0x03B9] = sRingOfDestructionBigPalette,
  [0x03BA] = sSasukeSamurai2BigPalette,
  [0x03BB] = sSasukeSamurai3BigPalette,
};

const u8 gCardArtUsesExtendedPalette_Hook[] APPEND_RODATA = {
  [0x00AD] = 0,
  [0x00AE] = 0,
  [0x0137] = 0,
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
};

const unsigned char *gMiniCardArts_Hook[] APPEND_RODATA = {
  [0x00AD] = sGiantRatMiniArt,
  [0x00AE] = sSenjuOfTheThousandHandsMiniArt,
  [0x0137] = sBlackPendantMiniArt,
  [0x0321] = sSorcererOfDarkMagicMiniArt,
  [0x0322] = sDeckDestructionVirusMiniArt,
  [0x0323] = sMagiciansValkyriaMiniArt,
  [0x0324] = sBlueEyesShiningDragonMiniArt,
  [0x0325] = sPaladinOfWhiteDragonMiniArt,
  [0x0326] = sCardOfDemiseMiniArt,
  [0x0327] = sCardOfSanctityMiniArt,
  [0x0328] = sShieldAndSwordMiniArt,
  [0x0329] = sBlueEyesChaosMaxDragonMiniArt,
  [0x032A] = sChainEnergyMiniArt,
  [0x032B] = sSpellCancellerMiniArt,
  [0x032C] = sExchangeMiniArt,
  [0x032D] = sCopycatMiniArt,
  [0x032E] = sMagePowerMiniArt,
  [0x032F] = sKaibamanMiniArt,
  [0x0330] = sUltimateOfferingMiniArt,
  [0x0331] = sUnitedWeStandMiniArt,
  [0x0332] = sWaveMotionCannonMiniArt,
  [0x0333] = sStJoanMiniArt,
  [0x0334] = sPyramidOfLightMiniArt,
  [0x0335] = sSoulExchangeMiniArt,
  [0x0336] = sMysticalSpaceTyphoonMiniArt,
  [0x0337] = sRareMetalDragonMiniArt,
  [0x0338] = sDoubleSummonMiniArt,
  [0x0339] = sObnoxiousCelticGuardianMiniArt,
  [0x033A] = sMaskOfRestrictMiniArt,
  [0x033B] = sFairyBoxMiniArt,
  [0x033C] = sCostDownMiniArt,
  [0x033D] = sBlueEyesAlternativeWhiteDragonMiniArt,
  [0x033E] = sAncientRulesMiniArt,
  [0x033F] = sMagicJammerMiniArt,
  [0x0340] = sSealOfOrichalcosMiniArt,
  [0x0341] = sFamiliarKnightMiniArt,
  [0x0342] = sRiryokuMiniArt,
  [0x0343] = sSpearDragonMiniArt,
  [0x0344] = sSagesStoneMiniArt,
  [0x0345] = sBowganianMiniArt,
  [0x0346] = sDarkMagicCurtainMiniArt,
  [0x0347] = sCatsEarTribeMiniArt,
  [0x0348] = sCureMermaidMiniArt,
  [0x0349] = sDesKoalaMiniArt,
  [0x034A] = sSkillDrainMiniArt,
  [0x034B] = sGuardianTreasureMiniArt,
  [0x034C] = sJarOfGreedMiniArt,
  [0x034D] = sMadSwordBeastMiniArt,
  [0x034E] = sOjamaTrioMiniArt,
  [0x034F] = sLusterDragonMiniArt,
  [0x0350] = sMysticalShineBallMiniArt,
  [0x0351] = sGoblinThiefMiniArt,
  [0x0352] = sHayabusaKnightMiniArt,
  [0x0353] = sMagicCylinderMiniArt,
  [0x0354] = sBlockAttackMiniArt,
  [0x0355] = sDelinquentDuoMiniArt,
  [0x0356] = sDrainingShieldMiniArt,
  [0x0357] = sMeteorOfDestructionMiniArt,
  [0x0358] = sTollMiniArt,
  [0x0359] = sRainOfMercyMiniArt,
  [0x035A] = sSolarFlareDragonMiniArt,
  [0x035B] = sYataGarasuMiniArt,
  [0x035C] = sUpstartGoblinMiniArt,
  [0x035D] = sNegateAttackMiniArt,
  [0x035E] = sReloadMiniArt,
  [0x035F] = sMaraudingCaptainMiniArt,
  [0x0360] = sSecretBarrelMiniArt,
  [0x0361] = sRobbinGoblinMiniArt,
  [0x0362] = sRobbinZombieMiniArt,
  [0x0363] = sCallOfTheHauntedMiniArt,
  [0x0364] = sKaiserGliderMiniArt,
  [0x0365] = sPiranhaArmyMiniArt,
  [0x0366] = sMoisterCreatureMiniArt,
  [0x0367] = sWhiteMagicianPikeruMiniArt,
  [0x0368] = sEbonMagicianCurranMiniArt,
  [0x0369] = sWeatherReportMiniArt,
  [0x036A] = sWarriorOfZeraMiniArt,
  [0x036B] = sTimeSealMiniArt,
  [0x036C] = sThousandEnergyMiniArt,
  [0x036D] = sTheDarkDoorMiniArt,
  [0x036E] = sSwiftGaiaTheFierceKnightMiniArt,
  [0x036F] = sSelfDestructButtonMiniArt,
  [0x0370] = sSkullInvitationMiniArt,
  [0x0371] = sNightmareHorseMiniArt,
  [0x0372] = sVampireBabyMiniArt,
  [0x0373] = sTheForcefulSentryMiniArt,
  [0x0374] = sTerrorkingSalmonMiniArt,
  [0x0375] = sSasukeSamuraiMiniArt,
  [0x0376] = sMaryokutaiMiniArt,
  [0x0377] = sMermaidKnightMiniArt,
  [0x0378] = sMefistTheInfernalGeneralMiniArt,
  [0x0379] = sGuardianAngelJoanMiniArt,
  [0x037A] = sPetenTheDarkClownMiniArt,
  [0x037B] = sLimiterRemovalMiniArt,
  [0x037C] = sJustDesertsMiniArt,
  [0x037D] = sGilasaurusMiniArt,
  [0x037E] = sGravityBindMiniArt,
  [0x037F] = sGiftOfTheMysticalElfMiniArt,
  [0x0380] = sRecklessGreedMiniArt,
  [0x0381] = sAirknightParshathMiniArt,
  [0x0382] = sAmphibiousBugrothMk3MiniArt,
  [0x0383] = sBlackTyrannoMiniArt,
  [0x0384] = sTheAgentOfCreationVenusMiniArt,
  [0x0385] = sBlastingTheRuinsMiniArt,
  [0x0386] = sCurseOfDarknessMiniArt,
  [0x0387] = sCoffinSellerMiniArt,
  [0x0388] = sCardDestructionMiniArt,
  [0x0389] = sDarkRoomOfNightmareMiniArt,
  [0x038A] = sDarkDriceratopsMiniArt,
  [0x038B] = sGracefulCharityMiniArt,
  [0x038C] = sGreatMajuGarzettMiniArt,
  [0x038D] = sTrianglePowerMiniArt,
  [0x038E] = sTwinSwordsOfFlashingLightTryceMiniArt,
  [0x038F] = sThousandKnivesMiniArt,
  [0x0390] = sSoulTakerMiniArt,
  [0x0391] = sSolarRayMiniArt,
  [0x0392] = sSolemnWishesMiniArt,
  [0x0393] = sStealthBirdMiniArt,
  [0x0394] = sNeedleBurrowerMiniArt,
  [0x0395] = sDesScissorsMiniArt,
  [0x0396] = sImperialOrderMiniArt,
  [0x0397] = sGrenMajuDaEizaMiniArt,
  [0x0398] = sRoyalDecreeMiniArt,
  [0x0399] = sReaperOnTheNightmareMiniArt,
  [0x039A] = sNegativeEnergyMiniArt,
  [0x039B] = sMatazaTheZapperMiniArt,
  [0x039C] = sDoubleCostonMiniArt,
  [0x039D] = sPreciousCardsFromBeyondMiniArt,
  [0x039E] = sTyrantDragonMiniArt,
  [0x039F] = sFinalCountdownMiniArt,
  [0x03A0] = sAbsorbingKidFromTheSkyMiniArt,
  [0x03A1] = sArsenalBugMiniArt,
  [0x03A2] = sBurningLandMiniArt,
  [0x03A3] = sBattleFootballerMiniArt,
  [0x03A4] = sDancingFairyMiniArt,
  [0x03A5] = sSpiritOfTheBreezeMiniArt,
  [0x03A6] = sDropOffMiniArt,
  [0x03A7] = sGoblinKingMiniArt,
  [0x03A8] = sGranadoraMiniArt,
  [0x03A9] = sHyperHammerheadMiniArt,
  [0x03AA] = sGyakuGirePandaMiniArt,
  [0x03AB] = sGracefulDiceMiniArt,
  [0x03AC] = sBerserkGorillaMiniArt,
  [0x03AD] = sChaosGreedMiniArt,
  [0x03AE] = sBookOfMoonMiniArt,
  [0x03AF] = sBurningAlgaeMiniArt,
  [0x03B0] = sDarklordMarieMiniArt,
  [0x03B1] = sFenrirMiniArt,
  [0x03B2] = sMagicalMerchantMiniArt,
  [0x03B3] = sRaregoldArmorMiniArt,
  [0x03B4] = sSpiritReaperMiniArt,
  [0x03B5] = sThunderCrashMiniArt,
  [0x03B6] = sTorpedoFishMiniArt,
  [0x03B7] = sSevenToolsOfTheBanditMiniArt,
  [0x03B8] = sRivalryOfWarlordsMiniArt,
  [0x03B9] = sRingOfDestructionMiniArt,
  [0x03BA] = sSasukeSamurai2MiniArt,
  [0x03BB] = sSasukeSamurai3MiniArt,
};
