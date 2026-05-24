#include "global.h"
#include "common-chax.h"

extern unsigned char* gDuelTextStrings[];
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
  PlayMusic(g89DC020[gCardInfo.spellEffect]);
}

static void PlaySpellEffectText(void) {
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041CCC(gCardEffectTextData.cardId, gCardEffectTextData.cardId2);
  SetCardInfo(gCardEffectTextData.cardId);
  PlayMusic(g89DC020[gCardInfo.spellEffect]);
}

static void PlayMonsterEffectText(void) {
  PlayMusic(SFX_MONSTER_EFFECT_ACTIVATION);
  sub_8041CCC(gCardEffectTextData.cardId, gCardEffectTextData.cardId2);
  SetCardInfo(gCardEffectTextData.cardId);
  PlayMusic(g89DC14C[gCardInfo.monsterEffect]);
}

static void PlaySpellRebuffText(void) {
  PlayMusic(SFX_ATTACK_REBUFFED);
  sub_8041CCC(gCardEffectTextData.cardId, gCardEffectTextData.cardId2);
  SetCardInfo(gCardEffectTextData.cardId);
  PlayMusic(g89DC020[gCardInfo.spellEffect]);
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
