#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "debug_ai_mode.h"

static const u8 sTextboxClearSpaces[] APPEND_RODATA =
    "                            "
    "                            "
    "                            "
    "                             ";

#include "duel_opponent_hand_scroll.h"
#include "duel.h"
#include "duel_textbox.h"
#include "text.h"
#include "graveyard_effects.h"
#include "the_unhappy_maiden.h"
#include "vampire_baby.h"
#include "ghost_knight_of_jackal.h"
#include "mefist_the_infernal_general.h"
#include "guardian_angel_joan.h"
#include "royal_knight.h"
#include "elemental_hero_steam_healer.h"
#include "elemental_hero_flame_wingman.h"
#include "elemental_hero_core.h"
#include "elemental_hero_ice_edge.h"
#include "elemental_hero_sunrise.h"
#include "lesser_fiend.h"
#include "dark_magician_of_chaos.h"
#include "needle_burrower.h"
#include "hyper_hammerhead.h"
#include "des_kangaroo.h"
#include "continuous_destruction_punch.h"
#include "amazoness_heirloom.h"
#include "d_d_warrior.h"
#include "absorbing_kid_from_the_sky.h"
#include "airknight_parshath.h"
#include "sasuke_samurai_3.h"
#include "coffin_seller.h"
#include "reaper_on_the_nightmare.h"
#include "spirit_reaper.h"
#include "yubel.h"
#include "dark_room_of_nightmare.h"
#include "hamon_lord_of_striking_thunder.h"

void sub_8040B4C(void);
void sub_80408FC(void);
void DisplayCardInfoBar(void);
void sub_8040EF0(void);
void sub_80411EC(struct OamData *oam);
s16 fix_mul(s16 a, s16 b);
s16 fix_inverse(s16 a);

extern struct OamData gOamBuffer[];
extern const s16 sin_cos_table[];

extern const u8 gFieldArenaTiles[];
extern const u8 gFieldForestTiles[];
extern const u8 gFieldWastelandTiles[];
extern const u8 gFieldMountainTiles[];
extern const u8 gFieldSogenTiles[];
extern const u8 gFieldUmiTiles[];
extern const u8 gFieldYamiTiles[];
extern const u16 gFieldArenaTilemap[][31];
extern const u16 gFieldForestTilemap[][31];
extern const u16 gFieldWastelandTilemap[][31];
extern const u16 gFieldMountainTilemap[][31];
extern const u16 gFieldSogenTilemap[][31];
extern const u16 gFieldUmiTilemap[][31];
extern const u16 gFieldYamiTilemap[][31];
extern const u16 gFieldArenaPalette[];
extern const u16 gFieldForestPalette[];
extern const u16 gFieldWastelandPalette[];
extern const u16 gFieldMountainPalette[];
extern const u16 gFieldSogenPalette[];
extern const u16 gFieldUmiPalette[];
extern const u16 gFieldYamiPalette[];

static const u8 *const sFieldTilePtrs[] APPEND_RODATA = {
  gFieldArenaTiles,
  gFieldForestTiles,
  gFieldWastelandTiles,
  gFieldMountainTiles,
  gFieldSogenTiles,
  gFieldUmiTiles,
  gFieldYamiTiles,
};

static const u16 (*const sFieldTileMapPtrs[])[31] APPEND_RODATA = {
  gFieldArenaTilemap,
  gFieldForestTilemap,
  gFieldWastelandTilemap,
  gFieldMountainTilemap,
  gFieldSogenTilemap,
  gFieldUmiTilemap,
  gFieldYamiTilemap,
};

static const u16 *const sFieldPalettePtrs[] APPEND_RODATA = {
  gFieldArenaPalette,
  gFieldForestPalette,
  gFieldWastelandPalette,
  gFieldMountainPalette,
  gFieldSogenPalette,
  gFieldUmiPalette,
  gFieldYamiPalette,
};

extern unsigned short g8E0D5A6[];
extern u8 g8E0D5A1[];
extern u16 gNewButtons;

void WaitForTextboxAdvanceInput(struct DuelTextbox *);

