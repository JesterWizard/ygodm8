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

static const unsigned char sTheWickedDreadrootBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_wicked_dreadroot.huff");
static const unsigned short sTheWickedDreadrootBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_wicked_dreadroot.gbapal");
static const unsigned char sTheWickedDreadrootMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_wicked_dreadroot.lz");

static const unsigned char sTheWickedEraserBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_wicked_eraser.huff");
static const unsigned short sTheWickedEraserBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_wicked_eraser.gbapal");
static const unsigned char sTheWickedEraserMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_wicked_eraser.lz");

static const unsigned char sTheWickedAvatarBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_wicked_avatar.huff");
static const unsigned short sTheWickedAvatarBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_wicked_avatar.gbapal");
static const unsigned char sTheWickedAvatarMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_wicked_avatar.lz");

static const unsigned char sTributeDollBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/tribute_doll.huff");
static const unsigned short sTributeDollBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/tribute_doll.gbapal");
static const unsigned char sTributeDollMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/tribute_doll.lz");

static const unsigned char sTradeInBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/trade_in.huff");
static const unsigned short sTradeInBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/trade_in.gbapal");
static const unsigned char sTradeInMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/trade_in.lz");

static const unsigned char sCyberBarrierDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cyber_barrier_dragon.huff");
static const unsigned short sCyberBarrierDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cyber_barrier_dragon.gbapal");
static const unsigned char sCyberBarrierDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cyber_barrier_dragon.lz");

static const unsigned char sCyberLaserDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cyber_laser_dragon.huff");
static const unsigned short sCyberLaserDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cyber_laser_dragon.gbapal");
static const unsigned char sCyberLaserDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cyber_laser_dragon.lz");

static const unsigned char sDarkEndDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_end_dragon.huff");
static const unsigned short sDarkEndDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_end_dragon.gbapal");
static const unsigned char sDarkEndDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_end_dragon.lz");

static const unsigned char sLightEndDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/light_end_dragon.huff");
static const unsigned short sLightEndDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/light_end_dragon.gbapal");
static const unsigned char sLightEndDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/light_end_dragon.lz");

static const unsigned char sDarkArmedDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_armed_dragon.huff");
static const unsigned short sDarkArmedDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_armed_dragon.gbapal");
static const unsigned char sDarkArmedDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_armed_dragon.lz");

static const unsigned char sAHeroEmergesBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/a_hero_emerges.huff");
static const unsigned short sAHeroEmergesBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/a_hero_emerges.gbapal");
static const unsigned char sAHeroEmergesMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/a_hero_emerges.lz");

static const unsigned char sAHeroLivesBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/a_hero_lives.huff");
static const unsigned short sAHeroLivesBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/a_hero_lives.gbapal");
static const unsigned char sAHeroLivesMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/a_hero_lives.lz");

static const unsigned char sAWingbeatOfGiantDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/a_wingbeat_of_giant_dragon.huff");
static const unsigned short sAWingbeatOfGiantDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/a_wingbeat_of_giant_dragon.gbapal");
static const unsigned char sAWingbeatOfGiantDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/a_wingbeat_of_giant_dragon.lz");

static const unsigned char sAllureOfDarknessBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/allure_of_darkness.huff");
static const unsigned short sAllureOfDarknessBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/allure_of_darkness.gbapal");
static const unsigned char sAllureOfDarknessMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/allure_of_darkness.lz");

static const unsigned char sAmuletDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/amulet_dragon.huff");
static const unsigned short sAmuletDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/amulet_dragon.gbapal");
static const unsigned char sAmuletDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/amulet_dragon.lz");

static const unsigned char sAndroSphinxBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/andro_sphinx.huff");
static const unsigned short sAndroSphinxBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/andro_sphinx.gbapal");
static const unsigned char sAndroSphinxMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/andro_sphinx.lz");

static const unsigned char sAntiSpellFragranceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/anti_spell_fragrance.huff");
static const unsigned short sAntiSpellFragranceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/anti_spell_fragrance.gbapal");
static const unsigned char sAntiSpellFragranceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/anti_spell_fragrance.lz");

static const unsigned char sAppropriateBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/appropriate.huff");
static const unsigned short sAppropriateBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/appropriate.gbapal");
static const unsigned char sAppropriateMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/appropriate.lz");

static const unsigned char sApprenticeIllusionMagicianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/apprentice_illusion_magician.huff");
static const unsigned short sApprenticeIllusionMagicianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/apprentice_illusion_magician.gbapal");
static const unsigned char sApprenticeIllusionMagicianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/apprentice_illusion_magician.lz");

static const unsigned char sApparationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/apparation.huff");
static const unsigned short sApparationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/apparation.gbapal");
static const unsigned char sApparationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/apparation.lz");

static const unsigned char sAttackGuidanceArmorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/attack_guidance_armor.huff");
static const unsigned short sAttackGuidanceArmorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/attack_guidance_armor.gbapal");
static const unsigned char sAttackGuidanceArmorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/attack_guidance_armor.lz");

static const unsigned char sAttackReflectorUnitBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/attack_reflector_unit.huff");
static const unsigned short sAttackReflectorUnitBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/attack_reflector_unit.gbapal");
static const unsigned char sAttackReflectorUnitMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/attack_reflector_unit.lz");

static const unsigned char sBackupSquadBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/backup_squad.huff");
static const unsigned short sBackupSquadBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/backup_squad.gbapal");
static const unsigned char sBackupSquadMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/backup_squad.lz");

static const unsigned char sArmageddonKnightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/armageddon_knight.huff");
static const unsigned short sArmageddonKnightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/armageddon_knight.gbapal");
static const unsigned char sArmageddonKnightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/armageddon_knight.lz");

static const unsigned char sArmedDragonLv3BigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/armed_dragon_lv3.huff");
static const unsigned short sArmedDragonLv3BigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/armed_dragon_lv3.gbapal");
static const unsigned char sArmedDragonLv3MiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/armed_dragon_lv3.lz");

static const unsigned char sArmedDragonLv5BigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/armed_dragon_lv5.huff");
static const unsigned short sArmedDragonLv5BigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/armed_dragon_lv5.gbapal");
static const unsigned char sArmedDragonLv5MiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/armed_dragon_lv5.lz");

static const unsigned char sArmedDragonLv7BigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/armed_dragon_lv7.huff");
static const unsigned short sArmedDragonLv7BigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/armed_dragon_lv7.gbapal");
static const unsigned char sArmedDragonLv7MiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/armed_dragon_lv7.lz");

static const unsigned char sArmedDragonLv10BigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/armed_dragon_lv10.huff");
static const unsigned short sArmedDragonLv10BigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/armed_dragon_lv10.gbapal");
static const unsigned char sArmedDragonLv10MiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/armed_dragon_lv10.lz");

static const unsigned char sAttackAndReceiveBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/attack_and_receive.huff");
static const unsigned short sAttackAndReceiveBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/attack_and_receive.gbapal");
static const unsigned char sAttackAndReceiveMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/attack_and_receive.lz");

static const unsigned char sBackfireBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/backfire.huff");
static const unsigned short sBackfireBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/backfire.gbapal");
static const unsigned char sBackfireMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/backfire.lz");

static const unsigned char sHamonLordOfStrikingThunderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/hamon_lord_of_striking_thunder.huff");
static const unsigned short sHamonLordOfStrikingThunderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/hamon_lord_of_striking_thunder.gbapal");
static const unsigned char sHamonLordOfStrikingThunderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/hamon_lord_of_striking_thunder.lz");

static const unsigned char sUriaLordOfSearingFlamesBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/uria_lord_of_searing_flames.huff");
static const unsigned short sUriaLordOfSearingFlamesBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/uria_lord_of_searing_flames.gbapal");
static const unsigned char sUriaLordOfSearingFlamesMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/uria_lord_of_searing_flames.lz");

static const unsigned char sRavielLordOfPhantasmsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/raviel_lord_of_phantasms.huff");
static const unsigned short sRavielLordOfPhantasmsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/raviel_lord_of_phantasms.gbapal");
static const unsigned char sRavielLordOfPhantasmsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/raviel_lord_of_phantasms.lz");

static const unsigned char sBerserkerSoulBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/berserker_soul.huff");
static const unsigned short sBerserkerSoulBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/berserker_soul.gbapal");
static const unsigned char sBerserkerSoulMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/berserker_soul.lz");

static const unsigned char sBirdfaceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/birdface.huff");
static const unsigned short sBirdfaceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/birdface.gbapal");
static const unsigned char sBirdfaceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/birdface.lz");

static const unsigned char sBlueEyesAlternativeUltimateDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_alternative_ultimate_dragon.huff");
static const unsigned short sBlueEyesAlternativeUltimateDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_alternative_ultimate_dragon.gbapal");
static const unsigned char sBlueEyesAlternativeUltimateDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_alternative_ultimate_dragon.lz");

static const unsigned char sBreakTheDestinyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/break_the_destiny.huff");
static const unsigned short sBreakTheDestinyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/break_the_destiny.gbapal");
static const unsigned char sBreakTheDestinyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/break_the_destiny.lz");

static const unsigned char sBubbleBlasterBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/bubble_blaster.huff");
static const unsigned short sBubbleBlasterBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/bubble_blaster.gbapal");
static const unsigned char sBubbleBlasterMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/bubble_blaster.lz");

static const unsigned char sBurdenOfTheMightyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/burden_of_the_mighty.huff");
static const unsigned short sBurdenOfTheMightyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/burden_of_the_mighty.gbapal");
static const unsigned char sBurdenOfTheMightyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/burden_of_the_mighty.lz");

static const unsigned char sCallOfTheMummyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/call_of_the_mummy.huff");
static const unsigned short sCallOfTheMummyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/call_of_the_mummy.gbapal");
static const unsigned char sCallOfTheMummyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/call_of_the_mummy.lz");

static const unsigned char sCannonballSpearShellfishBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cannonball_spear_shellfish.huff");
static const unsigned short sCannonballSpearShellfishBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cannonball_spear_shellfish.gbapal");
static const unsigned char sCannonballSpearShellfishMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cannonball_spear_shellfish.lz");

static const unsigned char sCelestialSwordEatosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/celestial_sword_eatos.huff");
static const unsigned short sCelestialSwordEatosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/celestial_sword_eatos.gbapal");
static const unsigned char sCelestialSwordEatosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/celestial_sword_eatos.lz");

static const unsigned char sChaosFormBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chaos_form.huff");
static const unsigned short sChaosFormBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chaos_form.gbapal");
static const unsigned char sChaosFormMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chaos_form.lz");

static const unsigned char sChickenGameBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chicken_game.huff");
static const unsigned short sChickenGameBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chicken_game.gbapal");
static const unsigned char sChickenGameMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chicken_game.lz");

static const unsigned char sChimeratechFortressDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chimeratech_fortress_dragon.huff");
static const unsigned short sChimeratechFortressDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chimeratech_fortress_dragon.gbapal");
static const unsigned char sChimeratechFortressDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chimeratech_fortress_dragon.lz");

static const unsigned char sChimeratechMegafleetDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chimeratech_megafleet_dragon.huff");
static const unsigned short sChimeratechMegafleetDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chimeratech_megafleet_dragon.gbapal");
static const unsigned char sChimeratechMegafleetDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chimeratech_megafleet_dragon.lz");

static const unsigned char sChimeratechRampageDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chimeratech_rampage_dragon.huff");
static const unsigned short sChimeratechRampageDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chimeratech_rampage_dragon.gbapal");
static const unsigned char sChimeratechRampageDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chimeratech_rampage_dragon.lz");

static const unsigned char sClockTowerPrisonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/clock_tower_prison.huff");
static const unsigned short sClockTowerPrisonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/clock_tower_prison.gbapal");
static const unsigned char sClockTowerPrisonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/clock_tower_prison.lz");

static const unsigned char sColdWaveBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cold_wave.huff");
static const unsigned short sColdWaveBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cold_wave.gbapal");
static const unsigned char sColdWaveMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cold_wave.lz");

static const unsigned char sContinuousDestructionPunchBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/continuous_destruction_punch.huff");
static const unsigned short sContinuousDestructionPunchBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/continuous_destruction_punch.gbapal");
static const unsigned char sContinuousDestructionPunchMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/continuous_destruction_punch.lz");

static const unsigned char sCyberEltaninBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cyber_eltanin.huff");
static const unsigned short sCyberEltaninBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cyber_eltanin.gbapal");
static const unsigned char sCyberEltaninMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cyber_eltanin.lz");

static const unsigned char sCyberKirinBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cyber_kirin.huff");
static const unsigned short sCyberKirinBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cyber_kirin.gbapal");
static const unsigned char sCyberKirinMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cyber_kirin.lz");

static const unsigned char sCyberPhoenixBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cyber_phoenix.huff");
static const unsigned short sCyberPhoenixBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cyber_phoenix.gbapal");
static const unsigned char sCyberPhoenixMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cyber_phoenix.lz");

static const unsigned char sCyberValleyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cyber_valley.huff");
static const unsigned short sCyberValleyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cyber_valley.gbapal");
static const unsigned char sCyberValleyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cyber_valley.lz");

static const unsigned char sCyberneticZoneBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cybernetic_zone.huff");
static const unsigned short sCyberneticZoneBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cybernetic_zone.gbapal");
static const unsigned char sCyberneticZoneMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cybernetic_zone.lz");

static const unsigned char sDTacticsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/d_tactics.huff");
static const unsigned short sDTacticsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/d_tactics.gbapal");
static const unsigned char sDTacticsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/d_tactics.lz");

static const unsigned char sDTimeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/d_time.huff");
static const unsigned short sDTimeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/d_time.gbapal");
static const unsigned char sDTimeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/d_time.lz");

static const unsigned char sDamagePolarizerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/damage_polarizer.huff");
static const unsigned short sDamagePolarizerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/damage_polarizer.gbapal");
static const unsigned char sDamagePolarizerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/damage_polarizer.lz");

static const unsigned char sDBurstBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/d_burst.huff");
static const unsigned short sDBurstBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/d_burst.gbapal");
static const unsigned char sDBurstMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/d_burst.lz");

static const unsigned char sDForceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/d_force.huff");
static const unsigned short sDForceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/d_force.gbapal");
static const unsigned char sDForceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/d_force.lz");

static const unsigned char sDarkBladeTheDragonKnightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_blade_the_dragon_knight.huff");
static const unsigned short sDarkBladeTheDragonKnightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_blade_the_dragon_knight.gbapal");
static const unsigned char sDarkBladeTheDragonKnightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_blade_the_dragon_knight.lz");

static const unsigned char sDarkGrepherBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_grepher.huff");
static const unsigned short sDarkGrepherBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_grepher.gbapal");
static const unsigned char sDarkGrepherMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_grepher.lz");

static const unsigned char sDarkMagicianGirlTheDragonKnightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_magician_girl_the_dragon_knight.huff");
static const unsigned short sDarkMagicianGirlTheDragonKnightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_magician_girl_the_dragon_knight.gbapal");
static const unsigned char sDarkMagicianGirlTheDragonKnightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_magician_girl_the_dragon_knight.lz");

static const unsigned char sDarklordNurseReficuleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/darklord_nurse_reficule.huff");
static const unsigned short sDarklordNurseReficuleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/darklord_nurse_reficule.gbapal");
static const unsigned char sDarklordNurseReficuleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/darklord_nurse_reficule.lz");

static const unsigned char sDarknessNeosphereBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/darkness_neosphere.huff");
static const unsigned short sDarknessNeosphereBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/darkness_neosphere.gbapal");
static const unsigned char sDarknessNeosphereMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/darkness_neosphere.lz");

static const unsigned char sDarkCityAtMidnightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_city_at_midnight.huff");
static const unsigned short sDarkCityAtMidnightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_city_at_midnight.gbapal");
static const unsigned char sDarkCityAtMidnightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_city_at_midnight.lz");

static const unsigned char sDarkMagicianTheDragonKnightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_magician_the_dragon_knight.huff");
static const unsigned short sDarkMagicianTheDragonKnightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_magician_the_dragon_knight.gbapal");
static const unsigned char sDarkMagicianTheDragonKnightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_magician_the_dragon_knight.lz");

static const unsigned char sDecoyDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/decoy_dragon.huff");
static const unsigned short sDecoyDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/decoy_dragon.gbapal");
static const unsigned char sDecoyDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/decoy_dragon.lz");

static const unsigned char sDesCounterblowBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/des_counterblow.huff");
static const unsigned short sDesCounterblowBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/des_counterblow.gbapal");
static const unsigned char sDesCounterblowMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/des_counterblow.lz");

static const unsigned char sDespairFromTheDarkBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/despair_from_the_dark.huff");
static const unsigned short sDespairFromTheDarkBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/despair_from_the_dark.gbapal");
static const unsigned char sDespairFromTheDarkMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/despair_from_the_dark.lz");

static const unsigned char sDestinyDrawBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_draw.huff");
static const unsigned short sDestinyDrawBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_draw.gbapal");
static const unsigned char sDestinyDrawMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_draw.lz");

static const unsigned char sDestinyEndDragoonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_end_dragoon.huff");
static const unsigned short sDestinyEndDragoonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_end_dragoon.gbapal");
static const unsigned char sDestinyEndDragoonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_end_dragoon.lz");

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

static const unsigned char sDestinyHeroDarkAngelBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dark_angel.huff");
static const unsigned short sDestinyHeroDarkAngelBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dark_angel.gbapal");
static const unsigned char sDestinyHeroDarkAngelMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dark_angel.lz");

static const unsigned char sDestinyHeroDasherBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dasher.huff");
static const unsigned short sDestinyHeroDasherBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dasher.gbapal");
static const unsigned char sDestinyHeroDasherMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dasher.lz");

static const unsigned char sDestinyHeroDeciderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_decider.huff");
static const unsigned short sDestinyHeroDeciderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_decider.gbapal");
static const unsigned char sDestinyHeroDeciderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_decider.lz");

static const unsigned char sDestinyHeroDefenderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_defender.huff");
static const unsigned short sDestinyHeroDefenderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_defender.gbapal");
static const unsigned char sDestinyHeroDefenderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_defender.lz");

static const unsigned char sDestinyHeroDenierBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_denier.huff");
static const unsigned short sDestinyHeroDenierBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_denier.gbapal");
static const unsigned char sDestinyHeroDenierMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_denier.lz");

static const unsigned char sDestinyHeroDestroyerPhoenixEnforcerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_destroyer_phoenix_enforcer.huff");
static const unsigned short sDestinyHeroDestroyerPhoenixEnforcerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_destroyer_phoenix_enforcer.gbapal");
static const unsigned char sDestinyHeroDestroyerPhoenixEnforcerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_destroyer_phoenix_enforcer.lz");

static const unsigned char sDestinyHeroDiamondDudeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_diamond_dude.huff");
static const unsigned short sDestinyHeroDiamondDudeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_diamond_dude.gbapal");
static const unsigned char sDestinyHeroDiamondDudeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_diamond_dude.lz");

static const unsigned char sDestinyHeroDiskCommanderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_disk_commander.huff");
static const unsigned short sDestinyHeroDiskCommanderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_disk_commander.gbapal");
static const unsigned char sDestinyHeroDiskCommanderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_disk_commander.lz");

static const unsigned char sDestinyHeroDogmaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dogma.huff");
static const unsigned short sDestinyHeroDogmaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dogma.gbapal");
static const unsigned char sDestinyHeroDogmaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dogma.lz");

static const unsigned char sDestinyHeroDominanceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dominance.huff");
static const unsigned short sDestinyHeroDominanceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dominance.gbapal");
static const unsigned char sDestinyHeroDominanceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dominance.lz");

static const unsigned char sDestinyHeroDoomLordBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_doom_lord.huff");
static const unsigned short sDestinyHeroDoomLordBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_doom_lord.gbapal");
static const unsigned char sDestinyHeroDoomLordMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_doom_lord.lz");

static const unsigned char sDestinyHeroDoubleDudeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_double_dude.huff");
static const unsigned short sDestinyHeroDoubleDudeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_double_dude.gbapal");
static const unsigned char sDestinyHeroDoubleDudeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_double_dude.lz");

static const unsigned char sDestinyHeroDrawhandBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_drawhand.huff");
static const unsigned short sDestinyHeroDrawhandBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_drawhand.gbapal");
static const unsigned char sDestinyHeroDrawhandMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_drawhand.lz");

static const unsigned char sDestinyHeroDreadServantBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dread_servant.huff");
static const unsigned short sDestinyHeroDreadServantBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dread_servant.gbapal");
static const unsigned char sDestinyHeroDreadServantMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dread_servant.lz");

static const unsigned char sDestinyHeroDreadmasterBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dreadmaster.huff");
static const unsigned short sDestinyHeroDreadmasterBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dreadmaster.gbapal");
static const unsigned char sDestinyHeroDreadmasterMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dreadmaster.lz");

static const unsigned char sDestinyHeroDoomOverlordBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_doom_overlord.huff");
static const unsigned short sDestinyHeroDoomOverlordBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_doom_overlord.gbapal");
static const unsigned char sDestinyHeroDoomOverlordMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_doom_overlord.lz");

static const unsigned char sDestinyHeroDreadnoughtMasterBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dreadnought_master.huff");
static const unsigned short sDestinyHeroDreadnoughtMasterBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dreadnought_master.gbapal");
static const unsigned char sDestinyHeroDreadnoughtMasterMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dreadnought_master.lz");

static const unsigned char sDestinyHeroDreadnoughtServantBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dreadnought_servant.huff");
static const unsigned short sDestinyHeroDreadnoughtServantBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dreadnought_servant.gbapal");
static const unsigned char sDestinyHeroDreadnoughtServantMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dreadnought_servant.lz");

static const unsigned char sDestinyHeroDreamerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dreamer.huff");
static const unsigned short sDestinyHeroDreamerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dreamer.gbapal");
static const unsigned char sDestinyHeroDreamerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dreamer.lz");

static const unsigned char sDestinyHeroDrilldarkBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_drilldark.huff");
static const unsigned short sDestinyHeroDrilldarkBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_drilldark.gbapal");
static const unsigned char sDestinyHeroDrilldarkMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_drilldark.lz");

static const unsigned char sDestinyHeroDunkerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dunker.huff");
static const unsigned short sDestinyHeroDunkerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dunker.gbapal");
static const unsigned char sDestinyHeroDunkerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dunker.lz");

static const unsigned char sDestinyHeroDynatagBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dynatag.huff");
static const unsigned short sDestinyHeroDynatagBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dynatag.gbapal");
static const unsigned char sDestinyHeroDynatagMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dynatag.lz");

static const unsigned char sDestinyHeroDystopiaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dystopia.huff");
static const unsigned short sDestinyHeroDystopiaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dystopia.gbapal");
static const unsigned char sDestinyHeroDystopiaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dystopia.lz");

static const unsigned char sDestinyHeroFearMongerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_fear_monger.huff");
static const unsigned short sDestinyHeroFearMongerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_fear_monger.gbapal");
static const unsigned char sDestinyHeroFearMongerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_fear_monger.lz");

static const unsigned char sDestinyHeroMaliciousBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_malicious.huff");
static const unsigned short sDestinyHeroMaliciousBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_malicious.gbapal");
static const unsigned char sDestinyHeroMaliciousMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_malicious.lz");

static const unsigned char sDestinyHeroPlasmaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_plasma.huff");
static const unsigned short sDestinyHeroPlasmaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_plasma.gbapal");
static const unsigned char sDestinyHeroPlasmaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_plasma.lz");

static const unsigned char sDifferentDimensionCapsuleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/different_dimension_capsule.huff");
static const unsigned short sDifferentDimensionCapsuleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/different_dimension_capsule.gbapal");
static const unsigned char sDifferentDimensionCapsuleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/different_dimension_capsule.lz");

static const unsigned char sDestinyHeroDusktopiaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_dusktopia.huff");
static const unsigned short sDestinyHeroDusktopiaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_dusktopia.gbapal");
static const unsigned char sDestinyHeroDusktopiaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_dusktopia.lz");

static const unsigned char sDimensionFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dimension_fusion.huff");
static const unsigned short sDimensionFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dimension_fusion.gbapal");
static const unsigned char sDimensionFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dimension_fusion.lz");

static const unsigned char sDivineSerpentGehBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/divine_serpent_geh.huff");
static const unsigned short sDivineSerpentGehBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/divine_serpent_geh.gbapal");
static const unsigned char sDivineSerpentGehMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/divine_serpent_geh.lz");

static const unsigned char sDonZaloogBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/don_zaloog.huff");
static const unsigned short sDonZaloogBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/don_zaloog.gbapal");
static const unsigned char sDonZaloogMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/don_zaloog.lz");

static const unsigned char sDoubleSpellBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/double_spell.huff");
static const unsigned short sDoubleSpellBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/double_spell.gbapal");
static const unsigned char sDoubleSpellMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/double_spell.lz");

static const unsigned char sDragonSRageBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dragon_s_rage.huff");
static const unsigned short sDragonSRageBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dragon_s_rage.gbapal");
static const unsigned char sDragonSRageMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dragon_s_rage.lz");

static const unsigned char sDestinyHeroDestroyDogmaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destiny_hero_destroy_dogma.huff");
static const unsigned short sDestinyHeroDestroyDogmaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destiny_hero_destroy_dogma.gbapal");
static const unsigned char sDestinyHeroDestroyDogmaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destiny_hero_destroy_dogma.lz");

static const unsigned char sDoctorDBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/doctor_d.huff");
static const unsigned short sDoctorDBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/doctor_d.gbapal");
static const unsigned char sDoctorDMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/doctor_d.lz");

static const unsigned char sDoomVirusDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/doom_virus_dragon.huff");
static const unsigned short sDoomVirusDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/doom_virus_dragon.gbapal");
static const unsigned char sDoomVirusDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/doom_virus_dragon.lz");

static const unsigned char sDoppelgangerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/doppelganger.huff");
static const unsigned short sDoppelgangerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/doppelganger.gbapal");
static const unsigned char sDoppelgangerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/doppelganger.lz");

static const unsigned char sEgyptianGodSlimeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/egyptian_god_slime.huff");
static const unsigned short sEgyptianGodSlimeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/egyptian_god_slime.gbapal");
static const unsigned char sEgyptianGodSlimeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/egyptian_god_slime.lz");

static const unsigned char sElementalHeroNeosKlugerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_neos_kluger.huff");
static const unsigned short sElementalHeroNeosKlugerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_neos_kluger.gbapal");
static const unsigned char sElementalHeroNeosKlugerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_neos_kluger.lz");

static const unsigned char sEmergencyProvisionsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/emergency_provisions.huff");
static const unsigned short sEmergencyProvisionsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/emergency_provisions.gbapal");
static const unsigned char sEmergencyProvisionsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/emergency_provisions.lz");

static const unsigned char sExodiusTheUltimateForbiddenLordBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/exodius_the_ultimate_forbidden_lord.huff");
static const unsigned short sExodiusTheUltimateForbiddenLordBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/exodius_the_ultimate_forbidden_lord.gbapal");
static const unsigned char sExodiusTheUltimateForbiddenLordMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/exodius_the_ultimate_forbidden_lord.lz");

static const unsigned char sFatalAbacusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/fatal_abacus.huff");
static const unsigned short sFatalAbacusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/fatal_abacus.gbapal");
static const unsigned char sFatalAbacusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/fatal_abacus.lz");

static const unsigned char sFelgrandDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/felgrand_dragon.huff");
static const unsigned short sFelgrandDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/felgrand_dragon.gbapal");
static const unsigned char sFelgrandDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/felgrand_dragon.lz");

static const unsigned char sFiresOfDoomsdayBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/fires_of_doomsday.huff");
static const unsigned short sFiresOfDoomsdayBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/fires_of_doomsday.gbapal");
static const unsigned char sFiresOfDoomsdayMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/fires_of_doomsday.lz");

static const unsigned char sForcedRequisitionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/forced_requisition.huff");
static const unsigned short sForcedRequisitionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/forced_requisition.gbapal");
static const unsigned char sForcedRequisitionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/forced_requisition.lz");

static const unsigned char sDrainTimeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/drain_time.huff");
static const unsigned short sDrainTimeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/drain_time.gbapal");
static const unsigned char sDrainTimeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/drain_time.lz");

static const unsigned char sFieldsSanctuaryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/fields_sanctuary.huff");
static const unsigned short sFieldsSanctuaryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/fields_sanctuary.gbapal");
static const unsigned char sFieldsSanctuaryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/fields_sanctuary.lz");

static const unsigned char sFusionDestinyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/fusion_destiny.huff");
static const unsigned short sFusionDestinyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/fusion_destiny.gbapal");
static const unsigned char sFusionDestinyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/fusion_destiny.lz");

static const unsigned char sFusionGateBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/fusion_gate.huff");
static const unsigned short sFusionGateBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/fusion_gate.gbapal");
static const unsigned char sFusionGateMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/fusion_gate.lz");

static const unsigned char sGateGuardiansCombinedBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gate_guardians_combined.huff");
static const unsigned short sGateGuardiansCombinedBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gate_guardians_combined.gbapal");
static const unsigned char sGateGuardiansCombinedMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gate_guardians_combined.lz");

static const unsigned char sGiftCardBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gift_card.huff");
static const unsigned short sGiftCardBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gift_card.gbapal");
static const unsigned char sGiftCardMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gift_card.lz");

static const unsigned char sGoddessBowBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/goddess_bow.huff");
static const unsigned short sGoddessBowBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/goddess_bow.gbapal");
static const unsigned char sGoddessBowMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/goddess_bow.lz");

static const unsigned char sGorzTheEmissaryOfDarknessBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gorz_the_emissary_of_darkness.huff");
static const unsigned short sGorzTheEmissaryOfDarknessBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gorz_the_emissary_of_darkness.gbapal");
static const unsigned char sGorzTheEmissaryOfDarknessMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gorz_the_emissary_of_darkness.lz");

static const unsigned char sGranmargTheRockMonarchBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/granmarg_the_rock_monarch.huff");
static const unsigned short sGranmargTheRockMonarchBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/granmarg_the_rock_monarch.gbapal");
static const unsigned char sGranmargTheRockMonarchMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/granmarg_the_rock_monarch.lz");

static const unsigned char sGreenGadgetBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/green_gadget.huff");
static const unsigned short sGreenGadgetBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/green_gadget.gbapal");
static const unsigned char sGreenGadgetMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/green_gadget.lz");

static const unsigned char sGroundCollapseBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ground_collapse.huff");
static const unsigned short sGroundCollapseBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ground_collapse.gbapal");
static const unsigned char sGroundCollapseMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ground_collapse.lz");

static const unsigned char sGuardianDreadscytheBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/guardian_dreadscythe.huff");
static const unsigned short sGuardianDreadscytheBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/guardian_dreadscythe.gbapal");
static const unsigned char sGuardianDreadscytheMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/guardian_dreadscythe.lz");

static const unsigned char sHarpieLadyPhoenixFormationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/harpie_lady_phoenix_formation.huff");
static const unsigned short sHarpieLadyPhoenixFormationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/harpie_lady_phoenix_formation.gbapal");
static const unsigned char sHarpieLadyPhoenixFormationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/harpie_lady_phoenix_formation.lz");

static const unsigned char sHeroFlashBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/hero_flash.huff");
static const unsigned short sHeroFlashBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/hero_flash.gbapal");
static const unsigned char sHeroFlashMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/hero_flash.lz");

static const unsigned char sInsectImitationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/insect_imitation.huff");
static const unsigned short sInsectImitationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/insect_imitation.gbapal");
static const unsigned char sInsectImitationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/insect_imitation.lz");

static const unsigned char sInstantFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/instant_fusion.huff");
static const unsigned short sInstantFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/instant_fusion.gbapal");
static const unsigned char sInstantFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/instant_fusion.lz");

static const unsigned char sGuardianEatosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/guardian_eatos.huff");
static const unsigned short sGuardianEatosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/guardian_eatos.gbapal");
static const unsigned char sGuardianEatosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/guardian_eatos.lz");

static const unsigned char sHeraldOfCreationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/herald_of_creation.huff");
static const unsigned short sHeraldOfCreationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/herald_of_creation.gbapal");
static const unsigned char sHeraldOfCreationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/herald_of_creation.lz");

static const unsigned char sHolactieTheCreatorOfLightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/holactie_the_creator_of_light.huff");
static const unsigned short sHolactieTheCreatorOfLightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/holactie_the_creator_of_light.gbapal");
static const unsigned char sHolactieTheCreatorOfLightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/holactie_the_creator_of_light.lz");

static const unsigned char sHorusTheBlackFlameDragonLv8BigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/horus_the_black_flame_dragon_lv8.huff");
static const unsigned short sHorusTheBlackFlameDragonLv8BigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/horus_the_black_flame_dragon_lv8.gbapal");
static const unsigned char sHorusTheBlackFlameDragonLv8MiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/horus_the_black_flame_dragon_lv8.lz");

static const unsigned char sHorusTheBlackFlameDragonLv4BigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/horus_the_black_flame_dragon_lv4.huff");
static const unsigned short sHorusTheBlackFlameDragonLv4BigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/horus_the_black_flame_dragon_lv4.gbapal");
static const unsigned char sHorusTheBlackFlameDragonLv4MiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/horus_the_black_flame_dragon_lv4.lz");

static const unsigned char sHorusTheBlackFlameDragonLv6BigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/horus_the_black_flame_dragon_lv6.huff");
static const unsigned short sHorusTheBlackFlameDragonLv6BigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/horus_the_black_flame_dragon_lv6.gbapal");
static const unsigned char sHorusTheBlackFlameDragonLv6MiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/horus_the_black_flame_dragon_lv6.lz");

static const unsigned char sJowgenTheSpiritualistBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/jowgen_the_spiritualist.huff");
static const unsigned short sJowgenTheSpiritualistBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/jowgen_the_spiritualist.gbapal");
static const unsigned char sJowgenTheSpiritualistMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/jowgen_the_spiritualist.lz");

static const unsigned char sJudgmentDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/judgment_dragon.huff");
static const unsigned short sJudgmentDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/judgment_dragon.gbapal");
static const unsigned char sJudgmentDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/judgment_dragon.lz");

static const unsigned char sKingDragunBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/king_dragun.huff");
static const unsigned short sKingDragunBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/king_dragun.gbapal");
static const unsigned char sKingDragunMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/king_dragun.lz");

static const unsigned char sKingOfTheSwampBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/king_of_the_swamp.huff");
static const unsigned short sKingOfTheSwampBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/king_of_the_swamp.gbapal");
static const unsigned char sKingOfTheSwampMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/king_of_the_swamp.lz");

static const unsigned char sKurazTheLightMonarchBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/kuraz_the_light_monarch.huff");
static const unsigned short sKurazTheLightMonarchBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/kuraz_the_light_monarch.gbapal");
static const unsigned char sKurazTheLightMonarchMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/kuraz_the_light_monarch.lz");

static const unsigned char sKuribanditBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/kuribandit.huff");
static const unsigned short sKuribanditBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/kuribandit.gbapal");
static const unsigned char sKuribanditMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/kuribandit.lz");

static const unsigned char sLastTurnBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/last_turn.huff");
static const unsigned short sLastTurnBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/last_turn.gbapal");
static const unsigned char sLastTurnMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/last_turn.lz");

static const unsigned char sLegendOfHeartBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/legend_of_heart.huff");
static const unsigned short sLegendOfHeartBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/legend_of_heart.gbapal");
static const unsigned char sLegendOfHeartMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/legend_of_heart.lz");

static const unsigned char sLegendaryFlameLordBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/legendary_flame_lord.huff");
static const unsigned short sLegendaryFlameLordBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/legendary_flame_lord.gbapal");
static const unsigned char sLegendaryFlameLordMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/legendary_flame_lord.lz");

static const unsigned char sKingTigerWanghuBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/king_tiger_wanghu.huff");
static const unsigned short sKingTigerWanghuBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/king_tiger_wanghu.gbapal");
static const unsigned char sKingTigerWanghuMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/king_tiger_wanghu.lz");

static const unsigned char sLegendaryKnightCritiasBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/legendary_knight_critias.huff");
static const unsigned short sLegendaryKnightCritiasBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/legendary_knight_critias.gbapal");
static const unsigned char sLegendaryKnightCritiasMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/legendary_knight_critias.lz");

static const unsigned char sLegendaryKnightHermosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/legendary_knight_hermos.huff");
static const unsigned short sLegendaryKnightHermosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/legendary_knight_hermos.gbapal");
static const unsigned char sLegendaryKnightHermosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/legendary_knight_hermos.lz");

static const unsigned char sLegendaryKnightTimaeusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/legendary_knight_timaeus.huff");
static const unsigned short sLegendaryKnightTimaeusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/legendary_knight_timaeus.gbapal");
static const unsigned char sLegendaryKnightTimaeusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/legendary_knight_timaeus.lz");

static const unsigned char sLekungaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lekunga.huff");
static const unsigned short sLekungaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lekunga.gbapal");
static const unsigned char sLekungaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lekunga.lz");

static const unsigned char sLightAndDarknessDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/light_and_darkness_dragon.huff");
static const unsigned short sLightAndDarknessDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/light_and_darkness_dragon.gbapal");
static const unsigned char sLightAndDarknessDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/light_and_darkness_dragon.lz");

static const unsigned char sLordOfTheRedBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lord_of_the_red.huff");
static const unsigned short sLordOfTheRedBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lord_of_the_red.gbapal");
static const unsigned char sLordOfTheRedMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lord_of_the_red.lz");

static const unsigned char sMaAtBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ma_at.huff");
static const unsigned short sMaAtBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ma_at.gbapal");
static const unsigned char sMaAtMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ma_at.lz");

static const unsigned char sMagicalDimensionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magical_dimension.huff");
static const unsigned short sMagicalDimensionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magical_dimension.gbapal");
static const unsigned char sMagicalDimensionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magical_dimension.lz");

static const unsigned char sMagicalHatsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magical_hats.huff");
static const unsigned short sMagicalHatsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magical_hats.gbapal");
static const unsigned char sMagicalHatsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magical_hats.lz");

static const unsigned char sMagicalPlantMandragolaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magical_plant_mandragola.huff");
static const unsigned short sMagicalPlantMandragolaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magical_plant_mandragola.gbapal");
static const unsigned char sMagicalPlantMandragolaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magical_plant_mandragola.lz");

static const unsigned char sMagicalScientistBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magical_scientist.huff");
static const unsigned short sMagicalScientistBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magical_scientist.gbapal");
static const unsigned char sMagicalScientistMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magical_scientist.lz");

static const unsigned char sMagicalStoneExcavationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magical_stone_excavation.huff");
static const unsigned short sMagicalStoneExcavationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magical_stone_excavation.gbapal");
static const unsigned char sMagicalStoneExcavationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magical_stone_excavation.lz");

