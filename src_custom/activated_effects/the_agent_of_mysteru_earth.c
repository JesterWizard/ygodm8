#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sTheAgentName[] APPEND_RODATA = "The Agent";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsTheAgentMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (cardId == THE_AGENT_OF_MYSTERU_EARTH)
    return FALSE;

  return Duel_CardNameContains(cardId, sTheAgentName);
}

static u16 FindDeckSearchTarget(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  if (Duel_IsBackrowCardOnField(THE_SANCTUARY_IN_THE_SKY, FALSE)) {
    if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, MASTER_HYPERION) >= 0)
      return MASTER_HYPERION;
  }

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsTheAgentMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static u8 AddDeckSearchTargetToHand(u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  s8 handZone;

  if (cardId == CARD_NONE)
    return FALSE;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0)
    return FALSE;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] != cardId)
      continue;

    if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, i, FALSE) != DUEL_ACTION_OK)
      return FALSE;

    InitHandSlotFromCard(
        SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), cardId);
    return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateTHE_AGENT_OF_MYSTERU_EARTH(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != THE_AGENT_OF_MYSTERU_EARTH)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != THE_AGENT_OF_MYSTERU_EARTH)
    return FALSE;

  /* ponytail: Normal Summon trigger needs summon hook. Ceiling: OPT add 1 The
   * Agent except Earth from Deck, or Master Hyperion if Sanctuary is face-up. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindDeckSearchTarget() != CARD_NONE;
}

void ActivateTHE_AGENT_OF_MYSTERU_EARTHEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(THE_AGENT_OF_MYSTERU_EARTH, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindDeckSearchTarget();
  if (cardId == CARD_NONE)
    return;

  if (!AddDeckSearchTargetToHand(cardId))
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
