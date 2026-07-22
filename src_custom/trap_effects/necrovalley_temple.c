#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "necrovalley_temple.h"
#include "spell_effects.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

#define NECROVALLEY_TEMPLE_OPP_PENALTY 500

static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 FieldHasGravekeepers(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->isFaceUp
          && Duel_CardIsMonster(zone->id)
          && Duel_CardNameContains(zone->id, sGravekeepersName))
        return TRUE;
    }
  }

  return FALSE;
}

static void TryActivateNecrovalleyFromHandOrGy(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 i;
  s8 empty;

  if (Duel_IsBackrowCardOnField(NECROVALLEY, TRUE))
    return;

  empty = FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_BACKROW]);
  if (empty < 0)
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[INACTIVE_DUELIST][i] != NULL
        && gTurnHands[INACTIVE_DUELIST][i]->id == NECROVALLEY) {
      struct DuelCard *slot = gTurnZones[INACTIVE_DUELIST_BACKROW][empty];

      slot->id = NECROVALLEY;
      slot->isFaceUp = TRUE;
      slot->isLocked = FALSE;
      ClearZone(gTurnHands[INACTIVE_DUELIST][i]);
      return;
    }
  }

  if (GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, i) == NECROVALLEY) {
        struct DuelCard *slot = gTurnZones[INACTIVE_DUELIST_BACKROW][empty];

        GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
        slot->id = NECROVALLEY;
        slot->isFaceUp = TRUE;
        slot->isLocked = FALSE;
        return;
      }
    }
  }
}

void ApplyNecrovalleyTempleOppStatPenaltyToCardInfo(const struct DuelCard *zone)
{
  u8 controller;
  u8 templeController;

  if (zone == NULL || zone->id == CARD_NONE)
    return;
  if (!Necrovalley_IsActive() || !FieldHasGravekeepers())
    return;
  if (Duel_FindBackrowCardOnField(NECROVALLEY_TEMPLE, TRUE) == NULL)
    return;

  controller = GetDuelistForZone((struct DuelCard *)zone);
  if (controller > DUEL_OPPONENT)
    return;

  /* Penalty applies to the opponent of whoever controls Temple. */
  if (Duel_FindBackrowCard(DUEL_PLAYER, NECROVALLEY_TEMPLE, TRUE) != NULL)
    templeController = DUEL_PLAYER;
  else if (Duel_FindBackrowCard(DUEL_OPPONENT, NECROVALLEY_TEMPLE, TRUE) != NULL)
    templeController = DUEL_OPPONENT;
  else
    return;

  if (controller == templeController)
    return;

  gCardInfo.atk = Duel_ClampStat(
      (u32)gCardInfo.atk > NECROVALLEY_TEMPLE_OPP_PENALTY
          ? (u32)gCardInfo.atk - NECROVALLEY_TEMPLE_OPP_PENALTY
          : 0);
  gCardInfo.def = Duel_ClampStat(
      (u32)gCardInfo.def > NECROVALLEY_TEMPLE_OPP_PENALTY
          ? (u32)gCardInfo.def - NECROVALLEY_TEMPLE_OPP_PENALTY
          : 0);
}

static void ActivateNECROVALLEY_TEMPLEZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, NECROVALLEY_TEMPLE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  /* Ceiling: destroy-Set Necrovalley S/T from Deck needs destroy hook — place
   * Necrovalley from hand/GY when GK present; continuous −500 via overlay. */
  if (FieldHasGravekeepers())
    TryActivateNecrovalleyFromHandOrGy();

  UpdateDuelGfxExceptField();
}

void TryActivateNECROVALLEY_TEMPLEOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(NECROVALLEY_TEMPLE,
                                         ActivateNECROVALLEY_TEMPLEZone);
}
