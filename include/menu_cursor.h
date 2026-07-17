#ifndef GUARD_MENU_CURSOR_H
#define GUARD_MENU_CURSOR_H

#include "gba/types.h"

#define MENU_CURSOR_EYE 0
#define MENU_CURSOR_KURIBOH 1
#define MENU_CURSOR_PUZZLE 2
#define MENU_CURSOR_COUNT 3

extern u8 gMenuCursorId;
extern u8 gMenuCursorIdFlashPrimary;
extern u8 gMenuCursorIdFlashBackup;

u8 MenuCursor_GetId(void);
void MenuCursor_SetId(u8 id);
void MenuCursor_LoadTiles(void *dest);
void MenuCursor_LoadPalette(u16 *dest);
u16 MenuCursor_GetColor(u8 index);
void MenuCursor_LoadFromFlashPrimary(void);
void MenuCursor_LoadFromFlashBackup(void);
void MenuCursor_SaveToFlashPrimary(void);
void MenuCursor_SaveToFlashBackup(void);
void MenuCursor_Reset(void);

#endif
