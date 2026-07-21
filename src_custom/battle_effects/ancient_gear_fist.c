#include "global.h"
#include "common-chax.h"
#include "ancient_gear_fist.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct AncientGearFistActionData {
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

extern struct AncientGearFistActionData sActionData;

void ApplyAncientGearFistBattleEffect(void)
{
  struct DuelCard *playerZone;
  struct DuelCard *oppZone;

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 3
      && sActionData.id != 5)
    return;

  if (sActionData.playerCardId == CARD_NONE || sActionData.opponentCardId == CARD_NONE)
    return;

  playerZone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
  oppZone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];

  if (playerZone != NULL && playerZone->id == sActionData.playerCardId
      && DynamicEquipTargetsMonsterWithSpell(playerZone, ANCIENT_GEAR_FIST))
    sActionData.flags |= FLAG_GRAVEYARD_OPPONENT;

  if (oppZone != NULL && oppZone->id == sActionData.opponentCardId
      && DynamicEquipTargetsMonsterWithSpell(oppZone, ANCIENT_GEAR_FIST))
    sActionData.flags |= FLAG_GRAVEYARD_PLAYER;
}
