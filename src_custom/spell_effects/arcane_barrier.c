#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define ARCANE_BARRIER_MAX_COUNTERS 4

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
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

static u8 IsFaceUpSpellcaster(struct DuelCard *zone)
{
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  if (!MonsterIsFaceUp(zone))
    return FALSE;

  return Duel_CardHasMonsterType(zone->id, TYPE_SPELLCASTER);
}

static u8 IsValidArcaneBarrierCostTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  return IsFaceUpSpellcaster(gFixedZones[fixedRow][fixedCol]);
}

static u8 HasArcaneBarrierCostTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidArcaneBarrierCostTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

static u8 CanArcaneBarrierIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ARCANE_BARRIER || zone->isFaceUp == FALSE)
    return FALSE;

  /* unk4 = Spell Counter count (placed by destroy hook when wired). */
  if (zone->unk4 == 0)
    return FALSE;

  return HasArcaneBarrierCostTarget();
}

static void ResolveArcaneBarrierCostTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *monster = gFixedZones[fixedRow][fixedCol];
  u8 counters;

  if (!IsValidArcaneBarrierCostTarget(fixedRow, fixedCol))
    return;

  if (spellZone == NULL || spellZone->id != ARCANE_BARRIER)
    return;

  counters = spellZone->unk4;
  if (counters == 0)
    return;

  if (counters > ARCANE_BARRIER_MAX_COUNTERS)
    counters = ARCANE_BARRIER_MAX_COUNTERS;

  spellZone->unk4 = 0;

  Duel_DestroyZone(monster, ACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  Duel_DrawCards(ACTIVE_DUELIST, counters, TRUE);
}

static void CancelArcaneBarrierCostTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickArcaneBarrierCostTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidArcaneBarrierCostTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ResolveArcaneBarrierIgnition(struct DuelCard *zone)
{
  if (!CanArcaneBarrierIgnition(zone))
    return;

  Duel_ShowEffectText(ARCANE_BARRIER);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidArcaneBarrierCostTarget, ResolveArcaneBarrierCostTarget,
                     CancelArcaneBarrierCostTargeting, AiPickArcaneBarrierCostTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

static void ARCANE_BARRIER_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation: send this + 1 face-up Spellcaster; draw = Spell Counters. */
  if (zone != NULL && zone->isLocked) {
    if (!CanArcaneBarrierIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveArcaneBarrierIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  if (zone != NULL)
    zone->unk4 = 0;

  Duel_ShowEffectText(ARCANE_BARRIER);

  /* ponytail: Spell Counters when a face-up Spellcaster is destroyed need a
   * destroy / leave-field hook outside this file (no in-file destroy dispatch).
   * Ceiling: continuous face-up + ignition when unk4>0 (never rises alone);
   * upgrade: on face-up Spellcaster destroy → if face-up ARCANE_BARRIER then
   * zone->unk4++ (cap ARCANE_BARRIER_MAX_COUNTERS). */

  /* ponytail: not in GetSpellType NORMAL override — face-up re-activation may
   * need card_hooks GetSpellType + ARCANE_BARRIER listed (same as SHARD_OF_GREED /
   * CALL_OF_THE_MUMMY). */
}

APPEND_TEXT void EffectARCANE_BARRIER(void)
{
  if (Duel_TryResolveSpellThroughTraps(ARCANE_BARRIER, ARCANE_BARRIER_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ARCANE_BARRIER_SelfCheck(void)
{
  if (!Duel_CardHasMonsterType(DARK_MAGICIAN, TYPE_SPELLCASTER))
    while (1)
      ;
  if (Duel_CardHasMonsterType(BLUE_EYES_WHITE_DRAGON, TYPE_SPELLCASTER))
    while (1)
      ;
  if (ARCANE_BARRIER_MAX_COUNTERS != 4)
    while (1)
      ;
}
#endif
