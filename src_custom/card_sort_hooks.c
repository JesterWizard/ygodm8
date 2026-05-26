/* eslint-disable */
#include "global.h"
#include "configs/runtime.h"

struct SortableEntry {
  u16 cardId;
  u64 sortKey;
};

extern struct SortableEntry *gSortableEntries;
extern struct CardSortContext gCardSortContext;

void SortCardsAccordingToContext(void);
void sub_8034DF8(void);
void SortCardsDescending(void);

void sub_8034AB8(void);
void sub_8034AF0(void);
void sub_8034B44(void);
void sub_8034BBC(void);
void sub_8034C00(void);
void sub_8034C44(void);
void sub_8034C88(void);
void sub_8033C28(void);
void sub_8033FF0(void);
void sub_8034078(void);
void sub_8034120(void);
void sub_80341F4(void);
void sub_80329C8(void);
void sub_8032BD8(void);
void sub_8032E98(void);
void sub_8033210(void);
void sub_8033588(void);
void sub_80338C4(void);
void sub_8033CB4(void);
void sub_803427C(void);
void sub_8032A50(void);
void sub_8032C88(void);
void sub_8032F50(void);
void sub_80332C8(void);
void sub_8033634(void);
void sub_8033978(void);
void sub_8033D60(void);
void sub_8034324(void);
void sub_8032AD0(void);
void sub_8032D38(void);
void sub_8033008(void);
void sub_8033380(void);
void sub_80336E0(void);
void sub_8033A2C(void);
void sub_8033E0C(void);
void sub_80343CC(void);
void sub_8034CCC(void);
void sub_8034D18(void);
void sub_80330C0(void);
void sub_8033438(void);
void sub_803378C(void);
void sub_8033AE0(void);
void sub_80345A4(void);
void sub_8033EB8(void);
void sub_8034474(void);
void sub_8032B50(void);
void sub_8032DE8(void);
void sub_8033158(void);
void sub_80334D0(void);
void sub_8033818(void);
void sub_8033B74(void);
void sub_803462C(void);
void sub_8033F44(void);
void sub_80344FC(void);
void sub_80346B4(void);
void sub_8034778(void);
void sub_803480C(void);
void sub_80348D0(void);

typedef void (*CardSortHelper)(void);

enum DynamicSortKind {
  DYNAMIC_SORT_NONE,
  DYNAMIC_SORT_NUMBER,
  DYNAMIC_SORT_NAME,
  DYNAMIC_SORT_ATTACK,
  DYNAMIC_SORT_DEFENSE,
  DYNAMIC_SORT_TYPE,
  DYNAMIC_SORT_ATTRIBUTE,
  DYNAMIC_SORT_QTY,
  DYNAMIC_SORT_COST,
  DYNAMIC_SORT_STARS,
  DYNAMIC_SORT_EFFECT,
};

#define SORT_TIE_SCALE NUM_TOTAL_CARDS
#define SORT_OWNED_BONUS 0x1000000000000000

extern u8 *gCardNames[];

static const CardSortHelper sVanillaSortHelpers[] APPEND_RODATA = {
  sub_8034AB8, sub_8034AF0, sub_8034B44, sub_8034BBC, sub_8034C00, sub_8034C44, sub_8034C88, sub_8033C28,
  sub_8033FF0, sub_8034078, sub_8034120, sub_80341F4, sub_80329C8, sub_8032BD8, sub_8032E98, sub_8033210,
  sub_8033588, sub_80338C4, sub_8033CB4, sub_803427C, sub_8032A50, sub_8032C88, sub_8032F50, sub_80332C8,
  sub_8033634, sub_8033978, sub_8033D60, sub_8034324, sub_8032AD0, sub_8032D38, sub_8033008, sub_8033380,
  sub_80336E0, sub_8033A2C, sub_8033E0C, sub_80343CC, sub_8034CCC, sub_8034D18, sub_80330C0, sub_8033438,
  sub_803378C, sub_8033AE0, sub_80345A4, sub_8033EB8, sub_8034474, sub_8032B50, sub_8032DE8, sub_8033158,
  sub_80334D0, sub_8033818, sub_8033B74, sub_803462C, sub_8033F44, sub_80344FC, sub_80346B4, sub_8034778,
  sub_803480C, sub_80348D0
};

