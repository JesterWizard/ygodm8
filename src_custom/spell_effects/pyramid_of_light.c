#include "global.h"
#include "common-chax.h"
#include "god_card.h"
#include "pyramid_of_light.h"
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
      ClearZoneAndSendMonToGraveyard(row[i], duelist);
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
  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
}

APPEND_TEXT void EffectPyramidOfLight(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyGodCardsOnMonsterFields();
  ActivatePyramidOfLightZone(zone);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = PYRAMID_OF_LIGHT;
    ActivateCardEffectText();
  }
}
