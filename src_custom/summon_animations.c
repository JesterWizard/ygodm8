#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "configs/runtime.h"
#include "summon_animations.h"
#include "gba/defines.h"
#include "gba/io_reg.h"
#include "gba/types.h"
#include "gfx_reg_buffers.h"
#include "duel.h"
#include "overworld.h"
#include "generated/popup_yubel_data.inc"

/* -- custom popup animation IDs (outside vanilla 0-58 range) ------------ */
#define CUSTOM_POPUP_ANIM_START 200

/* -- overworld GFX effect descriptor (mirrors overworld_gfx_effects.c) --- */
struct GfxEffect {
    unsigned char unk0;   /* graphicId */
    unsigned char unk1;
    unsigned short unk2;
    signed short unk4;
    unsigned char unk6bit0 : 2;
};

/* -- BG0 popup constants ------------------------------------------------ */
#define POPUP_BG_CHARBASE   0
#define POPUP_BG_SCREENBASE 30   /* sbb1E — even base for 512-wide mode, uses sbb1E+sbb1F */
#define POPUP_BG_TILE_W 30
#define POPUP_BG_TILE_H 20
#define POPUP_BG_TILE_BYTES (POPUP_BG_TILE_W * POPUP_BG_TILE_H * TILE_SIZE_8BPP)  /* 38400 */
#define POPUP_BG0CNT (BGCNT_PRIORITY(0) | BGCNT_CHARBASE(POPUP_BG_CHARBASE) \
                       | BGCNT_256COLOR | BGCNT_SCREENBASE(POPUP_BG_SCREENBASE) \
                       | BGCNT_TXT512x256)
#define POPUP_SLIDE_FRAMES 12

/* -- EWRAM-backed save buffers (declared in asm/ram_map_ewram.s) -------- */
extern u16 gSummonAnimSavedPalette[];
extern u16 gSummonAnimSavedDispCnt;
extern u8 gSummonAnimSavedCbb5[];
extern u8 gSummonAnimPendingGraphicId;

/* -- VBlank callback pointer -------------------------------------------- */
extern void (*g201CB20)(void);

extern struct OamData gOamBuffer[];

/* -- overworld GFX effects engine externs -------------------------------- */
extern const unsigned char g8E0E384[];

extern void sub_804FA28(struct GfxEffect *arg0);
extern void sub_804FE78(struct GfxEffect *arg0);
extern void sub_8050114(struct GfxEffect *arg0);
extern void sub_805022C(struct GfxEffect *arg0);
extern void sub_8051740(void);

/* -- config lookup ------------------------------------------------------ */
static u8 GetSummonAnimGraphic(u16 cardId)
{
    switch (cardId) {
    /* -- standard overworld GFX effects (vanilla full-art popups) ------ */
    case BLUE_EYES_WHITE_DRAGON:
        return GRAPHIC_BLUE_EYES_WHITE_DRAGON_FULL_ART;
    case RED_EYES_B_DRAGON:
        return GRAPHIC_RED_EYES_FULL_ART;
    case HARPIE_LADY_SISTERS:
        return GRAPHIC_HARPIE_LADY_SISTERS_FULL_ART;
    case DARK_MAGICIAN:
        return GRAPHIC_DARK_MAGICIAN_FULL_ART;
    case JINZO:
        return GRAPHIC_JINZO_FULL_ART;
    case MASTER_OF_DRAGON_SOLDIER:
        return GRAPHIC_DRAGON_MASTER_KNIGHT_FULL_ART;

    /* -- god cards (full-art with glowing orb entry) ------------------- */
    case SLIFER_THE_SKY_DRAGON:
        return GRAPHIC_SLIFER_FULL_ART;
    case OBELISK_THE_TORMENTOR:
        return GRAPHIC_OBELISK_FULL_ART;
    case THE_WINGED_DRAGON_OF_RA_SPHERE_MODE:
    case THE_WINGED_DRAGON_OF_RA_BATTLE_MODE:
        return GRAPHIC_RA_FULL_ART;
    case THE_WINGED_DRAGON_OF_RA_PHOENIX_MODE:
        return GRAPHIC_PHOENIX_RA_FULL_ART;

    /* -- custom 8bpp BG0 popup ----------------------------------------- */
    case YUBEL:
        return CUSTOM_POPUP_ANIM_START;
    default:
        return 0;
    }
}

