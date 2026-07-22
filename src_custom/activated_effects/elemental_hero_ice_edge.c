#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_ice_edge.h"
#include "monster_effect_usage.h"

u8 CanElementalHeroIceEdgeAttackDirectly(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == ELEMENTAL_HERO_ICE_EDGE && zone->unkTwo;
}

void ClearElementalHeroIceEdgeDirectAttackFlags(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone->id == ELEMENTAL_HERO_ICE_EDGE)
      zone->unkTwo = FALSE;
  }
}

unsigned char CanActivateElementalHeroIceEdge(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_ICE_EDGE)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) > 0;
}

void ActivateElementalHeroIceEdgeEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowCardEffectText(ELEMENTAL_HERO_ICE_EDGE,
                          CARD_EFFECT_TEXT_ELEMENTAL_HERO_ICE_EDGE_POPUP_1);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  /* Direct-attack grant (unkTwo); destroy Set S/T on direct damage via ApplyElementalHeroIceEdgeBattleEffect. */
  zone->unkTwo = TRUE;
}
