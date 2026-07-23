#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "player_decks.h"
#include "xyz_duel.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void PlayMusic(int);

extern const u8 gCardXyzMaterialCount_Hook[];
extern const CardData gCardData_NEW[];

extern u8 gXyzOverlayCount[2][MAX_ZONES_IN_ROW];
extern u16 gXyzOverlayIds[2][MAX_ZONES_IN_ROW][XYZ_MAX_OVERLAYS];

#define XYZ_PICK_MENU_CAPACITY ((u8)ARRAY_COUNT(gDeckMenu.cards))

static const u8 sXyzDuelPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_XYZ_SUMMON,
};

u8 Card_XyzMaterialCount(u16 cardId)
{
  if (cardId == CARD_NONE)
    return 0;
  return gCardXyzMaterialCount_Hook[cardId];
}

static u8 CardLevel(u16 cardId)
{
  return gCardData_NEW[cardId].level;
}

static u8 CardIsXyz(u16 cardId)
{
  return gCardData_NEW[cardId].color == COLOR_XYZ;
}

/* ponytail: ATK monsters keep isFaceUp=0 until EOT FlipAtkPosCardsFaceUp. */
static u8 ZoneIsFaceUpForXyz(const struct DuelCard *zone)
{
  return zone->isFaceUp || !zone->isDefending;
}

static u16 *ActiveExtraDeck(void)
{
  switch (gActiveDeckIndex) {
  case 2:
    return gPlayerDeck2ExtraDeck;
  case 3:
    return gPlayerDeck3ExtraDeck;
  case 1:
  default:
    return gPlayerDeck1ExtraDeck;
  }
}

void XyzOverlays_ClearZone(u8 fixedDuelist, u8 col)
{
  u8 i;

  if (fixedDuelist > DUEL_OPPONENT || col >= MAX_ZONES_IN_ROW)
    return;

  gXyzOverlayCount[fixedDuelist][col] = 0;
  for (i = 0; i < XYZ_MAX_OVERLAYS; i++)
    gXyzOverlayIds[fixedDuelist][col][i] = CARD_NONE;
}

void XyzOverlays_InitBoard(void)
{
  u8 d;
  u8 col;

  for (d = 0; d < 2; d++)
    for (col = 0; col < MAX_ZONES_IN_ROW; col++)
      XyzOverlays_ClearZone(d, col);
}

void XyzOverlays_Attach(u8 fixedDuelist, u8 col, const u16 *cardIds, u8 count)
{
  u8 i;
  u8 n;

  if (fixedDuelist > DUEL_OPPONENT || col >= MAX_ZONES_IN_ROW || cardIds == NULL)
    return;

  XyzOverlays_ClearZone(fixedDuelist, col);
  n = count;
  if (n > XYZ_MAX_OVERLAYS)
    n = XYZ_MAX_OVERLAYS;

  for (i = 0; i < n; i++) {
    gXyzOverlayIds[fixedDuelist][col][i] = cardIds[i];
  }
  gXyzOverlayCount[fixedDuelist][col] = n;
}

u8 XyzOverlays_GetCount(u8 fixedDuelist, u8 col)
{
  if (fixedDuelist > DUEL_OPPONENT || col >= MAX_ZONES_IN_ROW)
    return 0;

  return gXyzOverlayCount[fixedDuelist][col];
}

u16 XyzOverlays_DetachToGraveyard(u8 fixedDuelist, u8 col, u8 graveyardTurn)
{
  u8 n;
  u16 cardId;
  u8 i;

  (void)graveyardTurn;

  if (fixedDuelist > DUEL_OPPONENT || col >= MAX_ZONES_IN_ROW)
    return CARD_NONE;

  n = gXyzOverlayCount[fixedDuelist][col];
  if (n == 0)
    return CARD_NONE;

  cardId = gXyzOverlayIds[fixedDuelist][col][n - 1];
  gXyzOverlayIds[fixedDuelist][col][n - 1] = CARD_NONE;
  gXyzOverlayCount[fixedDuelist][col] = n - 1;

  if (cardId != CARD_NONE)
    GraveyardExpand_PushFixed(fixedDuelist, cardId);

  /* Shift not needed: detach from top (last index). */
  (void)i;
  return cardId;
}

void XyzOverlays_DumpAllToGraveyard(u8 fixedDuelist, u8 col, u8 graveyardTurn)
{
  u8 i;
  u8 n;

  (void)graveyardTurn;

  if (fixedDuelist > DUEL_OPPONENT || col >= MAX_ZONES_IN_ROW)
    return;

  n = gXyzOverlayCount[fixedDuelist][col];
  for (i = 0; i < n; i++) {
    u16 cardId = gXyzOverlayIds[fixedDuelist][col][i];
    if (cardId != CARD_NONE)
      GraveyardExpand_PushFixed(fixedDuelist, cardId);
  }
  XyzOverlays_ClearZone(fixedDuelist, col);
}

