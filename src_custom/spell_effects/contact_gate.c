#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "effect_events.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sNeoSpacianName[] APPEND_RODATA = "Neo-Spacian";

static const u8 sContactGatePickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

/* OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsNeoSpacianMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sNeoSpacianName);
}

static u8 CountGyNeoDifferentNames(u16 *outIds, u8 maxOut)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 count = 0;
  u8 i;
  u8 j;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    if (IsNeoSpacianMonster(top) && maxOut > 0) {
      outIds[0] = top;
      return 1;
    }
    return 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist) && count < maxOut; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    u8 dup = FALSE;

    if (!IsNeoSpacianMonster(cardId))
      continue;

    for (j = 0; j < count; j++) {
      if (outIds[j] == cardId) {
        dup = TRUE;
        break;
      }
    }
    if (dup)
      continue;

    outIds[count++] = cardId;
  }

  return count;
}

static u8 BanishTwoDifferentNeoFromGy(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 ids[2];
  u8 found;
  u8 banished = 0;
  u8 i;

  found = CountGyNeoDifferentNames(ids, 2);
  if (found < 2)
    return FALSE;

  /* Banish highest indices first to keep lower indices stable. */
  if (GraveyardExpand_IsEnabled()) {
    for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0 && banished < 2; i--) {
      u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);

      if (cardId != ids[0] && cardId != ids[1])
        continue;
      if (cardId == ids[0])
        ids[0] = CARD_NONE;
      else
        ids[1] = CARD_NONE;

      Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1);
      banished++;
    }
  } else {
    return FALSE;
  }

  return banished >= 2;
}

static u8 CollectSummonCandidates(u16 *outIds, u8 maxOut, u16 excludeA, u16 excludeB)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 count = 0;
  u8 i;
  u8 j;

  /* Hand */
  for (i = 0; i < MAX_ZONES_IN_ROW && count < maxOut; i++) {
    u16 cardId = gTurnHands[ACTIVE_DUELIST][i]->id;
    u8 dup = FALSE;

    if (!IsNeoSpacianMonster(cardId))
      continue;
    if (cardId == excludeA || cardId == excludeB)
      continue;
    if (Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

    for (j = 0; j < count; j++) {
      if (outIds[j] == cardId) {
        dup = TRUE;
        break;
      }
    }
    if (dup)
      continue;
    outIds[count++] = cardId;
  }

  /* Deck */
  {
    u8 deckSize = NumCardsInDeck(fixedDuelist);
    u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

    for (i = top; i < deckSize && count < maxOut; i++) {
      u16 cardId = gDuelDecks[fixedDuelist].cards[i];
      u8 dup = FALSE;

      if (!IsNeoSpacianMonster(cardId))
        continue;
      if (cardId == excludeA || cardId == excludeB)
        continue;
      if (Duel_CardCannotBeSpecialSummoned(cardId))
        continue;

      for (j = 0; j < count; j++) {
        if (outIds[j] == cardId) {
          dup = TRUE;
          break;
        }
      }
      if (dup)
        continue;
      outIds[count++] = cardId;
    }
  }

  /* GY remaining */
  if (GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist) && count < maxOut; i++) {
      u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
      u8 dup = FALSE;

      if (!IsNeoSpacianMonster(cardId))
        continue;
      if (cardId == excludeA || cardId == excludeB)
        continue;
      if (Duel_CardCannotBeSpecialSummoned(cardId))
        continue;

      for (j = 0; j < count; j++) {
        if (outIds[j] == cardId) {
          dup = TRUE;
          break;
        }
      }
      if (dup)
        continue;
      outIds[count++] = cardId;
    }
  }

  return count;
}

static u16 PlayerPickSummonId(u16 *ids, u8 count, u16 exclude)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 menuCount = 0;
  u8 i;
  u16 chosen;

  for (i = 0; i < count; i++) {
    if (ids[i] == exclude || ids[i] == CARD_NONE)
      continue;
    menuCount++;
  }
  if (menuCount == 0)
    return CARD_NONE;

  if (WhoseTurn() != DUEL_PLAYER || menuCount == 1) {
    for (i = 0; i < count; i++) {
      if (ids[i] != CARD_NONE && ids[i] != exclude)
        return ids[i];
    }
    return CARD_NONE;
  }

  DECKMENU_SAVE();
  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;
  menuCount = 0;
  for (i = 0; i < count; i++) {
    if (ids[i] == exclude || ids[i] == CARD_NONE)
      continue;
    gDeckMenu.cards[menuCount++] = ids[i];
  }
  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sContactGatePickLabels, ARRAY_COUNT(sContactGatePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    chosen = gDeckMenu.cards[0];
  } else {
    chosen = gDeckMenu.cards[gDeckMenu.currentPos];
    DeckMenu_EndDuelTrunkView();
  }
  DECKMENU_RESTORE();
  return chosen;
}

static enum DuelActionResult SpecialSummonNeoById(u16 cardId)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 i;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  /* Hand first */
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == cardId)
      return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, i, opts);
  }

  /* Deck */
  {
    u8 deckSize = NumCardsInDeck(fixedDuelist);
    u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

    for (i = top; i < deckSize; i++) {
      if (gDuelDecks[fixedDuelist].cards[i] == cardId)
        return Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts);
    }
  }

  /* GY */
  return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
}

u8 CanActivateCONTACT_GATE(void)
{
  u16 ids[2];

  if (EffectOpt_IsUsed(CONTACT_GATE))
    return FALSE;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;
  if (Duel_CountMonstersOnTurnRow(ACTIVE_DUELIST_MONSTER_ROW) > 3)
    return FALSE;
  if (CountGyNeoDifferentNames(ids, 2) < 2)
    return FALSE;

  return TRUE;
}

static void CONTACT_GATE_ResolveBody(void)
{
  u16 costIds[2];
  u16 candidates[16];
  u8 candCount;
  u16 first;
  u16 second;

  if (!CanActivateCONTACT_GATE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  CountGyNeoDifferentNames(costIds, 2);
  if (!BanishTwoDifferentNeoFromGy()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(CONTACT_GATE);
  if (IsDuelOver() == TRUE)
    return;

  candCount = CollectSummonCandidates(candidates, ARRAY_COUNT(candidates), CARD_NONE, CARD_NONE);
  first = PlayerPickSummonId(candidates, candCount, CARD_NONE);
  if (first == CARD_NONE) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (SpecialSummonNeoById(first) == DUEL_ACTION_DUEL_OVER)
    return;

  candCount = CollectSummonCandidates(candidates, ARRAY_COUNT(candidates), first, CARD_NONE);
  second = PlayerPickSummonId(candidates, candCount, first);
  if (second != CARD_NONE) {
    if (SpecialSummonNeoById(second) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  EffectOpt_MarkUsed(CONTACT_GATE);
  UpdateDuelGfxExceptField();

  /* ponytail: ED Fusion-only lock + GY ignition (banish this → SS banished Neo)
   * need hooks outside this file. Ceiling: field SS path only. */
  (void)costIds;
}

APPEND_TEXT void EffectCONTACT_GATE(void)
{
  if (Duel_TryResolveSpellThroughTraps(CONTACT_GATE, CONTACT_GATE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
