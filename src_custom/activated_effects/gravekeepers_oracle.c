#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

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

static u8 IsOppFieldCard(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 OppFieldHasCard(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsOppFieldCard(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void DestroyUpToTwoOppCards(void)
{
  u8 destroyed = 0;
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW && destroyed < 2; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW && destroyed < 2; col++) {
      struct DuelCard *zone;

      if (!IsOppFieldCard(row, col))
        continue;

      zone = gFixedZones[row][col];
      if (Duel_DestroyZone(zone, TurnDuelistForFixedRow(row), FALSE) == DUEL_ACTION_DUEL_OVER)
        return;

      destroyed++;
    }
  }

  if (destroyed)
    NotifyDynamicEquipFieldChanged();
}

unsigned char CanActivateGRAVEKEEPERS_ORACLE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GRAVEKEEPERS_ORACLE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GRAVEKEEPERS_ORACLE)
    return FALSE;

  /* ponytail: Tribute Summon sequence (destroy/flip/ATK) FALSE.
   * Ceiling: OPT destroy up to 2 cards on opp field. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OppFieldHasCard();
}

void ActivateGRAVEKEEPERS_ORACLEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_ORACLE, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  /* ponytail: multi-target picker not wired; auto-destroy up to 2 opp cards. */
  DestroyUpToTwoOppCards();
  if (IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
