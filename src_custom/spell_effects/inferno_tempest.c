#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "removed_from_play.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

u8 InfernoTempest_CanActivateAfterBattleDamage(s32 damage)
{
  return damage >= 3000;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsMonsterCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static s16 FindFirstMonsterDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsMonsterCard(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static void BanishAllMonstersFromDeck(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  for (;;) {
    s16 deckIndex = FindFirstMonsterDeckIndex(turnDuelist);
    u16 cardId;

    if (deckIndex < 0)
      break;

    cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
    if (Duel_RemoveDeckCardAt(turnDuelist, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
      break;

    RemovedFromPlay_PushFixed(fixedDuelist, cardId);
  }

  Duel_ShuffleDeckFromDrawn(turnDuelist);
}

static void BanishAllMonstersFromGraveyard(u8 fixedDuelist)
{
  s8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u8 turnDuelist =
        (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
            ? ACTIVE_DUELIST
            : INACTIVE_DUELIST;

    if (IsMonsterCard(gTurnDuelistBattleState[turnDuelist]->graveyard))
      Duel_BanishGraveyardTopTurn(turnDuelist);
    return;
  }

  for (i = (s8)GraveyardExpand_GetCount(fixedDuelist) - 1; i >= 0; i--) {
    if (!IsMonsterCard(GraveyardExpand_GetCardAt(fixedDuelist, (u8)i)))
      continue;

    Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)i);
  }
}

static void BanishAllMonstersFromDecksAndGraveyards(void)
{
  BanishAllMonstersFromDeck(ACTIVE_DUELIST);
  BanishAllMonstersFromDeck(INACTIVE_DUELIST);
  BanishAllMonstersFromGraveyard(DUEL_PLAYER);
  BanishAllMonstersFromGraveyard(DUEL_OPPONENT);
  GraveyardExpand_RefreshDisplay();
  UpdateDuelGfxExceptField();
}

static void INFERNO_TEMPEST_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(INFERNO_TEMPEST);

  if (IsDuelOver() == TRUE)
    return;

  BanishAllMonstersFromDecksAndGraveyards();

  if (IsDuelOver() == TRUE)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectINFERNO_TEMPEST(void)
{
  if (Duel_TryResolveSpellThroughTraps(INFERNO_TEMPEST, INFERNO_TEMPEST_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
