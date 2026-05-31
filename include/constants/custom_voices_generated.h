#ifndef GUARD_CUSTOM_VOICES_GENERATED_H
#define GUARD_CUSTOM_VOICES_GENERATED_H

#define CUSTOM_VOICE_SONG_COUNT 1
#define CUSTOM_VOICE_MATCH_COUNT 2
#define CUSTOM_VOICE_OPPONENT_ANY 0xFFFF
#define CUSTOM_VOICE_MPLAY_PLAYER 3
#define CUSTOM_VOICE_PART_SIZE 16
#define CUSTOM_VOICE_EWRAM_BYTES 256
#define CUSTOM_VOICE_SONG_ID_MIN 601
#define CUSTOM_VOICE_SONG_ID_MAX 601

#define SFX_VOICE_DUKE_TURN_START 601

enum CustomVoiceTriggerType {
  CUSTOM_VOICE_TRIGGER_TURN_START = 0,
  CUSTOM_VOICE_TRIGGER_ATTACK_CARD = 1,
  CUSTOM_VOICE_TRIGGER_OPPONENT_LP_BELOW = 2,
};

struct CustomVoiceClipMeta {
  u16 songId;
  u16 duelistId;
  u16 opponentId;
  u16 cardId;
  u16 lpThreshold;
  u8 triggerType;
  u8 priority;
  u8 replaceVanilla;
  u8 songIndex;
};

extern u8 gCustomVoiceBlob[];
void PlayCustomVoiceClip(u8 songIndex);
void TryCustomVoiceOnOpponentLpChange(u16 oldLp, u16 newLp);

#endif // GUARD_CUSTOM_VOICES_GENERATED_H
