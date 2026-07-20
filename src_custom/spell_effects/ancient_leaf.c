#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

#define ANCIENT_LEAF_LP_REQUIRE 9000
#define ANCIENT_LEAF_LP_COST 2000
#define ANCIENT_LEAF_DRAW_COUNT 2

u8 CanActivateAncientLeaf(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= ANCIENT_LEAF_LP_REQUIRE;

  return gDuelLifePoints[DUEL_OPPONENT] >= ANCIENT_LEAF_LP_REQUIRE;
}

/* Body lives in effect_scripts (Phase 4b JSON → C table). */
APPEND_TEXT void EffectANCIENT_LEAF(void)
{
  const struct EffectScript *script = EffectScript_Find(ANCIENT_LEAF, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ANCIENT_LEAF_SelfCheck(void)
{
  if (ANCIENT_LEAF_LP_REQUIRE != 9000)
    while (1)
      ;
  if (ANCIENT_LEAF_LP_COST != 2000)
    while (1)
      ;
  if (ANCIENT_LEAF_DRAW_COUNT != 2)
    while (1)
      ;
}
#endif
