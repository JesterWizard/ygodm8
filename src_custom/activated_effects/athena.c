#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "athena.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

extern unsigned char IsSkillDrainActiveOnField(void);
extern unsigned char TryActivateSkillDrainAndNegateCardId(u16 negatedCardId);
void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
extern void UpdateDuelGfxExceptField(void);
extern void CheckWinConditionExodia(void);
extern void TryActivatingPermanentEffects(void);

#define ATHENA_BURN_DAMAGE 600

static const u8 sAthenaPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForMonsterFixedRow(u8 fixedRow)
{
  if (fixedRow == PLAYER_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;

  if (fixedRow == OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return ACTIVE_DUELIST;
}

static u8 OpponentOfTurnDuelist(u8 turnDuelist)
{
  return turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;
}

static u8 IsFairyMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].type == TYPE_FAIRY;
}

static u8 IsFaceUpMonsterZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  /* Attack-position summons stay isFaceUp=0 until end-of-turn flip. */
  return zone->isDefending == FALSE;
}

static u8 IsTargetableGyFairy(u16 cardId)
{
  return IsFairyMonster(cardId) && cardId != ATHENA;
}

static u8 IsFaceUpFairyCostTarget(struct DuelCard *zone, struct DuelCard *athenaZone)
{
  if (zone == NULL || zone == athenaZone || zone->id == CARD_NONE)
    return FALSE;

  if (zone->id == ATHENA || !IsFaceUpMonsterZone(zone))
    return FALSE;

  return IsFairyMonster(zone->id);
}

static u8 HasFaceUpAthenaForFixedDuelist(u8 fixedDuelist)
{
  u8 monsterRow = Duel_FixedMonsterRowForDuelist(fixedDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[monsterRow][col];

    if (zone->id == ATHENA && IsFaceUpMonsterZone(zone))
      return TRUE;
  }

  return FALSE;
}

static u8 GraveyardHasTargetableFairy(u8 fixedDuelist)
{
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsTargetableGyFairy(cardId);
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsTargetableGyFairy(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 LoadTargetableGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsTargetableGyFairy(cardId))
      continue;

    gyIndexMap[menuCount] = i;
    gDeckMenu.cards[menuCount] = cardId;
    menuCount++;
  }

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  return menuCount;
}

static s8 FindBestTargetableGyIndexForAi(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 bestIndex = 0xFF;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    u16 atk;

    if (!IsTargetableGyFairy(cardId))
      continue;

    atk = gCardData_NEW[cardId].atk;
    if (bestIndex == 0xFF || atk > bestAtk) {
      bestAtk = atk;
      bestIndex = i;
    }
  }

  return (s8)bestIndex;
}

