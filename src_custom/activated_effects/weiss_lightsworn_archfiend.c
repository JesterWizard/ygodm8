#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"
#include "weiss_lightsworn_archfiend.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);
void RefreshFieldMonsterStatOverlays(void);

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

#define WEISS_MILL_COUNT 2

static u8 sWeissMillReentry APPEND_DATA = 0;

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 FixedDuelistForTurn(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
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

static s16 FindLightswornGyIndexFor(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

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

static enum DuelActionResult SpecialSummonLightswornFromGyFor(u8 turnDuelist, s16 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForTurn(turnDuelist);
  u16 cardId;

  if (gyIndex < 0)
    return DUEL_ACTION_NO_TARGET;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[turnDuelist]->graveyard;
    if (!IsLightswornMonsterExceptWeiss(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(turnDuelist, CARD_NONE, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsLightswornMonsterExceptWeiss(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
}

static u8 DeckCanMillWeissCount(void)
{
  u8 fixedDuelist = FixedDuelistForActive();

  return gDuelDecks[fixedDuelist].cardsDrawn + WEISS_MILL_COUNT <= NumCardsInDeck(fixedDuelist);
}

void TryApplyWeissAfterDeckMill(u8 turnDuelist, u16 cardId)
{
  u8 fixedDuelist;
  u8 monsterRow;
  s16 gyIndex;

  if (sWeissMillReentry || cardId != WEISS_LIGHTSWORN_ARCHFIEND || IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(WEISS_LIGHTSWORN_ARCHFIEND))
    return;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;

  monsterRow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                             : INACTIVE_DUELIST_MONSTER_ROW;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;

  fixedDuelist = FixedDuelistForTurn(turnDuelist);
  gyIndex = FindLightswornGyIndexFor(fixedDuelist);
  if (gyIndex < 0)
    return;

  sWeissMillReentry = TRUE;
  Duel_ShowEffectTextTyped(WEISS_LIGHTSWORN_ARCHFIEND, 8);
  if (SpecialSummonLightswornFromGyFor(turnDuelist, gyIndex) == DUEL_ACTION_OK) {
    EffectOpt_MarkUsed(WEISS_LIGHTSWORN_ARCHFIEND);
    RefreshFieldMonsterStatOverlays();
  }
  sWeissMillReentry = FALSE;
}

unsigned char CanActivateWEISS_LIGHTSWORN_ARCHFIEND(void)
{
  if (gMonEffect.id != WEISS_LIGHTSWORN_ARCHFIEND)
    return FALSE;

  /* Deck-mill GY SS via TryApplyWeissAfterDeckMill; hand SS via FromHand. */
  return FALSE;
}

void ActivateWEISS_LIGHTSWORN_ARCHFIENDEffect(void)
{
  Duel_ShowEffectTextTyped(WEISS_LIGHTSWORN_ARCHFIEND, 2);
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
