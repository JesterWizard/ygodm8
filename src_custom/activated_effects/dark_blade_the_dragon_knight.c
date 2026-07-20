#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForInactive(void)
{
  if (gTurnDuelistBattleState[INACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

unsigned char CanActivateDARK_BLADE_THE_DRAGON_KNIGHT(void)
{
  struct DuelCard *zone;
  u8 fixedOpp;
  u8 i;

  if (gMonEffect.id != DARK_BLADE_THE_DRAGON_KNIGHT)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DARK_BLADE_THE_DRAGON_KNIGHT)
    return FALSE;

  /* ponytail: battle-damage trigger. Ceiling: once via usage if opp GY has
   * monsters. */
  if (!CanUseMonsterEffect(zone) || !GraveyardExpand_IsEnabled())
    return FALSE;

  fixedOpp = FixedDuelistForInactive();
  for (i = 0; i < GraveyardExpand_GetCount(fixedOpp); i++) {
    if (GetTypeGroup(GraveyardExpand_GetCardAt(fixedOpp, i)) == TYPE_GROUP_MONSTER)
      return TRUE;
  }

  return FALSE;
}

void ActivateDARK_BLADE_THE_DRAGON_KNIGHTEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedOpp = FixedDuelistForInactive();
  u8 banished = 0;
  u8 i;

  Duel_ShowEffectTextTyped(DARK_BLADE_THE_DRAGON_KNIGHT, 2);

  if (self == NULL || IsDuelOver() == TRUE || !GraveyardExpand_IsEnabled())
    return;

  for (i = GraveyardExpand_GetCount(fixedOpp); i > 0 && banished < 3; i--) {
    if (GetTypeGroup(GraveyardExpand_GetCardAt(fixedOpp, i - 1)) != TYPE_GROUP_MONSTER)
      continue;
    Duel_BanishGraveyardAtFixed(fixedOpp, i - 1);
    banished++;
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
