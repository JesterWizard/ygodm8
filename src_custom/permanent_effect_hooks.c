#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "dynamic_equip.h"
#include "graveyard_effects.h"
#include "yubel.h"
#include "elemental_hero_flash.h"
#include "familiar_knight.h"
#include "giant_rat.h"
#include "the_thing_in_the_crater.h"
#include "pyramid_of_light.h"
#include "dark_magician_knight.h"
#include "zaborg_the_thunder_monarch.h"
#include "caius_the_shadow_monarch.h"
#include "mobius_the_frost_monarch.h"
#include "kaiser_glider.h"
#include "elemental_hero_core.h"
#include "moister_creature.h"
#include "great_maju_garzett.h"
#include "maju_garzett.h"
#include "the_tyrant_neptune.h"
#include "the_big_saturn.h"
#include "the_tripper_mercury.h"
#include "the_wicked_eraser.h"
#include "the_wicked_avatar.h"
#include "imperial_order.h"
#include "arsenal_bug.h"
#include "berserk_gorilla.h"
#include "level_limit_area_b.h"
#include "level_limit_area_a.h"
#include "duel_helpers.h"
#include "duel_attack_restrictions.h"
#include "ring_of_destruction.h"
#include "dark_dust_spirit.h"
#include "harpie_lady_2.h"
#include "ai_sim.h"
#include "card.h"

extern void (*sPermanentEffects[])(void);
extern unsigned char (*g8E0C800[])(void);

void TryActivatingPermanentEffects(void);
void sub_802ACC0(void);
void sub_802ADF4(void);
void sub_80408BC(void);
void sub_802ADA4(void);
void sub_802AE44(void);
void UpdateDuelGfxExceptField(void);
void ResetTempStagesForAllCards(void);
void AddTributeCredit(u16 tributeCardId);
u8 DoubleCostonCoversDarkTributeSummon(u16 summonCardId, u16 tributeCardId);

typedef unsigned char (*PermanentEffectCondition)(void);
typedef void (*PermanentEffectHandler)(void);

typedef struct {
  u16 cardId;
  PermanentEffectCondition shouldActivate;
  PermanentEffectHandler activate;
} PermanentEffectOverride;

unsigned char ShouldActivateMilusRadiant(void);
void ActivateMilusRadiant(void);
unsigned char ShouldActivateMukaMuka(void);
void ActivateMukaMuka(void);
unsigned char ShouldActivateCeremonialBell(void);
void ActivateCeremonialBell(void);
unsigned char ShouldActivateBlueEyesShiningDragon(void);
void ActivateBlueEyesShiningDragon(void);
unsigned char ShouldActivateSpellCanceller(void);
void ActivateSpellCanceller(void);
unsigned char ShouldActivateYamataDragon(void);
void ActivateYamataDragon(void);
unsigned char ShouldActivateMaraudingCaptain(void);
void ActivateMaraudingCaptain(void);
unsigned char ShouldActivatePetenTheDarkClown(void);
void ActivatePetenTheDarkClown(void);
unsigned char ShouldActivateYubelEvolution(void);
void ActivateYubelEvolution(void);
unsigned char ShouldActivateYubelTerrorEvolution(void);
void ActivateYubelTerrorEvolution(void);
unsigned char ShouldActivateGiantRat(void);
void ActivateGiantRat(void);
unsigned char ShouldActivateTheThingInTheCrater(void);
void ActivateTheThingInTheCrater(void);
unsigned char ShouldActivateGrenMajuDaEiza(void);
void ActivateGrenMajuDaEiza(void);
unsigned char ShouldActivateDesFeralImp(void);
void ActivateDesFeralImp(void);
unsigned char ShouldActivateDARK_MAGICIAN_OF_CHAOS(void);
void ActivateDARK_MAGICIAN_OF_CHAOS(void);
unsigned char ShouldActivateArsenalBug(void);
void ActivateArsenalBug(void);
unsigned char ShouldActivateGranadora(void);
void ActivateGranadora(void);
unsigned char ShouldActivateTheBigSaturn(void);
void ActivateTheBigSaturn(void);
unsigned char ShouldActivateBurningAlgae(void);
void ActivateBurningAlgae(void);
unsigned char ShouldActivateBerserkGorilla(void);
unsigned char ShouldActivateMobiusTheFrostMonarch(void);
void ActivateMobiusTheFrostMonarch(void);
void ActivateBerserkGorilla(void);
unsigned char ShouldActivateElementalHeroCaptainGold(void);
void ActivateElementalHeroCaptainGold(void);
unsigned char ShouldActivateTheWickedAvatar(void);
void ActivateTheWickedAvatar(void);
u8 TryAutoSummonBlueEyesShiningDragon(void);
u8 TryAutoSummonTheWingedDragonOfRaSphereMode(void);
unsigned char IsSkillDrainActiveOnField(void);
unsigned char TryActivateSkillDrainAndNegateCardId(u16 negatedCardId);

