#include "global.h"
#include "configs/runtime.h"
#include "generated/card_trunk_generated.inc"

extern const unsigned char gStarterTrunk[];
extern unsigned char gTrunkCardQty[];
extern unsigned char gTotalCardQty[];
extern void SortCardsAccordingToContext(void);
extern u8 gUnk_8DFA6A8[];
extern struct CardSortContext gCardSortContext;
extern struct TrunkMenu gTrunkMenu;
extern struct UnkStruct_2021AB4 gUnk2021AB4;
unsigned char GetDeckCardQty(unsigned short);
void SetCardInfo(unsigned short id);
void TrunkMenuDefaultSort(void);
unsigned short GetNthCardOnScreen(unsigned char);
void sub_800907C(void);
void GoUpOnePosition(void);
void GoDownOnePosition(void);
void GoUpFiftyPositions(void);
void GoDownFiftyPositions(void);
void InitTrunkData(void);

static u16 GetTrunkCardCount(void) {
  return NUM_TRUE_CARDS + NUM_CUSTOM_TRUNK_CARDS;
}

static u16 GetLastTrackedCardId(void) {
  return CUSTOM_CARD_START + NUM_CUSTOM_TRUNK_CARDS;
}

static void AppendCustomTrunkCard(void) {
  u16 i;

  for (i = 0; i < NUM_CUSTOM_TRUNK_CARDS; i++)
    gTrunkMenu.cards[NUM_TRUE_CARDS + i] = gCustomTrunkCards[i];
}

static void WrapTrunkCursorToList(void) {
  if (gTrunkMenu.currentPos >= GetTrunkCardCount())
    gTrunkMenu.currentPos -= GetTrunkCardCount();
}

LYN_REPLACE_CHECK(InitTrunkCards);
void InitTrunkCards__Replacement(void) {
  u32 id;

  for (id = 0; id < GetLastTrackedCardId(); id++) {
    if (id >= CUSTOM_CARD_START) {
      gTrunkCardQty[id] = gRuntimeConfig.start_with_three_copies_of_every_card == TRUE ? 3 : 1;
    }
    else if (gRuntimeConfig.start_with_three_copies_of_every_card == TRUE)
      gTrunkCardQty[id] = 3;
    else
      gTrunkCardQty[id] = gStarterTrunk[id];
  }
}

LYN_REPLACE_CHECK(InitTrunkData);
void InitTrunkData__Replacement(void) {
  unsigned short cardId;

  gTrunkMenu.currentPos = 0;
  gTrunkMenu.displayMode = 1;
  gTrunkMenu.sortMode = CARD_SORT_NUMBER;

  for (cardId = 0; cardId < GetLastTrackedCardId(); cardId++)
    gTotalCardQty[cardId] = gTrunkCardQty[cardId] + GetDeckCardQty(cardId);

  for (cardId = 0; cardId < NUM_TRUE_CARDS; cardId++)
    gTrunkMenu.cards[cardId] = cardId + 1;

  AppendCustomTrunkCard();
}

LYN_REPLACE_CHECK(TrunkMenuDefaultSort);
void TrunkMenuDefaultSort__Replacement(void) {
  u16 cardId;

  gCardSortContext.cards = gTrunkMenu.cards;
  gCardSortContext.cardCount = NUM_TRUE_CARDS;
  gCardSortContext.sortMode = gUnk_8DFA6A8[gTrunkMenu.sortMode];
  SortCardsAccordingToContext();
  AppendCustomTrunkCard();
}

LYN_REPLACE_CHECK(GetNthCardOnScreen);
unsigned short GetNthCardOnScreen__Replacement(u8 n) {
  s16 wrappedIndex = gTrunkMenu.currentPos + n - 2;
  u16 count = GetTrunkCardCount();

  if (wrappedIndex >= count)
    wrappedIndex -= count;
  else if (wrappedIndex < 0)
    wrappedIndex += count;

  return gTrunkMenu.cards[wrappedIndex];
}

LYN_REPLACE_CHECK(sub_800907C);
void sub_800907C__Replacement(void) {
  gUnk2021AB4.currentPos = gTrunkMenu.currentPos;
  gUnk2021AB4.lastValidIndex = GetTrunkCardCount() - 1;
}

LYN_REPLACE_CHECK(GoUpOnePosition);
void GoUpOnePosition__Replacement(void) {
  if (--gTrunkMenu.currentPos < 0)
    gTrunkMenu.currentPos += GetTrunkCardCount();
  PlayMusic(SFX_MOVE_CURSOR);
}

LYN_REPLACE_CHECK(GoDownOnePosition);
void GoDownOnePosition__Replacement(void) {
  if (++gTrunkMenu.currentPos > GetTrunkCardCount() - 1)
    gTrunkMenu.currentPos -= GetTrunkCardCount();
  PlayMusic(SFX_MOVE_CURSOR);
}

LYN_REPLACE_CHECK(GoUpFiftyPositions);
void GoUpFiftyPositions__Replacement(void) {
  gTrunkMenu.currentPos -= 50;
  if (gTrunkMenu.currentPos < 0)
    gTrunkMenu.currentPos += GetTrunkCardCount();
  PlayMusic(SFX_MOVE_CURSOR);
}

LYN_REPLACE_CHECK(GoDownFiftyPositions);
void GoDownFiftyPositions__Replacement(void) {
  gTrunkMenu.currentPos += 50;
  if (gTrunkMenu.currentPos > GetTrunkCardCount() - 1)
    gTrunkMenu.currentPos -= GetTrunkCardCount();
  PlayMusic(SFX_MOVE_CURSOR);
}
