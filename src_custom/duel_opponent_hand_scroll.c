#include "global.h"
#include "configs/runtime.h"
#include "duel.h"
#include "duel_opponent_hand_scroll.h"
#include "gfx_reg_buffers.h"
#include "mini_card.h"

extern u16 gOamBuffer[];
extern u16 g8E116BC[];
extern s16 g8E116EE[][5];
extern struct DuelCard *gFixedZones[][MAX_ZONES_IN_ROW];

int sub_80575E0(unsigned char, unsigned char);
int sub_8057600(unsigned char, unsigned char);

#define FIELD_OAM_BASE_INDEX      102
#define FIELD_OAM_U16_INDEX(row, col) \
  ((FIELD_OAM_BASE_INDEX + (row) * MAX_ZONES_IN_ROW + (col)) * 4)

/* Cursor uses OAM 0-3; field cards use 102-126. Hand view uses 4-8 (same as R-hand peek). */
#define OPPONENT_HAND_OAM_SLOT_FIRST 4

#define DUEL_FIELD_WIN0V_DEFAULT 0x8EA0

struct FieldOamEntry {
  u32 a;
  u16 b;
};

static const u16 sBoardScrollVofsExtended[NUM_DUEL_BOARD_ROWS] APPEND_RODATA = {
    76, 92, 92, 92, 138, 16,
};

bool8 IsOpponentHandFieldScrollEnabled(void) {
  return gRuntimeConfig.enable_opponent_hand_field_scroll == TRUE;
}

u16 GetBoardScrollVofs(u8 row) {
  if (!IsOpponentHandFieldScrollEnabled() || row >= NUM_DUEL_BOARD_ROWS)
    return sBoardScrollVofsExtended[0];

  return sBoardScrollVofsExtended[row];
}

bool8 ShouldDrawOpponentHandOnField(void) {
  if (!IsOpponentHandFieldScrollEnabled())
    return FALSE;

  if (gDuelCursor.currentY == OPPONENT_HAND_ROW || gDuelCursor.destY == OPPONENT_HAND_ROW)
    return TRUE;

  return FALSE;
}

bool8 IsLeavingOpponentHandScroll(u8 destRow) {
  if (!IsOpponentHandFieldScrollEnabled())
    return FALSE;

  if (destRow == OPPONENT_HAND_ROW)
    return FALSE;

  return gBG2VOFS == GetBoardScrollVofs(OPPONENT_HAND_ROW);
}

void ApplyOpponentHandFieldWindow(void) {
  REG_WIN0V = WIN_RANGE(160, 0);
}

void RestoreOpponentHandFieldWindow(void) {
  REG_WIN0V = DUEL_FIELD_WIN0V_DEFAULT;
}

static struct FieldOamEntry *FieldOamAt(u8 row, u8 col)
{
  return (struct FieldOamEntry *)&gOamBuffer[FIELD_OAM_U16_INDEX(row, col)];
}

static struct FieldOamEntry *OpponentHandOamAt(u8 col)
{
  return (struct FieldOamEntry *)&gOamBuffer[(OPPONENT_HAND_OAM_SLOT_FIRST + col) * 4];
}

/* OBJ tile staging in cbb4; same layout as sub_8044B90 (R-hand peek). */
static u8 *OpponentHandTilePtr(u8 col)
{
  return gBgVram.cbb0 + 0x10000 + (col % 4) * 256 + (col / 4) * 0x1000;
}

static u16 OpponentHandOamTileIndex(u8 col)
{
  return (col % 4) * 8 + (col / 4) * 128;
}

static s16 GetOpponentHandCardScreenY(void)
{
  return (s16)(OPPONENT_HAND_ROW_SCREEN_Y - gBG2VOFS);
}

static u8 OpponentHandZoneFromCol(u8 col)
{
  return 4 - col;
}

static void ApplyFieldCardOamPriority(struct FieldOamEntry *oam, u8 col, u8 row)
{
  switch (row) {
    case 0:
      oam->a |= 0x6000000;
      break;
    case 1:
      if (!gFixedZones[1][col]->isDefending)
        oam->a |= 0x6000000;
      else
        oam->a |= 0x8000000;
      break;
    case 2:
      if (gFixedZones[2][col]->isDefending)
        oam->a |= 0x4000000;
      else
        oam->a |= 0x2000000;
      break;
    default:
      oam->a |= 0x2000000;
      break;
  }
}

