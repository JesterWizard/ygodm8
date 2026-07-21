#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "dynamic_equip.h"
#include "fusion_recipes.h"
#include "player_decks.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);
u8 ExtraDeck_TryRemoveCard(u16 cardId);

static const u8 sMetamorphosisPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u16 *ActiveExtraDeck(void)
{
  switch (gActiveDeckIndex) {
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

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsValidMetamorphosisTributeZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 IsMetamorphosisFusionTarget(u16 cardId, u8 tributeLevel)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.color == COLOR_FUSION && gCardInfo.level == tributeLevel;
}

static u8 BuildMetamorphosisFusionTargets(u8 tributeLevel, u16 *outIds, u8 maxOut)
{
  u8 count = 0;
  u8 i;

  if (outIds == NULL || maxOut == 0)
    return 0;

  if (gRuntimeConfig.enable_extra_deck) {
    u16 *extra = ActiveExtraDeck();

    for (i = 0; i < EXTRA_DECK_SIZE && count < maxOut; i++) {
      u16 cardId = extra[i];
      u8 j;

      if (!IsMetamorphosisFusionTarget(cardId, tributeLevel))
        continue;
      for (j = 0; j < count; j++) {
        if (outIds[j] == cardId)
          break;
      }
      if (j == count)
        outIds[count++] = cardId;
    }
    return count;
  }

  /* ponytail: without the runtime Extra Deck, use registered Fusion results as
   * a stand-in. Ceiling: permits a result not physically in an Extra Deck. */
  for (i = 0; i < FusionRecipe_Count() && count < maxOut; i++) {
    u16 cardId = gFusionRecipes[i].result;
    u8 j;

    if (!IsMetamorphosisFusionTarget(cardId, tributeLevel))
      continue;
    for (j = 0; j < count; j++) {
      if (outIds[j] == cardId)
        break;
    }
    if (j == count)
      outIds[count++] = cardId;
  }

  return count;
}

static u16 PlayerPickMetamorphosisFusion(const u16 *targetIds, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u16 chosenId;
  u8 i;

  if (targetIds == NULL || count == 0)
    return CARD_NONE;
  if (count == 1)
    return targetIds[0];

  DECKMENU_SAVE();
  for (i = 0; i < EXTRA_DECK_SIZE; i++)
    gDeckMenu.cards[i] = CARD_NONE;
  for (i = 0; i < count; i++)
    gDeckMenu.cards[i] = targetIds[i];

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sMetamorphosisPickLabels,
                                         ARRAY_COUNT(sMetamorphosisPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return CARD_NONE;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenId;
}

static u16 AiPickMetamorphosisFusion(const u16 *targetIds, u8 count)
{
  u8 i;
  u16 chosenId = CARD_NONE;
  u16 bestAtk = 0;

  for (i = 0; i < count; i++) {
    SetCardInfo(targetIds[i]);
    if (chosenId == CARD_NONE || gCardInfo.atk > bestAtk) {
      chosenId = targetIds[i];
      bestAtk = gCardInfo.atk;
    }
  }

  return chosenId;
}

u8 CanActivateMETAMORPHOSIS(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();
  u16 targets[EXTRA_DECK_SIZE];

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (!IsValidMetamorphosisTributeZone(row, col))
      continue;
    SetCardInfo(zone->id);
    if (BuildMetamorphosisFusionTargets(gCardInfo.level, targets, ARRAY_COUNT(targets)) != 0)
      return TRUE;
  }

  return FALSE;
}

static void DestroyMetamorphosisSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == METAMORPHOSIS)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void FinishMetamorphosis(u8 tributeRow, u8 tributeCol)
{
  struct DuelCard *tributeZone;
  u8 tributeLevel;
  u16 targets[EXTRA_DECK_SIZE];
  u8 targetCount;
  u16 chosenId;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!IsValidMetamorphosisTributeZone(tributeRow, tributeCol)) {
    DestroyMetamorphosisSpellZone();
    return;
  }

  tributeZone = gFixedZones[tributeRow][tributeCol];
  SetCardInfo(tributeZone->id);
  tributeLevel = gCardInfo.level;
  targetCount = BuildMetamorphosisFusionTargets(tributeLevel, targets, ARRAY_COUNT(targets));
  if (targetCount == 0) {
    DestroyMetamorphosisSpellZone();
    return;
  }

  chosenId = WhoseTurn() == DUEL_PLAYER
      ? PlayerPickMetamorphosisFusion(targets, targetCount)
      : AiPickMetamorphosisFusion(targets, targetCount);
  if (chosenId == CARD_NONE) {
    DestroyMetamorphosisSpellZone();
    return;
  }

  DestroyMetamorphosisSpellZone();
  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(tributeZone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);

  if ((gRuntimeConfig.enable_extra_deck && !ExtraDeck_TryRemoveCard(chosenId))
      || Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, chosenId, opts) == DUEL_ACTION_DUEL_OVER)
    return;
}

static void CancelMetamorphosisTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyMetamorphosisSpellZone();
}

static u8 AiPickMetamorphosisTribute(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();
  u8 found = FALSE;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidMetamorphosisTributeZone(row, col))
      continue;

    zone = gFixedZones[row][col];
    SetCardInfo(zone->id);
    atk = gCardInfo.atk;
    if (!found || atk < bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = row;
      *outCol = col;
    }
  }

  return found;
}

static void ResolveMetamorphosisTribute(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidMetamorphosisTributeZone(fixedRow, fixedCol))
    return;

  FinishMetamorphosis(fixedRow, fixedCol);
}

static void METAMORPHOSIS_ResolveBody(void)
{
  Duel_ShowEffectText(METAMORPHOSIS);

  if (IsDuelOver() == TRUE || !CanActivateMETAMORPHOSIS())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidMetamorphosisTributeZone, ResolveMetamorphosisTribute,
                     CancelMetamorphosisTargeting, AiPickMetamorphosisTribute);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectMETAMORPHOSIS(void)
{
  if (!CanActivateMETAMORPHOSIS()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(METAMORPHOSIS, METAMORPHOSIS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void METAMORPHOSIS_SelfCheck(void)
{
  if (COLOR_FUSION == COLOR_NORMAL)
    while (1)
      ;
}
#endif
