#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

unsigned char CanActivateInjectionFairyLily(void) {
  if (gMonEffect.id != INJECTION_FAIRY_LILY)
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= 3000;

  return gDuelLifePoints[DUEL_OPPONENT] >= 3000;
}

void ActivateInjectionFairyLilyEffect(void) {
  u8 i;

  if (Duel_ChangeLp(WhoseTurn(), -3000, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  for (i = 0; i < 4; i++)
    IncrementPermStage(gTurnZones[gMonEffect.row][gMonEffect.zone]);

  Duel_ShowEffectTextTyped(INJECTION_FAIRY_LILY, 2);
}
