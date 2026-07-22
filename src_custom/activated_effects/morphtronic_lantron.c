#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "morphtronic_lantron.h"
#include "monster_effect_usage.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct MorphtronicLantronActionData {
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

extern struct MorphtronicLantronActionData sActionData;

static u8 sLantronNoDamageDuelist APPEND_DATA = {0xFF};

void MorphtronicLantron_ClearTurnState(void)
{
  sLantronNoDamageDuelist = 0xFF;
}

void MorphtronicLantron_MarkDefDestroyed(void)
{
  struct DuelCard *zone;

  if (sActionData.flags & FLAG_GRAVEYARD_PLAYER) {
    zone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    if (zone != NULL && zone->id == MORPHTRONIC_LANTRON && zone->isDefending)
      sLantronNoDamageDuelist = DUEL_PLAYER;
  }

  if (sActionData.flags & FLAG_GRAVEYARD_OPPONENT) {
    zone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    if (zone != NULL && zone->id == MORPHTRONIC_LANTRON && zone->isDefending)
      sLantronNoDamageDuelist = DUEL_OPPONENT;
  }
}

void ApplyMorphtronicLantronNoBattleDamage(void)
{
  u16 playerDamage;
  u16 opponentDamage;

  if (sLantronNoDamageDuelist > DUEL_OPPONENT)
    return;

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4
      && sActionData.id != 5 && sActionData.id != 6)
    return;

  playerDamage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  opponentDamage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];

  if (sLantronNoDamageDuelist == DUEL_PLAYER && playerDamage > 0) {
    gDuelLifePoints[DUEL_PLAYER] = gUnk2023EA0.unk0[0].initialLifePoints;
    gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
    sActionData.flags &= (u8)~FLAG_LOSER_PLAYER;
  }

  if (sLantronNoDamageDuelist == DUEL_OPPONENT && opponentDamage > 0) {
    gDuelLifePoints[DUEL_OPPONENT] = gUnk2023EA0.unk0[1].initialLifePoints;
    gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
    sActionData.flags &= (u8)~FLAG_LOSER_OPPONENT;
  }

  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

unsigned char CanActivateMORPHTRONIC_LANTRON(void)
{
  if (gMonEffect.id != MORPHTRONIC_LANTRON)
    return FALSE;

  /* DEF destroy → no battle damage this turn via ApplyMorphtronicLantronNoBattleDamage.
   * Ceiling: ATK redirect effect damage needs effect-damage hook. */
  return FALSE;
}

void ActivateMORPHTRONIC_LANTRONEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_LANTRON, 2);
}
