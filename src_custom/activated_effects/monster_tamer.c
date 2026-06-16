#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char CanActivateMonsterTamer(void) {
  u8 monsterRow;

  if (gMonEffect.id != MONSTER_TAMER)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    monsterRow = (WhoseTurn() == DUEL_PLAYER) ? ACTIVE_DUELIST_MONSTER_ROW
                                                : INACTIVE_DUELIST_MONSTER_ROW;
  else
    monsterRow = (WhoseTurn() == DUEL_PLAYER) ? INACTIVE_DUELIST_MONSTER_ROW
                                              : ACTIVE_DUELIST_MONSTER_ROW;

  return FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0;
}

void ActivateMonsterTamerEffect(void) {
  struct DuelSummonOpts opts;
  u8 monsterRow;
  u8 summonDuelist;

  if (gMonEffect.row == PLAYER_MONSTER_ROW) {
    monsterRow = (WhoseTurn() == DUEL_PLAYER) ? ACTIVE_DUELIST_MONSTER_ROW
                                                : INACTIVE_DUELIST_MONSTER_ROW;
  } else {
    monsterRow = (WhoseTurn() == DUEL_PLAYER) ? INACTIVE_DUELIST_MONSTER_ROW
                                              : ACTIVE_DUELIST_MONSTER_ROW;
  }

  summonDuelist = (monsterRow == ACTIVE_DUELIST_MONSTER_ROW) ? ACTIVE_DUELIST : INACTIVE_DUELIST;

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = MONSTER_TAMER;
    gCardEffectTextData.cardId2 = DUNGEON_WORM;
    ActivateCardEffectText();
  }

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.markSpecialSummon = FALSE;
  Duel_SpecialSummonMonsterId(summonDuelist, DUNGEON_WORM, opts);
}
