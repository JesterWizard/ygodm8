#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

unsigned char CanActivateDesKoala(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gTurnHands[INACTIVE_DUELIST][i]->id != CARD_NONE)
      return TRUE;

  return FALSE;
}

void ActivateDesKoalaEffect(void)
{
  u8 i;
  u16 damage = 0;
  u8 target = (WhoseTurn() == DUEL_PLAYER) ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gTurnHands[INACTIVE_DUELIST][i]->id != CARD_NONE)
      damage += 500;

  if (damage > 0) {
    if (Duel_ChangeLp(target, -(s32)damage, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  Duel_ShowEffectTextTyped(DES_KOALA, 2);
}
