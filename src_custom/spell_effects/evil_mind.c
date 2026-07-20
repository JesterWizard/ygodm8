#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

#define EVIL_MIND_DRAW_COUNT 1
#define EVIL_MIND_GY_DRAW 1
#define EVIL_MIND_GY_HERO 4
#define EVIL_MIND_GY_FUSION 10

enum EvilMindMode {
  EVIL_MIND_MODE_DRAW = 0,
  EVIL_MIND_MODE_HERO_OR_DARK_FUSION,
  EVIL_MIND_MODE_POLY_OR_FUSION,
};

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void UpdateDuelGfxExceptField(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static const char sHeroArchetypeName[] APPEND_RODATA = "HERO";
static const char sFusionName[] APPEND_RODATA = "Fusion";
static const char sPolymerizationName[] APPEND_RODATA = "Polymerization";

static const u8 sEvilMindPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHeroArchetypeName);
}

static u8 IsHeroOrDarkFusion(u16 cardId)
{
  if (cardId == DARK_FUSION)
    return TRUE;

  return IsHeroMonster(cardId);
}

static u8 IsPolymerizationOrFusionSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  if (Duel_CardNameContains(cardId, sPolymerizationName))
    return TRUE;

  return Duel_CardNameContains(cardId, sFusionName);
}

static u8 ControlsFiendMonster(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (Duel_IsFiendZone(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]))
      return TRUE;
  }

  return FALSE;
}

static u8 CountOpponentGyMonsters(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard;

    if (top != CARD_NONE && GetTypeGroup(top) == TYPE_GROUP_MONSTER)
      return 1;
    return 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER)
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
    if (gTurnHands[turnDuelist][i]->id == EVIL_MIND)
      return TRUE;
  }

  return FALSE;
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

static u8 ModeIsAvailable(u8 mode, u8 gyMonsters)
{
  if (mode == EVIL_MIND_MODE_DRAW)
    return gyMonsters >= EVIL_MIND_GY_DRAW;

  if (mode == EVIL_MIND_MODE_HERO_OR_DARK_FUSION) {
    if (gyMonsters < EVIL_MIND_GY_HERO)
      return FALSE;
    if (!HandHasRoomForDeckSearch(ACTIVE_DUELIST))
      return FALSE;
    return FindFirstMatchingDeckIndex(ACTIVE_DUELIST, IsHeroOrDarkFusion) >= 0;
  }

  if (mode == EVIL_MIND_MODE_POLY_OR_FUSION) {
    if (gyMonsters < EVIL_MIND_GY_FUSION)
      return FALSE;
    if (!HandHasRoomForDeckSearch(ACTIVE_DUELIST))
      return FALSE;
    return FindFirstMatchingDeckIndex(ACTIVE_DUELIST, IsPolymerizationOrFusionSpell) >= 0;
  }

  return FALSE;
}

u8 CanActivateEVIL_MIND(void)
{
  u8 gyMonsters;

  if (!ControlsFiendMonster())
    return FALSE;

  gyMonsters = CountOpponentGyMonsters();
  if (gyMonsters < EVIL_MIND_GY_DRAW)
    return FALSE;

  if (ModeIsAvailable(EVIL_MIND_MODE_DRAW, gyMonsters))
    return TRUE;
  if (ModeIsAvailable(EVIL_MIND_MODE_HERO_OR_DARK_FUSION, gyMonsters))
    return TRUE;
  return ModeIsAvailable(EVIL_MIND_MODE_POLY_OR_FUSION, gyMonsters);
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* Nested A/B among eligible modes: A = draw; B then A = HERO/Dark Fusion;
 * B then B = Poly/Fusion (only offered when that threshold is met). */
static u8 PlayerChoosesEvilMindMode(u8 gyMonsters)
{
  u8 hasHero = ModeIsAvailable(EVIL_MIND_MODE_HERO_OR_DARK_FUSION, gyMonsters);
  u8 hasFusion = ModeIsAvailable(EVIL_MIND_MODE_POLY_OR_FUSION, gyMonsters);

  /* ponytail: no dedicated 3-way choice UI — nested A/B unlabeled.
   * Ceiling: unlabeled buttons; upgrade: effect-text choice menu. */
  if (!hasHero && !hasFusion)
    return EVIL_MIND_MODE_DRAW;

  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return EVIL_MIND_MODE_DRAW;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      break;
    }

    WaitForVBlank();
  }

  if (!hasHero)
    return EVIL_MIND_MODE_POLY_OR_FUSION;
  if (!hasFusion)
    return EVIL_MIND_MODE_HERO_OR_DARK_FUSION;

  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return EVIL_MIND_MODE_HERO_OR_DARK_FUSION;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return EVIL_MIND_MODE_POLY_OR_FUSION;
    }

    WaitForVBlank();
  }
}

