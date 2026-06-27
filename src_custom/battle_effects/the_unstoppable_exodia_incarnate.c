#include "global.h"
#include "common-chax.h"
#include "duel.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "constants/card_ids.h"

/* ── Dynamic zone stat: ATK = controller's LP ── */

u8 UnstoppableExodiaIncarnate_ApplyStat(struct DuelCard *zone)
{
  u8 duelist = GetDuelistForZone(zone);
  u32 lp;

  if (zone == NULL || zone->id != THE_UNSTOPPABLE_EXODIA_INCARNATE)
    return FALSE;

  SetCardInfo(zone->id);

  lp = gDuelLifePoints[duelist];
  if (lp > 65535)
    lp = 65535;

  Duel_WriteCardInfoStats(zone->id, (u16)lp, gCardInfo.def);
  return TRUE;
}

/* ── Turn effect: show popup + lose 1000 LP ── */

u8 ShouldActivateUnstoppableExodiaIncarnateTurnEffect(void)
{
  if (gActiveEffect.cardId != THE_UNSTOPPABLE_EXODIA_INCARNATE)
    return FALSE;
  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col]->isFaceUp;
}

void ActivateUnstoppableExodiaIncarnateTurnEffect(void)
{
  u8 owner;

  Duel_ShowEffectTextTyped(THE_UNSTOPPABLE_EXODIA_INCARNATE, 8);
  if (IsDuelOver() == TRUE)
    return;

  owner = GetDuelistForZone(gTurnZones[gActiveEffect.turnRow][gActiveEffect.col]);
  Duel_ChangeLp(owner, -1000, TRUE);
}
