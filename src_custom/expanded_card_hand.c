#include "global.h"
#include "configs/runtime.h"
#include "card.h"
#include "duel.h"
#include "duel_helpers.h"
#include "duel_opponent_hand_scroll.h"
#include "exchange_hand_selection.h"
#include "mini_card.h"
#include "expanded_card_hand.h"

extern u16 gOamBuffer[];
extern u16 g8E116BC[];
extern s16 g8E116EE[][5];
extern s16 g8E11720[];
extern struct DuelCard *gFixedZones[][MAX_ZONES_IN_ROW];
extern struct DuelCard *gTurnHands[2][MAX_ZONES_IN_ROW];

void sub_80573D0(void *, unsigned short);
void sub_80576B4(unsigned char *, unsigned short);
void sub_80576EC(unsigned char *, unsigned short);
void sub_80572A8(unsigned char *, struct DuelCard *);
void sub_805733C(unsigned char *, struct DuelCard *);
void CopyFaceDownCardTiles(unsigned char *);
void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void UpdateDuelGfxExceptField(void);
void sub_8041C94(u8 *, u16, u16, u16, u16);

extern unsigned char *gUnk_8E17F48[];
extern unsigned char gSharedMem[];
extern u8 gHideEffectText;

typedef void (*StampLockedFn)(u8 *);
typedef void (*ComposeMiniCardFn)(u8 *, u8 *, u8 *);

static StampLockedFn const sStampLocked = (StampLockedFn)(0x08057621);
static ComposeMiniCardFn const sComposeMiniCard = (ComposeMiniCardFn)(0x080565F1);

static u8 AnyHandCard(u16 cardId)
{
  return cardId != CARD_NONE;
}

/* Shared OBJ tile base for extras (unique tiles when ≤7 so ATK/DEF can differ). */
#define HAND_EXTRA_TILE_INDEX 32
#define HAND_EXTRA_TILE_STRIDE 128 /* 0x1000-byte 2D mini-card footprint / 32 */
/*
 * GBA: lower OAM index draws in front. Field hand is OAM 122–126 (left→right = front→back).
 * Overlap mode: hide those and draw the whole hand at 10.. with the same front→back order.
 * Single 6th card (compressed): OAM 127 sits behind 126.
 */
#define HAND_OVERLAP_OAM_BASE 10
#define HAND_EXTRA_OAM_SINGLE 127
#define FIELD_HAND_OAM_BASE (102 + PLAYER_HAND * MAX_ZONES_IN_ROW)
/* mini.pal: 159=dark grey (41,41,41). */
#define HAND_GREY_ART_INDEX 159
#define HAND_GREY_ART_BYTES 576 /* 24x24 8bpp indices */
#define HAND_HIDE_ATK_DEF_AFTER 7

static const u8 sDiscardHandPrefix[] APPEND_RODATA = "Discard ";
static const u8 sDiscardHandOne[] APPEND_RODATA =
    "Discard 1 card to return#0your hand to 6.#1";
static const u8 sDiscardHandMany[] APPEND_RODATA =
    " cards to return#0your hand to 6.#1";

/* Vanilla hand: 16 + i*44. Six-card: pitch 36 from x=15 → no overlap on 32px OAM. */
static const u8 sCompressedHandX[HAND_SIZE_LIMIT] APPEND_RODATA = {
    15, 51, 87, 123, 159, 195
};

struct FieldOamEntry {
  u32 a;
  u16 b;
};

bool8 IsExpandedCardHandEnabled(void)
{
  return gRuntimeConfig.expanded_card_hand == TRUE;
}

u8 ExpandedHand_MaxSlots(void)
{
  return IsExpandedCardHandEnabled() ? MAX_HAND_CARDS : MAX_ZONES_IN_ROW;
}

static void ClearHandSlotRaw(struct DuelCard *zone)
{
  zone->id = CARD_NONE;
  zone->isFaceUp = 0;
  zone->isLocked = 0;
  zone->isDefending = 0;
  zone->unkTwo = 0;
  zone->unkThree = 0;
  zone->effectExhausted = 0;
  zone->effectUsedThisTurn = 0;
  zone->willChangeSides = 0;
  zone->unk4 = 0;
  zone->permStage = 0;
  zone->tempStage = 0;
}

