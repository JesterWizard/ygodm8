#include "global.h"
#include "configs/runtime.h"
#include "duel.h"
#include "gba/m4a_internal.h"

#define M4A_TEMPO_UNITY 0x100

extern struct MusicPlayerInfo g2025840;

static void ApplyM4aTempoMultiplier(struct MusicPlayerInfo *mplayInfo, u16 tempoU) {
  if (mplayInfo->ident != ID_NUMBER)
    return;

  mplayInfo->ident++;
  mplayInfo->tempoU = tempoU;
  mplayInfo->tempoI = (mplayInfo->tempoD * mplayInfo->tempoU) >> 8;
  mplayInfo->ident = ID_NUMBER;
}

static u16 GetDesiredTempoU(u8 wantBoost) {
  u16 speedPercent;

  if (!wantBoost)
    return M4A_TEMPO_UNITY;

  speedPercent = gRuntimeConfig.increase_bgm_tempo_speed_percent;
  if (speedPercent < 100)
    speedPercent = 100;

  return (M4A_TEMPO_UNITY * speedPercent) / 100;
}

void UpdateDuelBgmTempoForLifePoints(void) {
  u16 threshold = gRuntimeConfig.increase_bgm_tempo_when_lp_at_or_below;
  u16 desiredTempoU;
  u16 expectedTempoI;
  u8 wantBoost;

  if (threshold == 0)
    return;

  if (g2025840.ident != ID_NUMBER)
    return;

  wantBoost = gDuelLifePoints[DUEL_PLAYER] <= threshold;
  desiredTempoU = GetDesiredTempoU(wantBoost);
  expectedTempoI = (g2025840.tempoD * desiredTempoU) >> 8;

  if (g2025840.tempoU == desiredTempoU && g2025840.tempoI == expectedTempoI)
    return;

  ApplyM4aTempoMultiplier(&g2025840, desiredTempoU);
}
