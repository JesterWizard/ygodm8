#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

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

static u8 FixedOwnerOfBackrow(u8 fixedRow)
{
  if (fixedRow == PLAYER_BACKROW)
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static u8 BounceSpellTrapToHand(struct DuelCard *zone, u8 fixedRow)
{
  u8 fixedOwner = FixedOwnerOfBackrow(fixedRow);
  u8 turnDuelist = TurnDuelistForFixed(fixedOwner);
  s8 empty;
  u16 cardId;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  empty = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (empty < 0)
    return FALSE;

  cardId = zone->id;
  ClearZone(zone);
  InitHandSlotFromCard(gTurnHands[turnDuelist][empty], cardId);
  return TRUE;
}

static u8 IsSpellTrapZone(struct DuelCard *zone)
{
  u8 tg;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  tg = GetTypeGroup(zone->id);
  return tg == TYPE_GROUP_SPELL || tg == TYPE_GROUP_TRAP;
}

unsigned char CanActivateTORNADO_BIRD(void)
{
  struct DuelCard *zone;
  u8 row;
  u8 col;
  u8 count = 0;

  if (gMonEffect.id != TORNADO_BIRD)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != TORNADO_BIRD)
    return FALSE;

  /* FLIP trigger needs flip hook. Ceiling: once via usage. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    if (row != OPPONENT_BACKROW && row != PLAYER_BACKROW)
      continue;
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsSpellTrapZone(gFixedZones[row][col]))
        count++;
    }
  }

  return count >= 1;
}

void ActivateTORNADO_BIRDEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 row;
  u8 col;
  u8 bounced = 0;

  Duel_ShowEffectTextTyped(TORNADO_BIRD, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW && bounced < 2; row++) {
    if (row != OPPONENT_BACKROW && row != PLAYER_BACKROW)
      continue;
    for (col = 0; col < MAX_ZONES_IN_ROW && bounced < 2; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (!IsSpellTrapZone(zone))
        continue;
      if (BounceSpellTrapToHand(zone, row))
        bounced++;
    }
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
