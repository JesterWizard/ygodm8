#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

extern const CardData gCardData_NEW[];

void RefreshFieldMonsterStatOverlays(void);

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDragonMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_DRAGON);
}

static u16 FindFirstDragonInGraveyard(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsDragonMonster(top))
      return top;
    return CARD_NONE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsDragonMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static void ApplyAtkFromDragonOriginalAtk(struct DuelCard *zone, u16 dragonId)
{
  u32 baseAtk = gCardData_NEW[zone->id].atk;
  u32 targetAtk = gCardData_NEW[dragonId].atk;
  s8 stages;

  if (targetAtk <= baseAtk)
    return;

  stages = (s8)((targetAtk - baseAtk + 499) / 500);
  if (stages > 126)
    stages = 126;

  while (stages--)
    IncrementTempStage(zone);
}

unsigned char ShouldActivateDEEP_EYES_WHITE_DRAGON(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != DEEP_EYES_WHITE_DRAGON)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = SelfZone();
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  /* Printed remainder omitted by this ruleset. */
  return FindFirstDragonInGraveyard(duelist) != CARD_NONE;
}

void ActivateDEEP_EYES_WHITE_DRAGON(void)
{
  u8 duelist;
  struct DuelCard *zone;
  u16 dragonId;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  zone = SelfZone();

  Duel_ShowEffectTextTyped(DEEP_EYES_WHITE_DRAGON, 8);
  if (IsDuelOver() == TRUE)
    return;

  dragonId = FindFirstDragonInGraveyard(duelist);
  if (zone != NULL && dragonId != CARD_NONE) {
    ApplyAtkFromDragonOriginalAtk(zone, dragonId);
    RefreshFieldMonsterStatOverlays();
    zone->unk4 = 1;
  }
  /* Printed remainder omitted by this ruleset. */
}
