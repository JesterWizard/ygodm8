#include "global.h"
#include "configs/runtime.h"
#include "duel.h"
#include "duel_main.h"
#include "duel_status.h"
#include "custom_decks/custom_decks.h"
#include "timed_duel.h"
#include "generated/duelist_rewards_generated.inc"
#include "generated/card_trunk_generated.inc"
#include "card_shop.h"
#include "text.h"

void HandleWin(void);
void HandleLoss(void);
void HandleOutcome(void);
void DeclareLoser(u8);
u8 sub_801F098(u16);
extern struct Duelist* gUnk8E00B30[];
extern u16 g80B9620[];
extern u16 g80B96AA[];

void IncreaseDeckCapacity(u32);
void AddCardDropsToShop(void);
void AddMoneyFromDuelVictory(void);
void DisplayMoneyRewardText(void);
void DisplayDuelShopDropText(void);
int GetCardsDrawn(u8 arg0);
int GetDeckCardQty(u16);
u16 RandRangeU16(u16, u16);
u16 sub_801FFE0(void);
u16 sub_8020050(void);
u8 sub_801F0F0(u16, u16*);
void sub_8041C94(u8 *, u16, u16, u16, u16);

extern u8 g201CB58;
extern u8 g201CB59;
extern u16 g201CB60[2][2240];
extern u16 gNewButtons;
extern u16 gPressedButtons;
extern u8 gInputRepeatTimer;
extern struct CardInfo gCardInfo;

extern unsigned char g80B96B8[];
extern unsigned char g80B96BC[];

void sub_800B618(void*);
void sub_800BCB0(void*);
void sub_801FA84(void);
void sub_801FADC(void);
void sub_801FB14(void);
void sub_801FB2C(void);
void sub_801FB38(void);
void ShowCardDetailView(void);
void SetVBlankCallback(void (*)(void));
void WaitForVBlank(void);
void LoadCharblock1(void);
u8 CardUsesExtendedBigCardPalette(u16 cardId);
void ApplyCardDetailPaletteExtension(void);
void SetCardInfo(u16 id);
u16 GetNthCardOnScreen(u8 n);
u16 GetTrunkCardCount(void);

/* Card detail navigation context — allocated in ram_map_ewram.s.
 * Set by callers before ShowCardDetailView for deck (active=1)
 * or auto-detected from gTrunkMenu.cursorState for trunk (active=2). */
extern u8 gCardDetailNavActive;
extern u8 gCardDetailNavIndex;

static void BuildDescriptionPageBuffer(const u8 *text, u8 page, u8 pageCount, u16 *dest) {
  u8 buffer[144];
  u8 i = 0;
  u8 j = 0;

  CpuFastFill16(0, dest, 2240 * sizeof(u16));

  while (*text != '^') {
    buffer[i] = *text;
    if (*text > 127)
      buffer[++i] = *++text;
    i++;
    text++;
    j++;
    if (j == 12) {
      buffer[i] = ' ';
      i++;
      if (page) {
        buffer[i] = g80B96B8[0];
        i++;
        buffer[i] = g80B96B8[1];
      } else {
        buffer[i] = ' ';
      }
      i++;
      j += 2;
    }
  }

  if (page >= pageCount - 1) {
    while (j < 70) {
      buffer[i] = ' ';
      i++;
      j++;
    }
  } else {
    while (j < 69) {
      buffer[i] = ' ';
      i++;
      j++;
    }
    buffer[i] = g80B96BC[0];
    i++;
    buffer[i] = g80B96BC[1];
    i++;
  }

  buffer[i] = 0;
  CopyStringTilesToVRAMBuffer(dest, buffer, 0x901);
}

