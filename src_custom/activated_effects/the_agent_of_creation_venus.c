#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

#define VENUS_LP_COST 500

extern int NumCardsInDeck(unsigned char);

static u8 ActiveFixedDuelist(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 ActiveMonsterRow(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return ACTIVE_DUELIST_MONSTER_ROW;

  return INACTIVE_DUELIST_MONSTER_ROW;
}

static u8 DeckHasShineBall(u8 fixedDuelist)
{
  u8 i;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == MYSTICAL_SHINE_BALL)
      return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateTheAgentOfCreationVenus(void)
{
  u8 fixedDuelist;
  u8 monsterRow;
  struct DuelCard *zone;

  if (gMonEffect.id != THE_AGENT_OF_CREATION_VENUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER) {
    if (gDuelLifePoints[DUEL_PLAYER] < VENUS_LP_COST)
      return FALSE;
  } else if (gDuelLifePoints[DUEL_OPPONENT] < VENUS_LP_COST) {
    return FALSE;
  }

  fixedDuelist = ActiveFixedDuelist();
  if (!DeckHasShineBall(fixedDuelist))
    return FALSE;

  monsterRow = ActiveMonsterRow();
  return FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0;
}

void ActivateTheAgentOfCreationVenusEffect(void)
{
  u8 fixedDuelist;
  u8 monsterRow;
  struct DuelSummonOpts opts;
  u8 summonDuelist;

  fixedDuelist = ActiveFixedDuelist();
  monsterRow = ActiveMonsterRow();

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0 || !DeckHasShineBall(fixedDuelist))
    return;

  if (Duel_ChangeLp(WhoseTurn(), -VENUS_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  summonDuelist = (monsterRow == ACTIVE_DUELIST_MONSTER_ROW) ? ACTIVE_DUELIST : INACTIVE_DUELIST;
  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.markSpecialSummon = FALSE;
  if (Duel_SpecialSummonFromDeck(summonDuelist, MYSTICAL_SHINE_BALL, opts) != DUEL_ACTION_OK)
    return;

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = THE_AGENT_OF_CREATION_VENUS;
    gCardEffectTextData.cardId2 = MYSTICAL_SHINE_BALL;
    ActivateCardEffectText();
  }
}
