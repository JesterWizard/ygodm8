#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel.h"
#include "duel_helpers.h"
#include "player_decks.h"
#include "synchro_duel.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyardDuelist);
void UpdateDuelGfxExceptField(void);
void PlayMusic(int);

extern const u8 gCardIsTuner_Hook[];
extern const CardData gCardData_NEW[];

#define SYNCHRO_PICK_MENU_CAPACITY ((u8)ARRAY_COUNT(gDeckMenu.cards))

static const u8 sSynchroDuelPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SYNCHRO_SUMMON,
};

u8 Card_IsTuner(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;
  return gCardIsTuner_Hook[cardId] != 0;
}

static u8 CardLevel(u16 cardId)
{
  return gCardData_NEW[cardId].level;
}

static u8 CardIsSynchro(u16 cardId)
{
  return gCardData_NEW[cardId].color == COLOR_SYNCHRO;
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

/* ponytail: ATK monsters keep isFaceUp=0 until EOT FlipAtkPosCardsFaceUp.
 * Face-down sets are isDefending+!isFaceUp; those stay illegal materials. */
static u8 ZoneIsFaceUpForSynchro(const struct DuelCard *zone)
{
  return zone->isFaceUp || !zone->isDefending;
}

static void AddSource(struct SynchroMaterialSource *out, u8 *count, u8 maxOut,
                      struct DuelCard *zone)
{
  u16 cardId;

  if (*count >= maxOut || zone == NULL)
    return;

  cardId = zone->id;
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return;
  if (!ZoneIsFaceUpForSynchro(zone))
    return;

  out[*count].zone = zone;
  out[*count].cardId = cardId;
  out[*count].level = CardLevel(cardId);
  out[*count].isTuner = Card_IsTuner(cardId);
  (*count)++;
}

u8 SynchroDuel_CollectFaceUpFieldSources(struct SynchroMaterialSource *out, u8 maxOut)
{
  u8 count = 0;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    AddSource(out, &count, maxOut, gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]);

  return count;
}

/* ponytail: field is at most 5 monsters; 2^4 non-tuner subsets is fine.
 * requiredIndex 0xFF = any; otherwise the mask must include that source. */
static u8 FindNonTunerMaskForNeed(const struct SynchroMaterialSource *sources, u8 sourceCount,
                                  u8 tunerIndex, u8 needLevel, u8 requiredIndex, u16 *outMask)
{
  u8 nonTunerIdx[SYNCHRO_MAX_SOURCES];
  u8 nonTunerCount = 0;
  u16 mask;
  u8 i;

  for (i = 0; i < sourceCount; i++) {
    if (i == tunerIndex)
      continue;
    if (sources[i].isTuner)
      continue;
    nonTunerIdx[nonTunerCount++] = i;
  }

  if (nonTunerCount == 0 || needLevel == 0)
    return FALSE;

  for (mask = 1; mask < (u16)(1u << nonTunerCount); mask++) {
    u8 sum = 0;
    u8 bit;
    u16 sourceMask = 0;

    for (bit = 0; bit < nonTunerCount; bit++) {
      if (mask & (1u << bit)) {
        sum += sources[nonTunerIdx[bit]].level;
        sourceMask |= (u16)(1u << nonTunerIdx[bit]);
      }
    }

    if (sum != needLevel)
      continue;

    sourceMask |= (u16)(1u << tunerIndex);
    if (requiredIndex != 0xFF && !(sourceMask & (u16)(1u << requiredIndex)))
      continue;

    *outMask = sourceMask;
    return TRUE;
  }

  return FALSE;
}

static u8 CanMakeLevelUsingSource(const struct SynchroMaterialSource *sources, u8 sourceCount,
                                  u8 targetLevel, u8 requiredIndex)
{
  u8 i;
  u16 mask;

  if (sources == NULL || sourceCount < 2 || targetLevel == 0)
    return FALSE;

  for (i = 0; i < sourceCount; i++) {
    if (!sources[i].isTuner)
      continue;
    if (sources[i].level >= targetLevel)
      continue;
    if (FindNonTunerMaskForNeed(sources, sourceCount, i, targetLevel - sources[i].level,
                                requiredIndex, &mask))
      return TRUE;
  }

  return FALSE;
}

