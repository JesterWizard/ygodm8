#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "graveyard_effects.h"
#include "giant_rat.h"

extern int NumCardsInDeck(unsigned char);

static u8 DeckHasGiantRat(u8 fixedDuelist)
{
  u8 i;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == GIANT_RAT)
      return TRUE;
  }

  return FALSE;
}

static u8 RemoveGiantRatFromDeck(u8 fixedDuelist)
{
  u8 i;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] != GIANT_RAT)
      continue;

    gDuelDecks[fixedDuelist].cards[i] = gDuelDecks[fixedDuelist].cards[top];
    gDuelDecks[fixedDuelist].cardsDrawn++;
    return TRUE;
  }

  return FALSE;
}

static u8 TurnDuelistToFixed(u8 duelist)
{
  if (gTurnDuelistBattleState[duelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
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

static u8 CanSpecialSummonGiantRat(u8 turnDuelist, u8 fixedDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  return DeckHasGiantRat(fixedDuelist);
}

static void TrySpecialSummonGiantRat(u8 turnDuelist, u8 fixedDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  s8 monsterZone;
  struct DuelCard *summonZone;

  if (!CanSpecialSummonGiantRat(turnDuelist, fixedDuelist))
    return;

  monsterZone = FirstEmptyZoneInRow(gTurnZones[monsterRow]);
  if (monsterZone < 0 || !RemoveGiantRatFromDeck(fixedDuelist))
    return;

  summonZone = gTurnZones[monsterRow][monsterZone];
  summonZone->id = GIANT_RAT;
  InitSummonedMonsterZone(summonZone);
}

void MarkGiantRatBattleDestruction(u8 fixedDuelist, u16 cardId)
{
  if (cardId == GIANT_RAT)
    gGiantRatBattleDestroyMask |= (1 << fixedDuelist);
}

unsigned char ShouldActivateGiantRat(void)
{
  u8 turnDuelist;
  u8 fixedDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != GIANT_RAT)
    return FALSE;

  if (gActiveEffect.turnRow == 7) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard != GIANT_RAT)
      return FALSE;
    turnDuelist = INACTIVE_DUELIST;
  } else {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != GIANT_RAT)
      return FALSE;
    turnDuelist = ACTIVE_DUELIST;
  }

  fixedDuelist = TurnDuelistToFixed(turnDuelist);
  if ((gGiantRatBattleDestroyMask & (1 << fixedDuelist)) == 0)
    return FALSE;

  return CanSpecialSummonGiantRat(turnDuelist, fixedDuelist);
}

void ActivateGiantRat(void)
{
  u8 hideEffectText;
  u8 turnDuelist;
  u8 fixedDuelist;

  if (gActiveEffect.turnRow == 7) {
    turnDuelist = INACTIVE_DUELIST;
    fixedDuelist = TurnDuelistToFixed(INACTIVE_DUELIST);
  } else {
    turnDuelist = ACTIVE_DUELIST;
    fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  }

  hideEffectText = gHideEffectText;
  gHideEffectText = FALSE;
  gCardEffectTextData.cardId = GIANT_RAT;
  ActivateCardEffectText();
  gHideEffectText = hideEffectText;

  GetGraveCardAndClearGrave2(fixedDuelist);
  gGiantRatBattleDestroyMask &= ~(1 << fixedDuelist);
  TrySpecialSummonGiantRat(turnDuelist, fixedDuelist);
}
