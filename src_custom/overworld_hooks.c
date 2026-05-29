#include "global.h"
#include "configs/runtime.h"
#include "debug_menu.h"
#include "overworld_debug_overlay.h"
#include "thought_bubble.h"

#include "src_custom/thought_bubble_table.inc"

extern struct OamData gOamBuffer[];
extern u16 gNewButtons;
extern u16 gPressedButtons;
extern u16 gRepeatedOrNewButtons;

void sub_804F1E4(void);
void sub_80551B8(void);
void sub_804EC4C(void);
void OverworldSetRegDispcnt(void);
void sub_8045284(u16 *, u16, u16);

typedef void (*VoidFunc)(void);
typedef void (*VoidU8Func)(u8);

static inline void CallThumbVoid(u32 addr) {
  ((VoidFunc)(addr | 1))();
}

static inline void CallThumbVoidU8(u32 addr, u8 arg) {
  ((VoidU8Func)(addr | 1))(arg);
}

/* Same path as START_MENU -> OverworldLoadGraphics_inline(), not the overlay replacement. */
static void OverworldRestoreGraphicsAfterSubmenu(void) {
  REG_DISPCNT = 0;
  REG_BLDCNT = 0;
  CallThumbVoid(0x0804DCE8);
  CallThumbVoid(0x0804EDA0);
  CallThumbVoid(0x0804EDC8);
  CallThumbVoid(0x0804EDF0);
  CallThumbVoid(0x0804EE18);
  CallThumbVoid(0x0804EE6C);
  if (CheckFlag(0xF3))
    sub_8044E50(gPaletteBuffer, 0x10, 0x1FF);
  if (CheckFlag(0xF0))
    sub_8044EC8(gPaletteBuffer, 0x10, 0x1FF, 6);
  if (CheckFlag(0xEF))
    sub_8045284(gPaletteBuffer, 0x10, 0xFF);
  REG_BLDY = 7;
  WaitForVBlank();
  sub_804EC4C();
  REG_WINOUT = 0x3D3F;
  OverworldSetRegDispcnt();
}

static void OverworldRestoreAfterDebugMenu(void) {
  OverworldRestoreGraphicsAfterSubmenu();
  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_Refresh();
}

#define DECLARE_THOUGHT_BUBBLE_ASSET(symbol, tiles_path, palette_path) \
  static const u8 sThoughtBubble##symbol##TilesDmp[] APPEND_ASSET = \
      INCBIN_U8(tiles_path); \
  static const u16 sThoughtBubble##symbol##Palette[] APPEND_ASSET = \
      INCBIN_U16(palette_path);

#define DECLARE_THOUGHT_BUBBLE_ENUM(symbol, tiles_path, palette_path) THOUGHT_BUBBLE_##symbol,

#define DECLARE_THOUGHT_BUBBLE_ASSET_ENTRY(symbol, tiles_path, palette_path) \
  [THOUGHT_BUBBLE_##symbol] = { \
    .tilesDmp = sThoughtBubble##symbol##TilesDmp, \
    .palette = sThoughtBubble##symbol##Palette, \
  },

#define DECLARE_THOUGHT_BUBBLE_FLAG_ENTRY(flag, symbol) { flag, THOUGHT_BUBBLE_##symbol },

THOUGHT_BUBBLE_ASSET_LIST(DECLARE_THOUGHT_BUBBLE_ASSET)

static u16 *const sShowThoughtBubbles = (u16 *)0x03001678;
static u8 *const sSkipOverworldEndFrameAfterSubmenu = (u8 *)0x0300167A;
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

#define THOUGHT_BUBBLE_OAM_LEFT 65
#define THOUGHT_BUBBLE_OAM_RIGHT 66
#define THOUGHT_BUBBLE_TILE_NUM 0x300
#define THOUGHT_BUBBLE_VRAM 0x06016000
#define THOUGHT_BUBBLE_PALETTE_NUM 15
#define THOUGHT_BUBBLE_WIDTH 128
#define THOUGHT_BUBBLE_HEIGHT 64
#define THOUGHT_BUBBLE_X_OFFSET 64
#define THOUGHT_BUBBLE_Y_OFFSET 64
#define THOUGHT_BUBBLE_SCREEN_WIDTH 240
#define THOUGHT_BUBBLE_SCREEN_HEIGHT 160

enum {
  THOUGHT_BUBBLE_ASSET_LIST(DECLARE_THOUGHT_BUBBLE_ENUM)
  THOUGHT_BUBBLE_COUNT
};

struct ThoughtBubbleAsset {
  const u8 *tilesDmp;
  const u16 *palette;
};

struct ThoughtBubbleFlagMapping {
  u16 flag;
  u8 bubbleId;
};

static const struct ThoughtBubbleAsset sThoughtBubbleAssets[THOUGHT_BUBBLE_COUNT] APPEND_RODATA = {
  THOUGHT_BUBBLE_ASSET_LIST(DECLARE_THOUGHT_BUBBLE_ASSET_ENTRY)
};

static const struct ThoughtBubbleFlagMapping sThoughtBubbleFlagMappings[] APPEND_RODATA = {
  THOUGHT_BUBBLE_FLAG_LIST(DECLARE_THOUGHT_BUBBLE_FLAG_ENTRY)
};

#undef DECLARE_THOUGHT_BUBBLE_ASSET
#undef DECLARE_THOUGHT_BUBBLE_ENUM
#undef DECLARE_THOUGHT_BUBBLE_ASSET_ENTRY
#undef DECLARE_THOUGHT_BUBBLE_FLAG_ENTRY

