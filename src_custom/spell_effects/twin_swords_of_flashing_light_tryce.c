#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void Tryce_ResolveBody(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];

  DecrementPermStage(target);
  RegisterDynamicEquip(spellZone, target, TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE, 1);
  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
  Duel_ShowEffectText(TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE);
}

APPEND_TEXT void EffectTwinSwordsOfFlashingLightTryce(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!Duel_IsMonsterZoneTarget(target->id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE, Tryce_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
