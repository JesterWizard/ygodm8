#include "casino_internal.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "../debug/debug_menu_internal.h"
#include "global.h"

#define BJ_MAX_CARDS 8
#define BJ_VISIBLE 6
/* 32×32 minis; 6×32=192 → X0=48 leaves left gutter for cursor+Hit/Stand. */
#define BJ_CARD_X0 48
#define BJ_CARD_PITCH 32
#define BJ_DEALER_Y 24
#define BJ_PLAYER_Y 100
/* Hit/Stand: +32px from row 2 → row 4/5. Cursor: +4 then +32 on Y, +4 on X. */
#define BJ_HIT_ROW 4
#define BJ_CURSOR_X 4
#define BJ_CURSOR_Y_BASE 64 /* (row4*16 - 4) + 4 */
#define BJ_RIGHT_CHARS 12

static const u8 sLabelYou[] APPEND_RODATA = "You";
static const u8 sLabelDealer[] APPEND_RODATA = "Dealer";
/* Leading spaces: clear 16px cursor (at x=4) + extra nudge right. */
static const u8 sHit[] APPEND_RODATA = "   Hit";
static const u8 sStand[] APPEND_RODATA = "   Stand";

struct BjHand {
  u16 cardIds[BJ_MAX_CARDS];
  u8 levels[BJ_MAX_CARDS];
  u8 count;
};

extern u16 RandRangeU16(u16, u16);
extern void LoadOam(void);

static void DealTo(struct BjHand *hand) {
  u8 level;
  u16 cardId;

  if (hand->count >= BJ_MAX_CARDS)
    return;
  level = (u8)RandRangeU16(1, 11);
  cardId = Casino_RandomMonsterOfLevel(level);
  hand->cardIds[hand->count] = cardId;
  hand->levels[hand->count] = Casino_CardLevel(cardId);
  if (hand->levels[hand->count] < 1 || hand->levels[hand->count] > 11)
    hand->levels[hand->count] = level;
  hand->count++;
}

static void FormatTotal(u8 *buf, u8 bufLen, const u8 *label, u8 total, u8 rightAlign) {
  u8 raw[16];
  u8 n = 0;
  u8 t = 0;
  u8 i;
  u8 pad;

  while (label[t] != '\0' && n < 12) {
    raw[n++] = label[t++];
  }
  if (n < 12)
    raw[n++] = ':';
  if (n < 12)
    raw[n++] = ' ';
  if (total >= 10 && n < 12)
    raw[n++] = (u8)('0' + total / 10);
  if (n < 12)
    raw[n++] = (u8)('0' + total % 10);

  if (rightAlign && bufLen > 1 && n < bufLen - 1) {
    pad = (u8)((bufLen - 1) - n);
    for (i = 0; i < pad; i++)
      buf[i] = ' ';
    for (i = 0; i < n; i++)
      buf[pad + i] = raw[i];
    buf[bufLen - 1] = '\0';
  } else {
    for (i = 0; i < n && i < bufLen - 1; i++)
      buf[i] = raw[i];
    while (i < bufLen - 1)
      buf[i++] = ' ';
    buf[bufLen - 1] = '\0';
  }
}

