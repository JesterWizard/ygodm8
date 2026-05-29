#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"

extern u32** g8FA31C0[];
extern u16** g8FA3360[];
extern u8 gSharedMem[];
extern struct OamData gOamBuffer[];

const u8 sPlayerPortraitTiles[] APPEND_ASSET =
    INCBIN_U8("src_custom/assets/portraits/player.lz");
const u16 sPlayerPortraitPalette[] APPEND_ASSET =
    INCBIN_U16("src_custom/assets/portraits/player.gbapal");

static void CopyTilesToVram(u8* dest, u8* src) {
  int i, j;
  for (i = 0; i < 8; dest += 512, i++)
    for (j = 0; j < 512; j++)
      *dest++ = *src++;
}

void LoadPortraitGfx(u8 portraitId, u8 expression) {
  if (portraitId == PORTRAIT_PLAYER) {
    LZ77UnCompWram(sPlayerPortraitTiles, gSharedMem);
    CopyTilesToVram(gBgVram.cbb4 + 0x2000, gSharedMem);
    CpuCopy16(sPlayerPortraitPalette, gPaletteBuffer + 256 + 0xC0, 128);
  } else if (portraitId != PORTRAIT_NONE) {
    LZ77UnCompWram(g8FA31C0[portraitId][expression], gSharedMem);
    CopyTilesToVram(gBgVram.cbb4 + 0x2000, gSharedMem);
    CpuCopy16(*g8FA3360[portraitId], gPaletteBuffer + 256 + 0xC0, 128);
  }
}

/* LYN_REPLACEMENT(DisplayPortrait) */
LYN_REPLACE_CHECK(DisplayPortrait);
void DisplayPortrait__Replacement(struct ScriptCtx* scriptCtx) {
  struct OamData* oam = gOamBuffer;
  if (scriptCtx->unk86 == 1) {
    REG_WIN1H = 0x03ED;
    REG_WIN1V = 0x739D;
    (*(vu8 *)(REG_BASE + 0x49)) = 0x3F;
    REG_WINOUT = 0x1D1E;
    OverworldSetRegDispcnt2();
    REG_BLDCNT = 0xDE;
    REG_BLDY = 7;
  }
  sub_804EB04(oam, 2);
  SetVBlankCallback(LoadOam);
  WaitForVBlank();
  sub_804EB04(oam, scriptCtx->unk85);
  oam->paletteNum = 12;
  LoadPortraitGfx(scriptCtx->portraitId, scriptCtx->unk84);
  if (CheckFlag(0xF3))
    sub_8044E50(gPaletteBuffer, 0x1C0, 0x1FF);
  WaitForVBlank();
  sub_804EC64();
}
