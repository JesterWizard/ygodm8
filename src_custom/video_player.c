#include "global.h"
#include "configs/runtime.h"

#include "generated/video_assets_generated.inc"

extern u16 gTitleScreenIdleFrames;
extern void CopyGfxAndInitGfxRegs__Replacement(void);
extern void LoadVRAM(void);

#define RAW_FRAME_BYTES   0xA000
#define PALETTE_BYTES     512

bool8 VideoPlayer_Play(void) {
    const u8 *blob;
    u16 i, frame_idx, total, divider;

    if (VIDEO_COUNT == 0)
        return FALSE;

    blob = sVideoAssets[0].data;
    total = sVideoAssets[0].totalFrames;
    divider = sVideoAssets[0].fpsDivider;

    /* 8bpp 256-color BG3 on charblock 0, screenblock 31 */
    REG_BG3CNT = BGCNT_PRIORITY(3) | BGCNT_CHARBASE(0) | BGCNT_256COLOR | BGCNT_SCREENBASE(31);

    for (frame_idx = 0; frame_idx < total; frame_idx++) {
        u32 idx_off = 4 + PALETTE_BYTES + frame_idx * 8;
        u32 data_off = *(const u32 *)(blob + idx_off);
        const u8 *frame_src = blob + data_off;

        CpuCopy16(frame_src, (void *)0x06000000, RAW_FRAME_BYTES);

        if (frame_idx == 0) {
            CpuCopy16(blob + 4, gPaletteBuffer, PALETTE_BYTES);
            /* Identity tilemap: tile i shows at position i */
            for (i = 0; i < 640; i++)
                ((volatile u16 *)0x0600F800)[i] = i;
            REG_DISPCNT = DISPCNT_MODE_0 | DISPCNT_BG3_ON;
            LoadPalettes();
            LoadBgOffsets();
        }

        for (i = 0; i < divider; i++)
            WaitForVBlank();
    }

    /* -- Fade out video and restart title screen -- */

    /* 1. Clear VRAM charblocks 0-2 (0xC000 covers 768 8bpp tiles) */
    CpuFill16(0, (void *)0x06000000, 0xC000);

    /* 2. Turn off all display layers */
    REG_DISPCNT &= ~(DISPCNT_BG0_ON | DISPCNT_BG1_ON | DISPCNT_BG2_ON | DISPCNT_BG3_ON | DISPCNT_OBJ_ON);
    LoadPalettes();
    for (i = 0; i < 2; i++)
        WaitForVBlank();

    /* 3. Reload title screen */
    gTitleScreenIdleFrames = 0;
    CopyGfxAndInitGfxRegs__Replacement();

    /* 4. Copy shadow buffer -> VRAM */
    LoadVRAM();

    /* 5. Restart music */
    PlayMusic(MUSIC_TITLE_SCREEN);

    /* 6. Wait ~0.5s */
    for (i = 0; i < 30; i++)
        WaitForVBlank();

    /* 7. Fade in */
    REG_DISPCNT = DISPCNT_MODE_0 | DISPCNT_BG3_ON | DISPCNT_OBJ_ON;
    LoadPalettes();

    return FALSE;
}
