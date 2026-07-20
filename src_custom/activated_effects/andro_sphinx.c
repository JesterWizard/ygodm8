#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "pyramid_of_light.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

#define ANDRO_SPHINX_LP_COST 500

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CanPayAndroSphinxCost(void)
{
  return gDuelLifePoints[FixedDuelistForActive()] >= ANDRO_SPHINX_LP_COST;
}

unsigned char CanActivateANDRO_SPHINX(void)
{
  if (gMonEffect.id != ANDRO_SPHINX)
    return FALSE;

  /* ponytail: battle burn half ATK + GY SS ban need battle/GY hooks.
   * Ceiling: not field-ignition; FromHand pay 500 + Pyramid → SS. */
  return FALSE;
}

void ActivateANDRO_SPHINXEffect(void)
{
  Duel_ShowEffectTextTyped(ANDRO_SPHINX, 2);
}

u8 CanSpecialSummonAndroSphinxFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ANDRO_SPHINX)
    return FALSE;

  if (!IsPyramidOfLightActiveOnField())
    return FALSE;

  if (!CanPayAndroSphinxCost())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonAndroSphinxFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *summoned;
  u8 col;

  if (!CanSpecialSummonAndroSphinxFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ANDRO_SPHINX, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)ANDRO_SPHINX_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  /* Cannot attack the turn it is Summoned (unk4 stand-in). */
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    summoned = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    if (summoned != NULL && summoned->id == ANDRO_SPHINX) {
      summoned->unk4 |= 0x80;
      break;
    }
  }

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonAndroSphinxFromHand(u8 handZone);
u8 TrySpecialSummonAndroSphinxFromHand(u8 handZone);
#endif
