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

static u8 CountHeroKidInDeck(u8 turnDuelist)
{
  u8 fixedDuelist = (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
      ? DUEL_PLAYER
      : DUEL_OPPONENT;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u8 count = 0;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == HERO_KID)
      count++;
  }

  return count;
}

static u8 CanSpecialSummonHeroKidFromDeck(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (CountHeroKidInDeck(turnDuelist) == 0)
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0;
}

static void SpecialSummonAllHeroKidFromDeck(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  while (FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0
      && Duel_FindDeckCardIndex(turnDuelist, HERO_KID) >= 0) {
    if (Duel_SpecialSummonFromDeck(turnDuelist, HERO_KID, opts) != DUEL_ACTION_OK)
      break;
  }
}

unsigned char ShouldActivateHERO_KID(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != HERO_KID)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  /* ponytail: true trigger is Special Summon; on-summon stand-in covers SS path. */
  return CanSpecialSummonHeroKidFromDeck(duelist);
}

void ActivateHERO_KID(void)
{
  u8 duelist;
  struct DuelCard *zone;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(HERO_KID, 8);
  if (IsDuelOver() != TRUE)
    SpecialSummonAllHeroKidFromDeck(duelist);

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  zone->unk4 = 1;
}
