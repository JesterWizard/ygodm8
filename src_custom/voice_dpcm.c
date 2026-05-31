#include "global.h"
#include "configs/runtime.h"
#include "constants/custom_voices_generated.h"

#include "generated/voice_wave_loader_generated.inc"

extern u8 gCustomVoiceWaveBuffer[];
extern u8 gCustomVoiceTone[];
extern u8 gCustomVoiceSongHeader[];
extern u8 gCustomVoicePartTrack[];

extern struct {
  struct MusicPlayerInfo *unk0;
  u8 filler4[8];
} g8AFBD0C[];

typedef void (*MPlayStartFn)(struct MusicPlayerInfo *, struct SongHeader *);
#define MPlayStart_BODY ((MPlayStartFn)(0x08059D7C + 1))

#define DPCM_BLOCK_SAMPLES 64
#define DPCM_BLOCK_BYTES   33

static const s8 sDpcmLookup[16] APPEND_RODATA = {
  0, 1, 4, 9, 16, 25, 36, 49, -64, -49, -36, -25, -16, -9, -4, -1,
};

static s8 ClampS8(s32 value) {
  if (value < -128)
    return -128;
  if (value > 127)
    return 127;
  return (s8)value;
}

static void DecodeCustomVoiceDpcmBlock(const u8 *blockData, s8 *pcmOut) {
  s32 level;
  u32 outIdx;
  u32 byteIdx;
  u8 packed;
  u8 nibble;

  level = (s8)blockData[0];
  outIdx = 0;
  pcmOut[outIdx++] = (s8)level;

  packed = blockData[1];
  nibble = packed & 0xF;
  level = ClampS8(level + sDpcmLookup[nibble]);
  pcmOut[outIdx++] = (s8)level;

  for (byteIdx = 2; byteIdx < DPCM_BLOCK_BYTES; byteIdx++) {
    packed = blockData[byteIdx];
    nibble = (packed >> 4) & 0xF;
    level = ClampS8(level + sDpcmLookup[nibble]);
    pcmOut[outIdx++] = (s8)level;
    nibble = packed & 0xF;
    level = ClampS8(level + sDpcmLookup[nibble]);
    pcmOut[outIdx++] = (s8)level;
  }
}

static void DecodeCustomVoiceDpcm(const struct WaveData *dpcmWave, s8 *pcmOut) {
  const u8 *src = (const u8 *)dpcmWave->data;
  u32 sampleCount = dpcmWave->size;
  u32 outIdx = 0;
  u32 pos = 0;
  s8 blockSamples[DPCM_BLOCK_SAMPLES];

  while (outIdx < sampleCount) {
    u32 i;

    DecodeCustomVoiceDpcmBlock(&src[pos], blockSamples);
    pos += DPCM_BLOCK_BYTES;

    for (i = 0; i < DPCM_BLOCK_SAMPLES && outIdx < sampleCount; i++) {
      pcmOut[outIdx] = blockSamples[i];
      outIdx++;
    }
  }
}

static void CopyCustomVoicePartTrack(const u8 *src) {
  u8 i;

  for (i = 0; i < CUSTOM_VOICE_PART_SIZE; i++)
    gCustomVoicePartTrack[i] = src[i];
}

void PlayCustomVoiceClip(u8 songIndex) {
  const struct CustomVoiceRomClip *clip;
  struct WaveData *wave;
  struct ToneData *tone;
  struct SongHeader *song;

  if (songIndex >= CUSTOM_VOICE_SONG_COUNT)
    return;

  clip = &sCustomVoiceRomClips[songIndex];
  if (clip->dpcmWave->type != 1)
    return;

  wave = (struct WaveData *)gCustomVoiceWaveBuffer;
  wave->type = 0;
  wave->status = 0;
  wave->freq = clip->dpcmWave->freq;
  wave->loopStart = 0;
  wave->size = clip->dpcmWave->size;
  DecodeCustomVoiceDpcm(clip->dpcmWave, wave->data);

  tone = (struct ToneData *)gCustomVoiceTone;
  tone->type = TONEDATA_TYPE_FIX;
  tone->key = 0x3C;
  tone->length = 0;
  tone->pan_sweep = 0;
  tone->wav = wave;
  tone->attack = 0xFF;
  tone->decay = 0;
  tone->sustain = 0xFF;
  tone->release = 0xFF;

  CopyCustomVoicePartTrack(clip->partTrack);

  song = (struct SongHeader *)gCustomVoiceSongHeader;
  song->trackCount = 1;
  song->blockCount = 0;
  song->priority = 110;
  song->reverb = 0;
  song->tone = tone;
  song->part[0] = gCustomVoicePartTrack;

  MPlayStart_BODY(g8AFBD0C[CUSTOM_VOICE_MPLAY_PLAYER].unk0, song);
}
