#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "lev_shaddoll_fusion.h"
#include "player_decks.h"
#include "spell_effects.h"

static const u8 sLevShaddollFusionPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

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

static u8 IsFusionMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.color == FUSION_CARD;
}

static u8 BuildExtraDeckFusionTargets(u16 *outIds, u8 maxOut)
{
  u16 *extra;
  u8 count = 0;
  u8 i;

  if (outIds == NULL || maxOut == 0 || !gRuntimeConfig.enable_extra_deck)
    return 0;

  extra = ActiveExtraDeck();
  for (i = 0; i < EXTRA_DECK_SIZE && count < maxOut; i++) {
    if (IsFusionMonster(extra[i]))
      outIds[count++] = extra[i];
  }

  return count;
}

static u16 PlayerPickExtraDeckFusion(const u16 *targetIds, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 i;
  u16 chosenId;

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
  if (!DeckMenuMainPickConfirmWithLabels(sLevShaddollFusionPickLabels,
                                         ARRAY_COUNT(sLevShaddollFusionPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return CARD_NONE;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenId;
}

static u16 AiPickExtraDeckFusion(const u16 *targetIds, u8 count)
{
  u16 chosenId = CARD_NONE;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < count; i++) {
    SetCardInfo(targetIds[i]);
    if (chosenId == CARD_NONE || gCardInfo.atk > bestAtk) {
      chosenId = targetIds[i];
      bestAtk = gCardInfo.atk;
    }
  }

  return chosenId;
}

u8 LevShaddollFusion_SendFusionFromExtraDeck(void)
{
  u16 targets[EXTRA_DECK_SIZE];
  u16 chosenId;
  u16 *extra;
  u8 count;
  u8 i;

  count = BuildExtraDeckFusionTargets(targets, ARRAY_COUNT(targets));
  if (count == 0)
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    chosenId = PlayerPickExtraDeckFusion(targets, count);
  else
    chosenId = AiPickExtraDeckFusion(targets, count);

  if (!IsFusionMonster(chosenId))
    return FALSE;

  extra = ActiveExtraDeck();
  for (i = 0; i < EXTRA_DECK_SIZE; i++) {
    if (extra[i] != chosenId)
      continue;

    extra[i] = CARD_NONE;
    GraveyardExpand_PushTurn(ACTIVE_DUELIST, chosenId);
    return TRUE;
  }

  return FALSE;
}

static void LEV_SHADDOLL_FUSION_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (zone != NULL && zone->isLocked) {
    Duel_ShowEffectText(LEV_SHADDOLL_FUSION);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(LEV_SHADDOLL_FUSION);
  LevShaddollFusion_SendFusionFromExtraDeck();

  /* Ceiling: the face-up ignition still needs a monster-zone tribute picker and
   * an Extra Deck special-summon flow, neither of which is owned by this spell
   * activation dispatcher. */
}

APPEND_TEXT void EffectLEV_SHADDOLL_FUSION(void)
{
  if (Duel_TryResolveSpellThroughTraps(LEV_SHADDOLL_FUSION, LEV_SHADDOLL_FUSION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
