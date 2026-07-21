#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "imperial_order.h"
#include "spell_effects.h"

#define MASK_OF_THE_ACCURSED_STANDBY_DAMAGE 500

static u8 IsActivatedMaskOfTheAccursedZone(const struct DuelCard *spellZone)
{
  return spellZone != NULL && spellZone->id == MASK_OF_THE_ACCURSED
      && spellZone->isFaceUp == TRUE && spellZone->isLocked == TRUE
      && !IsImperialOrderNegatingSpell(MASK_OF_THE_ACCURSED);
}

u8 MaskOfTheAccursed_CanMonsterDeclareAttack(const struct DuelCard *zone)
{
  u8 targetRow;
  u8 targetCol;
  u8 i;

  if (zone == NULL || zone->id == CARD_NONE
      || !Duel_FindFixedMonsterZone((struct DuelCard *)zone, &targetRow, &targetCol))
    return TRUE;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    struct DynamicEquipLink *link = &gDynamicEquipLinks[i];
    struct DuelCard *spellZone;

    if (!link->active || link->spellId != MASK_OF_THE_ACCURSED
        || link->targetFixedRow != targetRow || link->targetFixedCol != targetCol)
      continue;

    spellZone = gFixedZones[link->spellFixedRow][link->spellFixedCol];
    if (IsActivatedMaskOfTheAccursedZone(spellZone))
      return FALSE;
  }

  return TRUE;
}

void TryApplyMaskOfTheAccursedStandbyDamage(void)
{
  u8 i;

  if (IsDuelOver() == TRUE || IsImperialOrderNegatingSpell(MASK_OF_THE_ACCURSED))
    return;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    struct DynamicEquipLink *link = &gDynamicEquipLinks[i];
    struct DuelCard *spellZone;
    struct DuelCard *target;

    if (!link->active || link->spellId != MASK_OF_THE_ACCURSED)
      continue;

    spellZone = gFixedZones[link->spellFixedRow][link->spellFixedCol];
    if (!IsActivatedMaskOfTheAccursedZone(spellZone)
        || GetDuelistForZone(spellZone) != WhoseTurn())
      continue;

    target = gFixedZones[link->targetFixedRow][link->targetFixedCol];
    if (target == NULL || target->id == CARD_NONE)
      continue;

    Duel_ShowEffectText(MASK_OF_THE_ACCURSED);
    if (Duel_ChangeLp(GetDuelistForZone(target), -MASK_OF_THE_ACCURSED_STANDBY_DAMAGE, TRUE)
        == DUEL_ACTION_DUEL_OVER)
      return;
  }
}

static void ActivateMaskOfTheAccursedEquip(struct DuelCard *spellZone, struct DuelCard *target)
{
  RegisterDynamicEquip(spellZone, target, MASK_OF_THE_ACCURSED, 0);
  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
}

static void MASK_OF_THE_ACCURSED_ResolveBody(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];

  ActivateMaskOfTheAccursedEquip(spellZone, target);
  Duel_ShowEffectText(MASK_OF_THE_ACCURSED);
}

APPEND_TEXT void EffectMASK_OF_THE_ACCURSED(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!Duel_IsMonsterZoneTarget(target->id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MASK_OF_THE_ACCURSED, MASK_OF_THE_ACCURSED_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MASK_OF_THE_ACCURSED_SelfCheck(void)
{
  if (MASK_OF_THE_ACCURSED_STANDBY_DAMAGE != 500)
    while (1)
      ;
}
#endif
