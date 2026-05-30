typedef struct {
  u16 cardId;
  const u8 *text;
} CardActivationTextEntry;

static const CardActivationTextEntry sCardActivationTextEntries[] APPEND_RODATA = {
  { MASK_OF_DARKNESS, gActivationDescription_MaskOfDarkness },
  { FIRE_REAPER, gActivationDescription_FireReaper },
  { MYSTERIOUS_PUPPETEER, gActivationDescription_MysteriousPuppeteer },
  { KARATE_MAN, gActivationDescription_KarateMan },
  { GIANT_GERM, gActivationDescription_GiantGerm },
  { NIMBLE_MOMONGA, gActivationDescription_NimbleMomonga },
  { CEREMONIAL_BELL, gActivationDescription_CeremonialBell },
  { JAM_BREEDING_MACHINE, gActivationDescription_JamBreedingMachine },
  { PRINCESS_OF_TSURUGI, gActivationDescription_PrincessOfTsurugi },
  { SPARKS, gActivationDescription_Sparks },
  { HINOTAMA, gActivationDescription_Hinotama },
  { FINAL_FLAME, gActivationDescription_FinalFlame },
  { OOKAZI, gActivationDescription_Ookazi },
  { CYBER_STEIN, gActivationDescription_CyberStein },
  { GODDESS_OF_WHIM, gActivationDescription_GoddessOfWhim },
  { NEEDLE_BALL, gActivationDescription_NeedleBall },
  { MAHA_VAILO, gActivationDescription_MahaVailo },
  { AMAZON_CHAIN_MASTER, gActivationDescription_AmazonChainMaster },
  { INJECTION_FAIRY_LILY, gActivationDescription_InjectionFairyLily },
  { NEEDLE_WORM, gActivationDescription_NeedleWorm },
  { PENGUIN_SOLDIER, gActivationDescription_PenguinSoldier },
  { SKULL_MARK_LADY_BUG, gActivationDescription_SkullMarkLadyBug },
  { DECK_DESTRUCTION_VIRUS, gActivationDescription_DeckDestructionVirus },
  { BLUE_EYES_SHINING_DRAGON, gActivationDescription_BlueEyesShiningDragon },
  { CARD_OF_DEMISE, gActivationDescription_CardOfDemise },
  { CARD_OF_SANCTITY, gActivationDescription_CardOfSanctity },
  { SHIELD_AND_SWORD, gActivationDescription_ShieldAndSword },
  { CHAIN_ENERGY, gActivationDescription_ChainEnergy },
  { SPELL_CANCELLER, gActivationDescription_SpellCanceller },
  { EXCHANGE, gActivationDescription_Exchange },
  { COPYCAT, gActivationDescription_Copycat },
  { MAGE_POWER, gActivationDescription_MagePower },
  { KAIBAMAN, gActivationDescription_Kaibaman },
  { ULTIMATE_OFFERING, gActivationDescription_UltimateOffering },
};

static const u8 *GetCardActivationText(u16 cardId) {
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sCardActivationTextEntries); i++)
    if (sCardActivationTextEntries[i].cardId == cardId)
      return sCardActivationTextEntries[i].text;

  return NULL;
}
