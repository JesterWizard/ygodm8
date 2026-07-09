#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/card_effect_texts.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "uria_lord_of_searing_flames.h"

void UpdateDuelGfxExceptField(void);
void BlockTurnSummoning(u8);

static u8 IsFaceUpTrapInBackrow(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (!zone->isFaceUp)
    return FALSE;
  return GetTypeGroup(zone->id) == TYPE_GROUP_TRAP;
}

static u8 CountFaceUpTraps(u8 fixedDuelist)
{
  u8 fixedRow = (fixedDuelist == DUEL_PLAYER) ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpTrapInBackrow(gFixedZones[fixedRow][col]))
      count++;
  }
  return count;
}

static void SendFaceUpTrapsToGrave(u8 fixedDuelist)
{
  u8 fixedRow = (fixedDuelist == DUEL_PLAYER) ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 col;
  u8 sent = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW && sent < URIA_COST_TRAPS; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (!IsFaceUpTrapInBackrow(zone))
      continue;
    Duel_DestroyZone(zone, fixedDuelist, FALSE);
    sent++;
  }
}

static u8 GraveyardCardIsTrap(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;
  return GetTypeGroup(cardId) == TYPE_GROUP_TRAP;
}

static u8 CountContinuousTrapsInGraveyard(u8 fixedDuelist)
{
  u8 i;
  u8 count = 0;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    return GraveyardCardIsTrap(cardId) ? 1 : 0;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (GraveyardCardIsTrap(cardId))
      count++;
  }
  return count;
}

static u16 UriaCurrentAtk(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 turnRow;
  u8 col;
  u8 trapCount;

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return 0;

  fixedDuelist = (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
      ? (WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT)
      : (WhoseTurn() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER);

  trapCount = CountContinuousTrapsInGraveyard(fixedDuelist);
  return Duel_ClampStat((u32)trapCount * URIA_ATK_PER_CONTINUOUS_TRAP);
}

u8 UriaLordOfSearingFlames_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != URIA_LORD_OF_SEARING_FLAMES)
    return FALSE;

  Duel_WriteCardInfoStats(zone->id, UriaCurrentAtk(zone),
                          gCardData_NEW[zone->id].def);
  return TRUE;
}

u8 CanSpecialSummonUriaLordOfSearingFlamesFromHand(u8 handZone)
{
  u8 fixedDuelist;
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= MAX_ZONES_IN_ROW)
    return FALSE;

  if (handRow[handZone]->id != URIA_LORD_OF_SEARING_FLAMES)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  fixedDuelist = (WhoseTurn() == DUEL_PLAYER) ? DUEL_PLAYER : DUEL_OPPONENT;
  return CountFaceUpTraps(fixedDuelist) >= URIA_COST_TRAPS;
}

u8 TrySpecialSummonUriaLordOfSearingFlamesFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist;

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;

  if (!CanSpecialSummonUriaLordOfSearingFlamesFromHand(handZone))
    return FALSE;

  fixedDuelist = (WhoseTurn() == DUEL_PLAYER) ? DUEL_PLAYER : DUEL_OPPONENT;
  SendFaceUpTrapsToGrave(fixedDuelist);

  Duel_ShowCardEffectText(URIA_LORD_OF_SEARING_FLAMES,
                          CARD_EFFECT_TEXT_URIA_LORD_OF_SEARING_FLAMES_POPUP_1);

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  BlockTurnSummoning(ACTIVE_DUELIST);
  return TRUE;
}
