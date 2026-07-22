#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "dust_tornado.h"
#include "duel_helpers.h"
#include "executor_makyura.h"
#include "expanded_graveyard.h"
#include "gravity_bind.h"
#include "imperial_order.h"
#include "jar_of_greed.h"
#include "ring_of_destruction.h"
#include "royal_decree.h"
#include "world_suppression.h"

void ActivateSpellEffect(void);
void CheckWinConditionExodia(unsigned char);
void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void TryActivatingPermanentEffects(void);
void UpdateDuelGfxExceptField(void);

extern u8 gExecutorMakyuraActivePlayer;
extern u8 gExecutorMakyuraActiveOpponent;
extern u8 gExecutorMakyuraPendingPopup;

static u8 *ExecutorMakyuraFlag(u8 fixedDuelist)
{
  if (fixedDuelist == DUEL_PLAYER)
    return &gExecutorMakyuraActivePlayer;

  return &gExecutorMakyuraActiveOpponent;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (turnDuelist == ACTIVE_DUELIST)
    return WhoseTurn();

  return WhoseTurn() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
}

void ResetExecutorMakyuraTurnState(void)
{
  gExecutorMakyuraActivePlayer = FALSE;
  gExecutorMakyuraActiveOpponent = FALSE;
  gExecutorMakyuraPendingPopup = FALSE;
}

void TryArmExecutorMakyuraOnGraveyardSendFixed(u8 fixedDuelist, u16 cardId)
{
  if (cardId != EXECUTOR_MAKYURA)
    return;

  if (fixedDuelist > DUEL_OPPONENT)
    return;

  *ExecutorMakyuraFlag(fixedDuelist) = TRUE;
  gExecutorMakyuraPendingPopup = TRUE;
}

void TryShowPendingExecutorMakyuraPopup(void)
{
  if (!gExecutorMakyuraPendingPopup)
    return;

  gExecutorMakyuraPendingPopup = FALSE;

  if (GraveyardExpand_IsEnabled())
    GraveyardExpand_RefreshDisplay();
  UpdateDuelGfxExceptField();

  if (!gHideEffectText)
    Duel_ShowCardEffectText(EXECUTOR_MAKYURA, CARD_EFFECT_TEXT_EXECUTOR_MAKYURA_POPUP_1);
}

void TryArmExecutorMakyuraOnGraveyardSend(u8 turnDuelist, u16 cardId)
{
  TryArmExecutorMakyuraOnGraveyardSendFixed(FixedDuelistForTurnDuelist(turnDuelist), cardId);
}

u8 IsExecutorMakyuraActiveForDuelist(u8 fixedDuelist)
{
  if (fixedDuelist > DUEL_OPPONENT)
    return FALSE;

  return *ExecutorMakyuraFlag(fixedDuelist);
}

static u8 TrapEffectAllowsMakyuraManualActivation(u8 trapEffect)
{
  // most non-zero trapEffect values are chain-only; allow continuous exceptions.
  if (trapEffect == 0)
    return TRUE;

  switch (trapEffect) {
  case TRAP_ROYAL_DECREE:
  case TRAP_IMPERIAL_ORDER:
  case TRAP_GRAVITY_BIND:
  case TRAP_WORLD_SUPPRESSION:
    return TRUE;
  default:
    return FALSE;
  }
}

static u8 TrapHasImmediateSpellEffectHandler(u16 trapId)
{
  switch (trapId) {
    case DUST_TORNADO:
    case RING_OF_DESTRUCTION:
    case JAR_OF_GREED:
    case NIGHTMARE_WHEEL:
    case SKULL_INVITATION:
    case COFFIN_SELLER:
    case BOTTOMLESS_SHIFTING_SAND:
    case LEVEL_LIMIT_AREA_A:
    case LEVEL_LIMIT_AREA_B:
    case R_RIGHTEOUS_JUSTICE:
      return TRUE;
    default:
      return FALSE;
  }
}

