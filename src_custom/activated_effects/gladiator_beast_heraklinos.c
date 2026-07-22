#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 HandHasDiscardableCard(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnHands[ACTIVE_DUELIST][col]->id != CARD_NONE)
      return TRUE;
  }

  return FALSE;
}

static u8 IsOppFieldCard(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow < INACTIVE_DUELIST_MONSTER_ROW || fixedRow > INACTIVE_DUELIST_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 OppFieldHasCard(void)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsOppFieldCard(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 GraveyardDuelistForTarget(u8 fixedRow)
{
  if (fixedRow == INACTIVE_DUELIST_MONSTER_ROW || fixedRow == INACTIVE_DUELIST_BACKROW)
    return INACTIVE_DUELIST;

  return ACTIVE_DUELIST;
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsOppFieldCard(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (Duel_DiscardRandomFromHand(ACTIVE_DUELIST, 1, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DestroyZone(zone, GraveyardDuelistForTarget(fixedRow), TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  EffectOpt_MarkUsed(GLADIATOR_BEAST_HERAKLINOS);
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

static u8 ScoreTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER) {
    SetCardInfo(zone->id);
    return 100 + gCardInfo.atk;
  }

  return 80;
}

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;
  u8 bestRow = 0xFF;
  u8 bestCol = 0xFF;
  u8 bestScore = 0;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      u8 score;

      if (!IsOppFieldCard(row, col))
        continue;

      score = ScoreTarget(row, col);
      if (score > bestScore) {
        bestScore = score;
        bestRow = row;
        bestCol = col;
      }
    }
  }

  if (bestRow == 0xFF)
    return FALSE;

  *outRow = bestRow;
  *outCol = bestCol;
  return TRUE;
}

unsigned char CanActivateGLADIATOR_BEAST_HERAKLINOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GLADIATOR_BEAST_HERAKLINOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GLADIATOR_BEAST_HERAKLINOS)
    return FALSE;

  /* Either-turn chain negate needs chain hook outside this file.
   * OPT discard 1 → destroy 1 opponent card (EffectOpt). */
  if (EffectOpt_IsUsed(GLADIATOR_BEAST_HERAKLINOS))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return HandHasDiscardableCard() && OppFieldHasCard();
}

void ActivateGLADIATOR_BEAST_HERAKLINOSEffect(void)
{
  u8 bestRow;
  u8 bestCol;

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_HERAKLINOS, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(GLADIATOR_BEAST_HERAKLINOS))
    return;

  if (!HandHasDiscardableCard() || !OppFieldHasCard())
    return;

  if (!AiPickDestroyTarget(&bestRow, &bestCol))
    return;

  ResolveDestroyTarget(bestRow, bestCol);
}
