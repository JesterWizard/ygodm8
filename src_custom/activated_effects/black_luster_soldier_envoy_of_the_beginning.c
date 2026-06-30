#include "global.h"
#include "common-chax.h"
#include "black_luster_soldier_envoy_of_the_beginning.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);
void sub_8022080(void);

extern const u8 gActivationDescription_BlackLusterSoldierEnvoyOfTheBeginning[];

#define BLS_BANISH_INDEX_NONE 0xFF

static u8 FixedDuelistYouControl(void)
{
  return WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
}

static u8 IsOnActiveDuelistMonsterRow(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gMonEffect.row == PLAYER_MONSTER_ROW;

  return gMonEffect.row == OPPONENT_MONSTER_ROW;
}

static u8 GraveyardMonsterHasAttribute(u16 cardId, u16 attribute)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == attribute;
}

static u8 FindGraveyardMonsterByAttribute(u8 fixedDuelist, u16 attribute, u8 skipIndex,
                                          u8 *outIndex)
{
  u8 i;
  u8 count;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (!GraveyardMonsterHasAttribute(cardId, attribute))
      return FALSE;

    *outIndex = 0;
    return TRUE;
  }

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    u16 cardId;

    if (skipIndex != BLS_BANISH_INDEX_NONE && i == skipIndex)
      continue;

    cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (!GraveyardMonsterHasAttribute(cardId, attribute))
      continue;

    *outIndex = i;
    return TRUE;
  }

  return FALSE;
}

static u8 GraveyardHasLightAndDarkMonsters(u8 fixedDuelist)
{
  u8 lightIndex;
  u8 darkIndex;

  if (!FindGraveyardMonsterByAttribute(fixedDuelist, ATTRIBUTE_LIGHT, BLS_BANISH_INDEX_NONE,
                                      &lightIndex))
    return FALSE;

  return FindGraveyardMonsterByAttribute(fixedDuelist, ATTRIBUTE_SHADOW, lightIndex, &darkIndex);
}

static void BanishGraveyardCardAt(u8 fixedDuelist, u8 index)
{
  if (GraveyardExpand_IsEnabled()) {
    GraveyardExpand_RemoveAtFixed(fixedDuelist, index);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    GraveyardExpand_RefreshDisplay();
    return;
  }

  gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
}

static u8 BanishLightAndDarkFromGraveyard(u8 fixedDuelist)
{
  u8 lightIndex;
  u8 darkIndex;

  if (!FindGraveyardMonsterByAttribute(fixedDuelist, ATTRIBUTE_LIGHT, BLS_BANISH_INDEX_NONE,
                                      &lightIndex))
    return FALSE;

  if (!FindGraveyardMonsterByAttribute(fixedDuelist, ATTRIBUTE_SHADOW, lightIndex, &darkIndex))
    return FALSE;

  if (lightIndex > darkIndex) {
    BanishGraveyardCardAt(fixedDuelist, lightIndex);
    BanishGraveyardCardAt(fixedDuelist, darkIndex);
  } else {
    BanishGraveyardCardAt(fixedDuelist, darkIndex);
    BanishGraveyardCardAt(fixedDuelist, lightIndex);
  }

  return TRUE;
}

u8 CanSpecialSummonBlackLusterSoldierEnvoyOfTheBeginningFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 fixedDuelist = FixedDuelistYouControl();

  if (handZone >= MAX_ZONES_IN_ROW)
    return FALSE;

  if (handRow[handZone]->id != BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return GraveyardHasLightAndDarkMonsters(fixedDuelist);
}

static void EnsureBlackLusterSoldierSummonedFaceUp(void)
{
  u8 col;
  struct DuelCard *zone;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    if (zone->id != BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING)
      continue;

    zone->isFaceUp = TRUE;
    zone->isDefending = FALSE;
    zone->isLocked = FALSE;
    UnlockCard(zone);
    Duel_NotifyMonsterZoneChanged(zone);
    return;
  }
}

u8 TrySpecialSummonBlackLusterSoldierEnvoyOfTheBeginningFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistYouControl();

  if (!CanSpecialSummonBlackLusterSoldierEnvoyOfTheBeginningFromHand(handZone))
    return FALSE;

  if (!BanishLightAndDarkFromGraveyard(fixedDuelist))
    return FALSE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  EnsureBlackLusterSoldierSummonedFaceUp();
  BlockTurnSummoning(ACTIVE_DUELIST);
  return TRUE;
}

static u8 IsBanishableMonsterZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != PLAYER_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 FindFirstBanishTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsBanishableMonsterZone(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void BanishTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *targetZone;

  if (!IsBanishableMonsterZone(fixedRow, fixedCol))
    return;

  targetZone = gFixedZones[fixedRow][fixedCol];
  if (Duel_BanishZone(targetZone, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
}

static void ShowBlackLusterSoldierActivationText(void)
{
  if (gHideEffectText)
    return;

  ResetCardEffectTextData();
  gCardEffectTextData.cardId = BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING;
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041C94((u8 *)gActivationDescription_BlackLusterSoldierEnvoyOfTheBeginning,
              BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING, CARD_NONE, 0, 0);
  SetCardInfo(BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING);
  PlayMusic(SFX_SPELL_ACTIVATION_END);
  sub_8022080();
}

static void BeginBlackLusterSoldierEnvoyTargeting(void)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstBanishTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;
  gDuelCursor.state = DUEL_CURSOR_BLACK_LUSTER_SOLDIER_ENVOY_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(gMonEffect.row, targetRow);
}

static void ResolveBlackLusterSoldierEnvoyEffectForAi(void)
{
  u8 targetRow;
  u8 targetCol;
  u8 bestRow = 0xFF;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;

      if (!IsBanishableMonsterZone(row, col))
        continue;

      zone = gFixedZones[row][col];
      SetCardInfo(zone->id);
      if (bestRow == 0xFF || gCardInfo.atk > bestAtk) {
        bestRow = row;
        bestCol = col;
        bestAtk = gCardInfo.atk;
      }
    }
  }

  if (bestRow == 0xFF)
    return;

  targetRow = bestRow;
  targetCol = bestCol;

  if (Duel_MonsterEffectConfirmTargetForAi(BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING, targetRow,
                                           targetCol))
    return;

  BanishTarget(targetRow, targetCol);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateBlackLusterSoldierEnvoyOfTheBeginning(void)
{
  struct DuelCard *zone;
  u8 unusedRow;
  u8 unusedCol;

  if (gMonEffect.id != BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING)
    return FALSE;

  if (!IsOnActiveDuelistMonsterRow())
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FindFirstBanishTarget(&unusedRow, &unusedCol);
}

void ActivateBlackLusterSoldierEnvoyOfTheBeginningEffect(void)
{
  ShowBlackLusterSoldierActivationText();

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    BeginBlackLusterSoldierEnvoyTargeting();
    return;
  }

  ResolveBlackLusterSoldierEnvoyEffectForAi();
}

void TrySelectBlackLusterSoldierEnvoyTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsBanishableMonsterZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  BanishTarget(targetRow, targetCol);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = originRow;
  gDuelCursor.currentX = originCol;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void CancelBlackLusterSoldierEnvoyTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}
