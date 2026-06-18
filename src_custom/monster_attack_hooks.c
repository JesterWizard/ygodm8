#include "global.h"
#include "common-chax.h"
#include "ai_actions.h"
#include "duel.h"

void sub_801C610(unsigned char arg0);
void sub_801CB24(unsigned char arg0);
void sub_801C1DC(unsigned char side);

extern void sub_803EEFC(u8, const unsigned char *, u16);

extern const unsigned short g80B4894[];
extern const unsigned char g80B1E94[];
extern const unsigned char g80B3E94[];
extern const unsigned char g80B48B4[];

extern const unsigned short g80B68B4[];

extern unsigned short gPaletteBuffer[];
extern unsigned short gOamBuffer[];
extern unsigned short gBLDCNT;
extern unsigned short gBLDALPHA;

struct UnkE0081C {
  unsigned char unk0;
  unsigned char unk1;
} extern *gE0081C;

struct Unk8E00AA0 {
  unsigned short unk0;
  unsigned short unk2;
  unsigned char unk4;
  unsigned char unk5;
  unsigned char unk6;
  unsigned char unk7;
  unsigned char unk8;
} extern *g8E00AA0;

extern const unsigned short g80B68D4[][4];

#define CLASH_PALETTE_U16_OFFSET 256
#define CLASH_PALETTE_COLOR_COUNT 16
// Low clash-palette entries tint the BG red on weak matchups; slash uses the rest.
#define CLASH_BG_RED_COLOR_FIRST 1
#define CLASH_BG_RED_COLOR_LAST 6

static void LoadNeutralClashBackgroundPalette(void) {
  u16 i;

  CpuCopy16(g80B4894, gPaletteBuffer + CLASH_PALETTE_U16_OFFSET, CLASH_PALETTE_COLOR_COUNT);
  for (i = CLASH_BG_RED_COLOR_FIRST; i <= CLASH_BG_RED_COLOR_LAST; i++)
    gPaletteBuffer[CLASH_PALETTE_U16_OFFSET + i] = 0;
}

typedef void (*BattleDestroyAnimFn)(void);

// ponytail: static vanilla battle FX; upgrade path = export from monster_attack_screen.c
#define BATTLE_DESTROY_PLAYER_ANIM ((BattleDestroyAnimFn)0x0801C2A1)
#define BATTLE_DESTROY_OPPONENT_ANIM ((BattleDestroyAnimFn)0x0801C219)

extern u8 gSharedMem[];

LYN_REPLACE_CHECK(sub_801C1DC);
void sub_801C1DC__Replacement(unsigned char side) {
  CpuFill16(0, gSharedMem, 0x4314);
  if (side == 0)
    BATTLE_DESTROY_PLAYER_ANIM();
  else if (side == 1)
    BATTLE_DESTROY_OPPONENT_ANIM();
}

LYN_REPLACE_CHECK(sub_801C610);
void sub_801C610__Replacement(unsigned char arg0) {
  unsigned short i;

  TryPlayCustomOpponentAttackVoice();

  LoadNeutralClashBackgroundPalette();
  sub_803EEFC(0, g80B1E94, 256);
  sub_803EEFC(1, g80B3E94, 80);
  for (i = 0; i < 128; i++) {
    gOamBuffer[i * 4] = 0xA0;
    gOamBuffer[i * 4 + 1] = 0xF0;
    gOamBuffer[i * 4 + 2] = 0xC00;
    gOamBuffer[i * 4 + 3] = 0;
  }
  gBLDCNT = 0x2C10;
  gBLDALPHA = 0x80E;
  gBLDY = 0;
  gE0081C->unk0 = 0;
  gE0081C->unk1 = 0;

  (void)arg0;
}

LYN_REPLACE_CHECK(sub_801CB24);
void sub_801CB24__Replacement(unsigned char arg0) {
  unsigned short i;

  if (!arg0) {
    g8E00AA0->unk0 = 0;
    g8E00AA0->unk4 = 4;
    g8E00AA0->unk2 = 508;
    g8E00AA0->unk5 = 12;
  } else {
    g8E00AA0->unk0 = 124;
    g8E00AA0->unk4 = 4;
    g8E00AA0->unk2 = 116;
    g8E00AA0->unk5 = 12;
  }
  g8E00AA0->unk6 = 0;
  g8E00AA0->unk7 = 0;
  g8E00AA0->unk8 = 0;
  LoadNeutralClashBackgroundPalette();
  CpuCopy16(g80B68B4, gPaletteBuffer + CLASH_PALETTE_U16_OFFSET + 16, 32);
  sub_803EEFC(0, g80B1E94, 256);
  sub_803EEFC(1, g80B3E94, 80);
  sub_803EEFC(2, g80B48B4, 256);
  for (i = 0; i < 128; i++) {
    gOamBuffer[i * 4] = 0xA0;
    gOamBuffer[i * 4 + 1] = 0xF0;
    gOamBuffer[i * 4 + 2] = 0xC00;
    gOamBuffer[i * 4 + 3] = 0;
  }
  for (i = 0; i < 4; i++)
    gOamBuffer[i * 4 + 3] = g80B68D4[0][i];
  gBLDCNT = 0x2C10;
  gBLDALPHA = 0x80E;
  gBLDY = 0;
}
