#include "global.h"
#include "configs/runtime.h"
#include "debug_save_anywhere.h"
#include "debug_menu.h"
#include "gba/io_reg.h"
#include "gfx_reg_buffers.h"
#include "overworld.h"
#include "overworld_debug_overlay.h"
#include "text.h"
#include "maps_custom.h"

void sub_804F1E4(void);
void sub_804EC4C(void);
void sub_804ECA8(void);
void sub_804EC64(void);
void sub_804EEE0(void);
void sub_804F218(void);
void sub_8053E34(u8);
void LoadBgOffsets(void);
void LoadOam(void);
void sub_80551B8(void);
void LoadObjVRAM(void);
void LoadPalettes(void);
void LoadVRAM(void);
void LoadDuelIconGfx(void);
void OverworldSetRegDispcnt(void);
void sub_8045284(u16 *, u16, u16);
void sub_8052088(u8);

extern const u32 g82AD2D0[];
extern u16 g82AD48C[];
extern const u16 g82ADC8C[];

typedef void (*VoidFunc)(void);

static inline void CallThumbVoid(u32 addr) {
  ((VoidFunc)(addr | 1))();
}

// Overworld BG0 textbox/font: gVramBuffer + 0xD800 (tiles), + 0xE800 (= gBgVram.sbb1D tilemap).
#define OVERWORLD_BG0_CHARBUF_OFFSET 0xE680
#define OVERWORLD_BG0_TILEMAP_OFFSET 0xE800

#define OVERLAY_BASE_TILE_ID 0x134
#define OVERLAY_MAX_CHARS 12
#define OVERLAY_CHARBUF_SIZE (OVERLAY_MAX_CHARS * 32)

#define OVERLAY_ROW 1
#define OVERLAY_COL 2

