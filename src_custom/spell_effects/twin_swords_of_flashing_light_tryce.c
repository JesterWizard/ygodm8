#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

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

static void Tryce_ResolveBody(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];

  DecrementPermStage(target);
  RegisterDynamicEquip(spellZone, target, TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE, 1);
  ActivateDynamicEquipSpell(spellZone);
  NotifyDynamicEquipFieldChanged();
  Duel_ShowEffectText(TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE);
}

APPEND_TEXT void EffectTwinSwordsOfFlashingLightTryce(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!IsValidTryceTarget(target->id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE, Tryce_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
