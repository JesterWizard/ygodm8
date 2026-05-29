#include "global.h"
#include "common-chax.h"
#include "custom_decks.h"

typedef struct {
  const u16 *(*getNewGameDeck)(void);
  const CustomDeckEntry *(*getCardShopEntries)(unsigned *count);
  const CustomDuelRewardEntry *(*getCardShopRewards)(unsigned *count);
} CustomDeckModule;

static const u8 sCardShopDuelPrefix[] APPEND_RODATA = {CUSTOM_DIALOGUE_PREFIX_BYTES};

static const CustomDeckModule sCustomDeckModules[] APPEND_RODATA = {
  {
    TeaCustomDeck_GetNewGameDeck,
    TeaCustomDeck_GetCardShopEntries,
    TeaCustomDeck_GetCardShopRewards
  }
};

static const CustomDeckEntry *FindCustomDeckEntry(u8 spriteId, u8 locationId) {
  unsigned moduleIndex;

  for (moduleIndex = 0; moduleIndex < ARRAY_COUNT(sCustomDeckModules); moduleIndex++) {
    const CustomDeckModule *module = &sCustomDeckModules[moduleIndex];
    const CustomDeckEntry *entries;
    unsigned entryCount;
    unsigned entryIndex;

    entries = module->getCardShopEntries(&entryCount);
    for (entryIndex = 0; entryIndex < entryCount; entryIndex++) {
      if (entries[entryIndex].spriteId == spriteId && entries[entryIndex].locationId == locationId)
        return &entries[entryIndex];
    }
  }

  return NULL;
}

static const CustomDuelRewardEntry *FindCustomDuelRewardEntry(u8 spriteId, u8 locationId) {
  unsigned moduleIndex;

  for (moduleIndex = 0; moduleIndex < ARRAY_COUNT(sCustomDeckModules); moduleIndex++) {
    const CustomDeckModule *module = &sCustomDeckModules[moduleIndex];
    const CustomDuelRewardEntry *entries;
    unsigned entryCount;
    unsigned entryIndex;

    entries = module->getCardShopRewards(&entryCount);
    if (entries == NULL)
      continue;
    for (entryIndex = 0; entryIndex < entryCount; entryIndex++) {
      if (entries[entryIndex].spriteId == spriteId && entries[entryIndex].locationId == locationId)
        return &entries[entryIndex];
    }
  }

  return NULL;
}

static struct {
  u8 isActive;
  u8 spriteId;
  u8 locationId;
} sPendingCardShopDuel APPEND_DATA = {0, 0, 0};

u8 CustomDecks_IsEnabled(void) {
  return gRuntimeConfig.enable_custom_decks == TRUE;
}

const u16 *CustomDecks_GetNewGameDeck(void) {
  unsigned i;

  for (i = 0; i < ARRAY_COUNT(sCustomDeckModules); i++) {
    const u16 *deck = sCustomDeckModules[i].getNewGameDeck();

    if (deck != NULL)
      return deck;
  }

  return NULL;
}

u8 CustomDecks_ShouldUseCardShopDuel(u8 spriteId, u8 locationId) {
  return FindCustomDeckEntry(spriteId, locationId) != NULL;
}

const CustomDuelRewardEntry *CustomDecks_FindCardShopDuelRewardEntry(u8 spriteId, u8 locationId) {
  if (CustomDecks_IsEnabled() != TRUE)
    return NULL;
  return FindCustomDuelRewardEntry(spriteId, locationId);
}

void CustomDecks_SetPendingCardShopDuel(u8 spriteId, u8 locationId) {
  sPendingCardShopDuel.spriteId = spriteId;
  sPendingCardShopDuel.locationId = locationId;
  sPendingCardShopDuel.isActive = FindCustomDeckEntry(spriteId, locationId) != NULL;
}

const u16 *CustomDecks_GetPendingCardShopDuelDeck(void) {
  const CustomDeckEntry *entry;

  if (!sPendingCardShopDuel.isActive)
    return NULL;

  entry = FindCustomDeckEntry(sPendingCardShopDuel.spriteId, sPendingCardShopDuel.locationId);
  if (entry == NULL)
    return NULL;
  return entry->deck;
}

const CustomDuelRewardEntry *CustomDecks_GetPendingCardShopDuelRewardEntry(void) {
  const CustomDuelRewardEntry *entry;

  if (!sPendingCardShopDuel.isActive)
    return NULL;

  entry = FindCustomDuelRewardEntry(sPendingCardShopDuel.spriteId, sPendingCardShopDuel.locationId);
  if (entry == NULL)
    return NULL;
  return entry;
}

void CustomDecks_ClearPendingCardShopDuel(void) {
  sPendingCardShopDuel.isActive = 0;
}

const u8 *CustomDecks_BuildCardShopDuelText(u8 *buffer, unsigned bufferSize, u8 spriteId, u8 locationId) {
  const CustomDeckEntry *entry = FindCustomDeckEntry(spriteId, locationId);
  const u8 *body;
  unsigned i;
  unsigned prefixLen = ARRAY_COUNT(sCardShopDuelPrefix);

  if (entry == NULL || bufferSize == 0)
    return NULL;

  if (bufferSize <= prefixLen)
    return NULL;

  for (i = 0; i < prefixLen; i++)
    buffer[i] = sCardShopDuelPrefix[i];
  buffer[2] = entry->portraitId;
  i = prefixLen;
  body = entry->dialogueBody;

  while (*body != 0 && i < bufferSize - 1)
    buffer[i++] = *body++;

  buffer[i] = 0;
  return buffer;
}

struct Script CustomDecks_BuildCardShopDuelScript(u8 *buffer, unsigned bufferSize, u8 spriteId, u8 locationId, const struct Script *fallbackScript) {
  struct Script script;

  script.start = (u8 *)CustomDecks_BuildCardShopDuelText(buffer, bufferSize, spriteId, locationId);
  script.unk4 = fallbackScript->unk4;
  script.unk8 = fallbackScript->unk8;
  return script;
}
