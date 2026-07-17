#ifndef GUARD_SIX_CARD_HAND_H
#define GUARD_SIX_CARD_HAND_H

#include "gba/types.h"

struct DuelCard;

#define MAX_HAND_ZONES_SIX 6
#define HAND_SLOT_EXTRA 5

/* ponytail: 6th hand card lives outside gDuel.hands (board still MAX_ZONES_IN_ROW). */
extern struct DuelCard gHandExtraSlots[2];

bool8 IsSixCardHandEnabled(void);
void SixCardHand_Init(void);

u8 SixCardHand_Count(u8 fixedDuelist);
bool8 SixCardHand_HasDrawRoom(u8 fixedDuelist);
bool8 SixCardHand_UsesCompressedLayout(u8 fixedDuelist);
s16 SixCardHand_GetScreenX(u8 col, u8 fixedDuelist);

struct DuelCard *SixCardHand_GetFixed(u8 fixedDuelist, u8 col);
struct DuelCard *SixCardHand_GetPlayerHandZone(u8 col);
struct DuelCard *SixCardHand_GetTurnHandZone(u8 turnDuelist, u8 col);
struct DuelCard *SixCardHand_ZoneAtHandRow(struct DuelCard **handRow, u8 col);

u8 SixCardHand_IsHandRowPtr(struct DuelCard **zonePtr);
u8 SixCardHand_FixedDuelistForHandRow(struct DuelCard **zonePtr);
u8 SixCardHand_IsHandZone(const struct DuelCard *zone);
u8 SixCardHand_OwnerOf(const struct DuelCard *zone);

void SixCardHand_Compact(u8 fixedDuelist);
void SixCardHand_OnZoneCleared(struct DuelCard *zone);

u8 SixCardHand_CursorMaxX(u8 row);
void SixCardHand_ClampCursorX(void);

void SixCardHand_DrawHandOam(void);
void SixCardHand_HideExtraOam(void);
void SixCardHand_RefreshExtraTiles(void);

u16 SixCardHand_ExtraTileIndex(void);

#endif
