#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

extern const CardData gCardData_NEW[];

void UpdateDuelGfxExceptField(void);

static const char sEvilHeroName[] APPEND_RODATA = "Evil HERO";

static u8 ControlsDarkFusionFusion(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
      continue;
    if (gCardData_NEW[zone->id].color != FUSION_CARD)
      continue;
    if (Duel_CardNameContains(zone->id, sEvilHeroName))
      return TRUE;
  }
  return FALSE;
}

void TryEvilHeroToxicBubbleOnMonsterPlacement(struct DuelCard *zone)
{
  u8 controller;
  u8 turnDuelist;

  if (zone == NULL || zone->id != EVIL_HERO_TOXIC_BUBBLE || gHideEffectText)
    return;
  if (EffectOpt_IsUsed(EVIL_HERO_TOXIC_BUBBLE))
    return;

  controller = GetDuelistForZone(zone);
  if (controller > DUEL_OPPONENT)
    return;
  if (!ControlsDarkFusionFusion(controller))
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(controller);
  Duel_ShowEffectTextTyped(EVIL_HERO_TOXIC_BUBBLE, 8);
  if (Duel_DrawCards(turnDuelist, 2, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  EffectOpt_MarkUsed(EVIL_HERO_TOXIC_BUBBLE);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateEVIL_HERO_TOXIC_BUBBLE(void)
{
  if (gMonEffect.id != EVIL_HERO_TOXIC_BUBBLE)
    return FALSE;

  /* On-SS draw via TryEvilHeroToxicBubbleOnMonsterPlacement.
   * Not field-ignition; SS-from-hand uses FromHand path. */
  return FALSE;
}

void ActivateEVIL_HERO_TOXIC_BUBBLEEffect(void)
{
  Duel_ShowEffectTextTyped(EVIL_HERO_TOXIC_BUBBLE, 2);
}

u8 CanSpecialSummonEvilHeroToxicBubbleFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != EVIL_HERO_TOXIC_BUBBLE)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  /* HERO-only SS lock this turn needs summon gate. */
  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonEvilHeroToxicBubbleFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonEvilHeroToxicBubbleFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(EVIL_HERO_TOXIC_BUBBLE, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonEvilHeroToxicBubbleFromHand(u8 handZone);
u8 TrySpecialSummonEvilHeroToxicBubbleFromHand(u8 handZone);
#endif
