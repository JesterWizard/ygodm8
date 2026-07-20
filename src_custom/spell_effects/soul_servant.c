#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void ClearZone(struct DuelCard *zone);
void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void UpdateDuelGfxExceptField(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

enum SoulServantSource {
  SOUL_SERVANT_SRC_HAND = 0,
  SOUL_SERVANT_SRC_DECK = 1,
  SOUL_SERVANT_SRC_GY = 2,
};

static const char sDarkMagicianName[] APPEND_RODATA = "Dark Magician";

/* ponytail: no card-description text search — approximate "lists DM/DMG" via
 * name contains "Dark Magician" plus a known support ID list.
 * Ceiling: misses text-only mentions. Upgrade: description-string helper. */
static const u16 sDmMentionSupport[] APPEND_RODATA = {
  DARK_MAGICIAN,
  DARK_MAGICIAN_GIRL,
  DARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHT,
  THE_DARK_MAGICIANS,
  MAGICIANS_ROD,
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
  DARK_MAGIC_INHERITANCE,
};

static const u8 sSoulServantPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsInDmSupportList(u16 cardId)
{
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sDmMentionSupport); i++) {
    if (cardId == sDmMentionSupport[i])
      return TRUE;
  }

  return FALSE;
}

static u8 IsSoulServantStackTarget(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == SOUL_SERVANT)
    return FALSE;

  if (IsInDmSupportList(cardId))
    return TRUE;

  return Duel_CardNameContains(cardId, sDarkMagicianName);
}

static void PlaceCardOnDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 HandHasStackTarget(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsSoulServantStackTarget(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 DeckHasStackTarget(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsSoulServantStackTarget(gDuelDecks[fixedDuelist].cards[i]))
      return TRUE;
  }

  return FALSE;
}

static u8 GyHasStackTarget(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsSoulServantStackTarget(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard);

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsSoulServantStackTarget(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 CanActivateSoulServant(void)
{
  return HandHasStackTarget() || DeckHasStackTarget() || GyHasStackTarget();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* Nested A/B among available sources: A = hand; B then A = Deck; B then B = GY. */
static u8 PlayerChoosesSource(u8 hasHand, u8 hasDeck, u8 hasGy)
{
  /* ponytail: no dedicated 3-way choice UI — nested A/B unlabeled.
   * Ceiling: unlabeled buttons; upgrade: effect-text choice menu. */
  if (hasHand && !hasDeck && !hasGy)
    return SOUL_SERVANT_SRC_HAND;
  if (!hasHand && hasDeck && !hasGy)
    return SOUL_SERVANT_SRC_DECK;
  if (!hasHand && !hasDeck && hasGy)
    return SOUL_SERVANT_SRC_GY;

  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  if (hasHand) {
    for (;;) {
      UpdateFilteredInput_WithRepeat();

      if (gNewButtons & A_BUTTON) {
        PlayMusic(SFX_SELECT);
        return SOUL_SERVANT_SRC_HAND;
      }

      if (gNewButtons & B_BUTTON) {
        PlayMusic(SFX_SELECT);
        break;
      }

      WaitForVBlank();
    }
  }

  if (hasDeck && !hasGy)
    return SOUL_SERVANT_SRC_DECK;
  if (!hasDeck && hasGy)
    return SOUL_SERVANT_SRC_GY;

  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return hasDeck ? SOUL_SERVANT_SRC_DECK : SOUL_SERVANT_SRC_GY;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      if (hasDeck && hasGy)
        return SOUL_SERVANT_SRC_GY;
      return hasDeck ? SOUL_SERVANT_SRC_DECK : SOUL_SERVANT_SRC_GY;
    }

    WaitForVBlank();
  }
}

static u8 AiPickSource(u8 hasHand, u8 hasDeck, u8 hasGy)
{
  if (hasDeck)
    return SOUL_SERVANT_SRC_DECK;
  if (hasGy)
    return SOUL_SERVANT_SRC_GY;
  (void)hasHand;
  return SOUL_SERVANT_SRC_HAND;
}

static u8 LoadDeckStackMenu(u8 *deckIndexOut)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsSoulServantStackTarget(cardId))
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

