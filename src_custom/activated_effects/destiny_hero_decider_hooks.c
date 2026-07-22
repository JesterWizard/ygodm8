#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "destiny_hero_decider.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"

u8 GetDuelistForZone(struct DuelCard *zone);

static const char sHeroName[] APPEND_RODATA = "HERO";
static u8 sDeciderEpPending APPEND_DATA = {0};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == DESTINY_HERO_DECIDER)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (Duel_IsElementalHeroCard(cardId))
    return TRUE;

  return Duel_CardNameContains(cardId, sHeroName);
}

static s16 FindHeroGyIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsHeroMonster(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 0;

    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsHeroMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s16)i;
  }

  return -1;
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

static u8 AddHeroFromGyToHand(u8 turnDuelist, s16 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    if (!IsHeroMonster(cardId))
      return FALSE;

    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
    InitHandSlotFromCard(
        SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
    return TRUE;
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsHeroMonster(cardId))
    return FALSE;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  InitHandSlotFromCard(
      SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
  return TRUE;
}

void TryDestinyHeroDeciderOnMonsterPlacement(struct DuelCard *zone)
{
  u8 fixedDuelist;

  if (zone == NULL || zone->id != DESTINY_HERO_DECIDER)
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist == DUEL_PLAYER)
    sDeciderEpPending |= 1;
  else if (fixedDuelist == DUEL_OPPONENT)
    sDeciderEpPending |= 2;
}

void TryApplyDestinyHeroDeciderEndPhase(void)
{
  u8 fixed = WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
  u8 bit = fixed == DUEL_PLAYER ? 1 : 2;
  u8 turnDuelist;
  u8 row;
  u8 col;
  s16 gyIndex;

  if ((sDeciderEpPending & bit) == 0)
    return;

  turnDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixed]
      ? ACTIVE_DUELIST
      : INACTIVE_DUELIST;
  row = Duel_FixedMonsterRowForDuelist(fixed);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == DESTINY_HERO_DECIDER) {
      gyIndex = FindHeroGyIndex(turnDuelist);
      if (gyIndex < 0)
        return;

      if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
        return;

      sDeciderEpPending &= (u8)~bit;
      Duel_ShowEffectTextTyped(DESTINY_HERO_DECIDER, 9);
      AddHeroFromGyToHand(turnDuelist, gyIndex);
      return;
    }
  }
}