static const PermanentEffectOverride sPermanentEffectOverrides[] __attribute__((section(".text"))) = {
  {
    .cardId = MILUS_RADIANT,
    .shouldActivate = ShouldActivateMilusRadiant,
    .activate = ActivateMilusRadiant,
  },
  {
    .cardId = MUKA_MUKA,
    .shouldActivate = ShouldActivateMukaMuka,
    .activate = ActivateMukaMuka,
  },
  {
    .cardId = CEREMONIAL_BELL,
    .shouldActivate = ShouldActivateCeremonialBell,
    .activate = ActivateCeremonialBell,
  },
  {
    .cardId = BLUE_EYES_SHINING_DRAGON,
    .shouldActivate = ShouldActivateBlueEyesShiningDragon,
    .activate = ActivateBlueEyesShiningDragon,
  },
  {
    .cardId = SPELL_CANCELLER,
    .shouldActivate = ShouldActivateSpellCanceller,
    .activate = ActivateSpellCanceller,
  },
  {
    .cardId = YAMATA_DRAGON,
    .shouldActivate = ShouldActivateYamataDragon,
    .activate = ActivateYamataDragon,
  },
  {
    .cardId = SANGAN,
    .shouldActivate = ShouldActivateGraveyardDrawOnDestroy,
    .activate = ActivateGraveyardDrawOnDestroy,
  },
  {
    .cardId = WITCH_OF_THE_BLACK_FOREST,
    .shouldActivate = ShouldActivateGraveyardDrawOnDestroy,
    .activate = ActivateGraveyardDrawOnDestroy,
  },
  {
    .cardId = FAMILIAR_KNIGHT,
    .shouldActivate = ShouldActivateFamiliarKnight,
    .activate = ActivateFamiliarKnight,
  },
  {
    .cardId = ELEMENTAL_HERO_FLASH,
    .shouldActivate = ShouldActivateElementalHeroFlash,
    .activate = ActivateElementalHeroFlash,
  },
  {
    .cardId = DARK_MAGICIAN_KNIGHT,
    .shouldActivate = ShouldActivateDarkMagicianKnight,
    .activate = ActivateDarkMagicianKnight,
  },
  {
    .cardId = ZABORG_THE_THUNDER_MONARCH,
    .shouldActivate = ShouldActivateZaborgTheThunderMonarch,
    .activate = ActivateZaborgTheThunderMonarch,
  },
  {
    .cardId = CAIUS_THE_SHADOW_MONARCH,
    .shouldActivate = ShouldActivateCaiusTheShadowMonarch,
    .activate = ActivateCaiusTheShadowMonarch,
  },
  {
    .cardId = DARK_DUST_SPIRIT,
    .shouldActivate = ShouldActivateDarkDustSpiritSummon,
    .activate = ActivateDarkDustSpiritSummon,
  },
  {
    .cardId = MARAUDING_CAPTAIN,
    .shouldActivate = ShouldActivateMaraudingCaptain,
    .activate = ActivateMaraudingCaptain,
  },
  {
    .cardId = KAISER_GLIDER,
    .shouldActivate = ShouldActivateKaiserGlider,
    .activate = ActivateKaiserGlider,
  },
  {
    .cardId = ELEMENTAL_HERO_CORE,
    .shouldActivate = ShouldActivateElementalHeroCore,
    .activate = ActivateElementalHeroCore,
  },
  {
    .cardId = MOISTER_CREATURE,
    .shouldActivate = ShouldActivateMoisterCreature,
    .activate = ActivateMoisterCreature,
  },
  {
    .cardId = GREAT_MAJU_GARZETT,
    .shouldActivate = ShouldActivateGreatMajuGarzett,
    .activate = ActivateGreatMajuGarzett,
  },
  {
    .cardId = MAJU_GARZETT,
    .shouldActivate = ShouldActivateMajuGarzett,
    .activate = ActivateMajuGarzett,
  },
  {
    .cardId = THE_TYRANT_NEPTUNE,
    .shouldActivate = ShouldActivateTheTyrantNeptune,
    .activate = ActivateTheTyrantNeptune,
  },
  {
    .cardId = PETEN_THE_DARK_CLOWN,
    .shouldActivate = ShouldActivatePetenTheDarkClown,
    .activate = ActivatePetenTheDarkClown,
  },
  {
    .cardId = YUBEL,
    .shouldActivate = ShouldActivateYubelEvolution,
    .activate = ActivateYubelEvolution,
  },
  {
    .cardId = YUBEL_TERROR_INCARNATE,
    .shouldActivate = ShouldActivateYubelTerrorEvolution,
    .activate = ActivateYubelTerrorEvolution,
  },
  {
    .cardId = GIANT_RAT,
    .shouldActivate = ShouldActivateGiantRat,
    .activate = ActivateGiantRat,
  },
  {
    .cardId = THE_THING_IN_THE_CRATER,
    .shouldActivate = ShouldActivateTheThingInTheCrater,
    .activate = ActivateTheThingInTheCrater,
  },
  {
    .cardId = GREN_MAJU_DA_EIZA,
    .shouldActivate = ShouldActivateGrenMajuDaEiza,
    .activate = ActivateGrenMajuDaEiza,
  },
  {
    .cardId = DES_FERAL_IMP,
    .shouldActivate = ShouldActivateDesFeralImp,
    .activate = ActivateDesFeralImp,
  },
  {
    .cardId = ARSENAL_BUG,
    .shouldActivate = ShouldActivateArsenalBug,
    .activate = ActivateArsenalBug,
  },
  {
    .cardId = GRANADORA,
    .shouldActivate = ShouldActivateGranadora,
    .activate = ActivateGranadora,
  },
  {
    .cardId = BURNING_ALGAE,
    .shouldActivate = ShouldActivateBurningAlgae,
    .activate = ActivateBurningAlgae,
  },
  {
    .cardId = BERSERK_GORILLA,
    .shouldActivate = ShouldActivateBerserkGorilla,
    .activate = ActivateBerserkGorilla,
  },
  {
    .cardId = MOBIUS_THE_FROST_MONARCH,
    .shouldActivate = ShouldActivateMobiusTheFrostMonarch,
    .activate = ActivateMobiusTheFrostMonarch,
  },
  {
    .cardId = DARK_MAGICIAN_OF_CHAOS,
    .shouldActivate = ShouldActivateDARK_MAGICIAN_OF_CHAOS,
    .activate = ActivateDARK_MAGICIAN_OF_CHAOS,
  },
  {
    .cardId = ELEMENTAL_HERO_CAPTAIN_GOLD,
    .shouldActivate = ShouldActivateElementalHeroCaptainGold,
    .activate = ActivateElementalHeroCaptainGold,
  },
  {
    .cardId = THE_BIG_SATURN,
    .shouldActivate = ShouldActivateTheBigSaturn,
    .activate = ActivateTheBigSaturn,
  },
  {
    .cardId = THE_WICKED_ERASER,
    .shouldActivate = ShouldActivateTheWickedEraser,
    .activate = ActivateTheWickedEraser,
  },
  {
    .cardId = THE_TRIPPER_MERCURY,
    .shouldActivate = ShouldActivateTheTripperMercury,
    .activate = ActivateTheTripperMercury,
  },
  {
    .cardId = THE_WICKED_AVATAR,
    .shouldActivate = ShouldActivateTheWickedAvatar,
    .activate = ActivateTheWickedAvatar,
  },
};

