#ifndef GUARD_FUSION_DUEL_H
#define GUARD_FUSION_DUEL_H

#include "fusion_recipes.h"

#define FUSION_MAX_SOURCES 20
#define FUSION_GY_INDEX_NONE 0xFF

struct FusionMaterialSource {
  struct DuelCard *zone;
  u8 gyIndex;
  u16 cardId;
};

typedef u8 (*FusionRecipeFilterFn)(const struct FusionRecipe *recipe);

u8 FusionDuel_CollectHandAndFieldSources(struct FusionMaterialSource *out, u8 maxOut);
u8 FusionDuel_CollectFieldAndGraveyardSources(struct FusionMaterialSource *out, u8 maxOut);
u8 FusionDuel_CollectGraveyardElementalHeroSources(struct FusionMaterialSource *out, u8 maxOut);
u8 FusionRecipe_IsFeasibleWithSources(const struct FusionRecipe *recipe,
                                      const struct FusionMaterialSource *sources,
                                      u8 sourceCount);
u8 FusionRecipe_SelectSources(const struct FusionRecipe *recipe,
                              const struct FusionMaterialSource *sources, u8 sourceCount,
                              struct FusionMaterialSource *selected, u8 maxSelected);
u8 FusionDuel_BuildFeasibleRecipeIndices(const struct FusionMaterialSource *sources,
                                         u8 sourceCount, u8 *outIndices, u8 maxOut,
                                         FusionRecipeFilterFn filter);
const struct FusionRecipe *FusionDuel_PlayerPickRecipe(const u8 *recipeIndices, u8 count);
const struct FusionRecipe *FusionDuel_PlayerConfirmFusionPick(const u8 *recipeIndices, u8 count);
void FusionDuel_ExecutePolymerization(const struct FusionRecipe *recipe,
                                    const struct FusionMaterialSource *sources,
                                    u8 sourceCount, u16 spellCardId, u8 showEffectText);
void FusionDuel_ExecuteMiracleFusion(const struct FusionRecipe *recipe,
                                     const struct FusionMaterialSource *sources,
                                     u8 sourceCount, u16 spellCardId, u8 showEffectText);
s8 FusionDuel_AiPickBestRecipeIndex(const struct FusionMaterialSource *sources,
                                    u8 sourceCount, FusionRecipeFilterFn filter);

#if defined(DUEL_HELPERS_SELF_CHECK)
void FusionDuel_SelfCheck(void);
#endif

#endif // GUARD_FUSION_DUEL_H
