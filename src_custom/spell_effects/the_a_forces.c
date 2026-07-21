#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"
#include "the_a_forces.h"

#define THE_A_FORCES_ATK_PER 200

static u8 FixedDuelistForMonsterZone(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (zone == NULL || !Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &fixedCol))
    return 0xFF;

  return Duel_FixedDuelistForMonsterRow(fixedRow);
}

static u8 CountWarriorSpellcaster(u8 fixedDuelist)
{
  u8 col;
  u8 row;
  u8 count = 0;

  if (fixedDuelist > DUEL_OPPONENT)
    return 0;

  row = Duel_FixedMonsterRowForDuelist(fixedDuelist);
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
      continue;
    if (Duel_CardHasMonsterType(zone->id, TYPE_WARRIOR)
        || Duel_CardHasMonsterType(zone->id, TYPE_SPELLCASTER))
      count++;
  }

  return count;
}

void ApplyTheAForcesAtkBoostToCardInfo(const struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 count;

  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return;
  if (Duel_FindBackrowCard(DUEL_PLAYER, THE_A_FORCES, TRUE) == NULL
      && Duel_FindBackrowCard(DUEL_OPPONENT, THE_A_FORCES, TRUE) == NULL)
    return;
  if (!Duel_CardHasMonsterType(zone->id, TYPE_WARRIOR))
    return;

  fixedDuelist = FixedDuelistForMonsterZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;
  /* Only boost Warriors controlled by the A-Forces controller. */
  if (Duel_FindBackrowCard(fixedDuelist, THE_A_FORCES, TRUE) == NULL)
    return;

  count = CountWarriorSpellcaster(fixedDuelist);
  if (count == 0 || gCardInfo.atk == 0xFFFF)
    return;

  gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk + (u32)count * THE_A_FORCES_ATK_PER);
}

static void THE_A_FORCES_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(THE_A_FORCES);
}

APPEND_TEXT void EffectTHE_A_FORCES(void)
{
  if (Duel_TryResolveSpellThroughTraps(THE_A_FORCES, THE_A_FORCES_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
