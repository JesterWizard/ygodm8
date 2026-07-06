#include "global.h"
#include "configs/runtime.h"
#include "delayed_effects.h"
#include "cost_down.h"
#include "riryoku.h"
#include "thousand_energy.h"
#include "triangle_power.h"
#include "limiter_removal.h"
#include "imperial_order.h"
#include "royal_decree.h"
#include "burning_land.h"
#include "dark_snake_syndrome.h"
#include "duel_helpers.h"
#include "sasuke_samurai_2.h"
#include "bottomless_shifting_sand.h"
#include "dark_dust_spirit.h"
#include "nightmare_wheel.h"
#include "mirror_wall.h"
#include "ectoplasmer.h"
#include "future_fusion.h"
#include "power_bond.h"
#include "the_big_saturn.h"
#include "the_grand_jupiter.h"
#include "the_supremacy_sun.h"
#include "yubel.h"

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
void CourtOfJustice_ResetTurnState(void);
void ResetExecutorMakyuraTurnState(void);
void AgeUltimateOfferingSetFlags(void);
unsigned char ShouldActivateUltimateOfferingTurnEffect(void);
void ActivateUltimateOfferingTurnEffect(void);
void AgeFairyBoxSetFlags(void);
unsigned char ShouldActivateFairyBoxUpkeep(void);
void ActivateFairyBoxUpkeep(void);
void AgeMirrorWallSetFlags(void);
unsigned char ShouldActivateMirrorWallUpkeep(void);
void ActivateMirrorWallUpkeep(void);
void AgeWaveMotionCannonTurns(void);
void AgeFinalCountdownTurns(void);
unsigned char ShouldActivateBowganianTurnEffect(void);
void ActivateBowganianTurnEffect(void);
unsigned char ShouldActivateCureMermaidTurnEffect(void);
void ActivateCureMermaidTurnEffect(void);
unsigned char ShouldActivateSolarFlareDragonTurnEffect(void);
void ActivateSolarFlareDragonTurnEffect(void);
unsigned char ShouldActivateEbonMagicianCurranTurnEffect(void);
void ActivateEbonMagicianCurranTurnEffect(void);
unsigned char ShouldActivateDancingFairyTurnEffect(void);
void ActivateDancingFairyTurnEffect(void);
unsigned char ShouldActivateSpiritOfTheBreezeTurnEffect(void);
void ActivateSpiritOfTheBreezeTurnEffect(void);
void ActivateDarklordMarieTurnEffect(void);
unsigned char ShouldActivateUnstoppableExodiaIncarnateTurnEffect(void);
void ActivateUnstoppableExodiaIncarnateTurnEffect(void);
unsigned char ShouldActivateBlueEyesChaosDragonTurnEffect(void);
void ActivateBlueEyesChaosDragonTurnEffect(void);
void ResolveYubelEndPhaseEffectsAtTurnEnd(void);

void TryActivatingTurnEffects(void);
void sub_802ACC0(void);
void sub_802ADF4(void);
void sub_80408BC(void);
void sub_802ADA4(void);
void ResetTempStagesForAllCards(void);
void DestroyKarateManAtEndOfTurn(void);
void DestroyThousandEnergyMonstersAtEndOfTurn(void);
void DestroyTrianglePowerMonstersAtEndOfTurn(void);
void DestroyLimiterRemovalMonstersAtEndOfTurn(void);

typedef unsigned char (*TurnEffectRowMatch)(void);
typedef unsigned char (*TurnEffectCondition)(void);
typedef void (*TurnEffectHandler)(void);

typedef struct {
  u16 cardId;
  TurnEffectRowMatch matchesRow;
  TurnEffectCondition shouldActivate;
  TurnEffectHandler activate;
} TurnEffectOverride;

static unsigned char MatchGraveyardRows(void)
{
  return gActiveEffect.turnRow == 6 || gActiveEffect.turnRow == 7;
}

static unsigned char MatchDeckDestructionVirusRow(void)
{
  return gActiveEffect.turnRow == 0;
}

static unsigned char MatchActiveDuelistMonsterRow(void)
{
  return gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW;
}

static unsigned char MatchActiveDuelistGraveyard(void)
{
  return gActiveEffect.turnRow == 6;
}

static unsigned char MatchActiveDuelistBackrow(void)
{
  return gActiveEffect.turnRow == ACTIVE_DUELIST_BACKROW;
}

