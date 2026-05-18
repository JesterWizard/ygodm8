#include "common-chax.h"

s16 GetTalkingUnitSprite(void)
{
  void *playerDirection_raw = (void *)0x02024282;
  void *x_raw = (void *)0x02024284;
  void *y_raw = (void *)0x02024286;
  s8 objId;
  u8 playerDirection = *(volatile u8 *)playerDirection_raw;
  u8 x = *(volatile u8 *)x_raw;
  u8 y = *(volatile u8 *)y_raw;

  objId = GetObjectIdInFrontOfPlayer(x, y, playerDirection);
  if (objId < 0)
    return -1;

  return gOverworld.objects[objId].spriteId;
}
