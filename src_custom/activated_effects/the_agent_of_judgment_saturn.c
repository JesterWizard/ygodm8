#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 LpHigherThanOpponent(void)
{
  u8 me = FixedDuelistForActive();
  u8 opp = me == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  return gDuelLifePoints[me] > gDuelLifePoints[opp];
}

unsigned char CanActivateTHE_AGENT_OF_JUDGMENT_SATURN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != THE_AGENT_OF_JUDGMENT_SATURN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != THE_AGENT_OF_JUDGMENT_SATURN)
    return FALSE;

  /* skip Battle Phase this turn needs phase-lock hook. Ceiling: tribute
   * self → burn LP difference when Sanctuary face-up and LP higher. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!Duel_IsBackrowCardOnField(THE_SANCTUARY_IN_THE_SKY, FALSE))
    return FALSE;

  return LpHigherThanOpponent();
}

void ActivateTHE_AGENT_OF_JUDGMENT_SATURNEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 me;
  u8 opp;
  s32 damage;

  Duel_ShowEffectTextTyped(THE_AGENT_OF_JUDGMENT_SATURN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!Duel_IsBackrowCardOnField(THE_SANCTUARY_IN_THE_SKY, FALSE) || !LpHigherThanOpponent())
    return;

  me = FixedDuelistForActive();
  opp = me == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  damage = (s32)gDuelLifePoints[me] - (s32)gDuelLifePoints[opp];

  ClearZone(self);

  if (IsDuelOver() == TRUE)
    return;

  if (damage > 0
      && Duel_ChangeLp(opp, -damage, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
