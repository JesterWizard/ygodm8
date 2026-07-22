#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "mucus_yolk.h"

#define MUCUS_YOLK_ATK_PER_STACK 1000
#define MUCUS_YOLK_PENDING 0x80
#define MUCUS_YOLK_STACKS 0x7F

struct MucusActionData {
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

extern struct MucusActionData sActionData;

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

static u8 sMucusInit APPEND_DATA = {0};

u8 CanMucusYolkAttackDirectly(u16 cardId)
{
  return cardId == MUCUS_YOLK;
}

u8 MucusYolk_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;
  u8 stacks;

  if (zone == NULL || zone->id != MUCUS_YOLK)
    return FALSE;

  stacks = zone->unk4 & MUCUS_YOLK_STACKS;
  SetCardInfo(zone->id);
  atk = Duel_StatFromCount(stacks, MUCUS_YOLK_ATK_PER_STACK, gCardInfo.atk);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

static u8 DidMucusDealBattleDamage(u8 attackerFixed)
{
  u16 damage;

  if (attackerFixed == DUEL_PLAYER) {
    if (sActionData.playerCardId != MUCUS_YOLK)
      return FALSE;
    if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4)
      return FALSE;
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
  } else {
    if (sActionData.opponentCardId != MUCUS_YOLK)
      return FALSE;
    if (sActionData.id != 5 && sActionData.id != 6)
      return FALSE;
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  }
  return damage > 0;
}

static void MarkMucusPending(u8 fixedRow, u8 col)
{
  struct DuelCard *zone = gFixedZones[fixedRow][col];

  if (zone == NULL || zone->id != MUCUS_YOLK)
    return;
  zone->unk4 |= MUCUS_YOLK_PENDING;
}

void ApplyMucusYolkBattleEffect(void)
{
  if (DidMucusDealBattleDamage(DUEL_PLAYER)) {
    MarkMucusPending(sActionData.playerMonsterRow, sActionData.unkA);
    return;
  }
  if (DidMucusDealBattleDamage(DUEL_OPPONENT))
    MarkMucusPending(sActionData.opponentMonsterRow, sActionData.unk16);
}

static void OnMucusStandby(const struct EffectEvent *ev)
{
  u8 row;
  u8 col;
  u8 controller;

  (void)ev;

  for (controller = DUEL_PLAYER; controller <= DUEL_OPPONENT; controller++) {
    /* Own Standby only. */
    if ((controller == DUEL_PLAYER) != (WhoseTurn() == DUEL_PLAYER))
      continue;

    row = Duel_FixedMonsterRowForDuelist(controller);
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];
      u8 stacks;

      if (zone == NULL || zone->id != MUCUS_YOLK)
        continue;
      if ((zone->unk4 & MUCUS_YOLK_PENDING) == 0)
        continue;

      stacks = zone->unk4 & MUCUS_YOLK_STACKS;
      if (stacks < MUCUS_YOLK_STACKS)
        stacks++;
      zone->unk4 = stacks;
      Duel_ShowEffectTextTyped(MUCUS_YOLK, 2);
    }
  }

  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}

void MucusYolk_EnsureInit(void)
{
  if (sMucusInit)
    return;
  sMucusInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_TURN_STANDBY, OnMucusStandby);
}

unsigned char CanActivateMUCUS_YOLK(void)
{
  if (gMonEffect.id != MUCUS_YOLK)
    return FALSE;

  /* Direct + Standby ATK via CanMucusYolkAttackDirectly / ApplyMucusYolkBattleEffect. */
  return FALSE;
}

void ActivateMUCUS_YOLKEffect(void)
{
  Duel_ShowEffectTextTyped(MUCUS_YOLK, 2);
}
