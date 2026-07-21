#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "contact_gate.h"
#include "constants/card_ids.h"
#include "effect_events.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "fusion_recipes.h"
#include "removed_from_play.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sNeoSpacianName[] APPEND_RODATA = "Neo-Spacian";
static const char sNeosName[] APPEND_RODATA = "Neos";

static u8 sContactGateFusionOnlyLock APPEND_DATA = {0};
static u8 sContactGateFusionReturnController APPEND_DATA = {0xFF};

static const u8 sContactGatePickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

/* OPT via EffectOpt_* - cleared on turn boundary (EffectEvent_OnTurnBoundary). */

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

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST]
      == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

u8 ContactGate_FusionListsElementalHeroNeos(u16 cardId)
{
  const struct FusionRecipe *recipe;
  u8 i;
  u8 materialCount;

  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  recipe = FusionRecipe_FindByResult(cardId);
  if (recipe != NULL) {
    materialCount = FusionRecipe_MaterialCount(recipe);
    for (i = 0; i < materialCount; i++) {
      if (FusionRecipe_MaterialAt(recipe, i) == ELEMENTAL_HERO_NEOS)
        return TRUE;
    }
  }

  if (cardId == ELEMENTAL_HERO_NEOS)
    return FALSE;

  return Duel_CardNameContains(cardId, sNeosName);
}

static u8 GyContainsContactGate(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == CONTACT_GATE)
      return TRUE;
  }

  return FALSE;
}

static s16 FindBanishedNeoSpacianIndex(u8 fixedDuelist)
{
  u8 i;

  if (!RemovedFromPlay_IsEnabled())
    return -1;

  for (i = 0; i < RemovedFromPlay_GetCount(fixedDuelist); i++) {
    if (IsNeoSpacianMonster(RemovedFromPlay_GetCardAt(fixedDuelist, i)))
      return (s16)i;
  }

  return -1;
}

void ContactGate_NotifyNeosFusionReturnedToExtra(u8 controllerFixedDuelist)
{
  if (controllerFixedDuelist == DUEL_PLAYER || controllerFixedDuelist == DUEL_OPPONENT)
    sContactGateFusionReturnController = controllerFixedDuelist;
}

void ContactGate_ArmExtraDeckFusionOnlyLock(void)
{
  sContactGateFusionOnlyLock = TRUE;
}

u8 ContactGate_BlocksExtraDeckSpecialSummon(u16 cardId)
{
  if (!sContactGateFusionOnlyLock)
    return FALSE;

  if (cardId == CARD_NONE)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color == FUSION_CARD)
    return FALSE;

  if (FusionRecipe_FindByResult(cardId) != NULL)
    return FALSE;

  return TRUE;
}

void ContactGate_OnTurnBoundary(void)
{
  sContactGateFusionOnlyLock = FALSE;
  sContactGateFusionReturnController = 0xFF;
}

u8 Cond_ContactGateOnFusionReturn(struct EffectCtx *ctx)
{
  u8 fixedDuelist;

  (void)ctx;

  fixedDuelist = sContactGateFusionReturnController;
  if (fixedDuelist > DUEL_OPPONENT)
    return FALSE;

  if (!GyContainsContactGate(fixedDuelist))
    return FALSE;

  return FindBanishedNeoSpacianIndex(fixedDuelist) >= 0;
}

enum DuelActionResult Op_ContactGateOnFusionReturn(struct EffectCtx *ctx)
{
  (void)ctx;
  /* Flag consumed when GyIgnition resolves; parent may also call Notify directly. */
  return DUEL_ACTION_OK;
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
  ContactGate_ArmExtraDeckFusionOnlyLock();
  UpdateDuelGfxExceptField();
}

u8 CanActivateContactGateGy(u8 fixedDuelist, u8 gyIndex)
{
  u8 turnDuelist;
  u8 monsterRow;

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  if (sContactGateFusionReturnController != fixedDuelist)
    return FALSE;

  if (gyIndex >= GraveyardExpand_GetCount(fixedDuelist))
    return FALSE;

  if (GraveyardExpand_GetCardAt(fixedDuelist, gyIndex) != CONTACT_GATE)
    return FALSE;

  if (FindBanishedNeoSpacianIndex(fixedDuelist) < 0)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  turnDuelist = TurnDuelistForFixed(fixedDuelist);
  monsterRow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                             : INACTIVE_DUELIST_MONSTER_ROW;
  return FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0;
}

void ActivateContactGateGy(u8 fixedDuelist, u8 gyIndex)
{
  s16 banishedIndex;
  u16 cardId;
  u8 turnDuelist;
  struct DuelSummonOpts opts;

  if (!CanActivateContactGateGy(fixedDuelist, gyIndex))
    return;

  banishedIndex = FindBanishedNeoSpacianIndex(fixedDuelist);
  if (banishedIndex < 0)
    return;

  cardId = RemovedFromPlay_GetCardAt(fixedDuelist, (u8)banishedIndex);
  if (!IsNeoSpacianMonster(cardId))
    return;

  Duel_ShowEffectText(CONTACT_GATE);
  if (IsDuelOver() == TRUE)
    return;

  Duel_BanishGraveyardAtFixed(fixedDuelist, gyIndex);
  sContactGateFusionReturnController = 0xFF;

  /* ponytail: no RemovedFromPlay_RemoveAt - parent must shift RFP after SS. */
  turnDuelist = TurnDuelistForFixed(fixedDuelist);
  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectCONTACT_GATE(void)
{
  if (Duel_TryResolveSpellThroughTraps(CONTACT_GATE, CONTACT_GATE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
