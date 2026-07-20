#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAmazonessName[] APPEND_RODATA = "Amazoness";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAmazonessSpellTrap(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sAmazonessName);
}

static u16 FindAmazonessSpellTrapInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsAmazonessSpellTrap(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateAMAZONESS_PRINCESS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AMAZONESS_PRINCESS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AMAZONESS_PRINCESS)
    return FALSE;

  /* ponytail: name=Queen + attack-send→SS need name/battle hooks.
   * Ceiling: OPT add 1 Amazoness Spell/Trap from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindAmazonessSpellTrapInDeck() != CARD_NONE;
}

void ActivateAMAZONESS_PRINCESSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(AMAZONESS_PRINCESS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindAmazonessSpellTrapInDeck();
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
