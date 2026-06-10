#include "global.h"
#include "configs/runtime.h"
#include "cg.h"
#include "duel.h"
#include "overworld.h"

extern u16 g82ADC8C[];
extern u16 *g8E11CD0[];
extern const u32 g82AD2D0[];
extern u16 g82AD48C[];
extern struct OamData gOamBuffer[];

extern u8 gCgSessionOpen;
extern u8 gCgActive;
extern u8 gCgFadeSpeed;
extern u8 gCgId;
extern u16 gCgSavedDispcnt;

#define CG_TILE_BYTES 0x9600
#define CG_PAL_BG_OFFSET 32
#define CG_PAL_BG_COUNT 224
#define CG_PAL_BG_BYTE_SIZE (CG_PAL_BG_COUNT * sizeof(u16))
#define CG_MAP_WIDTH 30
#define CG_MAP_HEIGHT 20
#define CG_DEFAULT_FADE_SPEED 8
#define CG_TEXTBOX_CHAR_BYTES 0xE20
#define CG_TEXT_WINDOW_BLDCNT 0xDE
#define CG_TEXT_WINDOW_BLDY 7
#define CG_BG2CNT \
  (BGCNT_PRIORITY(2) | BGCNT_CHARBASE(0) | BGCNT_256COLOR | BGCNT_SCREENBASE(31))

enum {
  CG_OP_COMPATIBLE,
  CG_OP_TEXT,
  CG_OP_ENDING,
};

#include "generated/event_cg_assets_generated.inc"

typedef void (*ScriptCtxFunc)(struct ScriptCtx *);

static void EventCg_GetAsset(u8 cgId, const u8 **tiles, const u16 **palette);

static u8 EventCg_NormalizeFadeSpeed(u8 speed) {
  return speed ? speed : CG_DEFAULT_FADE_SPEED;
}

static void EventCg_LoadTextPalettes(void) {
  CpuCopy16(g82ADC8C, gPaletteBuffer, 0x20);
  CpuCopy16(&g8E11CD0[gOverworld.map.id][8], gPaletteBuffer + 0x20, 0x20);
}

static void EventCg_ApplyCgPalette(const u16 *palette) {
  if (palette == NULL)
    return;

  EventCg_LoadTextPalettes();
  CpuFill16(0, gPaletteBuffer + CG_PAL_BG_OFFSET, CG_PAL_BG_BYTE_SIZE);
  CpuCopy16(palette + CG_PAL_BG_OFFSET, gPaletteBuffer + CG_PAL_BG_OFFSET,
            CG_PAL_BG_BYTE_SIZE);
}

static void EventCg_RefreshPalettes(void) {
  const u8 *tiles;
  const u16 *palette;

  if (!gCgActive || gCgId == CG_NONE || gCgId >= gEventCgTableCount)
    return;

  EventCg_GetAsset(gCgId, &tiles, &palette);
  EventCg_ApplyCgPalette(palette);
}

static void EventCg_FlushBackgroundPalette(void) {
  EventCg_LoadTextPalettes();
  CpuFill16(0, gPaletteBuffer + CG_PAL_BG_OFFSET, CG_PAL_BG_BYTE_SIZE);
  LoadPalettes();
  WaitForVBlank();
}

static void EventCg_InitTextboxCharTiles(void) {
  LZ77UnCompWram(g82AD2D0, gVramBuffer + 0xD800);
}

static void EventCg_LoadTextboxBg(void) {
  REG_BG0CNT = 0x1D0C;
  gBG0VOFS = 0;
  gBG0HOFS = 8;
  EventCg_InitTextboxCharTiles();
  CpuCopy16(g82AD48C, gVramBuffer + 0xE800, 0x500);
}

static void EventCg_PushTextboxVram(void) {
  CpuCopy16(g82AD48C, gVramBuffer + 0xE800, 0x500);
  CpuCopy32(gBgVram.sbb1B, (void *)0x0600D800, CG_TEXTBOX_CHAR_BYTES);
  CpuCopy16(gVramBuffer + 0xE800, (void *)0x0600E800, 0x500);
}

static void EventCg_SuppressAllSprites(void) {
  u8 i;

  for (i = 0; i < 128; i++)
    sub_80411EC(&gOamBuffer[i]);
}

