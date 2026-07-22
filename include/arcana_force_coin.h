#ifndef GUARD_ARCANA_FORCE_COIN_H
#define GUARD_ARCANA_FORCE_COIN_H

#include "global.h"

struct DuelCard;

/* Heads=1. Tails must not be 2 — InitMonsterZone marks Special Summons with unk4=2. */
#define ARCANA_FORCE_COIN_HEADS 1
#define ARCANA_FORCE_COIN_TAILS 3

static inline u8 ArcanaForce_CoinPending(const struct DuelCard *zone)
{
  if (zone == NULL)
    return FALSE;
  return zone->unk4 != ARCANA_FORCE_COIN_HEADS
      && zone->unk4 != ARCANA_FORCE_COIN_TAILS;
}

/* Stores coin on zone and shows a Heads/Tails duel popup (skipped when gHideEffectText). */
void ArcanaForce_SetCoin(struct DuelCard *zone, u8 heads);

/* Popup only — for flips that do not store on the zone. */
void ArcanaForce_AnnounceCoinResult(u16 cardId, u8 heads);

/* Sets gActiveEffect to zone, then Activate*() — for on-summon when permanent scan
 * did not run (Special Summon helper) or as a no-op backup after NS permanent. */
void ArcanaForce_RunSummonCoinIfPending(struct DuelCard *zone, u16 cardId,
                                        void (*activate)(void));

void TryArcanaForceOnSummonCoinHooks(struct DuelCard *zone);

#endif /* GUARD_ARCANA_FORCE_COIN_H */
