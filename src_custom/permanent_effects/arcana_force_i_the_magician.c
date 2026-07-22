#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 OpponentDuelist(u8 duelist)
{
  return duelist == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;
}

unsigned char ShouldActivateARCANA_FORCE_I_THE_MAGICIAN(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != ARCANA_FORCE_I_THE_MAGICIAN)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = SelfZone();
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  return TRUE;
}

void ActivateARCANA_FORCE_I_THE_MAGICIAN(void)
{
  struct DuelCard *zone;
  u8 duelist;
  u8 heads;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_I_THE_MAGICIAN, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL)
    return;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  heads = RandRangeU8(0, 1) == 1;
  zone->unk4 = 1;

  if (heads) {
    IncrementTempStage(zone);
    RefreshFieldMonsterStatOverlays();
    return;
  }

  Duel_ChangeLp(OpponentDuelist(duelist), 500, TRUE);
  /* ponytail: spell-trigger heads/tails not wired; on-summon coin only. */
}
