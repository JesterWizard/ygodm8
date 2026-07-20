#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void UpdateDuelGfxExceptField(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static const char sShaddollArchetypeName[] APPEND_RODATA = "Shaddoll";

/* Declared Attribute stored on equip spell unk4 (0 = unset). */
static const u8 sNepheAttributes[] APPEND_RODATA = {
  ATTRIBUTE_SHADOW,
  ATTRIBUTE_LIGHT,
  ATTRIBUTE_EARTH,
  ATTRIBUTE_FIRE,
  ATTRIBUTE_WATER,
  ATTRIBUTE_WIND,
  ATTRIBUTE_FOREST,
};

static u8 sNepheReqRow APPEND_DATA = {0};
static u8 sNepheReqCol APPEND_DATA = {0};
static u8 sNepheReqSet APPEND_DATA = {0};

static void SetNepheRequiredEquipped(struct DuelCard *equipped)
{
  u8 col;
  u8 row;

  sNepheReqSet = FALSE;
  if (equipped == NULL)
    return;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gFixedZones[row][col] == equipped) {
        sNepheReqRow = row;
        sNepheReqCol = col;
        sNepheReqSet = TRUE;
        return;
      }
    }
  }
}

static struct DuelCard *GetNepheRequiredEquipped(void)
{
  if (!sNepheReqSet)
    return NULL;

  return gFixedZones[sNepheReqRow][sNepheReqCol];
}

static void ClearNepheRequiredEquipped(void)
{
  sNepheReqSet = FALSE;
}

static u8 RecipeIsShaddollFusion(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return FALSE;

  SetCardInfo(recipe->result);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  return Duel_CardNameContains(recipe->result, sShaddollArchetypeName);
}

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsShaddollMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sShaddollArchetypeName);
}

static u8 IsValidNepheEquipTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsShaddollMonster(zone->id);
}

static u8 HasNepheEquipTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidNepheEquipTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

static u8 PlayerChoosesAttribute(void)
{
  u8 idx = 0;

  /* ponytail: no attribute-name UI — A confirms, B cycles list.
   * Ceiling: unlabeled; upgrade: effect-text attribute menu. */
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return sNepheAttributes[idx];
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      idx++;
      if (idx >= ARRAY_COUNT(sNepheAttributes))
        idx = 0;
    }

    WaitForVBlank();
  }
}

static u8 ExtraDeckHasResult(u16 resultId)
{
  u16 *extra;
  u8 active;
  u8 k;

  if (!gRuntimeConfig.enable_extra_deck)
    return TRUE;

  active = gActiveDeckIndex;
  if (active >= PLAYER_DECK_INDEX_MIN && active <= PLAYER_DECK_INDEX_MAX) {
    switch (active) {
    case 1: extra = gPlayerDeck1ExtraDeck; break;
    case 2: extra = gPlayerDeck2ExtraDeck; break;
    case 3: extra = gPlayerDeck3ExtraDeck; break;
    default: extra = gPlayerDeck1ExtraDeck; break;
    }
  } else {
    extra = gPlayerDeck1ExtraDeck;
  }

  for (k = 0; k < EXTRA_DECK_SIZE; k++) {
    if (extra[k] == resultId)
      return TRUE;
  }

  return FALSE;
}

static u8 SelectedIncludesZone(const struct FusionMaterialSource *selected, u8 selectedCount,
                               struct DuelCard *zone)
{
  u8 i;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].zone == zone)
      return TRUE;
  }

  return FALSE;
}