static int ClampInt(int value, int min, int max) {
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

static u8 GetThoughtBubbleIdForFlag(u16 flag) {
  unsigned i;

  if (flag == THOUGHT_BUBBLE_EVENT_FLAG_NONE)
    return THOUGHT_BUBBLE_DEFAULT;

  for (i = 0; i < ARRAY_COUNT(sThoughtBubbleFlagMappings); i++) {
    if (sThoughtBubbleFlagMappings[i].flag == flag)
      return sThoughtBubbleFlagMappings[i].bubbleId;
  }

  return THOUGHT_BUBBLE_DEFAULT;
}

static const struct ThoughtBubbleAsset *GetThoughtBubbleAsset(void) {
  return &sThoughtBubbleAssets[GetThoughtBubbleIdForFlag(GetLatestThoughtBubbleEventFlag())];
}

static void LoadThoughtBubbleGfx(void) {
  const struct ThoughtBubbleAsset *asset = GetThoughtBubbleAsset();

  LZ77UnCompVram__Hook(asset->tilesDmp, (void *)THOUGHT_BUBBLE_VRAM);
  CpuCopy16(asset->palette, gPaletteBuffer + 0x100 + THOUGHT_BUBBLE_PALETTE_NUM * 16, 0x20);
  CpuCopy16(asset->palette, (void *)(OBJ_PLTT + THOUGHT_BUBBLE_PALETTE_NUM * 0x20), 0x20);
}

static void SetThoughtBubbleOam(u8 visible) {
  u16 *oam = (u16 *)gOamBuffer;
  u16 left = THOUGHT_BUBBLE_OAM_LEFT * 4;
  u16 right = THOUGHT_BUBBLE_OAM_RIGHT * 4;
  u16 attr2 = THOUGHT_BUBBLE_TILE_NUM | (THOUGHT_BUBBLE_PALETTE_NUM << 12);
  int playerY = gOverworld.objects[0].y * 2 - gOverworld.objects[0].unk8 + gOverworld.unk24C;
  int playerX = gOverworld.objects[0].x * 2 + gOverworld.unk24E;
  int bubbleY = playerY - THOUGHT_BUBBLE_Y_OFFSET - 10;
  int bubbleX = playerX - THOUGHT_BUBBLE_X_OFFSET - 8;
  int bubbleMaxX = THOUGHT_BUBBLE_SCREEN_WIDTH - THOUGHT_BUBBLE_WIDTH;
  int bubbleMaxY = THOUGHT_BUBBLE_SCREEN_HEIGHT - THOUGHT_BUBBLE_HEIGHT;

  bubbleX = ClampInt(bubbleX, 0, bubbleMaxX);
  bubbleY = ClampInt(bubbleY, 0, bubbleMaxY);

  if (visible) {
    oam[left] = bubbleY;
    oam[left + 1] = bubbleX | 0xC000;
    oam[left + 2] = attr2;
    oam[left + 3] = 0;
    oam[right] = bubbleY;
    oam[right + 1] = (bubbleX + THOUGHT_BUBBLE_WIDTH / 2) | 0xC000;
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
  if (gRuntimeConfig.enable_world_map_thought_bubbles == TRUE && *sShowThoughtBubbles == TRUE) {
    if (gNewButtons & L_BUTTON) {
      *sShowThoughtBubbles = FALSE;
      PlayMusic(SFX_SELECT);
    }
    return OVERWORLD_INPUT_NONE;
  }

  if (gNewButtons & A_BUTTON)
    return OVERWORLD_INPUT_TALK;
  if (gRuntimeConfig.enable_world_map_thought_bubbles == TRUE && (gNewButtons & L_BUTTON)) {
    *sShowThoughtBubbles = TRUE;
    PlayMusic(SFX_SELECT);
    return OVERWORLD_INPUT_NONE;
  }
  if (gNewButtons & R_BUTTON)
    return OVERWORLD_INPUT_TRY_DUELING;
  if (gRuntimeConfig.enable_debug_menu == TRUE && (gNewButtons & B_BUTTON) &&
      !(gPressedButtons & 0xF0)) {
    PlayMusic(SFX_SELECT);
    DebugMenuMain();
    OverworldRestoreAfterDebugMenu();
    PlayOverworldMusic();
    /* Match START_MENU: restore without running sub_804EF10 on this frame. */
    *sSkipOverworldEndFrameAfterSubmenu = 1;
    return OVERWORLD_INPUT_NONE;
  }
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
  if (*sSkipOverworldEndFrameAfterSubmenu) {
    *sSkipOverworldEndFrameAfterSubmenu = 0;
    SetVBlankCallback(sub_804F1E4);
    return;
  }

  CallThumbVoidU8(0x0804E518, 0);
  if (gOverworld.objects[13].unk1Dl)
    CallThumbVoidU8(0x0804E518, 13);
  if (gOverworld.objects[14].unk1Dl)
    CallThumbVoidU8(0x0804E518, 14);
  sub_80551B8();
  OverworldOverlay_PrepareFrame();
  CallThumbVoid(0x0804E618);
  CallThumbVoid(0x0804EBE4);
  if (gRuntimeConfig.enable_world_map_thought_bubbles == TRUE && *sShowThoughtBubbles == TRUE) {
    LoadThoughtBubbleGfx();
    SetThoughtBubbleOam(TRUE);
  }
  else
    SetThoughtBubbleOam(FALSE);
  SetVBlankCallback(sub_804F1E4);
  WaitForVBlank();
  CpuFastCopy(gBgVram.cbb4, (void *)0x06010000, 0x4000);
  OverworldOverlay_CommitFrame();
}
