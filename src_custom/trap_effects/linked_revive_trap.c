#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "linked_revive_trap.h"

static u8 IsLinkedReviveTrapId(u16 cardId)
{
  return cardId == GLORIOUS_ILLUSION || cardId == AMAZONESS_WILLPOWER
      || cardId == FOSSIL_EXCAVATION;
}

void LinkedReviveTrap_Link(struct DuelCard *trapZone, u8 monsterTurnCol)
{
  if (trapZone == NULL || monsterTurnCol >= MAX_ZONES_IN_ROW)
    return;

  trapZone->unk4 = (u8)(monsterTurnCol + 1);
}

static u8 BackrowForFixedDuelist(u8 controller)
{
  return controller == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
}

static struct DuelCard *FindLinkedTrapForMonster(u8 controller, u8 monsterCol)
{
  u8 backRow = BackrowForFixedDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *trap = gFixedZones[backRow][col];

    if (trap == NULL || !trap->isFaceUp || !IsLinkedReviveTrapId(trap->id))
      continue;
    if (trap->unk4 == (u8)(monsterCol + 1))
      return trap;
  }

  return NULL;
}

u8 Cond_LinkedReviveTrapOnLeave(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;

  if (ctx == NULL || ctx->event == NULL || ctx->event->zone == NULL)
    return FALSE;

  ev = ctx->event;

  if (IsLinkedReviveTrapId(ev->cardId))
    return ev->zone->unk4 > 0 && ev->zone->unk4 <= MAX_ZONES_IN_ROW;

  if (GetTypeGroup(ev->cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (ev->controller > DUEL_OPPONENT || ev->col >= MAX_ZONES_IN_ROW)
    return FALSE;

  return FindLinkedTrapForMonster(ev->controller, ev->col) != NULL;
}

enum DuelActionResult Op_LinkedReviveTrapOnLeave(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  struct DuelCard *trap;
  struct DuelCard *monster;
  u8 col;
  u8 turnDuelist;

  if (ctx == NULL || ctx->event == NULL || ctx->event->zone == NULL)
    return DUEL_ACTION_INVALID;

  ev = ctx->event;
  turnDuelist = Duel_TurnDuelistForFixedDuelist(
      ev->controller <= DUEL_OPPONENT ? ev->controller : DUEL_PLAYER);

  if (IsLinkedReviveTrapId(ev->cardId)) {
    col = (u8)(ev->zone->unk4 - 1);
    monster = gFixedZones[Duel_FixedMonsterRowForDuelist(ev->controller)][col];
    ev->zone->unk4 = 0;
    if (monster != NULL && monster->id != CARD_NONE)
      Duel_DestroyZone(monster, turnDuelist, FALSE);
    return IsDuelOver() == TRUE ? DUEL_ACTION_DUEL_OVER : DUEL_ACTION_OK;
  }

  trap = FindLinkedTrapForMonster(ev->controller, ev->col);
  if (trap == NULL)
    return DUEL_ACTION_NO_TARGET;

  trap->unk4 = 0;
  Duel_DestroyZone(trap, turnDuelist, FALSE);
  return IsDuelOver() == TRUE ? DUEL_ACTION_DUEL_OVER : DUEL_ACTION_OK;
}
