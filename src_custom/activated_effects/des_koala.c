#include "global.h"
#include "common-chax.h"

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

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gTurnHands[INACTIVE_DUELIST][i]->id != CARD_NONE)
      damage += 500;

  if (damage > 0)
  {
    if (WhoseTurn() == DUEL_PLAYER)
      SetOpponentLifePointsToSubtract(damage);
    else
      SetPlayerLifePointsToSubtract(damage);

    HandleAtkAndLifePointsAction();
    CheckLoserFlags();
  }

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = DES_KOALA;
    ActivateCardEffectText();
  }
}
