#include "global.h"
#include "configs/runtime.h"
#include "card.h"
#include "digit.h"
#include "duel.h"
#include "duel_b_menu.h"
#include "duel_status.h"
#include "expanded_graveyard.h"
#include "text.h"

union BMenuVram {
  u8 a[0x4000];
  u16 b[0x2000];
};

extern union BMenuVram gVr;
extern u8 g8DF811C[];
extern u16 g80F13D0[][30];
extern u16 g80F30E0[];

void PlayMusic(int);
void UpdateDuelGfxExceptField(void);
void WaitForVBlank(void);
void sub_8041014(void);
int GetCardsDrawn(u8);

static const u8 *const sDeckCardsText = (const u8 *)0x8E0D668;

static u16 const sBMenuHighlightTileOffsets[] APPEND_RODATA = {
  0xE844,
  0xE8C4,
  0xE85C,
  0xE8DC,
  0xEA44,
  0xEBC4,
};

static u8 const sBMenuNextUp[] APPEND_RODATA = {
  [B_MENU_DETAILS] = B_MENU_DETAILS,
  [B_MENU_TURN_END] = B_MENU_DETAILS,
  [B_MENU_DISCARD] = B_MENU_DISCARD,
  [B_MENU_SURRENDER] = B_MENU_DISCARD,
  [B_MENU_GY_OPPONENT] = B_MENU_TURN_END,
  [B_MENU_GY_PLAYER] = B_MENU_GY_OPPONENT,
};

static u8 const sBMenuNextDown[] APPEND_RODATA = {
  [B_MENU_DETAILS] = B_MENU_TURN_END,
  [B_MENU_TURN_END] = B_MENU_GY_OPPONENT,
  [B_MENU_DISCARD] = B_MENU_SURRENDER,
  [B_MENU_SURRENDER] = B_MENU_GY_OPPONENT,
  [B_MENU_GY_OPPONENT] = B_MENU_GY_PLAYER,
  [B_MENU_GY_PLAYER] = B_MENU_GY_PLAYER,
};

static u8 const sBMenuNextLeft[] APPEND_RODATA = {
  [B_MENU_DETAILS] = B_MENU_DETAILS,
  [B_MENU_TURN_END] = B_MENU_TURN_END,
  [B_MENU_DISCARD] = B_MENU_DETAILS,
  [B_MENU_SURRENDER] = B_MENU_TURN_END,
  [B_MENU_GY_OPPONENT] = B_MENU_GY_OPPONENT,
  [B_MENU_GY_PLAYER] = B_MENU_GY_PLAYER,
};

static u8 const sBMenuNextRight[] APPEND_RODATA = {
  [B_MENU_DETAILS] = B_MENU_DISCARD,
  [B_MENU_TURN_END] = B_MENU_SURRENDER,
  [B_MENU_DISCARD] = B_MENU_DISCARD,
  [B_MENU_SURRENDER] = B_MENU_SURRENDER,
  [B_MENU_GY_OPPONENT] = B_MENU_GY_OPPONENT,
  [B_MENU_GY_PLAYER] = B_MENU_GY_PLAYER,
};

#define B_MENU_TEMPLATE_ROWS 18
#define B_MENU_TEMPLATE_COLS 32
#define B_MENU_LABEL_TILE_MIN 88

struct BMenuOptionLabel {
  u8 col;
  u8 rowTop;
  u8 rowBottom;
  u8 width;
  u16 tileTop;
  u16 tileBottom;
};

#define B_MENU_LABEL_COL_LEFT 5
#define B_MENU_LABEL_COL_RIGHT 17
#define B_MENU_LABEL_WIDTH 10
#define B_MENU_SURRENDER_WIDTH 9

#define B_MENU_LABEL_TILE_DETAILS_TOP 88
#define B_MENU_LABEL_TILE_DETAILS_BOTTOM 90
#define B_MENU_LABEL_TILE_TURN_END_TOP 108
#define B_MENU_LABEL_TILE_TURN_END_BOTTOM 110
#define B_MENU_LABEL_TILE_DISCARD_TOP 128
#define B_MENU_LABEL_TILE_DISCARD_BOTTOM 130
#define B_MENU_LABEL_TILE_SURRENDER_TOP 148
#define B_MENU_LABEL_TILE_SURRENDER_BOTTOM 150

