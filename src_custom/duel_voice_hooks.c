#include "global.h"
#include "ai.h"
#include "configs/runtime.h"
#include "constants/custom_voices_generated.h"

struct TurnVoice {
  u16 duelistId;
  u16 soundId;
};

struct AttackVoicing {
  u16 duelistId;
  u16 cardId;
  u16 soundId;
};

struct Unk2023E80 {
  u16 playerCardId;
  u16 playerCardAtkOrLifePointsMod;
  u16 playerCardDefense;
  u16 playerLifePoints;
  u8 playerCardAttribute;
  u8 playerMonsterRow;
  u8 unkA;
  u16 opponentCardId;
  u16 opponentCardAtkOrLifePointsMod;
  u16 opponentCardDefense;
  u16 opponentLifePoints;
  u8 opponentCardAttribute;
  u8 opponentMonsterRow;
  u8 unk16;
  u8 filler17;
  u8 id;
  u8 flags;
  u8 unk1A;
  u8 unk1B;
};

struct AI_Command {
  u16 action;
  u8 zone1Position;
  u8 zone2Position;
  u8 zone3Position;
  u8 zone4Position;
  u8 zone5Position;
  u8 zone6Position;
};

void PlayMusic(int);
void m4aSongNumStart(u16 songNum);
void TryPlayingMyTurnVoice(void);
void TryAttackVoicing(void);
void UpdateLifePointsAfterAction(void);
void SwitchTurn(void);

#include "generated/voice_triggers_generated.inc"

enum CustomVoiceAiAttackAction {
  CUSTOM_VOICE_AI_ACTION_DIRECT_ATTACK_NO_TRAP = 7,
  CUSTOM_VOICE_AI_ACTION_ATTACK_FACE_UP_NO_TRAP = 8,
  CUSTOM_VOICE_AI_ACTION_DIRECT_ATTACK_WITH_TRAP = 9,
  CUSTOM_VOICE_AI_ACTION_ATTACK_FACE_UP_WITH_TRAP = 10,
  CUSTOM_VOICE_AI_ACTION_ATTACK_FACE_DOWN_NO_TRAP = 12,
  CUSTOM_VOICE_AI_ACTION_ATTACK_FACE_DOWN_WITH_TRAP = 13,
  CUSTOM_VOICE_AI_ACTION_MONSTER_EFFECT = 23,
};

extern struct TurnVoice gTurnVoices[];
extern struct AI_Command sAI_Command;
extern struct Unk2023E80 sActionData;
extern struct DuelCard *gTurnZones[][MAX_ZONES_IN_ROW];

extern u8 gCustomVoiceLpFiredThisTurn[];

static const u8 sOtherTurn[] APPEND_RODATA = {DUEL_OPPONENT, DUEL_PLAYER};

static const struct AttackVoicing sVanillaAttackVoices[] APPEND_RODATA = {
    {AI_DUELIST_KAIBA, BLUE_EYES_WHITE_DRAGON, SFX_KAIBA_BLUE_EYES_VOICE},
    {AI_DUELIST_JOEY, RED_EYES_B_DRAGON, SFX_JOEY_RED_EYES_VOICE},
    {AI_DUELIST_EVIL_JOEY, RED_EYES_B_DRAGON, SFX_JOEY_RED_EYES_VOICE},
    {AI_DUELIST_ATEM, BLACK_LUSTER_SOLDIER, SFX_ATEM_BLACK_LUSTER_SOLDIER_VOICE},
    {AI_DUELIST_YUGI, DARK_MAGICIAN, SFX_YUGI_DARK_MAGICIAN_VOICE},
    {AI_DUELIST_NONE, CARD_NONE, SOUND_NONE},
};

static void ResetCustomVoiceLpFlags(void) {
  u8 i;

  for (i = 0; i < CUSTOM_VOICE_MATCH_COUNT; i++)
    gCustomVoiceLpFiredThisTurn[i] = 0;
}

void PlayCustomVoiceClip(u8 songIndex) {
  if (songIndex >= CUSTOM_VOICE_SONG_COUNT)
    return;

  m4aSongNumStart((u16)(CUSTOM_VOICE_SONG_ID_MIN + songIndex));
}

static bool8 CustomVoiceClipMatchesDuelist(const struct CustomVoiceClipMeta *clip) {
  if (clip->opponentId != CUSTOM_VOICE_OPPONENT_ANY)
    return clip->opponentId == gDuelData.opponent;

  return clip->duelistId == gDuelData.duelist.id;
}

static bool8 DoesVanillaDuelistHaveTurnVoice(u16 duelistId, u16 *soundId) {
  u8 i;

  for (i = 0; gTurnVoices[i].duelistId; i++) {
    if (gTurnVoices[i].duelistId == duelistId) {
      *soundId = gTurnVoices[i].soundId;
      return TRUE;
    }
  }

  *soundId = 0;
  return FALSE;
}

static void PlayVanillaTurnVoice(void) {
  u16 soundId;

  if (DoesVanillaDuelistHaveTurnVoice(gDuelData.duelist.id, &soundId))
    PlayMusic(soundId);
}

static bool8 TryCustomVoiceMatch(u8 triggerType, u16 cardId, u16 *clipIndexOut) {
  u8 i;
  u8 bestIndex = 0xFF;
  u8 bestPriority = 0;

  for (i = 0; i < CUSTOM_VOICE_MATCH_COUNT; i++) {
    const struct CustomVoiceClipMeta *clip = &sCustomVoiceClips[i];

    if (!CustomVoiceClipMatchesDuelist(clip))
      continue;
    if (clip->triggerType != triggerType)
      continue;
    if (triggerType == CUSTOM_VOICE_TRIGGER_ATTACK_CARD && clip->cardId != cardId)
      continue;

    if (bestIndex == 0xFF || clip->priority >= bestPriority) {
      bestIndex = i;
      bestPriority = clip->priority;
    }
  }

  if (bestIndex == 0xFF)
    return FALSE;

  *clipIndexOut = bestIndex;
  return TRUE;
}

