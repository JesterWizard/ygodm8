#include "ante_card_viewer.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "debug_menu_internal.h"
#include "duel.h"
#include "event_system.h"
#include "menu_cursor.h"
#include "overworld.h"
#include "../custom_decks/custom_decks.h"

#define ANTE_CARD_MAX_CARDS 128
#define ANTE_SCRIPT_SCAN_LIMIT 256
#define ANTE_MINI_CARD_TILE_NUM 0x180
#define ANTE_MINI_CARD_TILE_BYTES 0x1000
#define ANTE_MINI_CARD_X 180
#define ANTE_MINI_CARD_Y 64
#define ANTE_MINI_CARD_OAM_SLOT 1
#define ANTE_CURSOR_PAL_SLOT 15
#define ANTE_TEXT_PAL_WHITE 15
#define ANTE_TEXT_PAL_GOLD 14
#define ANTE_GOLD_TEXT_COLOR 0x031F

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

extern u8 gInputRepeatTimer;
extern u16 gPressedButtons;
extern u16 gOamBuffer[];
extern u16 gUnk_8079424[];
extern struct CardInfo gCardInfo;

void CopyMiniCardPalette(u16 *dest);
const struct CardDrop *GetDuelistAnteDrops(u16 opponent, u8 normalAnte);
void InitButtonMaps(void);
void LoadObjVRAM(void);
void LoadPalettes(void);
void SetCardInfo(u16 id);
void ShowCardDetailView(void);
void sub_80411EC(struct OamData *oam);
void sub_80573D0(void *dest, u16 cardId);

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

static u8 FindDuelistIdInScript(const struct Script *script, u16 *duelistId) {
  const u8 *text;
  u16 i;

  if (script == NULL || script->start == NULL)
    return FALSE;

  text = script->start;
  for (i = 0; i < ANTE_SCRIPT_SCAN_LIMIT; i++) {
    if (text[i] == 0x40 && text[i + 1] == '0') {
      *duelistId = text[i + 2];
      return TRUE;
    }
  }
  return FALSE;
}

static u8 CardAlreadyListed(const u16 *cards, u16 count, u16 cardId) {
  u16 i;

  for (i = 0; i < count; i++) {
    if (cards[i] == cardId)
      return TRUE;
  }
  return FALSE;
}

static void AddCardToList(u16 *cards, u8 *isNormalAnte, u16 *count, u16 cardId, u8 normalAnte) {
  if (cardId == CARD_NONE)
    return;
  if (*count >= ANTE_CARD_MAX_CARDS)
    return;
  if (CardAlreadyListed(cards, *count, cardId) == TRUE)
    return;
  cards[(*count)] = cardId;
  isNormalAnte[(*count)] = normalAnte;
  (*count)++;
}

static void AddCardDropList(u16 *cards, u8 *isNormalAnte, u16 *count, const struct CardDrop *drops, u8 normalAnte) {
  if (drops == NULL)
    return;
  while (drops->card != CARD_NONE) {
    AddCardToList(cards, isNormalAnte, count, drops->card, normalAnte);
    drops++;
  }
}

static void AddUniformCardList(u16 *cards, u8 *isNormalAnte, u16 *count, const u16 *drops, unsigned dropCount, u8 normalAnte) {
  unsigned i;

  if (drops == NULL)
    return;
  for (i = 0; i < dropCount; i++)
    AddCardToList(cards, isNormalAnte, count, drops[i], normalAnte);
}

static u16 BuildCustomAnteCardList(u16 *cards, u8 *isNormalAnte, const CustomDuelRewardEntry *entry) {
  u16 count = 0;

  AddUniformCardList(cards, isNormalAnte, &count, entry->normalDrops, entry->normalDropCount, TRUE);
  AddUniformCardList(cards, isNormalAnte, &count, entry->lowDrops, entry->lowDropCount, FALSE);
  return count;
}