static void ClearDuelPopupTextboxTiles(void) {
  CopyStringTilesToVRAMBuffer(gBgVram.cbb0 + 0x88A0, (u8 *)sTextboxClearSpaces, 0x101);
}

static u16 GetScrollTargetVofs(u8 row) {
  if (IsOpponentHandFieldScrollEnabled() && row < NUM_DUEL_BOARD_ROWS)
    return GetBoardScrollVofs(row);

  return g8E0D5A6[row];
}

static bool8 ScrollSnapRequired(u8 destRow) {
  if (!IsOpponentHandFieldScrollEnabled())
    return FALSE;

  if (destRow == OPPONENT_HAND_ROW)
    return TRUE;

  return IsLeavingOpponentHandScroll(destRow);
}

u32 AdjustBackgroundBeforeTurnStart(u8 row);

LYN_REPLACE_CHECK(AdjustBackgroundBeforeTurnStart);
u32 AdjustBackgroundBeforeTurnStart__Replacement(u8 row) {
  if (IsOpponentHandFieldScrollEnabled() && row < NUM_DUEL_BOARD_ROWS)
    return gBG2VOFS = GetBoardScrollVofs(row);

  return gBG2VOFS = g8E0D5A1[row];
}

void DisplayCardAttrTypeInInfoBar(void);
void CopyAttributeIconTiles (u8, u8*);
void CopyAttributeIconPal (u8, u16*);
void CopyTypeIconTiles (u8, u8*);
void CopyTypeIconPal (u8, u16*);

LYN_REPLACE_CHECK(DisplayCardAttrTypeInInfoBar);
void DisplayCardAttrTypeInInfoBar__Replacement(void) {
  CopyAttributeIconTiles(gCardInfo.attribute, gBgVram.cbb0 + 0x8580);
  CopyAttributeIconPal(gCardInfo.attribute, gPaletteBuffer + 96);
  CopyTypeIconTiles(gCardInfo.type, gBgVram.cbb0 + 0x8500);
  CopyTypeIconPal(gCardInfo.type, gPaletteBuffer + 80);
}

void sub_8041D78(u8 arg0);
void sub_8041DF0(u8 arg0);
void sub_8057808(void);
void sub_804078C(void);
void sub_8040FDC(void);
void sub_80411D4(void);
void LoadOam(void);
void LoadBgOffsets(void);

static void FlushPartialDuelGfx(void) {
  if (ShouldDrawOpponentHandOnField())
    DrawOpponentHandOnField();
  else
    RestoreOpponentHandFieldWindow();

  LoadOam();
  LoadBgOffsets();
  CpuCopy32(gBgVram.cbb0 + 0x8040, (unsigned char *)BG_VRAM + 0x8040, 0x740);
  CpuCopy16(gPaletteBuffer + 0x50, (u16 *)PLTT + 0x50, 0x40);
}

static void FlushDuelGfxAfterCursorMove(void) {
  if (gRuntimeConfig.turn_off_visual_scanner == TRUE)
    sub_80411D4();
  else
    FlushPartialDuelGfx();
}

LYN_REPLACE_CHECK(sub_8040FDC);
void sub_8040FDC__Replacement(void) {
  if (gRuntimeConfig.turn_off_visual_scanner == TRUE)
    sub_80411D4();
  else
    FlushPartialDuelGfx();
}

LYN_REPLACE_CHECK(sub_8041D78);
void sub_8041D78__Replacement(u8 arg0) {
  bool8 leavingHand = IsLeavingOpponentHandScroll(arg0);

  if (gRuntimeConfig.turn_off_visual_scanner == TRUE || ScrollSnapRequired(arg0)) {
    gBG2VOFS = GetScrollTargetVofs(arg0);
    sub_8057808();
    sub_804078C();
    WaitForVBlank();
    if (leavingHand)
      RebuildFieldCardGfxAfterOpponentHand();
    FlushDuelGfxAfterCursorMove();
    return;
  }

  while (gBG2VOFS > GetScrollTargetVofs(arg0) + 256) {
    gBG2VOFS -= 256;
    sub_8057808();
    WaitForVBlank();
    sub_8040FDC();
  }
  gBG2VOFS = GetScrollTargetVofs(arg0);
  sub_8057808();
  sub_804078C();
  WaitForVBlank();
  if (leavingHand)
    RebuildFieldCardGfxAfterOpponentHand();
  FlushDuelGfxAfterCursorMove();
}

