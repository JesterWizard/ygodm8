#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "rescue_end_phase.h"

void UpdateDuelGfxExceptField(void);

void RescueEndPhase_StampSummonedMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return;

  zone->unk4 |= (u8)(RESCUE_SUMMON_END_PHASE_MARK | 0x80);
}

void TryApplyRescueEndPhaseDestroy(void)
{
  u8 fixedRow;
  u8 col;
  u8 destroyed = FALSE;

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_MONSTER_ROW; fixedRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[fixedRow][col];

      if (zone == NULL || zone->id == CARD_NONE)
        continue;

      if ((zone->unk4 & RESCUE_SUMMON_END_PHASE_MARK) == 0)
        continue;

      zone->unk4 &= (u8)~RESCUE_SUMMON_END_PHASE_MARK;
      if (Duel_DestroyZone(zone,
                           Duel_TurnDuelistForFixedDuelist(Duel_FixedDuelistForMonsterRow(fixedRow)),
                           FALSE) == DUEL_ACTION_DUEL_OVER)
        return;

      destroyed = TRUE;
      if (IsDuelOver() == TRUE)
        return;
    }
  }

  if (destroyed) {
    NotifyDynamicEquipFieldChanged();
    UpdateDuelGfxExceptField();
  }
}
