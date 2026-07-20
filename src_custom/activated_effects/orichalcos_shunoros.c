#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 CountOpponentMonsters(void)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id != CARD_NONE)
      count++;
  }

  return count;
}

unsigned char CanActivateORICHALCOS_SHUNOROS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ORICHALCOS_SHUNOROS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ORICHALCOS_SHUNOROS)
    return FALSE;

  /* ponytail: battle-trigger SS + Lv4 Normal indestructible need trigger/permanent
   * hooks. Ceiling: OPT +2 tempStage per opp monster (~1000 ATK each). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CountOpponentMonsters() > 0;
}

void ActivateORICHALCOS_SHUNOROSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 oppCount;
  s8 stages;

  Duel_ShowEffectTextTyped(ORICHALCOS_SHUNOROS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  oppCount = CountOpponentMonsters();
  if (oppCount == 0)
    return;

  stages = (s8)(oppCount * 2);
  if (self->tempStage <= 127 - stages)
    self->tempStage += stages;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonOrichalcosShunorosFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ORICHALCOS_SHUNOROS)
    return FALSE;

  /* ponytail: SS only when your Normal Monster destroyed by battle needs battle hook.
   * Ceiling: hand SS anytime when zone open. */
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonOrichalcosShunorosFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonOrichalcosShunorosFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ORICHALCOS_SHUNOROS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonOrichalcosShunorosFromHand(u8 handZone);
u8 TrySpecialSummonOrichalcosShunorosFromHand(u8 handZone);
#endif
