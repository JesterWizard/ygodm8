#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

#define OIL_MAX_TARGETS 2
#define OIL_MAX_LEVEL 4

static const u8 sOilPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static u8 IsOilTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.attribute != ATTRIBUTE_FIRE)
    return FALSE;

  return gCardInfo.level <= OIL_MAX_LEVEL;
}

static u8 CountEmptyHandSlots(u8 turnDuelist)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[turnDuelist][i]->id == CARD_NONE)
      count++;
  }

  return count;
}

static u8 CountOilTargets(u8 fixedDuelist)
{
  u8 gyCount;
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsOilTarget(gDuel.duelistbattleState[fixedDuelist].graveyard) ? 1 : 0;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsOilTarget(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static s8 FindOilGyIndex(u8 fixedDuelist, u8 excludeGyIndex, u16 excludeCardId)
{
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (excludeGyIndex == 0)
      return -1;
    if (!IsOilTarget(top))
      return -1;
    if (excludeCardId != CARD_NONE && top == excludeCardId)
      return -1;
    return 0;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId;

    if (i == excludeGyIndex)
      continue;

    cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (excludeCardId != CARD_NONE && cardId == excludeCardId)
      continue;
    if (!IsOilTarget(cardId))
      continue;

    return (s8)i;
  }

  return -1;
}

u8 CanActivateOIL(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  if (CountEmptyHandSlots(ACTIVE_DUELIST) < 1)
    return FALSE;

  return CountOilTargets(fixedDuelist) >= 1;
}

static u8 LoadOilGyMenu(u8 fixedDuelist, u8 excludeGyIndex, u16 excludeCardId, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (i == excludeGyIndex)
      continue;
    if (excludeCardId != CARD_NONE && cardId == excludeCardId)
      continue;
    if (!IsOilTarget(cardId))
      continue;

    gyIndexMap[menuCount] = i;
    gDeckMenu.cards[menuCount] = cardId;
    menuCount++;
  }

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  return menuCount;
}

static s8 PlayerPickOilGyIndex(u8 fixedDuelist, u8 excludeGyIndex, u16 excludeCardId)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadOilGyMenu(fixedDuelist, excludeGyIndex, excludeCardId, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1 && excludeGyIndex == 0xFF) {
    chosenGyIndex = (s8)gyIndexMap[0];
    DECKMENU_RESTORE();
    return chosenGyIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sOilPickLabels, ARRAY_COUNT(sOilPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static u8 AddGraveyardCardToHand(u8 turnDuelist, u8 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  cardId = GraveyardExpand_RemoveAtTurn(turnDuelist, gyIndex);
  if (cardId == CARD_NONE)
    return FALSE;

  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return TRUE;
}

static void OIL_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 firstIndex;
  s8 secondIndex = -1;
  u16 firstCardId = CARD_NONE;

  Duel_ShowEffectText(OIL);

  if (IsDuelOver() == TRUE || !CanActivateOIL())
    return;

  /* ponytail: once-per-turn activation not tracked (no BSS turn flag editable
   * from this spell file alone). Ceiling: can activate multiple Oils per turn;
   * upgrade: shared OPT RAM bit / effect_usage once_per_turn. */

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    firstIndex = PlayerPickOilGyIndex(fixedDuelist, 0xFF, CARD_NONE);
    if (firstIndex < 0)
      return;

    firstCardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)firstIndex);

    if (CountEmptyHandSlots(ACTIVE_DUELIST) >= 2
        && FindOilGyIndex(fixedDuelist, (u8)firstIndex, firstCardId) >= 0) {
      /* Optional second pick — cancel keeps only the first. */
      secondIndex = PlayerPickOilGyIndex(fixedDuelist, (u8)firstIndex, firstCardId);
    }
  } else {
    firstIndex = FindOilGyIndex(fixedDuelist, 0xFF, CARD_NONE);
    if (firstIndex < 0)
      return;

    firstCardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)firstIndex);
    if (CountEmptyHandSlots(ACTIVE_DUELIST) >= 2)
      secondIndex = FindOilGyIndex(fixedDuelist, (u8)firstIndex, firstCardId);
  }

  if (secondIndex >= 0) {
    if (firstIndex > secondIndex) {
      if (!AddGraveyardCardToHand(ACTIVE_DUELIST, (u8)firstIndex))
        return;
      if (!AddGraveyardCardToHand(ACTIVE_DUELIST, (u8)secondIndex))
        return;
    } else {
      if (!AddGraveyardCardToHand(ACTIVE_DUELIST, (u8)secondIndex))
        return;
      if (!AddGraveyardCardToHand(ACTIVE_DUELIST, (u8)firstIndex))
        return;
    }
  } else {
    if (!AddGraveyardCardToHand(ACTIVE_DUELIST, (u8)firstIndex))
      return;
  }

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectOIL(void)
{
  if (!CanActivateOIL()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(OIL, OIL_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void Oil_SelfCheck(void)
{
  if (OIL_MAX_TARGETS != 2 || OIL_MAX_LEVEL != 4)
    while (1)
      ;
}
#endif
