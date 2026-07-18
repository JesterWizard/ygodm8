#include "casino_internal.h"
#include "ante.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "../debug/debug_menu_internal.h"
#include "duel.h"
#include "duel_helpers.h"
#include "global.h"
#include "mini_card.h"
#include "menu_cursor.h"
#include "money.h"
#include "overworld.h"
#include "text.h"

#define CASINO_RIGHT_TEXT_CHARS 12
/* Flush right on play field (30 cols); 12 chars → cols 18..29. */
#define CASINO_RIGHT_MAP_COL 18
/* Must stay below tile 0x81 (left text) and below 0x180 (sbb1E / BG3 map in cbb3).
 * Old base 0x121 overlapped sbb1E — ClearRightHud zeroed the Egyptian BG3 tilemap. */
#define CASINO_RIGHT_TEXT_TILE 0x08
#define CASINO_RIGHT_TEXT_OFFSET (CASINO_RIGHT_TEXT_TILE * 32)
#define CASINO_RIGHT_TEXT_BLOCKS ((CASINO_RIGHT_TEXT_CHARS + 1) / 2)
#define CASINO_GOLD_TEXT_COLOR 0x031F
#define CASINO_GREY_TEXT_COLOR 0x294A
#define CASINO_BG3_VRAM ((void *)BG_SCREEN_ADDR(0x1E))

static const u8 sStakeDomino100[] APPEND_RODATA = "Domino 100";
static const u8 sStakeDomino1000[] APPEND_RODATA = "Domino 1000";
static const u8 sStakeDomino10000[] APPEND_RODATA = "Domino 10000";
static const u8 sStakeAnte[] APPEND_RODATA = "Ante a card";
static const u8 *const sStakeLines[] APPEND_RODATA = {
  sStakeDomino100, sStakeDomino1000, sStakeDomino10000, sStakeAnte
};
static const u32 sStakeDominoAmounts[] APPEND_RODATA = {
  CASINO_BET_SMALL, CASINO_BET_MEDIUM, CASINO_BET_LARGE
};

static void Casino_ClearRightHud(void);
static void Casino_UpdateMenuCursor(u8 screenRow);
static void Casino_DrawStakeMenu(u8 cursor);

extern const CardData gCardData_NEW[];
extern u16 gOamBuffer[];
extern u16 gNewButtons;
extern u16 gRepeatedOrNewButtons;
extern u16 gPressedButtons;
extern u8 gInputRepeatTimer;
extern u16 gUnk_8079424[];
extern u16 gUnk_8079444[][30];
extern u16 gUnk_80798F4[][30];
extern struct CardInfo gCardInfo;
extern const u8 *gUnk_8E00E30[];

void InitButtonMaps(void);
void LoadObjVRAM(void);
void LoadPalettes(void);
void LoadOam(void);
void LoadBgOffsets(void);
void LoadBlendingRegs(void);
void SetCardInfo(u16 id);
void DisableDisplay(void);
void SetVBlankCallback(void (*)(void));
u16 RandRangeU16(u16 min, u16 max);
unsigned char GetTrunkCardQty(unsigned short);
void sub_80411EC(struct OamData *oam);

extern u16 gBLDCNT;
extern u16 gBLDY;

extern const u16 gCasinoPrizePoolPrimary[];
extern const u16 gCasinoPrizePoolSecondary[];
extern const u16 gCasinoPrizePoolPrimaryCount;
extern const u16 gCasinoPrizePoolSecondaryCount;

u8 Casino_BlackjackHandTotal(const u8 *levels, u8 count) {
  u8 i;
  u8 total = 0;
  u8 aces = 0;

  for (i = 0; i < count; i++) {
    u8 lv = levels[i];
    if (lv == 11) {
      aces++;
      total += 11;
    } else if (lv >= 1 && lv <= 10) {
      total += lv;
    }
  }
  while (total > 21 && aces > 0) {
    total -= 10;
    aces--;
  }
  return total;
}

u8 Casino_CardLevel(u16 cardId) {
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return 0;
  return gCardData_NEW[cardId].level;
}

