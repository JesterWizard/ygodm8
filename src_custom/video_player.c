#include "global.h"
#include "configs/runtime.h"

#include "generated/video_assets_generated.inc"

extern u16 gTitleScreenIdleFrames;
extern void CopyGfxAndInitGfxRegs__Replacement(void);
extern void LoadVRAM(void);
extern void SetVBlankCallback(void (*)(void));
extern u16 gPaletteBuffer[];
extern u8 gVideoPlayerFrameBuf[];

/* Decompress one LZSS-compressed frame into a destination buffer.
 * Pure C — no BIOS SWI calls.  Reads little-endian 16-bit back-refs
 * directly from the compressed blob.
 *
 *   header: u32 with bit31=1, bits 23-0 = decompressed size
 *   body:   1 flag byte, then 8 items per block.
 *           bit=0: literal (1 byte).  bit=1: u16 LE back-ref.
 *             length = (ref >> 12) + 3
 *             offset = (ref & 0xFFF) + 1    (points back in output)
 */
static void DecompressFrame(const u8 *src, u8 *dst) {
    u32 hdr = *(const u32 *)src;
    u32 unc_size = hdr & 0x7FFFFF;
    const u8 *in = src + 4;
    u8 *out = dst;
    u8 *end = dst + unc_size;
    u8 flags;
    int bit;
    u16 ref;
    u32 length, offset;
    const u8 *copy_src;
    u32 j;

    while (out < end) {
        flags = *in++;
        for (bit = 0; bit < 8 && out < end; bit++) {
            if (flags & (0x80 >> bit)) {
                ref = in[0] | ((u16)in[1] << 8);
                in += 2;
                length = (ref >> 12) + 3;
                offset = (ref & 0xFFF) + 1;
                copy_src = out - offset;
                for (j = 0; j < length; j++)
                    *out++ = *copy_src++;
            } else {
                *out++ = *in++;
            }
        }
    }
}

/* Mode 4 VRAM frame buffers (37.5 KB each) */
#define FRAME0_VRAM       ((u8 *)0x06000000)
#define FRAME1_VRAM       ((u8 *)0x0600A000)

/* DISPCNT bit 4: Frame Select (0=Frame0, 1=Frame1 in Mode 4/5) */
#define DISPCNT_FRAME_SEL 0x0010

#define BLOB_PALETTE_BYTES 512
#define BLOB_PAL_OFF      4
#define BLOB_IDX_OFF      (4 + BLOB_PALETTE_BYTES)

bool8 VideoPlayer_Play(void) {
    const u8 *blob;
    u16 i, v, total, divider;

    if (VIDEO_COUNT == 0)
        return FALSE;

    blob = sVideoAssets[0].data;
    total = sVideoAssets[0].totalFrames;
    divider = sVideoAssets[0].fpsDivider;

    /* Kill title screen VBlank callback — it writes tile-mode VRAM which
     * would corrupt our Mode 4 frame buffer (both share 0x06000000). */
    SetVBlankCallback(NULL);

    /* Load palette into both VRAM palette RAM and the shadow buffer. */
    CpuCopy16(blob + BLOB_PAL_OFF, (void *)0x05000000, BLOB_PALETTE_BYTES);
    CpuCopy16(blob + BLOB_PAL_OFF, gPaletteBuffer, BLOB_PALETTE_BYTES);

    /* Decompress frame 0 into EWRAM buffer, then copy to VRAM. */
    {
        u32 off = *(const u32 *)(blob + BLOB_IDX_OFF);
        DecompressFrame(blob + off, gVideoPlayerFrameBuf);
        CpuCopy16(gVideoPlayerFrameBuf, FRAME0_VRAM, 0x9600);
    }

    /* Mode 4: bitmap 256-color, BG2_ON, Frame 0 displayed (bit 4 = 0) */
    REG_DISPCNT = DISPCNT_MODE_4 | DISPCNT_BG2_ON;

    /* Double-buffered playback */
    for (i = 1; i < total; i++) {
        u32 off;
        u8 *target;

        off = *(const u32 *)(blob + BLOB_IDX_OFF + i * 8);

        /* Decompress into the buffer NOT currently displayed */
        if (REG_DISPCNT & DISPCNT_FRAME_SEL)
            target = FRAME0_VRAM;   /* Frame 1 visible, decode into Frame 0 */
        else
            target = FRAME1_VRAM;   /* Frame 0 visible, decode into Frame 1 */

        /* Decompress to EWRAM first (byte access OK), then copy to VRAM
         * (CpuCopy16 uses 16-bit writes which VRAM supports). */
        DecompressFrame(blob + off, gVideoPlayerFrameBuf);
        CpuCopy16(gVideoPlayerFrameBuf, target, 0x9600);

        /* Wait for divider VBlanks on the *current* frame */
        for (v = 0; v < divider; v++)
            WaitForVBlank();

        /* Flip to the newly decompressed frame at VBlank boundary */
        REG_DISPCNT ^= DISPCNT_FRAME_SEL;
    }

    /* -- Fade out video and restart title screen -- */

    CpuFill16(0, FRAME0_VRAM, 0x13000);
    REG_DISPCNT &= ~(DISPCNT_BG0_ON | DISPCNT_BG1_ON | DISPCNT_BG2_ON | DISPCNT_BG3_ON | DISPCNT_OBJ_ON);
    for (i = 0; i < 2; i++)
        WaitForVBlank();

    gTitleScreenIdleFrames = 0;
    CopyGfxAndInitGfxRegs__Replacement();
    LoadVRAM();
    PlayMusic(MUSIC_TITLE_SCREEN);

    for (i = 0; i < 30; i++)
        WaitForVBlank();

    REG_DISPCNT = DISPCNT_MODE_0 | DISPCNT_BG3_ON | DISPCNT_OBJ_ON;
    LoadPalettes();

    return FALSE;
}