static void EventCg_RefreshPortraitOam(struct ScriptCtx *scriptCtx) {
  struct OamData *oam;

  if (scriptCtx->portraitId == PORTRAIT_NONE)
    return;

  oam = gOamBuffer;
  sub_804EB04(oam, scriptCtx->unk85);
  oam->paletteNum = 12;
  if (CheckFlag(0xF3))
    sub_8044E50(gPaletteBuffer, 0x1C0, 0x1FF);
}

static void EventCg_WaitFrames(u8 count) {
  u8 i;

  for (i = 0; i < count; i++) {
    if (gCgSessionOpen && gCgActive)
      EventCg_SuppressAllSprites();
    LoadBgOffsets();
    SetVBlankCallback(LoadBgOffsets);
    WaitForVBlank();
    if (gCgSessionOpen && gCgActive) {
      EventCg_RefreshPalettes();
      LoadPalettes();
    }
    LoadOam();
  }
}

static void EventCg_FadeLayer(bool8 fadeIn, u8 speed, u16 blendTargets) {
  int i;

  REG_BLDCNT = blendTargets | BLDCNT_EFFECT_DARKEN;
  REG_WINOUT = 0x3D3E;

  if (fadeIn) {
    for (i = 16; i >= 0; i--) {
      REG_BLDY = i;
      EventCg_WaitFrames(speed);
    }
    REG_BLDCNT = 0;
    REG_BLDY = 0;
  } else {
    for (i = 0; i <= 16; i++) {
      REG_BLDY = i;
      EventCg_WaitFrames(speed);
    }
  }
}

static void EventCg_FadeToBlack(u8 speed) {
  int i, temp;

  REG_BLDCNT = 0xFF;
  REG_WINOUT = 0x3D3E;
  for (i = 0; i <= 16; i++) {
    REG_BLDY = i;
    for (temp = speed; temp; temp--)
      sub_804F218();
  }
}

static void EventCg_FadeCg(bool8 fadeIn, u8 speed) {
  EventCg_FadeLayer(fadeIn, speed, BLDCNT_TGT1_BG2);
}

static void EventCg_BuildTilemap(void) {
  u16 x, y, tile;

  for (y = 0; y < CG_MAP_HEIGHT; y++) {
    tile = y * CG_MAP_WIDTH + (CG_MAP_WIDTH - 1);
    for (x = 0; x < CG_MAP_WIDTH; x++) {
      gBgVram.sbb1F[y][x] = y * CG_MAP_WIDTH + x;
    }
    gBgVram.sbb1F[y][CG_MAP_WIDTH] = tile;
    gBgVram.sbb1F[y][CG_MAP_WIDTH + 1] = tile;
  }
}

static void EventCg_SyncBg2Vram(void) {
  const u8 *tiles;
  const u16 *palette;

  if (!gCgActive || gCgId == CG_NONE || gCgId >= gEventCgTableCount)
    return;

  EventCg_GetAsset(gCgId, &tiles, &palette);
  if (tiles == NULL)
    return;

  CpuCopy16(tiles, (void *)BG_CHAR_ADDR(0), CG_TILE_BYTES);
  CpuCopy16(gBgVram.sbb1F, (void *)BG_SCREEN_ADDR(31), BG_SCREEN_SIZE);
}

static void EventCg_ApplyCgBgRegs(void) {
  REG_BG2CNT = CG_BG2CNT;
  gBG2VOFS = 0;
  gBG2HOFS = 0;
  LoadBgOffsets();
}

static void EventCg_ApplyTextWindowRegsInternal(struct ScriptCtx *scriptCtx) {
  u16 dispcnt = DISPCNT_BG0_ON | DISPCNT_BG2_ON | DISPCNT_WIN1_ON;

  EventCg_ApplyCgBgRegs();
  REG_BG0CNT = 0x1D0C;
  gBG0VOFS = 0;
  gBG0HOFS = 8;
  EventCg_PushTextboxVram();
  REG_WIN1H = 0x03ED;
  REG_WIN1V = 0x739D;
  (*(vu8 *)(REG_BASE + 0x49)) = 0x3F;
  REG_WINOUT = 0x1D1E;
  if (scriptCtx != NULL && scriptCtx->portraitId != PORTRAIT_NONE)
    dispcnt |= DISPCNT_OBJ_ON;
  REG_DISPCNT = dispcnt;
  REG_BLDCNT = CG_TEXT_WINDOW_BLDCNT;
  REG_BLDY = CG_TEXT_WINDOW_BLDY;
}