#define B_MENU_GY_NAME_COL 5
#define B_MENU_GY_NAME_WIDTH 20
#define B_MENU_GY_NAME_ROW_PLAYER_TOP 15
#define B_MENU_GY_NAME_ROW_PLAYER_BOTTOM 16
#define B_MENU_GY_NAME_ROW_OPPONENT_TOP 9
#define B_MENU_GY_NAME_ROW_OPPONENT_BOTTOM 10
#define B_MENU_GY_NAME_TILE_PLAYER_TOP 188
#define B_MENU_GY_NAME_TILE_PLAYER_BOTTOM 190
#define B_MENU_GY_NAME_TILE_OPPONENT_TOP 228
#define B_MENU_GY_NAME_TILE_OPPONENT_BOTTOM 230
#define B_MENU_GY_NAME_CHR_PLAYER 0x9780
#define B_MENU_GY_NAME_CHR_OPPONENT 0x9C80

static const struct {
  u8 row;
  u8 col;
} sStaleTemplateLabelCells[] APPEND_RODATA = {
  {9, 0},  {9, 1},  {9, 2},  {9, 3},  {9, 4},  {9, 5},  {9, 6},
  {9, 27}, {9, 28}, {9, 29}, {9, 30}, {9, 31},
  {10, 0}, {10, 1}, {10, 2}, {10, 3}, {10, 4},
};

static const struct BMenuOptionLabel sBMenuOptionLabels[] APPEND_RODATA = {
  [B_MENU_DETAILS] = {B_MENU_LABEL_COL_LEFT, 1, 2, B_MENU_LABEL_WIDTH, B_MENU_LABEL_TILE_DETAILS_TOP,
                      B_MENU_LABEL_TILE_DETAILS_BOTTOM},
  [B_MENU_DISCARD] = {B_MENU_LABEL_COL_RIGHT, 1, 2, B_MENU_LABEL_WIDTH, B_MENU_LABEL_TILE_DISCARD_TOP,
                      B_MENU_LABEL_TILE_DISCARD_BOTTOM},
  [B_MENU_TURN_END] = {B_MENU_LABEL_COL_LEFT, 3, 4, B_MENU_LABEL_WIDTH, B_MENU_LABEL_TILE_TURN_END_TOP,
                       B_MENU_LABEL_TILE_TURN_END_BOTTOM},
  [B_MENU_SURRENDER] = {B_MENU_LABEL_COL_RIGHT, 3, 4, B_MENU_SURRENDER_WIDTH, B_MENU_LABEL_TILE_SURRENDER_TOP,
                        B_MENU_LABEL_TILE_SURRENDER_BOTTOM},
};

static const u8 sText_BMenuLabelsExtended[] APPEND_RODATA = _(
  "{ENG}"
    "Details   Turn end  Discard   Surrender "
  "{FRE}"
    "Détails   FinDuTour Défausser Capituler "
  "{GER}"
    "Details   Zug-Ende  Ablegen   Aufgeben  "
  "{ITA}"
    "Dettagli  Fine TurnoScarta    Resa      "
  "{SPA}"
    "Detalles  Fin turno Desechar  Rendirse  "
  "{JAP}"
    "ディテール" "ターン終わり" "すてる" "サレンダー"
);

u16 sub_08007FEC(u8, u8, u16);
void sub_800800C(u8, u8, u16, u16);

bool8 DuelBMenu_IsSurrenderEnabled(void) {
  return gRuntimeConfig.enable_surrender_in_duel_b_menu == TRUE;
}

static void LoadBMenuLabelTiles(void) {
  CopyStringTilesToVRAMBuffer(gBgVram.cbb0 + 0x8B00, sText_BMenuLabelsExtended, 0x901);
}

static u16 *BMenuTilemapCell(u8 col, u8 row) {
  return (u16 *)(gBgVram.cbb0 + 0xE800 + row * 64 + col * 2);
}

