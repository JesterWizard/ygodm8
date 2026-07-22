#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "yowie.h"

static u8 ControlsOnlyThisMonster(u8 turnRow, u8 col)
{
  u8 c;
  u8 count = 0;

  for (c = 0; c < MAX_ZONES_IN_ROW; c++) {
    if (gTurnZones[turnRow][c]->id == CARD_NONE)
      continue;

    count++;
    if (count > 1)
      return FALSE;
  }

  return count == 1 && gTurnZones[turnRow][col]->id == YOWIE;
}

void ResetYowieSkipDraw(void)
{
  gYowieSkipDrawDuelist = YOWIE_SKIP_DRAW_NONE;
}

u8 ShouldSkipDrawPhaseForYowie(u8 turn)
{
  return gYowieSkipDrawDuelist == turn;
}

void ConsumeYowieSkipDraw(u8 turn)
{
  if (gYowieSkipDrawDuelist == turn)
    gYowieSkipDrawDuelist = YOWIE_SKIP_DRAW_NONE;
}

void Yowie_MarkOpponentSkipDraw(u8 turnDuelist)
{
  u8 opponent = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  if (gTurnDuelistBattleState[opponent] == &gDuel.duelistbattleState[DUEL_PLAYER])
    gYowieSkipDrawDuelist = DUEL_PLAYER;
  else
    gYowieSkipDrawDuelist = DUEL_OPPONENT;
}

unsigned char ShouldActivateYOWIE(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != YOWIE)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  return ControlsOnlyThisMonster(gActiveEffect.turnRow, gActiveEffect.col);
}

void ActivateYOWIE(void)
{
  struct DuelCard *zone;
  u8 turnDuelist;

  Duel_ShowEffectTextTyped(YOWIE, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  zone->unk4 = 1;

  turnDuelist = gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW
      ? ACTIVE_DUELIST
      : INACTIVE_DUELIST;
  Yowie_MarkOpponentSkipDraw(turnDuelist);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void Yowie_SelfCheck(void)
{
  ResetYowieSkipDraw();
  Yowie_MarkOpponentSkipDraw(ACTIVE_DUELIST);
  if (gYowieSkipDrawDuelist == YOWIE_SKIP_DRAW_NONE)
    while (1)
      ;
}
#endif