void EventCg_ApplyTextWindowRegs(struct ScriptCtx *scriptCtx) {
  EventCg_ApplyTextWindowRegsInternal(scriptCtx);
}

void EventCg_ApplyPortraitSceneRegs(struct ScriptCtx *scriptCtx) {
  if (scriptCtx->unk86 == 1) {
    EventCg_ApplyTextWindowRegsInternal(scriptCtx);
  } else if (scriptCtx->portraitId != PORTRAIT_NONE) {
    REG_DISPCNT = DISPCNT_BG2_ON | DISPCNT_OBJ_ON;
    REG_BLDCNT = 0;
    REG_BLDY = 0;
    REG_WINOUT = 0x3D3E;
  }
}

static void EventCg_GetAsset(u8 cgId, const u8 **tiles, const u16 **palette) {
  EventCg_GetAssetFromTable(cgId, tiles, palette);
}

static void EventCg_LoadGraphics(u8 cgId) {
  const u8 *tiles;
  const u16 *palette;

  if (cgId == CG_NONE || cgId >= gEventCgTableCount)
    return;

  EventCg_GetAsset(cgId, &tiles, &palette);
  if (tiles == NULL || palette == NULL)
    return;

  CpuCopy32(tiles, gBgVram.cbb0, CG_TILE_BYTES);
  EventCg_ApplyCgPalette(palette);
  CpuFill16(0, gBgVram.sbb1F, BG_SCREEN_SIZE);
  EventCg_BuildTilemap();
  EventCg_ApplyCgBgRegs();
  EventCg_SyncBg2Vram();
  EventCg_LoadTextboxBg();
  LoadPalettes();
  WaitForVBlank();
  EventCg_RefreshPalettes();
  LoadPalettes();
  EventCg_PushTextboxVram();
}

static void EventCg_HideAllSprites(void) {
  EventCg_SuppressAllSprites();
  LoadOam();
  WaitForVBlank();
}

static void EventCg_ApplyCgDisplay(void) {
  gCgSavedDispcnt = REG_DISPCNT;
  EventCg_HideAllSprites();
  EventCg_FlushBackgroundPalette();
  REG_DISPCNT = DISPCNT_BG2_ON;
  REG_BLDCNT = BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_DARKEN;
  REG_BLDY = 16;
  REG_WINOUT = 0x3D3E;
}

static void EventCg_RestoreOverworldDisplay(void) {
  OverworldLoadGraphics();
  OverworldSetRegDispcnt();
  REG_BLDCNT = 0;
  REG_BLDY = 0;
}

static u8 EventCg_ClassifyOpcode(const u8 *script, u32 pointer) {
  u8 op = script[pointer];

  if (op == 0 || op == 0x5D)
    return CG_OP_ENDING;

  switch (op) {
  case 0x24:
    return CG_OP_TEXT;
  case 0x23:
    switch (script[pointer + 1]) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '5':
      return CG_OP_TEXT;
    case '4':
      return CG_OP_COMPATIBLE;
    default:
      return CG_OP_ENDING;
    }
  case 0x7C:
    switch (script[pointer + 1]) {
    case '1':
    case '3':
    case '6':
    case '7':
    case '9':
    case 'A':
      return CG_OP_COMPATIBLE;
    default:
      return CG_OP_ENDING;
    }
  case 0x5E:
    switch (script[pointer + 1]) {
    case '4':
    case '6':
      return CG_OP_COMPATIBLE;
    default:
      return CG_OP_ENDING;
    }
  case 0x40:
    return CG_OP_ENDING;
  default:
    if (op & 0x80)
      return CG_OP_TEXT;
    if (op >= ' ' && op <= 'z')
      return CG_OP_TEXT;
    return CG_OP_ENDING;
  }
}

static void EventCg_CloseSession(void) {
  u8 speed;

  if (!gCgSessionOpen)
    return;

  speed = EventCg_NormalizeFadeSpeed(gCgFadeSpeed);
  if (gCgActive)
    EventCg_FadeCg(FALSE, speed);

  EventCg_RestoreOverworldDisplay();
  gCgSessionOpen = FALSE;
  gCgActive = FALSE;
  gCgId = CG_NONE;
}

