#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel.h"
#include "duel_helpers.h"
#include "elemental_hero_electrum.h"
#include "elemental_hero_great_tornado.h"
#include "elemental_hero_gaia.h"
#include "elemental_hero_necroid_shaman.h"
#include "elemental_hero_absolute_zero.h"
#include "elemental_hero_sunrise.h"
#include "chimeratech_overdragon.h"
#include "expanded_graveyard.h"
#include "cybernetic_fusion_support.h"
#include "amazoness_secret_arts.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "power_bond.h"
#include "spell_effects.h"
#include "chimeratech_fusion_stats.h"
#include "evil_hero_dark_gaia.h"
#include "fusion_recipes.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyardDuelist);
void UpdateDuelGfxExceptField(void);

#define FUSION_PICK_MENU_CAPACITY ((u8)ARRAY_COUNT(gDeckMenu.cards))

static const u8 sFusionDuelPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_FUSION_SUMMON,
};

static const u8 sFusionMaterialPickLabelsRequired[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

/* After minimum materials: Select Card adds one, Fusion Summon finishes. */
static const u8 sFusionMaterialPickLabelsOptional[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
  DECK_MENU_PICK_LABEL_FUSION_SUMMON,
};

#define OVERDRAGON_PICK_ABORT (-1)
#define OVERDRAGON_PICK_DONE (-2)

static void FusionDuel_LoadPickMenu(const u8 *recipeIndices, u8 count)
{
  u8 j;

  for (j = 0; j < FUSION_PICK_MENU_CAPACITY; j++)
    gDeckMenu.cards[j] = CARD_NONE;
  for (j = 0; j < count; j++)
    gDeckMenu.cards[j] = gFusionRecipes[recipeIndices[j]].result;

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;
}

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_OPPONENT])
    return DUEL_OPPONENT;
  return DUEL_PLAYER;
}

static u8 MaterialMatches(u16 need, u16 have, struct DuelCard *zone)
{
  u16 effective = Duel_GetEffectiveCardId(zone);

  if (zone == NULL)
    effective = have;

  if ((need & ~FUSION_RECIPE_ATTRIBUTE_VALUE_MASK) == FUSION_RECIPE_ATTRIBUTE_BASE) {
    u8 declared = NepheShaddollFusion_GetDeclaredAttribute(zone);
    u8 want = (u8)(need & FUSION_RECIPE_ATTRIBUTE_VALUE_MASK);

    if (declared != 0)
      return declared == want;
  }

  return FusionRecipe_MaterialMatches(need, effective);
}

static void AddSource(struct FusionMaterialSource *out, u8 *count, u8 maxOut, struct DuelCard *zone,
                    u8 gyIndex, u16 cardId)
{
  if (*count >= maxOut || cardId == CARD_NONE)
    return;

  out[*count].zone = zone;
  out[*count].gyIndex = gyIndex;
  out[*count].cardId = cardId;
  (*count)++;
}

u8 FusionDuel_CollectHandAndFieldSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 count = 0;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnHands[ACTIVE_DUELIST][i];
    if (zone->id != CARD_NONE && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
      AddSource(out, &count, maxOut, zone, FUSION_GY_INDEX_NONE, zone->id);
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];
    if (zone->id != CARD_NONE && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
      AddSource(out, &count, maxOut, zone, FUSION_GY_INDEX_NONE, zone->id);
  }

  return AmazonessSecretArts_AppendExtraDeckSources(out, count, maxOut);
}

u8 FusionDuel_CollectFieldAndGraveyardSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 count = 0;
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 gyCount;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];
    if (zone->id != CARD_NONE && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
      AddSource(out, &count, maxOut, zone, FUSION_GY_INDEX_NONE, zone->id);
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER)
      AddSource(out, &count, maxOut, NULL, i, cardId);
  }

  return count;
}

u8 FusionDuel_CollectHandFieldAndGraveyardSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 count = FusionDuel_CollectHandAndFieldSources(out, maxOut);
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 gyCount;
  u8 i;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER)
      AddSource(out, &count, maxOut, NULL, i, cardId);
  }

  return count;
}

u8 FusionDuel_CollectFusionSpellSources(struct FusionMaterialSource *out, u8 maxOut)
{
  if (IsCyberneticFusionSupportActive())
    return FusionDuel_CollectHandFieldAndGraveyardSources(out, maxOut);

  return FusionDuel_CollectHandAndFieldSources(out, maxOut);
}