void XyzOverlays_OnMonsterZoneCleared(struct DuelCard *zone, u8 graveyardTurn)
{
  u8 fixedRow;
  u8 col;
  u8 fixedDuelist;

  if (zone == NULL)
    return;
  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return;

  fixedDuelist = Duel_FixedDuelistForMonsterRow(fixedRow);
  if (gXyzOverlayCount[fixedDuelist][col] == 0)
    return;

  XyzOverlays_DumpAllToGraveyard(fixedDuelist, col, graveyardTurn);
}

static void AddSource(struct XyzMaterialSource *out, u8 *count, u8 maxOut, struct DuelCard *zone)
{
  u16 cardId;

  if (*count >= maxOut || zone == NULL)
    return;

  cardId = zone->id;
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return;
  if (!ZoneIsFaceUpForXyz(zone))
    return;

  out[*count].zone = zone;
  out[*count].cardId = cardId;
  out[*count].level = CardLevel(cardId);
  (*count)++;
}

u8 XyzDuel_CollectFaceUpFieldSources(struct XyzMaterialSource *out, u8 maxOut)
{
  u8 count = 0;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    AddSource(out, &count, maxOut, gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]);

  return count;
}

u8 XyzDuel_CanMakeRank(const struct XyzMaterialSource *sources, u8 sourceCount, u8 rank,
                       u8 needCount)
{
  u8 i;
  u8 matched = 0;

  if (sources == NULL || needCount == 0 || rank == 0)
    return FALSE;

  for (i = 0; i < sourceCount; i++) {
    if (sources[i].level == rank)
      matched++;
  }

  return matched >= needCount;
}

u8 XyzDuel_SelectMaterialsForRank(const struct XyzMaterialSource *sources, u8 sourceCount,
                                  u8 rank, u8 needCount, struct XyzMaterialSource *selected,
                                  u8 maxSelected)
{
  u8 i;
  u8 count = 0;

  if (selected == NULL || maxSelected == 0 || needCount == 0)
    return 0;

  for (i = 0; i < sourceCount && count < needCount && count < maxSelected; i++) {
    if (sources[i].level == rank)
      selected[count++] = sources[i];
  }

  if (count < needCount)
    return 0;
  return count;
}

u8 XyzDuel_BuildFeasibleExtraDeckTargets(const struct XyzMaterialSource *sources, u8 sourceCount,
                                         u16 *outIds, u8 maxOut)
{
  u16 *extra;
  u8 count = 0;
  u8 i;
  u8 j;

  if (outIds == NULL || maxOut == 0 || !gRuntimeConfig.enable_extra_deck)
    return 0;

  extra = ActiveExtraDeck();
  for (i = 0; i < EXTRA_DECK_SIZE && count < maxOut; i++) {
    u16 cardId = extra[i];
    u8 need;
    u8 rank;
    u8 dup;

    if (cardId == CARD_NONE || !CardIsXyz(cardId))
      continue;

    need = Card_XyzMaterialCount(cardId);
    if (need == 0)
      continue;

    rank = CardLevel(cardId);
    if (!XyzDuel_CanMakeRank(sources, sourceCount, rank, need))
      continue;

    dup = FALSE;
    for (j = 0; j < count; j++) {
      if (outIds[j] == cardId) {
        dup = TRUE;
        break;
      }
    }
    if (dup)
      continue;

    outIds[count++] = cardId;
  }

  return count;
}

static void XyzDuel_LoadPickMenu(const u16 *targetIds, u8 count)
{
  u8 j;

  for (j = 0; j < XYZ_PICK_MENU_CAPACITY; j++)
    gDeckMenu.cards[j] = CARD_NONE;
  for (j = 0; j < count; j++)
    gDeckMenu.cards[j] = targetIds[j];

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;
}

