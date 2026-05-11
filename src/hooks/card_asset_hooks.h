#ifndef GUARD_SRC_HOOKS_CARD_ASSET_HOOKS_H
#define GUARD_SRC_HOOKS_CARD_ASSET_HOOKS_H

#include "global.h"

bool32 IsCustomCardId(u16 cardId);
const u8 *GetCardNameAsset(u16 cardId);
const void *GetBigCardArtAsset(u16 cardId);
const u16 *GetBigCardPaletteAsset(u16 cardId);
const u8 *GetMiniCardArtAsset(u16 cardId);

#endif // GUARD_SRC_HOOKS_CARD_ASSET_HOOKS_H