void ExpandedHand_Init(void)
{
  u8 d;
  u8 i;

  for (d = 0; d < 2; d++) {
    for (i = 0; i < MAX_HAND_EXTRA; i++)
      ClearHandSlotRaw(&gHandExtraSlots[d][i]);
  }
}

u8 ExpandedHand_Count(u8 fixedDuelist)
{
  u8 col;
  u8 count = 0;

  if (fixedDuelist > DUEL_OPPONENT)
    return 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gDuel.hands[fixedDuelist][col].id != CARD_NONE)
      count++;
  }
  if (IsExpandedCardHandEnabled()) {
    for (col = 0; col < MAX_HAND_EXTRA; col++) {
      if (gHandExtraSlots[fixedDuelist][col].id != CARD_NONE)
        count++;
    }
  }
  return count;
}

bool8 ExpandedHand_HasDrawRoom(u8 fixedDuelist)
{
  u8 col;

  if (fixedDuelist > DUEL_OPPONENT)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gDuel.hands[fixedDuelist][col].id == CARD_NONE)
      return TRUE;
  }

  if (!IsExpandedCardHandEnabled())
    return FALSE;

  for (col = 0; col < MAX_HAND_EXTRA; col++) {
    if (gHandExtraSlots[fixedDuelist][col].id == CARD_NONE)
      return TRUE;
  }
  return FALSE;
}

bool8 ExpandedHand_UsesCompressedLayout(u8 fixedDuelist)
{
  u8 count;

  if (!IsExpandedCardHandEnabled())
    return FALSE;

  count = ExpandedHand_Count(fixedDuelist);
  return count == HAND_SIZE_LIMIT;
}

bool8 ExpandedHand_UsesBlankOverlapLayout(u8 fixedDuelist)
{
  return IsExpandedCardHandEnabled() && ExpandedHand_Count(fixedDuelist) > HAND_SIZE_LIMIT;
}

bool8 ExpandedHand_ShouldHideHandAtkDef(u8 fixedDuelist)
{
  return IsExpandedCardHandEnabled()
      && ExpandedHand_Count(fixedDuelist) > HAND_HIDE_ATK_DEF_AFTER;
}

s16 ExpandedHand_GetScreenX(u8 col, u8 fixedDuelist)
{
  u8 count;

  if (col >= MAX_HAND_CARDS)
    col = HAND_SLOT_LAST;

  count = ExpandedHand_Count(fixedDuelist);

  if (ExpandedHand_UsesBlankOverlapLayout(fixedDuelist)) {
    /* Same span as a 6-card hand; closer pitch → overlap as count grows. */
    if (count <= 1)
      return sCompressedHandX[0];
    if (col >= count)
      col = count - 1;
    return (s16)(sCompressedHandX[0]
                 + ((sCompressedHandX[HAND_SIZE_LIMIT - 1] - sCompressedHandX[0]) * col)
                       / (count - 1));
  }

  if (ExpandedHand_UsesCompressedLayout(fixedDuelist)) {
    if (col >= HAND_SIZE_LIMIT)
      col = HAND_SIZE_LIMIT - 1;
    return sCompressedHandX[col];
  }

  if (col >= MAX_ZONES_IN_ROW)
    return sCompressedHandX[HAND_SIZE_LIMIT - 1];

  return g8E116EE[PLAYER_HAND][col];
}

struct DuelCard *ExpandedHand_GetFixed(u8 fixedDuelist, u8 col)
{
  if (fixedDuelist > DUEL_OPPONENT)
    return NULL;
  if (col < MAX_ZONES_IN_ROW)
    return &gDuel.hands[fixedDuelist][col];
  if (IsExpandedCardHandEnabled() && col < MAX_HAND_CARDS)
    return &gHandExtraSlots[fixedDuelist][col - HAND_SLOT_FIRST_EXTRA];
  return NULL;
}

struct DuelCard *ExpandedHand_GetPlayerHandZone(u8 col)
{
  return ExpandedHand_GetFixed(DUEL_PLAYER, col);
}

struct DuelCard *ExpandedHand_GetTurnHandZone(u8 turnDuelist, u8 col)
{
  u8 fixedDuelist;

  if (turnDuelist > INACTIVE_DUELIST)
    return NULL;

  fixedDuelist = (gTurnHands[turnDuelist][0] == &gDuel.hands[DUEL_PLAYER][0])
      ? DUEL_PLAYER
      : DUEL_OPPONENT;
  return ExpandedHand_GetFixed(fixedDuelist, col);
}

