#include "global.h"
#include "card.h"
#include "configs/runtime.h"
#include "constants/music_ids.h"
#include "custom_decks/custom_decks.h"
#include "deck_menu.h"
#include "player_decks.h"
#include "duel.h"
#include "text.h"

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

/* Set by deck_menu callers to enable DPAD left/right card navigation in detail view. */
extern u8 gCardDetailNavActive;
extern u8 gCardDetailNavIndex;
extern unsigned short gStarterDeck[];
void UpdateFilteredInput_NoRepeat(void);
void RunPlayerDeckTask(unsigned char);
void InitDeckData(void);
unsigned short GetSelectedCardWithOffset(unsigned char);
void SyncCardOwnershipQty(u16);
void SyncTrunkQtyFromOwnedTotal(u16);
u8 TrunkMenu_GetTrunkQty(u16 cardId);
void TrunkMenu_DecrementTrunkQty(u16 cardId);
void TrunkMenu_IncrementTrunkQty(u16 cardId);
void sub_801EF30(unsigned char);
void sub_801F4A0(unsigned char);
void sub_801F5F0(void);
void sub_801F5FC(void);
void sub_801F614(void);
void sub_801F630(void);
void sub_801F644(void);
void sub_801F120(void);
void sub_0801F62C(void);
void sub_0801F5EC(void);
void RunTrunkTask(unsigned char);
void DeckMenuSort(void);
void ToggleDeckSortMode(void);
unsigned IsPlayerDeckNonempty(void);
void ClearGraphicsBuffers(void);
void DisableDisplay(void);
void LoadOam(void);
void LoadPalettes(void);
void UpdateAllDuelGfx(void);
extern unsigned short gFilteredInput;
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

static const unsigned char sDeckMenuPickLabelDetails[] APPEND_TEXT = _(
  "{ENG}"
    "Details   "
  "{FRE}"
    "Détails   "
  "{GER}"
    "Details   "
  "{ITA}"
    "Dettagli  "
  "{SPA}"
    "Detalles  "
  "{JAP}"
    "ディテール     "
);

static const unsigned char sDeckMenuPickLabelFusionSummon[] APPEND_TEXT = _(
  "{ENG}"
    "Fusion Summon       "
  "{FRE}"
    "Invocation Fusion   "
  "{GER}"
    "Fusion beschwören   "
  "{ITA}"
    "Evoca Fusione       "
  "{SPA}"
    "Invocar Fusión      "
  "{JAP}"
    "フュージョン召喚         "
);

static const unsigned char sDeckMenuPickLabelSelectCard[] APPEND_TEXT = _(
  "{ENG}"
    "Select This Card    "
  "{FRE}"
    "Choisir cette carte "
  "{GER}"
    "Diese Karte wählen  "
  "{ITA}"
    "Scegli questa carta "
  "{SPA}"
    "Elegir esta carta   "
  "{JAP}"
    "このカードを選ぶ   "
);

static const unsigned char sDeckMenuPickLabelBlankShort[] APPEND_TEXT =
    "          ";

static const unsigned char sDeckMenuPickLabelBlankLong[] APPEND_TEXT =
    "                    ";

static const unsigned char sDeckMenuPickLabelReturnToTrunk[] APPEND_TEXT = _(
  "{ENG}"
    "Return to Trunk     "
  "{FRE}"
    "Retour au coffre    "
  "{GER}"
    "Zurück zum Koffer   "
  "{ITA}"
    "Ritorna al baule    "
  "{SPA}"
    "Volver al baúl      "
  "{JAP}"
    "トランクに戻す           "
);

static const u8 sDeckMenuPickDefaultLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_FUSION_SUMMON,
};

#define DECK_MENU_PICK_SUBMENU_TEXT_CAPACITY 96

static const u8 *DeckMenu_GetPickLabelText(u8 label)
{
  switch (label) {
  case DECK_MENU_PICK_LABEL_FUSION_SUMMON:
    return sDeckMenuPickLabelFusionSummon;
  case DECK_MENU_PICK_LABEL_SELECT_CARD:
    return sDeckMenuPickLabelSelectCard;
  case DECK_MENU_PICK_LABEL_RETURN_TO_TRUNK:
    return sDeckMenuPickLabelReturnToTrunk;
  case DECK_MENU_PICK_LABEL_DETAILS:
  default:
    return sDeckMenuPickLabelDetails;
  }
}

static const u8 *DeckMenu_GetPickBlankLabelText(u8 row)
{
  if (row == 0)
    return sDeckMenuPickLabelBlankShort;

  return sDeckMenuPickLabelBlankLong;
}

