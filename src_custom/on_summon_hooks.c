#include "global.h"
#include "destiny_hero_dread_servant.h"
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
void TryBlackRoseDragonOnMonsterPlacement(struct DuelCard *zone);
void TryQuintetMagicianOnMonsterPlacement(struct DuelCard *zone);
void TryEvilHeroToxicBubbleOnMonsterPlacement(struct DuelCard *zone);
void TryGravekeepersCurseOnMonsterPlacement(struct DuelCard *zone);
void TryMoltenZombieOnMonsterPlacement(struct DuelCard *zone);
void TryDivinerOfTheHeraldOnMonsterPlacement(struct DuelCard *zone);
void TryDestinyHeroDystopiaOnMonsterPlacement(struct DuelCard *zone);
void TryDestinyHeroDiskCommanderOnMonsterPlacement(struct DuelCard *zone);

/* BATCH8 — Round 17 on-summon wires (append-only; unique Try* names). */
void TryElderEntityNordenOnMonsterPlacement(struct DuelCard *zone, enum DuelSummonMode mode);
void TryHarpieHarpistOnNormalSummon(struct DuelCard *zone, enum DuelSummonMode mode);
void TryDestinyHeroDreadnoughtMasterOnMonsterPlacement(struct DuelCard *zone,
                                                       enum DuelSummonMode mode);
void TryEvilHeroInfernalRiderOnMonsterPlacement(struct DuelCard *zone);
void TryLightswornDragonlingOnMonsterPlacement(struct DuelCard *zone, enum DuelSummonMode mode);
/* BATCH11 */
void TryMorphtronicEarfonOnMonsterPlacement(struct DuelCard *zone, enum DuelSummonMode mode);
/* BATCH12 — Round 17 on-summon search wires. */
void TryDarkMagicianGirlTheMagicianSApprenticeOnMonsterPlacement(struct DuelCard *zone);
void TryDarkMagicianGirlTheMagiciansApprenticeOnMonsterPlacement(struct DuelCard *zone);
void TryCrimsonDragonOnMonsterPlacement(struct DuelCard *zone, enum DuelSummonMode mode);
void TryElementalHeroSpiritOfNeosOnMonsterPlacement(struct DuelCard *zone,
                                                    enum DuelSummonMode mode);

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
  TryBlackRoseDragonOnMonsterPlacement(zone);
  TryQuintetMagicianOnMonsterPlacement(zone);
  TryEvilHeroToxicBubbleOnMonsterPlacement(zone);
  TryDestinyHeroDreadServantOnMonsterPlacement(zone, mode);
  TryGravekeepersCurseOnMonsterPlacement(zone);
  TryMoltenZombieOnMonsterPlacement(zone);
  TryDivinerOfTheHeraldOnMonsterPlacement(zone);
  TryDestinyHeroDystopiaOnMonsterPlacement(zone);
  TryDestinyHeroDiskCommanderOnMonsterPlacement(zone);

  /* BATCH8 */
  TryElderEntityNordenOnMonsterPlacement(zone, mode);
  TryHarpieHarpistOnNormalSummon(zone, mode);
  TryDestinyHeroDreadnoughtMasterOnMonsterPlacement(zone, mode);
  TryEvilHeroInfernalRiderOnMonsterPlacement(zone);
  TryLightswornDragonlingOnMonsterPlacement(zone, mode);
  /* BATCH11 */
  TryMorphtronicEarfonOnMonsterPlacement(zone, mode);
  /* BATCH12 */
  TryDarkMagicianGirlTheMagicianSApprenticeOnMonsterPlacement(zone);
  TryDarkMagicianGirlTheMagiciansApprenticeOnMonsterPlacement(zone);
  TryCrimsonDragonOnMonsterPlacement(zone, mode);
  TryElementalHeroSpiritOfNeosOnMonsterPlacement(zone, mode);
}
