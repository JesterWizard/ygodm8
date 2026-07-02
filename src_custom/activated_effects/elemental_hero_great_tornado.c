#include "global.h"
#include "common-chax.h"
#include "card.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_great_tornado.h"
#include "god_card.h"
#include "mini_card.h"

void TryActivatingPermanentEffects(void);
void UpdateDuelGfxExceptField(void);

static u8 IsActiveFaceUpGreatTornado(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ELEMENTAL_HERO_GREAT_TORNADO)
    return FALSE;

  return IsCardFaceUp(zone);
}

static u8 ZoneQualifiesForGreatTornadoHalving(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  /* ponytail: GetTypeGroup calls SetCardInfo and would clobber gCardInfo.atk/def
   * that the stat pipeline already computed for zone. */
  if (gCardInfo.id != zone->id || gCardInfo.type >= TYPE_SPELL)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  return IsCardFaceUp((struct DuelCard *)zone);
}

static struct DuelCard *FindActiveGreatTornado(u8 *outRow)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (IsActiveFaceUpGreatTornado(zone)) {
        *outRow = row;
        return zone;
      }
    }
  }

  return NULL;
}

static u8 ZoneIsOpponentMonsterForGreatTornado(const struct DuelCard *zone,
                                               struct DuelCard *greatTornadoZone)
{
  u8 zoneRow;
  u8 col;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &zoneRow, &col))
    return FALSE;

  return zoneRow == Duel_OpponentMonsterRowForZone(greatTornadoZone);
}

u8 ElementalHeroGreatTornado_IsActiveOnField(void)
{
  u8 row;

  return FindActiveGreatTornado(&row) != NULL;
}

void ApplyGreatTornadoStatHalving(const struct DuelCard *zone)
{
  struct DuelCard *greatTornadoZone;
  u8 unusedRow;

  if (!ZoneQualifiesForGreatTornadoHalving(zone))
    return;

  greatTornadoZone = FindActiveGreatTornado(&unusedRow);
  if (greatTornadoZone == NULL)
    return;

  if (!ZoneIsOpponentMonsterForGreatTornado(zone, greatTornadoZone))
    return;

  gCardInfo.atk = (u16)(gCardInfo.atk / 2);
  gCardInfo.def = (u16)(gCardInfo.def / 2);
}

void ElementalHeroGreatTornado_RefreshStatsIfActive(void)
{
  if (ElementalHeroGreatTornado_IsActiveOnField())
    RefreshFieldMonsterStatOverlays();
}

void TryElementalHeroGreatTornadoOnMonsterPlacement(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return;

  ElementalHeroGreatTornado_RefreshStatsIfActive();
}

void ElementalHeroGreatTornado_OnZoneCleared(const struct DuelCard *zone)
{
  if (zone != NULL && zone->id == ELEMENTAL_HERO_GREAT_TORNADO)
    UpdateDuelGfxExceptField();
}

void ElementalHeroGreatTornado_OnFusionSummoned(void)
{
  Duel_ShowEffectText(ELEMENTAL_HERO_GREAT_TORNADO);

  if (IsDuelOver() == TRUE)
    return;

  UpdateDuelGfxExceptField();

  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
