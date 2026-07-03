#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "fusion_recipes.h"

/* ponytail: shared fusion recipe table for Polymerization, Miracle Fusion, and De-Fusion. */

APPEND_RODATA const struct FusionRecipe gFusionRecipes[] = {
  { FLAME_SWORDSMAN, FLAME_MANIPULATOR, MASAKI_THE_LEGENDARY_SWORDSMAN, 0, 0 },
  { THOUSAND_DRAGON, TIME_WIZARD, BABY_DRAGON, 0, 0 },
  { GAIA_THE_DRAGON_CHAMPION, GAIA_THE_FIERCE_KNIGHT, CURSE_OF_DRAGON, 0, 0 },
  { ALLIGATORS_SWORD_DRAGON, ALLIGATORS_SWORD_DRAGON, BABY_DRAGON, 0, 0 },
  { B_SKULL_DRAGON, SUMMONED_SKULL, RED_EYES_B_DRAGON, 0, 0 },
  { BLUE_EYES_ULTIMATE_DRAGON, BLUE_EYES_WHITE_DRAGON, BLUE_EYES_WHITE_DRAGON,
    BLUE_EYES_WHITE_DRAGON, 0 },
  { ELEMENTAL_HERO_MUDBALLMAN, ELEMENTAL_HERO_BUBBLEMAN, ELEMENTAL_HERO_CLAYMAN, 0, 0 },
  { ELEMENTAL_HERO_RAMPART_BLASTER, ELEMENTAL_HERO_CLAYMAN, ELEMENTAL_HERO_BURSTINATRIX, 0, 0 },
  { ELEMENTAL_HERO_STEAM_HEALER, ELEMENTAL_HERO_BURSTINATRIX, ELEMENTAL_HERO_BUBBLEMAN, 0, 0 },
  { ELEMENTAL_HERO_PHOENIX_ENFORCER, ELEMENTAL_HERO_AVIAN, ELEMENTAL_HERO_BURSTINATRIX, 0, 0 },
  { ELEMENTAL_HERO_FLAME_WINGMAN, ELEMENTAL_HERO_AVIAN, ELEMENTAL_HERO_BURSTINATRIX, 0, 0 },
  { ELEMENTAL_HERO_SHINING_PHOENIX_ENFORCER, ELEMENTAL_HERO_PHOENIX_ENFORCER,
    ELEMENTAL_HERO_SPARKMAN, 0, 0 },
  { ELEMENTAL_HERO_SHINING_FLARE_WINGMAN, ELEMENTAL_HERO_FLAME_WINGMAN,
    ELEMENTAL_HERO_SPARKMAN, 0, 0 },
  { ELEMENTAL_HERO_TEMPEST, ELEMENTAL_HERO_AVIAN, ELEMENTAL_HERO_SPARKMAN,
    ELEMENTAL_HERO_BUBBLEMAN, 0 },
  { ELEMENTAL_HERO_WILDEDGE, ELEMENTAL_HERO_WILDHEART, ELEMENTAL_HERO_BLADEDGE, 0, 0 },
  { ELEMENTAL_HERO_WILD_WINGMAN, ELEMENTAL_HERO_WILDHEART, ELEMENTAL_HERO_AVIAN, 0, 0 },
  { ELEMENTAL_HERO_THUNDER_GIANT, ELEMENTAL_HERO_SPARKMAN, ELEMENTAL_HERO_CLAYMAN, 0, 0 },
  { ELEMENTAL_HERO_MARINER, ELEMENTAL_HERO_BUBBLEMAN, ELEMENTAL_HERO_AVIAN, 0, 0 },
  { ELEMENTAL_HERO_ELECTRUM, ELEMENTAL_HERO_AVIAN, ELEMENTAL_HERO_BURSTINATRIX,
    ELEMENTAL_HERO_CLAYMAN, ELEMENTAL_HERO_BUBBLEMAN },
  { ELEMENTAL_HERO_GREAT_TORNADO, FUSION_RECIPE_ELEMENTAL_HERO, FUSION_RECIPE_ATTRIBUTE_WIND, 0, 0 },
  { ELEMENTAL_HERO_TERRA_FIRMA, ELEMENTAL_HERO_OCEAN, ELEMENTAL_HERO_WOODSMAN, 0, 0 },
  { ELEMENTAL_HERO_ABSOLUTE_ZERO, FUSION_RECIPE_ELEMENTAL_HERO, FUSION_RECIPE_ATTRIBUTE_WATER, 0, 0 },
  { ELEMENTAL_HERO_GAIA, FUSION_RECIPE_ELEMENTAL_HERO, FUSION_RECIPE_ATTRIBUTE_EARTH, 0, 0 },
  { ELEMENTAL_HERO_ESCURIDAO, FUSION_RECIPE_ELEMENTAL_HERO, FUSION_RECIPE_ATTRIBUTE_SHADOW, 0, 0 },
  { ELEMENTAL_HERO_THE_SHINING, FUSION_RECIPE_ELEMENTAL_HERO, FUSION_RECIPE_ATTRIBUTE_LIGHT, 0, 0 },
  { ELEMENTAL_HERO_INFERNO, ELEMENTAL_HERO_HEAT, ELEMENTAL_HERO_LADY_HEAT, 0, 0 },
  { ELEMENTAL_HERO_NECROID_SHAMAN, ELEMENTAL_HERO_WILDHEART, ELEMENTAL_HERO_NECROSHADE, 0, 0 },
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

  if (recipe->material4 != CARD_NONE && recipe->material4 != 0)
    return 4;

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
  case 3:
    return recipe->material4;
  default:
    return CARD_NONE;
  }
}

