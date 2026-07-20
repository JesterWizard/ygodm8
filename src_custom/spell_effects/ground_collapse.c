#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

/* First empty-zone pick stashed in gSpellEffectData.row2/col2. */

static u8 IsEmptyMainMonsterZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != PLAYER_MONSTER_ROW && fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id == CARD_NONE;
}

static u8 CountEmptyMainMonsterZones(void)
{
  u8 row;
  u8 col;
  u8 count = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsEmptyMainMonsterZone(row, col))
        count++;
    }
  }

  return count;
}

static u8 IsValidCollapseZone(u8 fixedRow, u8 fixedCol)
{
  if (!IsEmptyMainMonsterZone(fixedRow, fixedCol))
    return FALSE;

  /* Second pick: exclude the first selection. */
  if (gSpellEffectData.row2 != 0xFF
      && fixedRow == gSpellEffectData.row2
      && fixedCol == gSpellEffectData.col2)
    return FALSE;

  return TRUE;
}

static u8 HasTwoEmptyMainMonsterZones(void)
{
  return CountEmptyMainMonsterZones() >= 2;
}

u8 CanActivateGROUND_COLLAPSE(void)
{
  return HasTwoEmptyMainMonsterZones();
}

static void FinishGroundCollapse(u8 row2, u8 col2)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *zone1;
  struct DuelCard *zone2;

  if (spellZone == NULL || spellZone->id != GROUND_COLLAPSE)
    return;

  zone1 = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];
  zone2 = gFixedZones[row2][col2];

  /* Best-effort mark: empty-zone isLocked is not honored by FirstEmptyZoneInRow. */
  if (zone1 != NULL && zone1->id == CARD_NONE)
    zone1->isLocked = TRUE;
  if (zone2 != NULL && zone2->id == CARD_NONE)
    zone2->isLocked = TRUE;

  /* Stash selected cols on the continuous spell for a future lock hook. */
  spellZone->unk4 = (u8)(((gSpellEffectData.row2 & 3) << 4) | (gSpellEffectData.col2 & 0xF));
  spellZone->permStage = (s8)(((row2 & 3) << 4) | (col2 & 0xF));

  Duel_ActivateContinuousZone(spellZone);

  /* ponytail: continuous zone lock needs FirstEmptyZoneInRow / PlaceMonster /
   * summon-set validators outside this file (empty isLocked is ignored).
   * Ceiling: face-up continuous + marks/stash only; upgrade: LynJump
   * FirstEmptyZoneInRow (+ AI/player summon cursors) → skip isLocked empty
   * MMZ while face-up GROUND_COLLAPSE; clear marks when it leaves the field. */
}

static void CancelGroundCollapseTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == GROUND_COLLAPSE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static u8 AiPickCollapseZone(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidCollapseZone(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void ResolveSecondCollapseZone(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidCollapseZone(fixedRow, fixedCol))
    return;

  FinishGroundCollapse(fixedRow, fixedCol);
}

static void BeginSecondCollapsePick(void)
{
  Duel_SetupPickZone(IsValidCollapseZone, ResolveSecondCollapseZone,
                     CancelGroundCollapseTargeting, AiPickCollapseZone);
  Duel_EnterPickZoneTargeting();
}

static void ResolveFirstCollapseZone(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidCollapseZone(fixedRow, fixedCol))
    return;

  gSpellEffectData.row2 = fixedRow;
  gSpellEffectData.col2 = fixedCol;
  BeginSecondCollapsePick();
}

static void ResolveGroundCollapseForAi(void)
{
  u8 row1;
  u8 col1;
  u8 row2;
  u8 col2;

  gSpellEffectData.row2 = 0xFF;
  gSpellEffectData.col2 = 0xFF;

  if (!AiPickCollapseZone(&row1, &col1)) {
    CancelGroundCollapseTargeting();
    return;
  }

  gSpellEffectData.row2 = row1;
  gSpellEffectData.col2 = col1;

  if (!AiPickCollapseZone(&row2, &col2)) {
    CancelGroundCollapseTargeting();
    return;
  }

  FinishGroundCollapse(row2, col2);
}

static void GROUND_COLLAPSE_ResolveBody(void)
{
  Duel_ShowEffectText(GROUND_COLLAPSE);

  if (IsDuelOver() == TRUE || !CanActivateGROUND_COLLAPSE())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;
  gSpellEffectData.row2 = 0xFF;
  gSpellEffectData.col2 = 0xFF;

  if (WhoseTurn() != DUEL_PLAYER) {
    ResolveGroundCollapseForAi();
    return;
  }

  Duel_SetupPickZone(IsValidCollapseZone, ResolveFirstCollapseZone,
                     CancelGroundCollapseTargeting, AiPickCollapseZone);
  Duel_EnterPickZoneTargeting();
}

APPEND_TEXT void EffectGROUND_COLLAPSE(void)
{
  if (!CanActivateGROUND_COLLAPSE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(GROUND_COLLAPSE, GROUND_COLLAPSE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void GROUND_COLLAPSE_SelfCheck(void)
{
  if (MAX_ZONES_IN_ROW < 2)
    while (1)
      ;
}
#endif