LYN_REPLACE_CHECK(sub_8041DF0);
void sub_8041DF0__Replacement(u8 arg0) {
  bool8 leavingHand = IsLeavingOpponentHandScroll(arg0);

  if (gRuntimeConfig.turn_off_visual_scanner == TRUE || ScrollSnapRequired(arg0)) {
    gBG2VOFS = GetScrollTargetVofs(arg0);
    sub_8057808();
    sub_804078C();
    WaitForVBlank();
    if (leavingHand)
      RebuildFieldCardGfxAfterOpponentHand();
    FlushDuelGfxAfterCursorMove();
    return;
  }

  while (gBG2VOFS < GetScrollTargetVofs(arg0) - 256) {
    gBG2VOFS += 256;
    sub_8057808();
    WaitForVBlank();
    sub_8040FDC();
  }
  gBG2VOFS = GetScrollTargetVofs(arg0);
  sub_8057808();
  sub_804078C();
  WaitForVBlank();
  if (leavingHand)
    RebuildFieldCardGfxAfterOpponentHand();
  FlushDuelGfxAfterCursorMove();
}

LYN_REPLACE_CHECK(WaitForTextboxAdvanceInput);
void WaitForTextboxAdvanceInput__Replacement(struct DuelTextbox *textbox) {
  if (DebugAiMode_IsBothSides() == TRUE) {
    textbox->textCursor++;
    textbox->tileCursor = 0;
    textbox->blinkFrameCounter = 0;
    textbox->mode = 0;
    ClearDuelPopupTextboxTiles();
    return;
  }

  if (gNewButtons & (A_BUTTON | B_BUTTON | R_BUTTON)) {
    PlayMusic(SFX_DIALOGUE);
    textbox->textCursor++;
    textbox->tileCursor = 0;
    textbox->blinkFrameCounter = 0;
    textbox->mode = 0;
    ClearDuelPopupTextboxTiles();
  } else {
    switch (textbox->blinkFrameCounter++) {
    case 0:
      if (textbox->tileCursor % 2)
        sub_8020968(gBgVram.cbb0 + 0x88C0 + textbox->tileCursor / 2 * 128, 0xA081, 0x101);
      else
        sub_8020968(gBgVram.cbb0 + 0x88A0 + textbox->tileCursor / 2 * 128, 0xA081, 0x101);
      break;
    case 15:
      if (textbox->tileCursor % 2)
        sub_8020968(gBgVram.cbb0 + 0x88C0 + textbox->tileCursor / 2 * 128, 0x4081, 0x101);
      else
        sub_8020968(gBgVram.cbb0 + 0x88A0 + textbox->tileCursor / 2 * 128, 0x4081, 0x101);
      break;
    case 29:
      textbox->blinkFrameCounter = 0;
      break;
    }
  }
}

