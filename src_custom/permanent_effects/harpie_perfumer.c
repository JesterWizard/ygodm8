#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "harpie_perfumer.h"
#include "harpie_channeler.h"
#include "six_card_hand.h"
#include "summon_tribute.h"

void UpdateDuelGfxExceptField(void);

static const char sHarpieName[] APPEND_RODATA = "Harpie";

/* S/T that specifically list "Harpie Lady Sisters" in printed text.
 * Name-substring search is wrong here (no S/T is named that). */
static const u16 sSistersMentionSpellTraps[] APPEND_RODATA = {
  CYBER_SHIELD,
  ELEGANT_EGOTIST,
  HARPIE_LADY_PHOENIX_FORMATION,
  ALLURING_MIRROR_SPLIT,
  HARPIE_LADY_ELEGANCE,
  HARPIES_FEATHER_REST,
  HARPIES_HUNTING_GROUND,
  TRIANGLE_ECSTASY_SPARK,
};

u8 HarpiePerfumer_TreatsNameAsHarpieLady(const struct DuelCard *zone)
{
  if (zone == NULL)
    return FALSE;

  switch (zone->id) {
  case HARPIE_PERFUMER:
  case HARPIE_QUEEN:
  case HARPIE_DANCER:
  case HARPIE_ORACLE:
  case HARPIE_CONDUCTOR:
  case HARPIE_HARPIST:
  case CYBER_SLASH_HARPIE_LADY:
  case CYBER_SLASH_HARPY_LADY:
  case HARPIE_CHANNELER:
    return TRUE;
  default:
    return FALSE;
  }
}

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 sHarpieOracleGyPending APPEND_DATA = {0};
static u8 sHarpieOracleGyOptUsed APPEND_DATA = {0};

u8 Harpie_MentionsHarpieLadySisters(u16 cardId)
{
  u8 i;

  if (cardId == CARD_NONE)
    return FALSE;

  for (i = 0; i < ARRAY_COUNT(sSistersMentionSpellTraps); i++) {
    if (cardId == sSistersMentionSpellTraps[i])
      return TRUE;
  }

  return FALSE;
}

static u8 IsSistersMentionSpellTrap(u16 cardId)
{
  if (GetTypeGroup(cardId) != TYPE_GROUP_SPELL && GetTypeGroup(cardId) != TYPE_GROUP_TRAP)
    return FALSE;

  return Harpie_MentionsHarpieLadySisters(cardId);
}

static u16 FindSistersMentionSpellTrapInDeck(u8 turnDuelist, u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (cardId == excludeId)
      continue;

    if (IsSistersMentionSpellTrap(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 IsHarpieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 ControlsLevel5OrHigherHarpie(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[monsterRow][i];

    if (!MonsterIsFaceUp(zone) || !IsHarpieMonster(zone->id))
      continue;

    SetCardInfo(zone->id);
    if (gCardInfo.level >= 5)
      return TRUE;
  }

  return FALSE;
}

static u8 CanSearchSistersSpellTraps(u8 turnDuelist)
{
  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  return FindSistersMentionSpellTrapInDeck(turnDuelist, CARD_NONE) != CARD_NONE;
}

unsigned char ShouldActivateHARPIE_PERFUMER(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != HARPIE_PERFUMER)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  /* Name=Harpie Lady via HarpiePerfumer_TreatsNameAsHarpieLady + Duel_ZoneEffectCardId. */
  return CanSearchSistersSpellTraps(duelist);
}

void ActivateHARPIE_PERFUMER(void)
{
  u8 duelist;
  struct DuelCard *zone;
  u16 firstId;
  u16 secondId;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(HARPIE_PERFUMER, 8);
  if (IsDuelOver() == TRUE)
    return;

  firstId = FindSistersMentionSpellTrapInDeck(duelist, CARD_NONE);
  if (firstId != CARD_NONE)
    Duel_AddDeckCardToHand(duelist, firstId, TRUE);

  if (ControlsLevel5OrHigherHarpie(duelist)
      && FirstEmptyZoneInRow(gTurnHands[duelist]) >= 0) {
    secondId = FindSistersMentionSpellTrapInDeck(duelist, firstId);
    if (secondId != CARD_NONE)
      Duel_AddDeckCardToHand(duelist, secondId, TRUE);
  }

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone != NULL)
    zone->unk4 = 1;
}

u8 HarpiePerfumer_TryAddSistersSpellTrapFromDeck(u8 turnDuelist)
{
  u16 cardId;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  cardId = FindSistersMentionSpellTrapInDeck(turnDuelist, CARD_NONE);
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_AddDeckCardToHand(turnDuelist, cardId, TRUE) == DUEL_ACTION_OK;
}

static s16 FindSistersMentionSpellTrapGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return -1;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsSistersMentionSpellTrap(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s16)i;
  }

  return -1;
}

static u8 AddSistersMentionSpellTrapFromGyToHand(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s16 gyIndex;
  s8 handZone;
  u16 cardId;
  struct DuelCard *handSlot;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  gyIndex = FindSistersMentionSpellTrapGyIndex(fixedDuelist);
  if (gyIndex < 0)
    return FALSE;

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsSistersMentionSpellTrap(cardId))
    return FALSE;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  handSlot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone);
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
  return TRUE;
}

void HarpieOracle_ArmEndPhasePending(u8 turnDuelist)
{
  u8 optBit = turnDuelist == ACTIVE_DUELIST ? 1 : 2;

  if (sHarpieOracleGyOptUsed & optBit)
    return;

  sHarpieOracleGyOptUsed |= optBit;
  sHarpieOracleGyPending |= optBit;
}

void HarpieOracle_ClearOnTurnBoundary(void)
{
  sHarpieOracleGyPending = 0;
  sHarpieOracleGyOptUsed = 0;
}

void TryApplyHarpieOracleEndPhase(void)
{
  u8 turnDuelist;

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    u8 pendingBit = turnDuelist == ACTIVE_DUELIST ? 1 : 2;
    u8 monsterRow = turnDuelist == ACTIVE_DUELIST
        ? ACTIVE_DUELIST_MONSTER_ROW
        : INACTIVE_DUELIST_MONSTER_ROW;
    u8 col;
    u8 hasOracle = FALSE;

    if ((sHarpieOracleGyPending & pendingBit) == 0)
      continue;

    sHarpieOracleGyPending &= (u8)~pendingBit;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[monsterRow][col];

      if (zone != NULL && zone->id == HARPIE_ORACLE && MonsterIsFaceUp(zone))
        hasOracle = TRUE;
    }

    if (!hasOracle)
      continue;

    if (AddSistersMentionSpellTrapFromGyToHand(turnDuelist)) {
      Duel_ShowEffectTextTyped(HARPIE_ORACLE, 8);
      UpdateDuelGfxExceptField();
    }
  }
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void HARPIE_PERFUMER_SelfCheck(void)
{
  if (!Harpie_MentionsHarpieLadySisters(ELEGANT_EGOTIST))
    while (1)
      ;
  if (!Harpie_MentionsHarpieLadySisters(HARPIES_HUNTING_GROUND))
    while (1)
      ;
  if (Harpie_MentionsHarpieLadySisters(HARPIE_LADY_SISTERS))
    while (1)
      ;
  if (Harpie_MentionsHarpieLadySisters(HARPIE_PERFUMER))
    while (1)
      ;
}
#endif

