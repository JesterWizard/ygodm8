#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "gandora_x.h"
#include "dynamic_equip.h"
#include "god_card.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

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

static u16 DestroyAllOtherMonstersAndGetHighestOriginalAtk(struct DuelCard *protectedZone)
{
  u8 row;
  u8 col;
  u16 highestAtk = 0;
  u8 destroyed = FALSE;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 graveyardDuelist = TurnDuelistForFixedRow(row);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];
      u16 originalAtk;

      if (zone == protectedZone || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
        continue;

      originalAtk = gCardData_NEW[zone->id].atk;
      if (originalAtk > highestAtk)
        highestAtk = originalAtk;

      if (Duel_DestroyZone(zone, graveyardDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
        return highestAtk;

      destroyed = TRUE;
    }
  }

  if (destroyed) {
    NotifyDynamicEquipFieldChanged();
    UpdateDuelGfxExceptField();
  }

  return highestAtk;
}

static u8 IsOnSummonTrigger(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != GANDORA_X_THE_DRAGON_OF_DEMOLITION)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  return FieldHasOtherMonster(zone);
}

unsigned char ShouldActivateGANDORA_X_THE_DRAGON_OF_DEMOLITION(void)
{
  /* EP half LP needs EP hook; on-summon wipe only here. ATK overlay via
   * GandoraX_ApplyDynamicZoneStats. */
  return IsOnSummonTrigger();
}

void ActivateGANDORA_X_THE_DRAGON_OF_DEMOLITION(void)
{
  struct DuelCard *self;
  u16 burn;
  s8 stages;

  self = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  Duel_ShowEffectTextTyped(GANDORA_X_THE_DRAGON_OF_DEMOLITION, 8);
  if (self == NULL || IsDuelOver() == TRUE)
    return;

  burn = DestroyAllOtherMonstersAndGetHighestOriginalAtk(self);
  if (IsDuelOver() == TRUE)
    return;

  if (burn > 0) {
    if (Duel_ChangeLp(DuelistForMonsterTurnRow(gActiveEffect.turnRow) == ACTIVE_DUELIST
            ? INACTIVE_DUELIST
            : ACTIVE_DUELIST,
        -(s32)burn, TRUE)
        == DUEL_ACTION_DUEL_OVER)
      return;

    /* ATK = damage via tempStage (~500/unit) + GandoraX_ApplyDynamicZoneStats. */
    stages = (s8)((burn + 499) / 500);
    if (stages > 126)
      stages = 126;
    self->tempStage = stages;
    RefreshFieldMonsterStatOverlays();
  }

  self->unk4 = 1;
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