static void DeckMenu_AppendPickLabelText(u8 *dest, u8 *offset, const u8 *labelText)
{
  const u8 *text = GetCurrentLanguageString(labelText);

  while (*text != 0 && *text != '$' &&
         *offset < DECK_MENU_PICK_SUBMENU_TEXT_CAPACITY - 1) {
    dest[*offset] = *text;
    (*offset)++;
    text++;
  }
}

static void DeckMenu_BuildPickSubmenuText(u8 *dest, const u8 *labels, u8 labelCount)
{
  u8 i;
  u8 offset = 0;

  for (i = 0; i < DECK_MENU_PICK_MAX_OPTIONS; i++) {
    if (i < labelCount)
      DeckMenu_AppendPickLabelText(dest, &offset, DeckMenu_GetPickLabelText(labels[i]));
    else
      DeckMenu_AppendPickLabelText(dest, &offset, DeckMenu_GetPickBlankLabelText(i));
  }
  dest[offset] = 0;
}

enum {
  FUSION_PICK_SUBMENU_BACK,
  FUSION_PICK_SUBMENU_DETAILS,
  FUSION_PICK_SUBMENU_SELECT,
  FUSION_PICK_SUBMENU_SUMMON,
  FUSION_PICK_SUBMENU_RETURN,
};

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

static void DeckMenuPickSubmenu_InitGfx(const u8 *labels, u8 labelCount) {
  unsigned char i;
  unsigned short r7;
  u8 submenuText[DECK_MENU_PICK_SUBMENU_TEXT_CAPACITY];

  DeckMenu_BuildPickSubmenuText(submenuText, labels, labelCount);
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
  CopyStringTilesToVRAMBuffer(&gBgVram.cbb1[32], submenuText, 0x900);
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
      TrunkMenu_IncrementTrunkQty(cardId);
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
  TrunkMenu_IncrementTrunkQty(cardId);
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

  if (gDeckMenu.cardCount >= limit || !TrunkMenu_GetTrunkQty(cardId))
    return;

  if (CardExceedsCurrentDuelistLevel(cardId))
    return;

  SetCardInfo(cardId);

  TrunkMenu_DecrementTrunkQty(cardId);
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

            gCardDetailNavActive = 1;
            gCardDetailNavIndex = gDeckMenu.currentPos;
            SetCardInfoWithWarning(&cardId);
            PlayMusic(SFX_SELECT);
            ShowCardDetailView();
            gCardDetailNavActive = 0;
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

static unsigned short DeckMenuProcessInput(void) {
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
    if (mask & gFilteredInput)
      ret = mask & gFilteredInput;
    mask <<= 1;
  }
  if (gFilteredInput & DPAD_UP && gPressedButtons & R_BUTTON)
    ret = NEW_DPAD_UP | R_BUTTON;
  if (gFilteredInput & DPAD_DOWN && gPressedButtons & R_BUTTON)
    ret = NEW_DPAD_DOWN | R_BUTTON;
  return ret;
}

static void DeckMenuInitGraphics(void) {
  sub_801EF30(0);
  sub_801EF30(2);
  sub_801F4A0(1);
  sub_801F5F0();
  sub_801F4A0(3);
}

static void DeckMenuRestoreAfterCardDetails(void) {
  sub_801EF30(0);
  sub_801EF30(2);
  sub_801F4A0(1);
  sub_801F5F0();
  sub_801F4A0(3);
  sub_801F5FC();
  sub_801EF30(3);
  sub_801F4A0(4);
  WaitForVBlank();
  LoadCharblock1();
}

static void DeckMenuShutdownGraphics(void) {
  RunPlayerDeckTask(8);
  sub_801EF30(1);
  RunTrunkTask(9);
  sub_0801F5EC();
  sub_801F4A0(2);
}

static void DeckMenuShowSelectedCardDetails(void) {
  u16 cardId = GetSelectedCardWithOffset(2);

  gCardDetailNavActive = 1;
  gCardDetailNavIndex = gDeckMenu.currentPos;
  SetCardInfoWithWarning(&cardId);
  PlayMusic(SFX_SELECT);
  ShowCardDetailView();
  gCardDetailNavActive = 0;
  DeckMenuRestoreAfterCardDetails();
}

