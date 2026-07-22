#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "morphtronic_radion.h"

#define RADION_ATK_BONUS 800
#define RADION_DEF_BONUS 1000

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

u8 GetDuelistForZone(struct DuelCard *zone);

static u8 IsMorphtronic(u16 cardId)
{
  if (cardId == CARD_NONE || !Duel_CardIsMonster(cardId))
    return FALSE;
  return Duel_CardNameContains(cardId, sMorphtronicName);
}

static struct DuelCard *FindFaceUpRadion(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == MORPHTRONIC_RADION)
      return zone;
  }
  return NULL;
}

void ApplyMorphtronicRadionStatBoostToCardInfo(const struct DuelCard *zone)
{
  u8 controller;
  struct DuelCard *radion;

  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return;
  if (!IsMorphtronic(zone->id))
    return;

  controller = GetDuelistForZone((struct DuelCard *)zone);
  if (controller > DUEL_OPPONENT)
    return;

  radion = FindFaceUpRadion(controller);
  if (radion == NULL)
    return;

  if (radion->isDefending)
    gCardInfo.def = Duel_ClampStat((u32)gCardInfo.def + RADION_DEF_BONUS);
  else
    gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk + RADION_ATK_BONUS);
}

unsigned char CanActivateMORPHTRONIC_RADION(void)
{
  if (gMonEffect.id != MORPHTRONIC_RADION)
    return FALSE;

  /* Continuous Morphtronic boost via ApplyMorphtronicRadionStatBoostToCardInfo. */
  return FALSE;
}

void ActivateMORPHTRONIC_RADIONEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_RADION, 2);
}
