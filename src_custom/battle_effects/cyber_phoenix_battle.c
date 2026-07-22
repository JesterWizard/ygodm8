#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "cyber_phoenix_battle.h"
#include "duel_helpers.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct CyberPhoenixActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct CyberPhoenixActionData sActionData;

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

void ApplyCyberPhoenixBattleDestroyDraw(void)
{
  u8 turnDuelist;

  if (gHideEffectText)
    return;

  if ((sActionData.flags & FLAG_GRAVEYARD_PLAYER) && sActionData.playerCardId == CYBER_PHOENIX) {
    turnDuelist = TurnDuelistForFixed(DUEL_PLAYER);
    if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
      return;
    Duel_ShowEffectTextTyped(CYBER_PHOENIX, 2);
    Duel_DrawCards(turnDuelist, 1, TRUE);
    return;
  }

  if ((sActionData.flags & FLAG_GRAVEYARD_OPPONENT) && sActionData.opponentCardId == CYBER_PHOENIX) {
    turnDuelist = TurnDuelistForFixed(DUEL_OPPONENT);
    if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
      return;
    Duel_ShowEffectTextTyped(CYBER_PHOENIX, 2);
    Duel_DrawCards(turnDuelist, 1, TRUE);
  }
}
