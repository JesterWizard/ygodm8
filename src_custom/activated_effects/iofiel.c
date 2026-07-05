#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "iofiel.h"

extern unsigned char IsSkillDrainActiveOnField(void);
extern unsigned char TryActivateSkillDrainAndNegateCardId(u16 negatedCardId);
extern void UpdateDuelGfxExceptField(void);

#define IOFIEL_ATK_BOOST_STAGES 2

static const u8 sIofielPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsLevel1FairyMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  if (gCardData_NEW[cardId].type != TYPE_FAIRY)
    return FALSE;

  return gCardData_NEW[cardId].level == 1;
}

static u8 IsFaceUpIofielSummon(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != IOFIEL)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static s16 FindFirstLevel1FairyDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsLevel1FairyMonster(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 LoadLevel1FairyDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
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

    if (!IsLevel1FairyMonster(cardId))
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

static u8 PickAiLevel1FairyDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 bestMenuIdx = 0;
  u16 bestAtk = 0xFFFF;
  u8 i;

  menuCount = LoadLevel1FairyDeckMenu(turnDuelist, deckIndexMap);
  if (menuCount == 0)
    return 0xFF;

  for (i = 0; i < menuCount; i++) {
    u16 cardId = gDeckMenu.cards[i];
    u16 atk = gCardData_NEW[cardId].atk;

    if (atk < bestAtk) {
      bestAtk = atk;
      bestMenuIdx = i;
    }
  }

  return deckIndexMap[bestMenuIdx];
}

static u8 PickLevel1FairyDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 i;
  u8 deckIndex;

  menuCount = LoadLevel1FairyDeckMenu(turnDuelist, deckIndexMap);
  if (menuCount == 0)
    return 0xFF;

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER)
    return PickAiLevel1FairyDeckIndex(turnDuelist);

  for (i = 0; i < sizeof(gDeckMenu); i++)
    savedDeckMenu[i] = ((u8 *)&gDeckMenu)[i];

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sIofielPickLabels, ARRAY_COUNT(sIofielPickLabels))) {
    for (i = 0; i < sizeof(gDeckMenu); i++)
      ((u8 *)&gDeckMenu)[i] = savedDeckMenu[i];
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  for (i = 0; i < sizeof(gDeckMenu); i++)
    ((u8 *)&gDeckMenu)[i] = savedDeckMenu[i];
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static u8 SendLevel1FairyFromDeckToGraveyard(u8 turnDuelist, u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsLevel1FairyMonster(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  GraveyardExpand_PushTurn(turnDuelist, cardId);
  return TRUE;
}

static void ApplyIofielAtkBoost(struct DuelCard *zone)
{
  u8 stage;

  for (stage = 0; stage < IOFIEL_ATK_BOOST_STAGES; stage++)
    IncrementTempStage(zone);

  zone->unk4 = 1;
  Duel_NotifyMonsterZoneChanged(zone);
  Duel_RefreshMonsterStatOverlays();
}

static void ActivateIofielSummonEffect(struct DuelCard *zone, u8 turnDuelist)
{
  u8 deckIndex;

  Duel_ShowEffectTextTyped(IOFIEL, 2);

  if (IsDuelOver() == TRUE)
    return;

  deckIndex = PickLevel1FairyDeckIndex(turnDuelist);
  if (deckIndex == 0xFF)
    return;

  if (!SendLevel1FairyFromDeckToGraveyard(turnDuelist, deckIndex))
    return;

  if (IsDuelOver() == TRUE)
    return;

  ApplyIofielAtkBoost(zone);
  UpdateDuelGfxExceptField();
}

void TryIofielOnMonsterPlacement(struct DuelCard *zone)
{
  u8 turnRow;
  u8 col;
  u8 turnDuelist;

  if (!IsFaceUpIofielSummon(zone) || zone->unk4 == 1)
    return;

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return;

  turnDuelist = (turnRow == ACTIVE_DUELIST_MONSTER_ROW) ? ACTIVE_DUELIST : INACTIVE_DUELIST;

  if (FindFirstLevel1FairyDeckIndex(turnDuelist) < 0)
    return;

  if (IsSkillDrainActiveOnField() && TryActivateSkillDrainAndNegateCardId(IOFIEL))
    return;

  ActivateIofielSummonEffect(zone, turnDuelist);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void Iofiel_SelfCheck(void)
{
  if (!IsLevel1FairyMonster(TINY_ANGEL))
    while (1)
      ;
  if (IsLevel1FairyMonster(IOFIEL))
    while (1)
      ;
}
#endif
