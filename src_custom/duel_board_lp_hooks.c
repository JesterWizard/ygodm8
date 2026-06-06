#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "digit.h"
#include "gba/defines.h"
#include "text.h"

extern unsigned short gDuelLifePoints[];
extern u8 gDigitBufferU16[];

void sub_80411D4(void);
void LoadVRAM(void);
void LoadBgOffsets(void);
void LoadOam(void);
void LoadPalettes(void);
void FlushDuelFieldLayerToHardware(void);

// Small font (CopyStringTilesToVRAMBuffer flag 0x001). Tile map index must equal
// charBufOffset / 32 so tile graphics and tilemap entries refer to the same slots.
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

static void DrawBoardLifePoints(void) {
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

LYN_REPLACE_CHECK(sub_80411D4);
void sub_80411D4__Replacement(void) {
  LoadVRAM();
  LoadBgOffsets();
  LoadOam();
  FlushDuelFieldLayerToHardware();

  if (gRuntimeConfig.show_duel_life_points_on_board == TRUE)
    DrawBoardLifePoints();

  LoadPalettes();
}