static s8 PlayerPickTargetableGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 j;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadTargetableGyMenu(fixedDuelist, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1) {
    chosenGyIndex = (s8)gyIndexMap[0];
    DECKMENU_RESTORE();
    return chosenGyIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sAthenaPickLabels, ARRAY_COUNT(sAthenaPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();

  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static enum DuelActionResult SpecialSummonTargetableFairyFromGrave(u8 turnDuelist, u8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[turnDuelist]->graveyard;
    if (!IsTargetableGyFairy(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(turnDuelist, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsTargetableGyFairy(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtTurn(turnDuelist, gyIndex);
  if (!IsTargetableGyFairy(cardId))
    return DUEL_ACTION_NO_TARGET;

  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
}

static void ResolveGySpecialSummon(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 gyIndex;

  if (!GraveyardHasTargetableFairy(fixedDuelist))
    return;

  if (WhoseTurn() == DUEL_PLAYER && GraveyardExpand_IsEnabled())
    gyIndex = PlayerPickTargetableGyIndex(fixedDuelist);
  else if (GraveyardExpand_IsEnabled())
    gyIndex = FindBestTargetableGyIndexForAi(fixedDuelist);
  else
    gyIndex = 0;

  if (gyIndex < 0)
    return;

  if (SpecialSummonTargetableFairyFromGrave(turnDuelist, (u8)gyIndex) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia();
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static struct DuelCard *AthenaSelfZone(void)
{
  return gFixedZones[gMonEffect.row][gMonEffect.zone];
}

static u8 IsValidCostTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *athenaZone = AthenaSelfZone();

  if (fixedRow != gMonEffect.row)
    return FALSE;

  return IsFaceUpFairyCostTarget(gFixedZones[fixedRow][fixedCol], athenaZone);
}

static u8 FindFirstCostTarget(u8 *outCol)
{
  u8 col;
  struct DuelCard *athenaZone = AthenaSelfZone();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsFaceUpFairyCostTarget(gFixedZones[gMonEffect.row][col], athenaZone))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 OwnerHasCostTarget(void)
{
  u8 unusedCol;

  return FindFirstCostTarget(&unusedCol);
}

static u8 CanResolveAthenaIgnition(u8 turnDuelist)
{
  u8 monsterRow = Duel_TurnMonsterRowForDuelist(turnDuelist);

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  return OwnerHasCostTarget();
}

static u8 AiPickCostCol(u8 *outCol)
{
  u8 col;
  struct DuelCard *athenaZone = AthenaSelfZone();
  u8 bestCol = 0xFF;
  u16 bestAtk = 0xFFFF;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[gMonEffect.row][col];
    u16 atk;

    if (!IsFaceUpFairyCostTarget(zone, athenaZone))
      continue;

    atk = gCardData_NEW[zone->id].atk;
    if (bestCol == 0xFF || atk < bestAtk) {
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  *outCol = bestCol;
  return TRUE;
}

static void ResolveCostTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u8 turnDuelist = TurnDuelistForMonsterFixedRow(gMonEffect.row);
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidCostTarget(fixedRow, fixedCol))
    return;

  zone = gFixedZones[fixedRow][fixedCol];
  if (Duel_DestroyZone(zone, turnDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  /* Printed remainder omitted by this ruleset.
   * crashing when the menu opened on confirm. */
  gDuelCursor.state = 0;
  gDuelCursor.currentY = originRow;
  gDuelCursor.currentX = originCol;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();

  ResolveGySpecialSummon(turnDuelist);
}

static void ResolveCostTargetForAi(void)
{
  u8 col;

  if (!AiPickCostCol(&col))
    return;

  ResolveCostTarget(gMonEffect.row, col);
}

static void BeginCostTargeting(void)
{
  u8 targetCol;

  if (!FindFirstCostTarget(&targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  UpdateDuelGfxExceptField();

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;
  PlayMusic(SFX_SELECT);
  gDuelCursor.state = DUEL_CURSOR_ATHENA_COST_TARGET;
  gDuelCursor.currentY = gMonEffect.row;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
}

void TrySelectAthenaCostTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!IsValidCostTarget(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  ResolveCostTarget(targetRow, targetCol);

  if (gDuelCursor.state != DUEL_CURSOR_ATHENA_COST_TARGET)
    return;

  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia();
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void CancelAthenaCostTargeting(void)
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

unsigned char CanActivateATHENA(void)
{
  struct DuelCard *zone = AthenaSelfZone();
  u8 turnDuelist;

  if (gMonEffect.id != ATHENA)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  if (zone->id != ATHENA || !IsFaceUpMonsterZone(zone) || !CanUseMonsterEffect(zone))
    return FALSE;

  turnDuelist = TurnDuelistForMonsterFixedRow(gMonEffect.row);
  return CanResolveAthenaIgnition(turnDuelist);
}

void ActivateATHENAEffect(void)
{
  Duel_ShowCardEffectText(ATHENA, CARD_EFFECT_TEXT_ATHENA_POPUP_2);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    BeginCostTargeting();
  else
    ResolveCostTargetForAi();
}

static void ApplyAthenaSummonBurn(u8 controllerTurnDuelist)
{
  u8 opponent = OpponentOfTurnDuelist(controllerTurnDuelist);

  Duel_ShowCardEffectText(ATHENA, CARD_EFFECT_TEXT_ATHENA_POPUP_1);

  if (IsDuelOver() == TRUE)
    return;

  if (IsSkillDrainActiveOnField() && TryActivateSkillDrainAndNegateCardId(ATHENA))
    return;

  if (Duel_ChangeLp(opponent, -ATHENA_BURN_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryAthenaOnMonsterPlacement(struct DuelCard *zone)
{
  u8 turnRow;
  u8 col;
  u8 turnDuelist;
  u8 fixedDuelist;

  if (zone == NULL || zone->id == CARD_NONE || zone->id == ATHENA)
    return;

  if (!IsFairyMonster(zone->id))
    return;

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return;

  turnDuelist = (turnRow == ACTIVE_DUELIST_MONSTER_ROW) ? ACTIVE_DUELIST : INACTIVE_DUELIST;
  fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (!HasFaceUpAthenaForFixedDuelist(fixedDuelist))
    return;

  ApplyAthenaSummonBurn(turnDuelist);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void Athena_SelfCheck(void)
{
  if (!IsFairyMonster(TINY_ANGEL))
    while (1)
      ;
  if (IsTargetableGyFairy(ATHENA))
    while (1)
      ;
}
#endif
