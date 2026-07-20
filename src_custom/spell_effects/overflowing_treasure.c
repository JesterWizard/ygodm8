#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

#define OVERFLOWING_TREASURE_ATK_PER_CARD_STAGES 1

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsValidOverflowingTreasureTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 HasOverflowingTreasureTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidOverflowingTreasureTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static void DestroyOverflowingTreasureSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == OVERFLOWING_TREASURE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ApplyOverflowingTreasureBoost(struct DuelCard *zone)
{
  u8 handCards;
  u8 stages;
  u8 i;

  handCards = Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST])
              + Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]);
  stages = (u8)(handCards * OVERFLOWING_TREASURE_ATK_PER_CARD_STAGES);

  for (i = 0; i < stages; i++)
    IncrementTempStage(zone);

  Duel_NotifyMonsterZoneChanged(zone);
  Duel_RefreshMonsterStatOverlays();
}

static void ResolveOverflowingTreasureTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidOverflowingTreasureTarget(fixedRow, fixedCol))
    return;

  ApplyOverflowingTreasureBoost(zone);
  DestroyOverflowingTreasureSpellZone();
}

static void CancelOverflowingTreasureTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyOverflowingTreasureSpellZone();
}

static u8 AiPickOverflowingTreasureTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidOverflowingTreasureTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void OVERFLOWING_TREASURE_ResolveBody(void)
{
  Duel_ShowEffectText(OVERFLOWING_TREASURE);

  if (IsDuelOver() == TRUE || !HasOverflowingTreasureTarget())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidOverflowingTreasureTarget, ResolveOverflowingTreasureTarget,
                     CancelOverflowingTreasureTargeting, AiPickOverflowingTreasureTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectOVERFLOWING_TREASURE(void)
{
  if (!HasOverflowingTreasureTarget()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(OVERFLOWING_TREASURE, OVERFLOWING_TREASURE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
