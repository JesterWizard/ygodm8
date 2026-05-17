typedef struct {
  u16 cardId;
  const u8 *text;
} CardActivationTextEntry;

static const CardActivationTextEntry sCardActivationTextEntries[] APPEND_RODATA = {
  { CARD_OF_SANCTITY, gActivationDescription_CardOfSanctity },
  { SHIELD_AND_SWORD, gActivationDescription_ShieldAndSword },
};

static const u8 *GetCardActivationText(u16 cardId) {
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sCardActivationTextEntries); i++)
    if (sCardActivationTextEntries[i].cardId == cardId)
      return sCardActivationTextEntries[i].text;

  return NULL;
}