static const PermanentEffectOverride *GetPermanentEffectOverride(u16 cardId) {
  unsigned char i;

  for (i = 0; i < ARRAY_COUNT(sPermanentEffectOverrides); i++) {
    if (sPermanentEffectOverrides[i].cardId == cardId)
      return &sPermanentEffectOverrides[i];
  }

  return NULL;
}

static u8 CardHasPermanentEffectSource(u16 cardId)
{
  const PermanentEffectOverride *override;

  if (cardId == CARD_NONE)
    return FALSE;

  override = GetPermanentEffectOverride(cardId);
  if (override != NULL)
    return TRUE;

  SetCardInfo(cardId);
  return gCardInfo.unk1E != 0;
}

static u8 FieldZoneHasPermanentEffectSource(struct DuelCard *zone, u8 turnRow)
{
  u16 copied;

  if (zone->id == CARD_NONE)
    return FALSE;
  if (gHideEffectText && !zone->isFaceUp && (turnRow == 0 || turnRow == 1))
    return FALSE;
  if (CardHasPermanentEffectSource(zone->id))
    return TRUE;

  copied = TheTyrantNeptune_GetCopiedCardId(zone);
  if (copied == CARD_NONE)
    return FALSE;

  return CardHasPermanentEffectSource(copied);
}

