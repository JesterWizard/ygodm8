#ifndef GUARD_DUEL_B_MENU_H
#define GUARD_DUEL_B_MENU_H

#include "gba/types.h"

enum B_MenuOption {
  B_MENU_DETAILS = 0,
  B_MENU_TURN_END = 1,
  B_MENU_DISCARD = 2,
  B_MENU_SURRENDER = 3,
  B_MENU_GY_OPPONENT = 4,
  B_MENU_GY_PLAYER = 5,
};

bool8 DuelBMenu_IsSurrenderEnabled(void);
void DuelBMenu_Init(u8 initialCursor);
void DuelBMenu_HighlightOption(u8 option);
u8 DuelBMenu_GetNextUp(u8 option);
u8 DuelBMenu_GetNextDown(u8 option);
u8 DuelBMenu_GetNextLeft(u8 option);
u8 DuelBMenu_GetNextRight(u8 option);
void DuelBMenu_Surrender(void);
void Duel_GraveyardViewer_Open(u8 fixedDuelist);

void DuelBMenu_RefreshOverlay(u8 highlightedOption);

#endif
