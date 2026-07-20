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

static const char sHarpieName[] APPEND_RODATA = "Harpie";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsHarpieCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 IsHarpieMonster(u16 cardId)
{
  if (!IsHarpieCard(cardId) || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return TRUE;
}

static u8 ControlsLevel5PlusHarpie(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    u16 cardId;

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    cardId = zone->id;
    if (!IsHarpieMonster(cardId))
      continue;

    if (cardId < NUM_TOTAL_CARDS && gCardData_NEW[cardId].level >= 5)
      return TRUE;
  }

  return FALSE;
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

static s16 FindHarpieGyIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return -1;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsHarpieCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s16)i;
  }

  return -1;
}

static u8 AddHarpieFromGyToHand(s16 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForActive();
  s8 handZone;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0 || !GraveyardExpand_IsEnabled())
    return FALSE;

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsHarpieCard(cardId))
    return FALSE;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  InitHandSlotFromCard(
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), cardId);
  return TRUE;
}

unsigned char CanActivateHARPIE_ORACLE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != HARPIE_ORACLE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != HARPIE_ORACLE)
    return FALSE;

  /* ponytail: name becomes Harpie Lady + End Phase Sisters S/T add need name/EP hooks.
   * Ceiling: OPT add 1 Harpie from GY to hand. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindHarpieGyIndex() >= 0;
}

void ActivateHARPIE_ORACLEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s16 gyIndex;

  Duel_ShowEffectTextTyped(HARPIE_ORACLE, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  gyIndex = FindHarpieGyIndex();
  if (gyIndex < 0)
    return;

  if (!AddHarpieFromGyToHand(gyIndex))
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonHarpieOracleFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != HARPIE_ORACLE)
    return FALSE;

  if (!ControlsLevel5PlusHarpie())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonHarpieOracleFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonHarpieOracleFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(HARPIE_ORACLE, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonHarpieOracleFromHand(u8 handZone);
u8 TrySpecialSummonHarpieOracleFromHand(u8 handZone);
#endif