static void CardDetailViewRenderPage(u16 *pageBuffer, const u8 *pageStarts[], u8 pageCount) {
  g201CB58 = 0;
  sub_801FB2C();
  sub_800B618(pageBuffer);
  ApplyCardDetailPaletteExtension();
  sub_801FA84();
  SetVBlankCallback(sub_801FADC);
  WaitForVBlank();
  sub_801FB38();
  SetVBlankCallback(sub_801FB14);
  WaitForVBlank();
}

static u8 CardDetailViewBuildDescription(u16 *pageBuffer, const u8 *pageStarts[9]) {
  u8 i;
  u8 page;
  u8 buffer[144];
  const u8 *text = gCardInfo.description + 2;

  CpuFastFill16(0, pageBuffer, 4480);
  text = GetCurrentLanguageString(text);
  if (*text == '^') {
    u8 pageCount;

    text++;
    switch (*text) {
      case '2': pageCount = 2; break;
      case '3': pageCount = 3; break;
      case '4': pageCount = 4; break;
      case '5': pageCount = 5; break;
      case '6': pageCount = 6; break;
      case '7': pageCount = 7; break;
      case '8': pageCount = 8; break;
      case '9': pageCount = 9; break;
      default: pageCount = 1; break;
    }
    text++;
    for (page = 0; page < pageCount; page++) {
      pageStarts[page] = text;
      while (*text != '^') {
        text++;
      }
      text++;
    }
    g201CB59 = pageCount;
    BuildDescriptionPageBuffer(pageStarts[0], 0, pageCount, pageBuffer);
    return pageCount;
  }

  for (i = 0; *text && *text != '$';) {
    buffer[i] = *text;
    if (*text > 127)
      buffer[++i] = *++text;
    i++;
    text++;
    if (i == 12) {
      buffer[i++] = ' ';
      buffer[i++] = ' ';
    }
  }
  buffer[i] = 0;
  CopyStringTilesToVRAMBuffer(pageBuffer, buffer, 0x901);
  g201CB59 = 0;
  return 0;
}

LYN_REPLACE_CHECK(ShowCardDetailView);
void ShowCardDetailView__Replacement(void) {
  const u8 *pageStarts[9];
  u16 *pageBuffer = g201CB60[0];

  /* Auto-detect trunk context from gTrunkMenu.cursorState. */
  if (gRuntimeConfig.enable_card_detail_navigation) {
    if (!gCardDetailNavActive && gTrunkMenu.cursorState == TRUNK_CURSOR_DETAILS) {
      gCardDetailNavActive = 2;
      gCardDetailNavIndex = gTrunkMenu.currentPos;
    }
  }

render_card:
  CardDetailViewBuildDescription(pageBuffer, pageStarts);
  CardDetailViewRenderPage(pageBuffer, pageStarts, g201CB59);

  while (1) {
    if (gNewButtons & DPAD_UP && g201CB59 > 1 && g201CB58) {
      g201CB58--;
      PlayMusic(SFX_MOVE_CURSOR);
      BuildDescriptionPageBuffer(pageStarts[g201CB58], g201CB58, g201CB59, pageBuffer);
      sub_800BCB0(pageBuffer);
      LoadCharblock1();
    }
    if (gNewButtons & DPAD_DOWN && g201CB59 > 1 && g201CB58 < g201CB59 - 1) {
      g201CB58++;
      PlayMusic(SFX_MOVE_CURSOR);
      BuildDescriptionPageBuffer(pageStarts[g201CB58], g201CB58, g201CB59, pageBuffer);
      sub_800BCB0(pageBuffer);
      LoadCharblock1();
    }

    if (gRuntimeConfig.enable_card_detail_navigation && gCardDetailNavActive) {
      if (gNewButtons & DPAD_LEFT) {
        u16 newCard = CARD_NONE;

        if (gCardDetailNavActive == 1) {         /* Deck */
          if (gCardDetailNavIndex > 0) {
            gCardDetailNavIndex--;
            newCard = gDeckMenu.cards[gCardDetailNavIndex];
          }
        } else if (gCardDetailNavActive == 2) {  /* Trunk */
          if (gTrunkMenu.currentPos == 0)
            gTrunkMenu.currentPos = GetTrunkCardCount() - 1;
          else
            gTrunkMenu.currentPos--;
          newCard = GetNthCardOnScreen(2);
        }

        if (newCard != CARD_NONE) {
          SetCardInfo(newCard);
          PlayMusic(SFX_MOVE_CURSOR);
          goto render_card;
        }
      }

      if (gNewButtons & DPAD_RIGHT) {
        u16 newCard = CARD_NONE;

        if (gCardDetailNavActive == 1) {         /* Deck */
          if (gCardDetailNavIndex < gDeckMenu.cardCount - 1) {
            gCardDetailNavIndex++;
            newCard = gDeckMenu.cards[gCardDetailNavIndex];
          }
        } else if (gCardDetailNavActive == 2) {  /* Trunk */
          gTrunkMenu.currentPos++;
          if (gTrunkMenu.currentPos >= GetTrunkCardCount())
            gTrunkMenu.currentPos = 0;
          newCard = GetNthCardOnScreen(2);
        }

        if (newCard != CARD_NONE) {
          SetCardInfo(newCard);
          PlayMusic(SFX_MOVE_CURSOR);
          goto render_card;
        }
      }
    }

    if (gNewButtons & B_BUTTON || gNewButtons & A_BUTTON)
      break;
    WaitForVBlank();
  }
  PlayMusic(SFX_CANCEL);
  sub_801FB2C();
  while (gPressedButtons & (A_BUTTON | B_BUTTON))
    WaitForVBlank();
  gInputRepeatTimer = 0;
}

