#include "global.h"
#include "common-chax.h"
#include "bubble_blaster.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct BubbleBlasterActionData {
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

extern struct BubbleBlasterActionData sActionData;

static u8 IsMonsterVersusMonsterBattleAction(u8 actionId)
{
  return actionId == 1 || actionId == 2 || actionId == 3 || actionId == 5;
}

static struct DuelCard *FindBubbleBlasterSpellForTarget(u8 targetRow, u8 targetCol)
{
  u8 i;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    struct DynamicEquipLink *link = &gDynamicEquipLinks[i];
    struct DuelCard *spellZone;

    if (!link->active || link->spellId != BUBBLE_BLASTER)
      continue;

    if (link->targetFixedRow != targetRow || link->targetFixedCol != targetCol)
      continue;

    spellZone = gFixedZones[link->spellFixedRow][link->spellFixedCol];
    if (IsActiveDynamicEquipSpellZone(spellZone))
      return spellZone;
  }

  return NULL;
}

static void ZeroBattleDamageForPlayer(void)
{
  u16 damage;

  damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  if (damage == 0)
    return;

  gDuelLifePoints[DUEL_PLAYER] = gUnk2023EA0.unk0[0].initialLifePoints;
  gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  sActionData.flags &= (u8)~4u;
}

static void ZeroBattleDamageForOpponent(void)
{
  u16 damage;

  damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
  if (damage == 0)
    return;

  gDuelLifePoints[DUEL_OPPONENT] = gUnk2023EA0.unk0[1].initialLifePoints;
  gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
  sActionData.flags &= (u8)~16u;
}

static void DestroyBubbleBlasterInstead(struct DuelCard *targetZone, struct DuelCard *spellZone)
{
  u8 graveyardDuelist;

  if (spellZone == NULL || spellZone->id != BUBBLE_BLASTER)
    return;

  (void)targetZone;

  graveyardDuelist = GetDuelistForZone(spellZone);
  if (graveyardDuelist == 0xFF)
    return;

  Duel_ShowEffectTextTyped(BUBBLE_BLASTER, 3);
  if (IsDuelOver() == TRUE)
    return;

  if (spellZone->id != CARD_NONE)
    Duel_DestroyZone(spellZone, graveyardDuelist, TRUE);
}

void ApplyBubbleBlasterBattleProtection(void)
{
  struct DuelCard *zone;
  struct DuelCard *spellZone;

  if (!IsMonsterVersusMonsterBattleAction(sActionData.id))
    return;

  if ((sActionData.flags & FLAG_GRAVEYARD_PLAYER) && sActionData.playerCardId != CARD_NONE) {
    zone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    if (DynamicEquipTargetsMonsterWithSpell(zone, BUBBLE_BLASTER)) {
      spellZone = FindBubbleBlasterSpellForTarget(sActionData.playerMonsterRow, sActionData.unkA);
      sActionData.flags &= (u8)~FLAG_GRAVEYARD_PLAYER;
      ZeroBattleDamageForPlayer();
      DestroyBubbleBlasterInstead(zone, spellZone);
    }
  }

  if ((sActionData.flags & FLAG_GRAVEYARD_OPPONENT) && sActionData.opponentCardId != CARD_NONE) {
    zone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    if (DynamicEquipTargetsMonsterWithSpell(zone, BUBBLE_BLASTER)) {
      spellZone =
          FindBubbleBlasterSpellForTarget(sActionData.opponentMonsterRow, sActionData.unk16);
      sActionData.flags &= (u8)~FLAG_GRAVEYARD_OPPONENT;
      ZeroBattleDamageForOpponent();
      DestroyBubbleBlasterInstead(zone, spellZone);
    }
  }
}
