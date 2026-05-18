#include "global.h"
#include "configs/runtime.h"

static const enum Direction sDirectionFacePlayer[] APPEND_RODATA = {
  [DIRECTION_DOWN] = DIRECTION_UP,
  [DIRECTION_LEFT] = DIRECTION_RIGHT,
  [DIRECTION_UP] = DIRECTION_DOWN,
  [DIRECTION_RIGHT] = DIRECTION_LEFT
};

static const signed short gHorizontalDisplacements[] APPEND_RODATA = {
  [DIRECTION_DOWN] = 0,
  [DIRECTION_LEFT] = -1,
  [DIRECTION_UP] = 0,
  [DIRECTION_RIGHT] = 1
};

static const signed short g8E0E3CC[] APPEND_RODATA = {
  [DIRECTION_DOWN] = 1,
  [DIRECTION_LEFT] = 0,
  [DIRECTION_UP] = -1,
  [DIRECTION_RIGHT] = 0
};

static inline u8 sub_8052268_inline(int y, int x) {
  u8 temp = 0;
  if (x <= 0)
    if (x >= -4)
      temp = 1;
  if (y <= 0)
    if (y >= -8)
      temp |= 2;
  if (temp == 3)
    return 1;
  return 0;
}

static inline u8 sub_8052298_inline(int y, int x) {
  u8 temp = 0;
  if (x <= 4)
    if (x >= -4)
      temp = 1;
  if (y <= 0)
    if (y >= -8)
      temp |= 2;
  if (temp == 3)
    return 1;
  return 0;
}

static inline u8 sub_80522C0_inline(int y, int x) {
  u8 temp = 0;
  if (x <= 0)
    if (x >= -4)
      temp = 1;
  if (y <= 4)
    if (y >= -4)
      temp |= 2;
  if (temp == 3)
    return 1;
  return 0;
}

static inline u8 sub_80522E8_inline(int y, int x) {
  u8 temp = 0;
  if (x <= 0)
    if (x >= -8)
      temp = 1;
  if (y <= 4)
    if (y >= -4)
      temp |= 2;
  if (temp == 3)
    return 1;
  return 0;
}

static s8 GetObjectIdInFrontOfPlayer(u8 x, u8 y, u8 playerDirection) {
  u8 i, objExists;

  for (i = 1; i < 15; i++) {
    switch (playerDirection) {
      case 0:
        objExists = sub_8052268_inline(y - gOverworld.objects[i].y, x - gOverworld.objects[i].x);
        break;
      case 1:
        objExists = sub_8052298_inline(y - gOverworld.objects[i].y, x - gOverworld.objects[i].x);
        break;
      case 2:
        objExists = sub_80522C0_inline(y - gOverworld.objects[i].y, x - gOverworld.objects[i].x);
        break;
      default:
        objExists = sub_80522E8_inline(y - gOverworld.objects[i].y, x - gOverworld.objects[i].x);
        break;
    }
    if (objExists)
      return i;
  }
  return -1;
}

void sub_804EEAC(struct OamData *arg0, u16 arg1);
void sub_804EE84(struct OamData *arg0, int arg1, int arg2);
extern struct OamData gOamBuffer[];
void sub_8051A44(u8, u8, s16 *);
void sub_8052088(u8);

static void sub_8052108(u8 *arg0, u8 *arg1) {
  s8 sp[2];

  sub_804EEAC(gOamBuffer + 0, gOverworld.objects[0].unkC);
  sp[0] = (arg1[0] - arg0[0]) * 2;
  sp[1] = (arg1[1] - arg0[1]) * 2;
  sp[1] -= gOverworld.objects[0].unk8;
  sub_804EE84(gOamBuffer + 0, arg0[0] * 2 + sp[0], arg0[1] * 2 + sp[1]);
}

void sub_805236C(void);
void TryWalking(u8);

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

static const u8 sTeaCardShopDuelText[] APPEND_TEXT = {
  0x23, 0x34, 7, 0x00, PORTRAIT_POSITION_AUTO,
  'I', ' ', 'm', 'a', 'd', 'e', ' ', 'a', ' ', 'd', 'e', 'c', 'k', '.',
  0x23, 0x30,
  'L', 'e', 't', '\'', 's', ' ', 'd', 'u', 'e', 'l', '.',
  0x23, 0x31, '@', '0', 0x0A, 0x00
};

static int IsCustomTeaTalk(void) {
  if (gRuntimeConfig.enable_custom_decks != TRUE)
    return 0;
  if (gOverworld.map.id != LOCATION_CARD_SHOP_INSIDE)
    return 0;
  return 1;
}

LYN_REPLACE_CHECK(TryWalking);
void TryWalking__Replacement(u8 direction) {
  u8 i;
  u8 steps = gRuntimeConfig.faster_walking_speed;

  if (steps == 0)
    steps = 1;

  AdvancePlayerOneStep(direction);
  sub_805236C();
  for (i = 1; i < steps && gOverworld.flags != OVERWORLD_FLAG_MAP_TRANSITION; i++) {
    if (gOverworld.objects[0].motionState != MOTION_WALKING)
      break;
    AdvancePlayerOneStep(direction);
    sub_805236C();
  }
  if (steps > 1 && gOverworld.objects[0].motionState == MOTION_WALKING)
    gOverworld.objects[0].motionState = MOTION_RUNNING;
}

void TryTalking(void);

LYN_REPLACE_CHECK(TryTalking);
void TryTalking__Replacement(void) {
  int objId;
  u8 temp = gOverworld.objects[0].x + gHorizontalDisplacements[gOverworld.objects[0].direction];
  u8 temp2 = gOverworld.objects[0].y + g8E0E3CC[gOverworld.objects[0].direction];

  objId = GetObjectIdInFrontOfPlayer(temp, temp2, gOverworld.objects[0].direction);
  if (objId == -1)
    return;

  PlayMusic(SFX_DIALOGUE);
  if (gOverworld.objects[objId].facePlayer)
    gOverworld.objects[objId].direction = sDirectionFacePlayer[gOverworld.objects[0].direction];
  sub_804F19C(objId);
  sub_804DF5C(objId);
  sub_804EF10();
  LoadObjVRAM();
  InitiateScript(gOverworld.objects[objId].scriptA);
}

void TryDueling(void);

LYN_REPLACE_CHECK(TryDueling);
void TryDueling__Replacement(void) {
  int objId;
  u8 temp = gOverworld.objects[0].x + gHorizontalDisplacements[gOverworld.objects[0].direction];
  u8 temp2 = gOverworld.objects[0].y + g8E0E3CC[gOverworld.objects[0].direction];

  objId = GetObjectIdInFrontOfPlayer(temp, temp2, gOverworld.objects[0].direction);
  if (objId == -1)
    return;

  PlayMusic(SFX_DIALOGUE);
  if (gOverworld.objects[objId].facePlayer)
    gOverworld.objects[objId].direction = sDirectionFacePlayer[gOverworld.objects[0].direction];
  sub_804F19C(objId);
  sub_804DF5C(objId);
  sub_804EF10();
  LoadObjVRAM();

  if (gOverworld.objects[objId].spriteId == SPRITE_TEA && IsCustomTeaTalk()) {
    struct Script teaCardShopDuelScript = {
      (u8 *)sTeaCardShopDuelText,
      gOverworld.objects[objId].scriptR,
      gOverworld.objects[objId].scriptR
    };
    InitiateScript(&teaCardShopDuelScript);
  } else {
    InitiateScript(gOverworld.objects[objId].scriptR);
  }
}
