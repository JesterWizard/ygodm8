#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "weather_report.h"

static u8 OpponentBackrowHasSwordsOfRevealingLight(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[INACTIVE_DUELIST_BACKROW][i]->id == SWORDS_OF_REVEALING_LIGHT)
      return TRUE;
  }

  return FALSE;
}

static void DestroyOpponentSwordsOfRevealingLight(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];

    if (zone->id != SWORDS_OF_REVEALING_LIGHT)
      continue;

    ClearZoneAndSendMonToGraveyard(zone, INACTIVE_DUELIST);
  }
}

static u8 WeatherReportIsOnActiveDuelistMonsterRow(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gMonEffect.row == PLAYER_MONSTER_ROW;

  return gMonEffect.row == OPPONENT_MONSTER_ROW;
}

unsigned char CanActivateWeatherReport(void)
{
  if (gMonEffect.id != WEATHER_REPORT)
    return FALSE;

  if (!WeatherReportIsOnActiveDuelistMonsterRow())
    return FALSE;

  return OpponentBackrowHasSwordsOfRevealingLight();
}

void ActivateWeatherReportEffect(void)
{
  DestroyOpponentSwordsOfRevealingLight();

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = WEATHER_REPORT;
    ActivateCardEffectText();
  }
}
