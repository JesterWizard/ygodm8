#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 OwnBackrowFixed(void)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return PLAYER_BACKROW;

  return OPPONENT_BACKROW;
}

static u8 IsAmazonessWarriorMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_IsAmazonessCard(cardId))
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_WARRIOR);
}

static s8 FindAmazonessWarriorGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsAmazonessWarriorMonster(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsAmazonessWarriorMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 IsOwnAmazonessFieldTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != gMonEffect.row && fixedRow != OwnBackrowFixed())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return Duel_IsAmazonessCard(zone->id);
}

static u8 HasOwnAmazonessFieldTarget(void)
{
  u8 col;
  u8 backRow = OwnBackrowFixed();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOwnAmazonessFieldTarget(gMonEffect.row, col))
      return TRUE;
    if (IsOwnAmazonessFieldTarget(backRow, col))
      return TRUE;
  }

  return FALSE;
}

static enum DuelActionResult SpecialSummonAmazonessWarriorFromGy(s8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsAmazonessWarriorMonster(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsAmazonessWarriorMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s8 gyIndex;

  if (!IsOwnAmazonessFieldTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  gyIndex = FindAmazonessWarriorGyIndex(FixedDuelistForActive());
  if (gyIndex < 0)
    return;

  if (SpecialSummonAmazonessWarriorFromGy(gyIndex) == DUEL_ACTION_DUEL_OVER)
    return;

  /* Cannot attack this turn: isLocked honored by attack validators. */
  self->unk4 |= 0x80;
  self->isLocked = TRUE;
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 backRow = OwnBackrowFixed();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOwnAmazonessFieldTarget(gMonEffect.row, col)) {
      *outRow = gMonEffect.row;
      *outCol = col;
      return TRUE;
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOwnAmazonessFieldTarget(backRow, col)) {
      *outRow = backRow;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateAMAZONESS_PET_LIGER_KING(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AMAZONESS_PET_LIGER_KING)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AMAZONESS_PET_LIGER_KING)
    return FALSE;

  /* OPT destroy Amazoness → SS Warrior GY via Activate.
   * attack redirect FALSE. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!HasOwnAmazonessFieldTarget())
    return FALSE;

  return FindAmazonessWarriorGyIndex(FixedDuelistForActive()) >= 0;
}

void ActivateAMAZONESS_PET_LIGER_KINGEffect(void)
{
  Duel_ShowEffectTextTyped(AMAZONESS_PET_LIGER_KING, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsOwnAmazonessFieldTarget, ResolveDestroyTarget, CancelTargeting,
                     AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
