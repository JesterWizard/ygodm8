#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sTheAgentName[] APPEND_RODATA = "The Agent";
static const char sSanctuaryName[] APPEND_RODATA = "Sanctuary in the Sky";

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

  return Duel_CardNameContains(cardId, sTheAgentName);
}

static u8 IsSanctuaryMention(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (cardId == THE_SANCTUARY_IN_THE_SKY)
    return TRUE;

  return Duel_CardNameContains(cardId, sSanctuaryName);
}

static u8 IsMillTarget(u16 cardId)
{
  return IsTheAgentMonster(cardId) || IsSanctuaryMention(cardId);
}

static u16 FindMillTargetInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsMillTarget(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 MillCardFromDeck(u16 cardId)
{
  s16 deckIndex;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
  return TRUE;
}

static u8 IsFairyMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_FAIRY);
}

static u8 HasFairyHandOrGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (IsFairyMonster(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id))
      return TRUE;
  }

  if (!GraveyardExpand_IsEnabled())
    return IsFairyMonster(gDuel.duelistbattleState[fixedDuelist].graveyard);

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsFairyMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 BanishOneFairyHandOrGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (IsFairyMonster(slot->id)) {
      if (Duel_BanishZone(slot, TRUE) == DUEL_ACTION_DUEL_OVER)
        return FALSE;
      return TRUE;
    }
  }

  if (!GraveyardExpand_IsEnabled()) {
    if (IsFairyMonster(gDuel.duelistbattleState[fixedDuelist].graveyard)) {
      Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
      return TRUE;
    }
    return FALSE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsFairyMonster(GraveyardExpand_GetCardAt(fixedDuelist, i))) {
      u16 cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);

      GraveyardExpand_SyncLegacyTop(fixedDuelist);
      RemovedFromPlay_PushFixed(fixedDuelist, cardId);
      return TRUE;
    }
  }

  return FALSE;
}

static u8 IsDestroyableOppCard(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != INACTIVE_DUELIST_MONSTER_ROW && fixedRow != INACTIVE_DUELIST_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 OppHasDestroyableCard(void)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsDestroyableOppCard(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsDestroyableOppCard(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (!BanishOneFairyHandOrGy())
    return;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsDestroyableOppCard(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateMASTERFLARE_HYPERION(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MASTERFLARE_HYPERION)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MASTERFLARE_HYPERION)
    return FALSE;

  /* name/effect copy + Quick negate FALSE.
   * OPT mill Agent/Sanctuary-mention, else OPT banish Fairy → destroy 1. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FindMillTargetInDeck() != CARD_NONE)
    return TRUE;

  return HasFairyHandOrGy() && OppHasDestroyableCard();
}

void ActivateMASTERFLARE_HYPERIONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 millId;

  Duel_ShowEffectTextTyped(MASTERFLARE_HYPERION, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  millId = FindMillTargetInDeck();
  if (millId != CARD_NONE) {
    if (!MillCardFromDeck(millId))
      return;

    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  if (!HasFairyHandOrGy() || !OppHasDestroyableCard())
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;
  Duel_SetupPickZone(IsDestroyableOppCard, ResolveDestroyTarget, CancelTargeting,
                     AiPickDestroyTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
