typedef struct {
  u16 cardId;
  const u8 *text;
} CardActivationTextEntry;

static const CardActivationTextEntry sCardActivationTextEntries[] APPEND_RODATA = {
  { SANGAN, gActivationDescription_Sangan },
  { MASK_OF_DARKNESS, gActivationDescription_MaskOfDarkness },
  { FIRE_REAPER, gActivationDescription_FireReaper },
  { MYSTERIOUS_PUPPETEER, gActivationDescription_MysteriousPuppeteer },
  { BIG_EYE, gActivationDescription_BigEye },
  { KARATE_MAN, gActivationDescription_KarateMan },
  { GIANT_GERM, gActivationDescription_GiantGerm },
  { NIMBLE_MOMONGA, gActivationDescription_NimbleMomonga },
  { CEREMONIAL_BELL, gActivationDescription_CeremonialBell },
  { JAM_BREEDING_MACHINE, gActivationDescription_JamBreedingMachine },
  { SLIFER_THE_SKY_DRAGON, gActivationDescription_SliferTheSkyDragon },
  { PRINCESS_OF_TSURUGI, gActivationDescription_PrincessOfTsurugi },
  { SPARKS, gActivationDescription_Sparks },
  { HINOTAMA, gActivationDescription_Hinotama },
  { FINAL_FLAME, gActivationDescription_FinalFlame },
  { OOKAZI, gActivationDescription_Ookazi },
  { MONSTER_TAMER, gActivationDescription_MonsterTamer },
  { CYBER_STEIN, gActivationDescription_CyberStein },
  { GODDESS_OF_WHIM, gActivationDescription_GoddessOfWhim },
  { SINISTER_SERPENT, gActivationDescription_SinisterSerpent },
  { NEEDLE_BALL, gActivationDescription_NeedleBall },
  { MAHA_VAILO, gActivationDescription_MahaVailo },
  { CANNON_SOLDIER, gActivationDescription_CannonSoldier },
  { EMBODIMENT_OF_APOPHIS, gActivationDescription_EmbodimentOfApophis },
  { AMAZON_CHAIN_MASTER, gActivationDescription_AmazonChainMaster },
  { INJECTION_FAIRY_LILY, gActivationDescription_InjectionFairyLily },
  { NEEDLE_WORM, gActivationDescription_NeedleWorm },
  { WITCH_OF_THE_BLACK_FOREST, gActivationDescription_WitchOfTheBlackForest },
  { DARK_MAGICIAN_KNIGHT, gActivationDescription_DarkMagicianKnight },
  { PENGUIN_SOLDIER, gActivationDescription_PenguinSoldier },
  { YAMATA_DRAGON, gActivationDescription_YamataDragon },
  { SKULL_MARK_LADY_BUG, gActivationDescription_SkullMarkLadyBug },
  { THE_UNHAPPY_MAIDEN, gActivationDescription_TheUnhappyMaiden },
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
  { UNITED_WE_STAND, gActivationDescription_UnitedWeStand },
  { WAVE_MOTION_CANNON, gActivationDescription_WaveMotionCannon },
  { PYRAMID_OF_LIGHT, gActivationDescription_PyramidOfLight },
  { SOUL_EXCHANGE, gActivationDescription_SoulExchange },
  { MYSTICAL_SPACE_TYPHOON, gActivationDescription_MysticalSpaceTyphoon },
  { DOUBLE_SUMMON, gActivationDescription_DoubleSummon },
  { MASK_OF_RESTRICT, gActivationDescription_MaskOfRestrict },
  { FAIRY_BOX, gActivationDescription_FairyBox },
  { COST_DOWN, gActivationDescription_CostDown },
  { BLUE_EYES_ALTERNATIVE_WHITE_DRAGON, gActivationDescription_BlueEyesAlternativeWhiteDragon },
  { ANCIENT_RULES, gActivationDescription_AncientRules },
  { MAGIC_JAMMER, gActivationDescription_MagicJammer },
  { SEAL_OF_ORICHALCOS, gActivationDescription_SealOfOrichalcos },
  { FAMILIAR_KNIGHT, gActivationDescription_FamiliarKnight },
  { RIRYOKU, gActivationDescription_Riryoku },
  { SAGES_STONE, gActivationDescription_SagesStone },
  { BOWGANIAN, gActivationDescription_Bowganian },
  { DARK_MAGIC_CURTAIN, gActivationDescription_DarkMagicCurtain },
};

static const u8 *GetCardActivationText(u16 cardId) {
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sCardActivationTextEntries); i++)
    if (sCardActivationTextEntries[i].cardId == cardId)
      return sCardActivationTextEntries[i].text;

  return NULL;
}