u8 ExpandedHand_FixedDuelistForHandRow(struct DuelCard **zonePtr)
{
  if (zonePtr == NULL || zonePtr[0] == NULL)
    return 0xFF;

  if (zonePtr[0] == &gDuel.hands[DUEL_PLAYER][0])
    return DUEL_PLAYER;
  if (zonePtr[0] == &gDuel.hands[DUEL_OPPONENT][0])
    return DUEL_OPPONENT;

  return 0xFF;
}

u8 ExpandedHand_IsHandRowPtr(struct DuelCard **zonePtr)
{
  return ExpandedHand_FixedDuelistForHandRow(zonePtr) != 0xFF;
}

struct DuelCard *ExpandedHand_ZoneAtHandRow(struct DuelCard **handRow, u8 col)
{
  u8 fixedDuelist;

  if (col < MAX_ZONES_IN_ROW)
    return handRow[col];

  fixedDuelist = ExpandedHand_FixedDuelistForHandRow(handRow);
  if (fixedDuelist == 0xFF || !IsExpandedCardHandEnabled() || col >= MAX_HAND_CARDS)
    return handRow[0];
  return &gHandExtraSlots[fixedDuelist][col - HAND_SLOT_FIRST_EXTRA];
}

u8 ExpandedHand_IsHandZone(const struct DuelCard *zone)
{
  u8 col;
  u8 d;

  if (zone == NULL)
    return FALSE;

  if (IsExpandedCardHandEnabled()) {
    for (d = 0; d < 2; d++) {
      for (col = 0; col < MAX_HAND_EXTRA; col++) {
        if (zone == &gHandExtraSlots[d][col])
          return TRUE;
      }
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (&gDuel.hands[DUEL_PLAYER][col] == zone || &gDuel.hands[DUEL_OPPONENT][col] == zone)
      return TRUE;
  }
  return FALSE;
}

u8 ExpandedHand_OwnerOf(const struct DuelCard *zone)
{
  u8 col;
  u8 d;

  if (IsExpandedCardHandEnabled()) {
    for (d = 0; d < 2; d++) {
      for (col = 0; col < MAX_HAND_EXTRA; col++) {
        if (zone == &gHandExtraSlots[d][col])
          return d;
      }
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (&gDuel.hands[DUEL_PLAYER][col] == zone)
      return DUEL_PLAYER;
    if (&gDuel.hands[DUEL_OPPONENT][col] == zone)
      return DUEL_OPPONENT;
  }
  return 0xFF;
}

void ExpandedHand_Compact(u8 fixedDuelist)
{
  struct DuelCard packed[MAX_HAND_CARDS];
  u8 n = 0;
  u8 i;

  if (!IsExpandedCardHandEnabled() || fixedDuelist > DUEL_OPPONENT)
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gDuel.hands[fixedDuelist][i].id != CARD_NONE)
      packed[n++] = gDuel.hands[fixedDuelist][i];
  }
  for (i = 0; i < MAX_HAND_EXTRA; i++) {
    if (gHandExtraSlots[fixedDuelist][i].id != CARD_NONE)
      packed[n++] = gHandExtraSlots[fixedDuelist][i];
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    ClearHandSlotRaw(&gDuel.hands[fixedDuelist][i]);
  for (i = 0; i < MAX_HAND_EXTRA; i++)
    ClearHandSlotRaw(&gHandExtraSlots[fixedDuelist][i]);

  for (i = 0; i < n && i < MAX_ZONES_IN_ROW; i++)
    gDuel.hands[fixedDuelist][i] = packed[i];
  for (; i < n; i++)
    gHandExtraSlots[fixedDuelist][i - HAND_SLOT_FIRST_EXTRA] = packed[i];
}

void ExpandedHand_OnZoneCleared(struct DuelCard *zone)
{
  u8 owner;

  if (!IsExpandedCardHandEnabled())
    return;

  owner = ExpandedHand_OwnerOf(zone);
  if (owner == 0xFF)
    return;

  ExpandedHand_Compact(owner);
}

static s8 PickRandomOccupiedHandSlot(u8 fixedDuelist)
{
  u8 occupied = ExpandedHand_Count(fixedDuelist);
  u8 chosen;
  u8 seen = 0;
  u8 col;
  struct DuelCard *zone;

  if (occupied == 0)
    return -1;

  chosen = RandRangeU8(0, occupied - 1);
  for (col = 0; col < ExpandedHand_MaxSlots(); col++) {
    zone = ExpandedHand_GetFixed(fixedDuelist, col);
    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    if (seen == chosen)
      return (s8)col;
    seen++;
  }
  return -1;
}

void ExpandedHand_EnforceSizeLimit(u8 fixedDuelist)
{
  struct DuelCard **handRow;
  struct DuelCard *zone;
  s8 slot;
  u8 turnDuelist;
  u8 count;
  u8 discardCount;

  if (!IsExpandedCardHandEnabled() || fixedDuelist > DUEL_OPPONENT)
    return;

  count = ExpandedHand_Count(fixedDuelist);
  if (count <= HAND_SIZE_LIMIT)
    return;

  discardCount = count - HAND_SIZE_LIMIT;
  turnDuelist = (gTurnHands[ACTIVE_DUELIST][0] == &gDuel.hands[fixedDuelist][0])
      ? ACTIVE_DUELIST
      : INACTIVE_DUELIST;
  handRow = gTurnHands[turnDuelist];

  if (fixedDuelist == DUEL_PLAYER && WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    u8 buffer[80];
    u8 *write = buffer;

    if (discardCount == 1) {
      const u8 *src = sDiscardHandOne;
      while (*src)
        *write++ = *src++;
    } else {
      const u8 *src = sDiscardHandPrefix;
      while (*src)
        *write++ = *src++;
      *write++ = (u8)('0' + discardCount);
      src = sDiscardHandMany;
      while (*src)
        *write++ = *src++;
    }
    *write = 0;
    sub_8041C94(buffer, 0, 0, 0, 0);
  }

  while (ExpandedHand_Count(fixedDuelist) > HAND_SIZE_LIMIT) {
    if (fixedDuelist == DUEL_PLAYER && WhoseTurn() == DUEL_PLAYER) {
      slot = SelectHandCardMatchingPredicate(handRow, AnyHandCard);
      if (slot < 0)
        break;
      zone = ExpandedHand_ZoneAtHandRow(handRow, (u8)slot);
    } else {
      slot = PickRandomOccupiedHandSlot(fixedDuelist);
      if (slot < 0)
        break;
      zone = ExpandedHand_GetFixed(fixedDuelist, (u8)slot);
    }

    if (zone == NULL || zone->id == CARD_NONE)
      break;

    ClearZoneAndSendMonToGraveyard(zone, fixedDuelist);
    UpdateDuelGfxExceptField();

    if (IsDuelOver() == TRUE)
      return;
  }
}

u8 ExpandedHand_CursorMaxX(u8 row)
{
  u8 count;
  u8 fixedDuelist;

  if (!IsExpandedCardHandEnabled())
    return MAX_ZONES_IN_ROW - 1;

  if (row == PLAYER_HAND)
    fixedDuelist = DUEL_PLAYER;
  else if (row == OPPONENT_HAND_ROW)
    fixedDuelist = DUEL_OPPONENT;
  else
    return MAX_ZONES_IN_ROW - 1;

  count = ExpandedHand_Count(fixedDuelist);
  if (count == 0)
    return 0;
  if (count > MAX_ZONES_IN_ROW)
    return count - 1;
  return MAX_ZONES_IN_ROW - 1;
}

void ExpandedHand_ClampCursorX(void)
{
  u8 maxX = ExpandedHand_CursorMaxX(gDuelCursor.currentY);

  if (gDuelCursor.currentX > maxX)
    gDuelCursor.currentX = maxX;
  if (gDuelCursor.destX > maxX)
    gDuelCursor.destX = maxX;
}

u16 ExpandedHand_ExtraTileIndex(void)
{
  return HAND_EXTRA_TILE_INDEX;
}

static struct FieldOamEntry *OamAt(u8 index)
{
  return (struct FieldOamEntry *)&gOamBuffer[index * 4];
}

static void HideOam(u8 index)
{
  OamAt(index)->a = 0x200;
  OamAt(index)->b = 0;
}

void ExpandedHand_HideExtraOam(void)
{
  u8 i;

  for (i = 0; i < MAX_HAND_CARDS; i++)
    HideOam(HAND_OVERLAP_OAM_BASE + i);
  HideOam(HAND_EXTRA_OAM_SINGLE);
}

static void HidePlayerHandFieldOam(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++)
    HideOam(FIELD_HAND_OAM_BASE + col);
}

