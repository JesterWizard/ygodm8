#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

#define LIGHT_FORCE_SEARCH_COUNT 2
#define LIGHT_FORCE_FAIRY_STAT_BONUS 300

void UpdateDuelGfxExceptField(void);

static const char sArcanaForceArchetypeName[] APPEND_RODATA = "Arcana Force";
static u8 sLightForceNegated[2] APPEND_DATA = {FALSE, FALSE};
static u8 sLightForceSpecialSummonLocked[2] APPEND_DATA = {FALSE, FALSE};

static const u8 sLightForcePickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 AnyHandCard(u16 cardId)
{
  return cardId != CARD_NONE;
}

static u8 IsArcanaForceMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sArcanaForceArchetypeName);
}

u8 LightForce_IsActiveForDuelist(u8 fixedDuelist)
{
  if (fixedDuelist != DUEL_PLAYER && fixedDuelist != DUEL_OPPONENT)
    return FALSE;

  return Duel_FindBackrowCard(fixedDuelist, LIGHT_FORCE, TRUE) != NULL;
}

u8 LightForce_IsNegatedForDuelist(u8 fixedDuelist)
{
  if (fixedDuelist != DUEL_PLAYER && fixedDuelist != DUEL_OPPONENT)
    return FALSE;

  return sLightForceNegated[fixedDuelist];
}

void LightForce_ResolveStandbyCoin(u8 fixedDuelist, u8 heads)
{
  if (fixedDuelist != DUEL_PLAYER && fixedDuelist != DUEL_OPPONENT)
    return;

  if (Duel_FindBackrowCard(fixedDuelist, LIGHT_BARRIER, TRUE) != NULL) {
    sLightForceNegated[fixedDuelist] = FALSE;
    return;
  }

  sLightForceNegated[fixedDuelist] =
      LightForce_IsActiveForDuelist(fixedDuelist) && !heads;
}

u8 LightForce_BlocksSpecialSummon(u8 fixedDuelist, u16 cardId)
{
  if (fixedDuelist != DUEL_PLAYER && fixedDuelist != DUEL_OPPONENT)
    return FALSE;

  return sLightForceSpecialSummonLocked[fixedDuelist] && !IsArcanaForceMonster(cardId);
}

void LightForce_ClearTurnState(void)
{
  sLightForceSpecialSummonLocked[DUEL_PLAYER] = FALSE;
  sLightForceSpecialSummonLocked[DUEL_OPPONENT] = FALSE;
}

void ApplyLightForceFairyStatBoostForZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 fixedDuelist;
  u32 boosted;

  if (zone == NULL || zone->id == CARD_NONE
      || !Duel_CardHasMonsterType(zone->id, TYPE_FAIRY)
      || !Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return;

  fixedDuelist = Duel_FixedDuelistForMonsterRow(fixedRow);
  if (!LightForce_IsActiveForDuelist(fixedDuelist)
      || LightForce_IsNegatedForDuelist(fixedDuelist))
    return;

  if (gCardInfo.atk != 0xFFFF) {
    boosted = (u32)gCardInfo.atk + LIGHT_FORCE_FAIRY_STAT_BONUS;
    gCardInfo.atk = boosted > 0xFFFE ? 0xFFFE : (u16)boosted;
  }
  if (gCardInfo.def != 0xFFFF) {
    boosted = (u32)gCardInfo.def + LIGHT_FORCE_FAIRY_STAT_BONUS;
    gCardInfo.def = boosted > 0xFFFE ? 0xFFFE : (u16)boosted;
  }
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

static u8 CountDistinctArcanaForceInDeck(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u16 seen[LIGHT_FORCE_SEARCH_COUNT];
  u8 distinct = 0;
  u8 i;
  u8 j;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];
    u8 already = FALSE;

    if (!IsArcanaForceMonster(cardId))
      continue;

    for (j = 0; j < distinct; j++) {
      if (seen[j] == cardId) {
        already = TRUE;
        break;
      }
    }

    if (already)
      continue;

    if (distinct < LIGHT_FORCE_SEARCH_COUNT)
      seen[distinct] = cardId;
    distinct++;
    if (distinct >= LIGHT_FORCE_SEARCH_COUNT)
      return distinct;
  }

  return distinct;
}

