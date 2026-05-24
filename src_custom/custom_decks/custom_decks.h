struct Script;

typedef struct CustomDeckEntry {
  u8 spriteId;
  u8 locationId;
  u8 portraitId;
  const u16 *deck;
  const u8 *dialogueBody;
} CustomDeckEntry;

typedef struct CustomDuelRewardEntry {
  u8 spriteId;
  u8 locationId;
  const u16 *normalDrops;
  unsigned normalDropCount;
  const u16 *lowDrops;
  unsigned lowDropCount;
  u32 capacityYield;
  u16 minDomino;
  u16 maxDomino;
} CustomDuelRewardEntry;

#define CUSTOM_DIALOGUE_PREFIX_BYTES 0x23, 0x34, 0, 0, PORTRAIT_POSITION_AUTO

u8 CustomDecks_IsEnabled(void);
const u16 *CustomDecks_GetNewGameDeck(void);
u8 CustomDecks_ShouldUseCardShopDuel(u8 spriteId, u8 locationId);
void CustomDecks_SetPendingCardShopDuel(u8 spriteId, u8 locationId);
const u16 *CustomDecks_GetPendingCardShopDuelDeck(void);
const CustomDuelRewardEntry *CustomDecks_GetPendingCardShopDuelRewardEntry(void);
void CustomDecks_ClearPendingCardShopDuel(void);
const u8 *CustomDecks_BuildCardShopDuelText(u8 *buffer, unsigned bufferSize, u8 spriteId, u8 locationId);
struct Script CustomDecks_BuildCardShopDuelScript(u8 *buffer, unsigned bufferSize, u8 spriteId, u8 locationId, const struct Script *fallbackScript);

const u16 *TeaCustomDeck_GetNewGameDeck(void);
const u16 *TeaCustomDeck_GetDuelDeck(void);
const CustomDeckEntry *TeaCustomDeck_GetCardShopEntries(unsigned *count);
const CustomDuelRewardEntry *TeaCustomDeck_GetCardShopRewards(unsigned *count);
