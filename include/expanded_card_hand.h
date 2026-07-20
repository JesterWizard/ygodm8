#ifndef GUARD_EXPANDED_CARD_HAND_H
#define GUARD_EXPANDED_CARD_HAND_H

#include "gba/types.h"

struct DuelCard;

/* Mid-turn hard cap. EOT discard brings the hand down to HAND_SIZE_LIMIT. */
#define MAX_HAND_CARDS 10
#define HAND_SIZE_LIMIT 6
/* ponytail: equals MAX_HAND_CARDS - MAX_ZONES_IN_ROW (board stays 5-wide). */
#define MAX_HAND_EXTRA 5
#define HAND_SLOT_FIRST_EXTRA 5
#define HAND_SLOT_LAST (MAX_HAND_CARDS - 1)

/* Compat: HAND_SLOT_EXTRA = first overflow index; MAX_HAND_ZONES_SIX = hard cap. */
#define MAX_HAND_ZONES_SIX MAX_HAND_CARDS
#define HAND_SLOT_EXTRA HAND_SLOT_FIRST_EXTRA

/* ponytail: extras live outside gDuel.hands (board still MAX_ZONES_IN_ROW). */
extern struct DuelCard gHandExtraSlots[2][MAX_HAND_EXTRA];

bool8 IsExpandedCardHandEnabled(void);
void ExpandedHand_Init(void);

u8 ExpandedHand_Count(u8 fixedDuelist);
u8 ExpandedHand_MaxSlots(void);
bool8 ExpandedHand_HasDrawRoom(u8 fixedDuelist);
bool8 ExpandedHand_UsesCompressedLayout(u8 fixedDuelist);
bool8 ExpandedHand_UsesBlankOverlapLayout(u8 fixedDuelist);
bool8 ExpandedHand_ShouldHideHandAtkDef(u8 fixedDuelist);
s16 ExpandedHand_GetScreenX(u8 col, u8 fixedDuelist);

struct DuelCard *ExpandedHand_GetFixed(u8 fixedDuelist, u8 col);
struct DuelCard *ExpandedHand_GetPlayerHandZone(u8 col);
struct DuelCard *ExpandedHand_GetTurnHandZone(u8 turnDuelist, u8 col);
struct DuelCard *ExpandedHand_ZoneAtHandRow(struct DuelCard **handRow, u8 col);

u8 ExpandedHand_IsHandRowPtr(struct DuelCard **zonePtr);
u8 ExpandedHand_FixedDuelistForHandRow(struct DuelCard **zonePtr);
u8 ExpandedHand_IsHandZone(const struct DuelCard *zone);
u8 ExpandedHand_OwnerOf(const struct DuelCard *zone);

void ExpandedHand_Compact(u8 fixedDuelist);
void ExpandedHand_OnZoneCleared(struct DuelCard *zone);
void ExpandedHand_EnforceSizeLimit(u8 fixedDuelist);

u8 ExpandedHand_CursorMaxX(u8 row);
void ExpandedHand_ClampCursorX(void);

void ExpandedHand_DrawHandOam(void);
void ExpandedHand_HideExtraOam(void);
void ExpandedHand_RefreshExtraTiles(void);
void ExpandedHand_MaybeBlankHandTiles(void);
void ExpandedHand_ComposeGreyArtTile(u8 *tilePtr);

u16 ExpandedHand_ExtraTileIndex(void);

/* Compat aliases — existing call sites keep compiling during the rename. */
#define IsSixCardHandEnabled IsExpandedCardHandEnabled
#define SixCardHand_Init ExpandedHand_Init
#define SixCardHand_Count ExpandedHand_Count
#define SixCardHand_HasDrawRoom ExpandedHand_HasDrawRoom
#define SixCardHand_UsesCompressedLayout ExpandedHand_UsesCompressedLayout
#define SixCardHand_GetScreenX ExpandedHand_GetScreenX
#define SixCardHand_GetFixed ExpandedHand_GetFixed
#define SixCardHand_GetPlayerHandZone ExpandedHand_GetPlayerHandZone
#define SixCardHand_GetTurnHandZone ExpandedHand_GetTurnHandZone
#define SixCardHand_ZoneAtHandRow ExpandedHand_ZoneAtHandRow
#define SixCardHand_IsHandRowPtr ExpandedHand_IsHandRowPtr
#define SixCardHand_FixedDuelistForHandRow ExpandedHand_FixedDuelistForHandRow
#define SixCardHand_IsHandZone ExpandedHand_IsHandZone
#define SixCardHand_OwnerOf ExpandedHand_OwnerOf
#define SixCardHand_Compact ExpandedHand_Compact
#define SixCardHand_OnZoneCleared ExpandedHand_OnZoneCleared
#define SixCardHand_CursorMaxX ExpandedHand_CursorMaxX
#define SixCardHand_ClampCursorX ExpandedHand_ClampCursorX
#define SixCardHand_DrawHandOam ExpandedHand_DrawHandOam
#define SixCardHand_HideExtraOam ExpandedHand_HideExtraOam
#define SixCardHand_RefreshExtraTiles ExpandedHand_RefreshExtraTiles
#define SixCardHand_ExtraTileIndex ExpandedHand_ExtraTileIndex

#endif