static u16 BuildDuelistAnteCardList(u16 *cards, u8 *isNormalAnte, u16 duelistId) {
  u16 count = 0;

  AddCardDropList(cards, isNormalAnte, &count, GetDuelistAnteDrops(duelistId, TRUE), TRUE);
  AddCardDropList(cards, isNormalAnte, &count, GetDuelistAnteDrops(duelistId, FALSE), FALSE);
  return count;
}

static void ApplyAnteTextPalettes(void) {
  CpuCopy16(gUnk_8079424, &gPaletteBuffer[0xE0], 32);
  gPaletteBuffer[0xE1] = ANTE_GOLD_TEXT_COLOR;
  LoadPalettes();
}

static void FormatAnteCardRow(u8 *out, u16 cardId, u8 selected) {
  u8 i, t = 0;
  const u8 *name;

  (void)selected;

  SetCardInfo(cardId);
  name = GetCurrentLanguageString(gCardInfo.name);
  out[0] = '$';
  out[1] = '0';
  for (i = 0; i < DEBUG_SM_CHARS; i++) {
    if (name[t] != '\0' && name[t] != '$')
      out[2 + i] = name[t++];
    else
      out[2 + i] = ' ';
  }
  out[2 + DEBUG_SM_CHARS] = '\0';
}

static void DrawAnteRows(const u16 *cards, const u8 *isNormalAnte, u16 count, u16 scrollTop, u16 cursor) {
  u8 row;
  u8 buf[2 + DEBUG_SM_CHARS + 1];

  (void)cursor;

  for (row = 0; row < DEBUG_SM_ROWS; row++) {
    u16 index = scrollTop + row;

    if (index < count) {
      FormatAnteCardRow(buf, cards[index], index == cursor);
      DebugMenuCopyLineStartMenu(row, buf);
      DebugMenuSetLinePaletteStartMenu(row, isNormalAnte[index] ? ANTE_TEXT_PAL_GOLD : ANTE_TEXT_PAL_WHITE);
    } else {
      DebugMenuCopyLineStartMenu(row, gDebugMenuStartMenuBlankLine);
      DebugMenuSetLinePaletteStartMenu(row, ANTE_TEXT_PAL_WHITE);
    }
  }
  DebugMenuUploadStartMenuText();
}

static void ClearAnteMiniCard(void) {
  CpuFill16(0, gBgVram.cbb4 + ANTE_MINI_CARD_TILE_NUM * 32, ANTE_MINI_CARD_TILE_BYTES);
}

static void LoadAnteMiniCard(u16 cardId) {
  ClearAnteMiniCard();
  sub_80573D0(gBgVram.cbb4 + ANTE_MINI_CARD_TILE_NUM * 32, cardId);
  CopyMiniCardPalette(gPaletteBuffer + 256);
  MenuCursor_LoadPalette(gPaletteBuffer + 256 + ANTE_CURSOR_PAL_SLOT * 16);
  LoadObjVRAM();
  LoadPalettes();
}

static void ApplyAnteCursorPalette(void) {
  struct OamData *oam = (struct OamData *)gOamBuffer;

  oam->paletteNum = ANTE_CURSOR_PAL_SLOT;
}

static void ApplyAnteMiniCardOam(void) {
  struct OamData *oam = (struct OamData *)&gOamBuffer[ANTE_MINI_CARD_OAM_SLOT * 4];

  oam->y = ANTE_MINI_CARD_Y;
  oam->affineMode = ST_OAM_AFFINE_OFF;
  oam->objMode = ST_OAM_OBJ_NORMAL;
  oam->mosaic = 0;
  oam->bpp = ST_OAM_8BPP;
  oam->shape = 0;
  oam->x = ANTE_MINI_CARD_X;
  oam->hflip = 0;
  oam->vflip = 0;
  oam->size = 2;
  oam->tileNum = ANTE_MINI_CARD_TILE_NUM;
  oam->priority = 2;
  oam->paletteNum = 0;
  oam->affineParam = 0;
}

