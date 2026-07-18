@ ARM stubs for the Meteo COMET video player integration.
@
@ CallMeteoPlayer jumps into the embedded COMET blob.  On exit the blob's
@ SoftReset sequence is rewritten (meteo_integrate.py) to land here instead,
@ so we return to the title screen without a full ROM reboot through crt0.

#include "asm/macro.inc"

    .section .meteo_stubs, "a", %progbits
    .balign 4

@ Call the COMET player entry point (ARM code at blob base).
@ Must be called from Thumb mode with bit0=0 for ARM interwork.
    .global CallMeteoPlayer
    .type CallMeteoPlayer, %function
CallMeteoPlayer:
    ldr r0, =sMeteoVideoData
    bx r0
    .pool

@ COMET cleanup jumps here instead of BIOS SoftReset.
@ Restores IntrMain, clears EWRAM/VRAM (keeps IWRAM / gIntroVideoPlayed),
@ then enters MeteoReturnToTitle (Thumb).
    .global MeteoExitTrampoline
    .type MeteoExitTrampoline, %function
MeteoExitTrampoline:
    ldr r1, =0x03007FFC
    ldr r0, =IntrMain
    str r0, [r1]

    mov r0, #0xFD              @ EWRAM|palette|VRAM|OAM|SIO|sound|regs; not IWRAM
    swi 0x010000               @ RegisterRamReset

    ldr sp, =0x03007F00

    ldr r0, =MeteoReturnToTitle
    orr r0, r0, #1             @ Thumb
    bx r0
    .pool
