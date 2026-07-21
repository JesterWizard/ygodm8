#include "global.h"
#include "common-chax.h"
#include "burden_of_the_mighty.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "mini_card.h"
#include "spell_effects.h"

#define BURDEN_OF_THE_MIGHTY_ATK_PER_LEVEL 100

static u8 BurdenActiveForOpponentOf(u8 monsterFixedDuelist)
{
  u8 burdenOwner = monsterFixedDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  return Duel_FindBackrowCard(burdenOwner, BURDEN_OF_THE_MIGHTY, TRUE) != NULL;
}

void ApplyBurdenOfTheMightyStatForZone(struct DuelCard *zone)
{
  u8 row;
  u8 col;
  u8 fixedDuelist;
  u8 level;
  u32 reduced;

  if (zone == NULL || zone->id == CARD_NONE || !ZoneShowsCombatStats(zone))
    return;

  if (!Duel_FindFixedZone(zone, &row, &col) || !Duel_IsFixedMonsterRow(row))
    return;

  fixedDuelist = Duel_FixedDuelistForMonsterRow(row);
  if (!BurdenActiveForOpponentOf(fixedDuelist))
    return;

  if (gCardInfo.atk == 0xFFFF)
    return;

  if (zone->id >= NUM_TOTAL_CARDS)
    return;

  level = gCardData_NEW[zone->id].level;
  reduced = (u32)gCardInfo.atk;
  if (reduced > (u32)level * BURDEN_OF_THE_MIGHTY_ATK_PER_LEVEL)
    reduced -= (u32)level * BURDEN_OF_THE_MIGHTY_ATK_PER_LEVEL;
  else
    reduced = 0;

  gCardInfo.atk = (u16)reduced;
}

static void BURDEN_OF_THE_MIGHTY_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(BURDEN_OF_THE_MIGHTY);
  RefreshFieldMonsterStatOverlays();
}

APPEND_TEXT void EffectBURDEN_OF_THE_MIGHTY(void)
{
  if (Duel_TryResolveSpellThroughTraps(BURDEN_OF_THE_MIGHTY, BURDEN_OF_THE_MIGHTY_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void BURDEN_OF_THE_MIGHTY_SelfCheck(void)
{
  if (BURDEN_OF_THE_MIGHTY_ATK_PER_LEVEL != 100)
    while (1)
      ;
}
#endif
