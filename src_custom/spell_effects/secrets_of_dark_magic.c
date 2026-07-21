#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "dynamic_equip.h"
#include "exchange_hand_selection.h"
#include "expanded_graveyard.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"

#define SECRETS_MAX_TRIBUTES 10

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
void UpdateDuelGfxExceptField(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

enum SecretsMode {
  SECRETS_MODE_FUSION = 0,
  SECRETS_MODE_RITUAL,
};

/* Local recipes that list Dark Magician / Dark Magician Girl as material.
 * ponytail: incomplete vs printed DM Fusion pool (Dragon Knight, etc.).
 * Ceiling: Amulet Dragon + The Dark Magicians only; upgrade: add remaining DM
 * Fusion recipes to this table / gFusionRecipes. Wildcard ≈ any Spellcaster. */
static const struct FusionRecipe sSecretsRecipes[] APPEND_RODATA = {
  { AMULET_DRAGON, DARK_MAGICIAN, FUSION_RECIPE_DRAGON, 0, 0 },
  { THE_DARK_MAGICIANS, DARK_MAGICIAN, FUSION_RECIPE_WILDCARD, 0, 0 },
  { THE_DARK_MAGICIANS, DARK_MAGICIAN_GIRL, FUSION_RECIPE_WILDCARD, 0, 0 },
};

static const u8 sSecretsPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 IsDarkMagicianOrGirl(u16 cardId)
{
  return cardId == DARK_MAGICIAN || cardId == DARK_MAGICIAN_GIRL;
}

static u8 RecipeIncludesDarkMagicianMaterial(const struct FusionRecipe *recipe)
{
  u8 i;
  u8 matCount;

  if (recipe == NULL)
    return FALSE;

  SetCardInfo(recipe->result);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  matCount = FusionRecipe_MaterialCount(recipe);
  for (i = 0; i < matCount; i++) {
    if (IsDarkMagicianOrGirl(FusionRecipe_MaterialAt(recipe, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 ExtraDeckHasResult(u16 resultId)
{
  u16 *extra;
  u8 active;
  u8 k;

  if (!gRuntimeConfig.enable_extra_deck)
    return TRUE;

  active = gActiveDeckIndex;
  if (active >= PLAYER_DECK_INDEX_MIN && active <= PLAYER_DECK_INDEX_MAX) {
    switch (active) {
    case 1:
      extra = gPlayerDeck1ExtraDeck;
      break;
    case 2:
      extra = gPlayerDeck2ExtraDeck;
      break;
    case 3:
      extra = gPlayerDeck3ExtraDeck;
      break;
    default:
      extra = gPlayerDeck1ExtraDeck;
      break;
    }
  } else {
    extra = gPlayerDeck1ExtraDeck;
  }

  for (k = 0; k < EXTRA_DECK_SIZE; k++) {
    if (extra[k] == resultId)
      return TRUE;
  }

  return FALSE;
}

static u8 BuildFeasibleSecretsIndices(const struct FusionMaterialSource *sources,
                                      u8 sourceCount, u8 *outIndices, u8 maxOut)
{
  u8 count = 0;
  u8 i;
  u8 recipeCount = ARRAY_COUNT(sSecretsRecipes);

  for (i = 0; i < recipeCount; i++) {
    const struct FusionRecipe *recipe = &sSecretsRecipes[i];

    if (!RecipeIncludesDarkMagicianMaterial(recipe))
      continue;
    if (!FusionRecipe_IsFeasibleWithSources(recipe, sources, sourceCount))
      continue;
    if (!ExtraDeckHasResult(recipe->result))
      continue;
    if (count >= maxOut)
      break;

    outIndices[count++] = i;
  }

  return count;
}

static u8 CanActivateSecretsFusion(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[8];

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  sourceCount = FusionDuel_CollectHandAndFieldSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2)
    return FALSE;

  return BuildFeasibleSecretsIndices(sources, sourceCount, feasibleIndices,
                                     ARRAY_COUNT(feasibleIndices))
         > 0;
}

static u8 IsRitualMonsterCard(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.color == RITUAL_CARD;
}

static u8 MonsterLevel(u16 cardId)
{
  SetCardInfo(cardId);
  return gCardInfo.level;
}

static s8 FindRitualHandZone(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsRitualMonsterCard(handRow[i]->id))
      return (s8)i;
  }

  return -1;
}

static u8 CollectTributeCandidates(s8 ritualHandZone, struct DuelCard **outZones, u8 *outLevels,
                                   u8 *outIsField, u8 *outIsDm, u8 maxOut)
{
  u8 count = 0;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone == NULL || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;
    if (count >= maxOut)
      break;

    outZones[count] = zone;
    outLevels[count] = MonsterLevel(zone->id);
    outIsField[count] = TRUE;
    outIsDm[count] = IsDarkMagicianOrGirl(zone->id);
    count++;
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnHands[ACTIVE_DUELIST][i];

    if ((s8)i == ritualHandZone)
      continue;
    if (zone == NULL || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;
    if (count >= maxOut)
      break;

    outZones[count] = zone;
    outLevels[count] = MonsterLevel(zone->id);
    outIsField[count] = FALSE;
    outIsDm[count] = IsDarkMagicianOrGirl(zone->id);
    count++;
  }

  return count;
}

/* Levels equal or exceed ritual Level; must include DM or DMG. */
static u8 FindSecretsTributeMask(u8 targetLevel, u8 candCount, const u8 *levels,
                                 const u8 *isField, const u8 *isDm, u8 needFieldTribute,
                                 u16 *outMask)
{
  u16 mask;
  u16 maxMask;
  u16 bestMask = 0;
  u8 bestSum = 0xFF;
  u8 found = FALSE;

  if (candCount == 0 || candCount > 15 || targetLevel == 0)
    return FALSE;

  maxMask = (u16)(1u << candCount);
  for (mask = 1; mask < maxMask; mask++) {
    u8 sum = 0;
    u8 i;
    u8 hasField = FALSE;
    u8 hasDm = FALSE;

    for (i = 0; i < candCount; i++) {
      if (!(mask & (1u << i)))
        continue;
      sum += levels[i];
      if (isField[i])
        hasField = TRUE;
      if (isDm[i])
        hasDm = TRUE;
    }

    if (!hasDm || sum < targetLevel)
      continue;
    if (needFieldTribute && !hasField)
      continue;

    if (!found || sum < bestSum) {
      bestSum = sum;
      bestMask = mask;
      found = TRUE;
    }
  }

  if (!found)
    return FALSE;

  *outMask = bestMask;
  return TRUE;
}

static u8 CanActivateSecretsRitual(void)
{
  struct DuelCard *zones[SECRETS_MAX_TRIBUTES];
  u8 levels[SECRETS_MAX_TRIBUTES];
  u8 isField[SECRETS_MAX_TRIBUTES];
  u8 isDm[SECRETS_MAX_TRIBUTES];
  s8 ritualZone;
  u8 candCount;
  u16 mask;
  u8 needField;
  u16 ritualId;
  u8 level;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  ritualZone = FindRitualHandZone(gTurnHands[ACTIVE_DUELIST]);
  if (ritualZone < 0)
    return FALSE;

  ritualId = gTurnHands[ACTIVE_DUELIST][ritualZone]->id;
  level = MonsterLevel(ritualId);
  if (level == 0)
    return FALSE;

  needField = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0;
  candCount = CollectTributeCandidates(ritualZone, zones, levels, isField, isDm,
                                       SECRETS_MAX_TRIBUTES);
  return FindSecretsTributeMask(level, candCount, levels, isField, isDm, needField, &mask);
}

static u8 CanActivateSecrets(void)
{
  return CanActivateSecretsFusion() || CanActivateSecretsRitual();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

static u8 PlayerChoosesSecretsMode(u8 canFusion, u8 canRitual)
{
  if (canFusion && !canRitual)
    return SECRETS_MODE_FUSION;
  if (canRitual && !canFusion)
    return SECRETS_MODE_RITUAL;

  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return SECRETS_MODE_FUSION;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return SECRETS_MODE_RITUAL;
    }

    WaitForVBlank();
  }
}

static const struct FusionRecipe *PlayerPickSecretsRecipe(const u8 *recipeIndices, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 j;
  u16 chosenId;
  u8 chosenLocalIdx = 0xFF;

  if (recipeIndices == NULL || count == 0)
    return NULL;

  if (count == 1)
    return &sSecretsRecipes[recipeIndices[0]];

  DECKMENU_SAVE();

  for (j = 0; j < EXPANDED_GRAVEYARD_CAPACITY; j++)
    gDeckMenu.cards[j] = CARD_NONE;

  for (j = 0; j < count; j++)
    gDeckMenu.cards[j] = sSecretsRecipes[recipeIndices[j]].result;

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sSecretsPickLabels, ARRAY_COUNT(sSecretsPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return NULL;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  for (j = 0; j < count; j++) {
    if (sSecretsRecipes[recipeIndices[j]].result == chosenId) {
      chosenLocalIdx = recipeIndices[j];
      break;
    }
  }

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  if (chosenLocalIdx == 0xFF)
    return NULL;

  return &sSecretsRecipes[chosenLocalIdx];
}

static s8 AiPickBestSecretsIndex(const struct FusionMaterialSource *sources, u8 sourceCount)
{
  u8 i;
  u16 bestAtk = 0;
  s8 bestIdx = -1;
  u8 recipeCount = ARRAY_COUNT(sSecretsRecipes);

  for (i = 0; i < recipeCount; i++) {
    const struct FusionRecipe *recipe = &sSecretsRecipes[i];
    u16 candidateAtk;

    if (!RecipeIncludesDarkMagicianMaterial(recipe))
      continue;
    if (!FusionRecipe_IsFeasibleWithSources(recipe, sources, sourceCount))
      continue;
    if (!ExtraDeckHasResult(recipe->result))
      continue;

    SetCardInfo(recipe->result);
    candidateAtk = gCardInfo.atk;

    if (bestIdx < 0 || candidateAtk > bestAtk) {
      bestIdx = (s8)i;
      bestAtk = candidateAtk;
    }
  }

  return bestIdx;
}

static void ResolveSecretsFusion(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[8];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  sourceCount = FusionDuel_CollectHandAndFieldSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (WhoseTurn() != DUEL_PLAYER) {
    s8 bestIdx = AiPickBestSecretsIndex(sources, sourceCount);

    if (bestIdx < 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    FusionDuel_ExecutePolymerization(&sSecretsRecipes[bestIdx], sources, sourceCount,
                                     SECRETS_OF_DARK_MAGIC, FALSE);
    return;
  }

  feasibleCount = BuildFeasibleSecretsIndices(sources, sourceCount, feasibleIndices,
                                              ARRAY_COUNT(feasibleIndices));
  if (feasibleCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  recipe = PlayerPickSecretsRecipe(feasibleIndices, feasibleCount);
  if (recipe == NULL)
    return;

  FusionDuel_ExecutePolymerization(recipe, sources, sourceCount, SECRETS_OF_DARK_MAGIC, FALSE);
}

static s8 PickRitualHandZone(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(gTurnHands[ACTIVE_DUELIST], IsRitualMonsterCard);

  return FindRitualHandZone(gTurnHands[ACTIVE_DUELIST]);
}

static void ResolveSecretsRitual(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *zones[SECRETS_MAX_TRIBUTES];
  u8 levels[SECRETS_MAX_TRIBUTES];
  u8 isField[SECRETS_MAX_TRIBUTES];
  u8 isDm[SECRETS_MAX_TRIBUTES];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 ritualZone;
  u8 candCount;
  u16 mask;
  u8 needField;
  u16 ritualId;
  u8 level;
  u8 i;

  if (!CanActivateSecretsRitual()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  ritualZone = PickRitualHandZone();
  if (ritualZone < 0)
    return;

  ritualId = gTurnHands[ACTIVE_DUELIST][ritualZone]->id;
  level = MonsterLevel(ritualId);
  needField = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0;
  candCount = CollectTributeCandidates(ritualZone, zones, levels, isField, isDm,
                                       SECRETS_MAX_TRIBUTES);
  if (!FindSecretsTributeMask(level, candCount, levels, isField, isDm, needField, &mask))
    return;

  if (spellZone != NULL && spellZone->id == SECRETS_OF_DARK_MAGIC)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_TRIBUTE);

  for (i = 0; i < candCount; i++) {
    if (!(mask & (1u << i)))
      continue;

    if (Duel_DestroyZone(zones[i], ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  NotifyDynamicEquipFieldChanged();
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);

  if (IsDuelOver() == TRUE)
    return;

  ritualZone = FindRitualHandZone(gTurnHands[ACTIVE_DUELIST]);
  if (ritualZone < 0)
    return;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, ritualZone, opts) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
}

static void SECRETS_OF_DARK_MAGIC_ResolveBody(void)
{
  u8 canFusion = CanActivateSecretsFusion();
  u8 canRitual = CanActivateSecretsRitual();
  u8 mode;

  Duel_ShowEffectText(SECRETS_OF_DARK_MAGIC);

  if (IsDuelOver() == TRUE || (!canFusion && !canRitual))
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    mode = PlayerChoosesSecretsMode(canFusion, canRitual);
  else if (canFusion)
    mode = SECRETS_MODE_FUSION;
  else
    mode = SECRETS_MODE_RITUAL;

  if (mode == SECRETS_MODE_FUSION && canFusion)
    ResolveSecretsFusion();
  else if (mode == SECRETS_MODE_RITUAL && canRitual)
    ResolveSecretsRitual();
}

APPEND_TEXT void EffectSECRETS_OF_DARK_MAGIC(void)
{
  if (!CanActivateSecrets()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(SECRETS_OF_DARK_MAGIC, SECRETS_OF_DARK_MAGIC_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void SECRETS_OF_DARK_MAGIC_SelfCheck(void)
{
  if (!RecipeIncludesDarkMagicianMaterial(&sSecretsRecipes[0]))
    while (1)
      ;
  if (!IsDarkMagicianOrGirl(DARK_MAGICIAN))
    while (1)
      ;
  if (!IsDarkMagicianOrGirl(DARK_MAGICIAN_GIRL))
    while (1)
      ;
  if (IsDarkMagicianOrGirl(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
