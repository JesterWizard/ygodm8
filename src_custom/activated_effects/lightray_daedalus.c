#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "god_card.h"
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

static u8 IsLightMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_LIGHT;
}

static u8 CountLightMonstersInGraveyard(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    return IsLightMonster(cardId) ? 1 : 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsLightMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u8 IsFieldSpellZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_SPELL)
    return FALSE;

  return GetSpellType(zone->id) == SPELL_TYPE_INVALID;
}

static u8 FieldHasFieldSpell(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFieldSpellZone(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 CountOtherFieldCards(void)
{
  u8 row;
  u8 col;
  u8 count = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (IsFieldSpellZone(row, col))
        continue;

      count++;
    }
  }

  return count;
}

static u8 TurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void DestroyFieldSpellThenTwoOthers(struct DuelCard *self)
{
  u8 row;
  u8 col;
  u8 destroyedOthers = 0;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (!IsFieldSpellZone(row, col) || zone == NULL)
        continue;

      if (Duel_DestroyZone(zone, TurnDuelistForFixedRow(row), FALSE) == DUEL_ACTION_DUEL_OVER)
        return;

      goto destroyOthers;
    }
  }

destroyOthers:
  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == self || zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (IsFieldSpellZone(row, col))
        continue;

      if (Duel_DestroyZone(zone, TurnDuelistForFixedRow(row), FALSE) == DUEL_ACTION_DUEL_OVER)
        return;

      destroyedOthers++;
      if (destroyedOthers >= 2)
        return;
    }
  }
}

unsigned char CanActivateLIGHTRAY_DAEDALUS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != LIGHTRAY_DAEDALUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != LIGHTRAY_DAEDALUS)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!FieldHasFieldSpell())
    return FALSE;

  return CountOtherFieldCards() >= 2;
}

void ActivateLIGHTRAY_DAEDALUSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(LIGHTRAY_DAEDALUS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  DestroyFieldSpellThenTwoOthers(self);
  NotifyDynamicEquipFieldChanged();
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonLightrayDaedalusFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != LIGHTRAY_DAEDALUS)
    return FALSE;

  if (CountLightMonstersInGraveyard() < 4)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonLightrayDaedalusFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonLightrayDaedalusFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(LIGHTRAY_DAEDALUS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}
