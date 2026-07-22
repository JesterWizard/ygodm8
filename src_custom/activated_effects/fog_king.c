#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateFOG_KING(void)
{
  if (gMonEffect.id != FOG_KING)
    return FALSE;

  /* Tribute-flex Normal Summon, ATK = tributed ATK, and global tribute
   * lock need summon/tribute continuous hooks outside this file. Not field-ignition. */
  return FALSE;
}

void ActivateFOG_KINGEffect(void)
{
  Duel_ShowEffectTextTyped(FOG_KING, 2);
}
