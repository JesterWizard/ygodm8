/* eslint-disable */
#include "global.h"
#include "configs/runtime.h"

struct SortableEntry {
  u16 cardId;
  u64 sortKey;
};

/* Vanilla ROM pointer at 0x8E0CC20 still targets the fixed 800-entry buffer at
 * 0x2018800. C code uses gExpandedSortableEntries via gSortableEntries.
 * SortCardsAccordingToContext__Replacement bridges the two on the vanilla path. */
extern struct SortableEntry gExpandedSortableEntries[];
struct SortableEntry *gSortableEntries APPEND_DATA = gExpandedSortableEntries;

extern struct CardSortContext gCardSortContext;

void SortCardsAccordingToContext(void);
void sub_8034DF8(void);
void SortCardsDescending(void);

/* Vanilla unreplacable ASM helpers write 12-byte entries at 0x2018800 (ROM word 0x8E0CC20). */
/* Sentinel: not a valid card id (NUM_TOTAL_CARDS is well below this). */
#define SORT_BUFFER_SENTINEL 0xFFFF

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
extern unsigned char gTotalCardQty[];
extern unsigned char gLanguage;
extern unsigned short g80D0444[][801];
extern const CardData gCardData_NEW[];
extern unsigned short sRandomizedCardCosts[];
extern u8 gUnk8094C37[];
extern u8 gUnk8094CC3[];

#include "generated/card_name_sort_generated.inc"

static u8 GetSortOwnedQty(u16 cardId, u8 *ownedQtyTable) {
  if (ownedQtyTable == gTotalCardQty)
    return GetTotalCardQtyForCard(cardId);
  if (ownedQtyTable == gShopTempCardQty)
    return GetShopTempCardQty(cardId);
  if (ownedQtyTable == gPlayerTempCardQty)
    return GetPlayerTempCardQty(cardId);
  return ownedQtyTable[cardId];
}

