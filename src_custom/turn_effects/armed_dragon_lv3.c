#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

static u8 MatchArmedDragonLv5(u16 cardId)
{
  return cardId == ARMED_DRAGON_LV5;
}

static u8 HandHasArmedDragonLv5(u8 turnDuelist)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnHands[turnDuelist][col]->id == ARMED_DRAGON_LV5)
      return TRUE;
  }

  return FALSE;
}

u8 ShouldActivateArmedDragonLv3TurnEffect(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != ARMED_DRAGON_LV3)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->id != ARMED_DRAGON_LV3 || !zone->isFaceUp)
    return FALSE;

  return HandHasArmedDragonLv5(ACTIVE_DUELIST)
      || Duel_FindDeckCardIndex(ACTIVE_DUELIST, ARMED_DRAGON_LV5) >= 0;
}

void ActivateArmedDragonLv3TurnEffect(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist;
  struct DuelSummonOpts opts;

  if (!ShouldActivateArmedDragonLv3TurnEffect())
    return;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  fixedDuelist = GetDuelistForZone(zone);

  Duel_ShowEffectTextTyped(ARMED_DRAGON_LV3, 9);
  if (IsDuelOver() == TRUE)
    return;

  ClearZoneAndSendMonToGraveyard2(zone, fixedDuelist);

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;

  if (HandHasArmedDragonLv5(ACTIVE_DUELIST)) {
    Duel_SpecialSummonFromHand(ACTIVE_DUELIST, ARMED_DRAGON_LV5, MatchArmedDragonLv5, opts);
    return;
  }

  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, ARMED_DRAGON_LV5, opts);
}
