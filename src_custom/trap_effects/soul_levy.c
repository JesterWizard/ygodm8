#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect.h"
#include "soul_levy.h"

static void ActivateSOUL_LEVYZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, SOUL_LEVY) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateSOUL_LEVYOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(SOUL_LEVY, ActivateSOUL_LEVYZone);
}

static u8 CountFaceUpSoulLevy(u8 fixedDuelist)
{
  u8 backrow = fixedDuelist == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 col;
  u8 n = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[backrow][col];

    if (zone != NULL && zone->id == SOUL_LEVY && zone->isFaceUp)
      n++;
  }
  return n;
}

u8 Cond_SoulLevyOnSummon(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  u8 controller;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return FALSE;
  if (GetTypeGroup(ev->cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  /* Opp of Soul Levy controller Special Summons; only 1 Soul Levy face-up. */
  controller = ev->controller == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  if (CountFaceUpSoulLevy(controller) != 1)
    return FALSE;

  return Duel_FindBackrowCard(controller, SOUL_LEVY, TRUE) != NULL;
}

enum DuelActionResult Op_SoulLevyOnSummon(struct EffectCtx *ctx)
{
  u8 oppTurn;

  if (ctx == NULL || ctx->event == NULL)
    return DUEL_ACTION_INVALID;

  oppTurn = (gTurnDuelistBattleState[ACTIVE_DUELIST]
                 == &gDuel.duelistbattleState[ctx->event->controller])
                ? ACTIVE_DUELIST
                : INACTIVE_DUELIST;

  Duel_ShowEffectText(SOUL_LEVY);
  return Duel_MillTopDeckCards(oppTurn, 3, TRUE);
}
