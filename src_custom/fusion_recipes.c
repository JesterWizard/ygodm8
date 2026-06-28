#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "fusion_recipes.h"

/* ponytail: shared fusion recipe table for Polymerization and De-Fusion. */

APPEND_RODATA const struct FusionRecipe gFusionRecipes[] = {
  { FLAME_SWORDSMAN, FLAME_MANIPULATOR, MASAKI_THE_LEGENDARY_SWORDSMAN, 0 },
  { THOUSAND_DRAGON, TIME_WIZARD, BABY_DRAGON, 0 },
  { GAIA_THE_DRAGON_CHAMPION, GAIA_THE_FIERCE_KNIGHT, CURSE_OF_DRAGON, 0 },
  { ALLIGATORS_SWORD_DRAGON, ALLIGATORS_SWORD_DRAGON, BABY_DRAGON, 0 },
  { B_SKULL_DRAGON, SUMMONED_SKULL, RED_EYES_B_DRAGON, 0 },
  { BLUE_EYES_ULTIMATE_DRAGON, BLUE_EYES_WHITE_DRAGON, BLUE_EYES_WHITE_DRAGON, BLUE_EYES_WHITE_DRAGON },
};

u8 FusionRecipe_Count(void)
{
  return sizeof(gFusionRecipes) / sizeof(gFusionRecipes[0]);
}

const struct FusionRecipe *FusionRecipe_FindByResult(u16 result)
{
  u8 i;
  u8 count = FusionRecipe_Count();

  for (i = 0; i < count; i++) {
    if (gFusionRecipes[i].result == result)
      return &gFusionRecipes[i];
  }

  return NULL;
}

u8 FusionRecipe_MaterialCount(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return 0;

  if (recipe->material3 != CARD_NONE && recipe->material3 != 0)
    return 3;

  return 2;
}

u16 FusionRecipe_MaterialAt(const struct FusionRecipe *recipe, u8 index)
{
  if (recipe == NULL)
    return CARD_NONE;

  switch (index) {
  case 0:
    return recipe->material1;
  case 1:
    return recipe->material2;
  case 2:
    return recipe->material3;
  default:
    return CARD_NONE;
  }
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void FusionRecipes_SelfCheck(void)
{
  const struct FusionRecipe *recipe;

  if (FusionRecipe_Count() < 1)
    while (1)
      ;

  recipe = FusionRecipe_FindByResult(FLAME_SWORDSMAN);
  if (recipe == NULL || FusionRecipe_MaterialCount(recipe) != 2)
    while (1)
      ;

  recipe = FusionRecipe_FindByResult(BLUE_EYES_ULTIMATE_DRAGON);
  if (recipe == NULL || FusionRecipe_MaterialCount(recipe) != 3)
    while (1)
      ;

  if (FusionRecipe_FindByResult(CARD_NONE) != NULL)
    while (1)
      ;
}
#endif
