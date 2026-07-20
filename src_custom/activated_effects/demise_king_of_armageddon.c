#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

#define DEMISE_LP_COST 2000

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

unsigned char CanActivateDEMISE_KING_OF_ARMAGEDDON(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist;

  if (gMonEffect.id != DEMISE_KING_OF_ARMAGEDDON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DEMISE_KING_OF_ARMAGEDDON)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    fixedDuelist = DUEL_PLAYER;
  else
    fixedDuelist = DUEL_OPPONENT;

  return gDuelLifePoints[fixedDuelist] > DEMISE_LP_COST;
}

void ActivateDEMISE_KING_OF_ARMAGEDDONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 row;
  u8 col;

  Duel_ShowEffectTextTyped(DEMISE_KING_OF_ARMAGEDDON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -DEMISE_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE || zone == self)
        continue;

      Duel_DestroyZone(zone, TurnDuelistOwningFixedRow(row), FALSE);
      if (IsDuelOver() == TRUE)
        return;
    }
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
