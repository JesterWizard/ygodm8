#include "global.h"

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

static const unsigned char sKa2DesScissorsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ka_2_des_scissors.huff");
static const unsigned short sKa2DesScissorsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ka_2_des_scissors.gbapal");
static const unsigned char sKa2DesScissorsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ka_2_des_scissors.lz");

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

static const unsigned char sServantOfCatabolismBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/servant_of_catabolism.huff");
static const unsigned short sServantOfCatabolismBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/servant_of_catabolism.gbapal");
static const unsigned char sServantOfCatabolismMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/servant_of_catabolism.lz");

static const unsigned char sManThroTroBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/man_thro_tro.huff");
static const unsigned short sManThroTroBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/man_thro_tro.gbapal");
static const unsigned char sManThroTroMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/man_thro_tro.lz");

static const unsigned char sLevelLimitAreaBBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/level_limit_area_b.huff");
static const unsigned short sLevelLimitAreaBBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/level_limit_area_b.gbapal");
static const unsigned char sLevelLimitAreaBMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/level_limit_area_b.lz");

static const unsigned char sSpiritRyuBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/spirit_ryu.huff");
static const unsigned short sSpiritRyuBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/spirit_ryu.gbapal");
static const unsigned char sSpiritRyuMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/spirit_ryu.lz");

static const unsigned char sAmazonessTigerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/amazoness_tiger.huff");
static const unsigned short sAmazonessTigerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/amazoness_tiger.gbapal");
static const unsigned char sAmazonessTigerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/amazoness_tiger.lz");

static const unsigned char sBlastHeldByATributeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blast_held_by_a_tribute.huff");
static const unsigned short sBlastHeldByATributeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blast_held_by_a_tribute.gbapal");
static const unsigned char sBlastHeldByATributeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blast_held_by_a_tribute.lz");

static const unsigned char sDDWarriorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/d_d_warrior.huff");
static const unsigned short sDDWarriorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/d_d_warrior.gbapal");
static const unsigned char sDDWarriorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/d_d_warrior.lz");

static const unsigned char sConfiscationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/confiscation.huff");
static const unsigned short sConfiscationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/confiscation.gbapal");
static const unsigned char sConfiscationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/confiscation.lz");

static const unsigned char sBreakerTheMagicalWarriorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/breaker_the_magical_warrior.huff");
static const unsigned short sBreakerTheMagicalWarriorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/breaker_the_magical_warrior.gbapal");
static const unsigned char sBreakerTheMagicalWarriorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/breaker_the_magical_warrior.lz");

static const unsigned char sDesKangarooBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/des_kangaroo.huff");
static const unsigned short sDesKangarooBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/des_kangaroo.gbapal");
static const unsigned char sDesKangarooMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/des_kangaroo.lz");

static const unsigned char sDrillagoBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/drillago.huff");
static const unsigned short sDrillagoBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/drillago.gbapal");
static const unsigned char sDrillagoMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/drillago.lz");

static const unsigned char sDarkSnakeSyndromeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_snake_syndrome.huff");
static const unsigned short sDarkSnakeSyndromeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_snake_syndrome.gbapal");
static const unsigned char sDarkSnakeSyndromeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_snake_syndrome.lz");

static const unsigned char sJarRobberBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/jar_robber.huff");
static const unsigned short sJarRobberBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/jar_robber.gbapal");
static const unsigned char sJarRobberMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/jar_robber.lz");

static const unsigned char sGravekeepersServantBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gravekeepers_servant.huff");
static const unsigned short sGravekeepersServantBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gravekeepers_servant.gbapal");
static const unsigned char sGravekeepersServantMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gravekeepers_servant.lz");

static const unsigned char sDiceJarBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dice_jar.huff");
static const unsigned short sDiceJarBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dice_jar.gbapal");
static const unsigned char sDiceJarMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dice_jar.lz");

static const unsigned char sKnightsTitleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/knights_title.huff");
static const unsigned short sKnightsTitleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/knights_title.gbapal");
static const unsigned char sKnightsTitleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/knights_title.lz");

static const unsigned char sJowlsOfDarkDemiseBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/jowls_of_dark_demise.huff");
static const unsigned short sJowlsOfDarkDemiseBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/jowls_of_dark_demise.gbapal");
static const unsigned char sJowlsOfDarkDemiseMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/jowls_of_dark_demise.lz");

static const unsigned char sKishidoSpiritBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/kishido_spirit.huff");
static const unsigned short sKishidoSpiritBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/kishido_spirit.gbapal");
static const unsigned char sKishidoSpiritMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/kishido_spirit.lz");

static const unsigned char sPossessedDarkSoulBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/possessed_dark_soul.huff");
static const unsigned short sPossessedDarkSoulBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/possessed_dark_soul.gbapal");
static const unsigned char sPossessedDarkSoulMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/possessed_dark_soul.lz");

static const unsigned char sRoyalKnightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/royal_knight.huff");
static const unsigned short sRoyalKnightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/royal_knight.gbapal");
static const unsigned char sRoyalKnightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/royal_knight.lz");

static const unsigned char sTheThingInTheCraterBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_thing_in_the_crater.huff");
static const unsigned short sTheThingInTheCraterBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_thing_in_the_crater.gbapal");
static const unsigned char sTheThingInTheCraterMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_thing_in_the_crater.lz");

static const unsigned char sCreatureSwapBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/creature_swap.huff");
static const unsigned short sCreatureSwapBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/creature_swap.gbapal");
static const unsigned char sCreatureSwapMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/creature_swap.lz");

static const unsigned char sLesserFiendBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lesser_fiend.huff");
static const unsigned short sLesserFiendBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lesser_fiend.gbapal");
static const unsigned char sLesserFiendMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lesser_fiend.lz");

static const unsigned char sSpiritOfThePotOfGreedBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/spirit_of_the_pot_of_greed.huff");
static const unsigned short sSpiritOfThePotOfGreedBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/spirit_of_the_pot_of_greed.gbapal");
static const unsigned char sSpiritOfThePotOfGreedMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/spirit_of_the_pot_of_greed.lz");

static const unsigned char sZaborgTheThunderMonarchBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/zaborg_the_thunder_monarch.huff");
static const unsigned short sZaborgTheThunderMonarchBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/zaborg_the_thunder_monarch.gbapal");
static const unsigned char sZaborgTheThunderMonarchMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/zaborg_the_thunder_monarch.lz");

static const unsigned char sBottomlessShiftingSandBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/bottomless_shifting_sand.huff");
static const unsigned short sBottomlessShiftingSandBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/bottomless_shifting_sand.gbapal");
static const unsigned char sBottomlessShiftingSandMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/bottomless_shifting_sand.lz");

static const unsigned char sFirePrincessBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/fire_princess.huff");
static const unsigned short sFirePrincessBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/fire_princess.gbapal");
static const unsigned char sFirePrincessMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/fire_princess.lz");

static const unsigned char sInvaderOfTheThroneBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/invader_of_the_throne.huff");
static const unsigned short sInvaderOfTheThroneBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/invader_of_the_throne.gbapal");
static const unsigned char sInvaderOfTheThroneMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/invader_of_the_throne.lz");

static const unsigned char sTheFluteOfSummoningDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_flute_of_summoning_dragon.huff");
static const unsigned short sTheFluteOfSummoningDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_flute_of_summoning_dragon.gbapal");
static const unsigned char sTheFluteOfSummoningDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_flute_of_summoning_dragon.lz");

static const unsigned char sSpiritCallerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/spirit_caller.huff");
static const unsigned short sSpiritCallerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/spirit_caller.gbapal");
static const unsigned char sSpiritCallerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/spirit_caller.lz");

static const unsigned char sVengefulBogSpiritBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vengeful_bog_spirit.huff");
static const unsigned short sVengefulBogSpiritBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vengeful_bog_spirit.gbapal");
static const unsigned char sVengefulBogSpiritMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vengeful_bog_spirit.lz");

static const unsigned char sWallOfRevealingLightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/wall_of_revealing_light.huff");
static const unsigned short sWallOfRevealingLightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/wall_of_revealing_light.gbapal");
static const unsigned char sWallOfRevealingLightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/wall_of_revealing_light.lz");

static const unsigned char sWorldSuppressionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/world_suppression.huff");
static const unsigned short sWorldSuppressionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/world_suppression.gbapal");
static const unsigned char sWorldSuppressionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/world_suppression.lz");

static const unsigned char sRyuKishinClownBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ryu_kishin_clown.huff");
static const unsigned short sRyuKishinClownBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ryu_kishin_clown.gbapal");
static const unsigned char sRyuKishinClownMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ryu_kishin_clown.lz");

static const unsigned char sDarkDustSpiritBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_dust_spirit.huff");
static const unsigned short sDarkDustSpiritBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_dust_spirit.gbapal");
static const unsigned char sDarkDustSpiritMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_dust_spirit.lz");

static const unsigned char sGhostKnightOfJackalBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ghost_knight_of_jackal.huff");
static const unsigned short sGhostKnightOfJackalBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ghost_knight_of_jackal.gbapal");
static const unsigned char sGhostKnightOfJackalMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ghost_knight_of_jackal.lz");

static const unsigned char sKaiserColosseumBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/kaiser_colosseum.huff");
static const unsigned short sKaiserColosseumBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/kaiser_colosseum.gbapal");
static const unsigned char sKaiserColosseumMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/kaiser_colosseum.lz");

static const unsigned char sNightmareWheelBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/nightmare_wheel.huff");
static const unsigned short sNightmareWheelBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/nightmare_wheel.gbapal");
static const unsigned char sNightmareWheelMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/nightmare_wheel.lz");

static const unsigned char sMirrorWallBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mirror_wall.huff");
static const unsigned short sMirrorWallBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mirror_wall.gbapal");
static const unsigned char sMirrorWallMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mirror_wall.lz");

static const unsigned char sMajuGarzettBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/maju_garzett.huff");
static const unsigned short sMajuGarzettBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/maju_garzett.gbapal");
static const unsigned char sMajuGarzettMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/maju_garzett.lz");

static const unsigned char sDustTornadoBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dust_tornado.huff");
static const unsigned short sDustTornadoBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dust_tornado.gbapal");
static const unsigned char sDustTornadoMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dust_tornado.lz");

static const unsigned char sEctoplasmerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ectoplasmer.huff");
static const unsigned short sEctoplasmerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ectoplasmer.gbapal");
static const unsigned char sEctoplasmerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ectoplasmer.lz");

static const unsigned char sLeviaDragonDaedalusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/levia_dragon_daedalus.huff");
static const unsigned short sLeviaDragonDaedalusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/levia_dragon_daedalus.gbapal");
static const unsigned char sLeviaDragonDaedalusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/levia_dragon_daedalus.lz");

static const unsigned char sThebanNightmareBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/theban_nightmare.huff");
static const unsigned short sThebanNightmareBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/theban_nightmare.gbapal");
static const unsigned char sThebanNightmareMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/theban_nightmare.lz");

static const unsigned char sBigBangShotBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/big_bang_shot.huff");
static const unsigned short sBigBangShotBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/big_bang_shot.gbapal");
static const unsigned char sBigBangShotMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/big_bang_shot.lz");

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

static const unsigned char sElementalHeroAvianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_avian.huff");
static const unsigned short sElementalHeroAvianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_avian.gbapal");
static const unsigned char sElementalHeroAvianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_avian.lz");

static const unsigned char sElementalHeroBurstinatrixBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_burstinatrix.huff");
static const unsigned short sElementalHeroBurstinatrixBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_burstinatrix.gbapal");
static const unsigned char sElementalHeroBurstinatrixMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_burstinatrix.lz");

static const unsigned char sElementalHeroSparkmanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_sparkman.huff");
static const unsigned short sElementalHeroSparkmanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_sparkman.gbapal");
static const unsigned char sElementalHeroSparkmanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_sparkman.lz");

static const unsigned char sElementalHeroBubblemanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_bubbleman.huff");
static const unsigned short sElementalHeroBubblemanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_bubbleman.gbapal");
static const unsigned char sElementalHeroBubblemanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_bubbleman.lz");

static const unsigned char sElementalHeroWildheartBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_wildheart.huff");
static const unsigned short sElementalHeroWildheartBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_wildheart.gbapal");
static const unsigned char sElementalHeroWildheartMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_wildheart.lz");

static const unsigned char sElementalHeroBladedgeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_bladedge.huff");
static const unsigned short sElementalHeroBladedgeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_bladedge.gbapal");
static const unsigned char sElementalHeroBladedgeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_bladedge.lz");

static const unsigned char sElementalHeroClaymanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_clayman.huff");
static const unsigned short sElementalHeroClaymanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_clayman.gbapal");
static const unsigned char sElementalHeroClaymanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_clayman.lz");

static const unsigned char sElementalHeroMudballmanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_mudballman.huff");
static const unsigned short sElementalHeroMudballmanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_mudballman.gbapal");
static const unsigned char sElementalHeroMudballmanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_mudballman.lz");

static const unsigned char sHarpieLady1BigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpie_lady_1.huff");
static const unsigned short sHarpieLady1BigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpie_lady_1.gbapal");
static const unsigned char sHarpieLady1MiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpie_lady_1.lz");

static const unsigned char sHarpieLady2BigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpie_lady_2.huff");
static const unsigned short sHarpieLady2BigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpie_lady_2.gbapal");
static const unsigned char sHarpieLady2MiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpie_lady_2.lz");

static const unsigned char sHarpieLady3BigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpie_lady_3.huff");
static const unsigned short sHarpieLady3BigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpie_lady_3.gbapal");
static const unsigned char sHarpieLady3MiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpie_lady_3.lz");

static const unsigned char sSpellEconomicsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/spell_economics.huff");
static const unsigned short sSpellEconomicsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/spell_economics.gbapal");
static const unsigned char sSpellEconomicsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/spell_economics.lz");

static const unsigned char sTheUnstoppableExodiaIncarnateBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_unstoppable_exodia_incarnate.huff");
static const unsigned short sTheUnstoppableExodiaIncarnateBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_unstoppable_exodia_incarnate.gbapal");
static const unsigned char sTheUnstoppableExodiaIncarnateMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_unstoppable_exodia_incarnate.lz");

static const unsigned char sTheSanctuaryInTheSkyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_sanctuary_in_the_sky.huff");
static const unsigned short sTheSanctuaryInTheSkyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_sanctuary_in_the_sky.gbapal");
static const unsigned char sTheSanctuaryInTheSkyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_sanctuary_in_the_sky.lz");

static const unsigned char sMirrorForceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mirror_force.huff");
static const unsigned short sMirrorForceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mirror_force.gbapal");
static const unsigned char sMirrorForceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mirror_force.lz");

static const unsigned char sLevelLimitAreaABigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/level_limit_area_a.huff");
static const unsigned short sLevelLimitAreaABigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/level_limit_area_a.gbapal");
static const unsigned char sLevelLimitAreaAMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/level_limit_area_a.lz");

static const unsigned char sHarpiesPetBabyDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpies_pet_baby_dragon.huff");
static const unsigned short sHarpiesPetBabyDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpies_pet_baby_dragon.gbapal");
static const unsigned char sHarpiesPetBabyDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpies_pet_baby_dragon.lz");

static const unsigned char sBlueEyesChaosDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_chaos_dragon.huff");
static const unsigned short sBlueEyesChaosDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_chaos_dragon.gbapal");
static const unsigned char sBlueEyesChaosDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_chaos_dragon.lz");

static const unsigned char sBlowbackDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blowback_dragon.huff");
static const unsigned short sBlowbackDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blowback_dragon.gbapal");
static const unsigned char sBlowbackDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blowback_dragon.lz");

static const unsigned char sChaosCommandMagicianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chaos_command_magician.huff");
static const unsigned short sChaosCommandMagicianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chaos_command_magician.gbapal");
static const unsigned char sChaosCommandMagicianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chaos_command_magician.lz");

static const unsigned char sBookOfLifeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/book_of_life.huff");
static const unsigned short sBookOfLifeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/book_of_life.gbapal");
static const unsigned char sBookOfLifeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/book_of_life.lz");

static const unsigned char sBookOfTaiyouBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/book_of_taiyou.huff");
static const unsigned short sBookOfTaiyouBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/book_of_taiyou.gbapal");
static const unsigned char sBookOfTaiyouMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/book_of_taiyou.lz");

static const unsigned char sDeFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/de_fusion.huff");
static const unsigned short sDeFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/de_fusion.gbapal");
static const unsigned char sDeFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/de_fusion.lz");

static const unsigned char sDiffusionWaveMotionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/diffusion_wave_motion.huff");
static const unsigned short sDiffusionWaveMotionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/diffusion_wave_motion.gbapal");
static const unsigned char sDiffusionWaveMotionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/diffusion_wave_motion.lz");

static const unsigned char sAutonomousActionUnitBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/autonomous_action_unit.huff");
static const unsigned short sAutonomousActionUnitBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/autonomous_action_unit.gbapal");
static const unsigned char sAutonomousActionUnitMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/autonomous_action_unit.lz");

static const unsigned char sElementalHeroRampartBlasterBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_rampart_blaster.huff");
static const unsigned short sElementalHeroRampartBlasterBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_rampart_blaster.gbapal");
static const unsigned char sElementalHeroRampartBlasterMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_rampart_blaster.lz");

static const unsigned char sALegendaryOceanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/a_legendary_ocean.huff");
static const unsigned short sALegendaryOceanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/a_legendary_ocean.gbapal");
static const unsigned char sALegendaryOceanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/a_legendary_ocean.lz");

static const unsigned char sDarkMagicianOfChaosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_magician_of_chaos.huff");
static const unsigned short sDarkMagicianOfChaosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_magician_of_chaos.gbapal");
static const unsigned char sDarkMagicianOfChaosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_magician_of_chaos.lz");

static const unsigned char sDedicationThroughLightAndDarknessBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dedication_through_light_and_darkness.huff");
static const unsigned short sDedicationThroughLightAndDarknessBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dedication_through_light_and_darkness.gbapal");
static const unsigned char sDedicationThroughLightAndDarknessMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dedication_through_light_and_darkness.lz");

static const unsigned char sElementalHeroSteamHealerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_steam_healer.huff");
static const unsigned short sElementalHeroSteamHealerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_steam_healer.gbapal");
static const unsigned char sElementalHeroSteamHealerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_steam_healer.lz");

static const unsigned char sElementalHeroPhoenixEnforcerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_phoenix_enforcer.huff");
static const unsigned short sElementalHeroPhoenixEnforcerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_phoenix_enforcer.gbapal");
static const unsigned char sElementalHeroPhoenixEnforcerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_phoenix_enforcer.lz");

static const unsigned char sElementalHeroShiningPhoenixEnforcerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_shining_phoenix_enforcer.huff");
static const unsigned short sElementalHeroShiningPhoenixEnforcerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_shining_phoenix_enforcer.gbapal");
static const unsigned char sElementalHeroShiningPhoenixEnforcerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_shining_phoenix_enforcer.lz");

static const unsigned char sElementalHeroFlameWingmanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_flame_wingman.huff");
static const unsigned short sElementalHeroFlameWingmanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_flame_wingman.gbapal");
static const unsigned char sElementalHeroFlameWingmanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_flame_wingman.lz");

static const unsigned char sElementalHeroShiningFlareWingmanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_shining_flare_wingman.huff");
static const unsigned short sElementalHeroShiningFlareWingmanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_shining_flare_wingman.gbapal");
static const unsigned char sElementalHeroShiningFlareWingmanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_shining_flare_wingman.lz");

static const unsigned char sElementalHeroTempestBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_tempest.huff");
static const unsigned short sElementalHeroTempestBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_tempest.gbapal");
static const unsigned char sElementalHeroTempestMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_tempest.lz");

static const unsigned char sElementalHeroWildedgeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_wildedge.huff");
static const unsigned short sElementalHeroWildedgeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_wildedge.gbapal");
static const unsigned char sElementalHeroWildedgeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_wildedge.lz");

static const unsigned char sElementalHeroThunderGiantBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_thunder_giant.huff");
static const unsigned short sElementalHeroThunderGiantBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_thunder_giant.gbapal");
static const unsigned char sElementalHeroThunderGiantMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_thunder_giant.lz");

static const unsigned char sElementalHeroMarinerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_mariner.huff");
static const unsigned short sElementalHeroMarinerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_mariner.gbapal");
static const unsigned char sElementalHeroMarinerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_mariner.lz");

static const unsigned char sElementalHeroElectrumBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_electrum.huff");
static const unsigned short sElementalHeroElectrumBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_electrum.gbapal");
static const unsigned char sElementalHeroElectrumMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_electrum.lz");

static const unsigned char sElementalHeroNecroshadeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_necroshade.huff");
static const unsigned short sElementalHeroNecroshadeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_necroshade.gbapal");
static const unsigned char sElementalHeroNecroshadeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_necroshade.lz");

static const unsigned char sMiracleFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/miracle_fusion.huff");
static const unsigned short sMiracleFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/miracle_fusion.gbapal");
static const unsigned char sMiracleFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/miracle_fusion.lz");

static const unsigned char sTheAgentOfForceMarsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_agent_of_force_mars.huff");
static const unsigned short sTheAgentOfForceMarsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_agent_of_force_mars.gbapal");
static const unsigned char sTheAgentOfForceMarsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_agent_of_force_mars.lz");

static const unsigned char sChaosEmperorDragonEnvoyOfTheEndBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chaos_emperor_dragon_envoy_of_the_end.huff");
static const unsigned short sChaosEmperorDragonEnvoyOfTheEndBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chaos_emperor_dragon_envoy_of_the_end.gbapal");
static const unsigned char sChaosEmperorDragonEnvoyOfTheEndMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chaos_emperor_dragon_envoy_of_the_end.lz");

static const unsigned char sBlackLusterSoldierEnvoyOfTheBeginningBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/black_luster_soldier_envoy_of_the_beginning.huff");
static const unsigned short sBlackLusterSoldierEnvoyOfTheBeginningBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/black_luster_soldier_envoy_of_the_beginning.gbapal");
static const unsigned char sBlackLusterSoldierEnvoyOfTheBeginningMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/black_luster_soldier_envoy_of_the_beginning.lz");

static const unsigned char sElementalHeroNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_neos.huff");
static const unsigned short sElementalHeroNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_neos.gbapal");
static const unsigned char sElementalHeroNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_neos.lz");

static const unsigned char sElementalHeroWoodsmanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_woodsman.huff");
static const unsigned short sElementalHeroWoodsmanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_woodsman.gbapal");
static const unsigned char sElementalHeroWoodsmanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_woodsman.lz");

static const unsigned char sElementalHeroOceanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_ocean.huff");
static const unsigned short sElementalHeroOceanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_ocean.gbapal");
static const unsigned char sElementalHeroOceanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_ocean.lz");

static const unsigned char sElementalHeroHeatBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_heat.huff");
static const unsigned short sElementalHeroHeatBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_heat.gbapal");
static const unsigned char sElementalHeroHeatMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_heat.lz");

static const unsigned char sElementalHeroLadyHeatBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_lady_heat.huff");
static const unsigned short sElementalHeroLadyHeatBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_lady_heat.gbapal");
static const unsigned char sElementalHeroLadyHeatMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_lady_heat.lz");

static const unsigned char sElementalHeroNeosAliusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_neos_alius.huff");
static const unsigned short sElementalHeroNeosAliusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_neos_alius.gbapal");
static const unsigned char sElementalHeroNeosAliusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_neos_alius.lz");

static const unsigned char sElementalHeroGreatTornadoBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_great_tornado.huff");
static const unsigned short sElementalHeroGreatTornadoBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_great_tornado.gbapal");
static const unsigned char sElementalHeroGreatTornadoMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_great_tornado.lz");

static const unsigned char sElementalHeroTerraFirmaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_terra_firma.huff");
static const unsigned short sElementalHeroTerraFirmaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_terra_firma.gbapal");
static const unsigned char sElementalHeroTerraFirmaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_terra_firma.lz");

static const unsigned char sElementalHeroKnospeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_knospe.huff");
static const unsigned short sElementalHeroKnospeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_knospe.gbapal");
static const unsigned char sElementalHeroKnospeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_knospe.lz");

static const unsigned char sElementalHeroPoisonRoseBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_poison_rose.huff");
static const unsigned short sElementalHeroPoisonRoseBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_poison_rose.gbapal");
static const unsigned char sElementalHeroPoisonRoseMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_poison_rose.lz");

static const unsigned char sElementalHeroAbsoluteZeroBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_absolute_zero.huff");
static const unsigned short sElementalHeroAbsoluteZeroBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_absolute_zero.gbapal");
static const unsigned char sElementalHeroAbsoluteZeroMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_absolute_zero.lz");

static const unsigned char sElementalHeroWildWingmanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_wild_wingman.huff");
static const unsigned short sElementalHeroWildWingmanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_wild_wingman.gbapal");
static const unsigned char sElementalHeroWildWingmanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_wild_wingman.lz");

static const unsigned char sElementalHeroVolticBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_voltic.huff");
static const unsigned short sElementalHeroVolticBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_voltic.gbapal");
static const unsigned char sElementalHeroVolticMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_voltic.lz");

static const unsigned char sElementalHeroFlashBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_flash.huff");
static const unsigned short sElementalHeroFlashBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_flash.gbapal");
static const unsigned char sElementalHeroFlashMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_flash.lz");

static const unsigned char sElementalHeroGaiaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_gaia.huff");
static const unsigned short sElementalHeroGaiaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_gaia.gbapal");
static const unsigned char sElementalHeroGaiaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_gaia.lz");

static const unsigned char sElementalHeroEscuridaoBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_escuridao.huff");
static const unsigned short sElementalHeroEscuridaoBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_escuridao.gbapal");
static const unsigned char sElementalHeroEscuridaoMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_escuridao.lz");

static const unsigned char sElementalHeroTheShiningBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_the_shining.huff");
static const unsigned short sElementalHeroTheShiningBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_the_shining.gbapal");
static const unsigned char sElementalHeroTheShiningMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_the_shining.lz");

static const unsigned char sElementalHeroInfernoBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_inferno.huff");
static const unsigned short sElementalHeroInfernoBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_inferno.gbapal");
static const unsigned char sElementalHeroInfernoMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_inferno.lz");

static const unsigned char sElementalHeroNecroidShamanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_necroid_shaman.huff");
static const unsigned short sElementalHeroNecroidShamanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_necroid_shaman.gbapal");
static const unsigned char sElementalHeroNecroidShamanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_necroid_shaman.lz");

static const unsigned char sElementalHeroPlasmaViceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_plasma_vice.huff");
static const unsigned short sElementalHeroPlasmaViceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_plasma_vice.gbapal");
static const unsigned char sElementalHeroPlasmaViceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_plasma_vice.lz");

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

static const unsigned char sRRighteousJusticeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/r_righteous_justice.huff");
static const unsigned short sRRighteousJusticeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/r_righteous_justice.gbapal");
static const unsigned char sRRighteousJusticeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/r_righteous_justice.lz");

static const unsigned char sOOversoulBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/o_oversoul.huff");
static const unsigned short sOOversoulBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/o_oversoul.gbapal");
static const unsigned char sOOversoulMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/o_oversoul.lz");

static const unsigned char sFutureFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/future_fusion.huff");
static const unsigned short sFutureFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/future_fusion.gbapal");
static const unsigned char sFutureFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/future_fusion.lz");

static const unsigned char sElementalHeroCoreBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_core.huff");
static const unsigned short sElementalHeroCoreBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_core.gbapal");
static const unsigned char sElementalHeroCoreMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_core.lz");

static const unsigned char sElementalHeroSunriseBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_sunrise.huff");
static const unsigned short sElementalHeroSunriseBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_sunrise.gbapal");
static const unsigned char sElementalHeroSunriseMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_sunrise.lz");

static const unsigned char sElementalHeroCaptainGoldBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_captain_gold.huff");
static const unsigned short sElementalHeroCaptainGoldBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_captain_gold.gbapal");
static const unsigned char sElementalHeroCaptainGoldMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_captain_gold.lz");

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

static const unsigned char sFusionSageBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/fusion_sage.huff");
static const unsigned short sFusionSageBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/fusion_sage.gbapal");
static const unsigned char sFusionSageMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/fusion_sage.lz");

static const unsigned char sLyriluscIndependentNightingaleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lyrilusc_independent_nightingale.huff");
static const unsigned short sLyriluscIndependentNightingaleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lyrilusc_independent_nightingale.gbapal");
static const unsigned char sLyriluscIndependentNightingaleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lyrilusc_independent_nightingale.lz");

static const unsigned char sTheTyrantNeptuneBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_tyrant_neptune.huff");
static const unsigned short sTheTyrantNeptuneBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_tyrant_neptune.gbapal");
static const unsigned char sTheTyrantNeptuneMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_tyrant_neptune.lz");

static const unsigned char sTheSplendidVenusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_splendid_venus.huff");
static const unsigned short sTheSplendidVenusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_splendid_venus.gbapal");
static const unsigned char sTheSplendidVenusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_splendid_venus.lz");

static const unsigned char sTheBigSaturnBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_big_saturn.huff");
static const unsigned short sTheBigSaturnBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_big_saturn.gbapal");
static const unsigned char sTheBigSaturnMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_big_saturn.lz");

static const unsigned char sTheTripperMercuryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_tripper_mercury.huff");
static const unsigned short sTheTripperMercuryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_tripper_mercury.gbapal");
static const unsigned char sTheTripperMercuryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_tripper_mercury.lz");

static const unsigned char sTheGrandJupiterBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_grand_jupiter.huff");
static const unsigned short sTheGrandJupiterBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_grand_jupiter.gbapal");
static const unsigned char sTheGrandJupiterMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_grand_jupiter.lz");

static const unsigned char sTheDespairUranusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_despair_uranus.huff");
static const unsigned short sTheDespairUranusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_despair_uranus.gbapal");
static const unsigned char sTheDespairUranusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_despair_uranus.lz");

static const unsigned char sTheBlazingMarsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_blazing_mars.huff");
static const unsigned short sTheBlazingMarsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_blazing_mars.gbapal");
static const unsigned char sTheBlazingMarsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_blazing_mars.lz");

static const unsigned char sTheSuppressionPlutoBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_suppression_pluto.huff");
static const unsigned short sTheSuppressionPlutoBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_suppression_pluto.gbapal");
static const unsigned char sTheSuppressionPlutoMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_suppression_pluto.lz");

static const unsigned char sTheSupremacySunBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_supremacy_sun.huff");
static const unsigned short sTheSupremacySunBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_supremacy_sun.gbapal");
static const unsigned char sTheSupremacySunMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_supremacy_sun.lz");

static const unsigned char sMightyAngelVirchBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mighty_angel_virch.huff");
static const unsigned short sMightyAngelVirchBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mighty_angel_virch.gbapal");
static const unsigned char sMightyAngelVirchMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mighty_angel_virch.lz");

static const unsigned char sTinyAngelBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/tiny_angel.huff");
static const unsigned short sTinyAngelBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/tiny_angel.gbapal");
static const unsigned char sTinyAngelMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/tiny_angel.lz");

static const unsigned char sZerielBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/zeriel.huff");
static const unsigned short sZerielBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/zeriel.gbapal");
static const unsigned char sZerielMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/zeriel.lz");

static const unsigned char sShatielBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shatiel.huff");
static const unsigned short sShatielBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shatiel.gbapal");
static const unsigned char sShatielMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shatiel.lz");

static const unsigned char sSeraphimBlasterBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/seraphim_blaster.huff");
static const unsigned short sSeraphimBlasterBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/seraphim_blaster.gbapal");
static const unsigned char sSeraphimBlasterMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/seraphim_blaster.lz");

static const unsigned char sIofielBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/iofiel.huff");
static const unsigned short sIofielBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/iofiel.gbapal");
static const unsigned char sIofielMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/iofiel.lz");

static const unsigned char sArchlordKristyaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/archlord_kristya.huff");
static const unsigned short sArchlordKristyaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/archlord_kristya.gbapal");
static const unsigned char sArchlordKristyaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/archlord_kristya.lz");

static const unsigned char sTethysGoddessOfLightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/tethys_goddess_of_light.huff");
static const unsigned short sTethysGoddessOfLightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/tethys_goddess_of_light.gbapal");
static const unsigned char sTethysGoddessOfLightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/tethys_goddess_of_light.lz");

static const unsigned char sAthenaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/athena.huff");
static const unsigned short sAthenaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/athena.gbapal");
static const unsigned char sAthenaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/athena.lz");

static const unsigned char sValhallaHallOfTheFallenBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/valhalla_hall_of_the_fallen.huff");
static const unsigned short sValhallaHallOfTheFallenBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/valhalla_hall_of_the_fallen.gbapal");
static const unsigned char sValhallaHallOfTheFallenMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/valhalla_hall_of_the_fallen.lz");

static const unsigned char sAngelsTearBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/angels_tear.huff");
static const unsigned short sAngelsTearBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/angels_tear.gbapal");
static const unsigned char sAngelsTearMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/angels_tear.lz");

static const unsigned char sDivineSanctuaryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/divine_sanctuary.huff");
static const unsigned short sDivineSanctuaryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/divine_sanctuary.gbapal");
static const unsigned char sDivineSanctuaryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/divine_sanctuary.lz");

static const unsigned char sCourtOfJusticeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/court_of_justice.huff");
static const unsigned short sCourtOfJusticeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/court_of_justice.gbapal");
static const unsigned char sCourtOfJusticeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/court_of_justice.lz");

static const unsigned char sHecatriceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/hecatrice.huff");
static const unsigned short sHecatriceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/hecatrice.gbapal");
static const unsigned char sHecatriceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/hecatrice.lz");

static const unsigned char sPrematureBurialBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/premature_burial.huff");
static const unsigned short sPrematureBurialBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/premature_burial.gbapal");
static const unsigned char sPrematureBurialMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/premature_burial.lz");

static const unsigned char sYubelBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/yubel.huff");
static const unsigned short sYubelBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/yubel.gbapal");
static const unsigned char sYubelMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/yubel.lz");

static const unsigned char sYubelTerrorIncarnateBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/yubel_terror_incarnate.huff");
static const unsigned short sYubelTerrorIncarnateBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/yubel_terror_incarnate.gbapal");
static const unsigned char sYubelTerrorIncarnateMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/yubel_terror_incarnate.lz");

static const unsigned char sYubelTheUltimateNightmareBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/yubel_the_ultimate_nightmare.huff");
static const unsigned short sYubelTheUltimateNightmareBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/yubel_the_ultimate_nightmare.gbapal");
static const unsigned char sYubelTheUltimateNightmareMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/yubel_the_ultimate_nightmare.lz");

static const unsigned char sTheTrickyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_tricky.huff");
static const unsigned short sTheTrickyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_tricky.gbapal");
static const unsigned char sTheTrickyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_tricky.lz");

