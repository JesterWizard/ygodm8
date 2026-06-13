#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "spell_effects.h"

extern void ActivateTrapEffect(u16 lp);

static u8 IsValidTryceTarget(u16 cardId)
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

APPEND_TEXT void EffectTwinSwordsOfFlashingLightTryce(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];

  if (!IsValidTryceTarget(target->id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  gTrapEffectData.originRow = gSpellEffectData.row2;
  gTrapEffectData.originCol = gSpellEffectData.col2;
  gTrapEffectData.originCardId = spellZone->id;

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    DecrementPermStage(target);
    RegisterDynamicEquip(spellZone, target, TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE, 1);
    ActivateDynamicEquipSpell(spellZone);
    NotifyDynamicEquipFieldChanged();

    if (!gHideEffectText) {
      gCardEffectTextData.cardId = TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE;
      ActivateCardEffectText();
    }
  } else {
    ActivateTrapEffect(0);
  }
}