static u8 ShouldUseCustomDuelistRewards(void) {
  return gRuntimeConfig.repeatable_opponent_capacity_reward == 0
    && gRuntimeConfig.story_opponent_capacity_reward == 0;
}

static const CustomDuelistRewardEntry *GetCustomDuelistRewardEntryById(u16 opponent) {
  const CustomDuelistRewardEntry *entry;

  if (!ShouldUseCustomDuelistRewards())
    return NULL;
  if (opponent >= ARRAY_COUNT(gCustomDuelistRewards))
    return NULL;

  entry = &gCustomDuelistRewards[opponent];
  if (!entry->enabled)
    return NULL;
  return entry;
}

const struct CardDrop *GetDuelistAnteDrops(u16 opponent, u8 normalAnte) {
  const CustomDuelistRewardEntry *entry = GetCustomDuelistRewardEntryById(opponent);

  if (entry != NULL)
    return normalAnte ? entry->normalDrops : entry->lowDrops;
  if (opponent >= ARRAY_COUNT(gCustomDuelistRewards) || gUnk8E00B30[opponent] == NULL)
    return NULL;
  return normalAnte ? gUnk8E00B30[opponent]->goodDrops : gUnk8E00B30[opponent]->badDrops;
}

void ApplyCardDetailPaletteExtension(void) {
  u8 i;
  u16 cardColorPal[16];

  if (CardUsesExtendedBigCardPalette(gCardInfo.id) != TRUE)
    return;

  // Palette layout adjustment for card detail view only:
  // - keep banks 0..6 for big art
  // - move card color (old bank 4) to bank 7
  // - remap tilemap palette bank 4 -> 7
  CpuCopy16(gPaletteBuffer + 4 * 16, cardColorPal, 32);
  CpuCopy16(cardColorPal, gPaletteBuffer + 7 * 16, 32);

  for (i = 0; i < 20; i++) {
    u16 j;
    u16 *rows[] = {(u16 *)gBgVram.sbb1F[i], (u16 *)gBgVram.sbb1E[i], (u16 *)gBgVram.sbb1D[i]};
    for (j = 0; j < ARRAY_COUNT(rows); j++) {
      u16 *row = rows[j];
      u16 k;
      for (k = 0; k < 32; k++) {
        u16 entry = row[k];
        if ((entry >> 12) == 4)
          row[k] = (entry & 0x0FFF) | (7 << 12);
      }
    }
  }
}

