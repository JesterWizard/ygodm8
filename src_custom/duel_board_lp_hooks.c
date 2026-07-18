#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "digit.h"
#include "duel.h"
#include "timed_duel.h"
#include "mechanics_tutorial.h"
#include "duel_bgm_tempo.h"
#include "duel_voice.h"
#include "duel_status.h"
#include "gba/defines.h"
#include "text.h"

extern unsigned short gDuelLifePoints[];
extern u8 gDigitBufferU16[];
extern u16 gDuelBoardTurnCount;
extern u16 gTimedDuelTimerFrames;
extern u16 g80F0F00[];

void sub_80411D4(void);
void InitDuelistStatus(void);
void LoadVRAM(void);
void LoadBgOffsets(void);
void LoadOam(void);
void FlushDuelFieldLayerToHardware(void);

/* Small font (CopyStringTilesToVRAMBuffer flag 0x001). Tile map index must equal
 * charBufOffset / 32 so tile graphics and tilemap entries refer to the same slots. */
#define BOARD_LP_TILE_ATTR         0x3000
#define BOARD_LP_MAP_BASE          0xD800
#define BOARD_LP_MAX_DIGITS        5
#define BOARD_LP_CHARBUF_TILE_BYTES 32

#define BOARD_LP_BASE_TILE_PLAYER  0x380
#define BOARD_LP_CHARBUF_PLAYER    (BOARD_LP_BASE_TILE_PLAYER * BOARD_LP_CHARBUF_TILE_BYTES)
#define BOARD_LP_BASE_TILE_OPPONENT (BOARD_LP_BASE_TILE_PLAYER + BOARD_LP_MAX_DIGITS)
#define BOARD_LP_CHARBUF_OPPONENT  (BOARD_LP_BASE_TILE_OPPONENT * BOARD_LP_CHARBUF_TILE_BYTES)

#define BOARD_LP_PLAYER_X 1
#define BOARD_LP_PLAYER_Y 19
#define BOARD_LP_OPPONENT_X 25
#define BOARD_LP_OPPONENT_Y 19

#define BOARD_TURN_TILE_ATTR         0x7000
#define BOARD_TURN_MAX_DIGITS        3
#define BOARD_TIMER_MAX_CHARS        5 /* "MM:SS" */
#define BOARD_TURN_BASE_TILE         (BOARD_LP_BASE_TILE_OPPONENT + BOARD_LP_MAX_DIGITS)
#define BOARD_TURN_CHARBUF           (BOARD_TURN_BASE_TILE * BOARD_LP_CHARBUF_TILE_BYTES)
#define BOARD_TURN_X                 14
#define BOARD_TIMER_X                13
#define BOARD_TURN_Y                 19

static void RemapSmallFontTilesToColorIndex(u8 *tiles, u32 byteCount, u8 fromIndex, u8 toIndex) {
  u32 i;

  for (i = 0; i < byteCount; i++) {
    u8 byte = tiles[i];
    u8 lo = byte & 0x0F;
    u8 hi = byte >> 4;

    if (lo == fromIndex)
      lo = toIndex;
    if (hi == fromIndex)
      hi = toIndex;
    tiles[i] = (hi << 4) | lo;
  }
}

static void EnsureBoardLpPalette(void) {
  /* Same bank-3 palette as the duel info bar / B-menu LP digits (sub_8040B4C). */
  CpuCopy16(g80F0F00, &gPaletteBuffer[0x30], 32);
  CpuCopy16(&gPaletteBuffer[0x30], (u16 *)PLTT + 0x30, 32);
}

static void FormatLifePointsString(char *buf, u16 lifePoints) {
  u8 i;

  ConvertU16ToDigitBuffer(lifePoints, DIGIT_FLAG_DISPLAY_LEADING_ZEROES);
  for (i = 0; i < BOARD_LP_MAX_DIGITS; i++) {
    u8 digit = gDigitBufferU16[i];

    if (digit == DIGIT_TERMINATOR)
      buf[i] = '0';
    else
      buf[i] = (char)('0' + digit);
  }
  buf[BOARD_LP_MAX_DIGITS] = '\0';
}

static void DrawLifePointsAt(u8 x, u8 y, u16 lifePoints, u16 charBufOffset, u16 baseTileId) {
  char buf[BOARD_LP_MAX_DIGITS + 1];
  u16 *tilemap = (u16 *)(gBgVram.cbb0 + BOARD_LP_MAP_BASE);
  u16 attrs = (tilemap[y * 32 + x] & 0xC000) | BOARD_LP_TILE_ATTR;
  u8 i;

  FormatLifePointsString(buf, lifePoints);
  CopyStringTilesToVRAMBuffer(gBgVram.cbb0 + charBufOffset, (const u8 *)buf, 0x001);

  for (i = 0; i < BOARD_LP_MAX_DIGITS; i++)
    tilemap[y * 32 + x + i] = (u16)(attrs | (baseTileId + i));
}

