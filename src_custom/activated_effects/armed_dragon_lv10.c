#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsFaceUpMonsterZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 ControlsArmedDragonLv7(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == ARMED_DRAGON_LV7 && IsFaceUpMonsterZone(zone))
      return TRUE;
  }

  return FALSE;
}

static u8 FindArmedDragonLv7Col(u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == ARMED_DRAGON_LV7 && IsFaceUpMonsterZone(zone)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 TributeArmedDragonLv7(void)
{
  u8 col;

  if (!FindArmedDragonLv7Col(&col))
    return FALSE;

  if (Duel_DestroyZone(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col], ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return FALSE;

  NotifyDynamicEquipFieldChanged();
  return TRUE;
}

static s8 FindHandZoneWithId(u16 cardId)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == cardId)
      return (s8)i;
  }

  return -1;
}

static u8 OppHasFaceUpMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id != CARD_NONE && !IsGodCard(zone->id)
        && IsFaceUpMonsterZone(zone))
      return TRUE;
  }

  return FALSE;
}

static void DestroyAllFaceUpOpponentMonsters(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;

    if (!IsFaceUpMonsterZone(zone))
      continue;

    if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  NotifyDynamicEquipFieldChanged();
}

unsigned char CanActivateARMED_DRAGON_LV10(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ARMED_DRAGON_LV10)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ARMED_DRAGON_LV10)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) == 0)
    return FALSE;

  return OppHasFaceUpMonster();
}

void ActivateARMED_DRAGON_LV10Effect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ARMED_DRAGON_LV10, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE || !OppHasFaceUpMonster())
    return;

  DestroyAllFaceUpOpponentMonsters();

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonArmedDragonLv10FromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ARMED_DRAGON_LV10)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return ControlsArmedDragonLv7();
}

u8 TrySpecialSummonArmedDragonLv10FromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 lv10Zone;

  if (!CanSpecialSummonArmedDragonLv10FromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ARMED_DRAGON_LV10, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!TributeArmedDragonLv7())
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  lv10Zone = FindHandZoneWithId(ARMED_DRAGON_LV10);
  if (lv10Zone < 0)
    return FALSE;

  return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, (u8)lv10Zone, opts) == DUEL_ACTION_OK;
}
