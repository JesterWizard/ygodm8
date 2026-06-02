@ m4a HQ mixer configuration for Yu-Gi-Oh! DM (m4a @ 21024 Hz).
@ See documentation/m4a-hq-mixer.md and https://github.com/ipatix/gba-hq-mixer

.set POKE_CHN_INIT, 0
.set ENABLE_STEREO, 1
.set ENABLE_REVERB, 1
.set ENABLE_DMA, 1

@ 21024 Hz frame length 0x160 samples; HQ buffer is samples-per-frame * 4 bytes.
.set M4A_HQ_MIX_FRAME_SAMPLES, 0x160
.set M4A_HQ_MIX_BUFFER_BYTES, 0x580

@ HQ mixer execution buffer is allocated in IWRAM via asm/ram_map.s (MixerBuffer).
@ Kept as headroom for stack/DPCM decode; actual copy size comes from MixerSize.
.set M4A_HQ_MIXER_IW_RAM_BYTES, 0xC00

@ DPCM decode stack must stay above this.
.set M4A_HQ_STACK_BOUNDARY, 0x03007000

.equ hq_buffer_ptr, gM4aHqMixBuffer