static u8 AiPickEvilMindMode(u8 gyMonsters)
{
  if (ModeIsAvailable(EVIL_MIND_MODE_POLY_OR_FUSION, gyMonsters))
    return EVIL_MIND_MODE_POLY_OR_FUSION;
  if (ModeIsAvailable(EVIL_MIND_MODE_HERO_OR_DARK_FUSION, gyMonsters))
    return EVIL_MIND_MODE_HERO_OR_DARK_FUSION;
  return EVIL_MIND_MODE_DRAW;
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
  if (!DeckMenuMainPickConfirmWithLabels(sEvilMindPickLabels,
                                         ARRAY_COUNT(sEvilMindPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
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

static u8 AddDeckCardAtIndexToHand(u8 turnDuelist, u8 deckIndex, u8 (*pred)(u16))
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
  if (!pred(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone),
                       cardId);
  return TRUE;
}

static void ResolveDeckSearch(u8 (*pred)(u16))
{
  u8 deckIndex;

  deckIndex = PickMatchingDeckIndex(ACTIVE_DUELIST, pred);
  if (deckIndex != 0xFF)
    AddDeckCardAtIndexToHand(ACTIVE_DUELIST, deckIndex, pred);
}

static void EVIL_MIND_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 gyMonsters;
  u8 mode;

  gyMonsters = CountOpponentGyMonsters();
  if (!ControlsFiendMonster() || gyMonsters < EVIL_MIND_GY_DRAW) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(EVIL_MIND);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    mode = PlayerChoosesEvilMindMode(gyMonsters);
  else
    mode = AiPickEvilMindMode(gyMonsters);

  if (!ModeIsAvailable(mode, gyMonsters)) {
    if (ModeIsAvailable(EVIL_MIND_MODE_DRAW, gyMonsters))
      mode = EVIL_MIND_MODE_DRAW;
    else
      return;
  }

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (mode == EVIL_MIND_MODE_DRAW) {
    Duel_DrawCards(ACTIVE_DUELIST, EVIL_MIND_DRAW_COUNT, TRUE);
  } else if (mode == EVIL_MIND_MODE_HERO_OR_DARK_FUSION) {
    ResolveDeckSearch(IsHeroOrDarkFusion);
  } else {
    ResolveDeckSearch(IsPolymerizationOrFusionSpell);
  }

  UpdateDuelGfxExceptField();

  /* ponytail: "only activate 1 Evil Mind per turn" needs a turn-scoped cardId
   * lock outside this file (spell is already in GY). Ceiling: no OPT lock after
   * destroy; upgrade: turn flag checked in CanActivateEVIL_MIND. */
}

APPEND_TEXT void EffectEVIL_MIND(void)
{
  if (!CanActivateEVIL_MIND()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(EVIL_MIND, EVIL_MIND_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void EVIL_MIND_SelfCheck(void)
{
  if (!Duel_CardHasMonsterType(SUMMONED_SKULL, TYPE_FIEND))
    while (1)
      ;
  if (Duel_CardHasMonsterType(BLUE_EYES_WHITE_DRAGON, TYPE_FIEND))
    while (1)
      ;
  if (EVIL_MIND_GY_DRAW != 1 || EVIL_MIND_GY_HERO != 4 || EVIL_MIND_GY_FUSION != 10)
    while (1)
      ;
}
#endif
