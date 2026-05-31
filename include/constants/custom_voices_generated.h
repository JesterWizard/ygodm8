#ifndef GUARD_CUSTOM_VOICES_GENERATED_H
#define GUARD_CUSTOM_VOICES_GENERATED_H

#define CUSTOM_VOICE_SONG_COUNT 9
#define CUSTOM_VOICE_MATCH_COUNT 33
#define CUSTOM_VOICE_OPPONENT_ANY 0xFFFF
#define CUSTOM_VOICE_MPLAY_PLAYER 3
#define CUSTOM_VOICE_SONG_ID_MIN 601
#define CUSTOM_VOICE_SONG_ID_MAX 609

#define SFX_VOICE_DUKE_1 601
#define SFX_VOICE_DUKE_2 602
#define SFX_VOICE_DUKE_3 603
#define SFX_VOICE_TRISTAN_1 604
#define SFX_VOICE_TRISTAN_2 605
#define SFX_VOICE_TRISTAN_3 606
#define SFX_VOICE_MAI_1 607
#define SFX_VOICE_MAI_2 608
#define SFX_VOICE_MAI_3 609

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
  const u8 *turnText;
};

void PlayCustomVoiceClip(u8 songIndex);

#endif // GUARD_CUSTOM_VOICES_GENERATED_H
