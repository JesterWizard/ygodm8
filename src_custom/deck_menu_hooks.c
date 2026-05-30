#include "global.h"
#include "card.h"
#include "configs/runtime.h"
#include "custom_decks/custom_decks.h"
#include "player_decks.h"
#include "duel.h"

extern unsigned gDeckCapacity;
extern unsigned gDuelistLevel;
extern unsigned short gDeckCapacityUpperLimitForDuelistLevel[];
extern struct DuelData gDuelData;
void IncreaseDuelistLevel(void);
unsigned GetDuelistLevel(void);
unsigned GetDeckCapacity(void);
void IncreaseDeckCapacity(unsigned);
void SubtractCostFromDeckCapacity(unsigned);
unsigned char ShouldDuelistLevelIncrease(void);
extern unsigned short gNewButtons;
extern unsigned short gPressedButtons;
extern unsigned short gRepeatedOrNewButtons;
extern unsigned short gOamBuffer[];
extern unsigned short gStarterDeck[];
void UpdateFilteredInput_NoRepeat(void);
void RunPlayerDeckTask(unsigned char);
void InitDeckData(void);
unsigned short GetSelectedCardWithOffset(unsigned char);
void AddCardToTrunk(unsigned short);
void SyncCardOwnershipQty(u16);
void SyncTrunkQtyFromOwnedTotal(u16);
void sub_801EF30(unsigned char);
void sub_801F4A0(unsigned char);
void sub_801F5F0(void);
void sub_801F614(void);
int ProcessInputDeckSubmenus(void);
void A_Submenu_Main(void);
unsigned short sub_08007FEC(unsigned char, unsigned char, unsigned short);
void sub_800800C(unsigned char, unsigned char, unsigned short, unsigned short);
void CalculateCurrentDeckCost(void);
void AddCardToDeck(unsigned short);
unsigned char IsPlayerDeckFull(void);
unsigned char GetPlayerDeckSize(void);
void RemoveCardFromDeckAtIndex(unsigned char);
void SubtractCostFromDeckCapacity(unsigned);
void SetCardInfo(unsigned short);
extern struct CardInfo gCardInfo;

extern unsigned short gUnk_808D9B0[][30];
extern unsigned char g8DF811C[];

static const unsigned char gE00AD4[] APPEND_RODATA = {0, 0, 1};
static const unsigned char gE00AD6[] APPEND_RODATA = {1, 2, 2};
static const unsigned char gE00AD8[] APPEND_RODATA = {72, 88, 104};
static const unsigned char gE00ADB[] APPEND_RODATA = {56, 56, 56};

static const unsigned char gDeckSubmenuText[] APPEND_TEXT = _(
  "{ENG}"
    "Details   "
    "Add to trunk        "
    "Add all to trunk    "
  "{FRE}"
    "Détails   "
    "Ajouter au coffre   "
    "Tout ajouter au cof"
  "{GER}"
    "Details   "
    "In das Deck         "
    "Alle in Stamm       "
  "{ITA}"
    "Dettagli  "
    "Vai a Deck          "
    "Tutto nel Tronco    "
  "{SPA}"
    "Detalles  "
    "Mover al tronco     "
    "Todo al tronco      "
  "{JAP}"
    "ディテール     "
    "かばんへ送る       "
    "すべてかばんへ     "
);

static void sub_801DE5C(void) {
  unsigned char i;
  unsigned short r7;

  for (i = 0; i < 20; i++)
    CpuCopy32(gUnk_808D9B0[i], &(((struct Sbb *)&gBgVram)->sbbF[i]), 60);
  CpuFill16(0, gBgVram.cbb1, 32);
  r7 = sub_08007FEC(9, 9, 0x7800) & 0xFF00;
  for (i = 0; i < 20; i++) {
    sub_800800C(i + 9, 11, 0x7800, (g8DF811C[i] + 21) | r7);
    sub_800800C(i + 9, 12, 0x7800, (g8DF811C[i] + 23) | r7);
    sub_800800C(i + 9, 13, 0x7800, (g8DF811C[i] + 61) | r7);
    sub_800800C(i + 9, 14, 0x7800, (g8DF811C[i] + 63) | r7);
  }
  CopyStringTilesToVRAMBuffer(&gBgVram.cbb1[32], gDeckSubmenuText, 0x900);
}

static void sub_801D61C(unsigned char cursorState) {
  unsigned *oam = (unsigned *)&gOamBuffer[6 * 4];
  oam[0] = gE00AD8[cursorState] |
           gE00ADB[cursorState] << 16 | 0x40000000;
  oam[1] = 0xC120;
  oam[2] = gE00AD8[cursorState] |
           gE00ADB[cursorState] << 16 | 0x40000800;
  oam[3] = 0x120;
}