static const CustomDuelRewardEntry *GetCustomDuelRewardEntry(void) {
  return CustomDecks_GetPendingCardShopDuelRewardEntry();
}

static const CustomDuelistRewardEntry *GetCustomDuelistRewardEntry(void) {
  return GetCustomDuelistRewardEntryById(gDuelData.opponent);
}

static u8 IsAlternatePlayerVictory(void) {
  if (!gDuelLifePoints[DUEL_OPPONENT])
    return FALSE;
  return TRUE;
}

static u32 GetAlternateWinRewardMultiplier(void) {
  if (!IsAlternatePlayerVictory())
    return 1;
  if (!gRuntimeConfig.alternate_win_reward_multiplier)
    return 1;
  return gRuntimeConfig.alternate_win_reward_multiplier;
}

static u32 ApplyCapacityRewardMultiplier(u32 reward) {
  u32 multiplier = GetAlternateWinRewardMultiplier();
  u32 scaledReward = reward * multiplier;
  if (scaledReward > 65000)
    scaledReward = 65000;
  return scaledReward;
}

static u16 PickUniformRewardCard(const u16 *cards, unsigned count) {
  if (cards == NULL || count == 0)
    return CARD_NONE;
  return cards[RandRangeU16(1, count) - 1];
}

static u16 PickWeightedRewardCard(const struct CardDrop *cardDrops) {
  u16 random;

  if (cardDrops == NULL)
    return CARD_NONE;

  random = RandRangeU16(0, 2047);
  while (cardDrops->card != CARD_NONE && random > cardDrops->chance)
    cardDrops++;
  return cardDrops->card;
}

static void AddRewardCardToTrunk__Replacement(void) {
  u8 i;
  if (gAnte == CARD_NONE)
    return;
  for (i = 0; i < 10 && i < gDuelData.unk2A; i++) {
    gDuelData.unk14[i] = sub_801FFE0();
    AddCardQtyToTrunk(gDuelData.unk14[i], 1);
  }
}

static u32 GetConfiguredCapacityReward(u32 baseReward) {
  switch (baseReward) {
    case 1:
      return gRuntimeConfig.repeatable_opponent_capacity_reward;
    case 3:
      return gRuntimeConfig.story_opponent_capacity_reward;
    default:
      return baseReward;
  }
}

LYN_REPLACE_CHECK(sub_801FFE0);
u16 sub_801FFE0__Replacement(void) {
  const CustomDuelRewardEntry *entry = GetCustomDuelRewardEntry();
  const CustomDuelistRewardEntry *duelistEntry = GetCustomDuelistRewardEntry();
  struct CardDrop *cardDrops;
  u16 random;

  if (entry != NULL) {
    if (IsNormalAnte(gAnte) == TRUE)
      return PickUniformRewardCard(entry->normalDrops, entry->normalDropCount);
    return PickUniformRewardCard(entry->lowDrops, entry->lowDropCount);
  }

  if (duelistEntry != NULL) {
    if (IsNormalAnte(gAnte) == TRUE)
      return PickWeightedRewardCard(duelistEntry->normalDrops);
    return PickWeightedRewardCard(duelistEntry->lowDrops);
  }

  if (IsNormalAnte(gAnte) == TRUE)
    cardDrops = gDuelData.duelist.goodDrops;
  else
    cardDrops = gDuelData.duelist.badDrops;

  random = RandRangeU16(0, 2047);
  while (cardDrops->card != CARD_NONE && random > cardDrops->chance)
    cardDrops++;
  return cardDrops->card;
}

static u64 GetDominoScaleMultiplier(u8 scalePower) {
  u64 temp;

  for (temp = 1; scalePower != 0; scalePower--)
    temp *= 10;
  return temp;
}