static void HideAnteMiniCard(void) {
  sub_80411EC((struct OamData *)&gOamBuffer[ANTE_MINI_CARD_OAM_SLOT * 4]);
  LoadOam();
}

static void RenderAnteViewer(const u16 *cards, const u8 *isNormalAnte, u16 count, u16 scrollTop, u16 cursor, u16 *shownCardId) {
  DrawAnteRows(cards, isNormalAnte, count, scrollTop, cursor);

  if (*shownCardId != cards[cursor]) {
    *shownCardId = cards[cursor];
    LoadAnteMiniCard(cards[cursor]);
  }
}

static void AnteCardViewerMain(const u16 *cards, const u8 *isNormalAnte, u16 count) {
  u16 cursor = 0;
  u16 scrollTop = 0;
  u16 shownCardId = CARD_NONE;

  InitButtonMaps();
  DebugMenuLoadStartMenuGraphics();
  ApplyAnteTextPalettes();
  DebugMenuLatchButtons();
  RenderAnteViewer(cards, isNormalAnte, count, scrollTop, cursor, &shownCardId);

  while (1) {
    u16 buttons = DebugMenuButtons();

    if (buttons & B_BUTTON)
      break;
    if (buttons & DPAD_UP && cursor != 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (--cursor < scrollTop)
        scrollTop = cursor;
      RenderAnteViewer(cards, isNormalAnte, count, scrollTop, cursor, &shownCardId);
    }
    if (buttons & DPAD_DOWN && cursor < count - 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      if (++cursor >= scrollTop + DEBUG_SM_ROWS)
        scrollTop = cursor - (DEBUG_SM_ROWS - 1);
      RenderAnteViewer(cards, isNormalAnte, count, scrollTop, cursor, &shownCardId);
    }
    if (buttons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      SetCardInfo(cards[cursor]);
      ShowCardDetailView();
      DebugMenuLoadStartMenuGraphics();
      ApplyAnteTextPalettes();
      shownCardId = CARD_NONE;
      DebugMenuLatchButtons();
      RenderAnteViewer(cards, isNormalAnte, count, scrollTop, cursor, &shownCardId);
    }

    DebugMenuUpdateCursorStartMenu(cursor - scrollTop);
    ApplyAnteCursorPalette();
    ApplyAnteMiniCardOam();
    LoadOam();
    WaitForVBlank();
  }

  PlayMusic(SFX_CANCEL);
  while (gPressedButtons & B_BUTTON)
    WaitForVBlank();
  HideAnteMiniCard();
  ClearAnteMiniCard();
  gInputRepeatTimer = 0;
  DisableDisplay();
}

u8 AnteCardViewer_TryOpen(void) {
  u8 x;
  u8 y;
  s8 objId;
  u16 cards[ANTE_CARD_MAX_CARDS];
  u8 isNormalAnte[ANTE_CARD_MAX_CARDS];
  u16 count = 0;
  u16 duelistId;
  const CustomDuelRewardEntry *customEntry;

  x = gOverworld.objects[0].x + sHorizontalDisplacements[gOverworld.objects[0].direction];
  y = gOverworld.objects[0].y + sVerticalDisplacements[gOverworld.objects[0].direction];
  objId = GetObjectIdInFrontOfPlayer(x, y, gOverworld.objects[0].direction);
  if (objId == -1)
    return FALSE;

  customEntry = CustomDecks_FindCardShopDuelRewardEntry(gOverworld.objects[objId].spriteId, gOverworld.map.id);
  if (customEntry != NULL)
    count = BuildCustomAnteCardList(cards, isNormalAnte, customEntry);
  else if (FindDuelistIdInScript(EventSystem_ResolveScript(gOverworld.objects[objId].scriptR), &duelistId) == TRUE)
    count = BuildDuelistAnteCardList(cards, isNormalAnte, duelistId);

  if (count == 0)
    return FALSE;

  PlayMusic(SFX_SELECT);
  AnteCardViewerMain(cards, isNormalAnte, count);
  return TRUE;
}
