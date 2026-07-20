#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 OpponentDuelist(u8 duelist)
{
  return duelist == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

unsigned char ShouldActivateDESTINY_HERO_DOGMA(void)
{
  struct DuelCard *zone;
  u8 duelist;
  u8 oppFixed;

  if (gActiveEffect.cardId != DESTINY_HERO_DOGMA)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  oppFixed = FixedDuelistForTurnDuelist(OpponentDuelist(duelist));
  return gDuelLifePoints[oppFixed] > 1;
}

void ActivateDESTINY_HERO_DOGMA(void)
{
  u8 duelist;
  u8 oppTurn;
  u8 oppFixed;
  u16 lp;
  s32 pay;
  struct DuelCard *zone;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  oppTurn = OpponentDuelist(duelist);
  oppFixed = FixedDuelistForTurnDuelist(oppTurn);
  lp = gDuelLifePoints[oppFixed];
  pay = (s32)(lp / 2);

  Duel_ShowEffectTextTyped(DESTINY_HERO_DOGMA, 8);
  if (IsDuelOver() == TRUE)
    return;

  if (pay > 0) {
    if (Duel_ChangeLp(oppTurn, -pay, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone != NULL)
    zone->unk4 = 1;
  /* ponytail: true trigger is opp next Standby after 3-tribute SS; on-summon halve LP once. */
}
