#include "global.h"
#include "configs/runtime.h"
#include "src/hooks/card_asset_hooks.h"

extern u8 *gCardNames[];
extern u32 *gCardArts[];
extern u16 *gCardArtPalettes[];
extern u8 *g8E17F70[];

typedef struct CustomCardAsset {
  const u8 *name;
  const void *bigArt;
  const u16 *bigPalette;
  const u8 *miniArt;
} CustomCardAsset;

static const u8 gSorcererOfDarkMagicName[] APPEND_RODATA =
  "$0Sorcerer of Dark Magic"
  "$1Sorcerer of Dark Magic"
  "$2Sorcerer of Dark Magic"
  "$3Sorcerer of Dark Magic"
  "$4Sorcerer of Dark Magic"
  "$6";

static const u8 gSorcererOfDarkMagicBigArt[] APPEND_ASSET =
  INCBIN_U8("src/hooks/assets/cards/formatted/801_sorcerer_of_dark_magic_80x80.huff");
static const u16 gSorcererOfDarkMagicBigPalette[] APPEND_ASSET =
  INCBIN_U16("src/hooks/assets/cards/formatted/801_sorcerer_of_dark_magic_80x80.gbapal");
static const u8 gSorcererOfDarkMagicMiniArt[] APPEND_ASSET =
  INCBIN_U8("src/hooks/assets/cards/formatted/801_sorcerer_of_dark_magic_24x24.lz");

/*
 * Add custom card assets here. Keep the binary asset files under:
 *   src/hooks/assets/cards/
 *
 * Expected formats:
 *   big art: same encoded format used by gCardArts[]
 *   big palette: 16-color .gbapal data
 *   mini art: LZ77-compressed mini-card tile data
 *
 * Example:
 * static const u8 MyCardBigArt[] = INCBIN_U8("src/hooks/assets/cards/my_card_big_art.bin");
 * static const u16 MyCardBigPalette[] = INCBIN_U16("src/hooks/assets/cards/my_card.gbapal");
 * static const u8 MyCardMiniArt[] = INCBIN_U8("src/hooks/assets/cards/my_card_mini.lz");
 *
 * [MY_CARD_ID - CUSTOM_CARD_START] = {
 *   .name = (const u8 *)gMyCardName,
 *   .bigArt = MyCardBigArt,
 *   .bigPalette = MyCardBigPalette,
 *   .miniArt = MyCardMiniArt,
 * },
 */

#if NUM_CUSTOM_CARDS > 0
static const CustomCardAsset sCustomCardAssets[NUM_CUSTOM_CARDS] APPEND_RODATA = {
  [SORCERER_OF_DARK_MAGIC - CUSTOM_CARD_START] = {
    .name = gSorcererOfDarkMagicName,
    .bigArt = gSorcererOfDarkMagicBigArt,
    .bigPalette = gSorcererOfDarkMagicBigPalette,
    .miniArt = gSorcererOfDarkMagicMiniArt,
  },
};
#else
static const CustomCardAsset sCustomCardAssets[1] APPEND_RODATA = {
  {0}
};
#endif

APPEND_TEXT bool32 IsCustomCardId(u16 cardId) {
  if (cardId < CUSTOM_CARD_START)
    return FALSE;
  if (cardId >= NUM_CARDS)
    return FALSE;
  return TRUE;
}

static APPEND_TEXT const CustomCardAsset *GetCustomCardAsset(u16 cardId) {
  if (!IsCustomCardId(cardId))
    return NULL;

  return &sCustomCardAssets[cardId - CUSTOM_CARD_START];
}

APPEND_TEXT const u8 *GetCardNameAsset(u16 cardId) {
  const CustomCardAsset *asset = GetCustomCardAsset(cardId);

  if (asset != NULL && asset->name != NULL)
    return asset->name;

  return gCardNames[cardId];
}

APPEND_TEXT const void *GetBigCardArtAsset(u16 cardId) {
  const CustomCardAsset *asset = GetCustomCardAsset(cardId);

  if (asset != NULL && asset->bigArt != NULL)
    return asset->bigArt;

  return gCardArts[cardId];
}

APPEND_TEXT const u16 *GetBigCardPaletteAsset(u16 cardId) {
  const CustomCardAsset *asset = GetCustomCardAsset(cardId);

  if (asset != NULL && asset->bigPalette != NULL)
    return asset->bigPalette;

  return gCardArtPalettes[cardId];
}

APPEND_TEXT const u8 *GetMiniCardArtAsset(u16 cardId) {
  const CustomCardAsset *asset = GetCustomCardAsset(cardId);

  if (asset != NULL && asset->miniArt != NULL)
    return asset->miniArt;

  return g8E17F70[cardId];
}
