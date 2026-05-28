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

  return gCardNames[cardId];
}
