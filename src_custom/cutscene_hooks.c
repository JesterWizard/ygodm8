#include "global.h"
#include "configs/runtime.h"
#include "cutscene.h"

void ReshefVisionMain(void);
void sub_8001AD8(void);
void sub_8001B88(void);
void sub_8001BFC(void);
void sub_8001C70(void);
void sub_8001CE4(void);
void sub_8001D58(void);
void sub_8001DD4(void);

/* No CallThumb into statics — MyBoy dies on that pattern. */
LYN_REPLACE_CHECK(StartCutscene);
APPEND_TEXT void StartCutscene__Replacement(unsigned char cutscene) {
  switch (cutscene) {
    case 0:
      ReshefVisionMain();
      break;
    case 1:
      sub_8001C70();
      break;
    case 2:
      CreditsMain();
      break;
    case 3:
      sub_8001B88();
      break;
    case 4:
      sub_8001BFC();
      break;
    case 5:
      sub_8001CE4();
      break;
    case 6:
      sub_8001DD4();
      break;
    case 7:
      sub_8001D58();
      break;
    case 8:
      if (gRuntimeConfig.skip_opening_sequence == TRUE)
        SetFlag(0x8);
      else
        sub_8001AD8();
      break;
  }
  REG_DISPCNT = 0;
}
