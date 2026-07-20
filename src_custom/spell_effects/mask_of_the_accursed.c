#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define MASK_OF_THE_ACCURSED_STANDBY_DAMAGE 500

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

  /* ponytail: attack lock + Standby 500 burn need hooks outside this file.
   * Ceiling: equip registers only (like Raregold Armor without force-target).
   * Upgrade: wire DynamicEquipTargetsMonsterWithSpell(MASK_OF_THE_ACCURSED) into
   * duel_attack_restrictions.c (CannotAttack) and turn_effect_hooks.c
   * (Duel_ChangeLp controller, -MASK_OF_THE_ACCURSED_STANDBY_DAMAGE) — clone
   * NightmareWheel_CanMonsterDeclareAttack / TryApplyNightmareWheelStandbyDamage. */
  (void)MASK_OF_THE_ACCURSED_STANDBY_DAMAGE;
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
