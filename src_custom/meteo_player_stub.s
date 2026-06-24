@ ARM stubs for the Meteo COMET video player integration.
@
@ sMeteoVideoData points to the raw Meteo-generated blob (video.gba embedded
@ in .meteo_video section).  It starts with an ARM branch that jumps to the
@ actual COMET player code past the GBA header.
@
@ The player runs to completion (or Start/A skip), then does bx 0x08000000
@ which cold-boots the game.  The exit handler is NOT patched — the blob
@ handles its own exit natively.

#include "asm/macro.inc"

    .section .meteo_stubs, "a", %progbits
    .balign 4

@ Call the COMET player entry point (ARM code at blob base).
@ Must be called from Thumb mode with bit0=0 for ARM interwork.
@ The player never returns — it cold-boots the game on exit.
    .global CallMeteoPlayer
    .type CallMeteoPlayer, %function
CallMeteoPlayer:
    ldr r0, =sMeteoVideoData
    bx r0                          @ ARM mode (bit0=0 on data addr)
    .pool
