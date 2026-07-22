#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "morphtronic_magnen.h"

static struct DuelCard *FindFaceUpMagnen(u8 defenderDuelist, u8 defending)
{
  u8 fixedRow = Duel_FixedMonsterRowForDuelist(defenderDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone == NULL || zone->id != MORPHTRONIC_MAGNEN || !zone->isFaceUp)
      continue;
    if (zone->isDefending != defending)
      continue;

    return zone;
  }

  return NULL;
}

struct DuelCard *MorphtronicMagnen_GetForcedAttackTarget(u8 defenderDuelist)
{
  return FindFaceUpMagnen(defenderDuelist, TRUE);
}

u8 MorphtronicMagnen_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE || zone->id == MORPHTRONIC_MAGNEN)
    return TRUE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return TRUE;

  return MorphtronicMagnen_GetForcedAttackTarget(
      Duel_FixedDuelistForMonsterRow(fixedRow)) == NULL;
}

static struct DuelCard *HighestAtkFaceUpMonsterOnRow(u8 fixedMonsterRow)
{
  u8 col;
  struct DuelCard *best = NULL;
  u16 bestAtk = 0;
  u8 found = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedMonsterRow][col];
    u16 atk;

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;
    if (!IsCardFaceUp(zone) && zone->isDefending)
      continue;

    atk = Duel_GetZoneFinalAtk(zone);
    if (!found || atk > bestAtk) {
      best = zone;
      bestAtk = atk;
      found = TRUE;
    }
  }

  return best;
}

u8 MorphtronicMagnen_CanSelectAttackTarget(const struct DuelCard *attacker,
                                           const struct DuelCard *defender)
{
  u8 fixedRow;
  u8 col;
  struct DuelCard *highest;

  if (attacker == NULL || defender == NULL)
    return TRUE;

  if (attacker->id != MORPHTRONIC_MAGNEN || attacker->isDefending)
    return TRUE;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)defender, &fixedRow, &col))
    return TRUE;

  highest = HighestAtkFaceUpMonsterOnRow(fixedRow);
  if (highest == NULL)
    return TRUE;

  return defender == highest;
}

unsigned char CanActivateMORPHTRONIC_MAGNEN(void)
{
  if (gMonEffect.id != MORPHTRONIC_MAGNEN)
    return FALSE;

  /* ATK highest-ATK-only via MorphtronicMagnen_CanSelectAttackTarget; DEF redirect
   * via MorphtronicMagnen_GetForcedAttackTarget. */
  return FALSE;
}

void ActivateMORPHTRONIC_MAGNENEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_MAGNEN, 2);
}
