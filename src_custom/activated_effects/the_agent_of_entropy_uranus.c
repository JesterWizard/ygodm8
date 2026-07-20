#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
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

  if (cardId == THE_AGENT_OF_ENTROPY_URANUS)
    return FALSE;

  return Duel_CardNameContains(cardId, sTheAgentName);
}

static u16 FindDeckAgentToMill(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsTheAgentMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 MillAgentFromDeckToGy(u16 *outCardId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u16 cardId;

  cardId = FindDeckAgentToMill();
  if (cardId == CARD_NONE)
    return FALSE;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] != cardId)
      continue;

    if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, i, FALSE) != DUEL_ACTION_OK)
      return FALSE;

    if (GraveyardExpand_IsEnabled())
      GraveyardExpand_PushFixed(fixedDuelist, cardId);
    else
      gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard = cardId;

    *outCardId = cardId;
    return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateTHE_AGENT_OF_ENTROPY_URANUS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != THE_AGENT_OF_ENTROPY_URANUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != THE_AGENT_OF_ENTROPY_URANUS)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FindDeckAgentToMill() != CARD_NONE;
}

void ActivateTHE_AGENT_OF_ENTROPY_URANUSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 milledId = CARD_NONE;
  u8 milledLevel;

  Duel_ShowEffectTextTyped(THE_AGENT_OF_ENTROPY_URANUS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!MillAgentFromDeckToGy(&milledId))
    return;

  SetCardInfo(milledId);
  milledLevel = gCardInfo.level;

  /* ponytail: tempStage stores milled Level, not a true level change hook. */
  self->tempStage = (s8)milledLevel;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonTheAgentOfEntropyUranusFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != THE_AGENT_OF_ENTROPY_URANUS)
    return FALSE;

  if (!Duel_IsBackrowCardOnField(THE_SANCTUARY_IN_THE_SKY, FALSE))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonTheAgentOfEntropyUranusFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonTheAgentOfEntropyUranusFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(THE_AGENT_OF_ENTROPY_URANUS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}
