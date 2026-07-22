#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsFairyMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].type == TYPE_FAIRY;
}

static u16 FindFairyInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsFairyMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 SendFairyFromDeckToGraveyard(u16 *outLevel)
{
  u8 fixedDuelist = FixedDuelistForActive();
  s16 deckIndex;
  u16 cardId;
  u8 turnDuelist;

  cardId = FindFairyInDeck();
  if (cardId == CARD_NONE)
    return FALSE;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[fixedDuelist]) {
      GraveyardExpand_PushTurn(turnDuelist, cardId);
      break;
    }
  }

  *outLevel = gCardData_NEW[cardId].level;
  return TRUE;
}

unsigned char CanActivateDIVINER_OF_THE_HERALD(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DIVINER_OF_THE_HERALD)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DIVINER_OF_THE_HERALD)
    return FALSE;

  /* Ceiling: on-NS/SS mill + tribute SS Fairy need summon/tribute hooks.
   * Ceiling: OPT send 1 Fairy from Deck to GY (+unkTwo Level stand-in). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FindFairyInDeck() != CARD_NONE;
}

void ActivateDIVINER_OF_THE_HERALDEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 level = 0;

  Duel_ShowEffectTextTyped(DIVINER_OF_THE_HERALD, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!SendFairyFromDeckToGraveyard(&level))
    return;

  /* Ceiling: Level bump until EOT needs level-override hook; unkTwo stores milled Level. */
  self->unkTwo = (u8)level;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
