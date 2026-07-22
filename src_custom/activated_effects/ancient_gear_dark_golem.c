#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAncientGearOrGeartown(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == ANCIENT_GEAR_DARK_GOLEM)
    return FALSE;

  if (cardId == GEARTOWN)
    return TRUE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

static u16 FindAncientGearOrGeartownInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsAncientGearOrGeartown(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateANCIENT_GEAR_DARK_GOLEM(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ANCIENT_GEAR_DARK_GOLEM)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ANCIENT_GEAR_DARK_GOLEM)
    return FALSE;

  /* OPT add up to 2 Ancient Gear/Geartown from Deck then discard 1. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindAncientGearOrGeartownInDeck() != CARD_NONE;
}

void ActivateANCIENT_GEAR_DARK_GOLEMEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 added = 0;
  u16 cardId;

  Duel_ShowEffectTextTyped(ANCIENT_GEAR_DARK_GOLEM, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  while (added < 2 && FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0) {
    cardId = FindAncientGearOrGeartownInDeck();
    if (cardId == CARD_NONE)
      break;

    if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, cardId, TRUE) != DUEL_ACTION_OK)
      break;

    added++;
  }

  if (added == 0)
    return;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) > 0) {
    if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