static s16 FindFirstArcanaDeckIndex(u8 turnDuelist, u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsArcanaForceMonster(cardId))
      continue;
    if (excludeId != CARD_NONE && cardId == excludeId)
      continue;

    return (s16)i;
  }

  return -1;
}

static u8 CanActivateLightForceIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != LIGHT_FORCE || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) == 0)
    return FALSE;

  /* After discard need 2 empty slots to add 2 → need ≥1 empty before discard. */
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return CountDistinctArcanaForceInDeck(ACTIVE_DUELIST) >= LIGHT_FORCE_SEARCH_COUNT;
}

static u8 LoadArcanaDeckMenu(u8 turnDuelist, u16 excludeId, u8 *deckIndexOut)
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

    if (!IsArcanaForceMonster(cardId))
      continue;
    if (excludeId != CARD_NONE && cardId == excludeId)
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

static u8 PickArcanaDeckIndex(u8 turnDuelist, u16 excludeId)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadArcanaDeckMenu(turnDuelist, excludeId, deckIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sLightForcePickLabels,
                                         ARRAY_COUNT(sLightForcePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static u8 AddDeckCardAtIndexToHand(u8 turnDuelist, u8 deckIndex, u16 excludeId)
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
  if (!IsArcanaForceMonster(cardId))
    return FALSE;
  if (excludeId != CARD_NONE && cardId == excludeId)
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone),
                       cardId);
  return TRUE;
}

static void SearchTwoArcanaForce(void)
{
  u8 i;
  u16 firstId = CARD_NONE;

  for (i = 0; i < LIGHT_FORCE_SEARCH_COUNT; i++) {
    u8 deckIndex;
    u8 fixedDuelist;
    u16 addedId;

    if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
      break;

    if (FindFirstArcanaDeckIndex(ACTIVE_DUELIST, firstId) < 0)
      break;

    deckIndex = PickArcanaDeckIndex(ACTIVE_DUELIST, firstId);
    if (deckIndex == 0xFF)
      break;

    fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
    addedId = gDuelDecks[fixedDuelist].cards[deckIndex];

    if (!AddDeckCardAtIndexToHand(ACTIVE_DUELIST, deckIndex, firstId))
      break;

    if (i == 0)
      firstId = addedId;
  }
}

static void ResolveLightForceIgnition(struct DuelCard *zone)
{
  if (!CanActivateLightForceIgnition(zone))
    return;

  Duel_ShowEffectText(LIGHT_FORCE);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, AnyHandCard, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  SearchTwoArcanaForce();
  sLightForceSpecialSummonLocked[FixedDuelistForTurnDuelist(ACTIVE_DUELIST)] = TRUE;
  zone->effectUsedThisTurn = TRUE;
  UpdateDuelGfxExceptField();
}

static void LIGHT_FORCE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up continuous (OPT discard/search). */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivateLightForceIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveLightForceIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(LIGHT_FORCE);

  if (CanActivateLightForceIgnition(zone))
    ResolveLightForceIgnition(zone);
}

APPEND_TEXT void EffectLIGHT_FORCE(void)
{
  if (Duel_TryResolveSpellThroughTraps(LIGHT_FORCE, LIGHT_FORCE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void LIGHT_FORCE_SelfCheck(void)
{
  if (LIGHT_FORCE_SEARCH_COUNT != 2)
    while (1)
      ;
  if (LIGHT_FORCE_FAIRY_STAT_BONUS != 300)
    while (1)
      ;
  if (!IsArcanaForceMonster(ARCANA_FORCE_0_THE_FOOL))
    while (1)
      ;
  if (!IsArcanaForceMonster(ARCANA_FORCE_EX_THE_LIGHT_RULER))
    while (1)
      ;
  if (IsArcanaForceMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