static u8 PickDeckStackIndex(void)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadDeckStackMenu(deckIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sSoulServantPickLabels,
                                         ARRAY_COUNT(sSoulServantPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return deckIndex;
}

static u8 LoadGyStackMenu(u8 *gyIndexOut)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 gyCount;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  if (!GraveyardExpand_IsEnabled()) {
    gDeckMenu.cost = 0;
    gDeckMenu.currentPos = 0;
    gDeckMenu.sortMode = 0;
    gDeckMenu.displayMode = 1;
    gDeckMenu.cardCount = 0;
    return 0;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsSoulServantStackTarget(cardId))
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

static s8 PickGyStackIndex(void)
{
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  s8 chosen;

  DECKMENU_SAVE();

  menuCount = LoadGyStackMenu(gyIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sSoulServantPickLabels,
                                         ARRAY_COUNT(sSoulServantPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosen = (s8)gyIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosen;
}

static u8 StackFromHand(void)
{
  s8 handZone;
  u16 cardId;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (WhoseTurn() == DUEL_PLAYER)
    handZone = SelectHandCardMatchingPredicate(gTurnHands[ACTIVE_DUELIST],
                                               IsSoulServantStackTarget);
  else {
    u8 i;

    handZone = -1;
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (IsSoulServantStackTarget(gTurnHands[ACTIVE_DUELIST][i]->id)) {
        handZone = (s8)i;
        break;
      }
    }
  }

  if (handZone < 0)
    return FALSE;

  cardId = gTurnHands[ACTIVE_DUELIST][handZone]->id;
  ClearZone(gTurnHands[ACTIVE_DUELIST][handZone]);
  PlaceCardOnDeckTop(fixedDuelist, cardId);
  return TRUE;
}

static u8 StackFromDeck(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckIndex;
  u16 cardId;

  deckIndex = PickDeckStackIndex();
  if (deckIndex == 0xFF)
    return FALSE;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsSoulServantStackTarget(cardId))
    return FALSE;

  /* Remove from undrawn pool, then put back as new top (no shuffle). */
  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  PlaceCardOnDeckTop(fixedDuelist, cardId);
  return TRUE;
}

static u8 StackFromGy(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 gyIndex;
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsSoulServantStackTarget(cardId))
      return FALSE;

    gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard = CARD_NONE;
    PlaceCardOnDeckTop(fixedDuelist, cardId);
    return TRUE;
  }

  gyIndex = PickGyStackIndex();
  if (gyIndex < 0)
    return FALSE;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  if (!IsSoulServantStackTarget(cardId))
    return FALSE;

  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  PlaceCardOnDeckTop(fixedDuelist, cardId);
  return TRUE;
}

static void SOUL_SERVANT_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 hasHand = HandHasStackTarget();
  u8 hasDeck = DeckHasStackTarget();
  u8 hasGy = GyHasStackTarget();
  u8 source;
  u8 ok = FALSE;

  if (!CanActivateSoulServant())
    return;

  Duel_ShowEffectText(SOUL_SERVANT);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    source = PlayerChoosesSource(hasHand, hasDeck, hasGy);
  else
    source = AiPickSource(hasHand, hasDeck, hasGy);

  if (source == SOUL_SERVANT_SRC_HAND && hasHand)
    ok = StackFromHand();
  else if (source == SOUL_SERVANT_SRC_DECK && hasDeck)
    ok = StackFromDeck();
  else if (source == SOUL_SERVANT_SRC_GY && hasGy)
    ok = StackFromGy();

  if (!ok)
    return;

  /* ponytail: GY ignition "banish this; draw for distinct Palladium/DM/DMG
   * on field+GYs" needs a GY-activate spell path outside this file.
   * Ceiling: on-field stack-to-Deck only; upgrade: GY activate → banish
   * SOUL_SERVANT → Duel_DrawCards(count distinct Palladium/DM/DMG names). */

  if (spellZone != NULL && spellZone->id == SOUL_SERVANT)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectSOUL_SERVANT(void)
{
  if (!CanActivateSoulServant()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(SOUL_SERVANT, SOUL_SERVANT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void SOUL_SERVANT_SelfCheck(void)
{
  if (!IsSoulServantStackTarget(DARK_MAGICIAN))
    while (1)
      ;
  if (!IsSoulServantStackTarget(DARK_MAGICIAN_GIRL))
    while (1)
      ;
  if (IsSoulServantStackTarget(SOUL_SERVANT))
    while (1)
      ;
  if (IsSoulServantStackTarget(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
