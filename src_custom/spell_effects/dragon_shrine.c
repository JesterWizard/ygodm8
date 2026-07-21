#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
void UpdateDuelGfxExceptField(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static const u8 sDragonShrinePickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDragonMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_DRAGON);
}

static u8 IsDragonNormalMonster(u16 cardId)
{
  if (!IsDragonMonster(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.color == COLOR_NORMAL;
}

static s16 FindFirstMatchingDeckIndex(u8 turnDuelist, u8 (*pred)(u16))
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (pred(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

u8 DragonShrine_IsOptUsed(void)
{
  return EffectOpt_IsUsed(DRAGON_SHRINE);
}

void DragonShrine_MarkOptUsed(void)
{
  EffectOpt_MarkUsed(DRAGON_SHRINE);
}

u8 CanActivateDRAGON_SHRINE(void)
{
  return !DragonShrine_IsOptUsed()
      && FindFirstMatchingDeckIndex(ACTIVE_DUELIST, IsDragonMonster) >= 0;
}

static u8 LoadMatchingDeckMenu(u8 turnDuelist, u8 (*pred)(u16), u8 *deckIndexOut)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!pred(cardId))
      continue;

    deckIndexOut[menuCount] = i;
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

static u8 PickMatchingDeckIndex(u8 turnDuelist, u8 (*pred)(u16))
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadMatchingDeckMenu(turnDuelist, pred, deckIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return 0xFF;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    deckIndex = deckIndexMap[0];
    DECKMENU_RESTORE();
    return deckIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sDragonShrinePickLabels, ARRAY_COUNT(sDragonShrinePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static u8 SendDeckCardAtIndexToGraveyard(u8 turnDuelist, u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsDragonMonster(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  GraveyardExpand_PushTurn(turnDuelist, cardId);
  return TRUE;
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* Returns TRUE to send a second Dragon. */
static u8 PlayerChoosesSecondSend(void)
{
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return TRUE;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return FALSE;
    }

    WaitForVBlank();
  }
}

static void DRAGON_SHRINE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 deckIndex;
  u16 sentId;
  u8 fixedDuelist;
  u8 sendSecond;

  if (!CanActivateDRAGON_SHRINE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  DragonShrine_MarkOptUsed();
  Duel_ShowEffectText(DRAGON_SHRINE);

  if (IsDuelOver() == TRUE)
    return;

  deckIndex = PickMatchingDeckIndex(ACTIVE_DUELIST, IsDragonMonster);
  if (deckIndex == 0xFF) {
    s16 autoIndex = FindFirstMatchingDeckIndex(ACTIVE_DUELIST, IsDragonMonster);

    if (autoIndex < 0)
      return;
    deckIndex = (u8)autoIndex;
  }

  fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  sentId = gDuelDecks[fixedDuelist].cards[deckIndex];

  if (!SendDeckCardAtIndexToGraveyard(ACTIVE_DUELIST, deckIndex))
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (IsDragonNormalMonster(sentId)
      && FindFirstMatchingDeckIndex(ACTIVE_DUELIST, IsDragonMonster) >= 0) {
    if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
      sendSecond = PlayerChoosesSecondSend();
    else
      sendSecond = TRUE;

    if (sendSecond) {
      deckIndex = PickMatchingDeckIndex(ACTIVE_DUELIST, IsDragonMonster);
      if (deckIndex == 0xFF) {
        s16 autoIndex = FindFirstMatchingDeckIndex(ACTIVE_DUELIST, IsDragonMonster);

        if (autoIndex >= 0)
          SendDeckCardAtIndexToGraveyard(ACTIVE_DUELIST, (u8)autoIndex);
      } else {
        SendDeckCardAtIndexToGraveyard(ACTIVE_DUELIST, deckIndex);
      }
    }
  }

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectDRAGON_SHRINE(void)
{
  if (!CanActivateDRAGON_SHRINE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(DRAGON_SHRINE, DRAGON_SHRINE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DRAGON_SHRINE_SelfCheck(void)
{
  if (!IsDragonMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (!IsDragonNormalMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (IsDragonMonster(DARK_MAGICIAN))
    while (1)
      ;
}
#endif
