#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
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

static u8 ExchangeOfSpiritInGy(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard == EXCHANGE_OF_THE_SPIRIT;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == EXCHANGE_OF_THE_SPIRIT)
      return TRUE;
  }

  return FALSE;
}

static u8 IsGravekeeperOrEarthFairy(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (Duel_CardNameContains(cardId, sGravekeepersName))
    return TRUE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_EARTH
      && Duel_CardHasMonsterType(cardId, TYPE_FAIRY);
}

static u8 AnyHandCard(u16 cardId)
{
  (void)cardId;
  return TRUE;
}

static void ActivateGRAVEKEEPERS_TRAPZone(struct DuelCard *zone)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u16 cardId = CARD_NONE;
  u8 deckIndex = 0;
  s8 empty;

  if (Duel_ActivateContinuousTrapPreamble(zone, GRAVEKEEPERS_TRAP)
      == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: Exchange lock GY effects/SS + opp Draw Phase look + discard cost
   * need GY/draw gates. Ceiling: if Exchange in GY mark unk4 lock; discard 1
   * → search Gravekeeper's / EARTH Fairy. */

  if (ExchangeOfSpiritInGy())
    zone->unk4 = 1; /* GY lock mark */

  if (Duel_DiscardFromHand(INACTIVE_DUELIST, 1, AnyHandCard, TRUE) != DUEL_ACTION_OK)
    return;

  empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
  if (empty < 0)
    return;

  for (i = top; i < deckSize; i++) {
    if (IsGravekeeperOrEarthFairy(gDuelDecks[fixedDuelist].cards[i])) {
      cardId = gDuelDecks[fixedDuelist].cards[i];
      deckIndex = i;
      break;
    }
  }

  if (cardId != CARD_NONE
      && Duel_RemoveDeckCardAt(INACTIVE_DUELIST, deckIndex, FALSE) == DUEL_ACTION_OK)
    InitHandSlotFromCard(gTurnHands[INACTIVE_DUELIST][empty], cardId);

  UpdateDuelGfxExceptField();
}

void TryActivateGRAVEKEEPERS_TRAPOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(GRAVEKEEPERS_TRAP,
                                         ActivateGRAVEKEEPERS_TRAPZone);
}

/* ponytail: TryActivateGRAVEKEEPERS_TRAPOnOpponentTurnStart must be called from
 * turn_effect_hooks. Ceiling: body ready, not wired. */
