#include "global.h"
#include "configs/runtime.h"

extern const unsigned char gStarterTrunk[];
extern unsigned char gTrunkCardQty[];

LYN_REPLACE_CHECK(InitTrunkCards);
void InitTrunkCards__Replacement(void) {
  u32 id;

  for (id = 0; id < NUM_CARDS; id++) {
    if (gRuntimeConfig.start_with_three_copies_of_every_card == TRUE)
      gTrunkCardQty[id] = 3;
    else
      gTrunkCardQty[id] = gStarterTrunk[id];
  }
}
