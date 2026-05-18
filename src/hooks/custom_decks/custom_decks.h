#ifndef GUARD_CUSTOM_DECKS_H
#define GUARD_CUSTOM_DECKS_H

#include "gba/types.h"

struct Script;

u8 CustomDecks_IsEnabled(void);
const u16 *CustomDecks_GetNewGameDeck(void);
u8 CustomDecks_ShouldUseCardShopDuel(u8 spriteId, u8 locationId);
struct Script CustomDecks_BuildCardShopDuelScript(u8 spriteId, u8 locationId, const struct Script *fallbackScript);

#endif
