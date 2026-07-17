#include "global.h"
#include "configs/runtime.h"
#include "card.h"
#include "duel.h"
#include "duel_opponent_hand_scroll.h"
#include "mini_card.h"
#include "six_card_hand.h"

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

typedef void (*StampLockedFn)(u8 *);
static StampLockedFn const sStampLocked = (StampLockedFn)(0x08057621);

/* Free OBJ tile base (see VRAM scan); 32x32 2D mini-card block. */
#define HAND_EXTRA_TILE_INDEX 32
#define HAND_EXTRA_OAM_PLAYER 127
#define HAND_EXTRA_OAM_OPPONENT 9

/* Vanilla hand: 16 + i*44. Six-card: pitch 36 from x=8 → no overlap on 32px OAM. */
static const u8 sSixCardHandX[MAX_HAND_ZONES_SIX] APPEND_RODATA = {
    15, 51, 87, 123, 159, 195
};

struct FieldOamEntry {
  u32 a;
  u16 b;
};

bool8 IsSixCardHandEnabled(void)
{
  return gRuntimeConfig.enable_six_card_hand == TRUE;
}

void SixCardHand_Init(void)
{
  u8 i;

  for (i = 0; i < 2; i++) {
    gHandExtraSlots[i].id = CARD_NONE;
    gHandExtraSlots[i].isFaceUp = 0;
    gHandExtraSlots[i].isLocked = 0;
    gHandExtraSlots[i].isDefending = 0;
    gHandExtraSlots[i].unkTwo = 0;
    gHandExtraSlots[i].unkThree = 0;
    gHandExtraSlots[i].effectExhausted = 0;
    gHandExtraSlots[i].effectUsedThisTurn = 0;
    gHandExtraSlots[i].willChangeSides = 0;
    gHandExtraSlots[i].unk4 = 0;
    gHandExtraSlots[i].permStage = 0;
    gHandExtraSlots[i].tempStage = 0;
  }
}

u8 SixCardHand_Count(u8 fixedDuelist)
{
  u8 col;
  u8 count = 0;

  if (fixedDuelist > DUEL_OPPONENT)
    return 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gDuel.hands[fixedDuelist][col].id != CARD_NONE)
      count++;
  }
  if (IsSixCardHandEnabled() && gHandExtraSlots[fixedDuelist].id != CARD_NONE)
    count++;
  return count;
}

bool8 SixCardHand_HasDrawRoom(u8 fixedDuelist)
{
  u8 col;

  if (fixedDuelist > DUEL_OPPONENT)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gDuel.hands[fixedDuelist][col].id == CARD_NONE)
      return TRUE;
  }

  return IsSixCardHandEnabled() && gHandExtraSlots[fixedDuelist].id == CARD_NONE;
}

bool8 SixCardHand_UsesCompressedLayout(u8 fixedDuelist)
{
  return IsSixCardHandEnabled() && SixCardHand_Count(fixedDuelist) >= MAX_HAND_ZONES_SIX;
}

s16 SixCardHand_GetScreenX(u8 col, u8 fixedDuelist)
{
  if (col >= MAX_HAND_ZONES_SIX)
    col = HAND_SLOT_EXTRA;

  if (SixCardHand_UsesCompressedLayout(fixedDuelist))
    return sSixCardHandX[col];

  if (col >= MAX_ZONES_IN_ROW)
    return sSixCardHandX[HAND_SLOT_EXTRA];

  return g8E116EE[PLAYER_HAND][col];
}

struct DuelCard *SixCardHand_GetFixed(u8 fixedDuelist, u8 col)
{
  if (fixedDuelist > DUEL_OPPONENT)
    return NULL;
  if (col < MAX_ZONES_IN_ROW)
    return &gDuel.hands[fixedDuelist][col];
  if (col == HAND_SLOT_EXTRA && IsSixCardHandEnabled())
    return &gHandExtraSlots[fixedDuelist];
  return NULL;
}

