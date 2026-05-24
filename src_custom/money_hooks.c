#include "global.h"
#include "configs/runtime.h"

#define MAX_MONEY 9999999999999ULL

extern u64 gMoney;

LYN_REPLACE_CHECK(InitMoney);
void InitMoney__Replacement(void) {
  gMoney = 500;

  if (gRuntimeConfig.max_money_at_start == TRUE)
    gMoney = MAX_MONEY;
}
