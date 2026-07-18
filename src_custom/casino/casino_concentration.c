#include "casino_internal.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "../debug/debug_menu_internal.h"
#include "global.h"

#define CONC_COLS 5
#define CONC_ROWS 4
#define CONC_CELLS (CONC_COLS * CONC_ROWS)
#define CONC_PAIRS 10

#define CONC_X0 16
#define CONC_Y0 28
#define CONC_PITCH_X 44
#define CONC_PITCH_Y 32

struct ConcBoard {
  u16 cardIds[CONC_CELLS];
  u8 matched[CONC_CELLS];
  u16 memory[CONC_CELLS];
  u8 playerMatches;
  u8 npcMatches;
  u8 cursor;
  s8 revealA;
  s8 revealB;
};

extern u16 gOamBuffer[];
extern u16 RandRangeU16(u16, u16);
extern void LoadOam(void);

static void ShufflePairs(u16 *ids) {
  u8 i;
  for (i = 0; i < CONC_CELLS; i++) {
    u8 j = (u8)RandRangeU16(0, CONC_CELLS - 1);
    u16 tmp = ids[i];
    ids[i] = ids[j];
    ids[j] = tmp;
  }
}

static void InitBoard(struct ConcBoard *b) {
  u16 unique[CONC_PAIRS];
  u8 i, k, guard, dup;

  for (i = 0; i < CONC_PAIRS; i++) {
    guard = 0;
    do {
      unique[i] = Casino_RandomMonsterId();
      dup = FALSE;
      for (k = 0; k < i; k++) {
        if (unique[k] == unique[i]) {
          dup = TRUE;
          break;
        }
      }
      guard++;
    } while (dup && guard < 32);
  }

  for (i = 0; i < CONC_PAIRS; i++) {
    b->cardIds[i * 2] = unique[i];
    b->cardIds[i * 2 + 1] = unique[i];
  }
  ShufflePairs(b->cardIds);

  for (i = 0; i < CONC_CELLS; i++) {
    b->matched[i] = FALSE;
    b->memory[i] = CARD_NONE;
  }
  b->playerMatches = 0;
  b->npcMatches = 0;
  b->cursor = 0;
  b->revealA = -1;
  b->revealB = -1;
}

static void Remember(struct ConcBoard *b, u8 idx) {
  if (idx < CONC_CELLS && b->matched[idx] == FALSE)
    b->memory[idx] = b->cardIds[idx];
}

static u8 FindKnownMatch(const struct ConcBoard *b, u8 *outA, u8 *outB) {
  u8 i, j;
  for (i = 0; i < CONC_CELLS; i++) {
    if (b->matched[i] || b->memory[i] == CARD_NONE)
      continue;
    for (j = i + 1; j < CONC_CELLS; j++) {
      if (b->matched[j] || b->memory[j] == CARD_NONE)
        continue;
      if (b->memory[i] == b->memory[j]) {
        *outA = i;
        *outB = j;
        return TRUE;
      }
    }
  }
  return FALSE;
}

static u8 PickRandomUnmatched(const struct ConcBoard *b, u8 avoid) {
  u8 candidates[CONC_CELLS];
  u8 count = 0;
  u8 i;

  for (i = 0; i < CONC_CELLS; i++) {
    if (b->matched[i] == FALSE && i != avoid)
      candidates[count++] = i;
  }
  if (count == 0)
    return avoid;
  return candidates[RandRangeU16(0, count - 1)];
}

static void CellPos(u8 index, u8 *x, u8 *y) {
  *x = (u8)(CONC_X0 + (index % CONC_COLS) * CONC_PITCH_X);
  *y = (u8)(CONC_Y0 + (index / CONC_COLS) * CONC_PITCH_Y);
}

static u8 CellOpen(const struct ConcBoard *b, u8 index) {
  return index < CONC_CELLS && b->matched[index] == FALSE;
}

/* Right: next open on row, else first open on rows above (topward). */
static u8 CursorMoveRight(const struct ConcBoard *b, u8 cursor) {
  u8 row = cursor / CONC_COLS;
  u8 col = cursor % CONC_COLS;
  u8 c, r, i;

  for (c = col + 1; c < CONC_COLS; c++) {
    i = (u8)(row * CONC_COLS + c);
    if (CellOpen(b, i))
      return i;
  }
  if (row > 0) {
    for (r = row; r > 0; r--) {
      for (c = 0; c < CONC_COLS; c++) {
        i = (u8)((r - 1) * CONC_COLS + c);
        if (CellOpen(b, i))
          return i;
      }
    }
  }
  return cursor;
}

/* Left: previous open on row, else last open on rows below. */
static u8 CursorMoveLeft(const struct ConcBoard *b, u8 cursor) {
  u8 row = cursor / CONC_COLS;
  u8 col = cursor % CONC_COLS;
  u8 c, r, i;

  if (col > 0) {
    for (c = col; c > 0; c--) {
      i = (u8)(row * CONC_COLS + (c - 1));
      if (CellOpen(b, i))
        return i;
    }
  }
  for (r = row + 1; r < CONC_ROWS; r++) {
    for (c = CONC_COLS; c > 0; c--) {
      i = (u8)(r * CONC_COLS + (c - 1));
      if (CellOpen(b, i))
        return i;
    }
  }
  return cursor;
}

