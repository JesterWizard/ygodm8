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

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

#define AURKUS_MILL_COUNT 2

unsigned char ShouldActivateAURKUS_LIGHTSWORN_DRUID(void)
{
  struct DuelCard *zone;
  u8 duelist;
  u8 fixedDuelist;

  if (gActiveEffect.cardId != AURKUS_LIGHTSWORN_DRUID)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  fixedDuelist = FixedDuelistForTurnDuelist(duelist);
  /* ponytail: Lightsworn target protection + true End Phase mill need turn hooks;
     on-summon mill 2 is the End-Phase stand-in. */
  return NumCardsInDeck(fixedDuelist) > 0;
}

void ActivateAURKUS_LIGHTSWORN_DRUID(void)
{
  u8 duelist;
  struct DuelCard *zone;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(AURKUS_LIGHTSWORN_DRUID, 8);
  if (IsDuelOver() != TRUE)
    Duel_MillTopDeckCards(duelist, AURKUS_MILL_COUNT, TRUE);

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  zone->unk4 = 1;
}
