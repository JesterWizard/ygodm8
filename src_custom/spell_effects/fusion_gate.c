#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "elemental_hero_absolute_zero.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"

void SetDuelFieldGfx(u8 field);

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == FUSION_GATE || cardId == GEARTOWN || cardId == DRAGON_RAVINE
      || cardId == WETLANDS || cardId == BURNING_LAND || cardId == SEAL_OF_ORICHALCOS)
    return TRUE;

  return IsVanillaTerrainFieldSpell(cardId);
}

static u8 GetTurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void ResetActiveFieldTerrain(void)
{
  RevertCustomFieldToArena();

  if (gDuel.field == FIELD_ARENA)
    return;

  gDuel.field = FIELD_ARENA;

  if (!gHideEffectText)
    SetDuelFieldGfx(gDuel.field);
}

static void DestroyOtherFieldSpellsOnBoard(struct DuelCard *activatingZone)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == activatingZone || zone->id == CARD_NONE)
        continue;

      if (!IsFieldSpellCardOnField(zone->id))
        continue;

      Duel_DestroyZone(zone, GetTurnDuelistForFixedRow(row), FALSE);

      if (IsDuelOver() == TRUE)
        return;
    }
  }

  ResetActiveFieldTerrain();
}

static void PayFusionGateMaterials(const struct FusionMaterialSource *selected, u8 selectedCount)
{
  u8 i;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].zone != NULL)
      Duel_BanishZone(selected[i].zone, FALSE);
  }
}

/* Like Miracle Fusion pay+SS, but keeps Fusion Gate on the field. */
static void ExecuteFusionGateFusion(const struct FusionRecipe *recipe,
                                    const struct FusionMaterialSource *sources,
                                    u8 sourceCount, u8 showEffectText)
{
  struct FusionMaterialSource selected[FUSION_MAX_MATERIALS];
  u8 selectedCount;
  s8 emptyZone;

  if (recipe == NULL)
    return;

  if (recipe->result == CHIMERATECH_OVERDRAGON) {
    u8 playerPick = WhoseTurn() == DUEL_PLAYER;

    if (playerPick)
      DeckMenu_BeginDuelTrunkView();
    selectedCount = FusionDuel_SelectOverdragonMaterials(
        sources, sourceCount, selected, FUSION_MAX_MATERIALS, playerPick);
    if (playerPick)
      DeckMenu_EndDuelTrunkView();
  } else {
    selectedCount = FusionRecipe_SelectSources(recipe, sources, sourceCount, selected,
                                               FUSION_MAX_MATERIALS);
  }

  if (!FusionRecipe_SelectedCountIsValid(recipe, selectedCount))
    return;

  emptyZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (emptyZone < 0)
    return;

  if (showEffectText) {
    Duel_ShowEffectText(FUSION_GATE);
    if (IsDuelOver() == TRUE)
      return;
  }

  ElementalHeroAbsoluteZero_BeginSuppressLeave();
  PayFusionGateMaterials(selected, selectedCount);
  FusionDuel_SpecialSummonResult(recipe->result, selectedCount);
  ElementalHeroAbsoluteZero_EndSuppressLeave();
}

static u8 ExtraDeckAllowsFeasible(const u8 *feasibleIndices, u8 feasibleCount)
{
  u16 *extra;
  u8 active;
  u8 i, filteredCount;

  if (!gRuntimeConfig.enable_extra_deck)
    return TRUE;

  active = gActiveDeckIndex;
  if (active >= PLAYER_DECK_INDEX_MIN && active <= PLAYER_DECK_INDEX_MAX) {
    switch (active) {
    case 1:
      extra = gPlayerDeck1ExtraDeck;
      break;
    case 2:
      extra = gPlayerDeck2ExtraDeck;
      break;
    case 3:
      extra = gPlayerDeck3ExtraDeck;
      break;
    default:
      extra = gPlayerDeck1ExtraDeck;
      break;
    }
  } else {
    extra = gPlayerDeck1ExtraDeck;
  }

  filteredCount = 0;
  for (i = 0; i < feasibleCount; i++) {
    u16 result = gFusionRecipes[feasibleIndices[i]].result;
    u8 k;

    for (k = 0; k < EXTRA_DECK_SIZE; k++) {
      if (extra[k] == result) {
        filteredCount++;
        break;
      }
    }
  }

  return filteredCount > 0;
}

static u8 CanFusionGateIgnition(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  sourceCount = FusionDuel_CollectHandAndFieldSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2)
    return FALSE;

  feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                                        ARRAY_COUNT(feasibleIndices), NULL);
  if (feasibleCount == 0)
    return FALSE;

  return ExtraDeckAllowsFeasible(feasibleIndices, feasibleCount);
}

static void ResolveFusionGateIgnition(void)
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

  if (WhoseTurn() != DUEL_PLAYER) {
    s8 bestIdx = FusionDuel_AiPickBestRecipeIndex(sources, sourceCount, NULL);

    if (bestIdx < 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ExecuteFusionGateFusion(&gFusionRecipes[bestIdx], sources, sourceCount, TRUE);
    return;
  }

  feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                                        ARRAY_COUNT(feasibleIndices), NULL);
  if (feasibleCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (!ExtraDeckAllowsFeasible(feasibleIndices, feasibleCount)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(FUSION_GATE);
  if (IsDuelOver() == TRUE)
    return;

  recipe = FusionDuel_PlayerConfirmFusionPick(feasibleIndices, feasibleCount);
  if (recipe != NULL)
    ExecuteFusionGateFusion(recipe, sources, sourceCount, FALSE);
}

static void FUSION_GATE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up field: Fusion Summon by banishing hand/field. */
  if (zone != NULL && zone->isLocked) {
    if (!CanFusionGateIgnition()) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveFusionGateIgnition();
    return;
  }

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);

  if (CanFusionGateIgnition())
    ResolveFusionGateIgnition();
  else
    Duel_ShowEffectText(FUSION_GATE);

  /* ponytail: real text lets the turn player use either player's Fusion Gate.
   * Ceiling: only the controller's face-up gate via this spell activation path;
   * upgrade: turn-player Main Phase check for any face-up FUSION_GATE then run
   * ResolveFusionGateIgnition for ACTIVE_DUELIST. */
  /* ponytail: not in GetSpellType NORMAL override — face-up re-activation may
   * need card_hooks GetSpellType + FUSION_GATE listed (same as DRAGON_RAVINE). */
}

APPEND_TEXT void EffectFUSION_GATE(void)
{
  if (Duel_TryResolveSpellThroughTraps(FUSION_GATE, FUSION_GATE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void FUSION_GATE_SelfCheck(void)
{
  if (!IsFieldSpellCardOnField(FUSION_GATE))
    while (1)
      ;
  if (IsFieldSpellCardOnField(POLYMERIZATION))
    while (1)
      ;
}
#endif
