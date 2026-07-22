#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dark_magician_the_dragon_knight.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

static u8 ControllerHasFaceUpDragonKnight(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == DARK_MAGICIAN_THE_DRAGON_KNIGHT)
      return TRUE;
  }

  return FALSE;
}

static u8 ZoneOwnerFixedDuelist(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (!Duel_FindFixedZone((struct DuelCard *)zone, &fixedRow, &col))
    return 0xFF;

  if (fixedRow == PLAYER_MONSTER_ROW || fixedRow == PLAYER_BACKROW)
    return DUEL_PLAYER;
  if (fixedRow == OPPONENT_MONSTER_ROW || fixedRow == OPPONENT_BACKROW)
    return DUEL_OPPONENT;

  return 0xFF;
}

u8 DarkMagicianTheDragonKnight_ProtectsSpellTrap(const struct DuelCard *zone)
{
  u8 controller;
  u8 typeGroup;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  controller = ZoneOwnerFixedDuelist(zone);
  if (controller > DUEL_OPPONENT)
    return FALSE;

  return ControllerHasFaceUpDragonKnight(controller);
}

unsigned char CanActivateDARK_MAGICIAN_THE_DRAGON_KNIGHT(void)
{
  if (gMonEffect.id != DARK_MAGICIAN_THE_DRAGON_KNIGHT)
    return FALSE;

  /* Name=Dark Magician via DarkMagicianTheDragonKnight_TreatsNameAsDarkMagician +
   * Duel_ZoneEffectCardId; S/T protect via DarkMagicianTheDragonKnight_ProtectsSpellTrap.
   * Not field-ignition. */
  return FALSE;
}

void ActivateDARK_MAGICIAN_THE_DRAGON_KNIGHTEffect(void)
{
  Duel_ShowEffectTextTyped(DARK_MAGICIAN_THE_DRAGON_KNIGHT, 2);
}
