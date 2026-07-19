#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "duel.h"
#include "mini_card.h"
#include "synchro_duel.h"
#include "text.h"
#include "xyz_duel.h"

enum MonsterAction {
  MONSTER_ACTION_ATTACK = 0,
  MONSTER_ACTION_DEFEND = 1,
  MONSTER_ACTION_TRIBUTE = 2,
  MONSTER_ACTION_EFFECT = 3,
  MONSTER_ACTION_SYNCHRO = 4,
  MONSTER_ACTION_XYZ = 5,
  MONSTER_ACTION_COUNT = 6
};

union MonsterMenuVram {
  u8 a[0x4000];
  u16 b[0x2000];
};

extern union MonsterMenuVram gVr;
extern u16 g80F1880[][30];
extern u16 g80F30E0[];
extern u8 g8DF811C[];
extern u16 gRepeatedOrNewButtons;
extern u16 gNewButtons;

void PlayMusic(int);
void WaitForVBlank(void);
void LoadOam(void);
void SetVBlankCallback(void (*func)(void));
void sub_8041014(void);
u16 sub_08007FEC(u8, u8, u16);
void sub_800800C(u8, u8, u16, u16);

/* Byte offsets into BG map at 0xE800; /2 indexes gVr.b. */
static const u16 sMonsterActionHighlight[] APPEND_RODATA = {
  0xE8C4, /* Attack */
  0xE944, /* Defend */
  0xE8D8, /* Tribute */
  0xE958, /* Effect */
  0xE9C4, /* Synchro (left, under Defend) */
  0xE9D8, /* XYZ (right, under Effect) */
};

/* Attack=65, Defend=81, Tribute=97, Effect=121, Synchro=145, XYZ=161. */
#define MONSTER_ACTION_TILE_SYNCHRO_TOP 145
#define MONSTER_ACTION_TILE_SYNCHRO_BOT 147
#define MONSTER_ACTION_TILE_XYZ_TOP 161
#define MONSTER_ACTION_TILE_XYZ_BOT 163

static const unsigned char sText_AttackDefendTributeEffectSynchroXyz[] APPEND_RODATA = __(
  "{ENG}"
    "Attack  Defend  Tribute     Effect      Synchro XYZ     "
  "{FRE}"
    "Attaque Défense Tribut      Effet       Synchro XYZ     "
  "{GER}"
    "Angriff Verteid.Tribut      Effekt      Synchro XYZ     "
  "{ITA}"
    "Attacca Difendi Tributo     Effetto     Synchro XYZ     "
  "{SPA}"
    "Atacar  DefenderTributo     Efecto      Synchro XYZ     "
  "{JAP}"
    "こうげき" "守備　" "生けにえ" "効果　" "シンクロ" "エクシーズ"
);

static const unsigned char sText_AttackDefendTributeEffect[] APPEND_RODATA = __(
  "{ENG}"
    "Attack  Defend  Tribute     Effect      "
  "{FRE}"
    "Attaque Défense Tribut      Effet       "
  "{GER}"
    "Angriff Verteid.Tribut      Effekt      "
  "{ITA}"
    "Attacca Difendi Tributo     Effetto     "
  "{SPA}"
    "Atacar  DefenderTributo     Efecto      "
  "{JAP}"
    "こうげき" "守備　" "生けにえ" "効果　"
);

static const u8 sMonsterActionNextUp[] APPEND_RODATA = {
  [MONSTER_ACTION_ATTACK] = MONSTER_ACTION_ATTACK,
  [MONSTER_ACTION_DEFEND] = MONSTER_ACTION_ATTACK,
  [MONSTER_ACTION_TRIBUTE] = MONSTER_ACTION_TRIBUTE,
  [MONSTER_ACTION_EFFECT] = MONSTER_ACTION_TRIBUTE,
  [MONSTER_ACTION_SYNCHRO] = MONSTER_ACTION_DEFEND,
  [MONSTER_ACTION_XYZ] = MONSTER_ACTION_EFFECT,
};

static const u8 sMonsterActionNextDown[] APPEND_RODATA = {
  [MONSTER_ACTION_ATTACK] = MONSTER_ACTION_DEFEND,
  [MONSTER_ACTION_DEFEND] = MONSTER_ACTION_SYNCHRO,
  [MONSTER_ACTION_TRIBUTE] = MONSTER_ACTION_EFFECT,
  [MONSTER_ACTION_EFFECT] = MONSTER_ACTION_XYZ,
  [MONSTER_ACTION_SYNCHRO] = MONSTER_ACTION_SYNCHRO,
  [MONSTER_ACTION_XYZ] = MONSTER_ACTION_XYZ,
};

static const u8 sMonsterActionNextLeft[] APPEND_RODATA = {
  [MONSTER_ACTION_ATTACK] = MONSTER_ACTION_ATTACK,
  [MONSTER_ACTION_DEFEND] = MONSTER_ACTION_DEFEND,
  [MONSTER_ACTION_TRIBUTE] = MONSTER_ACTION_ATTACK,
  [MONSTER_ACTION_EFFECT] = MONSTER_ACTION_DEFEND,
  [MONSTER_ACTION_SYNCHRO] = MONSTER_ACTION_SYNCHRO,
  [MONSTER_ACTION_XYZ] = MONSTER_ACTION_SYNCHRO,
};