extern const unsigned char g89A7BDE[];

/* Same 2D OBJ footprint as Casino_ClearMiniSlot / CopyFaceDownCardTiles. */
static void ClearMiniCardSlot(u8 *dest)
{
  u8 i;

  for (i = 0; i < 4; i++)
    CpuFill16(0, dest + i * 0x400, 0x100);
}

static void ComposeGreyArtMiniCard(u8 *tilePtr)
{
  u16 i;

  /* Wipe prior art/ATK/DEF stamps — compose only rewrites the leading merge block. */
  ClearMiniCardSlot(tilePtr);

  for (i = 0; i < HAND_GREY_ART_BYTES; i++)
    gSharedMem[i] = HAND_GREY_ART_INDEX;

  sComposeMiniCard(tilePtr, gSharedMem, gUnk_8E17F48[COLOR_NORMAL]);
}

static void ComposePlayerHandMiniCard(u8 *tilePtr, struct DuelCard *card)
{
  sub_80573D0(tilePtr, card->id);
  sub_80576B4(tilePtr, card->id);
  sub_80576EC(tilePtr, card->id);
  sub_80572A8(tilePtr, card);
  sub_805733C(tilePtr, card);
  if (card->isLocked)
    sStampLocked(tilePtr);
  if (!card->isFaceUp) {
    tilePtr += 0xC80;
    CpuCopy16(g89A7BDE, tilePtr, 64);
  }
}

