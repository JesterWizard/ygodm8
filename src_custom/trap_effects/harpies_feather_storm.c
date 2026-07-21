#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "harpies_feather_storm.h"

void UpdateDuelGfxExceptField(void);

static const char sHarpieName[] APPEND_RODATA = "Harpie";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 ControlsWindWingedBeast(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    if (!Duel_CardHasMonsterType(zone->id, TYPE_WINGED_BEAST))
      continue;
    SetCardInfo(zone->id);
    if (gCardInfo.attribute == ATTRIBUTE_WIND)
      return TRUE;
  }

  return FALSE;
}

static u8 ControlsHarpie(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && Duel_CardNameContains(zone->id, sHarpieName))
      return TRUE;
  }

  return FALSE;
}

static void TryAddFeatherDuster(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  s8 empty;
  u16 cardId = CARD_NONE;
  u8 deckIndex = 0;

  empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
  if (empty < 0)
    return;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == HARPIES_FEATHER_DUSTER) {
      cardId = HARPIES_FEATHER_DUSTER;
      deckIndex = i;
      break;
    }
  }

  if (cardId == CARD_NONE && GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, i) == HARPIES_FEATHER_DUSTER) {
        if (GraveyardExpand_RemoveAtFixed(fixedDuelist, i) == HARPIES_FEATHER_DUSTER) {
          gTurnHands[INACTIVE_DUELIST][empty]->id = HARPIES_FEATHER_DUSTER;
          gTurnHands[INACTIVE_DUELIST][empty]->isFaceUp = FALSE;
          gTurnHands[INACTIVE_DUELIST][empty]->isLocked = FALSE;
          ResetPermStage(gTurnHands[INACTIVE_DUELIST][empty]);
          ResetTempStage(gTurnHands[INACTIVE_DUELIST][empty]);
        }
        return;
      }
    }
  }

  if (cardId != CARD_NONE
      && Duel_RemoveDeckCardAt(INACTIVE_DUELIST, deckIndex, FALSE) == DUEL_ACTION_OK) {
    gTurnHands[INACTIVE_DUELIST][empty]->id = cardId;
    gTurnHands[INACTIVE_DUELIST][empty]->isFaceUp = FALSE;
    gTurnHands[INACTIVE_DUELIST][empty]->isLocked = FALSE;
    ResetPermStage(gTurnHands[INACTIVE_DUELIST][empty]);
    ResetTempStage(gTurnHands[INACTIVE_DUELIST][empty]);
  }
}

u8 HarpiesFeatherStorm_BlocksMonsterEffects(u8 fixedDuelist)
{
  struct DuelCard *trap;

  if (fixedDuelist > DUEL_OPPONENT)
    return FALSE;

  /* Blocks the opponent of the Storm controller. */
  trap = Duel_FindBackrowCard(fixedDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER,
                              HARPIES_FEATHER_STORM, TRUE);
  return trap != NULL && trap->unk4 != 0;
}

void HarpiesFeatherStorm_ClearAtTurnBoundary(void)
{
  u8 fixed;
  u8 col;

  for (fixed = DUEL_PLAYER; fixed <= DUEL_OPPONENT; fixed++) {
    u8 backrow = fixed == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *trap = gFixedZones[backrow][col];

      if (trap != NULL && trap->id == HARPIES_FEATHER_STORM && trap->isFaceUp
          && trap->unk4 != 0) {
        trap->unk4 = 0;
        Duel_DestroyZone(trap, Duel_TurnDuelistForFixedDuelist(fixed), FALSE);
      }
    }
  }
}

APPEND_TEXT void EffectHARPIES_FEATHER_STORM(void)
{
  Duel_ShowTrapResponseText(HARPIES_FEATHER_STORM, gTrapEffectData.originCardId);

  if (ControlsWindWingedBeast()) {
    struct DuelCard *trapZone =
        gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];

    if (trapZone != NULL) {
      Duel_ActivateContinuousZone(trapZone);
      trapZone->unk4 = 1; /* monster-effect lock until turn boundary */
    }
  } else {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
  }

  if (ControlsHarpie())
    TryAddFeatherDuster();

  UpdateDuelGfxExceptField();
}