void PlaceFieldCardOam(u8 col, u8 row)
{
  struct FieldOamEntry *oam = FieldOamAt(row, col);
  s16 y = sub_8057600(col, row);
  s16 x = sub_80575E0(col, row);

  oam->a = (u32)((y & 0xFF) | ((x << 16) & 0x01FF0000) | 0x80002100);
  oam->b = (g8E116BC[row * MAX_ZONES_IN_ROW + col] & 0x3FF) | 0x800;
  ApplyFieldCardOamPriority(oam, col, row);
}

static void HideOpponentHandZone(u8 col)
{
  OpponentHandOamAt(col)->a = 0x200;
  OpponentHandOamAt(col)->b = 0;
}

static void PlaceOpponentHandOam(u8 col)
{
  struct FieldOamEntry *oam = OpponentHandOamAt(col);
  s16 x = g8E116EE[0][col];
  s16 y = GetOpponentHandCardScreenY();

  oam->a = (u32)((y & 0xFF) | ((x << 16) & 0x01FF0000) | 0x80002100);
  oam->a |= 0x2000000;
  oam->b = (OpponentHandOamTileIndex(col) & 0x3FF) | 0x800;
}

void DrawOpponentHandZone(u8 col)
{
  struct DuelCard *card;
  u8 *tilePtr;
  u8 zone;

  if (col >= MAX_ZONES_IN_ROW)
    return;

  zone = OpponentHandZoneFromCol(col);
  card = gTurnHands[INACTIVE_DUELIST][zone];
  if (card == NULL || card->id == CARD_NONE) {
    HideOpponentHandZone(col);
    return;
  }

  tilePtr = OpponentHandTilePtr(col);

  if (card->isFaceUp) {
    sub_80573D0(tilePtr, card->id);
    sub_80576B4(tilePtr, card->id);
    sub_80576EC(tilePtr, card->id);
    sub_80572A8(tilePtr, card);
    sub_805733C(tilePtr, card);
    if (card->isLocked) {
      typedef void (*StampLockedFn)(u8 *);
      static StampLockedFn const stampLocked = (StampLockedFn)(0x08057621);

      stampLocked(tilePtr);
    }
  } else {
    CopyFaceDownCardTiles(tilePtr);
    if (card->isLocked) {
      typedef void (*StampLockedFn)(u8 *);
      static StampLockedFn const stampLocked = (StampLockedFn)(0x08057621);

      stampLocked(tilePtr);
    }
  }

  PlaceOpponentHandOam(col);
}

void HideOpponentHandFieldOam(void) {
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++)
    HideOpponentHandZone(col);
}

void DrawOpponentHandOnField(void) {
  typedef void (*RefreshFieldCardTilesFn)(void);
  static RefreshFieldCardTilesFn const refreshFieldCardTiles =
      (RefreshFieldCardTilesFn)(0x080562F5);
  u8 row;
  u8 col;
  struct DuelCard *card;

  /* Hand tiles share cbb4 with the field; refresh field art before compositing hand. */
  refreshFieldCardTiles();

  for (row = 0; row < PLAYER_HAND + 1; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gFixedZones[row][col]->id != CARD_NONE)
        PlaceFieldCardOam(col, row);
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    card = gTurnHands[INACTIVE_DUELIST][OpponentHandZoneFromCol(col)];
    if (card == NULL || card->id == CARD_NONE)
      HideOpponentHandZone(col);
    else
      DrawOpponentHandZone(col);
  }

  CopyMiniCardPalette(gPaletteBuffer + 256);
  ApplyOpponentHandFieldWindow();
  LoadCharblock4();
}

void RebuildFieldCardGfxAfterOpponentHand(void) {
  typedef void (*RefreshFieldCardTilesFn)(void);
  static RefreshFieldCardTilesFn const refreshFieldCardTiles =
      (RefreshFieldCardTilesFn)(0x080562F5);
  u8 row;
  u8 col;

  HideOpponentHandFieldOam();
  RestoreOpponentHandFieldWindow();
  refreshFieldCardTiles();

  for (row = 0; row < PLAYER_HAND + 1; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gFixedZones[row][col]->id != CARD_NONE)
        PlaceFieldCardOam(col, row);
    }
  }

  CopyMiniCardPalette(gPaletteBuffer + 256);
  LoadCharblock4();
}