u8 AiSimFieldNeedsPermanentRescan(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (FieldZoneHasPermanentEffectSource(gTurnZones[2][col], 2))
      return TRUE;
  }
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (FieldZoneHasPermanentEffectSource(gTurnZones[1][col], 1))
      return TRUE;
  }
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (FieldZoneHasPermanentEffectSource(gTurnZones[3][col], 3))
      return TRUE;
  }
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (FieldZoneHasPermanentEffectSource(gTurnZones[0][col], 0))
      return TRUE;
  }

  if (CardHasPermanentEffectSource(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard))
    return TRUE;
  if (CardHasPermanentEffectSource(gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard))
    return TRUE;

  return FALSE;
}

static void ResetTempStagesForFieldCards(void)
{
  u8 row;
  u8 col;

  for (row = 0; row < 4; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++)
      gDuel.board[row][col].tempStage = 0;
  }
}

static void TryActivatingPermanentEffect__Hook(void) {
  const PermanentEffectOverride *override;

  /* Skill Drain negates all monster effects on the field */
  if (gActiveEffect.turnRow == 1 || gActiveEffect.turnRow == 2) {
    if (TryActivateSkillDrainAndNegateCardId(gActiveEffect.cardId))
      return;
  }

  override = GetPermanentEffectOverride(gActiveEffect.cardId);

  if (override != NULL) {
    ResetCardEffectTextData();
    SetCardEffectTextType(8);
    override->activate();
    return;
  }

  ResetCardEffectTextData();
  SetCardEffectTextType(8);
  SetCardInfo(gActiveEffect.cardId);
  sPermanentEffects[gCardInfo.unk1E]();
}

static unsigned char ShouldActivatePermanentEffect__Hook(void) {
  const PermanentEffectOverride *override;

  if (gActiveEffect.cardId == CARD_NONE)
    return FALSE;

  /* Skill Drain negates all monster effects on the field */
  if ((gActiveEffect.turnRow == 1 || gActiveEffect.turnRow == 2) && IsSkillDrainActiveOnField())
    return FALSE;

  if (IsImperialOrderNegatingSpell(gActiveEffect.cardId))
    return FALSE;

  /* Harpie Lady 2: negate effects of monsters destroyed in battle */
  if ((gActiveEffect.turnRow == 6 || gActiveEffect.turnRow == 7)
      && gActiveEffect.cardId == gHarpieLady2NegatedCardId) {
    gHarpieLady2NegatedCardId = CARD_NONE;
    return FALSE;
  }

  override = GetPermanentEffectOverride(gActiveEffect.cardId);

  if (gActiveEffect.cardId == JAM_BREEDING_MACHINE || gActiveEffect.cardId == TOLL)
    return FALSE;

  if (override != NULL)
    return override->shouldActivate();

  SetCardInfo(gActiveEffect.cardId);
  if (gCardInfo.unk1E == 0)
    return FALSE;
  return g8E0C800[gCardInfo.unk1E]();
}

static void TryScanPermanentEffectAt(struct DuelCard **row, u8 turnRow, u8 col,
                                     u8 animateCursor)
{
  gActiveEffect.turnRow = turnRow;
  gActiveEffect.col = col;
  gActiveEffect.cardId = row[col]->id;
  if (animateCursor == TRUE && !gHideEffectText)
    sub_802ACC0();
  if (ShouldActivatePermanentEffect__Hook() == 1) {
    if (!gHideEffectText)
      sub_8034FEC(0x177);
    TryActivatingPermanentEffect__Hook();
    if (!gHideEffectText)
      PlayMusic(MUSIC_375);
  }
}