static void UploadBoardLpCharTiles(void) {
  CpuCopy16(
      gBgVram.cbb0 + BOARD_LP_CHARBUF_PLAYER,
      (void *)(BG_VRAM + BOARD_LP_CHARBUF_PLAYER),
      BOARD_LP_MAX_DIGITS * BOARD_LP_CHARBUF_TILE_BYTES);
  CpuCopy16(
      gBgVram.cbb0 + BOARD_LP_CHARBUF_OPPONENT,
      (void *)(BG_VRAM + BOARD_LP_CHARBUF_OPPONENT),
      BOARD_LP_MAX_DIGITS * BOARD_LP_CHARBUF_TILE_BYTES);
}

static void FlushBoardLpRow(u8 y) {
  CpuCopy32(
      gBgVram.cbb0 + BOARD_LP_MAP_BASE + y * 64,
      (void *)(BG_VRAM + BOARD_LP_MAP_BASE + y * 64),
      64);
}

static void FormatTurnCountString(char *buf, u16 turnCount) {
  u8 i;

  if (turnCount > 999)
    turnCount = 999;

  for (i = 0; i < BOARD_TURN_MAX_DIGITS; i++) {
    u8 power = BOARD_TURN_MAX_DIGITS - 1 - i;
    u16 divisor = 1;

    while (power--)
      divisor *= 10;
    buf[i] = (char)('0' + ((turnCount / divisor) % 10));
  }
  buf[BOARD_TURN_MAX_DIGITS] = '\0';
}

static void FormatTimerString(char *buf, u16 totalSeconds) {
  u16 mins;
  u16 secs;

  if (totalSeconds > 99 * 60 + 59)
    totalSeconds = 99 * 60 + 59;

  mins = totalSeconds / 60;
  secs = totalSeconds % 60;
  buf[0] = (char)('0' + (mins / 10));
  buf[1] = (char)('0' + (mins % 10));
  buf[2] = ':';
  buf[3] = (char)('0' + (secs / 10));
  buf[4] = (char)('0' + (secs % 10));
  buf[5] = '\0';
}

static void DrawHudStringAt(u8 x, u8 y, const char *buf, u8 charCount) {
  u16 *tilemap = (u16 *)(gBgVram.cbb0 + BOARD_LP_MAP_BASE);
  u16 attrs = (tilemap[y * 32 + x] & 0xC000) | BOARD_TURN_TILE_ATTR;
  u8 i;

  CopyStringTilesToVRAMBuffer(gBgVram.cbb0 + BOARD_TURN_CHARBUF, (const u8 *)buf, 0x001);
  gPaletteBuffer[0x70 + 8] = 0x0421;
  RemapSmallFontTilesToColorIndex(
      gBgVram.cbb0 + BOARD_TURN_CHARBUF,
      charCount * BOARD_LP_CHARBUF_TILE_BYTES,
      0,
      8);
  RemapSmallFontTilesToColorIndex(
      gBgVram.cbb0 + BOARD_TURN_CHARBUF,
      charCount * BOARD_LP_CHARBUF_TILE_BYTES,
      1,
      2);

  for (i = 0; i < charCount; i++)
    tilemap[y * 32 + x + i] = (u16)(attrs | (BOARD_TURN_BASE_TILE + i));
}

static void UploadBoardTurnCharTiles(u8 charCount) {
  CpuCopy16(
      gBgVram.cbb0 + BOARD_TURN_CHARBUF,
      (void *)(BG_VRAM + BOARD_TURN_CHARBUF),
      charCount * BOARD_LP_CHARBUF_TILE_BYTES);
}

static void DrawBoardLifePoints(void) {
  EnsureBoardLpPalette();
  DrawLifePointsAt(
      BOARD_LP_PLAYER_X,
      BOARD_LP_PLAYER_Y,
      gDuelLifePoints[DUEL_PLAYER],
      BOARD_LP_CHARBUF_PLAYER,
      BOARD_LP_BASE_TILE_PLAYER);
  DrawLifePointsAt(
      BOARD_LP_OPPONENT_X,
      BOARD_LP_OPPONENT_Y,
      gDuelLifePoints[DUEL_OPPONENT],
      BOARD_LP_CHARBUF_OPPONENT,
      BOARD_LP_BASE_TILE_OPPONENT);
  UploadBoardLpCharTiles();
  FlushBoardLpRow(BOARD_LP_PLAYER_Y);
  FlushBoardLpRow(BOARD_LP_OPPONENT_Y);
}

