#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"

extern void (*const gSpellEffects[])(void);
extern void EffectCardOfDemise(void);
extern void EffectCardOfSanctity(void);
extern void EffectJamBreedingMachine(void);
extern void EffectShieldAndSword(void);
extern void EffectSwordsOfRevealingLight(void);
extern void EffectChainEnergy(void);
extern void EffectExchange(void);
void ApplyMahaVailoEquipBonus(struct DuelCard* zone);

void ActivateSpellEffect(void);
u8 TryPayChainEnergyCost(void);
unsigned char IsSpellCancellerSpellLockActive(void);

LYN_REPLACE_CHECK(ActivateSpellEffect);
void ActivateSpellEffect__Replacement(void)
{
  if (gSpellEffectData.row1 == ACTIVE_DUELIST_HAND) {
    if (!TryPayChainEnergyCost())
      return;
  }

  if (IsSpellCancellerSpellLockActive()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

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
    case CHAIN_ENERGY:
      EffectChainEnergy();
      return;
    case EXCHANGE:
      EffectExchange();
      return;
    default:
      gSpellEffects[gCardInfo.spellEffect]();
      if (GetSpellType(gSpellEffectData.id) == SPELL_TYPE_EQUIP
          && gTurnZones[gSpellEffectData.row2][gSpellEffectData.col2]->id == CARD_NONE)
        ApplyMahaVailoEquipBonus(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]);
      return;
  }
}
