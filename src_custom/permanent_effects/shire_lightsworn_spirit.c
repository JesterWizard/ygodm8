#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "shire_lightsworn_spirit.h"

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

#define SHIRE_DISTINCT_CAP 32
#define SHIRE_ATK_PER_NAME 300
#define SHIRE_END_PHASE_MILL 2

static u8 IsLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

static u8 CountDistinctLightswornNamesInGy(u8 fixedDuelist)
{
  u16 seen[SHIRE_DISTINCT_CAP];
  u8 distinct = 0;
  u8 i;
  u8 j;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsLightswornMonster(cardId) ? 1 : 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    u8 already = FALSE;

    if (!IsLightswornMonster(cardId))
      continue;

    for (j = 0; j < distinct; j++) {
      if (seen[j] == cardId) {
        already = TRUE;
        break;
      }
    }

    if (already)
      continue;

    if (distinct >= SHIRE_DISTINCT_CAP)
      break;

    seen[distinct++] = cardId;
  }

  return distinct;
}

static u16 ShireCurrentAtk(struct DuelCard *zone)
{
  u8 fixedDuelist = GetDuelistForZone(zone);
  u32 baseAtk = gCardData_NEW[zone->id].atk;

  if (fixedDuelist == 0xFF)
    return (u16)baseAtk;

  return Duel_StatFromCount(
      CountDistinctLightswornNamesInGy(fixedDuelist),
      SHIRE_ATK_PER_NAME,
      baseAtk);
}

u8 ShireLightswornSpirit_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;

  if (zone == NULL || zone->id != SHIRE_LIGHTSWORN_SPIRIT)
    return FALSE;

  atk = ShireCurrentAtk(zone);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, atk, gCardData_NEW[zone->id].def);
  return TRUE;
}

void TryApplyShireEndPhase(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 turn = ACTIVE_DUELIST;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !zone->isFaceUp || zone->id != SHIRE_LIGHTSWORN_SPIRIT)
      continue;
    Duel_ShowEffectTextTyped(SHIRE_LIGHTSWORN_SPIRIT, 2);
    Duel_MillTopDeckCards(turn, SHIRE_END_PHASE_MILL, TRUE);
    return;
  }
}

unsigned char ShouldActivateSHIRE_LIGHTSWORN_SPIRIT(void)
{
  /* ATK overlay via ShireLightswornSpirit_ApplyDynamicZoneStats; EP mill via TryApplyShireEndPhase. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateSHIRE_LIGHTSWORN_SPIRIT(void)
{
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ShireLightswornSpirit_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = SHIRE_LIGHTSWORN_SPIRIT;
  ShireLightswornSpirit_ApplyDynamicZoneStats(&zone);
}
#endif