static u8 DeckMenuPickSubmenu_Main(const u8 *labels, u8 labelCount) {
  unsigned keepProcessing = 1;
  unsigned char cursorState = 0;
  u8 result = FUSION_PICK_SUBMENU_BACK;

  PlayMusic(SFX_SELECT);
  DeckMenuPickSubmenu_InitGfx(labels, labelCount);
  sub_801D61C(cursorState);
  LoadCharblock1();
  SetVBlankCallback(DeckSubmenuVBlank);
  WaitForVBlank();
  while (keepProcessing) {
    switch (ProcessInputDeckSubmenus__Replacement()) {
      case REPEAT_DPAD_UP:
        cursorState = (cursorState + labelCount - 1) % labelCount;
        sub_801D61C(cursorState);
        PlayMusic(SFX_MOVE_CURSOR);
        SetVBlankCallback(LoadOam);
        WaitForVBlank();
        break;
      case REPEAT_DPAD_DOWN:
        cursorState = (cursorState + 1) % labelCount;
        sub_801D61C(cursorState);
        PlayMusic(SFX_MOVE_CURSOR);
        SetVBlankCallback(LoadOam);
        WaitForVBlank();
        break;
      case NEW_A_BUTTON:
        switch (labels[cursorState]) {
          case DECK_MENU_PICK_LABEL_DETAILS:
            DeckMenuShowSelectedCardDetails();
            result = FUSION_PICK_SUBMENU_DETAILS;
            keepProcessing = 0;
            break;
          case DECK_MENU_PICK_LABEL_SELECT_CARD:
            result = FUSION_PICK_SUBMENU_SELECT;
            keepProcessing = 0;
            PlayMusic(SFX_SELECT);
            break;
          case DECK_MENU_PICK_LABEL_FUSION_SUMMON:
            result = FUSION_PICK_SUBMENU_SUMMON;
            keepProcessing = 0;
            PlayMusic(SFX_SELECT);
            break;
          case DECK_MENU_PICK_LABEL_RETURN_TO_TRUNK:
            result = FUSION_PICK_SUBMENU_RETURN;
            keepProcessing = 0;
            PlayMusic(SFX_SELECT);
            break;
        }
        break;
      case NEW_B_BUTTON:
        result = FUSION_PICK_SUBMENU_BACK;
        keepProcessing = 0;
        PlayMusic(SFX_CANCEL);
        break;
      default:
        WaitForVBlank();
        break;
    }
  }
  sub_801D678();
  return result;
}

void DeckMenu_BeginDuelTrunkView(void)
{
  ClearGraphicsBuffers();
  LoadOam();
  LoadPalettes();
  DisableDisplay();
}

void DeckMenu_EndDuelTrunkView(void)
{
  DisableDisplay();
  UpdateAllDuelGfx();
}

void DeckMenuMainReadOnly(void) {
  unsigned keepProcessing = 1;

  if (IsPlayerDeckNonempty() != 1)
    return;

  DeckMenuSort();
  DeckMenuInitGraphics();
  while (keepProcessing) {
    switch (DeckMenuProcessInput()) {
      case DPAD_UP:
        RunPlayerDeckTask(3);
        sub_801EF30(3);
        sub_801F5FC();
        sub_801F4A0(4);
        break;
      case DPAD_UP | R_BUTTON:
        RunPlayerDeckTask(5);
        sub_801EF30(3);
        sub_801F5FC();
        sub_801F4A0(4);
        break;
      case DPAD_DOWN:
        RunPlayerDeckTask(2);
        sub_801EF30(3);
        sub_801F5FC();
        sub_801F4A0(4);
        break;
      case DPAD_DOWN | R_BUTTON:
        RunPlayerDeckTask(4);
        sub_801EF30(3);
        sub_801F5FC();
        sub_801F4A0(4);
        break;
      case L_BUTTON:
        RunPlayerDeckTask(6);
        sub_801EF30(4);
        sub_801F5FC();
        sub_801F4A0(4);
        break;
      case NEW_A_BUTTON:
        DeckMenuShowSelectedCardDetails();
        sub_801F4A0(7);
        break;
      case NEW_B_BUTTON:
        keepProcessing = 0;
        PlayMusic(SFX_CANCEL);
        break;
      case NEW_START_BUTTON:
        sub_801F120();
        sub_801EF30(7);
        sub_801F4A0(9);
        sub_801F644();
        break;
      case NEW_SELECT_BUTTON:
        ToggleDeckSortMode();
        sub_801EF30(6);
        PlayMusic(SFX_SELECT);
        sub_801F4A0(8);
        sub_801F630();
        break;
      case 0:
      default:
        sub_801EF30(5);
        sub_0801F62C();
        sub_801F4A0(5);
        break;
    }
    if (IsPlayerDeckNonempty() != 1)
      keepProcessing = 0;
  }
  DeckMenuShutdownGraphics();
}