const unsigned char *gCardArts_Hook[] APPEND_RODATA = {
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
  [0x0395] = sKa2DesScissorsBigArt,
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
  [0x03BC] = sServantOfCatabolismBigArt,
  [0x03BD] = sManThroTroBigArt,
  [0x03BE] = sLevelLimitAreaBBigArt,
  [0x03BF] = sSpiritRyuBigArt,
  [0x03C0] = sAmazonessTigerBigArt,
  [0x03C1] = sBlastHeldByATributeBigArt,
  [0x03C2] = sDDWarriorBigArt,
  [0x03C3] = sConfiscationBigArt,
  [0x03C4] = sBreakerTheMagicalWarriorBigArt,
  [0x03C5] = sDesKangarooBigArt,
  [0x03C6] = sDrillagoBigArt,
  [0x03C7] = sDarkSnakeSyndromeBigArt,
  [0x03C8] = sJarRobberBigArt,
  [0x03C9] = sGravekeepersServantBigArt,
  [0x03CA] = sDiceJarBigArt,
  [0x03CB] = sKnightsTitleBigArt,
  [0x03CC] = sJowlsOfDarkDemiseBigArt,
  [0x03CD] = sKishidoSpiritBigArt,
  [0x03CE] = sPossessedDarkSoulBigArt,
  [0x03CF] = sRoyalKnightBigArt,
  [0x03D0] = sTheThingInTheCraterBigArt,
  [0x03D1] = sCreatureSwapBigArt,
  [0x03D2] = sLesserFiendBigArt,
  [0x03D3] = sSpiritOfThePotOfGreedBigArt,
  [0x03D4] = sZaborgTheThunderMonarchBigArt,
  [0x03D5] = sBottomlessShiftingSandBigArt,
  [0x03D6] = sFirePrincessBigArt,
  [0x03D7] = sInvaderOfTheThroneBigArt,
  [0x03D8] = sTheFluteOfSummoningDragonBigArt,
  [0x03D9] = sSpiritCallerBigArt,
  [0x03DA] = sVengefulBogSpiritBigArt,
  [0x03DB] = sWallOfRevealingLightBigArt,
  [0x03DC] = sWorldSuppressionBigArt,
  [0x03DD] = sRyuKishinClownBigArt,
  [0x03DE] = sDarkDustSpiritBigArt,
  [0x03DF] = sGhostKnightOfJackalBigArt,
  [0x03E0] = sKaiserColosseumBigArt,
  [0x03E1] = sNightmareWheelBigArt,
  [0x03E2] = sMirrorWallBigArt,
  [0x03E3] = sMajuGarzettBigArt,
  [0x03E4] = sDustTornadoBigArt,
  [0x03E5] = sEctoplasmerBigArt,
  [0x03E6] = sLeviaDragonDaedalusBigArt,
  [0x03E7] = sThebanNightmareBigArt,
  [0x03E8] = sBigBangShotBigArt,
  [0x03E9] = sPolymerizationBigArt,
  [0x03EA] = sCyberDragonBigArt,
  [0x03EB] = sCyberTwinDragonBigArt,
  [0x03EC] = sCyberEndDragonBigArt,
  [0x03ED] = sCaiusTheShadowMonarchBigArt,
  [0x03EE] = sMobiusTheFrostMonarchBigArt,
  [0x03EF] = sProtoCyberDragonBigArt,
  [0x03F0] = sAmazonessArcherBigArt,
  [0x03F1] = sElementalHeroAvianBigArt,
  [0x03F2] = sElementalHeroBurstinatrixBigArt,
  [0x03F3] = sElementalHeroSparkmanBigArt,
  [0x03F4] = sElementalHeroBubblemanBigArt,
  [0x03F5] = sElementalHeroWildheartBigArt,
  [0x03F6] = sElementalHeroBladedgeBigArt,
  [0x03F7] = sElementalHeroClaymanBigArt,
  [0x03F8] = sElementalHeroMudballmanBigArt,
  [0x03F9] = sHarpieLady1BigArt,
  [0x03FA] = sHarpieLady2BigArt,
  [0x03FB] = sHarpieLady3BigArt,
  [0x03FC] = sSpellEconomicsBigArt,
  [0x03FD] = sTheUnstoppableExodiaIncarnateBigArt,
  [0x03FE] = sTheSanctuaryInTheSkyBigArt,
  [0x03FF] = sMirrorForceBigArt,
  [0x0400] = sLevelLimitAreaABigArt,
  [0x0401] = sHarpiesPetBabyDragonBigArt,
  [0x0402] = sBlueEyesChaosDragonBigArt,
  [0x0403] = sBlowbackDragonBigArt,
  [0x0404] = sChaosCommandMagicianBigArt,
  [0x0405] = sBookOfLifeBigArt,
  [0x0406] = sBookOfTaiyouBigArt,
  [0x0407] = sDeFusionBigArt,
  [0x0408] = sDiffusionWaveMotionBigArt,
  [0x0409] = sAutonomousActionUnitBigArt,
  [0x040A] = sElementalHeroRampartBlasterBigArt,
  [0x040B] = sALegendaryOceanBigArt,
  [0x040C] = sDarkMagicianOfChaosBigArt,
  [0x040D] = sDedicationThroughLightAndDarknessBigArt,
  [0x040E] = sElementalHeroSteamHealerBigArt,
  [0x040F] = sElementalHeroPhoenixEnforcerBigArt,
  [0x0410] = sElementalHeroShiningPhoenixEnforcerBigArt,
  [0x0411] = sElementalHeroFlameWingmanBigArt,
  [0x0412] = sElementalHeroShiningFlareWingmanBigArt,
  [0x0413] = sElementalHeroTempestBigArt,
  [0x0414] = sElementalHeroWildedgeBigArt,
  [0x0415] = sElementalHeroThunderGiantBigArt,
  [0x0416] = sElementalHeroMarinerBigArt,
  [0x0417] = sElementalHeroElectrumBigArt,
  [0x0418] = sElementalHeroNecroshadeBigArt,
  [0x0419] = sMiracleFusionBigArt,
  [0x041A] = sTheAgentOfForceMarsBigArt,
  [0x041B] = sChaosEmperorDragonEnvoyOfTheEndBigArt,
  [0x041C] = sBlackLusterSoldierEnvoyOfTheBeginningBigArt,
  [0x041D] = sElementalHeroNeosBigArt,
  [0x041E] = sElementalHeroWoodsmanBigArt,
  [0x041F] = sElementalHeroOceanBigArt,
  [0x0420] = sElementalHeroHeatBigArt,
  [0x0421] = sElementalHeroLadyHeatBigArt,
  [0x0422] = sElementalHeroNeosAliusBigArt,
  [0x0423] = sElementalHeroGreatTornadoBigArt,
  [0x0424] = sElementalHeroTerraFirmaBigArt,
  [0x0425] = sElementalHeroKnospeBigArt,
  [0x0426] = sElementalHeroPoisonRoseBigArt,
  [0x0427] = sElementalHeroAbsoluteZeroBigArt,
  [0x0428] = sElementalHeroWildWingmanBigArt,
  [0x0429] = sElementalHeroVolticBigArt,
  [0x042A] = sElementalHeroFlashBigArt,
  [0x042B] = sElementalHeroGaiaBigArt,
  [0x042C] = sElementalHeroEscuridaoBigArt,
  [0x042D] = sElementalHeroTheShiningBigArt,
  [0x042E] = sElementalHeroInfernoBigArt,
  [0x042F] = sElementalHeroNecroidShamanBigArt,
  [0x0430] = sElementalHeroPlasmaViceBigArt,
  [0x0431] = sFusionRecoveryBigArt,
  [0x0432] = sSkyscraperBigArt,
  [0x0433] = sHHeatedHeartBigArt,
  [0x0434] = sEEmergencyCallBigArt,
  [0x0435] = sRRighteousJusticeBigArt,
  [0x0436] = sOOversoulBigArt,
  [0x0437] = sFutureFusionBigArt,
  [0x0438] = sElementalHeroCoreBigArt,
  [0x0439] = sElementalHeroSunriseBigArt,
  [0x043A] = sElementalHeroCaptainGoldBigArt,
  [0x043B] = sElementalHeroIceEdgeBigArt,
  [0x043C] = sElementalHeroBlazemanBigArt,
  [0x043D] = sElementalHeroStratosBigArt,
  [0x043E] = sChimeratechOverdragonBigArt,
  [0x043F] = sCyberneticFusionSupportBigArt,
  [0x0440] = sOverloadFusionBigArt,
  [0x0441] = sPowerBondBigArt,
  [0x0442] = sFusionSageBigArt,
  [0x0443] = sLyriluscIndependentNightingaleBigArt,
  [0x0444] = sTheTyrantNeptuneBigArt,
  [0x0445] = sTheSplendidVenusBigArt,
  [0x0446] = sTheBigSaturnBigArt,
  [0x0447] = sTheTripperMercuryBigArt,
  [0x0448] = sTheGrandJupiterBigArt,
  [0x0449] = sTheDespairUranusBigArt,
  [0x044A] = sTheBlazingMarsBigArt,
  [0x044B] = sTheSuppressionPlutoBigArt,
  [0x044C] = sTheSupremacySunBigArt,
  [0x044D] = sMightyAngelVirchBigArt,
  [0x044E] = sTinyAngelBigArt,
  [0x044F] = sZerielBigArt,
  [0x0450] = sShatielBigArt,
  [0x0451] = sSeraphimBlasterBigArt,
  [0x0452] = sIofielBigArt,
  [0x0453] = sArchlordKristyaBigArt,
  [0x0454] = sTethysGoddessOfLightBigArt,
  [0x0455] = sAthenaBigArt,
  [0x0456] = sValhallaHallOfTheFallenBigArt,
  [0x0457] = sAngelsTearBigArt,
  [0x0458] = sDivineSanctuaryBigArt,
  [0x0459] = sCourtOfJusticeBigArt,
  [0x045A] = sHecatriceBigArt,
  [0x045B] = sPrematureBurialBigArt,
  [0x045C] = sYubelBigArt,
  [0x045D] = sYubelTerrorIncarnateBigArt,
  [0x045E] = sYubelTheUltimateNightmareBigArt,
  [0x045F] = sTheTrickyBigArt,
};