struct DuelCard *SixCardHand_GetPlayerHandZone(u8 col)
{
  return SixCardHand_GetFixed(DUEL_PLAYER, col);
}

struct DuelCard *SixCardHand_GetTurnHandZone(u8 turnDuelist, u8 col)
{
  u8 fixedDuelist;

  if (turnDuelist > INACTIVE_DUELIST)
    return NULL;

  fixedDuelist = (gTurnHands[turnDuelist][0] == &gDuel.hands[DUEL_PLAYER][0])
      ? DUEL_PLAYER
      : DUEL_OPPONENT;
  return SixCardHand_GetFixed(fixedDuelist, col);
}

u8 SixCardHand_FixedDuelistForHandRow(struct DuelCard **zonePtr)
{
  if (zonePtr == NULL || zonePtr[0] == NULL)
    return 0xFF;

  if (zonePtr[0] == &gDuel.hands[DUEL_PLAYER][0])
    return DUEL_PLAYER;
  if (zonePtr[0] == &gDuel.hands[DUEL_OPPONENT][0])
    return DUEL_OPPONENT;

  return 0xFF;
}

u8 SixCardHand_IsHandRowPtr(struct DuelCard **zonePtr)
{
  return SixCardHand_FixedDuelistForHandRow(zonePtr) != 0xFF;
}

struct DuelCard *SixCardHand_ZoneAtHandRow(struct DuelCard **handRow, u8 col)
{
  u8 fixedDuelist;

  if (col < MAX_ZONES_IN_ROW)
    return handRow[col];

  fixedDuelist = SixCardHand_FixedDuelistForHandRow(handRow);
  if (fixedDuelist == 0xFF || !IsSixCardHandEnabled())
    return handRow[0];
  return &gHandExtraSlots[fixedDuelist];
}

u8 SixCardHand_IsHandZone(const struct DuelCard *zone)
{
  u8 col;

  if (zone == NULL)
    return FALSE;

  if (zone == &gHandExtraSlots[DUEL_PLAYER] || zone == &gHandExtraSlots[DUEL_OPPONENT])
    return TRUE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (&gDuel.hands[DUEL_PLAYER][col] == zone || &gDuel.hands[DUEL_OPPONENT][col] == zone)
      return TRUE;
  }
  return FALSE;
}

u8 SixCardHand_OwnerOf(const struct DuelCard *zone)
{
  u8 col;

  if (zone == &gHandExtraSlots[DUEL_PLAYER])
    return DUEL_PLAYER;
  if (zone == &gHandExtraSlots[DUEL_OPPONENT])
    return DUEL_OPPONENT;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (&gDuel.hands[DUEL_PLAYER][col] == zone)
      return DUEL_PLAYER;
    if (&gDuel.hands[DUEL_OPPONENT][col] == zone)
      return DUEL_OPPONENT;
  }
  return 0xFF;
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

void SixCardHand_Compact(u8 fixedDuelist)
{
  struct DuelCard packed[MAX_HAND_ZONES_SIX];
  u8 n = 0;
  u8 i;

  if (!IsSixCardHandEnabled() || fixedDuelist > DUEL_OPPONENT)
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gDuel.hands[fixedDuelist][i].id != CARD_NONE)
      packed[n++] = gDuel.hands[fixedDuelist][i];
  }
  if (gHandExtraSlots[fixedDuelist].id != CARD_NONE)
    packed[n++] = gHandExtraSlots[fixedDuelist];

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    ClearHandSlotRaw(&gDuel.hands[fixedDuelist][i]);
  ClearHandSlotRaw(&gHandExtraSlots[fixedDuelist]);

  for (i = 0; i < n && i < MAX_ZONES_IN_ROW; i++)
    gDuel.hands[fixedDuelist][i] = packed[i];
  if (n == MAX_HAND_ZONES_SIX)
    gHandExtraSlots[fixedDuelist] = packed[HAND_SLOT_EXTRA];
}

