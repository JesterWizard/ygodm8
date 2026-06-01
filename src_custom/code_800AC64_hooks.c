#include "global.h"
#include "configs/runtime.h"
#include "debug_ai_mode.h"
#include "player_decks.h"
#include "shiny_zones.h"

extern u8 *g8E0CD10;
int sub_80588C4(u8 *, int, int);
extern void (*g20245AC)(int, u8 *, int);

int sub_800AD84(void);
int sub_800ADA4(void);
void sub_800ADC4(void);
void sub_800ADF0(void);
void sub_800AE1C(void);
void sub_800AE70(void);
void sub_800AED0(void);
int sub_800B034(void);
int sub_800B050(void);
int sub_800B06C(void);
u8 sub_800B088(void);
int sub_800B0E4(void);
int sub_800B10C(void);
void InitNewGame(void);
void sub_800B0AC(u16);
void sub_800B0C8(u16);
void sub_800B1E4(void);
void sub_800B17C(void);
void sub_80351F8(void);
void sub_803519C(void);
u16 sub_8035170(void);
u16 sub_800B134(void);
u16 sub_800B158(void);

extern void SyncAllCustomTrunkCardQtyMirrorsToVanilla(void);
extern void SyncAllCustomTrunkCardQtyMirrorsFromVanilla(void);

static void SyncCustomCardQtyToFlashBuffers(void) {
  u16 i;

  SyncAllCustomTrunkCardQtyMirrorsFromVanilla();
  for (i = 0; i < NUM_CUSTOM_CARDS; i++) {
    gCustomShopCardQty[i] = gShopCardQty[CUSTOM_CARD_START + i];
    gCustomPlayerTempCardQty[i] = gPlayerTempCardQty[CUSTOM_CARD_START + i];
  }
}

static void SyncCustomCardQtyFromFlashBuffers(void) {
  u16 i;

  SyncAllCustomTrunkCardQtyMirrorsToVanilla();
  for (i = 0; i < NUM_CUSTOM_CARDS; i++) {
    gShopCardQty[CUSTOM_CARD_START + i] = gCustomShopCardQty[i];
    gPlayerTempCardQty[CUSTOM_CARD_START + i] = gCustomPlayerTempCardQty[i];
  }
}

static inline void Test(int a, u8 *b, int c) {
  g20245AC(a, b, c);
}

LYN_REPLACE_CHECK(sub_800AD84);
int sub_800AD84__Replacement(void) {
  int result = sub_80588C4(g8E0CD10, (int)gSaveSlotPrimary, 0x747);

  SyncCustomCardQtyToFlashBuffers();
  sub_80588C4(gCustomTrunkCardQty, (int)gCustomTrunkCardQtyFlashPrimary, NUM_CUSTOM_CARDS);
  sub_80588C4(gCustomShopCardQty, (int)gCustomShopCardQtyFlashPrimary, NUM_CUSTOM_CARDS);
  sub_80588C4(gCustomPlayerTempCardQty, (int)gCustomPlayerTempCardQtyFlashPrimary, NUM_CUSTOM_CARDS);
  ShinyZones_SaveFlagsToFlashPrimary();
  PlayerDecks_OnSaveSlotWrite();
  DebugAiMode_SaveToFlashPrimary();

  return result;
}

LYN_REPLACE_CHECK(sub_800ADA4);
int sub_800ADA4__Replacement(void) {
  int result = sub_80588C4(g8E0CD10, (int)gSaveSlotBackup, 0x747);

  SyncCustomCardQtyToFlashBuffers();
  sub_80588C4(gCustomTrunkCardQty, (int)gCustomTrunkCardQtyFlashBackup, NUM_CUSTOM_CARDS);
  sub_80588C4(gCustomShopCardQty, (int)gCustomShopCardQtyFlashBackup, NUM_CUSTOM_CARDS);
  sub_80588C4(gCustomPlayerTempCardQty, (int)gCustomPlayerTempCardQtyFlashBackup, NUM_CUSTOM_CARDS);
  ShinyZones_SaveFlagsToFlashBackup();
  PlayerDecks_OnSaveSlotWriteBackup();
  DebugAiMode_SaveToFlashBackup();

  return result;
}

LYN_REPLACE_CHECK(sub_800ADC4);
void sub_800ADC4__Replacement(void) {
  u8 *temp2 = g8E0CD10;
  int temp = (int)gSaveSlotPrimary;
  g20245AC(temp, temp2, 0x747);
  ShinyZones_LoadFlagsFromFlashPrimary();
  sub_803519C();
  PlayerDecks_OnSaveSlotRead();
  DebugAiMode_LoadFromFlashPrimary();
}

