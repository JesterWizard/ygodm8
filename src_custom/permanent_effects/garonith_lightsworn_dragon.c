#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "garonith_lightsworn_dragon.h"

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

#define GARONITH_DISTINCT_CAP 32
#define GARONITH_ATK_DEF_PER_NAME 300
#define GARONITH_END_PHASE_MILL 3

static u8 IsLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

static u8 CountDistinctLightswornNamesInGy(u8 fixedDuelist)
{
  u16 seen[GARONITH_DISTINCT_CAP];
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

    if (distinct >= GARONITH_DISTINCT_CAP)
      break;

    seen[distinct++] = cardId;
  }

  return distinct;
}

static void GaronithCurrentStats(struct DuelCard *zone, u16 *outAtk, u16 *outDef)
{
  u8 fixedDuelist = GetDuelistForZone(zone);
  u32 baseAtk = gCardData_NEW[zone->id].atk;
  u32 baseDef = gCardData_NEW[zone->id].def;
  u8 count = 0;

  if (fixedDuelist != 0xFF)
    count = CountDistinctLightswornNamesInGy(fixedDuelist);

  *outAtk = Duel_StatFromCount(count, GARONITH_ATK_DEF_PER_NAME, baseAtk);
  *outDef = Duel_StatFromCount(count, GARONITH_ATK_DEF_PER_NAME, baseDef);
}

u8 GaronithLightswornDragon_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;
  u16 def;

  if (zone == NULL || zone->id != GARONITH_LIGHTSWORN_DRAGON)
    return FALSE;

  GaronithCurrentStats(zone, &atk, &def);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, atk, def);
  return TRUE;
}

void TryApplyGaronithEndPhase(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 turn = ACTIVE_DUELIST;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !zone->isFaceUp || zone->id != GARONITH_LIGHTSWORN_DRAGON)
      continue;
    Duel_ShowEffectTextTyped(GARONITH_LIGHTSWORN_DRAGON, 2);
    Duel_MillTopDeckCards(turn, GARONITH_END_PHASE_MILL, TRUE);
    return;
  }
}

unsigned char ShouldActivateGARONITH_LIGHTSWORN_DRAGON(void)
{
  /* Pierce via ApplySimplePiercersBattleEffect; EP mill via TryApplyGaronithEndPhase.
   * ApplyDynamicZoneStats live. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGARONITH_LIGHTSWORN_DRAGON(void)
{
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void GaronithLightswornDragon_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = GARONITH_LIGHTSWORN_DRAGON;
  GaronithLightswornDragon_ApplyDynamicZoneStats(&zone);
}
#endif
