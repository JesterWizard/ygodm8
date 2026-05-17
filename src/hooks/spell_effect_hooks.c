#include "global.h"
#include "common-chax.h"

extern void (*const gSpellEffects[])(void);
extern void EffectCardOfSanctity(void);

void ActivateSpellEffect(void);

LYN_REPLACE_CHECK(ActivateSpellEffect);
void ActivateSpellEffect__Replacement(void)
{
  ResetCardEffectTextData();
  SetCardEffectTextType(1);
  SetCardInfo(gSpellEffectData.id);

  switch (gSpellEffectData.id) {
    case CARD_OF_SANCTITY:
      EffectCardOfSanctity();
      return;
    default:
      gSpellEffects[gCardInfo.spellEffect]();
      return;
  }
}
