#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "fusion_duel.h"
#include "monster_effect_usage.h"
#include "player_decks.h"

#define MAGICAL_SCIENTIST_LP_COST 1000
#define MAGICAL_SCIENTIST_MAX_LEVEL 6

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);
u8 ExtraDeck_TryRemoveCard(u16 cardId);

static const u8 sMagicalScientistPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CanPayMagicalScientistCost(void)
{
  return gDuelLifePoints[FixedDuelistForActive()] >= MAGICAL_SCIENTIST_LP_COST;
}

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

static u8 IsMagicalScientistFusionTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  return gCardInfo.level > 0 && gCardInfo.level <= MAGICAL_SCIENTIST_MAX_LEVEL;
}

static u8 BuildMagicalScientistTargets(u16 *outIds, u8 maxOut)
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

      if (!IsMagicalScientistFusionTarget(cardId))
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

  {
    u8 recipeCount = FusionRecipe_Count();

    for (i = 0; i < recipeCount && count < maxOut; i++) {
      u16 cardId = gFusionRecipes[i].result;
      u8 dup = FALSE;

      if (!IsMagicalScientistFusionTarget(cardId))
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

static u16 PlayerPickFusionTarget(const u16 *targetIds, u8 count)
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
  if (!DeckMenuMainPickConfirmWithLabels(sMagicalScientistPickLabels,
                                         ARRAY_COUNT(sMagicalScientistPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return CARD_NONE;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenId;
}

static u16 AiPickFusionTarget(const u16 *targetIds, u8 count)
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

static u8 CanResolveMagicalScientistEffect(void)
{
  u16 targets[EXTRA_DECK_SIZE];

  if (!CanPayMagicalScientistCost())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return BuildMagicalScientistTargets(targets, EXTRA_DECK_SIZE) > 0;
}

unsigned char CanActivateMAGICAL_SCIENTIST(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MAGICAL_SCIENTIST)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MAGICAL_SCIENTIST)
    return FALSE;

  /* ponytail: no direct attack + End Phase Extra Deck return need battle/EP hooks.
   * Ceiling: pay 1000 → SS Lv≤6 Fusion from Extra/recipe list. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanResolveMagicalScientistEffect();
}

void ActivateMAGICAL_SCIENTISTEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 targets[EXTRA_DECK_SIZE];
  u8 targetCount;
  u16 chosenId;
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(MAGICAL_SCIENTIST, 2);

  if (self == NULL || IsDuelOver() == TRUE || !CanResolveMagicalScientistEffect())
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)MAGICAL_SCIENTIST_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  targetCount = BuildMagicalScientistTargets(targets, EXTRA_DECK_SIZE);
  if (targetCount == 0)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    chosenId = PlayerPickFusionTarget(targets, targetCount);
  else
    chosenId = AiPickFusionTarget(targets, targetCount);

  if (chosenId == CARD_NONE || !IsMagicalScientistFusionTarget(chosenId))
    return;

  if (gRuntimeConfig.enable_extra_deck && !ExtraDeck_TryRemoveCard(chosenId))
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.lockMonster = TRUE;
  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, chosenId, opts) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MAGICAL_SCIENTIST_SelfCheck(void)
{
  if (!IsMagicalScientistFusionTarget(FLAME_SWORDSMAN))
    while (1)
      ;
  if (IsMagicalScientistFusionTarget(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
