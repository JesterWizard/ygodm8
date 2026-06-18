#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "des_kangaroo.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct DesKangarooActionData {
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

extern struct DesKangarooActionData sActionData;

void ClearDesKangarooPending(void)
{
  gPendingDesKangarooAttackerRow = DES_KANGAROO_PENDING_NONE;
  gPendingDesKangarooAttackerCol = 0;
}

static u8 MarkPendingAttackerDestroy(u8 attackerRow, u8 attackerCol, u16 attackerCardId)
{
  struct DuelCard *zone;

  if (attackerCardId == CARD_NONE || attackerRow >= 5 || attackerCol >= MAX_ZONES_IN_ROW)
    return FALSE;

  zone = gFixedZones[attackerRow][attackerCol];
  if (zone == NULL || zone->id != attackerCardId)
    return FALSE;

  gPendingDesKangarooAttackerRow = attackerRow;
  gPendingDesKangarooAttackerCol = attackerCol;
  return TRUE;
}

static u8 TryMarkDesKangarooDestroyAttacker(void)
{
  u8 attackerRow;
  u8 attackerCol;
  u16 attackerCardId;
  u16 attackerAtk;
  u16 defenderDef;

  if (sActionData.id != 2 && sActionData.id != 5)
    return FALSE;

  if (sActionData.id == 2) {
    if (sActionData.opponentCardId != DES_KANGAROO)
      return FALSE;
    if (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      return FALSE;
    attackerAtk = sActionData.playerCardAtkOrLifePointsMod;
    defenderDef = sActionData.opponentCardDefense;
    attackerRow = sActionData.playerMonsterRow;
    attackerCol = sActionData.unkA;
    attackerCardId = sActionData.playerCardId;
  } else {
    if (sActionData.playerCardId != DES_KANGAROO)
      return FALSE;
    if (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      return FALSE;
    attackerAtk = sActionData.opponentCardAtkOrLifePointsMod;
    defenderDef = sActionData.playerCardDefense;
    attackerRow = sActionData.opponentMonsterRow;
    attackerCol = sActionData.unk16;
    attackerCardId = sActionData.opponentCardId;
  }

  if (attackerAtk >= defenderDef)
    return FALSE;

  return MarkPendingAttackerDestroy(attackerRow, attackerCol, attackerCardId);
}

void ResolveDesKangarooBattleEffect(void)
{
  u8 attackerRow;
  u8 attackerCol;
  struct DuelCard *zone;
  u8 graveyardDuelist;

  attackerRow = gPendingDesKangarooAttackerRow;
  if (attackerRow == DES_KANGAROO_PENDING_NONE)
    return;

  attackerCol = gPendingDesKangarooAttackerCol;
  ClearDesKangarooPending();

  zone = gFixedZones[attackerRow][attackerCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return;

  graveyardDuelist = GetDuelistForZone(zone);
  if (graveyardDuelist == 0xFF)
    return;

  Duel_ShowEffectTextTyped(DES_KANGAROO, 3);
  if (IsDuelOver() == TRUE)
    return;

  if (zone->id != CARD_NONE)
    Duel_DestroyZone(zone, graveyardDuelist, TRUE);
}

void ApplyDesKangarooBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (!TryMarkDesKangarooDestroyAttacker()) {
    ClearDesKangarooPending();
    return;
  }

  /* Defer until battle animation finishes (sub_8040EF0 / player attack resolve). */
  if (gUnk2023EA0.unk18 == 0)
    ResolveDesKangarooBattleEffect();
}