static u8 RecipeUsesRequiredEquipped(const struct FusionRecipe *recipe)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  struct FusionMaterialSource selected[FUSION_MAX_MATERIALS];
  u8 sourceCount;
  u8 selectedCount;
  struct DuelCard *equipped = GetNepheRequiredEquipped();

  if (recipe == NULL || equipped == NULL || equipped->id == CARD_NONE)
    return FALSE;

  if (!RecipeIsShaddollFusion(recipe))
    return FALSE;

  sourceCount = FusionDuel_CollectHandAndFieldSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2)
    return FALSE;

  /* Prefer equipped first so greedy SelectSources includes it when possible. */
  {
    u8 i;
    for (i = 0; i < sourceCount; i++) {
      if (sources[i].zone == equipped) {
        struct FusionMaterialSource tmp = sources[0];
        sources[0] = sources[i];
        sources[i] = tmp;
        break;
      }
    }
  }

  selectedCount = FusionRecipe_SelectSources(recipe, sources, sourceCount, selected,
                                             FUSION_MAX_MATERIALS);
  if (!FusionRecipe_SelectedCountIsValid(recipe, selectedCount))
    return FALSE;

  return SelectedIncludesZone(selected, selectedCount, equipped);
}

static struct DuelCard *FindNepheEquipTarget(struct DuelCard *spellZone)
{
  u8 i;

  if (spellZone == NULL)
    return NULL;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    struct DynamicEquipLink *link = &gDynamicEquipLinks[i];

    if (!link->active || link->spellId != NEPHE_SHADDOLL_FUSION)
      continue;
    if (gFixedZones[link->spellFixedRow][link->spellFixedCol] != spellZone)
      continue;

    return gFixedZones[link->targetFixedRow][link->targetFixedCol];
  }

  return NULL;
}

static void CollectSourcesEquippedFirst(struct FusionMaterialSource *out, u8 *outCount,
                                        struct DuelCard *equipped)
{
  u8 count = FusionDuel_CollectHandAndFieldSources(out, FUSION_MAX_SOURCES);
  u8 i;

  for (i = 0; i < count; i++) {
    if (out[i].zone == equipped) {
      struct FusionMaterialSource tmp = out[0];
      out[0] = out[i];
      out[i] = tmp;
      break;
    }
  }

  *outCount = count;
}

static void RunNepheFusionIgnition(struct DuelCard *spellZone)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;
  u8 filtered[32];
  u8 filteredCount = 0;
  const struct FusionRecipe *recipe;
  struct DuelCard *equipped;
  u8 i;

  equipped = FindNepheEquipTarget(spellZone);
  if (equipped == NULL || equipped->id == CARD_NONE) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  SetNepheRequiredEquipped(equipped);
  CollectSourcesEquippedFirst(sources, &sourceCount, equipped);
  if (sourceCount < 2) {
    ClearNepheRequiredEquipped();
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                                        ARRAY_COUNT(feasibleIndices),
                                                        RecipeUsesRequiredEquipped);
  for (i = 0; i < feasibleCount; i++) {
    u16 result = gFusionRecipes[feasibleIndices[i]].result;

    if (!ExtraDeckHasResult(result))
      continue;

    filtered[filteredCount++] = feasibleIndices[i];
  }

  if (filteredCount == 0) {
    ClearNepheRequiredEquipped();
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(NEPHE_SHADDOLL_FUSION);
  if (IsDuelOver() == TRUE) {
    ClearNepheRequiredEquipped();
    return;
  }

  spellZone->effectUsedThisTurn = TRUE;

  if (WhoseTurn() != DUEL_PLAYER) {
    s8 bestIdx = FusionDuel_AiPickBestRecipeIndex(sources, sourceCount,
                                                 RecipeUsesRequiredEquipped);

    ClearNepheRequiredEquipped();
    if (bestIdx < 0 || !ExtraDeckHasResult(gFusionRecipes[bestIdx].result)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    CollectSourcesEquippedFirst(sources, &sourceCount, equipped);
    FusionDuel_ExecutePolymerization(&gFusionRecipes[bestIdx], sources, sourceCount,
                                     NEPHE_SHADDOLL_FUSION, FALSE);
    UpdateDuelGfxExceptField();
    return;
  }

  ClearNepheRequiredEquipped();
  recipe = FusionDuel_PlayerConfirmFusionPick(filtered, filteredCount);
  if (recipe == NULL)
    return;

  CollectSourcesEquippedFirst(sources, &sourceCount, equipped);
  FusionDuel_ExecutePolymerization(recipe, sources, sourceCount, NEPHE_SHADDOLL_FUSION,
                                   FALSE);
  UpdateDuelGfxExceptField();
}

static u8 CanActivateNepheFusionIgnition(struct DuelCard *zone)
{
  struct DuelCard *equipped;

  if (zone == NULL || zone->id != NEPHE_SHADDOLL_FUSION || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  equipped = FindNepheEquipTarget(zone);
  if (equipped == NULL || equipped->id == CARD_NONE)
    return FALSE;

  SetNepheRequiredEquipped(equipped);
  {
    struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
    u8 sourceCount;
    u8 feasibleIndices[32];
    u8 feasibleCount;

    CollectSourcesEquippedFirst(sources, &sourceCount, equipped);
    feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(
        sources, sourceCount, feasibleIndices, ARRAY_COUNT(feasibleIndices),
        RecipeUsesRequiredEquipped);
    ClearNepheRequiredEquipped();
    return feasibleCount > 0;
  }
}

static void EquipNephe(struct DuelCard *spellZone, struct DuelCard *target, u8 attribute)
{
  if (!RegisterDynamicEquip(spellZone, target, NEPHE_SHADDOLL_FUSION, 0))
    return;

  spellZone->unk4 = attribute;
  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();

  /* ponytail: declared Attribute is stored in unk4 only — fusion/material checks
   * still use printed SetCardInfo attribute. Ceiling: equip + OPT fusion works;
   * Attribute change cosmetic. Upgrade: MaterialMatches / SourceQualifies reads
   * DynamicEquipTargetsMonsterWithSpell attribute override from unk4. */

  /* ponytail: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone
   * instead of vanilla equip targeting. Ceiling: add NEPHE_SHADDOLL_FUSION to
   * card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone. */
}

static void ResolveNepheEquipTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];
  u8 attribute;

  if (!IsValidNepheEquipTarget(fixedRow, fixedCol) || spellZone == NULL)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    attribute = PlayerChoosesAttribute();
  else
    attribute = ATTRIBUTE_SHADOW;

  EquipNephe(spellZone, target, attribute);
}

