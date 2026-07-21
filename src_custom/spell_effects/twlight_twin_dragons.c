#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "duel_status.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

#define TWLIGHT_TWIN_DRAGONS_MILL_COUNT 4

void UpdateDuelGfxExceptField(void);

static const u8 sTwlightPickLabels[] APPEND_RODATA = {
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

static u8 ControlsPunishmentDragon(void)
{
  return RowHasCardMatch(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW], PUNISHMENT_DRAGON);
}

static u8 GraveyardHasJudgmentDragon(u8 fixedDuelist)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard == JUDGMENT_DRAGON;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == JUDGMENT_DRAGON)
      return TRUE;
  }

  return FALSE;
}

static s8 FindFirstJudgmentDragonGyIndex(u8 fixedDuelist)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == JUDGMENT_DRAGON)
      return 0;
    return -1;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == JUDGMENT_DRAGON)
      return (s8)i;
  }

  return -1;
}

static u8 LoadJudgmentDragonGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (top != JUDGMENT_DRAGON) {
      gDeckMenu.cardCount = 0;
      return 0;
    }

    gyIndexMap[0] = 0;
    gDeckMenu.cards[0] = top;
    gDeckMenu.cost = 0;
    gDeckMenu.currentPos = 0;
    gDeckMenu.sortMode = 0;
    gDeckMenu.displayMode = 1;
    gDeckMenu.cardCount = 1;
    return 1;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (cardId != JUDGMENT_DRAGON)
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

static s8 PlayerPickJudgmentDragonGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadJudgmentDragonGyMenu(fixedDuelist, gyIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sTwlightPickLabels, ARRAY_COUNT(sTwlightPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static u8 AddJudgmentDragonFromGyToHand(u8 turnDuelist, u8 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = GetGraveCardAndClearGrave(turnDuelist);
    if (cardId != JUDGMENT_DRAGON)
      return FALSE;
  } else {
    cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
    if (cardId != JUDGMENT_DRAGON)
      return FALSE;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
  }

  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
  return TRUE;
}

static u8 CanActivateTwlightTwinDragons(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (!ControlsPunishmentDragon())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return GraveyardHasJudgmentDragon(fixedDuelist);
}

u8 CanActivateTWLIGHT_TWIN_DRAGONS(void)
{
  return CanActivateTwlightTwinDragons();
}

static void TWLIGHT_TWIN_DRAGONS_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 gyIndex;

  Duel_ShowEffectText(TWLIGHT_TWIN_DRAGONS);

  if (IsDuelOver() == TRUE || !CanActivateTwlightTwinDragons())
    return;

  if (!GraveyardExpand_IsEnabled()) {
    gyIndex = 0;
  } else if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    gyIndex = PlayerPickJudgmentDragonGyIndex(fixedDuelist);
  } else {
    gyIndex = FindFirstJudgmentDragonGyIndex(fixedDuelist);
  }

  if (gyIndex < 0)
    return;

  if (!AddJudgmentDragonFromGyToHand(ACTIVE_DUELIST, (u8)gyIndex))
    return;

  if (Duel_MillTopDeckCards(ACTIVE_DUELIST, TWLIGHT_TWIN_DRAGONS_MILL_COUNT, TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: Deck-to-GY by Lightsworn → add Punishment Dragon from GY + banish
   * top 4 needs a mill/send-from-deck hook outside this file.
   * Ceiling: on-activate JD recycle + mill only; upgrade: if TWLIGHT_TWIN_DRAGONS
   * sent Deck→GY by Lightsworn effect → PickZone PD in GY → hand, then banish top 4. */

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectTWLIGHT_TWIN_DRAGONS(void)
{
  if (!CanActivateTwlightTwinDragons()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(TWLIGHT_TWIN_DRAGONS, TWLIGHT_TWIN_DRAGONS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void TWLIGHT_TWIN_DRAGONS_SelfCheck(void)
{
  if (JUDGMENT_DRAGON == CARD_NONE || PUNISHMENT_DRAGON == CARD_NONE)
    while (1)
      ;
  if (TWLIGHT_TWIN_DRAGONS_MILL_COUNT != 4)
    while (1)
      ;
}
#endif