static void sub_801D678(void) {
  unsigned *oam = (unsigned *)&gOamBuffer[6 * 4];
  oam[0] = 0;
  oam[1] = 0;
  oam[2] = 0;
  oam[3] = 0;
}

static void DeckSubmenuVBlank(void) {
  LoadPalettes();
  LoadOam();
  REG_DISPCNT = DISPCNT_BG_ALL_ON | DISPCNT_OBJ_ON | DISPCNT_WIN0_ON | DISPCNT_OBJWIN_ON;
  REG_BLDALPHA = 6;
  REG_BLDY = 10;
  REG_BLDCNT |= 8;
}

static void MoveAllCardsToTrunk(void) {
  unsigned i;

  for (i = 0; i < 40; i++) {
    unsigned short cardId = gDeckMenu.cards[i];

    if (cardId != CARD_NONE) {
      AddCardToTrunk(cardId);
      gDeckMenu.cards[i] = CARD_NONE;
      SyncCardOwnershipQty(cardId);
    }
  }
  gDeckMenu.cardCount = 0;
  gDeckMenu.currentPos = 0;
  CalculateCurrentDeckCost();
  PlayMusic(SFX_SELECT);
}

static void MoveSelectedCardToTrunk(void) {
  unsigned short cardId = GetSelectedCardWithOffset(2);

  if (!cardId) {
    PlayMusic(SFX_FORBIDDEN);
    return;
  }

  SetCardInfo(cardId);
  AddCardToTrunk(cardId);
  RemoveCardFromDeckAtIndex(gDeckMenu.currentPos);
  SyncCardOwnershipQty(cardId);

  if (gDeckMenu.currentPos >= gDeckMenu.cardCount) {
    unsigned char temp = gDeckMenu.currentPos - gDeckMenu.cardCount + 1;

    if (gDeckMenu.currentPos) {
      if (temp <= gDeckMenu.currentPos)
        gDeckMenu.currentPos -= temp;
      else
        gDeckMenu.currentPos = 0;
      PlayMusic(SFX_MOVE_CURSOR);
    }
    else if (GetPlayerDeckSize()) {
      PlayMusic(SFX_FORBIDDEN);
      while (gPressedButtons & DPAD_UP)
        WaitForVBlank();
    }
  }

  SubtractCostFromDeckCapacity(gCardInfo.cost);
  PlayMusic(SFX_SELECT);
}

static u8 GetRuntimeDeckLimit(void) {
  u8 limit = gRuntimeConfig.max_deck_cards;

  if (limit == 0 || limit > DECK_SIZE)
    return DECK_SIZE;
  return limit;
}

static u32 GetDefaultDeckCapacityValue(void) {
  if (gRuntimeConfig.max_deck_capacity_at_start == TRUE)
    return 65000;
  return 1600;
}

LYN_REPLACE_CHECK(InitDeckCapacity);
void InitDeckCapacity__Replacement(void) {
  gDeckCapacity = GetDefaultDeckCapacityValue();
}

LYN_REPLACE_CHECK(InitNewGameDeck);
void InitNewGameDeck__Replacement(void) {
  unsigned i;
  const u16 *deck = gStarterDeck;

  if (CustomDecks_IsEnabled() == TRUE) {
    const u16 *customDeck = CustomDecks_GetNewGameDeck();

    if (customDeck != NULL)
      deck = customDeck;
  }

  for (i = 0; i < DECK_SIZE; i++)
    gDeckMenu.cards[i] = deck[i];

  InitDeckData();

  if (PlayerDecks_IsEnabled() == TRUE)
    PlayerDecks_InitNewGame();
}

LYN_REPLACE_CHECK(IncreaseDeckCapacity);
void IncreaseDeckCapacity__Replacement(unsigned increase) {
  if (increase > 65000 - gDeckCapacity)
    gDeckCapacity = 65000;
  else
    gDeckCapacity += increase;

  IncreaseDuelistLevel();
}

LYN_REPLACE_CHECK(SubtractCostFromDeckCapacity);
void SubtractCostFromDeckCapacity__Replacement(unsigned subtractCost) {
  if (subtractCost > gDeckMenu.cost)
    gDeckMenu.cost = 0;
  else
    gDeckMenu.cost -= subtractCost;
}

LYN_REPLACE_CHECK(ShouldDuelistLevelIncrease);
unsigned char ShouldDuelistLevelIncrease__Replacement(void) {
  if (gDuelistLevel >= 999)
    return 0;

  if (gDeckCapacity >= gDeckCapacityUpperLimitForDuelistLevel[gDuelistLevel + 1]) {
    gDuelData.unk2c = 1;
    return 1;
  }

  return 0;
}

