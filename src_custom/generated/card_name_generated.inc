static const u8 sSorcererOfDarkMagicName[] __attribute__((section(".append_assets"))) = "Sorcerer of Dark Magic";
static const u8 sDeckDestructionVirusName[] __attribute__((section(".append_assets"))) = "Deck Destruction Virus";
static const u8 sMagiciansValkyriaName[] __attribute__((section(".append_assets"))) = "Magician's Valkyria";
static const u8 sBlueEyesShiningDragonName[] __attribute__((section(".append_assets"))) = "Blue-Eyes Shining Dragon";
static const u8 sPaladinOfWhiteDragonName[] __attribute__((section(".append_assets"))) = "Paladin Of White Dragon";
static const u8 sCardOfDemiseName[] __attribute__((section(".append_assets"))) = "Card Of Demise";
static const u8 sCardOfSanctityName[] __attribute__((section(".append_assets"))) = "Card Of Sanctity";
static const u8 sShieldAndSwordName[] __attribute__((section(".append_assets"))) = "Shield And Sword";
static const u8 sBlueEyesChaosMaxDragonName[] __attribute__((section(".append_assets"))) = "Blue-Eyes Chaos Max Dragon";
static const u8 sChainEnergyName[] __attribute__((section(".append_assets"))) = "Chain Energy";
static const u8 sSpellCancellerName[] __attribute__((section(".append_assets"))) = "Spell Canceller";
static const u8 sExchangeName[] __attribute__((section(".append_assets"))) = "Exchange";
static const u8 sCopycatName[] __attribute__((section(".append_assets"))) = "Copycat";
static const u8 sMagePowerName[] __attribute__((section(".append_assets"))) = "Mage Power";
static const u8 sKaibamanName[] __attribute__((section(".append_assets"))) = "Kaibaman";
static const u8 sUltimateOfferingName[] __attribute__((section(".append_assets"))) = "Ultimate Offering";
static const u8 sUnitedWeStandName[] __attribute__((section(".append_assets"))) = "United We Stand";
static const u8 sWaveMotionCannonName[] __attribute__((section(".append_assets"))) = "Wave Motion Cannon";
static const u8 sStJoanName[] __attribute__((section(".append_assets"))) = "St Joan";
static const u8 sPyramidOfLightName[] __attribute__((section(".append_assets"))) = "Pyramid of Light";
static const u8 sSoulExchangeName[] __attribute__((section(".append_assets"))) = "Soul Exchange";
static const u8 sMysticalSpaceTyphoonName[] __attribute__((section(".append_assets"))) = "Mystical Space Typhoon";
static const u8 sRareMetalDragonName[] __attribute__((section(".append_assets"))) = "Rare Metal Dragon";
static const u8 sDoubleSummonName[] __attribute__((section(".append_assets"))) = "Double Summon";
static const u8 sObnoxiousCelticGuardianName[] __attribute__((section(".append_assets"))) = "Obnoxious Celtic Guardian";
static const u8 sMaskOfRestrictName[] __attribute__((section(".append_assets"))) = "Mask of Restrict";
static const u8 sFairyBoxName[] __attribute__((section(".append_assets"))) = "Fairy Box";
static const u8 sCostDownName[] __attribute__((section(".append_assets"))) = "Cost Down";
static const u8 sBlueEyesAlternativeWhiteDragonName[] __attribute__((section(".append_assets"))) = "Blue-Eyes Alternative White Dragon";
static const u8 sAncientRulesName[] __attribute__((section(".append_assets"))) = "Ancient Rules";
static const u8 sMagicJammerName[] __attribute__((section(".append_assets"))) = "Magic Jammer";

static u8 *GetCardName_Hook(unsigned short cardId) {
  if (cardId == 0x0321)
    return (u8 *)sSorcererOfDarkMagicName;
  if (cardId == 0x0322)
    return (u8 *)sDeckDestructionVirusName;
  if (cardId == 0x0323)
    return (u8 *)sMagiciansValkyriaName;
  if (cardId == 0x0324)
    return (u8 *)sBlueEyesShiningDragonName;
  if (cardId == 0x0325)
    return (u8 *)sPaladinOfWhiteDragonName;
  if (cardId == 0x0326)
    return (u8 *)sCardOfDemiseName;
  if (cardId == 0x0327)
    return (u8 *)sCardOfSanctityName;
  if (cardId == 0x0328)
    return (u8 *)sShieldAndSwordName;
  if (cardId == 0x0329)
    return (u8 *)sBlueEyesChaosMaxDragonName;
  if (cardId == 0x032A)
    return (u8 *)sChainEnergyName;
  if (cardId == 0x032B)
    return (u8 *)sSpellCancellerName;
  if (cardId == 0x032C)
    return (u8 *)sExchangeName;
  if (cardId == 0x032D)
    return (u8 *)sCopycatName;
  if (cardId == 0x032E)
    return (u8 *)sMagePowerName;
  if (cardId == 0x032F)
    return (u8 *)sKaibamanName;
  if (cardId == 0x0330)
    return (u8 *)sUltimateOfferingName;
  if (cardId == 0x0331)
    return (u8 *)sUnitedWeStandName;
  if (cardId == 0x0332)
    return (u8 *)sWaveMotionCannonName;
  if (cardId == 0x0333)
    return (u8 *)sStJoanName;
  if (cardId == 0x0334)
    return (u8 *)sPyramidOfLightName;
  if (cardId == 0x0335)
    return (u8 *)sSoulExchangeName;
  if (cardId == 0x0336)
    return (u8 *)sMysticalSpaceTyphoonName;
  if (cardId == 0x0337)
    return (u8 *)sRareMetalDragonName;
  if (cardId == 0x0338)
    return (u8 *)sDoubleSummonName;
  if (cardId == 0x0339)
    return (u8 *)sObnoxiousCelticGuardianName;
  if (cardId == 0x033A)
    return (u8 *)sMaskOfRestrictName;
  if (cardId == 0x033B)
    return (u8 *)sFairyBoxName;
  if (cardId == 0x033C)
    return (u8 *)sCostDownName;
  if (cardId == 0x033D)
    return (u8 *)sBlueEyesAlternativeWhiteDragonName;
  if (cardId == 0x033E)
    return (u8 *)sAncientRulesName;
  if (cardId == 0x033F)
    return (u8 *)sMagicJammerName;

  return gCardNames[cardId];
}
