#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

#define WEISS_MILL_COUNT 2

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsLightswornCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

static u8 IsOtherLightswornCard(u16 cardId)
{
  return IsLightswornCard(cardId) && cardId != WEISS_LIGHTSWORN_ARCHFIEND;
}

static u8 IsLightswornMonsterExceptWeiss(u16 cardId)
{
  if (!IsOtherLightswornCard(cardId) || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return !Duel_CardCannotBeSpecialSummoned(cardId);
}

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 HandHasOtherLightsworn(u8 exceptHandZone)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (col == exceptHandZone)
      continue;

    if (IsOtherLightswornCard(gTurnHands[ACTIVE_DUELIST][col]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 PutOtherLightswornFromHandOnDeckTop(u8 weissHandZone)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *handSlot;
    u16 cardId;

    if (col == weissHandZone)
      continue;

    handSlot = gTurnHands[ACTIVE_DUELIST][col];
    cardId = handSlot->id;
    if (!IsOtherLightswornCard(cardId))
      continue;

    ClearZone(handSlot);
    ReturnCardToDeckTop(fixedDuelist, cardId);
    return TRUE;
  }

  return FALSE;
}

static s16 FindLightswornGyIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    if (IsLightswornMonsterExceptWeiss(cardId))
      return 0;

    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsLightswornMonsterExceptWeiss(cardId))
      return (s16)i;
  }

  return -1;
}

static enum DuelActionResult SpecialSummonLightswornFromGy(s16 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;

  if (gyIndex < 0)
    return DUEL_ACTION_NO_TARGET;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsLightswornMonsterExceptWeiss(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsLightswornMonsterExceptWeiss(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

static u8 DeckCanMillWeissCount(void)
{
  u8 fixedDuelist = FixedDuelistForActive();

  return gDuelDecks[fixedDuelist].cardsDrawn + WEISS_MILL_COUNT <= NumCardsInDeck(fixedDuelist);
}

unsigned char CanActivateWEISS_LIGHTSWORN_ARCHFIEND(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != WEISS_LIGHTSWORN_ARCHFIEND)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != WEISS_LIGHTSWORN_ARCHFIEND)
    return FALSE;

  /* sent-from-Deck-to-GY trigger needs mill/send hook. Ceiling: field OPT
   * SS 1 other Lightsworn from GY. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindLightswornGyIndex() >= 0;
}

void ActivateWEISS_LIGHTSWORN_ARCHFIENDEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s16 gyIndex;

  Duel_ShowEffectTextTyped(WEISS_LIGHTSWORN_ARCHFIEND, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  gyIndex = FindLightswornGyIndex();
  if (gyIndex < 0 || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  if (SpecialSummonLightswornFromGy(gyIndex) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanActivateWeissLightswornArchfiendFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != WEISS_LIGHTSWORN_ARCHFIEND)
    return FALSE;

  if (!HandHasOtherLightsworn(handZone))
    return FALSE;

  if (!DeckCanMillWeissCount())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TryActivateWeissLightswornArchfiendFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanActivateWeissLightswornArchfiendFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(WEISS_LIGHTSWORN_ARCHFIEND, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!PutOtherLightswornFromHandOnDeckTop(handZone))
    return FALSE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_MillTopDeckCards(ACTIVE_DUELIST, WEISS_MILL_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanActivateWeissLightswornArchfiendFromHand(u8 handZone);
u8 TryActivateWeissLightswornArchfiendFromHand(u8 handZone);
#endif