static void BMenuWriteTile(u8 col, u8 row, u16 tile) {
  *BMenuTilemapCell(col, row) = tile;
}

static void ClearBMenuLabelRows(u8 rowFirst, u8 rowLast, u16 blankTile) {
  u8 row;
  u8 col;

  for (row = rowFirst; row <= rowLast; row++) {
    for (col = 0; col < B_MENU_TEMPLATE_COLS; col++)
      BMenuWriteTile(col, row, blankTile);
  }
}

static void ClearBMenuOptionLabelCells(u16 blankTile) {
  u8 i;
  u8 row;
  u8 col;

  ClearBMenuLabelRows(1, 4, blankTile);
  ClearBMenuLabelRows(14, 16, blankTile);

  for (i = 0; i < ARRAY_COUNT(sStaleTemplateLabelCells); i++)
    BMenuWriteTile(sStaleTemplateLabelCells[i].col, sStaleTemplateLabelCells[i].row, blankTile);

  for (row = 1; row <= 4; row++) {
    for (col = 0; col < B_MENU_TEMPLATE_COLS; col++) {
      u16 entry = *BMenuTilemapCell(col, row);

      if ((entry & 0x3FF) >= B_MENU_LABEL_TILE_MIN)
        BMenuWriteTile(col, row, blankTile);
    }
  }
}

static void CopyGraveyardNameTiles(u16 cardId, u32 chrOffset) {
  u8 buffer[44];
  u8 i;
  u8 nameLength;
  const u8 *name;

  if (cardId == CARD_NONE) {
    for (i = 0, nameLength = 0; nameLength < B_MENU_GY_NAME_WIDTH; nameLength++) {
      buffer[i] = 129;
      buffer[i + 1] = 64;
      i += 2;
    }
    buffer[i] = 0;
    CopyStringTilesToVRAMBuffer(gBgVram.cbb0 + chrOffset, buffer, 0x901);
    return;
  }

  SetCardInfo(cardId);
  i = 0;
  nameLength = 0;
  name = (u8 *)GetCurrentLanguageString(gCardInfo.name);
  while (nameLength < B_MENU_GY_NAME_WIDTH && *name && *name != '$') {
    if (*name > 127) {
      buffer[i] = *name;
      i++;
      name++;
    }
    buffer[i] = *name;
    i++;
    name++;
    nameLength++;
  }
  for (; nameLength < B_MENU_GY_NAME_WIDTH; nameLength++) {
    buffer[i] = 129;
    buffer[i + 1] = 64;
    i += 2;
  }
  buffer[i] = 0;
  CopyStringTilesToVRAMBuffer(gBgVram.cbb0 + chrOffset, buffer, 0x901);
}

static u16 GraveyardTopCardForDisplay(u8 fixedDuelist)
{
  if (gRuntimeConfig.expand_graveyard == TRUE) {
    u8 count = GraveyardExpand_GetCount(fixedDuelist);

    if (count == 0)
      return CARD_NONE;
    return GraveyardExpand_GetCardAt(fixedDuelist, count - 1);
  }

  return gDuel.duelistbattleState[fixedDuelist].graveyard;
}

static void RefreshGraveyardNameTiles(void) {
  CopyGraveyardNameTiles(GraveyardTopCardForDisplay(DUEL_PLAYER), B_MENU_GY_NAME_CHR_PLAYER);
  CopyGraveyardNameTiles(GraveyardTopCardForDisplay(DUEL_OPPONENT), B_MENU_GY_NAME_CHR_OPPONENT);
}

