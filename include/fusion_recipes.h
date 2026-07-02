#ifndef GUARD_FUSION_RECIPES_H
#define GUARD_FUSION_RECIPES_H

#include "constants/card_enums.h"

#define FUSION_RECIPE_WILDCARD 0xFFFF
#define FUSION_RECIPE_ELEMENTAL_HERO 0xFFFE
#define FUSION_RECIPE_ATTRIBUTE_BASE 0xFF80
#define FUSION_RECIPE_ATTRIBUTE_VALUE_MASK 0x007F
#define FUSION_RECIPE_ATTRIBUTE_WIND (FUSION_RECIPE_ATTRIBUTE_BASE | ATTRIBUTE_WIND)
#define FUSION_MAX_MATERIALS 4

struct FusionRecipe {
  u16 result;
  u16 material1;
  u16 material2;
  u16 material3;
  u16 material4;
};

extern const struct FusionRecipe gFusionRecipes[];

u8 FusionRecipe_Count(void);

const struct FusionRecipe *FusionRecipe_FindByResult(u16 result);
u8 FusionRecipe_MaterialCount(const struct FusionRecipe *recipe);
u16 FusionRecipe_MaterialAt(const struct FusionRecipe *recipe, u8 index);
u8 FusionRecipe_MaterialIsConcrete(u16 material);
u8 FusionRecipe_MaterialMatches(u16 need, u16 cardId);

#endif // GUARD_FUSION_RECIPES_H
