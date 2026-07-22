#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "cyber_phoenix.h"
#include "duel_helpers.h"

static u8 RowHasAtkCyberPhoenix(u8 fixedMonsterRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedMonsterRow][col];

    if (zone != NULL && zone->id == CYBER_PHOENIX && zone->isFaceUp && !zone->isDefending)
      return TRUE;
  }

  return FALSE;
}

u8 CyberPhoenix_BlocksSpellTrapTarget(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(zone->id);
  if (gCardInfo.type != TYPE_MACHINE)
    return FALSE;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &col))
    return FALSE;

  return RowHasAtkCyberPhoenix(fixedRow);
}

unsigned char CanActivateCYBER_PHOENIX(void)
{
  if (gMonEffect.id != CYBER_PHOENIX)
    return FALSE;

  /* Battle-destroy draw via ApplyCyberPhoenixBattleDestroyDraw; ATK-position Machine
   * S/T target-negate via CyberPhoenix_BlocksSpellTrapTarget. */
  return FALSE;
}

void ActivateCYBER_PHOENIXEffect(void)
{
  Duel_ShowEffectTextTyped(CYBER_PHOENIX, 2);
}
