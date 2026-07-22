#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sHarpieName[] APPEND_RODATA = "Harpie";

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static u8 IsHarpieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 BounceOppZoneToHand(struct DuelCard *zone)
{
  u8 typeGroup;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]) < 0)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  if (typeGroup == TYPE_GROUP_MONSTER)
    return Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) == DUEL_ACTION_OK;

  if (typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP) {
    s8 empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
    u16 cardId;

    if (empty < 0)
      return FALSE;

    cardId = zone->id;
    ClearZone(zone);
    InitHandSlotFromCard(gTurnHands[INACTIVE_DUELIST][empty], cardId);
    return TRUE;
  }

  return FALSE;
}

static u8 OwnMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 OppMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

static u8 OppBackrowFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? OPPONENT_BACKROW : PLAYER_BACKROW;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (fixedRow == OppMonsterFixedRow() || fixedRow == OppBackrowFixedRow()) {
    if (FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]) < 0)
      return FALSE;
    return TRUE;
  }

  if (fixedRow == OwnMonsterFixedRow())
    return IsHarpieMonster(zone->id)
        && FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0;

  return FALSE;
}

static u8 FieldHasTarget(void)
{
  u8 row;
  u8 col;
  u8 rows[3];
  u8 r;

  rows[0] = OppMonsterFixedRow();
  rows[1] = OppBackrowFixedRow();
  rows[2] = OwnMonsterFixedRow();

  for (r = 0; r < 3; r++) {
    row = rows[r];
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 ok = FALSE;

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (fixedRow == OppMonsterFixedRow() || fixedRow == OppBackrowFixedRow())
    ok = BounceOppZoneToHand(zone);
  else
    ok = Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) == DUEL_ACTION_OK;

  if (!ok)
    return;

  EffectOpt_MarkUsed(CYBER_SLASH_HARPIE_LADY);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;
  u8 rows[2];
  u8 r;

  rows[0] = OppMonsterFixedRow();
  rows[1] = OppBackrowFixedRow();

  for (r = 0; r < 2; r++) {
    row = rows[r];
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  row = OwnMonsterFixedRow();
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(row, col)) {
      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateCYBER_SLASH_HARPIE_LADY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CYBER_SLASH_HARPIE_LADY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CYBER_SLASH_HARPIE_LADY)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * OPT bounce 1 opp card or your Harpie to hand (EffectOpt). */
  if (EffectOpt_IsUsed(CYBER_SLASH_HARPIE_LADY))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTarget();
}

void ActivateCYBER_SLASH_HARPIE_LADYEffect(void)
{
  Duel_ShowEffectTextTyped(CYBER_SLASH_HARPIE_LADY, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(CYBER_SLASH_HARPIE_LADY))
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
