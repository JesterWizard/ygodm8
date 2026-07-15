#include "global.h"
#include "configs/runtime.h"
#include "card.h"
#include "text.h"
#include "digit.h"
#include "constants/card_ids.h"

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

const unsigned short *gCustomCardColorPalettes[NUM_NEW_COLORS] APPEND_RODATA = {
    [COLOR_SYNCHRO - FIRST_NEW_COLOR]  = sSynchroPalette,
    [COLOR_XYZ - FIRST_NEW_COLOR]      = sXyzPalette,
    [COLOR_PENDULUM - FIRST_NEW_COLOR] = sPendulumPalette,
    [COLOR_LINK - FIRST_NEW_COLOR]     = sLinkPalette,
};

/* ---- Mini card border tile pointers (NULL = use vanilla fallback) ---- */
/* ponytail: border tile data is complex to author; set non-NULL when
 * custom .4bpp border files are added. Until then, mini card hooks
 * fall back to gUnk_8E17F48[COLOR_NORMAL]. */
const unsigned char *gCustomCardColorBorders[NUM_NEW_COLORS] APPEND_RODATA = {
    [COLOR_SYNCHRO - FIRST_NEW_COLOR]  = NULL,
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

/* CopyCardName replacement — renders synchro card names with
 * palette index 12 (black) instead of the normal indices 4/10
 * (white). This avoids overwriting index 11 which the card
 * border and stars share.
 * ponytail: extend COLOR_SYNCHRO check to
 * COLOR_XYZ / COLOR_PENDULUM / COLOR_LINK when those palettes
 * also define index 12 as black. */
extern void CopyCardName(void);
LYN_REPLACE_CHECK(CopyCardName);
void CopyCardName__Replacement(void)
{
    u8 pos;
    bool32 abbreviate;
    u32 buffer[16];
    const unsigned char* name;

    if (gLanguage == ENGLISH &&
        (gCardInfo.id == BLACK_LUSTER_SOLDIER || gCardInfo.id == BLACK_LUSTER_RITUAL))
        abbreviate = TRUE;
    else
        abbreviate = FALSE;

    name = gCardInfo.name;
    name = GetCurrentLanguageString(name);
    pos = 0;

    while (pos < 10 && *name && *name != 0x24) {
        u16 r1;
        u16 encoding = (gCardInfo.color == COLOR_SYNCHRO) ? 0x411 : 0x44A;

        if (abbreviate && pos == 1) {
            r1 = gUnk_8E00E30[14][1];
            r1 <<= 8;
            r1 |= gUnk_8E00E30[14][0];
            name += 4;
        }
        else if (*name <= 127) {
            r1 = gUnk_8E00E30[*name - 32][1];
            r1 <<= 8;
            r1 |= gUnk_8E00E30[*name - 32][0];
            name++;
        }
        else {
            r1 = name[1] << 8 | name[0];
            name += 2;
        }

        sub_8020968(buffer, r1, encoding);
        CpuFill32(0, g2021B50, 64);
        CpuCopy32(buffer, g2021B50 + 40, 24);
        CpuCopy32(gUnk_8E01364 + (pos * 2 + 133) * 32, g2021B10, 64);
        sub_800DD4C();
        CpuCopy32(g2021B90, gUnk_8E01364 + (pos * 2 + 133) * 32, 64);

        CpuFill32(0, g2021B50, 64);
        CpuCopy32(&buffer[6], g2021B50, 40);
        CpuCopy32(gUnk_8E01364 + (pos * 2 + 134) * 32, g2021B10, 64);
        sub_800DD4C();
        CpuCopy32(g2021B90, gUnk_8E01364 + (pos * 2 + 134) * 32, 64);
        pos++;
    }
}
