#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "card.h"
#include "duel.h"
#include "duel_opponent_hand_scroll.h"
#include "gfx_reg_buffers.h"

#define OPPONENT_BACKROW 0

extern struct DuelCard *gTurnHands[2][MAX_ZONES_IN_ROW];
extern s16 g8E116EE[][5];
extern s16 g8E11720[];

void PlayMusic(int);
void sub_8041D78(u8);
void sub_8041DF0(u8);
void sub_804078C(void);
void sub_8040880(u8 *dest, u8 *src);
void sub_8040868(void);
void sub_8040FDC(void);
void WaitForVBlank(void);
void DisplayCardNameInInfoBar(void);
void DisplayCardLevelInInfoBar(void);
void DisplayCardAtkDefInInfoBar(void);
void DisplayCardAttrTypeInInfoBar(void);
void DisplayCardFacedownIndicatorInInfoBar(void);
void SetFinalStat(struct StatMod *);
void MoveCursorUp(void);
void MoveCursorDown(void);
void sub_8041E70(u8, u8);
u32 CanPlayerSeeCard(u8, u8);
void DisplayCardInfoBar(void);
void sub_80408FC(void);
void PlaceFieldCardOam(u8 col, u8 row);
extern u8 gDFBA4[];

#define DUEL_CURSOR_TILE_INDEX 0x180

LYN_REPLACE_CHECK(MoveCursorUp);
void MoveCursorUp__Replacement(void) {
  PlayMusic(SFX_MOVE_CURSOR);

  if (IsOpponentHandFieldScrollEnabled() && gDuelCursor.currentY == OPPONENT_BACKROW) {
    gDuelCursor.currentY = OPPONENT_HAND_ROW;
    gDuelCursor.destY = OPPONENT_HAND_ROW;
    gDuelCursor.destX = gDuelCursor.currentX;
    return;
  }

  if (gDuelCursor.currentY == OPPONENT_HAND_ROW)
    return;

  if (gDuelCursor.currentY == 0)
    gDuelCursor.currentY++;

  gDuelCursor.currentY--;
}

LYN_REPLACE_CHECK(MoveCursorDown);
void MoveCursorDown__Replacement(void) {
  PlayMusic(SFX_MOVE_CURSOR);

  if (IsOpponentHandFieldScrollEnabled() && gDuelCursor.currentY == OPPONENT_HAND_ROW) {
    gDuelCursor.currentY = OPPONENT_BACKROW;
    gDuelCursor.destY = OPPONENT_BACKROW;
    gDuelCursor.destX = gDuelCursor.currentX;
    return;
  }

  if (++gDuelCursor.currentY > PLAYER_HAND)
    gDuelCursor.currentY--;
}

LYN_REPLACE_CHECK(sub_80575E0);
int sub_80575E0__Replacement(unsigned char arg0, unsigned char arg1) {
  if (IsOpponentHandFieldScrollEnabled() && arg1 == OPPONENT_HAND_ROW)
    return g8E116EE[OPPONENT_BACKROW][arg0];

  return g8E116EE[arg1][arg0];
}

LYN_REPLACE_CHECK(sub_8057600);
int sub_8057600__Replacement(unsigned char arg0_unused, unsigned char arg1) {
  if (IsOpponentHandFieldScrollEnabled() && arg1 == OPPONENT_HAND_ROW)
    return (signed short)(OPPONENT_HAND_ROW_SCREEN_Y - gBG2VOFS);

  return (signed short)(g8E11720[arg1] - gBG2VOFS);
}

