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

u8 GroundCollapse_IsMainMonsterZoneLocked(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone;
  u8 firstPick;
  u8 secondPick;

  if ((fixedRow != PLAYER_MONSTER_ROW && fixedRow != OPPONENT_MONSTER_ROW)
      || fixedCol >= MAX_ZONES_IN_ROW)
    return FALSE;

  spellZone = Duel_FindBackrowCardOnField(GROUND_COLLAPSE, TRUE);
  if (spellZone == NULL)
    return FALSE;

  firstPick = spellZone->unk4;
  secondPick = (u8)spellZone->permStage;
  return (((firstPick >> 4) & 3) == fixedRow && (firstPick & 0xF) == fixedCol)
      || (((secondPick >> 4) & 3) == fixedRow && (secondPick & 0xF) == fixedCol);
}

static void FinishGroundCollapse(u8 row2, u8 col2)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone == NULL || spellZone->id != GROUND_COLLAPSE)
    return;

  /* Parent summon/placement hooks query these selected main monster zones. */
  spellZone->unk4 = (u8)(((gSpellEffectData.row2 & 3) << 4) | (gSpellEffectData.col2 & 0xF));
  spellZone->permStage = (s8)(((row2 & 3) << 4) | (col2 & 0xF));

  Duel_ActivateContinuousZone(spellZone);
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
