#include "global.h"
#include "common-chax.h"
#include "charm_of_shabti.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "six_card_hand.h"
#include "spell_effects.h"

u8 GetDuelistForZone(struct DuelCard *zone);

static u8 sCharmProtectMask APPEND_DATA = {0};

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;
  return DUEL_OPPONENT;
}

u8 CharmOfShabti_PreventsBattleDestroy(const struct DuelCard *zone)
{
  u8 controller;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (!Necrovalley_IsGravekeeperMonster(zone->id))
    return FALSE;

  controller = GetDuelistForZone((struct DuelCard *)zone);
  if (controller > DUEL_OPPONENT)
    return FALSE;

  return (sCharmProtectMask & (1u << controller)) != 0;
}

void CharmOfShabti_ClearOnTurnBoundary(void)
{
  sCharmProtectMask = 0;
}

unsigned char CanActivateCHARM_OF_SHABTI(void)
{
  if (gMonEffect.id != CHARM_OF_SHABTI)
    return FALSE;

  /* Printed effect is hand discard — use FromHand path. */
  return FALSE;
}

void ActivateCHARM_OF_SHABTIEffect(void)
{
  Duel_ShowEffectTextTyped(CHARM_OF_SHABTI, 2);
}

u8 CanActivateCHARM_OF_SHABTIFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  return SixCardHand_ZoneAtHandRow(handRow, handZone)->id == CHARM_OF_SHABTI;
}

u8 TryActivateCHARM_OF_SHABTIFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 fixed;

  if (!CanActivateCHARM_OF_SHABTIFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(CHARM_OF_SHABTI, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  fixed = FixedDuelistForActive();
  sCharmProtectMask |= (u8)(1u << fixed);
  return TRUE;
}
