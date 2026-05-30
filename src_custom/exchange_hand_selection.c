#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "gfx_reg_buffers.h"
#include "mini_card.h"
#include "exchange_hand_selection.h"

extern u16 gNewButtons;
extern u16 gRepeatedOrNewButtons;

void sub_8044D00(void);
void sub_8044B90(void);
void sub_8044DAC(void);
void UpdateAllDuelGfx(void);
void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void sub_8040880(unsigned char *dest, unsigned char *src);
void sub_8040868(void);
void sub_804078C(void);
void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void MoveCursorLeft(void);
void MoveCursorRight(void);

extern u16 gPressedButtons;

extern unsigned char gDFBA4[];

extern u16 gOamBuffer[];

struct ExchangeOamEntry {
  u32 a;
  u16 b;
};

static const s8 sCursorCornerXOffset[] APPEND_RODATA = { -17, 17, -17, 17 };
static const s8 sCursorCornerYOffset[] APPEND_RODATA = { -16, -16, 16, 16 };
static const u32 sCursorCornerFlipFlags[] APPEND_RODATA = {
  0x80000000,
  0x90000000,
  0xA0000000,
  0xB0000000,
};

#define EXCHANGE_CURSOR_OAM_SLOT 5
#define EXCHANGE_CURSOR_TILE_INDEX 0x180
#define EXCHANGE_CURSOR_ATTR2 0xA180
#define HAND_CARD_HALF_SIZE 32
#define EXCHANGE_CURSOR_ANCHOR_X_OFFSET -32
#define EXCHANGE_CURSOR_ANCHOR_Y_OFFSET -32
#define OPPONENT_HAND_OAM_SLOT_BASE 0
#define PLAYER_HAND_ROW 4

static struct ExchangeOamEntry *ExchangeOamAtSlot(u8 slot)
{
  return (struct ExchangeOamEntry *)&gOamBuffer[slot * 4];
}

static u8 HandZoneFromDisplayIndex(u8 displayIndex)
{
  return 4 - displayIndex;
}

static u8 DisplayIndexHasCard(struct DuelCard **handRow, u8 displayIndex)
{
  return handRow[HandZoneFromDisplayIndex(displayIndex)]->id != CARD_NONE;
}

static u8 FindFirstDisplayIndexWithCard(struct DuelCard **handRow)
{
  u8 displayIndex;

  for (displayIndex = 0; displayIndex < MAX_ZONES_IN_ROW; displayIndex++) {
    if (DisplayIndexHasCard(handRow, displayIndex))
      return displayIndex;
  }

  return 0;
}

static void InitExchangeCursorGfx(void)
{
  sub_8040880(&gBgVram.cbb4[EXCHANGE_CURSOR_TILE_INDEX * 32], gDFBA4);
  sub_8040868();
  LoadCharblock4();
  LoadPalettes();
}

static void GetHandCardCenterFromOamSlot(u8 oamSlot, s16 *centerX, s16 *centerY)
{
  u32 cardA = ExchangeOamAtSlot(oamSlot)->a;

  *centerX = (s16)((cardA >> 16) & 0x1FF) + HAND_CARD_HALF_SIZE;
  *centerY = (s16)(cardA & 0xFF) + HAND_CARD_HALF_SIZE;
}

static void GetHandCardCenter(u8 displayIndex, s16 *centerX, s16 *centerY)
{
  GetHandCardCenterFromOamSlot(OPPONENT_HAND_OAM_SLOT_BASE + displayIndex, centerX, centerY);
}

static void SetCursorCornerOam(u8 slot, s16 x, s16 y, u32 flipFlags)
{
  struct ExchangeOamEntry *oam = ExchangeOamAtSlot(slot);

  oam->a = ((u32)y & 0xFF) | ((u32)(x << 16) & 0x01FF0000) | flipFlags;
  oam->b = EXCHANGE_CURSOR_ATTR2;
}