u16 Casino_RandomMonsterId(void) {
  u16 id;
  u16 guard = 0;

  /* ponytail: rejection sample; ceiling = sparse empty ids, upgrade = prebuilt monster list */
  do {
    id = RandRangeU16(1, NUM_TOTAL_CARDS - 1);
    guard++;
  } while ((Duel_CardIsMonster(id) != TRUE || Casino_CardLevel(id) == 0) && guard < 512);

  if (Duel_CardIsMonster(id) != TRUE)
    return BLUE_EYES_WHITE_DRAGON;
  return id;
}

u16 Casino_RandomMonsterOfLevel(u8 level) {
  u16 matches[64];
  u16 count = 0;
  u16 id;

  if (level < 1 || level > 11)
    level = 1;

  for (id = 1; id < NUM_TOTAL_CARDS && count < 64; id++) {
    if (Duel_CardIsMonster(id) == TRUE && Casino_CardLevel(id) == level)
      matches[count++] = id;
  }
  if (count == 0)
    return Casino_RandomMonsterId();
  return matches[RandRangeU16(0, count - 1)];
}

void Casino_ClearOam(void) {
  u8 i;
  for (i = 0; i < 128; i++)
    sub_80411EC((struct OamData *)&gOamBuffer[i * 4]);
}

static void CasinoApplyStartMenuBg2(void) {
  /* Vanilla HOFS (not debug +28) so WIN0 matches start-menu cursor X. */
  gBG2HOFS = 0xFFB0;
  gBG2VOFS = DEBUG_SM_BG2VOFS;
  LoadBgOffsets();
}

static void CasinoMenuVBlank(void) {
  ((void (*)(void))(DEBUG_SM_THUMB_VBLANK_WIN | 1))();
  CasinoApplyStartMenuBg2();
  /* Vanilla clip — debug 0x20D8 shows cols 16+ where tile-0 aliases look like junk text;
   * play-field VBlank leaves WIN0V=0x00A0 which shreds the panel if left stuck. */
  REG_WIN0H = 0x38B8;
  REG_WIN0V = 0x2878;
}

/* Full-screen window; park HUD text at top of screen (not mid-panel). */
static void CasinoPlayVBlank(void) {
  ((void (*)(void))(DEBUG_SM_THUMB_VBLANK_WIN | 1))();
  gBG2HOFS = 0;
  gBG2VOFS = 0;
  LoadBgOffsets();
  REG_WIN0H = 0x00F0;
  REG_WIN0V = 0x00A0;
  /* Keep start-menu BG3 darken (fade-in must not leave blend off). */
  gBLDCNT = 0xE8;
  gBLDY = 8;
  LoadBlendingRegs();
}

void Casino_BeginOverlay(void) {
  InitButtonMaps();
  DebugMenuLoadStartMenuGraphics();
  SetVBlankCallback(CasinoMenuVBlank);
  CpuCopy16(gUnk_8079424, &gPaletteBuffer[0xE0], 32);
  Casino_SetHudGoldColor();
  LoadPalettes();
  Casino_ClearOam();
  Casino_ClearRightHud();
  DebugMenuUploadStartMenuText(); /* push restored BG2 map to VRAM */
  LoadOam();
  DebugMenuLatchButtons();
  REG_WIN0H = 0x38B8;
  REG_WIN0V = 0x2878;
  CasinoMenuVBlank();
}

void Casino_BeginPlayField(void) {
  InitButtonMaps();
  DebugMenuLoadStartMenuGraphics();
  SetVBlankCallback(CasinoPlayVBlank);
  CpuCopy16(gUnk_8079424, &gPaletteBuffer[0xE0], 32);
  Casino_SetHudGoldColor();
  LoadPalettes();
  Casino_ClearOam();
  LoadOam();
  DebugMenuLatchButtons();
  Casino_BlankTextRows();
  /* Start fully darkened; caller draws first frame then Casino_FadeInPlayField. */
  gBLDCNT = BLDCNT_TGT1_ALL | BLDCNT_EFFECT_DARKEN;
  gBLDY = 16;
  LoadBlendingRegs();
  CasinoPlayVBlank();
}

