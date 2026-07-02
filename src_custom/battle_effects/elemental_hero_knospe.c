#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_knospe.h"

struct ElementalHeroKnospeActionData {
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

extern struct ElementalHeroKnospeActionData sActionData;

static u8 IsPlayerAttackAction(u8 id)
{
  return id == 1 || id == 2 || id == 4;
}

static u8 IsOpponentAttackAction(u8 id)
{
  return id == 5 || id == 6;
}

static void ApplyBattleDamageBoost(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ELEMENTAL_HERO_KNOSPE)
    return;

  if (zone->permStage < 127)
    zone->permStage++;

  Duel_NotifyMonsterZoneChanged(zone);
}

void ApplyElementalHeroKnospeBattleEffect(void)
{
  struct DuelCard *zone;

  if (IsPlayerAttackAction(sActionData.id)
      && sActionData.playerCardId == ELEMENTAL_HERO_KNOSPE
      && gUnk2023EA0.unk0[1].initialLifePoints > gDuelLifePoints[DUEL_OPPONENT]) {
    zone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    ApplyBattleDamageBoost(zone);
    return;
  }

  if (IsOpponentAttackAction(sActionData.id)
      && sActionData.opponentCardId == ELEMENTAL_HERO_KNOSPE
      && gUnk2023EA0.unk0[0].initialLifePoints > gDuelLifePoints[DUEL_PLAYER]) {
    zone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    ApplyBattleDamageBoost(zone);
  }
}