static void DrawBjCards(const struct BjHand *player, const struct BjHand *dealer, u8 revealDealer) {
  u8 i;
  u8 dShow = dealer->count;
  u8 pShow = player->count;

  if (dShow > BJ_VISIBLE)
    dShow = BJ_VISIBLE;
  if (pShow > BJ_VISIBLE)
    pShow = BJ_VISIBLE;

  /* ponytail: 2 face-up VRAM slots — dealer upcard + (hole if revealed else player latest) */
  Casino_LoadFaceDownMini(CASINO_MINI_TILE_BACK);

  for (i = 0; i < 8; i++) {
    Casino_SetMiniOam(CASINO_OAM_CARD0 + i, CASINO_MINI_TILE_BACK, 0, 0, TRUE);
    Casino_SetMiniOam(CASINO_OAM_CARD0 + 8 + i, CASINO_MINI_TILE_BACK, 0, 0, TRUE);
  }

  for (i = 0; i < dShow; i++)
    Casino_SetMiniOam(CASINO_OAM_CARD0 + i, CASINO_MINI_TILE_BACK,
                       (u8)(BJ_CARD_X0 + i * BJ_CARD_PITCH), BJ_DEALER_Y, FALSE);
  for (i = 0; i < pShow; i++)
    Casino_SetMiniOam(CASINO_OAM_CARD0 + 8 + i, CASINO_MINI_TILE_BACK,
                       (u8)(BJ_CARD_X0 + i * BJ_CARD_PITCH), BJ_PLAYER_Y, FALSE);

  if (dealer->count > 0) {
    Casino_LoadFaceUpMini(CASINO_MINI_TILE_A, dealer->cardIds[0]);
    Casino_SetMiniOam(CASINO_OAM_CARD0, CASINO_MINI_TILE_A, BJ_CARD_X0, BJ_DEALER_Y, FALSE);
  }
  if (revealDealer && dealer->count > 1 && 1 < BJ_VISIBLE) {
    Casino_LoadFaceUpMini(CASINO_MINI_TILE_B, dealer->cardIds[1]);
    Casino_SetMiniOam(CASINO_OAM_CARD0 + 1, CASINO_MINI_TILE_B,
                      (u8)(BJ_CARD_X0 + BJ_CARD_PITCH), BJ_DEALER_Y, FALSE);
  } else if (player->count > 0) {
    u8 pi = (player->count > BJ_VISIBLE) ? (BJ_VISIBLE - 1) : (u8)(player->count - 1);
    Casino_LoadFaceUpMini(CASINO_MINI_TILE_B, player->cardIds[pi]);
    Casino_SetMiniOam(CASINO_OAM_CARD0 + 8 + pi, CASINO_MINI_TILE_B,
                      (u8)(BJ_CARD_X0 + pi * BJ_CARD_PITCH), BJ_PLAYER_Y, FALSE);
  }
}

static void DrawBjUi(const struct BjHand *player, const struct BjHand *dealer, u8 revealDealer,
                     u8 cursor, u8 playerTurn) {
  u8 left[DEBUG_SM_CHARS + 1];
  u8 right[BJ_RIGHT_CHARS + 1];
  u8 pTotal = Casino_BlackjackHandTotal(player->levels, player->count);
  u8 dTotal;
  u8 leftPal = playerTurn ? CASINO_TEXT_PAL_GOLD : CASINO_TEXT_PAL_WHITE;
  u8 rightPal = playerTurn ? CASINO_TEXT_PAL_WHITE : CASINO_TEXT_PAL_GOLD;

  if (revealDealer)
    dTotal = Casino_BlackjackHandTotal(dealer->levels, dealer->count);
  else if (dealer->count > 0)
    dTotal = Casino_BlackjackHandTotal(dealer->levels, 1);
  else
    dTotal = 0;

  FormatTotal(left, sizeof(left), sLabelYou, pTotal, FALSE);
  FormatTotal(right, sizeof(right), sLabelDealer, dTotal, TRUE);

  Casino_WriteSideText(FALSE, 0, left, leftPal);
  Casino_WriteSideText(TRUE, 0, right, rightPal);
  Casino_WriteSideText(FALSE, 1, NULL, CASINO_TEXT_PAL_WHITE);
  Casino_WriteSideText(TRUE, 1, NULL, CASINO_TEXT_PAL_WHITE);
  /* Clear old Hit/Stand rows (2–3) after +32px shift to rows 4–5. */
  Casino_WriteSideText(FALSE, 2, NULL, CASINO_TEXT_PAL_WHITE);
  Casino_WriteSideText(FALSE, 3, NULL, CASINO_TEXT_PAL_WHITE);
  Casino_WriteSideText(TRUE, 2, NULL, CASINO_TEXT_PAL_WHITE);
  Casino_WriteSideText(TRUE, 3, NULL, CASINO_TEXT_PAL_WHITE);

  if (playerTurn) {
    Casino_WriteSideText(FALSE, BJ_HIT_ROW, sHit, CASINO_TEXT_PAL_WHITE);
    Casino_WriteSideText(FALSE, BJ_HIT_ROW + 1, sStand, CASINO_TEXT_PAL_WHITE);
  } else {
    Casino_WriteSideText(FALSE, BJ_HIT_ROW, NULL, CASINO_TEXT_PAL_WHITE);
    Casino_WriteSideText(FALSE, BJ_HIT_ROW + 1, NULL, CASINO_TEXT_PAL_WHITE);
  }
  Casino_WriteSideText(TRUE, BJ_HIT_ROW, NULL, CASINO_TEXT_PAL_WHITE);
  Casino_WriteSideText(TRUE, BJ_HIT_ROW + 1, NULL, CASINO_TEXT_PAL_WHITE);
  Casino_UploadHudText();

  DrawBjCards(player, dealer, revealDealer);
  Casino_ReloadCursorPalette();
  if (playerTurn)
    Casino_SetCursorOam(BJ_CURSOR_X, (u8)(BJ_CURSOR_Y_BASE + cursor * 16), FALSE);
  else
    Casino_SetCursorOam(0, 0, TRUE);
  LoadOam();
}