static const unsigned char sMajesticMechGoryuBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/majestic_mech_goryu.huff");
static const unsigned short sMajesticMechGoryuBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/majestic_mech_goryu.gbapal");
static const unsigned char sMajesticMechGoryuMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/majestic_mech_goryu.lz");

static const unsigned char sManjuOfTheTenThousandHandsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/manju_of_the_ten_thousand_hands.huff");
static const unsigned short sManjuOfTheTenThousandHandsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/manju_of_the_ten_thousand_hands.gbapal");
static const unsigned char sManjuOfTheTenThousandHandsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/manju_of_the_ten_thousand_hands.lz");

static const unsigned char sMarshmallonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/marshmallon.huff");
static const unsigned short sMarshmallonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/marshmallon.gbapal");
static const unsigned char sMarshmallonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/marshmallon.lz");

static const unsigned char sMaskOfDispelBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mask_of_dispel.huff");
static const unsigned short sMaskOfDispelBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mask_of_dispel.gbapal");
static const unsigned char sMaskOfDispelMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mask_of_dispel.lz");

static const unsigned char sMasterPeaceTheTrueDracoslayingKingBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/master_peace_the_true_dracoslaying_king.huff");
static const unsigned short sMasterPeaceTheTrueDracoslayingKingBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/master_peace_the_true_dracoslaying_king.gbapal");
static const unsigned char sMasterPeaceTheTrueDracoslayingKingMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/master_peace_the_true_dracoslaying_king.lz");

static const unsigned char sMaskOfTheAccursedBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mask_of_the_accursed.huff");
static const unsigned short sMaskOfTheAccursedBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mask_of_the_accursed.gbapal");
static const unsigned char sMaskOfTheAccursedMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mask_of_the_accursed.lz");

static const unsigned char sMausoleumOfTheEmperorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mausoleum_of_the_emperor.huff");
static const unsigned short sMausoleumOfTheEmperorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mausoleum_of_the_emperor.gbapal");
static const unsigned char sMausoleumOfTheEmperorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mausoleum_of_the_emperor.lz");

static const unsigned char sMazeraDevilleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mazera_deville.huff");
static const unsigned short sMazeraDevilleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mazera_deville.gbapal");
static const unsigned char sMazeraDevilleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mazera_deville.lz");

static const unsigned char sMetamorphosisBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/metamorphosis.huff");
static const unsigned short sMetamorphosisBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/metamorphosis.gbapal");
static const unsigned char sMetamorphosisMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/metamorphosis.lz");

static const unsigned char sMeteorainBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/meteorain.huff");
static const unsigned short sMeteorainBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/meteorain.gbapal");
static const unsigned char sMeteorainMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/meteorain.lz");

static const unsigned char sMirageOfNightmareBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mirage_of_nightmare.huff");
static const unsigned short sMirageOfNightmareBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mirage_of_nightmare.gbapal");
static const unsigned char sMirageOfNightmareMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mirage_of_nightmare.lz");

static const unsigned char sMirrorForceDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mirror_force_dragon.huff");
static const unsigned short sMirrorForceDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mirror_force_dragon.gbapal");
static const unsigned char sMirrorForceDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mirror_force_dragon.lz");

static const unsigned char sMoltenZombieBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/molten_zombie.huff");
static const unsigned short sMoltenZombieBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/molten_zombie.gbapal");
static const unsigned char sMoltenZombieMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/molten_zombie.lz");

static const unsigned char sMonsterGateBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/monster_gate.huff");
static const unsigned short sMonsterGateBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/monster_gate.gbapal");
static const unsigned char sMonsterGateMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/monster_gate.lz");

static const unsigned char sMonsterRecoveryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/monster_recovery.huff");
static const unsigned short sMonsterRecoveryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/monster_recovery.gbapal");
static const unsigned char sMonsterRecoveryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/monster_recovery.lz");

static const unsigned char sMoraleBoostBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/morale_boost.huff");
static const unsigned short sMoraleBoostBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/morale_boost.gbapal");
static const unsigned char sMoraleBoostMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/morale_boost.lz");

static const unsigned char sMucusYolkBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mucus_yolk.huff");
static const unsigned short sMucusYolkBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mucus_yolk.gbapal");
static const unsigned char sMucusYolkMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mucus_yolk.lz");

static const unsigned char sMystikWokBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mystik_wok.huff");
static const unsigned short sMystikWokBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mystik_wok.gbapal");
static const unsigned char sMystikWokMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mystik_wok.lz");

static const unsigned char sNecrovalleyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/necrovalley.huff");
static const unsigned short sNecrovalleyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/necrovalley.gbapal");
static const unsigned char sNecrovalleyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/necrovalley.lz");

static const unsigned char sNeedleWallBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/needle_wall.huff");
static const unsigned short sNeedleWallBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/needle_wall.gbapal");
static const unsigned char sNeedleWallMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/needle_wall.lz");

static const unsigned char sNeoBlueEyesUltimateDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_blue_eyes_ultimate_dragon.huff");
static const unsigned short sNeoBlueEyesUltimateDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_blue_eyes_ultimate_dragon.gbapal");
static const unsigned char sNeoBlueEyesUltimateDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_blue_eyes_ultimate_dragon.lz");

static const unsigned char sNeosWisemanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neos_wiseman.huff");
static const unsigned short sNeosWisemanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neos_wiseman.gbapal");
static const unsigned char sNeosWisemanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neos_wiseman.lz");

static const unsigned char sNibiruThePrimalBeingBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/nibiru_the_primal_being.huff");
static const unsigned short sNibiruThePrimalBeingBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/nibiru_the_primal_being.gbapal");
static const unsigned char sNibiruThePrimalBeingMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/nibiru_the_primal_being.lz");

static const unsigned char sNuminousHealerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/numinous_healer.huff");
static const unsigned short sNuminousHealerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/numinous_healer.gbapal");
static const unsigned char sNuminousHealerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/numinous_healer.lz");

static const unsigned char sOjamaKingBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ojama_king.huff");
static const unsigned short sOjamaKingBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ojama_king.gbapal");
static const unsigned char sOjamaKingMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ojama_king.lz");

static const unsigned char sOrichalcosShunorosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/orichalcos_shunoros.huff");
static const unsigned short sOrichalcosShunorosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/orichalcos_shunoros.gbapal");
static const unsigned char sOrichalcosShunorosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/orichalcos_shunoros.lz");

static const unsigned char sOverDestinyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/over_destiny.huff");
static const unsigned short sOverDestinyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/over_destiny.gbapal");
static const unsigned char sOverDestinyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/over_destiny.lz");

static const unsigned char sPainfulChoiceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/painful_choice.huff");
static const unsigned short sPainfulChoiceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/painful_choice.gbapal");
static const unsigned char sPainfulChoiceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/painful_choice.lz");

static const unsigned char sPandemoniumBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/pandemonium.huff");
static const unsigned short sPandemoniumBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/pandemonium.gbapal");
static const unsigned char sPandemoniumMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/pandemonium.lz");

static const unsigned char sParallelWorldFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/parallel_world_fusion.huff");
static const unsigned short sParallelWorldFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/parallel_world_fusion.gbapal");
static const unsigned char sParallelWorldFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/parallel_world_fusion.lz");

static const unsigned char sPhotonGeneratorUnitBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/photon_generator_unit.huff");
static const unsigned short sPhotonGeneratorUnitBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/photon_generator_unit.gbapal");
static const unsigned char sPhotonGeneratorUnitMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/photon_generator_unit.lz");

static const unsigned char sPoisonOfTheOldManBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/poison_of_the_old_man.huff");
static const unsigned short sPoisonOfTheOldManBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/poison_of_the_old_man.gbapal");
static const unsigned char sPoisonOfTheOldManMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/poison_of_the_old_man.lz");

static const unsigned char sProtectorOfTheSanctuaryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/protector_of_the_sanctuary.huff");
static const unsigned short sProtectorOfTheSanctuaryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/protector_of_the_sanctuary.gbapal");
static const unsigned char sProtectorOfTheSanctuaryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/protector_of_the_sanctuary.lz");

static const unsigned char sQuintetMagicianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/quintet_magician.huff");
static const unsigned short sQuintetMagicianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/quintet_magician.gbapal");
static const unsigned char sQuintetMagicianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/quintet_magician.lz");

static const unsigned char sRaigekiBreakBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/raigeki_break.huff");
static const unsigned short sRaigekiBreakBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/raigeki_break.gbapal");
static const unsigned char sRaigekiBreakMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/raigeki_break.lz");

static const unsigned char sProphecyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/prophecy.huff");
static const unsigned short sProphecyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/prophecy.gbapal");
static const unsigned char sProphecyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/prophecy.lz");

static const unsigned char sReaperScytheDreadscytheBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reaper_scythe_dreadscythe.huff");
static const unsigned short sReaperScytheDreadscytheBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reaper_scythe_dreadscythe.gbapal");
static const unsigned char sReaperScytheDreadscytheMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reaper_scythe_dreadscythe.lz");

static const unsigned char sRedEyesBlackDragonSwordBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/red_eyes_black_dragon_sword.huff");
static const unsigned short sRedEyesBlackDragonSwordBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/red_eyes_black_dragon_sword.gbapal");
static const unsigned char sRedEyesBlackDragonSwordMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/red_eyes_black_dragon_sword.lz");

static const unsigned char sRedEyesDarkDragoonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/red_eyes_dark_dragoon.huff");
static const unsigned short sRedEyesDarkDragoonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/red_eyes_dark_dragoon.gbapal");
static const unsigned char sRedEyesDarkDragoonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/red_eyes_dark_dragoon.lz");

static const unsigned char sRedEyesDarknessMetalDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/red_eyes_darkness_metal_dragon.huff");
static const unsigned short sRedEyesDarknessMetalDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/red_eyes_darkness_metal_dragon.gbapal");
static const unsigned char sRedEyesDarknessMetalDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/red_eyes_darkness_metal_dragon.lz");

static const unsigned char sRedEyesTransmigrationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/red_eyes_transmigration.huff");
static const unsigned short sRedEyesTransmigrationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/red_eyes_transmigration.gbapal");
static const unsigned char sRedEyesTransmigrationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/red_eyes_transmigration.lz");

static const unsigned char sRedGadgetBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/red_gadget.huff");
static const unsigned short sRedGadgetBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/red_gadget.gbapal");
static const unsigned char sRedGadgetMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/red_gadget.lz");

static const unsigned char sRelaySoulBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/relay_soul.huff");
static const unsigned short sRelaySoulBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/relay_soul.gbapal");
static const unsigned char sRelaySoulMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/relay_soul.lz");

static const unsigned char sReverseOfReverseBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reverse_of_reverse.huff");
static const unsigned short sReverseOfReverseBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reverse_of_reverse.gbapal");
static const unsigned char sReverseOfReverseMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reverse_of_reverse.lz");

static const unsigned char sRocketHermosCannonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/rocket_hermos_cannon.huff");
static const unsigned short sRocketHermosCannonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/rocket_hermos_cannon.gbapal");
static const unsigned char sRocketHermosCannonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/rocket_hermos_cannon.lz");

static const unsigned char sRopeOfLifeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/rope_of_life.huff");
static const unsigned short sRopeOfLifeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/rope_of_life.gbapal");
static const unsigned char sRopeOfLifeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/rope_of_life.lz");

static const unsigned char sRoyalMagicalLibraryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/royal_magical_library.huff");
static const unsigned short sRoyalMagicalLibraryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/royal_magical_library.gbapal");
static const unsigned char sRoyalMagicalLibraryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/royal_magical_library.lz");

static const unsigned char sScapegoatBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/scapegoat.huff");
static const unsigned short sScapegoatBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/scapegoat.gbapal");
static const unsigned char sScapegoatMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/scapegoat.lz");

static const unsigned char sSecondCoinTossBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/second_coin_toss.huff");
static const unsigned short sSecondCoinTossBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/second_coin_toss.gbapal");
static const unsigned char sSecondCoinTossMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/second_coin_toss.lz");

static const unsigned char sSecretVillageOfTheSpellcastersBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/secret_village_of_the_spellcasters.huff");
static const unsigned short sSecretVillageOfTheSpellcastersBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/secret_village_of_the_spellcasters.gbapal");
static const unsigned char sSecretVillageOfTheSpellcastersMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/secret_village_of_the_spellcasters.lz");

static const unsigned char sShareThePainBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/share_the_pain.huff");
static const unsigned short sShareThePainBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/share_the_pain.gbapal");
static const unsigned char sShareThePainMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/share_the_pain.lz");

static const unsigned char sSixthSenseBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/sixth_sense.huff");
static const unsigned short sSixthSenseBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/sixth_sense.gbapal");
static const unsigned char sSixthSenseMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/sixth_sense.lz");

static const unsigned char sSkilledDarkMagicianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/skilled_dark_magician.huff");
static const unsigned short sSkilledDarkMagicianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/skilled_dark_magician.gbapal");
static const unsigned char sSkilledDarkMagicianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/skilled_dark_magician.lz");

static const unsigned char sSkilledWhiteMagicianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/skilled_white_magician.huff");
static const unsigned short sSkilledWhiteMagicianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/skilled_white_magician.gbapal");
static const unsigned char sSkilledWhiteMagicianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/skilled_white_magician.lz");

static const unsigned char sSolemnJudgmentBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/solemn_judgment.huff");
static const unsigned short sSolemnJudgmentBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/solemn_judgment.gbapal");
static const unsigned char sSolemnJudgmentMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/solemn_judgment.lz");

static const unsigned char sSparkBlasterBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/spark_blaster.huff");
static const unsigned short sSparkBlasterBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/spark_blaster.gbapal");
static const unsigned char sSparkBlasterMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/spark_blaster.lz");

static const unsigned char sSkyscraper2HeroCityBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/skyscraper_2_hero_city.huff");
static const unsigned short sSkyscraper2HeroCityBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/skyscraper_2_hero_city.gbapal");
static const unsigned char sSkyscraper2HeroCityMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/skyscraper_2_hero_city.lz");

static const unsigned char sSpellAbsorptionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/spell_absorption.huff");
static const unsigned short sSpellAbsorptionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/spell_absorption.gbapal");
static const unsigned char sSpellAbsorptionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/spell_absorption.lz");

static const unsigned char sSphinxTeleiaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/sphinx_teleia.huff");
static const unsigned short sSphinxTeleiaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/sphinx_teleia.gbapal");
static const unsigned char sSphinxTeleiaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/sphinx_teleia.lz");

static const unsigned char sStatueOfTheWickedBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/statue_of_the_wicked.huff");
static const unsigned short sStatueOfTheWickedBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/statue_of_the_wicked.gbapal");
static const unsigned char sStatueOfTheWickedMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/statue_of_the_wicked.lz");

static const unsigned char sStaunchDefenderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/staunch_defender.huff");
static const unsigned short sStaunchDefenderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/staunch_defender.gbapal");
static const unsigned char sStaunchDefenderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/staunch_defender.lz");

static const unsigned char sStrayLambsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/stray_lambs.huff");
static const unsigned short sStrayLambsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/stray_lambs.gbapal");
static const unsigned char sStrayLambsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/stray_lambs.lz");

static const unsigned char sStrongholdTheMovingFortressBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/stronghold_the_moving_fortress.huff");
static const unsigned short sStrongholdTheMovingFortressBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/stronghold_the_moving_fortress.gbapal");
static const unsigned char sStrongholdTheMovingFortressMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/stronghold_the_moving_fortress.lz");

static const unsigned char sSummonerMonkBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/summoner_monk.huff");
static const unsigned short sSummonerMonkBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/summoner_monk.gbapal");
static const unsigned char sSummonerMonkMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/summoner_monk.lz");

static const unsigned char sSummonerOfIllusionsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/summoner_of_illusions.huff");
static const unsigned short sSummonerOfIllusionsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/summoner_of_illusions.gbapal");
static const unsigned char sSummonerOfIllusionsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/summoner_of_illusions.lz");

static const unsigned char sSuperPolymerizationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/super_polymerization.huff");
static const unsigned short sSuperPolymerizationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/super_polymerization.gbapal");
static const unsigned char sSuperPolymerizationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/super_polymerization.lz");

static const unsigned char sTerraformingBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/terraforming.huff");
static const unsigned short sTerraformingBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/terraforming.gbapal");
static const unsigned char sTerraformingMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/terraforming.lz");

static const unsigned char sTheAForcesBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_a_forces.huff");
static const unsigned short sTheAForcesBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_a_forces.gbapal");
static const unsigned char sTheAForcesMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_a_forces.lz");

static const unsigned char sTheAgentOfJudgmentSaturnBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_agent_of_judgment_saturn.huff");
static const unsigned short sTheAgentOfJudgmentSaturnBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_agent_of_judgment_saturn.gbapal");
static const unsigned char sTheAgentOfJudgmentSaturnMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_agent_of_judgment_saturn.lz");

static const unsigned char sTheAgentOfWisdomMercuryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_agent_of_wisdom_mercury.huff");
static const unsigned short sTheAgentOfWisdomMercuryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_agent_of_wisdom_mercury.gbapal");
static const unsigned char sTheAgentOfWisdomMercuryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_agent_of_wisdom_mercury.lz");

static const unsigned char sTheClawOfHermosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_claw_of_hermos.huff");
static const unsigned short sTheClawOfHermosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_claw_of_hermos.gbapal");
static const unsigned char sTheClawOfHermosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_claw_of_hermos.lz");

static const unsigned char sTheCreatorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_creator.huff");
static const unsigned short sTheCreatorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_creator.gbapal");
static const unsigned char sTheCreatorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_creator.lz");

static const unsigned char sTheCreatorIncarnateBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_creator_incarnate.huff");
static const unsigned short sTheCreatorIncarnateBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_creator_incarnate.gbapal");
static const unsigned char sTheCreatorIncarnateMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_creator_incarnate.lz");

static const unsigned char sTheEyeOfTimaeusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_eye_of_timaeus.huff");
static const unsigned short sTheEyeOfTimaeusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_eye_of_timaeus.gbapal");
static const unsigned char sTheEyeOfTimaeusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_eye_of_timaeus.lz");

static const unsigned char sTheFangOfCritiasBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_fang_of_critias.huff");
static const unsigned short sTheFangOfCritiasBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_fang_of_critias.gbapal");
static const unsigned char sTheFangOfCritiasMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_fang_of_critias.lz");

static const unsigned char sTheLawOfTheNormalBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_law_of_the_normal.huff");
static const unsigned short sTheLawOfTheNormalBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_law_of_the_normal.gbapal");
static const unsigned char sTheLawOfTheNormalMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_law_of_the_normal.lz");

static const unsigned char sTheLegendaryExodiaIncarnateBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_legendary_exodia_incarnate.huff");
static const unsigned short sTheLegendaryExodiaIncarnateBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_legendary_exodia_incarnate.gbapal");
static const unsigned char sTheLegendaryExodiaIncarnateMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_legendary_exodia_incarnate.lz");

static const unsigned char sTheShallowGraveBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_shallow_grave.huff");
static const unsigned short sTheShallowGraveBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_shallow_grave.gbapal");
static const unsigned char sTheShallowGraveMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_shallow_grave.lz");

static const unsigned char sTheinenTheGreatSphinxBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/theinen_the_great_sphinx.huff");
static const unsigned short sTheinenTheGreatSphinxBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/theinen_the_great_sphinx.gbapal");
static const unsigned char sTheinenTheGreatSphinxMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/theinen_the_great_sphinx.lz");

static const unsigned char sThestalosTheFirestormMonarchBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/thestalos_the_firestorm_monarch.huff");
static const unsigned short sThestalosTheFirestormMonarchBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/thestalos_the_firestorm_monarch.gbapal");
static const unsigned char sThestalosTheFirestormMonarchMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/thestalos_the_firestorm_monarch.lz");

static const unsigned char sThunderDragonColossusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/thunder_dragon_colossus.huff");
static const unsigned short sThunderDragonColossusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/thunder_dragon_colossus.gbapal");
static const unsigned char sThunderDragonColossusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/thunder_dragon_colossus.lz");

static const unsigned char sThunderDragonTitanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/thunder_dragon_titan.huff");
static const unsigned short sThunderDragonTitanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/thunder_dragon_titan.gbapal");
static const unsigned char sThunderDragonTitanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/thunder_dragon_titan.lz");

static const unsigned char sTimaeusTheKnightOfDestinyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/timaeus_the_knight_of_destiny.huff");
static const unsigned short sTimaeusTheKnightOfDestinyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/timaeus_the_knight_of_destiny.gbapal");
static const unsigned char sTimaeusTheKnightOfDestinyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/timaeus_the_knight_of_destiny.lz");

static const unsigned char sTimeMagicHammerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/time_magic_hammer.huff");
static const unsigned short sTimeMagicHammerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/time_magic_hammer.gbapal");
static const unsigned char sTimeMagicHammerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/time_magic_hammer.lz");

static const unsigned char sTornadoWallBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/tornado_wall.huff");
static const unsigned short sTornadoWallBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/tornado_wall.gbapal");
static const unsigned char sTornadoWallMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/tornado_wall.lz");

static const unsigned char sToonWorldBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/toon_world.huff");
static const unsigned short sToonWorldBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/toon_world.gbapal");
static const unsigned char sToonWorldMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/toon_world.lz");

static const unsigned char sTornadoBirdBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/tornado_bird.huff");
static const unsigned short sTornadoBirdBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/tornado_bird.gbapal");
static const unsigned char sTornadoBirdMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/tornado_bird.lz");

static const unsigned char sTrapDustshootBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/trap_dustshoot.huff");
static const unsigned short sTrapDustshootBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/trap_dustshoot.gbapal");
static const unsigned char sTrapDustshootMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/trap_dustshoot.lz");

static const unsigned char sTyrantBurstDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/tyrant_burst_dragon.huff");
static const unsigned short sTyrantBurstDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/tyrant_burst_dragon.gbapal");
static const unsigned char sTyrantBurstDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/tyrant_burst_dragon.lz");

static const unsigned char sTyrantWingBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/tyrant_wing.huff");
static const unsigned short sTyrantWingBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/tyrant_wing.gbapal");
static const unsigned char sTyrantWingMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/tyrant_wing.lz");

static const unsigned char sUltimateConductorTyrannoBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ultimate_conductor_tyranno.huff");
static const unsigned short sUltimateConductorTyrannoBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ultimate_conductor_tyranno.gbapal");
static const unsigned char sUltimateConductorTyrannoMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ultimate_conductor_tyranno.lz");

static const unsigned char sUltimateObedientFiendBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ultimate_obedient_fiend.huff");
static const unsigned short sUltimateObedientFiendBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ultimate_obedient_fiend.gbapal");
static const unsigned char sUltimateObedientFiendMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ultimate_obedient_fiend.lz");

static const unsigned char sVisionFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vision_fusion.huff");
static const unsigned short sVisionFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vision_fusion.gbapal");
static const unsigned char sVisionFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vision_fusion.lz");

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

static const unsigned char sVisionHeroMinimumRayBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vision_hero_minimum_ray.huff");
static const unsigned short sVisionHeroMinimumRayBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vision_hero_minimum_ray.gbapal");
static const unsigned char sVisionHeroMinimumRayMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vision_hero_minimum_ray.lz");

static const unsigned char sVisionHeroMultiplyGuyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vision_hero_multiply_guy.huff");
static const unsigned short sVisionHeroMultiplyGuyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vision_hero_multiply_guy.gbapal");
static const unsigned char sVisionHeroMultiplyGuyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vision_hero_multiply_guy.lz");

static const unsigned char sVisionHeroPoisonerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vision_hero_poisoner.huff");
static const unsigned short sVisionHeroPoisonerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vision_hero_poisoner.gbapal");
static const unsigned char sVisionHeroPoisonerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vision_hero_poisoner.lz");

static const unsigned char sVisionHeroTrinityBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vision_hero_trinity.huff");
static const unsigned short sVisionHeroTrinityBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vision_hero_trinity.gbapal");
static const unsigned char sVisionHeroTrinityMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vision_hero_trinity.lz");

static const unsigned char sVisionHeroVyonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vision_hero_vyon.huff");
static const unsigned short sVisionHeroVyonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vision_hero_vyon.gbapal");
static const unsigned char sVisionHeroVyonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vision_hero_vyon.lz");

static const unsigned char sVisionReleaseBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vision_release.huff");
static const unsigned short sVisionReleaseBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vision_release.gbapal");
static const unsigned char sVisionReleaseMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vision_release.lz");

static const unsigned char sWataponBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/watapon.huff");
static const unsigned short sWataponBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/watapon.gbapal");
static const unsigned char sWataponMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/watapon.lz");

static const unsigned char sWhiteDragonRitualBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/white_dragon_ritual.huff");
static const unsigned short sWhiteDragonRitualBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/white_dragon_ritual.gbapal");
static const unsigned char sWhiteDragonRitualMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/white_dragon_ritual.lz");

static const unsigned char sWildNaturesReleaseBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/wild_natures_release.huff");
static const unsigned short sWildNaturesReleaseBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/wild_natures_release.gbapal");
static const unsigned char sWildNaturesReleaseMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/wild_natures_release.lz");

static const unsigned char sWoughtweilerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/woughtweiler.huff");
static const unsigned short sWoughtweilerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/woughtweiler.gbapal");
static const unsigned char sWoughtweilerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/woughtweiler.lz");

static const unsigned char sYellowGadgetBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/yellow_gadget.huff");
static const unsigned short sYellowGadgetBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/yellow_gadget.gbapal");
static const unsigned char sYellowGadgetMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/yellow_gadget.lz");

static const unsigned char sVisionHeroWitchRaiderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vision_hero_witch_raider.huff");
static const unsigned short sVisionHeroWitchRaiderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vision_hero_witch_raider.gbapal");
static const unsigned char sVisionHeroWitchRaiderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vision_hero_witch_raider.lz");

static const unsigned char sAlluringMirrorSplitBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/alluring_mirror_split.huff");
static const unsigned short sAlluringMirrorSplitBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/alluring_mirror_split.gbapal");
static const unsigned char sAlluringMirrorSplitMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/alluring_mirror_split.lz");

static const unsigned char sAmbushFangsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ambush_fangs.huff");
static const unsigned short sAmbushFangsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ambush_fangs.gbapal");
static const unsigned char sAmbushFangsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ambush_fangs.lz");

static const unsigned char sArcaniteMagicianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcanite_magician.huff");
static const unsigned short sArcaniteMagicianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcanite_magician.gbapal");
static const unsigned char sArcaniteMagicianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcanite_magician.lz");

static const unsigned char sArmoryArmBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/armory_arm.huff");
static const unsigned short sArmoryArmBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/armory_arm.gbapal");
static const unsigned char sArmoryArmMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/armory_arm.lz");

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

static const unsigned char sAromageBergamotBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aromage_bergamot.huff");
static const unsigned short sAromageBergamotBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aromage_bergamot.gbapal");
static const unsigned char sAromageBergamotMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aromage_bergamot.lz");

static const unsigned char sAromageCanangaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aromage_cananga.huff");
static const unsigned short sAromageCanangaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aromage_cananga.gbapal");
static const unsigned char sAromageCanangaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aromage_cananga.lz");

static const unsigned char sAromageJasmineBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aromage_jasmine.huff");
static const unsigned short sAromageJasmineBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aromage_jasmine.gbapal");
static const unsigned char sAromageJasmineMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aromage_jasmine.lz");

static const unsigned char sAromageLaurelBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aromage_laurel.huff");
static const unsigned short sAromageLaurelBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aromage_laurel.gbapal");
static const unsigned char sAromageLaurelMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aromage_laurel.lz");

static const unsigned char sAromageMarjoramBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aromage_marjoram.huff");
static const unsigned short sAromageMarjoramBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aromage_marjoram.gbapal");
static const unsigned char sAromageMarjoramMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aromage_marjoram.lz");

static const unsigned char sAromageRosemaryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aromage_rosemary.huff");
static const unsigned short sAromageRosemaryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aromage_rosemary.gbapal");
static const unsigned char sAromageRosemaryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aromage_rosemary.lz");

static const unsigned char sAromalilithMagnoliaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aromalilith_magnolia.huff");
static const unsigned short sAromalilithMagnoliaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aromalilith_magnolia.gbapal");
static const unsigned char sAromalilithMagnoliaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aromalilith_magnolia.lz");

static const unsigned char sAromalilithRosalinaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aromalilith_rosalina.huff");
static const unsigned short sAromalilithRosalinaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aromalilith_rosalina.gbapal");
static const unsigned char sAromalilithRosalinaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aromalilith_rosalina.lz");

static const unsigned char sAromalilithRosemaryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aromalilith_rosemary.huff");
static const unsigned short sAromalilithRosemaryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aromalilith_rosemary.gbapal");
static const unsigned char sAromalilithRosemaryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aromalilith_rosemary.lz");

static const unsigned char sAromaseraphyJasmineBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aromaseraphy_jasmine.huff");
static const unsigned short sAromaseraphyJasmineBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aromaseraphy_jasmine.gbapal");
static const unsigned char sAromaseraphyJasmineMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aromaseraphy_jasmine.lz");

static const unsigned char sAromaseraphyRosemaryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aromaseraphy_rosemary.huff");
static const unsigned short sAromaseraphyRosemaryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aromaseraphy_rosemary.gbapal");
static const unsigned char sAromaseraphyRosemaryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aromaseraphy_rosemary.lz");

static const unsigned char sAromaseraphySweetMarjoramBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aromaseraphy_sweet_marjoram.huff");
static const unsigned short sAromaseraphySweetMarjoramBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aromaseraphy_sweet_marjoram.gbapal");
static const unsigned char sAromaseraphySweetMarjoramMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aromaseraphy_sweet_marjoram.lz");

static const unsigned char sAttackPheromonesBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/attack_pheromones.huff");
static const unsigned short sAttackPheromonesBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/attack_pheromones.gbapal");
static const unsigned char sAttackPheromonesMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/attack_pheromones.lz");

static const unsigned char sAzureEyesSilverDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/azure_eyes_silver_dragon.huff");
static const unsigned short sAzureEyesSilverDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/azure_eyes_silver_dragon.gbapal");
static const unsigned char sAzureEyesSilverDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/azure_eyes_silver_dragon.lz");

static const unsigned char sBlackRoseDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/black_rose_dragon.huff");
static const unsigned short sBlackRoseDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/black_rose_dragon.gbapal");
static const unsigned char sBlackRoseDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/black_rose_dragon.lz");

static const unsigned char sBlessedWindsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blessed_winds.huff");
static const unsigned short sBlessedWindsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blessed_winds.gbapal");
static const unsigned char sBlessedWindsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blessed_winds.lz");

static const unsigned char sBlueEyesJetDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_jet_dragon.huff");
static const unsigned short sBlueEyesJetDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_jet_dragon.gbapal");
static const unsigned char sBlueEyesJetDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_jet_dragon.lz");

static const unsigned char sBlueEyesSolidDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_solid_dragon.huff");
static const unsigned short sBlueEyesSolidDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_solid_dragon.gbapal");
static const unsigned char sBlueEyesSolidDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_solid_dragon.lz");

static const unsigned char sBlueEyesTyrantDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_tyrant_dragon.huff");
static const unsigned short sBlueEyesTyrantDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_tyrant_dragon.gbapal");
static const unsigned char sBlueEyesTyrantDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_tyrant_dragon.lz");

static const unsigned char sBlueEyesUltimateSpiritDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_ultimate_spirit_dragon.huff");
static const unsigned short sBlueEyesUltimateSpiritDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_ultimate_spirit_dragon.gbapal");
static const unsigned char sBlueEyesUltimateSpiritDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_ultimate_spirit_dragon.lz");

static const unsigned char sBondBetweenTeacherAndStudentBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/bond_between_teacher_and_student.huff");
static const unsigned short sBondBetweenTeacherAndStudentBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/bond_between_teacher_and_student.gbapal");
static const unsigned char sBondBetweenTeacherAndStudentMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/bond_between_teacher_and_student.lz");

static const unsigned char sBlueEyesSpiritDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/blue_eyes_spirit_dragon.huff");
static const unsigned short sBlueEyesSpiritDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/blue_eyes_spirit_dragon.gbapal");
static const unsigned char sBlueEyesSpiritDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/blue_eyes_spirit_dragon.lz");

static const unsigned char sBrionacDragonOfTheIceBarrierBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/brionac_dragon_of_the_ice_barrier.huff");
static const unsigned short sBrionacDragonOfTheIceBarrierBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/brionac_dragon_of_the_ice_barrier.gbapal");
static const unsigned char sBrionacDragonOfTheIceBarrierMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/brionac_dragon_of_the_ice_barrier.lz");

static const unsigned char sChainMaterialBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chain_material.huff");
static const unsigned short sChainMaterialBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chain_material.gbapal");
static const unsigned char sChainMaterialMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chain_material.lz");

static const unsigned char sColossalFighterBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/colossal_fighter.huff");
static const unsigned short sColossalFighterBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/colossal_fighter.gbapal");
static const unsigned char sColossalFighterMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/colossal_fighter.lz");

static const unsigned char sCupOfAceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cup_of_ace.huff");
static const unsigned short sCupOfAceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cup_of_ace.gbapal");
static const unsigned char sCupOfAceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cup_of_ace.lz");

static const unsigned char sCyberSlashHarpieLadyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cyber_slash_harpie_lady.huff");
static const unsigned short sCyberSlashHarpieLadyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cyber_slash_harpie_lady.gbapal");
static const unsigned char sCyberSlashHarpieLadyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cyber_slash_harpie_lady.lz");

static const unsigned char sDamageReptileBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/damage_reptile.huff");
static const unsigned short sDamageReptileBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/damage_reptile.gbapal");
static const unsigned char sDamageReptileMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/damage_reptile.lz");

static const unsigned char sDarkBurningAttackBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_burning_attack.huff");
static const unsigned short sDarkBurningAttackBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_burning_attack.gbapal");
static const unsigned char sDarkBurningAttackMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_burning_attack.lz");

static const unsigned char sDarkBurningMagicBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_burning_magic.huff");
static const unsigned short sDarkBurningMagicBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_burning_magic.gbapal");
static const unsigned char sDarkBurningMagicMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_burning_magic.lz");

static const unsigned char sDarkCallingBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_calling.huff");
static const unsigned short sDarkCallingBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_calling.gbapal");
static const unsigned char sDarkCallingMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_calling.lz");

static const unsigned char sDarkContactBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_contact.huff");
static const unsigned short sDarkContactBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_contact.gbapal");
static const unsigned char sDarkContactMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_contact.lz");

static const unsigned char sDarkFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_fusion.huff");
static const unsigned short sDarkFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_fusion.gbapal");
static const unsigned char sDarkFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_fusion.lz");

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

static const unsigned char sDarkMagicianGirlTheMagicianSApprenticeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_magician_girl_the_magician_s_apprentice.huff");
static const unsigned short sDarkMagicianGirlTheMagicianSApprenticeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_magician_girl_the_magician_s_apprentice.gbapal");
static const unsigned char sDarkMagicianGirlTheMagicianSApprenticeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_magician_girl_the_magician_s_apprentice.lz");

static const unsigned char sDarkMagicianOfDestructionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_magician_of_destruction.huff");
static const unsigned short sDarkMagicianOfDestructionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_magician_of_destruction.gbapal");
static const unsigned char sDarkMagicianOfDestructionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_magician_of_destruction.lz");

static const unsigned char sDarkMagicianTheMagicianOfBlackMagicBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_magician_the_magician_of_black_magic.huff");
static const unsigned short sDarkMagicianTheMagicianOfBlackMagicBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_magician_the_magician_of_black_magic.gbapal");
static const unsigned char sDarkMagicianTheMagicianOfBlackMagicMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_magician_the_magician_of_black_magic.lz");

static const unsigned char sDarkRenewalBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_renewal.huff");
static const unsigned short sDarkRenewalBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_renewal.gbapal");
static const unsigned char sDarkRenewalMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_renewal.lz");

static const unsigned char sDarkStrikeFighterBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_strike_fighter.huff");
static const unsigned short sDarkStrikeFighterBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_strike_fighter.gbapal");
static const unsigned char sDarkStrikeFighterMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_strike_fighter.lz");

static const unsigned char sDarkSupremacyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dark_supremacy.huff");
static const unsigned short sDarkSupremacyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dark_supremacy.gbapal");
static const unsigned char sDarkSupremacyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dark_supremacy.lz");

static const unsigned char sDestinedRivalsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/destined_rivals.huff");
static const unsigned short sDestinedRivalsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/destined_rivals.gbapal");
static const unsigned char sDestinedRivalsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/destined_rivals.lz");

static const unsigned char sDriedWindsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dried_winds.huff");
static const unsigned short sDriedWindsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dried_winds.gbapal");
static const unsigned char sDriedWindsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dried_winds.lz");

static const unsigned char sDragonRavineBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dragon_ravine.huff");
static const unsigned short sDragonRavineBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dragon_ravine.gbapal");
static const unsigned char sDragonRavineMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dragon_ravine.lz");

static const unsigned char sDragonShrineBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dragon_shrine.huff");
static const unsigned short sDragonShrineBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dragon_shrine.gbapal");
static const unsigned char sDragonShrineMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dragon_shrine.lz");

static const unsigned char sDeepEyesWhiteDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/deep_eyes_white_dragon.huff");
static const unsigned short sDeepEyesWhiteDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/deep_eyes_white_dragon.gbapal");
static const unsigned char sDeepEyesWhiteDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/deep_eyes_white_dragon.lz");

static const unsigned char sDragonMasterMagiaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dragon_master_magia.huff");
static const unsigned short sDragonMasterMagiaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dragon_master_magia.gbapal");
static const unsigned char sDragonMasterMagiaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dragon_master_magia.lz");

static const unsigned char sDragonSpiritOfWhiteBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/dragon_spirit_of_white.huff");
static const unsigned short sDragonSpiritOfWhiteBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/dragon_spirit_of_white.gbapal");
static const unsigned char sDragonSpiritOfWhiteMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/dragon_spirit_of_white.lz");

static const unsigned char sEbonIllusionMagicianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ebon_illusion_magician.huff");
static const unsigned short sEbonIllusionMagicianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ebon_illusion_magician.gbapal");
static const unsigned char sEbonIllusionMagicianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ebon_illusion_magician.lz");

static const unsigned char sElShaddollAnoyatyllisBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/el_shaddoll_anoyatyllis.huff");
static const unsigned short sElShaddollAnoyatyllisBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/el_shaddoll_anoyatyllis.gbapal");
static const unsigned char sElShaddollAnoyatyllisMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/el_shaddoll_anoyatyllis.lz");

static const unsigned char sElShaddollApkalloneBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/el_shaddoll_apkallone.huff");
static const unsigned short sElShaddollApkalloneBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/el_shaddoll_apkallone.gbapal");
static const unsigned char sElShaddollApkalloneMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/el_shaddoll_apkallone.lz");

