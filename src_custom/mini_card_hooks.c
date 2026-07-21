#include "global.h"
#include "common-chax.h"
#include "ai_sim.h"
#include "card.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "elemental_hero_terra_firma.h"
#include "riryoku.h"
#include "duel_opponent_hand_scroll.h"
#include "six_card_hand.h"
#include "wave_motion_cannon.h"
#include "cost_down.h"
#include "tribute.h"
#include "duel_helpers.h"

extern unsigned char* g8E1168C[]; //attribute mini-icons
extern unsigned char gSharedMem[];
extern unsigned char *g8E17F70[];
extern const unsigned char *gMiniCardArts_Hook[];
extern unsigned char *gUnk_8E17F48[];
extern const unsigned char g89A781C[];
extern const unsigned char g89A81DE[];
extern const unsigned char g89A7F1E[][64];
extern const unsigned char g89A875E[][64];
extern const unsigned char g89A849E[][64];
extern const unsigned char g89A7ADE[][64];
extern const unsigned char g89A77DC[];
extern const unsigned char g89A7BDE[];
extern u8 gDigitBufferU16[];
extern u16 g8E116BC[];

const unsigned char *GetCustomCardColorBorder(u8 color);

typedef void (*StampStageFn)(u8 *, s8);

static StampStageFn const StampFieldCardStage = (StampStageFn)0x0805763D;
static void StampFieldCardLocked(u8 *tilePtr);

static void StampFieldCardLocked(u8 *tilePtr)
{
  tilePtr += 0xCC0;
  CpuCopy16(g89A77DC, tilePtr, 64);
}

static u8 *FieldCardTilePtr(u8 row, u8 col)
{
  u16 tileIndex;

  if (row == 0)
    tileIndex = col;
  else if (row == 1)
    tileIndex = col + 5;
  else if (row == 2)
    tileIndex = col + 10;
  else if (row == 3)
    tileIndex = col + 15;
  else
    tileIndex = col + 20;

  return gBgVram.cbb0 + 0x10000 + g8E116BC[tileIndex] * 32;
}

static void StampFieldCardAtkFromCardInfo(u8 *tilePtr)
{
  if (gCardInfo.atk / 100 > 99)
    ConvertU16ToDigitBuffer(99, DIGIT_FLAG_NONE);
  else
    ConvertU16ToDigitBuffer(gCardInfo.atk / 100, DIGIT_FLAG_NONE);

  tilePtr += 0x800;
  CpuCopy16(g89A81DE + gDigitBufferU16[3] * 64, tilePtr, 0x40);
  tilePtr += 0x40;
  CpuCopy16(g89A7F1E[gDigitBufferU16[4]], tilePtr, 0x40);
}

static void StampFieldCardDefFromCardInfo(u8 *tilePtr)
{
  if (gCardInfo.def / 100 > 99)
    ConvertU16ToDigitBuffer(99, DIGIT_FLAG_NONE);
  else
    ConvertU16ToDigitBuffer(gCardInfo.def / 100, DIGIT_FLAG_NONE);

  tilePtr += 0x880;
  CpuCopy16(g89A875E[gDigitBufferU16[3]], tilePtr, 0x40);
  tilePtr += 0x40;
  CpuCopy16(g89A849E[gDigitBufferU16[4]], tilePtr, 0x40);
}

static void StampFieldCardAtkDefForZone(u8 *tilePtr, struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || !ZoneShowsCombatStats(zone))
    return;

  ApplyFieldZoneStatsToCardInfo(zone);
  StampFieldCardAtkFromCardInfo(tilePtr);
  StampFieldCardDefFromCardInfo(tilePtr);
}

