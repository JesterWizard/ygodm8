@ m4a HQ mixer configuration for Yu-Gi-Oh! DM (m4a @ 21024 Hz).
@ See documentation/m4a-hq-mixer.md and https://github.com/ipatix/gba-hq-mixer

.set POKE_CHN_INIT, 0
.set ENABLE_STEREO, 1
.set ENABLE_REVERB, 1
.set ENABLE_DMA, 1

@ 21024 Hz frame length 0x160 samples; HQ buffer is samples-per-frame * 4 bytes.
.set M4A_HQ_MIX_FRAME_SAMPLES, 0x160
.set M4A_HQ_MIX_BUFFER_BYTES, 0x580

@ Copied to 0x03000000 at init (vanilla ~0x400 bytes; HQ blob is ~0xAB8).
.set M4A_HQ_MIXER_IW_RAM_BYTES, 0xC00

@ DPCM decode stack must stay above this; mix buffer lives at 0x03002200.
.set M4A_HQ_STACK_BOUNDARY, 0x03007000

.equ hq_buffer_ptr, gM4aHqMixBuffer