u16 XyzDuel_PlayerPickTarget(const u16 *targetIds, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u16 chosenId;

  if (targetIds == NULL || count == 0)
    return CARD_NONE;

  DECKMENU_SAVE();
  XyzDuel_LoadPickMenu(targetIds, count);
  DeckMenu_BeginDuelTrunkView();

  if (!DeckMenuMainPickConfirmWithLabels(sXyzDuelPickLabels, ARRAY_COUNT(sXyzDuelPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return CARD_NONE;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenId;
}

static u8 FindZoneColForAttach(u16 resultId, u8 *outFixedDuelist, u8 *outCol)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];
    u8 fixedRow;
    u8 col;
    u8 fixedDuelist;

    if (zone == NULL || zone->id != resultId)
      continue;
    if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
      continue;

    fixedDuelist = Duel_FixedDuelistForMonsterRow(fixedRow);
    if (gXyzOverlayCount[fixedDuelist][col] != 0)
      continue;

    *outFixedDuelist = fixedDuelist;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

void XyzDuel_Execute(u16 resultId, const struct XyzMaterialSource *selected, u8 selectedCount)
{
  struct DuelSummonOpts opts;
  u16 overlayIds[XYZ_MAX_OVERLAYS];
  u8 i;
  u8 fixedDuelist;
  u8 col;

  if (selectedCount > XYZ_MAX_OVERLAYS)
    selectedCount = XYZ_MAX_OVERLAYS;

  for (i = 0; i < selectedCount; i++)
    overlayIds[i] = selected[i].cardId;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].zone != NULL)
      ClearZone(selected[i].zone);
  }

  opts = Duel_DefaultSpecialSummonOpts(FALSE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, resultId, opts) != DUEL_ACTION_OK) {
    UpdateDuelGfxExceptField();
    return;
  }

  if (FindZoneColForAttach(resultId, &fixedDuelist, &col))
    XyzOverlays_Attach(fixedDuelist, col, overlayIds, selectedCount);

  UpdateDuelGfxExceptField();
}

u8 XyzDuel_PlayerCanSummon(void)
{
  struct XyzMaterialSource sources[XYZ_MAX_SOURCES];
  u16 targets[EXTRA_DECK_SIZE];
  u8 sourceCount;
  u8 targetCount;

  if (!gRuntimeConfig.enable_extra_deck)
    return FALSE;

  sourceCount = XyzDuel_CollectFaceUpFieldSources(sources, XYZ_MAX_SOURCES);
  if (sourceCount < 2)
    return FALSE;

  targetCount = XyzDuel_BuildFeasibleExtraDeckTargets(sources, sourceCount, targets, EXTRA_DECK_SIZE);
  return targetCount > 0;
}

void XyzDuel_RunPlayerFlow(void)
{
  struct XyzMaterialSource sources[XYZ_MAX_SOURCES];
  struct XyzMaterialSource selected[XYZ_MAX_SOURCES];
  u16 targets[EXTRA_DECK_SIZE];
  u8 sourceCount;
  u8 targetCount;
  u8 selectedCount;
  u16 resultId;
  u8 need;
  u8 rank;

  if (!XyzDuel_PlayerCanSummon()) {
    PlayMusic(SFX_FORBIDDEN);
    return;
  }

  sourceCount = XyzDuel_CollectFaceUpFieldSources(sources, XYZ_MAX_SOURCES);
  targetCount = XyzDuel_BuildFeasibleExtraDeckTargets(sources, sourceCount, targets, EXTRA_DECK_SIZE);
  if (targetCount == 0) {
    PlayMusic(SFX_FORBIDDEN);
    return;
  }

  resultId = XyzDuel_PlayerPickTarget(targets, targetCount);
  if (resultId == CARD_NONE)
    return;

  need = Card_XyzMaterialCount(resultId);
  rank = CardLevel(resultId);
  selectedCount = XyzDuel_SelectMaterialsForRank(sources, sourceCount, rank, need, selected,
                                                XYZ_MAX_SOURCES);
  if (selectedCount < need) {
    PlayMusic(SFX_FORBIDDEN);
    return;
  }

  PlayMusic(SFX_SELECT);
  XyzDuel_Execute(resultId, selected, selectedCount);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void XyzDuel_SelfCheck(void)
{
  struct XyzMaterialSource sources[3];
  struct XyzMaterialSource selected[3];
  u8 n;

  sources[0].zone = NULL;
  sources[0].cardId = MYSTICAL_ELF;
  sources[0].level = 4;
  sources[1].zone = NULL;
  sources[1].cardId = BATTLE_OX;
  sources[1].level = 4;
  sources[2].zone = NULL;
  sources[2].cardId = CELTIC_GUARDIAN;
  sources[2].level = 4;

  if (!XyzDuel_CanMakeRank(sources, 3, 4, 3))
    while (1)
      ;
  if (XyzDuel_CanMakeRank(sources, 2, 4, 3))
    while (1)
      ;
  n = XyzDuel_SelectMaterialsForRank(sources, 3, 4, 3, selected, 3);
  if (n != 3)
    while (1)
      ;
  if (Card_XyzMaterialCount(GAGAGIGO_THE_RISEN) != 3)
    while (1)
      ;
}
#endif
