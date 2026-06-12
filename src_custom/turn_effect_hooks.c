#include "global.h"
#include "configs/runtime.h"
#include "delayed_effects.h"
#include "cost_down.h"
#include "riryoku.h"

#define gShieldAndSwordActive (*(u8 *)0x02022EBC)

extern void (*g8E0C940[])(void);
extern unsigned char (*g8E0CA80[])(void);
void ActivateGiantGermEffect(void);
void ActivateNimbleMomongaEffect(void);
void ActivateSkullMarkLadyBugEffect(void);
u8 ShouldActivateSinisterSerpentEffect(void);
void ActivateSinisterSerpentEffect(void);
unsigned char ShouldActivateMysteriousPuppeteerTurnEffect(void);
void ActivateMysteriousPuppeteerTurnEffect(void);
unsigned char ShouldActivateWhiteMagicianPikeruTurnEffect(void);
void ActivateWhiteMagicianPikeruTurnEffect(void);
void ActivateDeckDestructionVirusEffect(void);
void ResetUltimateOfferingTurnState(void);
void AgeUltimateOfferingSetFlags(void);
unsigned char ShouldActivateUltimateOfferingTurnEffect(void);
void ActivateUltimateOfferingTurnEffect(void);
void AgeFairyBoxSetFlags(void);
unsigned char ShouldActivateFairyBoxTurnEffect(void);
void ActivateFairyBoxTurnEffect(void);
unsigned char ShouldActivateFairyBoxUpkeep(void);
void ActivateFairyBoxUpkeep(void);
void AgeWaveMotionCannonTurns(void);
unsigned char ShouldActivateBowganianTurnEffect(void);
void ActivateBowganianTurnEffect(void);
unsigned char ShouldActivateCureMermaidTurnEffect(void);
void ActivateCureMermaidTurnEffect(void);
unsigned char ShouldActivateSolarFlareDragonTurnEffect(void);
void ActivateSolarFlareDragonTurnEffect(void);
unsigned char ShouldActivateEbonMagicianCurranTurnEffect(void);
void ActivateEbonMagicianCurranTurnEffect(void);

void TryActivatingTurnEffects(void);
void sub_802ACC0(void);
void sub_802ADF4(void);
void sub_80408BC(void);
void sub_802ADA4(void);
void ResetTempStagesForAllCards(void);
void DestroyKarateManAtEndOfTurn(void);

static void TryActivatingTurnEffect__Hook(void) {
  ResetCardEffectTextData();
  SetCardEffectTextType(9);
  if (gActiveEffect.cardId == GIANT_GERM && (gActiveEffect.turnRow == 6 || gActiveEffect.turnRow == 7)) {
    ActivateGiantGermEffect();
    return;
  }
  if (gActiveEffect.cardId == NIMBLE_MOMONGA && (gActiveEffect.turnRow == 6 || gActiveEffect.turnRow == 7)) {
    ActivateNimbleMomongaEffect();
    return;
  }
  if (gActiveEffect.cardId == SKULL_MARK_LADY_BUG && (gActiveEffect.turnRow == 6 || gActiveEffect.turnRow == 7)) {
    ActivateSkullMarkLadyBugEffect();
    return;
  }
  if (gActiveEffect.cardId == SINISTER_SERPENT && (gActiveEffect.turnRow == 6 || gActiveEffect.turnRow == 7)) {
    ActivateSinisterSerpentEffect();
    return;
  }
  if (gActiveEffect.cardId == MYSTERIOUS_PUPPETEER && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW) {
    ActivateMysteriousPuppeteerTurnEffect();
    return;
  }
  if (gActiveEffect.cardId == WHITE_MAGICIAN_PIKERU && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW) {
    ActivateWhiteMagicianPikeruTurnEffect();
    return;
  }
  if (gActiveEffect.cardId == THE_UNHAPPY_MAIDEN && (gActiveEffect.turnRow == 6 || gActiveEffect.turnRow == 7))
    return;
  if (gActiveEffect.cardId == DECK_DESTRUCTION_VIRUS && gActiveEffect.turnRow == 0) {
    ActivateDeckDestructionVirusEffect();
    return;
  }
  if (gActiveEffect.cardId == ULTIMATE_OFFERING && gActiveEffect.turnRow == ACTIVE_DUELIST_BACKROW) {
    ActivateUltimateOfferingTurnEffect();
    return;
  }
  if (gActiveEffect.cardId == FAIRY_BOX && gActiveEffect.turnRow == ACTIVE_DUELIST_BACKROW) {
    if (ShouldActivateFairyBoxUpkeep())
      ActivateFairyBoxUpkeep();
    return;
  }
  if (gActiveEffect.cardId == BOWGANIAN && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW) {
    ActivateBowganianTurnEffect();
    return;
  }
  if (gActiveEffect.cardId == CURE_MERMAID && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW) {
    ActivateCureMermaidTurnEffect();
    return;
  }
  if (gActiveEffect.cardId == SOLAR_FLARE_DRAGON && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW) {
    ActivateSolarFlareDragonTurnEffect();
    return;
  }
  if (gActiveEffect.cardId == EBON_MAGICIAN_CURRAN && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW) {
    ActivateEbonMagicianCurranTurnEffect();
    return;
  }
  SetCardInfo(gActiveEffect.cardId);
  g8E0C940[gCardInfo.unk1E]();
}