void Casino_BlackjackMain(void) {
  struct CasinoStake stake;
  struct BjHand player;
  struct BjHand dealer;
  enum CasinoOutcome outcome = CASINO_OUTCOME_PUSH;
  u8 cursor = 0;
  u8 playing;

  if (Casino_PromptStake(&stake) != TRUE)
    return;

  player.count = 0;
  dealer.count = 0;
  DealTo(&player);
  DealTo(&dealer);
  DealTo(&player);
  DealTo(&dealer);

  Casino_BeginPlayField();
  playing = TRUE;

  {
    u8 pNat = (player.count == 2 && Casino_BlackjackHandTotal(player.levels, 2) == 21);
    u8 dNat = (dealer.count == 2 && Casino_BlackjackHandTotal(dealer.levels, 2) == 21);
    if (pNat || dNat) {
      DrawBjUi(&player, &dealer, TRUE, 0, FALSE);
      WaitForVBlank();
      if (pNat && dNat)
        outcome = CASINO_OUTCOME_PUSH;
      else if (pNat)
        outcome = CASINO_OUTCOME_WIN;
      else
        outcome = CASINO_OUTCOME_LOSE;
      playing = FALSE;
    }
  }

  while (playing) {
    u16 buttons;
    DrawBjUi(&player, &dealer, FALSE, cursor, TRUE);
    buttons = Casino_Buttons();
    if ((buttons & DPAD_UP) && cursor > 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      cursor = 0;
    }
    if ((buttons & DPAD_DOWN) && cursor < 1) {
      PlayMusic(SFX_MOVE_CURSOR);
      cursor = 1;
    }
    if (buttons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      if (cursor == 0) {
        DealTo(&player);
        if (Casino_BlackjackHandTotal(player.levels, player.count) > 21) {
          DrawBjUi(&player, &dealer, TRUE, cursor, FALSE);
          outcome = CASINO_OUTCOME_LOSE;
          playing = FALSE;
        }
      } else {
        DrawBjUi(&player, &dealer, TRUE, cursor, FALSE);
        WaitForVBlank();
        while (Casino_BlackjackHandTotal(dealer.levels, dealer.count) < 17) {
          DealTo(&dealer);
          DrawBjUi(&player, &dealer, TRUE, cursor, FALSE);
          WaitForVBlank();
        }
        {
          u8 p = Casino_BlackjackHandTotal(player.levels, player.count);
          u8 d = Casino_BlackjackHandTotal(dealer.levels, dealer.count);
          if (d > 21 || p > d)
            outcome = CASINO_OUTCOME_WIN;
          else if (p < d)
            outcome = CASINO_OUTCOME_LOSE;
          else
            outcome = CASINO_OUTCOME_PUSH;
          playing = FALSE;
        }
      }
    }
    WaitForVBlank();
  }

  Casino_EndOverlay();
  Casino_ResolveStake(&stake, outcome);
}
