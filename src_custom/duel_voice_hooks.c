#include "global.h"
#include "ai.h"
#include "ai_actions.h"
#include "configs/runtime.h"
#include "constants/custom_voices_generated.h"
#include "duel.h"
#include "overworld.h"
#include "duel_voice.h"
#include "gba/m4a_internal.h"

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
void sub_8041C94(u8 *textPtr, u16, u16, u16, u16);
void OpponentTurnTextAndVoice(void);
void TryAttackVoicing(void);
void LoadObjVRAM(void);
void LoadPalettes(void);
void LoadOam(void);
void sub_80411EC(struct OamData *oam);
void sub_805A5F0(struct MusicPlayerInfo *mplayInfo, u16 trackBits, u16 volume);

extern u8 *gMyTurnStrings[];
extern struct Unk2023E80 sActionData;
extern struct OamData gOamBuffer[];
extern struct MusicPlayerInfo g2025840;
extern struct {
  struct MusicPlayerInfo *unk0;
  unsigned char filler4[8];
} g8AFBD0C[];

#include "generated/voice_turn_text_generated.inc"
#include "generated/voice_triggers_generated.inc"

extern struct TurnVoice gTurnVoices[];
extern struct AI_Command sAI_Command;
extern struct DuelCard *gTurnZones[][MAX_ZONES_IN_ROW];

/* OAM 0-3 = cursor; 102-126 = mini-cards. Textbox does not refresh OAM until end. */
#define DUEL_VOICE_PORTRAIT_OAM_SLOT 127
#define DUEL_VOICE_PORTRAIT_X 8
#define DUEL_VOICE_PORTRAIT_Y 0

static const u8 sPortraitByOpponent[] APPEND_RODATA = {
#include "duel_voice_portrait_table.inc"
};

static const struct AttackVoicing sVanillaAttackVoices[] APPEND_RODATA = {
    {AI_DUELIST_KAIBA, BLUE_EYES_WHITE_DRAGON, SFX_KAIBA_BLUE_EYES_VOICE},
    {AI_DUELIST_JOEY, RED_EYES_B_DRAGON, SFX_JOEY_RED_EYES_VOICE},
    {AI_DUELIST_EVIL_JOEY, RED_EYES_B_DRAGON, SFX_JOEY_RED_EYES_VOICE},
    {AI_DUELIST_ATEM, BLACK_LUSTER_SOLDIER, SFX_ATEM_BLACK_LUSTER_SOLDIER_VOICE},
    {AI_DUELIST_YUGI, DARK_MAGICIAN, SFX_YUGI_DARK_MAGICIAN_VOICE},
    {AI_DUELIST_NONE, CARD_NONE, SOUND_NONE},
};

static bool8 CustomVoiceClipMatchesDuelist(const struct CustomVoiceClipMeta *clip) {
  if (clip->opponentId != CUSTOM_VOICE_OPPONENT_ANY)
    return clip->opponentId == gDuelData.opponent;

  return clip->duelistId == gDuelData.duelist.id;
}

/* Lower duel BGM while custom VO plays on player 3; restore in UpdateDuelBgmVoiceDuck. */
static bool8 CustomVoicePlayerIsBusy(void) {
  struct MusicPlayerInfo *voice = g8AFBD0C[CUSTOM_VOICE_MPLAY_PLAYER].unk0;

  if (voice == NULL)
    return FALSE;
  if (!(voice->status & MUSICPLAYER_STATUS_TRACK))
    return FALSE;
  if (voice->status & MUSICPLAYER_STATUS_PAUSE)
    return FALSE;
  return TRUE;
}

static u16 VoiceDuckVolumeParam(void) {
  u16 percent = gRuntimeConfig.duel_voice_bgm_volume_percent;
  u16 volume;

  if (percent >= 100)
    return 0x100;
  volume = (0x100 * percent) / 100;
  return volume & 0x3FC;
}

static void ApplyBgmVolume(u16 volume) {
  if (g2025840.ident != ID_NUMBER)
    return;
  sub_805A5F0(&g2025840, TRACKS_ALL, volume);
}

static void DuckBgmForVoiceClip(void) {
  if (gRuntimeConfig.duel_voice_bgm_volume_percent >= 100)
    return;
  ApplyBgmVolume(VoiceDuckVolumeParam());
}

