#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "pyramid_of_light.h"
#include "imperial_order.h"
#include "spell_effects.h"

static u8 ZoneHasActivePyramidOfLight(const struct DuelCard *zone)
{
  return zone != NULL
      && zone->id == PYRAMID_OF_LIGHT
      && zone->isFaceUp == TRUE
      && zone->isLocked == TRUE;
}

u8 IsActivatedPyramidOfLightZone(const struct DuelCard *zone)
{
  return ZoneHasActivePyramidOfLight(zone);
}

u8 IsPyramidOfLightActiveOnField(void)
{
  u8 row;
  u8 i;

  if (IsImperialOrderNegatingSpell(PYRAMID_OF_LIGHT))
    return FALSE;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (ZoneHasActivePyramidOfLight(gFixedZones[row][i]))
        return TRUE;
    }
  }

  return FALSE;
}

u8 ShouldBlockGodCardSummon(u16 cardId)
{
  if (!IsPyramidOfLightActiveOnField())
    return FALSE;

  return IsGodCard(cardId) == TRUE;
}

static void DestroyGodCardsInMonsterRow(struct DuelCard **row, u8 duelist)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsGodCard(row[i]->id) == TRUE)
      Duel_DestroyZone(row[i], duelist, FALSE);
  }
}

static void DestroyGodCardsOnMonsterFields(void)
{
  DestroyGodCardsInMonsterRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW], INACTIVE_DUELIST);
  DestroyGodCardsInMonsterRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW], ACTIVE_DUELIST);
}

void EnforcePyramidOfLightGodBan(void)
{
  if (!IsPyramidOfLightActiveOnField())
    return;

  DestroyGodCardsOnMonsterFields();
}

static void ActivatePyramidOfLightZone(struct DuelCard *zone)
{
  Duel_ActivateContinuousZone(zone);
}

APPEND_TEXT void EffectPyramidOfLight(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyGodCardsOnMonsterFields();
  ActivatePyramidOfLightZone(zone);
  Duel_ShowEffectText(PYRAMID_OF_LIGHT);
}
