#include "global.h"
#include "duel_helpers.h"

extern u8 TheSplendidVenus_DuelistHasNegationImmunity(u8 fixedDuelist);

u8 Duel_DuelistActivationsProtectedFromNegation(u8 fixedDuelist)
{
  if (TheSplendidVenus_DuelistHasNegationImmunity(fixedDuelist))
    return TRUE;

  return FALSE;
}