const unsigned short *gCardArtPalettes_Hook[] APPEND_RODATA = {
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
  [0x0395] = sKa2DesScissorsBigPalette,
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
  [0x03BC] = sServantOfCatabolismBigPalette,
  [0x03BD] = sManThroTroBigPalette,
  [0x03BE] = sLevelLimitAreaBBigPalette,
  [0x03BF] = sSpiritRyuBigPalette,
  [0x03C0] = sAmazonessTigerBigPalette,
  [0x03C1] = sBlastHeldByATributeBigPalette,
  [0x03C2] = sDDWarriorBigPalette,
  [0x03C3] = sConfiscationBigPalette,
  [0x03C4] = sBreakerTheMagicalWarriorBigPalette,
  [0x03C5] = sDesKangarooBigPalette,
  [0x03C6] = sDrillagoBigPalette,
  [0x03C7] = sDarkSnakeSyndromeBigPalette,
  [0x03C8] = sJarRobberBigPalette,
  [0x03C9] = sGravekeepersServantBigPalette,
  [0x03CA] = sDiceJarBigPalette,
  [0x03CB] = sKnightsTitleBigPalette,
  [0x03CC] = sJowlsOfDarkDemiseBigPalette,
  [0x03CD] = sKishidoSpiritBigPalette,
  [0x03CE] = sPossessedDarkSoulBigPalette,
  [0x03CF] = sRoyalKnightBigPalette,
  [0x03D0] = sTheThingInTheCraterBigPalette,
  [0x03D1] = sCreatureSwapBigPalette,
  [0x03D2] = sLesserFiendBigPalette,
  [0x03D3] = sSpiritOfThePotOfGreedBigPalette,
  [0x03D4] = sZaborgTheThunderMonarchBigPalette,
  [0x03D5] = sBottomlessShiftingSandBigPalette,
  [0x03D6] = sFirePrincessBigPalette,
  [0x03D7] = sInvaderOfTheThroneBigPalette,
  [0x03D8] = sTheFluteOfSummoningDragonBigPalette,
  [0x03D9] = sSpiritCallerBigPalette,
  [0x03DA] = sVengefulBogSpiritBigPalette,
  [0x03DB] = sWallOfRevealingLightBigPalette,
  [0x03DC] = sWorldSuppressionBigPalette,
  [0x03DD] = sRyuKishinClownBigPalette,
  [0x03DE] = sDarkDustSpiritBigPalette,
  [0x03DF] = sGhostKnightOfJackalBigPalette,
  [0x03E0] = sKaiserColosseumBigPalette,
  [0x03E1] = sNightmareWheelBigPalette,
  [0x03E2] = sMirrorWallBigPalette,
  [0x03E3] = sMajuGarzettBigPalette,
  [0x03E4] = sDustTornadoBigPalette,
  [0x03E5] = sEctoplasmerBigPalette,
  [0x03E6] = sLeviaDragonDaedalusBigPalette,
  [0x03E7] = sThebanNightmareBigPalette,
  [0x03E8] = sBigBangShotBigPalette,
  [0x03E9] = sPolymerizationBigPalette,
  [0x03EA] = sCyberDragonBigPalette,
  [0x03EB] = sCyberTwinDragonBigPalette,
  [0x03EC] = sCyberEndDragonBigPalette,
  [0x03ED] = sCaiusTheShadowMonarchBigPalette,
  [0x03EE] = sMobiusTheFrostMonarchBigPalette,
  [0x03EF] = sProtoCyberDragonBigPalette,
  [0x03F0] = sAmazonessArcherBigPalette,
  [0x03F1] = sElementalHeroAvianBigPalette,
  [0x03F2] = sElementalHeroBurstinatrixBigPalette,
  [0x03F3] = sElementalHeroSparkmanBigPalette,
  [0x03F4] = sElementalHeroBubblemanBigPalette,
  [0x03F5] = sElementalHeroWildheartBigPalette,
  [0x03F6] = sElementalHeroBladedgeBigPalette,
  [0x03F7] = sElementalHeroClaymanBigPalette,
  [0x03F8] = sElementalHeroMudballmanBigPalette,
  [0x03F9] = sHarpieLady1BigPalette,
  [0x03FA] = sHarpieLady2BigPalette,
  [0x03FB] = sHarpieLady3BigPalette,
  [0x03FC] = sSpellEconomicsBigPalette,
  [0x03FD] = sTheUnstoppableExodiaIncarnateBigPalette,
  [0x03FE] = sTheSanctuaryInTheSkyBigPalette,
  [0x03FF] = sMirrorForceBigPalette,
  [0x0400] = sLevelLimitAreaABigPalette,
  [0x0401] = sHarpiesPetBabyDragonBigPalette,
  [0x0402] = sBlueEyesChaosDragonBigPalette,
  [0x0403] = sBlowbackDragonBigPalette,
  [0x0404] = sChaosCommandMagicianBigPalette,
  [0x0405] = sBookOfLifeBigPalette,
  [0x0406] = sBookOfTaiyouBigPalette,
  [0x0407] = sDeFusionBigPalette,
  [0x0408] = sDiffusionWaveMotionBigPalette,
  [0x0409] = sAutonomousActionUnitBigPalette,
  [0x040A] = sElementalHeroRampartBlasterBigPalette,
  [0x040B] = sALegendaryOceanBigPalette,
  [0x040C] = sDarkMagicianOfChaosBigPalette,
  [0x040D] = sDedicationThroughLightAndDarknessBigPalette,
  [0x040E] = sElementalHeroSteamHealerBigPalette,
  [0x040F] = sElementalHeroPhoenixEnforcerBigPalette,
  [0x0410] = sElementalHeroShiningPhoenixEnforcerBigPalette,
  [0x0411] = sElementalHeroFlameWingmanBigPalette,
  [0x0412] = sElementalHeroShiningFlareWingmanBigPalette,
  [0x0413] = sElementalHeroTempestBigPalette,
  [0x0414] = sElementalHeroWildedgeBigPalette,
  [0x0415] = sElementalHeroThunderGiantBigPalette,
  [0x0416] = sElementalHeroMarinerBigPalette,
  [0x0417] = sElementalHeroElectrumBigPalette,
  [0x0418] = sElementalHeroNecroshadeBigPalette,
  [0x0419] = sMiracleFusionBigPalette,
  [0x041A] = sTheAgentOfForceMarsBigPalette,
  [0x041B] = sChaosEmperorDragonEnvoyOfTheEndBigPalette,
  [0x041C] = sBlackLusterSoldierEnvoyOfTheBeginningBigPalette,
  [0x041D] = sElementalHeroNeosBigPalette,
  [0x041E] = sElementalHeroWoodsmanBigPalette,
  [0x041F] = sElementalHeroOceanBigPalette,
  [0x0420] = sElementalHeroHeatBigPalette,
  [0x0421] = sElementalHeroLadyHeatBigPalette,
  [0x0422] = sElementalHeroNeosAliusBigPalette,
  [0x0423] = sElementalHeroGreatTornadoBigPalette,
  [0x0424] = sElementalHeroTerraFirmaBigPalette,
  [0x0425] = sElementalHeroKnospeBigPalette,
  [0x0426] = sElementalHeroPoisonRoseBigPalette,
  [0x0427] = sElementalHeroAbsoluteZeroBigPalette,
  [0x0428] = sElementalHeroWildWingmanBigPalette,
  [0x0429] = sElementalHeroVolticBigPalette,
  [0x042A] = sElementalHeroFlashBigPalette,
  [0x042B] = sElementalHeroGaiaBigPalette,
  [0x042C] = sElementalHeroEscuridaoBigPalette,
  [0x042D] = sElementalHeroTheShiningBigPalette,
  [0x042E] = sElementalHeroInfernoBigPalette,
  [0x042F] = sElementalHeroNecroidShamanBigPalette,
  [0x0430] = sElementalHeroPlasmaViceBigPalette,
  [0x0431] = sFusionRecoveryBigPalette,
  [0x0432] = sSkyscraperBigPalette,
  [0x0433] = sHHeatedHeartBigPalette,
  [0x0434] = sEEmergencyCallBigPalette,
  [0x0435] = sRRighteousJusticeBigPalette,
  [0x0436] = sOOversoulBigPalette,
  [0x0437] = sFutureFusionBigPalette,
  [0x0438] = sElementalHeroCoreBigPalette,
  [0x0439] = sElementalHeroSunriseBigPalette,
  [0x043A] = sElementalHeroCaptainGoldBigPalette,
  [0x043B] = sElementalHeroIceEdgeBigPalette,
  [0x043C] = sElementalHeroBlazemanBigPalette,
  [0x043D] = sElementalHeroStratosBigPalette,
  [0x043E] = sChimeratechOverdragonBigPalette,
  [0x043F] = sCyberneticFusionSupportBigPalette,
  [0x0440] = sOverloadFusionBigPalette,
  [0x0441] = sPowerBondBigPalette,
  [0x0442] = sFusionSageBigPalette,
  [0x0443] = sLyriluscIndependentNightingaleBigPalette,
  [0x0444] = sTheTyrantNeptuneBigPalette,
  [0x0445] = sTheSplendidVenusBigPalette,
  [0x0446] = sTheBigSaturnBigPalette,
  [0x0447] = sTheTripperMercuryBigPalette,
  [0x0448] = sTheGrandJupiterBigPalette,
  [0x0449] = sTheDespairUranusBigPalette,
  [0x044A] = sTheBlazingMarsBigPalette,
  [0x044B] = sTheSuppressionPlutoBigPalette,
  [0x044C] = sTheSupremacySunBigPalette,
  [0x044D] = sMightyAngelVirchBigPalette,
  [0x044E] = sTinyAngelBigPalette,
  [0x044F] = sZerielBigPalette,
  [0x0450] = sShatielBigPalette,
  [0x0451] = sSeraphimBlasterBigPalette,
  [0x0452] = sIofielBigPalette,
  [0x0453] = sArchlordKristyaBigPalette,
  [0x0454] = sTethysGoddessOfLightBigPalette,
  [0x0455] = sAthenaBigPalette,
  [0x0456] = sValhallaHallOfTheFallenBigPalette,
  [0x0457] = sAngelsTearBigPalette,
  [0x0458] = sDivineSanctuaryBigPalette,
  [0x0459] = sCourtOfJusticeBigPalette,
  [0x045A] = sHecatriceBigPalette,
  [0x045B] = sPrematureBurialBigPalette,
  [0x045C] = sYubelBigPalette,
  [0x045D] = sYubelTerrorIncarnateBigPalette,
  [0x045E] = sYubelTheUltimateNightmareBigPalette,
  [0x045F] = sTheTrickyBigPalette,
};