void RefreshFieldMonsterStatOverlays(void)
{
  u8 col;
  u8 row;
  struct DuelCard *zone;
  u8 *tilePtr;

  /* ponytail: skip VRAM stat writes during AI batch sim only; gHideEffectText
   * must not block refresh — Hourglass/Spellbinding stage changes need ATK/DEF
   * tiles updated while effect text is queued. */
  if (gAiSimInBatch)
    return;

  Duel_BeginFaceUpBackrowCache();
  for (row = 0; row < 5; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      zone = gFixedZones[row][col];
      if (zone->id == CARD_NONE)
        continue;

      if (row == OPPONENT_MONSTER_ROW && !zone->isFaceUp)
        continue;

      /* Row 4 tile VRAM is reused for the opponent hand while field-scrolling. */
      if (row == PLAYER_HAND && ShouldDrawOpponentHandOnField())
        continue;

      tilePtr = FieldCardTilePtr(row, col);

      if (row == OPPONENT_MONSTER_ROW || row == PLAYER_MONSTER_ROW)
        StampFieldCardStage(tilePtr, ComputeFinalStage(zone));

      if (row == PLAYER_HAND && ExpandedHand_ShouldHideHandAtkDef(DUEL_PLAYER))
        continue;

      if (row == OPPONENT_MONSTER_ROW || row == PLAYER_MONSTER_ROW || row == PLAYER_HAND)
        StampFieldCardAtkDefForZone(tilePtr, zone);
    }
  }
  Duel_EndFaceUpBackrowCache();
}

void sub_80573D0(void* arg0, unsigned short cardId);
void sub_805742C(unsigned char* arg0, unsigned short cardId);
void CopyMiniCardPalette(unsigned short* dest);

static const unsigned char *GetMiniArtForCard(u16 cardId) {
  if (cardId >= NUM_TOTAL_CARDS)
    return g8E17F70[CARD_NONE];
  if (gMiniCardArts_Hook[cardId] != NULL)
    return gMiniCardArts_Hook[cardId];
  if (cardId >= CUSTOM_CARD_START)
    return g8E17F70[CARD_NONE];
  return g8E17F70[cardId];
}

LYN_REPLACE_CHECK(sub_80573D0);
void sub_80573D0__Replacement(void* arg0, unsigned short cardId) {
  typedef void (*ComposeMiniCardFn)(void *, void *, unsigned char *);
  static ComposeMiniCardFn const composeMiniCard = (ComposeMiniCardFn)0x080565F1;
  const unsigned char *miniArt = GetMiniArtForCard(cardId);

  SetCardInfo(cardId);

  LZ77UnCompWram(miniArt, gSharedMem);
  {
    /* ponytail: cast discards const — composeMiniCard signature is non-const */
    const unsigned char *border = GetCustomCardColorBorder(gCardInfo.color);
    if (!border) {
      /* Vanilla gUnk_8E17F48 has 9 entries (0–8); guard against OOB for new colors */
      unsigned char *vanillaBorder = (gCardInfo.color < COLOR_SYNCHRO)
          ? gUnk_8E17F48[gCardInfo.color]
          : gUnk_8E17F48[COLOR_NORMAL];
      composeMiniCard(arg0, gSharedMem, vanillaBorder);
    } else {
      composeMiniCard(arg0, gSharedMem, (unsigned char *)border);
    }
  }
}

LYN_REPLACE_CHECK(sub_805742C);
void sub_805742C__Replacement(unsigned char* arg0, unsigned short cardId) {
  typedef void (*CopyShopCardBorderTilesFn)(unsigned char *, unsigned char *, unsigned char *);
  static CopyShopCardBorderTilesFn const copyShopCardBorderTiles = (CopyShopCardBorderTilesFn)0x08056C55;
  const unsigned char *miniArt = GetMiniArtForCard(cardId);

  SetCardInfo(cardId);

  LZ77UnCompWram(miniArt, gSharedMem);
  {
    const unsigned char *border = GetCustomCardColorBorder(gCardInfo.color);
    if (!border) {
      unsigned char *vanillaBorder = (gCardInfo.color < COLOR_SYNCHRO)
          ? gUnk_8E17F48[gCardInfo.color]
          : gUnk_8E17F48[COLOR_NORMAL];
      copyShopCardBorderTiles(arg0, gSharedMem, vanillaBorder);
    } else {
      copyShopCardBorderTiles(arg0, gSharedMem, (unsigned char *)border);
    }
  }
}

void sub_80572A8(unsigned char* arg0, struct DuelCard* arg1);
void sub_805733C(unsigned char* arg0, struct DuelCard* arg1);

