#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static void DestroyAllOpponentCards(void)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE)
        continue;

      if (IsGodCard(zone->id))
        continue;

      if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;
    }
  }

  NotifyDynamicEquipFieldChanged();
}

static u8 OpponentControlsCard(void)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE && !IsGodCard(zone->id))
        return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateQUINTET_MAGICIAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != QUINTET_MAGICIAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != QUINTET_MAGICIAN)
    return FALSE;

  /* Fusion-with-5-Spellcasters gate + untributable/undestroyable need
   * fusion/summon hooks. Ceiling: once via usage destroy all opp cards. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OpponentControlsCard();
}

void ActivateQUINTET_MAGICIANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(QUINTET_MAGICIAN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!OpponentControlsCard())
    return;

  DestroyAllOpponentCards();

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
