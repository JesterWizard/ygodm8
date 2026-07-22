#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "gandora_x.h"

extern const CardData gCardData_NEW[];

#define GANDORA_X_ATK_PER_STAGE 500

u8 GandoraX_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 baseAtk;
  u16 boostedAtk;

  if (zone == NULL)
    return FALSE;

  if (zone->id != GANDORA_X_THE_DRAGON_OF_DESTRUCTION
      && zone->id != GANDORA_X_THE_DRAGON_OF_DEMOLITION)
    return FALSE;

  if (zone->tempStage <= 0)
    return FALSE;

  baseAtk = gCardData_NEW[zone->id].atk;
  boostedAtk = baseAtk + (u16)(zone->tempStage * GANDORA_X_ATK_PER_STAGE);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, boostedAtk, gCardInfo.def);
  return TRUE;
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

void TryApplyGandoraXEndPhase(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || !zone->isFaceUp || zone->id != GANDORA_X_THE_DRAGON_OF_DESTRUCTION)
        continue;

      Duel_ShowEffectTextTyped(GANDORA_X_THE_DRAGON_OF_DESTRUCTION, 9);
      Duel_DestroyZone(zone, TurnDuelistForFixedRow(row), FALSE);
      return;
    }
  }
}
