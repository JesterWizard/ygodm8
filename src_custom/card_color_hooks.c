#include "global.h"
#include "configs/runtime.h"
#include "card.h"

/*
 * Custom card color palette and border data for new extra deck monster types
 * (Synchro, XYZ, Pendulum, Link). These entries extend the vanilla gUnk_8E137C4
 * and gUnk_8E17F48 arrays without touching ROM data.
 *
 * Big card frame palettes are 20 halfwords (40 bytes) — indexed by
 * gCardInfo.color - COLOR_SYNCHRO.
 *
 * Mini card border tile pointers default to a vanilla fallback until custom
 * border art is authored (set gCustomCardColorBorders[i] to an INCBIN).
 */

/* Color index threshold for new extra deck types */
#define FIRST_NEW_COLOR COLOR_SYNCHRO
#define NUM_NEW_COLORS  4

/* ---- Big card frame palettes ---- */
static const unsigned short sSynchroPalette[] APPEND_ASSET =
    INCBIN_U16("src_custom/assets/cards/frames/synchro.gbapal");

static const unsigned short sXyzPalette[] APPEND_ASSET =
    INCBIN_U16("src_custom/assets/cards/frames/xyz.gbapal");

static const unsigned short sPendulumPalette[] APPEND_ASSET =
    INCBIN_U16("src_custom/assets/cards/frames/pendulum.gbapal");

static const unsigned short sLinkPalette[] APPEND_ASSET =
    INCBIN_U16("src_custom/assets/cards/frames/link.gbapal");

/* ---- Mini card border tile data ---- */
/* ponytail: agbcc has INCBIN_U16 (16-bit) but no INCBIN (8-bit);
 * store as u16 and cast to u8* — same byte layout. */
static const unsigned short sSynchroMiniBorderU16[] APPEND_ASSET =
    INCBIN_U16("src_custom/assets/cards/frames/synchro_mini.4bpp");

const unsigned short *gCustomCardColorPalettes[NUM_NEW_COLORS] APPEND_RODATA = {
    [COLOR_SYNCHRO - FIRST_NEW_COLOR]  = sSynchroPalette,
    [COLOR_XYZ - FIRST_NEW_COLOR]      = sXyzPalette,
    [COLOR_PENDULUM - FIRST_NEW_COLOR] = sPendulumPalette,
    [COLOR_LINK - FIRST_NEW_COLOR]     = sLinkPalette,
};

/* ---- Mini card border tile pointers (NULL = use vanilla fallback) ---- */
/* ponytail: XYZ/Pendulum/Link mini borders not yet authored; only
 * synchro has one. NULL entries fall back to gUnk_8E17F48[COLOR_NORMAL]. */
const unsigned char *gCustomCardColorBorders[NUM_NEW_COLORS] APPEND_RODATA = {
    [COLOR_SYNCHRO - FIRST_NEW_COLOR]  = (const unsigned char *)sSynchroMiniBorderU16,
    [COLOR_XYZ - FIRST_NEW_COLOR]      = NULL,
    [COLOR_PENDULUM - FIRST_NEW_COLOR] = NULL,
    [COLOR_LINK - FIRST_NEW_COLOR]     = NULL,
};

/* ---- Vanilla externs ---- */
extern u16 *gUnk_8E01364;
extern u16 *gUnk_8E01368;
extern u16 *gUnk_8E0136C;
extern u8 *gUnk_8E137C0;
extern u8 *gUnk_8E137C4[];
extern u8 gUnk_8938384[];

/* ---- Helpers ---- */

u8 CardColorIsNew(u8 color)
{
    return color >= FIRST_NEW_COLOR
        && (color - FIRST_NEW_COLOR) < NUM_NEW_COLORS
        && gRuntimeConfig.enable_new_card_colors == TRUE;
}

const unsigned short *GetCustomCardColorPalette(u8 color)
{
    if (!CardColorIsNew(color))
        return NULL;
    return gCustomCardColorPalettes[color - FIRST_NEW_COLOR];
}

const unsigned char *GetCustomCardColorBorder(u8 color)
{
    if (!CardColorIsNew(color))
        return NULL;
    return gCustomCardColorBorders[color - FIRST_NEW_COLOR];
}

/* sub_80267E0 replacement — guards out-of-bounds color array access */
extern void sub_80267E0(void);
LYN_REPLACE_CHECK(sub_80267E0);
void sub_80267E0__Replacement(void)
{
    u16 i;
    const unsigned short *colorPal;

    CpuCopy16(gUnk_8938384, gUnk_8E0136C, 532);
    for (i = 0; i < 266; i++)
        gUnk_8E0136C[i] += 101;
    CpuCopy32(gUnk_8E137C0, gUnk_8E01364 + 0xCA0, 0x2000);

    /* Pick the correct palette: custom for new colors, vanilla elsewhere */
    colorPal = GetCustomCardColorPalette(gCardInfo.color);
    if (!colorPal)
        colorPal = (const unsigned short *)gUnk_8E137C4[gCardInfo.color];

    CpuCopy32(colorPal, gUnk_8E01368 + 0x40, 40);
}
