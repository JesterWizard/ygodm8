#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"

#define ANTE_DAMAGE 1000

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistIsHuman(u8 turnDuelist)
{
  return gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER];
}

static u8 AnyHandCard(u16 cardId)
{
  return cardId != CARD_NONE;
}

static u8 RevealLevel(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return 0;

  SetCardInfo(cardId);
  return gCardInfo.level;
}

static s8 PickAiHandZone(struct DuelCard **handRow)
{
  u8 i;
  s8 best = -1;
  u8 bestLevel = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u8 level;

    if (handRow[i]->id == CARD_NONE)
      continue;

    level = RevealLevel(handRow[i]->id);
    if (best < 0 || level > bestLevel) {
      best = (s8)i;
      bestLevel = level;
    }
  }

  return best;
}

static s8 PickHandZoneForDuelist(u8 turnDuelist)
{
  struct DuelCard **handRow = gTurnHands[turnDuelist];

  if (Duel_CountCardsInHand(handRow) == 0)
    return -1;

  if (FixedDuelistIsHuman(turnDuelist) && !gHideEffectText)
    return SelectHandCardMatchingPredicate(handRow, AnyHandCard);

  return PickAiHandZone(handRow);
}

u8 CanActivateANTE(void)
{
  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) == 0)
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) == 0)
    return FALSE;

  return TRUE;
}

static void ANTE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  s8 activeZone;
  s8 inactiveZone;
  struct DuelCard *activeCard;
  struct DuelCard *inactiveCard;
  u8 activeLevel;
  u8 inactiveLevel;

  if (!CanActivateANTE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(ANTE);

  if (IsDuelOver() == TRUE)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  activeZone = PickHandZoneForDuelist(ACTIVE_DUELIST);
  if (activeZone < 0)
    return;

  inactiveZone = PickHandZoneForDuelist(INACTIVE_DUELIST);
  if (inactiveZone < 0)
    return;

  activeCard = gTurnHands[ACTIVE_DUELIST][activeZone];
  inactiveCard = gTurnHands[INACTIVE_DUELIST][inactiveZone];

  activeCard->isFaceUp = TRUE;
  inactiveCard->isFaceUp = TRUE;
  UpdateDuelGfxExceptField();
  ShowExchangeOpponentHandResult();

  activeLevel = RevealLevel(activeCard->id);
  inactiveLevel = RevealLevel(inactiveCard->id);

  if (activeLevel > inactiveLevel) {
    Duel_DestroyZone(inactiveCard, INACTIVE_DUELIST, TRUE);
    if (Duel_ChangeLp(INACTIVE_DUELIST, -ANTE_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  } else if (inactiveLevel > activeLevel) {
    Duel_DestroyZone(activeCard, ACTIVE_DUELIST, TRUE);
    if (Duel_ChangeLp(ACTIVE_DUELIST, -ANTE_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }
}

APPEND_TEXT void EffectANTE(void)
{
  if (!CanActivateANTE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(ANTE, ANTE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ANTE_SelfCheck(void)
{
  if (ANTE_DAMAGE != 1000)
    while (1)
      ;
  if (RevealLevel(POT_OF_GREED) != 0)
    while (1)
      ;
}
#endif
