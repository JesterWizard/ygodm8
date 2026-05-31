#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "duel_opponent_hand_scroll.h"

extern unsigned short g8E0D5A6[];
extern u8 g8E0D5A1[];

static u16 GetScrollTargetVofs(u8 row) {
  if (IsOpponentHandFieldScrollEnabled() && row < NUM_DUEL_BOARD_ROWS)
    return GetBoardScrollVofs(row);

  return g8E0D5A6[row];
}

static bool8 ScrollSnapRequired(u8 destRow) {
  if (!IsOpponentHandFieldScrollEnabled())
    return FALSE;

  if (destRow == OPPONENT_HAND_ROW)
    return TRUE;

  return IsLeavingOpponentHandScroll(destRow);
}

u32 AdjustBackgroundBeforeTurnStart(u8 row);

LYN_REPLACE_CHECK(AdjustBackgroundBeforeTurnStart);
u32 AdjustBackgroundBeforeTurnStart__Replacement(u8 row) {
  if (IsOpponentHandFieldScrollEnabled() && row < NUM_DUEL_BOARD_ROWS)
    return gBG2VOFS = GetBoardScrollVofs(row);

  return gBG2VOFS = g8E0D5A1[row];
}

void DisplayCardAttrTypeInInfoBar(void);
void CopyAttributeIconTiles (u8, u8*);
void CopyAttributeIconPal (u8, u16*);
void CopyTypeIconTiles (u8, u8*);
void CopyTypeIconPal (u8, u16*);

LYN_REPLACE_CHECK(DisplayCardAttrTypeInInfoBar);
void DisplayCardAttrTypeInInfoBar__Replacement(void) {
  CopyAttributeIconTiles(gCardInfo.attribute, gBgVram.cbb0 + 0x8580);
  CopyAttributeIconPal(gCardInfo.attribute, gPaletteBuffer + 96);
  CopyTypeIconTiles(gCardInfo.type, gBgVram.cbb0 + 0x8500);
  CopyTypeIconPal(gCardInfo.type, gPaletteBuffer + 80);
}

void sub_8041D78(u8 arg0);
void sub_8041DF0(u8 arg0);
void sub_8057808(void);
void sub_804078C(void);
void sub_8040FDC(void);
void sub_80411D4(void);
void LoadOam(void);
void LoadBgOffsets(void);

static void FlushPartialDuelGfx(void) {
  if (ShouldDrawOpponentHandOnField())
    DrawOpponentHandOnField();
  else
    RestoreOpponentHandFieldWindow();

  LoadOam();
  LoadBgOffsets();
  CpuCopy32(gBgVram.cbb0 + 0x8040, (unsigned char *)BG_VRAM + 0x8040, 0x740);
  CpuCopy16(gPaletteBuffer + 0x50, (u16 *)PLTT + 0x50, 0x40);
}

static void FlushDuelGfxAfterCursorMove(void) {
  if (gRuntimeConfig.turn_off_visual_scanner == TRUE)
    sub_80411D4();
  else
    FlushPartialDuelGfx();
}

LYN_REPLACE_CHECK(sub_8040FDC);
void sub_8040FDC__Replacement(void) {
  if (gRuntimeConfig.turn_off_visual_scanner == TRUE)
    sub_80411D4();
  else
    FlushPartialDuelGfx();
}

LYN_REPLACE_CHECK(sub_8041D78);
void sub_8041D78__Replacement(u8 arg0) {
  bool8 leavingHand = IsLeavingOpponentHandScroll(arg0);

  if (gRuntimeConfig.turn_off_visual_scanner == TRUE || ScrollSnapRequired(arg0)) {
    gBG2VOFS = GetScrollTargetVofs(arg0);
    sub_8057808();
    sub_804078C();
    WaitForVBlank();
    if (leavingHand)
      RebuildFieldCardGfxAfterOpponentHand();
    FlushDuelGfxAfterCursorMove();
    return;
  }

  while (gBG2VOFS > GetScrollTargetVofs(arg0) + 256) {
    gBG2VOFS -= 256;
    sub_8057808();
    WaitForVBlank();
    sub_8040FDC();
  }
  gBG2VOFS = GetScrollTargetVofs(arg0);
  sub_8057808();
  sub_804078C();
  WaitForVBlank();
  if (leavingHand)
    RebuildFieldCardGfxAfterOpponentHand();
  FlushDuelGfxAfterCursorMove();
}

LYN_REPLACE_CHECK(sub_8041DF0);
void sub_8041DF0__Replacement(u8 arg0) {
  bool8 leavingHand = IsLeavingOpponentHandScroll(arg0);

  if (gRuntimeConfig.turn_off_visual_scanner == TRUE || ScrollSnapRequired(arg0)) {
    gBG2VOFS = GetScrollTargetVofs(arg0);
    sub_8057808();
    sub_804078C();
    WaitForVBlank();
    if (leavingHand)
      RebuildFieldCardGfxAfterOpponentHand();
    FlushDuelGfxAfterCursorMove();
    return;
  }

  while (gBG2VOFS < GetScrollTargetVofs(arg0) - 256) {
    gBG2VOFS += 256;
    sub_8057808();
    WaitForVBlank();
    sub_8040FDC();
  }
  gBG2VOFS = GetScrollTargetVofs(arg0);
  sub_8057808();
  sub_804078C();
  WaitForVBlank();
  if (leavingHand)
    RebuildFieldCardGfxAfterOpponentHand();
  FlushDuelGfxAfterCursorMove();
}
