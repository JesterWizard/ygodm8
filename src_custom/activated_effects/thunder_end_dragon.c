#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 TurnDuelistForFixedRow(u8 fixedRow)
{
  u8 fixedOwner;

  if (fixedRow == PLAYER_MONSTER_ROW || fixedRow == PLAYER_BACKROW)
    fixedOwner = DUEL_PLAYER;
  else
    fixedOwner = DUEL_OPPONENT;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedOwner])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static struct DuelCard *ThunderEndZone(void)
{
  return gTurnZones[gMonEffect.row][gMonEffect.zone];
}

static u8 FieldHasOtherMonster(struct DuelCard *self)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];

      if (zone == self || zone->id == CARD_NONE)
        continue;

      if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
        return TRUE;
    }
  }

  return FALSE;
}

static void DestroyAllOtherMonsters(struct DuelCard *protectedZone)
{
  u8 row;
  u8 col;
  u8 destroyed = FALSE;

  /* ponytail: no Xyz detach cost; OPT destroy-all-other-monsters stand-in.
   * Ceiling: materials not checked; upgrade: overlay detach before destroy. */
  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 graveyardDuelist = TurnDuelistForFixedRow(row);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];

      if (zone == protectedZone || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
        continue;

      if (Duel_DestroyZone(zone, graveyardDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;

      destroyed = TRUE;
    }
  }

  if (destroyed) {
    NotifyDynamicEquipFieldChanged();
    UpdateDuelGfxExceptField();
  }
}

unsigned char CanActivateTHUNDER_END_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != THUNDER_END_DRAGON)
    return FALSE;

  zone = ThunderEndZone();
  if (zone == NULL || zone->id != THUNDER_END_DRAGON)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  return CanUseMonsterEffect(zone) && FieldHasOtherMonster(zone);
}

void ActivateTHUNDER_END_DRAGONEffect(void)
{
  struct DuelCard *self = ThunderEndZone();

  Duel_ShowEffectTextTyped(THUNDER_END_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  DestroyAllOtherMonsters(self);

  if (IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