static const unsigned char sElShaddollConstructBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/el_shaddoll_construct.huff");
static const unsigned short sElShaddollConstructBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/el_shaddoll_construct.gbapal");
static const unsigned char sElShaddollConstructMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/el_shaddoll_construct.lz");

static const unsigned char sElShaddollFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/el_shaddoll_fusion.huff");
static const unsigned short sElShaddollFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/el_shaddoll_fusion.gbapal");
static const unsigned char sElShaddollFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/el_shaddoll_fusion.lz");

static const unsigned char sElShaddollGrystaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/el_shaddoll_grysta.huff");
static const unsigned short sElShaddollGrystaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/el_shaddoll_grysta.gbapal");
static const unsigned char sElShaddollGrystaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/el_shaddoll_grysta.lz");

static const unsigned char sElShaddollMeshahrailBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/el_shaddoll_meshahrail.huff");
static const unsigned short sElShaddollMeshahrailBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/el_shaddoll_meshahrail.gbapal");
static const unsigned char sElShaddollMeshahrailMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/el_shaddoll_meshahrail.lz");

static const unsigned char sElShaddollShekhinagaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/el_shaddoll_shekhinaga.huff");
static const unsigned short sElShaddollShekhinagaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/el_shaddoll_shekhinaga.gbapal");
static const unsigned char sElShaddollShekhinagaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/el_shaddoll_shekhinaga.lz");

static const unsigned char sElShaddollWendigoBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/el_shaddoll_wendigo.huff");
static const unsigned short sElShaddollWendigoBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/el_shaddoll_wendigo.gbapal");
static const unsigned char sElShaddollWendigoMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/el_shaddoll_wendigo.lz");

static const unsigned char sElShaddollWindaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/el_shaddoll_winda.huff");
static const unsigned short sElShaddollWindaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/el_shaddoll_winda.gbapal");
static const unsigned char sElShaddollWindaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/el_shaddoll_winda.lz");

static const unsigned char sEternalSoulBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/eternal_soul.huff");
static const unsigned short sEternalSoulBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/eternal_soul.gbapal");
static const unsigned char sEternalSoulMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/eternal_soul.lz");

static const unsigned char sEvilAssaultBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_assault.huff");
static const unsigned short sEvilAssaultBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_assault.gbapal");
static const unsigned char sEvilAssaultMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_assault.lz");

static const unsigned char sEvilDragonAnantaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_dragon_ananta.huff");
static const unsigned short sEvilDragonAnantaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_dragon_ananta.gbapal");
static const unsigned char sEvilDragonAnantaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_dragon_ananta.lz");

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

static const unsigned char sEvilHeroInfernalProdigyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_infernal_prodigy.huff");
static const unsigned short sEvilHeroInfernalProdigyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_infernal_prodigy.gbapal");
static const unsigned char sEvilHeroInfernalProdigyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_infernal_prodigy.lz");

static const unsigned char sEvilHeroInfernalRiderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_infernal_rider.huff");
static const unsigned short sEvilHeroInfernalRiderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_infernal_rider.gbapal");
static const unsigned char sEvilHeroInfernalRiderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_infernal_rider.lz");

static const unsigned char sEvilHeroInfernalSniperBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_infernal_sniper.huff");
static const unsigned short sEvilHeroInfernalSniperBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_infernal_sniper.gbapal");
static const unsigned char sEvilHeroInfernalSniperMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_infernal_sniper.lz");

static const unsigned char sEvilHeroInfernoWingBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_inferno_wing.huff");
static const unsigned short sEvilHeroInfernoWingBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_inferno_wing.gbapal");
static const unsigned char sEvilHeroInfernoWingMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_inferno_wing.lz");

static const unsigned char sEvilHeroInfernoWingBackfireBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_inferno_wing_backfire.huff");
static const unsigned short sEvilHeroInfernoWingBackfireBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_inferno_wing_backfire.gbapal");
static const unsigned char sEvilHeroInfernoWingBackfireMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_inferno_wing_backfire.lz");

static const unsigned char sEvilHeroLightningGolemBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_lightning_golem.huff");
static const unsigned short sEvilHeroLightningGolemBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_lightning_golem.gbapal");
static const unsigned char sEvilHeroLightningGolemMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_lightning_golem.lz");

static const unsigned char sEvilHeroMaliciousBaneBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_malicious_bane.huff");
static const unsigned short sEvilHeroMaliciousBaneBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_malicious_bane.gbapal");
static const unsigned char sEvilHeroMaliciousBaneMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_malicious_bane.lz");

static const unsigned char sEvilHeroMaliciousEdgeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_malicious_edge.huff");
static const unsigned short sEvilHeroMaliciousEdgeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_malicious_edge.gbapal");
static const unsigned char sEvilHeroMaliciousEdgeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_malicious_edge.lz");

static const unsigned char sEvilHeroMaliciousFiendBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_malicious_fiend.huff");
static const unsigned short sEvilHeroMaliciousFiendBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_malicious_fiend.gbapal");
static const unsigned char sEvilHeroMaliciousFiendMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_malicious_fiend.lz");

static const unsigned char sEvilHeroNeosLordBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_neos_lord.huff");
static const unsigned short sEvilHeroNeosLordBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_neos_lord.gbapal");
static const unsigned char sEvilHeroNeosLordMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_neos_lord.lz");

static const unsigned char sEvilHeroSinisterNecromBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_sinister_necrom.huff");
static const unsigned short sEvilHeroSinisterNecromBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_sinister_necrom.gbapal");
static const unsigned char sEvilHeroSinisterNecromMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_sinister_necrom.lz");

static const unsigned char sEvilHeroToxicBubbleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_toxic_bubble.huff");
static const unsigned short sEvilHeroToxicBubbleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_toxic_bubble.gbapal");
static const unsigned char sEvilHeroToxicBubbleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_toxic_bubble.lz");

static const unsigned char sEvilHeroViciousClawsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_vicious_claws.huff");
static const unsigned short sEvilHeroViciousClawsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_vicious_claws.gbapal");
static const unsigned char sEvilHeroViciousClawsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_vicious_claws.lz");

static const unsigned char sEvilHeroWildCycloneBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_hero_wild_cyclone.huff");
static const unsigned short sEvilHeroWildCycloneBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_hero_wild_cyclone.gbapal");
static const unsigned char sEvilHeroWildCycloneMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_hero_wild_cyclone.lz");

static const unsigned char sEvilMindBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/evil_mind.huff");
static const unsigned short sEvilMindBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/evil_mind.gbapal");
static const unsigned char sEvilMindMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/evil_mind.lz");

static const unsigned char sFusionDeploymentBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/fusion_deployment.huff");
static const unsigned short sFusionDeploymentBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/fusion_deployment.gbapal");
static const unsigned char sFusionDeploymentMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/fusion_deployment.lz");

static const unsigned char sGandoraGTheDragonOfDestructionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gandora_g_the_dragon_of_destruction.huff");
static const unsigned short sGandoraGTheDragonOfDestructionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gandora_g_the_dragon_of_destruction.gbapal");
static const unsigned char sGandoraGTheDragonOfDestructionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gandora_g_the_dragon_of_destruction.lz");

static const unsigned char sGandoraXTheDragonOfDemolitionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gandora_x_the_dragon_of_demolition.huff");
static const unsigned short sGandoraXTheDragonOfDemolitionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gandora_x_the_dragon_of_demolition.gbapal");
static const unsigned char sGandoraXTheDragonOfDemolitionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gandora_x_the_dragon_of_demolition.lz");

static const unsigned char sGoyoGuardianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/goyo_guardian.huff");
static const unsigned short sGoyoGuardianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/goyo_guardian.gbapal");
static const unsigned char sGoyoGuardianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/goyo_guardian.lz");

static const unsigned char sGrinderGolemBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/grinder_golem.huff");
static const unsigned short sGrinderGolemBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/grinder_golem.gbapal");
static const unsigned char sGrinderGolemMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/grinder_golem.lz");

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

static const unsigned char sHelshaddollHollowBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/helshaddoll_hollow.huff");
static const unsigned short sHelshaddollHollowBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/helshaddoll_hollow.gbapal");
static const unsigned char sHelshaddollHollowMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/helshaddoll_hollow.lz");

static const unsigned char sHeraldOfPerfectionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/herald_of_perfection.huff");
static const unsigned short sHeraldOfPerfectionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/herald_of_perfection.gbapal");
static const unsigned char sHeraldOfPerfectionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/herald_of_perfection.lz");

static const unsigned char sHeraldOfUltimatenessBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/herald_of_ultimateness.huff");
static const unsigned short sHeraldOfUltimatenessBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/herald_of_ultimateness.gbapal");
static const unsigned char sHeraldOfUltimatenessMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/herald_of_ultimateness.lz");

static const unsigned char sHeroKidBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/hero_kid.huff");
static const unsigned short sHeroKidBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/hero_kid.gbapal");
static const unsigned char sHeroKidMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/hero_kid.lz");

static const unsigned char sHumidWindsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/humid_winds.huff");
static const unsigned short sHumidWindsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/humid_winds.gbapal");
static const unsigned char sHumidWindsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/humid_winds.lz");

static const unsigned char sHystericPartyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/hysteric_party.huff");
static const unsigned short sHystericPartyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/hysteric_party.gbapal");
static const unsigned char sHystericPartyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/hysteric_party.lz");

static const unsigned char sHystericSignBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/hysteric_sign.huff");
static const unsigned short sHystericSignBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/hysteric_sign.gbapal");
static const unsigned char sHystericSignMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/hysteric_sign.lz");

static const unsigned char sIllusionMagicBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/illusion_magic.huff");
static const unsigned short sIllusionMagicBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/illusion_magic.gbapal");
static const unsigned char sIllusionMagicMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/illusion_magic.lz");

static const unsigned char sIllusionOfChaosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/illusion_of_chaos.huff");
static const unsigned short sIllusionOfChaosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/illusion_of_chaos.gbapal");
static const unsigned char sIllusionOfChaosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/illusion_of_chaos.lz");

static const unsigned char sIpiriaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ipiria.huff");
static const unsigned short sIpiriaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ipiria.gbapal");
static const unsigned char sIpiriaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ipiria.lz");

static const unsigned char sJunkWarriorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/junk_warrior.huff");
static const unsigned short sJunkWarriorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/junk_warrior.gbapal");
static const unsigned char sJunkWarriorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/junk_warrior.lz");

static const unsigned char sKeeperOfDragonMagicBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/keeper_of_dragon_magic.huff");
static const unsigned short sKeeperOfDragonMagicBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/keeper_of_dragon_magic.gbapal");
static const unsigned char sKeeperOfDragonMagicMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/keeper_of_dragon_magic.lz");

static const unsigned char sLegendaryMajuGarzettBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/legendary_maju_garzett.huff");
static const unsigned short sLegendaryMajuGarzettBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/legendary_maju_garzett.gbapal");
static const unsigned char sLegendaryMajuGarzettMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/legendary_maju_garzett.lz");

static const unsigned char sLevShaddollFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lev_shaddoll_fusion.huff");
static const unsigned short sLevShaddollFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lev_shaddoll_fusion.gbapal");
static const unsigned char sLevShaddollFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lev_shaddoll_fusion.lz");

static const unsigned char sLightSerpentBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/light_serpent.huff");
static const unsigned short sLightSerpentBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/light_serpent.gbapal");
static const unsigned char sLightSerpentMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/light_serpent.lz");

static const unsigned char sLightningWarriorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lightning_warrior.huff");
static const unsigned short sLightningWarriorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lightning_warrior.gbapal");
static const unsigned char sLightningWarriorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lightning_warrior.lz");

static const unsigned char sLonefireBlossomBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lonefire_blossom.huff");
static const unsigned short sLonefireBlossomBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lonefire_blossom.gbapal");
static const unsigned char sLonefireBlossomMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lonefire_blossom.lz");

static const unsigned char sMagicianNavigationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magician_navigation.huff");
static const unsigned short sMagicianNavigationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magician_navigation.gbapal");
static const unsigned char sMagicianNavigationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magician_navigation.lz");

static const unsigned char sMagicianOfDarkIllusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magician_of_dark_illusion.huff");
static const unsigned short sMagicianOfDarkIllusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magician_of_dark_illusion.gbapal");
static const unsigned char sMagicianOfDarkIllusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magician_of_dark_illusion.lz");

static const unsigned char sMagiciansCombinationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magicians_combination.huff");
static const unsigned short sMagiciansCombinationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magicians_combination.gbapal");
static const unsigned char sMagiciansCombinationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magicians_combination.lz");

static const unsigned char sMagiciansRobeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magicians_robe.huff");
static const unsigned short sMagiciansRobeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magicians_robe.gbapal");
static const unsigned char sMagiciansRobeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magicians_robe.lz");

static const unsigned char sMagiciansRodBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magicians_rod.huff");
static const unsigned short sMagiciansRodBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magicians_rod.gbapal");
static const unsigned char sMagiciansRodMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magicians_rod.lz");

static const unsigned char sMagiciansSoulsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/magicians_souls.huff");
static const unsigned short sMagiciansSoulsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/magicians_souls.gbapal");
static const unsigned char sMagiciansSoulsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/magicians_souls.lz");

static const unsigned char sMasterOfChaosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/master_of_chaos.huff");
static const unsigned short sMasterOfChaosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/master_of_chaos.gbapal");
static const unsigned char sMasterOfChaosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/master_of_chaos.lz");

static const unsigned char sMetaverseBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/metaverse.huff");
static const unsigned short sMetaverseBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/metaverse.gbapal");
static const unsigned char sMetaverseMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/metaverse.lz");

static const unsigned char sMillenniumEyesRestrictBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/millennium_eyes_restrict.huff");
static const unsigned short sMillenniumEyesRestrictBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/millennium_eyes_restrict.gbapal");
static const unsigned char sMillenniumEyesRestrictMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/millennium_eyes_restrict.lz");

static const unsigned char sMoltingEscapeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/molting_escape.huff");
static const unsigned short sMoltingEscapeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/molting_escape.gbapal");
static const unsigned char sMoltingEscapeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/molting_escape.lz");

static const unsigned char sMysticMineBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/mystic_mine.huff");
static const unsigned short sMysticMineBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/mystic_mine.gbapal");
static const unsigned char sMysticMineMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/mystic_mine.lz");

static const unsigned char sNaelshaddollArielBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/naelshaddoll_ariel.huff");
static const unsigned short sNaelshaddollArielBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/naelshaddoll_ariel.gbapal");
static const unsigned char sNaelshaddollArielMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/naelshaddoll_ariel.lz");

static const unsigned char sNehshaddollGeniusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/nehshaddoll_genius.huff");
static const unsigned short sNehshaddollGeniusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/nehshaddoll_genius.gbapal");
static const unsigned char sNehshaddollGeniusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/nehshaddoll_genius.lz");

static const unsigned char sNepheShaddollFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/nephe_shaddoll_fusion.huff");
static const unsigned short sNepheShaddollFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/nephe_shaddoll_fusion.gbapal");
static const unsigned char sNepheShaddollFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/nephe_shaddoll_fusion.lz");

static const unsigned char sNeutronBlastBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neutron_blast.huff");
static const unsigned short sNeutronBlastBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neutron_blast.gbapal");
static const unsigned char sNeutronBlastMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neutron_blast.lz");

static const unsigned char sOfferingToTheSnakeDeityBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/offering_to_the_snake_deity.huff");
static const unsigned short sOfferingToTheSnakeDeityBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/offering_to_the_snake_deity.gbapal");
static const unsigned char sOfferingToTheSnakeDeityMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/offering_to_the_snake_deity.lz");

static const unsigned char sOshaleonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/oshaleon.huff");
static const unsigned short sOshaleonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/oshaleon.gbapal");
static const unsigned char sOshaleonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/oshaleon.lz");

static const unsigned char sPowerToolDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/power_tool_dragon.huff");
static const unsigned short sPowerToolDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/power_tool_dragon.gbapal");
static const unsigned char sPowerToolDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/power_tool_dragon.lz");

static const unsigned char sPredaplantVerteAnacondaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/predaplant_verte_anaconda.huff");
static const unsigned short sPredaplantVerteAnacondaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/predaplant_verte_anaconda.gbapal");
static const unsigned char sPredaplantVerteAnacondaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/predaplant_verte_anaconda.lz");

static const unsigned char sQadshaddollKeiosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/qadshaddoll_keios.huff");
static const unsigned short sQadshaddollKeiosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/qadshaddoll_keios.gbapal");
static const unsigned char sQadshaddollKeiosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/qadshaddoll_keios.lz");

static const unsigned char sRedDragonArchfiendBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/red_dragon_archfiend.huff");
static const unsigned short sRedDragonArchfiendBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/red_dragon_archfiend.gbapal");
static const unsigned char sRedDragonArchfiendMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/red_dragon_archfiend.lz");

static const unsigned char sRedRebootBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/red_reboot.huff");
static const unsigned short sRedRebootBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/red_reboot.gbapal");
static const unsigned char sRedRebootMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/red_reboot.lz");

static const unsigned char sReeshaddollWendiBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reeshaddoll_wendi.huff");
static const unsigned short sReeshaddollWendiBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reeshaddoll_wendi.gbapal");
static const unsigned char sReeshaddollWendiMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reeshaddoll_wendi.lz");

static const unsigned char sReeshaddollWendikuruhuBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reeshaddoll_wendikuruhu.huff");
static const unsigned short sReeshaddollWendikuruhuBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reeshaddoll_wendikuruhu.gbapal");
static const unsigned char sReeshaddollWendikuruhuMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reeshaddoll_wendikuruhu.lz");

static const unsigned char sReptilanneRageBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilanne_rage.huff");
static const unsigned short sReptilanneRageBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilanne_rage.gbapal");
static const unsigned char sReptilanneRageMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilanne_rage.lz");

static const unsigned char sReptilianneEchidnaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_echidna.huff");
static const unsigned short sReptilianneEchidnaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_echidna.gbapal");
static const unsigned char sReptilianneEchidnaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_echidna.lz");

static const unsigned char sReptilianneGardnaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_gardna.huff");
static const unsigned short sReptilianneGardnaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_gardna.gbapal");
static const unsigned char sReptilianneGardnaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_gardna.lz");

static const unsigned char sReptilianneGorgonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_gorgon.huff");
static const unsigned short sReptilianneGorgonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_gorgon.gbapal");
static const unsigned char sReptilianneGorgonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_gorgon.lz");

static const unsigned char sReptilianneHydraBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_hydra.huff");
static const unsigned short sReptilianneHydraBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_hydra.gbapal");
static const unsigned char sReptilianneHydraMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_hydra.lz");

static const unsigned char sReptilianneLamiaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_lamia.huff");
static const unsigned short sReptilianneLamiaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_lamia.gbapal");
static const unsigned char sReptilianneLamiaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_lamia.lz");

static const unsigned char sReptilianneMedusaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_medusa.huff");
static const unsigned short sReptilianneMedusaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_medusa.gbapal");
static const unsigned char sReptilianneMedusaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_medusa.lz");

static const unsigned char sReptilianneNagaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_naga.huff");
static const unsigned short sReptilianneNagaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_naga.gbapal");
static const unsigned char sReptilianneNagaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_naga.lz");

static const unsigned char sReptiliannePoisonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_poison.huff");
static const unsigned short sReptiliannePoisonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_poison.gbapal");
static const unsigned char sReptiliannePoisonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_poison.lz");

static const unsigned char sReptilianneScyllaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_scylla.huff");
static const unsigned short sReptilianneScyllaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_scylla.gbapal");
static const unsigned char sReptilianneScyllaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_scylla.lz");

static const unsigned char sReptilianneServantBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_servant.huff");
static const unsigned short sReptilianneServantBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_servant.gbapal");
static const unsigned char sReptilianneServantMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_servant.lz");

static const unsigned char sReptilianneSpawnBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_spawn.huff");
static const unsigned short sReptilianneSpawnBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_spawn.gbapal");
static const unsigned char sReptilianneSpawnMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_spawn.lz");

static const unsigned char sReptilianneVaskiiBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_vaskii.huff");
static const unsigned short sReptilianneVaskiiBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_vaskii.gbapal");
static const unsigned char sReptilianneVaskiiMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_vaskii.lz");

static const unsigned char sReptilianneViperBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reptilianne_viper.huff");
static const unsigned short sReptilianneViperBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reptilianne_viper.gbapal");
static const unsigned char sReptilianneViperMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reptilianne_viper.lz");

static const unsigned char sReturnOfTheDragonLordsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/return_of_the_dragon_lords.huff");
static const unsigned short sReturnOfTheDragonLordsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/return_of_the_dragon_lords.gbapal");
static const unsigned char sReturnOfTheDragonLordsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/return_of_the_dragon_lords.lz");

static const unsigned char sRiseOfTheSnakeDeityBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/rise_of_the_snake_deity.huff");
static const unsigned short sRiseOfTheSnakeDeityBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/rise_of_the_snake_deity.gbapal");
static const unsigned char sRiseOfTheSnakeDeityMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/rise_of_the_snake_deity.lz");

static const unsigned char sSecretsOfDarkMagicBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/secrets_of_dark_magic.huff");
static const unsigned short sSecretsOfDarkMagicBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/secrets_of_dark_magic.gbapal");
static const unsigned char sSecretsOfDarkMagicMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/secrets_of_dark_magic.lz");

static const unsigned char sSerpentSuppressionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/serpent_suppression.huff");
static const unsigned short sSerpentSuppressionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/serpent_suppression.gbapal");
static const unsigned char sSerpentSuppressionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/serpent_suppression.lz");

static const unsigned char sShaddollBeastBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shaddoll_beast.huff");
static const unsigned short sShaddollBeastBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shaddoll_beast.gbapal");
static const unsigned char sShaddollBeastMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shaddoll_beast.lz");

static const unsigned char sShaddollCoreBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shaddoll_core.huff");
static const unsigned short sShaddollCoreBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shaddoll_core.gbapal");
static const unsigned char sShaddollCoreMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shaddoll_core.lz");

static const unsigned char sShaddollDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shaddoll_dragon.huff");
static const unsigned short sShaddollDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shaddoll_dragon.gbapal");
static const unsigned char sShaddollDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shaddoll_dragon.lz");

static const unsigned char sShaddollFalcoBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shaddoll_falco.huff");
static const unsigned short sShaddollFalcoBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shaddoll_falco.gbapal");
static const unsigned char sShaddollFalcoMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shaddoll_falco.lz");

static const unsigned char sShaddollFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shaddoll_fusion.huff");
static const unsigned short sShaddollFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shaddoll_fusion.gbapal");
static const unsigned char sShaddollFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shaddoll_fusion.lz");

static const unsigned char sShaddollHedgehogBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shaddoll_hedgehog.huff");
static const unsigned short sShaddollHedgehogBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shaddoll_hedgehog.gbapal");
static const unsigned char sShaddollHedgehogMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shaddoll_hedgehog.lz");

static const unsigned char sShaddollHoundBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shaddoll_hound.huff");
static const unsigned short sShaddollHoundBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shaddoll_hound.gbapal");
static const unsigned char sShaddollHoundMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shaddoll_hound.lz");

static const unsigned char sShaddollSchismBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shaddoll_schism.huff");
static const unsigned short sShaddollSchismBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shaddoll_schism.gbapal");
static const unsigned char sShaddollSchismMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shaddoll_schism.lz");

static const unsigned char sShaddollSquamataBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shaddoll_squamata.huff");
static const unsigned short sShaddollSquamataBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shaddoll_squamata.gbapal");
static const unsigned char sShaddollSquamataMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shaddoll_squamata.lz");

static const unsigned char sSilversCryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/silvers_cry.huff");
static const unsigned short sSilversCryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/silvers_cry.gbapal");
static const unsigned char sSilversCryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/silvers_cry.lz");

static const unsigned char sSnakeDeitysCommandBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/snake_deitys_command.huff");
static const unsigned short sSnakeDeitysCommandBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/snake_deitys_command.gbapal");
static const unsigned char sSnakeDeitysCommandMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/snake_deitys_command.lz");

static const unsigned char sSnakeRainBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/snake_rain.huff");
static const unsigned short sSnakeRainBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/snake_rain.gbapal");
static const unsigned char sSnakeRainMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/snake_rain.lz");

static const unsigned char sSnakeWhistleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/snake_whistle.huff");
static const unsigned short sSnakeWhistleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/snake_whistle.gbapal");
static const unsigned char sSnakeWhistleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/snake_whistle.lz");

static const unsigned char sSoulServantBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/soul_servant.huff");
static const unsigned short sSoulServantBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/soul_servant.gbapal");
static const unsigned char sSoulServantMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/soul_servant.lz");

static const unsigned char sStardustDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/stardust_dragon.huff");
static const unsigned short sStardustDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/stardust_dragon.gbapal");
static const unsigned char sStardustDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/stardust_dragon.lz");

static const unsigned char sSupremeKingsCastleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/supreme_kings_castle.huff");
static const unsigned short sSupremeKingsCastleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/supreme_kings_castle.gbapal");
static const unsigned char sSupremeKingsCastleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/supreme_kings_castle.lz");

static const unsigned char sThatGrassLooksGreenerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/that_grass_looks_greener.huff");
static const unsigned short sThatGrassLooksGreenerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/that_grass_looks_greener.gbapal");
static const unsigned char sThatGrassLooksGreenerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/that_grass_looks_greener.lz");

static const unsigned char sTheDarkMagiciansBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_dark_magicians.huff");
static const unsigned short sTheDarkMagiciansBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_dark_magicians.gbapal");
static const unsigned char sTheDarkMagiciansMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_dark_magicians.lz");

static const unsigned char sTheGazeOfTimaeusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_gaze_of_timaeus.huff");
static const unsigned short sTheGazeOfTimaeusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_gaze_of_timaeus.gbapal");
static const unsigned char sTheGazeOfTimaeusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_gaze_of_timaeus.lz");

static const unsigned char sTheMelodyOfAwakeningDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_melody_of_awakening_dragon.huff");
static const unsigned short sTheMelodyOfAwakeningDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_melody_of_awakening_dragon.gbapal");
static const unsigned char sTheMelodyOfAwakeningDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_melody_of_awakening_dragon.lz");

static const unsigned char sTheWhiteStoneOfAncientsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_white_stone_of_ancients.huff");
static const unsigned short sTheWhiteStoneOfAncientsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_white_stone_of_ancients.gbapal");
static const unsigned char sTheWhiteStoneOfAncientsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_white_stone_of_ancients.lz");

static const unsigned char sTheWhiteStoneOfLegendBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/the_white_stone_of_legend.huff");
static const unsigned short sTheWhiteStoneOfLegendBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/the_white_stone_of_legend.gbapal");
static const unsigned char sTheWhiteStoneOfLegendMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/the_white_stone_of_legend.lz");

static const unsigned char sTimeaeusTheUnitedMagicalDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/timeaeus_the_united_magical_dragon.huff");
static const unsigned short sTimeaeusTheUnitedMagicalDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/timeaeus_the_united_magical_dragon.gbapal");
static const unsigned char sTimeaeusTheUnitedMagicalDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/timeaeus_the_united_magical_dragon.lz");

static const unsigned char sTimeausTheUnitedDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/timeaus_the_united_dragon.huff");
static const unsigned short sTimeausTheUnitedDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/timeaus_the_united_dragon.gbapal");
static const unsigned char sTimeausTheUnitedDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/timeaus_the_united_dragon.lz");

static const unsigned char sTohushaddollGrystaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/tohushaddoll_grysta.huff");
static const unsigned short sTohushaddollGrystaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/tohushaddoll_grysta.gbapal");
static const unsigned char sTohushaddollGrystaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/tohushaddoll_grysta.lz");

static const unsigned char sTrapTrickBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/trap_trick.huff");
static const unsigned short sTrapTrickBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/trap_trick.gbapal");
static const unsigned char sTrapTrickMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/trap_trick.lz");

static const unsigned char sTriangleEcstasySparkBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/triangle_ecstasy_spark.huff");
static const unsigned short sTriangleEcstasySparkBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/triangle_ecstasy_spark.gbapal");
static const unsigned char sTriangleEcstasySparkMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/triangle_ecstasy_spark.lz");

static const unsigned char sUltraPolymerizationBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ultra_polymerization.huff");
static const unsigned short sUltraPolymerizationBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ultra_polymerization.gbapal");
static const unsigned char sUltraPolymerizationMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ultra_polymerization.lz");

static const unsigned char sVennominagaTheDeityOfPoisonousSnakesBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vennominaga_the_deity_of_poisonous_snakes.huff");
static const unsigned short sVennominagaTheDeityOfPoisonousSnakesBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vennominaga_the_deity_of_poisonous_snakes.gbapal");
static const unsigned char sVennominagaTheDeityOfPoisonousSnakesMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vennominaga_the_deity_of_poisonous_snakes.lz");

static const unsigned char sVennominonTheKingOfPoisonousSnakesBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vennominon_the_king_of_poisonous_snakes.huff");
static const unsigned short sVennominonTheKingOfPoisonousSnakesBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vennominon_the_king_of_poisonous_snakes.gbapal");
static const unsigned char sVennominonTheKingOfPoisonousSnakesMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vennominon_the_king_of_poisonous_snakes.lz");

static const unsigned char sVenomBoaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/venom_boa.huff");
static const unsigned short sVenomBoaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/venom_boa.gbapal");
static const unsigned char sVenomBoaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/venom_boa.lz");

static const unsigned char sVenomBurnBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/venom_burn.huff");
static const unsigned short sVenomBurnBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/venom_burn.gbapal");
static const unsigned char sVenomBurnMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/venom_burn.lz");

static const unsigned char sVenomCobraBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/venom_cobra.huff");
static const unsigned short sVenomCobraBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/venom_cobra.gbapal");
static const unsigned char sVenomCobraMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/venom_cobra.lz");

static const unsigned char sVenomSerpentBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/venom_serpent.huff");
static const unsigned short sVenomSerpentBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/venom_serpent.gbapal");
static const unsigned char sVenomSerpentMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/venom_serpent.lz");

static const unsigned char sVenomShotBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/venom_shot.huff");
static const unsigned short sVenomShotBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/venom_shot.gbapal");
static const unsigned char sVenomShotMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/venom_shot.lz");

static const unsigned char sVenomSnakeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/venom_snake.huff");
static const unsigned short sVenomSnakeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/venom_snake.gbapal");
static const unsigned char sVenomSnakeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/venom_snake.lz");

static const unsigned char sVenomSwampBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/venom_swamp.huff");
static const unsigned short sVenomSwampBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/venom_swamp.gbapal");
static const unsigned char sVenomSwampMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/venom_swamp.lz");

static const unsigned char sVipersRebirthBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vipers_rebirth.huff");
static const unsigned short sVipersRebirthBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vipers_rebirth.gbapal");
static const unsigned char sVipersRebirthMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vipers_rebirth.lz");

static const unsigned char sYamorimoriBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/yamorimori.huff");
static const unsigned short sYamorimoriBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/yamorimori.gbapal");
static const unsigned char sYamorimoriMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/yamorimori.lz");

static const unsigned char sYowieBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/yowie.huff");
static const unsigned short sYowieBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/yowie.gbapal");
static const unsigned char sYowieMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/yowie.lz");

static const unsigned char sAceOfSwordBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ace_of_sword.huff");
static const unsigned short sAceOfSwordBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ace_of_sword.gbapal");
static const unsigned char sAceOfSwordMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ace_of_sword.lz");

static const unsigned char sAceOfWandBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ace_of_wand.huff");
static const unsigned short sAceOfWandBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ace_of_wand.gbapal");
static const unsigned char sAceOfWandMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ace_of_wand.lz");

static const unsigned char sArcanaCallBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_call.huff");
static const unsigned short sArcanaCallBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_call.gbapal");
static const unsigned char sArcanaCallMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_call.lz");

static const unsigned char sArcanaForce0TheFoolBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_0_the_fool.huff");
static const unsigned short sArcanaForce0TheFoolBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_0_the_fool.gbapal");
static const unsigned char sArcanaForce0TheFoolMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_0_the_fool.lz");

static const unsigned char sArcanaForceExTheDarkRulerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_ex_the_dark_ruler.huff");
static const unsigned short sArcanaForceExTheDarkRulerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_ex_the_dark_ruler.gbapal");
static const unsigned char sArcanaForceExTheDarkRulerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_ex_the_dark_ruler.lz");

static const unsigned char sArcanaForceExTheLightRulerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_ex_the_light_ruler.huff");
static const unsigned short sArcanaForceExTheLightRulerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_ex_the_light_ruler.gbapal");
static const unsigned char sArcanaForceExTheLightRulerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_ex_the_light_ruler.lz");

static const unsigned char sArcanaForceITheMagicianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_i_the_magician.huff");
static const unsigned short sArcanaForceITheMagicianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_i_the_magician.gbapal");
static const unsigned char sArcanaForceITheMagicianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_i_the_magician.lz");

static const unsigned char sArcanaForceIiiTheEmpressBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_iii_the_empress.huff");
static const unsigned short sArcanaForceIiiTheEmpressBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_iii_the_empress.gbapal");
static const unsigned char sArcanaForceIiiTheEmpressMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_iii_the_empress.lz");

static const unsigned char sArcanaForceIvTheEmperorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_iv_the_emperor.huff");
static const unsigned short sArcanaForceIvTheEmperorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_iv_the_emperor.gbapal");
static const unsigned char sArcanaForceIvTheEmperorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_iv_the_emperor.lz");

static const unsigned char sArcanaForceTheChaosRulerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_the_chaos_ruler.huff");
static const unsigned short sArcanaForceTheChaosRulerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_the_chaos_ruler.gbapal");
static const unsigned char sArcanaForceTheChaosRulerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_the_chaos_ruler.lz");

static const unsigned char sArcanaForceVTheHierophantBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_v_the_hierophant.huff");
static const unsigned short sArcanaForceVTheHierophantBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_v_the_hierophant.gbapal");
static const unsigned char sArcanaForceVTheHierophantMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_v_the_hierophant.lz");

static const unsigned char sArcanaForceViTheLoversBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_vi_the_lovers.huff");
static const unsigned short sArcanaForceViTheLoversBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_vi_the_lovers.gbapal");
static const unsigned char sArcanaForceViTheLoversMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_vi_the_lovers.lz");

static const unsigned char sArcanaForceViiTheChariotBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_vii_the_chariot.huff");
static const unsigned short sArcanaForceViiTheChariotBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_vii_the_chariot.gbapal");
static const unsigned char sArcanaForceViiTheChariotMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_vii_the_chariot.lz");

static const unsigned char sArcanaForceViiiTheStrengthBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_viii_the_strength.huff");
static const unsigned short sArcanaForceViiiTheStrengthBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_viii_the_strength.gbapal");
static const unsigned char sArcanaForceViiiTheStrengthMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_viii_the_strength.lz");

static const unsigned char sArcanaForceXiiTheHangmanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_xii_the_hangman.huff");
static const unsigned short sArcanaForceXiiTheHangmanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_xii_the_hangman.gbapal");
static const unsigned char sArcanaForceXiiTheHangmanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_xii_the_hangman.lz");

static const unsigned char sArcanaForceXivTemperanceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_xiv_temperance.huff");
static const unsigned short sArcanaForceXivTemperanceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_xiv_temperance.gbapal");
static const unsigned char sArcanaForceXivTemperanceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_xiv_temperance.lz");

static const unsigned char sArcanaForceXixTheSunBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_xix_the_sun.huff");
static const unsigned short sArcanaForceXixTheSunBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_xix_the_sun.gbapal");
static const unsigned char sArcanaForceXixTheSunMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_xix_the_sun.lz");

static const unsigned char sArcanaForceXvTheFiendBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_xv_the_fiend.huff");
static const unsigned short sArcanaForceXvTheFiendBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_xv_the_fiend.gbapal");
static const unsigned char sArcanaForceXvTheFiendMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_xv_the_fiend.lz");

static const unsigned char sArcanaForceXviiiTheMoonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_xviii_the_moon.huff");
static const unsigned short sArcanaForceXviiiTheMoonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_xviii_the_moon.gbapal");
static const unsigned char sArcanaForceXviiiTheMoonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_xviii_the_moon.lz");

static const unsigned char sArcanaForceXxiTheWorldBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_force_xxi_the_world.huff");
static const unsigned short sArcanaForceXxiTheWorldBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_force_xxi_the_world.gbapal");
static const unsigned char sArcanaForceXxiTheWorldMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_force_xxi_the_world.lz");

static const unsigned char sArcanaReadingBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_reading.huff");
static const unsigned short sArcanaReadingBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_reading.gbapal");
static const unsigned char sArcanaReadingMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_reading.lz");

static const unsigned char sArcanaSpreadBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_spread.huff");
static const unsigned short sArcanaSpreadBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_spread.gbapal");
static const unsigned char sArcanaSpreadMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_spread.lz");

static const unsigned char sArmedNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/armed_neos.huff");
static const unsigned short sArmedNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/armed_neos.gbapal");
static const unsigned char sArmedNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/armed_neos.lz");

static const unsigned char sAurkusLightswornDruidBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/aurkus_lightsworn_druid.huff");
static const unsigned short sAurkusLightswornDruidBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/aurkus_lightsworn_druid.gbapal");
static const unsigned char sAurkusLightswornDruidMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/aurkus_lightsworn_druid.lz");

static const unsigned char sCelestiaLightswornAngelBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/celestia_lightsworn_angel.huff");
static const unsigned short sCelestiaLightswornAngelBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/celestia_lightsworn_angel.gbapal");
static const unsigned char sCelestiaLightswornAngelMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/celestia_lightsworn_angel.lz");

static const unsigned char sChargeOfTheLightBrigadeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/charge_of_the_light_brigade.huff");
static const unsigned short sChargeOfTheLightBrigadeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/charge_of_the_light_brigade.gbapal");
static const unsigned char sChargeOfTheLightBrigadeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/charge_of_the_light_brigade.lz");

static const unsigned char sChrysalisChickyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chrysalis_chicky.huff");
static const unsigned short sChrysalisChickyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chrysalis_chicky.gbapal");
static const unsigned char sChrysalisChickyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chrysalis_chicky.lz");

static const unsigned char sChrysalisDolphinBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chrysalis_dolphin.huff");
static const unsigned short sChrysalisDolphinBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chrysalis_dolphin.gbapal");
static const unsigned char sChrysalisDolphinMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chrysalis_dolphin.lz");

static const unsigned char sChrysalisMoleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chrysalis_mole.huff");
static const unsigned short sChrysalisMoleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chrysalis_mole.gbapal");
static const unsigned char sChrysalisMoleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chrysalis_mole.lz");

static const unsigned char sChrysalisPantailBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chrysalis_pantail.huff");
static const unsigned short sChrysalisPantailBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chrysalis_pantail.gbapal");
static const unsigned char sChrysalisPantailMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chrysalis_pantail.lz");

