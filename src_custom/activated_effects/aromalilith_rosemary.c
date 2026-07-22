#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAromaName[] APPEND_RODATA = "Aroma";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAromaCard(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == AROMALILITH_ROSEMARY)
    return FALSE;

  return Duel_CardNameContains(cardId, sAromaName);
}

static u16 FindDeckAroma(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsAromaCard(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateAROMALILITH_ROSEMARY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AROMALILITH_ROSEMARY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AROMALILITH_ROSEMARY)
    return FALSE;

  /* OPT search Aroma from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindDeckAroma() != CARD_NONE;
}

void ActivateAROMALILITH_ROSEMARYEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(AROMALILITH_ROSEMARY, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindDeckAroma();
  if (cardId == CARD_NONE)
    return;

  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, cardId, TRUE) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
