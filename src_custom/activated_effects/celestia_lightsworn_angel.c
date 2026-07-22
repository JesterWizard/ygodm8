#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "summon_tribute.h"

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

static void RunCelestiaMillAndDestroy(struct DuelCard *self)
{
  if (self == NULL || IsDuelOver() == TRUE)
    return;

  Duel_MillTopDeckCards(ACTIVE_DUELIST, 4, TRUE);
  if (IsDuelOver() == TRUE)
    return;

  DestroyUpToTwoOppCards();
}

unsigned char ShouldActivateCelestiaLightswornAngelTribute(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != CELESTIA_LIGHTSWORN_ANGEL)
    return FALSE;

  if (GetPendingTributeSummonCardId() != CELESTIA_LIGHTSWORN_ANGEL)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->id != CELESTIA_LIGHTSWORN_ANGEL)
    return FALSE;

  return zone->unk4 == 0;
}

void ActivateCelestiaLightswornAngelTribute(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  Duel_ShowEffectTextTyped(CELESTIA_LIGHTSWORN_ANGEL, 8);
  RunCelestiaMillAndDestroy(zone);

  if (zone != NULL && IsDuelOver() != TRUE)
    zone->unk4 = 1;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateCELESTIA_LIGHTSWORN_ANGEL(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CELESTIA_LIGHTSWORN_ANGEL)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CELESTIA_LIGHTSWORN_ANGEL)
    return FALSE;

  /* Tribute Summon mill/destroy via ActivateCelestiaLightswornAngelTribute.
   * Ceiling: field OPT repeat (usage-gated). Auto-destroy up to 2 (no PickZone). */
  return CanUseMonsterEffect(zone);
}

void ActivateCELESTIA_LIGHTSWORN_ANGELEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(CELESTIA_LIGHTSWORN_ANGEL, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  RunCelestiaMillAndDestroy(self);
  if (IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
