#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FlipAllOppMonstersToDef(void)
{
  u8 col;
  u8 changed = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    zone->isDefending = TRUE;
    zone->isFaceUp = TRUE;
    changed = TRUE;
  }

  return changed;
}

static u8 DestroyRandomHalfYourMonsters(void)
{
  struct DuelCard *picked[MAX_ZONES_IN_ROW];
  u8 pickCount = 0;
  u8 destroyCount;
  u8 i;
  u8 destroyed = FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone != NULL && zone->id != CARD_NONE && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
      picked[pickCount++] = zone;
  }

  if (pickCount == 0)
    return FALSE;

  destroyCount = (pickCount + 1) / 2;
  while (destroyCount > 0 && pickCount > 0) {
    u8 idx = (pickCount == 1) ? 0 : RandRangeU8(0, pickCount - 1);
    struct DuelCard *zone = picked[idx];

    picked[idx] = picked[pickCount - 1];
    pickCount--;

    if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return destroyed;

    destroyed = TRUE;
    destroyCount--;
  }

  return destroyed;
}

unsigned char CanActivateARCANA_FORCE_XIX_THE_SUN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ARCANA_FORCE_XIX_THE_SUN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ARCANA_FORCE_XIX_THE_SUN)
    return FALSE;

  /* OPT coin → flip all opp monsters DEF or destroy half yours. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return TRUE;
}

static u8 ResolveArcanaForceXixTheSunCoin(void)
{
  if (IsDuelOver() == TRUE)
    return FALSE;

  if (RandRangeU8(0, 1) == 1)
    FlipAllOppMonstersToDef();
  else
    DestroyRandomHalfYourMonsters();

  NotifyDynamicEquipFieldChanged();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  return TRUE;
}

void ActivateARCANA_FORCE_XIX_THE_SUNEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ARCANA_FORCE_XIX_THE_SUN, 2);

  if (!ResolveArcanaForceXixTheSunCoin())
    return;

  MarkMonsterEffectUsed(self);
}

void TryArcanaForceXixTheSunOnMonsterPlacement(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ARCANA_FORCE_XIX_THE_SUN)
    return;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_XIX_THE_SUN, 2);
  (void)ResolveArcanaForceXixTheSunCoin();
}

u8 CanSpecialSummonArcanaForceXixTheSunFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ARCANA_FORCE_XIX_THE_SUN)
    return FALSE;

  /* Requires coin-toss card on field — skipped; SS anytime when legal. */
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonArcanaForceXixTheSunFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 sunZone;

  if (!CanSpecialSummonArcanaForceXixTheSunFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_XIX_THE_SUN, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  sunZone = (s8)handZone;
  if (SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], handZone)->id
      != ARCANA_FORCE_XIX_THE_SUN) {
    u8 i;

    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (gTurnHands[ACTIVE_DUELIST][i]->id == ARCANA_FORCE_XIX_THE_SUN) {
        sunZone = (s8)i;
        break;
      }
    }
  }

  if (sunZone < 0)
    return FALSE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, (u8)sunZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}
