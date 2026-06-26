#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "dynamic_equip.h"
#include "graveyard_effects.h"
#include "familiar_knight.h"
#include "giant_rat.h"
#include "the_thing_in_the_crater.h"
#include "pyramid_of_light.h"
#include "dark_magician_knight.h"
#include "zaborg_the_thunder_monarch.h"
#include "caius_the_shadow_monarch.h"
#include "mobius_the_frost_monarch.h"
#include "kaiser_glider.h"
#include "moister_creature.h"
#include "great_maju_garzett.h"
#include "maju_garzett.h"
#include "imperial_order.h"
#include "arsenal_bug.h"
#include "berserk_gorilla.h"
#include "level_limit_area_b.h"
#include "duel_helpers.h"
#include "duel_attack_restrictions.h"
#include "ring_of_destruction.h"
#include "dark_dust_spirit.h"

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
unsigned char ShouldActivateGiantRat(void);
void ActivateGiantRat(void);
unsigned char ShouldActivateTheThingInTheCrater(void);
void ActivateTheThingInTheCrater(void);
unsigned char ShouldActivateGrenMajuDaEiza(void);
void ActivateGrenMajuDaEiza(void);
unsigned char ShouldActivateDesFeralImp(void);
void ActivateDesFeralImp(void);
unsigned char ShouldActivateArsenalBug(void);
void ActivateArsenalBug(void);
unsigned char ShouldActivateGranadora(void);
void ActivateGranadora(void);
unsigned char ShouldActivateBurningAlgae(void);
void ActivateBurningAlgae(void);
unsigned char ShouldActivateBerserkGorilla(void);
unsigned char ShouldActivateMobiusTheFrostMonarch(void);
void ActivateMobiusTheFrostMonarch(void);
void ActivateBerserkGorilla(void);
u8 TryAutoSummonBlueEyesShiningDragon(void);
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
    .cardId = PETEN_THE_DARK_CLOWN,
    .shouldActivate = ShouldActivatePetenTheDarkClown,
    .activate = ActivatePetenTheDarkClown,
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
};

static const PermanentEffectOverride *GetPermanentEffectOverride(u16 cardId) {
  unsigned char i;

  for (i = 0; i < ARRAY_COUNT(sPermanentEffectOverrides); i++) {
    if (sPermanentEffectOverrides[i].cardId == cardId)
      return &sPermanentEffectOverrides[i];
  }

  return NULL;
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

  /* Skill Drain negates all monster effects on the field */
  if ((gActiveEffect.turnRow == 1 || gActiveEffect.turnRow == 2) && IsSkillDrainActiveOnField())
    return FALSE;

  if (IsImperialOrderNegatingSpell(gActiveEffect.cardId))
    return FALSE;

  override = GetPermanentEffectOverride(gActiveEffect.cardId);

  if (gActiveEffect.cardId == JAM_BREEDING_MACHINE || gActiveEffect.cardId == TOLL)
    return FALSE;

  if (override != NULL)
    return override->shouldActivate();

  SetCardInfo(gActiveEffect.cardId);
  return g8E0C800[gCardInfo.unk1E]();
}

static void ScanPermanentEffectRow__Hook(struct DuelCard **row, u8 turnRow, u8 animateCursor) {
  u8 i;

  gActiveEffect.turnRow = turnRow;
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    gActiveEffect.col = i;
    gActiveEffect.cardId = row[i]->id;
    if (animateCursor == TRUE && !gHideEffectText)
      sub_802ACC0();
    if (ShouldActivatePermanentEffect__Hook() == 1) {
      sub_8034FEC(0x177);
      TryActivatingPermanentEffect__Hook();
      if (!gHideEffectText)
        PlayMusic(MUSIC_375);
    }
    if (IsDuelOver() == 1) {
      sub_8034FEC(0x177);
      return;
    }
  }
}

static void ScanPermanentEffectGraveyard__Hook(u8 turnRow, u8 duelist, u8 animateCursor) {
  gActiveEffect.turnRow = turnRow;
  gActiveEffect.col = 0;
  gActiveEffect.cardId = gTurnDuelistBattleState[duelist]->graveyard;
  if (animateCursor == TRUE && !gHideEffectText)
    sub_802ADF4();
  if (ShouldActivatePermanentEffect__Hook() == 1) {
    sub_8034FEC(0x177);
    TryActivatingPermanentEffect__Hook();
    if (!gHideEffectText)
      PlayMusic(MUSIC_375);
  }
}

static void CheckBoardForPermanentEffects__Hook(u8 animateScanner) {
  ScanPermanentEffectRow__Hook(gTurnHands[ACTIVE_DUELIST], 4, animateScanner);
  if (IsDuelOver() == 1)
    return;

  ScanPermanentEffectRow__Hook(gTurnHands[INACTIVE_DUELIST], 5, FALSE);
  if (IsDuelOver() == 1)
    return;

  if (!gHideEffectText)
    PlayMusic(MUSIC_375);

  ScanPermanentEffectGraveyard__Hook(6, ACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == 1) {
    sub_8034FEC(0x177);
    return;
  }

  ScanPermanentEffectGraveyard__Hook(7, INACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == 1) {
    sub_8034FEC(0x177);
    return;
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
  sub_8034FEC(0x177);
}

LYN_REPLACE_CHECK(TryActivatingPermanentEffects);
void TryActivatingPermanentEffects__Replacement(void) {
  u8 hideEffectText = gHideEffectText;

  RecalculateAllDynamicEquips();
  gActiveEffect.turn = WhoseTurn();
  if (!gHideEffectText && !gRuntimeConfig.turn_off_visual_scanner) {
    sub_80408BC();
    sub_802ADA4();
  }
  ResetTempStagesForAllCards();
  if (!gHideEffectText)
    UpdateDuelGfxExceptField();
  if (gRuntimeConfig.turn_off_visual_scanner == TRUE)
    gHideEffectText = TRUE;
  CheckBoardForPermanentEffects__Hook(!gRuntimeConfig.turn_off_visual_scanner);
  EnforcePyramidOfLightGodBan();

  if (TryAutoSummonBlueEyesShiningDragon() == TRUE) {
    if (!gHideEffectText)
      UpdateDuelGfxExceptField();
    ResetTempStagesForAllCards();
    CheckBoardForPermanentEffects__Hook(FALSE);
  }

  gHideEffectText = hideEffectText;
  ResolvePendingGraveyardDrawOnDestroy();
  Duel_CheckRivalryOfWarlordsAfterFieldChange();
  Duel_CheckLevelLimitAreaBAfterFieldChange();
  Duel_CheckAmazonessTigerAfterFieldChange();
  Duel_RefreshAttackRestrictions();
  Duel_CheckRingOfDestructionAfterFieldChange();
  if (!gHideEffectText)
    UpdateDuelGfxExceptField();
  if (!gHideEffectText)
    sub_802AE44();
}
