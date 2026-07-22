#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

void TryMoltenZombieOnMonsterPlacement(struct DuelCard *zone)
{
  u8 controller;
  u8 turnDuelist;

  if (zone == NULL || zone->id != MOLTEN_ZOMBIE || gHideEffectText)
    return;

  if (EffectOpt_IsUsed(MOLTEN_ZOMBIE))
    return;

  controller = GetDuelistForZone(zone);
  if (controller > DUEL_OPPONENT)
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(controller);

  /* ponytail: printed is SS from GY; any placement stand-in. */
  Duel_ShowEffectTextTyped(MOLTEN_ZOMBIE, 8);
  if (Duel_DrawCards(turnDuelist, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  EffectOpt_MarkUsed(MOLTEN_ZOMBIE);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateMOLTEN_ZOMBIE(void)
{
  if (gMonEffect.id != MOLTEN_ZOMBIE)
    return FALSE;

  /* On-SS draw via TryMoltenZombieOnMonsterPlacement (any-placement stand-in). */
  return FALSE;
}

void ActivateMOLTEN_ZOMBIEEffect(void)
{
  Duel_ShowEffectTextTyped(MOLTEN_ZOMBIE, 2);
}