u8 SynchroDuel_CanMakeLevel(const struct SynchroMaterialSource *sources, u8 sourceCount,
                            u8 targetLevel)
{
  return CanMakeLevelUsingSource(sources, sourceCount, targetLevel, 0xFF);
}

u8 SynchroDuel_SelectMaterialsForLevel(const struct SynchroMaterialSource *sources,
                                       u8 sourceCount, u8 targetLevel,
                                       struct SynchroMaterialSource *selected, u8 maxSelected)
{
  u8 i;
  u16 mask = 0;
  u8 count = 0;
  u8 bit;

  if (selected == NULL || maxSelected == 0)
    return 0;

  for (i = 0; i < sourceCount; i++) {
    if (!sources[i].isTuner)
      continue;
    if (sources[i].level >= targetLevel)
      continue;
    if (FindNonTunerMaskForNeed(sources, sourceCount, i, targetLevel - sources[i].level, 0xFF,
                                &mask))
      break;
  }

  if (mask == 0)
    return 0;

  for (bit = 0; bit < sourceCount && count < maxSelected; bit++) {
    if (mask & (1u << bit))
      selected[count++] = sources[bit];
  }

  return count;
}

u8 SynchroDuel_BuildFeasibleExtraDeckTargets(const struct SynchroMaterialSource *sources,
                                             u8 sourceCount, u16 *outIds, u8 maxOut)
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
    u8 level;
    u8 dup;

    if (cardId == CARD_NONE || !CardIsSynchro(cardId))
      continue;

    level = CardLevel(cardId);
    if (!SynchroDuel_CanMakeLevel(sources, sourceCount, level))
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

static void SynchroDuel_LoadPickMenu(const u16 *targetIds, u8 count)
{
  u8 j;

  for (j = 0; j < SYNCHRO_PICK_MENU_CAPACITY; j++)
    gDeckMenu.cards[j] = CARD_NONE;
  for (j = 0; j < count; j++)
    gDeckMenu.cards[j] = targetIds[j];

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;
}

u16 SynchroDuel_PlayerPickTarget(const u16 *targetIds, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u16 chosenId;

  if (targetIds == NULL || count == 0)
    return CARD_NONE;

  DECKMENU_SAVE();
  SynchroDuel_LoadPickMenu(targetIds, count);
  DeckMenu_BeginDuelTrunkView();

  if (!DeckMenuMainPickConfirmWithLabels(sSynchroDuelPickLabels,
                                         ARRAY_COUNT(sSynchroDuelPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return CARD_NONE;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenId;
}

void SynchroDuel_Execute(u16 resultId, const struct SynchroMaterialSource *selected,
                         u8 selectedCount)
{
  struct DuelSummonOpts opts;
  u8 i;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].zone != NULL)
      ClearZoneAndSendMonToGraveyard(selected[i].zone, ACTIVE_DUELIST);
  }

  opts = Duel_DefaultSpecialSummonOpts(FALSE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, resultId, opts);
  UpdateDuelGfxExceptField();
}

u8 SynchroDuel_PlayerCanSummon(void)
{
  struct SynchroMaterialSource sources[SYNCHRO_MAX_SOURCES];
  u16 targets[EXTRA_DECK_SIZE];
  u8 sourceCount;
  u8 targetCount;

  if (!gRuntimeConfig.enable_extra_deck)
    return FALSE;

  sourceCount = SynchroDuel_CollectFaceUpFieldSources(sources, SYNCHRO_MAX_SOURCES);
  if (sourceCount < 2)
    return FALSE;

  targetCount = SynchroDuel_BuildFeasibleExtraDeckTargets(sources, sourceCount, targets,
                                                         EXTRA_DECK_SIZE);
  return targetCount > 0;
}

