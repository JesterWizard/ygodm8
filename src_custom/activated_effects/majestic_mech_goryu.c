#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "majestic_mech_goryu.h"

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 player);

void TryApplyMajesticMechGoryuEndPhase(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 fixedDuelist = WhoseTurn();
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !zone->isFaceUp || zone->id != MAJESTIC_MECH_GORYU)
      continue;

    Duel_ShowEffectTextTyped(MAJESTIC_MECH_GORYU, 2);
    ClearZoneAndSendMonToGraveyard2(zone, fixedDuelist);
    return;
  }
}

unsigned char CanActivateMAJESTIC_MECH_GORYU(void)
{
  if (gMonEffect.id != MAJESTIC_MECH_GORYU)
    return FALSE;

  /* Pierce via ApplySimplePiercersBattleEffect; EP self-send via
   * TryApplyMajesticMechGoryuEndPhase. Not ignition-activatable. */
  return FALSE;
}

void ActivateMAJESTIC_MECH_GORYUEffect(void)
{
  Duel_ShowEffectTextTyped(MAJESTIC_MECH_GORYU, 2);
}