static void DrawGraveyardNameTilemap(u16 paletteBits) {
  u8 i;

  for (i = 0; i < B_MENU_GY_NAME_WIDTH; i++) {
    sub_800800C(B_MENU_GY_NAME_COL + i, B_MENU_GY_NAME_ROW_PLAYER_TOP, 0xE800,
        g8DF811C[i] + B_MENU_GY_NAME_TILE_PLAYER_TOP | paletteBits);
    sub_800800C(B_MENU_GY_NAME_COL + i, B_MENU_GY_NAME_ROW_PLAYER_BOTTOM, 0xE800,
        g8DF811C[i] + B_MENU_GY_NAME_TILE_PLAYER_BOTTOM | paletteBits);
    sub_800800C(B_MENU_GY_NAME_COL + i, B_MENU_GY_NAME_ROW_OPPONENT_TOP, 0xE800,
        g8DF811C[i] + B_MENU_GY_NAME_TILE_OPPONENT_TOP | paletteBits);
    sub_800800C(B_MENU_GY_NAME_COL + i, B_MENU_GY_NAME_ROW_OPPONENT_BOTTOM, 0xE800,
        g8DF811C[i] + B_MENU_GY_NAME_TILE_OPPONENT_BOTTOM | paletteBits);
  }
}

static void DrawBMenuOptionLabel(const struct BMenuOptionLabel *label, u16 paletteBits) {
  u8 i;

  for (i = 0; i < label->width; i++) {
    BMenuWriteTile(label->col + i, label->rowTop, (label->tileTop + g8DF811C[i]) | paletteBits);
    BMenuWriteTile(label->col + i, label->rowBottom, (label->tileBottom + g8DF811C[i]) | paletteBits);
  }
}

static void DrawBMenuAllOptionLabels(u16 paletteBits, u16 blankTile) {
  u8 option;

  LoadBMenuLabelTiles();
  ClearBMenuOptionLabelCells(blankTile);
  for (option = 0; option < ARRAY_COUNT(sBMenuOptionLabels); option++)
    DrawBMenuOptionLabel(&sBMenuOptionLabels[option], paletteBits);
  if (gRuntimeConfig.expand_graveyard == TRUE) {
    DrawGraveyardNameTilemap(paletteBits);
    RefreshGraveyardNameTiles();
  }
}

static void HighlightBMenuOption(u8 option);

static void InitBMenuWithSurrender(u8 arg0) {
  u16 deckCardsRemaining;
  u8 i;
  u16 blankTile;
  u16 paletteBits;

  (void)arg0;

  for (i = 0; i < 18; i++)
    CpuCopy32(g80F13D0[i], gBgVram.cbb0 + 0xE800 + i * 64, 64);
  CpuCopy16(g80F30E0, gBgVram.cbb0 + 0x87A0, 128);
  CopyStringTilesToVRAMBuffer(gBgVram.cbb0 + 0x8820, sDeckCardsText, 0x801);

  blankTile = sub_08007FEC(0, 0, 0xE800);
  paletteBits = sub_08007FEC(20, 1, 0xE800) & 0xFF00;

  for (i = 0; i < 4; i++) {
    sub_800800C(i + 4, 6, 0xE800, i + 78 | paletteBits);
    sub_800800C(i + 4, 12, 0xE800, i + 78 | paletteBits);
  }
  sub_800800C(8, 6, 0xE800, blankTile);
  sub_800800C(8, 12, 0xE800, blankTile);
  for (i = 0; i < 6; i++) {
    sub_800800C(i + 11, 6, 0xE800, i + 82 | paletteBits);
    sub_800800C(i + 11, 12, 0xE800, i + 82 | paletteBits);
  }

  ConvertU16ToDigitBuffer(gDuelLifePoints[DUEL_PLAYER], DIGIT_FLAG_NONE);
  for (i = 0; i < 5; i++)
    *(u16 *)(gBgVram.cbb0 + (0x75AC - i) * 2) = gDigitBufferU16[4 - i] + 65 | 0x3000;

  ConvertU16ToDigitBuffer(gDuelLifePoints[DUEL_OPPONENT], DIGIT_FLAG_NONE);
  for (i = 0; i < 5; i++)
    *(u16 *)(gBgVram.cbb0 + (0x74EC - i) * 2) = gDigitBufferU16[4 - i] + 65 | 0x3000;

  deckCardsRemaining = NumCardsInDeck(DUEL_PLAYER);
  if (deckCardsRemaining >= GetCardsDrawn(DUEL_PLAYER))
    deckCardsRemaining -= GetCardsDrawn(DUEL_PLAYER);
  else
    deckCardsRemaining = 0;
  ConvertU16ToDigitBuffer(deckCardsRemaining, DIGIT_FLAG_NONE);
  for (i = 0; i < 2; i++)
    *(u16 *)(gBgVram.cbb0 + (0x758A - i) * 2) = gDigitBufferU16[4 - i] + 65 | 0x3000;

  deckCardsRemaining = NumCardsInDeck(DUEL_OPPONENT);
  if (deckCardsRemaining >= GetCardsDrawn(DUEL_OPPONENT))
    deckCardsRemaining -= GetCardsDrawn(DUEL_OPPONENT);
  else
    deckCardsRemaining = 0;
  ConvertU16ToDigitBuffer(deckCardsRemaining, DIGIT_FLAG_NONE);
  for (i = 0; i < 2; i++)
    *(u16 *)(gBgVram.cbb0 + (0x74CA - i) * 2) = gDigitBufferU16[4 - i] + 65 | 0x3000;

  REG_DISPCNT = DISPCNT_BG1_ON | DISPCNT_BG2_ON | DISPCNT_OBJ_ON | DISPCNT_WIN0_ON | DISPCNT_WIN1_ON;
  REG_WIN1H = 0xF0;
  REG_WIN1V = 0x98;
  (*(vu8 *)(REG_BASE + 0x49)) = 0x36;
  REG_BLDY = 7;
  REG_WINOUT = 31;
}