u8 FusionDuel_CollectGraveyardElementalHeroSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 gyCount;
  u8 count = 0;
  u8 i;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;
    if (!Duel_IsElementalHeroCard(cardId))
      continue;
    AddSource(out, &count, maxOut, NULL, i, cardId);
  }

  return count;
}

u8 FusionDuel_CollectDeckSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 count = 0;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;
    AddSource(out, &count, maxOut, NULL, i, cardId);
  }

  return count;
}

static u8 SourceQualifiesAsFusionMaterial(const struct FusionRecipe *recipe,
                                        const struct FusionMaterialSource *source)
{
  if (recipe == NULL || source == NULL)
    return FALSE;

  /* ponytail: hand test copies of the fusion result are not valid materials. */
  if (source->cardId == recipe->result)
    return FALSE;

  return TRUE;
}

static u8 SourceAttribute(const struct FusionMaterialSource *source)
{
  u16 cardId;
  u8 declared;

  if (source == NULL)
    return 0;

  declared = NepheShaddollFusion_GetDeclaredAttribute(source->zone);
  if (declared != 0)
    return declared;

  cardId = source->cardId;
  if (source->zone != NULL)
    cardId = Duel_GetEffectiveCardId(source->zone);

  if (cardId == CARD_NONE)
    return 0;

  return gCardData_NEW[cardId].attribute;
}

static u16 SunriseSourceCardId(const struct FusionMaterialSource *source)
{
  if (source == NULL)
    return CARD_NONE;

  if (source->zone != NULL)
    return Duel_GetEffectiveCardId(source->zone);

  return source->cardId;
}

static u8 SunriseSourceIsEligibleHero(const struct FusionMaterialSource *source)
{
  u16 cardId = SunriseSourceCardId(source);

  if (cardId == CARD_NONE || cardId == ELEMENTAL_HERO_SUNRISE)
    return FALSE;

  return Duel_IsElementalHeroCard(cardId);
}

static u8 SunriseMaterialsFeasible(const struct FusionMaterialSource *sources, u8 sourceCount)
{
  u8 i;
  u8 j;

  for (i = 0; i < sourceCount; i++) {
    if (!SunriseSourceIsEligibleHero(&sources[i]))
      continue;

    for (j = i + 1; j < sourceCount; j++) {
      if (!SunriseSourceIsEligibleHero(&sources[j]))
        continue;
      if (SourceAttribute(&sources[i]) != SourceAttribute(&sources[j]))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 SunriseSelectSources(const struct FusionMaterialSource *sources, u8 sourceCount,
                               struct FusionMaterialSource *selected, u8 maxSelected)
{
  u8 i;
  u8 j;

  if (maxSelected < 2)
    return 0;

  for (i = 0; i < sourceCount; i++) {
    if (!SunriseSourceIsEligibleHero(&sources[i]))
      continue;

    for (j = i + 1; j < sourceCount; j++) {
      if (!SunriseSourceIsEligibleHero(&sources[j]))
        continue;
      if (SourceAttribute(&sources[i]) == SourceAttribute(&sources[j]))
        continue;

      selected[0] = sources[i];
      selected[1] = sources[j];
      return 2;
    }
  }

  return 0;
}

static u16 OverdragonSourceCardId(const struct FusionMaterialSource *source)
{
  if (source == NULL)
    return CARD_NONE;

  if (source->zone != NULL)
    return source->zone->id;

  return source->cardId;
}

/* Proto-Cyber Dragon is treated as Cyber Dragon only while on the field. */
static u8 OverdragonSourceIsCyberDragon(const struct FusionMaterialSource *source)
{
  u16 cardId = OverdragonSourceCardId(source);

  if (cardId == CYBER_DRAGON)
    return TRUE;

  if (cardId == PROTO_CYBER_DRAGON && source->zone != NULL)
    return TRUE;

  return FALSE;
}

static u8 OverdragonSourceIsMachine(const struct FusionMaterialSource *source)
{
  u16 cardId = OverdragonSourceCardId(source);

  if (cardId == CARD_NONE || cardId == CHIMERATECH_OVERDRAGON)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_MACHINE);
}

static u8 OverdragonMaterialsFeasible(const struct FusionMaterialSource *sources, u8 sourceCount)
{
  u8 i;
  u8 cyberIdx = 0xFF;
  u8 machineCount = 0;

  for (i = 0; i < sourceCount; i++) {
    if (cyberIdx == 0xFF && OverdragonSourceIsCyberDragon(&sources[i]))
      cyberIdx = i;
  }

  if (cyberIdx == 0xFF)
    return FALSE;

  for (i = 0; i < sourceCount; i++) {
    if (i == cyberIdx)
      continue;
    if (OverdragonSourceIsMachine(&sources[i]))
      machineCount++;
  }

  return machineCount >= 1;
}

typedef u8 (*OverdragonSourcePred)(const struct FusionMaterialSource *source);

static u8 OverdragonCountMatching(const struct FusionMaterialSource *sources, u8 sourceCount,
                                  const u8 *used, OverdragonSourcePred pred)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < sourceCount; i++) {
    if (used[i])
      continue;
    if (pred(&sources[i]))
      count++;
  }

  return count;
}

