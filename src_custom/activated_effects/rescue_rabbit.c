#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
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

static u8 IsRescueRabbitDeckTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color != COLOR_NORMAL)
    return FALSE;

  if (gCardInfo.level > 4)
    return FALSE;

  if (Duel_CardCannotBeSpecialSummoned(cardId))
    return FALSE;

  return TRUE;
}

static u16 FindDeckNormalPairName(u8 *pairCountOut)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u8 j;
  u16 bestId = CARD_NONE;
  u8 bestCount = 0;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];
    u8 count = 0;

    if (!IsRescueRabbitDeckTarget(cardId))
      continue;

    for (j = top; j < deckSize; j++) {
      if (gDuelDecks[fixedDuelist].cards[j] == cardId
          && IsRescueRabbitDeckTarget(gDuelDecks[fixedDuelist].cards[j]))
        count++;
    }

    if (count >= 2 && count > bestCount) {
      bestId = cardId;
      bestCount = count;
    }
  }

  *pairCountOut = bestCount >= 2 ? 2 : 0;
  return bestId;
}

unsigned char CanActivateRESCUE_RABBIT(void)
{
  struct DuelCard *zone;
  u8 pairCount;

  if (gMonEffect.id != RESCUE_RABBIT)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != RESCUE_RABBIT)
    return FALSE;

  if (!CanUseMonsterEffect(zone) || ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FindDeckNormalPairName(&pairCount) == CARD_NONE || pairCount < 2)
    return FALSE;

  return NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 1;
}

void ActivateRESCUE_RABBITEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;
  u16 cardId;
  u8 pairCount;
  u8 summoned = 0;

  Duel_ShowEffectTextTyped(RESCUE_RABBIT, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindDeckNormalPairName(&pairCount);
  if (cardId == CARD_NONE || pairCount < 2
      || NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 1)
    return;

  MarkMonsterEffectUsed(self);

  if (Duel_BanishZone(self, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);

  while (summoned < 2) {
    if (ArchlordKristya_IsSpecialSummonLocked()
        || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
      break;

    if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
      break;

    summoned++;
  }

  /* Ceiling: End Phase destroy + effect negate not applied; upgrade: turn-end gate. */

  UpdateDuelGfxExceptField();
}