static const unsigned char sChrysalisPinnyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/chrysalis_pinny.huff");
static const unsigned short sChrysalisPinnyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/chrysalis_pinny.gbapal");
static const unsigned char sChrysalisPinnyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/chrysalis_pinny.lz");

static const unsigned char sCocoonPartyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cocoon_party.huff");
static const unsigned short sCocoonPartyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cocoon_party.gbapal");
static const unsigned char sCocoonPartyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cocoon_party.lz");

static const unsigned char sCocoonRebirthBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cocoon_rebirth.huff");
static const unsigned short sCocoonRebirthBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cocoon_rebirth.gbapal");
static const unsigned char sCocoonRebirthMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cocoon_rebirth.lz");

static const unsigned char sColosseumCageOfTheGladiatorBeastsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/colosseum_cage_of_the_gladiator_beasts.huff");
static const unsigned short sColosseumCageOfTheGladiatorBeastsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/colosseum_cage_of_the_gladiator_beasts.gbapal");
static const unsigned char sColosseumCageOfTheGladiatorBeastsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/colosseum_cage_of_the_gladiator_beasts.lz");

static const unsigned char sContactBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/contact.huff");
static const unsigned short sContactBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/contact.gbapal");
static const unsigned char sContactMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/contact.lz");

static const unsigned char sContactGateBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/contact_gate.huff");
static const unsigned short sContactGateBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/contact_gate.gbapal");
static const unsigned char sContactGateMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/contact_gate.lz");

static const unsigned char sConvertContactBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/convert_contact.huff");
static const unsigned short sConvertContactBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/convert_contact.gbapal");
static const unsigned char sConvertContactMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/convert_contact.lz");

static const unsigned char sCrossKeeperBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/cross_keeper.huff");
static const unsigned short sCrossKeeperBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/cross_keeper.gbapal");
static const unsigned char sCrossKeeperMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/cross_keeper.lz");

static const unsigned char sCuriousTheLightswornDominionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/curious_the_lightsworn_dominion.huff");
static const unsigned short sCuriousTheLightswornDominionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/curious_the_lightsworn_dominion.gbapal");
static const unsigned char sCuriousTheLightswornDominionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/curious_the_lightsworn_dominion.lz");

static const unsigned char sEhrenLightswornMonkBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ehren_lightsworn_monk.huff");
static const unsigned short sEhrenLightswornMonkBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ehren_lightsworn_monk.gbapal");
static const unsigned char sEhrenLightswornMonkMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ehren_lightsworn_monk.lz");

static const unsigned char sElementalHeroAirNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_air_neos.huff");
static const unsigned short sElementalHeroAirNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_air_neos.gbapal");
static const unsigned char sElementalHeroAirNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_air_neos.lz");

static const unsigned char sElementalHeroAquaNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_aqua_neos.huff");
static const unsigned short sElementalHeroAquaNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_aqua_neos.gbapal");
static const unsigned char sElementalHeroAquaNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_aqua_neos.lz");

static const unsigned char sElementalHeroBraveNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_brave_neos.huff");
static const unsigned short sElementalHeroBraveNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_brave_neos.gbapal");
static const unsigned char sElementalHeroBraveNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_brave_neos.lz");

static const unsigned char sElementalHeroChaosNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_chaos_neos.huff");
static const unsigned short sElementalHeroChaosNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_chaos_neos.gbapal");
static const unsigned char sElementalHeroChaosNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_chaos_neos.lz");

static const unsigned char sElementalHeroCosmoNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_cosmo_neos.huff");
static const unsigned short sElementalHeroCosmoNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_cosmo_neos.gbapal");
static const unsigned char sElementalHeroCosmoNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_cosmo_neos.lz");

static const unsigned char sElementalHeroDarkNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_dark_neos.huff");
static const unsigned short sElementalHeroDarkNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_dark_neos.gbapal");
static const unsigned char sElementalHeroDarkNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_dark_neos.lz");

static const unsigned char sElementalHeroFlareNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_flare_neos.huff");
static const unsigned short sElementalHeroFlareNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_flare_neos.gbapal");
static const unsigned char sElementalHeroFlareNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_flare_neos.lz");

static const unsigned char sElementalHeroGlowNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_glow_neos.huff");
static const unsigned short sElementalHeroGlowNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_glow_neos.gbapal");
static const unsigned char sElementalHeroGlowNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_glow_neos.lz");

static const unsigned char sElementalHeroGrandNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_grand_neos.huff");
static const unsigned short sElementalHeroGrandNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_grand_neos.gbapal");
static const unsigned char sElementalHeroGrandNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_grand_neos.lz");

static const unsigned char sElementalHeroMagmaNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_magma_neos.huff");
static const unsigned short sElementalHeroMagmaNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_magma_neos.gbapal");
static const unsigned char sElementalHeroMagmaNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_magma_neos.lz");

static const unsigned char sElementalHeroMarineNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_marine_neos.huff");
static const unsigned short sElementalHeroMarineNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_marine_neos.gbapal");
static const unsigned char sElementalHeroMarineNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_marine_neos.lz");

static const unsigned char sElementalHeroNebulaNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_nebula_neos.huff");
static const unsigned short sElementalHeroNebulaNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_nebula_neos.gbapal");
static const unsigned char sElementalHeroNebulaNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_nebula_neos.lz");

static const unsigned char sElementalHeroShiningNeosWingmanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_shining_neos_wingman.huff");
static const unsigned short sElementalHeroShiningNeosWingmanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_shining_neos_wingman.gbapal");
static const unsigned char sElementalHeroShiningNeosWingmanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_shining_neos_wingman.lz");

static const unsigned char sElementalHeroSpiritOfNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_spirit_of_neos.huff");
static const unsigned short sElementalHeroSpiritOfNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_spirit_of_neos.gbapal");
static const unsigned char sElementalHeroSpiritOfNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_spirit_of_neos.lz");

static const unsigned char sElementalHeroStormNeosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/elemental_hero_storm_neos.huff");
static const unsigned short sElementalHeroStormNeosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/elemental_hero_storm_neos.gbapal");
static const unsigned char sElementalHeroStormNeosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/elemental_hero_storm_neos.lz");

static const unsigned char sEnEngageNeoSpaceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/en_engage_neo_space.huff");
static const unsigned short sEnEngageNeoSpaceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/en_engage_neo_space.gbapal");
static const unsigned char sEnEngageNeoSpaceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/en_engage_neo_space.lz");

static const unsigned char sEnShuffleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/en_shuffle.huff");
static const unsigned short sEnShuffleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/en_shuffle.gbapal");
static const unsigned char sEnShuffleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/en_shuffle.lz");

static const unsigned char sEnWaveBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/en_wave.huff");
static const unsigned short sEnWaveBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/en_wave.gbapal");
static const unsigned char sEnWaveMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/en_wave.lz");

static const unsigned char sEnlightenmentDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/enlightenment_dragon.huff");
static const unsigned short sEnlightenmentDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/enlightenment_dragon.gbapal");
static const unsigned char sEnlightenmentDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/enlightenment_dragon.lz");

static const unsigned char sFavouriteContactBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/favourite_contact.huff");
static const unsigned short sFavouriteContactBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/favourite_contact.gbapal");
static const unsigned char sFavouriteContactMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/favourite_contact.lz");

static const unsigned char sFelisLightswornArcherBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/felis_lightsworn_archer.huff");
static const unsigned short sFelisLightswornArcherBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/felis_lightsworn_archer.gbapal");
static const unsigned char sFelisLightswornArcherMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/felis_lightsworn_archer.lz");

static const unsigned char sFlavianColosseumOfTheGladiatorBeastsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/flavian_colosseum_of_the_gladiator_beasts.huff");
static const unsigned short sFlavianColosseumOfTheGladiatorBeastsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/flavian_colosseum_of_the_gladiator_beasts.gbapal");
static const unsigned char sFlavianColosseumOfTheGladiatorBeastsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/flavian_colosseum_of_the_gladiator_beasts.lz");

static const unsigned char sGaronithLightswornDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/garonith_lightsworn_dragon.huff");
static const unsigned short sGaronithLightswornDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/garonith_lightsworn_dragon.gbapal");
static const unsigned char sGaronithLightswornDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/garonith_lightsworn_dragon.lz");

static const unsigned char sGarothLightswornWarriorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/garoth_lightsworn_warrior.huff");
static const unsigned short sGarothLightswornWarriorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/garoth_lightsworn_warrior.gbapal");
static const unsigned char sGarothLightswornWarriorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/garoth_lightsworn_warrior.lz");

static const unsigned char sGenerationNextBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/generation_next.huff");
static const unsigned short sGenerationNextBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/generation_next.gbapal");
static const unsigned char sGenerationNextMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/generation_next.lz");

static const unsigned char sGladiatorBeastAlexanderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_alexander.huff");
static const unsigned short sGladiatorBeastAlexanderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_alexander.gbapal");
static const unsigned char sGladiatorBeastAlexanderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_alexander.lz");

static const unsigned char sGladiatorBeastAndabataBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_andabata.huff");
static const unsigned short sGladiatorBeastAndabataBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_andabata.gbapal");
static const unsigned char sGladiatorBeastAndabataMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_andabata.lz");

static const unsigned char sGladiatorBeastAndalBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_andal.huff");
static const unsigned short sGladiatorBeastAndalBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_andal.gbapal");
static const unsigned char sGladiatorBeastAndalMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_andal.lz");

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

static const unsigned char sGladiatorBeastDareiosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_dareios.huff");
static const unsigned short sGladiatorBeastDareiosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_dareios.gbapal");
static const unsigned char sGladiatorBeastDareiosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_dareios.lz");

static const unsigned char sGladiatorBeastDariusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_darius.huff");
static const unsigned short sGladiatorBeastDariusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_darius.gbapal");
static const unsigned char sGladiatorBeastDariusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_darius.lz");

static const unsigned char sGladiatorBeastDimacariBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_dimacari.huff");
static const unsigned short sGladiatorBeastDimacariBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_dimacari.gbapal");
static const unsigned char sGladiatorBeastDimacariMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_dimacari.lz");

static const unsigned char sGladiatorBeastDomitianusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_domitianus.huff");
static const unsigned short sGladiatorBeastDomitianusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_domitianus.gbapal");
static const unsigned char sGladiatorBeastDomitianusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_domitianus.lz");

static const unsigned char sGladiatorBeastDragasesBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_dragases.huff");
static const unsigned short sGladiatorBeastDragasesBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_dragases.gbapal");
static const unsigned char sGladiatorBeastDragasesMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_dragases.lz");

static const unsigned char sGladiatorBeastEquesteBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_equeste.huff");
static const unsigned short sGladiatorBeastEquesteBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_equeste.gbapal");
static const unsigned char sGladiatorBeastEquesteMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_equeste.lz");

static const unsigned char sGladiatorBeastEssedariiBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_essedarii.huff");
static const unsigned short sGladiatorBeastEssedariiBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_essedarii.gbapal");
static const unsigned char sGladiatorBeastEssedariiMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_essedarii.lz");

static const unsigned char sGladiatorBeastGaiodiazBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_gaiodiaz.huff");
static const unsigned short sGladiatorBeastGaiodiazBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_gaiodiaz.gbapal");
static const unsigned char sGladiatorBeastGaiodiazMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_gaiodiaz.lz");

static const unsigned char sGladiatorBeastGistelBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_gistel.huff");
static const unsigned short sGladiatorBeastGistelBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_gistel.gbapal");
static const unsigned char sGladiatorBeastGistelMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_gistel.lz");

static const unsigned char sGladiatorBeastGyzarusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_gyzarus.huff");
static const unsigned short sGladiatorBeastGyzarusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_gyzarus.gbapal");
static const unsigned char sGladiatorBeastGyzarusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_gyzarus.lz");

static const unsigned char sGladiatorBeastHeraklinosBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_heraklinos.huff");
static const unsigned short sGladiatorBeastHeraklinosBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_heraklinos.gbapal");
static const unsigned char sGladiatorBeastHeraklinosMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_heraklinos.lz");

static const unsigned char sGladiatorBeastHoplomusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_hoplomus.huff");
static const unsigned short sGladiatorBeastHoplomusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_hoplomus.gbapal");
static const unsigned char sGladiatorBeastHoplomusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_hoplomus.lz");

static const unsigned char sGladiatorBeastLanistaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_lanista.huff");
static const unsigned short sGladiatorBeastLanistaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_lanista.gbapal");
static const unsigned char sGladiatorBeastLanistaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_lanista.lz");

static const unsigned char sGladiatorBeastLaquariBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_laquari.huff");
static const unsigned short sGladiatorBeastLaquariBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_laquari.gbapal");
static const unsigned char sGladiatorBeastLaquariMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_laquari.lz");

static const unsigned char sGladiatorBeastMurmilloBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_murmillo.huff");
static const unsigned short sGladiatorBeastMurmilloBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_murmillo.gbapal");
static const unsigned char sGladiatorBeastMurmilloMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_murmillo.lz");

static const unsigned char sGladiatorBeastNerokiusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_nerokius.huff");
static const unsigned short sGladiatorBeastNerokiusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_nerokius.gbapal");
static const unsigned char sGladiatorBeastNerokiusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_nerokius.lz");

static const unsigned char sGladiatorBeastNoxiousBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_noxious.huff");
static const unsigned short sGladiatorBeastNoxiousBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_noxious.gbapal");
static const unsigned char sGladiatorBeastNoxiousMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_noxious.lz");

static const unsigned char sGladiatorBeastOctaviusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_octavius.huff");
static const unsigned short sGladiatorBeastOctaviusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_octavius.gbapal");
static const unsigned char sGladiatorBeastOctaviusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_octavius.lz");

static const unsigned char sGladiatorBeastRetiariBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_retiari.huff");
static const unsigned short sGladiatorBeastRetiariBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_retiari.gbapal");
static const unsigned char sGladiatorBeastRetiariMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_retiari.lz");

static const unsigned char sGladiatorBeastSagittariiBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_sagittarii.huff");
static const unsigned short sGladiatorBeastSagittariiBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_sagittarii.gbapal");
static const unsigned char sGladiatorBeastSagittariiMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_sagittarii.lz");

static const unsigned char sGladiatorBeastSamniteBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_samnite.huff");
static const unsigned short sGladiatorBeastSamniteBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_samnite.gbapal");
static const unsigned char sGladiatorBeastSamniteMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_samnite.lz");

static const unsigned char sGladiatorBeastSecutorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_secutor.huff");
static const unsigned short sGladiatorBeastSecutorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_secutor.gbapal");
static const unsigned char sGladiatorBeastSecutorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_secutor.lz");

static const unsigned char sGladiatorBeastSpartacusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_spartacus.huff");
static const unsigned short sGladiatorBeastSpartacusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_spartacus.gbapal");
static const unsigned char sGladiatorBeastSpartacusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_spartacus.lz");

static const unsigned char sGladiatorBeastTamerEditorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_tamer_editor.huff");
static const unsigned short sGladiatorBeastTamerEditorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_tamer_editor.gbapal");
static const unsigned char sGladiatorBeastTamerEditorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_tamer_editor.lz");

static const unsigned char sGladiatorBeastToraxBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_torax.huff");
static const unsigned short sGladiatorBeastToraxBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_torax.gbapal");
static const unsigned char sGladiatorBeastToraxMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_torax.lz");

static const unsigned char sGladiatorBeastTygeriusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_tygerius.huff");
static const unsigned short sGladiatorBeastTygeriusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_tygerius.gbapal");
static const unsigned char sGladiatorBeastTygeriusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_tygerius.lz");

static const unsigned char sGladiatorBeastVespasiusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_vespasius.huff");
static const unsigned short sGladiatorBeastVespasiusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_vespasius.gbapal");
static const unsigned char sGladiatorBeastVespasiusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_vespasius.lz");

static const unsigned char sGladiatorBeastWarChariotBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beast_war_chariot.huff");
static const unsigned short sGladiatorBeastWarChariotBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beast_war_chariot.gbapal");
static const unsigned char sGladiatorBeastWarChariotMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beast_war_chariot.lz");

static const unsigned char sGladiatorBeastsBattleArchfiendShieldBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beasts_battle_archfiend_shield.huff");
static const unsigned short sGladiatorBeastsBattleArchfiendShieldBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beasts_battle_archfiend_shield.gbapal");
static const unsigned char sGladiatorBeastsBattleArchfiendShieldMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beasts_battle_archfiend_shield.lz");

static const unsigned char sGladiatorBeastsBattleGladiusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beasts_battle_gladius.huff");
static const unsigned short sGladiatorBeastsBattleGladiusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beasts_battle_gladius.gbapal");
static const unsigned char sGladiatorBeastsBattleGladiusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beasts_battle_gladius.lz");

static const unsigned char sGladiatorBeastsBattleManicaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beasts_battle_manica.huff");
static const unsigned short sGladiatorBeastsBattleManicaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beasts_battle_manica.gbapal");
static const unsigned char sGladiatorBeastsBattleManicaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beasts_battle_manica.lz");

static const unsigned char sGladiatorBeastsMedusaShieldBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beasts_medusa_shield.huff");
static const unsigned short sGladiatorBeastsMedusaShieldBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beasts_medusa_shield.gbapal");
static const unsigned char sGladiatorBeastsMedusaShieldMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beasts_medusa_shield.lz");

static const unsigned char sGladiatorBeastsValorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_beasts_valor.huff");
static const unsigned short sGladiatorBeastsValorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_beasts_valor.gbapal");
static const unsigned char sGladiatorBeastsValorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_beasts_valor.lz");

static const unsigned char sGladiatorNaumachiaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/gladiator_naumachia.huff");
static const unsigned short sGladiatorNaumachiaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/gladiator_naumachia.gbapal");
static const unsigned char sGladiatorNaumachiaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/gladiator_naumachia.lz");

static const unsigned char sGloriousIllusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/glorious_illusion.huff");
static const unsigned short sGloriousIllusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/glorious_illusion.gbapal");
static const unsigned char sGloriousIllusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/glorious_illusion.lz");

static const unsigned char sInstantContactBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/instant_contact.huff");
static const unsigned short sInstantContactBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/instant_contact.gbapal");
static const unsigned char sInstantContactMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/instant_contact.lz");

static const unsigned char sInstantNeoSpaceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/instant_neo_space.huff");
static const unsigned short sInstantNeoSpaceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/instant_neo_space.gbapal");
static const unsigned char sInstantNeoSpaceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/instant_neo_space.lz");

static const unsigned char sJainLightswornPaladinBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/jain_lightsworn_paladin.huff");
static const unsigned short sJainLightswornPaladinBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/jain_lightsworn_paladin.gbapal");
static const unsigned char sJainLightswornPaladinMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/jain_lightsworn_paladin.lz");

static const unsigned char sJainTwilightswornGeneralBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/jain_twilightsworn_general.huff");
static const unsigned short sJainTwilightswornGeneralBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/jain_twilightsworn_general.gbapal");
static const unsigned char sJainTwilightswornGeneralMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/jain_twilightsworn_general.lz");

static const unsigned char sJenisLightswornMenderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/jenis_lightsworn_mender.huff");
static const unsigned short sJenisLightswornMenderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/jenis_lightsworn_mender.gbapal");
static const unsigned char sJenisLightswornMenderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/jenis_lightsworn_mender.lz");

static const unsigned char sJudgmentTheDragonOfHeavenBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/judgment_the_dragon_of_heaven.huff");
static const unsigned short sJudgmentTheDragonOfHeavenBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/judgment_the_dragon_of_heaven.gbapal");
static const unsigned char sJudgmentTheDragonOfHeavenMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/judgment_the_dragon_of_heaven.lz");

static const unsigned char sKnightOfPentaclesBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/knight_of_pentacles.huff");
static const unsigned short sKnightOfPentaclesBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/knight_of_pentacles.gbapal");
static const unsigned char sKnightOfPentaclesMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/knight_of_pentacles.lz");

static const unsigned char sLightBarrierBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/light_barrier.huff");
static const unsigned short sLightBarrierBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/light_barrier.gbapal");
static const unsigned char sLightBarrierMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/light_barrier.lz");

static const unsigned char sLightForceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/light_force.huff");
static const unsigned short sLightForceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/light_force.gbapal");
static const unsigned char sLightForceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/light_force.lz");

static const unsigned char sLightOfDestructionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/light_of_destruction.huff");
static const unsigned short sLightOfDestructionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/light_of_destruction.gbapal");
static const unsigned char sLightOfDestructionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/light_of_destruction.lz");

static const unsigned char sLightSpiralBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/light_spiral.huff");
static const unsigned short sLightSpiralBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/light_spiral.gbapal");
static const unsigned char sLightSpiralMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/light_spiral.lz");

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

static const unsigned char sLuminaLightswornSummonerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lumina_lightsworn_summoner.huff");
static const unsigned short sLuminaLightswornSummonerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lumina_lightsworn_summoner.gbapal");
static const unsigned char sLuminaLightswornSummonerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lumina_lightsworn_summoner.lz");

static const unsigned char sLuminaTwilightswornShamanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lumina_twilightsworn_shaman.huff");
static const unsigned short sLuminaTwilightswornShamanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lumina_twilightsworn_shaman.gbapal");
static const unsigned char sLuminaTwilightswornShamanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lumina_twilightsworn_shaman.lz");

static const unsigned char sLylaLightswornSorceressBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lyla_lightsworn_sorceress.huff");
static const unsigned short sLylaLightswornSorceressBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lyla_lightsworn_sorceress.gbapal");
static const unsigned char sLylaLightswornSorceressMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lyla_lightsworn_sorceress.lz");

static const unsigned char sLylaTwilightswornEnchantressBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/lyla_twilightsworn_enchantress.huff");
static const unsigned short sLylaTwilightswornEnchantressBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/lyla_twilightsworn_enchantress.gbapal");
static const unsigned char sLylaTwilightswornEnchantressMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/lyla_twilightsworn_enchantress.lz");

static const unsigned char sMarchOfTheDarkBrigadeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/march_of_the_dark_brigade.huff");
static const unsigned short sMarchOfTheDarkBrigadeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/march_of_the_dark_brigade.gbapal");
static const unsigned char sMarchOfTheDarkBrigadeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/march_of_the_dark_brigade.lz");

static const unsigned char sMichaelTheArchLightswornBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/michael_the_arch_lightsworn.huff");
static const unsigned short sMichaelTheArchLightswornBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/michael_the_arch_lightsworn.gbapal");
static const unsigned char sMichaelTheArchLightswornMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/michael_the_arch_lightsworn.lz");

static const unsigned char sMinervaLightswornMaidenBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/minerva_lightsworn_maiden.huff");
static const unsigned short sMinervaLightswornMaidenBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/minerva_lightsworn_maiden.gbapal");
static const unsigned char sMinervaLightswornMaidenMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/minerva_lightsworn_maiden.lz");

static const unsigned char sMinervaTheAthenianLightswornBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/minerva_the_athenian_lightsworn.huff");
static const unsigned short sMinervaTheAthenianLightswornBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/minerva_the_athenian_lightsworn.gbapal");
static const unsigned char sMinervaTheAthenianLightswornMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/minerva_the_athenian_lightsworn.lz");

static const unsigned char sMinervaTheExhaltedLightswornBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/minerva_the_exhalted_lightsworn.huff");
static const unsigned short sMinervaTheExhaltedLightswornBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/minerva_the_exhalted_lightsworn.gbapal");
static const unsigned char sMinervaTheExhaltedLightswornMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/minerva_the_exhalted_lightsworn.lz");

static const unsigned char sMiracleContactBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/miracle_contact.huff");
static const unsigned short sMiracleContactBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/miracle_contact.gbapal");
static const unsigned char sMiracleContactMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/miracle_contact.lz");

static const unsigned char sMoonTokenBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/moon_token.huff");
static const unsigned short sMoonTokenBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/moon_token.gbapal");
static const unsigned char sMoonTokenMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/moon_token.lz");

static const unsigned char sNeoSpaceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_space.huff");
static const unsigned short sNeoSpaceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_space.gbapal");
static const unsigned char sNeoSpaceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_space.lz");

static const unsigned char sNeoSpaceConnectorBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_space_connector.huff");
static const unsigned short sNeoSpaceConnectorBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_space_connector.gbapal");
static const unsigned char sNeoSpaceConnectorMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_space_connector.lz");

static const unsigned char sNeoSpacianAirHummingbirdBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_spacian_air_hummingbird.huff");
static const unsigned short sNeoSpacianAirHummingbirdBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_spacian_air_hummingbird.gbapal");
static const unsigned char sNeoSpacianAirHummingbirdMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_spacian_air_hummingbird.lz");

static const unsigned char sNeoSpacianAquaDolphinBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_spacian_aqua_dolphin.huff");
static const unsigned short sNeoSpacianAquaDolphinBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_spacian_aqua_dolphin.gbapal");
static const unsigned char sNeoSpacianAquaDolphinMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_spacian_aqua_dolphin.lz");

static const unsigned char sNeoSpacianDarkPantherBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_spacian_dark_panther.huff");
static const unsigned short sNeoSpacianDarkPantherBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_spacian_dark_panther.gbapal");
static const unsigned char sNeoSpacianDarkPantherMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_spacian_dark_panther.lz");

static const unsigned char sNeoSpacianFlareScarabBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_spacian_flare_scarab.huff");
static const unsigned short sNeoSpacianFlareScarabBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_spacian_flare_scarab.gbapal");
static const unsigned char sNeoSpacianFlareScarabMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_spacian_flare_scarab.lz");

static const unsigned char sNeoSpacianGlowMossBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_spacian_glow_moss.huff");
static const unsigned short sNeoSpacianGlowMossBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_spacian_glow_moss.gbapal");
static const unsigned char sNeoSpacianGlowMossMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_spacian_glow_moss.lz");

static const unsigned char sNeoSpacianGrandMoleBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_spacian_grand_mole.huff");
static const unsigned short sNeoSpacianGrandMoleBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_spacian_grand_mole.gbapal");
static const unsigned char sNeoSpacianGrandMoleMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_spacian_grand_mole.lz");

static const unsigned char sNeoSpacianMarineDolphinBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_spacian_marine_dolphin.huff");
static const unsigned short sNeoSpacianMarineDolphinBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_spacian_marine_dolphin.gbapal");
static const unsigned char sNeoSpacianMarineDolphinMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_spacian_marine_dolphin.lz");

static const unsigned char sNeoSpacianTwinkleMossBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/neo_spacian_twinkle_moss.huff");
static const unsigned short sNeoSpacianTwinkleMossBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/neo_spacian_twinkle_moss.gbapal");
static const unsigned char sNeoSpacianTwinkleMossMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/neo_spacian_twinkle_moss.lz");

static const unsigned char sNexBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/nex.huff");
static const unsigned short sNexBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/nex.gbapal");
static const unsigned char sNexMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/nex.lz");

static const unsigned char sNextBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/next.huff");
static const unsigned short sNextBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/next.gbapal");
static const unsigned char sNextMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/next.lz");

static const unsigned char sPentacleOfAceBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/pentacle_of_ace.huff");
static const unsigned short sPentacleOfAceBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/pentacle_of_ace.gbapal");
static const unsigned char sPentacleOfAceMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/pentacle_of_ace.lz");

static const unsigned char sPunishmentDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/punishment_dragon.huff");
static const unsigned short sPunishmentDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/punishment_dragon.gbapal");
static const unsigned char sPunishmentDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/punishment_dragon.lz");

static const unsigned char sRaidenHandOfTheLightswornBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/raiden_hand_of_the_lightsworn.huff");
static const unsigned short sRaidenHandOfTheLightswornBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/raiden_hand_of_the_lightsworn.gbapal");
static const unsigned char sRaidenHandOfTheLightswornMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/raiden_hand_of_the_lightsworn.lz");

static const unsigned char sRealmOfLightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/realm_of_light.huff");
static const unsigned short sRealmOfLightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/realm_of_light.gbapal");
static const unsigned char sRealmOfLightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/realm_of_light.lz");

static const unsigned char sRescueCatBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/rescue_cat.huff");
static const unsigned short sRescueCatBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/rescue_cat.gbapal");
static const unsigned char sRescueCatMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/rescue_cat.lz");

static const unsigned char sRescueRabbitBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/rescue_rabbit.huff");
static const unsigned short sRescueRabbitBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/rescue_rabbit.gbapal");
static const unsigned char sRescueRabbitMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/rescue_rabbit.lz");

static const unsigned char sReversalOfFateBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/reversal_of_fate.huff");
static const unsigned short sReversalOfFateBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/reversal_of_fate.gbapal");
static const unsigned char sReversalOfFateMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/reversal_of_fate.lz");

static const unsigned char sRinyanLightswornRogueBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/rinyan_lightsworn_rogue.huff");
static const unsigned short sRinyanLightswornRogueBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/rinyan_lightsworn_rogue.gbapal");
static const unsigned char sRinyanLightswornRogueMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/rinyan_lightsworn_rogue.lz");

static const unsigned char sRykoLightswornHunterBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ryko_lightsworn_hunter.huff");
static const unsigned short sRykoLightswornHunterBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ryko_lightsworn_hunter.gbapal");
static const unsigned char sRykoLightswornHunterMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ryko_lightsworn_hunter.lz");

static const unsigned char sRykoTwilightswornFighterBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ryko_twilightsworn_fighter.huff");
static const unsigned short sRykoTwilightswornFighterBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ryko_twilightsworn_fighter.gbapal");
static const unsigned char sRykoTwilightswornFighterMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ryko_twilightsworn_fighter.lz");

static const unsigned char sShireLightswornSpiritBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/shire_lightsworn_spirit.huff");
static const unsigned short sShireLightswornSpiritBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/shire_lightsworn_spirit.gbapal");
static const unsigned char sShireLightswornSpiritMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/shire_lightsworn_spirit.lz");

static const unsigned char sSolarRechargeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/solar_recharge.huff");
static const unsigned short sSolarRechargeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/solar_recharge.gbapal");
static const unsigned char sSolarRechargeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/solar_recharge.lz");

static const unsigned char sSuitOfSwordXBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/suit_of_sword_x.huff");
static const unsigned short sSuitOfSwordXBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/suit_of_sword_x.gbapal");
static const unsigned char sSuitOfSwordXMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/suit_of_sword_x.lz");

static const unsigned char sTestBearBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/test_bear.huff");
static const unsigned short sTestBearBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/test_bear.gbapal");
static const unsigned char sTestBearMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/test_bear.lz");

static const unsigned char sTestPantherBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/test_panther.huff");
static const unsigned short sTestPantherBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/test_panther.gbapal");
static const unsigned char sTestPantherMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/test_panther.lz");

static const unsigned char sTestTigerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/test_tiger.huff");
static const unsigned short sTestTigerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/test_tiger.gbapal");
static const unsigned char sTestTigerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/test_tiger.lz");

static const unsigned char sThumbsDownBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/thumbs_down.huff");
static const unsigned short sThumbsDownBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/thumbs_down.gbapal");
static const unsigned char sThumbsDownMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/thumbs_down.lz");

static const unsigned char sTourOfDoomBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/tour_of_doom.huff");
static const unsigned short sTourOfDoomBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/tour_of_doom.gbapal");
static const unsigned char sTourOfDoomMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/tour_of_doom.lz");

static const unsigned char sTrojanGladiatorBeastBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/trojan_gladiator_beast.huff");
static const unsigned short sTrojanGladiatorBeastBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/trojan_gladiator_beast.gbapal");
static const unsigned char sTrojanGladiatorBeastMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/trojan_gladiator_beast.lz");

static const unsigned char sTwilightClothBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/twilight_cloth.huff");
static const unsigned short sTwilightClothBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/twilight_cloth.gbapal");
static const unsigned char sTwilightClothMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/twilight_cloth.lz");

static const unsigned char sTwilightEraserBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/twilight_eraser.huff");
static const unsigned short sTwilightEraserBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/twilight_eraser.gbapal");
static const unsigned char sTwilightEraserMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/twilight_eraser.lz");

static const unsigned char sTwlightTwinDragonsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/twlight_twin_dragons.huff");
static const unsigned short sTwlightTwinDragonsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/twlight_twin_dragons.gbapal");
static const unsigned char sTwlightTwinDragonsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/twlight_twin_dragons.lz");

static const unsigned char sVanquishingLightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/vanquishing_light.huff");
static const unsigned short sVanquishingLightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/vanquishing_light.gbapal");
static const unsigned char sVanquishingLightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/vanquishing_light.lz");

static const unsigned char sWeissLightswornArchfiendBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/weiss_lightsworn_archfiend.huff");
static const unsigned short sWeissLightswornArchfiendBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/weiss_lightsworn_archfiend.gbapal");
static const unsigned char sWeissLightswornArchfiendMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/weiss_lightsworn_archfiend.lz");

static const unsigned char sWulfLightswornBeastBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/wulf_lightsworn_beast.huff");
static const unsigned short sWulfLightswornBeastBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/wulf_lightsworn_beast.gbapal");
static const unsigned char sWulfLightswornBeastMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/wulf_lightsworn_beast.lz");

static const unsigned char sAllOutAttacksBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/all_out_attacks.huff");
static const unsigned short sAllOutAttacksBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/all_out_attacks.gbapal");
static const unsigned char sAllOutAttacksMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/all_out_attacks.lz");

static const unsigned char sAncientFairyDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_fairy_dragon.huff");
static const unsigned short sAncientFairyDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_fairy_dragon.gbapal");
static const unsigned char sAncientFairyDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_fairy_dragon.lz");

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

static const unsigned char sAncientGearCommanderBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_commander.huff");
static const unsigned short sAncientGearCommanderBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_commander.gbapal");
static const unsigned char sAncientGearCommanderMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_commander.lz");

static const unsigned char sAncientGearDarkGolemBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_dark_golem.huff");
static const unsigned short sAncientGearDarkGolemBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_dark_golem.gbapal");
static const unsigned char sAncientGearDarkGolemMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_dark_golem.lz");

static const unsigned char sAncientGearDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_dragon.huff");
static const unsigned short sAncientGearDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_dragon.gbapal");
static const unsigned char sAncientGearDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_dragon.lz");

static const unsigned char sAncientGearDrillBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_drill.huff");
static const unsigned short sAncientGearDrillBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_drill.gbapal");
static const unsigned char sAncientGearDrillMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_drill.lz");

static const unsigned char sAncientGearDuelBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_duel.huff");
static const unsigned short sAncientGearDuelBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_duel.gbapal");
static const unsigned char sAncientGearDuelMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_duel.lz");

static const unsigned char sAncientGearEngineerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_engineer.huff");
static const unsigned short sAncientGearEngineerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_engineer.gbapal");
static const unsigned char sAncientGearEngineerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_engineer.lz");

static const unsigned char sAncientGearExplosiveBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_explosive.huff");
static const unsigned short sAncientGearExplosiveBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_explosive.gbapal");
static const unsigned char sAncientGearExplosiveMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_explosive.lz");

static const unsigned char sAncientGearFactoryBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_factory.huff");
static const unsigned short sAncientGearFactoryBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_factory.gbapal");
static const unsigned char sAncientGearFactoryMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_factory.lz");

static const unsigned char sAncientGearFistBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_fist.huff");
static const unsigned short sAncientGearFistBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_fist.gbapal");
static const unsigned char sAncientGearFistMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_fist.lz");

static const unsigned char sAncientGearFrameBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_frame.huff");
static const unsigned short sAncientGearFrameBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_frame.gbapal");
static const unsigned char sAncientGearFrameMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_frame.lz");

static const unsigned char sAncientGearFusionBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_fusion.huff");
static const unsigned short sAncientGearFusionBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_fusion.gbapal");
static const unsigned char sAncientGearFusionMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_fusion.lz");

static const unsigned char sAncientGearGadjiltronChimeraBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_gadjiltron_chimera.huff");
static const unsigned short sAncientGearGadjiltronChimeraBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_gadjiltron_chimera.gbapal");
static const unsigned char sAncientGearGadjiltronChimeraMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_gadjiltron_chimera.lz");

static const unsigned char sAncientGearGadjiltronDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_gadjiltron_dragon.huff");
static const unsigned short sAncientGearGadjiltronDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_gadjiltron_dragon.gbapal");
static const unsigned char sAncientGearGadjiltronDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_gadjiltron_dragon.lz");

static const unsigned char sAncientGearGolemBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_golem.huff");
static const unsigned short sAncientGearGolemBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_golem.gbapal");
static const unsigned char sAncientGearGolemMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_golem.lz");

static const unsigned char sAncientGearGolemUltimatePoundBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_golem_ultimate_pound.huff");
static const unsigned short sAncientGearGolemUltimatePoundBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_golem_ultimate_pound.gbapal");
static const unsigned char sAncientGearGolemUltimatePoundMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_golem_ultimate_pound.lz");

static const unsigned char sAncientGearKnightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_knight.huff");
static const unsigned short sAncientGearKnightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_knight.gbapal");
static const unsigned char sAncientGearKnightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_knight.lz");

static const unsigned char sAncientGearMegatonGolemBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_megaton_golem.huff");
static const unsigned short sAncientGearMegatonGolemBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_megaton_golem.gbapal");
static const unsigned char sAncientGearMegatonGolemMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_megaton_golem.lz");

static const unsigned char sAncientGearSoldierBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_soldier.huff");
static const unsigned short sAncientGearSoldierBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_soldier.gbapal");
static const unsigned char sAncientGearSoldierMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_soldier.lz");

static const unsigned char sAncientGearStatueBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_statue.huff");
static const unsigned short sAncientGearStatueBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_statue.gbapal");
static const unsigned char sAncientGearStatueMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_statue.lz");

static const unsigned char sAncientGearTankBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_tank.huff");
static const unsigned short sAncientGearTankBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_tank.gbapal");
static const unsigned char sAncientGearTankMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_tank.lz");

static const unsigned char sAncientGearTankerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_tanker.huff");
static const unsigned short sAncientGearTankerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_tanker.gbapal");
static const unsigned char sAncientGearTankerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_tanker.lz");

static const unsigned char sAncientGearWorkshopBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_gear_workshop.huff");
static const unsigned short sAncientGearWorkshopBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_gear_workshop.gbapal");
static const unsigned char sAncientGearWorkshopMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_gear_workshop.lz");

static const unsigned char sAncientLeafBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_leaf.huff");
static const unsigned short sAncientLeafBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_leaf.gbapal");
static const unsigned char sAncientLeafMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_leaf.lz");

static const unsigned char sAncientSacredWyvernBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/ancient_sacred_wyvern.huff");
static const unsigned short sAncientSacredWyvernBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/ancient_sacred_wyvern.gbapal");
static const unsigned char sAncientSacredWyvernMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/ancient_sacred_wyvern.lz");

static const unsigned char sArcanaKnightJokerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcana_knight_joker.huff");
static const unsigned short sArcanaKnightJokerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcana_knight_joker.gbapal");
static const unsigned char sArcanaKnightJokerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcana_knight_joker.lz");

