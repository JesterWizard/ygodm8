#include "global.h"
#include "configs/runtime.h"

#include "generated/meteo_video_assets_generated.inc"

extern void CallMeteoPlayer(void);
extern u8 gIntroVideoPlayed; /* IWRAM — survives RegisterRamReset(0xFD) */

extern u16 gUnk2021D00;
extern u8 gUnk2021D04;
extern u8 gLanguage;

extern void sub_8057854(void);
extern void InitButtonMaps(void);
extern void sub_80595C4(void);
extern void m4aSoundMode(u32);
extern void sub_800AEC4(void);
extern void sub_800AD24(void);
extern void ResetLfsrStateBit(void);
extern void sub_80327C8(void);
extern void sub_803276C(void);
extern void TitleScreenMain(void);
extern void OverworldMain(void);

/* Disable all GBA interrupts and set forced blank before entering COMET. */
static void HardStopGba(void) {
    *(volatile u16 *)0x04000208 = 0;
    *(volatile u16 *)0x04000200 = 0;
    (void)*(volatile u16 *)0x04000202;
    *(volatile u32 *)0x03007FFC = 0;
    *(volatile u16 *)0x04000000 = 0x80;
    CpuFill16(0, (void *)0x05000000, 0x400);
}

/*
 * Re-enter title after COMET without crt0 / copyright.
 * Same AgbMain setup, then TitleScreenMain → OverworldMain.
 */
void MeteoReturnToTitle(void) {
    gUnk2021D04 = 0;
    gUnk2021D00 = 0;
    gLanguage = 0;
    sub_8057854();
    InitButtonMaps();
    REG_IME = 0;
    REG_IE = INTR_FLAG_VBLANK | INTR_FLAG_GAMEPAK;
    REG_DISPSTAT = DISPSTAT_VBLANK_INTR;
    REG_IME = 1;
    REG_DISPCNT = DISPCNT_FORCED_BLANK;
    sub_80595C4();
    m4aSoundMode(0x0097FC00);
    sub_800AEC4();
    sub_800AD24();
    ResetLfsrStateBit();
    sub_80327C8();
    sub_803276C();
    TitleScreenMain();
    OverworldMain();
}

bool8 VideoPlayer_Play(void) {
    if (!METE0_VIDEO_AVAILABLE)
        return FALSE;

    if (gIntroVideoPlayed)
        return FALSE;

    gIntroVideoPlayed = 1;

    HardStopGba();
    CallMeteoPlayer(); /* never returns — exit trampoline → MeteoReturnToTitle */

    return FALSE;
}