/* Greedy max for AI. */
static u8 OverdragonSelectSourcesAuto(const struct FusionMaterialSource *sources, u8 sourceCount,
                                      struct FusionMaterialSource *selected, u8 maxSelected)
{
  u8 i;
  u8 cyberIdx = 0xFF;
  u8 out = 0;
  u8 used[FUSION_MAX_SOURCES];

  if (maxSelected < 2)
    return 0;

  for (i = 0; i < FUSION_MAX_SOURCES; i++)
    used[i] = FALSE;

  for (i = 0; i < sourceCount; i++) {
    if (OverdragonSourceIsCyberDragon(&sources[i])) {
      cyberIdx = i;
      break;
    }
  }

  if (cyberIdx == 0xFF)
    return 0;

  selected[out++] = sources[cyberIdx];
  used[cyberIdx] = TRUE;

  for (i = 0; i < sourceCount && out < maxSelected; i++) {
    if (used[i])
      continue;
    if (!OverdragonSourceIsMachine(&sources[i]))
      continue;

    selected[out++] = sources[i];
    used[i] = TRUE;
  }

  if (out < 2)
    return 0;

  return out;
}

/* Returns source index, OVERDRAGON_PICK_DONE, or OVERDRAGON_PICK_ABORT.
 * required: Details + Select Card; single candidate auto-picked; cancel aborts.
 * optional: Details + Select Card + Fusion Summon (finish without adding more). */
static s8 OverdragonPlayerPickSource(const struct FusionMaterialSource *sources, u8 sourceCount,
                                     const u8 *used, OverdragonSourcePred pred, u8 required)
{
  u8 sourceIndexMap[FUSION_MAX_SOURCES];
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 menuCount = 0;
  u8 i;
  u8 j;
  u8 action;
  u8 currentPos;

  for (i = 0; i < sourceCount; i++) {
    if (used[i])
      continue;
    if (!pred(&sources[i]))
      continue;

    sourceIndexMap[menuCount] = i;
    menuCount++;
  }

  if (menuCount == 0)
    return required ? OVERDRAGON_PICK_ABORT : OVERDRAGON_PICK_DONE;

  if (required && menuCount == 1)
    return (s8)sourceIndexMap[0];

  DECKMENU_SAVE();

  for (i = 0; i < FUSION_PICK_MENU_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < menuCount && i < FUSION_PICK_MENU_CAPACITY; i++)
    gDeckMenu.cards[i] = OverdragonSourceCardId(&sources[sourceIndexMap[i]]);

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;

  if (required) {
    action = DeckMenuMainPickChosenLabel(sFusionMaterialPickLabelsRequired,
                                         ARRAY_COUNT(sFusionMaterialPickLabelsRequired));
  } else {
    action = DeckMenuMainPickChosenLabel(sFusionMaterialPickLabelsOptional,
                                         ARRAY_COUNT(sFusionMaterialPickLabelsOptional));
  }

  currentPos = gDeckMenu.currentPos;

  DECKMENU_RESTORE();

  if (action == DECK_MENU_PICK_LABEL_FUSION_SUMMON)
    return OVERDRAGON_PICK_DONE;

  if (action != DECK_MENU_PICK_LABEL_SELECT_CARD)
    return OVERDRAGON_PICK_ABORT;

  if (currentPos >= menuCount)
    return OVERDRAGON_PICK_ABORT;

  return (s8)sourceIndexMap[currentPos];
}

