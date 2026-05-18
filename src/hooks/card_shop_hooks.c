#include "global.h"
#include "configs/runtime.h"

struct CardShopState {
  unsigned short* unk0[5][7];
  unsigned short unk8C[5][7];
  unsigned short unkD2[806];
  s16 firstVisibleRow;
  s16 numRows;
  s8 cursorColumn;
  s8 cursorRow;
  u8 unk724;
  u8 currentSortMode;
  u8 selectedMenuOption;
};

extern struct CardShopState sCardShop;
extern u16 gNewButtons;
extern u64 gMoney;
extern u8 gStartingShopCards[];
extern u8 gShopCardQty[];

void InitNewGameShopCards(void);
void TrySellCard (void);
void sub_802CEE0 (int);
void sub_802D174 (void);
int sub_802DE84 (int);
void sub_802E270 (void);
void sub_802EA74 (void);
void sub_802FC88 (void);
void sub_802FD84 (u16);
void sub_802FE84 (int);
void sub_8030690 (void);
void sub_803096C (int);
void RemoveCardQtyFromPlayerInShop (u16, u8);
unsigned PlayerInShopHasAtLeastCardQty (u16, u8);
void AddCardQtyToShop (u16, u8);
void AddMoney (u64);
void ScalePriceToQty (void);

LYN_REPLACE_CHECK(InitNewGameShopCards);
void InitNewGameShopCards__Replacement(void) {
  unsigned short cardId;

  for (cardId = 0; cardId < NUM_CARDS; cardId++) {
    if (gRuntimeConfig.start_shop_with_one_copy_of_every_card == TRUE)
      gShopCardQty[cardId] = 1;
    else
      gShopCardQty[cardId] = gStartingShopCards[cardId];
  }
}

LYN_REPLACE_CHECK(TrySellCard);
void TrySellCard__Replacement(void) {
  u16 cardId;
  u64 money;

  cardId = *sCardShop.unk0[sCardShop.cursorRow][sCardShop.cursorColumn];
  if (PlayerInShopHasAtLeastCardQty(cardId, (gRuntimeConfig.allow_sell_one_copy_of_card == TRUE) ? 1 : 2) == 1) {
    money = gShopSelectedCard.sellPrice;
    RemoveCardQtyFromPlayerInShop(cardId, 1);
    AddMoney(money);
    AddCardQtyToShop(cardId, 1);
    PlayMusic(SFX_SELECT);
  }
  else {
    PlayMusic(0x39);
    sub_802E270();
    while (!(gNewButtons & (A_BUTTON | B_BUTTON)))
      WaitForVBlank();
    PlayMusic(SFX_CANCEL);
    sub_802FC88();
  }
  gShopSelectedCard.cardId = cardId;
  gShopSelectedCard.shopQty = gShopTempCardQty[cardId];
  ScalePriceToQty();
  sub_802D174();
  sub_802CEE0(sCardShop.cursorRow);
  sub_802FE84(sCardShop.cursorRow);
  sub_802EA74();
  sub_802FD84(*sCardShop.unk0[sCardShop.cursorRow][sCardShop.cursorColumn]);
  SetVBlankCallback(sub_8030690);
  WaitForVBlank();
  sub_803096C(sub_802DE84(sCardShop.cursorRow));
}
