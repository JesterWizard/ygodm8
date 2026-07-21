#include "global.h"
#include "common-chax.h"
#include "cold_wave.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static u8 sColdWaveLockActive APPEND_DATA = {0};
static u8 sColdWaveLockController APPEND_DATA = {0xFF};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

u8 ColdWave_CanActivateAtMainPhase1Start(u8 isMainPhase1Start, u8 priorMainPhaseActionThisTurn)
{
  if (!isMainPhase1Start)
    return FALSE;

  return priorMainPhaseActionThisTurn == FALSE;
}

u8 CanActivateCOLD_WAVE(void)
{
  return TRUE;
}

void ColdWave_ArmSpellTrapLock(void)
{
  sColdWaveLockActive = TRUE;
  sColdWaveLockController = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
}

u8 ColdWave_IsSpellTrapPlayOrSetLocked(void)
{
  return sColdWaveLockActive;
}

void ColdWave_ClearLockAtControllerStandby(u8 controllerFixedDuelist)
{
  if (!sColdWaveLockActive)
    return;

  if (sColdWaveLockController == controllerFixedDuelist) {
    sColdWaveLockActive = FALSE;
    sColdWaveLockController = 0xFF;
  }
}

void ColdWave_OnTurnBoundary(void)
{
  sColdWaveLockActive = FALSE;
  sColdWaveLockController = 0xFF;
}

static void COLD_WAVE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(COLD_WAVE);

  if (IsDuelOver() == TRUE)
    return;

  ColdWave_ArmSpellTrapLock();
  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectCOLD_WAVE(void)
{
  if (!CanActivateCOLD_WAVE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(COLD_WAVE, COLD_WAVE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void COLD_WAVE_SelfCheck(void)
{
  ColdWave_OnTurnBoundary();
  if (ColdWave_IsSpellTrapPlayOrSetLocked())
    while (1)
      ;
  ColdWave_ArmSpellTrapLock();
  if (!ColdWave_IsSpellTrapPlayOrSetLocked())
    while (1)
      ;
  ColdWave_ClearLockAtControllerStandby(DUEL_PLAYER);
  if (ColdWave_IsSpellTrapPlayOrSetLocked())
    while (1)
      ;
  if (!ColdWave_CanActivateAtMainPhase1Start(TRUE, FALSE))
    while (1)
      ;
  if (ColdWave_CanActivateAtMainPhase1Start(FALSE, FALSE))
    while (1)
      ;
  if (ColdWave_CanActivateAtMainPhase1Start(TRUE, TRUE))
    while (1)
      ;
}
#endif