static const u8 sText_InStock[] APPEND_RODATA = "Added to shop:#0";
static const u8 sText_NoNewCards[] APPEND_RODATA = "No new cards added";
static const u8 sText_WaitInput[] APPEND_RODATA = "#1";

#define SHOP_DROP_LINE_WIDTH 28

static u8 *AppendAsciiToText(u8 *dest, const u8 *src) {
  while (*src)
    *dest++ = *src++;
  return dest;
}

static u8 *AppendU8ToText(u8 *dest, u8 value) {
  if (value >= 10) {
    *dest++ = (u8)('0' + value / 10);
    value = (u8)(value % 10);
  }
  *dest++ = (u8)('0' + value);
  return dest;
}

static u8 CountNameGlyphs(const u8 *name) {
  u8 count = 0;

  while (*name && *name != '$') {
    if (*name > 127)
      name += 2;
    else
      name++;
    count++;
  }
  return count;
}

static u8 GetQtySuffixWidth(u8 qty) {
  if (qty >= 10)
    return 6;
  return 5;
}

static u8 *AppendQtySuffix(u8 *dest, u8 qty) {
  *dest++ = ' ';
  *dest++ = '(';
  *dest++ = 'x';
  dest = AppendU8ToText(dest, qty);
  *dest++ = ')';
  return dest;
}

static u8 *AppendTruncatedName(u8 *dest, const u8 *name, u8 maxGlyphs) {
  u8 totalGlyphs = CountNameGlyphs(name);
  u8 glyphsWritten = 0;

  if (totalGlyphs <= maxGlyphs) {
    while (*name && *name != '$') {
      if (*name > 127) {
        *dest++ = *name++;
        *dest++ = *name++;
      }
      else {
        *dest++ = *name++;
      }
    }
    return dest;
  }

  if (maxGlyphs <= 3) {
    *dest++ = '.';
    *dest++ = '.';
    *dest++ = '.';
    return dest;
  }

  while (*name && *name != '$' && glyphsWritten < maxGlyphs - 3) {
    if (*name > 127) {
      *dest++ = *name++;
      *dest++ = *name++;
    }
    else {
      *dest++ = *name++;
    }
    glyphsWritten++;
  }

  *dest++ = '.';
  *dest++ = '.';
  *dest++ = '.';
  return dest;
}

static u8 *AppendCardShopDropLine(u8 *dest, u16 cardId, u8 qty, u8 addLineBreak) {
  const u8 *name;
  u16 offset;
  u8 maxNameGlyphs;

  SetCardInfo(cardId);
  name = gCardInfo.name;
  offset = GetCurrentLanguageStringOffset(name);
  name += offset;

  maxNameGlyphs = SHOP_DROP_LINE_WIDTH - GetQtySuffixWidth(qty);
  dest = AppendTruncatedName(dest, name, maxNameGlyphs);
  dest = AppendQtySuffix(dest, qty);
  if (addLineBreak) {
    *dest++ = '#';
    *dest++ = '0';
  }
  return dest;
}

static void MergeShopDrop(u16 cardId, u8 qty, u16 *ids, u8 *qtys, u8 *count) {
  u8 i;

  for (i = 0; i < *count; i++) {
    if (ids[i] == cardId) {
      qtys[i] = (u8)(qtys[i] + qty);
      return;
    }
  }

  if (*count < 3) {
    ids[*count] = cardId;
    qtys[*count] = qty;
    (*count)++;
  }
}

static u8 WasShopDropRolledThisWin(u16 cardId, const u16 *picked, u8 pickedCount) {
  u8 i;

  for (i = 0; i < pickedCount; i++) {
    if (picked[i] == cardId)
      return TRUE;
  }
  return FALSE;
}

