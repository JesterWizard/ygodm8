#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "effect_events.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

#define ARCANA_SPREAD_MAX_LEVEL 4

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
void UpdateDuelGfxExceptField(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static const char sArcanaForceArchetypeName[] APPEND_RODATA = "Arcana Force";
static const char sCoinNameNeedle[] APPEND_RODATA = "Coin";

static const u8 sArcanaSpreadPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

/* OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsKnownCoinTossCard(u16 cardId)
{
  switch (cardId) {
  case CUP_OF_ACE:
  case ACE_OF_SWORD:
  case SECOND_COIN_TOSS:
  case ARCANA_SPREAD:
  case ARCANA_READING:
  case TIME_WIZARD:
  case FAIRY_BOX:
  case BLOWBACK_DRAGON:
  case LIGHT_BARRIER:
    return TRUE;
  default:
    return FALSE;
  }
}

static u8 IsCoinTossCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (Duel_CardNameContains(cardId, sArcanaForceArchetypeName))
    return TRUE;

  if (Duel_CardNameContains(cardId, sCoinNameNeedle))
    return TRUE;

  return IsKnownCoinTossCard(cardId);
}

static u8 IsCoinTossMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return IsCoinTossCard(cardId);
}

static u8 IsArcanaForceLevel4OrLower(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardNameContains(cardId, sArcanaForceArchetypeName))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level > 0 && gCardInfo.level <= ARCANA_SPREAD_MAX_LEVEL;
}

static u8 ActiveControlsFaceUpLightBarrier(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];

    if (zone->id == LIGHT_BARRIER && zone->isFaceUp == TRUE)
      return TRUE;
  }

  return FALSE;
}

static u8 HasEmptyMonsterZone(void)
{
  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
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

static s8 FindFirstMatchingGyIndex(u8 fixedDuelist, u8 (*pred)(u16))
{
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return pred(gDuel.duelistbattleState[fixedDuelist].graveyard) ? 0 : -1;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (pred(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 CanActivateArcanaSpread(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (EffectOpt_IsUsed(ARCANA_SPREAD))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (!HasEmptyMonsterZone())
    return FALSE;

  if (FindFirstMatchingDeckIndex(ACTIVE_DUELIST, IsArcanaForceLevel4OrLower) >= 0)
    return TRUE;

  return FindFirstMatchingGyIndex(fixedDuelist, IsCoinTossMonster) >= 0;
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* Returns TRUE for Heads path, FALSE for Tails. */
static u8 PlayerChoosesCoinEffect(void)
{
  /* ponytail: no dedicated choice UI — A = Heads, B = Tails.
   * Ceiling: unlabeled buttons; upgrade path: effect-text choice menu. */
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

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER || gHideEffectText) {
    deckIndex = deckIndexMap[0];
    DECKMENU_RESTORE();
    return deckIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sArcanaSpreadPickLabels, ARRAY_COUNT(sArcanaSpreadPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static u8 LoadMatchingGyMenu(u8 fixedDuelist, u8 (*pred)(u16), u8 *gyIndexOut)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!pred(cardId))
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

static s8 PickMatchingGyIndex(u8 fixedDuelist, u8 (*pred)(u16))
{
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  s8 gyIndex;

  DECKMENU_SAVE();

  menuCount = LoadMatchingGyMenu(fixedDuelist, pred, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER || gHideEffectText) {
    gyIndex = (s8)gyIndexMap[0];
    DECKMENU_RESTORE();
    return gyIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sArcanaSpreadPickLabels, ARRAY_COUNT(sArcanaSpreadPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  gyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return gyIndex;
}

static enum DuelActionResult SpecialSummonDeckCardAtIndex(u8 turnDuelist, u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return DUEL_ACTION_NO_TARGET;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsArcanaForceLevel4OrLower(cardId))
    return DUEL_ACTION_NO_TARGET;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return DUEL_ACTION_NO_TARGET;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
}

static enum DuelActionResult SpecialSummonFromGyIndex(u8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 cardId;

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsCoinTossMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

static void ResolveHeadsFromDeck(void)
{
  u8 deckIndex;
  s16 autoIndex;

  deckIndex = PickMatchingDeckIndex(ACTIVE_DUELIST, IsArcanaForceLevel4OrLower);
  if (deckIndex == 0xFF) {
    autoIndex = FindFirstMatchingDeckIndex(ACTIVE_DUELIST, IsArcanaForceLevel4OrLower);
    if (autoIndex < 0)
      return;
    deckIndex = (u8)autoIndex;
  }

  SpecialSummonDeckCardAtIndex(ACTIVE_DUELIST, deckIndex);
}

static void ResolveTailsFromGy(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 gyIndex;

  if (!GraveyardExpand_IsEnabled())
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    gyIndex = PickMatchingGyIndex(fixedDuelist, IsCoinTossMonster);
  else
    gyIndex = FindFirstMatchingGyIndex(fixedDuelist, IsCoinTossMonster);

  if (gyIndex < 0)
    return;

  SpecialSummonFromGyIndex((u8)gyIndex);
}

static void ARCANA_SPREAD_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 heads;
  u8 hasHeads;
  u8 hasTails;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (!CanActivateArcanaSpread())
    return;

  Duel_ShowEffectText(ARCANA_SPREAD);

  if (IsDuelOver() == TRUE)
    return;

  hasHeads = FindFirstMatchingDeckIndex(ACTIVE_DUELIST, IsArcanaForceLevel4OrLower) >= 0;
  hasTails = FindFirstMatchingGyIndex(fixedDuelist, IsCoinTossMonster) >= 0;

  if (ActiveControlsFaceUpLightBarrier() && WhoseTurn() == DUEL_PLAYER && !gHideEffectText
      && hasHeads && hasTails)
    heads = PlayerChoosesCoinEffect();
  else if (ActiveControlsFaceUpLightBarrier() && WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    heads = hasHeads;
  else
    heads = RandRangeU8(0, 1) == 1;

  if (heads && !hasHeads && hasTails)
    heads = FALSE;
  else if (!heads && !hasTails && hasHeads)
    heads = TRUE;

  if (spellZone != NULL && spellZone->id == ARCANA_SPREAD)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE)
    return;

  if (!HasEmptyMonsterZone() || ArchlordKristya_IsSpecialSummonLocked())
    return;

  if (heads)
    ResolveHeadsFromDeck();
  else
    ResolveTailsFromGy();

  EffectOpt_MarkUsed(ARCANA_SPREAD);
  UpdateDuelGfxExceptField();

  /* ponytail: GY banish → add 1 coin-toss card from GY to hand needs a GY
   * ignition path outside this spell file (no in-file graveyard activation).
   * Ceiling: on-field coin SS only; upgrade: GY activate → banish ARCANA_SPREAD
   * then DeckMenu pick IsCoinTossCard from GY → add to hand (OPT shared). */
}

APPEND_TEXT void EffectARCANA_SPREAD(void)
{
  if (!CanActivateArcanaSpread()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(ARCANA_SPREAD, ARCANA_SPREAD_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ARCANA_SPREAD_SelfCheck(void)
{
  if (!IsArcanaForceLevel4OrLower(ARCANA_FORCE_0_THE_FOOL))
    while (1)
      ;
  if (IsArcanaForceLevel4OrLower(ARCANA_FORCE_EX_THE_LIGHT_RULER))
    while (1)
      ;
  if (!IsCoinTossMonster(ARCANA_FORCE_0_THE_FOOL))
    while (1)
      ;
  if (!IsCoinTossCard(CUP_OF_ACE))
    while (1)
      ;
}
#endif
