#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "evil_hero_malicious_fiend.h"

struct DuelCard *EvilHeroMaliciousFiend_GetForcedAttackTarget(u8 defenderDuelist)
{
  u8 fixedRow = Duel_FixedMonsterRowForDuelist(defenderDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone == NULL || zone->id != EVIL_HERO_MALICIOUS_FIEND)
      continue;
    if (!zone->isFaceUp)
      continue;
    if (zone->isDefending)
      continue;
    return zone;
  }

  return NULL;
}

u8 EvilHeroMaliciousFiend_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE || zone->id == EVIL_HERO_MALICIOUS_FIEND)
    return TRUE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return TRUE;

  return EvilHeroMaliciousFiend_GetForcedAttackTarget(
      Duel_FixedDuelistForMonsterRow(fixedRow)) == NULL;
}

unsigned char ShouldActivateEVIL_HERO_MALICIOUS_FIEND(void)
{
  /* Pierce via ApplySimplePiercersBattleEffect; forced attack via
   * EvilHeroMaliciousFiend_GetForcedAttackTarget + sForcedAttackRedirects. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_HERO_MALICIOUS_FIEND(void)
{
}
