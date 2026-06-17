#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "raregold_armor.h"
#include "spell_effects.h"

static void ActivateRaregoldEquip(struct DuelCard *spellZone, struct DuelCard *target)
{
  RegisterDynamicEquip(spellZone, target, RAREGOLD_ARMOR, 0);
  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
}

static void RaregoldArmor_ResolveBody(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];

  ActivateRaregoldEquip(spellZone, target);
  Duel_ShowEffectText(RAREGOLD_ARMOR);
}

struct DuelCard *RaregoldArmor_GetForcedAttackTarget(u8 defenderDuelist)
{
  u8 i;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    struct DynamicEquipLink *link = &gDynamicEquipLinks[i];
    struct DuelCard *spellZone;
    struct DuelCard *targetZone;

    if (!link->active || link->spellId != RAREGOLD_ARMOR)
      continue;

    spellZone = gFixedZones[link->spellFixedRow][link->spellFixedCol];
    if (!IsActiveDynamicEquipSpellZone(spellZone))
      continue;

    if (GetDuelistForZone(spellZone) != defenderDuelist)
      continue;

    targetZone = gFixedZones[link->targetFixedRow][link->targetFixedCol];
    if (targetZone->id == CARD_NONE || !Duel_IsMonsterZoneTarget(targetZone->id))
      continue;

    return targetZone;
  }

  return NULL;
}

u8 RaregoldArmor_CanBeAttacked(struct DuelCard *zone)
{
  return Duel_MonsterMayBeAttacked(zone);
}

u8 RaregoldArmor_BlocksDirectAttack(u8 defenderDuelist)
{
  return Duel_ForcedAttackBlocksDirect(defenderDuelist);
}

APPEND_TEXT void EffectRaregoldArmor(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!Duel_IsMonsterZoneTarget(target->id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(RAREGOLD_ARMOR, RaregoldArmor_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if !defined(__GNUC__)
#error Raregold Armor self-check requires GCC
#elif __GNUC__
void RaregoldArmor_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = CARD_NONE;
  RaregoldArmor_CanBeAttacked(&zone);
  RaregoldArmor_BlocksDirectAttack(DUEL_PLAYER);
}
#endif
