#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

#define MAGICAL_STONE_EXCAVATION_DISCARD_COUNT 2

static const u8 sMagicalStonePickLabels[] APPEND_RODATA = {
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

static u8 IsSpellCard(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_SPELL;
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

static u8 GraveyardHasSpell(u8 fixedDuelist)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled())
    return IsSpellCard(gDuel.duelistbattleState[fixedDuelist].graveyard);

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsSpellCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static s8 FindFirstSpellGyIndex(u8 fixedDuelist)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsSpellCard(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 0;
    return -1;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsSpellCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 LoadSpellGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (!IsSpellCard(top)) {
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

    if (!IsSpellCard(cardId))
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

static s8 PlayerPickSpellGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadSpellGyMenu(fixedDuelist, gyIndexMap);
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
          sMagicalStonePickLabels, ARRAY_COUNT(sMagicalStonePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static u8 AddSpellFromGyToHand(u8 turnDuelist, u8 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = GetGraveCardAndClearGrave(turnDuelist);
    if (!IsSpellCard(cardId))
      return FALSE;
  } else {
    cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
    if (!IsSpellCard(cardId))
      return FALSE;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
  }

  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
  return TRUE;
}

static u8 CanActivateMagicalStoneExcavation(void)
{
  /* Excavator is already on the field — need 2 other hand cards to discard. */
  return Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST])
      >= MAGICAL_STONE_EXCAVATION_DISCARD_COUNT;
}

static void MAGICAL_STONE_EXCAVATION_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 gyIndex;

  Duel_ShowEffectText(MAGICAL_STONE_EXCAVATION);

  if (IsDuelOver() == TRUE || !CanActivateMagicalStoneExcavation())
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, MAGICAL_STONE_EXCAVATION_DISCARD_COUNT, AnyHandCard,
                           TRUE)
      != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (!GraveyardHasSpell(fixedDuelist)) {
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
    return;
  }

  if (!GraveyardExpand_IsEnabled()) {
    gyIndex = 0;
  } else if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    gyIndex = PlayerPickSpellGyIndex(fixedDuelist);
  } else {
    gyIndex = FindFirstSpellGyIndex(fixedDuelist);
  }

  if (gyIndex < 0) {
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
    return;
  }

  AddSpellFromGyToHand(ACTIVE_DUELIST, (u8)gyIndex);
  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectMAGICAL_STONE_EXCAVATION(void)
{
  if (!CanActivateMagicalStoneExcavation()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MAGICAL_STONE_EXCAVATION,
                                       MAGICAL_STONE_EXCAVATION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MAGICAL_STONE_EXCAVATION_SelfCheck(void)
{
  if (MAGICAL_STONE_EXCAVATION_DISCARD_COUNT != 2)
    while (1)
      ;
  if (!IsSpellCard(POT_OF_GREED))
    while (1)
      ;
  if (IsSpellCard(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
