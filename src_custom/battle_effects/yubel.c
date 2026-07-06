#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "yubel.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct YubelActionData {
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

extern struct YubelActionData sActionData;
extern u8 gPendingYubelUltimateDestroyRow;
extern u8 gPendingYubelUltimateDestroyCol;

void Yubel_ClearBattlePending(void)
{
  gPendingYubelUltimateDestroyRow = YUBEL_PENDING_DESTROY_NONE;
  gPendingYubelUltimateDestroyCol = 0;
}

u8 Yubel_IsFamilyCard(u16 cardId)
{
  return cardId == YUBEL || cardId == YUBEL_TERROR_INCARNATE
      || cardId == YUBEL_THE_ULTIMATE_NIGHTMARE;
}

u8 Yubel_IsEvolutionForm(u16 cardId)
{
  return cardId == YUBEL_TERROR_INCARNATE || cardId == YUBEL_THE_ULTIMATE_NIGHTMARE;
}

static u8 IsMonsterBattleAction(u8 id)
{
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

static u8 ZoneIsFaceUpAtkMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return zone->isFaceUp && !zone->isDefending;
}

static u8 IsYubelReflectCard(u16 cardId)
{
  return cardId == YUBEL || cardId == YUBEL_TERROR_INCARNATE;
}

static void InflictBattleBurn(u8 targetDuelist, u16 damage)
{
  if (damage == 0)
    return;

  if (gDuelLifePoints[targetDuelist] <= damage) {
    gDuelLifePoints[targetDuelist] = 0;
    if (targetDuelist == DUEL_PLAYER)
      sActionData.flags |= FLAG_LOSER_PLAYER;
    else
      sActionData.flags |= FLAG_LOSER_OPPONENT;
  } else {
    gDuelLifePoints[targetDuelist] -= damage;
  }

  gUnk2023EA0.unk0[targetDuelist].lifePointsAfterDamage = gDuelLifePoints[targetDuelist];
  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

static void ApplyYubelNoBattleDamage(void)
{
  u16 playerDamage;
  u16 opponentDamage;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  playerDamage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  opponentDamage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];

  if (Yubel_IsFamilyCard(sActionData.playerCardId) && playerDamage > 0) {
    gDuelLifePoints[DUEL_PLAYER] = gUnk2023EA0.unk0[0].initialLifePoints;
    gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
    sActionData.flags &= ~FLAG_LOSER_PLAYER;
  }

  if (Yubel_IsFamilyCard(sActionData.opponentCardId) && opponentDamage > 0) {
    gDuelLifePoints[DUEL_OPPONENT] = gUnk2023EA0.unk0[1].initialLifePoints;
    gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
    sActionData.flags &= ~FLAG_LOSER_OPPONENT;
  }

  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

static void ApplyYubelAttackedReflect(void)
{
  struct DuelCard *defenderZone;
  u16 attackerAtk;
  u8 burnTarget;
  u16 defenderCardId;

  if (sActionData.id != 2 && sActionData.id != 5)
    return;

  if (sActionData.id == 5) {
    defenderCardId = sActionData.playerCardId;
    defenderZone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    attackerAtk = sActionData.opponentCardAtkOrLifePointsMod;
    burnTarget = DUEL_OPPONENT;
  } else {
    defenderCardId = sActionData.opponentCardId;
    defenderZone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    attackerAtk = sActionData.playerCardAtkOrLifePointsMod;
    burnTarget = DUEL_PLAYER;
  }

  if (!IsYubelReflectCard(defenderCardId))
    return;

  if (!ZoneIsFaceUpAtkMonster(defenderZone))
    return;

  if (gHideEffectText)
    return;

  Duel_ShowEffectTextTyped(defenderCardId, 3);
  InflictBattleBurn(burnTarget, attackerAtk);
}

static void MarkUltimateDestroyTarget(u8 targetRow, u8 targetCol)
{
  gPendingYubelUltimateDestroyRow = targetRow;
  gPendingYubelUltimateDestroyCol = targetCol;
}

static void ApplyYubelUltimateNightmarePostBattle(void)
{
  struct DuelCard *yubelZone;
  struct DuelCard *otherZone;
  u16 otherAtk;
  u8 burnTarget;
  u16 yubelCardId;

  if (sActionData.id != 2 && sActionData.id != 5)
    return;

  if (sActionData.id == 2 && sActionData.playerCardId == YUBEL_THE_ULTIMATE_NIGHTMARE) {
    yubelCardId = sActionData.playerCardId;
    yubelZone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    otherZone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    otherAtk = sActionData.opponentCardAtkOrLifePointsMod;
    burnTarget = DUEL_OPPONENT;
  } else if (sActionData.id == 5 && sActionData.playerCardId == YUBEL_THE_ULTIMATE_NIGHTMARE) {
    yubelCardId = sActionData.playerCardId;
    yubelZone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    otherZone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    otherAtk = sActionData.opponentCardAtkOrLifePointsMod;
    burnTarget = DUEL_OPPONENT;
  } else if (sActionData.id == 2 && sActionData.opponentCardId == YUBEL_THE_ULTIMATE_NIGHTMARE) {
    yubelCardId = sActionData.opponentCardId;
    yubelZone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    otherZone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    otherAtk = sActionData.playerCardAtkOrLifePointsMod;
    burnTarget = DUEL_PLAYER;
  } else {
    return;
  }

  if (otherZone == NULL || otherZone->id == CARD_NONE)
    return;

  if (!ZoneIsFaceUpAtkMonster(yubelZone))
    return;

  if (gHideEffectText)
    return;

  Duel_ShowEffectTextTyped(yubelCardId, 3);
  InflictBattleBurn(burnTarget, otherAtk);

  if (sActionData.id == 2 && sActionData.playerCardId == YUBEL_THE_ULTIMATE_NIGHTMARE)
    MarkUltimateDestroyTarget(sActionData.opponentMonsterRow, sActionData.unk16);
  else if (sActionData.id == 5 && sActionData.playerCardId == YUBEL_THE_ULTIMATE_NIGHTMARE)
    MarkUltimateDestroyTarget(sActionData.opponentMonsterRow, sActionData.unk16);
  else
    MarkUltimateDestroyTarget(sActionData.playerMonsterRow, sActionData.unkA);

  if (gUnk2023EA0.unk18 == 0)
    ResolveYubelUltimateNightmareBattleEffect();
}

void ResolveYubelUltimateNightmareBattleEffect(void)
{
  u8 targetRow;
  u8 targetCol;
  struct DuelCard *zone;
  u8 graveyardDuelist;

  targetRow = gPendingYubelUltimateDestroyRow;
  if (targetRow == YUBEL_PENDING_DESTROY_NONE)
    return;

  targetCol = gPendingYubelUltimateDestroyCol;
  Yubel_ClearBattlePending();

  zone = gFixedZones[targetRow][targetCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return;

  graveyardDuelist = GetDuelistForZone(zone);
  if (graveyardDuelist == 0xFF)
    return;

  if (Duel_DestroyZone(zone, graveyardDuelist, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}

void ApplyYubelBattleEffects(void)
{
  ApplyYubelNoBattleDamage();
  ApplyYubelAttackedReflect();
  ApplyYubelUltimateNightmarePostBattle();
}
