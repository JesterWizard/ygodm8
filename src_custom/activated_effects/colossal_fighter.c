#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsWarriorMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_WARRIOR);
}

static s8 FindBestWarriorGyIndex(u8 fixedDuelist)
{
  u8 i;
  s8 bestIndex = -1;
  u16 bestAtk = 0;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsWarriorMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return 0;

    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    u16 atk;

    if (!IsWarriorMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

    SetCardInfo(cardId);
    atk = gCardInfo.atk;
    if (bestIndex < 0 || atk > bestAtk) {
      bestAtk = atk;
      bestIndex = (s8)i;
    }
  }

  return bestIndex;
}

static u8 FindWarriorGySource(u8 *outFixedDuelist, s8 *outGyIndex)
{
  u8 fixedDuelist;
  s8 gyIndex;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    fixedDuelist = DUEL_PLAYER;
  else
    fixedDuelist = DUEL_OPPONENT;

  gyIndex = FindBestWarriorGyIndex(fixedDuelist);
  if (gyIndex >= 0) {
    *outFixedDuelist = fixedDuelist;
    *outGyIndex = gyIndex;
    return TRUE;
  }

  fixedDuelist = (u8)(1 - fixedDuelist);
  gyIndex = FindBestWarriorGyIndex(fixedDuelist);
  if (gyIndex >= 0) {
    *outFixedDuelist = fixedDuelist;
    *outGyIndex = gyIndex;
    return TRUE;
  }

  return FALSE;
}

static enum DuelActionResult SpecialSummonWarriorFromGy(u8 fixedDuelist, s8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    if (!IsWarriorMonster(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsWarriorMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

unsigned char CanActivateCOLOSSAL_FIGHTER(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist;
  s8 gyIndex;

  if (gMonEffect.id != COLOSSAL_FIGHTER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != COLOSSAL_FIGHTER)
    return FALSE;

  /* ponytail: +100 ATK per Warrior in any GY needs stat overlay; battle-destroy
   * trigger deferred. Ceiling: OPT SS 1 Warrior from either GY once via usage. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!FindWarriorGySource(&fixedDuelist, &gyIndex))
    return FALSE;

  (void)fixedDuelist;
  (void)gyIndex;
  return TRUE;
}

void ActivateCOLOSSAL_FIGHTEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist;
  s8 gyIndex;

  Duel_ShowEffectTextTyped(COLOSSAL_FIGHTER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!FindWarriorGySource(&fixedDuelist, &gyIndex))
    return;

  if (SpecialSummonWarriorFromGy(fixedDuelist, gyIndex) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
