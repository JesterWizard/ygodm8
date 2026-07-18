#ifndef GUARD_CASINO_INTERNAL_H
#define GUARD_CASINO_INTERNAL_H

#include "gba/types.h"
#include "casino.h"

enum CasinoStakeKind {
  CASINO_STAKE_NONE = 0,
  CASINO_STAKE_DOMINO,
  CASINO_STAKE_ANTE,
};

enum CasinoOutcome {
  CASINO_OUTCOME_CANCEL = 0,
  CASINO_OUTCOME_WIN,
  CASINO_OUTCOME_LOSE,
  CASINO_OUTCOME_PUSH,
};

struct CasinoStake {
  enum CasinoStakeKind kind;
  u32 dominoAmount; /* 100 / 1000 / 10000 when kind == DOMINO */
  u16 anteCardId;   /* when kind == ANTE */
};

#define CASINO_BET_SMALL 100
#define CASINO_BET_MEDIUM 1000
#define CASINO_BET_LARGE 10000

/* Ante viewer uses 0x1000 bytes per mini card — keep slots non-overlapping. */
#define CASINO_MINI_TILE_BACK  0x100
#define CASINO_MINI_TILE_A     0x180
#define CASINO_MINI_TILE_B     0x200
#define CASINO_MINI_TILE_BYTES 0x1000

#define CASINO_OAM_CARD0 16 /* leave 0–1 for start-menu cursor */
#define CASINO_CURSOR_PAL 15
#define CASINO_TEXT_PAL_WHITE 15
#define CASINO_TEXT_PAL_GOLD 14
#define CASINO_TEXT_PAL_GREY 13

u8 Casino_PromptStake(struct CasinoStake *out);
void Casino_ResolveStake(const struct CasinoStake *stake, enum CasinoOutcome outcome);

u16 Casino_RandomMonsterId(void);
u16 Casino_RandomMonsterOfLevel(u8 level);
u8 Casino_CardLevel(u16 cardId);

void Casino_BeginOverlay(void);      /* stake / result menus (narrow window) */
void Casino_BeginPlayField(void);    /* games: full-screen window for card grid */
void Casino_EndOverlay(void);
u16 Casino_Buttons(void);
void Casino_DrawMenuLines(const u8 *const *lines, u8 count, u8 cursor);
void Casino_ClearOam(void);
void Casino_BlankTextRows(void);
void Casino_WriteTextRow(u8 row, const u8 *ascii);
void Casino_WriteSideText(u8 rightSide, u8 row, const u8 *ascii, u8 paletteNum);
void Casino_UploadHudText(void);
void Casino_SetHudGoldColor(void);
void Casino_ReloadCursorPalette(void);
void Casino_SetCursorOam(u8 x, u8 y, u8 hide);
void Casino_LoadFaceDownMini(u16 tileNum);
void Casino_LoadFaceUpMini(u16 tileNum, u16 cardId);
void Casino_SetMiniOam(u8 slot, u16 tileNum, u8 x, u8 y, u8 hide);

#endif /* GUARD_CASINO_INTERNAL_H */
