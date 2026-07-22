#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

#define BONE_TOWER_MILL 2

static u8 SummonModeIsSpecial(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
}

static u8 IsZombieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_ZOMBIE);
}

static u8 TowerIsFaceUp(struct DuelCard *tower)
{
  if (tower == NULL || tower->id != SOUL_ABSORBING_BONE_TOWER)
    return FALSE;

  return IsCardFaceUp(tower) || tower->isDefending == FALSE;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

/* Other Zombie SS while face-up Tower on field → mill 2 from that Tower's opp. */
void TrySoulAbsorbingBoneTowerOnOtherZombieSummon(struct DuelCard *zone,
                                                  enum DuelSummonMode mode)
{
  u8 rows[2];
  u8 r;
  u8 col;
  u8 milled = FALSE;

  if (zone == NULL || zone->id == CARD_NONE || zone->id == SOUL_ABSORBING_BONE_TOWER)
    return;
  if (!SummonModeIsSpecial(mode) || !IsZombieMonster(zone->id) || gHideEffectText)
    return;

  rows[0] = OPPONENT_MONSTER_ROW;
  rows[1] = PLAYER_MONSTER_ROW;

  for (r = 0; r < 2; r++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *tower = gFixedZones[rows[r]][col];
      u8 controller;
      u8 turnDuelist;
      u8 oppTurn;

      if (!TowerIsFaceUp(tower) || tower == zone)
        continue;

      controller = GetDuelistForZone(tower);
      if (controller > DUEL_OPPONENT)
        continue;

      turnDuelist = TurnDuelistForFixed(controller);
      oppTurn = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;

      Duel_ShowEffectTextTyped(SOUL_ABSORBING_BONE_TOWER, 8);
      if (Duel_MillTopDeckCards(oppTurn, BONE_TOWER_MILL, TRUE) == DUEL_ACTION_DUEL_OVER)
        return;
      milled = TRUE;
    }
  }

  if (milled)
    UpdateDuelGfxExceptField();
}

unsigned char CanActivateSOUL_ABSORBING_BONE_TOWER(void)
{
  if (gMonEffect.id != SOUL_ABSORBING_BONE_TOWER)
    return FALSE;

  /* Other-Zombie SS mill via TrySoulAbsorbingBoneTowerOnOtherZombieSummon.
   * Ceiling: attack redirect while another Zombie present needs battle hooks.
   * Not field-ignition. */
  return FALSE;
}

void ActivateSOUL_ABSORBING_BONE_TOWEREffect(void)
{
  Duel_ShowEffectTextTyped(SOUL_ABSORBING_BONE_TOWER, 2);
}
