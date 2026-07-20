#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 player);
void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsWarriorMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_WARRIOR);
}

static struct DuelCard *FindWarriorTribute(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id != CARD_NONE && IsWarriorMonster(zone->id))
      return zone;
  }

  return NULL;
}

static u8 IsSpellZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_SPELL;
}

static u8 FieldHasSpell(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsSpellZone(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 TurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 DestroyFirstSpell(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsSpellZone(row, col))
        continue;

      if (Duel_DestroyZone(gFixedZones[row][col], TurnDuelistForFixedRow(row), FALSE)
          == DUEL_ACTION_DUEL_OVER)
        return TRUE;

      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateSILENT_SWORDSMAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SILENT_SWORDSMAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SILENT_SWORDSMAN)
    return FALSE;

  /* ponytail: Standby +500 + Quick Spell negate need phase/chain hooks.
   * Ceiling: OPT +1 tempStage (~500 ATK), else OPT destroy 1 Spell. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasSpell() || zone->tempStage < 126;
}

void ActivateSILENT_SWORDSMANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(SILENT_SWORDSMAN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (FieldHasSpell()) {
    if (!DestroyFirstSpell())
      return;

    NotifyDynamicEquipFieldChanged();
  } else if (self->tempStage < 126) {
    self->tempStage++;
    RefreshFieldMonsterStatOverlays();
  } else {
    return;
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonSilentSwordsmanFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != SILENT_SWORDSMAN)
    return FALSE;

  if (FindWarriorTribute() == NULL)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonSilentSwordsmanFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *tribute;
  u8 fixedDuelist = FixedDuelistForActive();

  if (!CanSpecialSummonSilentSwordsmanFromHand(handZone))
    return FALSE;

  tribute = FindWarriorTribute();
  if (tribute == NULL)
    return FALSE;

  Duel_ShowEffectTextTyped(SILENT_SWORDSMAN, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  ClearZoneAndSendMonToGraveyard2(tribute, fixedDuelist);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonSilentSwordsmanFromHand(u8 handZone);
u8 TrySpecialSummonSilentSwordsmanFromHand(u8 handZone);
#endif
