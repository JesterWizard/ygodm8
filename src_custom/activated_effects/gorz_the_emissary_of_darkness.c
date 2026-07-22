#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static u8 ActiveControlsNoCards(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *mon = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    struct DuelCard *st = gTurnZones[ACTIVE_DUELIST_BACKROW][col];

    if (mon != NULL && mon->id != CARD_NONE)
      return FALSE;

    if (st != NULL && st->id != CARD_NONE)
      return FALSE;
  }

  return TRUE;
}

unsigned char CanActivateGORZ_THE_EMISSARY_OF_DARKNESS(void)
{
  if (gMonEffect.id != GORZ_THE_EMISSARY_OF_DARKNESS)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateGORZ_THE_EMISSARY_OF_DARKNESSEffect(void)
{
  Duel_ShowEffectTextTyped(GORZ_THE_EMISSARY_OF_DARKNESS, 2);
}

u8 CanSpecialSummonGorzTheEmissaryOfDarknessFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != GORZ_THE_EMISSARY_OF_DARKNESS)
    return FALSE;

  if (!ActiveControlsNoCards())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonGorzTheEmissaryOfDarknessFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonGorzTheEmissaryOfDarknessFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(GORZ_THE_EMISSARY_OF_DARKNESS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonGorzTheEmissaryOfDarknessFromHand(u8 handZone);
u8 TrySpecialSummonGorzTheEmissaryOfDarknessFromHand(u8 handZone);
#endif
