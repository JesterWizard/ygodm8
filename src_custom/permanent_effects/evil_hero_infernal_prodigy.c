#include "global.h"
#include "common-chax.h"
#include "blast_held_by_a_tribute.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "evil_hero_infernal_prodigy.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

void TryApplyEvilHeroInfernalProdigyEndPhase(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id != EVIL_HERO_INFERNAL_PRODIGY)
      continue;

    if (!BlastHeldByATribute_WasTributeSummoned(zone))
      continue;

    Duel_ShowEffectTextTyped(EVIL_HERO_INFERNAL_PRODIGY, 9);

    if (Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;

    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }
}

unsigned char ShouldActivateEVIL_HERO_INFERNAL_PRODIGY(void)
{
  /* ponytail: empty-field hand SS is FromHand activated; End-Phase tribute draw via TryApplyEvilHeroInfernalProdigyEndPhase. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_HERO_INFERNAL_PRODIGY(void)
{
}