LYN_REPLACE_CHECK(sub_80572A8);
void sub_80572A8__Replacement(unsigned char* arg0, struct DuelCard* arg1) {
  if (arg1 == NULL || arg1->id == CARD_NONE)
    return;

  if (!ZoneShowsCombatStats(arg1))
    return;

  ApplyFieldZoneStatsToCardInfo(arg1);
  StampFieldCardAtkFromCardInfo(arg0);
}

LYN_REPLACE_CHECK(sub_805733C);
void sub_805733C__Replacement(unsigned char* arg0, struct DuelCard* arg1) {
  if (arg1 == NULL || arg1->id == CARD_NONE)
    return;

  if (!ZoneShowsCombatStats(arg1))
    return;

  ApplyFieldZoneStatsToCardInfo(arg1);
  StampFieldCardDefFromCardInfo(arg0);
}

void sub_80576B4(unsigned char* arg0, unsigned short cardId);

static int GetMiniCardTributeCount(u16 cardId)
{
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (gFixedZones[PLAYER_HAND][i]->id == cardId)
        return GetMonsterNumRequiredTributesForHandSlot(i, cardId);
    }
  }

  if (!gCostDownActive)
    return GetNumRequiredTributesWithCostDown(cardId);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (ShouldApplyCostDownForHandSlot(i, cardId))
      return GetNumRequiredTributesForHandSlot(i, cardId);
  }

  return GetNumRequiredTributesWithCostDown(cardId);
}

LYN_REPLACE_CHECK(sub_80576EC);
void sub_80576EC__Replacement(unsigned char* arg0, unsigned short cardId) {
  signed char numTributes;

  if (cardId == CARD_NONE)
    return;

  numTributes = GetMiniCardTributeCount(cardId);

  if (numTributes > 0)
    CpuCopy16(g89A7ADE[numTributes], arg0, 64);
}

LYN_REPLACE_CHECK(sub_80576B4);
void sub_80576B4__Replacement(unsigned char* arg0, unsigned short cardId) {
  if (cardId == CARD_NONE)
    return;

  SetCardInfo(cardId);
  if (gRuntimeConfig.disable_element_system == TRUE || gCardInfo.attribute == ATTRIBUTE_NONE)
    return;
  arg0 += 0xC0;
  CpuCopy16(g8E1168C[gCardInfo.attribute], arg0, 64);
}

LYN_REPLACE_CHECK(CopyMiniCardPalette);
void CopyMiniCardPalette__Replacement(unsigned short* dest) {
  CpuCopy16(g89A781C, dest, 320);
}

void sub_80574A8(unsigned char arg0, unsigned char arg1);
void sub_8057808(void);
void CopyFaceDownCardTiles(unsigned char *arg0);

static void StampFieldCardRitualTributes(u8 *tilePtr, u16 cardId)
{
  u8 numTributes = GetRitualNumRequiredTributes(cardId);

  if (numTributes > 0)
    CpuCopy16(g89A7ADE[numTributes], tilePtr, 64);
}