static u8 OverdragonSelectSourcesPlayer(const struct FusionMaterialSource *sources, u8 sourceCount,
                                        struct FusionMaterialSource *selected, u8 maxSelected)
{
  u8 used[FUSION_MAX_SOURCES];
  u8 out = 0;
  s8 pick;
  u8 i;

  if (maxSelected < 2 || sources == NULL || selected == NULL)
    return 0;

  for (i = 0; i < FUSION_MAX_SOURCES; i++)
    used[i] = FALSE;

  /* Caller must bracket with DeckMenu_Begin/EndDuelTrunkView when needed. */
  pick = OverdragonPlayerPickSource(sources, sourceCount, used, OverdragonSourceIsCyberDragon,
                                    TRUE);
  if (pick < 0)
    return 0;

  selected[out++] = sources[pick];
  used[pick] = TRUE;

  pick = OverdragonPlayerPickSource(sources, sourceCount, used, OverdragonSourceIsMachine, TRUE);
  if (pick < 0)
    return 0;

  selected[out++] = sources[pick];
  used[pick] = TRUE;

  /* Further Machines optional: Select Card adds one, Fusion Summon finishes. */
  while (out < maxSelected
         && OverdragonCountMatching(sources, sourceCount, used, OverdragonSourceIsMachine) > 0) {
    pick = OverdragonPlayerPickSource(sources, sourceCount, used, OverdragonSourceIsMachine,
                                      FALSE);
    if (pick == OVERDRAGON_PICK_DONE)
      break;
    if (pick < 0)
      return 0;

    selected[out++] = sources[pick];
    used[pick] = TRUE;
  }

  return out;
}

u8 FusionDuel_SelectOverdragonMaterials(const struct FusionMaterialSource *sources,
                                        u8 sourceCount,
                                        struct FusionMaterialSource *selected,
                                        u8 maxSelected, u8 playerControlled)
{
  if (playerControlled)
    return OverdragonSelectSourcesPlayer(sources, sourceCount, selected, maxSelected);

  return OverdragonSelectSourcesAuto(sources, sourceCount, selected, maxSelected);
}

u8 FusionRecipe_SelectedCountIsValid(const struct FusionRecipe *recipe, u8 selectedCount)
{
  if (recipe == NULL)
    return FALSE;

  if (recipe->result == CHIMERATECH_OVERDRAGON)
    return selectedCount >= 2 && selectedCount <= FUSION_MAX_MATERIALS;

  return selectedCount == FusionRecipe_MaterialCount(recipe);
}

u8 FusionRecipe_IsFeasibleWithSources(const struct FusionRecipe *recipe,
                                      const struct FusionMaterialSource *sources,
                                      u8 sourceCount)
{
  u8 used[FUSION_MAX_SOURCES];
  u8 matCount;
  u8 m;
  u8 i;

  if (recipe == NULL || recipe->result == CARD_NONE)
    return FALSE;

  if (recipe->result == ELEMENTAL_HERO_SUNRISE)
    return SunriseMaterialsFeasible(sources, sourceCount);

  if (recipe->result == CHIMERATECH_OVERDRAGON)
    return OverdragonMaterialsFeasible(sources, sourceCount);

  matCount = FusionRecipe_MaterialCount(recipe);
  if (matCount < 2 || sourceCount < matCount)
    return FALSE;

  for (i = 0; i < FUSION_MAX_SOURCES; i++)
    used[i] = FALSE;

  for (m = 0; m < matCount; m++) {
    u16 need = FusionRecipe_MaterialAt(recipe, m);
    u8 found = FALSE;

    for (i = 0; i < sourceCount; i++) {
      if (used[i])
        continue;
      if (!SourceQualifiesAsFusionMaterial(recipe, &sources[i]))
        continue;
      if (MaterialMatches(need, sources[i].cardId, sources[i].zone)) {
        used[i] = TRUE;
        found = TRUE;
        break;
      }
    }

    if (!found)
      return FALSE;
  }

  return TRUE;
}

u8 FusionRecipe_SelectSources(const struct FusionRecipe *recipe,
                              const struct FusionMaterialSource *sources, u8 sourceCount,
                              struct FusionMaterialSource *selected, u8 maxSelected)
{
  u8 used[FUSION_MAX_SOURCES];
  u8 matCount;
  u8 m;
  u8 i;
  u8 out = 0;

