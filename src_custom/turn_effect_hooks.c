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
#include "continuous_trap_turn_start.h"
#include "dark_dust_spirit.h"
#include "needle_wall.h"
#include "tour_of_doom.h"
#include "venom_swamp.h"
#include "glorious_illusion.h"
#include "tyrant_wing.h"
#include "arcana_force_ex_the_dark_ruler.h"
#include "aurkus_lightsworn_druid.h"
#include "ehren_lightsworn_monk.h"
#include "morphtronic_lantron.h"
#include "shire_lightsworn_spirit.h"
#include "jain_lightsworn_paladin.h"
#include "lumina_lightsworn_summoner.h"
#include "jenis_lightsworn_mender.h"
#include "lyla_lightsworn_sorceress.h"
#include "garonith_lightsworn_dragon.h"
#include "raiden_hand_of_the_lightsworn.h"
#include "michael_the_arch_lightsworn.h"
#include "silent_magician_lv4.h"
#include "cannot_attack_this_turn.h"
#include "morphtronic_magnen_bar.h"
#include "destiny_hero_doom_lord.h"
#include "bazoo_the_soul_eater.h"
#include "helios_duo_megistus.h"
#include "helios_trice_megistus.h"
#include "aroma_jar.h"
#include "contact_fusion_end_phase.h"
#include "destiny_hero_double_dude.h"
#include "weapon_change.h"
#include "nightmare_wheel.h"
#include "mirror_wall.h"
#include "cyber_barrier_dragon.h"
#include "ectoplasmer.h"
#include "future_fusion.h"
#include "cybernetic_zone.h"
#include "different_dimension_capsule.h"
#include "power_bond.h"
#include "the_big_saturn.h"
#include "the_grand_jupiter.h"
#include "the_supremacy_sun.h"
#include "light_end_dragon.h"
#include "yubel.h"
#include "effect_system.h"
#include "effect_events.h"
#include "aroma_garden.h"
#include "big_evolution_pill.h"
#include "flavian_colosseum_of_the_gladiator_beasts.h"
#include "fusion_destiny.h"
#include "hysteric_sign.h"
#include "instant_fusion.h"
#include "over_destiny.h"
#include "the_gaze_of_timaeus.h"
#include "vipers_rebirth.h"
#include "red_dragon_archfiend.h"
#include "destiny_hero_defender.h"
#include "armed_dragon_lv5.h"
#include "armed_dragon_lv7.h"
#include "horus_end_phase.h"
#include "gladiator_beast_battled.h"
#include "gandora_x.h"
#include "judgment_the_dragon_of_heaven.h"
#include "reptilianne_naga.h"
#include "majestic_mech_goryu.h"
#include "twilightsworn_end_phase.h"
#include "treeborn_frog.h"
#include "evil_dragon_ananta.h"
#include "azure_eyes_silver_dragon.h"
#include "evil_hero_infernal_prodigy.h"
#include "evil_hero_infernal_sniper.h"
#include "silent_swordsman.h"
#include "destiny_hero_captain_tenacious.h"
#include "diviner_of_the_herald.h"
#include "harpie_perfumer.h"
#include "rescue_end_phase.h"
#include "destiny_hero_destroy_dogma.h"
#include "destiny_hero_dogma_standby.h"
#include "destiny_hero_dusktopia.h"
#include "destiny_hero_drawhand.h"
#include "destiny_hero_decider.h"
#include "elemental_hero_glow_neos.h"
#include "spell_effects.h"

void TryApplyElementalHeroNebulaNeosEndPhase(void);
void TryApplyElementalHeroCosmoNeosEndPhase(void);
void TryApplyElementalHeroChaosNeosEndPhase(void);

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
u8 ShouldActivateDestinyHeroFearMongerTurnEffect(void);
void ActivateDestinyHeroFearMongerTurnEffect(void);
u8 ShouldActivateArmedDragonLv3TurnEffect(void);
void ActivateArmedDragonLv3TurnEffect(void);
u8 ShouldActivateTheWhiteStoneOfAncientsTurnEffect(void);
void ActivateTheWhiteStoneOfAncientsTurnEffect(void);
void TheWhiteStoneOfAncients_AgeSentFlags(void);
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

