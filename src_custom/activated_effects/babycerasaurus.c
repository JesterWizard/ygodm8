#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "babycerasaurus.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"

void UpdateDuelGfxExceptField(void);

static u8 sBabyInit APPEND_DATA = {0};

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static u8 IsDinoLevel4OrLower(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (!Duel_CardHasMonsterType(cardId, TYPE_DINOSAUR))
    return FALSE;
  return gCardData_NEW[cardId].level <= 4;
}

static u16 FindDeckDinoTarget(u8 turnDuelist)
{
  u8 fixedDuelist =
      gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]
          ? DUEL_PLAYER
          : DUEL_OPPONENT;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsDinoLevel4OrLower(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }
  return CARD_NONE;
}

static void TryBabySs(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  struct DuelSummonOpts opts;
  u16 cardId;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;

  cardId = FindDeckDinoTarget(turnDuelist);
  if (cardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(BABYCERASAURUS, 2);
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  Duel_SpecialSummonFromDeck(turnDuelist, cardId, opts);
  UpdateDuelGfxExceptField();
}

static void OnBabyEffectDestroyed(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != BABYCERASAURUS)
    return;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return;

  TryBabySs(ev->controller);
}

void Babycerasaurus_EnsureInit(void)
{
  if (sBabyInit)
    return;
  sBabyInit = TRUE;
  /* Printed: destroyed by a card effect — not battle. */
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnBabyEffectDestroyed);
}

unsigned char CanActivateBABYCERASAURUS(void)
{
  if (gMonEffect.id != BABYCERASAURUS)
    return FALSE;

  /* Effect-destroy Deck SS via Babycerasaurus_EnsureInit. */
  return FALSE;
}

void ActivateBABYCERASAURUSEffect(void)
{
  Duel_ShowEffectTextTyped(BABYCERASAURUS, 2);
}
