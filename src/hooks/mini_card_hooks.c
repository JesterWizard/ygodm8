#include "global.h"
#include "configs/runtime.h"
#include "src/hooks/card_asset_hooks.h"

extern unsigned char *gUnk_8E17F48[];
extern unsigned char gSharedMem[];

#define VanillaCopyMiniCardTiles ((void (*)(void *, unsigned char *, unsigned char *))0x080565F1)
#define VanillaCopyShopCardBorderTiles ((void (*)(unsigned char *, unsigned char *, unsigned char *))0x08056C55)

LYN_REPLACE_CHECK(sub_80573D0);
APPEND_TEXT void sub_80573D0__Replacement(void *dest, unsigned short cardId) {
  SetCardInfo(cardId);
  LZ77UnCompWram(GetMiniCardArtAsset(cardId), gSharedMem);
  VanillaCopyMiniCardTiles(dest, gSharedMem, gUnk_8E17F48[gCardInfo.color]);
}

LYN_REPLACE_CHECK(sub_805742C);
APPEND_TEXT void sub_805742C__Replacement(unsigned char *dest, unsigned short cardId) {
  SetCardInfo(cardId);
  LZ77UnCompWram(GetMiniCardArtAsset(cardId), gSharedMem);
  VanillaCopyShopCardBorderTiles(dest, gSharedMem, gUnk_8E17F48[gCardInfo.color]);
}