void SixCardHand_OnZoneCleared(struct DuelCard *zone)
{
  u8 owner;

  if (!IsSixCardHandEnabled())
    return;

  owner = SixCardHand_OwnerOf(zone);
  if (owner == 0xFF)
    return;

  SixCardHand_Compact(owner);
}

u8 SixCardHand_CursorMaxX(u8 row)
{
  if (!IsSixCardHandEnabled())
    return MAX_ZONES_IN_ROW - 1;

  if (row == PLAYER_HAND && SixCardHand_UsesCompressedLayout(DUEL_PLAYER))
    return HAND_SLOT_EXTRA;

  if (row == OPPONENT_HAND_ROW
      && SixCardHand_UsesCompressedLayout(DUEL_OPPONENT))
    return HAND_SLOT_EXTRA;

  return MAX_ZONES_IN_ROW - 1;
}

void SixCardHand_ClampCursorX(void)
{
  u8 maxX = SixCardHand_CursorMaxX(gDuelCursor.currentY);

  if (gDuelCursor.currentX > maxX)
    gDuelCursor.currentX = maxX;
  if (gDuelCursor.destX > maxX)
    gDuelCursor.destX = maxX;
}

u16 SixCardHand_ExtraTileIndex(void)
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

void SixCardHand_HideExtraOam(void)
{
  HideOam(HAND_EXTRA_OAM_PLAYER);
  HideOam(HAND_EXTRA_OAM_OPPONENT);
}

extern const unsigned char g89A7BDE[];

static void ComposePlayerHandMiniCard(u8 *tilePtr, struct DuelCard *card)
{
  /* Match vanilla hand blit: always show card art; face-down only adds the R icon. */
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

void SixCardHand_RefreshExtraTiles(void)
{
  struct DuelCard *card;
  u8 *tilePtr;

  if (!IsSixCardHandEnabled())
    return;

  tilePtr = gBgVram.cbb0 + 0x10000 + HAND_EXTRA_TILE_INDEX * 32;

  if (ShouldDrawOpponentHandOnField()) {
    card = &gHandExtraSlots[DUEL_OPPONENT];
    if (card->id == CARD_NONE)
      return;
    ComposeOpponentHandMiniCard(tilePtr, card);
    return;
  }

  card = &gHandExtraSlots[DUEL_PLAYER];
  if (card->id == CARD_NONE)
    return;
  ComposePlayerHandMiniCard(tilePtr, card);
}

static void PlaceExtraHandOam(u8 oamIndex, s16 x, s16 y)
{
  struct FieldOamEntry *oam = OamAt(oamIndex);

  oam->a = (u32)((y & 0xFF) | ((x << 16) & 0x01FF0000) | 0x80002100);
  oam->a |= 0x2000000;
  oam->b = (HAND_EXTRA_TILE_INDEX & 0x3FF) | 0x800;
}

void SixCardHand_DrawHandOam(void)
{
  struct DuelCard *card;
  s16 x;
  s16 y;

  SixCardHand_HideExtraOam();

  if (!IsSixCardHandEnabled())
    return;

  if (ShouldDrawOpponentHandOnField()) {
    card = &gHandExtraSlots[DUEL_OPPONENT];
    if (card->id == CARD_NONE)
      return;
    SixCardHand_RefreshExtraTiles();
    x = SixCardHand_GetScreenX(HAND_SLOT_EXTRA, DUEL_OPPONENT);
    y = (s16)(OPPONENT_HAND_ROW_SCREEN_Y - gBG2VOFS);
    PlaceExtraHandOam(HAND_EXTRA_OAM_OPPONENT, x, y);
    return;
  }

  card = &gHandExtraSlots[DUEL_PLAYER];
  if (card->id == CARD_NONE)
    return;

  SixCardHand_RefreshExtraTiles();
  x = SixCardHand_GetScreenX(HAND_SLOT_EXTRA, DUEL_PLAYER);
  y = (s16)(g8E11720[PLAYER_HAND] - gBG2VOFS);
  PlaceExtraHandOam(HAND_EXTRA_OAM_PLAYER, x, y);
}
