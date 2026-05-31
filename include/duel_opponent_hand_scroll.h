#ifndef GUARD_DUEL_OPPONENT_HAND_SCROLL_H
#define GUARD_DUEL_OPPONENT_HAND_SCROLL_H

#include "gba/types.h"

#define OPPONENT_HAND_ROW 5
#define NUM_DUEL_BOARD_ROWS 6

/*
 * BG2 row anchor (g8E11720-style). With hand VOFS 16, screen Y is 16 (+2 tiles vs
 * the old 0x10 fan top slot at Y=0, which clipped at the screen edge).
 */
#define OPPONENT_HAND_ROW_SCREEN_Y 0x20

bool8 IsOpponentHandFieldScrollEnabled(void);
u16 GetBoardScrollVofs(u8 row);
bool8 ShouldDrawOpponentHandOnField(void);
void PlaceFieldCardOam(u8 col, u8 row);
void DrawOpponentHandZone(u8 col);
void DrawOpponentHandOnField(void);
void HideOpponentHandFieldOam(void);
void ApplyOpponentHandFieldWindow(void);
void RestoreOpponentHandFieldWindow(void);
void RebuildFieldCardGfxAfterOpponentHand(void);
bool8 IsLeavingOpponentHandScroll(u8 destRow);
bool8 TryShowDuelCursorCardDetails(void);

#endif
