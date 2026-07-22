#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "gravekeepers_recruiter.h"

void UpdateDuelGfxExceptField(void);

static u8 sRecruiterInit APPEND_DATA = {0};
static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static u8 IsRecruiterTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (!Duel_CardNameContains(cardId, sGravekeepersName))
    return FALSE;
  return gCardData_NEW[cardId].def <= 1500;
}

static u16 FindDeckRecruiterTarget(u8 turnDuelist)
{
  u8 fixedDuelist =
      gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]
          ? DUEL_PLAYER
          : DUEL_OPPONENT;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsRecruiterTarget(gDuelDecks[fixedDuelist].cards[i]))
      return gDuelDecks[fixedDuelist].cards[i];
  }
  return CARD_NONE;
}

static void TryRecruiterSearch(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);
  u16 cardId;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;
  cardId = FindDeckRecruiterTarget(turnDuelist);
  if (cardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_RECRUITER, 2);
  Duel_AddDeckCardToHand(turnDuelist, cardId, TRUE);
  UpdateDuelGfxExceptField();
}

static void OnRecruiterSentToGy(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != GRAVEKEEPERS_RECRUITER)
    return;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return;
  TryRecruiterSearch(ev->controller);
}

void GravekeepersRecruiter_EnsureInit(void)
{
  if (sRecruiterInit)
    return;
  sRecruiterInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnRecruiterSentToGy);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnRecruiterSentToGy);
}

unsigned char CanActivateGRAVEKEEPERS_RECRUITER(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_RECRUITER)
    return FALSE;

  /* Sent-to-GY search via GravekeepersRecruiter_EnsureInit. */
  return FALSE;
}

void ActivateGRAVEKEEPERS_RECRUITEREffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_RECRUITER, 2);
}