const u8 gCardArtUsesExtendedPalette_Hook[] APPEND_RODATA = {
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
  [0x03F0] = 0,
  [0x03F1] = 0,
  [0x03F2] = 0,
  [0x03F3] = 0,
  [0x03F4] = 0,
  [0x03F5] = 0,
  [0x03F6] = 0,
  [0x03F7] = 0,
  [0x03F8] = 0,
  [0x03F9] = 0,
  [0x03FA] = 0,
  [0x03FB] = 0,
  [0x03FC] = 0,
  [0x03FD] = 0,
  [0x03FE] = 0,
  [0x03FF] = 0,
  [0x0400] = 0,
  [0x0401] = 0,
  [0x0402] = 0,
  [0x0403] = 0,
  [0x0404] = 0,
  [0x0405] = 0,
  [0x0406] = 0,
  [0x0407] = 0,
  [0x0408] = 0,
  [0x0409] = 0,
  [0x040A] = 0,
  [0x040B] = 0,
  [0x040C] = 0,
  [0x040D] = 0,
  [0x040E] = 0,
  [0x040F] = 0,
  [0x0410] = 0,
  [0x0411] = 0,
  [0x0412] = 0,
  [0x0413] = 0,
  [0x0414] = 0,
  [0x0415] = 0,
  [0x0416] = 0,
  [0x0417] = 0,
  [0x0418] = 0,
  [0x0419] = 0,
  [0x041A] = 0,
  [0x041B] = 0,
  [0x041C] = 0,
  [0x041D] = 0,
  [0x041E] = 0,
  [0x041F] = 0,
  [0x0420] = 0,
  [0x0421] = 0,
  [0x0422] = 0,
  [0x0423] = 0,
  [0x0424] = 0,
  [0x0425] = 0,
  [0x0426] = 0,
  [0x0427] = 0,
  [0x0428] = 0,
  [0x0429] = 0,
  [0x042A] = 0,
  [0x042B] = 0,
  [0x042C] = 0,
  [0x042D] = 0,
  [0x042E] = 0,
  [0x042F] = 0,
  [0x0430] = 0,
  [0x0431] = 0,
  [0x0432] = 0,
  [0x0433] = 0,
  [0x0434] = 0,
  [0x0435] = 0,
  [0x0436] = 0,
  [0x0437] = 0,
  [0x0438] = 0,
  [0x0439] = 0,
  [0x043A] = 0,
  [0x043B] = 0,
  [0x043C] = 0,
  [0x043D] = 0,
  [0x043E] = 0,
  [0x043F] = 0,
  [0x0440] = 0,
  [0x0441] = 0,
  [0x0442] = 0,
  [0x0443] = 0,
  [0x0444] = 0,
  [0x0445] = 0,
  [0x0446] = 0,
  [0x0447] = 0,
  [0x0448] = 0,
  [0x0449] = 0,
  [0x044A] = 0,
  [0x044B] = 0,
  [0x044C] = 0,
  [0x044D] = 0,
  [0x044E] = 0,
  [0x044F] = 0,
  [0x0450] = 0,
  [0x0451] = 0,
  [0x0452] = 0,
  [0x0453] = 0,
  [0x0454] = 0,
  [0x0455] = 0,
  [0x0456] = 0,
  [0x0457] = 0,
  [0x0458] = 0,
  [0x0459] = 0,
  [0x045A] = 0,
  [0x045B] = 0,
  [0x045C] = 0,
  [0x045D] = 0,
  [0x045E] = 0,
  [0x045F] = 0,
};

