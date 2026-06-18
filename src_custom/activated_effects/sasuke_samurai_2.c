#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "sasuke_samurai_2.h"

u8 SasukeSamurai2_AreInactiveBackrowTrapsBlocked(void)
{
  return gSasukeSamurai2InactiveBackrowTrapBlock != 0;
}

void SasukeSamurai2_ClearInactiveBackrowTrapBlock(void)
{
  gSasukeSamurai2InactiveBackrowTrapBlock = 0;
}

u8 SasukeSamurai2_AllowsFaceUpEffectActivation(u16 cardId)
{
  return cardId == SASUKE_SAMURAI_2;
}

unsigned char CanActivateSasukeSamurai2(void)
{
  if (gMonEffect.id != SASUKE_SAMURAI_2)
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= SASUKE_SAMURAI_2_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= SASUKE_SAMURAI_2_LP_COST;
}

void ActivateSasukeSamurai2Effect(void)
{
  gSasukeSamurai2InactiveBackrowTrapBlock = 1;

  Duel_ShowEffectTextTyped(SASUKE_SAMURAI_2, 2);
  if (IsDuelOver() == TRUE) {
    SasukeSamurai2_ClearInactiveBackrowTrapBlock();
    return;
  }

  if (Duel_ChangeLp(WhoseTurn(), -SASUKE_SAMURAI_2_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER) {
    SasukeSamurai2_ClearInactiveBackrowTrapBlock();
    return;
  }
}
