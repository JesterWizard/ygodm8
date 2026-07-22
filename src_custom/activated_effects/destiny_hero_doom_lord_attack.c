#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "destiny_hero_doom_lord.h"
#include "duel_helpers.h"

u8 DestinyHeroDoomLord_CanDeclareAttack(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != DESTINY_HERO_DOOM_LORD)
    return TRUE;

  return (zone->unk4 & DESTINY_HERO_DOOM_LORD_CANNOT_ATTACK_MARK) == 0;
}

void DestinyHeroDoomLord_ClearAttackLockAtEndPhase(void)
{
  u8 fixedRow;
  u8 col;

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_MONSTER_ROW; fixedRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[fixedRow][col];

      if (zone == NULL || zone->id != DESTINY_HERO_DOOM_LORD)
        continue;

      zone->unk4 &= (u8)~DESTINY_HERO_DOOM_LORD_CANNOT_ATTACK_MARK;
    }
  }
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DestinyHeroDoomLord_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = DESTINY_HERO_DOOM_LORD;
  zone.unk4 = DESTINY_HERO_DOOM_LORD_CANNOT_ATTACK_MARK;
  if (DestinyHeroDoomLord_CanDeclareAttack(&zone) != FALSE)
    __builtin_trap();
  zone.unk4 = 0;
  if (DestinyHeroDoomLord_CanDeclareAttack(&zone) == FALSE)
    __builtin_trap();
}
#endif
