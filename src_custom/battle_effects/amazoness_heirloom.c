#include "global.h"
#include "common-chax.h"
#include "amazoness_heirloom.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct AmazonessHeirloomActionData {
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

extern struct AmazonessHeirloomActionData sActionData;

void ClearAmazonessHeirloomPending(void)
{
  gPendingAmazonessHeirloomDefenderRow = AMAZONESS_HEIRLOOM_PENDING_NONE;
  gPendingAmazonessHeirloomDefenderCol = 0;
}

void ApplyAmazonessHeirloomBattleProtection(void)
{
  struct DuelCard *zone;

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 3
      && sActionData.id != 5)
    return;

  if ((sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !EffectOpt_IsUsed(AMAZONESS_HEIRLOOM)) {
    zone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    if (DynamicEquipTargetsMonsterWithSpell(zone, AMAZONESS_HEIRLOOM)) {
      sActionData.flags &= (u8)~FLAG_GRAVEYARD_PLAYER;
      EffectOpt_MarkUsed(AMAZONESS_HEIRLOOM);
    }
  }

  if ((sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !EffectOpt_IsUsed(AMAZONESS_HEIRLOOM)) {
    zone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    if (DynamicEquipTargetsMonsterWithSpell(zone, AMAZONESS_HEIRLOOM)) {
      sActionData.flags &= (u8)~FLAG_GRAVEYARD_OPPONENT;
      EffectOpt_MarkUsed(AMAZONESS_HEIRLOOM);
    }
  }
}

static u8 MarkPendingDefenderDestroy(u8 defenderRow, u8 defenderCol, u16 defenderCardId)
{
  struct DuelCard *zone;

  if (defenderCardId == CARD_NONE || defenderRow >= 5 || defenderCol >= MAX_ZONES_IN_ROW)
    return FALSE;

  zone = gFixedZones[defenderRow][defenderCol];
  if (zone == NULL || zone->id != defenderCardId)
    return FALSE;

  gPendingAmazonessHeirloomDefenderRow = defenderRow;
  gPendingAmazonessHeirloomDefenderCol = defenderCol;
  return TRUE;
}

static u8 TryMarkHeirloomDestroyDefender(void)
{
  struct DuelCard *attacker;
  u8 attackerRow;
  u8 attackerCol;
  u8 defenderRow;
  u8 defenderCol;
  u16 defenderCardId;

  /* Monster vs monster: player attacks (1/2) or opponent attacks (3/5). */
  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 3
      && sActionData.id != 5)
    return FALSE;

  if (sActionData.id == 1 || sActionData.id == 2) {
    attackerRow = sActionData.playerMonsterRow;
    attackerCol = sActionData.unkA;
    defenderRow = sActionData.opponentMonsterRow;
    defenderCol = sActionData.unk16;
    defenderCardId = sActionData.opponentCardId;
  } else {
    attackerRow = sActionData.opponentMonsterRow;
    attackerCol = sActionData.unk16;
    defenderRow = sActionData.playerMonsterRow;
    defenderCol = sActionData.unkA;
    defenderCardId = sActionData.playerCardId;
  }

  if (defenderCardId == CARD_NONE)
    return FALSE;

  attacker = gFixedZones[attackerRow][attackerCol];
  if (!DynamicEquipTargetsMonsterWithSpell(attacker, AMAZONESS_HEIRLOOM))
    return FALSE;

  return MarkPendingDefenderDestroy(defenderRow, defenderCol, defenderCardId);
}

void ResolveAmazonessHeirloomBattleEffect(void)
{
  u8 defenderRow;
  u8 defenderCol;
  struct DuelCard *zone;
  u8 graveyardDuelist;

  defenderRow = gPendingAmazonessHeirloomDefenderRow;
  if (defenderRow == AMAZONESS_HEIRLOOM_PENDING_NONE)
    return;

  defenderCol = gPendingAmazonessHeirloomDefenderCol;
  ClearAmazonessHeirloomPending();

  zone = gFixedZones[defenderRow][defenderCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return;

  graveyardDuelist = GetDuelistForZone(zone);
  if (graveyardDuelist == 0xFF)
    return;

  Duel_ShowEffectTextTyped(AMAZONESS_HEIRLOOM, 3);
  if (IsDuelOver() == TRUE)
    return;

  if (zone->id != CARD_NONE)
    Duel_DestroyZone(zone, graveyardDuelist, TRUE);
}

void ApplyAmazonessHeirloomBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (!TryMarkHeirloomDestroyDefender()) {
    ClearAmazonessHeirloomPending();
    return;
  }

  if (gUnk2023EA0.unk18 == 0)
    ResolveAmazonessHeirloomBattleEffect();
}