static void ScanPermanentEffectRow__Hook(struct DuelCard **row, u8 turnRow, u8 animateCursor) {
  u8 i;

  gActiveEffect.turnRow = turnRow;
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 neptuneSavedId;

    if (row[i]->id == CARD_NONE)
      continue;
    /* ponytail: AI sim must not read face-down opponent cards — prevents
       logic loops from spurious effect activation on unknown cards. */
    if (gHideEffectText && !row[i]->isFaceUp && (turnRow == 0 || turnRow == 1))
      continue;

    TryScanPermanentEffectAt(row, turnRow, i, animateCursor);
    if (IsDuelOver() == 1) {
      if (!gHideEffectText)
        sub_8034FEC(0x177);
      return;
    }

    /* Neptune gains permanent effects of its copied tribute. */
    neptuneSavedId = TheTyrantNeptune_BeginEffectIdentity(row[i]);
    if (neptuneSavedId != CARD_NONE) {
      TryScanPermanentEffectAt(row, turnRow, i, FALSE);
      TheTyrantNeptune_EndEffectIdentity(row[i], neptuneSavedId);
      if (IsDuelOver() == 1) {
        if (!gHideEffectText)
          sub_8034FEC(0x177);
        return;
      }
    }
  }
}

static void ScanPermanentEffectGraveyard__Hook(u8 turnRow, u8 duelist, u8 animateCursor) {
  gActiveEffect.turnRow = turnRow;
  gActiveEffect.col = 0;
  gActiveEffect.cardId = gTurnDuelistBattleState[duelist]->graveyard;
  TheBigSaturn_PrepareGraveyardScan(turnRow, &gActiveEffect.cardId);
  if (gActiveEffect.cardId == CARD_NONE)
    return;
  if (animateCursor == TRUE && !gHideEffectText)
    sub_802ADF4();
  if (ShouldActivatePermanentEffect__Hook() == 1) {
    if (!gHideEffectText)
      sub_8034FEC(0x177);
    TryActivatingPermanentEffect__Hook();
    if (!gHideEffectText)
      PlayMusic(MUSIC_375);
  }
}

static void CheckBoardForPermanentEffects__Hook(u8 animateScanner) {
  /* ponytail: AI sim never runs continuous effects from cards still in hand. */
  if (!gHideEffectText)
    ScanPermanentEffectRow__Hook(gTurnHands[ACTIVE_DUELIST], 4, animateScanner);
  if (IsDuelOver() == 1)
    return;

  /* ponytail: AI sim never activates hand permanent effects on the hidden hand. */
  if (!gHideEffectText) {
    ScanPermanentEffectRow__Hook(gTurnHands[INACTIVE_DUELIST], 5, FALSE);
    if (IsDuelOver() == 1)
      return;
  }

  if (!gHideEffectText)
    PlayMusic(MUSIC_375);

  if (!gHideEffectText ||
      CardHasPermanentEffectSource(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard) ||
      TheBigSaturn_PendingGraveyardTurnRow() == 6) {
    ScanPermanentEffectGraveyard__Hook(6, ACTIVE_DUELIST, FALSE);
    if (IsDuelOver() == 1) {
      if (!gHideEffectText)
        sub_8034FEC(0x177);
      return;
    }
  }

  if (!gHideEffectText ||
      CardHasPermanentEffectSource(gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard) ||
      TheBigSaturn_PendingGraveyardTurnRow() == 7) {
    ScanPermanentEffectGraveyard__Hook(7, INACTIVE_DUELIST, FALSE);
    if (IsDuelOver() == 1) {
      if (!gHideEffectText)
        sub_8034FEC(0x177);
      return;
    }
  }

  ScanPermanentEffectRow__Hook(gTurnZones[2], 2, animateScanner);
  if (IsDuelOver() == 1)
    return;

  ScanPermanentEffectRow__Hook(gTurnZones[1], 1, animateScanner);
  if (IsDuelOver() == 1)
    return;

  ScanPermanentEffectRow__Hook(gTurnZones[3], 3, animateScanner);
  if (IsDuelOver() == 1)
    return;

  ScanPermanentEffectRow__Hook(gTurnZones[0], 0, animateScanner);
  if (!gHideEffectText)
    sub_8034FEC(0x177);
}

