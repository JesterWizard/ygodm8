#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern u16 gRemovedFromPlay[2][REMOVED_FROM_PLAY_CAPACITY];

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

#define PUNISHMENT_DRAGON_HAND_COST 4
#define PUNISHMENT_DRAGON_LP_COST 1000

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

static u8 CountDistinctBanishedLightswornNames(u8 fixedDuelist)
{
  u16 seen[PUNISHMENT_DRAGON_HAND_COST];
  u8 distinct = 0;
  u8 i;
  u8 j;

  if (!RemovedFromPlay_IsEnabled())
    return 0;

  for (i = 0; i < RemovedFromPlay_GetCount(fixedDuelist); i++) {
    u16 cardId = RemovedFromPlay_GetCardAt(fixedDuelist, i);
    u8 already = FALSE;

    if (!IsLightswornMonster(cardId))
      continue;

    for (j = 0; j < distinct; j++) {
      if (seen[j] == cardId) {
        already = TRUE;
        break;
      }
    }

    if (already)
      continue;

    if (distinct >= PUNISHMENT_DRAGON_HAND_COST)
      break;

    seen[distinct++] = cardId;
  }

  return distinct;
}

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 ShuffleAllBanishedIntoDecks(void)
{
  u8 fixedDuelist;
  u8 total = 0;

  if (!RemovedFromPlay_IsEnabled())
    return FALSE;

  for (fixedDuelist = DUEL_PLAYER; fixedDuelist <= DUEL_OPPONENT; fixedDuelist++) {
    u8 count = RemovedFromPlay_GetCount(fixedDuelist);
    u8 i;

    for (i = 0; i < count; i++) {
      u16 cardId = RemovedFromPlay_GetCardAt(fixedDuelist, i);

      if (cardId == CARD_NONE)
        continue;

      ReturnCardToDeckTop(fixedDuelist, cardId);
      total++;
    }

    for (i = 0; i < REMOVED_FROM_PLAY_CAPACITY; i++)
      gRemovedFromPlay[fixedDuelist][i] = CARD_NONE;
  }

  if (total == 0)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  Duel_ShuffleDeckFromDrawn(INACTIVE_DUELIST);
  return TRUE;
}

static u8 CanPayPunishmentCost(void)
{
  return gDuelLifePoints[FixedDuelistForActive()] >= PUNISHMENT_DRAGON_LP_COST;
}

static u8 AnyBanishedCards(void)
{
  u8 fixedDuelist;

  if (!RemovedFromPlay_IsEnabled())
    return FALSE;

  for (fixedDuelist = DUEL_PLAYER; fixedDuelist <= DUEL_OPPONENT; fixedDuelist++) {
    if (RemovedFromPlay_GetCount(fixedDuelist) > 0)
      return TRUE;
  }

  return FALSE;
}

u8 CanSpecialSummonPunishmentDragonFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 fixedDuelist = FixedDuelistForActive();

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != PUNISHMENT_DRAGON)
    return FALSE;

  if (!RemovedFromPlay_IsEnabled())
    return FALSE;

  if (CountDistinctBanishedLightswornNames(fixedDuelist) < PUNISHMENT_DRAGON_HAND_COST)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonPunishmentDragonFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonPunishmentDragonFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(PUNISHMENT_DRAGON, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

unsigned char CanActivatePUNISHMENT_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != PUNISHMENT_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != PUNISHMENT_DRAGON)
    return FALSE;

  /* Hand SS via 4+ banished LS uses FromHand path. OPT pay 1000 → shuffle all
   * banished into Decks (EffectOpt). LS mill 4 needs effect-activation hook. */
  if (EffectOpt_IsUsed(PUNISHMENT_DRAGON))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanPayPunishmentCost() && AnyBanishedCards();
}

void ActivatePUNISHMENT_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(PUNISHMENT_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(PUNISHMENT_DRAGON))
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)PUNISHMENT_DRAGON_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (!ShuffleAllBanishedIntoDecks())
    return;

  EffectOpt_MarkUsed(PUNISHMENT_DRAGON);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

#if !defined(__GNUC__)
u8 CanSpecialSummonPunishmentDragonFromHand(u8 handZone);
u8 TrySpecialSummonPunishmentDragonFromHand(u8 handZone);
#endif
