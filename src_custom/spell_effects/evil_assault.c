#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "evil_assault.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void UpdateDuelGfxExceptField(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static const char sEvilHeroArchetypeName[] APPEND_RODATA = "Evil HERO";
static const char sHeroArchetypeName[] APPEND_RODATA = "HERO";

static const u8 sEvilAssaultPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 sEvilAssaultExtraDeckHeroOnlyLock APPEND_DATA = {0};
static u8 sEvilAssaultSentToGyThisTurn APPEND_DATA = {0};
static u8 sEvilAssaultGyUsedThisTurn APPEND_DATA = {0};

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

static u8 AnyHandCard(u16 cardId)
{
  return cardId != CARD_NONE;
}

static u8 IsEvilHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sEvilHeroArchetypeName);
}

static u8 IsEvilHeroLevel4OrLower(u16 cardId)
{
  if (!IsEvilHeroMonster(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level <= 4;
}

static u8 IsHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHeroArchetypeName);
}

static u8 HandHasDiscardCost(void)
{
  return Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) >= 1;
}

static u8 HandHasRoomForSearch(void)
{
  u8 i;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0)
    return TRUE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == EVIL_ASSAULT)
      return TRUE;
  }

  return FALSE;
}

static u8 CanSpecialSummonEvilHero(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

static s16 FindFirstEvilHeroDeckIndex(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsEvilHeroLevel4OrLower(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 CanActivateEvilAssault(void)
{
  if (!HandHasDiscardCost())
    return FALSE;

  if (FindFirstEvilHeroDeckIndex() < 0)
    return FALSE;

  return HandHasRoomForSearch() || CanSpecialSummonEvilHero();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* TRUE = add to hand, FALSE = Special Summon. */
static u8 PlayerChoosesAddToHand(void)
{
  /* ponytail: no dedicated hand/SS choice UI — A = add to hand, B = Special Summon.
   * Ceiling: unlabeled buttons; upgrade: effect-text choice menu. */
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

static u8 LoadEvilHeroDeckMenu(u8 *deckIndexOut)
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

    if (!IsEvilHeroLevel4OrLower(cardId))
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

static u8 PickEvilHeroDeckIndex(void)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadEvilHeroDeckMenu(deckIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sEvilAssaultPickLabels,
                                         ARRAY_COUNT(sEvilAssaultPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return deckIndex;
}

static u8 AddDeckCardAtIndexToHand(u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 handZone;
  u16 cardId;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0)
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsEvilHeroLevel4OrLower(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone),
                       cardId);
  return TRUE;
}

static enum DuelActionResult SpecialSummonDeckCardAtIndex(u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 cardId;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return DUEL_ACTION_NO_TARGET;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsEvilHeroLevel4OrLower(cardId))
    return DUEL_ACTION_NO_TARGET;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, deckIndex, FALSE) != DUEL_ACTION_OK)
    return DUEL_ACTION_NO_TARGET;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

static s8 FindDarkFusionGyIndex(u8 fixedDuelist)
{
  u8 i;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DARK_FUSION)
      return (s8)i;
  }

  return -1;
}

u8 EvilAssault_BlocksExtraDeckSpecialSummon(u16 cardId)
{
  return sEvilAssaultExtraDeckHeroOnlyLock && !IsHeroMonster(cardId);
}

void EvilAssault_OnTurnBoundary(void)
{
  sEvilAssaultExtraDeckHeroOnlyLock = FALSE;
  sEvilAssaultSentToGyThisTurn = FALSE;
  sEvilAssaultGyUsedThisTurn = FALSE;
}

void EvilAssault_NotifySentToGraveyard(void)
{
  sEvilAssaultSentToGyThisTurn = TRUE;
}

u8 CanActivateEvilAssaultGy(u8 fixedDuelist, u8 gyIndex)
{
  u8 turnDuelist;

  if (!GraveyardExpand_IsEnabled() || fixedDuelist > DUEL_OPPONENT)
    return FALSE;
  if (sEvilAssaultSentToGyThisTurn || sEvilAssaultGyUsedThisTurn)
    return FALSE;
  if (gyIndex >= GraveyardExpand_GetCount(fixedDuelist)
      || GraveyardExpand_GetCardAt(fixedDuelist, gyIndex) != EVIL_ASSAULT)
    return FALSE;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  return FindDarkFusionGyIndex(fixedDuelist) >= 0;
}

void ActivateEvilAssaultGy(u8 fixedDuelist, u8 gyIndex)
{
  u8 turnDuelist;
  s8 darkFusionIndex;
  s8 handZone;
  u16 cardId;

  if (!CanActivateEvilAssaultGy(fixedDuelist, gyIndex))
    return;

  Duel_ShowEffectText(EVIL_ASSAULT);
  if (IsDuelOver() == TRUE)
    return;

  if (Duel_BanishGraveyardAtFixed(fixedDuelist, gyIndex) != EVIL_ASSAULT)
    return;

  darkFusionIndex = FindDarkFusionGyIndex(fixedDuelist);
  if (darkFusionIndex < 0)
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)darkFusionIndex);
  if (cardId != DARK_FUSION)
    return;

  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  sEvilAssaultGyUsedThisTurn = TRUE;
  UpdateDuelGfxExceptField();
}

static void DestroyEvilAssaultSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == EVIL_ASSAULT)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void EVIL_ASSAULT_ResolveBody(void)
{
  u8 deckIndex;
  u8 addToHand;
  u8 canHand;
  u8 canSs;

  if (!CanActivateEvilAssault())
    return;

  Duel_ShowEffectText(EVIL_ASSAULT);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, AnyHandCard, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (FindFirstEvilHeroDeckIndex() < 0) {
    DestroyEvilAssaultSpellZone();
    return;
  }

  deckIndex = PickEvilHeroDeckIndex();
  if (deckIndex == 0xFF) {
    DestroyEvilAssaultSpellZone();
    return;
  }

  canHand = HandHasRoomForSearch();
  canSs = CanSpecialSummonEvilHero();

  if (canHand && canSs) {
    if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
      addToHand = PlayerChoosesAddToHand();
    else
      addToHand = FALSE; /* AI prefers SS */
  } else {
    addToHand = canHand;
  }

  if (addToHand) {
    if (!AddDeckCardAtIndexToHand(deckIndex)) {
      DestroyEvilAssaultSpellZone();
      return;
    }
  } else {
    if (SpecialSummonDeckCardAtIndex(deckIndex) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  sEvilAssaultExtraDeckHeroOnlyLock = TRUE;
  EvilAssault_NotifySentToGraveyard();

  DestroyEvilAssaultSpellZone();
}

APPEND_TEXT void EffectEVIL_ASSAULT(void)
{
  if (!CanActivateEvilAssault()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(EVIL_ASSAULT, EVIL_ASSAULT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void EVIL_ASSAULT_SelfCheck(void)
{
  if (!IsEvilHeroMonster(EVIL_HERO_INFERNAL_PRODIGY))
    while (1)
      ;
  if (!IsEvilHeroLevel4OrLower(EVIL_HERO_INFERNAL_PRODIGY))
    while (1)
      ;
  SetCardInfo(EVIL_HERO_MALICIOUS_EDGE);
  if (gCardInfo.level <= 4)
    while (1)
      ;
  if (IsEvilHeroMonster(ELEMENTAL_HERO_AVIAN))
    while (1)
      ;
  if (!IsHeroMonster(ELEMENTAL_HERO_AVIAN))
    while (1)
      ;
}
#endif