LYN_REPLACE_CHECK(sub_8020050);
u16 sub_8020050__Replacement(void) {
  struct CardDrop *cardDrops = gDuelData.duelist.shopCards;
  struct CardDrop *cursor;
  u16 random;
  u16 vanillaMaxChance;

  if (cardDrops == NULL)
    return CARD_NONE;

  vanillaMaxChance = 0;
  for (cursor = cardDrops; cursor->card != CARD_NONE; cursor++)
    vanillaMaxChance = cursor->chance;

  random = RandRangeU16(0, 29999);

#if NUM_CUSTOM_TRUNK_CARDS > 0
  // ponytail: carve custom picks from the vanilla success band so hit rate stays ~vanillaMaxChance/30000
  if (gRuntimeConfig.enable_custom_cards_past_800 == TRUE && vanillaMaxChance != 0) {
    u16 customThreshold = vanillaMaxChance / 4;

    if (random < customThreshold)
      return PickUniformRewardCard(gCustomTrunkCards, NUM_CUSTOM_TRUNK_CARDS);
  }
#endif

  cursor = cardDrops;
  while (cursor->card != CARD_NONE && random >= cursor->chance)
    cursor++;

  return cursor->card;
}

static void RunDuelShopDropLoop(u16 *ids, u8 *qtys, u8 *count) {
  unsigned i;
  u16 picked[3];
  u8 pickedCount = 0;

  *count = 0;
  for (i = 0; i < 3; i++) {
    u16 cardId = CARD_NONE;
    u8 attempt;
    u8 qtyBefore;
    u8 qtyAdded;

    for (attempt = 0; attempt < 8; attempt++) {
      cardId = sub_8020050();
      if (cardId == CARD_NONE)
        break;
      if (!WasShopDropRolledThisWin(cardId, picked, pickedCount))
        break;
    }

    if (cardId == CARD_NONE)
      continue;

    if (pickedCount < ARRAY_COUNT(picked))
      picked[pickedCount++] = cardId;

    qtyBefore = GetShopCardQty(cardId);
    AddCardQtyToShop2(cardId, 1);
    qtyAdded = (u8)(GetShopCardQty(cardId) - qtyBefore);
    if (qtyAdded > 0)
      MergeShopDrop(cardId, qtyAdded, ids, qtys, count);
  }
}

LYN_REPLACE_CHECK(AddCardDropsToShop);
void AddCardDropsToShop__Replacement(void) {
  u16 ids[3];
  u8 qtys[3];
  u8 count;

  RunDuelShopDropLoop(ids, qtys, &count);
}

void DisplayDuelShopDropText(void) {
  u8 textBuffer[384];
  u8 *write = textBuffer;
  u16 ids[3];
  u8 qtys[3];
  u8 count;
  u8 i;

  if (gRuntimeConfig.show_duel_shop_card_drops != TRUE)
    return;

  RunDuelShopDropLoop(ids, qtys, &count);

  write = AppendAsciiToText(write, sText_InStock);

  if (count == 0)
    write = AppendAsciiToText(write, sText_NoNewCards);
  else {
    for (i = 0; i < count; i++)
      write = AppendCardShopDropLine(write, ids[i], qtys[i], i + 1 < count);
  }

  write = AppendAsciiToText(write, sText_WaitInput);
  *write = 0;
  sub_8041C94(textBuffer, 0, 0, 0, 0);
}

LYN_REPLACE_CHECK(AddMoneyFromDuelVictory);
void AddMoneyFromDuelVictory__Replacement(void) {
  const CustomDuelRewardEntry *entry = GetCustomDuelRewardEntry();
  const CustomDuelistRewardEntry *duelistEntry = GetCustomDuelistRewardEntry();
  u64 temp;
  u16 minDomino;
  u16 maxDomino;

  if (entry != NULL) {
    temp = GetDominoScaleMultiplier(gUnk8E00B30[gDuelData.opponent]->unk20);
    minDomino = entry->minDomino;
    maxDomino = entry->maxDomino;
  } else if (duelistEntry != NULL) {
    temp = GetDominoScaleMultiplier(duelistEntry->dominoScalePower);
    minDomino = duelistEntry->minDomino;
    maxDomino = duelistEntry->maxDomino;
  } else {
    temp = GetDominoScaleMultiplier(gUnk8E00B30[gDuelData.opponent]->unk20);
    minDomino = gUnk8E00B30[gDuelData.opponent]->minDomino;
    maxDomino = gUnk8E00B30[gDuelData.opponent]->maxDomino;
  }

  gDuelData.moneyReward = RandRangeU16(minDomino, maxDomino) * temp;
  AddMoney(gDuelData.moneyReward);
}

