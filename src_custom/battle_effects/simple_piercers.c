#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "simple_piercers.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct SimplePiercerActionData {
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

extern struct SimplePiercerActionData sActionData;

static const u16 sPiercerIds[] APPEND_RODATA = {
  ENRAGED_BATTLE_OX,
  GRAVEKEEPERS_SPEAR_SOLDIER,
  DESTINY_HERO_DRILLDARK,
  EVIL_HERO_MALICIOUS_EDGE,
  EVIL_HERO_INFERNO_WING,
  EVIL_HERO_MALICIOUS_FIEND,
  GARONITH_LIGHTSWORN_DRAGON,
  MAJESTIC_MECH_GORYU,
  CHAOS_ANCIENT_GEAR_GIANT,
  ELEMENTAL_HERO_WILDEDGE,
  HAMON_LORD_OF_STRIKING_THUNDER,
  ARMITYLE_THE_CHAOS_PHANTASM,
  CELESTIAL_KNIGHTLORD_PARSHATH,
};

static u8 IsListedPiercer(u16 cardId)
{
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sPiercerIds); i++) {
    if (sPiercerIds[i] == cardId)
      return TRUE;
  }
  return FALSE;
}

static u8 ControllerHasBergamotLpHigher(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;
  u8 opp = controller == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  if (gDuelLifePoints[controller] <= gDuelLifePoints[opp])
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == AROMAGE_BERGAMOT)
      return TRUE;
  }
  return FALSE;
}

static u8 IsPiercingAttacker(u16 cardId, u8 controller)
{
  if (IsListedPiercer(cardId))
    return TRUE;
  if (Duel_CardHasMonsterType(cardId, TYPE_PLANT)
      && ControllerHasBergamotLpHigher(controller))
    return TRUE;
  return FALSE;
}

static void ApplyPiercingDamageToOpponent(u16 damage)
{
  if (damage == 0)
    return;
  if (gDuelLifePoints[DUEL_OPPONENT] <= damage) {
    gDuelLifePoints[DUEL_OPPONENT] = 0;
    sActionData.flags |= FLAG_LOSER_OPPONENT;
  } else {
    gDuelLifePoints[DUEL_OPPONENT] -= damage;
  }
  gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

static void ApplyPiercingDamageToPlayer(u16 damage)
{
  if (damage == 0)
    return;
  if (gDuelLifePoints[DUEL_PLAYER] <= damage) {
    gDuelLifePoints[DUEL_PLAYER] = 0;
    sActionData.flags |= FLAG_LOSER_PLAYER;
  } else {
    gDuelLifePoints[DUEL_PLAYER] -= damage;
  }
  gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
}

void ApplySimplePiercersBattleEffect(void)
{
  u16 atk;
  u16 def;

  if (sActionData.id == 2 && IsPiercingAttacker(sActionData.playerCardId, DUEL_PLAYER)
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    atk = sActionData.playerCardAtkOrLifePointsMod;
    def = sActionData.opponentCardDefense;
    if (atk > def)
      ApplyPiercingDamageToOpponent(atk - def);
    return;
  }

  if (sActionData.id == 5 && IsPiercingAttacker(sActionData.opponentCardId, DUEL_OPPONENT)
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    atk = sActionData.opponentCardAtkOrLifePointsMod;
    def = sActionData.playerCardDefense;
    if (atk > def)
      ApplyPiercingDamageToPlayer(atk - def);
  }
}
