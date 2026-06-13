#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "exchange_hand_selection.h"
#include "graveyard_effects.h"

extern int NumCardsInDeck(unsigned char);

static u8 HandHasPeten(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (handRow[i]->id == PETEN_THE_DARK_CLOWN)
      return TRUE;
  }

  return FALSE;
}

static u8 DeckHasPeten(u8 fixedDuelist)
{
  u8 i;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == PETEN_THE_DARK_CLOWN)
      return TRUE;
  }

  return FALSE;
}

static u8 RemovePetenFromDeck(u8 fixedDuelist)
{
  u8 i;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] != PETEN_THE_DARK_CLOWN)
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

static u8 IsPetenTheDarkClown(u16 cardId)
{
  return cardId == PETEN_THE_DARK_CLOWN;
}

static s8 PickPetenHandZone(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (handRow[i]->id == PETEN_THE_DARK_CLOWN)
      return i;
  }

  return -1;
}

static u8 CanSpecialSummonPeten(u8 turnDuelist, u8 fixedDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  if (HandHasPeten(gTurnHands[turnDuelist]))
    return TRUE;

  return DeckHasPeten(fixedDuelist);
}

static void TrySpecialSummonPeten(u8 turnDuelist, u8 fixedDuelist)
{
  struct DuelCard **handRow = gTurnHands[turnDuelist];
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  s8 handZone = -1;
  s8 monsterZone;
  struct DuelCard *summonZone;

  if (!CanSpecialSummonPeten(turnDuelist, fixedDuelist))
    return;

  monsterZone = FirstEmptyZoneInRow(gTurnZones[monsterRow]);
  if (monsterZone < 0)
    return;

  if (HandHasPeten(handRow)) {
    if (fixedDuelist == DUEL_PLAYER)
      handZone = SelectHandCardMatchingPredicate(handRow, IsPetenTheDarkClown);
    else
      handZone = PickPetenHandZone(handRow);

    if (handZone >= 0) {
      summonZone = gTurnZones[monsterRow][monsterZone];
      summonZone->id = PETEN_THE_DARK_CLOWN;
      InitSummonedMonsterZone(summonZone);
      ClearZone(handRow[handZone]);
      return;
    }
  }

  // ponytail: hand takes priority when both are available; deck is the fallback
  if (DeckHasPeten(fixedDuelist) && RemovePetenFromDeck(fixedDuelist)) {
    summonZone = gTurnZones[monsterRow][monsterZone];
    summonZone->id = PETEN_THE_DARK_CLOWN;
    InitSummonedMonsterZone(summonZone);
  }
}

unsigned char ShouldActivatePetenTheDarkClown(void)
{
  u8 turnDuelist;
  u8 fixedDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gGraveyardSendWasFromField)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != PETEN_THE_DARK_CLOWN)
    return FALSE;

  if (gActiveEffect.turnRow == 7) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard != PETEN_THE_DARK_CLOWN)
      return FALSE;
    turnDuelist = INACTIVE_DUELIST;
  } else {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != PETEN_THE_DARK_CLOWN)
      return FALSE;
    turnDuelist = ACTIVE_DUELIST;
  }

  fixedDuelist = TurnDuelistToFixed(turnDuelist);
  return CanSpecialSummonPeten(turnDuelist, fixedDuelist);
}

void ActivatePetenTheDarkClown(void)
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
  gCardEffectTextData.cardId = PETEN_THE_DARK_CLOWN;
  ActivateCardEffectText();
  gHideEffectText = hideEffectText;

  GetGraveCardAndClearGrave2(fixedDuelist);
  TrySpecialSummonPeten(turnDuelist, fixedDuelist);
}