void Casino_FadeInPlayField(void) {
  int i;

  for (i = 16; i >= 0; i--) {
    WaitForVBlank(); /* PlayVBlank restores menu blend — override for fade step */
    gBLDCNT = BLDCNT_TGT1_ALL | BLDCNT_EFFECT_DARKEN;
    gBLDY = i;
    LoadBlendingRegs();
  }
  gBLDCNT = 0xE8;
  gBLDY = 8;
  LoadBlendingRegs();
}

void Casino_EndOverlay(void) {
  Casino_ClearOam();
  LoadOam();
  gBLDCNT = 0;
  gBLDY = 0;
  LoadBlendingRegs();
  gInputRepeatTimer = 0;
  DisableDisplay();
}

u16 Casino_Buttons(void) {
  return DebugMenuButtons();
}

void Casino_BlankTextRows(void) {
  u8 row;
  for (row = 0; row < DEBUG_SM_ROWS; row++) {
    DebugMenuCopyLineStartMenu(row, gDebugMenuStartMenuBlankLine);
    DebugMenuSetLinePaletteStartMenu(row, 15);
  }
  DebugMenuUploadStartMenuText();
}

void Casino_WriteTextRow(u8 row, const u8 *ascii) {
  Casino_WriteSideText(FALSE, row, ascii, CASINO_TEXT_PAL_WHITE);
}

static u16 CasinoReadGlyphArg(const u8 **textPtr) {
  const u8 *text = *textPtr;
  u16 glyph;

  if (*text == '\0' || *text == '$') {
    glyph = gUnk_8E00E30[0][0] << 8 | gUnk_8E00E30[0][1];
  } else if (*text <= 127) {
    glyph = gUnk_8E00E30[*text - 32][0] << 8 | gUnk_8E00E30[*text - 32][1];
    text++;
  } else {
    glyph = text[0] << 8 | text[1];
    text += 2;
  }
  *textPtr = text;
  return (glyph >> 8) | (glyph << 8);
}

void Casino_SetHudGoldColor(void) {
  gPaletteBuffer[0xE0 + 1] = CASINO_GOLD_TEXT_COLOR;
  /* Bank 13 foreground for unaffordable stake options. */
  CpuCopy16(gUnk_8079424, &gPaletteBuffer[0xD0], 32);
  gPaletteBuffer[0xD0 + 1] = CASINO_GREY_TEXT_COLOR;
}

static void Casino_RestoreBg3Map(void) {
  u8 i;

  for (i = 0; i < DEBUG_SM_BG1_ROWS; i++)
    DmaCopy16(3, gUnk_8079444[i], gBgVram.sbb1E[i], DEBUG_SM_ROW_BYTES);
  CpuCopy32(gBgVram.sbb1E, CASINO_BG3_VRAM, DEBUG_SM_BG1_ROWS * DEBUG_SM_ROW_BYTES);
}

static void Casino_ClearRightHud(void) {
  u8 row, col;

  /* Wipe right-side glyphs only (tiles 0x08..; 5 rows end at 0x7F — must not
   * reach left text at 0x81 or sbb1E at 0x180+). */
  CpuFill16(0, (u8 *)gBgVram.sbb18 + CASINO_RIGHT_TEXT_OFFSET,
            DEBUG_SM_ROWS * CASINO_RIGHT_TEXT_BLOCKS * 4 * 32);
  for (row = 0; row < DEBUG_SM_BG1_ROWS; row++) {
    for (col = CASINO_RIGHT_MAP_COL; col < 30; col++)
      gBgVram.sbb1F[row][col] = gUnk_80798F4[row][col];
  }
  Casino_RestoreBg3Map();
}

static void Casino_UpdateMenuCursor(u8 screenRow) {
  u32 *oam = (u32 *)&gOamBuffer[0];

  /* Pre-nudge start-menu cursor: vanilla X (0x4040), Y tracks DEBUG_SM_BG2VOFS. */
  oam[0] = (screenRow << 4) + DEBUG_SM_CURSOR_Y + 4 | 0x40400000;
  oam[1] = 0x800;
  Casino_ReloadCursorPalette();
}

