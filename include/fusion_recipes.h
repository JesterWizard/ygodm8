#ifndef GUARD_FUSION_RECIPES_H
#define GUARD_FUSION_RECIPES_H

#define FUSION_RECIPE_WILDCARD 0xFFFF

struct FusionRecipe {
  u16 result;
  u16 material1;
  u16 material2;
  u16 material3;
};

extern const struct FusionRecipe gFusionRecipes[];

u8 FusionRecipe_Count(void);

const struct FusionRecipe *FusionRecipe_FindByResult(u16 result);
u8 FusionRecipe_MaterialCount(const struct FusionRecipe *recipe);
u16 FusionRecipe_MaterialAt(const struct FusionRecipe *recipe, u8 index);

#endif // GUARD_FUSION_RECIPES_H
