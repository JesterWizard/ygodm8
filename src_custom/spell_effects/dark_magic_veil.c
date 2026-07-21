#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "dark_magic_veil.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_economics.h"
#include "spell_effects.h"

#define DARK_MAGIC_VEIL_LP_COST 1000

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static const u8 sDarkMagicVeilPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDarkSpellcaster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_SHADOW
      && Duel_CardHasMonsterType(cardId, TYPE_SPELLCASTER);
}

static u8 HandHasDarkSpellcaster(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsDarkSpellcaster(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 GraveHasDarkSpellcaster(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 count;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsDarkSpellcaster(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard);

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    if (IsDarkSpellcaster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 CanPayDarkMagicVeilCost(void)
{
  if (IsSpellEconomicsActiveForActiveDuelist())
    return TRUE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] > DARK_MAGIC_VEIL_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] > DARK_MAGIC_VEIL_LP_COST;
}

u8 CanActivateDARK_MAGIC_VEIL(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!CanPayDarkMagicVeilCost())
    return FALSE;

  return HandHasDarkSpellcaster() || GraveHasDarkSpellcaster();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* TRUE = hand, FALSE = GY. */
static u8 PlayerChoosesHand(void)
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

static s8 PickAiDarkSpellcasterHandZone(void)
{
  u8 i;
  s8 chosen = -1;
  u16 bestAtk = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = gTurnHands[ACTIVE_DUELIST][i]->id;

    if (!IsDarkSpellcaster(cardId))
      continue;

    SetCardInfo(cardId);
    if (chosen < 0 || gCardInfo.atk > bestAtk) {
      chosen = (s8)i;
      bestAtk = gCardInfo.atk;
    }
  }

  return chosen;
}

static void SpecialSummonFromHand(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!HandHasDarkSpellcaster())
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    Duel_SpecialSummonFromHand(ACTIVE_DUELIST, CARD_NONE, IsDarkSpellcaster, opts);
    return;
  }

  {
    s8 handZone = PickAiDarkSpellcasterHandZone();

    if (handZone >= 0)
      Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts);
  }
}

static u8 LoadDarkSpellcasterGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsDarkSpellcaster(cardId))
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

static s8 GyIndexForSortedMenuPick(u8 fixedDuelist, u8 menuPos, u8 menuCount)
{
  u16 cardId;
  u8 occurrence = 0;
  u8 seen = 0;
  u8 i;
  u8 gyCount;

  if (menuPos >= menuCount)
    return -1;

  cardId = gDeckMenu.cards[menuPos];
  if (cardId == CARD_NONE)
    return -1;

  for (i = 0; i <= menuPos; i++) {
    if (gDeckMenu.cards[i] == cardId)
      occurrence++;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 gyCard = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsDarkSpellcaster(gyCard))
      continue;

    if (gyCard == cardId) {
      seen++;
      if (seen == occurrence)
        return (s8)i;
    }
  }

  return -1;
}

static s8 PlayerPickDarkSpellcasterGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadDarkSpellcasterGyMenu(fixedDuelist, gyIndexMap);
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
          sDarkMagicVeilPickLabels, ARRAY_COUNT(sDarkMagicVeilPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = GyIndexForSortedMenuPick(fixedDuelist, gDeckMenu.currentPos, menuCount);

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static s8 AiPickDarkSpellcasterGyIndex(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  s8 bestIndex = -1;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsDarkSpellcaster(cardId))
      continue;

    SetCardInfo(cardId);
    if (bestIndex < 0 || gCardInfo.atk > bestAtk) {
      bestAtk = gCardInfo.atk;
      bestIndex = (s8)i;
    }
  }

  return bestIndex;
}

static void SpecialSummonFromGrave(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 gyIndex;
  u16 cardId;

  if (!GraveHasDarkSpellcaster())
    return;

  if (!GraveyardExpand_IsEnabled()) {
    Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts);
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER)
    gyIndex = PlayerPickDarkSpellcasterGyIndex(fixedDuelist);
  else
    gyIndex = AiPickDarkSpellcasterGyIndex(fixedDuelist);

  if (gyIndex < 0)
    return;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  if (!IsDarkSpellcaster(cardId))
    return;

  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

static void DARK_MAGIC_VEIL_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 useHand;

  if (!CanActivateDARK_MAGIC_VEIL())
    return;

  if (!IsSpellEconomicsActiveForActiveDuelist()) {
    if (Duel_ChangeLp(ACTIVE_DUELIST, -DARK_MAGIC_VEIL_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  Duel_ShowEffectText(DARK_MAGIC_VEIL);

  if (IsDuelOver() == TRUE)
    return;

  if (HandHasDarkSpellcaster() && GraveHasDarkSpellcaster()) {
    if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
      useHand = PlayerChoosesHand();
    else
      useHand = TRUE; /* AI prefers hand */
  } else {
    useHand = HandHasDarkSpellcaster();
  }

  if (useHand)
    SpecialSummonFromHand();
  else
    SpecialSummonFromGrave();

  if (IsDuelOver() == TRUE)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectDARK_MAGIC_VEIL(void)
{
  if (!CanActivateDARK_MAGIC_VEIL()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTrapsEx(DARK_MAGIC_VEIL, DARK_MAGIC_VEIL_LP_COST,
                                         DARK_MAGIC_VEIL_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
