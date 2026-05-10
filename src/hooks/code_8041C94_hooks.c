#include "global.h"
#include "configs/runtime.h"

extern unsigned short g8E0D5A6[];

void sub_8041D78(u8 arg0);
void sub_8041DF0(u8 arg0);
void sub_8057808(void);
void sub_804078C(void);
void sub_8040FDC(void);

LYN_REPLACE_CHECK(sub_8041D78);
void sub_8041D78__Replacement(u8 arg0) {
  if (gRuntimeConfig.turn_off_visual_scanner == TRUE) {
    gBG2VOFS = g8E0D5A6[arg0];
    sub_8057808();
    sub_804078C();
    WaitForVBlank();
    sub_8040FDC();
    return;
  }

  while (gBG2VOFS > g8E0D5A6[arg0] + 256) {
    gBG2VOFS -= 256;
    sub_8057808();
    WaitForVBlank();
    sub_8040FDC();
  }
  gBG2VOFS = g8E0D5A6[arg0];
  sub_8057808();
  sub_804078C();
  WaitForVBlank();
  sub_8040FDC();
}

LYN_REPLACE_CHECK(sub_8041DF0);
void sub_8041DF0__Replacement(u8 arg0) {
  if (gRuntimeConfig.turn_off_visual_scanner == TRUE) {
    gBG2VOFS = g8E0D5A6[arg0];
    sub_8057808();
    sub_804078C();
    WaitForVBlank();
    sub_8040FDC();
    return;
  }

  while (gBG2VOFS < g8E0D5A6[arg0] - 256) {
    gBG2VOFS += 256;
    sub_8057808();
    WaitForVBlank();
    sub_8040FDC();
  }
  gBG2VOFS = g8E0D5A6[arg0];
  sub_8057808();
  sub_804078C();
  WaitForVBlank();
  sub_8040FDC();
}