/* -- helpers ------------------------------------------------------------ */

static void ZeroFill32(void *dst, u32 byteLen)
{
    u32 *p = (u32 *)dst;
    u32 *end = (u32 *)((u8 *)dst + byteLen);
    while (p < end)
        *p++ = 0;
}

static void DarkenBgPalette(u8 amount)
{
    u16 i;
    for (i = 0; i < 256; i++) {
        struct PlttData *p = (struct PlttData *)&gPaletteBuffer[i];
        if (p->r > amount) p->r -= amount; else p->r = 0;
        if (p->g > amount) p->g -= amount; else p->g = 0;
        if (p->b > amount) p->b -= amount; else p->b = 0;
    }
}

#define POPUP_DIM_FRAMES 8
#define POPUP_DIM_STEP   1

/* -- custom 8bpp BG0 popup renderer -------------------------------------
 *
 * Writes tiles directly from ROM to hardware charblock 0-2.  Builds a
 * 512-wide tilemap with the image in the RIGHT half (sbb1F cols 0-29)
 * and tile 0 (blank) filler everywhere else.  Animates HOFS
 * 496→256→496 so the image enters from the right, holds centred for
 * 1 second (60 frames), then exits through the left.  The blank filler
 * spans enough of the virtual map that no wrapping is ever visible.
 *
 * Virtual map (512px = 64 cols):
 *   sbb1E[0..31]      = tile 0 (blank)
 *   sbb1F[0..29]      = image tile indices 1..600
 *   sbb1F[30..31]     = tile 0 (blank)
 *
 * HOFS = 0           → all blank (image off-screen right).
 * HOFS = 256         → image perfectly centred on screen.
 * HOFS = 496-511     → all blank (image fully exited left).
 *
 * ponytail: the blank padding (tile 0 zeroed in VRAM on every call) means
 *           even if HOFS wraps past the tilemap boundary, the wrapped
 *           portion is also tile 0 → always black, never loops.
 *                                                                       */