static u8 CursorMoveUp(const struct ConcBoard *b, u8 cursor) {
  u8 row = cursor / CONC_COLS;
  u8 col = cursor % CONC_COLS;
  u8 r, i;

  for (r = row; r > 0; r--) {
    i = (u8)((r - 1) * CONC_COLS + col);
    if (CellOpen(b, i))
      return i;
  }
  return cursor;
}

static u8 CursorMoveDown(const struct ConcBoard *b, u8 cursor) {
  u8 row = cursor / CONC_COLS;
  u8 col = cursor % CONC_COLS;
  u8 r, i;

  for (r = row + 1; r < CONC_ROWS; r++) {
    i = (u8)(r * CONC_COLS + col);
    if (CellOpen(b, i))
      return i;
  }
  return cursor;
}

static void CursorSnapToOpen(struct ConcBoard *b) {
  u8 i;

  if (CellOpen(b, b->cursor))
    return;
  for (i = 0; i < CONC_CELLS; i++) {
    if (CellOpen(b, i)) {
      b->cursor = i;
      return;
    }
  }
}

static void WriteScoreHud(u8 playerScore, u8 npcScore, u8 playerTurn) {
  u8 left0[DEBUG_SM_CHARS + 1];
  u8 right0[12 + 1];
  u8 i;
  u8 leftPal = playerTurn ? CASINO_TEXT_PAL_GOLD : CASINO_TEXT_PAL_WHITE;
  u8 rightPal = playerTurn ? CASINO_TEXT_PAL_WHITE : CASINO_TEXT_PAL_GOLD;

  for (i = 0; i < DEBUG_SM_CHARS; i++)
    left0[i] = ' ';
  left0[0] = 'Y';
  left0[1] = 'o';
  left0[2] = 'u';
  left0[3] = ':';
  left0[4] = ' ';
  left0[5] = (u8)('0' + (playerScore % 10));
  left0[DEBUG_SM_CHARS] = '\0';

  for (i = 0; i < 12; i++)
    right0[i] = ' ';
  right0[0] = 'O';
  right0[1] = 'p';
  right0[2] = 'p';
  right0[3] = 'o';
  right0[4] = 'n';
  right0[5] = 'e';
  right0[6] = 'n';
  right0[7] = 't';
  right0[8] = ':';
  right0[9] = ' ';
  right0[10] = (u8)('0' + (npcScore % 10));
  right0[12] = '\0';

  Casino_WriteSideText(FALSE, 0, left0, leftPal);
  Casino_WriteSideText(TRUE, 0, right0, rightPal);
  Casino_WriteSideText(FALSE, 1, NULL, CASINO_TEXT_PAL_WHITE);
  Casino_WriteSideText(TRUE, 1, NULL, CASINO_TEXT_PAL_WHITE);
  Casino_WriteTextRow(2, NULL);
  Casino_WriteTextRow(3, NULL);
  Casino_WriteTextRow(4, NULL);
  Casino_SetHudGoldColor();
  Casino_UploadHudText();
}

static void DrawConcBoard(struct ConcBoard *b, u8 playerTurn) {
  u8 i;
  u8 x, y;
  u8 cursorX, cursorY;

  Casino_ComposeFaceDownMini(CASINO_MINI_TILE_BACK);
  if (b->revealA >= 0)
    Casino_ComposeFaceUpMini(CASINO_MINI_TILE_A, b->cardIds[b->revealA]);
  if (b->revealB >= 0)
    Casino_ComposeFaceUpMini(CASINO_MINI_TILE_B, b->cardIds[b->revealB]);

  for (i = 0; i < CONC_CELLS; i++) {
    CellPos(i, &x, &y);
    if (b->matched[i]) {
      Casino_SetMiniOam(CASINO_OAM_CARD0 + i, CASINO_MINI_TILE_BACK, x, y, TRUE);
    } else if (i == b->revealA) {
      Casino_SetMiniOam(CASINO_OAM_CARD0 + i, CASINO_MINI_TILE_A, x, y, FALSE);
    } else if (i == b->revealB) {
      Casino_SetMiniOam(CASINO_OAM_CARD0 + i, CASINO_MINI_TILE_B, x, y, FALSE);
    } else {
      Casino_SetMiniOam(CASINO_OAM_CARD0 + i, CASINO_MINI_TILE_BACK, x, y, FALSE);
    }
  }
  Casino_FlushMiniCards();

  /* HUD after minis so gold/white pals stick. */
  WriteScoreHud(b->playerMatches, b->npcMatches, playerTurn);
  LoadPalettes();

  if (playerTurn && b->cursor < CONC_CELLS && !b->matched[b->cursor]) {
    CellPos(b->cursor, &cursorX, &cursorY);
    Casino_SetCursorOam(cursorX, cursorY, FALSE);
  } else {
    Casino_SetCursorOam(0, 0, TRUE);
  }

  LoadOam();
}

