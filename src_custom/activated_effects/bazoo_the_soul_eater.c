#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

#define BAZOO_MAX_BANISH 3

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 GyMonsterCount(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    return (cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER) ? 1 : 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GetTypeGroup(GraveyardExpand_GetCardAt(fixedDuelist, i)) == TYPE_GROUP_MONSTER)
      count++;
  }

  return count;
}

static u8 BanishUpToThreeGyMonsters(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 banished = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      return 0;

    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return 1;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0 && banished < BAZOO_MAX_BANISH; i--) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);

    if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;

    Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1);
    banished++;
  }

  return banished;
}

unsigned char CanActivateBAZOO_THE_SOUL_EATER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != BAZOO_THE_SOUL_EATER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != BAZOO_THE_SOUL_EATER)
    return FALSE;

  return CanUseMonsterEffect(zone) && GyMonsterCount() > 0;
}

void ActivateBAZOO_THE_SOUL_EATEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 banished;

  Duel_ShowEffectTextTyped(BAZOO_THE_SOUL_EATER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  banished = BanishUpToThreeGyMonsters();
  if (banished == 0)
    return;

  /* ponytail: +1 tempStage per banished (~500 ATK each, not exact +300); until
   * opp EP clear needs EP tempStage reset hook. */
  if (self->tempStage < 127 - (s8)banished)
    self->tempStage += (s8)banished;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}