static void PlayCustomPopupBg8bpp(const u8 *tiles, const u16 *palette,
                                   int holdFrames)
{
    u16 savedDispCnt;
    u16 savedBldCnt, savedBldAlpha, savedBldY;
    u16 savedWinIn, savedWinOut;
    void (*prevVBlankCb)(void);
    u16 row, col;
    int frame;
    const int hold = 60;   /* 1 second at 60 fps */

    /* -- 1. save duel state ------------------------------------------ */
    CpuCopy16(gBgVram.cbb5, gSummonAnimSavedCbb5, 0x4000);
    CpuCopy16(gPaletteBuffer, gSummonAnimSavedPalette, 0x400);
    savedDispCnt   = REG_DISPCNT;
    savedBldCnt    = REG_BLDCNT;
    savedBldAlpha  = REG_BLDALPHA;
    savedBldY      = REG_BLDY;
    savedWinIn     = REG_WININ;
    savedWinOut    = REG_WINOUT;
    prevVBlankCb   = g201CB20;

    /* -- 2. hide OBJs, clear windows (display BGs stay ON this frame) -- */
    CpuFill16(0, gOamBuffer, 0x400);
    sub_804EB04(gOamBuffer, 2);
    CpuFill16(0, (void *)0x06010000, 0x7FE0);   /* OBJ VRAM */
    REG_WININ  = 0;
    REG_WINOUT = 0x3F;

    /* -- 3. switch to fully-blank display (mode 0, no layers) -------- */
    REG_DISPCNT = DISPCNT_MODE_0;
    WaitForVBlank();
    LoadOam();

    /* -- 4. upload popup tiles to HW charblock 0-2 (display is off) -- */
    CpuCopy16(tiles,                     (void *)BG_CHAR_ADDR(0), 0x4000);
    CpuCopy16(tiles + 0x4000,            (void *)BG_CHAR_ADDR(1), 0x4000);
    CpuCopy16(tiles + 0x8000,            (void *)BG_CHAR_ADDR(2), 0x1600);

    /* tile 0 → blank filler (kills any stale tile-0 data from duel) */
    CpuFill16(0, (void *)BG_CHAR_ADDR(0), 64);

    /* -- 5. fill 512-wide tilemap: blank left, image right ------------ */
    for (row = 0; row < POPUP_BG_TILE_H; row++) {
        for (col = 0; col < 32; col++)
            gBgVram.sbb1E[row][col] = 0;
        for (col = 0; col < POPUP_BG_TILE_W; col++)
            gBgVram.sbb1F[row][col] = (u16)(row * POPUP_BG_TILE_W + col + 1);
        gBgVram.sbb1F[row][30] = 0;
        gBgVram.sbb1F[row][31] = 0;
    }
    CpuCopy16(gBgVram.sbb1E, (void *)BG_SCREEN_ADDR(30), 0x800);
    CpuCopy16(gBgVram.sbb1F, (void *)BG_SCREEN_ADDR(31), 0x800);

    /* -- 6. load palette, set initial HOFS so image starts             *
     *     off-screen right, enable BG0 -------------------------------- */
    CpuCopy16(palette, gPaletteBuffer, 0x200);
    REG_BG0CNT = POPUP_BG0CNT;
    gBG0HOFS = 0;                            /* off-screen right (image at cols 32+) */
    gBG0VOFS = 0;
    LoadBgOffsets();
    REG_DISPCNT = DISPCNT_MODE_0 | DISPCNT_BG0_ON;
    WaitForVBlank();
    LoadPalettes();

    /* -- 7. slide in from right to centre (HOFS 0 → 256) ------------- */
    for (frame = 1; frame <= POPUP_SLIDE_FRAMES; frame++) {
        gBG0HOFS = (256 * frame) / POPUP_SLIDE_FRAMES;
        LoadBgOffsets();
        WaitForVBlank();
    }

    /* -- 8. hold at centre for 1 second ------------------------------- */
    for (frame = 0; frame < hold; frame++)
        WaitForVBlank();

    /* -- 9. slide out from centre to left (HOFS 256 → 496) ----------- */
    for (frame = 1; frame <= POPUP_SLIDE_FRAMES; frame++) {
        gBG0HOFS = 256 + (240 * frame) / POPUP_SLIDE_FRAMES;
        LoadBgOffsets();
        WaitForVBlank();
    }

    /* -- 10. restore duel display (off-screen left, invisible) ---------- */
    REG_DISPCNT = 0;
    CpuCopy16(gSummonAnimSavedCbb5,     gBgVram.cbb5,     0x4000);
    CpuCopy16(gSummonAnimSavedPalette,  gPaletteBuffer,    0x400);
    CpuCopy16(gBgVram.cbb0, (void *)BG_CHAR_ADDR(0), 0x4000);
    CpuCopy16(gBgVram.cbb1, (void *)BG_CHAR_ADDR(1), 0x4000);
    CpuCopy16(gBgVram.cbb2, (void *)BG_CHAR_ADDR(2), 0x4000);
    REG_BG0CNT   = 0;
    REG_BLDCNT   = savedBldCnt;
    REG_BLDALPHA = savedBldAlpha;
    REG_BLDY     = savedBldY;
    REG_WININ    = savedWinIn;
    REG_WINOUT   = savedWinOut;
    REG_DISPCNT  = savedDispCnt;
    CpuFill16(0, gOamBuffer, 0x400);
    gBG0HOFS = 0;
    gBG0VOFS = 0;
    SetVBlankCallback(prevVBlankCb);
    WaitForVBlank();
    LoadCharblock5();
    LoadOam();
    LoadPalettes();
}

/* -- overworld GFX effects engine (vanilla full-art popups) ---------------
 *
 * Saves duel display state, dims, plays the standard GBA overworld GFX
 * effect for the given graphicId, then restores everything.
 *                                                                       */
