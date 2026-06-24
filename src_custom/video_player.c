#include "global.h"
#include "configs/runtime.h"

#include "generated/meteo_video_assets_generated.inc"

extern void CallMeteoPlayer(void);
extern u8 gIntroVideoPlayed;    /* IWRAM flag — survives blob + cold boot */

/* Disable all GBA interrupts (both IME and IE) and set forced blank. */
static void HardStopGba(void) {
    /* Kill interrupt master enable */
    *(volatile u16 *)0x04000208 = 0;
    /* Clear all interrupt enables */
    *(volatile u16 *)0x04000200 = 0;
    /* Acknowledge any pending VBlank by reading the status */
    (void)*(volatile u16 *)0x04000202;
    /* Override IntrMain vector — the COMET player writes its own */
    *(volatile u32 *)0x03007FFC = 0;
    /* Display off (forced blank) */
    *(volatile u16 *)0x04000000 = 0x80;
    /* Clear palette (sanity) */
    CpuFill16(0, (void *)0x05000000, 0x400);
}

bool8 VideoPlayer_Play(void) {
    if (!METE0_VIDEO_AVAILABLE)
        return FALSE;

    /* IWRAM survives the COMET blob and the cold boot.  If we've already
     * played the intro this power cycle, skip re-playing. */
    if (gIntroVideoPlayed)
        return FALSE;

    gIntroVideoPlayed = 1;

    /*
     * Kill all interrupts and set the display to forced blank.
     * The COMET player expects the GBA's boot-time hardware state
     * — IE=0, IME=0, forced blank — not a running game's state.
     */
    HardStopGba();

    /*
     * Call the COMET player.  This never returns — it plays the video
     * then cold-boots the game via bx 0x08000000 (the blob's own exit).
     * Our EWRAM flag gIntroVideoPlayed survives the cold boot so the
     * next call to VideoPlayer_Play skips and the title screen lives.
     */
    CallMeteoPlayer();

    /* Not reached */
    return FALSE;
}
