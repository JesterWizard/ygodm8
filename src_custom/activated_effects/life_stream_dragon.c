#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

unsigned char CanActivateLIFE_STREAM_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != LIFE_STREAM_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != LIFE_STREAM_DRAGON)
    return FALSE;

  /* ponytail: Synchro LP=4000 trigger + no effect damage + Equip-banish
   * destruction-replace need synchro/LP/battle hooks. Ceiling: OPT set LP to
   * 4000 via usage. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return TRUE;
}

void ActivateLIFE_STREAM_DRAGONEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();
  s32 delta;

  Duel_ShowEffectTextTyped(LIFE_STREAM_DRAGON, 2);

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  delta = 4000 - (s32)gDuelLifePoints[fixedDuelist];
  if (delta != 0
      && Duel_ChangeLp(ACTIVE_DUELIST, delta, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(zone);
  UpdateDuelGfxExceptField();
}
