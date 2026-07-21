#include "global.h"
#include "common-chax.h"
#include "amazoness_queen.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"

static u8 ControllerHasFaceUpQueen(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == AMAZONESS_QUEEN)
      return TRUE;
  }

  return FALSE;
}

static u8 ControllerHasFaceUpEmpress(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == AMAZONESS_EMPRESS)
      return TRUE;
  }

  return FALSE;
}

u8 AmazonessQueen_PreventsBattleDestroy(const struct DuelCard *zone)
{
  u8 controller;

  if (zone == NULL || zone->id == CARD_NONE || !Duel_IsAmazonessCard(zone->id))
    return FALSE;

  controller = GetDuelistForZone((struct DuelCard *)zone);
  if (controller > DUEL_OPPONENT)
    return FALSE;

  if (ControllerHasFaceUpQueen(controller))
    return TRUE;

  /* Empress protects other Amazoness only. */
  if (zone->id != AMAZONESS_EMPRESS && ControllerHasFaceUpEmpress(controller))
    return TRUE;

  return FALSE;
}

unsigned char CanActivateAMAZONESS_QUEEN(void)
{
  if (gMonEffect.id != AMAZONESS_QUEEN)
    return FALSE;

  /* Continuous battle protection — not ignition-activatable. */
  return FALSE;
}

void ActivateAMAZONESS_QUEENEffect(void)
{
  Duel_ShowEffectTextTyped(AMAZONESS_QUEEN, 2);
}
