#include "global.h"

static const unsigned char sDeckDestructionVirusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/80x80/deck_destruction_virus_80x80.huff");
static const unsigned short sDeckDestructionVirusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src/hooks/assets/cards/80x80/deck_destruction_virus_80x80.gbapal");
static const unsigned char sDeckDestructionVirusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/24x24/deck_destruction_virus_24x24.lz");

static const unsigned char sMagiciansValkyriaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/80x80/magicians_valkyria_80x80.huff");
static const unsigned short sMagiciansValkyriaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src/hooks/assets/cards/80x80/magicians_valkyria_80x80.gbapal");
static const unsigned char sMagiciansValkyriaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/24x24/magicians_valkyria_24x24.lz");

static const unsigned char sSorcererOfDarkMagicBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/80x80/sorcerer_of_dark_magic_80x80.huff");
static const unsigned short sSorcererOfDarkMagicBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src/hooks/assets/cards/80x80/sorcerer_of_dark_magic_80x80.gbapal");
static const unsigned char sSorcererOfDarkMagicMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/24x24/sorcerer_of_dark_magic_24x24.lz");

const unsigned char *gCardArts_Hook[] APPEND_RODATA = {
  [0x0322] = sDeckDestructionVirusBigArt,
  [0x0323] = sMagiciansValkyriaBigArt,
  [0x0321] = sSorcererOfDarkMagicBigArt,
};

const unsigned short *gCardArtPalettes_Hook[] APPEND_RODATA = {
  [0x0322] = sDeckDestructionVirusBigPalette,
  [0x0323] = sMagiciansValkyriaBigPalette,
  [0x0321] = sSorcererOfDarkMagicBigPalette,
};
