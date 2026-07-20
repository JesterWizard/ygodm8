#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sGravekeeperName[] APPEND_RODATA = "Gravekeeper";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsGravekeeperMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGravekeeperName);
}

static u16 FindGravekeeperOrNecrovalleyInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (cardId == NECROVALLEY || IsGravekeeperMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateGRAVEKEEPERS_SUPERNATURALIST(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GRAVEKEEPERS_SUPERNATURALIST)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GRAVEKEEPERS_SUPERNATURALIST)
    return FALSE;

  /* ponytail: material ATK gain + Necrovalley destroy protect + EP schedule FALSE.
   * Ceiling: OPT add Gravekeeper or Necrovalley from Deck now (EP add stand-in). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindGravekeeperOrNecrovalleyInDeck() != CARD_NONE;
}

void ActivateGRAVEKEEPERS_SUPERNATURALISTEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_SUPERNATURALIST, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindGravekeeperOrNecrovalleyInDeck();
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
