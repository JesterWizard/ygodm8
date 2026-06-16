#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "mini_card.h"
#include "spell_effects.h"
#include "triangle_power.h"

#define TRIANGLE_POWER_LEVEL 1
#define TRIANGLE_POWER_STAGE_BOOST 4

static u8 MonsterQualifiesForTrianglePower(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level == TRIANGLE_POWER_LEVEL;
}

static void BoostMonsterStages(struct DuelCard *zone)
{
  u8 i;

  for (i = 0; i < TRIANGLE_POWER_STAGE_BOOST; i++)
    IncrementPermStage(zone);
}

void ResetTrianglePowerState(void)
{
  gTrianglePowerDestroyMaskPlayer = 0;
  gTrianglePowerDestroyMaskOpponent = 0;
}

static void DestroyMarkedMonstersInRow(u8 row, u8 mask, u8 duelist)
{
  u8 i;

  if (mask == 0)
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone;

    if (!(mask & (1 << i)))
      continue;

    zone = gFixedZones[row][i];
    if (zone->id != CARD_NONE)
      Duel_DestroyZone(zone, duelist, FALSE);
  }
}

void DestroyTrianglePowerMonstersAtEndOfTurn(void)
{
  if (gTrianglePowerDestroyMaskPlayer == 0 && gTrianglePowerDestroyMaskOpponent == 0)
    return;

  DestroyMarkedMonstersInRow(PLAYER_MONSTER_ROW, gTrianglePowerDestroyMaskPlayer, DUEL_PLAYER);
  DestroyMarkedMonstersInRow(OPPONENT_MONSTER_ROW, gTrianglePowerDestroyMaskOpponent, DUEL_OPPONENT);
  ResetTrianglePowerState();
}

APPEND_TEXT void EffectTrianglePower(void)
{
  u8 i;
  u8 row;

  ResetTrianglePowerState();
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);

  for (row = 0; row < 2; row++) {
    u8 monsterRow = row == 0 ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
    u8 *destroyMask = row == 0 ? &gTrianglePowerDestroyMaskPlayer : &gTrianglePowerDestroyMaskOpponent;

    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      struct DuelCard *zone = gFixedZones[monsterRow][i];

      if (!MonsterQualifiesForTrianglePower(zone->id))
        continue;

      BoostMonsterStages(zone);
      *destroyMask |= (1 << i);
    }
  }

  RefreshFieldMonsterStatOverlays();
  Duel_ShowEffectText(TRIANGLE_POWER);
}
