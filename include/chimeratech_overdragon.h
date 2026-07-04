#ifndef GUARD_CHIMERATECH_OVERDRAGON_H
#define GUARD_CHIMERATECH_OVERDRAGON_H

#include "duel.h"

u8 ChimeratechOverdragon_ApplyDynamicZoneStats(struct DuelCard *zone);
void ChimeratechOverdragon_OnFusionSummoned(u8 materialCount);
void ClearChimeratechOverdragonBoardStatsForZone(struct DuelCard *zone);
void ClearChimeratechOverdragonAttacksUsed(void);
void ClearChimeratechOverdragonState(void);
void TryUnlockChimeratechOverdragonForNextAttack(struct DuelCard *attacker);
u8 ChimeratechOverdragon_BlocksDirectAttack(const struct DuelCard *zone);
u16 ChimeratechOverdragon_EstimateAtk(u8 materialCount);

#endif // GUARD_CHIMERATECH_OVERDRAGON_H