static void DelayFrames(u8 frames) {
  u8 i;
  for (i = 0; i < frames; i++)
    WaitForVBlank();
}

static void ResolveFlip(struct ConcBoard *b, u8 a, u8 bIdx, u8 forPlayer) {
  Remember(b, a);
  Remember(b, bIdx);
  b->revealA = (s8)a;
  b->revealB = (s8)bIdx;
  DrawConcBoard(b, forPlayer);
  DelayFrames(45);

  if (b->cardIds[a] == b->cardIds[bIdx]) {
    b->matched[a] = TRUE;
    b->matched[bIdx] = TRUE;
    b->memory[a] = CARD_NONE;
    b->memory[bIdx] = CARD_NONE;
    if (forPlayer)
      b->playerMatches++;
    else
      b->npcMatches++;
    PlayMusic(SFX_SELECT);
    CursorSnapToOpen(b);
  } else {
    PlayMusic(SFX_CANCEL);
  }
  b->revealA = -1;
  b->revealB = -1;
}

static u8 BoardCleared(const struct ConcBoard *b) {
  u8 i;
  for (i = 0; i < CONC_CELLS; i++)
    if (!b->matched[i])
      return FALSE;
  return TRUE;
}

static void NpcTurn(struct ConcBoard *b) {
  u8 a, bIdx;

  DrawConcBoard(b, FALSE);
  DelayFrames(20);

  if (FindKnownMatch(b, &a, &bIdx) != TRUE) {
    a = PickRandomUnmatched(b, 0xFF);
    Remember(b, a);
    b->revealA = (s8)a;
    b->revealB = -1;
    DrawConcBoard(b, FALSE);
    DelayFrames(20);
    {
      u8 i;
      u8 found = FALSE;
      for (i = 0; i < CONC_CELLS; i++) {
        if (i == a || b->matched[i] || b->memory[i] == CARD_NONE)
          continue;
        if (b->memory[i] == b->cardIds[a]) {
          bIdx = i;
          found = TRUE;
          break;
        }
      }
      if (!found)
        bIdx = PickRandomUnmatched(b, a);
    }
  }
  ResolveFlip(b, a, bIdx, FALSE);
}

void Casino_ConcentrationMain(void) {
  struct CasinoStake stake;
  struct ConcBoard board;
  enum CasinoOutcome outcome;
  u8 playerTurn = TRUE;
  s8 firstPick = -1;

  if (Casino_PromptStake(&stake) != TRUE)
    return;

  InitBoard(&board);
  Casino_BeginPlayField();
  DrawConcBoard(&board, TRUE);
  Casino_FadeInPlayField();

  while (BoardCleared(&board) != TRUE) {
    if (!playerTurn) {
      NpcTurn(&board);
      playerTurn = TRUE;
      firstPick = -1;
      continue;
    }

    DrawConcBoard(&board, TRUE);
    {
      u16 buttons = Casino_Buttons();
      u8 next;

      if (buttons & DPAD_LEFT) {
        next = CursorMoveLeft(&board, board.cursor);
        if (next != board.cursor) {
          board.cursor = next;
          PlayMusic(SFX_MOVE_CURSOR);
        }
      }
      if (buttons & DPAD_RIGHT) {
        next = CursorMoveRight(&board, board.cursor);
        if (next != board.cursor) {
          board.cursor = next;
          PlayMusic(SFX_MOVE_CURSOR);
        }
      }
      if (buttons & DPAD_UP) {
        next = CursorMoveUp(&board, board.cursor);
        if (next != board.cursor) {
          board.cursor = next;
          PlayMusic(SFX_MOVE_CURSOR);
        }
      }
      if (buttons & DPAD_DOWN) {
        next = CursorMoveDown(&board, board.cursor);
        if (next != board.cursor) {
          board.cursor = next;
          PlayMusic(SFX_MOVE_CURSOR);
        }
      }
      if (buttons & A_BUTTON) {
        if (!board.matched[board.cursor] && board.cursor != firstPick) {
          PlayMusic(SFX_SELECT);
          if (firstPick < 0) {
            firstPick = (s8)board.cursor;
            board.revealA = firstPick;
            board.revealB = -1;
            Remember(&board, (u8)firstPick);
          } else {
            ResolveFlip(&board, (u8)firstPick, board.cursor, TRUE);
            firstPick = -1;
            playerTurn = FALSE;
          }
        }
      }
    }
    WaitForVBlank();
  }

  Casino_EndOverlay();

  if (board.playerMatches > board.npcMatches)
    outcome = CASINO_OUTCOME_WIN;
  else if (board.playerMatches < board.npcMatches)
    outcome = CASINO_OUTCOME_LOSE;
  else
    outcome = CASINO_OUTCOME_PUSH;

  {
    u16 prize = Casino_ResolveStake(&stake, outcome);
    Casino_QueueOverworldResult(&stake, outcome, prize);
  }
}
