#include "global.h"
#include "configs/runtime.h"
#include "event_system.h"
#include "custom_decks/custom_decks.h"
#include "life_points.h"
#include "shiny_zones.h"
#include "text.h"
#include "overworld.h"

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

static const u8 sRegularDuelLossBytes[] APPEND_TEXT = {0x23, 0x39, 0x00};
static const u8 sRegularDuelLossEndBytes[] APPEND_TEXT = {0x5D};
static const u8 sRegularDuelReturnHomeLossBytes[] APPEND_TEXT = {
  0x23, 0x39,
  0x7C, 0x35, LOCATION_PLAYER_HOUSE_INSIDE, 0, 0, 0,
  0x00
};
static const struct Script sRegularDuelLossEndScript APPEND_RODATA = {
  (u8 *)sRegularDuelLossEndBytes,
  (struct Script *)&sRegularDuelLossEndScript,
  (struct Script *)&sRegularDuelLossEndScript
};
static const struct Script sRegularDuelReturnHomeLossScript APPEND_RODATA = {
  (u8 *)sRegularDuelReturnHomeLossBytes,
  (struct Script *)&sRegularDuelLossEndScript,
  (struct Script *)&sRegularDuelLossEndScript
};
static const struct Script sRegularDuelLossScript APPEND_RODATA = {
  (u8 *)sRegularDuelLossBytes,
  (struct Script *)&sRegularDuelLossEndScript,
  (struct Script *)&sRegularDuelLossEndScript
};

static u8 ScriptAdvanceOpcode(const u8 **cursor) {
  const u8 *p = *cursor;
  u8 op = *p;

  if (op == 0 || op == 0x5D)
    return FALSE;

  if (op == 0x23) {
    switch (p[1]) {
    case '4':
      *cursor = p + 6;
      return TRUE;
    case '0':
      *cursor = p + 3;
      return TRUE;
    case '1':
    case '3':
    case '5':
      *cursor = p + 2;
      return TRUE;
    case '2':
      *cursor = p + 3;
      return TRUE;
    case '6':
    case '8':
      *cursor = p + 3;
      return TRUE;
    case '7':
      *cursor = p + 3;
      return TRUE;
    case '9':
      *cursor = p + 2;
      return TRUE;
    default:
      *cursor = p + 2;
      return TRUE;
    }
  }

  if (op == 0x24) {
    *cursor = p + GetCurrentLanguageStringOffset(p);
    return TRUE;
  }

  if (op == 0x40) {
    switch (p[1]) {
    case '0':
    case '1':
      *cursor = p + 4;
      return TRUE;
    case '2':
      *cursor = p + 2;
      return TRUE;
    case '3':
    case '4':
    case '5':
    case '6':
      *cursor = p + 4;
      return TRUE;
    case '7':
    case '9':
      *cursor = p + 6;
      return TRUE;
    case '8':
      *cursor = p + 2;
      return TRUE;
    default:
      *cursor = p + 2;
      return TRUE;
    }
  }

  *cursor = p + 1;
  return TRUE;
}

static u8 ScriptContainsDuel(const struct Script *script) {
  const u8 *p;
  unsigned guard = 0;

  if (script == NULL || script->start == NULL)
    return FALSE;

  p = script->start;
  while (*p != 0 && *p != 0x5D && guard++ < 512) {
    if (*p == 0x40 && p[1] == '0')
      return TRUE;
    if (!ScriptAdvanceOpcode(&p))
      break;
  }

  return FALSE;
}

static void ReturnHomeAfterDuelDefeat(void) {
  FullyRestoreLifePoints();
  gOverworld.flags |= OVERWORLD_FLAG_MAP_TRANSITION;
  sub_80523EC(LOCATION_PLAYER_HOUSE_INSIDE, 0, 0);
}

