#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 ControlsGladiatorBeast(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && Duel_CardNameContains(zone->id, sGladiatorBeastName))
      return TRUE;
  }

  return FALSE;
}

static void ActivateGLADIATOR_BEASTS_VALORZone(struct DuelCard *zone)
{
  if (!ControlsGladiatorBeast())
    return;

  if (Duel_ActivateContinuousTrapPreamble(zone, GLADIATOR_BEASTS_VALOR)
      == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: opp can only attack GB monsters needs attack-target gate.
   * Ceiling: face-up continuous only. */
}

void TryActivateGLADIATOR_BEASTS_VALOROnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(GLADIATOR_BEASTS_VALOR,
                                         ActivateGLADIATOR_BEASTS_VALORZone);
}
