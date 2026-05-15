static const u8 sSorcererOfDarkMagicName[] __attribute__((section(".append_assets"))) = "Sorcerer of Dark Magic";
static const u8 sDeckDestructionVirusName[] __attribute__((section(".append_assets"))) = "Deck Destruction Virus";
static const u8 sMagiciansValkyriaName[] __attribute__((section(".append_assets"))) = "Magician's Valkyria";

static u8 *GetCardName_Hook(unsigned short cardId) {
  if (cardId == 0x0321)
    return (u8 *)sSorcererOfDarkMagicName;
  if (cardId == 0x0322)
    return (u8 *)sDeckDestructionVirusName;
  if (cardId == 0x0323)
    return (u8 *)sMagiciansValkyriaName;

  return gCardNames[cardId];
}