static void EventCg_TryCloseSessionBeforeOpcode(struct ScriptCtx *scriptCtx) {
  if (!gCgSessionOpen)
    return;

  if (EventCg_ClassifyOpcode(scriptCtx->currentScript.start, scriptCtx->pointer) == CG_OP_ENDING)
    EventCg_CloseSession();
}

bool8 EventCg_IsSessionOpen(void) {
  return gCgSessionOpen;
}

bool8 EventCg_IsActive(void) {
  return gCgActive;
}

void EventCg_HandleDisplayOpcode(struct ScriptCtx *scriptCtx, u8 cgId, u8 fadeSpeed) {
  u8 speed;

  if (cgId == CG_NONE || cgId >= gEventCgTableCount)
    return;

  speed = EventCg_NormalizeFadeSpeed(fadeSpeed);
  gCgFadeSpeed = speed;

  if (!gCgSessionOpen)
    EventCg_FadeToBlack(speed);
  else if (gCgActive)
    EventCg_FadeCg(FALSE, speed);

  gCgSessionOpen = TRUE;
  gCgId = cgId;
  gCgActive = TRUE;

  EventCg_LoadGraphics(cgId);
  EventCg_ApplyCgDisplay();
  EventCg_RefreshPalettes();
  LoadPalettes();
  WaitForVBlank();
  EventCg_FadeCg(TRUE, speed);
}

void EventCg_HandleHideOpcode(struct ScriptCtx *scriptCtx, u8 fadeSpeed) {
  u8 speed;

  if (!gCgSessionOpen || !gCgActive)
    return;

  speed = EventCg_NormalizeFadeSpeed(fadeSpeed);
  gCgFadeSpeed = speed;
  EventCg_FadeCg(FALSE, speed);
  EventCg_RestoreOverworldDisplay();
  gCgActive = FALSE;
  gCgSessionOpen = FALSE;
  gCgId = CG_NONE;
}

bool8 EventCg_TryConsumeDisplayOpcode(struct ScriptCtx *scriptCtx) {
  const u8 *script = scriptCtx->currentScript.start;
  u32 pointer = scriptCtx->pointer;

  if (script[pointer] != 0x7C || script[pointer + 1] != '9')
    return FALSE;

  EventCg_HandleDisplayOpcode(scriptCtx, script[pointer + 2], script[pointer + 3]);
  scriptCtx->pointer += 4;
  return TRUE;
}

bool8 EventCg_TryConsumeHideOpcode(struct ScriptCtx *scriptCtx) {
  const u8 *script = scriptCtx->currentScript.start;
  u32 pointer = scriptCtx->pointer;

  if (script[pointer] != 0x7C || script[pointer + 1] != 'A')
    return FALSE;

  EventCg_HandleHideOpcode(scriptCtx, script[pointer + 2]);
  scriptCtx->pointer += 3;
  return TRUE;
}

void EventCg_BeforeExecuteOpcode(struct ScriptCtx *scriptCtx) {
  if (scriptCtx->unkC != 0)
    return;

  EventCg_TryCloseSessionBeforeOpcode(scriptCtx);
}

void EventCg_AfterExecuteOpcode(struct ScriptCtx *scriptCtx) {
  (void)scriptCtx;
}

void EventCg_OnTextWaitComplete(struct ScriptCtx *scriptCtx) {
  (void)scriptCtx;

  if (!gCgActive)
    return;

  EventCg_InitTextboxCharTiles();
  EventCg_SyncBg2Vram();
  EventCg_ApplyCgBgRegs();
}

void EventCg_OnScriptFrameEnd(struct ScriptCtx *scriptCtx) {
  if (!gCgSessionOpen || !gCgActive)
    return;

  EventCg_SuppressAllSprites();
  EventCg_RefreshPortraitOam(scriptCtx);
  EventCg_ApplyPortraitSceneRegs(scriptCtx);
  SetVBlankCallback(LoadBgOffsets);
  WaitForVBlank();
  EventCg_SyncBg2Vram();
  EventCg_ApplyCgBgRegs();
  EventCg_PushTextboxVram();
  EventCg_RefreshPalettes();
  LoadPalettes();
  LoadOam();
}

void EventCg_ForceClose(void) {
  EventCg_CloseSession();
}