u8 FusionRecipe_MaterialIsConcrete(u16 material)
{
  if (material == CARD_NONE || material == FUSION_RECIPE_WILDCARD)
    return FALSE;

  if (material == FUSION_RECIPE_ELEMENTAL_HERO)
    return FALSE;

  if ((material & ~FUSION_RECIPE_ATTRIBUTE_VALUE_MASK) == FUSION_RECIPE_ATTRIBUTE_BASE)
    return FALSE;

  return TRUE;
}

u8 FusionRecipe_MaterialMatches(u16 need, u16 cardId)
{
  u8 attribute;

  if (cardId == CARD_NONE)
    return FALSE;

  if (need == FUSION_RECIPE_WILDCARD)
    return TRUE;

  if (need == FUSION_RECIPE_ELEMENTAL_HERO)
    return Duel_IsElementalHeroCard(cardId);

  if ((need & ~FUSION_RECIPE_ATTRIBUTE_VALUE_MASK) == FUSION_RECIPE_ATTRIBUTE_BASE) {
    attribute = need & FUSION_RECIPE_ATTRIBUTE_VALUE_MASK;
    SetCardInfo(cardId);
    return gCardInfo.attribute == attribute;
  }

  return need == cardId;
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

  recipe = FusionRecipe_FindByResult(ELEMENTAL_HERO_TEMPEST);
  if (recipe == NULL || FusionRecipe_MaterialCount(recipe) != 3)
    while (1)
      ;

  recipe = FusionRecipe_FindByResult(ELEMENTAL_HERO_ELECTRUM);
  if (recipe == NULL || FusionRecipe_MaterialCount(recipe) != 4)
    while (1)
      ;

  recipe = FusionRecipe_FindByResult(ELEMENTAL_HERO_GREAT_TORNADO);
  if (recipe == NULL || FusionRecipe_MaterialCount(recipe) != 2)
    while (1)
      ;

  recipe = FusionRecipe_FindByResult(ELEMENTAL_HERO_TERRA_FIRMA);
  if (recipe == NULL || FusionRecipe_MaterialCount(recipe) != 2)
    while (1)
      ;

  recipe = FusionRecipe_FindByResult(ELEMENTAL_HERO_ABSOLUTE_ZERO);
  if (recipe == NULL || FusionRecipe_MaterialCount(recipe) != 2)
    while (1)
      ;

  recipe = FusionRecipe_FindByResult(ELEMENTAL_HERO_WILD_WINGMAN);
  if (recipe == NULL || FusionRecipe_MaterialCount(recipe) != 2)
    while (1)
      ;

  recipe = FusionRecipe_FindByResult(ELEMENTAL_HERO_GAIA);
  if (recipe == NULL || FusionRecipe_MaterialCount(recipe) != 2)
    while (1)
      ;

  recipe = FusionRecipe_FindByResult(ELEMENTAL_HERO_ESCURIDAO);
  if (recipe == NULL || FusionRecipe_MaterialCount(recipe) != 2)
    while (1)
      ;

  recipe = FusionRecipe_FindByResult(ELEMENTAL_HERO_THE_SHINING);
  if (recipe == NULL || FusionRecipe_MaterialCount(recipe) != 2)
    while (1)
      ;

  recipe = FusionRecipe_FindByResult(ELEMENTAL_HERO_INFERNO);
  if (recipe == NULL || FusionRecipe_MaterialCount(recipe) != 2)
    while (1)
      ;

  recipe = FusionRecipe_FindByResult(ELEMENTAL_HERO_NECROID_SHAMAN);
  if (recipe == NULL || FusionRecipe_MaterialCount(recipe) != 2)
    while (1)
      ;

  if (!FusionRecipe_MaterialMatches(FUSION_RECIPE_ELEMENTAL_HERO, ELEMENTAL_HERO_AVIAN))
    while (1)
      ;

  if (!FusionRecipe_MaterialMatches(FUSION_RECIPE_ATTRIBUTE_WIND, ELEMENTAL_HERO_AVIAN))
    while (1)
      ;

  if (FusionRecipe_MaterialMatches(FUSION_RECIPE_ATTRIBUTE_WIND, ELEMENTAL_HERO_CLAYMAN))
    while (1)
      ;

  if (!FusionRecipe_MaterialMatches(FUSION_RECIPE_ATTRIBUTE_EARTH, ELEMENTAL_HERO_CLAYMAN))
    while (1)
      ;

  if (!FusionRecipe_MaterialMatches(FUSION_RECIPE_ATTRIBUTE_SHADOW, DARK_MAGICIAN))
    while (1)
      ;

  if (!FusionRecipe_MaterialMatches(FUSION_RECIPE_ATTRIBUTE_LIGHT, ELEMENTAL_HERO_SPARKMAN))
    while (1)
      ;

  if (FusionRecipe_MaterialMatches(FUSION_RECIPE_ATTRIBUTE_LIGHT, ELEMENTAL_HERO_CLAYMAN))
    while (1)
      ;

  if (FusionRecipe_FindByResult(CARD_NONE) != NULL)
    while (1)
      ;
}
#endif
