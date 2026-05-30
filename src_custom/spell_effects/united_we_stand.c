#include "global.h"
#include "common-chax.h"
#include "dynamic_equip.h"
#include "spell_effects.h"

extern void ActivateTrapEffect(u16 lp);

static u8 IsValidUnitedWeStandTarget(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static void ActivateDynamicEquipSpell(struct DuelCard *spellZone)
{
  FlipCardFaceUp(spellZone);
  spellZone->isLocked = TRUE;
}

APPEND_TEXT void EffectUnitedWeStand(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];
  u8 stages = CountDuelistMonsterRowCards(GetDuelistForZone(spellZone));

  if (stages > MAX_ZONES_IN_ROW)
    stages = MAX_ZONES_IN_ROW;

  if (!IsValidUnitedWeStandTarget(target->id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  gTrapEffectData.originRow = gSpellEffectData.row2;
  gTrapEffectData.originCol = gSpellEffectData.col2;
  gTrapEffectData.originCardId = spellZone->id;

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    ApplyDynamicEquipStages(target, stages);
    RegisterDynamicEquip(spellZone, target, UNITED_WE_STAND, stages);
    ActivateDynamicEquipSpell(spellZone);
    NotifyDynamicEquipFieldChanged();

    if (!gHideEffectText) {
      gCardEffectTextData.cardId = UNITED_WE_STAND;
      ActivateCardEffectText();
    }
  } else {
    ActivateTrapEffect(0);
  }
}
