#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "graveyard_effects.h"
#include "oshaleon.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

struct DuelCard *Oshaleon_GetForcedAttackTarget(u8 defenderDuelist)
{
  u8 fixedRow = Duel_FixedMonsterRowForDuelist(defenderDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone == NULL || zone->id != OSHALEON)
      continue;
    if (!IsCardFaceUp(zone))
      continue;
    if (zone->isDefending)
      continue;
    return zone;
  }

  return NULL;
}

u8 Oshaleon_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE || zone->id == OSHALEON)
    return TRUE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return TRUE;

  return Oshaleon_GetForcedAttackTarget(Duel_FixedDuelistForMonsterRow(fixedRow)) == NULL;
}

static u8 TurnDuelistFromGraveyardRow(u8 turnRow)
{
  if (turnRow == 7)
    return INACTIVE_DUELIST;

  return ACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u16 FindReptileAtkOrLessInDeck(u8 turnDuelist, u16 maxAtk)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!Duel_CardHasMonsterType(cardId, TYPE_REPTILE))
      continue;
    SetCardInfo(cardId);
    if (gCardInfo.atk <= maxAtk)
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanAddReptileFromDeckToHand(u8 turnDuelist)
{
  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  return FindReptileAtkOrLessInDeck(turnDuelist, 500) != CARD_NONE;
}

unsigned char ShouldActivateOSHALEON(void)
{
  u8 turnDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gGraveyardSendWasFromField)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != OSHALEON)
    return FALSE;

  turnDuelist = TurnDuelistFromGraveyardRow(gActiveEffect.turnRow);
  if (gActiveEffect.turnRow == 7) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard != OSHALEON)
      return FALSE;
  } else if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != OSHALEON) {
    return FALSE;
  }

  return CanAddReptileFromDeckToHand(turnDuelist);
}

void ActivateOSHALEON(void)
{
  u8 turnDuelist;
  u16 cardId;

  if (gActiveEffect.turnRow == 7)
    turnDuelist = INACTIVE_DUELIST;
  else
    turnDuelist = ACTIVE_DUELIST;

  Duel_ShowEffectTextTyped(OSHALEON, 8);
  if (IsDuelOver() == TRUE)
    return;

  GetGraveCardAndClearGrave(turnDuelist);

  cardId = FindReptileAtkOrLessInDeck(turnDuelist, 500);
  if (cardId == CARD_NONE)
    return;

  if (Duel_AddDeckCardToHand(turnDuelist, cardId, TRUE) != DUEL_ACTION_OK)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
