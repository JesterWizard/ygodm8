#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 OpponentMonsterRow(void)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return OPPONENT_MONSTER_ROW;

  return PLAYER_MONSTER_ROW;
}

static u8 OpponentBackrow(void)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return OPPONENT_BACKROW;

  return PLAYER_BACKROW;
}

static u8 TurnDuelistOwningFixedRow(u8 fixedRow)
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

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OpponentMonsterRow() && fixedRow != OpponentBackrow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE;
}

static void DestroyUpToTwoOppCards(void)
{
  u8 destroyed = 0;
  u8 row;
  u8 col;

  for (row = 0; row <= PLAYER_BACKROW && destroyed < 2; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW && destroyed < 2; col++) {
      struct DuelCard *zone;

      if (!IsValidTarget(row, col))
        continue;

      zone = gFixedZones[row][col];
      if (zone == NULL)
        continue;

      if (Duel_DestroyZone(zone, TurnDuelistOwningFixedRow(row), FALSE)
          == DUEL_ACTION_DUEL_OVER)
        return;
      destroyed++;
    }
  }
}

unsigned char CanActivateCELESTIA_LIGHTSWORN_ANGEL(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CELESTIA_LIGHTSWORN_ANGEL)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CELESTIA_LIGHTSWORN_ANGEL)
    return FALSE;

  /* ponytail: Tribute Summon (by Lightsworn) trigger needs summon hook.
   * Ceiling: once via usage — mill 4 then auto-destroy up to 2 opp cards
   * (no player target pick; upgrade: PickZone for up to 2). */
  return CanUseMonsterEffect(zone);
}

void ActivateCELESTIA_LIGHTSWORN_ANGELEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(CELESTIA_LIGHTSWORN_ANGEL, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  Duel_MillTopDeckCards(ACTIVE_DUELIST, 4, TRUE);
  if (IsDuelOver() == TRUE)
    return;

  DestroyUpToTwoOppCards();
  if (IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
