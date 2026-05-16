static const u8 sSorcererOfDarkMagicName[] __attribute__((section(".append_assets"))) = "Sorcerer of Dark Magic";
static const u8 sDeckDestructionVirusName[] __attribute__((section(".append_assets"))) = "Deck Destruction Virus";
static const u8 sMagiciansValkyriaName[] __attribute__((section(".append_assets"))) = "Magician's Valkyria";
static const u8 sBlueEyesShiningDragonName[] __attribute__((section(".append_assets"))) = "Blue-Eyes Shining Dragon";
static const u8 sPaladinOfWhiteDragonName[] __attribute__((section(".append_assets"))) = "Paladin Of White Dragon";

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

  return gCardNames[cardId];
}