static void RestoreBattleOamAfterAnimation(void) {
  u8 i;

  for (i = 0; i < 128; i++)
    sub_80411EC(gOamBuffer + i);

  gOamBuffer[0].affineParam = fix_mul(sin_cos_table[64], fix_inverse(256));
  gOamBuffer[1].affineParam = fix_mul(sin_cos_table[0], fix_inverse(256));
  gOamBuffer[2].affineParam = fix_mul(-sin_cos_table[0], fix_inverse(256));
  gOamBuffer[3].affineParam = fix_mul(sin_cos_table[64], fix_inverse(256));

  gOamBuffer[4].affineParam = fix_mul(sin_cos_table[64], fix_inverse(256));
  gOamBuffer[5].affineParam = fix_mul(sin_cos_table[0], fix_inverse(256));
  gOamBuffer[6].affineParam = fix_mul(-sin_cos_table[0], fix_inverse(256));
  gOamBuffer[7].affineParam = fix_mul(sin_cos_table[64], fix_inverse(256));

  gOamBuffer[8].affineParam = fix_mul(sin_cos_table[128], fix_inverse(256));
  gOamBuffer[9].affineParam = fix_mul(sin_cos_table[64], fix_inverse(256));
  gOamBuffer[10].affineParam = fix_mul(-sin_cos_table[64], fix_inverse(256));
  gOamBuffer[11].affineParam = fix_mul(sin_cos_table[128], fix_inverse(256));
  gOamBuffer[8].affineParam = 0;
  gOamBuffer[9].affineParam = 256;
  gOamBuffer[10].affineParam = -257;
  gOamBuffer[11].affineParam = 0;

  gOamBuffer[12].affineParam = fix_mul(sin_cos_table[0xC0], fix_inverse(256));
  gOamBuffer[13].affineParam = fix_mul(sin_cos_table[128], fix_inverse(256));
  gOamBuffer[14].affineParam = fix_mul(-sin_cos_table[128], fix_inverse(256));
  gOamBuffer[15].affineParam = fix_mul(sin_cos_table[0xC0], fix_inverse(256));
  gOamBuffer[12].affineParam = 0xFF00;
  gOamBuffer[13].affineParam = 0;
  gOamBuffer[14].affineParam = 0;
  gOamBuffer[15].affineParam = -257;

  gOamBuffer[16].affineParam = fix_mul(sin_cos_table[256], fix_inverse(256));
  gOamBuffer[17].affineParam = fix_mul(sin_cos_table[0xC0], fix_inverse(256));
  gOamBuffer[18].affineParam = fix_mul(-sin_cos_table[0xC0], fix_inverse(256));
  gOamBuffer[19].affineParam = fix_mul(sin_cos_table[256], fix_inverse(256));
}

LYN_REPLACE_CHECK(sub_8040EF0);
void sub_8040EF0__Replacement(void) {
  WaitForVBlank();
  DisableDisplay();
  SetDuelFieldGfx(gDuel.field);
  gBG2VOFS = AdjustBackgroundBeforeTurnStart(1);
  sub_8040B4C();
  DisplayCardInfoBar();
  RestoreBattleOamAfterAnimation();
  sub_80577A4();
  sub_80408FC();
  WaitForVBlank();
  LoadVRAM();
  LoadBgOffsets();
  LoadOam();
  LoadPalettes();
  REG_DISPCNT = DISPCNT_BG1_ON | DISPCNT_BG2_ON | DISPCNT_OBJ_ON | DISPCNT_WIN0_ON;
  REG_BLDCNT = 0xD4;
  REG_BLDY = 10;
  ResolveTheUnhappyMaidenBattleEffect();
  ResolveVampireBabyBattleEffect();
  ResolveGhostKnightOfJackalBattleEffect();
  ResolveMefistTheInfernalGeneralDiscardBattleEffect();
  ResolveReaperOnTheNightmareDirectDamageEffect();
  ResolveSpiritReaperDiscardBattleEffect();
  ResolveGuardianAngelJoanBattleEffect();
  ResolveRoyalKnightBattleEffect();
  ResolveElementalHeroSteamHealerBattleEffect();
  ResolveElementalHeroFlameWingmanBattleEffect();
  ResolveLesserFiendBattleEffect();
  ResolveDarkMagicianOfChaosBattleEffect();
  ResolveAirknightParshathDrawBattleEffect();
  ResolveSasukeSamurai3BattleEffect();
  ResolveNeedleBurrowerBattleEffect();
  ResolveHyperHammerheadBattleEffect();
  ResolveYubelUltimateNightmareBattleEffect();
  ResolveDDWarriorBattleEffect();
  ResolveDesKangarooBattleEffect();
  ResolveContinuousDestructionPunchBattleEffect();
  ResolveAmazonessHeirloomBattleEffect();
  ResolveAbsorbingKidFromTheSkyBattleEffect();
  ResolveCoffinSellerBattleEffect();
  FinishGraveyardDrawBattleResolve();
  ResolveElementalHeroCoreBattledEffect();
  ResolveElementalHeroIceEdgeBattleEffect();
  ResolveYubelAttackedReflectEffect();
  ResolveElementalHeroSunriseDestroyEffect();
  ResolveHamonLordOfStrikingThunderBattleEffect();
}