  if (recipe == NULL || selected == NULL)
    return 0;

  if (recipe->result == ELEMENTAL_HERO_SUNRISE)
    return SunriseSelectSources(sources, sourceCount, selected, maxSelected);

  if (recipe->result == CHIMERATECH_OVERDRAGON)
    return OverdragonSelectSourcesAuto(sources, sourceCount, selected, maxSelected);

  matCount = FusionRecipe_MaterialCount(recipe);
  if (maxSelected < matCount)
    return 0;

  for (i = 0; i < FUSION_MAX_SOURCES; i++)
    used[i] = FALSE;

  for (m = 0; m < matCount; m++) {
    u16 need = FusionRecipe_MaterialAt(recipe, m);
    u8 found = FALSE;

    for (i = 0; i < sourceCount; i++) {
      if (used[i])
        continue;
      if (!SourceQualifiesAsFusionMaterial(recipe, &sources[i]))
        continue;
      if (MaterialMatches(need, sources[i].cardId, sources[i].zone)) {
        used[i] = TRUE;
        selected[out++] = sources[i];
        found = TRUE;
        break;
      }
    }

    if (!found)
      return 0;
  }

  return out;
}

u8 FusionDuel_BuildFeasibleRecipeIndices(const struct FusionMaterialSource *sources,
                                         u8 sourceCount, u8 *outIndices, u8 maxOut,
                                         FusionRecipeFilterFn filter)
{
  u8 count = 0;
  u8 i;
  u8 recipeCount = FusionRecipe_Count();

  for (i = 0; i < recipeCount; i++) {
    const struct FusionRecipe *recipe = &gFusionRecipes[i];

    if (filter != NULL && !filter(recipe))
      continue;
    if (!FusionRecipe_IsFeasibleWithSources(recipe, sources, sourceCount))
      continue;
    if (count >= maxOut)
      break;

    outIndices[count++] = i;
  }

  return count;
}

const struct FusionRecipe *FusionDuel_PlayerPickRecipe(const u8 *recipeIndices, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 j;
  u16 chosenId;
  u8 chosenRecipeIdx = 0xFF;

  if (recipeIndices == NULL || count == 0)
    return NULL;

  if (count == 1)
    return &gFusionRecipes[recipeIndices[0]];

  DECKMENU_SAVE();

  FusionDuel_LoadPickMenu(recipeIndices, count);

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sFusionDuelPickLabels, ARRAY_COUNT(sFusionDuelPickLabels))) {
    DECKMENU_RESTORE();

    DeckMenu_EndDuelTrunkView();
    return NULL;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  for (j = 0; j < count; j++) {
    if (gFusionRecipes[recipeIndices[j]].result == chosenId) {
      chosenRecipeIdx = recipeIndices[j];
      break;
    }
  }

  DECKMENU_RESTORE();

  DeckMenu_EndDuelTrunkView();

  if (chosenRecipeIdx == 0xFF)
    return NULL;

  return &gFusionRecipes[chosenRecipeIdx];
}

