#include "global.h"
#include "common-chax.h"
#include "board_placement.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "summon_tribute.h"
#include "dynamic_equip.h"
#include "mystical_space_typhoon.h"
#include "cannon_soldier.h"
#include "riryoku.h"
#include "pyramid_of_light.h"
#include "mask_of_restrict.h"
#include "soul_exchange.h"
#include "fairy_box.h"
#include "imperial_order.h"
#include "royal_decree.h"
#include "cats_ear_tribe.h"
#include "graveyard_effects.h"
#include "the_unhappy_maiden.h"
#include "vampire_baby.h"
#include "mefist_the_infernal_general.h"
#include "guardian_angel_joan.h"
#include "needle_burrower.h"
#include "hyper_hammerhead.h"
#include "absorbing_kid_from_the_sky.h"
#include "airknight_parshath.h"
#include "debug_ruleset.h"
#include "dark_magician_knight.h"
#include "embodiment_of_apophis.h"
#include "guardian_treasure.h"
#include "precious_cards_from_beyond.h"
#include "ojama_trio.h"
#include "hayabusa_knight.h"
#include "mermaid_knight.h"
#include "twin_swords_of_flashing_light_tryce.h"
#include "tyrant_dragon.h"
#include "sasuke_samurai.h"
#include "block_attack.h"
#include "soul_taker.h"
#include "negative_energy.h"
#include "delinquent_duo.h"
#include "the_forceful_sentry.h"
#include "meteor_of_destruction.h"
#include "final_countdown.h"
#include "chaos_greed.h"
#include "book_of_moon.h"
#include "toll.h"
#include "call_of_the_haunted.h"
#include "skull_invitation.h"
#include "self_destruct_button.h"
#include "the_dark_door.h"
#include "gravity_bind.h"
#include "curse_of_darkness.h"
#include "coffin_seller.h"
#include "dark_room_of_nightmare.h"
#include "kaiser_glider.h"
#include "nightmare_horse.h"
#include "amphibious_bugroth_mk_3.h"
#include "black_tyranno.h"
#include "reaper_on_the_nightmare.h"
#include "great_maju_garzett.h"
#include "goblin_king.h"
#include "raregold_armor.h"
#include "the_a_forces.h"

u8 TryPayChainEnergyCost(void);
u8 IsActivatedChainEnergyZone(const struct DuelCard *zone);
u8 IsActivatedTollZone(const struct DuelCard *zone);
u8 IsActivatedTheDarkDoorZone(const struct DuelCard *zone);
u8 IsActivatedDarkRoomZone(const struct DuelCard *zone);
u8 TryConsumeUltimateOfferingExtraSummonPayment(void);
void TryEnableUltimateOfferingExtraSummonAfterPlacement(void);
u8 IsActivatedUltimateOfferingZone(const struct DuelCard *zone);
void MarkUltimateOfferingJustSet(struct DuelCard *zone);
void MarkFairyBoxJustSet(struct DuelCard *zone);
unsigned char IsSpellCancellerSpellLockActive(void);
unsigned IsTrapTriggered(void);
void ActivateTrapEffect(u16 lp);

extern struct DuelCard gSelectedCard;

