#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "effect_events.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"

#define INSTANT_FUSION_LP_COST 1000
#define INSTANT_FUSION_MAX_LEVEL 5

void UpdateDuelGfxExceptField(void);
u8 ExtraDeck_TryRemoveCard(u16 cardId);

static const u8 sInstantFusionPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

/* OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */

static u16 *ActiveExtraDeck(void)
{
  u8 active = gActiveDeckIndex;

  if (active >= PLAYER_DECK_INDEX_MIN && active <= PLAYER_DECK_INDEX_MAX) {
    switch (active) {
    case 1:
      return gPlayerDeck1ExtraDeck;
    case 2:
      return gPlayerDeck2ExtraDeck;
    case 3:
      return gPlayerDeck3ExtraDeck;
    default:
      return gPlayerDeck1ExtraDeck;
    }
  }

  return gPlayerDeck1ExtraDeck;
}

static u8 IsInstantFusionTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  return gCardInfo.level > 0 && gCardInfo.level <= INSTANT_FUSION_MAX_LEVEL;
}

static u8 BuildInstantFusionTargets(u16 *outIds, u8 maxOut)
{
  u8 count = 0;
  u8 i;
  u8 j;

  if (outIds == NULL || maxOut == 0)
    return 0;

  if (gRuntimeConfig.enable_extra_deck) {
    u16 *extra = ActiveExtraDeck();

    for (i = 0; i < EXTRA_DECK_SIZE && count < maxOut; i++) {
      u16 cardId = extra[i];
      u8 dup = FALSE;

      if (!IsInstantFusionTarget(cardId))
        continue;

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

  /* Extra Deck off: offer Level ≤5 Fusion recipe results by id. */
  {
    u8 recipeCount = FusionRecipe_Count();

    for (i = 0; i < recipeCount && count < maxOut; i++) {
      u16 cardId = gFusionRecipes[i].result;
      u8 dup = FALSE;

      if (!IsInstantFusionTarget(cardId))
        continue;

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
  }

  return count;
}

static u16 PlayerPickInstantFusionTarget(const u16 *targetIds, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 j;
  u16 chosenId;

  if (targetIds == NULL || count == 0)
    return CARD_NONE;

  if (count == 1)
    return targetIds[0];

  DECKMENU_SAVE();

  for (j = 0; j < EXTRA_DECK_SIZE; j++)
    gDeckMenu.cards[j] = CARD_NONE;
  for (j = 0; j < count; j++)
    gDeckMenu.cards[j] = targetIds[j];

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sInstantFusionPickLabels,
                                         ARRAY_COUNT(sInstantFusionPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return CARD_NONE;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenId;
}

static u16 AiPickInstantFusionTarget(const u16 *targetIds, u8 count)
{
  u8 i;
  u16 bestId = CARD_NONE;
  u16 bestAtk = 0;

  for (i = 0; i < count; i++) {
    SetCardInfo(targetIds[i]);
    if (bestId == CARD_NONE || gCardInfo.atk > bestAtk) {
      bestId = targetIds[i];
      bestAtk = gCardInfo.atk;
    }
  }

  return bestId;
}

static u8 CanActivateInstantFusion(void)
{
  u16 targets[EXTRA_DECK_SIZE];

  if (EffectOpt_IsUsed(INSTANT_FUSION))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return BuildInstantFusionTargets(targets, EXTRA_DECK_SIZE) > 0;
}

static void INSTANT_FUSION_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u16 targets[EXTRA_DECK_SIZE];
  u8 targetCount;
  u16 chosenId;
  struct DuelSummonOpts opts;

  Duel_ShowEffectText(INSTANT_FUSION);

  if (IsDuelOver() == TRUE || !CanActivateInstantFusion())
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -INSTANT_FUSION_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  targetCount = BuildInstantFusionTargets(targets, EXTRA_DECK_SIZE);
  if (targetCount == 0)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    chosenId = PlayerPickInstantFusionTarget(targets, targetCount);
  else
    chosenId = AiPickInstantFusionTarget(targets, targetCount);

  if (chosenId == CARD_NONE || !IsInstantFusionTarget(chosenId))
    return;

  if (gRuntimeConfig.enable_extra_deck && !ExtraDeck_TryRemoveCard(chosenId))
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  /* cannot attack — isLocked honored by attack validators (clone Instant Neo Space lock). */
  opts.lockMonster = TRUE;

  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, chosenId, opts) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(INSTANT_FUSION);

  /* ponytail: End Phase destroy of the Instant Fusion monster needs a turn_effect
   * hook outside this file (no in-file End Phase destroy queue without BSS mark).
   * Ceiling: SS + attack-lock only; upgrade: turn_effect_hooks End Phase → destroy
   * zone marked by Instant Fusion this turn. Treated-as-Fusion-Summon name checks
   * also need a summon-tag outside this file. */
}

APPEND_TEXT void EffectINSTANT_FUSION(void)
{
  if (!CanActivateInstantFusion()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTrapsEx(INSTANT_FUSION, INSTANT_FUSION_LP_COST,
                                         INSTANT_FUSION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void INSTANT_FUSION_SelfCheck(void)
{
  if (!IsInstantFusionTarget(FLAME_SWORDSMAN))
    while (1)
      ;
  if (IsInstantFusionTarget(ELEMENTAL_HERO_FLAME_WINGMAN))
    while (1)
      ;
  if (IsInstantFusionTarget(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
