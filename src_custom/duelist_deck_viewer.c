#include "duelist_deck_viewer.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "custom_decks/custom_decks.h"
#include "deck_menu.h"
#include "duel.h"
#include "duel_helpers.h"
#include "event_system.h"
#include "overworld.h"
#include <string.h>

const u16 *GetManifestDuelDeck(u16 opponent);

void InitDeckData(void);
void InitTrunkData(void);
void ClearGraphicsBuffers(void);
void LoadVRAM(void);
unsigned IsPlayerDeckNonempty(void);

#define DUELIST_SCRIPT_SCAN_LIMIT 256

extern struct Duelist *gUnk8E00B30[];

static const signed short sHorizontalDisplacements[] APPEND_RODATA = {
  [DIRECTION_DOWN] = 0,
  [DIRECTION_LEFT] = -1,
  [DIRECTION_UP] = 0,
  [DIRECTION_RIGHT] = 1
};

static const signed short sVerticalDisplacements[] APPEND_RODATA = {
  [DIRECTION_DOWN] = 1,
  [DIRECTION_LEFT] = 0,
  [DIRECTION_UP] = -1,
  [DIRECTION_RIGHT] = 0
};

static inline u8 ObjectWithinDownTalkRange(int y, int x) {
  return y <= 0 && y >= -8 && x <= 4 && x >= -4;
}

static inline u8 ObjectWithinLeftTalkRange(int y, int x) {
  return x <= 8 && x >= 0 && y <= 4 && y >= -4;
}

static inline u8 ObjectWithinUpTalkRange(int y, int x) {
  return y <= 8 && y >= 0 && x <= 4 && x >= -4;
}

static inline u8 ObjectWithinRightTalkRange(int y, int x) {
  return x <= 0 && x >= -8 && y <= 4 && y >= -4;
}

static s8 GetObjectIdInFrontOfPlayer(u8 x, u8 y, u8 playerDirection) {
  u8 i;

  for (i = 1; i < 15; i++) {
    int dy = y - gOverworld.objects[i].y;
    int dx = x - gOverworld.objects[i].x;
    u8 objExists;

    switch (playerDirection) {
      case DIRECTION_DOWN:
        objExists = ObjectWithinDownTalkRange(dy, dx);
        break;
      case DIRECTION_LEFT:
        objExists = ObjectWithinLeftTalkRange(dy, dx);
        break;
      case DIRECTION_UP:
        objExists = ObjectWithinUpTalkRange(dy, dx);
        break;
      default:
        objExists = ObjectWithinRightTalkRange(dy, dx);
        break;
    }
    if (objExists)
      return i;
  }
  return -1;
}

static u8 ObjectHasDuelDialogue(s8 objId) {
  struct Script *scriptR;

  if (objId == -1)
    return FALSE;

  scriptR = gOverworld.objects[objId].scriptR;
  if (scriptR == NULL || scriptR == gOverworld.objects[objId].scriptA)
    return FALSE;

  if (EventSystem_ResolveScript(scriptR)->start == NULL)
    return FALSE;

  return TRUE;
}

static u8 FindDuelistIdInScript(const struct Script *script, u16 *duelistId) {
  const u8 *text;
  u16 i;

  if (script == NULL || script->start == NULL)
    return FALSE;

  text = script->start;
  for (i = 0; i < DUELIST_SCRIPT_SCAN_LIMIT; i++) {
    if (text[i] == 0x40 && text[i + 1] == '0') {
      *duelistId = text[i + 2];
      return TRUE;
    }
  }
  return FALSE;
}

static void CopyDeckIntoMenu(const u16 *deck) {
  unsigned i;

  for (i = 0; i < DECK_SIZE; i++)
    gDeckMenu.cards[i] = deck[i];
  InitDeckData();
}

static const u16 *ResolveDuelistDeck(s8 objId) {
  u16 duelistId;
  const u16 *deck;
  u8 spriteId = gOverworld.objects[objId].spriteId;
  u8 locationId = gOverworld.map.id;

  if (spriteId == SPRITE_TEA)
    return TeaCustomDeck_GetDuelDeck();

  if (CustomDecks_ShouldUseCardShopDuel(spriteId, locationId) == TRUE) {
    CustomDecks_SetPendingCardShopDuel(spriteId, locationId);
    deck = CustomDecks_GetPendingCardShopDuelDeck();
    CustomDecks_ClearPendingCardShopDuel();
    return deck;
  }

  if (FindDuelistIdInScript(EventSystem_ResolveScript(gOverworld.objects[objId].scriptR), &duelistId) != TRUE)
    return NULL;

  deck = GetManifestDuelDeck(duelistId);
  if (deck != NULL)
    return deck;

  if (gUnk8E00B30[duelistId] == NULL)
    return NULL;

  return gUnk8E00B30[duelistId]->deck;
}

u8 DuelistDeckViewer_TryOpen(void) {
  u8 x;
  u8 y;
  s8 objId;
  const u16 *deck;
  u8 savedDeckMenu[sizeof(gDeckMenu)];

  if (gRuntimeConfig.enable_duelist_deck_viewer != TRUE)
    return FALSE;

  x = gOverworld.objects[0].x + sHorizontalDisplacements[gOverworld.objects[0].direction];
  y = gOverworld.objects[0].y + sVerticalDisplacements[gOverworld.objects[0].direction];
  objId = GetObjectIdInFrontOfPlayer(x, y, gOverworld.objects[0].direction);
  if (ObjectHasDuelDialogue(objId) != TRUE)
    return FALSE;

  deck = ResolveDuelistDeck(objId);
  if (deck == NULL)
    return FALSE;

  DECKMENU_SAVE();
  CopyDeckIntoMenu(deck);
  if (IsPlayerDeckNonempty() != 1) {
    DECKMENU_RESTORE();
    InitDeckData();
    return FALSE;
  }

  ClearGraphicsBuffers();
  LoadOam();
  LoadPalettes();
  LoadVRAM();
  InitTrunkData();

  PlayMusic(SFX_SELECT);
  DisableDisplay();
  DeckMenuMainReadOnly();
  DisableDisplay();

  DECKMENU_RESTORE();
  InitDeckData();
  return TRUE;
}
