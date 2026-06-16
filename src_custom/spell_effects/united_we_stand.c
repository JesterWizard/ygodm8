#include "global.h"
#include "common-chax.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

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

static void UnitedWeStand_ResolveBody(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];
  u8 stages = CountDuelistMonsterRowCards(GetDuelistForZone(spellZone));

  if (stages > MAX_ZONES_IN_ROW)
    stages = MAX_ZONES_IN_ROW;

  ApplyDynamicEquipStages(target, stages);
  RegisterDynamicEquip(spellZone, target, UNITED_WE_STAND, stages);
  ActivateDynamicEquipSpell(spellZone);
  NotifyDynamicEquipFieldChanged();
  Duel_ShowEffectText(UNITED_WE_STAND);
}

APPEND_TEXT void EffectUnitedWeStand(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!IsValidUnitedWeStandTarget(target->id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(UNITED_WE_STAND, UnitedWeStand_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
