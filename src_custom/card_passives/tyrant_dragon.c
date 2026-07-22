#include "global.h"
#include "constants/card_ids.h"
#include "tyrant_dragon.h"
#include "the_dark_door.h"

u8 IsImmuneToTrapEffectsOnField(u16 cardId, u8 turnRow) {
  if (turnRow != ACTIVE_DUELIST_MONSTER_ROW && turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  return cardId == TYRANT_DRAGON
      || cardId == BLUE_EYES_TYRANT_DRAGON
      || cardId == ELEMENTAL_HERO_WILDHEART
      || cardId == LYRILUSC_INDEPENDENT_NIGHTINGALE;
}

static u8 OpponentMonsterRowForAttacker(void) {
  return WhoseTurn() == DUEL_PLAYER
      ? INACTIVE_DUELIST_MONSTER_ROW
      : ACTIVE_DUELIST_MONSTER_ROW;
}

static u8 OpponentHasMonsterOnField(void) {
  u8 i;
  u8 row = OpponentMonsterRowForAttacker();

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gTurnZones[row][i]->id != CARD_NONE)
      return TRUE;

  return FALSE;
}

void TryUnlockTyrantDragonForSecondAttack(struct DuelCard *attacker) {
  if (attacker == NULL)
    return;

  if (attacker->id != TYRANT_DRAGON)
    return;

  if (IsTheDarkDoorActiveOnField())
    return;

  if (!OpponentHasMonsterOnField())
    return;

  if (attacker->effectUsedThisTurn == FALSE) {
    attacker->effectUsedThisTurn = TRUE;
    attacker->isLocked = FALSE;
  }
}