static void ComposeOpponentHandMiniCard(u8 *tilePtr, struct DuelCard *card)
{
  if (card->isFaceUp) {
    sub_80573D0(tilePtr, card->id);
    sub_80576B4(tilePtr, card->id);
    sub_80576EC(tilePtr, card->id);
    sub_80572A8(tilePtr, card);
    sub_805733C(tilePtr, card);
    if (card->isLocked)
      sStampLocked(tilePtr);
  } else {
    CopyFaceDownCardTiles(tilePtr);
    if (card->isLocked)
      sStampLocked(tilePtr);
  }
}

void ExpandedHand_ComposeGreyArtTile(u8 *tilePtr)
{
  ComposeGreyArtMiniCard(tilePtr);
}

void ExpandedHand_MaybeBlankHandTiles(void)
{
  u8 i;
  u8 *tilePtr;
  u8 fixedDuelist = ShouldDrawOpponentHandOnField() ? DUEL_OPPONENT : DUEL_PLAYER;

  if (!ExpandedHand_UsesBlankOverlapLayout(fixedDuelist))
    return;

  /* ponytail: >6 cards keep the frame, grey the art; all extras share one tile. */
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (fixedDuelist == DUEL_PLAYER && gFixedZones[PLAYER_HAND][i]->id == CARD_NONE)
      continue;
    tilePtr = gBgVram.cbb0 + 0x10000 + g8E116BC[i + 20] * 32;
    ComposeGreyArtMiniCard(tilePtr);
  }
}

void ExpandedHand_RefreshExtraTiles(void)
{
  struct DuelCard *card;
  u8 *tilePtr;
  u8 fixedDuelist;
  u8 i;
  u8 oamSlot;
  u16 tileIndex;
  u8 hideStats;

  if (!IsExpandedCardHandEnabled())
    return;

  fixedDuelist = ShouldDrawOpponentHandOnField() ? DUEL_OPPONENT : DUEL_PLAYER;
  hideStats = ExpandedHand_ShouldHideHandAtkDef(fixedDuelist);

  if (ExpandedHand_UsesBlankOverlapLayout(fixedDuelist)) {
    if (hideStats) {
      /* 8+: one shared grey tile, no ATK/DEF. */
      tilePtr = gBgVram.cbb0 + 0x10000 + HAND_EXTRA_TILE_INDEX * 32;
      ComposeGreyArtMiniCard(tilePtr);
      return;
    }

    /* 7 cards: per-extra grey tile + that monster's ATK/DEF. */
    oamSlot = 0;
    for (i = 0; i < MAX_HAND_EXTRA; i++) {
      card = &gHandExtraSlots[fixedDuelist][i];
      if (card->id == CARD_NONE)
        continue;
      tileIndex = HAND_EXTRA_TILE_INDEX + oamSlot * HAND_EXTRA_TILE_STRIDE;
      tilePtr = gBgVram.cbb0 + 0x10000 + tileIndex * 32;
      ComposeGreyArtMiniCard(tilePtr);
      sub_80572A8(tilePtr, card);
      sub_805733C(tilePtr, card);
      oamSlot++;
    }
    return;
  }

  /* Exactly one extra (6-card compressed): blit that card's art. */
  card = NULL;
  for (i = 0; i < MAX_HAND_EXTRA; i++) {
    if (gHandExtraSlots[fixedDuelist][i].id != CARD_NONE) {
      card = &gHandExtraSlots[fixedDuelist][i];
      break;
    }
  }
  if (card == NULL)
    return;

  tilePtr = gBgVram.cbb0 + 0x10000 + HAND_EXTRA_TILE_INDEX * 32;
  if (fixedDuelist == DUEL_OPPONENT)
    ComposeOpponentHandMiniCard(tilePtr, card);
  else
    ComposePlayerHandMiniCard(tilePtr, card);
}

