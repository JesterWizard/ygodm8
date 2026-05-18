#include "global.h"
#include "configs/runtime.h"

extern u8 *g8E0CD10;
int sub_80588C4(u8 *, int, int);

void InitNewGame(void);
void sub_800AF68(void);
void sub_800B050(void);
void sub_800B0AC(u16);
void sub_800B06C(void);
void sub_800B0C8(u16);
void sub_800B1E4(void);
void sub_800B17C(void);
void sub_800B034(void);
void InitializeRandomizedCardCosts(void);

LYN_REPLACE_CHECK(sub_800AF68);
void sub_800AF68__Replacement(void) {
  u8 *ptr = g8E0CD10;
  int temp2 = 0xE000000;

  CpuFill16(0, ptr, 0x2000);
  sub_80588C4(ptr, temp2, 0x2000);
  sub_80588C4(ptr, temp2 += 0x2000, 0x2000);
  sub_80588C4(ptr, temp2 += 0x2000, 0x2000);
  sub_80588C4(ptr, temp2 += 0x2000, 0x2000);

  InitNewGame();
  InitializeRandomizedCardCosts();
  sub_800B050();
  sub_800B0AC(0xFFFF);
  sub_800B06C();
  sub_800B0C8(0xFFFF);
  sub_800B1E4();
  sub_800B17C();
  sub_800B034();
}
