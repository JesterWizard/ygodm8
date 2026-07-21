#include "global.h"
#include "common-chax.h"
#include "amazoness_spy.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "graveyard_effects.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

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

struct AmazonessSpyActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct AmazonessSpyActionData sActionData;

static u8 HandHasOtherAmazoness(u8 spyHandZone)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u16 cardId;

    if (col == spyHandZone)
      continue;

    cardId = gTurnHands[ACTIVE_DUELIST][col]->id;
    if (cardId != CARD_NONE && Duel_IsAmazonessCard(cardId) && cardId != AMAZONESS_SPY)
      return TRUE;
  }

  return FALSE;
}

static u8 FixedDuelistToTurnDuelist(u8 fixedDuelist)
{
  u8 duelist;

  for (duelist = 0; duelist < 2; duelist++) {
    if (gTurnDuelistBattleState[duelist] == &gDuel.duelistbattleState[fixedDuelist])
      return duelist;
  }

  return ACTIVE_DUELIST;
}

static s16 FindAmazonessGyIndexExceptSpy(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (Duel_IsAmazonessCard(top) && top != AMAZONESS_SPY
        && GetTypeGroup(top) == TYPE_GROUP_MONSTER)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (Duel_IsAmazonessCard(cardId) && cardId != AMAZONESS_SPY
        && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER)
      return (s16)i;
  }

  return -1;
}

static u8 ReturnAmazonessFromGyToHandOrDeck(u8 fixedDuelist)
{
  s16 gyIndex;
  u16 cardId;
  u8 turnDuelist = FixedDuelistToTurnDuelist(fixedDuelist);
  s8 handZone;

  gyIndex = FindAmazonessGyIndexExceptSpy(fixedDuelist);
  if (gyIndex < 0)
    return FALSE;

  if (GraveyardExpand_IsEnabled()) {
    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
  } else {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
  }

  if (cardId == CARD_NONE)
    return FALSE;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone >= 0) {
    InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone),
                         cardId);
    return TRUE;
  }

  /* Hand full: shuffle into Deck. */
  {
    u8 deckSize = NumCardsInDeck(fixedDuelist);

    if (deckSize >= 60)
      return FALSE;
    gDuelDecks[fixedDuelist].cards[deckSize] = cardId;
  }
  return TRUE;
}

void ClearAmazonessSpyPending(void)
{
  gAmazonessSpyPendingController = AMAZONESS_SPY_PENDING_NONE;
}

void ApplyAmazonessSpyBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (sActionData.playerCardId == AMAZONESS_SPY
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    gAmazonessSpyPendingController = DUEL_PLAYER;
    gDeferGraveyardDrawBattleResolve = TRUE;
  } else if (sActionData.opponentCardId == AMAZONESS_SPY
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    gAmazonessSpyPendingController = DUEL_OPPONENT;
    gDeferGraveyardDrawBattleResolve = TRUE;
  } else {
    return;
  }

  if (gUnk2023EA0.unk18 == 0)
    ResolveAmazonessSpyBattleEffect();
}

void ResolveAmazonessSpyBattleEffect(void)
{
  u8 controller;

  if (gAmazonessSpyPendingController == AMAZONESS_SPY_PENDING_NONE)
    return;

  controller = gAmazonessSpyPendingController;
  ClearAmazonessSpyPending();

  if (FindAmazonessGyIndexExceptSpy(controller) < 0)
    return;

  Duel_ShowEffectTextTyped(AMAZONESS_SPY, 3);
  if (IsDuelOver() == TRUE)
    return;

  ReturnAmazonessFromGyToHandOrDeck(controller);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateAMAZONESS_SPY(void)
{
  if (gMonEffect.id != AMAZONESS_SPY)
    return FALSE;

  /* Battle GY recycle is live via ApplyAmazonessSpyBattleEffect. */
  return FALSE;
}

void ActivateAMAZONESS_SPYEffect(void)
{
  Duel_ShowEffectTextTyped(AMAZONESS_SPY, 2);
}

u8 CanSpecialSummonAmazonessSpyFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != AMAZONESS_SPY)
    return FALSE;

  if (!HandHasOtherAmazoness(handZone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonAmazonessSpyFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonAmazonessSpyFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(AMAZONESS_SPY, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonAmazonessSpyFromHand(u8 handZone);
u8 TrySpecialSummonAmazonessSpyFromHand(u8 handZone);
#endif