static void ReconcileDuelDefeatStatus(void) {
  if (gDuelistStatus[DUEL_OPPONENT] != DUELIST_STATUS_DEFEAT) {
    if (gDuelLifePoints[DUEL_OPPONENT] == 0
        || NumCardsInDeck(DUEL_OPPONENT) < GetCardsDrawn(DUEL_OPPONENT))
      DeclareLoser(DUEL_OPPONENT);
  }
  if (gDuelistStatus[DUEL_PLAYER] != DUELIST_STATUS_DEFEAT) {
    if (gDuelLifePoints[DUEL_PLAYER] == 0
        || NumCardsInDeck(DUEL_PLAYER) < GetCardsDrawn(DUEL_PLAYER))
      DeclareLoser(DUEL_PLAYER);
  }
}

LYN_REPLACE_CHECK(HandleOutcome);
void HandleOutcome__Replacement(void) {
  ReconcileDuelDefeatStatus();

  if (gDuelistStatus[DUEL_OPPONENT] == DUELIST_STATUS_DEFEAT)
    gDuelData.winner = DUEL_WINNER_PLAYER;
  else
    gDuelData.winner = DUEL_WINNER_OPPONENT;

  if (gDuelData.winner == DUEL_WINNER_PLAYER)
    HandleWin();
  else
    HandleLoss();
}

LYN_REPLACE_CHECK(HandleWin);
void HandleWin__Replacement(void) {
  struct DuelText duelText;
  u32 rewardMultiplier;
  u64 baseMoneyReward;
  const CustomDuelRewardEntry *entry;
  const CustomDuelistRewardEntry *duelistEntry;

  if (TimedDuel_IsActive() == TRUE) {
    TimedDuel_HandleWin();
    if (gDuelType == DUEL_TYPE_INGAME)
      CapLifePointsAfterDuel();
    CustomDecks_ClearPendingCardShopDuel();
    return;
  }

  rewardMultiplier = GetAlternateWinRewardMultiplier();
  entry = GetCustomDuelRewardEntry();
  duelistEntry = GetCustomDuelistRewardEntry();

  if (entry != NULL)
    gDuelData.capacityYield = ApplyCapacityRewardMultiplier(GetConfiguredCapacityReward(entry->capacityYield));
  else if (duelistEntry != NULL)
    gDuelData.capacityYield = ApplyCapacityRewardMultiplier(duelistEntry->capacityYield);
  else
    gDuelData.capacityYield = ApplyCapacityRewardMultiplier(GetConfiguredCapacityReward(gUnk8E00B30[gDuelData.opponent]->capacityYield));
  IncreaseDeckCapacity(gDuelData.capacityYield);
  AddRewardCardToTrunk__Replacement();
  if (gRuntimeConfig.show_duel_shop_card_drops != TRUE)
    AddCardDropsToShop__Replacement();
  AddMoneyFromDuelVictory();
  baseMoneyReward = gDuelData.moneyReward;
  gDuelData.moneyReward = baseMoneyReward * rewardMultiplier;
  if (rewardMultiplier > 1)
    AddMoney(baseMoneyReward * (rewardMultiplier - 1));
  if (!gDuelLifePoints[DUEL_OPPONENT]) {
    FadeOutMusic(4);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_OPPONENT_OUT_OF_LP;
    DisplayDuelText(&duelText);
  }
  else if (NumCardsInDeck(1) < GetCardsDrawn(1)) {
    FadeOutMusic(4);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_OPPONENT_DECK_OUT;
    DisplayDuelText(&duelText);
  }
  if (gDuelData.unk2d) {
    u8 i;
    PlayMusic(gDuelData.winMusic);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_DUEL_VICTORY;
    DisplayDuelText(&duelText);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_CAPACITY_INCREASED;
    duelText.rewardAmount = gDuelData.capacityYield;
    DisplayDuelText(&duelText);
    DisplayMoneyRewardText();
    DisplayDuelShopDropText();
    for (i = 0; i < 10; i++) {
      if (!gDuelData.unk14[i])
        break;
      ResetDuelTextData(&duelText);
      duelText.textId = DUEL_TEXT_CARD_OBTAINED;
      duelText.unk0 = gDuelData.unk14[i];
      DisplayDuelText(&duelText);
      SetCardInfo(gDuelData.unk14[i]);
      ShowCardDetailView();
    }
  }
  if (gDuelType == DUEL_TYPE_INGAME)
    CapLifePointsAfterDuel();

  CustomDecks_ClearPendingCardShopDuel();
}