const unsigned char *gMiniCardArts_Hook[] APPEND_RODATA = {
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
  [0x0395] = sKa2DesScissorsMiniArt,
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
  [0x03BC] = sServantOfCatabolismMiniArt,
  [0x03BD] = sManThroTroMiniArt,
  [0x03BE] = sLevelLimitAreaBMiniArt,
  [0x03BF] = sSpiritRyuMiniArt,
  [0x03C0] = sAmazonessTigerMiniArt,
  [0x03C1] = sBlastHeldByATributeMiniArt,
  [0x03C2] = sDDWarriorMiniArt,
  [0x03C3] = sConfiscationMiniArt,
  [0x03C4] = sBreakerTheMagicalWarriorMiniArt,
  [0x03C5] = sDesKangarooMiniArt,
  [0x03C6] = sDrillagoMiniArt,
  [0x03C7] = sDarkSnakeSyndromeMiniArt,
  [0x03C8] = sJarRobberMiniArt,
  [0x03C9] = sGravekeepersServantMiniArt,
  [0x03CA] = sDiceJarMiniArt,
  [0x03CB] = sKnightsTitleMiniArt,
  [0x03CC] = sJowlsOfDarkDemiseMiniArt,
  [0x03CD] = sKishidoSpiritMiniArt,
  [0x03CE] = sPossessedDarkSoulMiniArt,
  [0x03CF] = sRoyalKnightMiniArt,
  [0x03D0] = sTheThingInTheCraterMiniArt,
  [0x03D1] = sCreatureSwapMiniArt,
  [0x03D2] = sLesserFiendMiniArt,
  [0x03D3] = sSpiritOfThePotOfGreedMiniArt,
  [0x03D4] = sZaborgTheThunderMonarchMiniArt,
  [0x03D5] = sBottomlessShiftingSandMiniArt,
  [0x03D6] = sFirePrincessMiniArt,
  [0x03D7] = sInvaderOfTheThroneMiniArt,
  [0x03D8] = sTheFluteOfSummoningDragonMiniArt,
  [0x03D9] = sSpiritCallerMiniArt,
  [0x03DA] = sVengefulBogSpiritMiniArt,
  [0x03DB] = sWallOfRevealingLightMiniArt,
  [0x03DC] = sWorldSuppressionMiniArt,
  [0x03DD] = sRyuKishinClownMiniArt,
  [0x03DE] = sDarkDustSpiritMiniArt,
  [0x03DF] = sGhostKnightOfJackalMiniArt,
  [0x03E0] = sKaiserColosseumMiniArt,
  [0x03E1] = sNightmareWheelMiniArt,
  [0x03E2] = sMirrorWallMiniArt,
  [0x03E3] = sMajuGarzettMiniArt,
  [0x03E4] = sDustTornadoMiniArt,
  [0x03E5] = sEctoplasmerMiniArt,
  [0x03E6] = sLeviaDragonDaedalusMiniArt,
  [0x03E7] = sThebanNightmareMiniArt,
  [0x03E8] = sBigBangShotMiniArt,
  [0x03E9] = sPolymerizationMiniArt,
  [0x03EA] = sCyberDragonMiniArt,
  [0x03EB] = sCyberTwinDragonMiniArt,
  [0x03EC] = sCyberEndDragonMiniArt,
  [0x03ED] = sCaiusTheShadowMonarchMiniArt,
  [0x03EE] = sMobiusTheFrostMonarchMiniArt,
  [0x03EF] = sProtoCyberDragonMiniArt,
  [0x03F0] = sAmazonessArcherMiniArt,
  [0x03F1] = sElementalHeroAvianMiniArt,
  [0x03F2] = sElementalHeroBurstinatrixMiniArt,
  [0x03F3] = sElementalHeroSparkmanMiniArt,
  [0x03F4] = sElementalHeroBubblemanMiniArt,
  [0x03F5] = sElementalHeroWildheartMiniArt,
  [0x03F6] = sElementalHeroBladedgeMiniArt,
  [0x03F7] = sElementalHeroClaymanMiniArt,
  [0x03F8] = sElementalHeroMudballmanMiniArt,
  [0x03F9] = sHarpieLady1MiniArt,
  [0x03FA] = sHarpieLady2MiniArt,
  [0x03FB] = sHarpieLady3MiniArt,
  [0x03FC] = sSpellEconomicsMiniArt,
  [0x03FD] = sTheUnstoppableExodiaIncarnateMiniArt,
  [0x03FE] = sTheSanctuaryInTheSkyMiniArt,
  [0x03FF] = sMirrorForceMiniArt,
  [0x0400] = sLevelLimitAreaAMiniArt,
  [0x0401] = sHarpiesPetBabyDragonMiniArt,
  [0x0402] = sBlueEyesChaosDragonMiniArt,
  [0x0403] = sBlowbackDragonMiniArt,
  [0x0404] = sChaosCommandMagicianMiniArt,
  [0x0405] = sBookOfLifeMiniArt,
  [0x0406] = sBookOfTaiyouMiniArt,
  [0x0407] = sDeFusionMiniArt,
  [0x0408] = sDiffusionWaveMotionMiniArt,
  [0x0409] = sAutonomousActionUnitMiniArt,
  [0x040A] = sElementalHeroRampartBlasterMiniArt,
  [0x040B] = sALegendaryOceanMiniArt,
  [0x040C] = sDarkMagicianOfChaosMiniArt,
  [0x040D] = sDedicationThroughLightAndDarknessMiniArt,
  [0x040E] = sElementalHeroSteamHealerMiniArt,
  [0x040F] = sElementalHeroPhoenixEnforcerMiniArt,
  [0x0410] = sElementalHeroShiningPhoenixEnforcerMiniArt,
  [0x0411] = sElementalHeroFlameWingmanMiniArt,
  [0x0412] = sElementalHeroShiningFlareWingmanMiniArt,
  [0x0413] = sElementalHeroTempestMiniArt,
  [0x0414] = sElementalHeroWildedgeMiniArt,
  [0x0415] = sElementalHeroThunderGiantMiniArt,
  [0x0416] = sElementalHeroMarinerMiniArt,
  [0x0417] = sElementalHeroElectrumMiniArt,
  [0x0418] = sElementalHeroNecroshadeMiniArt,
  [0x0419] = sMiracleFusionMiniArt,
  [0x041A] = sTheAgentOfForceMarsMiniArt,
  [0x041B] = sChaosEmperorDragonEnvoyOfTheEndMiniArt,
  [0x041C] = sBlackLusterSoldierEnvoyOfTheBeginningMiniArt,
  [0x041D] = sElementalHeroNeosMiniArt,
  [0x041E] = sElementalHeroWoodsmanMiniArt,
  [0x041F] = sElementalHeroOceanMiniArt,
  [0x0420] = sElementalHeroHeatMiniArt,
  [0x0421] = sElementalHeroLadyHeatMiniArt,
  [0x0422] = sElementalHeroNeosAliusMiniArt,
  [0x0423] = sElementalHeroGreatTornadoMiniArt,
  [0x0424] = sElementalHeroTerraFirmaMiniArt,
  [0x0425] = sElementalHeroKnospeMiniArt,
  [0x0426] = sElementalHeroPoisonRoseMiniArt,
  [0x0427] = sElementalHeroAbsoluteZeroMiniArt,
  [0x0428] = sElementalHeroWildWingmanMiniArt,
  [0x0429] = sElementalHeroVolticMiniArt,
  [0x042A] = sElementalHeroFlashMiniArt,
  [0x042B] = sElementalHeroGaiaMiniArt,
  [0x042C] = sElementalHeroEscuridaoMiniArt,
  [0x042D] = sElementalHeroTheShiningMiniArt,
  [0x042E] = sElementalHeroInfernoMiniArt,
  [0x042F] = sElementalHeroNecroidShamanMiniArt,
  [0x0430] = sElementalHeroPlasmaViceMiniArt,
  [0x0431] = sFusionRecoveryMiniArt,
  [0x0432] = sSkyscraperMiniArt,
  [0x0433] = sHHeatedHeartMiniArt,
  [0x0434] = sEEmergencyCallMiniArt,
  [0x0435] = sRRighteousJusticeMiniArt,
  [0x0436] = sOOversoulMiniArt,
  [0x0437] = sFutureFusionMiniArt,
  [0x0438] = sElementalHeroCoreMiniArt,
  [0x0439] = sElementalHeroSunriseMiniArt,
  [0x043A] = sElementalHeroCaptainGoldMiniArt,
  [0x043B] = sElementalHeroIceEdgeMiniArt,
  [0x043C] = sElementalHeroBlazemanMiniArt,
  [0x043D] = sElementalHeroStratosMiniArt,
  [0x043E] = sChimeratechOverdragonMiniArt,
  [0x043F] = sCyberneticFusionSupportMiniArt,
  [0x0440] = sOverloadFusionMiniArt,
  [0x0441] = sPowerBondMiniArt,
  [0x0442] = sFusionSageMiniArt,
  [0x0443] = sLyriluscIndependentNightingaleMiniArt,
  [0x0444] = sTheTyrantNeptuneMiniArt,
  [0x0445] = sTheSplendidVenusMiniArt,
  [0x0446] = sTheBigSaturnMiniArt,
  [0x0447] = sTheTripperMercuryMiniArt,
  [0x0448] = sTheGrandJupiterMiniArt,
  [0x0449] = sTheDespairUranusMiniArt,
  [0x044A] = sTheBlazingMarsMiniArt,
  [0x044B] = sTheSuppressionPlutoMiniArt,
  [0x044C] = sTheSupremacySunMiniArt,
  [0x044D] = sMightyAngelVirchMiniArt,
  [0x044E] = sTinyAngelMiniArt,
  [0x044F] = sZerielMiniArt,
  [0x0450] = sShatielMiniArt,
  [0x0451] = sSeraphimBlasterMiniArt,
  [0x0452] = sIofielMiniArt,
  [0x0453] = sArchlordKristyaMiniArt,
  [0x0454] = sTethysGoddessOfLightMiniArt,
  [0x0455] = sAthenaMiniArt,
  [0x0456] = sValhallaHallOfTheFallenMiniArt,
  [0x0457] = sAngelsTearMiniArt,
  [0x0458] = sDivineSanctuaryMiniArt,
  [0x0459] = sCourtOfJusticeMiniArt,
  [0x045A] = sHecatriceMiniArt,
  [0x045B] = sPrematureBurialMiniArt,
  [0x045C] = sYubelMiniArt,
  [0x045D] = sYubelTerrorIncarnateMiniArt,
  [0x045E] = sYubelTheUltimateNightmareMiniArt,
  [0x045F] = sTheTrickyMiniArt,
};
