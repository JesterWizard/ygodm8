#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "meteor_of_destruction.h"
#include "spell_effects.h"

#define METEOR_OF_DESTRUCTION_DAMAGE 1000
#define METEOR_OF_DESTRUCTION_LP_THRESHOLD 3000

u8 CanActivateMeteorOfDestruction(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_OPPONENT] > METEOR_OF_DESTRUCTION_LP_THRESHOLD;

  return gDuelLifePoints[DUEL_PLAYER] > METEOR_OF_DESTRUCTION_LP_THRESHOLD;
}

static void MeteorOfDestruction_ResolveBody(void)
{
  if (!CanActivateMeteorOfDestruction())
    return;

  if (Duel_ResolveBurnSpell(METEOR_OF_DESTRUCTION, METEOR_OF_DESTRUCTION_DAMAGE, TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;
}

APPEND_TEXT void EffectMeteorOfDestruction(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(METEOR_OF_DESTRUCTION, METEOR_OF_DESTRUCTION_DAMAGE,
                                         MeteorOfDestruction_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