static int ClampInt(int value, int min, int max) {
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

static void UploadOverworldBg0Base(void) {
  CpuCopy32(gBgVram.sbb1B, (void *)0x0600D800, 0xE20);
  CpuCopy16(gVramBuffer + OVERWORLD_BG0_TILEMAP_OFFSET, (void *)0x0600E800, 0x500);
}

static void ClearOverlayTilemap(void) {
  u16 *tilemap = (u16 *)(gVramBuffer + OVERWORLD_BG0_TILEMAP_OFFSET);
  u16 attrs = tilemap[OVERLAY_ROW * 32 + OVERLAY_COL] & 0xFC00;
  int i;

  for (i = 0; i < OVERLAY_MAX_CHARS; i++)
    tilemap[OVERLAY_ROW * 32 + OVERLAY_COL + i] = (u16)(attrs | 0xC0);
}

static char *AppendSignedInt(char *out, int value) {
  char tmp[12];
  unsigned u;
  int n = 0;
  int i;

  if (value < 0) {
    *out++ = '-';
    u = (unsigned)(-value);
  } else {
    u = (unsigned)value;
  }

  do {
    tmp[n++] = (char)('0' + (u % 10));
    u /= 10;
  } while (u && n < (int)sizeof(tmp));

  for (i = n - 1; i >= 0; i--)
    *out++ = tmp[i];

  return out;
}

static void WriteOverlayString(const char *str) {
  u16 *tilemap = (u16 *)(gVramBuffer + OVERWORLD_BG0_TILEMAP_OFFSET);
  u16 attrs = tilemap[OVERLAY_ROW * 32 + OVERLAY_COL] & 0xFC00;
  int i;

  CopyStringTilesToVRAMBuffer(
      gVramBuffer + OVERWORLD_BG0_CHARBUF_OFFSET,
      (const u8 *)str,
      0x001);

  for (i = 0; i < OVERLAY_MAX_CHARS; i++) {
    if (str[i] == '\0')
      break;
    tilemap[OVERLAY_ROW * 32 + OVERLAY_COL + i] = (u16)(attrs | (OVERLAY_BASE_TILE_ID + i));
  }
  for (; i < OVERLAY_MAX_CHARS; i++)
    tilemap[OVERLAY_ROW * 32 + OVERLAY_COL + i] = (u16)(attrs | 0xC0);
}

static void OverworldOverlay_PatchVram(void) {
  vu16 *vramMap = (vu16 *)0x0600E800;
  u16 *bufMap = (u16 *)(gVramBuffer + OVERWORLD_BG0_TILEMAP_OFFSET);
  int i;

  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    CpuCopy16(gVramBuffer + OVERWORLD_BG0_CHARBUF_OFFSET, (void *)0x0600E680, OVERLAY_CHARBUF_SIZE);

  for (i = 0; i < OVERLAY_MAX_CHARS; i++)
    vramMap[OVERLAY_ROW * 32 + OVERLAY_COL + i] = bufMap[OVERLAY_ROW * 32 + OVERLAY_COL + i];
}

static void OverworldOverlay_Update(void) {
  int screenX;
  int screenY;
  char buf[OVERLAY_MAX_CHARS + 1];
  char *p;

  if (gRuntimeConfig.show_player_screen_pixel_coords != TRUE) {
    ClearOverlayTilemap();
    return;
  }

  screenX = gOverworld.objects[0].x * 2 + gOverworld.unk24E - 16;
  screenY = gOverworld.objects[0].y * 2 + gOverworld.unk24C - 24 - gOverworld.objects[0].unk8 -
            gOverworld.objects[0].unkA;

  screenX = ClampInt(screenX, 0, 239);
  screenY = ClampInt(screenY, 0, 159);
  p = buf;

  *p++ = 'X';
  *p++ = ':';
  p = AppendSignedInt(p, screenX);
  *p++ = ' ';
  *p++ = 'Y';
  *p++ = ':';
  p = AppendSignedInt(p, screenY);
  *p = '\0';

  WriteOverlayString(buf);
}

void OverworldOverlay_PrepareFrame(void) {
  if (gDebugSaveAnywherePendingCapture == TRUE)
    return;
  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_Update();
}

void OverworldOverlay_CommitFrame(void) {
  if (gDebugSaveAnywherePendingCapture == TRUE)
    return;
  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_PatchVram();
}

void OverworldOverlay_OnWalkFrame(void) {
  if (gDebugSaveAnywherePendingCapture == TRUE)
    return;
  OverworldOverlay_PrepareFrame();
  OverworldOverlay_CommitFrame();
}

void OverworldOverlay_RestoreDisplayRegs(void) {
  REG_WINOUT = 0x3D3F;
  REG_BLDCNT = 0;
  REG_BLDY = 0;
}

void OverworldOverlay_Refresh(void) {
  if (gDebugSaveAnywherePendingCapture == TRUE)
    return;
  OverworldOverlay_Update();
  UploadOverworldBg0Base();
  OverworldOverlay_PatchVram();
  SetVBlankCallback(sub_804F1E4);
}

/* Pending custom map override state lives in gCustomMapOverridePending /
 * gCustomMapOverrideId (maps_custom.h), set by sub_804EF84__Replacement. */

/* Manifest graphics-source override table — generated from manifest. */
#include "src_custom/generated/maps/manifest_map_sources.inc"
#include "src_custom/generated/maps/manifest_collision_overrides.inc"

/* Custom map CopyOverworldBgGraphics logic. */
extern const u16 gOverworldEntityPalettes[];

#include "src_custom/generated/maps/manifest_spawn_overrides.inc"

static void ClearBg1IfNoRoof(void);

static void CopyCustomBgGraphics(u16 mapId) {
  const u8 *tileset = GetCustomMapTileset(mapId);
  const u16 *groundTm = GetCustomMapGroundTilemap(mapId);
  const u16 *roofTm = GetCustomMapRoofTilemap(mapId);
  const u16 *pal = GetCustomMapPalette(mapId);

  if (!tileset || !groundTm || !pal)
    return;

  LZ77UnCompWram(tileset, gBgVram.cbb0);
  /* sub_804F5D8 copies entity+font+map palettes but reads g8E11CD0[map.id]
   * which is OOB for custom maps. Replicate entity+font manually. */
  CpuCopy16(gOverworldEntityPalettes, gPaletteBuffer + 256, 0x180);
  CpuCopy16(g82ADC8C, gPaletteBuffer, 0x20);
  CpuCopy16(pal, gPaletteBuffer + 0x10, 0x1E0);
  CpuCopy16(groundTm, gBgVram.sbb1F, 0x800);
  if (roofTm)
    CpuCopy16(roofTm, gBgVram.sbb1E, 0x800);
  else
    CpuFill16(0, gBgVram.sbb1E, 0x800);  /* tile 0 = all-zero → transparent */

  /* Commit to hardware immediately. The vanilla sub_804EC4C already ran
   * with map_0 data, so without this commit the graveyard tileset, tilemap,
   * and palette stay in the backing buffer and never reach VRAM/hardware. */
  LoadVRAM();
  LoadPalettes();
}

/* Called at end-of-frame from sub_804EF10 when a custom map transition
 * is pending. Overrides VRAM with custom map tiles/tilemaps/palettes. */
void ApplyCustomMapOverride(void) {
  u16 id = gCustomMapOverrideId;
  gCustomMapOverridePending = FALSE;

  CopyCustomBgGraphics(id);

  /* Override collision pointer. InitOverworld set it to gMapCollisions[0]
   * because we redirected unk8 to 0. Fix it here. */
  gOverworld.unk23C = (u16 *)GetCustomMapCollision(id);

  /* Disable BG1 (roof layer) when the map has no roof — otherwise stale
   * tile data in sbb1E would cover BG2 (ground) since all 8bpp pixels
   * are non-zero (shifted by +16 palette offset) and therefore opaque. */
  if (!GetCustomMapRoofTilemap(id))
    REG_DISPCNT &= ~DISPCNT_BG1_ON;
  else
    REG_DISPCNT |= DISPCNT_BG1_ON;

  /* Play the custom map's music. */
  gOverworld.music = GetCustomMapMusic(id);
  PlayOverworldMusic();
}

LYN_REPLACE_CHECK(OverworldLoadGraphics);
void OverworldLoadGraphics__Replacement(void) {
  REG_DISPCNT = 0;
  REG_BLDCNT = 0;

  /* unk8→id copy: the original OverworldLoadGraphics at 0x0804ED08 does
   * this, but since we replaced that function, do it here. This ensures
   * gOverworld.map.id reflects the current transition destination. */
  gOverworld.map.id = gOverworld.map.unk8;
  gOverworld.map.state = gOverworld.map.unkA;
  gOverworld.map.unk4 = gOverworld.map.unkC;

  if (gOverworld.map.id >= CUSTOM_MAP_BASE) {
    /* Custom map: use safe dummy map (0) for vanilla loading to avoid
     * out-of-bounds array access. Schedule override for end-of-frame. */
    u16 realId = gOverworld.map.id;
    gOverworld.map.id = 0;
    gOverworld.map.state = 0;
    CallThumbVoid(0x0804DCE8);  /* CopyOverworldBgGraphics (safe, reads map 0) */
    gOverworld.map.id = realId; /* restore for remaining setup */
    gCustomMapOverrideId = realId;
    gCustomMapOverridePending = TRUE;
  } else {
    u16 graphicsId = gOverworld.map.id;
    if (gRuntimeConfig.enable_manifest_map_overrides) {
        u16 srcId = sManifestMapSources[gOverworld.map.id];
        if (srcId != gOverworld.map.id)
            graphicsId = srcId;
    }
    gOverworld.map.id = graphicsId;
    CallThumbVoid(0x0804DCE8);  /* CopyOverworldBgGraphics */
    gOverworld.map.id = gOverworld.map.unk8;  /* restore after redirect */

    /* Collision override: if the manifest specifies custom collision for
     * this map (gated by enable_manifest_map_overrides), replace the
     * pointer that InitOverworld set from gMapCollisions[]. */
    if (gRuntimeConfig.enable_manifest_map_overrides) {
        u16 overrideMapId = gOverworld.map.id;
        if (sManifestCollisionOverrides[overrideMapId] != NULL)
            gOverworld.unk23C = (u16 *)sManifestCollisionOverrides[overrideMapId];
    }
  }

  /* Spawn override only after InitOverworld (map / world-map transition).
   * Mid-script OverworldLoadGraphics (shop buy/sell, password, casino) must
   * keep the player's current tile — otherwise door slot unkC snaps you back
   * to the entrance (e.g. Card Shop after leaving Grandpa's buy menu). */
  if (((gOverworld.flags & OVERWORLD_FLAG_MAP_TRANSITION) != 0
       || gCustomMapOverridePending)
      && (gRuntimeConfig.enable_manifest_map_overrides
          || gCustomMapOverrideId >= CUSTOM_MAP_BASE)) {
    u16 overrideMapId = gOverworld.map.id;
    u8 slot = gOverworld.map.unk4;
    u8 sx, sy, sd;
    u8 i;

    if (gCustomMapOverrideId >= CUSTOM_MAP_BASE)
      overrideMapId = gCustomMapOverrideId;
    if (slot < 5 && overrideMapId < CUSTOM_SPAWN_OVERRIDE_COUNT) {
      sx = gManifestSpawnOverrideX[overrideMapId][slot];
      sy = gManifestSpawnOverrideY[overrideMapId][slot];
      sd = gManifestSpawnOverrideDir[overrideMapId][slot];
      if (sd != 0xFF)
        gOverworld.objects[0].direction = sd;
      if (sx != 0xFF)
        gOverworld.objects[0].x = sx;
      if (sy != 0xFF)
        gOverworld.objects[0].y = sy;
      if (sx != 0xFF || sy != 0xFF || sd != 0xFF) {
        sub_8052088(0);
        /* Keep Yugi/Joey followers on the player after the spawn fix. */
        for (i = 13; i <= 14; i++) {
          if (!gOverworld.objects[i].unk1Dl)
            continue;
          if (sd != 0xFF)
            gOverworld.objects[i].direction = sd;
          if (sx != 0xFF)
            gOverworld.objects[i].x = sx;
          if (sy != 0xFF)
            gOverworld.objects[i].y = sy;
          sub_8052088(i);
        }
      }
    }
  }

  CallThumbVoid(0x0804EDA0);  /* SetBg3Regs */
  CallThumbVoid(0x0804EDC8);  /* SetBg2Regs */
  CallThumbVoid(0x0804EDF0);  /* SetBg1Regs */
  CallThumbVoid(0x0804EE18);  /* SetBg0Data */
  CallThumbVoid(0x0804EE6C);  /* LoadSpriteGraphics */
  DebugMenuClearPortraitObjStash();
  if (CheckFlag(0xF3))
    sub_8044E50(gPaletteBuffer, 0x10, 0x1FF);
  if (CheckFlag(0xF0))
    sub_8044EC8(gPaletteBuffer, 0x10, 0x1FF, 6);
  if (CheckFlag(0xEF))
    sub_8045284(gPaletteBuffer, 0x10, 0xFF);
  /* Apply custom tiles while display is still off so map 0 never flashes. */
  if (gCustomMapOverridePending)
    ApplyCustomMapOverride();
  REG_BLDY = 7; /* match vanilla OverworldLoadGraphics */
  WaitForVBlank();
  sub_804EC4C();
  REG_WINOUT = 0x3D3F;
  OverworldSetRegDispcnt();
  ClearBg1IfNoRoof();
  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_Refresh();
}

/* OverworldSetRegDispcnt re-enables BG1 every frame, which would re-enable
 * the roof layer even for roof-less custom maps.  Suppress it here. */
static void ClearBg1IfNoRoof(void) {
  u16 id = gOverworld.map.id;
  if (id >= CUSTOM_MAP_BASE && !GetCustomMapRoofTilemap(id))
    REG_DISPCNT &= ~DISPCNT_BG1_ON;
}

LYN_REPLACE_CHECK(sub_8053E34);
void sub_8053E34__Replacement(u8 arg0) {
  int i, temp;

  CallThumbVoid(0x0805339C);
  OverworldSetRegDispcnt();
  ClearBg1IfNoRoof();
  REG_BLDCNT = 0xFF;
  REG_WINOUT = 0x3D3E;
  for (i = 0; i < 16; i++) {
    REG_BLDY = i;
    temp = arg0;
    while (--temp != -1)
      sub_804F218();
  }
  /* Leave BLDY=15 / BLDCNT=0xFF — RestoreDisplayRegs here undid the fade
   * and flashed the current map before the next load. */
}

/* LYN_REPLACEMENT(sub_80532A8) */
void sub_80532A8__Replacement(struct ScriptCtx *unused) {
  LZ77UnCompWram(g82AD2D0, gVramBuffer + 0xD800);
  CpuCopy16(g82AD48C, gVramBuffer + 0xE800, 0x500);
  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_Refresh();
  else
    UploadOverworldBg0Base();
  SetVBlankCallback(sub_804ECA8);
  WaitForVBlank();
}

LYN_REPLACE_CHECK(sub_804EEE0);
void sub_804EEE0__Replacement(void) {
  OverworldOverlay_PrepareFrame();
  CallThumbVoid(0x0804E618);
  CallThumbVoid(0x0804EBE4);
  SetVBlankCallback(sub_804F1E4);
  WaitForVBlank();
  CpuFastCopy(gBgVram.cbb4, (void *)0x06010000, 0x4000);
  OverworldOverlay_CommitFrame();
}

LYN_REPLACE_CHECK(sub_804F1E4);
void sub_804F1E4__Replacement(void) {
  LoadBgOffsets();
  LoadOam();
}

LYN_REPLACE_CHECK(sub_804ECA8);
void sub_804ECA8__Replacement(void) {
  CpuCopy32(gBgVram.sbb1B, (void *)0x0600D800, 0xE20);
  LoadOam();
  /* Textbox is on BG3; BLDCNT=0xDE during dialogue darkens BG3 (bit 3).
   * Clear bit 3 here so text isn't darkened to grey. */
  REG_BLDCNT &= ~0x0008;
  /* ponytail: start menu overwrites gPaletteBuffer bank 0 with grey-purple;
   * restore font palette to hardware every VBlank so text is white. */
  CpuCopy16(g82ADC8C, (void *)0x05000000, 0x20);
  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE
      && gDebugSaveAnywherePendingCapture != TRUE)
    OverworldOverlay_PatchVram();
  else if (gDebugSaveAnywherePendingCapture != TRUE)
    CpuCopy32(gBgVram.sbb1D, (void *)0x0600E800, 0x500);
}

