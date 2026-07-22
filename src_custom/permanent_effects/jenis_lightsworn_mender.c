#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "jenis_lightsworn_mender.h"

#define JENIS_BURN_HEAL 500

static u8 sDeckMilledThisTurn[2] APPEND_DATA = {0, 0};

void JenisLightswornMender_NoteDeckMill(u8 fixedDuelist)
{
  if (fixedDuelist <= DUEL_OPPONENT)
    sDeckMilledThisTurn[fixedDuelist] = TRUE;
}

void JenisLightswornMender_ClearTurnState(void)
{
  sDeckMilledThisTurn[0] = FALSE;
  sDeckMilledThisTurn[1] = FALSE;
}

void TryApplyJenisEndPhase(void)
{
  u8 fixed;
  u8 col;

  for (fixed = DUEL_PLAYER; fixed <= DUEL_OPPONENT; fixed++) {
    u8 row = Duel_FixedMonsterRowForDuelist(fixed);
    u8 burnTarget = fixed == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

    if (!sDeckMilledThisTurn[fixed])
      continue;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id != JENIS_LIGHTSWORN_MENDER || !zone->isFaceUp)
        continue;

      Duel_ShowEffectTextTyped(JENIS_LIGHTSWORN_MENDER, 8);
      if (Duel_ChangeLp(burnTarget, -(s32)JENIS_BURN_HEAL, TRUE) == DUEL_ACTION_DUEL_OVER)
        return;
      if (Duel_ChangeLp(fixed, JENIS_BURN_HEAL, TRUE) == DUEL_ACTION_DUEL_OVER)
        return;
      return;
    }
  }
}

unsigned char ShouldActivateJENIS_LIGHTSWORN_MENDER(void)
{
  /* ponytail: LS-effect mill source not tracked — any deck mill this turn stand-in.
   * EP burn/heal via TryApplyJenisEndPhase. */
  return FALSE;
}

void ActivateJENIS_LIGHTSWORN_MENDER(void)
{
}
