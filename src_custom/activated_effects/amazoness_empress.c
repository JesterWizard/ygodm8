#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u16 FindAmazonessQueenOrAmazonessInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, AMAZONESS_QUEEN) >= 0)
    return AMAZONESS_QUEEN;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (GetTypeGroup(cardId) == TYPE_GROUP_MONSTER && Duel_IsAmazonessCard(cardId)
        && cardId != AMAZONESS_EMPRESS && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateAMAZONESS_EMPRESS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AMAZONESS_EMPRESS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AMAZONESS_EMPRESS)
    return FALSE;

  /* ponytail: protect/pierce + leave-field SS Queen need permanent/leave hooks.
   * Ceiling: OPT add Amazoness Queen (or Amazoness) from Deck to hand. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindAmazonessQueenOrAmazonessInDeck() != CARD_NONE;
}

void ActivateAMAZONESS_EMPRESSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(AMAZONESS_EMPRESS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindAmazonessQueenOrAmazonessInDeck();
  if (cardId == CARD_NONE)
    return;

  /* ponytail: leave-field SS → Deck search stand-in (safer than Extra SS). */
  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, cardId, TRUE) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