void DisplayCardInfoBar(void);
void HandlePlayerBackrowAction(void);
void TrySelectSpellTarget(void);
void sub_8041E70(u8, u8);
void ActivateSpellEffect(void);
void LockMonsterCardsInRow(unsigned char);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);
void SelectZone(struct DuelCard *zone);
void ResetCursorDestToCurrentPos(void);
unsigned char GetFirstNonEmptyMonZoneId(struct DuelCard *zone[]);
void ClearZone(struct DuelCard *zone);
void CopySelectedCardToZone(struct DuelCard *zone);
void sub_80449D8(void);
void TryActivateGranadoraOnMonsterPlacement(struct DuelCard *zone);
void TryEnforceBerserkGorillaOnMonsterPlacement(struct DuelCard *zone);
signed char FirstEmptyZoneInRow(struct DuelCard **zonePtr);
void sub_80441D0(void);
void MonsterActionMenu(void);
void HandlePlayerBackrowAction(void);
void DisplayNumRequiredTributesTextbox(unsigned char);
void sub_80442AC(void);
void sub_8044570(void);
void TryAttackWithMonster(void);
void SetCursorToCardDest(void);
void sub_8044A5C(void);
void sub_8044A88(void);
void sub_8044A30(void);
void OpenBMenu(void);
void HandleAButtonAction(void);
void HandleBButtonAction(void);
void sub_8022080(void);
void SetAttackAction(s32, s32);
void SetAttackActionDirectAttack(int);
void CheckGraveyardAndLoserFlags(void);
void CheckWinConditionFINAL(void);
void BlockTurnSummoning(u8);
void HandleAtkAndLifePointsAction(void);
void UpdateAllDuelGfx(void);
u8 TrySpecialSummonBlueEyesAlternativeWhiteDragonFromHand(u8);
u8 TrySpecialSummonGilasaurusFromHand(u8);
u8 TrySpecialSummonFenrirFromHand(u8);
void sub_801BC00(void);
unsigned char GetLastNonEmptyMonZoneId(struct DuelCard *zone[]);
s32 NumEmptyZonesInRow(struct DuelCard **row);
unsigned char GetDuelistStatus(unsigned char);

static u8 CardRequiresSpecialSummonOnly(u16 cardId)
{
  return cardId == RARE_METAL_DRAGON || cardId == FENRIR;
}

static void TryPlaceSelectedCardOnField_Local(void)
{
  u16 placedCardId = gFixedZones[gDuelCursor.destY][gDuelCursor.destX]->id;

  SetCardInfo(placedCardId);
  if (CardRequiresSpecialSummonOnly(gCardInfo.id)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }
  switch (GetTypeGroup(gCardInfo.id)) {
    case TYPE_GROUP_SPELL:
    case TYPE_GROUP_TRAP:
    case TYPE_GROUP_RITUAL:
      if (gDuelCursor.currentY == 3) {
        PlayMusic(SFX_PLACE_CARD);
        sub_80449D8();
        CheckWinConditionFINAL();
        TryActivatingPermanentEffects();
      } else {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      }
      break;
    default:
      if (gDuelCursor.currentY != 2) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      } else {
        PlayMusic(SFX_PLACE_CARD);
        BlockTurnSummoning(ACTIVE_DUELIST);
        LockMonsterCardsInRow(4);
        RecordPendingSummonTributeCount();
        sub_80449D8();
        TryActivatingPermanentEffects();
        if (placedCardId == GetPendingTributeSummonCardId()) {
          ResetNumTributes();
          ClearPendingTributeSummonCardId();
        }
      }
  }
}

static void FinishEquipSpellTargeting(void)
{
  u8 cursorRow = gDuelCursor.currentY;

  if (cursorRow == PLAYER_MONSTER_ROW)
    sub_8041E70(PLAYER_MONSTER_ROW, PLAYER_BACKROW);

  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
}

static void OpenPlayerMonsterActionMenu(void)
{
  if (gFixedZones[PLAYER_MONSTER_ROW][gDuelCursor.currentX]->id != CARD_NONE
      && !gFixedZones[PLAYER_MONSTER_ROW][gDuelCursor.currentX]->isLocked) {
    PlayMusic(SFX_SELECT);
    MonsterActionMenu();
  } else {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  }
}


