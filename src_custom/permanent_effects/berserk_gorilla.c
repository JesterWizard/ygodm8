#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "berserk_gorilla.h"

static u8 ZoneIsInDefensePosition(struct DuelCard *zone)
{
  return zone->isDefending || !zone->isFaceUp;
}

static void EnforceBerserkGorillaAttackPosition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != BERSERK_GORILLA)
    return;

  if (!ZoneIsInDefensePosition(zone))
    return;

  zone->isDefending = FALSE;
  zone->isFaceUp = TRUE;
  FlipCardFaceUp(zone);
}

u8 BerserkGorilla_CannotUseDefensePosition(u16 cardId)
{
  return cardId == BERSERK_GORILLA;
}

void TryEnforceBerserkGorillaOnMonsterPlacement(struct DuelCard *zone)
{
  EnforceBerserkGorillaAttackPosition(zone);
}

unsigned char ShouldActivateBerserkGorilla(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != BERSERK_GORILLA)
    return FALSE;

  if (gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return ZoneIsInDefensePosition(zone);
}

void ActivateBerserkGorilla(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  EnforceBerserkGorillaAttackPosition(zone);
  Duel_ShowEffectTextTyped(BERSERK_GORILLA, 8);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void BerserkGorilla_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = BERSERK_GORILLA;
  zone.isDefending = TRUE;
  zone.isFaceUp = TRUE;
  EnforceBerserkGorillaAttackPosition(&zone);
  if (zone.isDefending || !zone.isFaceUp)
    __builtin_trap();
}
#endif
