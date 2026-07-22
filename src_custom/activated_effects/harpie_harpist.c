#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sHarpieName[] APPEND_RODATA = "Harpie";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsHarpieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 IsWingedBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_WINGED_BEAST);
}

static struct DuelCard *FindOwnOtherWingedBeast(struct DuelCard *self)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone == self || zone->id == CARD_NONE)
      continue;

    if (IsWingedBeastMonster(zone->id))
      return zone;
  }

  return NULL;
}

static struct DuelCard *FindOppFaceUpMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    if (IsCardFaceUp(zone) || zone->isDefending == FALSE)
      return zone;
  }

  return NULL;
}

static u8 CanBounceBoth(struct DuelCard *self)
{
  if (FindOwnOtherWingedBeast(self) == NULL)
    return FALSE;

  if (FindOppFaceUpMonster() == NULL)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]) >= 0;
}

static u16 FindHarpieInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsHarpieMonster(cardId) && cardId != HARPIE_HARPIST)
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanSearchHarpie(void)
{
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindHarpieInDeck() != CARD_NONE;
}

unsigned char CanActivateHARPIE_HARPIST(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != HARPIE_HARPIST)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != HARPIE_HARPIST)
    return FALSE;

  /* Ceiling: NS trigger + GY End Phase search need separate hooks. OPT bounce
   * own WB + opp face-up, else OPT add Harpie from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (CanBounceBoth(zone))
    return TRUE;

  return CanSearchHarpie();
}

void ActivateHARPIE_HARPISTEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelCard *ownWb;
  struct DuelCard *oppMon;
  u16 searchId;

  Duel_ShowEffectTextTyped(HARPIE_HARPIST, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (CanBounceBoth(self)) {
    ownWb = FindOwnOtherWingedBeast(self);
    oppMon = FindOppFaceUpMonster();
    if (ownWb == NULL || oppMon == NULL)
      return;

    if (Duel_ReturnMonsterZoneToOwnerHand(ownWb, FALSE) != DUEL_ACTION_OK)
      return;

    if (Duel_ReturnMonsterZoneToOwnerHand(oppMon, FALSE) != DUEL_ACTION_OK)
      return;

    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  searchId = FindHarpieInDeck();
  if (searchId == CARD_NONE)
    return;

  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, searchId, TRUE) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
