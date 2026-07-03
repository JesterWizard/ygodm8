#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "fusion_recipes.h"
#include "spell_effects.h"

void ClearGraphicsBuffers(void);
void DisableDisplay(void);
void LoadOam(void);
void LoadPalettes(void);
void UpdateAllDuelGfx(void);

enum FusionRecoveryPickKind {
  FR_PICK_POLYMERIZATION = 0,
  FR_PICK_FUSION_MATERIAL = 1,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static u8 CountEmptyHandSlots(u8 turnDuelist)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[turnDuelist][i]->id == CARD_NONE)
      count++;
  }

  return count;
}

static s8 FindFirstPolymerizationGyIndex(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < gyCount; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == POLYMERIZATION)
      return (s8)i;
  }

  return -1;
}

static s8 FindFirstFusionMaterialGyIndex(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (FusionRecipe_CardIsFusionMaterial(cardId))
      return (s8)i;
  }

  return -1;
}

static u8 CanActivateFusionRecovery(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  if (CountEmptyHandSlots(ACTIVE_DUELIST) < 2)
    return FALSE;

  if (FindFirstPolymerizationGyIndex(fixedDuelist) < 0)
    return FALSE;

  if (FindFirstFusionMaterialGyIndex(fixedDuelist) < 0)
    return FALSE;

  return TRUE;
}

static u8 LoadGraveyardPickMenu(u8 fixedDuelist, enum FusionRecoveryPickKind kind, u8 excludeGyIndex,
                                u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (i == excludeGyIndex)
      continue;

    if (kind == FR_PICK_POLYMERIZATION) {
      if (cardId != POLYMERIZATION)
        continue;
    } else if (!FusionRecipe_CardIsFusionMaterial(cardId)) {
      continue;
    }

    gyIndexMap[menuCount] = i;
    gDeckMenu.cards[menuCount] = cardId;
    menuCount++;
  }

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  return menuCount;
}

static s8 PlayerPickGyIndex(u8 fixedDuelist, enum FusionRecoveryPickKind kind, u8 excludeGyIndex)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 j;
  s8 chosenGyIndex;

  menuCount = LoadGraveyardPickMenu(fixedDuelist, kind, excludeGyIndex, gyIndexMap);
  if (menuCount == 0)
    return -1;

  if (menuCount == 1)
    return (s8)gyIndexMap[0];

  for (j = 0; j < sizeof(gDeckMenu); j++)
    ((u8 *)&savedDeckMenu)[j] = ((u8 *)&gDeckMenu)[j];

  ClearGraphicsBuffers();
  LoadOam();
  LoadPalettes();
  DisableDisplay();
  if (!DeckMenuMainPickConfirm()) {
    for (j = 0; j < sizeof(gDeckMenu); j++)
      ((u8 *)&gDeckMenu)[j] = ((u8 *)&savedDeckMenu)[j];
    UpdateAllDuelGfx();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  for (j = 0; j < sizeof(gDeckMenu); j++)
    ((u8 *)&gDeckMenu)[j] = ((u8 *)&savedDeckMenu)[j];

  UpdateAllDuelGfx();
  return chosenGyIndex;
}

static u8 AddGraveyardCardToHand(u8 turnDuelist, u8 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  cardId = GraveyardExpand_RemoveAtTurn(turnDuelist, gyIndex);
  if (cardId == CARD_NONE)
    return FALSE;

  InitHandSlotFromCard(gTurnHands[turnDuelist][handZone], cardId);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return TRUE;
}

static void FusionRecovery_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 polyIndex;
  s8 materialIndex;

  Duel_ShowEffectText(FUSION_RECOVERY);

  if (IsDuelOver() == TRUE || !CanActivateFusionRecovery())
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    polyIndex = PlayerPickGyIndex(fixedDuelist, FR_PICK_POLYMERIZATION, 0xFF);
    if (polyIndex < 0)
      return;

    materialIndex = PlayerPickGyIndex(fixedDuelist, FR_PICK_FUSION_MATERIAL, (u8)polyIndex);
    if (materialIndex < 0)
      return;
  } else {
    polyIndex = FindFirstPolymerizationGyIndex(fixedDuelist);
    materialIndex = FindFirstFusionMaterialGyIndex(fixedDuelist);
    if (polyIndex < 0 || materialIndex < 0)
      return;
  }

  if (polyIndex > materialIndex) {
    if (!AddGraveyardCardToHand(ACTIVE_DUELIST, (u8)polyIndex))
      return;
    if (!AddGraveyardCardToHand(ACTIVE_DUELIST, (u8)materialIndex))
      return;
  } else {
    if (!AddGraveyardCardToHand(ACTIVE_DUELIST, (u8)materialIndex))
      return;
    if (!AddGraveyardCardToHand(ACTIVE_DUELIST, (u8)polyIndex))
      return;
  }

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectFusionRecovery(void)
{
  if (!CanActivateFusionRecovery()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(FUSION_RECOVERY, FusionRecovery_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