LYN_REPLACE_CHECK(sub_804F218);
void sub_804F218__Replacement(void) {
  OverworldOverlay_PrepareFrame();
  CallThumbVoid(0x0804E618);
  CallThumbVoid(0x0804EBE4);
  sub_80551B8();
  SetVBlankCallback(LoadBgOffsets);
  WaitForVBlank();
  LoadOam();
  CpuCopy32(gBgVram.sbb1B, (void *)0x0600D800, 0xE20);
  if (gRuntimeConfig.show_player_screen_pixel_coords != TRUE
      && gDebugSaveAnywherePendingCapture != TRUE)
    CpuCopy32(gBgVram.sbb1D, (void *)0x0600E800, 0x500);
  LoadObjVRAM();
  LoadPalettes();
  if (gRuntimeConfig.enable_repeatable_duel_icon == TRUE)
    LoadDuelIconGfx();
  OverworldOverlay_CommitFrame();
}

LYN_REPLACE_CHECK(sub_804EC64);
void sub_804EC64__Replacement(void) {
  CpuCopy32(gBgVram.sbb1B, (void *)0x0600D800, 0xE20);
  if (gRuntimeConfig.show_player_screen_pixel_coords != TRUE)
    CpuCopy32(gBgVram.sbb1D, (void *)0x0600E800, 0x500);
  LoadObjVRAM();
  LoadPalettes();
  if (gRuntimeConfig.enable_repeatable_duel_icon == TRUE)
    LoadDuelIconGfx();
  LoadOam();
  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_Refresh();
  else
    UploadOverworldBg0Base();
  SetVBlankCallback(sub_804F1E4);
}

LYN_REPLACE_CHECK(sub_804EC4C);
void sub_804EC4C__Replacement(void) {
  LoadBgOffsets();
  LoadOam();
  LoadVRAM();
  LoadPalettes();

  SetVBlankCallback(sub_804F1E4);
  WaitForVBlank();
  SetVBlankCallback(sub_804F1E4);

  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_Refresh();
  else
    UploadOverworldBg0Base();
}