const struct FusionRecipe *FusionDuel_PlayerConfirmFusionPick(const u8 *recipeIndices, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 j;
  u16 chosenId;
  u8 chosenRecipeIdx = 0xFF;
  u8 filteredRecipeIndices[50]; /* ponytail: enough for all recipes (~33 as of writing) */

  if (recipeIndices == NULL || count == 0)
    return NULL;

  /* If the extra deck system is enabled, only show fusion monsters
   * that are actually present in the player's extra deck. */
  if (gRuntimeConfig.enable_extra_deck) {
    u8 i;
    u16 *extra;
    u8 active;
    u8 filteredCount;

    active = gActiveDeckIndex;
    if (active >= PLAYER_DECK_INDEX_MIN && active <= PLAYER_DECK_INDEX_MAX) {
      switch (active) {
      case 1: extra = gPlayerDeck1ExtraDeck; break;
      case 2: extra = gPlayerDeck2ExtraDeck; break;
      case 3: extra = gPlayerDeck3ExtraDeck; break;
      default: extra = gPlayerDeck1ExtraDeck; break;
      }
    } else {
      extra = gPlayerDeck1ExtraDeck;
    }

    filteredCount = 0;
    for (i = 0; i < count; i++) {
      u16 result = gFusionRecipes[recipeIndices[i]].result;
      u8 found = FALSE;
      u8 k;

      for (k = 0; k < EXTRA_DECK_SIZE; k++) {
        if (extra[k] == result) {
          found = TRUE;
          break;
        }
      }

      if (found)
        filteredRecipeIndices[filteredCount++] = recipeIndices[i];
    }

    if (filteredCount == 0)
      return NULL;

    count = filteredCount;
    recipeIndices = filteredRecipeIndices;
  }

  DECKMENU_SAVE();

  FusionDuel_LoadPickMenu(recipeIndices, count);

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sFusionDuelPickLabels, ARRAY_COUNT(sFusionDuelPickLabels))) {
    DECKMENU_RESTORE();

    DeckMenu_EndDuelTrunkView();
    return NULL;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  for (j = 0; j < count; j++) {
    if (gFusionRecipes[recipeIndices[j]].result == chosenId) {
      chosenRecipeIdx = recipeIndices[j];
      break;
    }
  }

  DECKMENU_RESTORE();

  DeckMenu_EndDuelTrunkView();

  if (chosenRecipeIdx == 0xFF)
    return NULL;

  return &gFusionRecipes[chosenRecipeIdx];
}

static void PayPolymerizationMaterials(const struct FusionMaterialSource *selected, u8 selectedCount)
{
  u8 i;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].zone != NULL)
      ClearZoneAndSendMonToGraveyard(selected[i].zone, ACTIVE_DUELIST);
    else if (AmazonessSecretArts_IsExtraDeckSource(&selected[i]))
      AmazonessSecretArts_PayExtraDeckSource(&selected[i]);
  }
}

static void PayMiracleFusionMaterials(const struct FusionMaterialSource *selected, u8 selectedCount)
{
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 gyIndices[FUSION_MAX_MATERIALS];
  u8 gyCount = 0;
  u8 i;
  u8 g;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].zone != NULL)
      Duel_BanishZone(selected[i].zone, FALSE);
    else if (selected[i].gyIndex != FUSION_GY_INDEX_NONE)
      gyIndices[gyCount++] = selected[i].gyIndex;
  }

  while (gyCount > 0) {
    u8 best = 0;
    for (g = 1; g < gyCount; g++) {
      if (gyIndices[g] > gyIndices[best])
        best = g;
    }
    Duel_BanishGraveyardAtFixed(fixedDuelist, gyIndices[best]);
    gyIndices[best] = gyIndices[gyCount - 1];
    gyCount--;
  }
}

void FusionDuel_SpecialSummonResult(u16 resultId, u8 materialCount)
{
  struct DuelSummonOpts opts;
  u8 i;

  opts = Duel_DefaultSpecialSummonOpts(FALSE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, resultId, opts);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];
    if (zone->id == resultId && zone->isFaceUp) {
      /* Great Tornado's halving is continuous while face-up on the field. */
      if (resultId != ELEMENTAL_HERO_GREAT_TORNADO
          && resultId != ELEMENTAL_HERO_ABSOLUTE_ZERO
          && resultId != ELEMENTAL_HERO_GAIA
          && resultId != ELEMENTAL_HERO_NECROID_SHAMAN
          && resultId != CHIMERATECH_OVERDRAGON
          && resultId != CHIMERATECH_FORTRESS_DRAGON
          && resultId != CHIMERATECH_MEGAFLEET_DRAGON)
        FlipCardFaceDown(zone);
      if (resultId == CHIMERATECH_FORTRESS_DRAGON
          || resultId == CHIMERATECH_MEGAFLEET_DRAGON)
        ChimeratechFusion_StampMaterialCount(zone, materialCount);
      break;
    }
  }

  UpdateDuelGfxExceptField();

  if (resultId == ELEMENTAL_HERO_ELECTRUM)
    ElementalHeroElectrum_OnFusionSummoned();

  if (resultId == ELEMENTAL_HERO_GREAT_TORNADO)
    ElementalHeroGreatTornado_OnFusionSummoned();

  if (resultId == ELEMENTAL_HERO_GAIA)
    ElementalHeroGaia_OnFusionSummoned();

  if (resultId == ELEMENTAL_HERO_NECROID_SHAMAN)
    ElementalHeroNecroidShaman_OnFusionSummoned();

  if (resultId == ELEMENTAL_HERO_SUNRISE)
    ElementalHeroSunrise_OnFusionSummoned();

  if (resultId == CHIMERATECH_OVERDRAGON)
    ChimeratechOverdragon_OnFusionSummoned(materialCount);
}

