#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateDARKLORD_NURSE_REFICULE(void)
{
  /* LP gain→damage redirect needs LP-change hook. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateDARKLORD_NURSE_REFICULE(void)
{
}
