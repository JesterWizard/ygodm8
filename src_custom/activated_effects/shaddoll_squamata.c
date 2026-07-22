#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "monster_effect_usage.h"

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

static u8 IsMillableShaddollFromDeck(u16 cardId)
{
  return IsShaddollCard(cardId) && cardId != SHADDOLL_SQUAMATA;
}

static u8 OppHasDestroyTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[OPPONENT_MONSTER_ROW][col];

    if (zone != NULL && zone->id != CARD_NONE && !IsGodCard(zone->id))
      return TRUE;
  }

  return FALSE;
}

static s16 FindDeckShaddollIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsMillableShaddollFromDeck(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 DeckHasMillableShaddoll(void)
{
  return FindDeckShaddollIndex() >= 0;
}

static u8 MillOneShaddollFromDeck(void)
{
  s16 deckIndex = FindDeckShaddollIndex();
  u16 cardId;

  if (deckIndex < 0)
    return FALSE;

  cardId = gDuelDecks[FixedDuelistForActive()].cards[deckIndex];
  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
  return TRUE;
}

static u8 IsValidDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return !IsGodCard(zone->id);
}

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = OPPONENT_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidDestroyTarget(*outRow, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidDestroyTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

unsigned char CanActivateSHADDOLL_SQUAMATA(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SHADDOLL_SQUAMATA)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SHADDOLL_SQUAMATA)
    return FALSE;

  /* FLIP destroy vs GY-sent mill exclusivity + trigger hooks deferred.
   * Ceiling: destroy 1 opp monster OR mill 1 Shaddoll from Deck once via usage. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OppHasDestroyTarget() || DeckHasMillableShaddoll();
}

void ActivateSHADDOLL_SQUAMATAEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(SHADDOLL_SQUAMATA, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (OppHasDestroyTarget()) {
    gDuelCursor.destY = gMonEffect.row;
    gDuelCursor.destX = gMonEffect.zone;

    Duel_SetupPickZone(IsValidDestroyTarget, ResolveDestroyTarget, CancelTargeting,
                       AiPickDestroyTarget);

    if (WhoseTurn() == DUEL_PLAYER)
      Duel_EnterPickZoneTargeting();
    else
      Duel_ResolvePickZoneForAi();
    return;
  }

  if (!DeckHasMillableShaddoll())
    return;

  if (!MillOneShaddollFromDeck())
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
