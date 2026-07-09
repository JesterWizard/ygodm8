#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "configs/runtime.h"
#include "summon_animations.h"
#include "overworld.h"
#include "gba/io_reg.h"
#include "gba/types.h"
#include "gfx_reg_buffers.h"

/* -- externs from the overworld GFX effects engine ---------------------- */

struct GfxEffect {
    unsigned char unk0;   /* graphicId */
    unsigned char unk1;
    unsigned short unk2;
    signed short unk4;
    unsigned char unk6bit0 : 2;
};

extern const unsigned char g8E0E384[];

extern void sub_804FA28(struct GfxEffect *arg0);
extern void sub_804FE78(struct GfxEffect *arg0);
extern void sub_8050114(struct GfxEffect *arg0);
extern void sub_805022C(struct GfxEffect *arg0);
extern void sub_8051740(void);

extern void LoadCharblock5(void);
extern void LoadCharblock2(void);
extern void LoadPalettes(void);
extern struct OamData gOamBuffer[];
extern struct BgVram gBgVram;

/* -- EWRAM-backed save buffers (declared in asm/ram_map_ewram.s) -------- */

extern u16 gSummonAnimSavedPalette[];
extern u16 gSummonAnimSavedDispCnt;
extern u8 gSummonAnimSavedCbb5[];

/* -- EWRAM-backed state shared between phase 1 and phase 2 -------------- */

extern u8 gSummonAnimPendingGraphicId;

/* -- VBlank callback pointer (SetVBlankCallback mutates this) ----------- */

extern void (*g201CB20)(void);

/* -- config lookup ------------------------------------------------------ */

static u8 GetSummonAnimGraphic(u16 cardId)
{
    switch (cardId) {
    case JINZO:  return GRAPHIC_JINZO_FULL_ART;
    default:     return 0;
    }
}

/* -- helpers ------------------------------------------------------------ */

/* ponytail: zero-fill helper.  gcc's -O0 degrades memset into
 * byte-at-a-time; this loop uses u32 writes for 4x throughput.          */
static void ZeroFill32(void *dst, u32 byteLen)
{
    u32 *p = (u32 *)dst;
    u32 *end = (u32 *)((u8 *)dst + byteLen);
    while (p < end)
        *p++ = 0;
}

/* Darken every BG palette entry (0-255) by `amount` per channel, clamped
 * at 0. OBJ palette (256-511) is left untouched so the popup sprite stays
 * full-bright.  Done by mutating gPaletteBuffer; the caller commits it via
 * LoadPalettes().                                                       */
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

/* -- renderer dispatch -------------------------------------------------- *
 *                                                                       *
 * EWRAM budget: ~0x4402 bytes total                                      *
 *   - gSummonAnimSavedPalette   0x400  (full palette, darkened then     *
 *                                       restored)                        *
 *   - gSummonAnimSavedCbb5      0x4000 (effect overwrites hand-card     *
 *                                       tiles; must restore)             *
 *   - gSummonAnimSavedDispCnt   2      (DISPCNT restore)                 *
 *                                                                       *
 * Everything else is cleared without saving:                             *
 *   - cbb4 + cbb2 mirrors & hardware OBJ VRAM → the duel's next frame   *
 *     rebuilds field cards (cbb4) and the info bar (cbb2).              *
 *   - OAM → cleared after the effect; next UpdateDuelGfx rebuilds it.    *
 *                                                                       *
 * Dimming approach: BG palette darkening, NOT BLD registers.            *
 * WaitForVBlank() resets the VBlank callback to a no-op after every    *
 * wait, so a custom callback cannot persist.  The effect's sub_804F2DC   *
 * also clobbers REG_BLDCNT once at start.  Palette darkening is the     *
 * only robust dim: sub_804F2DC commits gPaletteBuffer BG entries to      *
 * hardware, baking the dim in for the whole animation.                  */

