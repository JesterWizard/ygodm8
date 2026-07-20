#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

unsigned char CanActivateANCIENT_SACRED_WYVERN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ANCIENT_SACRED_WYVERN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ANCIENT_SACRED_WYVERN)
    return FALSE;

  /* ponytail: continuous LP→ATK + battle-reborn need permanent/battle hooks.
   * Ceiling: OPT refresh tempStage from LP difference/500. */
  return CanUseMonsterEffect(zone);
}

void ActivateANCIENT_SACRED_WYVERNEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 me;
  u8 opp;
  s32 diff;
  s32 stages;

  Duel_ShowEffectTextTyped(ANCIENT_SACRED_WYVERN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  me = FixedDuelistForActive();
  opp = me == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  diff = (s32)gDuelLifePoints[me] - (s32)gDuelLifePoints[opp];
  stages = diff / 500;

  if (stages > 126)
    stages = 126;
  else if (stages < -126)
    stages = -126;

  self->tempStage = (s8)stages;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
