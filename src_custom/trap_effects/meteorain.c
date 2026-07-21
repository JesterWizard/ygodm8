#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "meteorain.h"

void UpdateDuelGfxExceptField(void);

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_OPPONENT 16
#define FLAG_LOSER_PLAYER 4

struct MeteorainActionData {
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
};

extern struct MeteorainActionData sActionData;
u8 CanMonsterBeDestroyedByBattle(u16 cardId, u8 fixedDuelist, u16 defStat, u16 atkStat);

static u8 MeteorainActiveForAttacker(u8 attackerRow)
{
  u8 controller = Duel_FixedDuelistForMonsterRow(attackerRow);
  struct DuelCard *zone = Duel_FindBackrowCard(controller, METEORAIN, TRUE);

  return zone != NULL && zone->unk4 != 0;
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
}

void ApplyMeteorainPiercingBattleEffect(void)
{
  u16 attackerAtk;
  u16 defenderDef;
  u16 damage;

  if (sActionData.id == 2 && MeteorainActiveForAttacker(sActionData.playerMonsterRow)) {
    attackerAtk = sActionData.playerCardAtkOrLifePointsMod;
    defenderDef = sActionData.opponentCardDefense;
    if (attackerAtk <= defenderDef)
      return;
    if (CanMonsterBeDestroyedByBattle(
            sActionData.opponentCardId, DUEL_OPPONENT,
            sActionData.opponentCardAtkOrLifePointsMod,
            sActionData.playerCardAtkOrLifePointsMod))
      sActionData.flags |= FLAG_GRAVEYARD_OPPONENT;
    damage = attackerAtk - defenderDef;
    ApplyPiercingDamageToOpponent(damage);
    return;
  }

  if (sActionData.id == 5 && MeteorainActiveForAttacker(sActionData.opponentMonsterRow)) {
    attackerAtk = sActionData.opponentCardAtkOrLifePointsMod;
    defenderDef = sActionData.playerCardDefense;
    if (attackerAtk <= defenderDef)
      return;
    if (CanMonsterBeDestroyedByBattle(
            sActionData.playerCardId, DUEL_PLAYER,
            sActionData.playerCardAtkOrLifePointsMod,
            sActionData.opponentCardAtkOrLifePointsMod))
      sActionData.flags |= FLAG_GRAVEYARD_PLAYER;
    damage = attackerAtk - defenderDef;
    ApplyPiercingDamageToPlayer(damage);
  }
}

void Meteorain_ClearOnTurnBoundary(void)
{
  u8 duelist;
  u8 col;
  u8 backrow;

  for (duelist = DUEL_PLAYER; duelist <= DUEL_OPPONENT; duelist++) {
    backrow = duelist == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[backrow][col];

      if (zone != NULL && zone->id == METEORAIN) {
        zone->unk4 = 0;
        if (zone->isFaceUp)
          Duel_DestroyZone(zone, duelist, FALSE);
      }
    }
  }
}

APPEND_TEXT void EffectMETEORAIN(void)
{
  struct DuelCard *trapZone =
      gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];

  Duel_ShowTrapResponseText(METEORAIN, gTrapEffectData.originCardId);

  if (trapZone != NULL) {
    Duel_ActivateContinuousZone(trapZone);
    trapZone->unk4 = 1;
  }

  UpdateDuelGfxExceptField();
}