LYN_REPLACE_CHECK(sub_8041E70);
void sub_8041E70__Replacement(u8 arg0, u8 arg1) {
  extern u8 g20240E4;

  g20240E4 = arg1;

  if (IsOpponentHandFieldScrollEnabled()
      && (arg0 == OPPONENT_HAND_ROW || arg1 == OPPONENT_HAND_ROW)
      && arg0 < NUM_DUEL_BOARD_ROWS
      && arg1 < NUM_DUEL_BOARD_ROWS) {
    u16 oldVofs = GetBoardScrollVofs(arg0);
    u16 newVofs = GetBoardScrollVofs(arg1);

    if (newVofs < oldVofs) {
      sub_8041D78(arg1);
      return;
    }
    if (newVofs > oldVofs) {
      sub_8041DF0(arg1);
      return;
    }
    sub_804078C();
    WaitForVBlank();
    sub_8040FDC();
    return;
  }

  if (arg0 < PLAYER_HAND + 1 && arg1 < PLAYER_HAND + 1) {
    switch (((const u8 (*)[5])0x08E0D588)[arg0][arg1]) {
      case 0:
        sub_804078C();
        WaitForVBlank();
        sub_8040FDC();
        break;
      case 1:
        sub_8041D78(arg1);
        break;
      case 2:
        sub_8041DF0(arg1);
        break;
    }
  }
}

LYN_REPLACE_CHECK(CanPlayerSeeCard);
u32 CanPlayerSeeCard__Replacement(unsigned char y, unsigned char x) {
  if (IsOpponentHandFieldScrollEnabled() && y == OPPONENT_HAND_ROW) {
    struct DuelCard *card = gTurnHands[INACTIVE_DUELIST][4 - x];

    if (card == NULL || card->id == CARD_NONE)
      return 0;
    return !!card->isFaceUp;
  }

  switch (y) {
    case 0:
    case 1:
      return !!gFixedZones[y][x]->isFaceUp;
    case 2:
    case 3:
    case 4:
      return 1;
    default:
      return 0;
  }
}

LYN_REPLACE_CHECK(DisplayCardInfoBar);
void DisplayCardInfoBar__Replacement(void) {
  if (IsOpponentHandFieldScrollEnabled()
      && gDuelCursor.currentY == OPPONENT_HAND_ROW
      && CanPlayerSeeCard__Replacement(OPPONENT_HAND_ROW, gDuelCursor.currentX) == 1) {
    struct DuelCard *card = gTurnHands[INACTIVE_DUELIST][4 - gDuelCursor.currentX];

    gStatMod.card = card->id;
    gStatMod.field = gDuel.field;
    gStatMod.stage = GetFinalStage(card);
    SetFinalStat(&gStatMod);
  } else if (CanPlayerSeeCard__Replacement(gDuelCursor.currentY, gDuelCursor.currentX) == 1) {
    gStatMod.card = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id;
    gStatMod.field = gDuel.field;
    gStatMod.stage = GetFinalStage(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
    SetFinalStat(&gStatMod);
  } else {
    SetCardInfo(CARD_NONE);
  }

  DisplayCardNameInInfoBar();
  DisplayCardLevelInInfoBar();
  DisplayCardAtkDefInInfoBar();
  DisplayCardAttrTypeInInfoBar();
  DisplayCardFacedownIndicatorInInfoBar();
}

LYN_REPLACE_CHECK(sub_80408FC);
void sub_80408FC__Replacement(void) {
  if (ShouldDrawOpponentHandOnField())
    DrawOpponentHandOnField();
  else {
    HideOpponentHandFieldOam();
    RestoreOpponentHandFieldWindow();
  }

  sub_8040880(&gBgVram.cbb4[DUEL_CURSOR_TILE_INDEX * 32], gDFBA4);
  sub_8040868();
  sub_804078C();

  if (ShouldDrawOpponentHandOnField()) {
    LoadCharblock4();
    LoadOam();
  }
}

LYN_REPLACE_CHECK(sub_80574A8);
void sub_80574A8__Replacement(unsigned char col, unsigned char row) {
  if (IsOpponentHandFieldScrollEnabled() && row == OPPONENT_HAND_ROW) {
    DrawOpponentHandZone(col);
    return;
  }

  PlaceFieldCardOam(col, row);
}
