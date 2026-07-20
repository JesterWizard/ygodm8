#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateAROMA_JAR(void)
{
  if (gMonEffect.id != AROMA_JAR)
    return FALSE;

  /* ponytail: FLIP battle protection + End Phase LP gain need FLIP/continuous hooks.
   * Ceiling: not ignition-activatable here; upgrade: flip + turn-end overlay. */
  return FALSE;
}

void ActivateAROMA_JAREffect(void)
{
  Duel_ShowEffectTextTyped(AROMA_JAR, 2);
}
