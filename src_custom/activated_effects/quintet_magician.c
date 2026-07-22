#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static void DestroyAllOpponentCards(void)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE)
        continue;

      if (IsGodCard(zone->id))
        continue;

      if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;
    }
  }

  NotifyDynamicEquipFieldChanged();
}

static u8 OpponentControlsCard(void)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE && !IsGodCard(zone->id))
        return TRUE;
    }
  }

  return FALSE;
}

static void DestroyOppCardsForController(u8 controller)
{
  u8 monRow = Duel_FixedMonsterRowForDuelist(controller == DUEL_PLAYER ? DUEL_OPPONENT
                                                                       : DUEL_PLAYER);
  u8 backRow = controller == DUEL_PLAYER ? OPPONENT_BACKROW : PLAYER_BACKROW;
  u8 oppTurn = Duel_TurnDuelistForFixedDuelist(controller == DUEL_PLAYER ? DUEL_OPPONENT
                                                                         : DUEL_PLAYER);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[monRow][col];

    if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;
    if (Duel_DestroyZone(zone, oppTurn, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[backRow][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    if (Duel_DestroyZone(zone, oppTurn, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }
  NotifyDynamicEquipFieldChanged();
}

void TryQuintetMagicianOnMonsterPlacement(struct DuelCard *zone)
{
  u8 controller;

  if (zone == NULL || zone->id != QUINTET_MAGICIAN || gHideEffectText)
    return;
  if (EffectOpt_IsUsed(QUINTET_MAGICIAN))
    return;

  controller = GetDuelistForZone(zone);
  if (controller > DUEL_OPPONENT)
    return;

  Duel_ShowEffectTextTyped(QUINTET_MAGICIAN, 8);
  /* Fusion-with-5-different stand-in: any placement wipe opp field. */
  DestroyOppCardsForController(controller);
  EffectOpt_MarkUsed(QUINTET_MAGICIAN);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateQUINTET_MAGICIAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != QUINTET_MAGICIAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != QUINTET_MAGICIAN)
    return FALSE;

  /* On-summon wipe via TryQuintetMagicianOnMonsterPlacement.
   * Ceiling: untributable/undestroyable need continuous hooks.
   * OPT destroy all opp cards (ignition). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OpponentControlsCard();
}

void ActivateQUINTET_MAGICIANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(QUINTET_MAGICIAN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!OpponentControlsCard())
    return;

  DestroyAllOpponentCards();

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
