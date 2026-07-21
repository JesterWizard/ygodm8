#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dark_magic_inheritance.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sDarkMagicianName[] APPEND_RODATA = "Dark Magician";
static const char sDarkMagicName[] APPEND_RODATA = "Dark Magic";

static const u16 sDarkMagicianSupportST[] APPEND_RODATA = {
  DARK_MAGIC_CURTAIN,
  THOUSAND_KNIVES,
  SAGES_STONE,
  DEDICATION_THROUGH_LIGHT_AND_DARKNESS,
  DARK_MAGIC_ATTACK,
  DARK_MAGIC_VEIL,
  DARK_MAGICAL_CIRCLE,
  BOND_BETWEEN_TEACHER_AND_STUDENT,
  DARK_BURNING_ATTACK,
  DARK_BURNING_MAGIC,
  ILLUSION_MAGIC,
  MAGICIAN_NAVIGATION,
  SECRETS_OF_DARK_MAGIC,
  ETERNAL_SOUL,
  DARK_MAGIC_RITUAL,
};

static const u8 sDarkMagicInheritancePickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

u8 DarkMagicInheritance_IsOptUsed(void)
{
  return EffectOpt_IsUsed(DARK_MAGIC_INHERITANCE);
}

void DarkMagicInheritance_MarkOptUsed(void)
{
  EffectOpt_MarkUsed(DARK_MAGIC_INHERITANCE);
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsSpellCard(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_SPELL;
}

static u8 IsSpellOrTrap(u16 cardId)
{
  u8 group;

  if (cardId == CARD_NONE)
    return FALSE;

  group = GetTypeGroup(cardId);
  return group == TYPE_GROUP_SPELL || group == TYPE_GROUP_TRAP;
}

static u8 IsInSupportIdList(u16 cardId)
{
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sDarkMagicianSupportST); i++) {
    if (cardId == sDarkMagicianSupportST[i])
      return TRUE;
  }

  return FALSE;
}

static u8 IsDarkMagicianSupportST(u16 cardId)
{
  if (!IsSpellOrTrap(cardId) || cardId == DARK_MAGIC_INHERITANCE)
    return FALSE;

  if (Duel_CardNameContains(cardId, sDarkMagicianName))
    return TRUE;

  if (Duel_CardNameContains(cardId, sDarkMagicName))
    return TRUE;

  return IsInSupportIdList(cardId);
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

static u8 CountSpellsInGraveyard(u8 fixedDuelist)
{
  u8 count = 0;
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled())
    return IsSpellCard(gDuel.duelistbattleState[fixedDuelist].graveyard) ? 1 : 0;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsSpellCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u8 HandHasRoomForDeckSearch(u8 turnDuelist)
{
  u8 i;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) >= 0)
    return TRUE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[turnDuelist][i]->id == DARK_MAGIC_INHERITANCE)
      return TRUE;
  }

  return FALSE;
}

static s16 FindFirstSupportDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsDarkMagicianSupportST(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 LoadSpellGyMenu(u8 fixedDuelist, u8 skipIndex, u8 *gyIndexOut)
{
  u8 gyCount;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  if (!GraveyardExpand_IsEnabled()) {
    /* Legacy single-slot GY cannot hold 2 Spells — CanActivate already gates. */
    (void)skipIndex;
    (void)gyIndexOut;
    gDeckMenu.cost = 0;
    gDeckMenu.currentPos = 0;
    gDeckMenu.sortMode = 0;
    gDeckMenu.displayMode = 1;
    gDeckMenu.cardCount = 0;
    return 0;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId;

    if (i == skipIndex)
      continue;

    cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (!IsSpellCard(cardId))
      continue;

    gyIndexOut[menuCount] = i;
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

static s8 PickSpellGyIndex(u8 fixedDuelist, u8 skipIndex)
{
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  s8 chosen;

  DECKMENU_SAVE();

  menuCount = LoadSpellGyMenu(fixedDuelist, skipIndex, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    chosen = (s8)gyIndexMap[0];
    DECKMENU_RESTORE();
    return chosen;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sDarkMagicInheritancePickLabels,
          ARRAY_COUNT(sDarkMagicInheritancePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosen = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return chosen;
}

static u8 BanishTwoSpellsFromGraveyard(u8 fixedDuelist)
{
  s8 first;
  s8 second;

  first = PickSpellGyIndex(fixedDuelist, 0xFF);
  if (first < 0)
    return FALSE;

  second = PickSpellGyIndex(fixedDuelist, (u8)first);
  if (second < 0)
    return FALSE;

  if (first > second) {
    Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)first);
    Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)second);
  } else {
    Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)second);
    Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)first);
  }

  GraveyardExpand_RefreshDisplay();
  return TRUE;
}

static u8 LoadSupportDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
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

    if (!IsDarkMagicianSupportST(cardId))
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

static u8 AddDeckCardAtIndexToHand(u8 turnDuelist, u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsDarkMagicianSupportST(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
  return TRUE;
}

static u8 PickSupportDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadSupportDeckMenu(turnDuelist, deckIndexMap);
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
          sDarkMagicInheritancePickLabels,
          ARRAY_COUNT(sDarkMagicInheritancePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static u8 CanActivateDarkMagicInheritance(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (DarkMagicInheritance_IsOptUsed())
    return FALSE;

  if (CountSpellsInGraveyard(fixedDuelist) < 2)
    return FALSE;

  if (!HandHasRoomForDeckSearch(ACTIVE_DUELIST))
    return FALSE;

  return FindFirstSupportDeckIndex(ACTIVE_DUELIST) >= 0;
}

static void DARK_MAGIC_INHERITANCE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckIndex;

  Duel_ShowEffectText(DARK_MAGIC_INHERITANCE);

  if (IsDuelOver() == TRUE || !CanActivateDarkMagicInheritance())
    return;

  DarkMagicInheritance_MarkOptUsed();
  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE)
    return;

  if (!BanishTwoSpellsFromGraveyard(fixedDuelist))
    return;

  if (FindFirstSupportDeckIndex(ACTIVE_DUELIST) < 0)
    return;

  deckIndex = PickSupportDeckIndex(ACTIVE_DUELIST);
  if (deckIndex != 0xFF)
    AddDeckCardAtIndexToHand(ACTIVE_DUELIST, deckIndex);

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectDARK_MAGIC_INHERITANCE(void)
{
  if (!CanActivateDarkMagicInheritance()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(DARK_MAGIC_INHERITANCE,
                                       DARK_MAGIC_INHERITANCE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DarkMagicInheritance_SelfCheck(void)
{
  if (!IsDarkMagicianSupportST(DARK_MAGIC_ATTACK))
    while (1)
      ;
  if (IsDarkMagicianSupportST(DARK_MAGIC_INHERITANCE))
    while (1)
      ;
  if (IsDarkMagicianSupportST(DARK_MAGICIAN))
    while (1)
      ;
}
#endif
