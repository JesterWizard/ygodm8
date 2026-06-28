#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "de_fusion.h"
#include "duel_helpers.h"
#include "fusion_recipes.h"
#include "spell_effects.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void SetCursorToCardDest(void);
void ActivateSpellEffect(void);
void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyardDuelist);

static u8 GetTurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 MonsterTurnRowForFixedRow(u8 fixedRow)
{
  if (fixedRow == PLAYER_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST_MONSTER_ROW : INACTIVE_DUELIST_MONSTER_ROW;

  if (fixedRow == OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST_MONSTER_ROW : ACTIVE_DUELIST_MONSTER_ROW;

  return 0xFF;
}

static u8 CountEmptyMonsterZonesOnTurnRow(u8 turnRow)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnZones[turnRow][col]->id == CARD_NONE)
      count++;
  }

  return count;
}

static u8 IsFusionMonsterCard(u16 cardId)
{
  SetCardInfo(cardId);
  return gCardInfo.color == FUSION_CARD;
}

static u8 HasRoomForDefusionMaterials(u8 targetFixedRow, u8 materialCount)
{
  u8 summonRow = ACTIVE_DUELIST_MONSTER_ROW;
  u8 emptyZones = CountEmptyMonsterZonesOnTurnRow(summonRow);

  if (MonsterTurnRowForFixedRow(targetFixedRow) == summonRow)
    emptyZones++;

  return emptyZones >= materialCount;
}

static u8 IsValidDeFusionTargetZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  const struct FusionRecipe *recipe;
  u8 materialCount;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  if (!IsFusionMonsterCard(zone->id))
    return FALSE;

  recipe = FusionRecipe_FindByResult(zone->id);
  if (recipe == NULL)
    return FALSE;

  materialCount = FusionRecipe_MaterialCount(recipe);
  if (materialCount < 1)
    return FALSE;

  return HasRoomForDefusionMaterials(fixedRow, materialCount);
}

static u8 FindFirstDeFusionTarget(u8 *outRow, u8 *outCol)
{
  u8 row;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidDeFusionTargetZone(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void QueueDeFusionActivation(u8 targetRow, u8 targetCol, u8 originRow, u8 originCol)
{
  gSpellEffectData.id = DE_FUSION;
  gSpellEffectData.row1 = targetRow;
  gSpellEffectData.col1 = targetCol;
  gSpellEffectData.row2 = originRow;
  gSpellEffectData.col2 = originCol;
  ActivateSpellEffect();
}

static enum DuelActionResult SummonFusionMaterials(const struct FusionRecipe *recipe)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u8 materialCount = FusionRecipe_MaterialCount(recipe);
  u8 i;

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;

  for (i = 0; i < materialCount; i++) {
    u16 materialId = FusionRecipe_MaterialAt(recipe, i);

    if (materialId == CARD_NONE || materialId == FUSION_RECIPE_WILDCARD)
      continue;

    if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
      break;

    if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, materialId, opts) != DUEL_ACTION_OK)
      break;

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  return DUEL_ACTION_OK;
}

u8 IsDeFusionCard(u16 cardId)
{
  return cardId == DE_FUSION;
}

u8 FieldHasDeFusionTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 row;
  u8 col;

  (void)originFixedRow;
  (void)originFixedCol;
  return FindFirstDeFusionTarget(&row, &col);
}

void BeginDeFusionTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstDeFusionTarget(&targetRow, &targetCol))
    return;

  if (WhoseTurn() != DUEL_PLAYER) {
    QueueDeFusionActivation(targetRow, targetCol, originFixedRow, originFixedCol);
    return;
  }

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_DE_FUSION_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
}

void TrySelectDeFusionTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidDeFusionTargetZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  QueueDeFusionActivation(targetRow, targetCol, originRow, originCol);
  gDuelCursor.state = 0;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  TryActivatingPermanentEffects();
}

void CancelDeFusionTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

static void DeFusion_ResolveBody(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];
  const struct FusionRecipe *recipe;

  recipe = FusionRecipe_FindByResult(target->id);
  if (recipe == NULL)
    return;

  Duel_ShowEffectText(DE_FUSION);
  if (IsDuelOver() == TRUE)
    return;

  ClearZoneAndSendMonToGraveyard(target, GetTurnDuelistForFixedRow(gSpellEffectData.row1));
  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (SummonFusionMaterials(recipe) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectDeFusion(void)
{
  if (!IsValidDeFusionTargetZone(gSpellEffectData.row1, gSpellEffectData.col1)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(DE_FUSION, DeFusion_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
