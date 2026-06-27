#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "card.h"
#include "duel.h"
#include "duel_helpers.h"
#include "harpie_lady_1.h"

void ApplyHarpieLady1WindAtkBoost(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  /* Only affects monsters.  gCardInfo.type was already set by the caller
   * (SetCardInfo__Replacement in ApplyFieldZoneStatsToCardInfo).  Do NOT
   * call GetTypeGroup here — it calls SetCardInfo internally and would
   * reset gCardInfo.atk/def back to base, undoing any field-percent or
   * stage modifications applied by the caller. */
  if (gCardInfo.type >= TYPE_SPELL)
    return;

  /* Only affects WIND monsters */
  if (gCardInfo.attribute != ATTRIBUTE_WIND)
    return;

  /* Check both monster rows for a face-up Harpie Lady 1 */
  for (fixedRow = 1; fixedRow <= 2; fixedRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *hl1 = gFixedZones[fixedRow][col];
      if (hl1 != NULL && hl1->id == HARPIE_LADY_1 && hl1->isFaceUp) {
        gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk + 300);
        return;
      }
    }
  }
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void HarpieLady1_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = HARPIE_LADY_1;
  ApplyHarpieLady1WindAtkBoost(&zone);
  /* No crash = pass */
}
#endif