LYN_REPLACE_CHECK(InitDuelistLevel);
void InitDuelistLevel__Replacement(void) {
  gDuelistLevel = 72;

  if (gRuntimeConfig.max_duelist_level_at_start == TRUE)
    gDuelistLevel = 999;
}

LYN_REPLACE_CHECK(AddCardToDeck);
void AddCardToDeck__Replacement(unsigned short cardId) {
  unsigned limit = GetRuntimeDeckLimit();

  if (gDeckMenu.cardCount >= limit || !gTrunkCardQty[cardId])
    return;

  if (CardExceedsCurrentDuelistLevel(cardId))
    return;

  SetCardInfo(cardId);

  gTrunkCardQty[cardId]--;
  gDeckMenu.cards[gDeckMenu.cardCount] = cardId;
  gDeckMenu.cardCount++;
  CalculateCurrentDeckCost();
  SyncCardOwnershipQty(cardId);
}

LYN_REPLACE_CHECK(IsPlayerDeckFull);
unsigned char IsPlayerDeckFull__Replacement(void) {
  return gDeckMenu.cardCount >= GetRuntimeDeckLimit();
}

LYN_REPLACE_CHECK(ProcessInputDeckSubmenus);
int ProcessInputDeckSubmenus__Replacement(void) {
  unsigned char i;
  unsigned short mask;
  unsigned short ret = 0;
  UpdateFilteredInput_NoRepeat();
  mask = 0x1;
  for (i = 0; i < NUM_BUTTONS; i++) {
    if (mask & gNewButtons)
      ret = mask & gNewButtons;
    mask <<= 1;
  }
  mask = 0x10;
  for (i = 0; i < 4; i++) {
    if (mask & gRepeatedOrNewButtons)
      ret = mask & gRepeatedOrNewButtons;
    mask <<= 1;
  }
  if (gRepeatedOrNewButtons & DPAD_UP && gPressedButtons & R_BUTTON)
    ret = REPEAT_DPAD_UP | R_BUTTON;
  if (gRepeatedOrNewButtons & DPAD_DOWN && gPressedButtons & R_BUTTON)
    ret = REPEAT_DPAD_DOWN | R_BUTTON;
  return ret;
}

LYN_REPLACE_CHECK(A_Submenu_Main);
void A_Submenu_Main__Replacement(void) {
  unsigned keepProcessing;
  unsigned char cursorState;

  cursorState = 0;
  PlayMusic(SFX_SELECT);
  sub_801DE5C();
  sub_801D61C(cursorState);
  LoadCharblock1();
  SetVBlankCallback(DeckSubmenuVBlank);
  WaitForVBlank();
  keepProcessing = 1;
  while (keepProcessing) {
    switch (ProcessInputDeckSubmenus__Replacement()) {
      case REPEAT_DPAD_UP:
        cursorState = gE00AD4[cursorState];
        sub_801D61C(cursorState);
        PlayMusic(SFX_MOVE_CURSOR);
        SetVBlankCallback(LoadOam);
        WaitForVBlank();
        break;
      case REPEAT_DPAD_DOWN:
        cursorState = gE00AD6[cursorState];
        sub_801D61C(cursorState);
        PlayMusic(SFX_MOVE_CURSOR);
        SetVBlankCallback(LoadOam);
        WaitForVBlank();
        break;
      case NEW_A_BUTTON:
        switch (cursorState) {
          case 0: {
            u16 cardId = GetSelectedCardWithOffset(2);

            SetCardInfoWithWarning(&cardId);
            PlayMusic(SFX_SELECT);
            ShowCardDetailView();
            sub_801EF30(0);
            sub_801EF30(2);
            sub_801F4A0(1);
            sub_801F5F0();
            sub_801DE5C();
            sub_801D61C(cursorState);
            SetVBlankCallback(DeckSubmenuVBlank);
            WaitForVBlank();
            LoadCharblock1();
            break;
          }
          case 1:
            MoveSelectedCardToTrunk();
            sub_801EF30(3);
            sub_801F614();
            sub_801F4A0(6);
            keepProcessing = 0;
            break;
          case 2:
            MoveAllCardsToTrunk();
            sub_801EF30(3);
            sub_801F614();
            sub_801F4A0(6);
            keepProcessing = 0;
            break;
        }
        break;
      case NEW_B_BUTTON:
        keepProcessing = 0;
        PlayMusic(SFX_CANCEL);
        break;
      default:
        WaitForVBlank();
        break;
    }
  }
  sub_801D678();
}
