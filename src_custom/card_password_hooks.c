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

u16 sub_803F04C(u8);
void FadeInBlendEffect(void);
u32 sub_8056014(u16);
void LoadBgOffsets(void);
void LoadCharblock2(void);
void LoadCharblock3(void);

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

static void ClearPasswordPopupBg0(void)
{
    u8 y;

    for (y = 0; y < 32; y++)
        CpuFill16(0, gBgVram.sbb1E[y], 64);
}

static void DrawPasswordPopupBg0(const u8 *text)
{
    u8 x;
    u8 y;
    u16 *row;
    const u16 baseTile = 1;
    const u16 pal = 0x1000;

    CpuFill16(0, gBgVram.cbb2, 0x4000);
    ClearPasswordPopupBg0();
    CopyStringTilesToVRAMBuffer(gBgVram.cbb2 + baseTile * 32, text, 0x101);

    for (y = 8; y < 12; y++)
    {
        row = gBgVram.sbb1E[y];
        for (x = 4; x < 26; x++)
            row[x] = pal;
    }

    for (x = 0; text[x] != 0 && x < 20; x++)
    {
        u16 tile = baseTile + (x / 2) * 4 + (x & 1);
        gBgVram.sbb1E[9][6 + x] = pal | tile;
        gBgVram.sbb1E[10][6 + x] = pal | (tile + 2);
    }

    REG_BG0CNT = BGCNT_PRIORITY(0) | BGCNT_CHARBASE(2) | BGCNT_SCREENBASE(30);
    gBG0HOFS = 0;
    gBG0VOFS = 0;
    REG_DISPCNT |= DISPCNT_BG0_ON;
    LoadBgOffsets();
    LoadCharblock2();
    LoadCharblock3();
}

static void ShowPasswordFeedbackPopup(const u8 *text)
{
    u8 i;

    DrawPasswordPopupBg0(text);
    for (i = 0; i < 60; i++)
        WaitForVBlank();
    ClearPasswordPopupBg0();
    LoadCharblock3();
    REG_DISPCNT &= ~DISPCNT_BG0_ON;
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
