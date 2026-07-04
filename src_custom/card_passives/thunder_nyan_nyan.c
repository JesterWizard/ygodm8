#include "global.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "thunder_nyan_nyan.h"

extern const u8 gCardAttributes[];

static u8 OpponentControlsFaceUpShadowMonster(void)
{
  u8 col;
  struct DuelCard *zone;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];
    if (zone->id == CARD_NONE || !zone->isFaceUp)
      continue;
    if (gCardAttributes[zone->id] == ATTRIBUTE_SHADOW)
      return TRUE;
  }

  return FALSE;
}

u8 CanThunderNyanNyanAttackDirectly(u16 cardId)
{
  if (cardId != THUNDER_NYAN_NYAN)
    return FALSE;

  return OpponentControlsFaceUpShadowMonster();
}

void TryShowThunderNyanNyanDirectAttackText(u16 cardId)
{
  if (CanThunderNyanNyanAttackDirectly(cardId))
    ActivatePermanentEffectCardText(THUNDER_NYAN_NYAN);
}
