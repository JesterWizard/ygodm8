#include "casino_internal.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "../debug/debug_menu_internal.h"
#include "global.h"

#define BJ_MAX_CARDS 8
#define BJ_CARD_X0 112
#define BJ_CARD_PITCH 36
#define BJ_DEALER_Y 24
#define BJ_PLAYER_Y 100

static const u8 sLabelDealer[] APPEND_RODATA = "Dealer ";
static const u8 sLabelYou[] APPEND_RODATA = "You ";
static const u8 sHit[] APPEND_RODATA = "Hit";
static const u8 sStand[] APPEND_RODATA = "Stand";

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

static void WriteTotalRow(u8 row, const u8 *prefix, u8 total) {
  u8 line[DEBUG_SM_CHARS + 1];
  u8 t = 0;
  u8 i;

  while (prefix[t] != '\0' && t < 10) {
    line[t] = prefix[t];
    t++;
  }
  if (total >= 10)
    line[t++] = (u8)('0' + total / 10);
  line[t++] = (u8)('0' + total % 10);
  for (i = t; i < DEBUG_SM_CHARS; i++)
    line[i] = ' ';
  line[DEBUG_SM_CHARS] = '\0';
  Casino_WriteTextRow(row, line);
}

static void DrawBjCards(const struct BjHand *player, const struct BjHand *dealer, u8 revealDealer) {
  u8 i;

  /* ponytail: 2 face-up VRAM slots — dealer upcard + (hole if revealed else player latest) */
  Casino_LoadFaceDownMini(CASINO_MINI_TILE_BACK);

  for (i = 0; i < 8; i++) {
    Casino_SetMiniOam(CASINO_OAM_CARD0 + i, CASINO_MINI_TILE_BACK, 0, 0, TRUE);
    Casino_SetMiniOam(CASINO_OAM_CARD0 + 8 + i, CASINO_MINI_TILE_BACK, 0, 0, TRUE);
  }

  for (i = 0; i < dealer->count && i < 5; i++)
    Casino_SetMiniOam(CASINO_OAM_CARD0 + i, CASINO_MINI_TILE_BACK,
                       (u8)(BJ_CARD_X0 + i * BJ_CARD_PITCH), BJ_DEALER_Y, FALSE);
  for (i = 0; i < player->count && i < 5; i++)
    Casino_SetMiniOam(CASINO_OAM_CARD0 + 8 + i, CASINO_MINI_TILE_BACK,
                       (u8)(BJ_CARD_X0 + i * BJ_CARD_PITCH), BJ_PLAYER_Y, FALSE);

  if (dealer->count > 0) {
    Casino_LoadFaceUpMini(CASINO_MINI_TILE_A, dealer->cardIds[0]);
    Casino_SetMiniOam(CASINO_OAM_CARD0, CASINO_MINI_TILE_A, BJ_CARD_X0, BJ_DEALER_Y, FALSE);
  }
  if (revealDealer && dealer->count > 1) {
    Casino_LoadFaceUpMini(CASINO_MINI_TILE_B, dealer->cardIds[1]);
    Casino_SetMiniOam(CASINO_OAM_CARD0 + 1, CASINO_MINI_TILE_B,
                      (u8)(BJ_CARD_X0 + BJ_CARD_PITCH), BJ_DEALER_Y, FALSE);
  } else if (player->count > 0) {
    u8 pi = (player->count > 5) ? 4 : (u8)(player->count - 1);
    Casino_LoadFaceUpMini(CASINO_MINI_TILE_B, player->cardIds[pi]);
    Casino_SetMiniOam(CASINO_OAM_CARD0 + 8 + pi, CASINO_MINI_TILE_B,
                      (u8)(BJ_CARD_X0 + pi * BJ_CARD_PITCH), BJ_PLAYER_Y, FALSE);
  }
}

static void DrawBjUi(const struct BjHand *player, const struct BjHand *dealer, u8 revealDealer, u8 cursor) {
  u8 pTotal = Casino_BlackjackHandTotal(player->levels, player->count);
  u8 dTotal;

  if (revealDealer)
    dTotal = Casino_BlackjackHandTotal(dealer->levels, dealer->count);
  else if (dealer->count > 0)
    dTotal = Casino_BlackjackHandTotal(dealer->levels, 1);
  else
    dTotal = 0;

  WriteTotalRow(0, sLabelDealer, dTotal);
  WriteTotalRow(1, sLabelYou, pTotal);
  Casino_WriteTextRow(2, sHit);
  Casino_WriteTextRow(3, sStand);
  Casino_WriteTextRow(4, NULL);
  DebugMenuUploadStartMenuText();
  DebugMenuUpdateCursorStartMenu((u8)(2 + cursor));
  DrawBjCards(player, dealer, revealDealer);
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
      DrawBjUi(&player, &dealer, TRUE, 0);
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
    DrawBjUi(&player, &dealer, FALSE, cursor);
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
          DrawBjUi(&player, &dealer, TRUE, cursor);
          outcome = CASINO_OUTCOME_LOSE;
          playing = FALSE;
        }
      } else {
        while (Casino_BlackjackHandTotal(dealer.levels, dealer.count) < 17)
          DealTo(&dealer);
        {
          u8 p = Casino_BlackjackHandTotal(player.levels, player.count);
          u8 d = Casino_BlackjackHandTotal(dealer.levels, dealer.count);
          DrawBjUi(&player, &dealer, TRUE, cursor);
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
