#include "global.h"
#include "common-chax.h"
#include "arcana_force_coin.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
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

static u16 FindLightBarrierInDeckOrGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, LIGHT_BARRIER) >= 0)
    return LIGHT_BARRIER;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == LIGHT_BARRIER)
      return LIGHT_BARRIER;

    return CARD_NONE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == LIGHT_BARRIER)
      return LIGHT_BARRIER;
  }

  return CARD_NONE;
}

static u8 AddLightBarrierFromDeckOrGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  s8 handZone;
  u8 i;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0)
    return FALSE;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, LIGHT_BARRIER) >= 0)
    return Duel_AddDeckCardToHand(ACTIVE_DUELIST, LIGHT_BARRIER, TRUE) == DUEL_ACTION_OK;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard != LIGHT_BARRIER)
      return FALSE;

    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
    gTurnHands[ACTIVE_DUELIST][handZone]->id = LIGHT_BARRIER;
    gTurnHands[ACTIVE_DUELIST][handZone]->isFaceUp = FALSE;
    return TRUE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) != LIGHT_BARRIER)
      continue;

    GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    GraveyardExpand_RefreshDisplay();
    gTurnHands[ACTIVE_DUELIST][handZone]->id = LIGHT_BARRIER;
    gTurnHands[ACTIVE_DUELIST][handZone]->isFaceUp = FALSE;
    return TRUE;
  }

  return FALSE;
}

static u8 IsDestroyableMonsterZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != PLAYER_MONSTER_ROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return !IsGodCard(zone->id);
}

static u8 FieldHasDestroyableMonster(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsDestroyableMonsterZone(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 DestroyAllMonstersOnField(void)
{
  u8 row;
  u8 col;
  u8 destroyed = FALSE;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];
      u8 owner;

      if (!IsDestroyableMonsterZone(row, col) || zone == NULL)
        continue;

      owner = (row == PLAYER_MONSTER_ROW) ? DUEL_PLAYER : DUEL_OPPONENT;
      if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[owner])
        owner = ACTIVE_DUELIST;
      else
        owner = INACTIVE_DUELIST;

      if (Duel_DestroyZone(zone, owner, FALSE) == DUEL_ACTION_DUEL_OVER)
        return destroyed;

      destroyed = TRUE;
    }
  }

  return destroyed;
}

static u8 sXvMarkOpt APPEND_DATA = {0};

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = NULL;
  u8 owner;

  if (!IsDestroyableMonsterZone(fixedRow, fixedCol) || zone == NULL)
    return;

  owner = (fixedRow == PLAYER_MONSTER_ROW) ? DUEL_PLAYER : DUEL_OPPONENT;
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[owner])
    owner = ACTIVE_DUELIST;
  else
    owner = INACTIVE_DUELIST;

  if (Duel_DestroyZone(zone, owner, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (sXvMarkOpt) {
    self = gTurnZones[gMonEffect.row][gMonEffect.zone];
    if (self != NULL) {
      EffectOpt_MarkUsed(ARCANA_FORCE_XV_THE_FIEND);
      MarkMonsterEffectUsed(self);
    }
  }

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsDestroyableMonsterZone(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateARCANA_FORCE_XV_THE_FIEND(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ARCANA_FORCE_XV_THE_FIEND)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ARCANA_FORCE_XV_THE_FIEND)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * (EffectOpt). */
  if (EffectOpt_IsUsed(ARCANA_FORCE_XV_THE_FIEND))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasDestroyableMonster();
}

static u8 ResolveArcanaForceXvTheFiendCoinTails(void)
{
  if (!DestroyAllMonstersOnField())
    return FALSE;

  NotifyDynamicEquipFieldChanged();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  return TRUE;
}

void ActivateARCANA_FORCE_XV_THE_FIENDEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ARCANA_FORCE_XV_THE_FIEND, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(ARCANA_FORCE_XV_THE_FIEND))
    return;

  {
    u8 heads = RandRangeU8(0, 1) == 1;

    ArcanaForce_AnnounceCoinResult(ARCANA_FORCE_XV_THE_FIEND, heads);
    if (heads) {
      sXvMarkOpt = TRUE;
      gDuelCursor.destY = gMonEffect.row;
      gDuelCursor.destX = gMonEffect.zone;
      Duel_SetupPickZone(IsDestroyableMonsterZone, ResolveDestroyTarget, CancelTargeting,
                         AiPickDestroyTarget);

      if (WhoseTurn() == DUEL_PLAYER)
        Duel_EnterPickZoneTargeting();
      else
        Duel_ResolvePickZoneForAi();
      return;
    }
  }

  if (!ResolveArcanaForceXvTheFiendCoinTails())
    return;

  EffectOpt_MarkUsed(ARCANA_FORCE_XV_THE_FIEND);
  MarkMonsterEffectUsed(self);
}

void TryArcanaForceXvTheFiendOnMonsterPlacement(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ARCANA_FORCE_XV_THE_FIEND)
    return;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_XV_THE_FIEND, 2);

  if (IsDuelOver() == TRUE)
    return;

  {
    u8 heads = RandRangeU8(0, 1) == 1;

    ArcanaForce_AnnounceCoinResult(ARCANA_FORCE_XV_THE_FIEND, heads);
    if (heads) {
      u8 row;
      u8 col;

      if (!FieldHasDestroyableMonster())
        return;

      sXvMarkOpt = FALSE;
      for (row = 0; row < 4; row++) {
        for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
          if (gFixedZones[row][col] == zone) {
            gDuelCursor.destY = row;
            gDuelCursor.destX = col;
            goto found;
          }
        }
      }
    found:
      Duel_SetupPickZone(IsDestroyableMonsterZone, ResolveDestroyTarget, CancelTargeting,
                         AiPickDestroyTarget);

      if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
        Duel_RunPickZoneInputLoop();
      else
        Duel_ResolvePickZoneForAi();
      return;
    }
  }

  (void)ResolveArcanaForceXvTheFiendCoinTails();
}

u8 CanActivateArcanaForceXvTheFiendFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ARCANA_FORCE_XV_THE_FIEND)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindLightBarrierInDeckOrGy() != CARD_NONE;
}

u8 TryActivateArcanaForceXvTheFiendFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateArcanaForceXvTheFiendFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_XV_THE_FIEND, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!AddLightBarrierFromDeckOrGy())
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanActivateArcanaForceXvTheFiendFromHand(u8 handZone);
u8 TryActivateArcanaForceXvTheFiendFromHand(u8 handZone);
#endif
