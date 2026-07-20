#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void SetCardInfo(unsigned short id);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDragonMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_DRAGON);
}

static u8 HighestDragonLevelInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 bestLevel = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (!IsDragonMonster(cardId))
      return 0;

    SetCardInfo(cardId);
    return gCardInfo.level;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsDragonMonster(cardId))
      continue;

    SetCardInfo(cardId);
    if (gCardInfo.level > bestLevel)
      bestLevel = gCardInfo.level;
  }

  return bestLevel;
}

static u8 OppHasMonsterLevelAtMost(u8 maxLevel)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    SetCardInfo(zone->id);
    if (gCardInfo.level <= maxLevel)
      return TRUE;
  }

  return FALSE;
}

static void DestroyOppMonstersLevelAtMost(u8 maxLevel)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    SetCardInfo(zone->id);
    if (gCardInfo.level > maxLevel)
      continue;

    if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }
}

unsigned char CanActivateARMED_NEOS(void)
{
  struct DuelCard *zone;
  u8 maxLevel;

  if (gMonEffect.id != ARMED_NEOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ARMED_NEOS)
    return FALSE;

  /* ponytail: battle-destroy gain Extra tribute SS need battle/Extra hooks.
   * Ceiling: OPT destroy opp monsters with Level ≤ highest Dragon Level in GY. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  maxLevel = HighestDragonLevelInGy();
  if (maxLevel == 0)
    return FALSE;

  return OppHasMonsterLevelAtMost(maxLevel);
}

void ActivateARMED_NEOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 maxLevel;

  Duel_ShowEffectTextTyped(ARMED_NEOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  maxLevel = HighestDragonLevelInGy();
  if (maxLevel == 0)
    return;

  DestroyOppMonstersLevelAtMost(maxLevel);
  if (IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