void Casino_WriteSideText(u8 rightSide, u8 row, const u8 *ascii, u8 paletteNum) {
  u8 buf[2 + CASINO_RIGHT_TEXT_CHARS + 1];
  u8 i;
  const u8 *text;
  u8 *dest;
  u8 block;
  u16 base;
  u8 mapRow;
  u16 palMask;
  u8 chars;

  if (!rightSide) {
    u8 leftBuf[2 + DEBUG_SM_CHARS + 1];
    u8 done;

    if (ascii == NULL) {
      DebugMenuCopyLineStartMenu(row, gDebugMenuStartMenuBlankLine);
      DebugMenuSetLinePaletteStartMenu(row, paletteNum);
      return;
    }
    leftBuf[0] = '$';
    leftBuf[1] = '0';
    /* Stop at NUL — do not read into the next RODATA string ("Domi"/"Ç6" junk). */
    done = 0;
    for (i = 0; i < DEBUG_SM_CHARS; i++) {
      if (!done && ascii[i] != '\0')
        leftBuf[2 + i] = ascii[i];
      else {
        done = 1;
        leftBuf[2 + i] = ' ';
      }
    }
    leftBuf[2 + DEBUG_SM_CHARS] = '\0';
    DebugMenuCopyLineStartMenu(row, leftBuf);
    DebugMenuSetLinePaletteStartMenu(row, paletteNum);
    return;
  }

  chars = CASINO_RIGHT_TEXT_CHARS;
  buf[0] = '$';
  buf[1] = '0';
  {
    u8 done = 0;

    for (i = 0; i < chars; i++) {
      if (!done && ascii != NULL && ascii[i] != '\0')
        buf[2 + i] = ascii[i];
      else {
        done = 1;
        buf[2 + i] = ' ';
      }
    }
  }
  buf[2 + chars] = '\0';

  /* Skip $0 language prefix — GetCurrentLanguageString does this on the left path. */
  text = GetCurrentLanguageString(buf);
  dest = (u8 *)gBgVram.sbb18 + CASINO_RIGHT_TEXT_OFFSET + row * (CASINO_RIGHT_TEXT_BLOCKS * 4 * 32);
  for (i = 0; i < chars; i++)
    sub_8020968(dest + (i / 2 * 4 + (i & 1)) * 32, CasinoReadGlyphArg(&text), 0x901);

  base = CASINO_RIGHT_TEXT_TILE + row * (CASINO_RIGHT_TEXT_BLOCKS * 4);
  mapRow = row * 2;
  palMask = (paletteNum & 0xF) << 12;
  for (block = 0; block < CASINO_RIGHT_TEXT_BLOCKS; block++) {
    u8 col = CASINO_RIGHT_MAP_COL + block * 2;
    u16 tile = base + block * 4;
    if (col + 1 >= 30)
      break;
    gBgVram.sbb1F[mapRow][col] = palMask | ((tile + 0) & 0x3FF);
    gBgVram.sbb1F[mapRow][col + 1] = palMask | ((tile + 1) & 0x3FF);
    gBgVram.sbb1F[mapRow + 1][col] = palMask | ((tile + 2) & 0x3FF);
    gBgVram.sbb1F[mapRow + 1][col + 1] = palMask | ((tile + 3) & 0x3FF);
  }
}

void Casino_UploadHudText(void) {
  DebugMenuUploadStartMenuText();
  /* LoadCharblock3 re-pushes sbb1E from WRAM — keep BG3 map pristine. */
  Casino_RestoreBg3Map();
}

void Casino_ReloadCursorPalette(void) {
  MenuCursor_LoadPalette(gPaletteBuffer + 256 + CASINO_CURSOR_PAL * 16);
  LoadPalettes();
}

void Casino_SetCursorOam(u8 x, u8 y, u8 hide) {
  struct OamData *oam = (struct OamData *)&gOamBuffer[0];

  if (hide) {
    sub_80411EC(oam);
    return;
  }
  oam->y = y;
  oam->affineMode = ST_OAM_AFFINE_OFF;
  oam->objMode = ST_OAM_OBJ_NORMAL;
  oam->mosaic = 0;
  oam->bpp = ST_OAM_4BPP;
  oam->shape = ST_OAM_SQUARE;
  oam->x = x;
  oam->hflip = 0;
  oam->vflip = 0;
  oam->size = 1; /* 16x16 */
  oam->tileNum = 0;
  oam->priority = 0;
  oam->paletteNum = CASINO_CURSOR_PAL;
  oam->affineParam = 0;
}

