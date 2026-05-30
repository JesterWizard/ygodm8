#include "global.h"

static const unsigned char sSorcererOfDarkMagicBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/sorcerer_of_dark_magic.huff");
static const unsigned short sSorcererOfDarkMagicBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/sorcerer_of_dark_magic.gbapal");
static const unsigned char sSorcererOfDarkMagicMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/sorcerer_of_dark_magic.lz");

static const unsigned char sDeckDestructionVirusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/deck_destruction_virus.huff");
static const unsigned short sDeckDestructionVirusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/deck_destruction_virus.gbapal");
static const unsigned char sDeckDestructionVirusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/deck_destruction_virus.lz");

static const unsigned char sMagiciansValkyriaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/magicians_valkyria.huff");
static const unsigned short sMagiciansValkyriaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/magicians_valkyria.gbapal");
static const unsigned char sMagiciansValkyriaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/magicians_valkyria.lz");

static const unsigned char sBlueEyesShiningDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/blue_eyes_shining_dragon.huff");
static const unsigned short sBlueEyesShiningDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/blue_eyes_shining_dragon.gbapal");
static const unsigned char sBlueEyesShiningDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/blue_eyes_shining_dragon.lz");

static const unsigned char sPaladinOfWhiteDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/paladin_of_white_dragon.huff");
static const unsigned short sPaladinOfWhiteDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/paladin_of_white_dragon.gbapal");
static const unsigned char sPaladinOfWhiteDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/paladin_of_white_dragon.lz");

static const unsigned char sCardOfDemiseBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/card_of_demise.huff");
static const unsigned short sCardOfDemiseBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/card_of_demise.gbapal");
static const unsigned char sCardOfDemiseMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/card_of_demise.lz");

static const unsigned char sCardOfSanctityBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/card_of_sanctity.huff");
static const unsigned short sCardOfSanctityBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/card_of_sanctity.gbapal");
static const unsigned char sCardOfSanctityMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/card_of_sanctity.lz");

static const unsigned char sShieldAndSwordBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/shield_and_sword.huff");
static const unsigned short sShieldAndSwordBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/shield_and_sword.gbapal");
static const unsigned char sShieldAndSwordMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/shield_and_sword.lz");

static const unsigned char sBlueEyesChaosMaxDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/blue_eyes_chaos_max_dragon.huff");
static const unsigned short sBlueEyesChaosMaxDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/blue_eyes_chaos_max_dragon.gbapal");
static const unsigned char sBlueEyesChaosMaxDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/blue_eyes_chaos_max_dragon.lz");

static const unsigned char sChainEnergyBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/chain_energy.huff");
static const unsigned short sChainEnergyBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/chain_energy.gbapal");
static const unsigned char sChainEnergyMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/chain_energy.lz");

static const unsigned char sSpellCancellerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/spell_canceller.huff");
static const unsigned short sSpellCancellerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/spell_canceller.gbapal");
static const unsigned char sSpellCancellerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/spell_canceller.lz");

static const unsigned char sExchangeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/exchange.huff");
static const unsigned short sExchangeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/exchange.gbapal");
static const unsigned char sExchangeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/exchange.lz");

static const unsigned char sCopycatBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/copycat.huff");
static const unsigned short sCopycatBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/copycat.gbapal");
static const unsigned char sCopycatMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/copycat.lz");

static const unsigned char sMagePowerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/mage_power.huff");
static const unsigned short sMagePowerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/mage_power.gbapal");
static const unsigned char sMagePowerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/mage_power.lz");

static const unsigned char sKaibamanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/kaibaman.huff");
static const unsigned short sKaibamanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/kaibaman.gbapal");
static const unsigned char sKaibamanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/kaibaman.lz");

static const unsigned char sUltimateOfferingBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/ultimate_offering.huff");
static const unsigned short sUltimateOfferingBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/ultimate_offering.gbapal");
static const unsigned char sUltimateOfferingMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/ultimate_offering.lz");

static const unsigned char sUnitedWeStandBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/united_we_stand.huff");
static const unsigned short sUnitedWeStandBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/united_we_stand.gbapal");
static const unsigned char sUnitedWeStandMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/united_we_stand.lz");

static const unsigned char sWaveMotionCannonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/wave_motion_cannon.huff");
static const unsigned short sWaveMotionCannonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/wave_motion_cannon.gbapal");
static const unsigned char sWaveMotionCannonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/wave_motion_cannon.lz");

static const unsigned char sStJoanBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/st_joan.huff");
static const unsigned short sStJoanBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/st_joan.gbapal");
static const unsigned char sStJoanMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/st_joan.lz");

static const unsigned char sPyramidOfLightBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/pyramid_of_light.huff");
static const unsigned short sPyramidOfLightBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/pyramid_of_light.gbapal");
static const unsigned char sPyramidOfLightMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/pyramid_of_light.lz");

static const unsigned char sSoulExchangeBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/soul_exchange.huff");
static const unsigned short sSoulExchangeBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/soul_exchange.gbapal");
static const unsigned char sSoulExchangeMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/soul_exchange.lz");

static const unsigned char sMysticalSpaceTyphoonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/mystical_space_typhoon.huff");
static const unsigned short sMysticalSpaceTyphoonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/mystical_space_typhoon.gbapal");
static const unsigned char sMysticalSpaceTyphoonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/mystical_space_typhoon.lz");

static const unsigned char sRareMetalDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/rare_metal_dragon.huff");
static const unsigned short sRareMetalDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/rare_metal_dragon.gbapal");
static const unsigned char sRareMetalDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/rare_metal_dragon.lz");

static const unsigned char sDoubleSummonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/double_summon.huff");
static const unsigned short sDoubleSummonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/double_summon.gbapal");
static const unsigned char sDoubleSummonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/double_summon.lz");

static const unsigned char sObnoxiousCelticGuardianBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/obnoxious_celtic_guardian.huff");
static const unsigned short sObnoxiousCelticGuardianBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/obnoxious_celtic_guardian.gbapal");
static const unsigned char sObnoxiousCelticGuardianMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/obnoxious_celtic_guardian.lz");

static const unsigned char sMaskOfRestrictBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/mask_of_restrict.huff");
static const unsigned short sMaskOfRestrictBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/mask_of_restrict.gbapal");
static const unsigned char sMaskOfRestrictMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/mask_of_restrict.lz");

static const unsigned char sFairyBoxBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/fairy_box.huff");
static const unsigned short sFairyBoxBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/fairy_box.gbapal");
static const unsigned char sFairyBoxMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/fairy_box.lz");

static const unsigned char sCostDownBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/cost_down.huff");
static const unsigned short sCostDownBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/cost_down.gbapal");
static const unsigned char sCostDownMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/cost_down.lz");

static const unsigned char sBlueEyesAlternativeWhiteDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/blue_eyes_alternative_white_dragon.huff");
static const unsigned short sBlueEyesAlternativeWhiteDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/blue_eyes_alternative_white_dragon.gbapal");
static const unsigned char sBlueEyesAlternativeWhiteDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/blue_eyes_alternative_white_dragon.lz");

static const unsigned char sAncientRulesBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/ancient_rules.huff");
static const unsigned short sAncientRulesBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/ancient_rules.gbapal");
static const unsigned char sAncientRulesMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/ancient_rules.lz");

static const unsigned char sMagicJammerBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/80x80/magic_jammer.huff");
static const unsigned short sMagicJammerBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src_custom/assets/cards/80x80/magic_jammer.gbapal");
static const unsigned char sMagicJammerMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src_custom/assets/cards/24x24/magic_jammer.lz");

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
};