static void DestroyInstantFusionMonstersAtEndPhase(void)
{
  u8 fixedRow;
  u8 col;

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_MONSTER_ROW; fixedRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[fixedRow][col];

      if (InstantFusion_ShouldDestroyAtEndPhase(zone))
        Duel_DestroyZone(zone, Duel_FixedDuelistForMonsterRow(fixedRow), FALSE);
    }
  }
}

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
  { DESTINY_HERO_FEAR_MONGER, MatchActiveDuelistGraveyard, ShouldActivateDestinyHeroFearMongerTurnEffect, ActivateDestinyHeroFearMongerTurnEffect },
  { DESTINY_HERO_DOUBLE_DUDE, MatchActiveDuelistGraveyard, ShouldActivateDestinyHeroDoubleDudeTurnEffect, ActivateDestinyHeroDoubleDudeTurnEffect },
  { ARMED_DRAGON_LV3, MatchActiveDuelistMonsterRow, ShouldActivateArmedDragonLv3TurnEffect, ActivateArmedDragonLv3TurnEffect },
  { TREEBORN_FROG, MatchActiveDuelistGraveyard, ShouldActivateTreebornFrogTurnEffect, ActivateTreebornFrogTurnEffect },
  { THE_WHITE_STONE_OF_ANCIENTS, MatchActiveDuelistGraveyard, ShouldActivateTheWhiteStoneOfAncientsTurnEffect, ActivateTheWhiteStoneOfAncientsTurnEffect },
  { THE_UNSTOPPABLE_EXODIA_INCARNATE, MatchActiveDuelistMonsterRow, ShouldActivateUnstoppableExodiaIncarnateTurnEffect, ActivateUnstoppableExodiaIncarnateTurnEffect },
  { BLUE_EYES_CHAOS_DRAGON, MatchActiveDuelistMonsterRow, ShouldActivateBlueEyesChaosDragonTurnEffect, ActivateBlueEyesChaosDragonTurnEffect },
  { EVIL_HERO_INFERNAL_SNIPER, MatchActiveDuelistMonsterRow, ShouldActivateEvilHeroInfernalSniperTurnEffect, ActivateEvilHeroInfernalSniperTurnEffect },
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

  if (EffectDispatch_TryActivate(gActiveEffect.cardId, EFFECT_KIND_TURN)
      == EFFECT_DISPATCH_HANDLED)
    return;

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
  u8 should;

  should = EffectDispatch_QueryShouldActivate(gActiveEffect.cardId, EFFECT_KIND_TURN);
  if (should == EFFECT_SHOULD_YES)
    return TRUE;
  if (should == EFFECT_SHOULD_NO)
    return FALSE;

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
  u8 endedFixedDuelist;
  u8 standbyFixedDuelist;
  u8 coinHeads;

  gActiveEffect.turn = WhoseTurn();
  gShieldAndSwordActive = FALSE;
  /* Previous turn's End Phase just finished; WhoseTurn is the new turn player. */
  endedFixedDuelist = WhoseTurn() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  BigEvolutionPill_OnOpponentEndPhase(endedFixedDuelist);
  TryClearWeaponChangeOnOpponentEndPhase(endedFixedDuelist);
  TryClearGravekeepersInscriptionEndPhase();
  EffectEvent_OnTurnBoundary();
  TheWhiteStoneOfAncients_AgeSentFlags();
  ClearRedDragonArchfiendAttackDeclaredMask();
  ResetTheGrandJupiterEndPhaseFlags();
  Yubel_ClearTurnState();
  MorphtronicLantron_ClearTurnState();
  ClearCostDown();
  ResetUltimateOfferingTurnState();
  CourtOfJustice_ResetTurnState();
  ResetExecutorMakyuraTurnState();
  AgeUltimateOfferingSetFlags();
  AgeFairyBoxSetFlags();
  AgeMirrorWallSetFlags();
  ClearCyberBarrierDragonTurnState();
  AgeBottomlessShiftingSandSetFlags();
  AgeWaveMotionCannonTurns();
  AgeFinalCountdownTurns();
  TryApplyBurningLandStandbyDamage();
  TryApplyDarkSnakeSyndromeStandbyDamage();
  TryApplyNightmareWheelStandbyDamage();
  TryApplyMaskOfDispelStandbyDamage();
  TryApplyMaskOfTheAccursedStandbyDamage();
  TryApplyMirageOfNightmareStandby();
  TryApplyFutureFusionStandby();
  TryApplyMorphtronicEngineStandby();
  standbyFixedDuelist = WhoseTurn();
  if (LightBarrier_IsActiveForDuelist(standbyFixedDuelist)
      || LightForce_IsActiveForDuelist(standbyFixedDuelist)) {
    coinHeads = RandRangeU8(0, 1) == 1;
    LightBarrier_ResolveStandbyCoin(standbyFixedDuelist, coinHeads);
    LightForce_ResolveStandbyCoin(standbyFixedDuelist, coinHeads);
  }
  TryApplyCyberneticZoneStandby();
  TryApplyDifferentDimensionCapsuleStandby();
  TryApplyWeaponChangeStandby();
  TryApplyNeedleWallStandby();
  TryApplyTourOfDoomStandby();
  TryApplyDestinyHeroDefenderStandbyDraw();
  TryApplyDestinyHeroDrawhandStandby();
  TryApplyDestinyHeroDestroyDogmaStandby();
  TryApplyDestinyHeroDogmaStandby();
  TryApplySilentSwordsmanStandby();
  TryApplySilentSwordsmanZeroStandby();
  TryApplyAzureEyesSilverDragonStandby();
  TryApplySilentMagicianLv4Standby();
  TryApplyDestinyHeroCaptainTenaciousStandby();
  TryApplyDestinyHeroDoomLordStandbyReturn();
  TryBottomlessShiftingSandTurnStart();
  ContinuousTraps_TryActivateOnOpponentTurnStart();
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
  ClearGladiatorBeastBattledMarks();
  if (IsDuelOver() == 1)
    return;
  TryApplyEvilHeroInfernalProdigyEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyPowerBondEndPhaseBurn();
  if (IsDuelOver() == 1)
    return;
  TryApplyCyberneticZoneEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyVenomSwampEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyGloriousIllusionEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryDestroyTyrantWingAtEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyArcanaForceExDarkRulerEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyAurkusEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyJainEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyEhrenEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyShireEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyLylaEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyGaronithEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyRaidenEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyLuminaEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyTwilightswornEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyJenisEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyMichaelEndPhase();
  if (IsDuelOver() == 1)
    return;
  DestinyHeroDoomLord_ClearAttackLockAtEndPhase();
  if (IsDuelOver() == 1)
    return;
  CannotAttackThisTurn_ClearMarksAtEndPhase();
  if (IsDuelOver() == 1)
    return;
  MorphtronicMagnenBar_ClearAttackMarksAtEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyHeliosDuoMegistusEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyHeliosTriceMegistusEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyAromaJarEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyEvilDragonAnantaEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyArmedDragonLv5EndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyArmedDragonLv7EndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyHorusEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyJudgmentEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyReptilianneNagaEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyDestinyHeroDeciderEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryClearDestinyHeroDusktopiaProtectionEndPhase();
  TryClearAzureEyesSilverDragonProtectEndPhase();
  ElementalHeroGlowNeos_ClearTurnMarksAtEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyGandoraXEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyMajesticMechGoryuEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryReturnContactFusionsAtEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyFlavianEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyFusionDestinyEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyOverDestinyEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyTheGazeOfTimaeusEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyVipersRebirthEndPhase();
  if (IsDuelOver() == 1)
    return;
  HystericSign_TryResolveEndPhase();
  TryApplyMysticMineEndPhase();
  if (IsDuelOver() == 1)
    return;
  DestroyInstantFusionMonstersAtEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyRescueEndPhaseDestroy();
  if (IsDuelOver() == 1)
    return;
  TryApplyElementalHeroNebulaNeosEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyElementalHeroCosmoNeosEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryApplyElementalHeroChaosNeosEndPhase();
  if (IsDuelOver() == 1)
    return;
  TryClearDivinerOfTheHeraldEndPhase();
  TryApplyHarpieOracleEndPhase();
  if (IsDuelOver() == 1)
    return;
  BazooTheSoulEater_ClearAtkBoostOnEndPhase();
  ResetTempStagesForAllCards();
  AromaGarden_ReapplyTempBoostAfterReset();
  AromaGarden_OnEndPhase();
  ClearAllRiryokuAtkDeltas();
  ClearLightEndDragonDefStages();
  TheSupremacySun_AgeStandbyFlags();
  TheSupremacySun_TryResolveStandbyRevive();
  if (IsDuelOver() == 1)
    return;
  CheckBoardForTurnEffects__Hook(!gRuntimeConfig.turn_off_visual_scanner);
}