static const unsigned char sArcaneBarrierBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/arcane_barrier.huff");
static const unsigned short sArcaneBarrierBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/arcane_barrier.gbapal");
static const unsigned char sArcaneBarrierMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/arcane_barrier.lz");

static const unsigned char sArmityleTheChaosPhantasmBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/armityle_the_chaos_phantasm.huff");
static const unsigned short sArmityleTheChaosPhantasmBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/armityle_the_chaos_phantasm.gbapal");
static const unsigned char sArmityleTheChaosPhantasmMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/armityle_the_chaos_phantasm.lz");

static const unsigned char sBabycerasaurusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/babycerasaurus.huff");
static const unsigned short sBabycerasaurusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/babycerasaurus.gbapal");
static const unsigned char sBabycerasaurusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/babycerasaurus.lz");

static const unsigned char sBarrierStatueOfTheStormwindsBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/barrier_statue_of_the_stormwinds.huff");
static const unsigned short sBarrierStatueOfTheStormwindsBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/barrier_statue_of_the_stormwinds.gbapal");
static const unsigned char sBarrierStatueOfTheStormwindsMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/barrier_statue_of_the_stormwinds.lz");

static const unsigned char sBattleManiaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/battle_mania.huff");
static const unsigned short sBattleManiaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/battle_mania.gbapal");
static const unsigned char sBattleManiaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/battle_mania.lz");

static const unsigned char sBigEvolutionPillBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/big_evolution_pill.huff");
static const unsigned short sBigEvolutionPillBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/big_evolution_pill.gbapal");
static const unsigned char sBigEvolutionPillMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/big_evolution_pill.lz");

static const unsigned char sBlackWingedDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/black_winged_dragon.huff");
static const unsigned short sBlackWingedDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/black_winged_dragon.gbapal");
static const unsigned char sBlackWingedDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/black_winged_dragon.lz");

