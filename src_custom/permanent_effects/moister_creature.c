#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "moister_creature.h"
#include "summon_tribute.h"

#define MOISTER_CREATURE_TRIBUTE_COUNT 3

static u8 OpponentBackrowForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST_BACKROW;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST_BACKROW;
  return INACTIVE_DUELIST_BACKROW;
}

static u8 OpponentDuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static u8 BackrowZoneHasSpellOrTrap(struct DuelCard *zone)
{
  u8 typeGroup;

  if (zone->id == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static void DestroySpellAndTrapCardsInRow(struct DuelCard **row, u8 duelist)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (!BackrowZoneHasSpellOrTrap(row[i]))
      continue;

    if (Duel_DestroyZone(row[i], duelist, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }
}

unsigned char ShouldActivateMoisterCreature(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != MOISTER_CREATURE)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  if (GetPendingSummonTributeCount() != MOISTER_CREATURE_TRIBUTE_COUNT)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->unk4 == 0;
}

void ActivateMoisterCreature(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  u8 opponentBackrow = OpponentBackrowForMonsterTurnRow(gActiveEffect.turnRow);
  u8 opponentDuelist = OpponentDuelistForMonsterTurnRow(gActiveEffect.turnRow);

  FlipCardFaceUp(zone);
  DestroySpellAndTrapCardsInRow(gTurnZones[opponentBackrow], opponentDuelist);
  zone->unk4 = 1;
  ClearPendingSummonTributeCount();
  Duel_ShowEffectTextTyped(MOISTER_CREATURE, 8);
}