void Casino_DrawMenuLines(const u8 *const *lines, u8 count, u8 cursor) {
  u8 row;

  Casino_ClearRightHud();
  for (row = 0; row < DEBUG_SM_ROWS; row++) {
    if (row < count && lines[row] != NULL)
      Casino_WriteTextRow(row, lines[row]);
    else {
      DebugMenuCopyLineStartMenu(row, gDebugMenuStartMenuBlankLine);
      DebugMenuSetLinePaletteStartMenu(row, CASINO_TEXT_PAL_WHITE);
    }
  }
  DebugMenuUploadStartMenuText();
  Casino_UpdateMenuCursor(cursor);
  LoadOam();
}

static void Casino_DrawStakeMenu(u8 cursor) {
  u8 row;
  u8 pal;
  u8 canSelect[4];

  canSelect[0] = CanAfford(CASINO_BET_SMALL) ? TRUE : FALSE;
  canSelect[1] = CanAfford(CASINO_BET_MEDIUM) ? TRUE : FALSE;
  canSelect[2] = CanAfford(CASINO_BET_LARGE) ? TRUE : FALSE;
  canSelect[3] = TRUE; /* ante — trunk handles empty */

  Casino_ClearRightHud();
  for (row = 0; row < DEBUG_SM_ROWS; row++) {
    if (row < 4) {
      pal = canSelect[row] ? CASINO_TEXT_PAL_WHITE : CASINO_TEXT_PAL_GREY;
      Casino_WriteSideText(FALSE, row, sStakeLines[row], pal);
    } else {
      DebugMenuCopyLineStartMenu(row, gDebugMenuStartMenuBlankLine);
      DebugMenuSetLinePaletteStartMenu(row, CASINO_TEXT_PAL_WHITE);
    }
  }
  DebugMenuUploadStartMenuText();
  Casino_UpdateMenuCursor(cursor);
  LoadOam();
}

/* Clear only the 4×256 used rows — full 0x1000 fill wipes the interleaved sibling. */
static void Casino_ClearMiniSlot(u8 *dest) {
  u8 i;

  for (i = 0; i < 4; i++)
    CpuFill16(0, dest + i * 0x400, 0x100);
}

void Casino_ComposeFaceDownMini(u16 tileNum) {
  u8 *dest = gBgVram.cbb4 + tileNum * 32;

  Casino_ClearMiniSlot(dest);
  CopyFaceDownCardTiles(dest);
}

void Casino_ComposeFaceUpMini(u16 tileNum, u16 cardId) {
  u8 *dest = gBgVram.cbb4 + tileNum * 32;

  Casino_ClearMiniSlot(dest);
  sub_80573D0(dest, cardId);
}

void Casino_FlushMiniCards(void) {
  CopyMiniCardPalette(gPaletteBuffer + 256);
  Casino_ReloadCursorPalette();
  Casino_SetHudGoldColor();
  LoadObjVRAM();
  LoadPalettes();
}

void Casino_LoadFaceDownMini(u16 tileNum) {
  Casino_ComposeFaceDownMini(tileNum);
  Casino_FlushMiniCards();
}

void Casino_LoadFaceUpMini(u16 tileNum, u16 cardId) {
  Casino_ComposeFaceUpMini(tileNum, cardId);
  Casino_FlushMiniCards();
}

void Casino_SetMiniOam(u8 slot, u16 tileNum, u8 x, u8 y, u8 hide) {
  struct OamData *oam = (struct OamData *)&gOamBuffer[slot * 4];

  if (hide) {
    sub_80411EC(oam);
    return;
  }
  oam->y = y;
  oam->affineMode = ST_OAM_AFFINE_OFF;
  oam->objMode = ST_OAM_OBJ_NORMAL;
  oam->mosaic = 0;
  oam->bpp = ST_OAM_8BPP;
  oam->shape = 0;
  oam->x = x;
  oam->hflip = 0;
  oam->vflip = 0;
  oam->size = 2;
  oam->tileNum = tileNum;
  oam->priority = 2;
  oam->paletteNum = 0;
  oam->affineParam = 0;
}

