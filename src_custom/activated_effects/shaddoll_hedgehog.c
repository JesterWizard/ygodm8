#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sShaddollName[] APPEND_RODATA = "Shaddoll";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsShaddollCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sShaddollName);
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

static u16 FindDeckShaddollTarget(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u16 monsterTarget = CARD_NONE;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];
    u8 typeGroup;

    if (!IsShaddollCard(cardId))
      continue;

    typeGroup = GetTypeGroup(cardId);
    if (typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP)
      return cardId;

    if (monsterTarget == CARD_NONE && typeGroup == TYPE_GROUP_MONSTER
        && cardId != SHADDOLL_HEDGEHOG)
      monsterTarget = cardId;
  }

  return monsterTarget;
}

static u8 AddDeckShaddollTargetToHand(u16 cardId)
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

unsigned char CanActivateSHADDOLL_HEDGEHOG(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SHADDOLL_HEDGEHOG)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SHADDOLL_HEDGEHOG)
    return FALSE;

  /* ponytail: FLIP S/T vs GY-sent monster exclusivity + trigger hooks deferred.
   * Ceiling: OPT search 1 Shaddoll S/T or monster from Deck once via usage. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindDeckShaddollTarget() != CARD_NONE;
}

void ActivateSHADDOLL_HEDGEHOGEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(SHADDOLL_HEDGEHOG, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindDeckShaddollTarget();
  if (cardId == CARD_NONE)
    return;

  if (!AddDeckShaddollTargetToHand(cardId))
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
