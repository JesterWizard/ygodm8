#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsLevel5PlusMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].level >= 5;
}

static s16 FindLevelEaterInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == LEVEL_EATER)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == LEVEL_EATER)
      return (s16)i;
  }

  return -1;
}

static u8 IsOwnMonsterZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  u8 turnRow;
  u8 turnCol;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &turnCol))
    return FALSE;

  return turnRow == ACTIVE_DUELIST_MONSTER_ROW;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != PLAYER_MONSTER_ROW && fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  if (!IsOwnMonsterZone(fixedRow, fixedCol))
    return FALSE;

  return IsLevel5PlusMonster(zone->id);
}

static u8 OwnFieldHasTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && IsLevel5PlusMonster(zone->id))
      return TRUE;
  }

  return FALSE;
}

static enum DuelActionResult SpecialSummonLevelEaterFromGy(s16 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != LEVEL_EATER)
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, LEVEL_EATER, opts);
  }

  if (gyIndex < 0)
    return DUEL_ACTION_NO_TARGET;

  if (GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex) != LEVEL_EATER)
    return DUEL_ACTION_NO_TARGET;

  GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, LEVEL_EATER, opts);
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  s16 gyIndex;

  (void)fixedRow;
  (void)fixedCol;

  /* no zone Level-mod field (level is ROM-only via gCardData_NEW).
   * SS self from GY; upgrade: TempLevel overlay on target. */

  if (IsDuelOver() == TRUE)
    return;

  gyIndex = FindLevelEaterInGy();
  if (gyIndex < 0)
    return;

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  if (SpecialSummonLevelEaterFromGy(gyIndex) != DUEL_ACTION_OK)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    u8 fixedRow;
    u8 fixedCol;

    if (zone == NULL || !IsLevel5PlusMonster(zone->id))
      continue;

    if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
      continue;

    *outRow = fixedRow;
    *outCol = fixedCol;
    return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateLEVEL_EATER(void)
{
  if (gMonEffect.id != LEVEL_EATER)
    return FALSE;

  /* no zone Level-mod field (level is ROM-only via gCardData_NEW).
   * SS self from GY; upgrade: TempLevel overlay on target. */
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FindLevelEaterInGy() < 0)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return OwnFieldHasTarget();
}

void ActivateLEVEL_EATEREffect(void)
{
  Duel_ShowEffectTextTyped(LEVEL_EATER, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = PLAYER_HAND;
  gDuelCursor.destX = 0;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargetingFromRow(PLAYER_HAND);
  else
    Duel_ResolvePickZoneForAi();
}

u8 CanActivateLevelEaterGy(u8 fixedDuelist, u8 gyIndex)
{
  u16 savedId;
  u8 ok;

  if (!GraveyardExpand_IsEnabled())
    return FALSE;
  if (EffectOpt_IsUsed(LEVEL_EATER))
    return FALSE;
  if (gyIndex >= GraveyardExpand_GetCount(fixedDuelist))
    return FALSE;
  if (GraveyardExpand_GetCardAt(fixedDuelist, gyIndex) != LEVEL_EATER)
    return FALSE;

  savedId = gMonEffect.id;
  gMonEffect.id = LEVEL_EATER;
  ok = CanActivateLEVEL_EATER();
  gMonEffect.id = savedId;
  return ok;
}

void ActivateLevelEaterGy(u8 fixedDuelist, u8 gyIndex)
{
  if (!CanActivateLevelEaterGy(fixedDuelist, gyIndex))
    return;

  EffectOpt_MarkUsed(LEVEL_EATER);
  gMonEffect.id = LEVEL_EATER;
  ActivateLEVEL_EATEREffect();
}
