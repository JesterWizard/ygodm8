#include "global.h"

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

const unsigned char *gCardArts_Hook[] APPEND_RODATA = {
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
};

const unsigned short *gCardArtPalettes_Hook[] APPEND_RODATA = {
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
};

const u8 gCardArtUsesExtendedPalette_Hook[] APPEND_RODATA = {
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
};

const unsigned char *gMiniCardArts_Hook[] APPEND_RODATA = {
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
};