static const unsigned char sBeastMachineKingBarbarosUrBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/80x80/beast_machine_king_barbaros_ur.huff");
static const unsigned short sBeastMachineKingBarbarosUrBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("build/cards/80x80/beast_machine_king_barbaros_ur.gbapal");
static const unsigned char sBeastMachineKingBarbarosUrMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("build/cards/24x24/beast_machine_king_barbaros_ur.lz");

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
  [0x0460] = sTheWickedDreadrootBigArt,
  [0x0461] = sTheWickedEraserBigArt,
  [0x0462] = sTheWickedAvatarBigArt,
  [0x0463] = sTributeDollBigArt,
  [0x0464] = sTradeInBigArt,
  [0x0465] = sCyberBarrierDragonBigArt,
  [0x0466] = sCyberLaserDragonBigArt,
  [0x0467] = sDarkEndDragonBigArt,
  [0x0468] = sLightEndDragonBigArt,
  [0x0469] = sDarkArmedDragonBigArt,
  [0x046A] = sAHeroEmergesBigArt,
  [0x046B] = sAHeroLivesBigArt,
  [0x046C] = sAWingbeatOfGiantDragonBigArt,
  [0x046D] = sAllureOfDarknessBigArt,
  [0x046E] = sAmuletDragonBigArt,
  [0x046F] = sAndroSphinxBigArt,
  [0x0470] = sAntiSpellFragranceBigArt,
  [0x0471] = sAppropriateBigArt,
  [0x0472] = sApprenticeIllusionMagicianBigArt,
  [0x0473] = sApparationBigArt,
  [0x0474] = sAttackGuidanceArmorBigArt,
  [0x0475] = sAttackReflectorUnitBigArt,
  [0x0476] = sBackupSquadBigArt,
  [0x0477] = sArmageddonKnightBigArt,
  [0x0478] = sArmedDragonLv3BigArt,
  [0x0479] = sArmedDragonLv5BigArt,
  [0x047A] = sArmedDragonLv7BigArt,
  [0x047B] = sArmedDragonLv10BigArt,
  [0x047C] = sAttackAndReceiveBigArt,
  [0x047D] = sBackfireBigArt,
  [0x047E] = sHamonLordOfStrikingThunderBigArt,
  [0x047F] = sUriaLordOfSearingFlamesBigArt,
  [0x0480] = sRavielLordOfPhantasmsBigArt,
  [0x0481] = sBerserkerSoulBigArt,
  [0x0482] = sBirdfaceBigArt,
  [0x0483] = sBlueEyesAlternativeUltimateDragonBigArt,
  [0x0484] = sBreakTheDestinyBigArt,
  [0x0485] = sBubbleBlasterBigArt,
  [0x0486] = sBurdenOfTheMightyBigArt,
  [0x0487] = sCallOfTheMummyBigArt,
  [0x0488] = sCannonballSpearShellfishBigArt,
  [0x0489] = sCelestialSwordEatosBigArt,
  [0x048A] = sChaosFormBigArt,
  [0x048B] = sChickenGameBigArt,
  [0x048C] = sChimeratechFortressDragonBigArt,
  [0x048D] = sChimeratechMegafleetDragonBigArt,
  [0x048E] = sChimeratechRampageDragonBigArt,
  [0x048F] = sClockTowerPrisonBigArt,
  [0x0490] = sColdWaveBigArt,
  [0x0491] = sContinuousDestructionPunchBigArt,
  [0x0492] = sCyberEltaninBigArt,
  [0x0493] = sCyberKirinBigArt,
  [0x0494] = sCyberPhoenixBigArt,
  [0x0495] = sCyberValleyBigArt,
  [0x0496] = sCyberneticZoneBigArt,
  [0x0497] = sDTacticsBigArt,
  [0x0498] = sDTimeBigArt,
  [0x0499] = sDamagePolarizerBigArt,
  [0x049A] = sDBurstBigArt,
  [0x049B] = sDForceBigArt,
  [0x049C] = sDarkBladeTheDragonKnightBigArt,
  [0x049D] = sDarkGrepherBigArt,
  [0x049E] = sDarkMagicianGirlTheDragonKnightBigArt,
  [0x049F] = sDarklordNurseReficuleBigArt,
  [0x04A0] = sDarknessNeosphereBigArt,
  [0x04A1] = sDarkCityAtMidnightBigArt,
  [0x04A2] = sDarkMagicianTheDragonKnightBigArt,
  [0x04A3] = sDecoyDragonBigArt,
  [0x04A4] = sDesCounterblowBigArt,
  [0x04A5] = sDespairFromTheDarkBigArt,
  [0x04A6] = sDestinyDrawBigArt,
  [0x04A7] = sDestinyEndDragoonBigArt,
  [0x04A8] = sDestinyHeroBladeMasterBigArt,
  [0x04A9] = sDestinyHeroCaptainTenaciousBigArt,
  [0x04AA] = sDestinyHeroCelestialBigArt,
  [0x04AB] = sDestinyHeroDangerousBigArt,
  [0x04AC] = sDestinyHeroDarkAngelBigArt,
  [0x04AD] = sDestinyHeroDasherBigArt,
  [0x04AE] = sDestinyHeroDeciderBigArt,
  [0x04AF] = sDestinyHeroDefenderBigArt,
  [0x04B0] = sDestinyHeroDenierBigArt,
  [0x04B1] = sDestinyHeroDestroyerPhoenixEnforcerBigArt,
  [0x04B2] = sDestinyHeroDiamondDudeBigArt,
  [0x04B3] = sDestinyHeroDiskCommanderBigArt,
  [0x04B4] = sDestinyHeroDogmaBigArt,
  [0x04B5] = sDestinyHeroDominanceBigArt,
  [0x04B6] = sDestinyHeroDoomLordBigArt,
  [0x04B7] = sDestinyHeroDoubleDudeBigArt,
  [0x04B8] = sDestinyHeroDrawhandBigArt,
  [0x04B9] = sDestinyHeroDreadServantBigArt,
  [0x04BA] = sDestinyHeroDreadmasterBigArt,
  [0x04BB] = sDestinyHeroDoomOverlordBigArt,
  [0x04BC] = sDestinyHeroDreadnoughtMasterBigArt,
  [0x04BD] = sDestinyHeroDreadnoughtServantBigArt,
  [0x04BE] = sDestinyHeroDreamerBigArt,
  [0x04BF] = sDestinyHeroDrilldarkBigArt,
  [0x04C0] = sDestinyHeroDunkerBigArt,
  [0x04C1] = sDestinyHeroDynatagBigArt,
  [0x04C2] = sDestinyHeroDystopiaBigArt,
  [0x04C3] = sDestinyHeroFearMongerBigArt,
  [0x04C4] = sDestinyHeroMaliciousBigArt,
  [0x04C5] = sDestinyHeroPlasmaBigArt,
  [0x04C6] = sDifferentDimensionCapsuleBigArt,
  [0x04C7] = sDestinyHeroDusktopiaBigArt,
  [0x04C8] = sDimensionFusionBigArt,
  [0x04C9] = sDivineSerpentGehBigArt,
  [0x04CA] = sDonZaloogBigArt,
  [0x04CB] = sDoubleSpellBigArt,
  [0x04CC] = sDragonSRageBigArt,
  [0x04CD] = sDestinyHeroDestroyDogmaBigArt,
  [0x04CE] = sDoctorDBigArt,
  [0x04CF] = sDoomVirusDragonBigArt,
  [0x04D0] = sDoppelgangerBigArt,
  [0x04D1] = sEgyptianGodSlimeBigArt,
  [0x04D2] = sElementalHeroNeosKlugerBigArt,
  [0x04D3] = sEmergencyProvisionsBigArt,
  [0x04D4] = sExodiusTheUltimateForbiddenLordBigArt,
  [0x04D5] = sFatalAbacusBigArt,
  [0x04D6] = sFelgrandDragonBigArt,
  [0x04D7] = sFiresOfDoomsdayBigArt,
  [0x04D8] = sForcedRequisitionBigArt,
  [0x04D9] = sDrainTimeBigArt,
  [0x04DA] = sFieldsSanctuaryBigArt,
  [0x04DB] = sFusionDestinyBigArt,
  [0x04DC] = sFusionGateBigArt,
  [0x04DD] = sGateGuardiansCombinedBigArt,
  [0x04DE] = sGiftCardBigArt,
  [0x04DF] = sGoddessBowBigArt,
  [0x04E0] = sGorzTheEmissaryOfDarknessBigArt,
  [0x04E1] = sGranmargTheRockMonarchBigArt,
  [0x04E2] = sGreenGadgetBigArt,
  [0x04E3] = sGroundCollapseBigArt,
  [0x04E4] = sGuardianDreadscytheBigArt,
  [0x04E5] = sHarpieLadyPhoenixFormationBigArt,
  [0x04E6] = sHeroFlashBigArt,
  [0x04E7] = sInsectImitationBigArt,
  [0x04E8] = sInstantFusionBigArt,
  [0x04E9] = sGuardianEatosBigArt,
  [0x04EA] = sHeraldOfCreationBigArt,
  [0x04EB] = sHolactieTheCreatorOfLightBigArt,
  [0x04EC] = sHorusTheBlackFlameDragonLv8BigArt,
  [0x04ED] = sHorusTheBlackFlameDragonLv4BigArt,
  [0x04EE] = sHorusTheBlackFlameDragonLv6BigArt,
  [0x04EF] = sJowgenTheSpiritualistBigArt,
  [0x04F0] = sJudgmentDragonBigArt,
  [0x04F1] = sKingDragunBigArt,
  [0x04F2] = sKingOfTheSwampBigArt,
  [0x04F3] = sKurazTheLightMonarchBigArt,
  [0x04F4] = sKuribanditBigArt,
  [0x04F5] = sLastTurnBigArt,
  [0x04F6] = sLegendOfHeartBigArt,
  [0x04F7] = sLegendaryFlameLordBigArt,
  [0x04F8] = sKingTigerWanghuBigArt,
  [0x04F9] = sLegendaryKnightCritiasBigArt,
  [0x04FA] = sLegendaryKnightHermosBigArt,
  [0x04FB] = sLegendaryKnightTimaeusBigArt,
  [0x04FC] = sLekungaBigArt,
  [0x04FD] = sLightAndDarknessDragonBigArt,
  [0x04FE] = sLordOfTheRedBigArt,
  [0x04FF] = sMaAtBigArt,
  [0x0500] = sMagicalDimensionBigArt,
  [0x0501] = sMagicalHatsBigArt,
  [0x0502] = sMagicalPlantMandragolaBigArt,
  [0x0503] = sMagicalScientistBigArt,
  [0x0504] = sMagicalStoneExcavationBigArt,
  [0x0505] = sMajesticMechGoryuBigArt,
  [0x0506] = sManjuOfTheTenThousandHandsBigArt,
  [0x0507] = sMarshmallonBigArt,
  [0x0508] = sMaskOfDispelBigArt,
  [0x0509] = sMasterPeaceTheTrueDracoslayingKingBigArt,
  [0x050A] = sMaskOfTheAccursedBigArt,
  [0x050B] = sMausoleumOfTheEmperorBigArt,
  [0x050C] = sMazeraDevilleBigArt,
  [0x050D] = sMetamorphosisBigArt,
  [0x050E] = sMeteorainBigArt,
  [0x050F] = sMirageOfNightmareBigArt,
  [0x0510] = sMirrorForceDragonBigArt,
  [0x0511] = sMoltenZombieBigArt,
  [0x0512] = sMonsterGateBigArt,
  [0x0513] = sMonsterRecoveryBigArt,
  [0x0514] = sMoraleBoostBigArt,
  [0x0515] = sMucusYolkBigArt,
  [0x0516] = sMystikWokBigArt,
  [0x0517] = sNecrovalleyBigArt,
  [0x0518] = sNeedleWallBigArt,
  [0x0519] = sNeoBlueEyesUltimateDragonBigArt,
  [0x051A] = sNeosWisemanBigArt,
  [0x051B] = sNibiruThePrimalBeingBigArt,
  [0x051C] = sNuminousHealerBigArt,
  [0x051D] = sOjamaKingBigArt,
  [0x051E] = sOrichalcosShunorosBigArt,
  [0x051F] = sOverDestinyBigArt,
  [0x0520] = sPainfulChoiceBigArt,
  [0x0521] = sPandemoniumBigArt,
  [0x0522] = sParallelWorldFusionBigArt,
  [0x0523] = sPhotonGeneratorUnitBigArt,
  [0x0524] = sPoisonOfTheOldManBigArt,
  [0x0525] = sProtectorOfTheSanctuaryBigArt,
  [0x0526] = sQuintetMagicianBigArt,
  [0x0527] = sRaigekiBreakBigArt,
  [0x0528] = sProphecyBigArt,
  [0x0529] = sReaperScytheDreadscytheBigArt,
  [0x052A] = sRedEyesBlackDragonSwordBigArt,
  [0x052B] = sRedEyesDarkDragoonBigArt,
  [0x052C] = sRedEyesDarknessMetalDragonBigArt,
  [0x052D] = sRedEyesTransmigrationBigArt,
  [0x052E] = sRedGadgetBigArt,
  [0x052F] = sRelaySoulBigArt,
  [0x0530] = sReverseOfReverseBigArt,
  [0x0531] = sRocketHermosCannonBigArt,
  [0x0532] = sRopeOfLifeBigArt,
  [0x0533] = sRoyalMagicalLibraryBigArt,
  [0x0534] = sScapegoatBigArt,
  [0x0535] = sSecondCoinTossBigArt,
  [0x0536] = sSecretVillageOfTheSpellcastersBigArt,
  [0x0537] = sShareThePainBigArt,
  [0x0538] = sSixthSenseBigArt,
  [0x0539] = sSkilledDarkMagicianBigArt,
  [0x053A] = sSkilledWhiteMagicianBigArt,
  [0x053B] = sSolemnJudgmentBigArt,
  [0x053C] = sSparkBlasterBigArt,
  [0x053D] = sSkyscraper2HeroCityBigArt,
  [0x053E] = sSpellAbsorptionBigArt,
  [0x053F] = sSphinxTeleiaBigArt,
  [0x0540] = sStatueOfTheWickedBigArt,
  [0x0541] = sStaunchDefenderBigArt,
  [0x0542] = sStrayLambsBigArt,
  [0x0543] = sStrongholdTheMovingFortressBigArt,
  [0x0544] = sSummonerMonkBigArt,
  [0x0545] = sSummonerOfIllusionsBigArt,
  [0x0546] = sSuperPolymerizationBigArt,
  [0x0547] = sTerraformingBigArt,
  [0x0548] = sTheAForcesBigArt,
  [0x0549] = sTheAgentOfJudgmentSaturnBigArt,
  [0x054A] = sTheAgentOfWisdomMercuryBigArt,
  [0x054B] = sTheClawOfHermosBigArt,
  [0x054C] = sTheCreatorBigArt,
  [0x054D] = sTheCreatorIncarnateBigArt,
  [0x054E] = sTheEyeOfTimaeusBigArt,
  [0x054F] = sTheFangOfCritiasBigArt,
  [0x0550] = sTheLawOfTheNormalBigArt,
  [0x0551] = sTheLegendaryExodiaIncarnateBigArt,
  [0x0552] = sTheShallowGraveBigArt,
  [0x0553] = sTheinenTheGreatSphinxBigArt,
  [0x0554] = sThestalosTheFirestormMonarchBigArt,
  [0x0555] = sThunderDragonColossusBigArt,
  [0x0556] = sThunderDragonTitanBigArt,
  [0x0557] = sTimaeusTheKnightOfDestinyBigArt,
  [0x0558] = sTimeMagicHammerBigArt,
  [0x0559] = sTornadoWallBigArt,
  [0x055A] = sToonWorldBigArt,
  [0x055B] = sTornadoBirdBigArt,
  [0x055C] = sTrapDustshootBigArt,
  [0x055D] = sTyrantBurstDragonBigArt,
  [0x055E] = sTyrantWingBigArt,
  [0x055F] = sUltimateConductorTyrannoBigArt,
  [0x0560] = sUltimateObedientFiendBigArt,
  [0x0561] = sVisionFusionBigArt,
  [0x0562] = sVisionHeroAdorationBigArt,
  [0x0563] = sVisionHeroFarisBigArt,
  [0x0564] = sVisionHeroGravitoBigArt,
  [0x0565] = sVisionHeroIncreaseBigArt,
  [0x0566] = sVisionHeroMinimumRayBigArt,
  [0x0567] = sVisionHeroMultiplyGuyBigArt,
  [0x0568] = sVisionHeroPoisonerBigArt,
  [0x0569] = sVisionHeroTrinityBigArt,
  [0x056A] = sVisionHeroVyonBigArt,
  [0x056B] = sVisionReleaseBigArt,
  [0x056C] = sWataponBigArt,
  [0x056D] = sWhiteDragonRitualBigArt,
  [0x056E] = sWildNaturesReleaseBigArt,
  [0x056F] = sWoughtweilerBigArt,
  [0x0570] = sYellowGadgetBigArt,
  [0x0571] = sVisionHeroWitchRaiderBigArt,
  [0x0572] = sAlluringMirrorSplitBigArt,
  [0x0573] = sAmbushFangsBigArt,
  [0x0574] = sArcaniteMagicianBigArt,
  [0x0575] = sArmoryArmBigArt,
  [0x0576] = sAromaBlendBigArt,
  [0x0577] = sAromaGardenBigArt,
  [0x0578] = sAromaGardeningBigArt,
  [0x0579] = sAromaJarBigArt,
  [0x057A] = sAromageBergamotBigArt,
  [0x057B] = sAromageCanangaBigArt,
  [0x057C] = sAromageJasmineBigArt,
  [0x057D] = sAromageLaurelBigArt,
  [0x057E] = sAromageMarjoramBigArt,
  [0x057F] = sAromageRosemaryBigArt,
  [0x0580] = sAromalilithMagnoliaBigArt,
  [0x0581] = sAromalilithRosalinaBigArt,
  [0x0582] = sAromalilithRosemaryBigArt,
  [0x0583] = sAromaseraphyJasmineBigArt,
  [0x0584] = sAromaseraphyRosemaryBigArt,
  [0x0585] = sAromaseraphySweetMarjoramBigArt,
  [0x0586] = sAttackPheromonesBigArt,
  [0x0587] = sAzureEyesSilverDragonBigArt,
  [0x0588] = sBlackRoseDragonBigArt,
  [0x0589] = sBlessedWindsBigArt,
  [0x058A] = sBlueEyesJetDragonBigArt,
  [0x058B] = sBlueEyesSolidDragonBigArt,
  [0x058C] = sBlueEyesTyrantDragonBigArt,
  [0x058D] = sBlueEyesUltimateSpiritDragonBigArt,
  [0x058E] = sBondBetweenTeacherAndStudentBigArt,
  [0x058F] = sBlueEyesSpiritDragonBigArt,
  [0x0590] = sBrionacDragonOfTheIceBarrierBigArt,
  [0x0591] = sChainMaterialBigArt,
  [0x0592] = sColossalFighterBigArt,
  [0x0593] = sCupOfAceBigArt,
  [0x0594] = sCyberSlashHarpieLadyBigArt,
  [0x0595] = sDamageReptileBigArt,
  [0x0596] = sDarkBurningAttackBigArt,
  [0x0597] = sDarkBurningMagicBigArt,
  [0x0598] = sDarkCallingBigArt,
  [0x0599] = sDarkContactBigArt,
  [0x059A] = sDarkFusionBigArt,
  [0x059B] = sDarkMagicAttackBigArt,
  [0x059C] = sDarkMagicInheritanceBigArt,
  [0x059D] = sDarkMagicVeilBigArt,
  [0x059E] = sDarkMagicalCircleBigArt,
  [0x059F] = sDarkMagicianGirlTheMagicianSApprenticeBigArt,
  [0x05A0] = sDarkMagicianOfDestructionBigArt,
  [0x05A1] = sDarkMagicianTheMagicianOfBlackMagicBigArt,
  [0x05A2] = sDarkRenewalBigArt,
  [0x05A3] = sDarkStrikeFighterBigArt,
  [0x05A4] = sDarkSupremacyBigArt,
  [0x05A5] = sDestinedRivalsBigArt,
  [0x05A6] = sDriedWindsBigArt,
  [0x05A7] = sDragonRavineBigArt,
  [0x05A8] = sDragonShrineBigArt,
  [0x05A9] = sDeepEyesWhiteDragonBigArt,
  [0x05AA] = sDragonMasterMagiaBigArt,
  [0x05AB] = sDragonSpiritOfWhiteBigArt,
  [0x05AC] = sEbonIllusionMagicianBigArt,
  [0x05AD] = sElShaddollAnoyatyllisBigArt,
  [0x05AE] = sElShaddollApkalloneBigArt,
  [0x05AF] = sElShaddollConstructBigArt,
  [0x05B0] = sElShaddollFusionBigArt,
  [0x05B1] = sElShaddollGrystaBigArt,
  [0x05B2] = sElShaddollMeshahrailBigArt,
  [0x05B3] = sElShaddollShekhinagaBigArt,
  [0x05B4] = sElShaddollWendigoBigArt,
  [0x05B5] = sElShaddollWindaBigArt,
  [0x05B6] = sEternalSoulBigArt,
  [0x05B7] = sEvilAssaultBigArt,
  [0x05B8] = sEvilDragonAnantaBigArt,
  [0x05B9] = sEvilHeroAdustedGoldBigArt,
  [0x05BA] = sEvilHeroDarkGaiaBigArt,
  [0x05BB] = sEvilHeroDarkestKnightBigArt,
  [0x05BC] = sEvilHeroDeadEndPrisonBigArt,
  [0x05BD] = sEvilHeroInfernalGainerBigArt,
  [0x05BE] = sEvilHeroInfernalProdigyBigArt,
  [0x05BF] = sEvilHeroInfernalRiderBigArt,
  [0x05C0] = sEvilHeroInfernalSniperBigArt,
  [0x05C1] = sEvilHeroInfernoWingBigArt,
  [0x05C2] = sEvilHeroInfernoWingBackfireBigArt,
  [0x05C3] = sEvilHeroLightningGolemBigArt,
  [0x05C4] = sEvilHeroMaliciousBaneBigArt,
  [0x05C5] = sEvilHeroMaliciousEdgeBigArt,
  [0x05C6] = sEvilHeroMaliciousFiendBigArt,
  [0x05C7] = sEvilHeroNeosLordBigArt,
  [0x05C8] = sEvilHeroSinisterNecromBigArt,
  [0x05C9] = sEvilHeroToxicBubbleBigArt,
  [0x05CA] = sEvilHeroViciousClawsBigArt,
  [0x05CB] = sEvilHeroWildCycloneBigArt,
  [0x05CC] = sEvilMindBigArt,
  [0x05CD] = sFusionDeploymentBigArt,
  [0x05CE] = sGandoraGTheDragonOfDestructionBigArt,
  [0x05CF] = sGandoraXTheDragonOfDemolitionBigArt,
  [0x05D0] = sGoyoGuardianBigArt,
  [0x05D1] = sGrinderGolemBigArt,
  [0x05D2] = sHarpieChannelerBigArt,
  [0x05D3] = sHarpieConductorBigArt,
  [0x05D4] = sHarpieDancerBigArt,
  [0x05D5] = sHarpieHarpistBigArt,
  [0x05D6] = sHarpieLadyEleganceBigArt,
  [0x05D7] = sHarpieOracleBigArt,
  [0x05D8] = sHarpiePerfumerBigArt,
  [0x05D9] = sHarpieQueenBigArt,
  [0x05DA] = sHarpiesFeatherRestBigArt,
  [0x05DB] = sHarpiesFeatherStormBigArt,
  [0x05DC] = sHarpiesHuntingGroundBigArt,
  [0x05DD] = sHarpiesPetPhantasmalDragonBigArt,
  [0x05DE] = sHelshaddollHollowBigArt,
  [0x05DF] = sHeraldOfPerfectionBigArt,
  [0x05E0] = sHeraldOfUltimatenessBigArt,
  [0x05E1] = sHeroKidBigArt,
  [0x05E2] = sHumidWindsBigArt,
  [0x05E3] = sHystericPartyBigArt,
  [0x05E4] = sHystericSignBigArt,
  [0x05E5] = sIllusionMagicBigArt,
  [0x05E6] = sIllusionOfChaosBigArt,
  [0x05E7] = sIpiriaBigArt,
  [0x05E8] = sJunkWarriorBigArt,
  [0x05E9] = sKeeperOfDragonMagicBigArt,
  [0x05EA] = sLegendaryMajuGarzettBigArt,
  [0x05EB] = sLevShaddollFusionBigArt,
  [0x05EC] = sLightSerpentBigArt,
  [0x05ED] = sLightningWarriorBigArt,
  [0x05EE] = sLonefireBlossomBigArt,
  [0x05EF] = sMagicianNavigationBigArt,
  [0x05F0] = sMagicianOfDarkIllusionBigArt,
  [0x05F1] = sMagiciansCombinationBigArt,
  [0x05F2] = sMagiciansRobeBigArt,
  [0x05F3] = sMagiciansRodBigArt,
  [0x05F4] = sMagiciansSoulsBigArt,
  [0x05F5] = sMasterOfChaosBigArt,
  [0x05F6] = sMetaverseBigArt,
  [0x05F7] = sMillenniumEyesRestrictBigArt,
  [0x05F8] = sMoltingEscapeBigArt,
  [0x05F9] = sMysticMineBigArt,
  [0x05FA] = sNaelshaddollArielBigArt,
  [0x05FB] = sNehshaddollGeniusBigArt,
  [0x05FC] = sNepheShaddollFusionBigArt,
  [0x05FD] = sNeutronBlastBigArt,
  [0x05FE] = sOfferingToTheSnakeDeityBigArt,
  [0x05FF] = sOshaleonBigArt,
  [0x0600] = sPowerToolDragonBigArt,
  [0x0601] = sPredaplantVerteAnacondaBigArt,
  [0x0602] = sQadshaddollKeiosBigArt,
  [0x0603] = sRedDragonArchfiendBigArt,
  [0x0604] = sRedRebootBigArt,
  [0x0605] = sReeshaddollWendiBigArt,
  [0x0606] = sReeshaddollWendikuruhuBigArt,
  [0x0607] = sReptilanneRageBigArt,
  [0x0608] = sReptilianneEchidnaBigArt,
  [0x0609] = sReptilianneGardnaBigArt,
  [0x060A] = sReptilianneGorgonBigArt,
  [0x060B] = sReptilianneHydraBigArt,
  [0x060C] = sReptilianneLamiaBigArt,
  [0x060D] = sReptilianneMedusaBigArt,
  [0x060E] = sReptilianneNagaBigArt,
  [0x060F] = sReptiliannePoisonBigArt,
  [0x0610] = sReptilianneScyllaBigArt,
  [0x0611] = sReptilianneServantBigArt,
  [0x0612] = sReptilianneSpawnBigArt,
  [0x0613] = sReptilianneVaskiiBigArt,
  [0x0614] = sReptilianneViperBigArt,
  [0x0615] = sReturnOfTheDragonLordsBigArt,
  [0x0616] = sRiseOfTheSnakeDeityBigArt,
  [0x0617] = sSecretsOfDarkMagicBigArt,
  [0x0618] = sSerpentSuppressionBigArt,
  [0x0619] = sShaddollBeastBigArt,
  [0x061A] = sShaddollCoreBigArt,
  [0x061B] = sShaddollDragonBigArt,
  [0x061C] = sShaddollFalcoBigArt,
  [0x061D] = sShaddollFusionBigArt,
  [0x061E] = sShaddollHedgehogBigArt,
  [0x061F] = sShaddollHoundBigArt,
  [0x0620] = sShaddollSchismBigArt,
  [0x0621] = sShaddollSquamataBigArt,
  [0x0622] = sSilversCryBigArt,
  [0x0623] = sSnakeDeitysCommandBigArt,
  [0x0624] = sSnakeRainBigArt,
  [0x0625] = sSnakeWhistleBigArt,
  [0x0626] = sSoulServantBigArt,
  [0x0627] = sStardustDragonBigArt,
  [0x0628] = sSupremeKingsCastleBigArt,
  [0x0629] = sThatGrassLooksGreenerBigArt,
  [0x062A] = sTheDarkMagiciansBigArt,
  [0x062B] = sTheGazeOfTimaeusBigArt,
  [0x062C] = sTheMelodyOfAwakeningDragonBigArt,
  [0x062D] = sTheWhiteStoneOfAncientsBigArt,
  [0x062E] = sTheWhiteStoneOfLegendBigArt,
  [0x062F] = sTimeaeusTheUnitedMagicalDragonBigArt,
  [0x0630] = sTimeausTheUnitedDragonBigArt,
  [0x0631] = sTohushaddollGrystaBigArt,
  [0x0632] = sTrapTrickBigArt,
  [0x0633] = sTriangleEcstasySparkBigArt,
  [0x0634] = sUltraPolymerizationBigArt,
  [0x0635] = sVennominagaTheDeityOfPoisonousSnakesBigArt,
  [0x0636] = sVennominonTheKingOfPoisonousSnakesBigArt,
  [0x0637] = sVenomBoaBigArt,
  [0x0638] = sVenomBurnBigArt,
  [0x0639] = sVenomCobraBigArt,
  [0x063A] = sVenomSerpentBigArt,
  [0x063B] = sVenomShotBigArt,
  [0x063C] = sVenomSnakeBigArt,
  [0x063D] = sVenomSwampBigArt,
  [0x063E] = sVipersRebirthBigArt,
  [0x063F] = sYamorimoriBigArt,
  [0x0640] = sYowieBigArt,
  [0x0641] = sAceOfSwordBigArt,
  [0x0642] = sAceOfWandBigArt,
  [0x0643] = sArcanaCallBigArt,
  [0x0644] = sArcanaForce0TheFoolBigArt,
  [0x0645] = sArcanaForceExTheDarkRulerBigArt,
  [0x0646] = sArcanaForceExTheLightRulerBigArt,
  [0x0647] = sArcanaForceITheMagicianBigArt,
  [0x0648] = sArcanaForceIiiTheEmpressBigArt,
  [0x0649] = sArcanaForceIvTheEmperorBigArt,
  [0x064A] = sArcanaForceTheChaosRulerBigArt,
  [0x064B] = sArcanaForceVTheHierophantBigArt,
  [0x064C] = sArcanaForceViTheLoversBigArt,
  [0x064D] = sArcanaForceViiTheChariotBigArt,
  [0x064E] = sArcanaForceViiiTheStrengthBigArt,
  [0x064F] = sArcanaForceXiiTheHangmanBigArt,
  [0x0650] = sArcanaForceXivTemperanceBigArt,
  [0x0651] = sArcanaForceXixTheSunBigArt,
  [0x0652] = sArcanaForceXvTheFiendBigArt,
  [0x0653] = sArcanaForceXviiiTheMoonBigArt,
  [0x0654] = sArcanaForceXxiTheWorldBigArt,
  [0x0655] = sArcanaReadingBigArt,
  [0x0656] = sArcanaSpreadBigArt,
  [0x0657] = sArmedNeosBigArt,
  [0x0658] = sAurkusLightswornDruidBigArt,
  [0x0659] = sCelestiaLightswornAngelBigArt,
  [0x065A] = sChargeOfTheLightBrigadeBigArt,
  [0x065B] = sChrysalisChickyBigArt,
  [0x065C] = sChrysalisDolphinBigArt,
  [0x065D] = sChrysalisMoleBigArt,
  [0x065E] = sChrysalisPantailBigArt,
  [0x065F] = sChrysalisPinnyBigArt,
  [0x0660] = sCocoonPartyBigArt,
  [0x0661] = sCocoonRebirthBigArt,
  [0x0662] = sColosseumCageOfTheGladiatorBeastsBigArt,
  [0x0663] = sContactBigArt,
  [0x0664] = sContactGateBigArt,
  [0x0665] = sConvertContactBigArt,
  [0x0666] = sCrossKeeperBigArt,
  [0x0667] = sCuriousTheLightswornDominionBigArt,
  [0x0668] = sEhrenLightswornMonkBigArt,
  [0x0669] = sElementalHeroAirNeosBigArt,
  [0x066A] = sElementalHeroAquaNeosBigArt,
  [0x066B] = sElementalHeroBraveNeosBigArt,
  [0x066C] = sElementalHeroChaosNeosBigArt,
  [0x066D] = sElementalHeroCosmoNeosBigArt,
  [0x066E] = sElementalHeroDarkNeosBigArt,
  [0x066F] = sElementalHeroFlareNeosBigArt,
  [0x0670] = sElementalHeroGlowNeosBigArt,
  [0x0671] = sElementalHeroGrandNeosBigArt,
  [0x0672] = sElementalHeroMagmaNeosBigArt,
  [0x0673] = sElementalHeroMarineNeosBigArt,
  [0x0674] = sElementalHeroNebulaNeosBigArt,
  [0x0675] = sElementalHeroShiningNeosWingmanBigArt,
  [0x0676] = sElementalHeroSpiritOfNeosBigArt,
  [0x0677] = sElementalHeroStormNeosBigArt,
  [0x0678] = sEnEngageNeoSpaceBigArt,
  [0x0679] = sEnShuffleBigArt,
  [0x067A] = sEnWaveBigArt,
  [0x067B] = sEnlightenmentDragonBigArt,
  [0x067C] = sFavouriteContactBigArt,
  [0x067D] = sFelisLightswornArcherBigArt,
  [0x067E] = sFlavianColosseumOfTheGladiatorBeastsBigArt,
  [0x067F] = sGaronithLightswornDragonBigArt,
  [0x0680] = sGarothLightswornWarriorBigArt,
  [0x0681] = sGenerationNextBigArt,
  [0x0682] = sGladiatorBeastAlexanderBigArt,
  [0x0683] = sGladiatorBeastAndabataBigArt,
  [0x0684] = sGladiatorBeastAndalBigArt,
  [0x0685] = sGladiatorBeastAttorixBigArt,
  [0x0686] = sGladiatorBeastAugustusBigArt,
  [0x0687] = sGladiatorBeastBattleHalberdBigArt,
  [0x0688] = sGladiatorBeastBestiariBigArt,
  [0x0689] = sGladiatorBeastClaudiusBigArt,
  [0x068A] = sGladiatorBeastDareiosBigArt,
  [0x068B] = sGladiatorBeastDariusBigArt,
  [0x068C] = sGladiatorBeastDimacariBigArt,
  [0x068D] = sGladiatorBeastDomitianusBigArt,
  [0x068E] = sGladiatorBeastDragasesBigArt,
  [0x068F] = sGladiatorBeastEquesteBigArt,
  [0x0690] = sGladiatorBeastEssedariiBigArt,
  [0x0691] = sGladiatorBeastGaiodiazBigArt,
  [0x0692] = sGladiatorBeastGistelBigArt,
  [0x0693] = sGladiatorBeastGyzarusBigArt,
  [0x0694] = sGladiatorBeastHeraklinosBigArt,
  [0x0695] = sGladiatorBeastHoplomusBigArt,
  [0x0696] = sGladiatorBeastLanistaBigArt,
  [0x0697] = sGladiatorBeastLaquariBigArt,
  [0x0698] = sGladiatorBeastMurmilloBigArt,
  [0x0699] = sGladiatorBeastNerokiusBigArt,
  [0x069A] = sGladiatorBeastNoxiousBigArt,
  [0x069B] = sGladiatorBeastOctaviusBigArt,
  [0x069C] = sGladiatorBeastRetiariBigArt,
  [0x069D] = sGladiatorBeastSagittariiBigArt,
  [0x069E] = sGladiatorBeastSamniteBigArt,
  [0x069F] = sGladiatorBeastSecutorBigArt,
  [0x06A0] = sGladiatorBeastSpartacusBigArt,
  [0x06A1] = sGladiatorBeastTamerEditorBigArt,
  [0x06A2] = sGladiatorBeastToraxBigArt,
  [0x06A3] = sGladiatorBeastTygeriusBigArt,
  [0x06A4] = sGladiatorBeastVespasiusBigArt,
  [0x06A5] = sGladiatorBeastWarChariotBigArt,
  [0x06A6] = sGladiatorBeastsBattleArchfiendShieldBigArt,
  [0x06A7] = sGladiatorBeastsBattleGladiusBigArt,
  [0x06A8] = sGladiatorBeastsBattleManicaBigArt,
  [0x06A9] = sGladiatorBeastsMedusaShieldBigArt,
  [0x06AA] = sGladiatorBeastsValorBigArt,
  [0x06AB] = sGladiatorNaumachiaBigArt,
  [0x06AC] = sGloriousIllusionBigArt,
  [0x06AD] = sInstantContactBigArt,
  [0x06AE] = sInstantNeoSpaceBigArt,
  [0x06AF] = sJainLightswornPaladinBigArt,
  [0x06B0] = sJainTwilightswornGeneralBigArt,
  [0x06B1] = sJenisLightswornMenderBigArt,
  [0x06B2] = sJudgmentTheDragonOfHeavenBigArt,
  [0x06B3] = sKnightOfPentaclesBigArt,
  [0x06B4] = sLightBarrierBigArt,
  [0x06B5] = sLightForceBigArt,
  [0x06B6] = sLightOfDestructionBigArt,
  [0x06B7] = sLightSpiralBigArt,
  [0x06B8] = sLightswornAegisBigArt,
  [0x06B9] = sLightswornBarrierBigArt,
  [0x06BA] = sLightswornDragonlingBigArt,
  [0x06BB] = sLightswornJudgementBigArt,
  [0x06BC] = sLightswornSabreBigArt,
  [0x06BD] = sLightswornSanctuaryBigArt,
  [0x06BE] = sLuminaLightswornSummonerBigArt,
  [0x06BF] = sLuminaTwilightswornShamanBigArt,
  [0x06C0] = sLylaLightswornSorceressBigArt,
  [0x06C1] = sLylaTwilightswornEnchantressBigArt,
  [0x06C2] = sMarchOfTheDarkBrigadeBigArt,
  [0x06C3] = sMichaelTheArchLightswornBigArt,
  [0x06C4] = sMinervaLightswornMaidenBigArt,
  [0x06C5] = sMinervaTheAthenianLightswornBigArt,
  [0x06C6] = sMinervaTheExhaltedLightswornBigArt,
  [0x06C7] = sMiracleContactBigArt,
  [0x06C8] = sMoonTokenBigArt,
  [0x06C9] = sNeoSpaceBigArt,
  [0x06CA] = sNeoSpaceConnectorBigArt,
  [0x06CB] = sNeoSpacianAirHummingbirdBigArt,
  [0x06CC] = sNeoSpacianAquaDolphinBigArt,
  [0x06CD] = sNeoSpacianDarkPantherBigArt,
  [0x06CE] = sNeoSpacianFlareScarabBigArt,
  [0x06CF] = sNeoSpacianGlowMossBigArt,
  [0x06D0] = sNeoSpacianGrandMoleBigArt,
  [0x06D1] = sNeoSpacianMarineDolphinBigArt,
  [0x06D2] = sNeoSpacianTwinkleMossBigArt,
  [0x06D3] = sNexBigArt,
  [0x06D4] = sNextBigArt,
  [0x06D5] = sPentacleOfAceBigArt,
  [0x06D6] = sPunishmentDragonBigArt,
  [0x06D7] = sRaidenHandOfTheLightswornBigArt,
  [0x06D8] = sRealmOfLightBigArt,
  [0x06D9] = sRescueCatBigArt,
  [0x06DA] = sRescueRabbitBigArt,
  [0x06DB] = sReversalOfFateBigArt,
  [0x06DC] = sRinyanLightswornRogueBigArt,
  [0x06DD] = sRykoLightswornHunterBigArt,
  [0x06DE] = sRykoTwilightswornFighterBigArt,
  [0x06DF] = sShireLightswornSpiritBigArt,
  [0x06E0] = sSolarRechargeBigArt,
  [0x06E1] = sSuitOfSwordXBigArt,
  [0x06E2] = sTestBearBigArt,
  [0x06E3] = sTestPantherBigArt,
  [0x06E4] = sTestTigerBigArt,
  [0x06E5] = sThumbsDownBigArt,
  [0x06E6] = sTourOfDoomBigArt,
  [0x06E7] = sTrojanGladiatorBeastBigArt,
  [0x06E8] = sTwilightClothBigArt,
  [0x06E9] = sTwilightEraserBigArt,
  [0x06EA] = sTwlightTwinDragonsBigArt,
  [0x06EB] = sVanquishingLightBigArt,
  [0x06EC] = sWeissLightswornArchfiendBigArt,
  [0x06ED] = sWulfLightswornBeastBigArt,
  [0x06EE] = sAllOutAttacksBigArt,
  [0x06EF] = sAncientFairyDragonBigArt,
  [0x06F0] = sAncientGearBigArt,
  [0x06F1] = sAncientGearAdvanceBigArt,
  [0x06F2] = sAncientGearBeastBigArt,
  [0x06F3] = sAncientGearCannonBigArt,
  [0x06F4] = sAncientGearCastleBigArt,
  [0x06F5] = sAncientGearCommanderBigArt,
  [0x06F6] = sAncientGearDarkGolemBigArt,
  [0x06F7] = sAncientGearDragonBigArt,
  [0x06F8] = sAncientGearDrillBigArt,
  [0x06F9] = sAncientGearDuelBigArt,
  [0x06FA] = sAncientGearEngineerBigArt,
  [0x06FB] = sAncientGearExplosiveBigArt,
  [0x06FC] = sAncientGearFactoryBigArt,
  [0x06FD] = sAncientGearFistBigArt,
  [0x06FE] = sAncientGearFrameBigArt,
  [0x06FF] = sAncientGearFusionBigArt,
  [0x0700] = sAncientGearGadjiltronChimeraBigArt,
  [0x0701] = sAncientGearGadjiltronDragonBigArt,
  [0x0702] = sAncientGearGolemBigArt,
  [0x0703] = sAncientGearGolemUltimatePoundBigArt,
  [0x0704] = sAncientGearKnightBigArt,
  [0x0705] = sAncientGearMegatonGolemBigArt,
  [0x0706] = sAncientGearSoldierBigArt,
  [0x0707] = sAncientGearStatueBigArt,
  [0x0708] = sAncientGearTankBigArt,
  [0x0709] = sAncientGearTankerBigArt,
  [0x070A] = sAncientGearWorkshopBigArt,
  [0x070B] = sAncientLeafBigArt,
  [0x070C] = sAncientSacredWyvernBigArt,
  [0x070D] = sArcanaKnightJokerBigArt,
  [0x070E] = sArcaneBarrierBigArt,
  [0x070F] = sArmityleTheChaosPhantasmBigArt,
  [0x0710] = sBabycerasaurusBigArt,
  [0x0711] = sBarrierStatueOfTheStormwindsBigArt,
  [0x0712] = sBattleManiaBigArt,
  [0x0713] = sBigEvolutionPillBigArt,
  [0x0714] = sBlackWingedDragonBigArt,
  [0x0715] = sBeastMachineKingBarbarosUrBigArt,
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
  [0x0460] = sTheWickedDreadrootBigPalette,
  [0x0461] = sTheWickedEraserBigPalette,
  [0x0462] = sTheWickedAvatarBigPalette,
  [0x0463] = sTributeDollBigPalette,
  [0x0464] = sTradeInBigPalette,
  [0x0465] = sCyberBarrierDragonBigPalette,
  [0x0466] = sCyberLaserDragonBigPalette,
  [0x0467] = sDarkEndDragonBigPalette,
  [0x0468] = sLightEndDragonBigPalette,
  [0x0469] = sDarkArmedDragonBigPalette,
  [0x046A] = sAHeroEmergesBigPalette,
  [0x046B] = sAHeroLivesBigPalette,
  [0x046C] = sAWingbeatOfGiantDragonBigPalette,
  [0x046D] = sAllureOfDarknessBigPalette,
  [0x046E] = sAmuletDragonBigPalette,
  [0x046F] = sAndroSphinxBigPalette,
  [0x0470] = sAntiSpellFragranceBigPalette,
  [0x0471] = sAppropriateBigPalette,
  [0x0472] = sApprenticeIllusionMagicianBigPalette,
  [0x0473] = sApparationBigPalette,
  [0x0474] = sAttackGuidanceArmorBigPalette,
  [0x0475] = sAttackReflectorUnitBigPalette,
  [0x0476] = sBackupSquadBigPalette,
  [0x0477] = sArmageddonKnightBigPalette,
  [0x0478] = sArmedDragonLv3BigPalette,
  [0x0479] = sArmedDragonLv5BigPalette,
  [0x047A] = sArmedDragonLv7BigPalette,
  [0x047B] = sArmedDragonLv10BigPalette,
  [0x047C] = sAttackAndReceiveBigPalette,
  [0x047D] = sBackfireBigPalette,
  [0x047E] = sHamonLordOfStrikingThunderBigPalette,
  [0x047F] = sUriaLordOfSearingFlamesBigPalette,
  [0x0480] = sRavielLordOfPhantasmsBigPalette,
  [0x0481] = sBerserkerSoulBigPalette,
  [0x0482] = sBirdfaceBigPalette,
  [0x0483] = sBlueEyesAlternativeUltimateDragonBigPalette,
  [0x0484] = sBreakTheDestinyBigPalette,
  [0x0485] = sBubbleBlasterBigPalette,
  [0x0486] = sBurdenOfTheMightyBigPalette,
  [0x0487] = sCallOfTheMummyBigPalette,
  [0x0488] = sCannonballSpearShellfishBigPalette,
  [0x0489] = sCelestialSwordEatosBigPalette,
  [0x048A] = sChaosFormBigPalette,
  [0x048B] = sChickenGameBigPalette,
  [0x048C] = sChimeratechFortressDragonBigPalette,
  [0x048D] = sChimeratechMegafleetDragonBigPalette,
  [0x048E] = sChimeratechRampageDragonBigPalette,
  [0x048F] = sClockTowerPrisonBigPalette,
  [0x0490] = sColdWaveBigPalette,
  [0x0491] = sContinuousDestructionPunchBigPalette,
  [0x0492] = sCyberEltaninBigPalette,
  [0x0493] = sCyberKirinBigPalette,
  [0x0494] = sCyberPhoenixBigPalette,
  [0x0495] = sCyberValleyBigPalette,
  [0x0496] = sCyberneticZoneBigPalette,
  [0x0497] = sDTacticsBigPalette,
  [0x0498] = sDTimeBigPalette,
  [0x0499] = sDamagePolarizerBigPalette,
  [0x049A] = sDBurstBigPalette,
  [0x049B] = sDForceBigPalette,
  [0x049C] = sDarkBladeTheDragonKnightBigPalette,
  [0x049D] = sDarkGrepherBigPalette,
  [0x049E] = sDarkMagicianGirlTheDragonKnightBigPalette,
  [0x049F] = sDarklordNurseReficuleBigPalette,
  [0x04A0] = sDarknessNeosphereBigPalette,
  [0x04A1] = sDarkCityAtMidnightBigPalette,
  [0x04A2] = sDarkMagicianTheDragonKnightBigPalette,
  [0x04A3] = sDecoyDragonBigPalette,
  [0x04A4] = sDesCounterblowBigPalette,
  [0x04A5] = sDespairFromTheDarkBigPalette,
  [0x04A6] = sDestinyDrawBigPalette,
  [0x04A7] = sDestinyEndDragoonBigPalette,
  [0x04A8] = sDestinyHeroBladeMasterBigPalette,
  [0x04A9] = sDestinyHeroCaptainTenaciousBigPalette,
  [0x04AA] = sDestinyHeroCelestialBigPalette,
  [0x04AB] = sDestinyHeroDangerousBigPalette,
  [0x04AC] = sDestinyHeroDarkAngelBigPalette,
  [0x04AD] = sDestinyHeroDasherBigPalette,
  [0x04AE] = sDestinyHeroDeciderBigPalette,
  [0x04AF] = sDestinyHeroDefenderBigPalette,
  [0x04B0] = sDestinyHeroDenierBigPalette,
  [0x04B1] = sDestinyHeroDestroyerPhoenixEnforcerBigPalette,
  [0x04B2] = sDestinyHeroDiamondDudeBigPalette,
  [0x04B3] = sDestinyHeroDiskCommanderBigPalette,
  [0x04B4] = sDestinyHeroDogmaBigPalette,
  [0x04B5] = sDestinyHeroDominanceBigPalette,
  [0x04B6] = sDestinyHeroDoomLordBigPalette,
  [0x04B7] = sDestinyHeroDoubleDudeBigPalette,
  [0x04B8] = sDestinyHeroDrawhandBigPalette,
  [0x04B9] = sDestinyHeroDreadServantBigPalette,
  [0x04BA] = sDestinyHeroDreadmasterBigPalette,
  [0x04BB] = sDestinyHeroDoomOverlordBigPalette,
  [0x04BC] = sDestinyHeroDreadnoughtMasterBigPalette,
  [0x04BD] = sDestinyHeroDreadnoughtServantBigPalette,
  [0x04BE] = sDestinyHeroDreamerBigPalette,
  [0x04BF] = sDestinyHeroDrilldarkBigPalette,
  [0x04C0] = sDestinyHeroDunkerBigPalette,
  [0x04C1] = sDestinyHeroDynatagBigPalette,
  [0x04C2] = sDestinyHeroDystopiaBigPalette,
  [0x04C3] = sDestinyHeroFearMongerBigPalette,
  [0x04C4] = sDestinyHeroMaliciousBigPalette,
  [0x04C5] = sDestinyHeroPlasmaBigPalette,
  [0x04C6] = sDifferentDimensionCapsuleBigPalette,
  [0x04C7] = sDestinyHeroDusktopiaBigPalette,
  [0x04C8] = sDimensionFusionBigPalette,
  [0x04C9] = sDivineSerpentGehBigPalette,
  [0x04CA] = sDonZaloogBigPalette,
  [0x04CB] = sDoubleSpellBigPalette,
  [0x04CC] = sDragonSRageBigPalette,
  [0x04CD] = sDestinyHeroDestroyDogmaBigPalette,
  [0x04CE] = sDoctorDBigPalette,
  [0x04CF] = sDoomVirusDragonBigPalette,
  [0x04D0] = sDoppelgangerBigPalette,
  [0x04D1] = sEgyptianGodSlimeBigPalette,
  [0x04D2] = sElementalHeroNeosKlugerBigPalette,
  [0x04D3] = sEmergencyProvisionsBigPalette,
  [0x04D4] = sExodiusTheUltimateForbiddenLordBigPalette,
  [0x04D5] = sFatalAbacusBigPalette,
  [0x04D6] = sFelgrandDragonBigPalette,
  [0x04D7] = sFiresOfDoomsdayBigPalette,
  [0x04D8] = sForcedRequisitionBigPalette,
  [0x04D9] = sDrainTimeBigPalette,
  [0x04DA] = sFieldsSanctuaryBigPalette,
  [0x04DB] = sFusionDestinyBigPalette,
  [0x04DC] = sFusionGateBigPalette,
  [0x04DD] = sGateGuardiansCombinedBigPalette,
  [0x04DE] = sGiftCardBigPalette,
  [0x04DF] = sGoddessBowBigPalette,
  [0x04E0] = sGorzTheEmissaryOfDarknessBigPalette,
  [0x04E1] = sGranmargTheRockMonarchBigPalette,
  [0x04E2] = sGreenGadgetBigPalette,
  [0x04E3] = sGroundCollapseBigPalette,
  [0x04E4] = sGuardianDreadscytheBigPalette,
  [0x04E5] = sHarpieLadyPhoenixFormationBigPalette,
  [0x04E6] = sHeroFlashBigPalette,
  [0x04E7] = sInsectImitationBigPalette,
  [0x04E8] = sInstantFusionBigPalette,
  [0x04E9] = sGuardianEatosBigPalette,
  [0x04EA] = sHeraldOfCreationBigPalette,
  [0x04EB] = sHolactieTheCreatorOfLightBigPalette,
  [0x04EC] = sHorusTheBlackFlameDragonLv8BigPalette,
  [0x04ED] = sHorusTheBlackFlameDragonLv4BigPalette,
  [0x04EE] = sHorusTheBlackFlameDragonLv6BigPalette,
  [0x04EF] = sJowgenTheSpiritualistBigPalette,
  [0x04F0] = sJudgmentDragonBigPalette,
  [0x04F1] = sKingDragunBigPalette,
  [0x04F2] = sKingOfTheSwampBigPalette,
  [0x04F3] = sKurazTheLightMonarchBigPalette,
  [0x04F4] = sKuribanditBigPalette,
  [0x04F5] = sLastTurnBigPalette,
  [0x04F6] = sLegendOfHeartBigPalette,
  [0x04F7] = sLegendaryFlameLordBigPalette,
  [0x04F8] = sKingTigerWanghuBigPalette,
  [0x04F9] = sLegendaryKnightCritiasBigPalette,
  [0x04FA] = sLegendaryKnightHermosBigPalette,
  [0x04FB] = sLegendaryKnightTimaeusBigPalette,
  [0x04FC] = sLekungaBigPalette,
  [0x04FD] = sLightAndDarknessDragonBigPalette,
  [0x04FE] = sLordOfTheRedBigPalette,
  [0x04FF] = sMaAtBigPalette,
  [0x0500] = sMagicalDimensionBigPalette,
  [0x0501] = sMagicalHatsBigPalette,
  [0x0502] = sMagicalPlantMandragolaBigPalette,
  [0x0503] = sMagicalScientistBigPalette,
  [0x0504] = sMagicalStoneExcavationBigPalette,
  [0x0505] = sMajesticMechGoryuBigPalette,
  [0x0506] = sManjuOfTheTenThousandHandsBigPalette,
  [0x0507] = sMarshmallonBigPalette,
  [0x0508] = sMaskOfDispelBigPalette,
  [0x0509] = sMasterPeaceTheTrueDracoslayingKingBigPalette,
  [0x050A] = sMaskOfTheAccursedBigPalette,
  [0x050B] = sMausoleumOfTheEmperorBigPalette,
  [0x050C] = sMazeraDevilleBigPalette,
  [0x050D] = sMetamorphosisBigPalette,
  [0x050E] = sMeteorainBigPalette,
  [0x050F] = sMirageOfNightmareBigPalette,
  [0x0510] = sMirrorForceDragonBigPalette,
  [0x0511] = sMoltenZombieBigPalette,
  [0x0512] = sMonsterGateBigPalette,
  [0x0513] = sMonsterRecoveryBigPalette,
  [0x0514] = sMoraleBoostBigPalette,
  [0x0515] = sMucusYolkBigPalette,
  [0x0516] = sMystikWokBigPalette,
  [0x0517] = sNecrovalleyBigPalette,
  [0x0518] = sNeedleWallBigPalette,
  [0x0519] = sNeoBlueEyesUltimateDragonBigPalette,
  [0x051A] = sNeosWisemanBigPalette,
  [0x051B] = sNibiruThePrimalBeingBigPalette,
  [0x051C] = sNuminousHealerBigPalette,
  [0x051D] = sOjamaKingBigPalette,
  [0x051E] = sOrichalcosShunorosBigPalette,
  [0x051F] = sOverDestinyBigPalette,
  [0x0520] = sPainfulChoiceBigPalette,
  [0x0521] = sPandemoniumBigPalette,
  [0x0522] = sParallelWorldFusionBigPalette,
  [0x0523] = sPhotonGeneratorUnitBigPalette,
  [0x0524] = sPoisonOfTheOldManBigPalette,
  [0x0525] = sProtectorOfTheSanctuaryBigPalette,
  [0x0526] = sQuintetMagicianBigPalette,
  [0x0527] = sRaigekiBreakBigPalette,
  [0x0528] = sProphecyBigPalette,
  [0x0529] = sReaperScytheDreadscytheBigPalette,
  [0x052A] = sRedEyesBlackDragonSwordBigPalette,
  [0x052B] = sRedEyesDarkDragoonBigPalette,
  [0x052C] = sRedEyesDarknessMetalDragonBigPalette,
  [0x052D] = sRedEyesTransmigrationBigPalette,
  [0x052E] = sRedGadgetBigPalette,
  [0x052F] = sRelaySoulBigPalette,
  [0x0530] = sReverseOfReverseBigPalette,
  [0x0531] = sRocketHermosCannonBigPalette,
  [0x0532] = sRopeOfLifeBigPalette,
  [0x0533] = sRoyalMagicalLibraryBigPalette,
  [0x0534] = sScapegoatBigPalette,
  [0x0535] = sSecondCoinTossBigPalette,
  [0x0536] = sSecretVillageOfTheSpellcastersBigPalette,
  [0x0537] = sShareThePainBigPalette,
  [0x0538] = sSixthSenseBigPalette,
  [0x0539] = sSkilledDarkMagicianBigPalette,
  [0x053A] = sSkilledWhiteMagicianBigPalette,
  [0x053B] = sSolemnJudgmentBigPalette,
  [0x053C] = sSparkBlasterBigPalette,
  [0x053D] = sSkyscraper2HeroCityBigPalette,
  [0x053E] = sSpellAbsorptionBigPalette,
  [0x053F] = sSphinxTeleiaBigPalette,
  [0x0540] = sStatueOfTheWickedBigPalette,
  [0x0541] = sStaunchDefenderBigPalette,
  [0x0542] = sStrayLambsBigPalette,
  [0x0543] = sStrongholdTheMovingFortressBigPalette,
  [0x0544] = sSummonerMonkBigPalette,
  [0x0545] = sSummonerOfIllusionsBigPalette,
  [0x0546] = sSuperPolymerizationBigPalette,
  [0x0547] = sTerraformingBigPalette,
  [0x0548] = sTheAForcesBigPalette,
  [0x0549] = sTheAgentOfJudgmentSaturnBigPalette,
  [0x054A] = sTheAgentOfWisdomMercuryBigPalette,
  [0x054B] = sTheClawOfHermosBigPalette,
  [0x054C] = sTheCreatorBigPalette,
  [0x054D] = sTheCreatorIncarnateBigPalette,
  [0x054E] = sTheEyeOfTimaeusBigPalette,
  [0x054F] = sTheFangOfCritiasBigPalette,
  [0x0550] = sTheLawOfTheNormalBigPalette,
  [0x0551] = sTheLegendaryExodiaIncarnateBigPalette,
  [0x0552] = sTheShallowGraveBigPalette,
  [0x0553] = sTheinenTheGreatSphinxBigPalette,
  [0x0554] = sThestalosTheFirestormMonarchBigPalette,
  [0x0555] = sThunderDragonColossusBigPalette,
  [0x0556] = sThunderDragonTitanBigPalette,
  [0x0557] = sTimaeusTheKnightOfDestinyBigPalette,
  [0x0558] = sTimeMagicHammerBigPalette,
  [0x0559] = sTornadoWallBigPalette,
  [0x055A] = sToonWorldBigPalette,
  [0x055B] = sTornadoBirdBigPalette,
  [0x055C] = sTrapDustshootBigPalette,
  [0x055D] = sTyrantBurstDragonBigPalette,
  [0x055E] = sTyrantWingBigPalette,
  [0x055F] = sUltimateConductorTyrannoBigPalette,
  [0x0560] = sUltimateObedientFiendBigPalette,
  [0x0561] = sVisionFusionBigPalette,
  [0x0562] = sVisionHeroAdorationBigPalette,
  [0x0563] = sVisionHeroFarisBigPalette,
  [0x0564] = sVisionHeroGravitoBigPalette,
  [0x0565] = sVisionHeroIncreaseBigPalette,
  [0x0566] = sVisionHeroMinimumRayBigPalette,
  [0x0567] = sVisionHeroMultiplyGuyBigPalette,
  [0x0568] = sVisionHeroPoisonerBigPalette,
  [0x0569] = sVisionHeroTrinityBigPalette,
  [0x056A] = sVisionHeroVyonBigPalette,
  [0x056B] = sVisionReleaseBigPalette,
  [0x056C] = sWataponBigPalette,
  [0x056D] = sWhiteDragonRitualBigPalette,
  [0x056E] = sWildNaturesReleaseBigPalette,
  [0x056F] = sWoughtweilerBigPalette,
  [0x0570] = sYellowGadgetBigPalette,
  [0x0571] = sVisionHeroWitchRaiderBigPalette,
  [0x0572] = sAlluringMirrorSplitBigPalette,
  [0x0573] = sAmbushFangsBigPalette,
  [0x0574] = sArcaniteMagicianBigPalette,
  [0x0575] = sArmoryArmBigPalette,
  [0x0576] = sAromaBlendBigPalette,
  [0x0577] = sAromaGardenBigPalette,
  [0x0578] = sAromaGardeningBigPalette,
  [0x0579] = sAromaJarBigPalette,
  [0x057A] = sAromageBergamotBigPalette,
  [0x057B] = sAromageCanangaBigPalette,
  [0x057C] = sAromageJasmineBigPalette,
  [0x057D] = sAromageLaurelBigPalette,
  [0x057E] = sAromageMarjoramBigPalette,
  [0x057F] = sAromageRosemaryBigPalette,
  [0x0580] = sAromalilithMagnoliaBigPalette,
  [0x0581] = sAromalilithRosalinaBigPalette,
  [0x0582] = sAromalilithRosemaryBigPalette,
  [0x0583] = sAromaseraphyJasmineBigPalette,
  [0x0584] = sAromaseraphyRosemaryBigPalette,
  [0x0585] = sAromaseraphySweetMarjoramBigPalette,
  [0x0586] = sAttackPheromonesBigPalette,
  [0x0587] = sAzureEyesSilverDragonBigPalette,
  [0x0588] = sBlackRoseDragonBigPalette,
  [0x0589] = sBlessedWindsBigPalette,
  [0x058A] = sBlueEyesJetDragonBigPalette,
  [0x058B] = sBlueEyesSolidDragonBigPalette,
  [0x058C] = sBlueEyesTyrantDragonBigPalette,
  [0x058D] = sBlueEyesUltimateSpiritDragonBigPalette,
  [0x058E] = sBondBetweenTeacherAndStudentBigPalette,
  [0x058F] = sBlueEyesSpiritDragonBigPalette,
  [0x0590] = sBrionacDragonOfTheIceBarrierBigPalette,
  [0x0591] = sChainMaterialBigPalette,
  [0x0592] = sColossalFighterBigPalette,
  [0x0593] = sCupOfAceBigPalette,
  [0x0594] = sCyberSlashHarpieLadyBigPalette,
  [0x0595] = sDamageReptileBigPalette,
  [0x0596] = sDarkBurningAttackBigPalette,
  [0x0597] = sDarkBurningMagicBigPalette,
  [0x0598] = sDarkCallingBigPalette,
  [0x0599] = sDarkContactBigPalette,
  [0x059A] = sDarkFusionBigPalette,
  [0x059B] = sDarkMagicAttackBigPalette,
  [0x059C] = sDarkMagicInheritanceBigPalette,
  [0x059D] = sDarkMagicVeilBigPalette,
  [0x059E] = sDarkMagicalCircleBigPalette,
  [0x059F] = sDarkMagicianGirlTheMagicianSApprenticeBigPalette,
  [0x05A0] = sDarkMagicianOfDestructionBigPalette,
  [0x05A1] = sDarkMagicianTheMagicianOfBlackMagicBigPalette,
  [0x05A2] = sDarkRenewalBigPalette,
  [0x05A3] = sDarkStrikeFighterBigPalette,
  [0x05A4] = sDarkSupremacyBigPalette,
  [0x05A5] = sDestinedRivalsBigPalette,
  [0x05A6] = sDriedWindsBigPalette,
  [0x05A7] = sDragonRavineBigPalette,
  [0x05A8] = sDragonShrineBigPalette,
  [0x05A9] = sDeepEyesWhiteDragonBigPalette,
  [0x05AA] = sDragonMasterMagiaBigPalette,
  [0x05AB] = sDragonSpiritOfWhiteBigPalette,
  [0x05AC] = sEbonIllusionMagicianBigPalette,
  [0x05AD] = sElShaddollAnoyatyllisBigPalette,
  [0x05AE] = sElShaddollApkalloneBigPalette,
  [0x05AF] = sElShaddollConstructBigPalette,
  [0x05B0] = sElShaddollFusionBigPalette,
  [0x05B1] = sElShaddollGrystaBigPalette,
  [0x05B2] = sElShaddollMeshahrailBigPalette,
  [0x05B3] = sElShaddollShekhinagaBigPalette,
  [0x05B4] = sElShaddollWendigoBigPalette,
  [0x05B5] = sElShaddollWindaBigPalette,
  [0x05B6] = sEternalSoulBigPalette,
  [0x05B7] = sEvilAssaultBigPalette,
  [0x05B8] = sEvilDragonAnantaBigPalette,
  [0x05B9] = sEvilHeroAdustedGoldBigPalette,
  [0x05BA] = sEvilHeroDarkGaiaBigPalette,
  [0x05BB] = sEvilHeroDarkestKnightBigPalette,
  [0x05BC] = sEvilHeroDeadEndPrisonBigPalette,
  [0x05BD] = sEvilHeroInfernalGainerBigPalette,
  [0x05BE] = sEvilHeroInfernalProdigyBigPalette,
  [0x05BF] = sEvilHeroInfernalRiderBigPalette,
  [0x05C0] = sEvilHeroInfernalSniperBigPalette,
  [0x05C1] = sEvilHeroInfernoWingBigPalette,
  [0x05C2] = sEvilHeroInfernoWingBackfireBigPalette,
  [0x05C3] = sEvilHeroLightningGolemBigPalette,
  [0x05C4] = sEvilHeroMaliciousBaneBigPalette,
  [0x05C5] = sEvilHeroMaliciousEdgeBigPalette,
  [0x05C6] = sEvilHeroMaliciousFiendBigPalette,
  [0x05C7] = sEvilHeroNeosLordBigPalette,
  [0x05C8] = sEvilHeroSinisterNecromBigPalette,
  [0x05C9] = sEvilHeroToxicBubbleBigPalette,
  [0x05CA] = sEvilHeroViciousClawsBigPalette,
  [0x05CB] = sEvilHeroWildCycloneBigPalette,
  [0x05CC] = sEvilMindBigPalette,
  [0x05CD] = sFusionDeploymentBigPalette,
  [0x05CE] = sGandoraGTheDragonOfDestructionBigPalette,
  [0x05CF] = sGandoraXTheDragonOfDemolitionBigPalette,
  [0x05D0] = sGoyoGuardianBigPalette,
  [0x05D1] = sGrinderGolemBigPalette,
  [0x05D2] = sHarpieChannelerBigPalette,
  [0x05D3] = sHarpieConductorBigPalette,
  [0x05D4] = sHarpieDancerBigPalette,
  [0x05D5] = sHarpieHarpistBigPalette,
  [0x05D6] = sHarpieLadyEleganceBigPalette,
  [0x05D7] = sHarpieOracleBigPalette,
  [0x05D8] = sHarpiePerfumerBigPalette,
  [0x05D9] = sHarpieQueenBigPalette,
  [0x05DA] = sHarpiesFeatherRestBigPalette,
  [0x05DB] = sHarpiesFeatherStormBigPalette,
  [0x05DC] = sHarpiesHuntingGroundBigPalette,
  [0x05DD] = sHarpiesPetPhantasmalDragonBigPalette,
  [0x05DE] = sHelshaddollHollowBigPalette,
  [0x05DF] = sHeraldOfPerfectionBigPalette,
  [0x05E0] = sHeraldOfUltimatenessBigPalette,
  [0x05E1] = sHeroKidBigPalette,
  [0x05E2] = sHumidWindsBigPalette,
  [0x05E3] = sHystericPartyBigPalette,
  [0x05E4] = sHystericSignBigPalette,
  [0x05E5] = sIllusionMagicBigPalette,
  [0x05E6] = sIllusionOfChaosBigPalette,
  [0x05E7] = sIpiriaBigPalette,
  [0x05E8] = sJunkWarriorBigPalette,
  [0x05E9] = sKeeperOfDragonMagicBigPalette,
  [0x05EA] = sLegendaryMajuGarzettBigPalette,
  [0x05EB] = sLevShaddollFusionBigPalette,
  [0x05EC] = sLightSerpentBigPalette,
  [0x05ED] = sLightningWarriorBigPalette,
  [0x05EE] = sLonefireBlossomBigPalette,
  [0x05EF] = sMagicianNavigationBigPalette,
  [0x05F0] = sMagicianOfDarkIllusionBigPalette,
  [0x05F1] = sMagiciansCombinationBigPalette,
  [0x05F2] = sMagiciansRobeBigPalette,
  [0x05F3] = sMagiciansRodBigPalette,
  [0x05F4] = sMagiciansSoulsBigPalette,
  [0x05F5] = sMasterOfChaosBigPalette,
  [0x05F6] = sMetaverseBigPalette,
  [0x05F7] = sMillenniumEyesRestrictBigPalette,
  [0x05F8] = sMoltingEscapeBigPalette,
  [0x05F9] = sMysticMineBigPalette,
  [0x05FA] = sNaelshaddollArielBigPalette,
  [0x05FB] = sNehshaddollGeniusBigPalette,
  [0x05FC] = sNepheShaddollFusionBigPalette,
  [0x05FD] = sNeutronBlastBigPalette,
  [0x05FE] = sOfferingToTheSnakeDeityBigPalette,
  [0x05FF] = sOshaleonBigPalette,
  [0x0600] = sPowerToolDragonBigPalette,
  [0x0601] = sPredaplantVerteAnacondaBigPalette,
  [0x0602] = sQadshaddollKeiosBigPalette,
  [0x0603] = sRedDragonArchfiendBigPalette,
  [0x0604] = sRedRebootBigPalette,
  [0x0605] = sReeshaddollWendiBigPalette,
  [0x0606] = sReeshaddollWendikuruhuBigPalette,
  [0x0607] = sReptilanneRageBigPalette,
  [0x0608] = sReptilianneEchidnaBigPalette,
  [0x0609] = sReptilianneGardnaBigPalette,
  [0x060A] = sReptilianneGorgonBigPalette,
  [0x060B] = sReptilianneHydraBigPalette,
  [0x060C] = sReptilianneLamiaBigPalette,
  [0x060D] = sReptilianneMedusaBigPalette,
  [0x060E] = sReptilianneNagaBigPalette,
  [0x060F] = sReptiliannePoisonBigPalette,
  [0x0610] = sReptilianneScyllaBigPalette,
  [0x0611] = sReptilianneServantBigPalette,
  [0x0612] = sReptilianneSpawnBigPalette,
  [0x0613] = sReptilianneVaskiiBigPalette,
  [0x0614] = sReptilianneViperBigPalette,
  [0x0615] = sReturnOfTheDragonLordsBigPalette,
  [0x0616] = sRiseOfTheSnakeDeityBigPalette,
  [0x0617] = sSecretsOfDarkMagicBigPalette,
  [0x0618] = sSerpentSuppressionBigPalette,
  [0x0619] = sShaddollBeastBigPalette,
  [0x061A] = sShaddollCoreBigPalette,
  [0x061B] = sShaddollDragonBigPalette,
  [0x061C] = sShaddollFalcoBigPalette,
  [0x061D] = sShaddollFusionBigPalette,
  [0x061E] = sShaddollHedgehogBigPalette,
  [0x061F] = sShaddollHoundBigPalette,
  [0x0620] = sShaddollSchismBigPalette,
  [0x0621] = sShaddollSquamataBigPalette,
  [0x0622] = sSilversCryBigPalette,
  [0x0623] = sSnakeDeitysCommandBigPalette,
  [0x0624] = sSnakeRainBigPalette,
  [0x0625] = sSnakeWhistleBigPalette,
  [0x0626] = sSoulServantBigPalette,
  [0x0627] = sStardustDragonBigPalette,
  [0x0628] = sSupremeKingsCastleBigPalette,
  [0x0629] = sThatGrassLooksGreenerBigPalette,
  [0x062A] = sTheDarkMagiciansBigPalette,
  [0x062B] = sTheGazeOfTimaeusBigPalette,
  [0x062C] = sTheMelodyOfAwakeningDragonBigPalette,
  [0x062D] = sTheWhiteStoneOfAncientsBigPalette,
  [0x062E] = sTheWhiteStoneOfLegendBigPalette,
  [0x062F] = sTimeaeusTheUnitedMagicalDragonBigPalette,
  [0x0630] = sTimeausTheUnitedDragonBigPalette,
  [0x0631] = sTohushaddollGrystaBigPalette,
  [0x0632] = sTrapTrickBigPalette,
  [0x0633] = sTriangleEcstasySparkBigPalette,
  [0x0634] = sUltraPolymerizationBigPalette,
  [0x0635] = sVennominagaTheDeityOfPoisonousSnakesBigPalette,
  [0x0636] = sVennominonTheKingOfPoisonousSnakesBigPalette,
  [0x0637] = sVenomBoaBigPalette,
  [0x0638] = sVenomBurnBigPalette,
  [0x0639] = sVenomCobraBigPalette,
  [0x063A] = sVenomSerpentBigPalette,
  [0x063B] = sVenomShotBigPalette,
  [0x063C] = sVenomSnakeBigPalette,
  [0x063D] = sVenomSwampBigPalette,
  [0x063E] = sVipersRebirthBigPalette,
  [0x063F] = sYamorimoriBigPalette,
  [0x0640] = sYowieBigPalette,
  [0x0641] = sAceOfSwordBigPalette,
  [0x0642] = sAceOfWandBigPalette,
  [0x0643] = sArcanaCallBigPalette,
  [0x0644] = sArcanaForce0TheFoolBigPalette,
  [0x0645] = sArcanaForceExTheDarkRulerBigPalette,
  [0x0646] = sArcanaForceExTheLightRulerBigPalette,
  [0x0647] = sArcanaForceITheMagicianBigPalette,
  [0x0648] = sArcanaForceIiiTheEmpressBigPalette,
  [0x0649] = sArcanaForceIvTheEmperorBigPalette,
  [0x064A] = sArcanaForceTheChaosRulerBigPalette,
  [0x064B] = sArcanaForceVTheHierophantBigPalette,
  [0x064C] = sArcanaForceViTheLoversBigPalette,
  [0x064D] = sArcanaForceViiTheChariotBigPalette,
  [0x064E] = sArcanaForceViiiTheStrengthBigPalette,
  [0x064F] = sArcanaForceXiiTheHangmanBigPalette,
  [0x0650] = sArcanaForceXivTemperanceBigPalette,
  [0x0651] = sArcanaForceXixTheSunBigPalette,
  [0x0652] = sArcanaForceXvTheFiendBigPalette,
  [0x0653] = sArcanaForceXviiiTheMoonBigPalette,
  [0x0654] = sArcanaForceXxiTheWorldBigPalette,
  [0x0655] = sArcanaReadingBigPalette,
  [0x0656] = sArcanaSpreadBigPalette,
  [0x0657] = sArmedNeosBigPalette,
  [0x0658] = sAurkusLightswornDruidBigPalette,
  [0x0659] = sCelestiaLightswornAngelBigPalette,
  [0x065A] = sChargeOfTheLightBrigadeBigPalette,
  [0x065B] = sChrysalisChickyBigPalette,
  [0x065C] = sChrysalisDolphinBigPalette,
  [0x065D] = sChrysalisMoleBigPalette,
  [0x065E] = sChrysalisPantailBigPalette,
  [0x065F] = sChrysalisPinnyBigPalette,
  [0x0660] = sCocoonPartyBigPalette,
  [0x0661] = sCocoonRebirthBigPalette,
  [0x0662] = sColosseumCageOfTheGladiatorBeastsBigPalette,
  [0x0663] = sContactBigPalette,
  [0x0664] = sContactGateBigPalette,
  [0x0665] = sConvertContactBigPalette,
  [0x0666] = sCrossKeeperBigPalette,
  [0x0667] = sCuriousTheLightswornDominionBigPalette,
  [0x0668] = sEhrenLightswornMonkBigPalette,
  [0x0669] = sElementalHeroAirNeosBigPalette,
  [0x066A] = sElementalHeroAquaNeosBigPalette,
  [0x066B] = sElementalHeroBraveNeosBigPalette,
  [0x066C] = sElementalHeroChaosNeosBigPalette,
  [0x066D] = sElementalHeroCosmoNeosBigPalette,
  [0x066E] = sElementalHeroDarkNeosBigPalette,
  [0x066F] = sElementalHeroFlareNeosBigPalette,
  [0x0670] = sElementalHeroGlowNeosBigPalette,
  [0x0671] = sElementalHeroGrandNeosBigPalette,
  [0x0672] = sElementalHeroMagmaNeosBigPalette,
  [0x0673] = sElementalHeroMarineNeosBigPalette,
  [0x0674] = sElementalHeroNebulaNeosBigPalette,
  [0x0675] = sElementalHeroShiningNeosWingmanBigPalette,
  [0x0676] = sElementalHeroSpiritOfNeosBigPalette,
  [0x0677] = sElementalHeroStormNeosBigPalette,
  [0x0678] = sEnEngageNeoSpaceBigPalette,
  [0x0679] = sEnShuffleBigPalette,
  [0x067A] = sEnWaveBigPalette,
  [0x067B] = sEnlightenmentDragonBigPalette,
  [0x067C] = sFavouriteContactBigPalette,
  [0x067D] = sFelisLightswornArcherBigPalette,
  [0x067E] = sFlavianColosseumOfTheGladiatorBeastsBigPalette,
  [0x067F] = sGaronithLightswornDragonBigPalette,
  [0x0680] = sGarothLightswornWarriorBigPalette,
  [0x0681] = sGenerationNextBigPalette,
  [0x0682] = sGladiatorBeastAlexanderBigPalette,
  [0x0683] = sGladiatorBeastAndabataBigPalette,
  [0x0684] = sGladiatorBeastAndalBigPalette,
  [0x0685] = sGladiatorBeastAttorixBigPalette,
  [0x0686] = sGladiatorBeastAugustusBigPalette,
  [0x0687] = sGladiatorBeastBattleHalberdBigPalette,
  [0x0688] = sGladiatorBeastBestiariBigPalette,
  [0x0689] = sGladiatorBeastClaudiusBigPalette,
  [0x068A] = sGladiatorBeastDareiosBigPalette,
  [0x068B] = sGladiatorBeastDariusBigPalette,
  [0x068C] = sGladiatorBeastDimacariBigPalette,
  [0x068D] = sGladiatorBeastDomitianusBigPalette,
  [0x068E] = sGladiatorBeastDragasesBigPalette,
  [0x068F] = sGladiatorBeastEquesteBigPalette,
  [0x0690] = sGladiatorBeastEssedariiBigPalette,
  [0x0691] = sGladiatorBeastGaiodiazBigPalette,
  [0x0692] = sGladiatorBeastGistelBigPalette,
  [0x0693] = sGladiatorBeastGyzarusBigPalette,
  [0x0694] = sGladiatorBeastHeraklinosBigPalette,
  [0x0695] = sGladiatorBeastHoplomusBigPalette,
  [0x0696] = sGladiatorBeastLanistaBigPalette,
  [0x0697] = sGladiatorBeastLaquariBigPalette,
  [0x0698] = sGladiatorBeastMurmilloBigPalette,
  [0x0699] = sGladiatorBeastNerokiusBigPalette,
  [0x069A] = sGladiatorBeastNoxiousBigPalette,
  [0x069B] = sGladiatorBeastOctaviusBigPalette,
  [0x069C] = sGladiatorBeastRetiariBigPalette,
  [0x069D] = sGladiatorBeastSagittariiBigPalette,
  [0x069E] = sGladiatorBeastSamniteBigPalette,
  [0x069F] = sGladiatorBeastSecutorBigPalette,
  [0x06A0] = sGladiatorBeastSpartacusBigPalette,
  [0x06A1] = sGladiatorBeastTamerEditorBigPalette,
  [0x06A2] = sGladiatorBeastToraxBigPalette,
  [0x06A3] = sGladiatorBeastTygeriusBigPalette,
  [0x06A4] = sGladiatorBeastVespasiusBigPalette,
  [0x06A5] = sGladiatorBeastWarChariotBigPalette,
  [0x06A6] = sGladiatorBeastsBattleArchfiendShieldBigPalette,
  [0x06A7] = sGladiatorBeastsBattleGladiusBigPalette,
  [0x06A8] = sGladiatorBeastsBattleManicaBigPalette,
  [0x06A9] = sGladiatorBeastsMedusaShieldBigPalette,
  [0x06AA] = sGladiatorBeastsValorBigPalette,
  [0x06AB] = sGladiatorNaumachiaBigPalette,
  [0x06AC] = sGloriousIllusionBigPalette,
  [0x06AD] = sInstantContactBigPalette,
  [0x06AE] = sInstantNeoSpaceBigPalette,
  [0x06AF] = sJainLightswornPaladinBigPalette,
  [0x06B0] = sJainTwilightswornGeneralBigPalette,
  [0x06B1] = sJenisLightswornMenderBigPalette,
  [0x06B2] = sJudgmentTheDragonOfHeavenBigPalette,
  [0x06B3] = sKnightOfPentaclesBigPalette,
  [0x06B4] = sLightBarrierBigPalette,
  [0x06B5] = sLightForceBigPalette,
  [0x06B6] = sLightOfDestructionBigPalette,
  [0x06B7] = sLightSpiralBigPalette,
  [0x06B8] = sLightswornAegisBigPalette,
  [0x06B9] = sLightswornBarrierBigPalette,
  [0x06BA] = sLightswornDragonlingBigPalette,
  [0x06BB] = sLightswornJudgementBigPalette,
  [0x06BC] = sLightswornSabreBigPalette,
  [0x06BD] = sLightswornSanctuaryBigPalette,
  [0x06BE] = sLuminaLightswornSummonerBigPalette,
  [0x06BF] = sLuminaTwilightswornShamanBigPalette,
  [0x06C0] = sLylaLightswornSorceressBigPalette,
  [0x06C1] = sLylaTwilightswornEnchantressBigPalette,
  [0x06C2] = sMarchOfTheDarkBrigadeBigPalette,
  [0x06C3] = sMichaelTheArchLightswornBigPalette,
  [0x06C4] = sMinervaLightswornMaidenBigPalette,
  [0x06C5] = sMinervaTheAthenianLightswornBigPalette,
  [0x06C6] = sMinervaTheExhaltedLightswornBigPalette,
  [0x06C7] = sMiracleContactBigPalette,
  [0x06C8] = sMoonTokenBigPalette,
  [0x06C9] = sNeoSpaceBigPalette,
  [0x06CA] = sNeoSpaceConnectorBigPalette,
  [0x06CB] = sNeoSpacianAirHummingbirdBigPalette,
  [0x06CC] = sNeoSpacianAquaDolphinBigPalette,
  [0x06CD] = sNeoSpacianDarkPantherBigPalette,
  [0x06CE] = sNeoSpacianFlareScarabBigPalette,
  [0x06CF] = sNeoSpacianGlowMossBigPalette,
  [0x06D0] = sNeoSpacianGrandMoleBigPalette,
  [0x06D1] = sNeoSpacianMarineDolphinBigPalette,
  [0x06D2] = sNeoSpacianTwinkleMossBigPalette,
  [0x06D3] = sNexBigPalette,
  [0x06D4] = sNextBigPalette,
  [0x06D5] = sPentacleOfAceBigPalette,
  [0x06D6] = sPunishmentDragonBigPalette,
  [0x06D7] = sRaidenHandOfTheLightswornBigPalette,
  [0x06D8] = sRealmOfLightBigPalette,
  [0x06D9] = sRescueCatBigPalette,
  [0x06DA] = sRescueRabbitBigPalette,
  [0x06DB] = sReversalOfFateBigPalette,
  [0x06DC] = sRinyanLightswornRogueBigPalette,
  [0x06DD] = sRykoLightswornHunterBigPalette,
  [0x06DE] = sRykoTwilightswornFighterBigPalette,
  [0x06DF] = sShireLightswornSpiritBigPalette,
  [0x06E0] = sSolarRechargeBigPalette,
  [0x06E1] = sSuitOfSwordXBigPalette,
  [0x06E2] = sTestBearBigPalette,
  [0x06E3] = sTestPantherBigPalette,
  [0x06E4] = sTestTigerBigPalette,
  [0x06E5] = sThumbsDownBigPalette,
  [0x06E6] = sTourOfDoomBigPalette,
  [0x06E7] = sTrojanGladiatorBeastBigPalette,
  [0x06E8] = sTwilightClothBigPalette,
  [0x06E9] = sTwilightEraserBigPalette,
  [0x06EA] = sTwlightTwinDragonsBigPalette,
  [0x06EB] = sVanquishingLightBigPalette,
  [0x06EC] = sWeissLightswornArchfiendBigPalette,
  [0x06ED] = sWulfLightswornBeastBigPalette,
  [0x06EE] = sAllOutAttacksBigPalette,
  [0x06EF] = sAncientFairyDragonBigPalette,
  [0x06F0] = sAncientGearBigPalette,
  [0x06F1] = sAncientGearAdvanceBigPalette,
  [0x06F2] = sAncientGearBeastBigPalette,
  [0x06F3] = sAncientGearCannonBigPalette,
  [0x06F4] = sAncientGearCastleBigPalette,
  [0x06F5] = sAncientGearCommanderBigPalette,
  [0x06F6] = sAncientGearDarkGolemBigPalette,
  [0x06F7] = sAncientGearDragonBigPalette,
  [0x06F8] = sAncientGearDrillBigPalette,
  [0x06F9] = sAncientGearDuelBigPalette,
  [0x06FA] = sAncientGearEngineerBigPalette,
  [0x06FB] = sAncientGearExplosiveBigPalette,
  [0x06FC] = sAncientGearFactoryBigPalette,
  [0x06FD] = sAncientGearFistBigPalette,
  [0x06FE] = sAncientGearFrameBigPalette,
  [0x06FF] = sAncientGearFusionBigPalette,
  [0x0700] = sAncientGearGadjiltronChimeraBigPalette,
  [0x0701] = sAncientGearGadjiltronDragonBigPalette,
  [0x0702] = sAncientGearGolemBigPalette,
  [0x0703] = sAncientGearGolemUltimatePoundBigPalette,
  [0x0704] = sAncientGearKnightBigPalette,
  [0x0705] = sAncientGearMegatonGolemBigPalette,
  [0x0706] = sAncientGearSoldierBigPalette,
  [0x0707] = sAncientGearStatueBigPalette,
  [0x0708] = sAncientGearTankBigPalette,
  [0x0709] = sAncientGearTankerBigPalette,
  [0x070A] = sAncientGearWorkshopBigPalette,
  [0x070B] = sAncientLeafBigPalette,
  [0x070C] = sAncientSacredWyvernBigPalette,
  [0x070D] = sArcanaKnightJokerBigPalette,
  [0x070E] = sArcaneBarrierBigPalette,
  [0x070F] = sArmityleTheChaosPhantasmBigPalette,
  [0x0710] = sBabycerasaurusBigPalette,
  [0x0711] = sBarrierStatueOfTheStormwindsBigPalette,
  [0x0712] = sBattleManiaBigPalette,
  [0x0713] = sBigEvolutionPillBigPalette,
  [0x0714] = sBlackWingedDragonBigPalette,
  [0x0715] = sBeastMachineKingBarbarosUrBigPalette,
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
  [0x0460] = 0,
  [0x0461] = 0,
  [0x0462] = 0,
  [0x0463] = 0,
  [0x0464] = 0,
  [0x0465] = 0,
  [0x0466] = 0,
  [0x0467] = 0,
  [0x0468] = 0,
  [0x0469] = 0,
  [0x046A] = 0,
  [0x046B] = 0,
  [0x046C] = 0,
  [0x046D] = 0,
  [0x046E] = 0,
  [0x046F] = 0,
  [0x0470] = 0,
  [0x0471] = 0,
  [0x0472] = 0,
  [0x0473] = 0,
  [0x0474] = 0,
  [0x0475] = 0,
  [0x0476] = 0,
  [0x0477] = 0,
  [0x0478] = 0,
  [0x0479] = 0,
  [0x047A] = 0,
  [0x047B] = 0,
  [0x047C] = 0,
  [0x047D] = 0,
  [0x047E] = 0,
  [0x047F] = 0,
  [0x0480] = 0,
  [0x0481] = 0,
  [0x0482] = 0,
  [0x0483] = 0,
  [0x0484] = 0,
  [0x0485] = 0,
  [0x0486] = 0,
  [0x0487] = 0,
  [0x0488] = 0,
  [0x0489] = 0,
  [0x048A] = 0,
  [0x048B] = 0,
  [0x048C] = 0,
  [0x048D] = 0,
  [0x048E] = 0,
  [0x048F] = 0,
  [0x0490] = 0,
  [0x0491] = 0,
  [0x0492] = 0,
  [0x0493] = 0,
  [0x0494] = 0,
  [0x0495] = 0,
  [0x0496] = 0,
  [0x0497] = 0,
  [0x0498] = 0,
  [0x0499] = 0,
  [0x049A] = 0,
  [0x049B] = 0,
  [0x049C] = 0,
  [0x049D] = 0,
  [0x049E] = 0,
  [0x049F] = 0,
  [0x04A0] = 0,
  [0x04A1] = 0,
  [0x04A2] = 0,
  [0x04A3] = 0,
  [0x04A4] = 0,
  [0x04A5] = 0,
  [0x04A6] = 0,
  [0x04A7] = 0,
  [0x04A8] = 0,
  [0x04A9] = 0,
  [0x04AA] = 0,
  [0x04AB] = 0,
  [0x04AC] = 0,
  [0x04AD] = 0,
  [0x04AE] = 0,
  [0x04AF] = 0,
  [0x04B0] = 0,
  [0x04B1] = 0,
  [0x04B2] = 0,
  [0x04B3] = 0,
  [0x04B4] = 0,
  [0x04B5] = 0,
  [0x04B6] = 0,
  [0x04B7] = 0,
  [0x04B8] = 0,
  [0x04B9] = 0,
  [0x04BA] = 0,
  [0x04BB] = 0,
  [0x04BC] = 0,
  [0x04BD] = 0,
  [0x04BE] = 0,
  [0x04BF] = 0,
  [0x04C0] = 0,
  [0x04C1] = 0,
  [0x04C2] = 0,
  [0x04C3] = 0,
  [0x04C4] = 0,
  [0x04C5] = 0,
  [0x04C6] = 0,
  [0x04C7] = 0,
  [0x04C8] = 0,
  [0x04C9] = 0,
  [0x04CA] = 0,
  [0x04CB] = 0,
  [0x04CC] = 0,
  [0x04CD] = 0,
  [0x04CE] = 0,
  [0x04CF] = 0,
  [0x04D0] = 0,
  [0x04D1] = 0,
  [0x04D2] = 0,
  [0x04D3] = 0,
  [0x04D4] = 0,
  [0x04D5] = 0,
  [0x04D6] = 0,
  [0x04D7] = 0,
  [0x04D8] = 0,
  [0x04D9] = 0,
  [0x04DA] = 0,
  [0x04DB] = 0,
  [0x04DC] = 0,
  [0x04DD] = 0,
  [0x04DE] = 0,
  [0x04DF] = 0,
  [0x04E0] = 0,
  [0x04E1] = 0,
  [0x04E2] = 0,
  [0x04E3] = 0,
  [0x04E4] = 0,
  [0x04E5] = 0,
  [0x04E6] = 0,
  [0x04E7] = 0,
  [0x04E8] = 0,
  [0x04E9] = 0,
  [0x04EA] = 0,
  [0x04EB] = 0,
  [0x04EC] = 0,
  [0x04ED] = 0,
  [0x04EE] = 0,
  [0x04EF] = 0,
  [0x04F0] = 0,
  [0x04F1] = 0,
  [0x04F2] = 0,
  [0x04F3] = 0,
  [0x04F4] = 0,
  [0x04F5] = 0,
  [0x04F6] = 0,
  [0x04F7] = 0,
  [0x04F8] = 0,
  [0x04F9] = 0,
  [0x04FA] = 0,
  [0x04FB] = 0,
  [0x04FC] = 0,
  [0x04FD] = 0,
  [0x04FE] = 0,
  [0x04FF] = 0,
  [0x0500] = 0,
  [0x0501] = 0,
  [0x0502] = 0,
  [0x0503] = 0,
  [0x0504] = 0,
  [0x0505] = 0,
  [0x0506] = 0,
  [0x0507] = 0,
  [0x0508] = 0,
  [0x0509] = 1,
  [0x050A] = 0,
  [0x050B] = 0,
  [0x050C] = 0,
  [0x050D] = 0,
  [0x050E] = 0,
  [0x050F] = 0,
  [0x0510] = 0,
  [0x0511] = 0,
  [0x0512] = 0,
  [0x0513] = 0,
  [0x0514] = 0,
  [0x0515] = 0,
  [0x0516] = 0,
  [0x0517] = 0,
  [0x0518] = 0,
  [0x0519] = 0,
  [0x051A] = 0,
  [0x051B] = 0,
  [0x051C] = 0,
  [0x051D] = 0,
  [0x051E] = 0,
  [0x051F] = 0,
  [0x0520] = 0,
  [0x0521] = 0,
  [0x0522] = 0,
  [0x0523] = 0,
  [0x0524] = 0,
  [0x0525] = 0,
  [0x0526] = 0,
  [0x0527] = 0,
  [0x0528] = 0,
  [0x0529] = 0,
  [0x052A] = 0,
  [0x052B] = 0,
  [0x052C] = 0,
  [0x052D] = 0,
  [0x052E] = 0,
  [0x052F] = 0,
  [0x0530] = 0,
  [0x0531] = 0,
  [0x0532] = 0,
  [0x0533] = 0,
  [0x0534] = 0,
  [0x0535] = 0,
  [0x0536] = 0,
  [0x0537] = 0,
  [0x0538] = 0,
  [0x0539] = 0,
  [0x053A] = 0,
  [0x053B] = 0,
  [0x053C] = 0,
  [0x053D] = 0,
  [0x053E] = 0,
  [0x053F] = 0,
  [0x0540] = 0,
  [0x0541] = 0,
  [0x0542] = 0,
  [0x0543] = 0,
  [0x0544] = 0,
  [0x0545] = 0,
  [0x0546] = 0,
  [0x0547] = 0,
  [0x0548] = 0,
  [0x0549] = 0,
  [0x054A] = 0,
  [0x054B] = 0,
  [0x054C] = 0,
  [0x054D] = 0,
  [0x054E] = 0,
  [0x054F] = 0,
  [0x0550] = 0,
  [0x0551] = 0,
  [0x0552] = 0,
  [0x0553] = 0,
  [0x0554] = 0,
  [0x0555] = 0,
  [0x0556] = 0,
  [0x0557] = 0,
  [0x0558] = 0,
  [0x0559] = 0,
  [0x055A] = 0,
  [0x055B] = 0,
  [0x055C] = 0,
  [0x055D] = 0,
  [0x055E] = 0,
  [0x055F] = 0,
  [0x0560] = 0,
  [0x0561] = 0,
  [0x0562] = 0,
  [0x0563] = 0,
  [0x0564] = 0,
  [0x0565] = 0,
  [0x0566] = 0,
  [0x0567] = 0,
  [0x0568] = 0,
  [0x0569] = 0,
  [0x056A] = 0,
  [0x056B] = 0,
  [0x056C] = 0,
  [0x056D] = 0,
  [0x056E] = 0,
  [0x056F] = 0,
  [0x0570] = 0,
  [0x0571] = 0,
  [0x0572] = 0,
  [0x0573] = 0,
  [0x0574] = 0,
  [0x0575] = 0,
  [0x0576] = 0,
  [0x0577] = 0,
  [0x0578] = 0,
  [0x0579] = 0,
  [0x057A] = 0,
  [0x057B] = 0,
  [0x057C] = 0,
  [0x057D] = 0,
  [0x057E] = 0,
  [0x057F] = 0,
  [0x0580] = 0,
  [0x0581] = 0,
  [0x0582] = 0,
  [0x0583] = 0,
  [0x0584] = 0,
  [0x0585] = 0,
  [0x0586] = 0,
  [0x0587] = 0,
  [0x0588] = 0,
  [0x0589] = 0,
  [0x058A] = 0,
  [0x058B] = 0,
  [0x058C] = 0,
  [0x058D] = 0,
  [0x058E] = 0,
  [0x058F] = 0,
  [0x0590] = 0,
  [0x0591] = 0,
  [0x0592] = 0,
  [0x0593] = 0,
  [0x0594] = 0,
  [0x0595] = 0,
  [0x0596] = 0,
  [0x0597] = 0,
  [0x0598] = 0,
  [0x0599] = 0,
  [0x059A] = 0,
  [0x059B] = 0,
  [0x059C] = 0,
  [0x059D] = 0,
  [0x059E] = 0,
  [0x059F] = 0,
  [0x05A0] = 0,
  [0x05A1] = 0,
  [0x05A2] = 0,
  [0x05A3] = 0,
  [0x05A4] = 0,
  [0x05A5] = 0,
  [0x05A6] = 0,
  [0x05A7] = 0,
  [0x05A8] = 0,
  [0x05A9] = 0,
  [0x05AA] = 0,
  [0x05AB] = 0,
  [0x05AC] = 0,
  [0x05AD] = 0,
  [0x05AE] = 0,
  [0x05AF] = 0,
  [0x05B0] = 0,
  [0x05B1] = 0,
  [0x05B2] = 0,
  [0x05B3] = 0,
  [0x05B4] = 0,
  [0x05B5] = 0,
  [0x05B6] = 0,
  [0x05B7] = 0,
  [0x05B8] = 0,
  [0x05B9] = 0,
  [0x05BA] = 0,
  [0x05BB] = 0,
  [0x05BC] = 0,
  [0x05BD] = 0,
  [0x05BE] = 0,
  [0x05BF] = 0,
  [0x05C0] = 0,
  [0x05C1] = 0,
  [0x05C2] = 0,
  [0x05C3] = 0,
  [0x05C4] = 0,
  [0x05C5] = 0,
  [0x05C6] = 0,
  [0x05C7] = 0,
  [0x05C8] = 0,
  [0x05C9] = 0,
  [0x05CA] = 0,
  [0x05CB] = 0,
  [0x05CC] = 0,
  [0x05CD] = 0,
  [0x05CE] = 0,
  [0x05CF] = 0,
  [0x05D0] = 0,
  [0x05D1] = 0,
  [0x05D2] = 0,
  [0x05D3] = 0,
  [0x05D4] = 0,
  [0x05D5] = 0,
  [0x05D6] = 0,
  [0x05D7] = 0,
  [0x05D8] = 0,
  [0x05D9] = 0,
  [0x05DA] = 0,
  [0x05DB] = 0,
  [0x05DC] = 0,
  [0x05DD] = 0,
  [0x05DE] = 0,
  [0x05DF] = 0,
  [0x05E0] = 0,
  [0x05E1] = 0,
  [0x05E2] = 0,
  [0x05E3] = 0,
  [0x05E4] = 0,
  [0x05E5] = 0,
  [0x05E6] = 0,
  [0x05E7] = 0,
  [0x05E8] = 0,
  [0x05E9] = 0,
  [0x05EA] = 0,
  [0x05EB] = 0,
  [0x05EC] = 0,
  [0x05ED] = 0,
  [0x05EE] = 0,
  [0x05EF] = 0,
  [0x05F0] = 0,
  [0x05F1] = 0,
  [0x05F2] = 0,
  [0x05F3] = 0,
  [0x05F4] = 0,
  [0x05F5] = 0,
  [0x05F6] = 0,
  [0x05F7] = 0,
  [0x05F8] = 0,
  [0x05F9] = 0,
  [0x05FA] = 0,
  [0x05FB] = 0,
  [0x05FC] = 0,
  [0x05FD] = 0,
  [0x05FE] = 0,
  [0x05FF] = 0,
  [0x0600] = 0,
  [0x0601] = 0,
  [0x0602] = 0,
  [0x0603] = 0,
  [0x0604] = 0,
  [0x0605] = 0,
  [0x0606] = 0,
  [0x0607] = 0,
  [0x0608] = 0,
  [0x0609] = 0,
  [0x060A] = 0,
  [0x060B] = 0,
  [0x060C] = 0,
  [0x060D] = 0,
  [0x060E] = 0,
  [0x060F] = 0,
  [0x0610] = 0,
  [0x0611] = 0,
  [0x0612] = 0,
  [0x0613] = 0,
  [0x0614] = 0,
  [0x0615] = 0,
  [0x0616] = 0,
  [0x0617] = 0,
  [0x0618] = 0,
  [0x0619] = 0,
  [0x061A] = 0,
  [0x061B] = 0,
  [0x061C] = 0,
  [0x061D] = 0,
  [0x061E] = 0,
  [0x061F] = 0,
  [0x0620] = 0,
  [0x0621] = 0,
  [0x0622] = 0,
  [0x0623] = 0,
  [0x0624] = 0,
  [0x0625] = 0,
  [0x0626] = 0,
  [0x0627] = 0,
  [0x0628] = 0,
  [0x0629] = 0,
  [0x062A] = 0,
  [0x062B] = 0,
  [0x062C] = 0,
  [0x062D] = 0,
  [0x062E] = 0,
  [0x062F] = 0,
  [0x0630] = 0,
  [0x0631] = 0,
  [0x0632] = 0,
  [0x0633] = 0,
  [0x0634] = 0,
  [0x0635] = 0,
  [0x0636] = 0,
  [0x0637] = 0,
  [0x0638] = 0,
  [0x0639] = 0,
  [0x063A] = 0,
  [0x063B] = 0,
  [0x063C] = 0,
  [0x063D] = 0,
  [0x063E] = 0,
  [0x063F] = 0,
  [0x0640] = 0,
  [0x0641] = 0,
  [0x0642] = 0,
  [0x0643] = 0,
  [0x0644] = 0,
  [0x0645] = 0,
  [0x0646] = 0,
  [0x0647] = 0,
  [0x0648] = 0,
  [0x0649] = 0,
  [0x064A] = 0,
  [0x064B] = 0,
  [0x064C] = 0,
  [0x064D] = 0,
  [0x064E] = 0,
  [0x064F] = 0,
  [0x0650] = 0,
  [0x0651] = 0,
  [0x0652] = 0,
  [0x0653] = 0,
  [0x0654] = 0,
  [0x0655] = 0,
  [0x0656] = 0,
  [0x0657] = 0,
  [0x0658] = 0,
  [0x0659] = 0,
  [0x065A] = 0,
  [0x065B] = 0,
  [0x065C] = 0,
  [0x065D] = 0,
  [0x065E] = 0,
  [0x065F] = 0,
  [0x0660] = 0,
  [0x0661] = 0,
  [0x0662] = 0,
  [0x0663] = 0,
  [0x0664] = 0,
  [0x0665] = 0,
  [0x0666] = 0,
  [0x0667] = 0,
  [0x0668] = 0,
  [0x0669] = 0,
  [0x066A] = 0,
  [0x066B] = 0,
  [0x066C] = 0,
  [0x066D] = 0,
  [0x066E] = 0,
  [0x066F] = 0,
  [0x0670] = 0,
  [0x0671] = 0,
  [0x0672] = 0,
  [0x0673] = 0,
  [0x0674] = 0,
  [0x0675] = 0,
  [0x0676] = 0,
  [0x0677] = 0,
  [0x0678] = 0,
  [0x0679] = 0,
  [0x067A] = 0,
  [0x067B] = 0,
  [0x067C] = 0,
  [0x067D] = 0,
  [0x067E] = 0,
  [0x067F] = 0,
  [0x0680] = 0,
  [0x0681] = 0,
  [0x0682] = 0,
  [0x0683] = 0,
  [0x0684] = 0,
  [0x0685] = 0,
  [0x0686] = 0,
  [0x0687] = 0,
  [0x0688] = 0,
  [0x0689] = 0,
  [0x068A] = 0,
  [0x068B] = 0,
  [0x068C] = 0,
  [0x068D] = 0,
  [0x068E] = 0,
  [0x068F] = 0,
  [0x0690] = 0,
  [0x0691] = 0,
  [0x0692] = 0,
  [0x0693] = 0,
  [0x0694] = 0,
  [0x0695] = 0,
  [0x0696] = 0,
  [0x0697] = 0,
  [0x0698] = 0,
  [0x0699] = 0,
  [0x069A] = 0,
  [0x069B] = 0,
  [0x069C] = 0,
  [0x069D] = 0,
  [0x069E] = 0,
  [0x069F] = 0,
  [0x06A0] = 0,
  [0x06A1] = 0,
  [0x06A2] = 0,
  [0x06A3] = 0,
  [0x06A4] = 0,
  [0x06A5] = 0,
  [0x06A6] = 0,
  [0x06A7] = 0,
  [0x06A8] = 0,
  [0x06A9] = 0,
  [0x06AA] = 0,
  [0x06AB] = 0,
  [0x06AC] = 0,
  [0x06AD] = 0,
  [0x06AE] = 0,
  [0x06AF] = 0,
  [0x06B0] = 0,
  [0x06B1] = 0,
  [0x06B2] = 0,
  [0x06B3] = 0,
  [0x06B4] = 0,
  [0x06B5] = 0,
  [0x06B6] = 0,
  [0x06B7] = 0,
  [0x06B8] = 0,
  [0x06B9] = 0,
  [0x06BA] = 0,
  [0x06BB] = 0,
  [0x06BC] = 0,
  [0x06BD] = 0,
  [0x06BE] = 0,
  [0x06BF] = 0,
  [0x06C0] = 0,
  [0x06C1] = 0,
  [0x06C2] = 0,
  [0x06C3] = 0,
  [0x06C4] = 0,
  [0x06C5] = 0,
  [0x06C6] = 0,
  [0x06C7] = 0,
  [0x06C8] = 0,
  [0x06C9] = 0,
  [0x06CA] = 0,
  [0x06CB] = 0,
  [0x06CC] = 0,
  [0x06CD] = 0,
  [0x06CE] = 0,
  [0x06CF] = 0,
  [0x06D0] = 0,
  [0x06D1] = 0,
  [0x06D2] = 0,
  [0x06D3] = 0,
  [0x06D4] = 0,
  [0x06D5] = 0,
  [0x06D6] = 0,
  [0x06D7] = 0,
  [0x06D8] = 0,
  [0x06D9] = 0,
  [0x06DA] = 0,
  [0x06DB] = 0,
  [0x06DC] = 0,
  [0x06DD] = 0,
  [0x06DE] = 0,
  [0x06DF] = 0,
  [0x06E0] = 0,
  [0x06E1] = 0,
  [0x06E2] = 0,
  [0x06E3] = 0,
  [0x06E4] = 0,
  [0x06E5] = 0,
  [0x06E6] = 0,
  [0x06E7] = 0,
  [0x06E8] = 0,
  [0x06E9] = 0,
  [0x06EA] = 0,
  [0x06EB] = 0,
  [0x06EC] = 0,
  [0x06ED] = 0,
  [0x06EE] = 0,
  [0x06EF] = 0,
  [0x06F0] = 0,
  [0x06F1] = 0,
  [0x06F2] = 0,
  [0x06F3] = 0,
  [0x06F4] = 0,
  [0x06F5] = 0,
  [0x06F6] = 0,
  [0x06F7] = 0,
  [0x06F8] = 0,
  [0x06F9] = 0,
  [0x06FA] = 0,
  [0x06FB] = 0,
  [0x06FC] = 0,
  [0x06FD] = 0,
  [0x06FE] = 0,
  [0x06FF] = 0,
  [0x0700] = 0,
  [0x0701] = 0,
  [0x0702] = 0,
  [0x0703] = 0,
  [0x0704] = 0,
  [0x0705] = 0,
  [0x0706] = 0,
  [0x0707] = 0,
  [0x0708] = 0,
  [0x0709] = 0,
  [0x070A] = 0,
  [0x070B] = 0,
  [0x070C] = 0,
  [0x070D] = 0,
  [0x070E] = 0,
  [0x070F] = 0,
  [0x0710] = 0,
  [0x0711] = 0,
  [0x0712] = 0,
  [0x0713] = 0,
  [0x0714] = 0,
  [0x0715] = 0,
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
  [0x0460] = sTheWickedDreadrootMiniArt,
  [0x0461] = sTheWickedEraserMiniArt,
  [0x0462] = sTheWickedAvatarMiniArt,
  [0x0463] = sTributeDollMiniArt,
  [0x0464] = sTradeInMiniArt,
  [0x0465] = sCyberBarrierDragonMiniArt,
  [0x0466] = sCyberLaserDragonMiniArt,
  [0x0467] = sDarkEndDragonMiniArt,
  [0x0468] = sLightEndDragonMiniArt,
  [0x0469] = sDarkArmedDragonMiniArt,
  [0x046A] = sAHeroEmergesMiniArt,
  [0x046B] = sAHeroLivesMiniArt,
  [0x046C] = sAWingbeatOfGiantDragonMiniArt,
  [0x046D] = sAllureOfDarknessMiniArt,
  [0x046E] = sAmuletDragonMiniArt,
  [0x046F] = sAndroSphinxMiniArt,
  [0x0470] = sAntiSpellFragranceMiniArt,
  [0x0471] = sAppropriateMiniArt,
  [0x0472] = sApprenticeIllusionMagicianMiniArt,
  [0x0473] = sApparationMiniArt,
  [0x0474] = sAttackGuidanceArmorMiniArt,
  [0x0475] = sAttackReflectorUnitMiniArt,
  [0x0476] = sBackupSquadMiniArt,
  [0x0477] = sArmageddonKnightMiniArt,
  [0x0478] = sArmedDragonLv3MiniArt,
  [0x0479] = sArmedDragonLv5MiniArt,
  [0x047A] = sArmedDragonLv7MiniArt,
  [0x047B] = sArmedDragonLv10MiniArt,
  [0x047C] = sAttackAndReceiveMiniArt,
  [0x047D] = sBackfireMiniArt,
  [0x047E] = sHamonLordOfStrikingThunderMiniArt,
  [0x047F] = sUriaLordOfSearingFlamesMiniArt,
  [0x0480] = sRavielLordOfPhantasmsMiniArt,
  [0x0481] = sBerserkerSoulMiniArt,
  [0x0482] = sBirdfaceMiniArt,
  [0x0483] = sBlueEyesAlternativeUltimateDragonMiniArt,
  [0x0484] = sBreakTheDestinyMiniArt,
  [0x0485] = sBubbleBlasterMiniArt,
  [0x0486] = sBurdenOfTheMightyMiniArt,
  [0x0487] = sCallOfTheMummyMiniArt,
  [0x0488] = sCannonballSpearShellfishMiniArt,
  [0x0489] = sCelestialSwordEatosMiniArt,
  [0x048A] = sChaosFormMiniArt,
  [0x048B] = sChickenGameMiniArt,
  [0x048C] = sChimeratechFortressDragonMiniArt,
  [0x048D] = sChimeratechMegafleetDragonMiniArt,
  [0x048E] = sChimeratechRampageDragonMiniArt,
  [0x048F] = sClockTowerPrisonMiniArt,
  [0x0490] = sColdWaveMiniArt,
  [0x0491] = sContinuousDestructionPunchMiniArt,
  [0x0492] = sCyberEltaninMiniArt,
  [0x0493] = sCyberKirinMiniArt,
  [0x0494] = sCyberPhoenixMiniArt,
  [0x0495] = sCyberValleyMiniArt,
  [0x0496] = sCyberneticZoneMiniArt,
  [0x0497] = sDTacticsMiniArt,
  [0x0498] = sDTimeMiniArt,
  [0x0499] = sDamagePolarizerMiniArt,
  [0x049A] = sDBurstMiniArt,
  [0x049B] = sDForceMiniArt,
  [0x049C] = sDarkBladeTheDragonKnightMiniArt,
  [0x049D] = sDarkGrepherMiniArt,
  [0x049E] = sDarkMagicianGirlTheDragonKnightMiniArt,
  [0x049F] = sDarklordNurseReficuleMiniArt,
  [0x04A0] = sDarknessNeosphereMiniArt,
  [0x04A1] = sDarkCityAtMidnightMiniArt,
  [0x04A2] = sDarkMagicianTheDragonKnightMiniArt,
  [0x04A3] = sDecoyDragonMiniArt,
  [0x04A4] = sDesCounterblowMiniArt,
  [0x04A5] = sDespairFromTheDarkMiniArt,
  [0x04A6] = sDestinyDrawMiniArt,
  [0x04A7] = sDestinyEndDragoonMiniArt,
  [0x04A8] = sDestinyHeroBladeMasterMiniArt,
  [0x04A9] = sDestinyHeroCaptainTenaciousMiniArt,
  [0x04AA] = sDestinyHeroCelestialMiniArt,
  [0x04AB] = sDestinyHeroDangerousMiniArt,
  [0x04AC] = sDestinyHeroDarkAngelMiniArt,
  [0x04AD] = sDestinyHeroDasherMiniArt,
  [0x04AE] = sDestinyHeroDeciderMiniArt,
  [0x04AF] = sDestinyHeroDefenderMiniArt,
  [0x04B0] = sDestinyHeroDenierMiniArt,
  [0x04B1] = sDestinyHeroDestroyerPhoenixEnforcerMiniArt,
  [0x04B2] = sDestinyHeroDiamondDudeMiniArt,
  [0x04B3] = sDestinyHeroDiskCommanderMiniArt,
  [0x04B4] = sDestinyHeroDogmaMiniArt,
  [0x04B5] = sDestinyHeroDominanceMiniArt,
  [0x04B6] = sDestinyHeroDoomLordMiniArt,
  [0x04B7] = sDestinyHeroDoubleDudeMiniArt,
  [0x04B8] = sDestinyHeroDrawhandMiniArt,
  [0x04B9] = sDestinyHeroDreadServantMiniArt,
  [0x04BA] = sDestinyHeroDreadmasterMiniArt,
  [0x04BB] = sDestinyHeroDoomOverlordMiniArt,
  [0x04BC] = sDestinyHeroDreadnoughtMasterMiniArt,
  [0x04BD] = sDestinyHeroDreadnoughtServantMiniArt,
  [0x04BE] = sDestinyHeroDreamerMiniArt,
  [0x04BF] = sDestinyHeroDrilldarkMiniArt,
  [0x04C0] = sDestinyHeroDunkerMiniArt,
  [0x04C1] = sDestinyHeroDynatagMiniArt,
  [0x04C2] = sDestinyHeroDystopiaMiniArt,
  [0x04C3] = sDestinyHeroFearMongerMiniArt,
  [0x04C4] = sDestinyHeroMaliciousMiniArt,
  [0x04C5] = sDestinyHeroPlasmaMiniArt,
  [0x04C6] = sDifferentDimensionCapsuleMiniArt,
  [0x04C7] = sDestinyHeroDusktopiaMiniArt,
  [0x04C8] = sDimensionFusionMiniArt,
  [0x04C9] = sDivineSerpentGehMiniArt,
  [0x04CA] = sDonZaloogMiniArt,
  [0x04CB] = sDoubleSpellMiniArt,
  [0x04CC] = sDragonSRageMiniArt,
  [0x04CD] = sDestinyHeroDestroyDogmaMiniArt,
  [0x04CE] = sDoctorDMiniArt,
  [0x04CF] = sDoomVirusDragonMiniArt,
  [0x04D0] = sDoppelgangerMiniArt,
  [0x04D1] = sEgyptianGodSlimeMiniArt,
  [0x04D2] = sElementalHeroNeosKlugerMiniArt,
  [0x04D3] = sEmergencyProvisionsMiniArt,
  [0x04D4] = sExodiusTheUltimateForbiddenLordMiniArt,
  [0x04D5] = sFatalAbacusMiniArt,
  [0x04D6] = sFelgrandDragonMiniArt,
  [0x04D7] = sFiresOfDoomsdayMiniArt,
  [0x04D8] = sForcedRequisitionMiniArt,
  [0x04D9] = sDrainTimeMiniArt,
  [0x04DA] = sFieldsSanctuaryMiniArt,
  [0x04DB] = sFusionDestinyMiniArt,
  [0x04DC] = sFusionGateMiniArt,
  [0x04DD] = sGateGuardiansCombinedMiniArt,
  [0x04DE] = sGiftCardMiniArt,
  [0x04DF] = sGoddessBowMiniArt,
  [0x04E0] = sGorzTheEmissaryOfDarknessMiniArt,
  [0x04E1] = sGranmargTheRockMonarchMiniArt,
  [0x04E2] = sGreenGadgetMiniArt,
  [0x04E3] = sGroundCollapseMiniArt,
  [0x04E4] = sGuardianDreadscytheMiniArt,
  [0x04E5] = sHarpieLadyPhoenixFormationMiniArt,
  [0x04E6] = sHeroFlashMiniArt,
  [0x04E7] = sInsectImitationMiniArt,
  [0x04E8] = sInstantFusionMiniArt,
  [0x04E9] = sGuardianEatosMiniArt,
  [0x04EA] = sHeraldOfCreationMiniArt,
  [0x04EB] = sHolactieTheCreatorOfLightMiniArt,
  [0x04EC] = sHorusTheBlackFlameDragonLv8MiniArt,
  [0x04ED] = sHorusTheBlackFlameDragonLv4MiniArt,
  [0x04EE] = sHorusTheBlackFlameDragonLv6MiniArt,
  [0x04EF] = sJowgenTheSpiritualistMiniArt,
  [0x04F0] = sJudgmentDragonMiniArt,
  [0x04F1] = sKingDragunMiniArt,
  [0x04F2] = sKingOfTheSwampMiniArt,
  [0x04F3] = sKurazTheLightMonarchMiniArt,
  [0x04F4] = sKuribanditMiniArt,
  [0x04F5] = sLastTurnMiniArt,
  [0x04F6] = sLegendOfHeartMiniArt,
  [0x04F7] = sLegendaryFlameLordMiniArt,
  [0x04F8] = sKingTigerWanghuMiniArt,
  [0x04F9] = sLegendaryKnightCritiasMiniArt,
  [0x04FA] = sLegendaryKnightHermosMiniArt,
  [0x04FB] = sLegendaryKnightTimaeusMiniArt,
  [0x04FC] = sLekungaMiniArt,
  [0x04FD] = sLightAndDarknessDragonMiniArt,
  [0x04FE] = sLordOfTheRedMiniArt,
  [0x04FF] = sMaAtMiniArt,
  [0x0500] = sMagicalDimensionMiniArt,
  [0x0501] = sMagicalHatsMiniArt,
  [0x0502] = sMagicalPlantMandragolaMiniArt,
  [0x0503] = sMagicalScientistMiniArt,
  [0x0504] = sMagicalStoneExcavationMiniArt,
  [0x0505] = sMajesticMechGoryuMiniArt,
  [0x0506] = sManjuOfTheTenThousandHandsMiniArt,
  [0x0507] = sMarshmallonMiniArt,
  [0x0508] = sMaskOfDispelMiniArt,
  [0x0509] = sMasterPeaceTheTrueDracoslayingKingMiniArt,
  [0x050A] = sMaskOfTheAccursedMiniArt,
  [0x050B] = sMausoleumOfTheEmperorMiniArt,
  [0x050C] = sMazeraDevilleMiniArt,
  [0x050D] = sMetamorphosisMiniArt,
  [0x050E] = sMeteorainMiniArt,
  [0x050F] = sMirageOfNightmareMiniArt,
  [0x0510] = sMirrorForceDragonMiniArt,
  [0x0511] = sMoltenZombieMiniArt,
  [0x0512] = sMonsterGateMiniArt,
  [0x0513] = sMonsterRecoveryMiniArt,
  [0x0514] = sMoraleBoostMiniArt,
  [0x0515] = sMucusYolkMiniArt,
  [0x0516] = sMystikWokMiniArt,
  [0x0517] = sNecrovalleyMiniArt,
  [0x0518] = sNeedleWallMiniArt,
  [0x0519] = sNeoBlueEyesUltimateDragonMiniArt,
  [0x051A] = sNeosWisemanMiniArt,
  [0x051B] = sNibiruThePrimalBeingMiniArt,
  [0x051C] = sNuminousHealerMiniArt,
  [0x051D] = sOjamaKingMiniArt,
  [0x051E] = sOrichalcosShunorosMiniArt,
  [0x051F] = sOverDestinyMiniArt,
  [0x0520] = sPainfulChoiceMiniArt,
  [0x0521] = sPandemoniumMiniArt,
  [0x0522] = sParallelWorldFusionMiniArt,
  [0x0523] = sPhotonGeneratorUnitMiniArt,
  [0x0524] = sPoisonOfTheOldManMiniArt,
  [0x0525] = sProtectorOfTheSanctuaryMiniArt,
  [0x0526] = sQuintetMagicianMiniArt,
  [0x0527] = sRaigekiBreakMiniArt,
  [0x0528] = sProphecyMiniArt,
  [0x0529] = sReaperScytheDreadscytheMiniArt,
  [0x052A] = sRedEyesBlackDragonSwordMiniArt,
  [0x052B] = sRedEyesDarkDragoonMiniArt,
  [0x052C] = sRedEyesDarknessMetalDragonMiniArt,
  [0x052D] = sRedEyesTransmigrationMiniArt,
  [0x052E] = sRedGadgetMiniArt,
  [0x052F] = sRelaySoulMiniArt,
  [0x0530] = sReverseOfReverseMiniArt,
  [0x0531] = sRocketHermosCannonMiniArt,
  [0x0532] = sRopeOfLifeMiniArt,
  [0x0533] = sRoyalMagicalLibraryMiniArt,
  [0x0534] = sScapegoatMiniArt,
  [0x0535] = sSecondCoinTossMiniArt,
  [0x0536] = sSecretVillageOfTheSpellcastersMiniArt,
  [0x0537] = sShareThePainMiniArt,
  [0x0538] = sSixthSenseMiniArt,
  [0x0539] = sSkilledDarkMagicianMiniArt,
  [0x053A] = sSkilledWhiteMagicianMiniArt,
  [0x053B] = sSolemnJudgmentMiniArt,
  [0x053C] = sSparkBlasterMiniArt,
  [0x053D] = sSkyscraper2HeroCityMiniArt,
  [0x053E] = sSpellAbsorptionMiniArt,
  [0x053F] = sSphinxTeleiaMiniArt,
  [0x0540] = sStatueOfTheWickedMiniArt,
  [0x0541] = sStaunchDefenderMiniArt,
  [0x0542] = sStrayLambsMiniArt,
  [0x0543] = sStrongholdTheMovingFortressMiniArt,
  [0x0544] = sSummonerMonkMiniArt,
  [0x0545] = sSummonerOfIllusionsMiniArt,
  [0x0546] = sSuperPolymerizationMiniArt,
  [0x0547] = sTerraformingMiniArt,
  [0x0548] = sTheAForcesMiniArt,
  [0x0549] = sTheAgentOfJudgmentSaturnMiniArt,
  [0x054A] = sTheAgentOfWisdomMercuryMiniArt,
  [0x054B] = sTheClawOfHermosMiniArt,
  [0x054C] = sTheCreatorMiniArt,
  [0x054D] = sTheCreatorIncarnateMiniArt,
  [0x054E] = sTheEyeOfTimaeusMiniArt,
  [0x054F] = sTheFangOfCritiasMiniArt,
  [0x0550] = sTheLawOfTheNormalMiniArt,
  [0x0551] = sTheLegendaryExodiaIncarnateMiniArt,
  [0x0552] = sTheShallowGraveMiniArt,
  [0x0553] = sTheinenTheGreatSphinxMiniArt,
  [0x0554] = sThestalosTheFirestormMonarchMiniArt,
  [0x0555] = sThunderDragonColossusMiniArt,
  [0x0556] = sThunderDragonTitanMiniArt,
  [0x0557] = sTimaeusTheKnightOfDestinyMiniArt,
  [0x0558] = sTimeMagicHammerMiniArt,
  [0x0559] = sTornadoWallMiniArt,
  [0x055A] = sToonWorldMiniArt,
  [0x055B] = sTornadoBirdMiniArt,
  [0x055C] = sTrapDustshootMiniArt,
  [0x055D] = sTyrantBurstDragonMiniArt,
  [0x055E] = sTyrantWingMiniArt,
  [0x055F] = sUltimateConductorTyrannoMiniArt,
  [0x0560] = sUltimateObedientFiendMiniArt,
  [0x0561] = sVisionFusionMiniArt,
  [0x0562] = sVisionHeroAdorationMiniArt,
  [0x0563] = sVisionHeroFarisMiniArt,
  [0x0564] = sVisionHeroGravitoMiniArt,
  [0x0565] = sVisionHeroIncreaseMiniArt,
  [0x0566] = sVisionHeroMinimumRayMiniArt,
  [0x0567] = sVisionHeroMultiplyGuyMiniArt,
  [0x0568] = sVisionHeroPoisonerMiniArt,
  [0x0569] = sVisionHeroTrinityMiniArt,
  [0x056A] = sVisionHeroVyonMiniArt,
  [0x056B] = sVisionReleaseMiniArt,
  [0x056C] = sWataponMiniArt,
  [0x056D] = sWhiteDragonRitualMiniArt,
  [0x056E] = sWildNaturesReleaseMiniArt,
  [0x056F] = sWoughtweilerMiniArt,
  [0x0570] = sYellowGadgetMiniArt,
  [0x0571] = sVisionHeroWitchRaiderMiniArt,
  [0x0572] = sAlluringMirrorSplitMiniArt,
  [0x0573] = sAmbushFangsMiniArt,
  [0x0574] = sArcaniteMagicianMiniArt,
  [0x0575] = sArmoryArmMiniArt,
  [0x0576] = sAromaBlendMiniArt,
  [0x0577] = sAromaGardenMiniArt,
  [0x0578] = sAromaGardeningMiniArt,
  [0x0579] = sAromaJarMiniArt,
  [0x057A] = sAromageBergamotMiniArt,
  [0x057B] = sAromageCanangaMiniArt,
  [0x057C] = sAromageJasmineMiniArt,
  [0x057D] = sAromageLaurelMiniArt,
  [0x057E] = sAromageMarjoramMiniArt,
  [0x057F] = sAromageRosemaryMiniArt,
  [0x0580] = sAromalilithMagnoliaMiniArt,
  [0x0581] = sAromalilithRosalinaMiniArt,
  [0x0582] = sAromalilithRosemaryMiniArt,
  [0x0583] = sAromaseraphyJasmineMiniArt,
  [0x0584] = sAromaseraphyRosemaryMiniArt,
  [0x0585] = sAromaseraphySweetMarjoramMiniArt,
  [0x0586] = sAttackPheromonesMiniArt,
  [0x0587] = sAzureEyesSilverDragonMiniArt,
  [0x0588] = sBlackRoseDragonMiniArt,
  [0x0589] = sBlessedWindsMiniArt,
  [0x058A] = sBlueEyesJetDragonMiniArt,
  [0x058B] = sBlueEyesSolidDragonMiniArt,
  [0x058C] = sBlueEyesTyrantDragonMiniArt,
  [0x058D] = sBlueEyesUltimateSpiritDragonMiniArt,
  [0x058E] = sBondBetweenTeacherAndStudentMiniArt,
  [0x058F] = sBlueEyesSpiritDragonMiniArt,
  [0x0590] = sBrionacDragonOfTheIceBarrierMiniArt,
  [0x0591] = sChainMaterialMiniArt,
  [0x0592] = sColossalFighterMiniArt,
  [0x0593] = sCupOfAceMiniArt,
  [0x0594] = sCyberSlashHarpieLadyMiniArt,
  [0x0595] = sDamageReptileMiniArt,
  [0x0596] = sDarkBurningAttackMiniArt,
  [0x0597] = sDarkBurningMagicMiniArt,
  [0x0598] = sDarkCallingMiniArt,
  [0x0599] = sDarkContactMiniArt,
  [0x059A] = sDarkFusionMiniArt,
  [0x059B] = sDarkMagicAttackMiniArt,
  [0x059C] = sDarkMagicInheritanceMiniArt,
  [0x059D] = sDarkMagicVeilMiniArt,
  [0x059E] = sDarkMagicalCircleMiniArt,
  [0x059F] = sDarkMagicianGirlTheMagicianSApprenticeMiniArt,
  [0x05A0] = sDarkMagicianOfDestructionMiniArt,
  [0x05A1] = sDarkMagicianTheMagicianOfBlackMagicMiniArt,
  [0x05A2] = sDarkRenewalMiniArt,
  [0x05A3] = sDarkStrikeFighterMiniArt,
  [0x05A4] = sDarkSupremacyMiniArt,
  [0x05A5] = sDestinedRivalsMiniArt,
  [0x05A6] = sDriedWindsMiniArt,
  [0x05A7] = sDragonRavineMiniArt,
  [0x05A8] = sDragonShrineMiniArt,
  [0x05A9] = sDeepEyesWhiteDragonMiniArt,
  [0x05AA] = sDragonMasterMagiaMiniArt,
  [0x05AB] = sDragonSpiritOfWhiteMiniArt,
  [0x05AC] = sEbonIllusionMagicianMiniArt,
  [0x05AD] = sElShaddollAnoyatyllisMiniArt,
  [0x05AE] = sElShaddollApkalloneMiniArt,
  [0x05AF] = sElShaddollConstructMiniArt,
  [0x05B0] = sElShaddollFusionMiniArt,
  [0x05B1] = sElShaddollGrystaMiniArt,
  [0x05B2] = sElShaddollMeshahrailMiniArt,
  [0x05B3] = sElShaddollShekhinagaMiniArt,
  [0x05B4] = sElShaddollWendigoMiniArt,
  [0x05B5] = sElShaddollWindaMiniArt,
  [0x05B6] = sEternalSoulMiniArt,
  [0x05B7] = sEvilAssaultMiniArt,
  [0x05B8] = sEvilDragonAnantaMiniArt,
  [0x05B9] = sEvilHeroAdustedGoldMiniArt,
  [0x05BA] = sEvilHeroDarkGaiaMiniArt,
  [0x05BB] = sEvilHeroDarkestKnightMiniArt,
  [0x05BC] = sEvilHeroDeadEndPrisonMiniArt,
  [0x05BD] = sEvilHeroInfernalGainerMiniArt,
  [0x05BE] = sEvilHeroInfernalProdigyMiniArt,
  [0x05BF] = sEvilHeroInfernalRiderMiniArt,
  [0x05C0] = sEvilHeroInfernalSniperMiniArt,
  [0x05C1] = sEvilHeroInfernoWingMiniArt,
  [0x05C2] = sEvilHeroInfernoWingBackfireMiniArt,
  [0x05C3] = sEvilHeroLightningGolemMiniArt,
  [0x05C4] = sEvilHeroMaliciousBaneMiniArt,
  [0x05C5] = sEvilHeroMaliciousEdgeMiniArt,
  [0x05C6] = sEvilHeroMaliciousFiendMiniArt,
  [0x05C7] = sEvilHeroNeosLordMiniArt,
  [0x05C8] = sEvilHeroSinisterNecromMiniArt,
  [0x05C9] = sEvilHeroToxicBubbleMiniArt,
  [0x05CA] = sEvilHeroViciousClawsMiniArt,
  [0x05CB] = sEvilHeroWildCycloneMiniArt,
  [0x05CC] = sEvilMindMiniArt,
  [0x05CD] = sFusionDeploymentMiniArt,
  [0x05CE] = sGandoraGTheDragonOfDestructionMiniArt,
  [0x05CF] = sGandoraXTheDragonOfDemolitionMiniArt,
  [0x05D0] = sGoyoGuardianMiniArt,
  [0x05D1] = sGrinderGolemMiniArt,
  [0x05D2] = sHarpieChannelerMiniArt,
  [0x05D3] = sHarpieConductorMiniArt,
  [0x05D4] = sHarpieDancerMiniArt,
  [0x05D5] = sHarpieHarpistMiniArt,
  [0x05D6] = sHarpieLadyEleganceMiniArt,
  [0x05D7] = sHarpieOracleMiniArt,
  [0x05D8] = sHarpiePerfumerMiniArt,
  [0x05D9] = sHarpieQueenMiniArt,
  [0x05DA] = sHarpiesFeatherRestMiniArt,
  [0x05DB] = sHarpiesFeatherStormMiniArt,
  [0x05DC] = sHarpiesHuntingGroundMiniArt,
  [0x05DD] = sHarpiesPetPhantasmalDragonMiniArt,
  [0x05DE] = sHelshaddollHollowMiniArt,
  [0x05DF] = sHeraldOfPerfectionMiniArt,
  [0x05E0] = sHeraldOfUltimatenessMiniArt,
  [0x05E1] = sHeroKidMiniArt,
  [0x05E2] = sHumidWindsMiniArt,
  [0x05E3] = sHystericPartyMiniArt,
  [0x05E4] = sHystericSignMiniArt,
  [0x05E5] = sIllusionMagicMiniArt,
  [0x05E6] = sIllusionOfChaosMiniArt,
  [0x05E7] = sIpiriaMiniArt,
  [0x05E8] = sJunkWarriorMiniArt,
  [0x05E9] = sKeeperOfDragonMagicMiniArt,
  [0x05EA] = sLegendaryMajuGarzettMiniArt,
  [0x05EB] = sLevShaddollFusionMiniArt,
  [0x05EC] = sLightSerpentMiniArt,
  [0x05ED] = sLightningWarriorMiniArt,
  [0x05EE] = sLonefireBlossomMiniArt,
  [0x05EF] = sMagicianNavigationMiniArt,
  [0x05F0] = sMagicianOfDarkIllusionMiniArt,
  [0x05F1] = sMagiciansCombinationMiniArt,
  [0x05F2] = sMagiciansRobeMiniArt,
  [0x05F3] = sMagiciansRodMiniArt,
  [0x05F4] = sMagiciansSoulsMiniArt,
  [0x05F5] = sMasterOfChaosMiniArt,
  [0x05F6] = sMetaverseMiniArt,
  [0x05F7] = sMillenniumEyesRestrictMiniArt,
  [0x05F8] = sMoltingEscapeMiniArt,
  [0x05F9] = sMysticMineMiniArt,
  [0x05FA] = sNaelshaddollArielMiniArt,
  [0x05FB] = sNehshaddollGeniusMiniArt,
  [0x05FC] = sNepheShaddollFusionMiniArt,
  [0x05FD] = sNeutronBlastMiniArt,
  [0x05FE] = sOfferingToTheSnakeDeityMiniArt,
  [0x05FF] = sOshaleonMiniArt,
  [0x0600] = sPowerToolDragonMiniArt,
  [0x0601] = sPredaplantVerteAnacondaMiniArt,
  [0x0602] = sQadshaddollKeiosMiniArt,
  [0x0603] = sRedDragonArchfiendMiniArt,
  [0x0604] = sRedRebootMiniArt,
  [0x0605] = sReeshaddollWendiMiniArt,
  [0x0606] = sReeshaddollWendikuruhuMiniArt,
  [0x0607] = sReptilanneRageMiniArt,
  [0x0608] = sReptilianneEchidnaMiniArt,
  [0x0609] = sReptilianneGardnaMiniArt,
  [0x060A] = sReptilianneGorgonMiniArt,
  [0x060B] = sReptilianneHydraMiniArt,
  [0x060C] = sReptilianneLamiaMiniArt,
  [0x060D] = sReptilianneMedusaMiniArt,
  [0x060E] = sReptilianneNagaMiniArt,
  [0x060F] = sReptiliannePoisonMiniArt,
  [0x0610] = sReptilianneScyllaMiniArt,
  [0x0611] = sReptilianneServantMiniArt,
  [0x0612] = sReptilianneSpawnMiniArt,
  [0x0613] = sReptilianneVaskiiMiniArt,
  [0x0614] = sReptilianneViperMiniArt,
  [0x0615] = sReturnOfTheDragonLordsMiniArt,
  [0x0616] = sRiseOfTheSnakeDeityMiniArt,
  [0x0617] = sSecretsOfDarkMagicMiniArt,
  [0x0618] = sSerpentSuppressionMiniArt,
  [0x0619] = sShaddollBeastMiniArt,
  [0x061A] = sShaddollCoreMiniArt,
  [0x061B] = sShaddollDragonMiniArt,
  [0x061C] = sShaddollFalcoMiniArt,
  [0x061D] = sShaddollFusionMiniArt,
  [0x061E] = sShaddollHedgehogMiniArt,
  [0x061F] = sShaddollHoundMiniArt,
  [0x0620] = sShaddollSchismMiniArt,
  [0x0621] = sShaddollSquamataMiniArt,
  [0x0622] = sSilversCryMiniArt,
  [0x0623] = sSnakeDeitysCommandMiniArt,
  [0x0624] = sSnakeRainMiniArt,
  [0x0625] = sSnakeWhistleMiniArt,
  [0x0626] = sSoulServantMiniArt,
  [0x0627] = sStardustDragonMiniArt,
  [0x0628] = sSupremeKingsCastleMiniArt,
  [0x0629] = sThatGrassLooksGreenerMiniArt,
  [0x062A] = sTheDarkMagiciansMiniArt,
  [0x062B] = sTheGazeOfTimaeusMiniArt,
  [0x062C] = sTheMelodyOfAwakeningDragonMiniArt,
  [0x062D] = sTheWhiteStoneOfAncientsMiniArt,
  [0x062E] = sTheWhiteStoneOfLegendMiniArt,
  [0x062F] = sTimeaeusTheUnitedMagicalDragonMiniArt,
  [0x0630] = sTimeausTheUnitedDragonMiniArt,
  [0x0631] = sTohushaddollGrystaMiniArt,
  [0x0632] = sTrapTrickMiniArt,
  [0x0633] = sTriangleEcstasySparkMiniArt,
  [0x0634] = sUltraPolymerizationMiniArt,
  [0x0635] = sVennominagaTheDeityOfPoisonousSnakesMiniArt,
  [0x0636] = sVennominonTheKingOfPoisonousSnakesMiniArt,
  [0x0637] = sVenomBoaMiniArt,
  [0x0638] = sVenomBurnMiniArt,
  [0x0639] = sVenomCobraMiniArt,
  [0x063A] = sVenomSerpentMiniArt,
  [0x063B] = sVenomShotMiniArt,
  [0x063C] = sVenomSnakeMiniArt,
  [0x063D] = sVenomSwampMiniArt,
  [0x063E] = sVipersRebirthMiniArt,
  [0x063F] = sYamorimoriMiniArt,
  [0x0640] = sYowieMiniArt,
  [0x0641] = sAceOfSwordMiniArt,
  [0x0642] = sAceOfWandMiniArt,
  [0x0643] = sArcanaCallMiniArt,
  [0x0644] = sArcanaForce0TheFoolMiniArt,
  [0x0645] = sArcanaForceExTheDarkRulerMiniArt,
  [0x0646] = sArcanaForceExTheLightRulerMiniArt,
  [0x0647] = sArcanaForceITheMagicianMiniArt,
  [0x0648] = sArcanaForceIiiTheEmpressMiniArt,
  [0x0649] = sArcanaForceIvTheEmperorMiniArt,
  [0x064A] = sArcanaForceTheChaosRulerMiniArt,
  [0x064B] = sArcanaForceVTheHierophantMiniArt,
  [0x064C] = sArcanaForceViTheLoversMiniArt,
  [0x064D] = sArcanaForceViiTheChariotMiniArt,
  [0x064E] = sArcanaForceViiiTheStrengthMiniArt,
  [0x064F] = sArcanaForceXiiTheHangmanMiniArt,
  [0x0650] = sArcanaForceXivTemperanceMiniArt,
  [0x0651] = sArcanaForceXixTheSunMiniArt,
  [0x0652] = sArcanaForceXvTheFiendMiniArt,
  [0x0653] = sArcanaForceXviiiTheMoonMiniArt,
  [0x0654] = sArcanaForceXxiTheWorldMiniArt,
  [0x0655] = sArcanaReadingMiniArt,
  [0x0656] = sArcanaSpreadMiniArt,
  [0x0657] = sArmedNeosMiniArt,
  [0x0658] = sAurkusLightswornDruidMiniArt,
  [0x0659] = sCelestiaLightswornAngelMiniArt,
  [0x065A] = sChargeOfTheLightBrigadeMiniArt,
  [0x065B] = sChrysalisChickyMiniArt,
  [0x065C] = sChrysalisDolphinMiniArt,
  [0x065D] = sChrysalisMoleMiniArt,
  [0x065E] = sChrysalisPantailMiniArt,
  [0x065F] = sChrysalisPinnyMiniArt,
  [0x0660] = sCocoonPartyMiniArt,
  [0x0661] = sCocoonRebirthMiniArt,
  [0x0662] = sColosseumCageOfTheGladiatorBeastsMiniArt,
  [0x0663] = sContactMiniArt,
  [0x0664] = sContactGateMiniArt,
  [0x0665] = sConvertContactMiniArt,
  [0x0666] = sCrossKeeperMiniArt,
  [0x0667] = sCuriousTheLightswornDominionMiniArt,
  [0x0668] = sEhrenLightswornMonkMiniArt,
  [0x0669] = sElementalHeroAirNeosMiniArt,
  [0x066A] = sElementalHeroAquaNeosMiniArt,
  [0x066B] = sElementalHeroBraveNeosMiniArt,
  [0x066C] = sElementalHeroChaosNeosMiniArt,
  [0x066D] = sElementalHeroCosmoNeosMiniArt,
  [0x066E] = sElementalHeroDarkNeosMiniArt,
  [0x066F] = sElementalHeroFlareNeosMiniArt,
  [0x0670] = sElementalHeroGlowNeosMiniArt,
  [0x0671] = sElementalHeroGrandNeosMiniArt,
  [0x0672] = sElementalHeroMagmaNeosMiniArt,
  [0x0673] = sElementalHeroMarineNeosMiniArt,
  [0x0674] = sElementalHeroNebulaNeosMiniArt,
  [0x0675] = sElementalHeroShiningNeosWingmanMiniArt,
  [0x0676] = sElementalHeroSpiritOfNeosMiniArt,
  [0x0677] = sElementalHeroStormNeosMiniArt,
  [0x0678] = sEnEngageNeoSpaceMiniArt,
  [0x0679] = sEnShuffleMiniArt,
  [0x067A] = sEnWaveMiniArt,
  [0x067B] = sEnlightenmentDragonMiniArt,
  [0x067C] = sFavouriteContactMiniArt,
  [0x067D] = sFelisLightswornArcherMiniArt,
  [0x067E] = sFlavianColosseumOfTheGladiatorBeastsMiniArt,
  [0x067F] = sGaronithLightswornDragonMiniArt,
  [0x0680] = sGarothLightswornWarriorMiniArt,
  [0x0681] = sGenerationNextMiniArt,
  [0x0682] = sGladiatorBeastAlexanderMiniArt,
  [0x0683] = sGladiatorBeastAndabataMiniArt,
  [0x0684] = sGladiatorBeastAndalMiniArt,
  [0x0685] = sGladiatorBeastAttorixMiniArt,
  [0x0686] = sGladiatorBeastAugustusMiniArt,
  [0x0687] = sGladiatorBeastBattleHalberdMiniArt,
  [0x0688] = sGladiatorBeastBestiariMiniArt,
  [0x0689] = sGladiatorBeastClaudiusMiniArt,
  [0x068A] = sGladiatorBeastDareiosMiniArt,
  [0x068B] = sGladiatorBeastDariusMiniArt,
  [0x068C] = sGladiatorBeastDimacariMiniArt,
  [0x068D] = sGladiatorBeastDomitianusMiniArt,
  [0x068E] = sGladiatorBeastDragasesMiniArt,
  [0x068F] = sGladiatorBeastEquesteMiniArt,
  [0x0690] = sGladiatorBeastEssedariiMiniArt,
  [0x0691] = sGladiatorBeastGaiodiazMiniArt,
  [0x0692] = sGladiatorBeastGistelMiniArt,
  [0x0693] = sGladiatorBeastGyzarusMiniArt,
  [0x0694] = sGladiatorBeastHeraklinosMiniArt,
  [0x0695] = sGladiatorBeastHoplomusMiniArt,
  [0x0696] = sGladiatorBeastLanistaMiniArt,
  [0x0697] = sGladiatorBeastLaquariMiniArt,
  [0x0698] = sGladiatorBeastMurmilloMiniArt,
  [0x0699] = sGladiatorBeastNerokiusMiniArt,
  [0x069A] = sGladiatorBeastNoxiousMiniArt,
  [0x069B] = sGladiatorBeastOctaviusMiniArt,
  [0x069C] = sGladiatorBeastRetiariMiniArt,
  [0x069D] = sGladiatorBeastSagittariiMiniArt,
  [0x069E] = sGladiatorBeastSamniteMiniArt,
  [0x069F] = sGladiatorBeastSecutorMiniArt,
  [0x06A0] = sGladiatorBeastSpartacusMiniArt,
  [0x06A1] = sGladiatorBeastTamerEditorMiniArt,
  [0x06A2] = sGladiatorBeastToraxMiniArt,
  [0x06A3] = sGladiatorBeastTygeriusMiniArt,
  [0x06A4] = sGladiatorBeastVespasiusMiniArt,
  [0x06A5] = sGladiatorBeastWarChariotMiniArt,
  [0x06A6] = sGladiatorBeastsBattleArchfiendShieldMiniArt,
  [0x06A7] = sGladiatorBeastsBattleGladiusMiniArt,
  [0x06A8] = sGladiatorBeastsBattleManicaMiniArt,
  [0x06A9] = sGladiatorBeastsMedusaShieldMiniArt,
  [0x06AA] = sGladiatorBeastsValorMiniArt,
  [0x06AB] = sGladiatorNaumachiaMiniArt,
  [0x06AC] = sGloriousIllusionMiniArt,
  [0x06AD] = sInstantContactMiniArt,
  [0x06AE] = sInstantNeoSpaceMiniArt,
  [0x06AF] = sJainLightswornPaladinMiniArt,
  [0x06B0] = sJainTwilightswornGeneralMiniArt,
  [0x06B1] = sJenisLightswornMenderMiniArt,
  [0x06B2] = sJudgmentTheDragonOfHeavenMiniArt,
  [0x06B3] = sKnightOfPentaclesMiniArt,
  [0x06B4] = sLightBarrierMiniArt,
  [0x06B5] = sLightForceMiniArt,
  [0x06B6] = sLightOfDestructionMiniArt,
  [0x06B7] = sLightSpiralMiniArt,
  [0x06B8] = sLightswornAegisMiniArt,
  [0x06B9] = sLightswornBarrierMiniArt,
  [0x06BA] = sLightswornDragonlingMiniArt,
  [0x06BB] = sLightswornJudgementMiniArt,
  [0x06BC] = sLightswornSabreMiniArt,
  [0x06BD] = sLightswornSanctuaryMiniArt,
  [0x06BE] = sLuminaLightswornSummonerMiniArt,
  [0x06BF] = sLuminaTwilightswornShamanMiniArt,
  [0x06C0] = sLylaLightswornSorceressMiniArt,
  [0x06C1] = sLylaTwilightswornEnchantressMiniArt,
  [0x06C2] = sMarchOfTheDarkBrigadeMiniArt,
  [0x06C3] = sMichaelTheArchLightswornMiniArt,
  [0x06C4] = sMinervaLightswornMaidenMiniArt,
  [0x06C5] = sMinervaTheAthenianLightswornMiniArt,
  [0x06C6] = sMinervaTheExhaltedLightswornMiniArt,
  [0x06C7] = sMiracleContactMiniArt,
  [0x06C8] = sMoonTokenMiniArt,
  [0x06C9] = sNeoSpaceMiniArt,
  [0x06CA] = sNeoSpaceConnectorMiniArt,
  [0x06CB] = sNeoSpacianAirHummingbirdMiniArt,
  [0x06CC] = sNeoSpacianAquaDolphinMiniArt,
  [0x06CD] = sNeoSpacianDarkPantherMiniArt,
  [0x06CE] = sNeoSpacianFlareScarabMiniArt,
  [0x06CF] = sNeoSpacianGlowMossMiniArt,
  [0x06D0] = sNeoSpacianGrandMoleMiniArt,
  [0x06D1] = sNeoSpacianMarineDolphinMiniArt,
  [0x06D2] = sNeoSpacianTwinkleMossMiniArt,
  [0x06D3] = sNexMiniArt,
  [0x06D4] = sNextMiniArt,
  [0x06D5] = sPentacleOfAceMiniArt,
  [0x06D6] = sPunishmentDragonMiniArt,
  [0x06D7] = sRaidenHandOfTheLightswornMiniArt,
  [0x06D8] = sRealmOfLightMiniArt,
  [0x06D9] = sRescueCatMiniArt,
  [0x06DA] = sRescueRabbitMiniArt,
  [0x06DB] = sReversalOfFateMiniArt,
  [0x06DC] = sRinyanLightswornRogueMiniArt,
  [0x06DD] = sRykoLightswornHunterMiniArt,
  [0x06DE] = sRykoTwilightswornFighterMiniArt,
  [0x06DF] = sShireLightswornSpiritMiniArt,
  [0x06E0] = sSolarRechargeMiniArt,
  [0x06E1] = sSuitOfSwordXMiniArt,
  [0x06E2] = sTestBearMiniArt,
  [0x06E3] = sTestPantherMiniArt,
  [0x06E4] = sTestTigerMiniArt,
  [0x06E5] = sThumbsDownMiniArt,
  [0x06E6] = sTourOfDoomMiniArt,
  [0x06E7] = sTrojanGladiatorBeastMiniArt,
  [0x06E8] = sTwilightClothMiniArt,
  [0x06E9] = sTwilightEraserMiniArt,
  [0x06EA] = sTwlightTwinDragonsMiniArt,
  [0x06EB] = sVanquishingLightMiniArt,
  [0x06EC] = sWeissLightswornArchfiendMiniArt,
  [0x06ED] = sWulfLightswornBeastMiniArt,
  [0x06EE] = sAllOutAttacksMiniArt,
  [0x06EF] = sAncientFairyDragonMiniArt,
  [0x06F0] = sAncientGearMiniArt,
  [0x06F1] = sAncientGearAdvanceMiniArt,
  [0x06F2] = sAncientGearBeastMiniArt,
  [0x06F3] = sAncientGearCannonMiniArt,
  [0x06F4] = sAncientGearCastleMiniArt,
  [0x06F5] = sAncientGearCommanderMiniArt,
  [0x06F6] = sAncientGearDarkGolemMiniArt,
  [0x06F7] = sAncientGearDragonMiniArt,
  [0x06F8] = sAncientGearDrillMiniArt,
  [0x06F9] = sAncientGearDuelMiniArt,
  [0x06FA] = sAncientGearEngineerMiniArt,
  [0x06FB] = sAncientGearExplosiveMiniArt,
  [0x06FC] = sAncientGearFactoryMiniArt,
  [0x06FD] = sAncientGearFistMiniArt,
  [0x06FE] = sAncientGearFrameMiniArt,
  [0x06FF] = sAncientGearFusionMiniArt,
  [0x0700] = sAncientGearGadjiltronChimeraMiniArt,
  [0x0701] = sAncientGearGadjiltronDragonMiniArt,
  [0x0702] = sAncientGearGolemMiniArt,
  [0x0703] = sAncientGearGolemUltimatePoundMiniArt,
  [0x0704] = sAncientGearKnightMiniArt,
  [0x0705] = sAncientGearMegatonGolemMiniArt,
  [0x0706] = sAncientGearSoldierMiniArt,
  [0x0707] = sAncientGearStatueMiniArt,
  [0x0708] = sAncientGearTankMiniArt,
  [0x0709] = sAncientGearTankerMiniArt,
  [0x070A] = sAncientGearWorkshopMiniArt,
  [0x070B] = sAncientLeafMiniArt,
  [0x070C] = sAncientSacredWyvernMiniArt,
  [0x070D] = sArcanaKnightJokerMiniArt,
  [0x070E] = sArcaneBarrierMiniArt,
  [0x070F] = sArmityleTheChaosPhantasmMiniArt,
  [0x0710] = sBabycerasaurusMiniArt,
  [0x0711] = sBarrierStatueOfTheStormwindsMiniArt,
  [0x0712] = sBattleManiaMiniArt,
  [0x0713] = sBigEvolutionPillMiniArt,
  [0x0714] = sBlackWingedDragonMiniArt,
  [0x0715] = sBeastMachineKingBarbarosUrMiniArt,
};