static void CopySortedCardsBack(void) {
  u16 i;

  for (i = 0; i < gCardSortContext.cardCount; i++)
    gCardSortContext.cards[i] = gSortableEntries[i].cardId;
}

static void SortDynamicEntriesDescending(void) {
  u16 gap;

  for (gap = gCardSortContext.cardCount / 2; gap > 0; gap /= 2) {
    u16 i;

    for (i = gap; i < gCardSortContext.cardCount; i++) {
      struct SortableEntry entry = gSortableEntries[i];
      u16 j = i;

      while (j >= gap && gSortableEntries[j - gap].sortKey < entry.sortKey) {
        gSortableEntries[j] = gSortableEntries[j - gap];
        j -= gap;
      }

      gSortableEntries[j] = entry;
    }
  }
}

static u16 GetCardIdTieValue(u16 cardId) {
  return NUM_TOTAL_CARDS - cardId;
}

static u8 *GetOwnedQtyForDynamicSort(u8 sortMode) {
  if ((sortMode >= 20 && sortMode <= 27) || sortMode == 9 || sortMode == 57)
    return gShopTempCardQty;
  if ((sortMode >= 28 && sortMode <= 35) || sortMode == 10 || sortMode == 56)
    return gPlayerTempCardQty;
  if (sortMode >= 45 && sortMode <= 54)
    return gTrunkCardQty;
  return 0;
}

static u8 GetDynamicSortKind(u8 sortMode) {
  switch (sortMode) {
    case 20:
    case 28:
    case 45:
      return DYNAMIC_SORT_NUMBER;
    case 21:
    case 29:
    case 46:
      return DYNAMIC_SORT_NAME;
    case 22:
    case 30:
    case 47:
      return DYNAMIC_SORT_ATTACK;
    case 23:
    case 31:
    case 48:
      return DYNAMIC_SORT_DEFENSE;
    case 24:
    case 32:
    case 49:
      return DYNAMIC_SORT_TYPE;
    case 25:
    case 33:
    case 50:
      return DYNAMIC_SORT_ATTRIBUTE;
    case 9:
    case 10:
    case 51:
      return DYNAMIC_SORT_QTY;
    case 26:
    case 34:
    case 52:
      return DYNAMIC_SORT_COST;
    case 27:
    case 35:
    case 53:
      return DYNAMIC_SORT_STARS;
    case 54:
    case 56:
    case 57:
      return DYNAMIC_SORT_EFFECT;
  }

  return DYNAMIC_SORT_NONE;
}

static u8 *GetSortCardName(u16 cardId) {
  if (cardId < NUM_CARDS)
    return gCardNames[cardId];

  SetCardInfo(cardId);
  return gCardInfo.name;
}

static int CompareSortCardNames(u16 leftCardId, u16 rightCardId) {
  u8 *leftName = GetSortCardName(leftCardId);
  u8 *rightName = GetSortCardName(rightCardId);

  while (*leftName && *rightName && *leftName == *rightName) {
    leftName++;
    rightName++;
  }

  if (*leftName < *rightName)
    return -1;
  if (*leftName > *rightName)
    return 1;
  if (leftCardId < rightCardId)
    return -1;
  if (leftCardId > rightCardId)
    return 1;
  return 0;
}

static u16 GetDynamicNameRank(u16 cardId) {
  u16 i;
  u16 rank = 0;

  if (cardId < NUM_CARDS)
    rank = g80D0444[gLanguage][cardId] - 1;

  for (i = 0; i < gCardSortContext.cardCount; i++) {
    u16 otherCardId = gCardSortContext.cards[i];

    if (otherCardId == cardId)
      continue;

    if (cardId < NUM_CARDS && otherCardId < NUM_CARDS)
      continue;

    if (CompareSortCardNames(otherCardId, cardId) < 0)
      rank++;
  }

  return rank;
}

static u64 GetDynamicNameSortKey(u16 cardId) {
  u16 rank = GetDynamicNameRank(cardId);

  return (u64)(gCardSortContext.cardCount - rank) * SORT_TIE_SCALE + GetCardIdTieValue(cardId);
}

