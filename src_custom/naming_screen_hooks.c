#include "global.h"
#include "configs/runtime.h"

typedef void (*VoidFunc)(void);
typedef void (*VBlankFunc)(void);

static inline void CallThumbVoid(u32 addr) {
  ((VoidFunc)(addr | 1))();
}

static inline VBlankFunc ThumbFunc(u32 addr) {
  return (VBlankFunc)(addr | 1);
}

extern u32 gUnk_807A9EC[];
extern u16 gRepeatedOrNewButtons;
extern u16 gNewButtons;
extern u16 gUnk_8081640[][30];
extern u16 gUnk_8081F10[];
extern u16 gUnk_8081440[];
extern u16 gUnk_8081AF0[];
extern u32 gUnk_807F2F0[];
void ClearGraphicsBuffers (void);
void sub_80075B0 (void);
void sub_8006B40 (void);
void sub_8006958 (void);
void sub_8006C60 (void);
void sub_8006E84 (void);
void sub_8007068 (void);
void sub_8007350 (void);

extern struct Unk8DF8114_Hooks {
  s8 unk0;
  s8 unk1;
  u8 unk2;
  u8 unk3;
  u8 unk4;
  u8 filler5[4];
  u8 unk9;
  u16 unkA;
  u16 unkC;
  u16 unkE[9];
  u16 unk20[9];
  u16 unk32;
  struct {
    u16 unk0;
    u16 unk2;
  } unk34[7][11];
  u8 filler168[2];
  u16 unk16A;
  u16 unk16C;
  u16 unk16E;
} * gUnk_8DF8114;

LYN_REPLACE_CHECK(NamingScreenMain);
APPEND_TEXT void NamingScreenMain__Replacement (void) {
  u16 i;

  ClearGraphicsBuffers();
  CallThumbVoid(0x0800604C);
  PlayMusic(MUSIC_NAMING_SCREEN);
  LZ77UnCompWram(gUnk_807A9EC, gBgVram.cbb0);
  CpuCopy16(gUnk_8081440, gPaletteBuffer, 512);
  for (i = 0; i < 20; i++)
    CpuCopy16(gUnk_8081640[i], gBgVram.cbb0 + 0xF000 + i * 64, 60);
  CpuCopy16(gUnk_8081F10, gBgVram.cbb0 + 0xF800, 1216);
  CpuCopy16(gUnk_8081AF0, gPaletteBuffer + 256, 512);
  LZ77UnCompWram(gUnk_807F2F0, gBgVram.cbb0 + 0x10000);
  sub_8020DB8((u32*)(gBgVram.cbb0 + 0x8020), (u8*)gUnk_8DF8114->unkE, 0x901);
  CallThumbVoid(0x0800683C);
  SetVBlankCallback(ThumbFunc(0x080074CC));
  WaitForVBlank();
  sub_80075B0();

  while (1) {
    if (gNewButtons & START_BUTTON) {
      if (gUnk_8DF8114->unk32 != 5) {
        PlayMusic(SFX_MOVE_CURSOR);
        gUnk_8DF8114->unk32 = 5;
      }
      else if (gUnk_8DF8114->unkE[0] != 0x4081) {
        PlayMusic(SFX_SELECT);
        gUnk_8DF8114->unk9 = 1;
        sub_8006B40();
        return;
      }
      else
        PlayMusic(SFX_FORBIDDEN);
      gUnk_8DF8114->unk16A = 0;
    }
    if (gNewButtons & A_BUTTON && gUnk_8DF8114->unk32 == 5) {
      if (gUnk_8DF8114->unkE[0] != 0x4081) {
        PlayMusic(SFX_SELECT);
        gUnk_8DF8114->unk9 = 1;
        sub_8006B40();
        return;
      }
      else
        PlayMusic(SFX_FORBIDDEN);
    }
    if (gRepeatedOrNewButtons & R_BUTTON) {
      if (gUnk_8DF8114->unk2 < 8) {
        PlayMusic(SFX_MOVE_CURSOR);
        gUnk_8DF8114->unk2++;
      }
    }
    else if (gRepeatedOrNewButtons & L_BUTTON && gUnk_8DF8114->unk2) {
      PlayMusic(SFX_MOVE_CURSOR);
      gUnk_8DF8114->unk2--;
    }
    switch (gUnk_8DF8114->unk3) {
      case 0:
        CallThumbVoid(0x08006764);
        CallThumbVoid(0x080064F4);
        break;
      case 1:
        if (gNewButtons & A_BUTTON) {
          if (gUnk_8DF8114->unk32 != 5)
            PlayMusic(SFX_SELECT);
          gUnk_8DF8114->unk0 = 0;
          gUnk_8DF8114->unk1 = 0;
          gUnk_8DF8114->unk3 = 0;
        }
        if (gNewButtons & B_BUTTON) {
          if (gUnk_8DF8114->unk32 == 5) {
            PlayMusic(SFX_CANCEL);
            gUnk_8DF8114->unk32 = 3;
            gUnk_8DF8114->unk0 = 0;
            gUnk_8DF8114->unk1 = 0;
            gUnk_8DF8114->unk3 = 0;
            gUnk_8DF8114->unk16A = 0;
            CallThumbVoid(0x0800683C);
          }
          else {
            PlayMusic(SFX_SELECT);
            gUnk_8DF8114->unk0 = 0;
            gUnk_8DF8114->unk1 = 0;
            gUnk_8DF8114->unk3 = 0;
          }
        }
        if (gRepeatedOrNewButtons & DPAD_LEFT) {
          gUnk_8DF8114->unk3 = 0;
          gUnk_8DF8114->unk0 = 10;
          gUnk_8DF8114->unk32 = 3;
        }
        else if (gRepeatedOrNewButtons & DPAD_RIGHT) {
          gUnk_8DF8114->unk3 = 0;
          gUnk_8DF8114->unk0 = 0;
          gUnk_8DF8114->unk32 = 3;
        }
        break;
    }
    if (gUnk_8DF8114->unk32 == 5)
      gUnk_8DF8114->unk3 = 1;
    sub_8006958();
    sub_8006B40();
    sub_8006C60();
    sub_8006E84();
    sub_8007068();
    sub_8007350();
    switch (gUnk_8DF8114->unk4) {
      case 0:
        gUnk_8DF8114->unk16C += 16;
        gUnk_8DF8114->unk16E += 16;
        if (gUnk_8DF8114->unk16C == 512)
          gUnk_8DF8114->unk4 = 1;
        break;
      case 1:
        gUnk_8DF8114->unk16C -= 16;
        gUnk_8DF8114->unk16E -= 16;
        if (gUnk_8DF8114->unk16C == 320)
          gUnk_8DF8114->unk4 = 0;
        break;
      default:
        gUnk_8DF8114->unk4 = 0;
        break;
    }
    LoadOam();
    WaitForVBlank();
  }
}
