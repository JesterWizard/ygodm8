#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

void TryDestinyHeroDiskCommanderOnMonsterPlacement(struct DuelCard *zone)
{
  u8 controller;
  u8 turnDuelist;

  if (zone == NULL || zone->id != DESTINY_HERO_DISK_COMMANDER || gHideEffectText)
    return;

  if (EffectOpt_IsUsed(DESTINY_HERO_DISK_COMMANDER))
    return;

  controller = GetDuelistForZone(zone);
  if (controller > DUEL_OPPONENT)
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(controller);

  /* Printed is SS from GY once per Duel; any-placement + EffectOpt stand-in. */
  Duel_ShowEffectTextTyped(DESTINY_HERO_DISK_COMMANDER, 8);
  if (Duel_DrawCards(turnDuelist, 2, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  EffectOpt_MarkUsed(DESTINY_HERO_DISK_COMMANDER);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateDESTINY_HERO_DISK_COMMANDER(void)
{
  if (gMonEffect.id != DESTINY_HERO_DISK_COMMANDER)
    return FALSE;

  /* On-SS draw via TryDestinyHeroDiskCommanderOnMonsterPlacement
   * (SS-from-GY / once-per-Duel → any-placement + EffectOpt stand-in). */
  return FALSE;
}

void ActivateDESTINY_HERO_DISK_COMMANDEREffect(void)
{
  Duel_ShowEffectTextTyped(DESTINY_HERO_DISK_COMMANDER, 2);
}
