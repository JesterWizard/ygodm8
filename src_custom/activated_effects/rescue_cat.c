#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsRescueCatDeckTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardHasMonsterType(cardId, TYPE_BEAST))
    return FALSE;

  if (Duel_CardCannotBeSpecialSummoned(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level <= 3;
}

static u8 CountDeckRescueCatTargets(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u8 count = 0;

  for (i = top; i < deckSize; i++) {
    if (IsRescueCatDeckTarget(gDuelDecks[fixedDuelist].cards[i]))
      count++;
  }

  return count;
}

static u16 FindDeckRescueCatTarget(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsRescueCatDeckTarget(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateRESCUE_CAT(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != RESCUE_CAT)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != RESCUE_CAT)
    return FALSE;

  if (!CanUseMonsterEffect(zone) || ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return CountDeckRescueCatTargets() >= 2
      && NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 1;
}

void ActivateRESCUE_CATEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;
  u16 cardId;
  u8 summoned = 0;

  Duel_ShowEffectTextTyped(RESCUE_CAT, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (CountDeckRescueCatTargets() < 2
      || NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 1)
    return;

  MarkMonsterEffectUsed(self);

  if (Duel_DestroyZone(self, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);

  while (summoned < 2) {
    if (ArchlordKristya_IsSpecialSummonLocked()
        || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
      break;

    cardId = FindDeckRescueCatTarget();
    if (cardId == CARD_NONE)
      break;

    if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
      break;

    summoned++;
  }

  /* Ceiling: negated effects + End Phase destroy not applied; upgrade: summon
   * flags + turn-end cleanup gate. */

  UpdateDuelGfxExceptField();
}
