#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u16 HalfLpCost(void)
{
  return gDuelLifePoints[FixedDuelistForActive()] / 2;
}

unsigned char CanActivateDIVINE_SERPENT_GEH(void)
{
  if (gMonEffect.id != DIVINE_SERPENT_GEH)
    return FALSE;

  /* Ceiling: destroy gate + untargetable + battle negate need destroy/battle hooks.
   * Ceiling: field ignition FALSE; FromHand pay half LP → SS only. */
  return FALSE;
}

void ActivateDIVINE_SERPENT_GEHEffect(void)
{
  Duel_ShowEffectTextTyped(DIVINE_SERPENT_GEH, 2);
}

u8 CanSpecialSummonDivineSerpentGehFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != DIVINE_SERPENT_GEH)
    return FALSE;

  if (HalfLpCost() == 0)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonDivineSerpentGehFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 cost;

  if (!CanSpecialSummonDivineSerpentGehFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(DIVINE_SERPENT_GEH, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  cost = HalfLpCost();
  if (cost == 0)
    return FALSE;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)cost, TRUE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonDivineSerpentGehFromHand(u8 handZone);
u8 TrySpecialSummonDivineSerpentGehFromHand(u8 handZone);
#endif
