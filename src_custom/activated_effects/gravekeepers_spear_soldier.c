#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char CanActivateGRAVEKEEPERS_SPEAR_SOLDIER(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_SPEAR_SOLDIER)
    return FALSE;

  /* Pierce via ApplySimplePiercersBattleEffect. */
  return FALSE;
}

void ActivateGRAVEKEEPERS_SPEAR_SOLDIEREffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_SPEAR_SOLDIER, 2);
}
