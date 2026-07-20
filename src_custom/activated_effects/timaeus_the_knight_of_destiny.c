#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static u16 HighestFieldAtk(void)
{
  u8 col;
  u16 highest = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    u16 atk;

    if (zone != NULL && zone->id != CARD_NONE
        && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER) {
      atk = Duel_GetZoneFinalAtk(zone);
      if (atk > highest)
        highest = atk;
    }

    zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];
    if (zone != NULL && zone->id != CARD_NONE
        && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER) {
      atk = Duel_GetZoneFinalAtk(zone);
      if (atk > highest)
        highest = atk;
    }
  }

  return highest;
}

unsigned char CanActivateTIMAEUS_THE_KNIGHT_OF_DESTINY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != TIMAEUS_THE_KNIGHT_OF_DESTINY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != TIMAEUS_THE_KNIGHT_OF_DESTINY)
    return FALSE;

  /* ponytail: unaffected + once-per-battle damage calc FALSE.
   * Ceiling: OPT set ATK/DEF ≈ highest field ATK via tempStage. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return HighestFieldAtk() > 0;
}

void ActivateTIMAEUS_THE_KNIGHT_OF_DESTINYEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 highest;
  u16 originalAtk;
  s32 delta;
  s8 stages;

  Duel_ShowEffectTextTyped(TIMAEUS_THE_KNIGHT_OF_DESTINY, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  highest = HighestFieldAtk();
  if (highest == 0)
    return;

  originalAtk = (self->id < NUM_TOTAL_CARDS) ? gCardData_NEW[self->id].atk : 0;
  delta = (s32)highest - (s32)originalAtk;
  if (delta >= 0)
    stages = (s8)((delta + 499) / 500);
  else
    stages = (s8)((delta - 499) / 500);

  if (stages > 126)
    stages = 126;
  if (stages < -126)
    stages = -126;

  self->tempStage = stages;
  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