static u8 *GetOwnedQtyForDynamicSort(u8 sortMode) {
  if ((sortMode >= 20 && sortMode <= 27) || sortMode == 9 || sortMode == 57)
    return gShopTempCardQty;
  if ((sortMode >= 28 && sortMode <= 35) || sortMode == 10 || sortMode == 56)
    return gPlayerTempCardQty;
  if (sortMode >= 45 && sortMode <= 54)
    return gTotalCardQty;
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

static u16 GetCardIdTieValue(u16 cardId) {
  return NUM_TOTAL_CARDS - cardId;
}

static u16 GetSortCardCost(u16 cardId) {
  if (gRuntimeConfig.randomize_card_costs_at_start == TRUE)
    return sRandomizedCardCosts[cardId];

  return (u16)gCardData_NEW[cardId].cost;
}

static u32 GetSortCardTypeValue(u16 cardId) {
  u8 type = gCardData_NEW[cardId].type;

  if (type > TYPE_RITUAL)
    return 0;
  return TYPE_RITUAL - type;
}

static u32 GetSortCardAttributeValue(u16 cardId) {
  u8 attribute = gCardData_NEW[cardId].attribute;

  if (gRuntimeConfig.disable_element_system == TRUE)
    attribute = ATTRIBUTE_NONE;

  return (256 - attribute) & 0xFF;
}

static u8 CardHasSortableEffect(u16 cardId) {
  const CardData *card = &gCardData_NEW[cardId];

  if (card->monsterEffect || card->trapEffect || gUnk8094C37[card->spellEffect])
    return TRUE;

  if (cardId < CUSTOM_CARD_START && gUnk8094CC3[cardId])
    return TRUE;

  return FALSE;
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

static int CompareCardNameSortOrder(u16 leftCardId, u16 rightCardId) {
  if (leftCardId < NUM_CARDS && rightCardId < NUM_CARDS) {
    u16 leftRank = g80D0444[gLanguage][leftCardId];
    u16 rightRank = g80D0444[gLanguage][rightCardId];

    if (leftRank != rightRank)
      return (int)leftRank - (int)rightRank;
    return (int)leftCardId - (int)rightCardId;
  }

  if (leftCardId >= CUSTOM_CARD_START && rightCardId >= CUSTOM_CARD_START) {
    u16 leftRank = GetCustomCardNameSortOrder(leftCardId);
    u16 rightRank = GetCustomCardNameSortOrder(rightCardId);

    if (leftRank != rightRank)
      return (int)leftRank - (int)rightRank;
    return (int)leftCardId - (int)rightCardId;
  }

  return CompareSortCardNames(leftCardId, rightCardId);
}

static void SortSortableEntriesByName(void) {
  u16 gap;

  for (gap = gCardSortContext.cardCount / 2; gap > 0; gap /= 2) {
    u16 i;

    for (i = gap; i < gCardSortContext.cardCount; i++) {
      struct SortableEntry entry = gSortableEntries[i];
      u16 j = i;

      while (j >= gap && CompareCardNameSortOrder(gSortableEntries[j - gap].cardId, entry.cardId) > 0) {
        gSortableEntries[j] = gSortableEntries[j - gap];
        j -= gap;
      }

      gSortableEntries[j] = entry;
    }
  }
}

static u64 GetDynamicPrimarySortKey(u8 sortKind, u16 cardId) {
  u32 primaryValue;
  const CardData *card = &gCardData_NEW[cardId];

  switch (sortKind) {
    case DYNAMIC_SORT_NUMBER:
      primaryValue = 0;
      break;
    case DYNAMIC_SORT_ATTACK:
      primaryValue = (card->atk + 1) & 0xFFFF;
      break;
    case DYNAMIC_SORT_DEFENSE:
      primaryValue = (card->def + 1) & 0xFFFF;
      break;
    case DYNAMIC_SORT_TYPE:
      primaryValue = GetSortCardTypeValue(cardId);
      break;
    case DYNAMIC_SORT_ATTRIBUTE:
      primaryValue = GetSortCardAttributeValue(cardId);
      break;
    case DYNAMIC_SORT_COST:
      primaryValue = GetSortCardCost(cardId);
      break;
    case DYNAMIC_SORT_STARS:
      primaryValue = card->level;
      break;
    case DYNAMIC_SORT_EFFECT:
      primaryValue = CardHasSortableEffect(cardId) ? 1 : 0;
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
    return (u64)GetSortOwnedQty(cardId, ownedQty) * SORT_TIE_SCALE + GetCardIdTieValue(cardId);

  if (sortKind == DYNAMIC_SORT_EFFECT) {
    sortKey = GetCardIdTieValue(cardId);
    if (CardHasSortableEffect(cardId))
      sortKey += SORT_TIE_SCALE;
    if (GetSortOwnedQty(cardId, ownedQty))
      sortKey += SORT_TIE_SCALE * 2;
    return sortKey;
  }

  sortKey = GetDynamicPrimarySortKey(sortKind, cardId);
  if (GetSortOwnedQty(cardId, ownedQty))
    sortKey |= SORT_OWNED_BONUS;

  return sortKey;
}

static void BuildDynamicNumberSortOwnedFirst(u8 *ownedQty) {
  u16 count = gCardSortContext.cardCount;
  u16 ownedWrite = 0;
  u16 unownedWrite = 0;
  u16 i;

  for (i = 0; i < count; i++) {
    u16 cardId = gCardSortContext.cards[i];

    if (GetSortOwnedQty(cardId, ownedQty))
      gSortableEntries[ownedWrite++].cardId = cardId;
  }

  for (i = 0; i < count; i++) {
    u16 cardId = gCardSortContext.cards[i];

    if (!GetSortOwnedQty(cardId, ownedQty))
      gSortableEntries[ownedWrite + unownedWrite++].cardId = cardId;
  }
}

static void BuildDynamicNameSort(u8 *ownedQty) {
  u16 i;
  u16 count = gCardSortContext.cardCount;

  for (i = 0; i < count; i++)
    gSortableEntries[i].cardId = gCardSortContext.cards[i];

  SortSortableEntriesByName();

  for (i = 0; i < count; i++) {
    u16 cardId = gSortableEntries[i].cardId;
    u64 sortKey = (u64)(count - i) * SORT_TIE_SCALE + GetCardIdTieValue(cardId);

    if (GetSortOwnedQty(cardId, ownedQty))
      sortKey |= SORT_OWNED_BONUS;

    gSortableEntries[i].sortKey = sortKey;
  }
}

static void BuildDynamicShopOrTrunkSort(void) {
  u16 i;
  u8 sortKind = GetDynamicSortKind(gCardSortContext.sortMode);
  u8 *ownedQty = GetOwnedQtyForDynamicSort(gCardSortContext.sortMode);

  if (sortKind == DYNAMIC_SORT_NAME) {
    BuildDynamicNameSort(ownedQty);
    return;
  }

  if (sortKind == DYNAMIC_SORT_NUMBER) {
    BuildDynamicNumberSortOwnedFirst(ownedQty);
    return;
  }

  for (i = 0; i < gCardSortContext.cardCount; i++) {
    u16 cardId = gCardSortContext.cards[i];

    gSortableEntries[i].cardId = cardId;
    gSortableEntries[i].sortKey = GetDynamicSortKey(sortKind, cardId, ownedQty);
  }
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

static void BridgeVanillaSortBufferIfNeeded(void) {
  u16 i;
  const u8 *src;

  /* LynJump-replaced helpers write gSortableEntries; unreplacable ASM still
   * writes 12-byte entries at 0x2018800. Sentinel detects which path ran. */
  if (gCardSortContext.cardCount == 0)
    return;
  if (gSortableEntries[0].cardId != SORT_BUFFER_SENTINEL)
    return;

  /* ponytail: vanilla stride is fixed 12; don't use C sizeof indexing on 0x2018800
   * in case agbcc ever pads SortableEntry differently. Upgrade: patch ROM
   * 0x8E0CC20 → gExpandedSortableEntries and drop this bridge. */
  src = (const u8 *)0x02018800;
  for (i = 0; i < gCardSortContext.cardCount; i++) {
    const u8 *entry = src + i * 12;
    u32 lo = *(const u32 *)(entry + 4);
    u32 hi = *(const u32 *)(entry + 8);

    gSortableEntries[i].cardId = *(const u16 *)entry;
    gSortableEntries[i].sortKey = ((u64)hi << 32) | lo;
  }
}

LYN_REPLACE_CHECK(SortCardsAccordingToContext);
void SortCardsAccordingToContext__Replacement(void) {
  u8 sortMode = gCardSortContext.sortMode;

  if (sortMode > 57)
    return;

  sub_8034DF8();

  if (gRuntimeConfig.dynamic_card_shop_and_trunk_sorting == TRUE && GetDynamicSortKind(sortMode) != DYNAMIC_SORT_NONE) {
    u8 sortKind = GetDynamicSortKind(sortMode);

    BuildDynamicShopOrTrunkSort();
    if (sortKind != DYNAMIC_SORT_NUMBER)
      SortDynamicEntriesDescending();
    CopySortedCardsBack();
  }
  else {
    if (gCardSortContext.cardCount > 0)
      gSortableEntries[0].cardId = SORT_BUFFER_SENTINEL;

    sVanillaSortHelpers[sortMode]();
    BridgeVanillaSortBufferIfNeeded();
    SortCardsDescending();
    CopySortedCardsBack();
  }
}

LYN_REPLACE_CHECK(sub_8032B50);
void sub_8032B50__Replacement(void) {
  unsigned i;

  for (i = 0; i < gCardSortContext.cardCount; i++) {
    gSortableEntries[i].cardId = gCardSortContext.cards[i];
    gSortableEntries[i].sortKey = 800 - gCardSortContext.cards[i];
    if (GetTotalCardQtyForCard(gCardSortContext.cards[i]))
      gSortableEntries[i].sortKey += 800;
  }
}

LYN_REPLACE_CHECK(sub_8032DE8);
void sub_8032DE8__Replacement(void) {
  unsigned i;

  for (i = 0; i < gCardSortContext.cardCount; i++) {
    gSortableEntries[i].cardId = gCardSortContext.cards[i];
    gSortableEntries[i].sortKey = 800 - g80D0444[gLanguage][gCardSortContext.cards[i]];
    if (GetTotalCardQtyForCard(gCardSortContext.cards[i]))
      gSortableEntries[i].sortKey += 800;
  }
}

LYN_REPLACE_CHECK(sub_8032A50);
void sub_8032A50__Replacement(void) {
  unsigned i;

  for (i = 0; i < gCardSortContext.cardCount; i++) {
    gSortableEntries[i].cardId = gCardSortContext.cards[i];
    gSortableEntries[i].sortKey = 800 - gCardSortContext.cards[i];
    if (GetShopTempCardQty(gCardSortContext.cards[i]))
      gSortableEntries[i].sortKey |= 0x1000000000000000;
  }
}

LYN_REPLACE_CHECK(sub_8032AD0);
void sub_8032AD0__Replacement(void) {
  unsigned i;

  for (i = 0; i < gCardSortContext.cardCount; i++) {
    gSortableEntries[i].cardId = gCardSortContext.cards[i];
    gSortableEntries[i].sortKey = 800 - gCardSortContext.cards[i];
    if (GetPlayerTempCardQty(gCardSortContext.cards[i]))
      gSortableEntries[i].sortKey |= 0x1000000000000000;
  }
}

LYN_REPLACE_CHECK(sub_8032C88);
void sub_8032C88__Replacement(void) {
  unsigned i;

  for (i = 0; i < gCardSortContext.cardCount; i++) {
    u16 cardId = gCardSortContext.cards[i];

    gSortableEntries[i].cardId = cardId;
    if (cardId < NUM_CARDS)
      gSortableEntries[i].sortKey = 800 - g80D0444[gLanguage][cardId];
    else
      gSortableEntries[i].sortKey = 800 - cardId;
    if (GetShopTempCardQty(cardId))
      gSortableEntries[i].sortKey += 800;
  }
}

LYN_REPLACE_CHECK(sub_8032D38);
void sub_8032D38__Replacement(void) {
  unsigned i;

  for (i = 0; i < gCardSortContext.cardCount; i++) {
    u16 cardId = gCardSortContext.cards[i];

    gSortableEntries[i].cardId = cardId;
    if (cardId < NUM_CARDS)
      gSortableEntries[i].sortKey = 800 - g80D0444[gLanguage][cardId];
    else
      gSortableEntries[i].sortKey = 800 - cardId;
    if (GetPlayerTempCardQty(cardId))
      gSortableEntries[i].sortKey += 800;
  }
}
