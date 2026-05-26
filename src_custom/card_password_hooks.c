#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"

#define PASSWORD_LEN 8
#define RESULT_MATCH 10
#define RESULT_MISMATCH 11

extern u8 g8E1167C[];
extern u8 g8E11684[];
extern u8 g8E1165C[][PASSWORD_LEN];
extern u8 g8E11664[][PASSWORD_LEN];
extern u8 g2024588[];
extern u8 g202458C[];
extern u8 gCardPasswordDigits[];
extern u32 gDE7888[];
extern u16 gDEDF50[];
extern u16 gDF0908[];

u16 sub_803F04C(u8);
void FadeInBlendEffect(void);
u32 sub_8056014(u16);
void LoadBgOffsets(void);
void LoadCharblock2(void);
void LoadCharblock3(void);
void LoadPalettes(void);
void LZ77UnCompWram(const void *src, void *dest);

struct PasswordData {
    u16 cardId;
    u8 result;
    u8 digits[PASSWORD_LEN];
};

extern struct PasswordData sPasswordData;

static const u8 sPasswordAcceptedText[] APPEND_RODATA = "Password accepted.";
static const u8 sPasswordRejectedText[] APPEND_RODATA = "Password not found.";

static u8 inline ComparePasswords_Hook(const u8 *a, const u8 *b)
{
    u8 i;
    for (i = 0; i < PASSWORD_LEN; i++)
        if (a[i] != b[i])
            return RESULT_MISMATCH;
    return RESULT_MATCH;
}

void SearchForMatchingCard(void);

LYN_REPLACE_CHECK(SearchForMatchingCard);
APPEND_TEXT void SearchForMatchingCard__Replacement(void)
{
    sPasswordData.cardId = 1;
    while (sPasswordData.cardId < NUM_TOTAL_CARDS)
    {
        const u8 *password = gCardData_NEW[sPasswordData.cardId].password;

        if (ComparePasswords_Hook(g8E11684, password) != RESULT_MATCH &&
            ComparePasswords_Hook(sPasswordData.digits, password) == RESULT_MATCH)
        {
            sPasswordData.result = RESULT_MATCH;
            return;
        }
        sPasswordData.cardId++;
    }

    sPasswordData.result = RESULT_MISMATCH;
}

static void ClearPasswordFeedbackBgs(void)
{
    u8 y;

    for (y = 0; y < 32; y++)
    {
        CpuFill16(0, gBgVram.sbb1D[y], 64);
        CpuFill16(0, gBgVram.sbb1E[y], 64);
    }
}

static void DrawPasswordFeedbackBgs(const u8 *text)
{
    u8 x;
    u8 y;
    u8 len;
    u8 textX;
    const u16 baseTile = 0x180;
    const u16 pal = 0x1000;
    const u8 popupY = 7;
    const u8 textY = popupY + 2;

    CpuFill16(0, gBgVram.cbb2, 0x4000);
    ClearPasswordFeedbackBgs();
    LZ77UnCompWram(gDE7888, gBgVram.cbb2);
    CpuCopy16(gDF0908, gPaletteBuffer + 80, 32);
    gPaletteBuffer[0x10] = 0;
    gPaletteBuffer[0x11] = 0x7FFF;
    gPaletteBuffer[0x12] = 0;
    CopyStringTilesToVRAMBuffer(gBgVram.cbb2 + baseTile * 32, text, 0x101);

    for (y = 0; y < 6; y++)
        CpuCopy16(gDEDF50 + y * 30, gBgVram.sbb1D[popupY + y], 60);

    for (len = 0; text[len] != 0 && len < 20; len++)
        ;
    textX = (30 - len) / 2;

    for (x = 0; x < len; x++)
    {
        u16 tile = baseTile + (x / 2) * 4 + (x & 1);
        gBgVram.sbb1E[textY][textX + x] = pal | tile;
        gBgVram.sbb1E[textY + 1][textX + x] = pal | (tile + 2);
    }

    REG_BG0CNT = BGCNT_PRIORITY(0) | BGCNT_CHARBASE(2) | BGCNT_SCREENBASE(30);
    REG_BG1CNT = BGCNT_PRIORITY(1) | BGCNT_CHARBASE(2) | BGCNT_SCREENBASE(29);
    gBG0HOFS = 0;
    gBG0VOFS = 0;
    gBG1HOFS = 0;
    gBG1VOFS = 0;
    REG_DISPCNT |= DISPCNT_BG0_ON | DISPCNT_BG1_ON;
    LoadBgOffsets();
    LoadPalettes();
    LoadCharblock2();
    LoadCharblock3();
}