u8 DeckMenuMainPickChosenLabel(const u8 *labels, u8 labelCount)
{
  unsigned keepProcessing = 1;
  u8 chosen = DECK_MENU_PICK_RESULT_CANCEL;
  const u8 *activeLabels = labels;
  u8 activeLabelCount = labelCount;

  if (activeLabels == NULL || activeLabelCount == 0) {
    activeLabels = sDeckMenuPickDefaultLabels;
    activeLabelCount = ARRAY_COUNT(sDeckMenuPickDefaultLabels);
  }
  if (activeLabelCount > DECK_MENU_PICK_MAX_OPTIONS)
    activeLabelCount = DECK_MENU_PICK_MAX_OPTIONS;

  if (IsPlayerDeckNonempty() != 1)
    return DECK_MENU_PICK_RESULT_CANCEL;

  DeckMenuSort();
  DeckMenuInitGraphics();
  while (keepProcessing) {
    switch (DeckMenuProcessInput()) {
      case DPAD_UP:
        RunPlayerDeckTask(3);
        sub_801EF30(3);
        sub_801F5FC();
        sub_801F4A0(4);
        break;
      case DPAD_UP | R_BUTTON:
        RunPlayerDeckTask(5);
        sub_801EF30(3);
        sub_801F5FC();
        sub_801F4A0(4);
        break;
      case DPAD_DOWN:
        RunPlayerDeckTask(2);
        sub_801EF30(3);
        sub_801F5FC();
        sub_801F4A0(4);
        break;
      case DPAD_DOWN | R_BUTTON:
        RunPlayerDeckTask(4);
        sub_801EF30(3);
        sub_801F5FC();
        sub_801F4A0(4);
        break;
      case L_BUTTON:
        RunPlayerDeckTask(6);
        sub_801EF30(4);
        sub_801F5FC();
        sub_801F4A0(4);
        break;
      case NEW_A_BUTTON:
        switch (DeckMenuPickSubmenu_Main(activeLabels, activeLabelCount)) {
          case FUSION_PICK_SUBMENU_SELECT:
            chosen = DECK_MENU_PICK_LABEL_SELECT_CARD;
            keepProcessing = 0;
            break;
          case FUSION_PICK_SUBMENU_SUMMON:
            chosen = DECK_MENU_PICK_LABEL_FUSION_SUMMON;
            keepProcessing = 0;
            break;
          case FUSION_PICK_SUBMENU_BACK:
            /* ponytail: submenu B cancels the whole pick (not just the submenu). */
            chosen = DECK_MENU_PICK_RESULT_CANCEL;
            keepProcessing = 0;
            break;
          case FUSION_PICK_SUBMENU_RETURN:
            chosen = DECK_MENU_PICK_LABEL_RETURN_TO_TRUNK;
            keepProcessing = 0;
            break;
          case FUSION_PICK_SUBMENU_DETAILS:
          default:
            sub_801F4A0(7);
            break;
        }
        break;
      case NEW_B_BUTTON:
        chosen = DECK_MENU_PICK_RESULT_CANCEL;
        keepProcessing = 0;
        PlayMusic(SFX_CANCEL);
        break;
      case NEW_START_BUTTON:
        sub_801F120();
        sub_801EF30(7);
        sub_801F4A0(9);
        sub_801F644();
        break;
      case NEW_SELECT_BUTTON:
        ToggleDeckSortMode();
        sub_801EF30(6);
        PlayMusic(SFX_SELECT);
        sub_801F4A0(8);
        sub_801F630();
        break;
      case 0:
      default:
        sub_801EF30(5);
        sub_0801F62C();
        sub_801F4A0(5);
        break;
    }
    if (IsPlayerDeckNonempty() != 1)
      keepProcessing = 0;
  }
  DeckMenuShutdownGraphics();
  return chosen;
}

bool8 DeckMenuMainPickConfirmWithLabels(const u8 *labels, u8 labelCount)
{
  u8 chosen = DeckMenuMainPickChosenLabel(labels, labelCount);

  return chosen == DECK_MENU_PICK_LABEL_SELECT_CARD
      || chosen == DECK_MENU_PICK_LABEL_FUSION_SUMMON;
}

bool8 DeckMenuMainPickConfirm(void)
{
  return DeckMenuMainPickConfirmWithLabels(
      sDeckMenuPickDefaultLabels, ARRAY_COUNT(sDeckMenuPickDefaultLabels));
}