static void FlushBMenuGfx(void) {
  WaitForVBlank();
  sub_8041014();
}

void DuelBMenu_RefreshOverlay(u8 highlightedOption) {
  u16 blankTile;
  u16 paletteBits;

  blankTile = sub_08007FEC(0, 0, 0xE800);
  paletteBits = sub_08007FEC(20, 1, 0xE800) & 0xFF00;
  DrawBMenuAllOptionLabels(paletteBits, blankTile);
  HighlightBMenuOption(highlightedOption);
  FlushBMenuGfx();
}

static void HighlightBMenuOption(u8 option) {
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sBMenuHighlightTileOffsets); i++) {
    u16 const tileBase = sBMenuHighlightTileOffsets[i] / 2;

    if (option != i) {
      gVr.b[tileBase + 1] = 0x7000;
      gVr.b[tileBase + 2] = 0x7000;
      gVr.b[tileBase + 33] = 0x7000;
      gVr.b[tileBase + 34] = 0x7000;
    } else {
      gVr.b[tileBase + 1] = 0x703D;
      gVr.b[tileBase + 2] = 0x703E;
      gVr.b[tileBase + 33] = 0x703F;
      gVr.b[tileBase + 34] = 0x7040;
    }
  }
}

void DuelBMenu_Init(u8 initialCursor) {
  InitBMenuWithSurrender(initialCursor);
  DuelBMenu_RefreshOverlay(initialCursor);
}

void DuelBMenu_HighlightOption(u8 option) {
  HighlightBMenuOption(option);
}

u8 DuelBMenu_GetNextUp(u8 option) {
  if (option >= ARRAY_COUNT(sBMenuNextUp))
    return B_MENU_DETAILS;
  return sBMenuNextUp[option];
}

u8 DuelBMenu_GetNextDown(u8 option) {
  if (option >= ARRAY_COUNT(sBMenuNextDown))
    return B_MENU_DETAILS;
  if (gRuntimeConfig.expand_graveyard != TRUE) {
    if (option == B_MENU_TURN_END)
      return B_MENU_TURN_END;
    if (option == B_MENU_SURRENDER)
      return B_MENU_SURRENDER;
  }
  return sBMenuNextDown[option];
}

u8 DuelBMenu_GetNextLeft(u8 option) {
  if (option >= ARRAY_COUNT(sBMenuNextLeft))
    return B_MENU_DETAILS;
  return sBMenuNextLeft[option];
}

u8 DuelBMenu_GetNextRight(u8 option) {
  if (option >= ARRAY_COUNT(sBMenuNextRight))
    return B_MENU_DETAILS;
  return sBMenuNextRight[option];
}

void DuelBMenu_Surrender(void) {
  PlayMusic(SFX_SELECT);
  DeclareLoser(DUEL_PLAYER);
  UpdateDuelGfxExceptField();
}
