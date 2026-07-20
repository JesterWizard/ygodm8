#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "red_dragon_archfiend.h"

struct RedDragonArchfiendActionData {
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

extern struct RedDragonArchfiendActionData sActionData;
extern u8 gMonstersDeclaredAttackThisTurn[4];

void ClearRedDragonArchfiendPending(void)
{
  gPendingRedDragonArchfiendFixedRow = RED_DRAGON_ARCHFIEND_PENDING_NONE;
}

void ClearRedDragonArchfiendAttackDeclaredMask(void)
{
  u8 i;

  for (i = 0; i < 4; i++)
    gMonstersDeclaredAttackThisTurn[i] = 0;
}

void MarkMonsterDeclaredAttackThisTurn(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (!Duel_FindFixedZone(zone, &fixedRow, &col))
    return;

  if (fixedRow > PLAYER_BACKROW)
    return;

  gMonstersDeclaredAttackThisTurn[fixedRow] |= (u8)(1u << col);
}

static u8 IsDefendingMonster(struct DuelCard *zone)
{
  return zone != NULL && zone->id != CARD_NONE && zone->isDefending == TRUE;
}

static u8 BattledMonsterWasDefending(void)
{
  struct DuelCard *zone;

  if (sActionData.id == 2 && sActionData.playerCardId == RED_DRAGON_ARCHFIEND) {
    zone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    return zone != NULL && zone->isDefending == TRUE;
  }

  if (sActionData.id == 5 && sActionData.opponentCardId == RED_DRAGON_ARCHFIEND) {
    zone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    return zone != NULL && zone->isDefending == TRUE;
  }

  return FALSE;
}

static u8 OpponentFixedRowForRedDragon(void)
{
  if (sActionData.id == 2 && sActionData.playerCardId == RED_DRAGON_ARCHFIEND)
    return sActionData.opponentMonsterRow;
  if (sActionData.id == 5 && sActionData.opponentCardId == RED_DRAGON_ARCHFIEND)
    return sActionData.playerMonsterRow;
  return RED_DRAGON_ARCHFIEND_PENDING_NONE;
}

static void DestroyAllDefendingOnFixedRow(u8 fixedRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];
    u8 graveyardDuelist;

    if (!IsDefendingMonster(zone))
      continue;

    graveyardDuelist = GetDuelistForZone(zone);
    ClearZoneAndSendMonToGraveyard2(zone, graveyardDuelist);
  }
}

void ResolveRedDragonArchfiendBattleEffect(void)
{
  u8 fixedRow;

  fixedRow = gPendingRedDragonArchfiendFixedRow;
  if (fixedRow == RED_DRAGON_ARCHFIEND_PENDING_NONE)
    return;

  ClearRedDragonArchfiendPending();
  Duel_ShowEffectText(RED_DRAGON_ARCHFIEND);
  DestroyAllDefendingOnFixedRow(fixedRow);
}

void ApplyRedDragonArchfiendBattleEffect(void)
{
  u8 fixedRow;

  if (gHideEffectText)
    return;

  if (sActionData.id != 2 && sActionData.id != 5)
    return;

  if (!BattledMonsterWasDefending())
    return;

  fixedRow = OpponentFixedRowForRedDragon();
  if (fixedRow == RED_DRAGON_ARCHFIEND_PENDING_NONE)
    return;

  gPendingRedDragonArchfiendFixedRow = fixedRow;

  if (gUnk2023EA0.unk18 == 0)
    ResolveRedDragonArchfiendBattleEffect();
}

static u8 ActiveDuelistMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static struct DuelCard *FindFaceUpRedDragonArchfiend(u8 *outCol)
{
  u8 col;
  u8 row = ActiveDuelistMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone->id == RED_DRAGON_ARCHFIEND && zone->isFaceUp) {
      *outCol = col;
      return zone;
    }
  }

  return NULL;
}

void TryApplyRedDragonArchfiendEndPhaseEffect(void)
{
  u8 rdaCol;
  u8 col;
  u8 row;
  u8 attackMask;
  struct DuelCard *rda;

  if (IsDuelOver() == TRUE || gHideEffectText)
    return;

  rda = FindFaceUpRedDragonArchfiend(&rdaCol);
  if (rda == NULL)
    return;

  row = ActiveDuelistMonsterFixedRow();
  attackMask = gMonstersDeclaredAttackThisTurn[row];

  Duel_ShowEffectText(RED_DRAGON_ARCHFIEND);
  if (IsDuelOver() == TRUE)
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == rda || zone->id == CARD_NONE)
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    if (IsGodCard(zone->id))
      continue;

    /* Did not declare an attack this turn. */
    if ((attackMask & (1u << col)) != 0)
      continue;

    if (Duel_DestroyZone(zone, GetDuelistForZone(zone), TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }
}