LYN_REPLACE_CHECK(sub_800ADF0);
void sub_800ADF0__Replacement(void) {
  u8 *temp2 = g8E0CD10;
  int temp = (int)gSaveSlotBackup;
  g20245AC(temp, temp2, 0x747);
  ShinyZones_LoadFlagsFromFlashBackup();
  sub_803519C();
  PlayerDecks_OnSaveSlotReadBackup();
  DebugAiMode_LoadFromFlashBackup();
}

LYN_REPLACE_CHECK(sub_800AE1C);
void sub_800AE1C__Replacement(void) {
  u16 temp;
  Test((int)gSaveSlotPrimary, g8E0CD10, 0x747);
  ShinyZones_LoadFlagsFromFlashPrimary();
  sub_803519C();
  PlayerDecks_OnSaveSlotRead();
  PlayerDecks_OnSaveSlotWriteBackup();
  temp = sub_800B134();
  sub_800B06C();
  sub_80588C4(g8E0CD10, (int)gSaveSlotBackup, 0x747);
  sub_800B0C8(temp);
  sub_800B034();
}

LYN_REPLACE_CHECK(sub_800AE70);
void sub_800AE70__Replacement(void) {
  u16 temp;
  Test((int)gSaveSlotBackup, g8E0CD10, 0x747);
  ShinyZones_LoadFlagsFromFlashBackup();
  sub_803519C();
  PlayerDecks_OnSaveSlotReadBackup();
  PlayerDecks_OnSaveSlotWrite();
  temp = sub_800B158();
  sub_800B050();
  sub_80588C4(g8E0CD10, (int)gSaveSlotPrimary, 0x747);
  sub_800B0AC(temp);
  sub_800B034();
}

LYN_REPLACE_CHECK(sub_800B0E4);
int sub_800B0E4__Replacement(void) {
  u16 checksum;

  g20245AC((int)gSaveSlotPrimary, g8E0CD10, 0x747);
  checksum = sub_8035170();
  return checksum == sub_800B134();
}

LYN_REPLACE_CHECK(sub_800B10C);
int sub_800B10C__Replacement(void) {
  u16 checksum;

  g20245AC((int)gSaveSlotBackup, g8E0CD10, 0x747);
  checksum = sub_8035170();
  return checksum == sub_800B158();
}

LYN_REPLACE_CHECK(sub_800AED0);
void sub_800AED0__Replacement(void) {
  u8 *ptr = g8E0CD10;
  int temp2 = (int)gSaveFlashPrimaryBase;
  u16 temp;

  CpuFill16(0, ptr, 0x2000);
  sub_80588C4(ptr, temp2, 0x2000);
  sub_80588C4(ptr, temp2 += 0x2000, 0x2000);
  sub_80588C4(ptr, temp2 += 0x2000, 0x2000);
  sub_80588C4(ptr, temp2 += 0x2000, 0x2000);
  InitNewGame();
  DebugAiMode_Reset();
  sub_80351F8();
  temp = sub_8035170();
  sub_800B050();
  sub_800AD84__Replacement();
  sub_800B0AC(temp);
  sub_800B06C();
  sub_800ADA4__Replacement();
  sub_800B0C8(temp);
  sub_800B1E4();
  sub_800B17C();
  sub_800B034();
}

LYN_REPLACE_CHECK(sub_800B034);
int sub_800B034__Replacement(void) {
  u8 fill = 0;
  int temp = (int)gSaveFlashPrimaryBase;
  return sub_80588C4(&fill, temp, 1);
}

LYN_REPLACE_CHECK(sub_800B050);
int sub_800B050__Replacement(void) {
  u8 fill = 1;
  int temp = (int)gSaveFlashPrimaryBase;
  return sub_80588C4(&fill, temp, 1);
}

LYN_REPLACE_CHECK(sub_800B06C);
int sub_800B06C__Replacement(void) {
  u8 fill = 2;
  int temp = (int)gSaveFlashPrimaryBase;
  return sub_80588C4(&fill, temp, 1);
}

LYN_REPLACE_CHECK(sub_800B088);
u8 sub_800B088__Replacement(void) {
  u8 temp;
  u32 a = (u32)gSaveFlashPrimaryBase;
  g20245AC(a, &temp, 1);
  return temp;
}
