#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

APPEND_TEXT void EffectRED_REBOOT(void)
{
  struct DuelCard *origin;
  u8 fixedOpp = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedOpp);
  u8 top = gDuelDecks[fixedOpp].cardsDrawn;
  u8 i;
  u16 setId = CARD_NONE;
  u8 setIdx = 0;
  s8 empty;

  Duel_ShowTrapResponseText(RED_REBOOT, gTrapEffectData.originCardId);

  /* ponytail: hand-activate by paying half LP + full Trap negate need gates.
   * Ceiling: Set origin Trap face-down + optional Deck Set 1 Trap for opp;
   * opp Trap lock this turn not wired. */

  origin = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];
  if (origin != NULL && GetTypeGroup(origin->id) == TYPE_GROUP_TRAP) {
    origin->isFaceUp = FALSE;
    origin->isLocked = FALSE;
  }

  empty = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]);
  if (empty >= 0) {
    for (i = top; i < deckSize; i++) {
      if (GetTypeGroup(gDuelDecks[fixedOpp].cards[i]) == TYPE_GROUP_TRAP) {
        setId = gDuelDecks[fixedOpp].cards[i];
        setIdx = i;
        break;
      }
    }
    if (setId != CARD_NONE
        && Duel_RemoveDeckCardAt(ACTIVE_DUELIST, setIdx, FALSE) == DUEL_ACTION_OK) {
      struct DuelCard *slot = gTurnZones[ACTIVE_DUELIST_BACKROW][empty];

      slot->id = setId;
      slot->isFaceUp = FALSE;
      slot->isLocked = FALSE;
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
