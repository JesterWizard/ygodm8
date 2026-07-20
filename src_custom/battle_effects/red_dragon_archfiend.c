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

void ClearRedDragonArchfiendPending(void)
{
  gPendingRedDragonArchfiendFixedRow = RED_DRAGON_ARCHFIEND_PENDING_NONE;
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

/* ponytail: End Phase destroy other non-attacking monsters FALSE — no EP attacker tracking. */
