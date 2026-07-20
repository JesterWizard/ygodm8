#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void SetCardInfo(unsigned short id);
void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static struct DuelCard *FindFirstLightBattler(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    SetCardInfo(zone->id);
    if (gCardInfo.attribute != ATTRIBUTE_LIGHT)
      continue;

    if (!IsCardFaceUp(zone) && zone->isDefending)
      continue;

    return zone;
  }

  return NULL;
}

static u16 GetStrongestOpponentMonsterAtk(void)
{
  u16 bestAtk = 0;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];
    struct StatMod statMod;

    if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    if (!IsCardFaceUp(zone) && zone->isDefending)
      continue;

    statMod.card = zone->id;
    statMod.field = gDuel.field;
    statMod.stage = GetFinalStage(zone);
    SetFinalStat(&statMod);

    if (gCardInfo.atk > bestAtk)
      bestAtk = gCardInfo.atk;
  }

  return bestAtk;
}

static u8 ApplyHonestBoostToLightBattler(u16 opponentAtk)
{
  struct DuelCard *battler = FindFirstLightBattler();
  s8 stages;

  if (battler == NULL || opponentAtk == 0)
    return FALSE;

  stages = (s8)((opponentAtk + 499) / 500);
  if (stages <= 0)
    stages = 1;

  if (battler->tempStage <= 127 - stages)
    battler->tempStage += stages;

  RefreshFieldMonsterStatOverlays();
  return TRUE;
}

unsigned char CanActivateHONEST(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != HONEST)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != HONEST)
    return FALSE;

  /* ponytail: Damage Step hand discard uses FromHand path. Ceiling: Main Phase
   * return this face-up card to the hand. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!IsCardFaceUp(zone))
    return FALSE;

  return FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0;
}

void ActivateHONESTEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(HONEST, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_ReturnMonsterZoneToOwnerHand(self, TRUE) != DUEL_ACTION_OK)
    return;

  NotifyDynamicEquipFieldChanged();
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanActivateHonestFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != HONEST)
    return FALSE;

  return FindFirstLightBattler() != NULL && GetStrongestOpponentMonsterAtk() > 0;
}

u8 TryActivateHonestFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u16 opponentAtk;

  if (!CanActivateHonestFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(HONEST, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  opponentAtk = GetStrongestOpponentMonsterAtk();
  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  ApplyHonestBoostToLightBattler(opponentAtk);
  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanActivateHonestFromHand(u8 handZone);
u8 TryActivateHonestFromHand(u8 handZone);
#endif
