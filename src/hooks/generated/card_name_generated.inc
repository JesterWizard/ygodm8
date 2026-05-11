static const u8 sSorcererOfDarkMagicName[] __attribute__((section(".append_assets"))) = "Sorcerer of Dark Magic";

static u8 *GetCardName_Hook(unsigned short cardId) {
  if (cardId == SORCERER_OF_DARK_MAGIC)
    return (u8 *)sSorcererOfDarkMagicName;

  return gCardNames[cardId];
}