#define SUMMON_ANIM_DIM_FRAMES 8
#define SUMMON_ANIM_DIM_STEP   1   /* per-channel subtract per fade frame */

static void PlayGfxEffectByGraphic(u8 graphicId)
{
    struct GfxEffect fx;
    void (*prevVBlankCb)(void);
    u16 prevWinIn, prevWinOut, prevBldCnt, prevBldAlpha, prevBldY;
    int i;

    fx.unk0 = graphicId;
    fx.unk1 = 0;
    fx.unk2 = 0;
    fx.unk4 = 0;
    fx.unk6bit0 = 0;

    /* 1. Save the pieces the effect mutates and the duel won't auto-fix. */
    CpuCopy16(gBgVram.cbb5, gSummonAnimSavedCbb5, 0x4000);
    CpuCopy16(gPaletteBuffer, gSummonAnimSavedPalette, 0x400);
    gSummonAnimSavedDispCnt = REG_DISPCNT;
    prevVBlankCb = g201CB20;
    prevWinIn = REG_WININ;
    prevWinOut = REG_WINOUT;
    prevBldCnt = REG_BLDCNT;
    prevBldAlpha = REG_BLDALPHA;
    prevBldY = REG_BLDY;

    /* 2. Hide everything the popup shouldn't cover:                   *
     *    - BG1 (cbb2)          → bottom info bar (name, level, etc.)  *
     *    - OBJ tiles (cbb4/5)  → field + hand card sprites              *
     *    - OAM                 → all OBJ sprite positions               *
     *  The duel's next UpdateDuelGfx will redraw cbb2/cbb4; we save    *
     *  cbb5 because the effect overwrites it with popup tiles.          */
    ZeroFill32(gBgVram.cbb2, 0x4000);
    ZeroFill32(gBgVram.cbb4, 0x4000);
    ZeroFill32(gBgVram.cbb5, 0x4000);
    ZeroFill32((void *)0x06010000, 0x7FE0);
    sub_804EB04(gOamBuffer, 2);
    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_DISPCNT = gSummonAnimSavedDispCnt
                & ~(DISPCNT_WIN0_ON | DISPCNT_WIN1_ON | DISPCNT_OBJWIN_ON);
    LoadCharblock2();
    LoadCharblock5();
    WaitForVBlank();
    LoadOam();

    /* 3. Fade the board to dim over the card-less board display.         */
    for (i = 0; i < SUMMON_ANIM_DIM_FRAMES; i++) {
        DarkenBgPalette(SUMMON_ANIM_DIM_STEP);
        LoadPalettes();
        WaitForVBlank();
    }

    /* 4. Play the popup.  BG palette stays darkened in hardware.        */
    switch (g8E0E384[graphicId]) {
    case 3:  sub_804FE78(&fx);  break;
    case 4:  sub_8050114(&fx);  break;
    case 5:  sub_805022C(&fx);  break;
    default:
        sub_804FA28(&fx);
        break;
    }
    sub_8051740();

    /* 5. Restore the duel display.  cbb2/cbb4 are left for the duel to   *
     * redraw; cbb5 and palette are restored immediately so hand cards    *
     * and colours come back on the very next frame.  OAM is wiped so    *
     * no stale popup sprites leak through before the duel rebuilds.      */
    REG_DISPCNT = 0;
    CpuCopy16(gSummonAnimSavedCbb5, gBgVram.cbb5, 0x4000);
    CpuCopy16(gSummonAnimSavedPalette, gPaletteBuffer, 0x400);
    REG_BLDCNT = prevBldCnt;
    REG_BLDALPHA = prevBldAlpha;
    REG_BLDY = prevBldY;
    REG_WININ = prevWinIn;
    REG_WINOUT = prevWinOut;
    REG_DISPCNT = gSummonAnimSavedDispCnt;
    CpuFill16(0, gOamBuffer, 0x400);
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
    PlayGfxEffectByGraphic(gSummonAnimPendingGraphicId);
}
