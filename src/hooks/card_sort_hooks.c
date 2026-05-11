// #include "global.h"
// #include "configs/runtime.h"

// struct SortableEntry {
//   u16 cardId;
//   u64 sortKey;
// };

// extern struct SortableEntry *gSortableEntries;

// void SortCardsAccordingToContext(void);
// void sub_8034DF8(void);
// void SortCardsDescending(void);

// void sub_8034AB8(void);
// void sub_8034AF0(void);
// void sub_8034B44(void);
// void sub_8034BBC(void);
// void sub_8034C00(void);
// void sub_8034C44(void);
// void sub_8034C88(void);
// void sub_8033C28(void);
// void sub_8033FF0(void);
// void sub_8034078(void);
// void sub_8034120(void);
// void sub_80341F4(void);
// void sub_80329C8(void);
// void sub_8032BD8(void);
// void sub_8032E98(void);
// void sub_8033210(void);
// void sub_8033588(void);
// void sub_80338C4(void);
// void sub_8033CB4(void);
// void sub_803427C(void);
// void sub_8032A50(void);
// void sub_8032C88(void);
// void sub_8032F50(void);
// void sub_80332C8(void);
// void sub_8033634(void);
// void sub_8033978(void);
// void sub_8033D60(void);
// void sub_8034324(void);
// void sub_8032AD0(void);
// void sub_8032D38(void);
// void sub_8033008(void);
// void sub_8033380(void);
// void sub_80336E0(void);
// void sub_8033A2C(void);
// void sub_8033E0C(void);
// void sub_80343CC(void);
// void sub_8034CCC(void);
// void sub_8034D18(void);
// void sub_80330C0(void);
// void sub_8033438(void);
// void sub_803378C(void);
// void sub_8033AE0(void);
// void sub_80345A4(void);
// void sub_8033EB8(void);
// void sub_8034474(void);
// void sub_8032B50(void);
// void sub_8032DE8(void);
// void sub_8033158(void);
// void sub_80334D0(void);
// void sub_8033818(void);
// void sub_8033B74(void);
// void sub_803462C(void);
// void sub_8033F44(void);
// void sub_80344FC(void);
// void sub_80346B4(void);
// void sub_8034778(void);
// void sub_803480C(void);
// void sub_80348D0(void);

// extern u8 gCardTypes[];
// extern u8 gCardAttributes[];
// extern u8 gCardLevels[];
// extern u8 gCardMonsterEffects[];
// extern u8 gUnk8094CC3[];
// extern u32 gCardCosts[];

// typedef void (*CardSortHelper)(void);

// enum DynamicSortKind {
//   DYNAMIC_SORT_NONE,
//   DYNAMIC_SORT_NUMBER,
//   DYNAMIC_SORT_NAME,
//   DYNAMIC_SORT_ATTACK,
//   DYNAMIC_SORT_DEFENSE,
//   DYNAMIC_SORT_TYPE,
//   DYNAMIC_SORT_ATTRIBUTE,
//   DYNAMIC_SORT_QTY,
//   DYNAMIC_SORT_COST,
//   DYNAMIC_SORT_STARS,
//   DYNAMIC_SORT_EFFECT,
// };

// static const CardSortHelper sVanillaSortHelpers[] APPEND_RODATA = {
//   sub_8034AB8, sub_8034AF0, sub_8034B44, sub_8034BBC, sub_8034C00, sub_8034C44, sub_8034C88, sub_8033C28,
//   sub_8033FF0, sub_8034078, sub_8034120, sub_80341F4, sub_80329C8, sub_8032BD8, sub_8032E98, sub_8033210,
//   sub_8033588, sub_80338C4, sub_8033CB4, sub_803427C, sub_8032A50, sub_8032C88, sub_8032F50, sub_80332C8,
//   sub_8033634, sub_8033978, sub_8033D60, sub_8034324, sub_8032AD0, sub_8032D38, sub_8033008, sub_8033380,
//   sub_80336E0, sub_8033A2C, sub_8033E0C, sub_80343CC, sub_8034CCC, sub_8034D18, sub_80330C0, sub_8033438,
//   sub_803378C, sub_8033AE0, sub_80345A4, sub_8033EB8, sub_8034474, sub_8032B50, sub_8032DE8, sub_8033158,
//   sub_80334D0, sub_8033818, sub_8033B74, sub_803462C, sub_8033F44, sub_80344FC, sub_80346B4, sub_8034778,
//   sub_803480C, sub_80348D0
// };

// static void CopySortedCardsBack(void) {
//   u16 i;

//   for (i = 0; i < gCardSortContext.cardCount; i++)
//     gCardSortContext.cards[i] = gSortableEntries[i].cardId;
// }