static void RefreshAllFieldCardTiles(void)
{
  u8 i;

  Duel_BeginFaceUpBackrowCache();

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[0][i]->isFaceUp)
      sub_80573D0(gBgVram.cbb0 + 0x10000 + g8E116BC[i] * 32, gFixedZones[0][i]->id);
    else
      CopyFaceDownCardTiles(gBgVram.cbb0 + 0x10000 + g8E116BC[i] * 32);
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u8 *tilePtr = gBgVram.cbb0 + 0x10000 + g8E116BC[i + 5] * 32;
    struct DuelCard *zone = gFixedZones[1][i];

    if (zone->isFaceUp) {
      sub_80573D0(tilePtr, zone->id);
      sub_80576EC(tilePtr, zone->id);
      sub_80576B4(tilePtr, zone->id);
      StampFieldCardStage(tilePtr, ComputeFinalStage(zone));
      StampFieldCardAtkDefForZone(tilePtr, zone);
    } else {
      CopyFaceDownCardTiles(tilePtr);
    }

    if (zone->isLocked)
      StampFieldCardLocked(tilePtr);
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u8 *tilePtr = gBgVram.cbb0 + 0x10000 + g8E116BC[i + 10] * 32;
    struct DuelCard *zone = gFixedZones[2][i];

    if (zone->id == CARD_NONE)
      continue;

    sub_80573D0(tilePtr, zone->id);
    if (zone->isLocked)
      StampFieldCardLocked(tilePtr);
    sub_80576B4(tilePtr, zone->id);
    sub_80576EC(tilePtr, zone->id);
    StampFieldCardStage(tilePtr, ComputeFinalStage(zone));
    StampFieldCardAtkDefForZone(tilePtr, zone);

    if (!zone->isFaceUp && !ElementalHeroTerraFirma_RevealsAllyZone(PLAYER_MONSTER_ROW, i)) {
      tilePtr += 0xC80;
      CpuCopy16(g89A7BDE, tilePtr, 64);
    }
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u8 *tilePtr = gBgVram.cbb0 + 0x10000 + g8E116BC[i + 15] * 32;
    struct DuelCard *zone = gFixedZones[3][i];

    if (zone->id == CARD_NONE)
      continue;

    sub_80573D0(tilePtr, zone->id);
    StampFieldCardRitualTributes(tilePtr, zone->id);

    if (!zone->isFaceUp) {
      tilePtr += 0xC80;
      CpuCopy16(g89A7BDE, tilePtr, 64);
    }
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u8 *tilePtr = gBgVram.cbb0 + 0x10000 + g8E116BC[i + 20] * 32;
    struct DuelCard *zone = gFixedZones[4][i];

    if (zone->id == CARD_NONE)
      continue;

    sub_80573D0(tilePtr, zone->id);
    sub_80576B4(tilePtr, zone->id);
    sub_80576EC(tilePtr, zone->id);
    StampFieldCardAtkDefForZone(tilePtr, zone);

    if (zone->isLocked)
      StampFieldCardLocked(tilePtr);

    if (!zone->isFaceUp) {
      tilePtr += 0xC80;
      CpuCopy16(g89A7BDE, tilePtr, 64);
    }
  }

  Duel_EndFaceUpBackrowCache();
}

LYN_REPLACE_CHECK(sub_80577A4);
void sub_80577A4__Replacement(void) {
  u8 i;
  u8 j;

  RefreshAllFieldCardTiles();
  ExpandedHand_MaybeBlankHandTiles();
  SixCardHand_RefreshExtraTiles();
  RefreshAllWaveMotionCannonFieldCounters();
  CpuCopy16(g89A781C, gPaletteBuffer + 256, 320);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    for (j = 0; j < 5; j++) {
      if (ShouldDrawOpponentHandOnField() && i == PLAYER_HAND)
        continue;
      if (gFixedZones[i][j]->id != CARD_NONE)
        sub_80574A8(j, i);
    }
  }

  if (ShouldDrawOpponentHandOnField())
    DrawOpponentHandOnField();
  else if (!IsOpponentHandFieldScrollEnabled()
           || gBG2VOFS != GetBoardScrollVofs(OPPONENT_HAND_ROW)) {
    HideOpponentHandFieldOam();
    RestoreOpponentHandFieldWindow();
  }

  SixCardHand_DrawHandOam();
  /* RefreshAllFieldCardTiles already stamped ATK/DEF/stage — skip a second
   * ApplyFieldZoneStats pass (was ~2× overlay cost per UpdateDuelGfxExceptField). */
}

LYN_REPLACE_CHECK(sub_8057808);
void sub_8057808__Replacement(void) {
  u8 i;
  u8 j;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    for (j = 0; j < 5; j++) {
      if (ShouldDrawOpponentHandOnField() && i == PLAYER_HAND)
        continue;
      if (gFixedZones[i][j]->id != CARD_NONE)
        sub_80574A8(j, i);
    }
  }

  if (ShouldDrawOpponentHandOnField())
    DrawOpponentHandOnField();
  else if (!IsOpponentHandFieldScrollEnabled()
           || gBG2VOFS != GetBoardScrollVofs(OPPONENT_HAND_ROW)) {
    HideOpponentHandFieldOam();
    RestoreOpponentHandFieldWindow();
  }

  SixCardHand_DrawHandOam();
  RefreshFieldMonsterStatOverlays();
}
