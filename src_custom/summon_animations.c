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
extern void LoadPalettes(void);
extern struct OamData gOamBuffer[];
extern struct BgVram gBgVram;

/* -- EWRAM-backed save buffers (declared in asm/ram_map_ewram.s) -------- */

extern struct OamData gSummonAnimSavedOam[];
extern u16 gSummonAnimSavedPalette[];
extern u16 gSummonAnimSavedDispCnt;
extern u8 gSummonAnimSavedObjVram[];

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
 * Dimming approach: BG palette darkening, NOT BLD registers.            *
 *                                                                       *
 * The engine's WaitForVBlank() resets the VBlank callback pointer to    *
 * the no-op sub_800842C after EVERY wait (src/code_8008030.c:166), so a *
 * custom VBlank callback cannot persist across the effect's internal    *
 * frame loop.  The GFX effect's sub_804F2DC also writes REG_BLDCNT =    *
 * gBLDCNT (= 0) once at start.  Together these wipe any BLD-based dim   *
 * after one frame.                                                      *
 *                                                                       *
 * Palette darkening is robust: sub_804F2DC commits gPaletteBuffer's BG  *
 * entries (0-255) to hardware inside the effect, so darkening them      *
 * bakes the dim in for the whole animation.  OBJ palette (256-511) is   *
 * untouched, so the popup sprite renders at full brightness over the    *
 * dimmed board.                                                         *
 *                                                                       *
 * Sequence:                                                             *
 *   1. Save full duel display state (OBJ VRAM, OAM, full palette,       *
 *      DISPCNT, window + blend regs).                                   *
 *   2. Disable the duel's textbox windows; keep BG0-BG3 + OBJ enabled.  *
 *   3. Fade the board to dim: darken the BG palette one step per frame, *
 *      LoadPalettes + WaitForVBlank, repeated.  The board + card        *
 *      sprites stay fully rendered, just darkening.                     *
 *   4. Clear OBJ VRAM + OAM so the effect has clean tile space; the     *
 *      duel's card sprites vanish here (popup is about to play).        *
 *   5. Run the overworld GFX renderer directly (NOT sub_80512E0, which  *
 *      calls sub_8053404 -> sub_804F508 and turns BG0-BG3 OFF, killing  *
 *      the dimmed board).  The board stays dim behind the popup.        *
 *   6. Restore everything.                                              */

#define SUMMON_ANIM_DIM_FRAMES 8
#define SUMMON_ANIM_DIM_STEP   2   /* per-channel subtract per fade frame */

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

    /* 1. Save duel display state. */
    CpuCopy16((void *)0x06010000, gSummonAnimSavedObjVram, 0x7FE0);
    CpuCopy16(gOamBuffer, gSummonAnimSavedOam, 0x400);
    CpuCopy16(gPaletteBuffer, gSummonAnimSavedPalette, 0x800);
    gSummonAnimSavedDispCnt = REG_DISPCNT;
    prevVBlankCb = g201CB20;
    prevWinIn = REG_WININ;
    prevWinOut = REG_WINOUT;
    prevBldCnt = REG_BLDCNT;
    prevBldAlpha = REG_BLDALPHA;
    prevBldY = REG_BLDY;

    /* 2. Disable textbox windows; keep BG0-BG3 + OBJ on so the board    *
     * shows through, dimmed.                                            */
    REG_WININ = 0;
    REG_WINOUT = 0x3F;
    REG_DISPCNT = gSummonAnimSavedDispCnt
                & ~(DISPCNT_WIN0_ON | DISPCNT_WIN1_ON | DISPCNT_OBJWIN_ON);

    /* 3. Clear ALL OBJ tile VRAM (0x6010000-0x6017FE0) so no duel card    *
     * sprites remain in the OBJ tile space when the popup plays.  The    *
     * popup effect writes its own tiles into this region; any leftover   *
     * card tiles get partially overwritten and render corrupted.         *
     * Both the hardware VRAM AND the gBgVram mirror (cbb4 + cbb5) are    *
     * cleared: the duel's VBlank callback copies the mirror back into    *
     * hardware, so the mirror must be zeroed too or the clear is undone. */
    ZeroFill32((void *)0x06010000, 0x7FE0);
    ZeroFill32(gBgVram.cbb4, 0x4000);
    ZeroFill32(gBgVram.cbb5, 0x4000);
    sub_804EB04(gOamBuffer, 2);
    WaitForVBlank();
    LoadOam();

    /* 4. Fade the board to dim over the (now card-less) board display.   */
    for (i = 0; i < SUMMON_ANIM_DIM_FRAMES; i++) {
        DarkenBgPalette(SUMMON_ANIM_DIM_STEP);
        LoadPalettes();
        WaitForVBlank();
    }

    /* 5. Play the popup.  BG palette stays darkened in hardware, so the *
     * board remains dim behind the bright popup sprite.                 */
    switch (g8E0E384[graphicId]) {
    case 3:  sub_804FE78(&fx);  break;
    case 4:  sub_8050114(&fx);  break;
    case 5:  sub_805022C(&fx);  break;
    default:
        sub_804FA28(&fx);
        break;
    }
    sub_8051740();

    /* 6. Restore the duel display.  Restore both the hardware OBJ VRAM    *
     * AND the gBgVram mirror (cbb4 + cbb5): the duel's VBlank callback   *
     * copies the mirror to hardware, so a zeroed mirror would wipe the   *
     * restore on the next frame.                                         */
    REG_DISPCNT = 0;
    CpuCopy16(gSummonAnimSavedObjVram, gBgVram.cbb4, 0x4000);
    CpuCopy16(gSummonAnimSavedObjVram + 0x4000, gBgVram.cbb5, 0x4000);
    CpuCopy16(gSummonAnimSavedObjVram, (void *)0x06010000, 0x7FE0);
    CpuCopy16(gSummonAnimSavedOam, gOamBuffer, 0x400);
    CpuCopy16(gSummonAnimSavedPalette, gPaletteBuffer, 0x800);
    REG_BLDCNT = prevBldCnt;
    REG_BLDALPHA = prevBldAlpha;
    REG_BLDY = prevBldY;
    REG_WININ = prevWinIn;
    REG_WINOUT = prevWinOut;
    REG_DISPCNT = gSummonAnimSavedDispCnt;
    SetVBlankCallback(prevVBlankCb);
    WaitForVBlank();
    LoadCharblock5();
    LoadOam();
    LoadPalettes();
}

/* -- public API --------------------------------------------------------- *
 *                                                                       *
 * Phase 1 (TryPlaySummonAnimation): called BEFORE card placement. Only  *
 * records the graphic id; no VRAM save so the post-placement draw is    *
 * captured correctly in phase 2.                                        *
 * Phase 2 (FinishSummonAnimation): called AFTER UpdateDuelGfx /         *
 * MaybeUpdateGfx has drawn the new card. Fades the board to dim, plays  *
 * the popup over it, then restores the duel display.                    */

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
