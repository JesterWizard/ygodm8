#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

#define POT_OF_AVARICE_RETURN_COUNT 5
#define POT_OF_AVARICE_DRAW_COUNT 2

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

static u8 CountMonstersInGraveyard(u8 fixedDuelist)
{
  u8 count = 0;
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsMonsterCard(gDuel.duelistbattleState[fixedDuelist].graveyard) ? 1 : 0;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsMonsterCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u8 CanActivatePotOfAvarice(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  return CountMonstersInGraveyard(fixedDuelist) >= POT_OF_AVARICE_RETURN_COUNT;
}

static void ReturnCardToDeck(u8 turnDuelist, u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

/* Collect POT_OF_AVARICE_RETURN_COUNT most-recent monster GY indices (high→low). */
static u8 CollectRecentMonsterGyIndices(u8 fixedDuelist, u8 *outIndices)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 found = 0;
  s8 i;

  for (i = (s8)gyCount - 1; i >= 0 && found < POT_OF_AVARICE_RETURN_COUNT; i--) {
    if (!IsMonsterCard(GraveyardExpand_GetCardAt(fixedDuelist, (u8)i)))
      continue;

    outIndices[found++] = (u8)i;
  }

  return found;
}

static void ShuffleMonstersFromGraveToDeck(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 indices[POT_OF_AVARICE_RETURN_COUNT];
  u8 found;
  u8 i;

  found = CollectRecentMonsterGyIndices(fixedDuelist, indices);
  if (found < POT_OF_AVARICE_RETURN_COUNT)
    return;

  for (i = 0; i < POT_OF_AVARICE_RETURN_COUNT; i++) {
    u16 cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, indices[i]);

    ReturnCardToDeck(turnDuelist, cardId);
  }

  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  Duel_ShuffleDeckFromDrawn(turnDuelist);
}

static void POT_OF_AVARICE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!CanActivatePotOfAvarice())
    return;

  Duel_ShowEffectText(POT_OF_AVARICE);

  if (IsDuelOver() == TRUE)
    return;

  ShuffleMonstersFromGraveToDeck(ACTIVE_DUELIST);

  if (Duel_DrawCards(ACTIVE_DUELIST, POT_OF_AVARICE_DRAW_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectPOT_OF_AVARICE(void)
{
  if (!CanActivatePotOfAvarice()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(POT_OF_AVARICE, POT_OF_AVARICE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