static u8 PickAnteFromTrunk(u16 *outCardId) {
  gAnte = CARD_NONE;
  DuelTrunkMenu();
  if (gAnte == CARD_NONE)
    return FALSE;
  *outCardId = gAnte;
  return TRUE;
}

u8 Casino_PromptStake(struct CasinoStake *out) {
  u8 cursor = 0;

  out->kind = CASINO_STAKE_NONE;
  out->dominoAmount = 0;
  out->anteCardId = CARD_NONE;

  Casino_BeginOverlay();
  while (1) {
    u16 buttons;
    u8 canSelect[4];

    canSelect[0] = CanAfford(CASINO_BET_SMALL) ? TRUE : FALSE;
    canSelect[1] = CanAfford(CASINO_BET_MEDIUM) ? TRUE : FALSE;
    canSelect[2] = CanAfford(CASINO_BET_LARGE) ? TRUE : FALSE;
    canSelect[3] = TRUE;

    Casino_DrawStakeMenu(cursor);
    buttons = Casino_Buttons();
    if (buttons & B_BUTTON) {
      PlayMusic(SFX_CANCEL);
      Casino_EndOverlay();
      return FALSE;
    }
    if ((buttons & DPAD_UP) && cursor > 0) {
      PlayMusic(SFX_MOVE_CURSOR);
      cursor--;
    }
    if ((buttons & DPAD_DOWN) && cursor < 3) {
      PlayMusic(SFX_MOVE_CURSOR);
      cursor++;
    }
    if (buttons & A_BUTTON) {
      if (cursor <= 2) {
        u32 amount = sStakeDominoAmounts[cursor];
        if (!canSelect[cursor]) {
          PlayMusic(0x39);
          WaitForVBlank();
          continue;
        }
        PlayMusic(SFX_SELECT);
        RemoveMoney(amount);
        out->kind = CASINO_STAKE_DOMINO;
        out->dominoAmount = amount;
        Casino_EndOverlay();
        return TRUE;
      }
      /* Ante: open trunk; B/cancel returns to this menu. */
      PlayMusic(SFX_SELECT);
      Casino_EndOverlay();
      if (PickAnteFromTrunk(&out->anteCardId) == TRUE) {
        out->kind = CASINO_STAKE_ANTE;
        return TRUE;
      }
      Casino_BeginOverlay();
      DebugMenuLatchButtons();
      continue;
    }
    WaitForVBlank();
  }
}

static u16 PickPrize(u16 anteCardId) {
  const u16 *pool;
  u16 count;

  if (IsNormalAnte(anteCardId) == FALSE) {
    pool = gCasinoPrizePoolSecondary;
    count = gCasinoPrizePoolSecondaryCount;
  } else {
    pool = gCasinoPrizePoolPrimary;
    count = gCasinoPrizePoolPrimaryCount;
  }
  if (count == 0)
    return CARD_NONE;
  return pool[RandRangeU16(0, count - 1)];
}

void Casino_ResolveStake(const struct CasinoStake *stake, enum CasinoOutcome outcome) {
  if (stake == NULL || stake->kind == CASINO_STAKE_NONE)
    return;

  if (stake->kind == CASINO_STAKE_DOMINO) {
    if (outcome == CASINO_OUTCOME_WIN)
      AddMoney((unsigned long long)stake->dominoAmount * 2);
    else if (outcome == CASINO_OUTCOME_PUSH)
      AddMoney(stake->dominoAmount);
    return;
  }

  if (stake->kind == CASINO_STAKE_ANTE) {
    if (outcome == CASINO_OUTCOME_LOSE) {
      if (stake->anteCardId != CARD_NONE)
        RemoveCardQtyFromTrunk(stake->anteCardId, 1);
    } else if (outcome == CASINO_OUTCOME_WIN) {
      u16 prize = PickPrize(stake->anteCardId);
      if (prize != CARD_NONE)
        AddCardQtyToTrunk(prize, 1);
    }
  }
}
