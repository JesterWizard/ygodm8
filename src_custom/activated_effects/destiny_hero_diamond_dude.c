#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 DeckHasRemainingCards(u8 fixedDuelist)
{
  return gDuelDecks[fixedDuelist].cardsDrawn < NumCardsInDeck(fixedDuelist);
}

static u8 IsNormalSpellCard(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  return GetSpellType(cardId) == SPELL_TYPE_NORMAL;
}

static void MoveTopUndrawnCardToDeckBottom(u8 fixedDuelist, u16 cardId, u8 topIndex)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 i;

  for (i = topIndex; i + 1 < deckSize; i++)
    gDuelDecks[fixedDuelist].cards[i] = gDuelDecks[fixedDuelist].cards[i + 1];

  gDuelDecks[fixedDuelist].cards[deckSize - 1] = cardId;
}

static void ExcavateTopCard(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 top;
  u16 cardId;

  if (!DeckHasRemainingCards(fixedDuelist))
    return;

  top = gDuelDecks[fixedDuelist].cardsDrawn;
  cardId = gDuelDecks[fixedDuelist].cards[top];

  if (IsNormalSpellCard(cardId)) {
    gDuelDecks[fixedDuelist].cardsDrawn++;
    GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
    /* Next-turn GY Normal Spell activation needs Main Phase hook. */
    return;
  }

  MoveTopUndrawnCardToDeckBottom(fixedDuelist, cardId, top);
}

unsigned char CanActivateDESTINY_HERO_DIAMOND_DUDE(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist;

  if (gMonEffect.id != DESTINY_HERO_DIAMOND_DUDE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_DIAMOND_DUDE)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  fixedDuelist = FixedDuelistForActive();
  return DeckHasRemainingCards(fixedDuelist);
}

void ActivateDESTINY_HERO_DIAMOND_DUDEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(DESTINY_HERO_DIAMOND_DUDE, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  ExcavateTopCard();

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
