#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "atlantean_dragoons.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

u8 GetDuelistForZone(struct DuelCard *zone);

static u8 ControllerHasFaceUpDragoons(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == ATLANTEAN_DRAGOONS)
      return TRUE;
  }
  return FALSE;
}

u8 AtlanteanDragoons_CanSeaSerpentAttackDirectly(const struct DuelCard *attacker)
{
  u8 controller;

  if (attacker == NULL || attacker->id == CARD_NONE)
    return FALSE;
  if (!Duel_CardHasMonsterType(attacker->id, TYPE_SEA_SERPENT))
    return FALSE;
  if (gCardData_NEW[attacker->id].level == 0 || gCardData_NEW[attacker->id].level > 3)
    return FALSE;

  controller = GetDuelistForZone((struct DuelCard *)attacker);
  if (controller > DUEL_OPPONENT)
    return FALSE;
  return ControllerHasFaceUpDragoons(controller);
}

void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsSeaSerpentMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_SEA_SERPENT);
}

static u16 FindDeckSeaSerpentTarget(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsSeaSerpentMonster(cardId) && cardId != ATLANTEAN_DRAGOONS)
      return cardId;
  }

  return CARD_NONE;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static u8 AddDeckSeaSerpentToHand(u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  s8 handZone;

  if (cardId == CARD_NONE)
    return FALSE;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0)
    return FALSE;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] != cardId)
      continue;

    if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, i, FALSE) != DUEL_ACTION_OK)
      return FALSE;

    InitHandSlotFromCard(
        SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), cardId);
    return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateATLANTEAN_DRAGOONS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ATLANTEAN_DRAGOONS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ATLANTEAN_DRAGOONS)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindDeckSeaSerpentTarget() != CARD_NONE;
}

void ActivateATLANTEAN_DRAGOONSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(ATLANTEAN_DRAGOONS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindDeckSeaSerpentTarget();
  if (cardId == CARD_NONE)
    return;

  if (!AddDeckSeaSerpentToHand(cardId))
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
