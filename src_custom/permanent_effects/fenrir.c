#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "fenrir.h"

static void InitSummonedMonsterZone(struct DuelCard *zone)
{
  zone->isFaceUp = TRUE;
  zone->isLocked = FALSE;
  zone->isDefending = FALSE;
  zone->permStage = 0;
  zone->tempStage = 0;
  zone->unk4 = 0;
  zone->unkTwo = 0;
  zone->willChangeSides = 0;
}

static u8 GraveyardTopIsWaterMonster(u8 turnDuelist)
{
  u16 cardId = gTurnDuelistBattleState[turnDuelist]->graveyard;

  if (cardId == CARD_NONE)
    return FALSE;
  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_WATER;
}

u8 CanSpecialSummonFenrirFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= MAX_ZONES_IN_ROW)
    return FALSE;

  if (handRow[handZone]->id != FENRIR)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!GraveyardTopIsWaterMonster(ACTIVE_DUELIST))
    return FALSE;

  return TRUE;
}

u8 TrySpecialSummonFenrirFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  s8 monsterZone;
  struct DuelCard *summonZone;

  if (!CanSpecialSummonFenrirFromHand(handZone))
    return FALSE;

  monsterZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (monsterZone < 0)
    return FALSE;

  GetGraveCardAndClearGrave(ACTIVE_DUELIST);

  summonZone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][monsterZone];
  summonZone->id = FENRIR;
  InitSummonedMonsterZone(summonZone);
  ClearZone(handRow[handZone]);

  return TRUE;
}