static const u8 sMonsterActionNextRight[] APPEND_RODATA = {
  [MONSTER_ACTION_ATTACK] = MONSTER_ACTION_TRIBUTE,
  [MONSTER_ACTION_DEFEND] = MONSTER_ACTION_EFFECT,
  [MONSTER_ACTION_TRIBUTE] = MONSTER_ACTION_TRIBUTE,
  [MONSTER_ACTION_EFFECT] = MONSTER_ACTION_EFFECT,
  [MONSTER_ACTION_SYNCHRO] = MONSTER_ACTION_XYZ,
  [MONSTER_ACTION_XYZ] = MONSTER_ACTION_XYZ,
};

static u8 SynchroOptionVisible(void)
{
  return SynchroDuel_PlayerCanSummon();
}

static u8 XyzOptionVisible(void)
{
  return XyzDuel_PlayerCanSummon();
}

static u8 MonsterAction_IsVisible(u8 action, u8 showSynchro, u8 showXyz)
{
  if (action == MONSTER_ACTION_SYNCHRO)
    return showSynchro;
  if (action == MONSTER_ACTION_XYZ)
    return showXyz;
  return TRUE;
}

static u8 MonsterAction_NextUp(u8 cur)
{
  return sMonsterActionNextUp[cur];
}

static u8 MonsterAction_NextDown(u8 cur, u8 showSynchro, u8 showXyz)
{
  u8 next = sMonsterActionNextDown[cur];

  if (!MonsterAction_IsVisible(next, showSynchro, showXyz))
    return cur;
  return next;
}

static u8 MonsterAction_NextLeft(u8 cur, u8 showSynchro, u8 showXyz)
{
  u8 next = sMonsterActionNextLeft[cur];

  if (next == MONSTER_ACTION_SYNCHRO && !showSynchro)
    return MONSTER_ACTION_DEFEND;
  if (!MonsterAction_IsVisible(next, showSynchro, showXyz))
    return MONSTER_ACTION_DEFEND;
  return next;
}

static u8 MonsterAction_NextRight(u8 cur, u8 showSynchro, u8 showXyz)
{
  u8 next = sMonsterActionNextRight[cur];

  if (next == MONSTER_ACTION_XYZ && !showXyz)
    return MONSTER_ACTION_EFFECT;
  if (!MonsterAction_IsVisible(next, showSynchro, showXyz))
    return cur;
  return next;
}

static void MonsterActionMenu_Highlight(u8 selected, u8 showSynchro, u8 showXyz)
{
  u8 i;

  for (i = 0; i < MONSTER_ACTION_COUNT; i++) {
    u16 base = sMonsterActionHighlight[i] / 2;

    if (!MonsterAction_IsVisible(i, showSynchro, showXyz)) {
      gVr.b[base] = 0x7000;
      gVr.b[base + 1] = 0x7000;
      gVr.b[base + 32] = 0x7000;
      gVr.b[base + 33] = 0x7000;
      continue;
    }

    if (selected != i) {
      gVr.b[base] = 0x7000;
      gVr.b[base + 1] = 0x7000;
      gVr.b[base + 32] = 0x7000;
      gVr.b[base + 33] = 0x7000;
    } else {
      gVr.b[base] = 0x703D;
      gVr.b[base + 1] = 0x703E;
      gVr.b[base + 32] = 0x703F;
      gVr.b[base + 33] = 0x7040;
    }
  }
}

