#include "global.h"

static const unsigned char sSorcererOfDarkMagicBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/80x80/sorcerer_of_dark_magic.huff");
static const unsigned short sSorcererOfDarkMagicBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src/hooks/assets/cards/80x80/sorcerer_of_dark_magic.gbapal");
static const unsigned char sSorcererOfDarkMagicMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/24x24/sorcerer_of_dark_magic.lz");

static const unsigned char sDeckDestructionVirusBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/80x80/deck_destruction_virus.huff");
static const unsigned short sDeckDestructionVirusBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src/hooks/assets/cards/80x80/deck_destruction_virus.gbapal");
static const unsigned char sDeckDestructionVirusMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/24x24/deck_destruction_virus.lz");

static const unsigned char sMagiciansValkyriaBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/80x80/magicians_valkyria.huff");
static const unsigned short sMagiciansValkyriaBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src/hooks/assets/cards/80x80/magicians_valkyria.gbapal");
static const unsigned char sMagiciansValkyriaMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/24x24/magicians_valkyria.lz");

static const unsigned char sBlueEyesShiningDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/80x80/blue_eyes_shining_dragon.huff");
static const unsigned short sBlueEyesShiningDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src/hooks/assets/cards/80x80/blue_eyes_shining_dragon.gbapal");
static const unsigned char sBlueEyesShiningDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/24x24/blue_eyes_shining_dragon.lz");

static const unsigned char sPaladinOfWhiteDragonBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/80x80/paladin_of_white_dragon.huff");
static const unsigned short sPaladinOfWhiteDragonBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src/hooks/assets/cards/80x80/paladin_of_white_dragon.gbapal");
static const unsigned char sPaladinOfWhiteDragonMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/24x24/paladin_of_white_dragon.lz");

static const unsigned char sCardOfDemiseBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/80x80/card_of_demise.huff");
static const unsigned short sCardOfDemiseBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src/hooks/assets/cards/80x80/card_of_demise.gbapal");
static const unsigned char sCardOfDemiseMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/24x24/card_of_demise.lz");

static const unsigned char sCardOfSanctityBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/80x80/card_of_sanctity.huff");
static const unsigned short sCardOfSanctityBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src/hooks/assets/cards/80x80/card_of_sanctity.gbapal");
static const unsigned char sCardOfSanctityMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/24x24/card_of_sanctity.lz");

static const unsigned char sShieldAndSwordBigArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/80x80/shield_and_sword.huff");
static const unsigned short sShieldAndSwordBigPalette[] __attribute__((section(".append_assets"))) = INCBIN_U16("src/hooks/assets/cards/80x80/shield_and_sword.gbapal");
static const unsigned char sShieldAndSwordMiniArt[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/24x24/shield_and_sword.lz");

const unsigned char *gCardArts_Hook[] APPEND_RODATA = {
  [0x0321] = sSorcererOfDarkMagicBigArt,
  [0x0322] = sDeckDestructionVirusBigArt,
  [0x0323] = sMagiciansValkyriaBigArt,
  [0x0324] = sBlueEyesShiningDragonBigArt,
  [0x0325] = sPaladinOfWhiteDragonBigArt,
  [0x0326] = sCardOfDemiseBigArt,
  [0x0327] = sCardOfSanctityBigArt,
  [0x0328] = sShieldAndSwordBigArt,
};

const unsigned short *gCardArtPalettes_Hook[] APPEND_RODATA = {
  [0x0321] = sSorcererOfDarkMagicBigPalette,
  [0x0322] = sDeckDestructionVirusBigPalette,
  [0x0323] = sMagiciansValkyriaBigPalette,
  [0x0324] = sBlueEyesShiningDragonBigPalette,
  [0x0325] = sPaladinOfWhiteDragonBigPalette,
  [0x0326] = sCardOfDemiseBigPalette,
  [0x0327] = sCardOfSanctityBigPalette,
  [0x0328] = sShieldAndSwordBigPalette,
};

const unsigned char *gMiniCardArts_Hook[] APPEND_RODATA = {
  [0x0321] = sSorcererOfDarkMagicMiniArt,
  [0x0322] = sDeckDestructionVirusMiniArt,
  [0x0323] = sMagiciansValkyriaMiniArt,
  [0x0324] = sBlueEyesShiningDragonMiniArt,
  [0x0325] = sPaladinOfWhiteDragonMiniArt,
  [0x0326] = sCardOfDemiseMiniArt,
  [0x0327] = sCardOfSanctityMiniArt,
  [0x0328] = sShieldAndSwordMiniArt,
};