static void DrawBoardTurnCounter(void) {
  char buf[BOARD_TURN_MAX_DIGITS + 1];

  FormatTurnCountString(buf, gDuelBoardTurnCount);
  DrawHudStringAt(BOARD_TURN_X, BOARD_TURN_Y, buf, BOARD_TURN_MAX_DIGITS);
  UploadBoardTurnCharTiles(BOARD_TURN_MAX_DIGITS);
  FlushBoardLpRow(BOARD_TURN_Y);
}

static void DrawBoardTimer(void) {
  char buf[BOARD_TIMER_MAX_CHARS + 1];

  FormatTimerString(buf, gDuelBoardTurnCount);
  DrawHudStringAt(BOARD_TIMER_X, BOARD_TURN_Y, buf, BOARD_TIMER_MAX_CHARS);
  UploadBoardTurnCharTiles(BOARD_TIMER_MAX_CHARS);
  FlushBoardLpRow(BOARD_TURN_Y);
}

void RefreshDuelBoardTurnHud(void) {
  const struct TimedDuelLayout *layout;

  if (TimedDuel_IsActive() == TRUE) {
    layout = TimedDuel_GetActiveLayout();
    if (TimedDuel_UsesTurnLimit(layout) == TRUE)
      DrawBoardTurnCounter();
    else
      DrawBoardTimer();
  } else if (gRuntimeConfig.show_duel_turn_counter_on_board == TRUE) {
    DrawBoardTurnCounter();
  }
}

LYN_REPLACE_CHECK(sub_80411D4);
void sub_80411D4__Replacement(void) {
  LoadVRAM();
  LoadBgOffsets();
  LoadOam();

  if (gRuntimeConfig.show_duel_life_points_on_board == TRUE)
    DrawBoardLifePoints();

  RefreshDuelBoardTurnHud();

  FlushDuelFieldLayerToHardware();

  if (gRuntimeConfig.show_duel_life_points_on_board == TRUE)
    EnsureBoardLpPalette();

  UpdateDuelBgmTempoForLifePoints();
  UpdateDuelBgmVoiceDuck();
}

LYN_REPLACE_CHECK(InitDuelistStatus);
void InitDuelistStatus__Replacement(void) {
  u8 i;

  for (i = 0; i < 2; i++)
    gDuelistStatus[i] = DUELIST_STATUS_CANNOT_ATTACK;
  if (TimedDuel_IsActive() == TRUE) {
    const struct TimedDuelLayout *layout;

    layout = TimedDuel_GetActiveLayout();
    if (TimedDuel_UsesTurnLimit(layout) == TRUE)
      gDuelBoardTurnCount = TimedDuel_ResolveTurnNumber(layout);
    else
      gDuelBoardTurnCount = TimedDuel_ResolveTimerSeconds(layout);
    gTimedDuelTimerFrames = 0;
    /* ponytail: timed-duel loop returns before EndFirstTurnAttackBan; allow attacks immediately. */
    gDuelistStatus[DUEL_PLAYER] = DUELIST_STATUS_CAN_ATTACK;
  } else if (MechanicsTutorial_IsActive() == TRUE) {
    const struct TimedDuelLayout *layout;
    u16 startTurn;

    layout = MechanicsTutorial_GetActiveLayout();
    /* turnNumber 0 → turn 1 (attack ban). >1 → already past first turn. */
    startTurn = (layout != NULL && layout->turnNumber != 0) ? layout->turnNumber : 1;
    gDuelBoardTurnCount = startTurn - 1; /* BeginDuelBoardTurn increments to startTurn */
    gTimedDuelTimerFrames = 0;
    if (startTurn > 1) {
      gDuelistStatus[DUEL_PLAYER] = DUELIST_STATUS_CAN_ATTACK;
      gDuelistStatus[DUEL_OPPONENT] = DUELIST_STATUS_CAN_ATTACK;
    }
  } else {
    gDuelBoardTurnCount = 0;
    gTimedDuelTimerFrames = 0;
  }
}

void BeginDuelBoardTurn(void) {
  if (TimedDuel_IsActive() == TRUE)
    return;
  if (gDuelBoardTurnCount < 999)
    gDuelBoardTurnCount++;
}
