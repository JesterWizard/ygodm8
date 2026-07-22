#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "gladiator_beast_battled.h"
#include "mirage_dragon.h"
#include "monster_effect_usage.h"

static u8 TurnMonsterRowHasFaceUpMirageDragon(u8 turnMonsterRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[turnMonsterRow][col];

    if (zone != NULL && zone->id == MIRAGE_DRAGON && zone->isFaceUp)
      return TRUE;
  }

  return FALSE;
}

u8 MirageDragon_BlocksInactiveTrapInBattlePhase(void)
{
  if (!GladiatorBeast_InBattlePhase())
    return FALSE;

  return TurnMonsterRowHasFaceUpMirageDragon(ACTIVE_DUELIST_MONSTER_ROW);
}

u8 MirageDragon_BlocksActiveTrapInBattlePhase(void)
{
  if (!GladiatorBeast_InBattlePhase())
    return FALSE;

  return TurnMonsterRowHasFaceUpMirageDragon(INACTIVE_DUELIST_MONSTER_ROW);
}

unsigned char CanActivateMIRAGE_DRAGON(void)
{
  if (gMonEffect.id != MIRAGE_DRAGON)
    return FALSE;

  /* Continuous opp trap lock in BP via MirageDragon_Blocks*InBattlePhase. */
  return FALSE;
}

void ActivateMIRAGE_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(MIRAGE_DRAGON, 2);
}