static unsigned char NeverActivateTurnEffect(void)
{
  return FALSE;
}

static unsigned char MatchAnyMonsterRow(void)
{
  return gActiveEffect.turnRow == OPPONENT_MONSTER_ROW
      || gActiveEffect.turnRow == PLAYER_MONSTER_ROW;
}

static const TurnEffectOverride sTurnEffectOverrides[] __attribute__((section(".text"))) = {
  { GIANT_GERM, MatchGraveyardRows, NULL, ActivateGiantGermEffect },
  { NIMBLE_MOMONGA, MatchGraveyardRows, NULL, ActivateNimbleMomongaEffect },
  { SKULL_MARK_LADY_BUG, MatchGraveyardRows, NULL, ActivateSkullMarkLadyBugEffect },
  { SINISTER_SERPENT, MatchGraveyardRows, ShouldActivateSinisterSerpentEffect, ActivateSinisterSerpentEffect },
  { MYSTERIOUS_PUPPETEER, MatchActiveDuelistMonsterRow, ShouldActivateMysteriousPuppeteerTurnEffect, ActivateMysteriousPuppeteerTurnEffect },
  { WHITE_MAGICIAN_PIKERU, MatchActiveDuelistMonsterRow, ShouldActivateWhiteMagicianPikeruTurnEffect, ActivateWhiteMagicianPikeruTurnEffect },
  { THE_UNHAPPY_MAIDEN, MatchGraveyardRows, NeverActivateTurnEffect, NULL },
  { DECK_DESTRUCTION_VIRUS, MatchDeckDestructionVirusRow, NULL, ActivateDeckDestructionVirusEffect },
  { ULTIMATE_OFFERING, MatchActiveDuelistBackrow, ShouldActivateUltimateOfferingTurnEffect, ActivateUltimateOfferingTurnEffect },
  { FAIRY_BOX, MatchActiveDuelistBackrow, ShouldActivateFairyBoxUpkeep, ActivateFairyBoxUpkeep },
  { MIRROR_WALL, MatchActiveDuelistBackrow, ShouldActivateMirrorWallUpkeep, ActivateMirrorWallUpkeep },
  { IMPERIAL_ORDER, MatchActiveDuelistBackrow, ShouldActivateImperialOrderUpkeep, ActivateImperialOrderUpkeep },
  { BOWGANIAN, MatchActiveDuelistMonsterRow, ShouldActivateBowganianTurnEffect, ActivateBowganianTurnEffect },
  { CURE_MERMAID, MatchActiveDuelistMonsterRow, ShouldActivateCureMermaidTurnEffect, ActivateCureMermaidTurnEffect },
  { SOLAR_FLARE_DRAGON, MatchActiveDuelistMonsterRow, ShouldActivateSolarFlareDragonTurnEffect, ActivateSolarFlareDragonTurnEffect },
  { EBON_MAGICIAN_CURRAN, MatchActiveDuelistMonsterRow, ShouldActivateEbonMagicianCurranTurnEffect, ActivateEbonMagicianCurranTurnEffect },
  { DANCING_FAIRY, MatchActiveDuelistMonsterRow, ShouldActivateDancingFairyTurnEffect, ActivateDancingFairyTurnEffect },
  { SPIRIT_OF_THE_BREEZE, MatchActiveDuelistMonsterRow, ShouldActivateSpiritOfTheBreezeTurnEffect, ActivateSpiritOfTheBreezeTurnEffect },
  { DARK_DUST_SPIRIT, MatchActiveDuelistMonsterRow, ShouldActivateDarkDustSpiritTurnEffect, ActivateDarkDustSpiritTurnEffect },
  { DARKLORD_MARIE, MatchActiveDuelistGraveyard, NULL, ActivateDarklordMarieTurnEffect },
  { THE_UNSTOPPABLE_EXODIA_INCARNATE, MatchActiveDuelistMonsterRow, ShouldActivateUnstoppableExodiaIncarnateTurnEffect, ActivateUnstoppableExodiaIncarnateTurnEffect },
  { BLUE_EYES_CHAOS_DRAGON, MatchActiveDuelistMonsterRow, ShouldActivateBlueEyesChaosDragonTurnEffect, ActivateBlueEyesChaosDragonTurnEffect },
  { THE_GRAND_JUPITER, MatchAnyMonsterRow, ShouldActivateTheGrandJupiterTurnEffect, ActivateTheGrandJupiterTurnEffect },
};

