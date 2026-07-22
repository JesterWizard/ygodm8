#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForFixedRow(u8 fixedRow)
{
  u8 fixedOwner;

  if (fixedRow == PLAYER_MONSTER_ROW || fixedRow == PLAYER_BACKROW)
    fixedOwner = DUEL_PLAYER;
  else
    fixedOwner = DUEL_OPPONENT;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedOwner])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static struct DuelCard *JudgmentZone(void)
{
  return gTurnZones[gMonEffect.row][gMonEffect.zone];
}

static u8 FieldHasOtherCard(struct DuelCard *self)
{
  u8 row;
  u8 col;

  for (row = 0; row < 4; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];

      if (zone == self || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      return TRUE;
    }
  }

  return FALSE;
}

static u16 HalfLpCost(void)
{
  u8 me = FixedDuelistForActive();

  return gDuelLifePoints[me] / 2;
}

static void DestroyAllOtherFieldCards(struct DuelCard *protectedZone)
{
  u8 row;
  u8 col;
  u8 destroyed = FALSE;

  for (row = 0; row < 4; row++) {
    u8 graveyardDuelist = TurnDuelistForFixedRow(row);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];

      if (zone == protectedZone || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (Duel_DestroyZone(zone, graveyardDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;

      destroyed = TRUE;
    }
  }

  if (destroyed) {
    NotifyDynamicEquipFieldChanged();
    UpdateDuelGfxExceptField();
  }
}

unsigned char CanActivateJUDGMENT_THE_DRAGON_OF_HEAVEN(void)
{
  struct DuelCard *zone;
  u16 cost;

  if (gMonEffect.id != JUDGMENT_THE_DRAGON_OF_HEAVEN)
    return FALSE;

  zone = JudgmentZone();
  if (zone == NULL || zone->id != JUDGMENT_THE_DRAGON_OF_HEAVEN)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * TryApplyJudgmentEndPhase. OPT pay half LP → destroy all other field cards. */
  if (EffectOpt_IsUsed(JUDGMENT_THE_DRAGON_OF_HEAVEN))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  cost = HalfLpCost();
  if (cost == 0)
    return FALSE;

  return FieldHasOtherCard(zone);
}

void ActivateJUDGMENT_THE_DRAGON_OF_HEAVENEffect(void)
{
  struct DuelCard *self = JudgmentZone();
  u16 cost;

  Duel_ShowEffectTextTyped(JUDGMENT_THE_DRAGON_OF_HEAVEN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(JUDGMENT_THE_DRAGON_OF_HEAVEN))
    return;

  cost = HalfLpCost();
  if (cost == 0)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)cost, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  DestroyAllOtherFieldCards(self);

  EffectOpt_MarkUsed(JUDGMENT_THE_DRAGON_OF_HEAVEN);
  if (self != NULL)
    MarkMonsterEffectUsed(self);

  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