// static u8 *GetOwnedQtyForDynamicSort(u8 sortMode) {
//   switch (sortMode) {
//     case 20 ... 27:
//     case 57:
//       return gShopTempCardQty;
//     case 28 ... 35:
//     case 56:
//       return gPlayerTempCardQty;
//     case 45 ... 54:
//       return gTotalCardQty;
//   }

//   return NULL;
// }

// static u8 GetDynamicSortKind(u8 sortMode) {
//   switch (sortMode) {
//     case 20:
//     case 28:
//     case 45:
//       return DYNAMIC_SORT_NUMBER;
//     case 21:
//     case 29:
//     case 46:
//       return DYNAMIC_SORT_NAME;
//     case 22:
//     case 30:
//     case 47:
//       return DYNAMIC_SORT_ATTACK;
//     case 23:
//     case 31:
//     case 48:
//       return DYNAMIC_SORT_DEFENSE;
//     case 24:
//     case 32:
//     case 49:
//       return DYNAMIC_SORT_TYPE;
//     case 25:
//     case 33:
//     case 50:
//       return DYNAMIC_SORT_ATTRIBUTE;
//     case 9:
//     case 10:
//     case 51:
//       return DYNAMIC_SORT_QTY;
//     case 26:
//     case 34:
//     case 52:
//       return DYNAMIC_SORT_COST;
//     case 27:
//     case 35:
//     case 53:
//       return DYNAMIC_SORT_STARS;
//     case 54:
//     case 56:
//     case 57:
//       return DYNAMIC_SORT_EFFECT;
//   }

//   return DYNAMIC_SORT_NONE;
// }

// static u32 GetDynamicPrimaryValue(u8 sortKind, u16 cardId) {
//   switch (sortKind) {
//     case DYNAMIC_SORT_NUMBER:
//     case DYNAMIC_SORT_EFFECT:
//       return 800 - cardId;
//     case DYNAMIC_SORT_NAME:
//       return 800 - g80D0444[gLanguage][cardId];
//     case DYNAMIC_SORT_ATTACK:
//       return (gCardAtks[cardId] + 1) * 800 + 800;
//     case DYNAMIC_SORT_DEFENSE:
//       return (gCardDefs[cardId] + 1) * 800 + 800;
//     case DYNAMIC_SORT_TYPE:
//       return (23 - gCardTypes[cardId]) * 800 + 800;
//     case DYNAMIC_SORT_ATTRIBUTE:
//       return ((256 - gCardAttributes[cardId]) & 0xFF) * 800 + 800;
//     case DYNAMIC_SORT_QTY:
//       return 0;
//     case DYNAMIC_SORT_COST:
//       return gCardCosts[cardId] * 800 + 800;
//     case DYNAMIC_SORT_STARS:
//       return gCardLevels[cardId] * 800 + 800;
//   }

//   return 0;
// }

// static u64 GetDynamicSortKey(u8 sortKind, u16 cardId, u8 *ownedQty) {
//   u64 sortKey;

//   switch (sortKind) {
//     case DYNAMIC_SORT_QTY:
//       sortKey = (u64)ownedQty[cardId] * 800 + 800 - cardId;
//       break;
//     case DYNAMIC_SORT_EFFECT:
//       sortKey = 800 - cardId;
//       if (gCardMonsterEffects[cardId] || gUnk8094CC3[cardId])
//         sortKey += 0x320;
//       if (ownedQty[cardId])
//         sortKey += 0x640;
//       break;
//     default:
//       sortKey = GetDynamicPrimaryValue(sortKind, cardId) - cardId;
//       if (ownedQty[cardId])
//         sortKey |= 0x1000000000000000;
//       break;
//   }

//   return sortKey;
// }

// static void BuildDynamicShopOrTrunkSort(void) {
//   u16 i;
//   u8 sortKind = GetDynamicSortKind(gCardSortContext.sortMode);
//   u8 *ownedQty = GetOwnedQtyForDynamicSort(gCardSortContext.sortMode);

//   for (i = 0; i < gCardSortContext.cardCount; i++) {
//     u16 cardId = gCardSortContext.cards[i];

//     gSortableEntries[i].cardId = cardId;
//     gSortableEntries[i].sortKey = GetDynamicSortKey(sortKind, cardId, ownedQty);
//   }
// }

// LYN_REPLACE_CHECK(SortCardsAccordingToContext);
// void SortCardsAccordingToContext__Replacement(void) {
//   u8 sortMode = gCardSortContext.sortMode;

//   if (sortMode > 57)
//     return;

//   sub_8034DF8();

//   if (gRuntimeConfig.dynamic_card_shop_and_trunk_sorting == TRUE
//       && GetDynamicSortKind(sortMode) != DYNAMIC_SORT_NONE) {
//     BuildDynamicShopOrTrunkSort();
//   }
//   else {
//     sVanillaSortHelpers[sortMode]();
//   }

//   SortCardsDescending();
//   CopySortedCardsBack();
// }