LYN_REPLACE_CHECK(sub_80441D0);
void sub_80441D0__Replacement(void)
{
  switch (gDuelCursor.currentY) {
    case PLAYER_MONSTER_ROW:
      if (IsSoulExchangeActive()) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      } else {
        OpenPlayerMonsterActionMenu();
      }
      break;
    case OPPONENT_MONSTER_ROW:
      if (IsSoulExchangeActive()) {
        PerformSoulExchangeOpponentTribute();
        break;
      } else {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      }
      break;
    case PLAYER_BACKROW:
      if (gFixedZones[PLAYER_BACKROW][gDuelCursor.currentX]->id == CARD_NONE) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      } else {
        unsigned char numTributes = GetRitualNumRequiredTributes(
            gFixedZones[PLAYER_BACKROW][gDuelCursor.currentX]->id);
        if (!numTributes)
          HandlePlayerBackrowAction();
        else {
          PlayMusic(SFX_FORBIDDEN);
          DisplayNumRequiredTributesTextbox(numTributes);
        }
      }
      break;
    case PLAYER_HAND: {
      u16 handCardId = gFixedZones[PLAYER_HAND][gDuelCursor.currentX]->id;

      if (handCardId == CARD_NONE
          || gFixedZones[PLAYER_HAND][gDuelCursor.currentX]->isLocked) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      } else if (handCardId == BLUE_EYES_ALTERNATIVE_WHITE_DRAGON
          && TrySpecialSummonBlueEyesAlternativeWhiteDragonFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == GILASAURUS
          && TrySpecialSummonGilasaurusFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == FENRIR
          && TrySpecialSummonFenrirFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (CardRequiresSpecialSummonOnly(handCardId)) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      } else {
        unsigned char numTributes = GetMonsterNumRequiredTributesForHandSlot(
            gDuelCursor.currentX,
            gFixedZones[PLAYER_HAND][gDuelCursor.currentX]->id);
        if (numTributes) {
          if (IsMaskOfRestrictActiveOnField()) {
            PlayMusic(SFX_FORBIDDEN);
            WaitForVBlank();
          } else {
            SetGreatMajuGarzettPendingSummon(handCardId == GREAT_MAJU_GARZETT);
            SetPendingTributeSummonCardId(handCardId);
            ResetCursorDestToCurrentPos();
            PlayMusic(SFX_FORBIDDEN);
            DisplayNumRequiredTributesTextbox(numTributes);
          }
        } else {
          if (handCardId != GREAT_MAJU_GARZETT)
            SetGreatMajuGarzettPendingSummon(FALSE);
          PlayMusic(SFX_SELECT);
          sub_80442AC();
        }
      }
      break;
    }
    default:
      PlayMusic(SFX_FORBIDDEN);
      WaitForVBlank();
  }
}