LYN_REPLACE_CHECK(HandleLoss);
void HandleLoss__Replacement(void) {
  struct DuelText duelText;

  if (TimedDuel_IsActive() == TRUE) {
    if (!gDuelLifePoints[DUEL_PLAYER]) {
      FadeOutMusic(4);
      ResetDuelTextData(&duelText);
      duelText.textId = DUEL_TEXT_PLAYER_OUT_OF_LP;
      DisplayDuelText(&duelText);
    } else if (NumCardsInDeck(0) < GetCardsDrawn(0)) {
      FadeOutMusic(4);
      ResetDuelTextData(&duelText);
      duelText.textId = DUEL_TEXT_PLAYER_DECK_OUT;
      DisplayDuelText(&duelText);
    }
    if (gDuelData.unk2d) {
      PlayMusic(gDuelData.lossMusic);
      ResetDuelTextData(&duelText);
      duelText.textId = DUEL_TEXT_DUEL_LOSS;
      DisplayDuelText(&duelText);
    }
    if (gDuelType == DUEL_TYPE_INGAME)
      CapLifePointsAfterDuel();
    TimedDuel_OnDuelEnd();
    CustomDecks_ClearPendingCardShopDuel();
    return;
  }

  if (gAnte != CARD_NONE)
    RemoveCardQtyFromTrunk(gAnte, 1);
  if (!gDuelLifePoints[DUEL_PLAYER]) {
    FadeOutMusic(4);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_PLAYER_OUT_OF_LP;
    DisplayDuelText(&duelText);
  }
  else if (NumCardsInDeck(0) < GetCardsDrawn(0)) {
    FadeOutMusic(4);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_PLAYER_DECK_OUT;
    DisplayDuelText(&duelText);
  }
  if (gDuelData.unk2d) {
    PlayMusic(gDuelData.lossMusic);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_DUEL_LOSS;
    DisplayDuelText(&duelText);
  }
  if (gDuelType == DUEL_TYPE_INGAME)
    CapLifePointsAfterDuel();

  CustomDecks_ClearPendingCardShopDuel();
}

LYN_REPLACE_CHECK(sub_801F098);
u8 sub_801F098__Replacement(u16 cardId) {
  u8 qty = GetDeckCardQty(cardId);
  if (gRuntimeConfig.disable_ban_list == TRUE)
    return 1;
  if (sub_801F0F0(cardId, g80B9620) == 1) {
    if (qty)
      return 0;
    return 1;
  }
  if (sub_801F0F0(cardId, g80B96AA) == 1) {
    if (qty > 1)
      return 0;
    return 1;
  }
  if (qty > 2)
    return 0;
  return 1;
}
