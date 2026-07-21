#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsTrapCard(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_TRAP;
}

static u16 FindDeckTrapIndex(u8 fixedDuelist, u8 *outIndex)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsTrapCard(cardId)) {
      *outIndex = i;
      return cardId;
    }
  }

  return CARD_NONE;
}

static void PlaceCardOnDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 MoveDeckTrapToTop(u8 fixedDuelist, u8 deckIndex, u16 cardId)
{
  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  PlaceCardOnDeckTop(fixedDuelist, cardId);
  return TRUE;
}

unsigned char CanActivateA_CAT_OF_ILL_OMEN(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist;
  u8 deckIndex;
  u8 necrovalley;

  if (gMonEffect.id != A_CAT_OF_ILL_OMEN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != A_CAT_OF_ILL_OMEN)
    return FALSE;

  /* Flip trigger is live via TryActivateFlipDeckSearchOnFaceUp. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  fixedDuelist = FixedDuelistForActive();
  if (FindDeckTrapIndex(fixedDuelist, &deckIndex) == CARD_NONE)
    return FALSE;

  necrovalley = Duel_IsBackrowCardOnField(NECROVALLEY, TRUE);
  if (necrovalley && FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return TRUE;
}

void ActivateA_CAT_OF_ILL_OMENEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckIndex;
  u16 trapId;

  Duel_ShowEffectTextTyped(A_CAT_OF_ILL_OMEN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  trapId = FindDeckTrapIndex(fixedDuelist, &deckIndex);
  if (trapId == CARD_NONE)
    return;

  if (Duel_IsBackrowCardOnField(NECROVALLEY, TRUE)) {
    if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
      return;

    if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, trapId, TRUE) != DUEL_ACTION_OK)
      return;
  } else if (!MoveDeckTrapToTop(fixedDuelist, deckIndex, trapId)) {
    return;
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
