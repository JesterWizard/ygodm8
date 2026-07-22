#include "global.h"
#include "on_summon_hooks.h"

void TryArcanaForceVTheHierophantOnMonsterPlacement(struct DuelCard *zone);
void TryArcanaForceXiiTheHangmanOnMonsterPlacement(struct DuelCard *zone);
void TryArcanaForceXixTheSunOnMonsterPlacement(struct DuelCard *zone);
void TryArcanaForceXvTheFiendOnMonsterPlacement(struct DuelCard *zone);
void TryArcanaForceITheMagicianOnMonsterPlacement(struct DuelCard *zone);
void TryBeastKingBarbarosOnTributeSummonDestroy(struct DuelCard *zone);
void TryManjuOfTheTenThousandHandsOnNormalSummon(struct DuelCard *zone, enum DuelSummonMode mode);
void TryTheAgentOfMysteruEarthOnNormalSummon(struct DuelCard *zone, enum DuelSummonMode mode);
void TryWhiteHornedDragonOnMonsterPlacement(struct DuelCard *zone);
void TryGreenGadgetOnMonsterPlacement(struct DuelCard *zone);
void TryDestinyHeroDrilldarkOnMonsterPlacement(struct DuelCard *zone);
void TryHeroKidOnMonsterPlacement(struct DuelCard *zone);
void TryDestinyHeroDreadmasterOnMonsterPlacement(struct DuelCard *zone);
void TryDestinyHeroDrawhandOnMonsterPlacement(struct DuelCard *zone);
void TryApprenticeIllusionMagicianOnMonsterPlacement(struct DuelCard *zone);
void TryGravekeepersHeadmanOnMonsterPlacement(struct DuelCard *zone);

void TryOnSummonPlacementHooks(struct DuelCard *zone, enum DuelSummonMode mode)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return;

  TryBeastKingBarbarosOnTributeSummonDestroy(zone);
  TryArcanaForceVTheHierophantOnMonsterPlacement(zone);
  TryArcanaForceXiiTheHangmanOnMonsterPlacement(zone);
  TryArcanaForceXixTheSunOnMonsterPlacement(zone);
  TryArcanaForceXvTheFiendOnMonsterPlacement(zone);
  TryArcanaForceITheMagicianOnMonsterPlacement(zone);
  TryManjuOfTheTenThousandHandsOnNormalSummon(zone, mode);
  TryTheAgentOfMysteruEarthOnNormalSummon(zone, mode);
  TryWhiteHornedDragonOnMonsterPlacement(zone);
  TryGreenGadgetOnMonsterPlacement(zone);
  TryDestinyHeroDrilldarkOnMonsterPlacement(zone);
  TryHeroKidOnMonsterPlacement(zone);
  TryDestinyHeroDreadmasterOnMonsterPlacement(zone);
  TryDestinyHeroDrawhandOnMonsterPlacement(zone);
  TryApprenticeIllusionMagicianOnMonsterPlacement(zone);
  TryGravekeepersHeadmanOnMonsterPlacement(zone);
}
