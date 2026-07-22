#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define THEINEN_LP_COST 500
#define THEINEN_ATK_STAGES 7 /* ~3000 ATK */

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CanPayCost(void)
{
  return gDuelLifePoints[FixedDuelistForActive()] >= THEINEN_LP_COST;
}

unsigned char CanActivateTHEINEN_THE_GREAT_SPHINX(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != THEINEN_THE_GREAT_SPHINX)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != THEINEN_THE_GREAT_SPHINX)
    return FALSE;

  /* Andro+Teleia destroy SS from hand/Deck needs destroy hook.
   * Ceiling: OPT pay 500 → +7 tempStage (~3000 ATK). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanPayCost();
}

void ActivateTHEINEN_THE_GREAT_SPHINXEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s8 stages;

  Duel_ShowEffectTextTyped(THEINEN_THE_GREAT_SPHINX, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!CanPayCost())
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)THEINEN_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  stages = self->tempStage + THEINEN_ATK_STAGES;
  if (stages > 126)
    stages = 126;
  self->tempStage = stages;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