u8 SynchroDuel_PlayerCanSummonWithSelected(void)
{
  struct SynchroMaterialSource sources[SYNCHRO_MAX_SOURCES];
  u16 targets[EXTRA_DECK_SIZE];
  struct DuelCard *selected;
  u8 sourceCount;
  u8 targetCount;
  u8 selectedIndex = 0xFF;
  u8 i;

  if (!gRuntimeConfig.enable_extra_deck)
    return FALSE;

  /* Cursor is fixed-POV; menu opens on PLAYER_MONSTER_ROW only. */
  if (gDuelCursor.currentY != PLAYER_MONSTER_ROW)
    return FALSE;

  selected = gFixedZones[PLAYER_MONSTER_ROW][gDuelCursor.currentX];
  if (selected == NULL || selected->id == CARD_NONE || !ZoneIsFaceUpForSynchro(selected))
    return FALSE;

  sourceCount = SynchroDuel_CollectFaceUpFieldSources(sources, SYNCHRO_MAX_SOURCES);
  if (sourceCount < 2)
    return FALSE;

  for (i = 0; i < sourceCount; i++) {
    if (sources[i].zone == selected) {
      selectedIndex = i;
      break;
    }
  }
  if (selectedIndex == 0xFF)
    return FALSE;

  targetCount = SynchroDuel_BuildFeasibleExtraDeckTargets(sources, sourceCount, targets,
                                                         EXTRA_DECK_SIZE);
  for (i = 0; i < targetCount; i++) {
    if (CanMakeLevelUsingSource(sources, sourceCount, CardLevel(targets[i]), selectedIndex))
      return TRUE;
  }

  return FALSE;
}

void SynchroDuel_RunPlayerFlow(void)
{
  struct SynchroMaterialSource sources[SYNCHRO_MAX_SOURCES];
  struct SynchroMaterialSource selected[SYNCHRO_MAX_SOURCES];
  u16 targets[EXTRA_DECK_SIZE];
  u8 sourceCount;
  u8 targetCount;
  u8 selectedCount;
  u16 resultId;
  u8 level;

  if (!SynchroDuel_PlayerCanSummon()) {
    PlayMusic(SFX_FORBIDDEN);
    return;
  }

  sourceCount = SynchroDuel_CollectFaceUpFieldSources(sources, SYNCHRO_MAX_SOURCES);
  targetCount = SynchroDuel_BuildFeasibleExtraDeckTargets(sources, sourceCount, targets,
                                                         EXTRA_DECK_SIZE);
  if (targetCount == 0) {
    PlayMusic(SFX_FORBIDDEN);
    return;
  }

  resultId = SynchroDuel_PlayerPickTarget(targets, targetCount);
  if (resultId == CARD_NONE)
    return;

  level = CardLevel(resultId);
  selectedCount = SynchroDuel_SelectMaterialsForLevel(sources, sourceCount, level, selected,
                                                     SYNCHRO_MAX_SOURCES);
  if (selectedCount < 2) {
    PlayMusic(SFX_FORBIDDEN);
    return;
  }

  PlayMusic(SFX_SELECT);
  SynchroDuel_Execute(resultId, selected, selectedCount);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void SynchroDuel_SelfCheck(void)
{
  struct SynchroMaterialSource sources[2];
  struct SynchroMaterialSource selected[2];
  u8 n;

  sources[0].zone = NULL;
  sources[0].cardId = JUNK_SYNCHRON;
  sources[0].level = 3;
  sources[0].isTuner = TRUE;
  sources[1].zone = NULL;
  sources[1].cardId = CYBER_DRAGON;
  sources[1].level = 5;
  sources[1].isTuner = FALSE;

  if (!SynchroDuel_CanMakeLevel(sources, 2, 8))
    while (1)
      ;
  if (SynchroDuel_CanMakeLevel(sources, 2, 7))
    while (1)
      ;
  n = SynchroDuel_SelectMaterialsForLevel(sources, 2, 8, selected, 2);
  if (n != 2)
    while (1)
      ;
  if (!Card_IsTuner(JUNK_SYNCHRON))
    while (1)
      ;
  if (Card_IsTuner(CYBER_DRAGON))
    while (1)
      ;
}
#endif
