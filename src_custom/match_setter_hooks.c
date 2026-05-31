#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "match_setter.h"
#include "overworld.h"

void sub_804F3E4(void);
void sub_8052088(u8);

typedef void (*MatchSetterVoidU8Func)(u8);

static inline void MatchSetterCallThumbU8(u32 addr, u8 arg) {
  ((MatchSetterVoidU8Func)(addr | 1))(arg);
}

static const struct MatchSetterEntry sMatchSetterEntries[] APPEND_RODATA = {
#include "generated/match_setter_table_generated.inc"
};

#undef MATCH_SETTER_TABLE_ENTRY

extern u8 gDebugMatchSetterSelection;

void MatchSetter_Init(void) {
  /* Selection of 0 means none; no separate init flag needed for IWRAM. */
}

const struct MatchSetterEntry *MatchSetter_GetEntry(u8 index) {
  if (index >= MATCH_SETTER_ENTRY_COUNT)
    return NULL;
  return &sMatchSetterEntries[index];
}

u8 MatchSetter_GetEntryCount(void) {
  return MATCH_SETTER_ENTRY_COUNT;
}

void MatchSetter_ApplySpawn(void) {
  const struct MatchSetterEntry *entry;
  struct Object *obj;

  if (gRuntimeConfig.enable_debug_menu != TRUE)
    return;
  if (gOverworld.map.id != LOCATION_PLAYER_HOUSE_OUTSIDE)
    return;

  obj = &gOverworld.objects[MATCH_SETTER_OBJECT_SLOT];
  if (gDebugMatchSetterSelection == DEBUG_MATCH_SETTER_NONE) {
    obj->spriteId = SPRITE_NONE;
    sub_8052088(MATCH_SETTER_OBJECT_SLOT);
    return;
  }

  entry = MatchSetter_GetEntry(gDebugMatchSetterSelection - 1);
  if (entry == NULL)
    return;

  obj->spriteId = entry->spriteId;
  obj->direction = DIRECTION_DOWN;
  obj->x = MATCH_SETTER_SPAWN_X;
  obj->y = MATCH_SETTER_SPAWN_Y;
  obj->unk8 = 0;
  obj->unkA = 0;
  obj->unkC = 0;
  obj->unkE = 19;
  obj->unkF = 0;
  obj->scriptA = entry->scriptA;
  obj->scriptR = entry->scriptR;
  obj->motionState = MOTION_STATIONARY;
  obj->unk1A = 0;
  obj->unk1C = 0;
  obj->hasShadow = 1;
  obj->facePlayer = 1;
  obj->wander = 0;
  obj->unk1Dl = 0;
  obj->enableBlending = 0;
  obj->unk1E = 19;
  sub_8052088(MATCH_SETTER_OBJECT_SLOT);
}

void MatchSetter_RefreshField(void) {
  MatchSetter_ApplySpawn();
  if (gOverworld.map.id != LOCATION_PLAYER_HOUSE_OUTSIDE)
    return;
  MatchSetterCallThumbU8(0x0804E518, MATCH_SETTER_OBJECT_SLOT);
  MatchSetterCallThumbU8(0x0804E518, 0);
}

void sub_804F714(void);

/* LYN_REPLACEMENT(sub_804F714) */
LYN_REPLACE_CHECK(sub_804F714);
void sub_804F714__Replacement(void) {
  int i;

  for (i = 0; i < 10; i++)
    sub_804F3E4();
  for (i = 0; i < 2; i++) {
    if (gOverworld.objects[i + 13].unk1Dl) {
      gOverworld.objects[i + 13].direction = gOverworld.objects[0].direction;
      gOverworld.objects[i + 13].unkE = 19;
    }
  }
  MatchSetter_ApplySpawn();
}
