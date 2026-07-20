#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

#define SALVAGE_TARGET_COUNT 2
#define SALVAGE_MAX_ATK 1500

static const u8 sSalvagePickLabels[] APPEND_RODATA = {
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

static u8 IsSalvageTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.attribute != ATTRIBUTE_WATER)
    return FALSE;

  return gCardInfo.atk <= SALVAGE_MAX_ATK;
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

static u8 CountSalvageTargets(u8 fixedDuelist)
{
  u8 gyCount;
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsSalvageTarget(gDuel.duelistbattleState[fixedDuelist].graveyard) ? 1 : 0;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsSalvageTarget(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static s8 FindFirstSalvageGyIndex(u8 fixedDuelist, u8 excludeGyIndex)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < gyCount; i++) {
    if (i == excludeGyIndex)
      continue;
    if (IsSalvageTarget(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 CanActivateSalvage(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  if (CountEmptyHandSlots(ACTIVE_DUELIST) < SALVAGE_TARGET_COUNT)
    return FALSE;

  return CountSalvageTargets(fixedDuelist) >= SALVAGE_TARGET_COUNT;
}

static u8 LoadSalvageGyMenu(u8 fixedDuelist, u8 excludeGyIndex, u8 *gyIndexMap)
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
    if (!IsSalvageTarget(cardId))
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

static s8 PlayerPickSalvageGyIndex(u8 fixedDuelist, u8 excludeGyIndex)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadSalvageGyMenu(fixedDuelist, excludeGyIndex, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1) {
    chosenGyIndex = (s8)gyIndexMap[0];
    DECKMENU_RESTORE();
    return chosenGyIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sSalvagePickLabels, ARRAY_COUNT(sSalvagePickLabels))) {
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

static void SALVAGE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 firstIndex;
  s8 secondIndex;

  Duel_ShowEffectText(SALVAGE);

  if (IsDuelOver() == TRUE || !CanActivateSalvage())
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    firstIndex = PlayerPickSalvageGyIndex(fixedDuelist, 0xFF);
    if (firstIndex < 0)
      return;

    secondIndex = PlayerPickSalvageGyIndex(fixedDuelist, (u8)firstIndex);
    if (secondIndex < 0)
      return;
  } else {
    firstIndex = FindFirstSalvageGyIndex(fixedDuelist, 0xFF);
    secondIndex = FindFirstSalvageGyIndex(fixedDuelist, (u8)firstIndex);
    if (firstIndex < 0 || secondIndex < 0)
      return;
  }

  /* Remove higher index first so the lower index stays valid. */
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

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectSALVAGE(void)
{
  if (!CanActivateSalvage()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(SALVAGE, SALVAGE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
