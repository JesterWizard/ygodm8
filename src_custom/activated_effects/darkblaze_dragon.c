#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "darkblaze_dragon.h"
#include "duel_helpers.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct DarkblazeActionData {
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

extern struct DarkblazeActionData sActionData;

static void BurnFixed(u8 fixedDuelist, u16 damage)
{
  if (damage == 0)
    return;
  if (gDuelLifePoints[fixedDuelist] <= damage) {
    gDuelLifePoints[fixedDuelist] = 0;
    sActionData.flags |= fixedDuelist == DUEL_PLAYER ? FLAG_LOSER_PLAYER : FLAG_LOSER_OPPONENT;
  } else {
    gDuelLifePoints[fixedDuelist] -= damage;
  }
  gUnk2023EA0.unk0[fixedDuelist].lifePointsAfterDamage = gDuelLifePoints[fixedDuelist];
  if (fixedDuelist == DUEL_PLAYER)
    sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  else
    sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

void ApplyDarkblazeDragonBattleEffect(void)
{
  u16 burn;

  if (sActionData.playerCardId == DARKBLAZE_DRAGON
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    burn = gCardData_NEW[sActionData.opponentCardId].atk;
    if (burn != 0) {
      Duel_ShowEffectTextTyped(DARKBLAZE_DRAGON, 2);
      BurnFixed(DUEL_OPPONENT, burn);
    }
    return;
  }

  if (sActionData.opponentCardId == DARKBLAZE_DRAGON
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    burn = gCardData_NEW[sActionData.playerCardId].atk;
    if (burn != 0) {
      Duel_ShowEffectTextTyped(DARKBLAZE_DRAGON, 2);
      BurnFixed(DUEL_PLAYER, burn);
    }
  }
}

unsigned char CanActivateDARKBLAZE_DRAGON(void)
{
  if (gMonEffect.id != DARKBLAZE_DRAGON)
    return FALSE;

  /* Battle-destroy burn via ApplyDarkblazeDragonBattleEffect.
   * GY SS double original ATK/DEF needs SS-origin flag. */
  return FALSE;
}

void ActivateDARKBLAZE_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(DARKBLAZE_DRAGON, 2);
}