static void TryActivatingPermanentEffectsPostBoardScan(u8 aiSim)
{
  if (!aiSim || IsPyramidOfLightActiveOnField())
    EnforcePyramidOfLightGodBan();

  if (TryAutoSummonBlueEyesShiningDragon() == TRUE
      || TryAutoSummonTheWingedDragonOfRaSphereMode() == TRUE) {
    if (!aiSim)
      UpdateDuelGfxExceptField();
    ResetTempStagesForAllCards();
    CheckBoardForPermanentEffects__Hook(FALSE);
  }

  ResolvePendingGraveyardDrawOnDestroy();
  if (!aiSim) {
    TheBigSaturn_TryResolveGyDamage();
    TheWickedEraser_TryResolveFieldWipe();
  }
  if (!aiSim || IsLevelLimitAreaBActiveOnField())
    Duel_CheckLevelLimitAreaBAfterFieldChange();
  if (!aiSim || IsLevelLimitAreaAActiveOnField())
    Duel_CheckLevelLimitAreaAAfterFieldChange();
  Duel_RefreshAttackRestrictions();

  if (aiSim)
    return;

  Duel_CheckRivalryOfWarlordsAfterFieldChange();
  Duel_CheckAmazonessTigerAfterFieldChange();
  Duel_CheckRingOfDestructionAfterFieldChange();
}

void PermanentEffect_RunSimBoardScan(void)
{
  CheckBoardForPermanentEffects__Hook(FALSE);
}

void PermanentEffect_RunSimPostBoardScan(void)
{
  TryActivatingPermanentEffectsPostBoardScan(TRUE);
}

LYN_REPLACE_CHECK(TryActivatingPermanentEffects);
void TryActivatingPermanentEffects__Replacement(void) {
  u8 hideEffectText = gHideEffectText;
  u8 aiSim = gHideEffectText == TRUE;
  u8 needsRescan;

  if (aiSim) {
    if (HasActiveDynamicEquips())
      RecalculateAllDynamicEquips();
    gActiveEffect.turn = WhoseTurn();
    ResetTempStagesForFieldCards();
    needsRescan = AiSimFieldNeedsPermanentRescan();
    if (needsRescan)
      CheckBoardForPermanentEffects__Hook(FALSE);
    TryActivatingPermanentEffectsPostBoardScan(TRUE);
    gHideEffectText = hideEffectText;
    return;
  }

  if (!aiSim || HasActiveDynamicEquips())
    RecalculateAllDynamicEquips();
  gActiveEffect.turn = WhoseTurn();
  if (!aiSim && !gRuntimeConfig.turn_off_visual_scanner) {
    sub_80408BC();
    sub_802ADA4();
  }
  ResetTempStagesForAllCards();
  if (!aiSim)
    UpdateDuelGfxExceptField();
  if (gRuntimeConfig.turn_off_visual_scanner == TRUE)
    gHideEffectText = TRUE;
  CheckBoardForPermanentEffects__Hook(!aiSim && !gRuntimeConfig.turn_off_visual_scanner);

  TryActivatingPermanentEffectsPostBoardScan(aiSim);

  gHideEffectText = hideEffectText;
  if (!aiSim) {
    UpdateDuelGfxExceptField();
    sub_802AE44();
  }
}

unsigned char ShouldActivateDARKLORD_NURSE_REFICULE(void);
void ActivateDARKLORD_NURSE_REFICULE(void);
unsigned char ShouldActivatePROTECTOR_OF_THE_SANCTUARY(void);
void ActivatePROTECTOR_OF_THE_SANCTUARY(void);
unsigned char ShouldActivateVISION_HERO_TRINITY(void);
void ActivateVISION_HERO_TRINITY(void);
unsigned char ShouldActivateTHE_AGENT_OF_WISDOM_MERCURY(void);
void ActivateTHE_AGENT_OF_WISDOM_MERCURY(void);

static const PermanentEffectOverride sPermanentEffectOverrides2[] __attribute__((section(".text"))) = {
  {
    .cardId = DARKLORD_NURSE_REFICULE,
    .shouldActivate = ShouldActivateDARKLORD_NURSE_REFICULE,
    .activate = ActivateDARKLORD_NURSE_REFICULE,
  },
  {
    .cardId = PROTECTOR_OF_THE_SANCTUARY,
    .shouldActivate = ShouldActivatePROTECTOR_OF_THE_SANCTUARY,
    .activate = ActivatePROTECTOR_OF_THE_SANCTUARY,
  },
  {
    .cardId = VISION_HERO_TRINITY,
    .shouldActivate = ShouldActivateVISION_HERO_TRINITY,
    .activate = ActivateVISION_HERO_TRINITY,
  },
  {
    .cardId = THE_AGENT_OF_WISDOM_MERCURY,
    .shouldActivate = ShouldActivateTHE_AGENT_OF_WISDOM_MERCURY,
    .activate = ActivateTHE_AGENT_OF_WISDOM_MERCURY,
  },
};

