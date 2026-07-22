#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "magna_drago.h"

#define MAGNA_DRAGO_ATK_PER_HIT 200

struct MagnaActionData {
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

extern struct MagnaActionData sActionData;

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

u8 MagnaDrago_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;

  if (zone == NULL || zone->id != MAGNA_DRAGO)
    return FALSE;

  SetCardInfo(zone->id);
  atk = Duel_StatFromCount(zone->unk4, MAGNA_DRAGO_ATK_PER_HIT, gCardInfo.atk);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

static u8 DidMagnaDealBattleDamage(u8 attackerFixed)
{
  u16 damage;

  if (attackerFixed == DUEL_PLAYER) {
    if (sActionData.playerCardId != MAGNA_DRAGO)
      return FALSE;
    if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4)
      return FALSE;
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
  } else {
    if (sActionData.opponentCardId != MAGNA_DRAGO)
      return FALSE;
    if (sActionData.id != 5 && sActionData.id != 6)
      return FALSE;
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  }
  return damage > 0;
}

static void TryGainMagnaAtk(u8 fixedRow, u8 col)
{
  struct DuelCard *zone = gFixedZones[fixedRow][col];

  if (zone == NULL || zone->id != MAGNA_DRAGO)
    return;
  if (zone->unk4 < 255)
    zone->unk4++;

  Duel_ShowEffectTextTyped(MAGNA_DRAGO, 2);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}

void ApplyMagnaDragoBattleEffect(void)
{
  if (DidMagnaDealBattleDamage(DUEL_PLAYER)) {
    TryGainMagnaAtk(sActionData.playerMonsterRow, sActionData.unkA);
    return;
  }
  if (DidMagnaDealBattleDamage(DUEL_OPPONENT))
    TryGainMagnaAtk(sActionData.opponentMonsterRow, sActionData.unk16);
}

unsigned char CanActivateMAGNA_DRAGO(void)
{
  if (gMonEffect.id != MAGNA_DRAGO)
    return FALSE;

  /* +200 ATK on battle damage via ApplyMagnaDragoBattleEffect + dynamic overlay. */
  return FALSE;
}

void ActivateMAGNA_DRAGOEffect(void)
{
  Duel_ShowEffectTextTyped(MAGNA_DRAGO, 2);
}
