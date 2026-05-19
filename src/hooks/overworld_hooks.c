#include "global.h"
#include "configs/runtime.h"

extern struct OamData gOamBuffer[];
extern u16 gNewButtons;
extern u16 gPressedButtons;
extern u16 gRepeatedOrNewButtons;

void sub_804F1E4(void);
void sub_80551B8(void);

typedef void (*VoidFunc)(void);
typedef void (*VoidU8Func)(u8);

static inline void CallThumbVoid(u32 addr) {
  ((VoidFunc)(addr | 1))();
}

static inline void CallThumbVoidU8(u32 addr, u8 arg) {
  ((VoidU8Func)(addr | 1))(arg);
}

static const u8 sThoughtBubbleTilesDmp[] APPEND_ASSET = INCBIN_U8("src/hooks/assets/thought_bubbles/thought.dmp");
static const u16 sThoughtBubblePalette[] APPEND_ASSET = INCBIN_U16("src/hooks/assets/thought_bubbles/thought.gbapal");

static u16 *const sShowThoughtBubble = (u16 *)0x03001678;
NAKED
static void LZ77UnCompVram__Hook(const void *src, void *dest) {
  asm_unified("swi 0x12\n\
	bx lr");
}

enum {
  OVERWORLD_INPUT_NONE,
  OVERWORLD_INPUT_WALK_UP,
  OVERWORLD_INPUT_WALK_DOWN,
  OVERWORLD_INPUT_WALK_LEFT,
  OVERWORLD_INPUT_WALK_RIGHT,
  OVERWORLD_INPUT_TRY_DUELING,
  OVERWORLD_INPUT_TALK,
  OVERWORLD_INPUT_START_MENU,
  OVERWORLD_INPUT_RUN_UP = 11,
  OVERWORLD_INPUT_RUN_DOWN,
  OVERWORLD_INPUT_RUN_LEFT,
  OVERWORLD_INPUT_RUN_RIGHT
};

#define THOUGHT_BUBBLE_OAM_LEFT 126
#define THOUGHT_BUBBLE_OAM_RIGHT 127
#define THOUGHT_BUBBLE_TILE_NUM 0x300
#define THOUGHT_BUBBLE_VRAM 0x06016000
#define THOUGHT_BUBBLE_PALETTE_NUM 15
#define THOUGHT_BUBBLE_X 56
#define THOUGHT_BUBBLE_Y 48

static void LoadThoughtBubbleGfx(void) {
  LZ77UnCompVram__Hook(sThoughtBubbleTilesDmp, (void *)THOUGHT_BUBBLE_VRAM);
  CpuCopy16(sThoughtBubblePalette, gPaletteBuffer + 0x100 + THOUGHT_BUBBLE_PALETTE_NUM * 16, 0x20);
  CpuCopy16(sThoughtBubblePalette, (void *)(OBJ_PLTT + THOUGHT_BUBBLE_PALETTE_NUM * 0x20), 0x20);
}

static void SetThoughtBubbleOam(u8 visible) {
  u16 *oam = (u16 *)gOamBuffer;
  u16 left = THOUGHT_BUBBLE_OAM_LEFT * 4;
  u16 right = THOUGHT_BUBBLE_OAM_RIGHT * 4;
  u16 attr2 = THOUGHT_BUBBLE_TILE_NUM | (THOUGHT_BUBBLE_PALETTE_NUM << 12);

  if (visible) {
    oam[left] = THOUGHT_BUBBLE_Y;
    oam[left + 1] = THOUGHT_BUBBLE_X | 0xC000;
    oam[left + 2] = attr2;
    oam[left + 3] = 0;
    oam[right] = THOUGHT_BUBBLE_Y;
    oam[right + 1] = (THOUGHT_BUBBLE_X + 64) | 0xC000;
    oam[right + 2] = attr2 + 8;
    oam[right + 3] = 0;
  }
  else {
    oam[left] = 0xA0;
    oam[left + 1] = 0xF0;
    oam[left + 2] = 0xC00;
    oam[left + 3] = 0;
    oam[right] = 0xA0;
    oam[right + 1] = 0xF0;
    oam[right + 2] = 0xC00;
    oam[right + 3] = 0;
  }
}

/* LYN_REPLACEMENT(ProcessInput) */
u8 ProcessInput__Replacement(void) {
  if (gNewButtons & A_BUTTON)
    return OVERWORLD_INPUT_TALK;
  if (gRuntimeConfig.enable_world_map_thought_bubbles == TRUE && (gNewButtons & L_BUTTON)) {
    *sShowThoughtBubble ^= TRUE;
    PlayMusic(SFX_SELECT);
    return OVERWORLD_INPUT_NONE;
  }
  if (gNewButtons & R_BUTTON)
    return OVERWORLD_INPUT_TRY_DUELING;
  if (gPressedButtons & B_BUTTON) {
    if (gPressedButtons & DPAD_UP)
      return OVERWORLD_INPUT_RUN_UP;
    if (gPressedButtons & DPAD_DOWN)
      return OVERWORLD_INPUT_RUN_DOWN;
    if (gPressedButtons & DPAD_LEFT)
      return OVERWORLD_INPUT_RUN_LEFT;
    if (gPressedButtons & DPAD_RIGHT)
      return OVERWORLD_INPUT_RUN_RIGHT;
  }
  if (gPressedButtons & DPAD_UP)
    return OVERWORLD_INPUT_WALK_UP;
  if (gPressedButtons & DPAD_DOWN)
    return OVERWORLD_INPUT_WALK_DOWN;
  if (gPressedButtons & DPAD_LEFT)
    return OVERWORLD_INPUT_WALK_LEFT;
  if (gPressedButtons & DPAD_RIGHT)
    return OVERWORLD_INPUT_WALK_RIGHT;
  if (gRepeatedOrNewButtons & SELECT_BUTTON)
    return OVERWORLD_INPUT_START_MENU;
  if (gRepeatedOrNewButtons & START_BUTTON)
    return OVERWORLD_INPUT_START_MENU;
  return OVERWORLD_INPUT_NONE;
}

LYN_REPLACE_CHECK(sub_804EF10);
void sub_804EF10__Replacement(void) {
  CallThumbVoidU8(0x0804E518, 0);
  if (gOverworld.objects[13].unk1Dl)
    CallThumbVoidU8(0x0804E518, 13);
  if (gOverworld.objects[14].unk1Dl)
    CallThumbVoidU8(0x0804E518, 14);
  sub_80551B8();
  CallThumbVoid(0x0804E618);
  CallThumbVoid(0x0804EBE4);
  if (gRuntimeConfig.enable_world_map_thought_bubbles == TRUE && *sShowThoughtBubble == TRUE) {
    LoadThoughtBubbleGfx();
    SetThoughtBubbleOam(TRUE);
  }
  else
    SetThoughtBubbleOam(FALSE);
  SetVBlankCallback(sub_804F1E4);
  WaitForVBlank();
  CpuFastCopy(gBgVram.cbb4, (void *)0x06010000, 0x4000);
}
