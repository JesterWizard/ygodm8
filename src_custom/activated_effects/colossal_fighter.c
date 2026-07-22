#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "colossal_fighter.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define COLOSSAL_FIGHTER_ATK_PER_WARRIOR 100

static u8 sColossalInit APPEND_DATA = {0};

static u8 IsWarriorMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  return Duel_CardHasMonsterType(cardId, TYPE_WARRIOR);
}

static u8 CountWarriorsInGy(u8 fixedDuelist)
{
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsWarriorMonster(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 1;
    return 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsWarriorMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }
  return count;
}

static u8 CountWarriorsInAnyGy(void)
{
  return (u8)(CountWarriorsInGy(DUEL_PLAYER) + CountWarriorsInGy(DUEL_OPPONENT));
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

static u8 FindWarriorGySource(u8 preferred, u8 *outFixed, s8 *outGy)
{
  s8 gy = FindBestWarriorGyIndex(preferred);

  if (gy >= 0) {
    *outFixed = preferred;
    *outGy = gy;
    return TRUE;
  }
  preferred = (u8)(1 - preferred);
  gy = FindBestWarriorGyIndex(preferred);
  if (gy >= 0) {
    *outFixed = preferred;
    *outGy = gy;
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
    return Duel_SpecialSummonFromGrave(
        (gTurnDuelistBattleState[ACTIVE_DUELIST]
         == &gDuel.duelistbattleState[fixedDuelist])
            ? ACTIVE_DUELIST
            : INACTIVE_DUELIST,
        cardId, opts);
  }

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  return Duel_SpecialSummonMonsterId(
      (gTurnDuelistBattleState[ACTIVE_DUELIST]
       == &gDuel.duelistbattleState[fixedDuelist])
          ? ACTIVE_DUELIST
          : INACTIVE_DUELIST,
      cardId, opts);
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static void TryColossalBattleDestroySs(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  u8 srcFixed;
  s8 gyIndex;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;
  if (!FindWarriorGySource(fixedDuelist, &srcFixed, &gyIndex))
    return;

  Duel_ShowEffectTextTyped(COLOSSAL_FIGHTER, 2);
  if (IsDuelOver() == TRUE)
    return;

  if (SpecialSummonWarriorFromGy(srcFixed, gyIndex) != DUEL_ACTION_OK)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void OnColossalBattleDestroyed(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != COLOSSAL_FIGHTER)
    return;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return;

  TryColossalBattleDestroySs(ev->controller);
}

void ColossalFighter_EnsureInit(void)
{
  if (sColossalInit)
    return;
  sColossalInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnColossalBattleDestroyed);
}

u8 ColossalFighter_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;

  if (zone == NULL || zone->id != COLOSSAL_FIGHTER)
    return FALSE;

  SetCardInfo(zone->id);
  atk = Duel_StatFromCount(CountWarriorsInAnyGy(), COLOSSAL_FIGHTER_ATK_PER_WARRIOR,
                           gCardInfo.atk);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

unsigned char CanActivateCOLOSSAL_FIGHTER(void)
{
  if (gMonEffect.id != COLOSSAL_FIGHTER)
    return FALSE;

  /* ATK overlay via ColossalFighter_ApplyDynamicZoneStats;
   * battle-destroy SS via ColossalFighter_EnsureInit. */
  return FALSE;
}

void ActivateCOLOSSAL_FIGHTEREffect(void)
{
  Duel_ShowEffectTextTyped(COLOSSAL_FIGHTER, 2);
}
