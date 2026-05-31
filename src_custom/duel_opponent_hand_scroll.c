#include "global.h"
#include "configs/runtime.h"
#include "card.h"
#include "duel.h"
#include "duel_opponent_hand_scroll.h"
#include "gfx_reg_buffers.h"
#include "mini_card.h"

extern u16 gOamBuffer[];
extern u16 g8E116BC[];
extern s16 g8E116EE[][5];
extern struct DuelCard *gFixedZones[][MAX_ZONES_IN_ROW];
extern struct DuelCard *gTurnHands[2][MAX_ZONES_IN_ROW];

u32 CanPlayerSeeCard(u8 y, u8 x);
void ShowCardDetailView(void);
void UpdateAllDuelGfx(void);

int sub_80575E0(unsigned char, unsigned char);
int sub_8057600(unsigned char, unsigned char);
void sub_80574A8(unsigned char, unsigned char);

typedef void (*StampLockedFn)(u8 *);
typedef void (*StampStageFn)(u8 *, s8);

static StampLockedFn const sStampLocked = (StampLockedFn)(0x08057621);
static StampStageFn const sStampStage = (StampStageFn)(0x0805763D);

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

static struct DuelCard *GetVisibleCardAtBoardPos(u8 y, u8 x) {
  struct DuelCard *card;

  if (IsOpponentHandFieldScrollEnabled() && y == OPPONENT_HAND_ROW) {
    card = gTurnHands[INACTIVE_DUELIST][4 - x];
    if (card == NULL || card->id == CARD_NONE || !card->isFaceUp)
      return NULL;
    return card;
  }

  if (CanPlayerSeeCard(y, x) != 1)
    return NULL;

  return gFixedZones[y][x];
}

bool8 TryShowDuelCursorCardDetails(void) {
  struct DuelCard *card =
      GetVisibleCardAtBoardPos(gDuelCursor.currentY, gDuelCursor.currentX);

  if (card == NULL || !GetTypeGroup(card->id))
    return FALSE;

  gStatMod.card = card->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(card);
  SetFinalStat(&gStatMod);
  ShowCardDetailView();
  UpdateAllDuelGfx();
  return TRUE;
}

void ApplyOpponentHandFieldWindow(void) {
  /*
   * Keep the vanilla bottom info-bar window (sub_8040B4C). A full-screen WIN0V
   * moves the blend strip off-screen and hides the card stats bar while
   * scrolling the opponent hand.
   */
  REG_WIN0V = DUEL_FIELD_WIN0V_DEFAULT;
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

/*
 * Reuse the player-hand row sparse tile map (g8E116BC row 4). Matrix 3
 * (0x6000000), same as opponent backrow, pairs with this layout.
 */
static u8 *OpponentHandTilePtr(u8 col)
{
  return gBgVram.cbb0 + 0x10000
      + g8E116BC[PLAYER_HAND * MAX_ZONES_IN_ROW + col] * 32;
}

static u16 OpponentHandOamTileIndex(u8 col)
{
  return g8E116BC[PLAYER_HAND * MAX_ZONES_IN_ROW + col];
}

static s16 GetOpponentHandCardScreenY(void)
{
  return (s16)(OPPONENT_HAND_ROW_SCREEN_Y - gBG2VOFS);
}

static u8 OpponentHandZoneFromCol(u8 col)
{
  return 4 - col;
}

/* sub_80562F4 only blits art for face-up opponent backrow; add in-play overlays. */
static void ComposeFaceUpFieldMiniCard(u8 *tilePtr, struct DuelCard *card)
{
  sub_80573D0(tilePtr, card->id);
  sub_80576B4(tilePtr, card->id);
  sub_80576EC(tilePtr, card->id);
  sStampStage(tilePtr, GetFinalStage(card));
  sub_80572A8(tilePtr, card);
  sub_805733C(tilePtr, card);
  if (card->isLocked)
    sStampLocked(tilePtr);
}

static void RefreshOpponentBackrowFaceUpTiles(void)
{
  u8 col;
  struct DuelCard *card;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    card = gFixedZones[0][col];
    if (card->id == CARD_NONE || !card->isFaceUp)
      continue;
    ComposeFaceUpFieldMiniCard(
        gBgVram.cbb0 + 0x10000 + g8E116BC[col] * 32, card);
  }
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

/* Row 4 OAM wraps to the top of the screen at opponent-hand scroll VOFS. */
static void HidePlayerHandFieldOam(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    FieldOamAt(PLAYER_HAND, col)->a = 0x200;
    FieldOamAt(PLAYER_HAND, col)->b = 0;
  }
}

static void PlaceOpponentHandOam(u8 col)
{
  struct FieldOamEntry *oam = OpponentHandOamAt(col);
  /* Row 4 fan coords match the vanilla R-hand peek layout at the top edge. */
  s16 x = g8E116EE[PLAYER_HAND][col];
  s16 y = GetOpponentHandCardScreenY();

  /* Same affine matrix 3 as opponent backrow (sub_805754C row 0). */
  oam->a = (u32)((y & 0xFF) | ((x << 16) & 0x01FF0000) | 0x80002100);
  oam->a |= 0x6000000;
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
    ComposeFaceUpFieldMiniCard(tilePtr, card);
  } else {
    CopyFaceDownCardTiles(tilePtr);
    if (card->isLocked)
      sStampLocked(tilePtr);
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

  /* Hide row-4 field OAM first so it cannot linger at the scrolled top edge. */
  HidePlayerHandFieldOam();

  /* Hand tiles share cbb4 with the field; refresh field art before compositing hand. */
  refreshFieldCardTiles();
  RefreshOpponentBackrowFaceUpTiles();

  for (row = 0; row < PLAYER_HAND; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gFixedZones[row][col]->id != CARD_NONE)
        sub_80574A8(col, row);
    }
  }

  HideOpponentHandFieldOam();

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
