#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"

extern void (*const gSpellEffects[])(void);
extern void EffectCardOfDemise(void);
extern void EffectCardOfSanctity(void);
extern void EffectJamBreedingMachine(void);
extern void EffectShieldAndSword(void);
extern void EffectSwordsOfRevealingLight(void);
void ApplyMahaVailoEquipBonus(struct DuelCard* zone);

void ActivateSpellEffect(void);

LYN_REPLACE_CHECK(ActivateSpellEffect);
void ActivateSpellEffect__Replacement(void)
{
  ResetCardEffectTextData();
  SetCardEffectTextType(1);
  SetCardInfo(gSpellEffectData.id);

  switch (gSpellEffectData.id) {
    case CARD_OF_DEMISE:
      EffectCardOfDemise();
      return;
    case CARD_OF_SANCTITY:
      EffectCardOfSanctity();
      return;
    case JAM_BREEDING_MACHINE:
      EffectJamBreedingMachine();
      return;
    case SHIELD_AND_SWORD:
      EffectShieldAndSword();
      return;
    case SWORDS_OF_REVEALING_LIGHT:
      EffectSwordsOfRevealingLight();
      return;
    default:
      gSpellEffects[gCardInfo.spellEffect]();
      if (GetSpellType(gSpellEffectData.id) == SPELL_TYPE_EQUIP
          && gTurnZones[gSpellEffectData.row2][gSpellEffectData.col2]->id == CARD_NONE)
        ApplyMahaVailoEquipBonus(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]);
      return;
  }
}
