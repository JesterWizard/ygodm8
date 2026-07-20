#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "meteor_of_destruction.h"
#include "spell_effects.h"

#define METEOR_OF_DESTRUCTION_LP_THRESHOLD 3000

u8 CanActivateMeteorOfDestruction(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_OPPONENT] > METEOR_OF_DESTRUCTION_LP_THRESHOLD;

  return gDuelLifePoints[DUEL_PLAYER] > METEOR_OF_DESTRUCTION_LP_THRESHOLD;
}

APPEND_TEXT void EffectMeteorOfDestruction(void)
{
  const struct EffectScript *script = EffectScript_Find(METEOR_OF_DESTRUCTION, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
