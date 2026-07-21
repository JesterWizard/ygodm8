#include "global.h"
#include "common-chax.h"
#include "attack_pheromones.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct AttackPheromonesActionData {
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

extern struct AttackPheromonesActionData sActionData;

void ApplyAttackPheromonesBattleEffect(void)
{
  u8 attackerRow;
  u8 attackerCol;
  u8 defenderRow;
  u8 defenderCol;
  u16 attackerCardId;
  u8 attackerFixed;
  u8 defenderDestroyedFlag;
  struct DuelCard *defenderZone;

  /* id 2 = player attacks DEF; id 5 = opponent attacks DEF. */
  if (sActionData.id != 2 && sActionData.id != 5)
    return;

  if (sActionData.id == 2) {
    attackerCardId = sActionData.playerCardId;
    attackerRow = sActionData.playerMonsterRow;
    attackerCol = sActionData.unkA;
    defenderRow = sActionData.opponentMonsterRow;
    defenderCol = sActionData.unk16;
    attackerFixed = DUEL_PLAYER;
    defenderDestroyedFlag = FLAG_GRAVEYARD_OPPONENT;
  } else {
    attackerCardId = sActionData.opponentCardId;
    attackerRow = sActionData.opponentMonsterRow;
    attackerCol = sActionData.unk16;
    defenderRow = sActionData.playerMonsterRow;
    defenderCol = sActionData.unkA;
    attackerFixed = DUEL_OPPONENT;
    defenderDestroyedFlag = FLAG_GRAVEYARD_PLAYER;
  }

  if (attackerCardId == CARD_NONE)
    return;

  if (!Duel_CardHasMonsterType(attackerCardId, TYPE_REPTILE))
    return;

  if (Duel_FindBackrowCard(attackerFixed, ATTACK_PHEROMONES, TRUE) == NULL)
    return;

  if (sActionData.flags & defenderDestroyedFlag)
    return;

  defenderZone = gFixedZones[defenderRow][defenderCol];
  if (defenderZone == NULL || defenderZone->id == CARD_NONE || !defenderZone->isDefending)
    return;

  (void)attackerRow;
  (void)attackerCol;

  defenderZone->isDefending = FALSE;
  defenderZone->isFaceUp = TRUE;
  Duel_NotifyMonsterZoneChanged(defenderZone);
  Duel_RefreshMonsterStatOverlays();
}
