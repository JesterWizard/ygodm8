#include "global.h"
#include "common-chax.h"
#include "chainsaw_insect.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

struct ChainsawActionData {
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

extern struct ChainsawActionData sActionData;

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

void ApplyChainsawInsectBattleEffect(void)
{
  /* After battling: opponent draws 1. */
  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 5)
    return;

  if (sActionData.playerCardId == CHAINSAW_INSECT) {
    Duel_ShowEffectTextTyped(CHAINSAW_INSECT, 2);
    Duel_DrawCards(TurnDuelistForFixed(DUEL_OPPONENT), 1, TRUE);
    return;
  }

  if (sActionData.opponentCardId == CHAINSAW_INSECT) {
    Duel_ShowEffectTextTyped(CHAINSAW_INSECT, 2);
    Duel_DrawCards(TurnDuelistForFixed(DUEL_PLAYER), 1, TRUE);
  }
}

unsigned char CanActivateCHAINSAW_INSECT(void)
{
  if (gMonEffect.id != CHAINSAW_INSECT)
    return FALSE;

  /* Opp draw after battle via ApplyChainsawInsectBattleEffect. */
  return FALSE;
}

void ActivateCHAINSAW_INSECTEffect(void)
{
  Duel_ShowEffectTextTyped(CHAINSAW_INSECT, 2);
}
