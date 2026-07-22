#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spined_gillman.h"

u8 GetDuelistForZone(struct DuelCard *zone);

#define SPINED_GILLMAN_ATK_BONUS 400

static u8 IsFishSeaAqua(u16 cardId)
{
  if (cardId == CARD_NONE || !Duel_CardIsMonster(cardId))
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_FISH)
      || Duel_CardHasMonsterType(cardId, TYPE_SEA_SERPENT)
      || Duel_CardHasMonsterType(cardId, TYPE_AQUA);
}

static u8 ControllerHasFaceUpGillman(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == SPINED_GILLMAN)
      return TRUE;
  }
  return FALSE;
}

void ApplySpinedGillmanAtkBoostToCardInfo(const struct DuelCard *zone)
{
  u8 controller;

  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return;
  if (!IsFishSeaAqua(zone->id))
    return;

  controller = GetDuelistForZone((struct DuelCard *)zone);
  if (controller > DUEL_OPPONENT)
    return;
  if (!ControllerHasFaceUpGillman(controller))
    return;

  gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk + SPINED_GILLMAN_ATK_BONUS);
}

unsigned char CanActivateSPINED_GILLMAN(void)
{
  if (gMonEffect.id != SPINED_GILLMAN)
    return FALSE;

  /* Continuous +400 via ApplySpinedGillmanAtkBoostToCardInfo. */
  return FALSE;
}

void ActivateSPINED_GILLMANEffect(void)
{
  Duel_ShowEffectTextTyped(SPINED_GILLMAN, 2);
}
