#include "global.h"
#include "common-chax.h"
#include "dark_room_of_nightmare.h"
#include "fire_princess.h"
#include "duel_main.h"

extern unsigned char* gDuelTextStrings[];
extern unsigned char g2021D98;
extern u8 g3000C6C;
extern void sub_8024548(void);
extern void sub_8024354(void);
extern void sub_8022080(void);
extern void sub_801CF08(void);
extern unsigned char* g8F9E35C[];
extern unsigned char* g8FA0964[];
extern unsigned short g89DC020[];
extern unsigned short g89DC14C[];
extern unsigned short g89DC23C[];
extern unsigned short g89DC2DC[];
#include "generated/card_activation_text_generated.inc"
#include "generated/card_activation_text_lookup_generated.inc"
static void EmptyCardEffectText(void) {}
static void PlayActivationDescriptionText(const u8 *text);
static void PlayActivationEndSfx(u16 soundId);
static void PlaySpellEffectText(void);
static void PlayMonsterEffectText(void);
static void PlaySpellRebuffText(void);
static void ShowUnusedCardEffectText(void) {}
static void ShowDuelTextWithFade(void);
static void ShowDuelTextWithFadeAlt(void);
static void ShowDuelText(void);
static void ShowCardEffectNameText(void);
static void ShowCardEffectNameTextAlt(void);
static void ShowDestroyWithBackrowText(void);

void ActivatePermanentEffectCardText(u16 cardId);

static void (*const sCardEffectTextHandlers[])(void) APPEND_RODATA = {
  EmptyCardEffectText,
  PlaySpellEffectText,
  PlayMonsterEffectText,
  PlaySpellRebuffText,
  ShowUnusedCardEffectText,
  ShowDuelTextWithFade,
  ShowDuelTextWithFadeAlt,
  ShowDuelText,
  ShowCardEffectNameText,
  ShowCardEffectNameTextAlt,
  ShowDestroyWithBackrowText,
  EmptyCardEffectText,
};

LYN_REPLACE_CHECK(ActivateCardEffectText);
void ActivateCardEffectText__Replacement(void)
{
  struct DuelText duelText;

  if (gDuelType == DUEL_TYPE_LINK) {
    sub_80240BC(&duelText);
    duelText.textId = DUEL_TEXT_LINKING;
    sub_802408C(&duelText);
    g2021D98 = 5;
    sub_8024548();
    do {
      sub_8024354();
    } while (g3000C6C);
  }

  TryNotifyFirePrincessOnLpGainAction();
  sub_801CF08();
  ResolveDarkRoomEffect();
  ResolveFirePrincessEffect();
}

LYN_REPLACE_CHECK(sub_801CF08);
void sub_801CF08__Replacement(void)
{
  const u8 *activationText = GetCardActivationText(gCardEffectTextData.cardId);

  if (activationText != NULL) {
    PlayActivationDescriptionText(activationText);
    sub_8022080();
    return;
  }

  if (gCardEffectTextData.unkA < 11) {
    sCardEffectTextHandlers[gCardEffectTextData.unkA]();
    sub_8022080();
  }
}

static void PlayActivationDescriptionText(const u8 *text) {
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041C94((unsigned char *)text, gCardEffectTextData.cardId, gCardEffectTextData.cardId2, 0, 0);
  SetCardInfo(gCardEffectTextData.cardId);
  PlayActivationEndSfx(g89DC020[gCardInfo.spellEffect]);
}

void ActivatePermanentEffectCardText(u16 cardId) {
  const u8 *text;

  if (gHideEffectText)
    return;

  text = GetCardActivationText(cardId);
  gCardEffectTextData.cardId = cardId;
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  if (text != NULL)
    sub_8041C94((unsigned char *)text, cardId, gCardEffectTextData.cardId2, 0, 0);
  else
    sub_8041C94(g8F9E35C[cardId], cardId, gCardEffectTextData.cardId2, 0, 0);
  SetCardInfo(cardId);
  PlayMusic(g89DC23C[gCardInfo.unk1E]);
  sub_8022080();
}

static void PlayActivationEndSfx(u16 soundId) {
  if (soundId == SOUND_NONE)
    soundId = SFX_SPELL_ACTIVATION_END;
  PlayMusic(soundId);
}

static void PlaySpellEffectText(void) {
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041CCC(gCardEffectTextData.cardId, gCardEffectTextData.cardId2);
  SetCardInfo(gCardEffectTextData.cardId);
  PlayActivationEndSfx(g89DC020[gCardInfo.spellEffect]);
}

static void PlayMonsterEffectText(void) {
  PlayMusic(SFX_MONSTER_EFFECT_ACTIVATION);
  sub_8041CCC(gCardEffectTextData.cardId, gCardEffectTextData.cardId2);
  SetCardInfo(gCardEffectTextData.cardId);
  PlayActivationEndSfx(g89DC14C[gCardInfo.monsterEffect]);
}

static void PlaySpellRebuffText(void) {
  PlayMusic(SFX_ATTACK_REBUFFED);
  sub_8041CCC(gCardEffectTextData.cardId, gCardEffectTextData.cardId2);
  SetCardInfo(gCardEffectTextData.cardId);
  PlayActivationEndSfx(g89DC020[gCardInfo.spellEffect]);
}

static void ShowDuelTextWithFade(void) {
  FadeOutMusic(4);
  PlayMusic(MUSIC_82);
  sub_8041C94(gDuelTextStrings[gCardEffectTextData.textId], gCardEffectTextData.cardId2, gCardEffectTextData.unk4, gCardEffectTextData.unk6, 0);
}

static void ShowDuelTextWithFadeAlt(void) {
  FadeOutMusic(4);
  PlayMusic(MUSIC_82);
  sub_8041C94(gDuelTextStrings[gCardEffectTextData.textId], gCardEffectTextData.cardId2, gCardEffectTextData.unk4, gCardEffectTextData.unk6, 0);
}

static void ShowDuelText(void) {
  sub_8041C94(gDuelTextStrings[gCardEffectTextData.textId], gCardEffectTextData.cardId2, gCardEffectTextData.unk4, gCardEffectTextData.unk6, 0);
}

static void ShowCardEffectNameText(void) {
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041C94(g8F9E35C[gCardEffectTextData.cardId], gCardEffectTextData.cardId, gCardEffectTextData.cardId2, 0, 0);
  SetCardInfo(gCardEffectTextData.cardId);
  PlayMusic(g89DC23C[gCardInfo.unk1E]);
}

static void ShowCardEffectNameTextAlt(void) {
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041C94(g8FA0964[gCardEffectTextData.cardId], gCardEffectTextData.cardId, gCardEffectTextData.cardId2, 0, 0);
  SetCardInfo(gCardEffectTextData.cardId);
  PlayMusic(g89DC2DC[gCardInfo.unk1E]);
}

static void ShowDestroyWithBackrowText(void) {
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041C94(gDuelTextStrings[gCardEffectTextData.textId], gCardEffectTextData.cardId, gCardEffectTextData.cardId2, 0, 0);
  PlayMusic(SFX_DESTROY_MON_WITH_BACKROW);
}
