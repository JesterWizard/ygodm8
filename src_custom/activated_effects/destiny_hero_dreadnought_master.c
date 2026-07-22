#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == DESTINY_HERO_DREADNOUGHT_MASTER)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u16 FindDestinyHeroInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsDestinyHeroMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateDESTINY_HERO_DREADNOUGHT_MASTER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DESTINY_HERO_DREADNOUGHT_MASTER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_DREADNOUGHT_MASTER)
    return FALSE;

  /* Ceiling: SS trigger → OPT ignition; cards-mentioning-D-HERO FALSE.
   * Ceiling: OPT add up to 2 Destiny HERO from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindDestinyHeroInDeck() != CARD_NONE;
}

void ActivateDESTINY_HERO_DREADNOUGHT_MASTEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 added = 0;
  u16 cardId;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DREADNOUGHT_MASTER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  while (added < 2 && FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0) {
    cardId = FindDestinyHeroInDeck();
    if (cardId == CARD_NONE)
      break;

    if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, cardId, TRUE) != DUEL_ACTION_OK)
      break;

    added++;
  }

  if (added == 0)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
