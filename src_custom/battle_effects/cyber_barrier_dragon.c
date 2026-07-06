#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "cyber_barrier_dragon.h"

void LockMonsterCardsInRow(unsigned char turnRow);

static u8 ColumnHasUnusedCyberBarrierDragon(u8 col, struct DuelCard **outZone)
{
  struct DuelCard *zone;

  if ((gCyberBarrierDragonUsedMask & (1u << col)) != 0)
    return FALSE;

  zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];
  if (zone == NULL || zone->id != CYBER_BARRIER_DRAGON)
    return FALSE;
  if (!zone->isFaceUp || zone->isDefending)
    return FALSE;

  *outZone = zone;
  return TRUE;
}

void ClearCyberBarrierDragonTurnState(void)
{
  gCyberBarrierDragonUsedMask = 0;
}

u8 TryNegateDeclaredAttackWithCyberBarrierDragon(void)
{
  u8 col;
  struct DuelCard *barrier;
  u16 attackerCardId;

  attackerCardId = gTrapEffectData.originCardId;
  if (attackerCardId == CARD_NONE)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!ColumnHasUnusedCyberBarrierDragon(col, &barrier))
      continue;

    gCyberBarrierDragonUsedMask |= 1u << col;
    LockMonsterCardsInRow(ACTIVE_DUELIST_MONSTER_ROW);

    /* ponytail: Duel_ShowEffectText naturally skips during AI sim (gHideEffectText)
     * but fires on real gameplay. No forced override — that would block the sim loop. */
    gCardEffectTextData.cardId2 = attackerCardId;
    Duel_ShowEffectText(CYBER_BARRIER_DRAGON);

    return TRUE;
  }

  return FALSE;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void CyberBarrierDragon_SelfCheck(void)
{
  u8 savedMask = gCyberBarrierDragonUsedMask;
  u8 savedTurn = gWhoseTurn;
  struct DuelCard savedZone = *gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][0];

  gWhoseTurn = DUEL_OPPONENT;
  gTrapEffectData.originCardId = CYBER_DRAGON;
  gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][0]->id = CYBER_BARRIER_DRAGON;
  gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][0]->isFaceUp = TRUE;
  gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][0]->isDefending = FALSE;
  gCyberBarrierDragonUsedMask = 0;

  if (!TryNegateDeclaredAttackWithCyberBarrierDragon())
    while (1)
      ;
  if (gCyberBarrierDragonUsedMask != 1)
    while (1)
      ;

  if (TryNegateDeclaredAttackWithCyberBarrierDragon())
    while (1)
      ;

  gCyberBarrierDragonUsedMask = savedMask;
  gWhoseTurn = savedTurn;
  *gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][0] = savedZone;
  gTrapEffectData.originCardId = CARD_NONE;
}
#endif