LYN_REPLACE_CHECK(HandlePlayerBackrowAction);
void HandlePlayerBackrowAction__Replacement(void) {
  u16 id = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id;
  struct DuelCard *zone = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX];

  if ((id == SWORDS_OF_REVEALING_LIGHT && zone->isFaceUp == TRUE)
      || IsActivatedChainEnergyZone(zone)
      || IsActivatedTollZone(zone)
      || IsActivatedTheDarkDoorZone(zone)
      || IsActivatedDarkRoomZone(zone)
      || IsActivatedPyramidOfLightZone(zone)
      || IsActivatedUltimateOfferingZone(zone)
      || IsActivatedMaskOfRestrictZone(zone)
      || IsActivatedGravityBindZone(zone)
      || IsActivatedFairyBoxZone(zone)
      || IsActivatedSkullInvitationZone(zone)
      || IsActivatedSelfDestructButtonZone(zone)
      || IsActivatedCurseOfDarknessZone(zone)
      || IsNonSelectableCoffinSellerZone(zone)
      || IsActivatedFinalCountdownZone(zone)
      || IsActivatedPreciousCardsFromBeyondZone(zone)
      || IsActivatedTheAForcesZone(zone)
      || IsActiveDynamicEquipSpellZone(zone)) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  SelectZone(zone);
  ResetCursorDestToCurrentPos();

  if ((IsSpellCancellerSpellLockActive() || IsImperialOrderActiveOnField())
      && GetTypeGroup(id) == TYPE_GROUP_SPELL) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsRoyalDecreeActiveOnField() && GetTypeGroup(id) == TYPE_GROUP_TRAP) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsMysticalSpaceTyphoonCard(id)) {
    if (!FieldHasMysticalSpaceTyphoonTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginMysticalSpaceTyphoonTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsRiryokuCard(id)) {
    if (!FieldHasRiryokuTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginRiryokuTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsBlockAttackCard(id)) {
    if (!FieldHasBlockAttackTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginBlockAttackTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsSoulTakerCard(id)) {
    if (!FieldHasSoulTakerTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginSoulTakerTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsNegativeEnergyCard(id)) {
    if (!FieldHasNegativeEnergyTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginNegativeEnergyTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsBookOfMoonCard(id)) {
    if (!FieldHasBookOfMoonTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginBookOfMoonTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (id == GUARDIAN_TREASURE && !CanActivateGuardianTreasure()) {
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (id == DELINQUENT_DUO && !CanActivateDelinquentDuo()) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (id == THE_FORCEFUL_SENTRY && !CanActivateTheForcefulSentry()) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (id == METEOR_OF_DESTRUCTION && !CanActivateMeteorOfDestruction()) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (id == FINAL_COUNTDOWN && !CanActivateFinalCountdown()) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (id == CHAOS_GREED && !CanActivateChaosGreed()) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  switch (GetSpellType(id)) {
    case SPELL_TYPE_NORMAL:
      gDuelCursor.state = 0;
      gSpellEffectData.id = id;
      gSpellEffectData.row1 = gDuelCursor.currentY;
      gSpellEffectData.col1 = gDuelCursor.currentX;
      ActivateSpellEffect();
      if (gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked)
        LockMonsterCardsInRow(4);
      UpdateDuelGfxExceptField();
      CheckWinConditionExodia(WhoseTurn());
      if (IsDuelOver() != TRUE)
        TryActivatingPermanentEffects();
      break;
    case SPELL_TYPE_EQUIP:
      PlayMusic(SFX_SELECT);
      gDuelCursor.state = 2;
      gDuelCursor.currentX = GetFirstNonEmptyMonZoneId(gFixedZones[2]);
      gDuelCursor.currentY = 2;
      break;
    case SPELL_TYPE_INVALID:
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      break;
    default:
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      break;
  }

  DisplayCardInfoBar();
  sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
}

LYN_REPLACE_CHECK(TrySelectSpellTarget);
void TrySelectSpellTarget__Replacement(void) {
  if (gDuelCursor.currentY != 2) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else if (gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id == CARD_NONE) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else if (gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else {
    SetCardInfo(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id);
    if (GetTypeGroup(gCardInfo.id) == TYPE_GROUP_MONSTER) {
      gSpellEffectData.id = gFixedZones[gDuelCursor.destY][gDuelCursor.destX]->id;
      gSpellEffectData.row2 = gDuelCursor.destY;
      gSpellEffectData.col2 = gDuelCursor.destX;
      gSpellEffectData.row1 = gDuelCursor.currentY;
      gSpellEffectData.col1 = gDuelCursor.currentX;
      ActivateSpellEffect();
    }
    gDuelCursor.state = 0;
    FinishEquipSpellTargeting();
    TryActivatingPermanentEffects();
  }
}

static u8 PlayerPreferredPlacementCol(u8 fixedRow) {
  u8 col;

  if (gRuntimeConfig.enable_smarter_ai != TRUE)
    return (u8)FirstEmptyZoneInRow(gFixedZones[fixedRow]);

  col = Board_PreferredEmptyFixedCol(fixedRow);
  if (col != 0xFF)
    return col;

  return (u8)FirstEmptyZoneInRow(gFixedZones[fixedRow]);
}

LYN_REPLACE_CHECK(sub_80442AC);
void sub_80442AC__Replacement(void) {
  u16 id = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id;

  SetGreatMajuGarzettPendingSummon(id == GREAT_MAJU_GARZETT);
  if (!PendingTributeSummonStillUnpaid())
    SetPendingTributeSummonCardId(id);
  SelectZone(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
  gDuelCursor.state = 1;
  ResetCursorDestToCurrentPos();
  switch (GetTypeGroup(id)) {
  case TYPE_GROUP_MONSTER:
    gDuelCursor.currentX = PlayerPreferredPlacementCol(PLAYER_MONSTER_ROW);
    gDuelCursor.currentY = 2;
    break;
  case TYPE_GROUP_SPELL:
  case TYPE_GROUP_TRAP:
  case TYPE_GROUP_RITUAL:
    gDuelCursor.currentX = PlayerPreferredPlacementCol(PLAYER_BACKROW);
    gDuelCursor.currentY = 3;
    break;
  default:
    break;
  }
  DisplayCardInfoBar();
  sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
}

LYN_REPLACE_CHECK(sub_80449D8);
void sub_80449D8__Replacement(void)
{
  u8 placedRow;
  u8 placedCol;

  if (!TryPayChainEnergyCost()) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if (!TryConsumeUltimateOfferingExtraSummonPayment()) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if (ShouldBlockGodCardSummon(gSelectedCard.id)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  placedRow = gDuelCursor.currentY;
  placedCol = gDuelCursor.currentX;

  if (gRuntimeConfig.enable_smarter_ai == TRUE) {
    u8 preferredCol;

    if (placedRow == PLAYER_MONSTER_ROW)
      preferredCol = Board_PreferredEmptyFixedCol(PLAYER_MONSTER_ROW);
    else if (placedRow == PLAYER_BACKROW)
      preferredCol = Board_PreferredEmptyFixedCol(PLAYER_BACKROW);
    else
      preferredCol = 0xFF;

    if (preferredCol != 0xFF)
      placedCol = preferredCol;
  }

  if (gFixedZones[placedRow][placedCol]->id != CARD_NONE) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  ClearZone(gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
  CopySelectedCardToZone(gFixedZones[placedRow][placedCol]);
  if (placedRow == PLAYER_MONSTER_ROW || placedRow == OPPONENT_MONSTER_ROW) {
    TryEnforceBerserkGorillaOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
    TryActivateGranadoraOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
  }
  if (placedRow == PLAYER_MONSTER_ROW) {
    TryApplyPreciousCardsFromBeyondOnTributeSummon(
        gFixedZones[placedRow][placedCol]->id, WhoseTurn());
  }
  FinishGreatMajuGarzettTributeSummon(
      gFixedZones[placedRow][placedCol], placedRow, placedCol);
  MarkUltimateOfferingJustSet(gFixedZones[placedRow][placedCol]);
  MarkFairyBoxJustSet(gFixedZones[placedRow][placedCol]);
  TryEnableUltimateOfferingExtraSummonAfterPlacement();
  gDuelCursor.state = 0;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
}

LYN_REPLACE_CHECK(sub_8044570);
void sub_8044570__Replacement(void)
{
  unsigned char turn = WhoseTurn();

  if (GetDuelistStatus(turn) == DUELIST_STATUS_CANNOT_ATTACK || gTurnDuelistBattleState[ACTIVE_DUELIST]->sorlTurns) {
    PlayMusic(SFX_FORBIDDEN);
    gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked = 1;
    UpdateDuelGfxExceptField();
  } else if (!DebugRuleset_CanAttackThisTurn() || !TheDarkDoor_CanAttackThisTurn()
      || !GravityBind_CanMonsterAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)) {
    PlayMusic(SFX_FORBIDDEN);
    gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked = 1;
    UpdateDuelGfxExceptField();
  } else if ((NumEmptyZonesInRow(gTurnZones[1]) == MAX_ZONES_IN_ROW
      || CanNightmareHorseAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)
      || CanAmphibiousBugrothMk3AttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)
      || CanBlackTyrannoAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)
      || CanReaperOnTheNightmareAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id))
      && !RaregoldArmor_BlocksDirectAttack(
          WhoseTurn() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER)) {
    if (!DebugRuleset_AllowDirectAttacks()) {
      PlayMusic(SFX_FORBIDDEN);
      gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked = 1;
      UpdateDuelGfxExceptField();
    } else {
    gTrapEffectData.originRow = gDuelCursor.currentY;
    gTrapEffectData.originCol = gDuelCursor.currentX;
    gTrapEffectData.originCardId = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id;
    TryActivateEmbodimentOfApophisOnAttack();
    if (IsTrapTriggered() != 1) {
      if (!TryPayTollAttackCost()) {
        PlayMusic(SFX_FORBIDDEN);
        gDuelCursor.state = 0;
        return;
      }
      PlayMusic(SFX_SELECT);
      gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 0;
      gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isFaceUp = 1;
      gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked = 1;
      TryShowBlackTyrannoDirectAttackText(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id);
      PerformDirectAttackOrRedirectToEmbodimentOfApophis(gDuelCursor.currentX);
      TryApplyFairyBoxToPendingAction();
      TryApplyCatsEarTribeToPendingAction();
      HandleAtkAndLifePointsAction();
      DebugRuleset_MarkAttackUsed();
      TheDarkDoor_MarkAttackUsed();
      CheckGraveyardAndLoserFlags();
      TryUnlockHayabusaKnightForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockMermaidKnightForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockTryceEquipForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockTyrantDragonForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      gDuelCursor.state = 0;
      sub_801BC00();
      UpdateAllDuelGfx();
      ResolveTheUnhappyMaidenBattleEffect();
      ResolveVampireBabyBattleEffect();
      ResolveMefistTheInfernalGeneralDiscardBattleEffect();
      ResolveReaperOnTheNightmareDirectDamageEffect();
      ResolveGuardianAngelJoanBattleEffect();
      ResolveAirknightParshathDrawBattleEffect();
      ResolveNeedleBurrowerBattleEffect();
      ResolveHyperHammerheadBattleEffect();
      ResolveAbsorbingKidFromTheSkyBattleEffect();
      ResolveCoffinSellerBattleEffect();
      sub_8022080();
      FinishGraveyardDrawBattleResolve();
    } else {
      if (!TryPayTollAttackCost()) {
        PlayMusic(SFX_FORBIDDEN);
        gDuelCursor.state = 0;
        return;
      }
      if (IsTollActiveOnField())
        MarkCallOfTheHauntedAttackTollPaid();
      PlayMusic(SFX_ATTACK_REBUFFED);
      ActivateTrapEffect(0);
      TryResumeInterruptedAttackAfterCallOfTheHaunted();
      gDuelCursor.state = 0;
    }
    TryActivatingPermanentEffects();
    }
  } else {
    PlayMusic(SFX_SELECT);
    SelectZone(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
    gDuelCursor.state = 4;
    ResetCursorDestToCurrentPos();
    gDuelCursor.currentX = GetLastNonEmptyMonZoneId(&gFixedZones[1][4]);
    gDuelCursor.currentY = 1;
    RefreshPendingSasukeBattleTarget();
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    UpdateDuelGfxExceptField();
  }
}

LYN_REPLACE_CHECK(TryAttackWithMonster);
void TryAttackWithMonster__Replacement(void)
{
  if (gDuelCursor.currentY != 1) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else if (gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id == CARD_NONE) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else if (!DebugRuleset_CanAttackThisTurn() || !TheDarkDoor_CanAttackThisTurn()
      || !GravityBind_CanMonsterAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]->id)
      || !GoblinKing_CanBeAttacked(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])
      || !RaregoldArmor_CanBeAttacked(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else {
    gTrapEffectData.originRow = gDuelCursor.destY;
    gTrapEffectData.originCol = gDuelCursor.destX;
    gTrapEffectData.originCardId = gFixedZones[gDuelCursor.destY][gDuelCursor.destX]->id;
    TryActivateEmbodimentOfApophisOnAttack();
    if (IsTrapTriggered() != 1) {
      if (!TryPayTollAttackCost()) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
        return;
      }
      PlayMusic(SFX_SELECT);
      RefreshPendingSasukeBattleTarget();
      gFixedZones[gDuelCursor.destY][gDuelCursor.destX]->isDefending = 0;
      gFixedZones[gDuelCursor.destY][gDuelCursor.destX]->isFaceUp = 1;
      gFixedZones[gDuelCursor.destY][gDuelCursor.destX]->isLocked = 1;
      SetAttackAction(gDuelCursor.destX, gDuelCursor.currentX);
      TryApplyFairyBoxToPendingAction();
      TryApplyCatsEarTribeToPendingAction();
      RunMonsterBattleAction();
      if (gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id != CARD_NONE)
        gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isFaceUp = 1;
      DebugRuleset_MarkAttackUsed();
      TheDarkDoor_MarkAttackUsed();
      CheckGraveyardAndLoserFlags();
      TryUnlockHayabusaKnightForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockMermaidKnightForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockTryceEquipForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockTyrantDragonForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      gDuelCursor.state = 0;
      SetCursorToCardDest();
      sub_801BC00();
      UpdateAllDuelGfx();
      ResolveTheUnhappyMaidenBattleEffect();
      ResolveVampireBabyBattleEffect();
      ResolveMefistTheInfernalGeneralDiscardBattleEffect();
      ResolveReaperOnTheNightmareDirectDamageEffect();
      ResolveGuardianAngelJoanBattleEffect();
      ResolveAirknightParshathDrawBattleEffect();
      ResolveNeedleBurrowerBattleEffect();
      ResolveHyperHammerheadBattleEffect();
      ResolveAbsorbingKidFromTheSkyBattleEffect();
      ResolveCoffinSellerBattleEffect();
      sub_8022080();
      FinishGraveyardDrawBattleResolve();
    } else {
      if (!TryPayTollAttackCost()) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
        return;
      }
      if (IsTollActiveOnField())
        MarkCallOfTheHauntedAttackTollPaid();
      ActivateTrapEffect(0);
      TryResumeInterruptedAttackAfterCallOfTheHaunted();
      gDuelCursor.state = 0;
      SetCursorToCardDest();
      UpdateDuelGfxExceptField();
    }
    TryActivatingPermanentEffects();
  }
}

LYN_REPLACE_CHECK(HandleAButtonAction);
void HandleAButtonAction__Replacement(void)
{
  switch (gDuelCursor.state) {
    case 0:
      sub_80441D0__Replacement();
      break;
    case 1:
      TryPlaceSelectedCardOnField_Local();
      break;
    case 2:
      TrySelectSpellTarget();
      break;
    case DUEL_CURSOR_MST_TARGET:
      TrySelectMysticalSpaceTyphoonTarget();
      break;
    case DUEL_CURSOR_RIRYOKU_SOURCE:
      TrySelectRiryokuSourceTarget();
      break;
    case DUEL_CURSOR_RIRYOKU_RECIPIENT:
      TrySelectRiryokuRecipientTarget();
      break;
    case 4:
      TryAttackWithMonster();
      break;
    case DUEL_CURSOR_CANNON_SOLDIER_TARGET:
      TrySelectCannonSoldierTarget();
      break;
    case DUEL_CURSOR_DARK_MAGICIAN_KNIGHT_TARGET:
      TrySelectDarkMagicianKnightTarget();
      break;
    case DUEL_CURSOR_BLOCK_ATTACK_TARGET:
      TrySelectBlockAttackTarget();
      break;
    case DUEL_CURSOR_SOUL_TAKER_TARGET:
      TrySelectSoulTakerTarget();
      break;
    case DUEL_CURSOR_NEGATIVE_ENERGY_TARGET:
      TrySelectNegativeEnergyTarget();
      break;
    case DUEL_CURSOR_BOOK_OF_MOON_TARGET:
      TrySelectBookOfMoonTarget();
      break;
    case DUEL_CURSOR_KAISER_GLIDER_TARGET:
      TrySelectKaiserGliderTarget();
      break;
  }
}

LYN_REPLACE_CHECK(HandleBButtonAction);
void HandleBButtonAction__Replacement(void)
{
  switch (gDuelCursor.state) {
    case 0:
      OpenBMenu();
      break;
    case 1:
      sub_8044A30();
      break;
    case 2:
      sub_8044A5C();
      break;
    case DUEL_CURSOR_MST_TARGET:
      CancelMysticalSpaceTyphoonTargeting();
      break;
    case DUEL_CURSOR_RIRYOKU_SOURCE:
    case DUEL_CURSOR_RIRYOKU_RECIPIENT:
      CancelRiryokuTargeting();
      break;
    case DUEL_CURSOR_CANNON_SOLDIER_TARGET:
      PlayMusic(SFX_FORBIDDEN);
      WaitForVBlank();
      break;
    case DUEL_CURSOR_DARK_MAGICIAN_KNIGHT_TARGET:
      CancelDarkMagicianKnightTargeting();
      break;
    case DUEL_CURSOR_BLOCK_ATTACK_TARGET:
      CancelBlockAttackTargeting();
      break;
    case DUEL_CURSOR_SOUL_TAKER_TARGET:
      CancelSoulTakerTargeting();
      break;
    case DUEL_CURSOR_NEGATIVE_ENERGY_TARGET:
      CancelNegativeEnergyTargeting();
      break;
    case DUEL_CURSOR_BOOK_OF_MOON_TARGET:
      CancelBookOfMoonTargeting();
      break;
    case DUEL_CURSOR_KAISER_GLIDER_TARGET:
      CancelKaiserGliderTargeting();
      break;
    case 4:
      sub_8044A88();
      break;
  }
}
