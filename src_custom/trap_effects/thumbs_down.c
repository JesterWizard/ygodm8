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

static void ActivateTHUMBS_DOWNZone(struct DuelCard *zone)
{
  if (!ControlsGladiatorBeast())
    return;

  if (Duel_ActivateContinuousTrapPreamble(zone, THUMBS_DOWN) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: destroy by battle/effect → controller takes 500 each needs destroy
   * hook. Ceiling: face-up continuous only. */
}

void TryActivateTHUMBS_DOWNOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(THUMBS_DOWN, ActivateTHUMBS_DOWNZone);
}