static unsigned char ShouldActivateTurnEffect__Hook(void) {
  if (gActiveEffect.cardId == GIANT_GERM && (gActiveEffect.turnRow == 6 || gActiveEffect.turnRow == 7))
    return TRUE;
  if (gActiveEffect.cardId == NIMBLE_MOMONGA && (gActiveEffect.turnRow == 6 || gActiveEffect.turnRow == 7))
    return TRUE;
  if (gActiveEffect.cardId == SKULL_MARK_LADY_BUG && (gActiveEffect.turnRow == 6 || gActiveEffect.turnRow == 7))
    return TRUE;
  if (gActiveEffect.cardId == SINISTER_SERPENT && (gActiveEffect.turnRow == 6 || gActiveEffect.turnRow == 7))
    return ShouldActivateSinisterSerpentEffect();
  if (gActiveEffect.cardId == MYSTERIOUS_PUPPETEER && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ShouldActivateMysteriousPuppeteerTurnEffect();
  if (gActiveEffect.cardId == WHITE_MAGICIAN_PIKERU && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ShouldActivateWhiteMagicianPikeruTurnEffect();
  if (gActiveEffect.cardId == THE_UNHAPPY_MAIDEN && (gActiveEffect.turnRow == 6 || gActiveEffect.turnRow == 7))
    return FALSE;
  if (gActiveEffect.cardId == DECK_DESTRUCTION_VIRUS && gActiveEffect.turnRow == 0)
    return TRUE;
  if (gActiveEffect.cardId == ULTIMATE_OFFERING && gActiveEffect.turnRow == ACTIVE_DUELIST_BACKROW)
    return ShouldActivateUltimateOfferingTurnEffect();
  if (gActiveEffect.cardId == FAIRY_BOX && gActiveEffect.turnRow == ACTIVE_DUELIST_BACKROW)
    return ShouldActivateFairyBoxUpkeep();
  if (gActiveEffect.cardId == BOWGANIAN && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ShouldActivateBowganianTurnEffect();
  if (gActiveEffect.cardId == CURE_MERMAID && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ShouldActivateCureMermaidTurnEffect();
  if (gActiveEffect.cardId == SOLAR_FLARE_DRAGON && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ShouldActivateSolarFlareDragonTurnEffect();
  if (gActiveEffect.cardId == EBON_MAGICIAN_CURRAN && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ShouldActivateEbonMagicianCurranTurnEffect();
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
  ClearCostDown();
  ResetUltimateOfferingTurnState();
  AgeUltimateOfferingSetFlags();
  AgeFairyBoxSetFlags();
  AgeWaveMotionCannonTurns();
  if (!gHideEffectText && !gRuntimeConfig.turn_off_visual_scanner) {
    sub_80408BC();
    sub_802ADA4();
  }
  DestroyKarateManAtEndOfTurn();
  if (IsDuelOver() == 1)
    return;
  ResetTempStagesForAllCards();
  ClearAllRiryokuAtkDeltas();
  CheckBoardForTurnEffects__Hook(!gRuntimeConfig.turn_off_visual_scanner);
}
