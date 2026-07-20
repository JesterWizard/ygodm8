#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 OpponentMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST_MONSTER_ROW;
  return ACTIVE_DUELIST_MONSTER_ROW;
}

static u8 IsFaceUpZeroAtkMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (!IsCardFaceUp(zone))
    return FALSE;

  return Duel_GetZoneFinalAtk(zone) == 0;
}

static u8 CountFaceUpZeroAtkMonsters(u8 turnRow)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpZeroAtkMonster(gTurnZones[turnRow][col]))
      count++;
  }

  return count;
}

unsigned char ShouldActivateREPTILIANNE_HYDRA(void)
{
  struct DuelCard *zone;
  u8 oppRow;

  if (gActiveEffect.cardId != REPTILIANNE_HYDRA)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  oppRow = OpponentMonsterTurnRow(gActiveEffect.turnRow);
  return CountFaceUpZeroAtkMonsters(oppRow) > 0;
}

void ActivateREPTILIANNE_HYDRA(void)
{
  u8 duelist;
  u8 oppRow;
  u8 destroyCount;
  struct DuelCard *zone;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  oppRow = OpponentMonsterTurnRow(gActiveEffect.turnRow);
  destroyCount = CountFaceUpZeroAtkMonsters(oppRow);

  Duel_ShowEffectTextTyped(REPTILIANNE_HYDRA, 8);
  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DestroyAllMonstersMatching(oppRow, IsFaceUpZeroAtkMonster, TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  if (destroyCount > 0) {
    if (Duel_DrawCards(duelist, destroyCount, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  zone->unk4 = 1;
}
