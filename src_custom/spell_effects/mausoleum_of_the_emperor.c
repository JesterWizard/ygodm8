#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"

#define MAUSOLEUM_LP_PER_TRIBUTE 1000
#define MAUSOLEUM_LP_COST_MAX 2000

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
void BlockTurnSummoning(u8);
void UnlockCardsInRow(unsigned char);
void LockMonsterCardsInRow(unsigned char);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static u8 TributeCostForCard(u16 cardId)
{
  int tributes;

  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return 0;

  SetCardInfo(cardId);
  if (gCardInfo.color != COLOR_NORMAL && gCardInfo.color != COLOR_EFFECT)
    return 0;

  tributes = GetNumRequiredTributes(cardId);
  if (tributes <= 0)
    return 0;
  if (tributes > 2)
    tributes = 2;

  return (u8)tributes;
}

static u32 LpCostForTributes(u8 tributes)
{
  u32 cost = (u32)tributes * MAUSOLEUM_LP_PER_TRIBUTE;

  if (cost > MAUSOLEUM_LP_COST_MAX)
    cost = MAUSOLEUM_LP_COST_MAX;
  return cost;
}

static u8 CanPayMausoleumCost(u8 tributes)
{
  u32 cost = LpCostForTributes(tributes);

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= cost;

  return gDuelLifePoints[DUEL_OPPONENT] >= cost;
}

static u8 IsMausoleumSummonTarget(u16 cardId)
{
  u8 tributes = TributeCostForCard(cardId);

  if (tributes == 0)
    return FALSE;

  return CanPayMausoleumCost(tributes);
}

static u8 HandHasMausoleumTarget(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsMausoleumSummonTarget(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 CanActivateMausoleumIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != MAUSOLEUM_OF_THE_EMPEROR || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!HandHasMausoleumTarget(gTurnHands[ACTIVE_DUELIST]))
    return FALSE;

  return TRUE;
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* TRUE = face-up Attack Normal Summon; FALSE = Set. */
static u8 PlayerChoosesNormalSummonFaceUp(void)
{
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return TRUE;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return FALSE;
    }

    WaitForVBlank();
  }
}

static s8 PickAiMausoleumHandZone(struct DuelCard **handRow)
{
  u8 i;
  s8 chosen = -1;
  u16 bestAtk = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = handRow[i]->id;
    u8 tributes = TributeCostForCard(cardId);

    if (tributes == 0 || !CanPayMausoleumCost(tributes))
      continue;

    SetCardInfo(cardId);
    if (chosen < 0 || gCardInfo.atk > bestAtk) {
      chosen = (s8)i;
      bestAtk = gCardInfo.atk;
    }
  }

  return chosen;
}

static void ResolveMausoleumIgnition(struct DuelCard *zone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  struct DuelSummonOpts opts = Duel_DefaultNormalSummonOpts(TRUE);
  s8 handZone;
  u16 cardId;
  u8 tributes;
  u8 faceUp;
  u8 relockHand = FALSE;

  if (!CanActivateMausoleumIgnition(zone))
    return;

  Duel_ShowEffectText(MAUSOLEUM_OF_THE_EMPEROR);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked) {
      UnlockCardsInRow(ACTIVE_DUELIST_HAND);
      relockHand = TRUE;
    }

    handZone = SelectHandCardMatchingPredicate(handRow, IsMausoleumSummonTarget);
    if (handZone < 0) {
      if (relockHand)
        LockMonsterCardsInRow(ACTIVE_DUELIST_HAND);
      return;
    }
  } else {
    handZone = PickAiMausoleumHandZone(handRow);
    if (handZone < 0)
      return;
  }

  cardId = handRow[handZone]->id;
  tributes = TributeCostForCard(cardId);
  if (tributes == 0 || !CanPayMausoleumCost(tributes)) {
    if (relockHand)
      LockMonsterCardsInRow(ACTIVE_DUELIST_HAND);
    return;
  }

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)LpCostForTributes(tributes), FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    faceUp = PlayerChoosesNormalSummonFaceUp();
  else
    faceUp = TRUE;

  if (!faceUp)
    opts.mode = DUEL_SUMMON_NORMAL_SET;

  /* Bypass tribute pay: place via hand-zone summon with Normal opts, then block NS. */
  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) == DUEL_ACTION_DUEL_OVER)
    return;

  BlockTurnSummoning(ACTIVE_DUELIST);
  zone->effectUsedThisTurn = TRUE;

  if (relockHand)
    LockMonsterCardsInRow(ACTIVE_DUELIST_HAND);

}

static void MAUSOLEUM_OF_THE_EMPEROR_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up continuous/field (OPT Main Phase ignition). */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivateMausoleumIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveMausoleumIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(MAUSOLEUM_OF_THE_EMPEROR);
if (CanActivateMausoleumIgnition(zone))
    ResolveMausoleumIgnition(zone);
}

APPEND_TEXT void EffectMAUSOLEUM_OF_THE_EMPEROR(void)
{
  if (Duel_TryResolveSpellThroughTraps(MAUSOLEUM_OF_THE_EMPEROR,
                                       MAUSOLEUM_OF_THE_EMPEROR_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MAUSOLEUM_OF_THE_EMPEROR_SelfCheck(void)
{
  if (TributeCostForCard(BLUE_EYES_WHITE_DRAGON) == 0)
    while (1)
      ;
  if (TributeCostForCard(DARK_MAGICIAN) == 0)
    while (1)
      ;
  if (TributeCostForCard(KURIBOH) != 0)
    while (1)
      ;
  if (LpCostForTributes(2) != MAUSOLEUM_LP_COST_MAX)
    while (1)
      ;
}
#endif