static void InitiateRegularDuelScript(struct Script *script) {
  struct Script regularDuelScript = *script;
  u8 stayOnMapAfterDefeat = gRuntimeConfig.return_home_after_defeat == FALSE;
  u8 cardShopCustomDuel = CustomDecks_IsPendingCardShopDuel();

  if (ScriptContainsDuel(script) || cardShopCustomDuel == TRUE) {
    if (stayOnMapAfterDefeat)
      regularDuelScript.unk8 = (struct Script *)&sRegularDuelLossScript;
    else
      regularDuelScript.unk8 = (struct Script *)&sRegularDuelReturnHomeLossScript;
  }

  InitiateScript(&regularDuelScript);

  if (gDuelData.winner == DUEL_WINNER_OPPONENT) {
    if (stayOnMapAfterDefeat) {
      OverworldLoadGraphics();
    } else if (!(gOverworld.flags & OVERWORLD_FLAG_MAP_TRANSITION)) {
      if (cardShopCustomDuel == TRUE)
        ReturnHomeAfterDuelDefeat();
      else
        OverworldLoadGraphics();
    }
  }
}

static inline u8 sub_8052268_inline(int y, int x) {
  u8 temp = 0;
  if (y <= 0)
    if (y >= -8)
      temp = 1;
  if (x <= 4)
    if (x >= -4)
      temp |= 2;
  if (temp == 3)
    return 1;
  return 0;
}

static inline u8 sub_8052298_inline(int y, int x) {
  u8 temp = 0;
  if (x <= 8)
    if (x >= 0)
      temp = 1;
  if (y <= 4)
    if (y >= -4)
      temp |= 2;
  if (temp == 3)
    return 1;
  return 0;
}

static inline u8 sub_80522C0_inline(int y, int x) {
  u8 temp = 0;
  if (y <= 8)
    if (y >= 0)
      temp = 1;
  if (x <= 4)
    if (x >= -4)
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
  if (ShinyZones_TryInteract(temp, temp2, objId) == TRUE)
    return;
  if (objId == -1)
    return;

  PlayMusic(SFX_DIALOGUE);
  if (gOverworld.objects[objId].facePlayer)
    gOverworld.objects[objId].direction = sDirectionFacePlayer[gOverworld.objects[0].direction];
  sub_804F19C(objId);
  sub_804DF5C(objId);
  sub_804EF10();
  LoadObjVRAM();
  InitiateScript((struct Script *)EventSystem_ResolveScript(gOverworld.objects[objId].scriptA));
}

void TryDueling(void);

LYN_REPLACE_CHECK(TryDueling);
void TryDueling__Replacement(void) {
  int objId;
  u8 temp = gOverworld.objects[0].x + gHorizontalDisplacements[gOverworld.objects[0].direction];
  u8 temp2 = gOverworld.objects[0].y + g8E0E3CC[gOverworld.objects[0].direction];
  u8 cardShopDuelText[128];
  struct Script cardShopDuelScript;

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

  if (CustomDecks_IsEnabled() == TRUE &&
      CustomDecks_ShouldUseCardShopDuel(gOverworld.objects[objId].spriteId, gOverworld.map.id) == TRUE) {
    CustomDecks_SetPendingCardShopDuel(gOverworld.objects[objId].spriteId, gOverworld.map.id);
    cardShopDuelScript = CustomDecks_BuildCardShopDuelScript(
      cardShopDuelText,
      sizeof(cardShopDuelText),
      gOverworld.objects[objId].spriteId,
      gOverworld.map.id,
      EventSystem_ResolveScript(gOverworld.objects[objId].scriptR)
    );
    InitiateRegularDuelScript(&cardShopDuelScript);
  } else {
    CustomDecks_ClearPendingCardShopDuel();
    InitiateRegularDuelScript((struct Script *)EventSystem_ResolveScript(gOverworld.objects[objId].scriptR));
  }
}

u32 sub_805222C(u8, u8, u8);

LYN_REPLACE_CHECK(sub_8052088);
void sub_8052088__Replacement(u8 obj) {
  if (sub_805222C(0, gOverworld.objects[obj].x, gOverworld.objects[obj].y)) {
    u8 y = gOverworld.objects[obj].y;
    u8 x = gOverworld.objects[obj].x;
    u16 temp = gOverworld.unk23C[y * 120 + x];

    gOverworld.objects[obj].unk8 = (temp & 254) >> 1;
  }
}
