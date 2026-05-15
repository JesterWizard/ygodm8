#include "global.h"
#include "configs/runtime.h"

void sub_8051A44(u8 obj, u8 direction, s16 *displacement);
void sub_8052088(u8 obj);
void sub_805236C (void);
void TryWalking (u8 direction);
void sub_804EEAC(struct OamData *arg0, u16 arg1);
void sub_804EE84(struct OamData *arg0, int arg1, int arg2);
extern struct OamData gOamBuffer[];

static void sub_8052108(u8 *arg0, u8 *arg1) {
  s8 sp[2];

  sub_804EEAC(gOamBuffer + 0, gOverworld.objects[0].unkC);
  sp[0] = (arg1[0] - arg0[0]) * 2;
  sp[1] = (arg1[1] - arg0[1]) * 2;
  sp[1] -= gOverworld.objects[0].unk8;
  sub_804EE84(gOamBuffer + 0, arg0[0] * 2 + sp[0], arg0[1] * 2 + sp[1]);
}

static void AdvancePlayerOneStep(u8 direction) {
  u8 pos[2];
  s16 displacement[4];

  pos[0] = gOverworld.objects[0].x;
  pos[1] = gOverworld.objects[0].y;
  gOverworld.objects[0].direction = direction;
  sub_8051A44(0, direction, displacement);
  gOverworld.objects[0].x += displacement[0];
  gOverworld.objects[0].y += displacement[1];
  sub_8052088(0);
  sub_8052108(pos, (u8 *)&gOverworld.objects[0].x);
}

LYN_REPLACE_CHECK(TryWalking);
void TryWalking__Replacement(u8 direction) {
  u8 i;
  u8 steps = gRuntimeConfig.faster_walking_speed;

  if (steps == 0)
    steps = 1;

  AdvancePlayerOneStep(direction);
  sub_805236C(); // check transitioning to a new map/the world map
  for (i = 1; i < steps && gOverworld.flags != OVERWORLD_FLAG_MAP_TRANSITION; i++) {
    if (gOverworld.objects[0].motionState != MOTION_WALKING)
      break;
    AdvancePlayerOneStep(direction);
    sub_805236C();
  }
  if (steps > 1 && gOverworld.objects[0].motionState == MOTION_WALKING)
    gOverworld.objects[0].motionState = MOTION_RUNNING;
}
