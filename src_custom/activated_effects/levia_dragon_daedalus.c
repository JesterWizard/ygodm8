#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/duel_fields.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "dynamic_equip.h"
#include "levia_dragon_daedalus.h"
#include "monster_effect_usage.h"

void SetDuelFieldGfx(u8 field);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);
void UpdateDuelGfxExceptField(void);

static u8 IsOnActiveDuelistMonsterRow(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gMonEffect.row == PLAYER_MONSTER_ROW;

  return gMonEffect.row == OPPONENT_MONSTER_ROW;
}

static u8 TurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 FixedDuelistYouControl(void)
{
  return WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
}

static struct DuelCard *FindFaceUpUmiYouControl(void)
{
  return Duel_FindBackrowCard(FixedDuelistYouControl(), UMI, TRUE);
}

static u8 FixedRowForZone(struct DuelCard *zone, u8 *fixedRow)
{
  u8 row;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gFixedZones[row][col] == zone) {
        *fixedRow = row;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static void ResetFieldToArenaAfterUmiCost(void)
{
  RevertCustomFieldToArena();

  if (gDuel.field == FIELD_ARENA)
    return;

  gDuel.field = FIELD_ARENA;

  if (!gHideEffectText)
    SetDuelFieldGfx(gDuel.field);

  EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);
}

static u8 CanPayLeviaDragonDaedalusCost(void)
{
  if (FindFaceUpUmiYouControl() != NULL)
    return TRUE;

  return gDuel.field == FIELD_UMI;
}

static u8 PayLeviaDragonDaedalusCost(void)
{
  struct DuelCard *umiZone = FindFaceUpUmiYouControl();
  u8 fixedRow;
  u8 wasUmiField = gDuel.field == FIELD_UMI;

  if (umiZone != NULL) {
    if (!FixedRowForZone(umiZone, &fixedRow))
      return FALSE;

    if (Duel_DestroyZone(umiZone, TurnDuelistForFixedRow(fixedRow), FALSE) == DUEL_ACTION_DUEL_OVER)
      return FALSE;

    if (wasUmiField)
      ResetFieldToArenaAfterUmiCost();

    return TRUE;
  }

  if (wasUmiField) {
    ResetFieldToArenaAfterUmiCost();
    return TRUE;
  }

  return FALSE;
}

static struct DuelCard *GetActivatingDaedalusZone(void)
{
  return gFixedZones[gMonEffect.row][gMonEffect.zone];
}

static void DestroyAllOtherFieldCards(struct DuelCard *protectedZone)
{
  u8 row;
  u8 col;
  u8 destroyed = FALSE;

  /* walk gDuel.board directly; gFixedZones column order differs on
   * opponent rows, so row/col checks against gMonEffect can skip the wrong slot. */
  for (row = 0; row < 4; row++) {
    u8 graveyardDuelist = TurnDuelistForFixedRow(row);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];

      if (zone == protectedZone || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (Duel_DestroyZone(zone, graveyardDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;

      destroyed = TRUE;
    }
  }

  if (destroyed) {
    NotifyDynamicEquipFieldChanged();
    UpdateDuelGfxExceptField();
  }
}

unsigned char CanActivateLeviaDragonDaedalus(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != LEVIA_DRAGON_DAEDALUS)
    return FALSE;

  if (!IsOnActiveDuelistMonsterRow())
    return FALSE;

  if (!CanPayLeviaDragonDaedalusCost())
    return FALSE;

  zone = GetActivatingDaedalusZone();
  return CanUseMonsterEffect(zone);
}

void ActivateLeviaDragonDaedalusEffect(void)
{
  struct DuelCard *protectedZone = GetActivatingDaedalusZone();

  if (protectedZone->id != LEVIA_DRAGON_DAEDALUS)
    return;

  Duel_ShowEffectTextTyped(LEVIA_DRAGON_DAEDALUS, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (!PayLeviaDragonDaedalusCost())
    return;

  if (IsDuelOver() == TRUE)
    return;

  DestroyAllOtherFieldCards(protectedZone);

  if (IsDuelOver() == TRUE)
    return;

  CheckWinConditionExodia(WhoseTurn());
  TryActivatingPermanentEffects();
}