static void UpdateExchangeHandCursorOam(u8 displayIndex)
{
  s16 centerX;
  s16 centerY;
  u8 corner;

  GetHandCardCenter(displayIndex, &centerX, &centerY);
  centerX += EXCHANGE_CURSOR_ANCHOR_X_OFFSET;
  centerY += EXCHANGE_CURSOR_ANCHOR_Y_OFFSET;

  for (corner = 0; corner < 4; corner++) {
    SetCursorCornerOam(
        EXCHANGE_CURSOR_OAM_SLOT + corner,
        centerX + sCursorCornerXOffset[corner],
        centerY + sCursorCornerYOffset[corner],
        sCursorCornerFlipFlags[corner]);
  }
}

static void HideExchangeHandCursor(void)
{
  u8 corner;

  for (corner = 0; corner < 4; corner++) {
    gOamBuffer[(EXCHANGE_CURSOR_OAM_SLOT + corner) * 4] = 0x0200;
    gOamBuffer[(EXCHANGE_CURSOR_OAM_SLOT + corner) * 4 + 1] = 0;
    gOamBuffer[(EXCHANGE_CURSOR_OAM_SLOT + corner) * 4 + 2] = 0;
    gOamBuffer[(EXCHANGE_CURSOR_OAM_SLOT + corner) * 4 + 3] = 0;
  }

  LoadOam();
}

static void RefreshExchangeHandOam(u8 displayIndex)
{
  UpdateExchangeHandCursorOam(displayIndex);
  LoadOam();
}

static u8 HandZoneHasMatchingType(struct DuelCard **handRow, u8 zone, u8 type)
{
  u16 cardId = handRow[zone]->id;

  if (cardId == CARD_NONE)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.type == type;
}

static u8 HandZoneMatchesPredicate(struct DuelCard **handRow, u8 zone, HandCardPredicate predicate)
{
  u16 cardId = handRow[zone]->id;

  if (cardId == CARD_NONE)
    return FALSE;

  return predicate(cardId);
}

