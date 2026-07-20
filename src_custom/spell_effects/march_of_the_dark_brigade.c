#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "duel_status.h"
#include "expanded_graveyard.h"
#include "removed_from_play.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sLightswornArchetypeName[] APPEND_RODATA = "Lightsworn";

static const u8 sMarchPickLabels[] APPEND_RODATA = {
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

static u8 IsLightswornWithLevel(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardNameContains(cardId, sLightswornArchetypeName))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level > 0;
}

static u8 GetOriginalLevel(u16 cardId)
{
  SetCardInfo(cardId);
  return gCardInfo.level;
}

static u8 GraveyardHasLightswornWithLevel(u8 fixedDuelist)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled())
    return IsLightswornWithLevel(gDuel.duelistbattleState[fixedDuelist].graveyard);

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsLightswornWithLevel(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static s8 FindFirstLightswornGyIndex(u8 fixedDuelist)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsLightswornWithLevel(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 0;
    return -1;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsLightswornWithLevel(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 LoadLightswornGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (!IsLightswornWithLevel(top)) {
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

    if (!IsLightswornWithLevel(cardId))
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

static s8 PlayerPickLightswornGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadLightswornGyMenu(fixedDuelist, gyIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sMarchPickLabels, ARRAY_COUNT(sMarchPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static u8 AddLightswornFromGyToHand(u8 turnDuelist, u8 gyIndex, u16 *outCardId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = GetGraveCardAndClearGrave(turnDuelist);
    if (!IsLightswornWithLevel(cardId))
      return FALSE;
  } else {
    cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
    if (!IsLightswornWithLevel(cardId))
      return FALSE;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
  }

  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
  if (outCardId != NULL)
    *outCardId = cardId;
  return TRUE;
}

static enum DuelActionResult BanishTopDeckCards(u8 turnDuelist, u8 count)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 i;

  for (i = 0; i < count; i++) {
    u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
    u16 cardId;

    if (top >= NumCardsInDeck(fixedDuelist)) {
      DeclareLoser(fixedDuelist);
      return DUEL_ACTION_DUEL_OVER;
    }

    cardId = gDuelDecks[fixedDuelist].cards[top];
    if (Duel_RemoveDeckCardAt(turnDuelist, top, FALSE) != DUEL_ACTION_OK)
      return DUEL_ACTION_INVALID;

    RemovedFromPlay_PushFixed(fixedDuelist, cardId);

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  return DUEL_ACTION_OK;
}

static u8 CanActivateMarchOfTheDarkBrigade(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return GraveyardHasLightswornWithLevel(fixedDuelist);
}

u8 CanActivateMARCH_OF_THE_DARK_BRIGADE(void)
{
  return CanActivateMarchOfTheDarkBrigade();
}

static void MARCH_OF_THE_DARK_BRIGADE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 gyIndex;
  u16 addedId = CARD_NONE;
  u8 level;

  Duel_ShowEffectText(MARCH_OF_THE_DARK_BRIGADE);

  if (IsDuelOver() == TRUE || !CanActivateMarchOfTheDarkBrigade())
    return;

  /* ponytail: once-per-turn activation not tracked (no BSS turn flag editable
   * from this spell file alone). Ceiling: can activate multiple Marches per turn;
   * upgrade: shared OPT RAM bit / effect_usage once_per_turn. */

  if (!GraveyardExpand_IsEnabled()) {
    gyIndex = 0;
  } else if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    gyIndex = PlayerPickLightswornGyIndex(fixedDuelist);
  } else {
    gyIndex = FindFirstLightswornGyIndex(fixedDuelist);
  }

  if (gyIndex < 0)
    return;

  if (!AddLightswornFromGyToHand(ACTIVE_DUELIST, (u8)gyIndex, &addedId))
    return;

  level = GetOriginalLevel(addedId);
  if (level > 0 && BanishTopDeckCards(ACTIVE_DUELIST, level) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectMARCH_OF_THE_DARK_BRIGADE(void)
{
  if (!CanActivateMarchOfTheDarkBrigade()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MARCH_OF_THE_DARK_BRIGADE,
                                       MARCH_OF_THE_DARK_BRIGADE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MarchOfTheDarkBrigade_SelfCheck(void)
{
  if (!IsLightswornWithLevel(JAIN_LIGHTSWORN_PALADIN))
    while (1)
      ;
  if (IsLightswornWithLevel(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
