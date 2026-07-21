#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "the_dark_door.h"
#include "tyrant_wing.h"

void UpdateDuelGfxExceptField(void);

/* 1 stage ~= 500 ATK; printed +400 → nearest 1 stage. */
#define TYRANT_WING_ATK_STAGES 1

void TryUnlockTyrantWingForSecondAttack(struct DuelCard *attacker)
{
  if (attacker == NULL)
    return;
  if (!DynamicEquipTargetsMonsterWithSpell(attacker, TYRANT_WING))
    return;
  if (IsTheDarkDoorActiveOnField())
    return;

  if (attacker->effectUsedThisTurn == FALSE) {
    attacker->effectUsedThisTurn = TRUE;
    attacker->isLocked = FALSE;
  }
}

void TryDestroyTyrantWingAtEndPhase(void)
{
  u8 fixed;
  u8 col;

  for (fixed = DUEL_PLAYER; fixed <= DUEL_OPPONENT; fixed++) {
    u8 backrow = fixed == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
    u8 monRow = Duel_FixedMonsterRowForDuelist(fixed);
    u8 turn = Duel_TurnDuelistForFixedDuelist(fixed);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *trap = gFixedZones[backrow][col];
      struct DuelCard *mon;
      u8 mcol;

      if (trap == NULL || trap->id != TYRANT_WING || !trap->isFaceUp)
        continue;

      for (mcol = 0; mcol < MAX_ZONES_IN_ROW; mcol++) {
        mon = gFixedZones[monRow][mcol];
        if (mon != NULL && DynamicEquipTargetsMonsterWithSpell(mon, TYRANT_WING)
            && mon->effectUsedThisTurn) {
          Duel_DestroyZone(trap, turn, FALSE);
          break;
        }
      }
    }
  }
}

APPEND_TEXT void EffectTYRANT_WING(void)
{
  u8 col;
  u8 row;
  struct DuelCard *dragon = NULL;
  struct DuelCard *trapZone;

  Duel_ShowTrapResponseText(TYRANT_WING, gTrapEffectData.originCardId);

  row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && Duel_CardHasMonsterType(zone->id, TYPE_DRAGON)) {
      dragon = zone;
      break;
    }
  }

  if (dragon == NULL) {
    row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && Duel_CardHasMonsterType(zone->id, TYPE_DRAGON)) {
        dragon = zone;
        break;
      }
    }
  }

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  if (dragon != NULL && trapZone != NULL) {
    ApplyDynamicEquipStages(dragon, TYRANT_WING_ATK_STAGES);
    RegisterDynamicEquip(trapZone, dragon, TYRANT_WING, TYRANT_WING_ATK_STAGES);
    Duel_ActivateContinuousZone(trapZone);
    NotifyDynamicEquipFieldChanged();
  } else if (trapZone != NULL) {
    Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);
  }

  UpdateDuelGfxExceptField();
}
