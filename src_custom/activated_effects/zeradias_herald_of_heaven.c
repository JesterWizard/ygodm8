#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"
#include "zeradias_herald_of_heaven.h"

void TryMaintainZeradiasHeraldOfHeaven(void)
{
  u8 fixedRow;
  u8 col;

  if (Duel_IsBackrowCardOnField(THE_SANCTUARY_IN_THE_SKY, TRUE))
    return;

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_MONSTER_ROW; fixedRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[fixedRow][col];

      if (zone == NULL || zone->id != ZERADIAS_HERALD_OF_HEAVEN || !zone->isFaceUp)
        continue;

      Duel_DestroyZone(zone, Duel_FixedDuelistForMonsterRow(fixedRow), FALSE);
      return;
    }
  }
}

unsigned char CanActivateZERADIAS_HERALD_OF_HEAVEN(void)
{
  if (gMonEffect.id != ZERADIAS_HERALD_OF_HEAVEN)
    return FALSE;

  /* Sanctuary absent destroy via TryMaintainZeradiasHeraldOfHeaven. */
  return FALSE;
}

void ActivateZERADIAS_HERALD_OF_HEAVENEffect(void)
{
  Duel_ShowEffectTextTyped(ZERADIAS_HERALD_OF_HEAVEN, 2);
}

u8 CanActivateZERADIAS_HERALD_OF_HEAVENFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ZERADIAS_HERALD_OF_HEAVEN)
    return FALSE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, THE_SANCTUARY_IN_THE_SKY) >= 0;
}

u8 TryActivateZERADIAS_HERALD_OF_HEAVENFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateZERADIAS_HERALD_OF_HEAVENFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ZERADIAS_HERALD_OF_HEAVEN, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  Duel_AddDeckCardToHand(ACTIVE_DUELIST, THE_SANCTUARY_IN_THE_SKY, TRUE);
  return TRUE;
}