static void CancelNepheEquipTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == NEPHE_SHADDOLL_FUSION)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickNepheEquipTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidNepheEquipTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void NEPHE_SHADDOLL_FUSION_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Face-up equip re-activation → OPT Fusion Summon including equipped. */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivateNepheFusionIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    RunNepheFusionIgnition(zone);
    return;
  }

  Duel_ShowEffectText(NEPHE_SHADDOLL_FUSION);

  if (IsDuelOver() == TRUE || !HasNepheEquipTarget())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidNepheEquipTarget, ResolveNepheEquipTarget,
                     CancelNepheEquipTargeting, AiPickNepheEquipTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();

  /* ponytail: not in GetSpellType NORMAL override — face-up OPT fusion
   * re-activation may need card_hooks GetSpellType + NEPHE_SHADDOLL_FUSION
   * listed (same as WEAPON_CHANGE / CHICKEN_GAME). */
}

APPEND_TEXT void EffectNEPHE_SHADDOLL_FUSION(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (zone != NULL && zone->isLocked) {
    if (!CanActivateNepheFusionIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }
  } else if (!HasNepheEquipTarget()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(NEPHE_SHADDOLL_FUSION,
                                       NEPHE_SHADDOLL_FUSION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void NEPHE_SHADDOLL_FUSION_SelfCheck(void)
{
  struct FusionRecipe recipe;

  if (!IsShaddollMonster(SHADDOLL_DRAGON))
    while (1)
      ;

  recipe.result = EL_SHADDOLL_CONSTRUCT;
  recipe.material1 = CARD_NONE;
  recipe.material2 = CARD_NONE;
  recipe.material3 = CARD_NONE;
  recipe.material4 = CARD_NONE;
  if (!RecipeIsShaddollFusion(&recipe))
    while (1)
      ;

  recipe.result = BLUE_EYES_WHITE_DRAGON;
  if (RecipeIsShaddollFusion(&recipe))
    while (1)
      ;
}
#endif