static void ShowPasswordFeedbackPopup(const u8 *text)
{
    u8 i;

    DrawPasswordFeedbackBgs(text);
    for (i = 0; i < 60; i++)
        WaitForVBlank();
    ClearPasswordFeedbackBgs();
    LoadCharblock3();
    REG_DISPCNT &= ~(DISPCNT_BG0_ON | DISPCNT_BG1_ON);
}

static void CheckForSpecialPassword1_Hook(void)
{
    sPasswordData.cardId = 0;
    while (TRUE)
    {
        if (ComparePasswords_Hook(g8E1167C, g8E1165C[sPasswordData.cardId]) == RESULT_MATCH)
        {
            sPasswordData.result = RESULT_MISMATCH;
            return;
        }
        if (ComparePasswords_Hook(g8E11684, g8E1165C[sPasswordData.cardId]) != RESULT_MATCH &&
            ComparePasswords_Hook(sPasswordData.digits, g8E1165C[sPasswordData.cardId]) == RESULT_MATCH)
        {
            sPasswordData.result = RESULT_MATCH;
            return;
        }
        sPasswordData.cardId++;
    }
}

static void CheckForSpecialPassword2_Hook(void)
{
    sPasswordData.cardId = 0;
    while (TRUE)
    {
        if (ComparePasswords_Hook(g8E1167C, g8E11664[sPasswordData.cardId]) == RESULT_MATCH)
        {
            sPasswordData.result = RESULT_MISMATCH;
            return;
        }
        if (ComparePasswords_Hook(g8E11684, g8E11664[sPasswordData.cardId]) != RESULT_MATCH &&
            ComparePasswords_Hook(sPasswordData.digits, g8E11664[sPasswordData.cardId]) == RESULT_MATCH)
        {
            sPasswordData.result = RESULT_MATCH;
            return;
        }
        sPasswordData.cardId++;
    }
}

static void ApplySpecialPasswordFlag1_Hook(u16 flag)
{
    g202458C[flag >> 3] |= sub_803F04C(flag & 7);
}

static void ApplySpecialPasswordFlag2_Hook(u16 flag)
{
    g2024588[flag >> 3] |= sub_803F04C(flag & 7);
}

static void TryPlaySpecialPasswordSuccessSfx(u16 flag)
{
    if (flag < 2)
        PlayMusic(SFX_CODE_ENTRY_SUCCESS);
}

static void CopyEnteredPasswordDigits(void)
{
    u8 i;
    for (i = 0; i < PASSWORD_LEN; i++)
        sPasswordData.digits[i] = gCardPasswordDigits[i];
}

static void HandlePasswordMatchFeedback(void)
{
    if (gRuntimeConfig.enable_password_terminal_feedback == TRUE)
    {
        ShowPasswordFeedbackPopup(sPasswordAcceptedText);
        RemoveMoney(1000);
    }
}

void CardPasswordMain(void);

LYN_REPLACE_CHECK(CardPasswordMain);
APPEND_TEXT void CardPasswordMain__Replacement(void)
{
    PasswordTerminalMain();
    CopyEnteredPasswordDigits();
    SearchForMatchingCard__Replacement();

    if (sPasswordData.result == RESULT_MATCH)
    {
        HandlePasswordMatchFeedback();
        SetCardInfo(sPasswordData.cardId);
        PlayMusic(SFX_CODE_ENTRY_SUCCESS);
        ShowCardDetailView();
        AddCardQtyToShop2(sPasswordData.cardId, 1);
        FadeInBlendEffect();
        return;
    }

    CheckForSpecialPassword1_Hook();
    if (sPasswordData.result == RESULT_MATCH)
    {
        HandlePasswordMatchFeedback();
        if (!sub_8056014(sPasswordData.cardId))
        {
            ApplySpecialPasswordFlag1_Hook(sPasswordData.cardId);
        }
        else
            PlayMusic(SFX_FORBIDDEN);
        FadeInBlendEffect();
        return;
    }

    CheckForSpecialPassword2_Hook();
    if (sPasswordData.result == RESULT_MATCH)
    {
        HandlePasswordMatchFeedback();
        ApplySpecialPasswordFlag2_Hook(sPasswordData.cardId);
        TryPlaySpecialPasswordSuccessSfx(sPasswordData.cardId);
    }
    else
    {
        if (gRuntimeConfig.enable_password_terminal_feedback == TRUE)
            ShowPasswordFeedbackPopup(sPasswordRejectedText);
        PlayMusic(SFX_FORBIDDEN);
    }

    FadeInBlendEffect();
}