static void MonsterActionMenu_InitGfx(u8 selected, u8 showSynchro, u8 showXyz)
{
  unsigned char i;
  unsigned short r7;
  u8 expand = showSynchro || showXyz;

  for (i = 0; i < 18; i++)
    CpuCopy16(g80F1880[i], gVr.a + 0xE800 + i * 64, 64);
  CpuCopy16(g80F30E0, gVr.a + 0x87A0, 128);
  r7 = sub_08007FEC(4, 3, 0xE800) & 0xFF00;

  for (i = 0; i < 8; i++) {
    sub_800800C(i + 4, 3, 0xE800, (g8DF811C[i] + 65) | r7);
    sub_800800C(i + 4, 4, 0xE800, (g8DF811C[i] + 67) | r7);
    sub_800800C(i + 4, 5, 0xE800, (g8DF811C[i] + 81) | r7);
    sub_800800C(i + 4, 6, 0xE800, (g8DF811C[i] + 83) | r7);
  }
  for (i = 0; i < 12; i++) {
    sub_800800C(i + 14, 3, 0xE800, (g8DF811C[i] + 97) | r7);
    sub_800800C(i + 14, 4, 0xE800, (g8DF811C[i] + 99) | r7);
    sub_800800C(i + 14, 5, 0xE800, (g8DF811C[i] + 121) | r7);
    sub_800800C(i + 14, 6, 0xE800, (g8DF811C[i] + 123) | r7);
  }

  if (expand) {
    CopyStringTilesToVRAMBuffer(gVr.a + 0x8820, sText_AttackDefendTributeEffectSynchroXyz, 0x901);
    REG_WIN1V = 0x144C;

    if (showSynchro) {
      for (i = 0; i < 8; i++) {
        sub_800800C(i + 4, 7, 0xE800, (g8DF811C[i] + MONSTER_ACTION_TILE_SYNCHRO_TOP) | r7);
        sub_800800C(i + 4, 8, 0xE800, (g8DF811C[i] + MONSTER_ACTION_TILE_SYNCHRO_BOT) | r7);
      }
    }
    if (showXyz) {
      for (i = 0; i < 8; i++) {
        sub_800800C(i + 14, 7, 0xE800, (g8DF811C[i] + MONSTER_ACTION_TILE_XYZ_TOP) | r7);
        sub_800800C(i + 14, 8, 0xE800, (g8DF811C[i] + MONSTER_ACTION_TILE_XYZ_BOT) | r7);
      }
    }
  } else {
    CopyStringTilesToVRAMBuffer(gVr.a + 0x8820, sText_AttackDefendTributeEffect, 0x901);
    REG_WIN1V = 0x143C;
  }

  MonsterActionMenu_Highlight(selected, showSynchro, showXyz);
  WaitForVBlank();
  REG_WIN1H = 0xCD4;
  *(vu8 *)(0x4000049) = 54;
  sub_8041014();
  REG_BLDY = 10;
  REG_WINOUT = 31;
  REG_DISPCNT = DISPCNT_BG1_ON | DISPCNT_BG2_ON | DISPCNT_OBJ_ON | DISPCNT_WIN0_ON | DISPCNT_WIN1_ON;
}

void sub_80574A8(unsigned char arg0, unsigned char arg1);
unsigned HandlePlayerMonsterAction(void);

LYN_REPLACE_CHECK(HandlePlayerMonsterAction);
unsigned HandlePlayerMonsterAction__Replacement(void)
{
  enum MonsterAction cursorState = MONSTER_ACTION_ATTACK;
  u8 showSynchro = SynchroOptionVisible();
  u8 showXyz = XyzOptionVisible();

  MonsterActionMenu_InitGfx(0, showSynchro, showXyz);
  while (1) {
    while (1) {
      if (gRepeatedOrNewButtons & DPAD_UP) {
        PlayMusic(SFX_MOVE_CURSOR);
        cursorState = MonsterAction_NextUp(cursorState);
      } else if (gRepeatedOrNewButtons & DPAD_DOWN) {
        PlayMusic(SFX_MOVE_CURSOR);
        cursorState = MonsterAction_NextDown(cursorState, showSynchro, showXyz);
      } else if (gRepeatedOrNewButtons & DPAD_LEFT) {
        PlayMusic(SFX_MOVE_CURSOR);
        cursorState = MonsterAction_NextLeft(cursorState, showSynchro, showXyz);
      } else if (gRepeatedOrNewButtons & DPAD_RIGHT) {
        PlayMusic(SFX_MOVE_CURSOR);
        cursorState = MonsterAction_NextRight(cursorState, showSynchro, showXyz);
      } else {
        break;
      }
      MonsterActionMenu_Highlight(cursorState, showSynchro, showXyz);
      WaitForVBlank();
      sub_8041014();
    }

    if (gNewButtons & A_BUTTON) {
      switch (cursorState) {
      case MONSTER_ACTION_ATTACK:
        return 1;
      case MONSTER_ACTION_DEFEND:
        return 2;
      case MONSTER_ACTION_TRIBUTE:
        return 3;
      case MONSTER_ACTION_EFFECT:
        return 4;
      case MONSTER_ACTION_SYNCHRO:
        if (!showSynchro) {
          PlayMusic(SFX_FORBIDDEN);
          break;
        }
        gTurnZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 0;
        return 6;
      case MONSTER_ACTION_XYZ:
        if (!showXyz) {
          PlayMusic(SFX_FORBIDDEN);
          break;
        }
        gTurnZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 0;
        return 7;
      }
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_CANCEL);
      return 5;
    }

    /* Attack/Defend preview; Synchro/XYZ clear Defend so materials still count. */
    if (cursorState == MONSTER_ACTION_ATTACK || cursorState == MONSTER_ACTION_SYNCHRO
        || cursorState == MONSTER_ACTION_XYZ) {
      gTurnZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 0;
      sub_80574A8(gDuelCursor.currentX, gDuelCursor.currentY);
      SetVBlankCallback(LoadOam);
    } else if (cursorState == MONSTER_ACTION_DEFEND) {
      gTurnZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 1;
      sub_80574A8(gDuelCursor.currentX, gDuelCursor.currentY);
      SetVBlankCallback(LoadOam);
    }
    WaitForVBlank();
  }
}
