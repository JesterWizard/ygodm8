#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);
void ClearZone(struct DuelCard *zone);

static const u8 sAromaBlendPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static const u16 sAromaWindsIds[] APPEND_RODATA = {
  HUMID_WINDS,
  DRIED_WINDS,
  BLESSED_WINDS,
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

static u8 IsAromaWindsCard(u16 cardId)
{
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sAromaWindsIds); i++) {
    if (cardId == sAromaWindsIds[i])
      return TRUE;
  }

  return FALSE;
}

static u8 HasEmptyBackrow(void)
{
  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]) >= 0;
}

static s8 FindAromaWindsHandZone(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsAromaWindsCard(gTurnHands[ACTIVE_DUELIST][i]->id))
      return (s8)i;
  }

  return -1;
}

static s16 FindFirstAromaWindsDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsAromaWindsCard(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 HasAromaWindsInHandOrDeck(void)
{
  if (FindAromaWindsHandZone() >= 0)
    return TRUE;

  return FindFirstAromaWindsDeckIndex(ACTIVE_DUELIST) >= 0;
}

static u8 CanActivateAromaBlend(void)
{
  u8 handCount = Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]);

  if (handCount < 1)
    return FALSE;

  if (!HasEmptyBackrow())
    return FALSE;

  /* After discard, need a Winds left in hand or Deck to place. */
  if (FindFirstAromaWindsDeckIndex(ACTIVE_DUELIST) >= 0)
    return TRUE;

  return FindAromaWindsHandZone() >= 0 && handCount >= 2;
}

static void InitFaceUpBackrowSlot(struct DuelCard *zone, u16 cardId)
{
  zone->id = cardId;
  zone->isFaceUp = TRUE;
  zone->isLocked = TRUE;
  zone->isDefending = FALSE;
  zone->unkTwo = 0;
  zone->unkThree = 0;
  zone->unk4 = 0;
  zone->willChangeSides = FALSE;
  ResetPermStage(zone);
  ResetTempStage(zone);
}

/* Menu entries: hand zones first (index | 0x80), then deck indices. */
#define AROMA_BLEND_HAND_FLAG 0x80

static u8 LoadAromaWindsMenu(u8 *locOut)
{
  u8 menuCount = 0;
  u8 i;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = gTurnHands[ACTIVE_DUELIST][i]->id;

    if (!IsAromaWindsCard(cardId))
      continue;

    locOut[menuCount] = (u8)(i | AROMA_BLEND_HAND_FLAG);
    gDeckMenu.cards[menuCount] = cardId;
    menuCount++;
  }

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsAromaWindsCard(cardId))
      continue;

    locOut[menuCount] = i;
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

static u8 PickAromaWindsLocation(void)
{
  u8 locMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 loc;

  DECKMENU_SAVE();

  menuCount = LoadAromaWindsMenu(locMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return 0xFF;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER || gHideEffectText) {
    loc = locMap[0];
    DECKMENU_RESTORE();
    return loc;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sAromaBlendPickLabels,
                                         ARRAY_COUNT(sAromaBlendPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  loc = locMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return loc;
}

static u8 PlaceAromaWindsFromLocation(u8 loc)
{
  s8 backCol;
  u16 cardId;

  backCol = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]);
  if (backCol < 0)
    return FALSE;

  if (loc & AROMA_BLEND_HAND_FLAG) {
    u8 handZone = loc & ~AROMA_BLEND_HAND_FLAG;
    struct DuelCard *handSlot;

    if (handZone >= MAX_ZONES_IN_ROW)
      return FALSE;

    handSlot = gTurnHands[ACTIVE_DUELIST][handZone];
    cardId = handSlot->id;
    if (!IsAromaWindsCard(cardId))
      return FALSE;

    ClearZone(handSlot);
    InitFaceUpBackrowSlot(gTurnZones[ACTIVE_DUELIST_BACKROW][backCol], cardId);
    return TRUE;
  }

  {
    u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
    u8 deckIndex = loc;

    if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
        || deckIndex >= NumCardsInDeck(fixedDuelist))
      return FALSE;

    cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
    if (!IsAromaWindsCard(cardId))
      return FALSE;

    if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, deckIndex, FALSE) != DUEL_ACTION_OK)
      return FALSE;

    Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
    InitFaceUpBackrowSlot(gTurnZones[ACTIVE_DUELIST_BACKROW][backCol], cardId);
    return TRUE;
  }
}

static void DestroyAromaBlendSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == AROMA_BLEND)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void AROMA_BLEND_ResolveBody(void)
{
  u8 loc;

  Duel_ShowEffectText(AROMA_BLEND);

  if (IsDuelOver() == TRUE || !CanActivateAromaBlend())
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, AnyHandCard, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  /* Discard may have consumed the only Winds in hand — re-check. */
  if (!HasEmptyBackrow() || !HasAromaWindsInHandOrDeck()) {
    DestroyAromaBlendSpellZone();
    return;
  }

  loc = PickAromaWindsLocation();
  if (loc == 0xFF) {
    DestroyAromaBlendSpellZone();
    return;
  }

  if (!PlaceAromaWindsFromLocation(loc)) {
    DestroyAromaBlendSpellZone();
    return;
  }

  DestroyAromaBlendSpellZone();

  /* ponytail: GY effect (banish this → Fusion Summon Plant Fusion by banishing
   * materials from hand/field, and GY Plants if LP higher) needs a GY-activate
   * path + Plant Fusion recipe filter outside this file.
   * Ceiling: discard + place Humid/Dried/Blessed Winds face-up only; upgrade:
   * GY activate AROMA_BLEND → banish self → FusionDuel Plant Fusion pay
   * banish hand/field (+ GY Plants if gDuelLifePoints[self] > opp). */

  /* ponytail: placed Winds are face-up/locked but their continuous trap effects
   * are not auto-wired (trap stubs). Ceiling: card sits face-up; upgrade: call
   * each Winds activate body after place, or wire trap dispatcher. */
}

APPEND_TEXT void EffectAROMA_BLEND(void)
{
  if (!CanActivateAromaBlend()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(AROMA_BLEND, AROMA_BLEND_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void AROMA_BLEND_SelfCheck(void)
{
  if (!IsAromaWindsCard(HUMID_WINDS))
    while (1)
      ;
  if (!IsAromaWindsCard(DRIED_WINDS))
    while (1)
      ;
  if (!IsAromaWindsCard(BLESSED_WINDS))
    while (1)
      ;
  if (IsAromaWindsCard(AROMA_GARDEN))
    while (1)
      ;
}
#endif