static u8 TrapNeedsMakyuraContinuousFlip(u16 trapId)
{
  switch (trapId) {
  case ROYAL_DECREE:
  case SOLEMN_WISHES:
  case SKILL_DRAIN:
  case MASK_OF_RESTRICT:
  case ULTIMATE_OFFERING:
  case IMPERIAL_ORDER:
    return TRUE;
  default:
    return FALSE;
  }
}

u8 CanPlayTrapFromHandViaMakyura(u16 trapId)
{
  if (GetTypeGroup(trapId) != TYPE_GROUP_TRAP)
    return FALSE;

  if (Duel_IsCardActivationBlocked(trapId))
    return FALSE;

  SetCardInfo(trapId);

  if (!TrapEffectAllowsMakyuraManualActivation(gCardInfo.trapEffect))
    return FALSE;

  if (TrapNeedsMakyuraContinuousFlip(trapId))
    return TRUE;

  if (GetSpellType(trapId) == SPELL_TYPE_NORMAL)
    return TRUE;

  return TrapHasImmediateSpellEffectHandler(trapId);
}

static u8 BeginMakyuraTrapTargeting(u16 trapId, u8 originFixedRow, u8 originFixedCol)
{
  if (trapId == DUST_TORNADO) {
    if (!FieldHasDustTornadoTarget(originFixedRow, originFixedCol))
      return FALSE;

    BeginDustTornadoTargeting(originFixedRow, originFixedCol);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return TRUE;
  }

  if (trapId == RING_OF_DESTRUCTION) {
    if (!CanActivateRingOfDestruction()
        || !FieldHasRingOfDestructionTarget(originFixedRow, originFixedCol))
      return FALSE;

    BeginRingOfDestructionTargeting(originFixedRow, originFixedCol);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return TRUE;
  }

  return FALSE;
}

static void ActivateMakyuraContinuousTrap(struct DuelCard *zone, u16 trapId)
{
  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectTextTyped(trapId, 3);
}

static void FinishMakyuraTrapActivation(u16 trapId, u8 originFixedRow, u8 originFixedCol)
{
  struct DuelCard *originZone = gFixedZones[originFixedRow][originFixedCol];

  if (trapId == JAR_OF_GREED) {
    ActivateJarOfGreedFromZone(originZone, ACTIVE_DUELIST);
  } else if (TrapNeedsMakyuraContinuousFlip(trapId)) {
    ActivateMakyuraContinuousTrap(originZone, trapId);
  } else {
    gSpellEffectData.id = trapId;
    gSpellEffectData.row1 = originFixedRow;
    gSpellEffectData.col1 = originFixedCol;
    ActivateSpellEffect();
  }

  if (gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked)
    LockMonsterCardsInRow(4);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());

  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static u8 TryActivateExecutorMakyuraTrapFromZone(u8 originFixedRow, u8 originFixedCol)
{
  u16 trapId;
  struct DuelCard *originZone;

  if (!IsExecutorMakyuraActiveForDuelist(WhoseTurn()))
    return FALSE;

  originZone = gFixedZones[originFixedRow][originFixedCol];
  trapId = originZone->id;

  if (GetTypeGroup(trapId) != TYPE_GROUP_TRAP)
    return FALSE;

  if (originZone->isFaceUp)
    return FALSE;

  if (!CanPlayTrapFromHandViaMakyura(trapId))
    return FALSE;

  if (BeginMakyuraTrapTargeting(trapId, originFixedRow, originFixedCol))
    return TRUE;

  FinishMakyuraTrapActivation(trapId, originFixedRow, originFixedCol);
  return TRUE;
}

u8 TryActivateExecutorMakyuraTrapFromBackrow(u8 fixedRow, u8 fixedCol)
{
  return TryActivateExecutorMakyuraTrapFromZone(fixedRow, fixedCol);
}