static const TurnEffectOverride *GetTurnEffectOverride(u16 cardId)
{
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sTurnEffectOverrides); i++) {
    if (sTurnEffectOverrides[i].cardId == cardId)
      return &sTurnEffectOverrides[i];
  }

  return NULL;
}

static unsigned char ShouldRunTurnEffectOverride(const TurnEffectOverride *override)
{
  if (override->matchesRow != NULL && override->matchesRow() == FALSE)
    return FALSE;
  if (override->shouldActivate != NULL)
    return override->shouldActivate();
  return TRUE;
}

static void TryActivatingTurnEffect__Hook(void) {
  const TurnEffectOverride *override;

  ResetCardEffectTextData();
  SetCardEffectTextType(9);
  override = GetTurnEffectOverride(gActiveEffect.cardId);
  if (override != NULL) {
    if (override->matchesRow == NULL || override->matchesRow() == TRUE) {
      if (override->activate != NULL)
        override->activate();
      return;
    }
  }
  SetCardInfo(gActiveEffect.cardId);
  g8E0C940[gCardInfo.unk1E]();
}

static unsigned char ShouldActivateTurnEffect__Hook(void) {
  const TurnEffectOverride *override;

  override = GetTurnEffectOverride(gActiveEffect.cardId);
  if (override != NULL) {
    if (ShouldRunTurnEffectOverride(override))
      return TRUE;
    if (override->matchesRow != NULL && override->matchesRow() == FALSE)
      goto vanilla;
    return FALSE;
  }
  if (Duel_IsCardActivationBlocked(gActiveEffect.cardId))
    return FALSE;
vanilla:
  SetCardInfo(gActiveEffect.cardId);
  return g8E0CA80[gCardInfo.unk1E]();
}

static void ScanTurnEffectRow__Hook(struct DuelCard **row, u8 turnRow, u8 animateCursor, u8 checkFinal) {
  u8 i;

  gActiveEffect.turnRow = turnRow;
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    /* ponytail: AI sim must not read face-down opponent cards — prevents
       logic loops from spurious effect activation on unknown cards. */
    if (gHideEffectText && !row[i]->isFaceUp && (turnRow == 0 || turnRow == 1))
      continue;
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
  ResetTheGrandJupiterEndPhaseFlags();
  Yubel_ClearTurnState();
  ClearCostDown();
  ResetUltimateOfferingTurnState();
  CourtOfJustice_ResetTurnState();
  ResetExecutorMakyuraTurnState();
  AgeUltimateOfferingSetFlags();
  AgeFairyBoxSetFlags();
  AgeMirrorWallSetFlags();
  AgeBottomlessShiftingSandSetFlags();
  AgeWaveMotionCannonTurns();
  AgeFinalCountdownTurns();
  TryApplyBurningLandStandbyDamage();
  TryApplyDarkSnakeSyndromeStandbyDamage();
  TryApplyNightmareWheelStandbyDamage();
  TryApplyFutureFusionStandby();
  TryBottomlessShiftingSandTurnStart();
  if (IsDuelOver() == 1)
    return;
  if (!gHideEffectText && !gRuntimeConfig.turn_off_visual_scanner) {
    sub_80408BC();
    sub_802ADA4();
  }
  DestroyKarateManAtEndOfTurn();
  ClearTheBigSaturnAtkBoostAtEndOfTurn();
  DestroyThousandEnergyMonstersAtEndOfTurn();
  DestroyTrianglePowerMonstersAtEndOfTurn();
  DestroyLimiterRemovalMonstersAtEndOfTurn();
  SasukeSamurai2_ClearInactiveBackrowTrapBlock();
  if (IsDuelOver() == 1)
    return;
  TryApplyEctoplasmerEndPhaseEffect();
  if (IsDuelOver() == 1)
    return;
  TryApplyPowerBondEndPhaseBurn();
  if (IsDuelOver() == 1)
    return;
  ResetTempStagesForAllCards();
  ClearAllRiryokuAtkDeltas();
  TheSupremacySun_AgeStandbyFlags();
  TheSupremacySun_TryResolveStandbyRevive();
  if (IsDuelOver() == 1)
    return;
  CheckBoardForTurnEffects__Hook(!gRuntimeConfig.turn_off_visual_scanner);
}