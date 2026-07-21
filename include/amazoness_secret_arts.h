#ifndef GUARD_AMAZONESS_SECRET_ARTS_H
#define GUARD_AMAZONESS_SECRET_ARTS_H

#include "fusion_duel.h"
#include "global.h"

/* gyIndex = FUSION_EXTRA_SLOT_BASE + extraDeckSlot for Extra Deck materials. */
#define FUSION_EXTRA_SLOT_BASE 0x80

u8 CanActivateAmazonessSecretArtsGy(u8 fixedDuelist, u8 gyIndex);
void ActivateAmazonessSecretArtsGy(u8 fixedDuelist, u8 gyIndex);

u8 AmazonessSecretArts_ExtraMaterialActive(void);
void AmazonessSecretArts_ClearExtraMaterial(void);
u8 AmazonessSecretArts_AppendExtraDeckSources(struct FusionMaterialSource *out, u8 count,
                                              u8 maxOut);
u8 AmazonessSecretArts_IsExtraDeckSource(const struct FusionMaterialSource *src);
void AmazonessSecretArts_PayExtraDeckSource(const struct FusionMaterialSource *src);

#endif /* GUARD_AMAZONESS_SECRET_ARTS_H */
