#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "lady_of_d.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 ControllerHasFaceUpLadyOfD(u8 defenderDuelist)
{
  u8 fixedRow = Duel_FixedMonsterRowForDuelist(defenderDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone != NULL && zone->id == LADY_OF_D && IsCardFaceUp(zone))
      return TRUE;
  }

  return FALSE;
}

u8 LadyOfD_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 defenderDuelist;

  if (zone == NULL || zone->id == CARD_NONE || zone->id == LADY_OF_D)
    return TRUE;

  if (!Duel_CardHasMonsterType(zone->id, TYPE_DRAGON))
    return TRUE;

  if (!IsCardFaceUp(zone) && zone->isDefending)
    return TRUE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return TRUE;

  defenderDuelist = Duel_FixedDuelistForMonsterRow(fixedRow);
  if (!ControllerHasFaceUpLadyOfD(defenderDuelist))
    return TRUE;

  return FALSE;
}

static u8 IsDragonMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_DRAGON);
}

static u8 HandHasDragonMonster(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsDragonMonster(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 IsHandDragonMonster(u16 cardId)
{
  return IsDragonMonster(cardId);
}

unsigned char CanActivateLADY_OF_D(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != LADY_OF_D)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != LADY_OF_D)
    return FALSE;

  /* Dragon attack lock via LadyOfD_CanAttackMonsterZone.
   * OPT discard 1 Dragon from hand (destroy-save stand-in). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return HandHasDragonMonster();
}

void ActivateLADY_OF_DEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(LADY_OF_D, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, IsHandDragonMonster, TRUE) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
