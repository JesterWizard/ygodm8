#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static u8 IsRaTribute(u16 cardId)
{
  return IsWingedDragonOfRa(cardId) == TRUE;
}

static struct DuelCard *FindTributeZone(u16 cardId, u8 (*extraPred)(u16))
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    if (zone->id == cardId || (extraPred != NULL && extraPred(zone->id)))
      return zone;
  }

  return NULL;
}

static u8 ControlsHolactieTributes(void)
{
  return FindTributeZone(SLIFER_THE_SKY_DRAGON, NULL) != NULL
      && FindTributeZone(OBELISK_THE_TORMENTOR, NULL) != NULL
      && FindTributeZone(CARD_NONE, IsRaTribute) != NULL;
}

static void TributeHolactieCosts(void)
{
  struct DuelCard *zone;

  zone = FindTributeZone(SLIFER_THE_SKY_DRAGON, NULL);
  if (zone != NULL)
    ClearZone(zone);

  zone = FindTributeZone(OBELISK_THE_TORMENTOR, NULL);
  if (zone != NULL)
    ClearZone(zone);

  zone = FindTributeZone(CARD_NONE, IsRaTribute);
  if (zone != NULL)
    ClearZone(zone);
}

unsigned char CanActivateHOLACTIE_THE_CREATOR_OF_LIGHT(void)
{
  if (gMonEffect.id != HOLACTIE_THE_CREATOR_OF_LIGHT)
    return FALSE;

  /* SS-this-card-wins-Duel needs win-on-summon hook; no duel_helpers win API.
   * Ceiling: not field-ignition activatable; use FromHand tribute path. */
  return FALSE;
}

void ActivateHOLACTIE_THE_CREATOR_OF_LIGHTEffect(void)
{
  Duel_ShowEffectTextTyped(HOLACTIE_THE_CREATOR_OF_LIGHT, 2);
}

u8 CanSpecialSummonHolactieTheCreatorOfLightFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != HOLACTIE_THE_CREATOR_OF_LIGHT)
    return FALSE;

  if (!ControlsHolactieTributes())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonHolactieTheCreatorOfLightFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonHolactieTheCreatorOfLightFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(HOLACTIE_THE_CREATOR_OF_LIGHT, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  TributeHolactieCosts();

  if (IsDuelOver() == TRUE)
    return FALSE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonHolactieTheCreatorOfLightFromHand(u8 handZone);
u8 TrySpecialSummonHolactieTheCreatorOfLightFromHand(u8 handZone);
#endif
