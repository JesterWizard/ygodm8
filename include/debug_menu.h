#ifndef GUARD_DEBUG_MENU_H
#define GUARD_DEBUG_MENU_H

void DebugMenuMain(void);
void DebugMenuClearPortraitObjStash(void);
void DebugMenu_ApplyPendingMapTeleport(void);
void DebugMenu_ApplyPendingScene(void);
void DebugMenu_TeardownForDuel(void);
void DebugMenu_ReinitAfterDuel(void);
void OverworldRestoreAfterDebugMenu(void);

#endif // GUARD_DEBUG_MENU_H