static void PlayGfxEffectByGraphic(u8 graphicId)
{
    struct GfxEffect fx;
    u16 savedDispCnt, savedBldCnt, savedBldAlpha, savedBldY;
    u16 savedWinIn, savedWinOut;
    void (*prevVBlankCb)(void);
    u8 effectType;
    int i;

    /* -- 1. save duel state ------------------------------------------ */
    CpuCopy16(gPaletteBuffer, gSummonAnimSavedPalette, 0x400);
    savedDispCnt   = REG_DISPCNT;
    savedBldCnt    = REG_BLDCNT;
    savedBldAlpha  = REG_BLDALPHA;
    savedBldY      = REG_BLDY;
    savedWinIn     = REG_WININ;
    savedWinOut    = REG_WINOUT;
    prevVBlankCb   = g201CB20;

    /* -- 2. hide duel display ---------------------------------------- */
    ZeroFill32(gBgVram.cbb2, 0x4000);
    ZeroFill32(gBgVram.cbb4, 0x4000);
    ZeroFill32(gBgVram.cbb5, 0x4000);
    ZeroFill32((void *)0x06010000, 0x7FE0);
    sub_804EB04(gOamBuffer, 2);
    REG_WININ  = 0;
    REG_WINOUT = 0x3F;
    REG_DISPCNT = savedDispCnt
                & ~(DISPCNT_WIN0_ON | DISPCNT_WIN1_ON | DISPCNT_OBJWIN_ON);
    LoadCharblock2();
    LoadObjVRAM();
    WaitForVBlank();
    LoadOam();

    /* -- 3. fade duel to dim ----------------------------------------- */
    for (i = 0; i < POPUP_DIM_FRAMES; i++) {
        DarkenBgPalette(POPUP_DIM_STEP);
        LoadPalettes();
        WaitForVBlank();
    }

    /* -- 4. init effect descriptor ----------------------------------- */
    fx.unk0 = graphicId;
    fx.unk1 = 0;
    fx.unk2 = 0;
    fx.unk4 = 0;
    fx.unk6bit0 = 0;

    /* -- 5. play effect based on type -------------------------------- */
    effectType = g8E0E384[graphicId];

    switch (effectType) {
    case 3: /* horizontal slide full-art popup */
        sub_804FE78(&fx);
        break;
    case 4: /* vertical slide full-art popup */
        sub_8050114(&fx);
        break;
    case 5: /* attack / swipe */
        sub_805022C(&fx);
        break;
    default:
        sub_804FA28(&fx);
        sub_8051740();
        break;
    }

    /* -- 6. restore duel display ------------------------------------- */
    REG_DISPCNT = 0;
    CpuCopy16(gSummonAnimSavedPalette, gPaletteBuffer, 0x400);
    REG_BG0CNT   = 0;
    REG_BLDCNT   = savedBldCnt;
    REG_BLDALPHA = savedBldAlpha;
    REG_BLDY     = savedBldY;
    REG_WININ    = savedWinIn;
    REG_WINOUT   = savedWinOut;
    REG_DISPCNT  = savedDispCnt;
    CpuFill16(0, gOamBuffer, 0x400);
    gBG0HOFS = 0;
    gBG0VOFS = 0;
    SetVBlankCallback(prevVBlankCb);
    WaitForVBlank();
    LoadCharblock5();
    LoadOam();
    LoadPalettes();
}

/* -- public API --------------------------------------------------------- */

bool32 TryPlaySummonAnimation(u16 cardId)
{
    u8 graphicId;

    if (!gRuntimeConfig.enable_summon_animations)
        return FALSE;

    graphicId = GetSummonAnimGraphic(cardId);
    if (graphicId == 0)
        return FALSE;

    gSummonAnimPendingGraphicId = graphicId;
    return TRUE;
}

void FinishSummonAnimation(void)
{
    u8 graphicId = gSummonAnimPendingGraphicId;

    if (graphicId == 0)
        return;

    if (graphicId < CUSTOM_POPUP_ANIM_START) {
        PlayGfxEffectByGraphic(graphicId);
        return;
    }

    switch (graphicId) {
    case CUSTOM_POPUP_ANIM_START:
        PlayCustomPopupBg8bpp(gPopupYubelTiles, gPopupYubelPalette,
                               POPUP_YUBEL_DURATION);
        break;
    }
}