static bool8 TryCustomVoiceTurnStart(void) {
  u16 clipIndex;
  const struct CustomVoiceClipMeta *clip;

  if (!TryCustomVoiceMatch(CUSTOM_VOICE_TRIGGER_TURN_START, CARD_NONE, &clipIndex))
    return FALSE;

  clip = &sCustomVoiceClips[clipIndex];
  PlayCustomVoiceClip(clip->songIndex);
  return TRUE;
}

static bool8 LookupVanillaAttackVoicing(u16 duelistId, u16 cardId, u16 *soundId) {
  u8 i;

  for (i = 0; sVanillaAttackVoices[i].duelistId; i++) {
    if (sVanillaAttackVoices[i].duelistId == duelistId &&
        sVanillaAttackVoices[i].cardId == cardId) {
      *soundId = sVanillaAttackVoices[i].soundId;
      return TRUE;
    }
  }

  *soundId = 0;
  return FALSE;
}

static void PlayVanillaAttackVoicing(u16 cardId) {
  u16 soundId;

  if (LookupVanillaAttackVoicing(gDuelData.duelist.id, cardId, &soundId))
    PlayMusic(soundId);
}

static bool8 IsAttackVoicingAction(u16 action) {
  switch (action) {
  case CUSTOM_VOICE_AI_ACTION_DIRECT_ATTACK_NO_TRAP:
  case CUSTOM_VOICE_AI_ACTION_ATTACK_FACE_UP_NO_TRAP:
  case CUSTOM_VOICE_AI_ACTION_DIRECT_ATTACK_WITH_TRAP:
  case CUSTOM_VOICE_AI_ACTION_ATTACK_FACE_UP_WITH_TRAP:
  case CUSTOM_VOICE_AI_ACTION_ATTACK_FACE_DOWN_NO_TRAP:
  case CUSTOM_VOICE_AI_ACTION_ATTACK_FACE_DOWN_WITH_TRAP:
  case CUSTOM_VOICE_AI_ACTION_MONSTER_EFFECT:
    return TRUE;
  default:
    return FALSE;
  }
}

static bool8 TryCustomVoiceAttack(u16 cardId) {
  u16 clipIndex;
  const struct CustomVoiceClipMeta *clip;

  if (!TryCustomVoiceMatch(CUSTOM_VOICE_TRIGGER_ATTACK_CARD, cardId, &clipIndex))
    return FALSE;

  clip = &sCustomVoiceClips[clipIndex];
  PlayCustomVoiceClip(clip->songIndex);
  return TRUE;
}

void TryCustomVoiceOnOpponentLpChange(u16 oldLp, u16 newLp) {
  u8 i;

  if (newLp >= oldLp)
    return;

  for (i = 0; i < CUSTOM_VOICE_MATCH_COUNT; i++) {
    const struct CustomVoiceClipMeta *clip = &sCustomVoiceClips[i];

    if (clip->triggerType != CUSTOM_VOICE_TRIGGER_OPPONENT_LP_BELOW)
      continue;
    if (!CustomVoiceClipMatchesDuelist(clip))
      continue;
    if (gCustomVoiceLpFiredThisTurn[i])
      continue;
    if (oldLp < clip->lpThreshold || newLp >= clip->lpThreshold)
      continue;

    gCustomVoiceLpFiredThisTurn[i] = 1;
    PlayCustomVoiceClip(clip->songIndex);
  }
}

LYN_REPLACE_CHECK(TryPlayingMyTurnVoice);
void TryPlayingMyTurnVoice__Replacement(void) {
  if (TryCustomVoiceTurnStart())
    return;

  PlayVanillaTurnVoice();
}

LYN_REPLACE_CHECK(TryAttackVoicing);
void TryAttackVoicing__Replacement(void) {
  u8 row2;
  u8 col2;
  u16 cardId;

  if (!IsAttackVoicingAction(sAI_Command.action))
    return;

  row2 = sAI_Command.zone1Position >> 4;
  col2 = sAI_Command.zone1Position & 0xF;
  cardId = gTurnZones[row2][col2]->id;

  if (TryCustomVoiceAttack(cardId))
    return;

  PlayVanillaAttackVoicing(cardId);
}

LYN_REPLACE_CHECK(UpdateLifePointsAfterAction);
void UpdateLifePointsAfterAction__Replacement(void) {
  u16 oldOpponentLp;

  oldOpponentLp = gDuelLifePoints[DUEL_OPPONENT];
  gDuelLifePoints[sActionData.unk1A] = sActionData.playerLifePoints;
  gUnk2023EA0.unk0[0].lifePointsAfterDamage = sActionData.playerLifePoints;
  gDuelLifePoints[sActionData.unk1B] = sActionData.opponentLifePoints;
  gUnk2023EA0.unk0[1].lifePointsAfterDamage = sActionData.opponentLifePoints;
  TryCustomVoiceOnOpponentLpChange(oldOpponentLp, gDuelLifePoints[DUEL_OPPONENT]);
}

LYN_REPLACE_CHECK(SwitchTurn);
void SwitchTurn__Replacement(void) {
  ResetCustomVoiceLpFlags();
  gWhoseTurn = sOtherTurn[gWhoseTurn];
}