static enum DuelActionResult ExecuteFusionRecipe(const struct FusionRecipe *recipe,
                                                 const struct FusionMaterialSource *sources,
                                                 u8 sourceCount, u16 spellCardId,
                                                 void (*payMaterials)(const struct FusionMaterialSource *,
                                                                      u8),
                                                 u8 showEffectText)
{
  struct FusionMaterialSource selected[FUSION_MAX_MATERIALS];
  u8 selectedCount;
  s8 emptyZone;
  u16 darkGaiaFusionAtk = 0;
  u8 i;

  if (recipe == NULL || payMaterials == NULL)
    return DUEL_ACTION_INVALID;

  if (recipe->result == CHIMERATECH_OVERDRAGON) {
    u8 playerPick = WhoseTurn() == DUEL_PLAYER;

    if (playerPick)
      DeckMenu_BeginDuelTrunkView();
    selectedCount = FusionDuel_SelectOverdragonMaterials(
        sources, sourceCount, selected, FUSION_MAX_MATERIALS, playerPick);
    if (playerPick)
      DeckMenu_EndDuelTrunkView();
  } else {
    selectedCount = FusionRecipe_SelectSources(recipe, sources, sourceCount, selected,
                                               FUSION_MAX_MATERIALS);
  }
  if (!FusionRecipe_SelectedCountIsValid(recipe, selectedCount))
    return DUEL_ACTION_NO_TARGET;

  if (recipe->result == EVIL_HERO_DARK_GAIA) {
    for (i = 0; i < selectedCount; i++)
      darkGaiaFusionAtk = (u16)(darkGaiaFusionAtk + gCardData_NEW[selected[i].cardId].atk);
  }

  emptyZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (emptyZone < 0)
    return DUEL_ACTION_NO_ZONE;

  if (showEffectText) {
    Duel_ShowEffectText(spellCardId);
    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  ElementalHeroAbsoluteZero_BeginSuppressLeave();
  payMaterials(selected, selectedCount);
  ClearZoneAndSendMonToGraveyard(
      gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);
  FusionDuel_SpecialSummonResult(recipe->result, selectedCount);
  if (recipe->result == EVIL_HERO_DARK_GAIA)
    EvilHeroDarkGaia_StampFusionMaterialAtk(darkGaiaFusionAtk);
  ElementalHeroAbsoluteZero_EndSuppressLeave();
  return DUEL_ACTION_OK;
}

void FusionDuel_ExecutePolymerization(const struct FusionRecipe *recipe,
                                    const struct FusionMaterialSource *sources,
                                    u8 sourceCount, u16 spellCardId, u8 showEffectText)
{
  enum DuelActionResult result;
  u8 useCybernetic = IsCyberneticFusionSupportActive();

  /* ponytail: CFS makes materials banish from hand/field/GY for this fusion only. */
  result = ExecuteFusionRecipe(recipe, sources, sourceCount, spellCardId,
                               useCybernetic ? PayMiracleFusionMaterials
                                             : PayPolymerizationMaterials,
                               showEffectText);
  if (useCybernetic && result == DUEL_ACTION_OK)
    ClearCyberneticFusionSupport();
}

void FusionDuel_ExecuteMiracleFusion(const struct FusionRecipe *recipe,
                                     const struct FusionMaterialSource *sources,
                                     u8 sourceCount, u16 spellCardId, u8 showEffectText)
{
  ExecuteFusionRecipe(recipe, sources, sourceCount, spellCardId, PayMiracleFusionMaterials,
                      showEffectText);
}

void FusionDuel_ExecutePowerBond(const struct FusionRecipe *recipe,
                                 const struct FusionMaterialSource *sources,
                                 u8 sourceCount, u16 spellCardId, u8 showEffectText)
{
  enum DuelActionResult result;

  result = ExecuteFusionRecipe(recipe, sources, sourceCount, spellCardId,
                               PayPolymerizationMaterials, showEffectText);
  if (result == DUEL_ACTION_OK && recipe != NULL)
    PowerBond_OnFusionSummoned(recipe->result);
}

s8 FusionDuel_AiPickBestRecipeIndex(const struct FusionMaterialSource *sources,
                                    u8 sourceCount, FusionRecipeFilterFn filter)
{
  u8 i;
  u16 bestAtk = 0;
  s8 bestIdx = -1;
  u8 recipeCount = FusionRecipe_Count();

  for (i = 0; i < recipeCount; i++) {
    const struct FusionRecipe *recipe = &gFusionRecipes[i];
    u16 candidateAtk;

    if (filter != NULL && !filter(recipe))
      continue;
    if (!FusionRecipe_IsFeasibleWithSources(recipe, sources, sourceCount))
      continue;

    if (recipe->result == CHIMERATECH_OVERDRAGON) {
      u8 selectedCount;
      struct FusionMaterialSource selected[FUSION_MAX_MATERIALS];

      selectedCount = FusionRecipe_SelectSources(recipe, sources, sourceCount, selected,
                                                 FUSION_MAX_MATERIALS);
      candidateAtk = ChimeratechOverdragon_EstimateAtk(selectedCount);
    } else {
      SetCardInfo(recipe->result);
      candidateAtk = gCardInfo.atk;
    }

    if (bestIdx < 0 || candidateAtk > bestAtk) {
      bestIdx = (s8)i;
      bestAtk = candidateAtk;
    }
  }

  return bestIdx;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void FusionDuel_SelfCheck(void)
{
  const struct FusionRecipe *recipe = FusionRecipe_FindByResult(ELEMENTAL_HERO_ABSOLUTE_ZERO);
  struct FusionMaterialSource sources[4];
  struct FusionMaterialSource selected[2];
  u8 selectedCount;

  if (recipe == NULL)
    while (1)
      ;

  sources[0].zone = NULL;
  sources[0].gyIndex = FUSION_GY_INDEX_NONE;
  sources[0].cardId = ELEMENTAL_HERO_ABSOLUTE_ZERO;
  sources[1].zone = NULL;
  sources[1].gyIndex = FUSION_GY_INDEX_NONE;
  sources[1].cardId = ELEMENTAL_HERO_OCEAN;

  if (FusionRecipe_IsFeasibleWithSources(recipe, sources, 2))
    while (1)
      ;

  sources[0].cardId = ELEMENTAL_HERO_AVIAN;
  if (!FusionRecipe_IsFeasibleWithSources(recipe, sources, 2))
    while (1)
      ;

  selectedCount = FusionRecipe_SelectSources(recipe, sources, 2, selected, 2);
  if (selectedCount != 2)
    while (1)
      ;

  if (selected[0].cardId == ELEMENTAL_HERO_ABSOLUTE_ZERO
      || selected[1].cardId == ELEMENTAL_HERO_ABSOLUTE_ZERO)
    while (1)
      ;

  recipe = FusionRecipe_FindByResult(CHIMERATECH_OVERDRAGON);
  if (recipe == NULL)
    while (1)
      ;

  sources[0].cardId = CYBER_DRAGON;
  sources[1].cardId = BATTLE_FOOTBALLER;
  sources[2].zone = NULL;
  sources[2].gyIndex = FUSION_GY_INDEX_NONE;
  sources[2].cardId = CYBER_DRAGON;
  sources[3].zone = NULL;
  sources[3].gyIndex = FUSION_GY_INDEX_NONE;
  sources[3].cardId = PROTO_CYBER_DRAGON;

  if (!FusionRecipe_IsFeasibleWithSources(recipe, sources, 4))
    while (1)
      ;

  {
    struct FusionMaterialSource overSelected[FUSION_MAX_MATERIALS];

    selectedCount = FusionRecipe_SelectSources(recipe, sources, 4, overSelected,
                                               FUSION_MAX_MATERIALS);
    if (selectedCount != 4)
      while (1)
        ;

    if (!FusionRecipe_SelectedCountIsValid(recipe, selectedCount))
      while (1)
        ;
  }

  sources[0].cardId = ELEMENTAL_HERO_AVIAN;
  sources[1].cardId = BATTLE_FOOTBALLER;
  if (FusionRecipe_IsFeasibleWithSources(recipe, sources, 2))
    while (1)
      ;
}
#endif
