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

/*
 * Mini cards use duel-style interleaved packing: two sprites share one 0x1000
 * window via +0x08 into each other's 0x300 row padding (see g8E116BC).
 * Base stays above cursor tiles 0..0x21.
 */
#define CASINO_MINI_BASE 0x28
#define CASINO_MINI_PAIR_STRIDE 0x80
#define CASINO_MINI_PAIR_OFF 0x08
#define CASINO_MINI_TILE(slot) \
  ((u16)(CASINO_MINI_BASE + ((slot) / 2) * CASINO_MINI_PAIR_STRIDE + \
         ((slot) % 2) * CASINO_MINI_PAIR_OFF))
#define CASINO_MINI_TILE_BACK CASINO_MINI_TILE(0)
#define CASINO_MINI_TILE_A CASINO_MINI_TILE(1)
#define CASINO_MINI_TILE_B CASINO_MINI_TILE(2)
#define CASINO_MINI_FACE0 1 /* first face-up slot index (0 = shared back) */
#define CASINO_MINI_FACE_SLOTS 12

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
void Casino_FadeInPlayField(void);   /* BLDY 16→0 after stake → play */
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
void Casino_ComposeFaceDownMini(u16 tileNum);
void Casino_ComposeFaceUpMini(u16 tileNum, u16 cardId);
void Casino_FlushMiniCards(void);
void Casino_SetMiniOam(u8 slot, u16 tileNum, u8 x, u8 y, u8 hide);

#endif /* GUARD_CASINO_INTERNAL_H */
