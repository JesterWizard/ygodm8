#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static const char sAromaName[] APPEND_RODATA = "Aroma";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 ControlsAroma(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && Duel_CardNameContains(zone->id, sAromaName)
        && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
      return TRUE;
  }

  return FALSE;
}

static void ActivateDRIED_WINDSZone(struct DuelCard *zone)
{
  u8 fixedMe = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 fixedOpp = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 myLp = gDuelLifePoints[fixedMe];
  u16 oppLp = gDuelLifePoints[fixedOpp];
  u8 oppRow = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 col;

  if (Duel_ActivateContinuousTrapPreamble(zone, DRIED_WINDS) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: LP-gain destroy + OPT flags need LP-gain hook.
   * Ceiling: if Aroma + LP≥opp+3000, pay difference and destroy opp face-up
   * monsters while remaining budget covers printed ATK. */

  if (ControlsAroma() && myLp >= oppLp + 3000) {
    u16 pay = myLp - oppLp;
    u16 budget;

    Duel_ChangeLp(INACTIVE_DUELIST, -(s32)pay, FALSE);
    budget = pay;
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *m = gFixedZones[oppRow][col];

      if (m == NULL || !m->isFaceUp || m->id == CARD_NONE)
        continue;
      SetCardInfo(m->id);
      if (gCardInfo.atk > budget)
        continue;
      budget -= gCardInfo.atk;
      Duel_DestroyZone(m, ACTIVE_DUELIST, FALSE);
      if (IsDuelOver() == TRUE)
        return;
    }
  } else {
    /* Soft primary: destroy 1 face-up opp monster (LP-gain stand-in). */
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *m = gFixedZones[oppRow][col];

      if (m != NULL && m->isFaceUp && m->id != CARD_NONE) {
        Duel_DestroyZone(m, ACTIVE_DUELIST, FALSE);
        break;
      }
    }
  }

  UpdateDuelGfxExceptField();
}

void TryActivateDRIED_WINDSOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(DRIED_WINDS, ActivateDRIED_WINDSZone);
}

/* ponytail: TryActivateDRIED_WINDSOnOpponentTurnStart must be called from
 * turn_effect_hooks. Ceiling: body ready, not wired. */
