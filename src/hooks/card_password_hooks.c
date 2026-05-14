#include "global.h"
#include "common-chax.h"

#define PASSWORD_LEN 8
#define RESULT_MATCH 10
#define RESULT_MISMATCH 11

extern u8 g8E1167C[];
extern u8 g8E11684[];

struct PasswordData {
    u16 cardId;
    u8 result;
    u8 digits[PASSWORD_LEN];
};

extern struct PasswordData sPasswordData;

static u8 inline ComparePasswords_Hook(const u8 *a, const u8 *b)
{
    u8 i;
    for (i = 0; i < PASSWORD_LEN; i++)
        if (a[i] != b[i])
            return RESULT_MISMATCH;
    return RESULT_MATCH;
}

static u8 PasswordMatchesCard_Hook(u16 cardId)
{
    const u8 *password = gCardData_NEW[cardId].password;

    if (ComparePasswords_Hook(g8E1167C, password) == RESULT_MATCH)
        return 0;
    if (ComparePasswords_Hook(g8E11684, password) == RESULT_MATCH)
        return 1;
    return 2;
}

void SearchForMatchingCard(void);

LYN_REPLACE_CHECK(SearchForMatchingCard);
APPEND_TEXT void SearchForMatchingCard__Replacement(void)
{
    sPasswordData.cardId = 0;
    while (TRUE)
    {
        switch (PasswordMatchesCard_Hook(sPasswordData.cardId))
        {
        case 1:
            break;
        case 0:
            sPasswordData.result = RESULT_MISMATCH;
            return;
        default:
            if (ComparePasswords_Hook(sPasswordData.digits, gCardData_NEW[sPasswordData.cardId].password) == RESULT_MATCH)
            {
                sPasswordData.result = RESULT_MATCH;
                return;
            }
        }
        sPasswordData.cardId++;
    }
}
