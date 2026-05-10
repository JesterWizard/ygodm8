#include "global.h"
#include "configs/runtime.h"

extern unsigned gDeckCapacity;
extern unsigned gDuelistLevel;

LYN_REPLACE_CHECK(InitDeckCapacity);
void InitDeckCapacity__Replacement(void) {
  gDeckCapacity = 1600;

  if (gRuntimeConfig.max_deck_capacity_at_start == TRUE)
    gDeckCapacity = 65000;
}

LYN_REPLACE_CHECK(InitDuelistLevel);
void InitDuelistLevel__Replacement(void) {
  gDuelistLevel = 72;

  if (gRuntimeConfig.max_duelist_level_at_start == TRUE)
    gDuelistLevel = 999;
}
