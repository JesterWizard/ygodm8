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

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

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

static u8 GyHasLightsworn(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsLightswornCard(cardId);
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsLightswornCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u16 FindDeckLightswornExceptSelf(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsLightswornCard(cardId) && cardId != LIGHTSWORN_DRAGONLING)
      return cardId;
  }

  return CARD_NONE;
}

static u8 SendDeckLightswornToGy(u16 cardId)
{
  s16 deckIndex;
  u8 fixedDuelist = FixedDuelistForActive();

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  GraveyardExpand_PushFixed(fixedDuelist, cardId);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return TRUE;
}

u8 CanSpecialSummonLightswornDragonlingFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 fixedDuelist = FixedDuelistForActive();

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != LIGHTSWORN_DRAGONLING)
    return FALSE;

  if (!GyHasLightsworn(fixedDuelist))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonLightswornDragonlingFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonLightswornDragonlingFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(LIGHTSWORN_DRAGONLING, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

unsigned char CanActivateLIGHTSWORN_DRAGONLING(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != LIGHTSWORN_DRAGONLING)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != LIGHTSWORN_DRAGONLING)
    return FALSE;

  /* ponytail: hand SS when Lightsworn in GY uses FromHand path. Ceiling: field
   * OPT send 1 other Lightsworn from Deck to GY. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FindDeckLightswornExceptSelf() != CARD_NONE;
}

void ActivateLIGHTSWORN_DRAGONLINGEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(LIGHTSWORN_DRAGONLING, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindDeckLightswornExceptSelf();
  if (cardId == CARD_NONE)
    return;

  if (!SendDeckLightswornToGy(cardId))
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

#if !defined(__GNUC__)
u8 CanSpecialSummonLightswornDragonlingFromHand(u8 handZone);
u8 TrySpecialSummonLightswornDragonlingFromHand(u8 handZone);
#endif
