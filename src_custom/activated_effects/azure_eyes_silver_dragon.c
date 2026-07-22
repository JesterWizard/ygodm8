#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "azure_eyes_silver_dragon.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsOwnFaceUpDragon(u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[ACTIVE_DUELIST_MONSTER_ROW][fixedCol];

  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardHasMonsterType(zone->id, TYPE_DRAGON))
    return FALSE;

  return IsCardFaceUp(zone) || zone->isDefending == FALSE;
}

static u8 FieldHasOwnDragon(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOwnFaceUpDragon(col))
      return TRUE;
  }

  return FALSE;
}

static u8 MarkOwnDragonsProtected(void)
{
  u8 col;
  u8 marked = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (!IsOwnFaceUpDragon(col) || zone == NULL)
      continue;

    zone->unk4 |= 0x80;
    marked = TRUE;
  }

  return marked;
}

static u8 ControllerHasFaceUpAzureEyes(u8 fixedDuelist)
{
  u8 row = Duel_FixedMonsterRowForDuelist(fixedDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == AZURE_EYES_SILVER_DRAGON)
      return TRUE;
  }

  return FALSE;
}

static u8 IsProtectedOwnDragon(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;
  u8 fixedDuelist;

  if (zone == NULL || zone->id == AZURE_EYES_SILVER_DRAGON)
    return FALSE;

  if (!Duel_CardHasMonsterType(zone->id, TYPE_DRAGON))
    return FALSE;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &fixedCol))
    return FALSE;

  fixedDuelist = Duel_FixedDuelistForMonsterRow(fixedRow);
  if (zone->unk4 & 0x80)
    return TRUE;

  return ControllerHasFaceUpAzureEyes(fixedDuelist);
}

u8 AzureEyesSilverDragon_PreventsBattleDestroy(const struct DuelCard *zone)
{
  return zone != NULL && zone->isFaceUp && IsProtectedOwnDragon(zone);
}

u8 AzureEyesSilverDragon_PreventsDestroy(const struct DuelCard *zone)
{
  return IsProtectedOwnDragon(zone);
}

static u8 IsNormalMonsterId(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.monsterEffect == MONSTER_EFFECT_NONE;
}

static s16 FindNormalMonsterInOwnGy(void)
{
  u8 fixedDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER]
      ? DUEL_PLAYER
      : DUEL_OPPONENT;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsNormalMonsterId(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard))
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsNormalMonsterId(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s16)i;
  }

  return -1;
}

static enum DuelActionResult SpecialSummonNormalFromOwnGy(s16 gyIndex, u16 cardId)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER]
      ? DUEL_PLAYER
      : DUEL_OPPONENT;

  if (!GraveyardExpand_IsEnabled()) {
    if (!IsNormalMonsterId(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
  }

  if (gyIndex < 0)
    return DUEL_ACTION_NO_TARGET;

  if (GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex) != cardId)
    return DUEL_ACTION_NO_TARGET;

  GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

void TryClearAzureEyesSilverDragonProtectEndPhase(void)
{
  u8 fixedRow;
  u8 col;

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_MONSTER_ROW; fixedRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[fixedRow][col];

      if (zone != NULL && (zone->unk4 & 0x80))
        zone->unk4 &= (u8)~0x80;
    }
  }
}

void TryApplyAzureEyesSilverDragonStandby(void)
{
  u8 col;
  struct DuelCard *azure = NULL;
  s16 gyIndex;
  u16 normalId;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->isFaceUp && zone->id == AZURE_EYES_SILVER_DRAGON) {
      azure = zone;
      break;
    }
  }

  if (azure == NULL || !CanUseMonsterEffect(azure))
    return;

  gyIndex = FindNormalMonsterInOwnGy();
  if (gyIndex < 0)
    return;

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  if (!GraveyardExpand_IsEnabled())
    normalId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
  else {
    u8 fixedDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER]
        ? DUEL_PLAYER
        : DUEL_OPPONENT;

    normalId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  }

  Duel_ShowEffectTextTyped(AZURE_EYES_SILVER_DRAGON, 9);

  if (SpecialSummonNormalFromOwnGy(gyIndex, normalId) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(azure);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateAZURE_EYES_SILVER_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AZURE_EYES_SILVER_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AZURE_EYES_SILVER_DRAGON)
    return FALSE;

  /* Dragon battle/effect protect via AzureEyesSilverDragon_Prevents*; EP clear via
   * TryClearAzureEyesSilverDragonProtectEndPhase. Standby Normal SS wired. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasOwnDragon();
}

void ActivateAZURE_EYES_SILVER_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(AZURE_EYES_SILVER_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!MarkOwnDragonsProtected())
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
