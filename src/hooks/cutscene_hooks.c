#include "global.h"
#include "configs/runtime.h"

typedef void (*VoidFunc)(void);

static inline void CallThumbVoid(u32 addr) {
  ((VoidFunc)(addr | 1))();
}

LYN_REPLACE_CHECK(StartCutscene);
APPEND_TEXT void StartCutscene__Replacement (unsigned char cutscene) {
  switch (cutscene) {
    case 0:
      CallThumbVoid(0x080009BC);
      break;
    case 1:
      CallThumbVoid(0x08001C70);
      break;
    case 2:
      CreditsMain();
      break;
    case 3:
      CallThumbVoid(0x08001B88);
      break;
    case 4:
      CallThumbVoid(0x08001BFC);
      break;
    case 5:
      CallThumbVoid(0x08001CE4);
      break;
    case 6:
      CallThumbVoid(0x08001DD4);
      break;
    case 7:
      CallThumbVoid(0x08001D58);
      break;
    case 8:
      if (gRuntimeConfig.skip_opening_sequence == TRUE)
        SetFlag(0x8);
      else
        CallThumbVoid(0x08001AD8);
      break;
  }
  REG_DISPCNT = 0;
}
