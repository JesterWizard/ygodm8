#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

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

static u8 OppHandHasRoom(void)
{
  return NumEmptyZonesInRow(gTurnHands[INACTIVE_DUELIST]) > 0;
}

static u8 BounceOppZoneToHand(struct DuelCard *zone)
{
  u8 typeGroup;

  if (zone == NULL || zone->id == CARD_NONE || !OppHandHasRoom())
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  if (typeGroup == TYPE_GROUP_MONSTER)
    return Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) == DUEL_ACTION_OK;

  if (typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP) {
    s8 empty;
    u16 cardId;

    empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
    if (empty < 0)
      return FALSE;

    cardId = zone->id;
    ClearZone(zone);
    InitHandSlotFromCard(gTurnHands[INACTIVE_DUELIST][empty], cardId);
    return TRUE;
  }

  return FALSE;
}

static u8 BounceOneOppCard(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE)
        continue;

      if (BounceOppZoneToHand(zone))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 CanBounceOppCard(void)
{
  u8 row;
  u8 col;

  if (!OppHandHasRoom())
    return FALSE;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE)
        return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateSIMORGH_BIRD_OF_ANCESTRY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SIMORGH_BIRD_OF_ANCESTRY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SIMORGH_BIRD_OF_ANCESTRY)
    return FALSE;

  /* ponytail: WIND tribute-reduce continuous + hand-as-Normal Monster need
   * summon/permanent hooks. Ceiling: OPT return up to 2 opp cards to hand. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanBounceOppCard();
}

void ActivateSIMORGH_BIRD_OF_ANCESTRYEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 bounced = 0;

  Duel_ShowEffectTextTyped(SIMORGH_BIRD_OF_ANCESTRY, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  while (bounced < 2 && BounceOneOppCard())
    bounced++;

  if (bounced == 0)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
