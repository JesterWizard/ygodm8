#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "morphtronic_boarden.h"

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

u8 GetDuelistForZone(struct DuelCard *zone);

static u8 IsMorphtronic(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  return Duel_CardNameContains(cardId, sMorphtronicName);
}

static struct DuelCard *FindFaceUpBoarden(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == MORPHTRONIC_BOARDEN)
      return zone;
  }
  return NULL;
}

u8 MorphtronicBoarden_PreventsBattleDestroy(const struct DuelCard *zone)
{
  u8 controller;
  struct DuelCard *boarden;

  if (zone == NULL || zone->id == CARD_NONE || zone->id == MORPHTRONIC_BOARDEN)
    return FALSE;
  if (!IsMorphtronic(zone->id))
    return FALSE;

  controller = GetDuelistForZone((struct DuelCard *)zone);
  if (controller > DUEL_OPPONENT)
    return FALSE;

  boarden = FindFaceUpBoarden(controller);
  return boarden != NULL && boarden->isDefending;
}

u8 MorphtronicBoarden_CanMorphtronicAttackDirectly(const struct DuelCard *attacker)
{
  u8 controller;
  struct DuelCard *boarden;

  if (attacker == NULL || !IsMorphtronic(attacker->id))
    return FALSE;

  controller = GetDuelistForZone((struct DuelCard *)attacker);
  if (controller > DUEL_OPPONENT)
    return FALSE;

  boarden = FindFaceUpBoarden(controller);
  return boarden != NULL && !boarden->isDefending;
}

unsigned char CanActivateMORPHTRONIC_BOARDEN(void)
{
  if (gMonEffect.id != MORPHTRONIC_BOARDEN)
    return FALSE;

  /* ATK direct / DEF battle protect via MorphtronicBoarden_* helpers. */
  return FALSE;
}

void ActivateMORPHTRONIC_BOARDENEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_BOARDEN, 2);
}
