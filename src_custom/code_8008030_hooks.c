#include "global.h"
#include "common-chax.h"
#include "timed_duel.h"

extern vu16 g2020E00;
extern void (*g201CB20)(void);
extern void sub_800842C(void);
extern void sub_80082E8(void);

void WaitForVBlank(void);

LYN_REPLACE_CHECK(WaitForVBlank);
void WaitForVBlank__Replacement(void) {
  g2020E00 &= 0xFFFE;
  while (1) {
    if (g2020E00 & 1)
      break;
  }
  g201CB20 = sub_800842C;
  sub_80082E8();
  TimedDuel_OnVBlank();
}
