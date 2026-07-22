#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "clear_vice_dragon.h"
#include "monster_effect_usage.h"

struct ClearViceActionData {
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

extern struct ClearViceActionData sActionData;

static u8 IsClearViceAttackingMonster(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != CLEAR_VICE_DRAGON)
    return FALSE;

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 5)
    return FALSE;

  if (sActionData.playerCardId == CLEAR_VICE_DRAGON
      && gFixedZones[sActionData.playerMonsterRow][sActionData.unkA] == zone)
    return sActionData.opponentCardId != CARD_NONE;

  if (sActionData.opponentCardId == CLEAR_VICE_DRAGON
      && gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16] == zone)
    return sActionData.playerCardId != CARD_NONE;

  return FALSE;
}

void ApplyClearViceDragonDamageStepAtk(const struct DuelCard *zone)
{
  u16 targetAtk;

  if (!IsClearViceAttackingMonster(zone))
    return;

  if (sActionData.playerCardId == CLEAR_VICE_DRAGON)
    targetAtk = sActionData.opponentCardAtkOrLifePointsMod;
  else
    targetAtk = sActionData.playerCardAtkOrLifePointsMod;

  gCardInfo.atk = Duel_ClampStat((u32)targetAtk * 2);
}

unsigned char CanActivateCLEAR_VICE_DRAGON(void)
{
  if (gMonEffect.id != CLEAR_VICE_DRAGON)
    return FALSE;

  /* Battle ATK = 2× target via ApplyClearViceDragonDamageStepAtk.
   * ponytail: Clear World immunity + discard-to-save need continuous/destruction hooks.
   * Ceiling: not ignition-activatable here. */
  return FALSE;
}

void ActivateCLEAR_VICE_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(CLEAR_VICE_DRAGON, 2);
}
