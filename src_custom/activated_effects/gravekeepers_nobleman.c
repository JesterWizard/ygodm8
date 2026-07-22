#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "gravekeepers_nobleman.h"

void UpdateDuelGfxExceptField(void);

static u8 sNoblemanInit APPEND_DATA = {0};
static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static u8 IsGravekeeperMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  return Duel_CardNameContains(cardId, sGravekeepersName);
}

static u16 FindOtherGravekeeperInDeck(u8 turnDuelist)
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

    if (IsGravekeeperMonster(cardId) && cardId != GRAVEKEEPERS_NOBLEMAN
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }
  return CARD_NONE;
}

static void TryNoblemanBattleDestroySs(u8 fixedDuelist)
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

  cardId = FindOtherGravekeeperInDeck(turnDuelist);
  if (cardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_NOBLEMAN, 2);
  if (IsDuelOver() == TRUE)
    return;

  /* Face-down DEF via NORMAL_SET (no dedicated SS face-down mode). */
  opts = Duel_DefaultSpecialSummonOpts(FALSE);
  opts.mode = DUEL_SUMMON_NORMAL_SET;
  Duel_SpecialSummonFromDeck(turnDuelist, cardId, opts);
  UpdateDuelGfxExceptField();
}

static void OnNoblemanBattleDestroyed(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != GRAVEKEEPERS_NOBLEMAN)
    return;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return;

  TryNoblemanBattleDestroySs(ev->controller);
}

void GravekeepersNobleman_EnsureInit(void)
{
  if (sNoblemanInit)
    return;
  sNoblemanInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnNoblemanBattleDestroyed);
}

unsigned char CanActivateGRAVEKEEPERS_NOBLEMAN(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_NOBLEMAN)
    return FALSE;

  /* Battle-destroy Deck SS via GravekeepersNobleman_EnsureInit. */
  return FALSE;
}

void ActivateGRAVEKEEPERS_NOBLEMANEffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_NOBLEMAN, 2);
}
