#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"

static struct DuelCard **MonsterRowForEffect(void) {
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return gFixedZones[PLAYER_MONSTER_ROW];
  if (gMonEffect.row == OPPONENT_MONSTER_ROW)
    return gFixedZones[OPPONENT_MONSTER_ROW];
  return gTurnZones[gMonEffect.row];
}

static u8 SummonDungeonWorm(void) {
  struct DuelCard **monsterRow = MonsterRowForEffect();
  s8 monsterZone;
  struct DuelCard *summonZone;

  monsterZone = FirstEmptyZoneInRow(monsterRow);
  if (monsterZone < 0)
    return FALSE;

  summonZone = monsterRow[monsterZone];
  summonZone->id = DUNGEON_WORM;
  FlipCardFaceUp(summonZone);
  UnlockCard(summonZone);
  summonZone->isDefending = FALSE;
  summonZone->unkTwo = 0;
  summonZone->unkThree = 0;
  ResetPermStage(summonZone);
  ResetTempStage(summonZone);
  summonZone->unk4 = 0;
  summonZone->willChangeSides = FALSE;

  return TRUE;
}

unsigned char CanActivateMonsterTamer(void) {
  if (gMonEffect.id != MONSTER_TAMER)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  return FirstEmptyZoneInRow(MonsterRowForEffect()) >= 0;
}

void ActivateMonsterTamerEffect(void) {
  if (!gHideEffectText) {
    gCardEffectTextData.cardId = MONSTER_TAMER;
    gCardEffectTextData.cardId2 = DUNGEON_WORM;
    ActivateCardEffectText();
  }

  SummonDungeonWorm();
}