static u32 GetCardTypeSortValue(void) {
  if (gCardInfo.type > TYPE_RITUAL)
    return 0;
  return TYPE_RITUAL - gCardInfo.type;
}

static u32 GetCardAttributeSortValue(void) {
  return (256 - gCardInfo.attribute) & 0xFF;
}

static u8 CardHasSortableEffect(void) {
  if (gCardInfo.monsterEffect || gCardInfo.trapEffect || gCardInfo.ritualEffect || gCardInfo.unk1E)
    return TRUE;
  return FALSE;
}

static u64 GetDynamicPrimarySortKey(u8 sortKind, u16 cardId) {
  u32 primaryValue;

  if (sortKind == DYNAMIC_SORT_NAME)
    return GetDynamicNameSortKey(cardId);

  SetCardInfo(cardId);

  switch (sortKind) {
    case DYNAMIC_SORT_NUMBER:
      primaryValue = 0;
      break;
    case DYNAMIC_SORT_ATTACK:
      primaryValue = (gCardInfo.atk + 1) & 0xFFFF;
      break;
    case DYNAMIC_SORT_DEFENSE:
      primaryValue = (gCardInfo.def + 1) & 0xFFFF;
      break;
    case DYNAMIC_SORT_TYPE:
      primaryValue = GetCardTypeSortValue();
      break;
    case DYNAMIC_SORT_ATTRIBUTE:
      primaryValue = GetCardAttributeSortValue();
      break;
    case DYNAMIC_SORT_COST:
      primaryValue = gCardInfo.cost;
      break;
    case DYNAMIC_SORT_STARS:
      primaryValue = gCardInfo.level;
      break;
    case DYNAMIC_SORT_EFFECT:
      primaryValue = CardHasSortableEffect() ? 1 : 0;
      break;
    default:
      primaryValue = 0;
      break;
  }

  return (u64)(primaryValue + 1) * SORT_TIE_SCALE + GetCardIdTieValue(cardId);
}

static u64 GetDynamicSortKey(u8 sortKind, u16 cardId, u8 *ownedQty) {
  u64 sortKey;

  if (sortKind == DYNAMIC_SORT_QTY)
    return (u64)ownedQty[cardId] * SORT_TIE_SCALE + GetCardIdTieValue(cardId);

  if (sortKind == DYNAMIC_SORT_EFFECT) {
    sortKey = GetCardIdTieValue(cardId);
    SetCardInfo(cardId);
    if (CardHasSortableEffect())
      sortKey += SORT_TIE_SCALE;
    if (ownedQty[cardId])
      sortKey += SORT_TIE_SCALE * 2;
    return sortKey;
  }

  sortKey = GetDynamicPrimarySortKey(sortKind, cardId);
  if (ownedQty[cardId])
    sortKey |= SORT_OWNED_BONUS;

  return sortKey;
}

static void BuildDynamicShopOrTrunkSort(void) {
  u16 i;
  u8 sortKind = GetDynamicSortKind(gCardSortContext.sortMode);
  u8 *ownedQty = GetOwnedQtyForDynamicSort(gCardSortContext.sortMode);

  for (i = 0; i < gCardSortContext.cardCount; i++) {
    u16 cardId = gCardSortContext.cards[i];

    gSortableEntries[i].cardId = cardId;
    gSortableEntries[i].sortKey = GetDynamicSortKey(sortKind, cardId, ownedQty);
  }
}

LYN_REPLACE_CHECK(SortCardsAccordingToContext);
void SortCardsAccordingToContext__Replacement(void) {
  u8 sortMode = gCardSortContext.sortMode;

  if (sortMode > 57)
    return;

  sub_8034DF8();

  if (gRuntimeConfig.dynamic_card_shop_and_trunk_sorting == TRUE && GetDynamicSortKind(sortMode) != DYNAMIC_SORT_NONE) {
    BuildDynamicShopOrTrunkSort();
    SortDynamicEntriesDescending();
  }
  else {
    sVanillaSortHelpers[sortMode]();
    SortCardsDescending();
  }
  CopySortedCardsBack();
}
