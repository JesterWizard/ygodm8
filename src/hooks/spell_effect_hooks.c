#include "global.h"
#include "common-chax.h"

extern void (*const gSpellEffects[])(void);
extern void EffectCardOfSanctity(void);
extern void EffectJamBreedingMachine(void);
extern void EffectShieldAndSword(void);

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
    case JAM_BREEDING_MACHINE:
      EffectJamBreedingMachine();
      return;
    case SHIELD_AND_SWORD:
      EffectShieldAndSword();
      return;
    default:
      gSpellEffects[gCardInfo.spellEffect]();
      return;
  }
}
