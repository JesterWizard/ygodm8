#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "monster_effect_usage.h"

#define GRAVEKEEPERS_CURSE_DAMAGE 500

void UpdateDuelGfxExceptField(void);

void TryGravekeepersCurseOnMonsterPlacement(struct DuelCard *zone)
{
  u8 controller;
  u8 turnDuelist;
  u8 opp;

  if (zone == NULL || zone->id != GRAVEKEEPERS_CURSE || gHideEffectText)
    return;

  if (EffectOpt_IsUsed(GRAVEKEEPERS_CURSE))
    return;

  controller = GetDuelistForZone(zone);
  if (controller > DUEL_OPPONENT)
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(controller);
  opp = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_CURSE, 8);
  if (Duel_ChangeLp(opp, -GRAVEKEEPERS_CURSE_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  EffectOpt_MarkUsed(GRAVEKEEPERS_CURSE);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateGRAVEKEEPERS_CURSE(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_CURSE)
    return FALSE;

  /* On-Summon burn via TryGravekeepersCurseOnMonsterPlacement. */
  return FALSE;
}

void ActivateGRAVEKEEPERS_CURSEEffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_CURSE, 2);
}
