#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "morphtronic_boomboxen.h"

u8 GetDuelistForZone(struct DuelCard *zone);

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

static u8 IsMorphtronicMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicName);
}

static struct DuelCard *FindDefBoomboxen(u8 controller)
{
  u8 fixedRow = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone == NULL || zone->id != MORPHTRONIC_BOOMBOXEN || !zone->isFaceUp)
      continue;
    if (!zone->isDefending)
      continue;
    if (zone->effectUsedThisTurn)
      continue;

    return zone;
  }

  return NULL;
}

void MorphtronicBoomboxen_MaybeMarkExtraAttackOnPlacement(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != MORPHTRONIC_BOOMBOXEN)
    return;

  if (zone->isDefending)
    return;

  zone->unk4 = 2;
}

u8 TryNegateDeclaredAttackWithMorphtronicBoomboxen(const struct DuelCard *defender)
{
  struct DuelCard *boomboxen;
  u8 controller;

  if (defender == NULL || defender->id == CARD_NONE)
    return FALSE;

  if (!IsMorphtronicMonster(defender->id))
    return FALSE;
  if (!IsCardFaceUp((struct DuelCard *)defender))
    return FALSE;

  controller = GetDuelistForZone((struct DuelCard *)defender);
  if (controller > DUEL_OPPONENT)
    return FALSE;

  boomboxen = FindDefBoomboxen(controller);
  if (boomboxen == NULL)
    return FALSE;

  boomboxen->effectUsedThisTurn = TRUE;
  Duel_ShowEffectTextTyped(MORPHTRONIC_BOOMBOXEN, 2);
  return TRUE;
}

unsigned char CanActivateMORPHTRONIC_BOOMBOXEN(void)
{
  if (gMonEffect.id != MORPHTRONIC_BOOMBOXEN)
    return FALSE;

  /* ATK double attack via MorphtronicBoomboxen_MaybeMarkExtraAttackOnPlacement +
   * TryUnlockUnk4MarkedExtraAttack; DEF negate via
   * TryNegateDeclaredAttackWithMorphtronicBoomboxen. */
  return FALSE;
}

void ActivateMORPHTRONIC_BOOMBOXENEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_BOOMBOXEN, 2);
}
