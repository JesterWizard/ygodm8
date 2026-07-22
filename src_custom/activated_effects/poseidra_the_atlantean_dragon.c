#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 fixedDuelist);
void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define POSEIDRA_TRIBUTE_COUNT 3

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
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

static u8 IsWaterTributeMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_WATER
      && gCardInfo.level >= 1 && gCardInfo.level <= 3;
}

static u8 CountWaterTributesOnField(void)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && IsWaterTributeMonster(zone->id))
      count++;
  }

  return count;
}

static u8 PayThreeWaterTributes(void)
{
  u8 col;
  u8 paid = 0;
  u8 fixedDuelist = FixedDuelistForActive();

  for (col = 0; col < MAX_ZONES_IN_ROW && paid < POSEIDRA_TRIBUTE_COUNT; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || !IsWaterTributeMonster(zone->id))
      continue;

    ClearZoneAndSendMonToGraveyard2(zone, fixedDuelist);
    paid++;

    if (IsDuelOver() == TRUE)
      return FALSE;
  }

  return paid >= POSEIDRA_TRIBUTE_COUNT;
}

static s16 FindPoseidraInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == POSEIDRA_THE_ATLANTEAN_DRAGON)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == POSEIDRA_THE_ATLANTEAN_DRAGON)
      return (s16)i;
  }

  return -1;
}

static u8 BounceBackrowToOwnerHand(struct DuelCard *zone, u8 turnDuelist)
{
  s8 empty;
  u16 cardId;
  u8 typeGroup;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  empty = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (empty < 0)
    return FALSE;

  cardId = zone->id;
  ClearZone(zone);
  InitHandSlotFromCard(gTurnHands[turnDuelist][empty], cardId);
  return TRUE;
}

static u8 TurnDuelistForFixedBackrow(u8 fixedRow)
{
  if (fixedRow == PLAYER_BACKROW)
    return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;
}

static u8 BounceAllSpellTrapsOnField(u8 *outReturned)
{
  u8 row;
  u8 col;
  u8 returned = 0;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    u8 turnDuelist = TurnDuelistForFixedBackrow(row);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (BounceBackrowToOwnerHand(zone, turnDuelist))
        returned++;
    }
  }

  *outReturned = returned;
  return TRUE;
}

static void ApplyOpponentAtkPenalty(u8 returnedCount)
{
  u8 col;
  s8 stages;

  if (returnedCount < POSEIDRA_TRIBUTE_COUNT)
    return;

  stages = (s8)(-((s32)returnedCount * 300 + 499) / 500);
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    if (zone->tempStage > -126 + stages)
      zone->tempStage = (s8)(zone->tempStage + stages);
    else
      zone->tempStage = -126;
  }
}

static u8 CanPoseidraSummon(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (CountWaterTributesOnField() < POSEIDRA_TRIBUTE_COUNT)
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

static u8 ResolvePoseidraSummonFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 returned = 0;

  if (!PayThreeWaterTributes())
    return FALSE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  BounceAllSpellTrapsOnField(&returned);
  ApplyOpponentAtkPenalty(returned);
  RefreshFieldMonsterStatOverlays();
  return TRUE;
}

static u8 ResolvePoseidraSummonFromGrave(s16 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;
  u8 returned = 0;

  if (!PayThreeWaterTributes())
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (cardId != POSEIDRA_THE_ATLANTEAN_DRAGON)
      return FALSE;

    if (Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts) != DUEL_ACTION_OK)
      return FALSE;
  } else {
    cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
    if (cardId != POSEIDRA_THE_ATLANTEAN_DRAGON)
      return FALSE;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
      return FALSE;
  }

  BounceAllSpellTrapsOnField(&returned);
  ApplyOpponentAtkPenalty(returned);
  RefreshFieldMonsterStatOverlays();
  return TRUE;
}

u8 CanSpecialSummonPoseidraFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != POSEIDRA_THE_ATLANTEAN_DRAGON)
    return FALSE;

  return CanPoseidraSummon();
}

u8 TrySpecialSummonPoseidraFromHand(u8 handZone)
{
  if (!CanSpecialSummonPoseidraFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(POSEIDRA_THE_ATLANTEAN_DRAGON, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!ResolvePoseidraSummonFromHand(handZone))
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

unsigned char CanActivatePOSEIDRA_THE_ATLANTEAN_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != POSEIDRA_THE_ATLANTEAN_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone != NULL && zone->id == POSEIDRA_THE_ATLANTEAN_DRAGON)
    return FALSE;

  /* hand SS uses FromHand path. Ceiling: GY ignition like Malicious. */
  if (FindPoseidraInGy() < 0)
    return FALSE;

  return CanPoseidraSummon();
}

void ActivatePOSEIDRA_THE_ATLANTEAN_DRAGONEffect(void)
{
  s16 gyIndex;

  Duel_ShowEffectTextTyped(POSEIDRA_THE_ATLANTEAN_DRAGON, 2);

  if (IsDuelOver() == TRUE)
    return;

  gyIndex = FindPoseidraInGy();
  if (gyIndex < 0 || !CanPoseidraSummon())
    return;

  if (!ResolvePoseidraSummonFromGrave(gyIndex))
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

#if !defined(__GNUC__)
u8 CanSpecialSummonPoseidraFromHand(u8 handZone);
u8 TrySpecialSummonPoseidraFromHand(u8 handZone);
#endif
