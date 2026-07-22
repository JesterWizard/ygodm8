#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/card_effect_texts.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(u8);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 GetOwnerFixedDuelist(void)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return DUEL_PLAYER;
  return DUEL_OPPONENT;
}

static u8 GraveyardCardIsDarkMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_SHADOW;
}

static u8 CountDarkMonstersInGraveyard(u8 fixedDuelist)
{
  u8 i;
  u8 darkCount = 0;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (GraveyardCardIsDarkMonster(cardId))
      return 1;
    return 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++)
  {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (GraveyardCardIsDarkMonster(cardId))
      darkCount++;
  }
  return darkCount;
}

static u8 FindDarkMonsterInGraveyard(u8 fixedDuelist, u8 *outIndex)
{
  u8 i;
  u8 count;

  if (!GraveyardExpand_IsEnabled())
  {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (GraveyardCardIsDarkMonster(cardId))
    {
      *outIndex = 0;
      return TRUE;
    }
    return FALSE;
  }

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++)
  {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (GraveyardCardIsDarkMonster(cardId))
    {
      *outIndex = i;
      return TRUE;
    }
  }
  return FALSE;
}

static void EnsureDarkArmedDragonSummonedFaceUp(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone->id != DARK_ARMED_DRAGON)
      continue;

    zone->isFaceUp = TRUE;
    zone->isDefending = FALSE;
    zone->isLocked = FALSE;
    UnlockCard(zone);
    Duel_NotifyMonsterZoneChanged(zone);
    return;
  }
}

u8 CanSpecialSummonDarkArmedDragonFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != DARK_ARMED_DRAGON)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  return CountDarkMonstersInGraveyard(fixedDuelist) == 3;
}

u8 TrySpecialSummonDarkArmedDragonFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;

  if (!CanSpecialSummonDarkArmedDragonFromHand(handZone))
    return FALSE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  EnsureDarkArmedDragonSummonedFaceUp();
  BlockTurnSummoning(ACTIVE_DUELIST);
  return TRUE;
}

static u8 IsOnActiveDuelistMonsterRow(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gMonEffect.row == PLAYER_MONSTER_ROW;

  return gMonEffect.row == OPPONENT_MONSTER_ROW;
}

static u8 GraveyardHasDarkMonster(void)
{
  u8 unusedIndex;
  return FindDarkMonsterInGraveyard(GetOwnerFixedDuelist(), &unusedIndex);
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow > PLAYER_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  /* Ceiling: allow self-target for faithful TCG simulation;
     player can choose suboptimally */
  return TRUE;
}

static u8 FieldHasTarget(void)
{
  u8 row;
  u8 col;

  for (row = 0; row <= PLAYER_BACKROW; row++)
  {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++)
    {
      if (IsValidTarget(row, col))
        return TRUE;
    }
  }
  return FALSE;
}

static u8 GraveyardDuelistForTarget(u8 fixedRow)
{
  if (fixedRow == OPPONENT_BACKROW || fixedRow == OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *targetZone;

  targetZone = gFixedZones[fixedRow][fixedCol];
  if (Duel_DestroyZone(targetZone, GraveyardDuelistForTarget(fixedRow), FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static u8 ScoreTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (zone->id == CARD_NONE)
    return 0;

  /* prioritize opponent's cards */
  if (fixedRow == ACTIVE_DUELIST_MONSTER_ROW || fixedRow == ACTIVE_DUELIST_BACKROW)
    return 50;

  SetCardInfo(zone->id);
  if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
    return 100 + gCardInfo.atk;

  /* backrow: score 80 as baseline */
  return 80;
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;
  u8 bestRow = 0xFF;
  u8 bestCol = 0xFF;
  u8 bestScore = 0;

  for (row = 0; row <= PLAYER_BACKROW; row++)
  {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++)
    {
      u8 score;

      if (!IsValidTarget(row, col))
        continue;

      score = ScoreTarget(row, col);
      if (score > bestScore)
      {
        bestScore = score;
        bestRow = row;
        bestCol = col;
      }
    }
  }

  if (bestRow == 0xFF)
    return FALSE;

  *outRow = bestRow;
  *outCol = bestCol;
  return TRUE;
}

unsigned char CanActivateDARK_ARMED_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DARK_ARMED_DRAGON)
    return FALSE;

  if (!IsOnActiveDuelistMonsterRow())
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  /* need at least one DARK monster in GY for cost */
  if (!GraveyardHasDarkMonster())
    return FALSE;

  /* need at least one target on the field */
  return FieldHasTarget();
}

void ActivateDARK_ARMED_DRAGONEffect(void)
{
  u8 ownerFixed = GetOwnerFixedDuelist();
  u8 banishIndex;
  u8 bestRow, bestCol;

  Duel_ShowCardEffectText(DARK_ARMED_DRAGON, CARD_EFFECT_TEXT_DARK_ARMED_DRAGON_POPUP_1);

  if (IsDuelOver() == TRUE)
    return;

  /* Cost: banish 1 DARK monster from own GY (auto-picks first found) */
  if (!FindDarkMonsterInGraveyard(ownerFixed, &banishIndex))
    return;

  Duel_BanishGraveyardAtFixed(ownerFixed, banishIndex);
  GraveyardExpand_RefreshDisplay();
  UpdateDuelGfxExceptField();

  if (IsDuelOver() == TRUE)
    return;

  /* Ceiling: auto-target. No GY picker (DeckMenu screen switch corrupts VRAM
     from inside monster effect handler) and no PickZone cursor state (200
     conflicts with game loop after MonsterActionMenu case 4 returns).
     Picks the best field target via AiPickTarget logic.
     Upgrade path: dedicated cursor state + A/B handlers like Cannon Soldier. */

  /* Find best target (AiPickTarget prefers opponent's, then higher ATK) */
  if (!AiPickTarget(&bestRow, &bestCol))
    return;

  ResolveDestroyTarget(bestRow, bestCol);
}
