#include "global.h"
#include "common-chax.h"
#include "a_legendary_ocean.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "tornado_wall.h"

static u8 FieldHasUmi(void)
{
  if (gDuel.field == FIELD_UMI || IsLegendaryOceanActive())
    return TRUE;

  return Duel_FindBackrowCard(DUEL_PLAYER, UMI, TRUE) != NULL
      || Duel_FindBackrowCard(DUEL_OPPONENT, UMI, TRUE) != NULL
      || Duel_FindBackrowCard(DUEL_PLAYER, A_LEGENDARY_OCEAN, TRUE) != NULL
      || Duel_FindBackrowCard(DUEL_OPPONENT, A_LEGENDARY_OCEAN, TRUE) != NULL;
}

static void ActivateTORNADO_WALLZone(struct DuelCard *zone)
{
  if (!FieldHasUmi()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_ActivateContinuousTrapPreamble(zone, TORNADO_WALL) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateTORNADO_WALLOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(TORNADO_WALL, ActivateTORNADO_WALLZone);
}

u8 TornadoWall_ShouldBlockBattleDamage(u8 damagedFixedDuelist)
{
  if (!FieldHasUmi())
    return FALSE;

  return Duel_FindBackrowCard(damagedFixedDuelist, TORNADO_WALL, TRUE) != NULL;
}

void TornadoWall_CheckAfterFieldChange(void)
{
  u8 duelist;
  u8 col;
  u8 backrow;

  if (FieldHasUmi())
    return;

  for (duelist = DUEL_PLAYER; duelist <= DUEL_OPPONENT; duelist++) {
    backrow = duelist == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[backrow][col];

      if (zone != NULL && zone->id == TORNADO_WALL && zone->isFaceUp)
        Duel_DestroyZone(zone, duelist, FALSE);
    }
  }
}
