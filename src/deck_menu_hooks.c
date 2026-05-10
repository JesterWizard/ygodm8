#include "global.h"
#include "configs/runtime.h"

extern unsigned gDuelistLevel;

LYN_REPLACE_CHECK(InitDuelistLevel);
void InitDuelistLevel__Replacement(void) {
  gDuelistLevel = 72;

  if (gRuntimeConfig.max_duelist_level_at_start == TRUE)
    gDuelistLevel = 999;
}