static void PlaceExtraHandOam(u8 oamIndex, s16 x, s16 y, u16 tileIndex)
{
  struct FieldOamEntry *oam = OamAt(oamIndex);

  oam->a = (u32)((y & 0xFF) | ((x << 16) & 0x01FF0000) | 0x80002100);
  oam->a |= 0x2000000;
  oam->b = (tileIndex & 0x3FF) | 0x800;
}

void ExpandedHand_DrawHandOam(void)
{
  struct DuelCard *card;
  s16 x;
  s16 y;
  u8 fixedDuelist;
  u8 col;
  u8 oamSlot = 0;
  u8 extraSlot = 0;
  u16 tileIndex;
  u8 hideStats;
  u8 blank;

  ExpandedHand_HideExtraOam();

  if (!IsExpandedCardHandEnabled())
    return;

  fixedDuelist = ShouldDrawOpponentHandOnField() ? DUEL_OPPONENT : DUEL_PLAYER;
  ExpandedHand_RefreshExtraTiles();
  hideStats = ExpandedHand_ShouldHideHandAtkDef(fixedDuelist);
  blank = ExpandedHand_UsesBlankOverlapLayout(fixedDuelist);

  y = ShouldDrawOpponentHandOnField()
      ? (s16)(OPPONENT_HAND_ROW_SCREEN_Y - gBG2VOFS)
      : (s16)(g8E11720[PLAYER_HAND] - gBG2VOFS);

  /*
   * Overlap (>6): redraw the whole hand. OAM 10+i keeps left-over-right stacking
   * (lower index = in front), matching field hand 122–126.
   */
  if (blank && !ShouldDrawOpponentHandOnField()) {
    HidePlayerHandFieldOam();
    for (col = 0; col < MAX_HAND_CARDS; col++) {
      card = ExpandedHand_GetFixed(fixedDuelist, col);
      if (card == NULL || card->id == CARD_NONE)
        continue;
      if (oamSlot >= MAX_HAND_CARDS)
        break;
      x = ExpandedHand_GetScreenX(col, fixedDuelist);
      if (col < MAX_ZONES_IN_ROW)
        tileIndex = g8E116BC[PLAYER_HAND * MAX_ZONES_IN_ROW + col];
      else if (!hideStats)
        tileIndex = HAND_EXTRA_TILE_INDEX + extraSlot++ * HAND_EXTRA_TILE_STRIDE;
      else
        tileIndex = HAND_EXTRA_TILE_INDEX;
      PlaceExtraHandOam(HAND_OVERLAP_OAM_BASE + oamSlot, x, y, tileIndex);
      oamSlot++;
    }
    return;
  }

  /* ≤6: field OAM owns slots 0–4; one overflow sprite behind them at 127. */
  for (col = HAND_SLOT_FIRST_EXTRA; col < MAX_HAND_CARDS; col++) {
    card = ExpandedHand_GetFixed(fixedDuelist, col);
    if (card == NULL || card->id == CARD_NONE)
      continue;
    x = ExpandedHand_GetScreenX(col, fixedDuelist);
    PlaceExtraHandOam(HAND_EXTRA_OAM_SINGLE, x, y, HAND_EXTRA_TILE_INDEX);
    break;
  }
}
