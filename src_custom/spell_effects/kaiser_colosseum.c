#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "imperial_order.h"
#include "kaiser_colosseum.h"
#include "spell_effects.h"

static u8 ColosseumControllerForBackrowRow(u8 fixedBackrowRow)
{
  return fixedBackrowRow == OPPONENT_BACKROW ? DUEL_OPPONENT : DUEL_PLAYER;
}

u8 IsActivatedKaiserColosseumZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == KAISER_COLOSSEUM && zone->isFaceUp == TRUE;
}

static u8 FindActiveKaiserColosseumController(u8 *controller)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (!IsActivatedKaiserColosseumZone(zone))
        continue;
      if (IsImperialOrderNegatingSpell(KAISER_COLOSSEUM))
        continue;

      *controller = ColosseumControllerForBackrowRow(row);
      return TRUE;
    }
  }

  return FALSE;
}

u8 IsKaiserColosseumActiveOnField(void)
{
  u8 controller;

  return FindActiveKaiserColosseumController(&controller);
}

u8 KaiserColosseum_AllowsMonsterPlacement(u8 fixedMonsterRow)
{
  u8 controller;
  u8 placingDuelist;
  u8 controllerMonsterRow;
  u8 controllerMonsterCount;
  u8 placingMonsterCount;

  if (!Duel_IsFixedMonsterRow(fixedMonsterRow))
    return TRUE;

  if (!FindActiveKaiserColosseumController(&controller))
    return TRUE;

  placingDuelist = Duel_FixedDuelistForMonsterRow(fixedMonsterRow);
  if (placingDuelist == controller)
    return TRUE;

  controllerMonsterRow = Duel_FixedMonsterRowForDuelist(controller);
  controllerMonsterCount = Duel_CountMonstersOnFixedRow(controllerMonsterRow);
  if (controllerMonsterCount == 0)
    return TRUE;

  placingMonsterCount = Duel_CountMonstersOnFixedRow(fixedMonsterRow);
  return placingMonsterCount + 1 <= controllerMonsterCount;
}

APPEND_TEXT void EffectKaiserColosseum(void)
{
  struct DuelCard *zone;

  if (gSpellEffectData.row1 == PLAYER_BACKROW || gSpellEffectData.row1 == OPPONENT_BACKROW)
    zone = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  else
    zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(KAISER_COLOSSEUM);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void KaiserColosseum_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = KAISER_COLOSSEUM;
  zone.isFaceUp = TRUE;
  if (!IsActivatedKaiserColosseumZone(&zone))
    __builtin_trap();
  if (!KaiserColosseum_AllowsMonsterPlacement(PLAYER_MONSTER_ROW))
    __builtin_trap();
}
#endif
