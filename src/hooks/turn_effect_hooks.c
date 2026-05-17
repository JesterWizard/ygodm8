#include "global.h"
#include "configs/runtime.h"

#define gShieldAndSwordActive (*(u8 *)0x02022EBC)
extern void (*g8E0C940[])(void);
extern unsigned char (*g8E0CA80[])(void);

void TryActivatingTurnEffects(void);
void sub_802ACC0(void);
void sub_802ADF4(void);
void sub_80408BC(void);
void sub_802ADA4(void);
void ResetTempStagesForAllCards(void);

static void TryActivatingTurnEffect__Hook(void) {
  ResetCardEffectTextData();
  SetCardEffectTextType(9);
  SetCardInfo(gActiveEffect.cardId);
  g8E0C940[gCardInfo.unk1E]();
}

static unsigned char ShouldActivateTurnEffect__Hook(void) {
  SetCardInfo(gActiveEffect.cardId);
  return g8E0CA80[gCardInfo.unk1E]();
}

static void ScanTurnEffectRow__Hook(struct DuelCard **row, u8 turnRow, u8 animateCursor, u8 checkFinal) {
  u8 i;

  gActiveEffect.turnRow = turnRow;
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    gActiveEffect.col = i;
    gActiveEffect.cardId = row[i]->id;
    if (animateCursor == TRUE && !gHideEffectText)
      sub_802ACC0();
    if (ShouldActivateTurnEffect__Hook() == 1) {
      sub_8034FEC(375);
      TryActivatingTurnEffect__Hook();
      if (checkFinal == TRUE)
        CheckWinConditionFINAL();
      if (!gHideEffectText)
        PlayMusic(MUSIC_375);
    }
    if (IsDuelOver() == 1) {
      sub_8034FEC(375);
      return;
    }
  }
}

static void ScanTurnEffectGraveyard__Hook(u8 turnRow, u8 duelist, u8 animateCursor) {
  gActiveEffect.turnRow = turnRow;
  gActiveEffect.col = 0;
  gActiveEffect.cardId = gTurnDuelistBattleState[duelist]->graveyard;
  if (animateCursor == TRUE && !gHideEffectText)
    sub_802ADF4();
  if (ShouldActivateTurnEffect__Hook() == 1) {
    sub_8034FEC(375);
    TryActivatingTurnEffect__Hook();
    if (!gHideEffectText)
      PlayMusic(MUSIC_375);
  }
}

static void CheckBoardForTurnEffects__Hook(u8 animateScanner) {
  ScanTurnEffectRow__Hook(gTurnHands[ACTIVE_DUELIST], 4, animateScanner, FALSE);
  if (IsDuelOver() == 1)
    return;

  ScanTurnEffectRow__Hook(gTurnHands[INACTIVE_DUELIST], 5, FALSE, FALSE);
  if (IsDuelOver() == 1)
    return;

  if (!gHideEffectText)
    PlayMusic(MUSIC_375);

  ScanTurnEffectGraveyard__Hook(6, ACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == 1) {
    sub_8034FEC(375);
    return;
  }

  ScanTurnEffectGraveyard__Hook(7, INACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == 1) {
    sub_8034FEC(375);
    return;
  }

  ScanTurnEffectRow__Hook(gTurnZones[2], 2, animateScanner, FALSE);
  if (IsDuelOver() == 1)
    return;

  ScanTurnEffectRow__Hook(gTurnZones[1], 1, animateScanner, FALSE);
  if (IsDuelOver() == 1)
    return;

  ScanTurnEffectRow__Hook(gTurnZones[3], 3, animateScanner, TRUE);
  if (IsDuelOver() == 1)
    return;

  ScanTurnEffectRow__Hook(gTurnZones[0], 0, animateScanner, FALSE);
  sub_8034FEC(375);
}

LYN_REPLACE_CHECK(TryActivatingTurnEffects);
void TryActivatingTurnEffects__Replacement(void) {
  gActiveEffect.turn = WhoseTurn();
  gShieldAndSwordActive = FALSE;
  if (!gHideEffectText && !gRuntimeConfig.turn_off_visual_scanner) {
    sub_80408BC();
    sub_802ADA4();
  }
  ResetTempStagesForAllCards();
  CheckBoardForTurnEffects__Hook(!gRuntimeConfig.turn_off_visual_scanner);
}