static u8 FindFirstOccupiedHandZone(struct DuelCard **handRow)
{
  u8 zone;

  for (zone = 0; zone < MAX_ZONES_IN_ROW; zone++) {
    if (handRow[zone]->id != CARD_NONE)
      return zone;
  }

  return 0;
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

static u8 MoveDisplayIndex(struct DuelCard **handRow, u8 displayIndex, s8 delta)
{
  u8 attempts = 0;

  while (attempts < MAX_ZONES_IN_ROW) {
    displayIndex = (displayIndex + delta + MAX_ZONES_IN_ROW) % MAX_ZONES_IN_ROW;

    if (DisplayIndexHasCard(handRow, displayIndex))
      return displayIndex;

    attempts++;
  }

  return displayIndex;
}

APPEND_TEXT s8 SelectHandCardMatchingType(struct DuelCard **handRow, u8 type)
{
  struct DuelCursor savedCursor = gDuelCursor;
  u8 scrollY;
  u8 running;

  InitButtonMaps();
  gDuelCursor.currentY = PLAYER_HAND_ROW;
  gDuelCursor.destY = PLAYER_HAND_ROW;
  gDuelCursor.currentX = FindFirstOccupiedHandZone(handRow);
  gDuelCursor.destX = gDuelCursor.currentX;
  DisplayCardInfoBar();
  sub_8041E70(savedCursor.currentY, PLAYER_HAND_ROW);

  WaitForNoButtonsHeld();
  InitButtonMaps();

  running = TRUE;
  while (running) {
    scrollY = gDuelCursor.currentY;
    UpdateFilteredInput_WithRepeat();

    if (gRepeatedOrNewButtons & DPAD_LEFT) {
      MoveCursorLeft();
      DisplayCardInfoBar();
      sub_8041E70(scrollY, gDuelCursor.currentY);
    }
    else if (gRepeatedOrNewButtons & DPAD_RIGHT) {
      MoveCursorRight();
      DisplayCardInfoBar();
      sub_8041E70(scrollY, gDuelCursor.currentY);
    }
    else if (gNewButtons & A_BUTTON) {
      if (HandZoneHasMatchingType(handRow, gDuelCursor.currentX, type)) {
        PlayMusic(SFX_SELECT);
        running = FALSE;
      } else {
        PlayMusic(SFX_FORBIDDEN);
      }
    }

    WaitForVBlank();
  }

  return gDuelCursor.currentX;
}

APPEND_TEXT s8 SelectHandCardMatchingPredicate(struct DuelCard **handRow, HandCardPredicate predicate)
{
  struct DuelCursor savedCursor = gDuelCursor;
  u8 scrollY;
  u8 running;

  InitButtonMaps();
  gDuelCursor.currentY = PLAYER_HAND_ROW;
  gDuelCursor.destY = PLAYER_HAND_ROW;
  gDuelCursor.currentX = FindFirstOccupiedHandZone(handRow);
  gDuelCursor.destX = gDuelCursor.currentX;
  DisplayCardInfoBar();
  sub_8041E70(savedCursor.currentY, PLAYER_HAND_ROW);

  WaitForNoButtonsHeld();
  InitButtonMaps();

  running = TRUE;
  while (running) {
    scrollY = gDuelCursor.currentY;
    UpdateFilteredInput_WithRepeat();

    if (gRepeatedOrNewButtons & DPAD_LEFT) {
      MoveCursorLeft();
      DisplayCardInfoBar();
      sub_8041E70(scrollY, gDuelCursor.currentY);
    }
    else if (gRepeatedOrNewButtons & DPAD_RIGHT) {
      MoveCursorRight();
      DisplayCardInfoBar();
      sub_8041E70(scrollY, gDuelCursor.currentY);
    }
    else if (gNewButtons & A_BUTTON) {
      if (HandZoneMatchesPredicate(handRow, gDuelCursor.currentX, predicate)) {
        PlayMusic(SFX_SELECT);
        running = FALSE;
      } else {
        PlayMusic(SFX_FORBIDDEN);
      }
    }

    WaitForVBlank();
  }

  return gDuelCursor.currentX;
}

APPEND_TEXT s8 SelectExchangeHandCard(struct DuelCard **handRow)
{
  u8 displayIndex;
  u8 running;

  sub_8044D00();
  InitExchangeCursorGfx();

  displayIndex = FindFirstDisplayIndexWithCard(handRow);
  InitButtonMaps();
  RefreshExchangeHandOam(displayIndex);

  running = TRUE;
  while (running) {
    UpdateFilteredInput_WithRepeat();

    if (gRepeatedOrNewButtons & DPAD_LEFT) {
      PlayMusic(SFX_MOVE_CURSOR);
      displayIndex = MoveDisplayIndex(handRow, displayIndex, -1);
      RefreshExchangeHandOam(displayIndex);
    }

    if (gRepeatedOrNewButtons & DPAD_RIGHT) {
      PlayMusic(SFX_MOVE_CURSOR);
      displayIndex = MoveDisplayIndex(handRow, displayIndex, 1);
      RefreshExchangeHandOam(displayIndex);
    }

    if (gNewButtons & A_BUTTON) {
      if (DisplayIndexHasCard(handRow, displayIndex)) {
        PlayMusic(SFX_SELECT);
        running = FALSE;
      } else {
        PlayMusic(SFX_FORBIDDEN);
      }
    }

    WaitForVBlank();
  }

  HideExchangeHandCursor();
  return HandZoneFromDisplayIndex(displayIndex);
}

APPEND_TEXT void ShowExchangeOpponentHandResult(void)
{
  sub_8044B90();
  sub_8044DAC();
  InitButtonMaps();

  while (1) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      break;
    }

    WaitForVBlank();
  }

  UpdateAllDuelGfx();
}
