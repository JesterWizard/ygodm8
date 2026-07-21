#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

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
          && Duel_CardNameContains(zone->id, sGravekeepersName)
          && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
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

static void ActivateNECROVALLEY_TEMPLEZone(struct DuelCard *zone)
{
  u8 oppRow = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 col;

  if (Duel_ActivateContinuousTrapPreamble(zone, NECROVALLEY_TEMPLE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: -500 ATK/DEF while GK+Necrovalley need stat overlay; destroy-Set
   * Necrovalley S/T from Deck need destroy hook. Ceiling: if GK present, try
   * place Necrovalley from hand/GY; mark opp monsters -1 stage. */

  if (FieldHasGravekeepers()) {
    TryActivateNecrovalleyFromHandOrGy();
    if (Duel_IsBackrowCardOnField(NECROVALLEY, TRUE)) {
      for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
        struct DuelCard *m = gFixedZones[oppRow][col];

        if (m != NULL && m->id != CARD_NONE)
          DecrementPermStage(m);
      }
    }
  }

  UpdateDuelGfxExceptField();
}

void TryActivateNECROVALLEY_TEMPLEOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(NECROVALLEY_TEMPLE,
                                         ActivateNECROVALLEY_TEMPLEZone);
}

