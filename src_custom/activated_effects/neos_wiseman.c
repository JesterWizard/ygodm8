#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 player);
void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static struct DuelCard *FindFaceUpCard(u16 cardId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->isFaceUp && zone->id == cardId)
      return zone;
  }

  return NULL;
}

unsigned char CanActivateNEOS_WISEMAN(void)
{
  if (gMonEffect.id != NEOS_WISEMAN)
    return FALSE;

  /* ponytail: battle burn/heal + effect-destroy immunity FALSE.
   * Ceiling: FromHand send Neos+Yubel → SS only. */
  return FALSE;
}

void ActivateNEOS_WISEMANEffect(void)
{
  Duel_ShowEffectTextTyped(NEOS_WISEMAN, 2);
}

u8 CanSpecialSummonNeosWisemanFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != NEOS_WISEMAN)
    return FALSE;

  if (FindFaceUpCard(ELEMENTAL_HERO_NEOS) == NULL)
    return FALSE;

  if (FindFaceUpCard(YUBEL) == NULL)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonNeosWisemanFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *neos;
  struct DuelCard *yubel;
  u8 fixedDuelist = FixedDuelistForActive();

  if (!CanSpecialSummonNeosWisemanFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(NEOS_WISEMAN, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  neos = FindFaceUpCard(ELEMENTAL_HERO_NEOS);
  yubel = FindFaceUpCard(YUBEL);
  if (neos == NULL || yubel == NULL)
    return FALSE;

  ClearZoneAndSendMonToGraveyard2(neos, fixedDuelist);
  ClearZoneAndSendMonToGraveyard2(yubel, fixedDuelist);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonNeosWisemanFromHand(u8 handZone);
u8 TrySpecialSummonNeosWisemanFromHand(u8 handZone);
#endif
