#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel.h"
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

static u8 RemoveShineBallFromDeck(u8 fixedDuelist)
{
  u8 i;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] != MYSTICAL_SHINE_BALL)
      continue;

    gDuelDecks[fixedDuelist].cards[i] = gDuelDecks[fixedDuelist].cards[top];
    gDuelDecks[fixedDuelist].cardsDrawn++;
    return TRUE;
  }

  return FALSE;
}

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
  s8 monsterZone;
  struct DuelCard *summonZone;

  fixedDuelist = ActiveFixedDuelist();
  monsterRow = ActiveMonsterRow();
  monsterZone = FirstEmptyZoneInRow(gTurnZones[monsterRow]);
  if (monsterZone < 0 || !DeckHasShineBall(fixedDuelist))
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(VENUS_LP_COST);
  else
    SetOpponentLifePointsToSubtract(VENUS_LP_COST);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  if (IsDuelOver() == TRUE)
    return;

  if (!RemoveShineBallFromDeck(fixedDuelist))
    return;

  summonZone = gTurnZones[monsterRow][monsterZone];
  summonZone->id = MYSTICAL_SHINE_BALL;
  InitSummonedMonsterZone(summonZone);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = THE_AGENT_OF_CREATION_VENUS;
    gCardEffectTextData.cardId2 = MYSTICAL_SHINE_BALL;
    ActivateCardEffectText();
  }
}
