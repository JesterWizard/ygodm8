#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "fusion_duel.h"
#include "power_bond.h"
#include "spell_effects.h"

#define POWER_BOND_BOARD_CELLS 20

static u16 GetDuelBoardCellIndex(const struct DuelCard *zone)
{
  const struct DuelCard *base = &gDuel.board[0][0];

  if (zone < base || zone >= base + POWER_BOND_BOARD_CELLS)
    return 0xFFFF;

  return (u16)(zone - base);
}

static u16 *GetPowerBondAtkBonusPtr(const struct DuelCard *zone)
{
  u16 index = GetDuelBoardCellIndex(zone);

  if (index >= POWER_BOND_BOARD_CELLS)
    return NULL;

  return &gPowerBondAtkBonus[index];
}

static u8 RecipeIsMachineFusion(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return FALSE;

  return Duel_CardHasMonsterType(recipe->result, TYPE_MACHINE);
}

static struct DuelCard *FindActiveFusionResultZone(u16 resultId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == resultId)
      return zone;
  }

  return NULL;
}

void PowerBond_ClearAtkBonusForZone(const struct DuelCard *zone)
{
  u16 *bonus = GetPowerBondAtkBonusPtr(zone);

  if (bonus != NULL)
    *bonus = 0;
}

void PowerBond_ClearState(void)
{
  u16 i;

  for (i = 0; i < POWER_BOND_BOARD_CELLS; i++)
    gPowerBondAtkBonus[i] = 0;
  gPowerBondEndPhaseBurn = 0;
}

void ApplyPowerBondAtkBonusToCardInfo(const struct DuelCard *zone)
{
  const u16 *bonus = GetPowerBondAtkBonusPtr(zone);
  u32 atk;

  if (bonus == NULL || *bonus == 0)
    return;

  atk = (u32)gCardInfo.atk + (u32)(*bonus);
  gCardInfo.atk = Duel_ClampStat(atk);
}

void PowerBond_OnFusionSummoned(u16 resultId)
{
  struct DuelCard *zone;
  u16 *bonus;
  u16 originalAtk;
  u32 burn;

  /* Printed original ATK only — Overdragon's material-based ATK is not original. */
  SetCardInfo(resultId);
  originalAtk = gCardInfo.atk;
  if (originalAtk == 0)
    return;

  zone = FindActiveFusionResultZone(resultId);
  if (zone == NULL)
    return;

  bonus = GetPowerBondAtkBonusPtr(zone);
  if (bonus == NULL)
    return;

  *bonus = originalAtk;

  burn = (u32)gPowerBondEndPhaseBurn + (u32)originalAtk;
  if (burn > 65535)
    burn = 65535;
  gPowerBondEndPhaseBurn = (u16)burn;
}

void TryApplyPowerBondEndPhaseBurn(void)
{
  u16 burn = gPowerBondEndPhaseBurn;

  if (burn == 0 || IsDuelOver() == TRUE)
    return;

  gPowerBondEndPhaseBurn = 0;

  /* TryActivatingTurnEffects runs at the start of the next turn, so the
   * activator is the inactive (previous-turn) duelist. */
  Duel_ShowCardEffectText(POWER_BOND, CARD_EFFECT_TEXT_POWER_BOND_POPUP_2);
  if (IsDuelOver() == TRUE)
    return;

  Duel_ChangeLp(INACTIVE_DUELIST, -(s32)burn, TRUE);
}

static void RunPlayerPowerBondFlow(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  sourceCount = FusionDuel_CollectHandAndFieldSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                                        ARRAY_COUNT(feasibleIndices),
                                                        RecipeIsMachineFusion);
  if (feasibleCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(POWER_BOND);
  if (IsDuelOver() == TRUE)
    return;

  recipe = FusionDuel_PlayerConfirmFusionPick(feasibleIndices, feasibleCount);
  if (recipe != NULL)
    FusionDuel_ExecutePowerBond(recipe, sources, sourceCount, POWER_BOND, FALSE);
}

APPEND_TEXT void EffectPowerBond(void)
{
  if (WhoseTurn() != DUEL_PLAYER) {
    struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
    u8 sourceCount;
    s8 bestIdx;

    sourceCount = FusionDuel_CollectHandAndFieldSources(sources, FUSION_MAX_SOURCES);
    if (sourceCount < 2) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    bestIdx = FusionDuel_AiPickBestRecipeIndex(sources, sourceCount, RecipeIsMachineFusion);
    if (bestIdx < 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    FusionDuel_ExecutePowerBond(&gFusionRecipes[bestIdx], sources, sourceCount, POWER_BOND, TRUE);
    return;
  }

  RunPlayerPowerBondFlow();
}