void UpdateDuelBgmVoiceDuck(void) {
  u16 percent = gRuntimeConfig.duel_voice_bgm_volume_percent;
  u8 duckedVolX;
  u8 curVolX;

  if (percent >= 100)
    return;
  if (g2025840.ident != ID_NUMBER)
    return;
  if (g2025840.tracks == NULL || g2025840.trackCount == 0)
    return;

  if (CustomVoicePlayerIsBusy()) {
    ApplyBgmVolume(VoiceDuckVolumeParam());
    return;
  }

  /* Restore only if still at our ducked level — avoid fighting fades / new songs. */
  duckedVolX = (u8)(VoiceDuckVolumeParam() >> 2);
  curVolX = g2025840.tracks[0].volX;
  if (curVolX == duckedVolX)
    ApplyBgmVolume(0x100);
}

static void PlayDuelCustomVoiceClip(u8 songIndex) {
  DuckBgmForVoiceClip();
  PlayCustomVoiceClip(songIndex);
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

static bool8 PlayVanillaTurnVoice(void) {
  u16 soundId;

  if (!DoesVanillaDuelistHaveTurnVoice(gDuelData.duelist.id, &soundId))
    return FALSE;

  PlayMusic(soundId);
  return TRUE;
}

static u8 PortraitForCurrentOpponent(void) {
  u16 opponent = gDuelData.opponent;

  if (opponent < ARRAY_COUNT(sPortraitByOpponent) &&
      sPortraitByOpponent[opponent] != PORTRAIT_NONE)
    return sPortraitByOpponent[opponent];

  switch (gDuelData.duelist.id) {
  case AI_DUELIST_YUGI:
    return PORTRAIT_YUGI;
  case AI_DUELIST_ATEM:
    return PORTRAIT_ATEM;
  case AI_DUELIST_KAIBA:
    return PORTRAIT_SETO;
  case AI_DUELIST_JOEY:
    return PORTRAIT_JOEY;
  case AI_DUELIST_EVIL_JOEY:
    return PORTRAIT_DARK_JOEY;
  default:
    return PORTRAIT_NONE;
  }
}

/* Portrait tileNum 256 (cbb4+0x2000) stomps only g8E116BC[0] (opp ST col 0,
 * OAM 102) in the 2D mini-card layout. All other field/hand mini-cards stay up.
 * OAM 0 can also hold a leftover 64x64 portrait (overworld uses y=48) — clear it
 * or a second glitch square appears under the duel portrait at y=0.
 * ponytail: ceiling = that one backrow slot stays hidden; upgrade = evacuate its
 * tiles to free OBJ bands (0x1400+) before LoadPortraitGfx. */
static void HideDuelCursorOam(void) {
  u8 i;

  for (i = 0; i < 4; i++)
    sub_80411EC(&gOamBuffer[i]);
}

static void HidePortraitVramClashMiniCard(void) {
  sub_80411EC(&gOamBuffer[102]);
}

static void PlacePortraitOam(u8 hideBoardSprites) {
  struct OamData *oam;

  (void)hideBoardSprites; /* was full mini-card hide; only OAM 102 clashes now */
  HideDuelCursorOam();
  HidePortraitVramClashMiniCard();

  oam = &gOamBuffer[DUEL_VOICE_PORTRAIT_OAM_SLOT];
  sub_80411EC(oam);
  oam->affineMode = ST_OAM_AFFINE_OFF;
  oam->objMode = ST_OAM_OBJ_NORMAL;
  oam->mosaic = 0;
  oam->bpp = 1;
  oam->shape = ST_OAM_SQUARE;
  oam->size = 3; /* 64x64 */
  oam->priority = 0;
  oam->tileNum = 256;
  oam->x = DUEL_VOICE_PORTRAIT_X;
  oam->y = DUEL_VOICE_PORTRAIT_Y;
  oam->hflip = 0;
  oam->vflip = 0;
  oam->paletteNum = 12;

  LoadOam();
}

void Duel_ShowPortraitForTextbox(u8 portraitId, u8 hideBoardSprites) {
  if (portraitId == PORTRAIT_NONE)
    return;

  LoadPortraitGfx(portraitId, EXPRESSION_NEUTRAL);
  PlacePortraitOam(hideBoardSprites);
  LoadObjVRAM();
  LoadPalettes();
  LoadOam();
}

/* Re-place OAM only — tiles/palettes must already be loaded for this portrait. */
void Duel_PlacePortraitForTextbox(u8 portraitId, u8 hideBoardSprites) {
  if (portraitId == PORTRAIT_NONE)
    return;
  PlacePortraitOam(hideBoardSprites);
}

static void ShowDuelVoicePortrait(void) {
  if (gRuntimeConfig.show_duel_voice_portraits != TRUE)
    return;
  Duel_ShowPortraitForTextbox(PortraitForCurrentOpponent(), FALSE);
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

static bool8 OpponentLpBelowCustomThreshold(void) {
  u8 i;

  for (i = 0; i < CUSTOM_VOICE_MATCH_COUNT; i++) {
    const struct CustomVoiceClipMeta *clip = &sCustomVoiceClips[i];

    if (clip->triggerType != CUSTOM_VOICE_TRIGGER_OPPONENT_LP_BELOW)
      continue;
    if (!CustomVoiceClipMatchesDuelist(clip))
      continue;
    if (gDuelLifePoints[DUEL_OPPONENT] < clip->lpThreshold)
      return TRUE;
  }

  return FALSE;
}

static bool8 ResolveTurnStartClipIndex(u16 *clipIndexOut) {
  u8 triggerType = CUSTOM_VOICE_TRIGGER_TURN_START;

  if (OpponentLpBelowCustomThreshold())
    triggerType = CUSTOM_VOICE_TRIGGER_OPPONENT_LP_BELOW;

  if (!TryCustomVoiceMatch(triggerType, CARD_NONE, clipIndexOut)) {
    if (triggerType != CUSTOM_VOICE_TRIGGER_OPPONENT_LP_BELOW)
      return FALSE;
    return TryCustomVoiceMatch(CUSTOM_VOICE_TRIGGER_TURN_START, CARD_NONE, clipIndexOut);
  }

  return TRUE;
}

static bool8 TryCustomVoiceTurnStart(void) {
  u16 clipIndex;
  const struct CustomVoiceClipMeta *clip;

  if (!ResolveTurnStartClipIndex(&clipIndex))
    return FALSE;

  clip = &sCustomVoiceClips[clipIndex];
  PlayDuelCustomVoiceClip(clip->songIndex);
  return TRUE;
}

static u8 *GetCustomOpponentTurnText(void) {
  u16 clipIndex;
  const struct CustomVoiceClipMeta *clip;

  if (!ResolveTurnStartClipIndex(&clipIndex))
    return NULL;

  clip = &sCustomVoiceClips[clipIndex];
  if (clip->turnText == NULL)
    return NULL;

  return (u8 *)clip->turnText;
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

u8 IsAiDirectAttackVoicingAction(u16 action) {
  switch (action) {
  case AI_ACTION_DIRECT_ATTACK_NO_TRAP:
  case AI_ACTION_DIRECT_ATTACK_WITH_TRAP:
  case AI_ACTION_PERM_CARD_DIRECT_ATTACK_NO_TRAP:
  case AI_ACTION_PERM_CARD_DIRECT_ATTACK_WITH_TRAP:
    return TRUE;
  default:
    return FALSE;
  }
}

void TryPlayCustomOpponentAttackVoice(void) {
  u16 clipIndex;

  if (WhoseTurn() != DUEL_OPPONENT)
    return;

  if (!TryCustomVoiceMatch(CUSTOM_VOICE_TRIGGER_ATTACK_CARD, sActionData.opponentCardId, &clipIndex))
    return;

  PlayDuelCustomVoiceClip(sCustomVoiceClips[clipIndex].songIndex);
}

static bool8 TryCustomVoiceAttack(u16 cardId) {
  u16 clipIndex;
  const struct CustomVoiceClipMeta *clip;

  if (!TryCustomVoiceMatch(CUSTOM_VOICE_TRIGGER_ATTACK_CARD, cardId, &clipIndex))
    return FALSE;

  clip = &sCustomVoiceClips[clipIndex];
  PlayDuelCustomVoiceClip(clip->songIndex);
  return TRUE;
}

LYN_REPLACE_CHECK(OpponentTurnTextAndVoice);
void OpponentTurnTextAndVoice__Replacement(void) {
  u8 *text;
  bool8 voiced;

  voiced = TryCustomVoiceTurnStart();
  if (!voiced)
    voiced = PlayVanillaTurnVoice();

  if (voiced)
    ShowDuelVoicePortrait();

  text = GetCustomOpponentTurnText();
  if (text != NULL)
    sub_8041C94(text, 0, 0, 0, 0);
  else
    sub_8041C94(gMyTurnStrings[gDuelData.opponent], 0, 0, 0, 0);
  /* Portrait OAM cleared by UpdateDuelGfxExceptField inside sub_8041C94. */
}

LYN_REPLACE_CHECK(TryAttackVoicing);
void TryAttackVoicing__Replacement(void) {
  u8 row2;
  u8 col2;
  u16 cardId;

  if (!IsAiDirectAttackVoicingAction(sAI_Command.action))
    return;

  row2 = sAI_Command.zone1Position >> 4;
  col2 = sAI_Command.zone1Position & 0xF;
  cardId = gTurnZones[row2][col2]->id;

  if (TryCustomVoiceAttack(cardId))
    return;

  PlayVanillaAttackVoicing(cardId);
}

