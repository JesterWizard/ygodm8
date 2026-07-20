#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsRecruiterTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardNameContains(cardId, sGravekeepersName))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.def <= 1500;
}

static u16 FindDeckRecruiterTarget(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsRecruiterTarget(gDuelDecks[fixedDuelist].cards[i]))
      return gDuelDecks[fixedDuelist].cards[i];
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

static u8 AddDeckRecruiterTargetToHand(u16 cardId)
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

unsigned char CanActivateGRAVEKEEPERS_RECRUITER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GRAVEKEEPERS_RECRUITER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GRAVEKEEPERS_RECRUITER)
    return FALSE;

  /* ponytail: sent-to-GY trigger needs destroy/send hook. Ceiling: once via usage
   * if GK ≤1500 DEF in Deck and hand space. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindDeckRecruiterTarget() != CARD_NONE;
}

void ActivateGRAVEKEEPERS_RECRUITEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_RECRUITER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindDeckRecruiterTarget();
  if (cardId == CARD_NONE)
    return;

  if (!AddDeckRecruiterTargetToHand(cardId))
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
